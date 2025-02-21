#include "emit_cfg_pass.h"

#include "assembler/backend.h"
#include "assembler/instruction/operands/memory.h"

namespace baremetal::assembler::pass {
	namespace detail {
		auto instruction_block_to_string(const basic_block* block, const section& section, const module& module) -> utility::dynamic_string {
			utility::dynamic_string string;
			u64 position = 0;

			// stringify all isntruction in this block
			for(u64 i = 0; i < block->instructions.size; ++i) {
				const instruction_data* instruction_data = block->instructions.data[i];
				const instruction* inst = &INSTRUCTION_DB[instruction_data->index];

				// assemble the instruction (hex representation)
				auto data = module.resolve_instruction(instruction_data, section, position);
				auto bytes = utility::bytes_to_string(data.data, data.size, ' ');

				string.append(g_instruction_label, section.position + block->start_position + position, bytes, inst->name);

				// stringify instruction operands (assembly representation)
				for(u8 j = 0; j < inst->operand_count; ++j) {
					string += operand_to_string(inst, instruction_data->operands[j], j);
		
					// separate individual operands with commas
					if(j + 1 != inst->operand_count) {
						string += ", ";
					}
				}
				
				string += "</font></td></tr>";
				position += instruction_data->size;
			}

			return string;
		}

		auto label_block_to_string(const basic_block* block, const section& section) -> utility::dynamic_string {
			utility::dynamic_string string;
			string.append(g_label_header, section.position + block->start_position, *block->label.name);

			return string;
		}

		auto data_block_to_string(const basic_block* block, const section& section)  -> utility::dynamic_string {
			constexpr u8 chars_per_line = 30;
			const u64 line_count = ceil(static_cast<f32>(block->size) / static_cast<f32>(chars_per_line));

			utility::dynamic_string string;

			// stringify a block of data
			for(u64 i = 0; i < line_count; ++i) {
				string.append("<tr><td align=\"left\">");
				string.append(section.position + block->start_position + i * chars_per_line);
				string.append("</td><td COLSPAN=\"100%\" align=\"left\">");

				// append a line of chars_per_line bytes
				const u64 start = i * chars_per_line;
				const u64 end = utility::min(block->size, start + chars_per_line);

				string.append("{} </td></tr>", utility::bytes_to_string(block->data.data + start, end - start, ' '));
			}

			return string;
		}

		auto operand_to_string(const instruction* inst, const operand& op, u8 index) -> utility::dynamic_string {
			utility::dynamic_string string;
		
			// HACK: not all operands with a symbol should be resolved as their symbol
			if(op.symbol) {
				string += *op.symbol;
				return string;
			}

			switch(op.type) {
				case OP_RAX:    string += "rax"; break;
				case OP_EAX:    string += "eax"; break;
				case OP_R8:     
				case OP_R16:    
				case OP_R32:    
				case OP_R64:    
				case OP_XMM:    
				case OP_YMM:    
				case OP_ZMM:    
				case OP_TMM:    
				case OP_MMX:    
				case OP_ST:    
				case OP_SREG:    
				case OP_DREG:    
				case OP_CREG:    
				case OP_BND:    string += register_to_string(reg(op.r, static_cast<reg_type>(op.type))); break;
				case OP_K_K:    string.append("k{} {k{}}", op.mr.index, op.mr.k); break;
				case OP_XMM_KZ: string.append("xmm{} {k{}}{z}", op.r, op.mr.k); break;
				case OP_B16: 
				case OP_B32: 
				case OP_B64:    string += broadcast_to_string(inst, index); break;
				case OP_MEM:
				case OP_M8:     string.append("byte {}", memory_to_string(op.memory)); break;
				case OP_M16:    string.append("word {}", memory_to_string(op.memory)); break;
				case OP_M32:    string.append("dword {}", memory_to_string(op.memory)); break;
				case OP_M64:    string.append("qword {}", memory_to_string(op.memory)); break;
				case OP_M128:   string += memory_to_string(op.memory); break;
				case OP_I8:
				case OP_I16:
				case OP_I32:
				case OP_I64:    string += immediate_to_string(op.immediate); break;
				default:        utility::console::print_err("[cfg emit]: unhandled operand type '{}'\n", operand_type_to_string(op.type));
			}

			return string;
		}

		auto broadcast_to_string(const instruction* inst, u8 index) -> utility::dynamic_string {
			const u8 broadcast_bits = broadcast_to_bits(inst->operands[index]);
			const u16 inst_size = inst_size_to_int(inst->op_size);

			utility::dynamic_string string;
			string.append("[rax]{1to{}}", inst_size / broadcast_bits);

			return string;
		}
	} // namespace detail

	auto emit_control_flow_graph(const module& module) -> utility::dynamic_string {
		struct edge {
			enum edge_type {
				BRANCH_PASS,
				BRANCH_FAIL,
				FALLTHROUGH
			};

			edge_type type;
			u64 source;
			u64 destination;
		};

		utility::dynamic_array<edge> edges;
		utility::dynamic_string graph;

		bool block_is_new_segment = true;
		u64 global_block_offset = 0;
		u64 current_block_id = 0;

		// graphviz header
		graph.append("digraph cfg {\n");
		graph.append("\tgraph [splines=ortho]\n");
		graph.append("\tnode [shape=plaintext fontname=\"monospace\"]\n");
		graph.append("\tedge [penwidth=2.0]\n\n");

		// emit individual basic blocks
		for(const section& section : module.sections) {
			for(u64 i = 0; i < section.blocks.get_size(); ++i) {
				const u64 global_block_index = global_block_offset + i;
				const basic_block* block = section.blocks[i];

				// new control flow block
				if(block->incoming_control_edge_count || block_is_new_segment) {
					if(global_block_index > 0) {
						graph.append(detail::g_row_header);
					}

					graph.append(detail::g_block_header, global_block_index);
					current_block_id = global_block_index;
					block_is_new_segment = false;
				}	

				// append the current instruction block to the current control flow block
				switch(block->type) {
					case BB_INSTRUCTION: graph += detail::instruction_block_to_string(block, section, module); break;
					case BB_BRANCH:      graph += detail::instruction_block_to_string(block, section, module); block_is_new_segment = true; break;
					case BB_LABEL:       graph += detail::label_block_to_string(block, section); break;
					case BB_DATA:        graph += detail::data_block_to_string(block, section); break;
					default: ASSERT(false, "unknown basic block type received\n");
				}

				// blocks with no instructions cannot produce a control flow edge
				if(!block->is_instruction_block()) {
					continue;
				}

				// generate control flow edges
				const instruction_data* inst = block->instructions.data[block->instructions.size - 1];
				bool is_branch = false;

				// branch edge
				if(is_jump_or_branch_inst(inst->index)) {
					edges.push_back({ 
						edge::BRANCH_PASS,
						current_block_id,
						module.get_symbol(inst->operands[0].symbol).block_index
					});
					
					is_branch = true;
				}

				// branch to the following control flow block (occurs when the next block has an incoming edge)
				if(global_block_index < module.get_block_count() - 1) {
					if(block_is_new_segment || module.get_block_at_index(global_block_index + 1)->incoming_control_edge_count) {
						edges.push_back({ 
							is_branch ? edge::BRANCH_FAIL : edge::FALLTHROUGH,
							current_block_id, 
							global_block_index + 1
						});
					}
				}
			}

			global_block_offset += section.blocks.get_size();
		}

		graph += "</table>>]\n\n";

		// append generated edges
		for(auto edge : edges) {
			graph.append("\t\"{}\":bottom:s -> \"{}\":top:n [color=\"", edge.source, edge.destination);

			switch(edge.type) {
				case edge::BRANCH_PASS: graph += "darkgreen"; break;
				case edge::BRANCH_FAIL: graph += "red";       break;
				case edge::FALLTHROUGH: graph += "black";     break;
			}

			graph += "\"";

			// if an edge creates a loop, we have to swap the direction, this is a workaround around 
			// a bug with ortho edges in graphviz
			if(edge.source == edge.destination) {
				graph += "dir=back";
			}

			graph += "]\n";
		}

		graph += "}\n";

		return graph;
	}
} // namespace baremetal::assembler::pass

