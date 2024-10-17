#include "module.h"
#include "assembler/backend.h"
#include "assembler/instruction/instruction.h"
#include "assembler/instruction/operands/memory.h"
#include "utility/containers/dynamic_string.h"

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
		if(m_current_block.is_empty() == false) {
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

	auto module_t::operand_to_string(const operand& op) -> utility::dynamic_string {
		utility::dynamic_string result;

		// TODO: check 8 bit regs, they're probably wrong everywhere
		constexpr const char* r8_names[] = { "ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "al", "cl", "dl", "bl", "spl", "bpl", "sil", "dil" };
		constexpr const char* r32_names[] = { "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" };
		constexpr const char* r64_names[] = { "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" };

		switch(op.type) {
			case OP_EAX: result += "eax"; break;
			case OP_R8:  result += r8_names[op.r]; break;
			case OP_R32: result += r32_names[op.r]; break;
			case OP_R64: result += r64_names[op.r]; break;
			case OP_MEM:
			case OP_M8:
			case OP_M16:
			case OP_M32:
			case OP_M64: {
				const auto memory = op.memory;

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
	
				break;
			}
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
		utility::dynamic_string result;

		result += "digraph cfg {\n";
		// result += "\tconcentrate=true\n";
		result += "\tgraph [splines=ortho]\n";
		result += "\tnode [shape=plaintext fontname=\"monospace\"]\n";

		result += "\n";

		// generate nodes
		for(u64 i = 0; i < m_blocks.get_size(); ++i) {
			const instruction_block* block = m_blocks[i];

			result += "\t\"";
			result += utility::int_to_string(i);
			result += "\"[";
			result += "label=<<table border=\"1\" cellborder=\"0\" cellspacing=\"0\">";

			// if(block->name) {
			// 	utility::console::print("block: '{}':'{}'\n", i, *block->name);
			// 	result += "<tr><td align=\"left\">";
			// 	result += *block->name;
			// 	result += "</td></tr>";
			// 	result += "<tr><td></td></tr>";
			// 	result += "<tr><td></td></tr>";
			// 	result += "<tr><td></td></tr>";
			// }

			for(u64 j = 0; j < block->size; ++j) {
				const instruction_t* inst = block->instructions[j];
				const instruction* inst_actual = &instruction_db[inst->index];

				result += "<tr PORT=\"p";
				result += utility::int_to_string(j);
				result += "\"><td align=\"left\" ";
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
			}

			result += "</table>>]\n";
		}

		result += "\n";

		// generate edges
		for(u64 i = 0; i < m_blocks.get_size(); ++i) {
			const instruction_block* block = m_blocks[i];
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
			bool in;
			bool out;
		};

		// blocks which have an edge leading into them
		utility::dynamic_array<edge> edge_connections(m_blocks.get_size(), { false, false });
		utility::dynamic_array<instruction_block*> blocks;

		m_current_start_position = 0;
		m_current_segment_length = 0;
		m_current_block.clear();

		// calculate edge connections
		for(u64 i = 0; i < m_blocks.get_size(); ++i) {
			const instruction_block* block = m_blocks[i];
			const instruction_t* last_inst = block->instructions[block->size - 1];

			if(is_jump_or_branch_inst(last_inst->index)) {
				// TODO: check if its an actual symbol
				// BRANCH_IN always has a priority
				edge_connections[m_symbols.at(last_inst->operands[0].symbol).block_index].in = true; // branch - pass case - incoming edge

				if(i < m_blocks.get_size() - 1) {
					edge_connections[i + 1].in = true; // branch - fail case - incoming edge (next block)
				}

				edge_connections[i].out = true; // a branch instruction always outputs somewhere - mark us as having an outgoing edge
			}
		}

		// generate new blocks 
		for(u64 i = 0; i < edge_connections.get_size(); ++i) {
			const instruction_block* block = m_blocks[i];
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
		
		utility::memcpy(instructions, m_current_block.get_data(), instruction_memory);

		m_current_start_position += m_current_segment_length;
		m_current_segment_length = 0;

		m_current_block.clear();
		return new_block;
	}
} // namespace baremetal::assembler
