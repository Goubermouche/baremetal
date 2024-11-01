#include "module.h"
#include "assembler/backend.h"
#include "assembler/instruction/instruction.h"
#include "assembler/instruction/operands/memory.h"
#include "assembler/instruction/operands/operands.h"
#include "utility/containers/dynamic_string.h"

#include <utility/algorithms/sort.h>

namespace baremetal::assembler {
	auto basic_block::is_instruction_block() const -> bool {
		switch(type) {
			case BB_BRANCH:
			case BB_INSTRUCTION: return true;
			default:             return false;
		}
	}

	auto basic_block::is_data_block() const -> bool {
		switch(type) {
			default:             return false;
		}
	}

  module_t::module_t(context* ctx) : ctx(ctx) {
		set_section(ctx->strings.add(".text"));
	}

  void module_t::add_instruction(const operand* operands, u32 index, u8 size) {
    instruction_t* instruction = ctx->allocator.emplace<instruction_t>();

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
		// utility::console::print("add symbol '{}' ({}, section # {})\n", *name, m_blocks.get_size(), m_current_section);
		symbols[name] = { m_current_segment_length, blocks.get_size(), m_current_section };
	}

	void module_t::set_section(utility::string_view* name) {
		u64 new_index;

		for(u64 i = 0; i < sections.get_size(); ++i) {
			if(name == sections[i]) {
				new_index = i;
				break;
			}
		}

		new_index = sections.get_size();
		sections.push_back(name);

		// force a new block
		if(new_index != m_current_section) {
			if(!m_current_block.is_empty()) {
				auto new_block = allocate_block(BB_INSTRUCTION);

				u64 memory_size = m_current_block.get_size() * sizeof(instruction_t*);
				new_block->instructions.data = static_cast<instruction_t**>(ctx->allocator.allocate(memory_size));
				new_block->instructions.size = m_current_block.get_size();
				utility::memcpy(new_block->instructions.data, m_current_block.get_data(), memory_size);

				new_block->size = m_current_segment_length;
				new_block->start_position = m_current_start_position;
				new_block->section_index = m_current_section;

				blocks.push_back(new_block);

				m_current_start_position += m_current_segment_length;
				m_current_segment_length = 0;

				m_current_block.clear();
			}

			m_current_section = new_index;
		}
	}

	void module_t::begin_block(basic_block_type ty, utility::string_view* name) {
		if(ty == BB_INSTRUCTION) {
			if(m_current_block.is_empty()) {
				return;
			}
		}

		m_current_block_name = name;
		auto new_block = allocate_block(ty);

		if(ty == BB_LABEL) {
			new_block->label.name = m_current_block_name;
		}
		else {
			u64 memory_size = m_current_block.get_size() * sizeof(instruction_t*);
			new_block->instructions.data = static_cast<instruction_t**>(ctx->allocator.allocate(memory_size));
			new_block->instructions.size = m_current_block.get_size();
			utility::memcpy(new_block->instructions.data, m_current_block.get_data(), memory_size);
		}

		new_block->size = m_current_segment_length;
		new_block->start_position = m_current_start_position;
		new_block->section_index = m_current_section;

		blocks.push_back(new_block);

		m_current_start_position += m_current_segment_length;
		m_current_segment_length = 0;

		m_current_block.clear();
	}

	auto module_t::allocate_block(basic_block_type type) -> basic_block* {
		basic_block* block = ctx->allocator.emplace<basic_block>();

		block->incoming_control_edge_count = 0;
		block->type = type;

		return block;
	}

	void module_t::recalculate_block_sizes() {
		u64 position = 0;

		for(basic_block* block : blocks) { 
			u64 size = 0;

			if(block->is_instruction_block()) {
				for(u64 i = 0; i < block->instructions.size; ++i) {
					size += block->instructions.data[i]->size;
				}
			}

			block->start_position = position;
			block->size = size; 

			position += size;
		}

		for(auto& [symbol, location] : symbols) {
			location.position = blocks[location.block_index]->start_position;
		}
	}
} // namespace baremetal::assembler
