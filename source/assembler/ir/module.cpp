#include "module.h"
#include "assembler/backend.h"
#include "assembler/instruction/instruction.h"
#include "assembler/instruction/operands/memory.h"
#include "utility/containers/dynamic_string.h"

#include <utility/algorithms/sort.h>

namespace baremetal::assembler {
  module_t::module_t(context* ctx) : m_ctx(ctx) {}

  void module_t::add_instruction(const operand* operands, u32 index, u8 size) {
    instruction_t* instruction = m_ctx->allocator.emplace<instruction_t>();

    instruction->operands[0] = operands[0];
    instruction->operands[1] = operands[1];
    instruction->operands[2] = operands[2];
    instruction->operands[3] = operands[3];

    instruction->index = index;
		instruction->size = size;

		m_current_segment_length += size;

    m_current_block.push_back(instruction);
  }

	void module_t::add_symbol(utility::string_view* name) {
		// utility::console::print("add symbol '{}' ({})\n", *name, m_blocks.get_size());
		m_symbols[name] = { m_current_segment_length, m_blocks.get_size() };
	}

	void module_t::begin_block(utility::string_view* name) {
		if(m_current_block.is_empty() == false || m_current_block_name) {
			m_blocks.push_back(create_new_block());
		}	

		m_current_block_name = name;
	}

	auto module_t::register_to_string(reg r) -> const char* {
		constexpr const char* r8_names[] = { "ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "al", "cl", "dl", "bl", "spl", "bpl", "sil", "dil" };
		constexpr const char* r32_names[] = { "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" };
		constexpr const char* r64_names[] = { "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" };

		switch(r.type) {
			case REG_R8:  return r8_names[r.index];
			case REG_R32: return r32_names[r.index];
			case REG_R64: return r64_names[r.index];
			default: return "unknown reg class";
		}
	}

	auto module_t::immediate_to_string(imm i) -> utility::dynamic_string {
		utility::dynamic_string result;

		if(i.sign) {
			result += '-';
			result += utility::int_to_string(~i.value + 1); 
		}
		else {
			result += utility::int_to_string(i.value); 
		}

		return result;
	}

	auto module_t::memory_to_string(mem memory) -> utility::dynamic_string {
		utility::dynamic_string result;
		result += '[';
		
		if(memory.has_base) {
			result += register_to_string(memory.base);

			if(memory.has_index || memory.s != SCALE_1 || (memory.displacement.value != 0 && memory.displacement.sign == false)) {
				result += '+';
			}
		}

		if(memory.has_index) {
			result += register_to_string(memory.index);

			if(memory.s != SCALE_1 || (memory.displacement.value != 0 && memory.displacement.sign == false)) {
				result += '+';
			}
		}

		switch(memory.s) {
			case SCALE_1: break;
			case SCALE_2: result += "2"; break;
			case SCALE_4: result += "4"; break;
			case SCALE_8: result += "8"; break;
			default: ASSERT(false, "invalid scale specified\n");
		}

		if(memory.s != SCALE_1 && memory.displacement.value != 0 && memory.displacement.sign == false) {
			result += '+';
		}

		if(memory.displacement.value != 0) {
			result += immediate_to_string(memory.displacement);
		}

		result += ']';
		return result;
	}

	auto module_t::operand_to_string(const operand& op) -> utility::dynamic_string {
		utility::dynamic_string result;

		// TODO: check 8 bit regs, they're probably wrong everywhere
		constexpr const char* r8_names[] = { "ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "al", "cl", "dl", "bl", "spl", "bpl", "sil", "dil" };
		constexpr const char* r32_names[] = { "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" };
		constexpr const char* r64_names[] = { "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" };

		switch(op.type) {
			case OP_RAX: result += "rax"; break;
			case OP_EAX: result += "eax"; break;
			case OP_R8:  result += r8_names[op.r]; break;
			case OP_R32: result += r32_names[op.r]; break;
			case OP_R64: result += r64_names[op.r]; break;
			case OP_MEM:
			case OP_M8:  result += "byte " + memory_to_string(op.memory); break;
			case OP_M16: result += "word " + memory_to_string(op.memory); break;
			case OP_M32: result += "dword " + memory_to_string(op.memory); break;
			case OP_M64: result += "qword " + memory_to_string(op.memory); break;
			case OP_HIDDEN: result += *op.symbol; break; // TODO: this can break with special instructions, rename 
			case OP_I8:
			case OP_I16:
			case OP_I32:
			case OP_I64: {
				result += immediate_to_string(op.immediate);
				break;
			}
			default: utility::console::print_err("unhandled operand type '{}'\n", operand_type_to_string(op.type));
		}

		return result;
	}

	auto module_t::emit_graph() -> utility::dynamic_string {
		simplify_cfg();
		optimize_instruction_size();
		recalculate_block_sizes();

		utility::dynamic_string result;

		result += "digraph cfg {\n";
		// result += "\tconcentrate=true\n";
		result += "\tgraph [splines=ortho]\n";
		result += "\tnode [shape=plaintext fontname=\"monospace\"]\n";
		result += "\tedge [penwidth=2.0]\n";

		result += "\n";

		// generate nodes
		for(u64 i = 0; i < m_blocks.get_size(); ++i) {
			const instruction_block* block = m_blocks[i];

			result += "\t\"";
			result += utility::int_to_string(i);
			result += "\"[";
			result += "label=<<table border=\"1\" cellborder=\"0\" cellspacing=\"0\">";

			if(block->size == 0 && block->name) {
				// just a label with incoming edges, no instructions
				result += "<tr><td align=\"left\"><font color=\"blue\">";
				result += *block->name;
				result += "</font></td></tr>";
			}

			u64 local_pos = 0;

			for(u64 j = 0; j < block->size; ++j) {
				const instruction_t* inst = block->instructions[j];
				const instruction* inst_actual = &instruction_db[inst->index];

				result += "<tr PORT=\"p";
				result += utility::int_to_string(j);
				result += "\"><td align=\"left\" width=\"50px\">";
				result += utility::int_to_string(block->start_position + local_pos);
				result += "</td><td align=\"left\" ";
				result += " width=\"100px\">";
				result += inst_actual->name;
				result += "</td><td ";
				result += "align=\"left\">";

				for(u8 k = 0; k < inst_actual->operand_count; ++k) {
					result += operand_to_string(inst->operands[k]);

					if(k + 1 != inst_actual->operand_count) {
						result += ", ";
					}
				}
				
				result += "</td></tr>";
				local_pos += inst->size;
			}

			result += "</table>>]\n";
		}

		result += "\n";

		// generate edges
		for(u64 i = 0; i < m_blocks.get_size(); ++i) {
			const instruction_block* block = m_blocks[i];

			if(block->size == 0) {
				continue;
			}

			const instruction_t* inst = block->instructions[block->size - 1];

			// branch edges
			if(is_jump_or_branch_inst(inst->index)) {
				bool to_same_block = i == m_symbols.at(inst->operands[0].symbol).block_index;

				result += "\t\"";
				result += utility::int_to_string(i);
				result += "\":p";
				result += utility::int_to_string(block->size - 1);
				result += ":s -> ";
				result += "\"";
				result += utility::int_to_string(m_symbols.at(inst->operands[0].symbol).block_index);
				result += "\":p0";
				result += ":n [color=\"darkgreen\"";
				result += to_same_block ? "dir=back" : "";
				result += "]";
				result += "\n";
			}
	
			// edges to following blocks 
			// TODO: make this smarter, currently it always draws this, but if a jmp without a condition is present 
			//       we shouldn't create these
			if(i != m_blocks.get_size() - 1) {
				result += "\t\"";
				result += utility::int_to_string(i);
				result += "\":s -> ";
				result += "\"";
				result += utility::int_to_string(i + 1);
				result += "\":n [color=\"";
				result += is_jump_or_branch_inst(inst->index) ? "red" : "blue";
				result += "\"]\n";
			}
		}

		result += "}\n";

		return result;
	}

	void module_t::simplify_cfg() {
		struct edge {
			u32 in;
			u32 out;
		};

		// blocks which have an edge leading into them
		utility::dynamic_array<edge> edge_connections(m_blocks.get_size(), { 0, 0 });
		utility::dynamic_array<instruction_block*> blocks;

		m_current_block_name = nullptr;
		m_current_start_position = 0;
		m_current_segment_length = 0;
		m_current_block.clear();

		// calculate edge connections
		for(u64 i = 0; i < m_blocks.get_size(); ++i) {
			const instruction_block* block = m_blocks[i];

			if(block->size == 0) {
				continue; 
			}

			const instruction_t* last_inst = block->instructions[block->size - 1];

			if(is_jump_or_branch_inst(last_inst->index)) {
				// TODO: check if its an actual symbol
				// BRANCH_IN always has a priority
				edge_connections[m_symbols.at(last_inst->operands[0].symbol).block_index].in++; // branch - pass case - incoming edge

				if(i < m_blocks.get_size() - 1) {
					edge_connections[i + 1].in++; // branch - fail case - incoming edge (next block)
				}

				edge_connections[i].out++; // a branch instruction always outputs somewhere - mark us as having an outgoing edge
			}
		}

		// generate new blocks 
		for(u64 i = 0; i < edge_connections.get_size(); ++i) {
			const instruction_block* block = m_blocks[i];
			utility::console::print("block {}: {} inputs, {} outputs\n", i, edge_connections[i].in, edge_connections[i].out);
			m_current_block_name = block->name;

			// if there is an block with inputs leading into it we first have to push the block data we've gathered so far, and then
			// push the data in the block with the edge leading into it

			if(edge_connections[i].in && m_current_block.is_empty() == false) {
				// push the last block first, if there is anything in it
				blocks.push_back(create_new_block());
			}
		
			// append the instructions from the current block
			m_current_block.insert(m_current_block.end(), block->instructions, block->instructions + block->size);
			m_current_segment_length += block->lenght;

			// recalculate symbol positions (this has to be done before pushing the next block, otherwise we desync) 
			for(auto& [symbol, location] : m_symbols) {
				if(location.block_index == i) {
					location.block_index = blocks.get_size();
				}
			}

			if((edge_connections[i].out && edge_connections[i].in) || i == edge_connections.get_size() - 1) {
				// push the current block
				blocks.push_back(create_new_block());
			}
		}

		m_blocks = blocks;
	}

	auto module_t::create_new_block() -> instruction_block* {
		instruction_block* new_block = m_ctx->allocator.emplace<instruction_block>();
		u64 instruction_memory = sizeof(instruction_t*) * m_current_block.get_size();
		instruction_t** instructions = static_cast<instruction_t**>(m_ctx->allocator.allocate(instruction_memory));

		new_block->instructions = instructions;
		new_block->size = m_current_block.get_size();
		new_block->lenght = m_current_segment_length;
		new_block->start_position = m_current_start_position;
		new_block->name = m_current_block_name;
		
		utility::memcpy(instructions, m_current_block.get_data(), instruction_memory);

		m_current_start_position += m_current_segment_length;
		m_current_segment_length = 0;

		m_current_block.clear();
		return new_block;
	}

	auto get_instruction_using_magic(instruction_t* inst, const imm& imm_op) -> bool {
		ASSERT(instruction_db[inst->index].has_magic(), "instruction does not have a magic number\n");
		const u16 context_index = instruction_db[inst->index].get_magic_index();

		// switch on the context kind
		switch(instruction_db[inst->index].get_magic_kind()) {
			case 0: {
				// if we have a destination which uses a 64 bit register, and an operand which fits into 32 bits or
				// less we can look for a smaller destination
				if(inst->operands[0].type == OP_R64 && imm_op.min_bits <= 32) {
					// verify if it's safe to zero extend the operand (since we're implicitly going from 32 to 64
					// bits) we can't zero extend 
					if(imm_op.sign == false) {
						inst->index = context_index;
						return true;
					}
				}

				break;
			}
			case 1: {
				// if we have a source operand which is equal to 1, we can use a shorter encoding, in basically all
				// cases we can just return, since the operand is effectively removed
				if(inst->operands[1].immediate.value == 1) {
					inst->index = context_index;
					return true;
				}

				break; // we're not using the optimization index, continue
			}
			case 2: {
				// truncate to 8 bits, this is only used with imul instructions
				const u64 truncated = inst->operands[2].immediate.value & 0b011111111;
				const u64 extend = detail::sign_extend(truncated, 8);

				if(extend == inst->operands[2].immediate.value) {
					inst->index = context_index;
					return true;
				}

				break;
			}
			default: ASSERT(false, "unknown context kind");
		}

		return false;
	}

	void module_t::optimize_instruction_size(instruction_t* inst) {
		u8 operand_index = utility::limits<u8>::max();
		bool has_unresolved = false;

		// locate the first unresolved/immediate operand
		for(u8 i = 0; i < 4; ++i) {
			if(is_operand_imm(inst->operands[i].type)) {
				operand_index = i;
				break;
			}
			else if(inst->operands[i].unknown) {
				has_unresolved = true;
				operand_index = i;
				break;
			}
		}

		if(operand_index == utility::limits<u8>::max()) {
			// no 'special' operand which we could optimize, return
			return;
		}

		const imm& imm_op = inst->operands[operand_index].immediate;
		u32 legal_variants[5];
		u8 legal_variants_index = 0;

		// some instructions have a special optimization index, check if we have it
		if(instruction_db[inst->index].has_magic() && has_unresolved == false) {
			if(get_instruction_using_magic(inst, imm_op)) {
				return;
			}
		}

		// locate all legal variants of our instruction
		u32 current_index = inst->index;

		while(is_legal_variant(inst->index, current_index, operand_index)) {
			legal_variants[legal_variants_index++] = current_index++;
		}

		// sort by the smallest source operands, we need to do this for cases where one of the
		// variants has a destination operand which isn't a generic register, but a specific
		// one (ie. an ax register). In these cases we lose the guarantee of them being sorted
		// from smallest to biggest immediate operands, hence we have to sort them.
		utility::stable_sort(legal_variants, legal_variants + legal_variants_index, [=](auto a, auto b) {
			const instruction* a_inst = &instruction_db[a];
			const instruction* b_inst = &instruction_db[b];

			const u16 a_width = get_operand_bit_width(a_inst->operands[operand_index]);
			const u16 b_width = get_operand_bit_width(b_inst->operands[operand_index]);

			return a_width < b_width;
		});

		if(has_unresolved) {
			// instructions with unresolved operands can just use the largest variant
			ASSERT(legal_variants_index > 0, "no variants found\n");
			inst->index = legal_variants[legal_variants_index - 1];
			return;
		}

		// multiple legal variants, determine the best one (since our data is sorted from smallest
		// source operands to largest, we can exit as soon as we get a valid match)
		for(u32 index : legal_variants) {
			const instruction* curr = &instruction_db[index];

			const u16 src_bits = get_operand_bit_width(curr->operands[operand_index]);
			const u16 dst_bits = get_operand_bit_width(curr->operands[0]);

			// check if there is a possibility of sign extending the immediate
			if(src_bits < dst_bits) {
				ASSERT(src_bits <= utility::limits<u8>::max(), "invalid bit range\n");

				// assume we're sign extending
				if(detail::sign_extend_representable(imm_op.value, static_cast<u8>(src_bits))) {
					inst->index = index;
					return;
				}
			}

			// check if the source operand is representable with a smaller immediate
			if(src_bits >= imm_op.min_bits) {
				inst->index = index;
				return;
			}
		}

		ASSERT(false, "faulty instruction received\n");
	}

	void module_t::recalculate_block_sizes() {
		u64 position = 0;
		u64 size = 0;

		for(instruction_block* block : m_blocks) { 
			for(u64 i = 0; i < block->size; ++i) {
				size += block->instructions[i]->size;
			}

			block->start_position = position;
			block->lenght = size; 

			position += size;
			size = 0;
		}
	}

	void module_t::optimize_instruction_size() {
		for(const instruction_block* block : m_blocks) {
			for(u64 i = 0; i < block->size; ++i) {
				instruction_t* inst = block->instructions[i];
				u32 old_index = inst->index;
				optimize_instruction_size(inst);

				if(inst->index != old_index) {
					// HACK: recalculate the size, this needs to be done in a different way
					// u8 old_size = inst->size;
					inst->size = backend::emit_instruction(&instruction_db[inst->index], inst->operands).size;
					// utility::console::print("inst optimized {}B -> {}B\n", old_size, inst->size);
				}
			}
		}
	}
} // namespace baremetal::assembler
