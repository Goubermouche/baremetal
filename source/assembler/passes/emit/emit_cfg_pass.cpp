#include "emit_cfg_pass.h"

#include "assembler/ir/module.h"
#include "assembler/backend.h"
#include "utility/containers/dynamic_string.h"

namespace baremetal::assembler::pass {
	namespace detail {
		auto instruction_block_to_string(const instruction_block* block, const module_t& module) -> utility::dynamic_string {
			utility::dynamic_string string;
			operand operands[4];
			u64 position = 0;

			for(u64 i = 0; i < block->size; ++i) {
				const instruction_t* inst_ir = block->instructions[i];
				const instruction*   inst    = &instruction_db[inst_ir->index];

				// copy operands so that we don't modify the actual values
				utility::memcpy(operands, inst_ir->operands, sizeof(operand) * 4);

				// resolve symbols
				for(u8 j = 0; j < inst->operand_count; ++j) {
					if(operands[j].symbol) {
						auto it = module.m_symbols.find(operands[j].symbol);

						ASSERT(it != module.m_symbols.end(), "invalid operand symbol detected ('{}')\n", *operands[j].symbol);
						i64 value = 0;

						if(!is_operand_rel(operands[j].type)) {
							value = it->second.position;
						}
						else {
							if(block->section_index == it->second.section_index) {
								// same sections
								value = it->second.position - (position + inst_ir->size);
							}
							else {
								// different sections
								ASSERT(false, "todo\n");
								value = 0;
							}
						}

						operands[j].immediate = imm(value);
					}
				}

				auto data = backend::emit_instruction(inst, operands);
				string += "<tr><td align=\"left\" width=\"50px\">";
				string += utility::int_to_string(block->start_position + position);
				string += "</td><td align=\"left\" width=\"100px\">";
				string += bytes_to_string(data.data, data.size);
				string += "</td><td align=\"left\" width=\"100px\"><font COLOR=\"black\"><b>";
				string += inst->name;
				string += "</b></font></td><td align=\"left\"><font COLOR=\"black\"> ";

				for(u8 j = 0; j < inst->operand_count; ++j) {
					string += operand_to_string(inst, inst_ir->operands[j], j);
			
					if(j + 1 != inst->operand_count) {
						string += ", ";
					}
				}
				
				string += "</font></td></tr>";
				position += inst_ir->size;
			}

			return string;
		}

		auto operand_to_string(const instruction* inst, const operand& op, u8 index) -> utility::dynamic_string {
			utility::dynamic_string string;
			
			if(op.symbol) {
				string += *op.symbol;
				return string;
			}

			switch(op.type) {
				case OP_RAX: string += "rax"; break;
				case OP_EAX: string += "eax"; break;
				case OP_R8:  string += g_gpr8_names[op.r]; break;
				case OP_R32: string += g_gpr32_names[op.r]; break;
				case OP_R64: string += g_gpr64_names[op.r]; break;
				case OP_XMM: string += "xmm"; string += utility::int_to_string(op.r); break;
				case OP_YMM: string += "ymm"; string += utility::int_to_string(op.r); break;
				case OP_ZMM: string += "zmm"; string += utility::int_to_string(op.r); break;
				case OP_K_K: string += "k"; string += utility::int_to_string(op.mr.index); string += " {k"; string += utility::int_to_string(op.mr.k); string += "}"; break;
				case OP_XMM_KZ: string += "xmm"; string += utility::int_to_string(op.r); string += " {k"; string += utility::int_to_string(op.mr.k); string += "}{z}"; break;
				case OP_B32: {
					const operand_type type = inst->operands[index];
					const u8 broadcast_bits = broadcast_to_bits(type);
					const u16 inst_size = inst_size_to_int(inst->op_size);

					string += "[rax]{1to";
					string += utility::int_to_string(inst_size / broadcast_bits);
					string += '}';

					break;
				} 
				case OP_MEM:
				case OP_M8:  string += "byte " + memory_to_string(op.memory); break;
				case OP_M16: string += "word " + memory_to_string(op.memory); break;
				case OP_M32: string += "dword " + memory_to_string(op.memory); break;
				case OP_M64: string += "qword " + memory_to_string(op.memory); break;
				case OP_I8:
				case OP_I16:
				case OP_I32:
				case OP_I64: string += immediate_to_string(op.immediate); break;
				default: utility::console::print_err("unhandled operand type '{}'\n", operand_type_to_string(op.type));
			}

			return string;
		}

		auto immediate_to_string(imm i) -> utility::dynamic_string {
			utility::dynamic_string string;

			if(i.sign) {
				string += '-';
				string += utility::int_to_string(~i.value + 1); // two's complement 
			}
			else {
				string += utility::int_to_string(i.value); 
			}
	
			return string;
		}

		auto register_to_string(reg r) -> const char* {
			switch(r.type) {
				case REG_R8:  return g_gpr8_names[r.index];
				case REG_R32: return g_gpr32_names[r.index];
				case REG_R64: return g_gpr64_names[r.index];
				default: return "unknown reg class";
			}
		}

		auto memory_to_string(mem m) -> utility::dynamic_string {
			utility::dynamic_string string;
			string += '[';
			
			if(m.has_base) {
				string += register_to_string(m.base);
	
				if(m.has_index || m.s != SCALE_1 || (m.displacement.value != 0 && m.displacement.sign == false)) {
					string += '+';
				}
			}
	
			if(m.has_index) {
				string += register_to_string(m.index);
	
				if(m.s != SCALE_1 || (m.displacement.value != 0 && m.displacement.sign == false)) {
					string += '+';
				}
			}
	
			switch(m.s) {
				case SCALE_1: break;
				case SCALE_2: string += "2"; break;
				case SCALE_4: string += "4"; break;
				case SCALE_8: string += "8"; break;
				default: ASSERT(false, "invalid scale specified\n");
			}
	
			if(m.s != SCALE_1 && m.displacement.value != 0 && m.displacement.sign == false) {
				string += '+';
			}
	
			if(m.displacement.value != 0) {
				string += immediate_to_string(m.displacement);
			}
	
			string += ']';
			return string;
		}

		auto bytes_to_string(const u8* bytes, u8 count) -> utility::dynamic_string {
			utility::dynamic_string string;
			string.reserve(count * 3);

			constexpr char digits[] = "0123456789abcdef";

			for(u64 i = 0; i < count; ++i) {
				const u8 value = bytes[i];
				string += (digits[(value >> 4) & 0x0F]);
				string += (digits[value & 0x0F]);
				string += ' ';
			}

			return string;
		}
	} // namespace detail

	auto emit_control_flow_graph(const module_t& module) -> utility::dynamic_string {
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

		utility::dynamic_array<edge> edges;
		utility::dynamic_string graph;

		bool block_is_new_segment = true;
		u64 current_block_id = 0;

		graph += "digraph cfg {\n";
		graph += "\tgraph [splines=ortho]\n";
		graph += "\tnode [shape=plaintext fontname=\"monospace\"]\n";
		graph += "\tedge [penwidth=2.0]\n\n";

		// generate nodes (control flow blocks)
		for(u64 i = 0; i < module.m_blocks.get_size(); ++i) {
			const instruction_block* block = module.m_blocks[i];

			// new control flow block
			if(block->new_segment || block_is_new_segment) {
				if(i > 0) {
					graph += "<tr PORT=\"bottom\"><td></td></tr></table>>]\n";
				}

				graph += "\t\"";
				graph += utility::int_to_string(i);
				graph += "\"[label=<<table border=\"1\" cellborder=\"0\" cellspacing=\"0\"><tr PORT=\"top\"><td></td></tr>";

				block_is_new_segment = false;
				current_block_id = i;
			}	

			// append the current instruction block to the current control flow block
			switch(block->ty) {
				case instruction_block::LABEL: {
					graph += "<tr><td align=\"left\">";
					graph += utility::int_to_string(block->start_position);
					graph += "</td><td></td><td COLSPAN=\"100%\" align=\"left\"><b><font color=\"blue\">";
					graph += *block->name;
					graph += "</font></b></td></tr>";
					break;
				}
				case instruction_block::INSTRUCTION: {
					graph += detail::instruction_block_to_string(block, module);
					break;
				}
				case instruction_block::BRANCH: {
					graph += detail::instruction_block_to_string(block, module);
					block_is_new_segment = true;
					break;
				}
			}

			// instructions with no instructions cannot produce a control flow edge
			if(block->size == 0) {
				continue;
			}

			// generate edges
			const instruction_t* inst = block->instructions[block->size - 1];
			bool is_branch = false;

			// branch edge
			if(is_jump_or_branch_inst(inst->index)) {
				const auto it = module.m_symbols.find(inst->operands[0].symbol);
				ASSERT(it != module.m_symbols.end(), "branch to an invalid symbol detected ('{}')\n", *inst->operands[0].symbol);

				edges.push_back({ edge::BRANCH_PASS, current_block_id, it->second.block_index });
				is_branch = true;
			}

			// branch to the following control flow block (occurs when the next block has an incoming edge)
			if(i != module.m_blocks.get_size() - 1 && (block_is_new_segment || module.m_blocks[i + 1]->new_segment)) {
				edges.push_back({ is_branch ? edge::BRANCH_FAIL : edge::FALLTHROUGH, current_block_id, i + 1});	
			}
		}

		graph += "</table>>]\n\n";

		// append generated edges
		for(auto edge : edges) {
			graph += "\t\"";
			graph += utility::int_to_string(edge.from);
			graph += "\":bottom:s -> \"";
			graph += utility::int_to_string(edge.to);
			graph += "\":top:n [color=\"";

			switch(edge.type) {
				case edge::BRANCH_PASS: graph += "darkgreen"; break;
				case edge::BRANCH_FAIL: graph += "red"; break;
				case edge::FALLTHROUGH: graph += "black"; break;
			}

			graph += "\"";

			// if an edge creates a loop, we have to swap the direction, this is a workaround around 
			// a bug with ortho edges in graphviz
			if(edge.from == edge.to) {
				graph += "dir=back";
			}

			graph += "]\n";
		}

		graph += "}\n";

		return graph;
	}
} // namespace baremetal::assembler::pass

