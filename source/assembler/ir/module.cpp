#include "module.h"
#include "assembler/backend.h"

namespace baremetal::assembler {
  module_t::module_t(context* ctx) : m_ctx(ctx) {}

  void module_t::add_instruction(const instruction_t::operand* operands, u32 index) {
    instruction_t* instruction = m_ctx->allocator.emplace<instruction_t>();

    instruction->operands[0] = operands[0];
    instruction->operands[1] = operands[1];
    instruction->operands[2] = operands[2];
    instruction->operands[3] = operands[3];

    instruction->index = index;

    m_current_block.push_back(instruction);
  }

	void module_t::begin_block(utility::string_view* name) {
		if(m_current_block_name) {
			instruction_block* block = m_ctx->allocator.emplace<instruction_block>();
			u64 instruction_memory = sizeof(instruction_t*) * m_current_block.get_size();
			instruction_t** instructions = static_cast<instruction_t**>(m_ctx->allocator.allocate(instruction_memory));

			block->name = m_current_block_name;
	    block->instructions = instructions;
	    block->size = m_current_block.get_size();
	
	    m_blocks.push_back(block);
			utility::memcpy(instructions, m_current_block.get_data(), instruction_memory);
		}	

		m_current_block_name = name;
    m_current_block.clear();
	}

	auto module_t::emit_graph() -> utility::dynamic_string {
		utility::dynamic_string result;

		result += "digraph cfg {\n";
		result += "\tnode [shape=plaintext fontname=\"monospace\"]\n";
		result += "\tedge [overlap=false]\n";

		result += "\n";

		// generate nodes
		for(const instruction_block* block : m_blocks) {
			result += "\t\"";
			result += *block->name;
			result += "\"[";
			result += "label=<<table border=\"1\" cellborder=\"0\" cellspacing=\"0\" >";
			result += "<tr><td align=\"left\">";
			result += *block->name;
			result += "</td></tr>";
			result += "<tr><td></td></tr>";

			for(u64 i = 0; i < block->size; ++i) {
				instruction_t* inst = block->instructions[i];
				result += "<tr>";
				result += "<td align=\"left\" ";
				result += " width=\"100px\">";
				result += instruction_db[inst->index].name;
				result += "</td><td PORT=\"p";
				result += utility::int_to_string(i);
				result += "\" align=\"left\">";

				if(inst->operands[0].branch_to) {
					result += *inst->operands[0].branch_to;
				}

				result += "</td></tr>";
			}

			result += "</table>>]\n";
		}

		result += "\n";

		// generate edges
		for(u64 i = 0; i < m_blocks.get_size(); ++i) {
			const instruction_block* block = m_blocks[i];

			for(u64 j = 0; j < block->size; ++j) {
				instruction_t* inst = block->instructions[j];

				if(is_jump_or_branch_inst(inst->index)) {
					result += "\t\"";
					result += *block->name;
					result += "\":p";
					result += utility::int_to_string(j);
					result += ":e -> ";
					result += "\"";
					result += *inst->operands[0].branch_to;
					result += "\":p0:e";
					result += "\n";
				}

				if(j == block->size - 1 && i != m_blocks.get_size() - 1) {
					result += "\t\"";
					result += *block->name;
					result += "\"";
					result += ":s";
					result += " -> ";
					result += "\"";
					result += *m_blocks[i + 1]->name;
					result += "\":n";
					result += "\n";
				}
			}
		}

		result += "}\n";

		return result;
	}
} // namespace baremetal::assembler
