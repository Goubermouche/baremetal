#include "module.h"
#include "assembler/backend.h"
#include "assembler/instruction/instruction.h"
#include "assembler/instruction/operands/memory.h"
#include "assembler/instruction/operands/operands.h"
#include "utility/containers/dynamic_string.h"

#include <utility/algorithms/sort.h>

namespace baremetal::assembler {
  module_t::module_t(context* ctx) : m_ctx(ctx) {
		set_section(m_ctx->strings.add(".text"));
	}

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
		utility::console::print("add symbol '{}' ({}, section # {})\n", *name, m_blocks.get_size(), m_current_section);
		m_symbols[name] = { m_current_segment_length, m_blocks.get_size(), m_current_section };
	}

	void module_t::set_section(utility::string_view* name) {
		u64 new_index;

		for(u64 i = 0; i < m_sections.get_size(); ++i) {
			if(name == m_sections[i]) {
				new_index = i;
				break;
			}
		}

		new_index = m_sections.get_size();
		m_sections.push_back(name);

		// force a new block
		if(new_index != m_current_section) {
			if(!m_current_block.is_empty()) {
				m_blocks.push_back(create_new_block(instruction_block::INSTRUCTION));
			}

			m_current_section = new_index;
		}
	}

	void module_t::begin_block(instruction_block::type ty, utility::string_view* name) {
		if(ty == instruction_block::INSTRUCTION) {
			if(m_current_block.is_empty()) {
				return;
			}
		}

		m_current_block_name = name;
		m_blocks.push_back(create_new_block(ty));
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

		if(op.symbol) {
			result += *op.symbol;
			return result;
		}

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
			// case OP_HIDDEN: result += *op.symbol; break; // TODO: this can break with special instructions, rename 
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

	auto bytes_to_string(const u8* bytes, u8 count) -> utility::dynamic_string {
		utility::dynamic_string result;
		result.reserve(count * 3);

		constexpr char digits[] = "0123456789abcdef";

		for(u64 i = 0; i < count; ++i) {
			const u8 value = bytes[i];
			result += (digits[(value >> 4) & 0x0F]);
			result += (digits[value & 0x0F]);
			result += ' ';
		}

		return result;
	}

	auto module_t::instruction_block_to_string(const instruction_block* block) {
		utility::dynamic_string result;
		u64 local_pos = 0;
		
		for(u64 j = 0; j < block->size; ++j) {
			const instruction_t* inst = block->instructions[j];
			const instruction* inst_actual = &instruction_db[inst->index];

			operand temp_operands[4];
			utility::memcpy(temp_operands, inst->operands, sizeof(operand) * 4);

			// resolve symbols
			for(u8 i = 0; i < inst_actual->operand_count; ++i) {
				if(temp_operands[i].symbol) { // TODO: get rid of the HIDDEN type
					// resolve
					u64 symbol_block = m_symbols.at(temp_operands[i].symbol).block_index;
					temp_operands[i].immediate = imm(m_blocks[symbol_block]->start_position);
					// utility::console::print("{}\n", operand_type_to_string(temp_operands[i].type));
				}
			}

			auto data = backend::emit_instruction(inst_actual, temp_operands);
		
			result += "<tr><td align=\"left\" width=\"50px\">";
			result += utility::int_to_string(block->start_position + local_pos);
			result += "</td><td align=\"left\" width=\"100px\">";
			result += bytes_to_string(data.data, data.size);
			result += "</td><td align=\"left\" width=\"100px\"><font COLOR=\"black\"><b>";
			result += inst_actual->name;
			result += "</b></font></td><td align=\"left\"><font COLOR=\"black\"> ";
		
			for(u8 k = 0; k < inst_actual->operand_count; ++k) {
				result += operand_to_string(inst->operands[k]);
		
				if(k + 1 != inst_actual->operand_count) {
					result += ", ";
				}
			}
			
			result += "</font></td></tr>";
			local_pos += inst->size;
		}


		return result;
	}

	auto module_t::emit_graph() -> utility::dynamic_string {
		simplify_cfg();
		optimize_instruction_size();
		recalculate_block_sizes();
		optimize_symbol_resolutions();

		utility::dynamic_string result;

		result += "digraph cfg {\n";
		// result += "\tconcentrate=true\n";
		result += "\tgraph [splines=ortho]\n";
		result += "\tnode [shape=plaintext fontname=\"monospace\"]\n";
		result += "\tedge [penwidth=2.0]\n";

		result += "\n";

		struct edge {
			enum edge_type {
				BRANCH_PASS,
				BRANCH_FAIL,
				FALLTHROUGH
			};

			edge_type type;
			u64 from;
			u64 to;
		};

		// generate node
		utility::dynamic_array<edge> edges;
		bool next_is_new_segment = true;
		u64 current_id = 0;

		for(u64 i = 0; i < m_blocks.get_size(); ++i) {
			const instruction_block* block = m_blocks[i];

			if(block->new_segment || next_is_new_segment) {
				if(i > 0) {
					result += "<tr PORT=\"bottom\"><td></td></tr>";
					result += "</table>>]\n";
				}

				result += "\t\"";
				result += utility::int_to_string(i);
				result += "\"[";
				result += "label=<<table border=\"1\" cellborder=\"0\" cellspacing=\"0\">";
				result += "<tr PORT=\"top\"><td></td></tr>";
				next_is_new_segment = false;
				current_id = i;
			}

			switch(block->ty) {
				case instruction_block::LABEL: {
					result += "<tr><td align=\"left\">";
					result += utility::int_to_string(block->start_position);
					result += "</td><td></td><td COLSPAN=\"100%\" align=\"left\"><b><font color=\"blue\">";
					result += *block->name;
					result += "</font></b></td></tr>";
					break;
				}
				case instruction_block::INSTRUCTION: {
					result += instruction_block_to_string(block);
					break;
				}
				case instruction_block::BRANCH: {
					result += instruction_block_to_string(block);
					next_is_new_segment = true;
					break;
				}
			}

			if(block->size == 0) {
				continue;
			}

			const instruction_t* inst = block->instructions[block->size - 1];
			bool is_branch = false;

			if(is_jump_or_branch_inst(inst->index)) {
				edges.push_back({ edge::BRANCH_PASS, current_id, m_symbols.at(inst->operands[0].symbol).block_index });
				is_branch = true;
			}

			if(i != m_blocks.get_size() - 1 && (next_is_new_segment || m_blocks[i + 1]->new_segment)) {
				edges.push_back({ is_branch ? edge::BRANCH_FAIL : edge::FALLTHROUGH, current_id, i + 1});	
			}
		}

		result += "</table>>]\n";
		result += "\n";

		for(auto edge : edges) {
			result += "\t\"";
			result += utility::int_to_string(edge.from);
			result += "\":bottom:s -> \"";
			result += utility::int_to_string(edge.to);
			result += "\":top:n [color=\"";

			switch(edge.type) {
				case edge::BRANCH_PASS: result += "darkgreen"; break;
				case edge::BRANCH_FAIL: result += "red"; break;
				case edge::FALLTHROUGH: result += "black"; break;
			}

			result += "\"";

			if(edge.from == edge.to) {
				result += "dir=back";
			}

			result += "]\n";
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
			utility::console::print("[CFGSIMPLIFY] block {}: {} inputs, {} outputs\n", i, edge_connections[i].in, edge_connections[i].out);
			m_current_block_name = block->name;
			m_current_section = block->section_index;
			m_current_block.insert(m_current_block.end(), block->instructions, block->instructions + block->size);

			switch(block->ty) {
				case instruction_block::LABEL: {
					auto new_block = create_new_block(block->ty);
					new_block->new_segment = edge_connections[i].in > 0;
					blocks.push_back(new_block);
					break;
				}
				case instruction_block::INSTRUCTION: {
					auto new_block = create_new_block(block->ty);
					blocks.push_back(new_block);
					break;
				}
				case instruction_block::BRANCH: {
					auto new_block = create_new_block(block->ty);
					blocks.push_back(new_block);
					break;
				}
			}
		}

		for(u64 i = 0; i < m_blocks.get_size(); ++i) {
			const instruction_block* block = m_blocks[i];

			if(block->ty == instruction_block::LABEL) {
				m_symbols[block->name].block_index = i;
			}
		}

		m_blocks = blocks;
	}

	auto module_t::create_new_block(instruction_block::type ty) -> instruction_block* {
		instruction_block* new_block = m_ctx->allocator.emplace<instruction_block>();
		u64 instruction_memory = sizeof(instruction_t*) * m_current_block.get_size();
		instruction_t** instructions = static_cast<instruction_t**>(m_ctx->allocator.allocate(instruction_memory));

		new_block->instructions = instructions;
		new_block->size = m_current_block.get_size();
		new_block->lenght = m_current_segment_length;
		new_block->start_position = m_current_start_position;
		new_block->name = m_current_block_name;
		new_block->ty = ty;
		new_block->new_segment = false;
		new_block->section_index = m_current_section;
		
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

		for(auto& [symbol, location] : m_symbols) {
			location.position = m_blocks[location.block_index]->start_position;
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

	auto fits_into_type(i64 value, operand_type type) -> bool {
		switch(type) {
			case OP_REL8:
			case OP_REL8_RIP:  return value >= utility::limits<i8>::min() && value <= utility::limits<i8>::max();
			case OP_REL16_RIP: return value >= utility::limits<i16>::min() && value <= utility::limits<i16>::max();
			case OP_REL32:     return value >= utility::limits<i32>::min() && value <= utility::limits<i32>::max();
			default: ASSERT(false, "unexpected operand type {}\n", operand_type_to_string(type));
		}

		return false;
	}

	void module_t::optimize_symbol_resolutions() {
		struct unresolved {
			u64 block_index;
			u64 instruction_index;
			u8 unresolved_index;
			u64 position;
			utility::dynamic_array<inst_variant> variants;
		};

		utility::dynamic_array<unresolved> indices;

		// locate all references to symbols
		for(u64 i = 0; i < m_blocks.get_size(); ++i) {
			const instruction_block* block = m_blocks[i];

			for(u64 j = 0; j < block->size; ++j) {
				instruction_t* inst = block->instructions[j];
				u64 local_position = 0;

				for(u8 k = 0; k < 4; ++k) {
					if(inst->operands[k].symbol) {
						const auto symbol_it = m_symbols.find(inst->operands[k].symbol);

						if(symbol_it->second.section_index == block->section_index) {
							// we can only optimize references to symbols in the same section
							auto variants = backend::get_variants_i(inst->index, inst->operands);

							auto last = variants.pop_back();
							inst->operands[k].type = last.type;
							inst->index = last.index;
							inst->size = backend::emit_instruction(&instruction_db[inst->index], inst->operands).size;

							if(!is_operand_rel(inst->operands[k].type)) {
								variants.clear(); // no potential for optimizations
							}

							indices.push_back({i, j, k, local_position, variants });
						}
						else {
							utility::console::print("[SYMRES] skipping non-local symbol reference to symbol '{}'\n", *inst->operands[k].symbol);
						}

						break;
					}
				}

				local_position += inst->size;
			}
		}

		utility::console::print("[SYMRES] found {} unresolved symbols:\n", indices.get_size());

		for(const auto& unres : indices) {
			instruction_t* current_inst = m_blocks[unres.block_index]->instructions[unres.instruction_index];
			operand& unresolved = current_inst->operands[unres.unresolved_index];
			utility::console::print("[SYMRES] '{}' ({} variants)\n", *unresolved.symbol, unres.variants.get_size());
		}

		bool change = true;
		recalculate_block_sizes();

		// greedy optimizations
		while(change) {
			change = false;

			for(unresolved& unres : indices) {
				if(unres.variants.is_empty()) {
					continue;
				}

				instruction_t* current_inst = m_blocks[unres.block_index]->instructions[unres.instruction_index];
				operand& unresolved = current_inst->operands[unres.unresolved_index];
				const auto symbol_it = m_symbols.find(unresolved.symbol);

				const i64 distance = symbol_it->second.position - unres.position + current_inst->size;
				const operand_type new_type = unres.variants.get_last().type;

				if(!fits_into_type(distance, new_type)) {
					// we can't use a smaller operand, no optimization possible in this iteration
					continue;
				}
				
				// use the next smallest operand instead
				unresolved.type = new_type;
				
				u8 new_size = backend::emit_instruction(&instruction_db[unres.variants.get_last().index], current_inst->operands).size;

				utility::console::print("[SYMRES] reference to '{}' optimized {} -> {}\n", *unresolved.symbol, current_inst->size, new_size);
				
				current_inst->size = new_size;
				current_inst->index = unres.variants.get_last().index;
				change = true;

				unres.variants.pop_back();

				// update our symbol table to account for the difference in code length
				recalculate_block_sizes();

				// TODO: investigate whether it's better to break immediately or to continue
				break;
			}
		}
	}

	auto module_t::emit_binary() -> utility::dynamic_array<u8> {
		utility::dynamic_array<u8> bytes;

		// TODO: dumb
		for(u64 i = 0; i < m_sections.get_size(); ++i) {
			// append alignment bytes for the previous section
			const u64 alignment_offset = utility::align(bytes.get_size(), 4) - bytes.get_size();
			u64 inst_pos = 0;

			for(u64 i = 0; i < alignment_offset; ++i) {
				bytes.push_back(0);
			}

			for(instruction_block* block : m_blocks) {
				if(block->section_index != i) {
					continue;
				}

				for(u64 j = 0; j < block->size; ++j) {
					instruction_t* inst = block->instructions[j];
					const instruction* inst_actual = &instruction_db[inst->index];

					operand temp_operands[4];
					utility::memcpy(temp_operands, inst->operands, sizeof(operand) * 4);

					// resolve symbols
					for(u8 i = 0; i < inst_actual->operand_count; ++i) {
						if(temp_operands[i].symbol) { // TODO: get rid of the HIDDEN type
							// resolve
							symbol sym = m_symbols.at(temp_operands[i].symbol);
							i64 value;


							if(!is_operand_rel(temp_operands[i].type)) {
								value = sym.position;
							}
							else {
								utility::console::print("new {} @ {}\n", *temp_operands[i].symbol, inst_pos);
								if(block->section_index == sym.section_index) {
									// same sections
									value = sym.position - (inst_pos + inst->size);
								}
								else {
									// different sections
									ASSERT(false, "todo\n");
								}
							}
						
							temp_operands[i].immediate = imm(value);
							// utility::console::print("{}\n", operand_type_to_string(temp_operands[i].type));
						}
						
					}

					inst_pos += inst->size;

					auto data = backend::emit_instruction(inst_actual, temp_operands);
					bytes.insert(bytes.end(), data.data, data.data + data.size);
				}
			}
		}

		return bytes;
	}
} // namespace baremetal::assembler
