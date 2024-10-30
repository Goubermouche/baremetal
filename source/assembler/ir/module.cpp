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
		// utility::console::print("add symbol '{}' ({}, section # {})\n", *name, m_blocks.get_size(), m_current_section);
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
} // namespace baremetal::assembler
