#include "module.h"

#include "assembler/backend.h"
#include "assembler/instruction/instruction.h"

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
			case BB_DATA: return true;
			default:      return false;
		}
	}

  module::module(context* ctx) : ctx(ctx) {
		set_section(ctx->strings.add(".text"));
	}

  void module::add_instruction(const operand* operands, u32 index, u8 size) {
    instruction_data* instruction = ctx->allocator.emplace<instruction_data>();

    instruction->operands[0] = operands[0];
    instruction->operands[1] = operands[1];
    instruction->operands[2] = operands[2];
    instruction->operands[3] = operands[3];

    instruction->index = index;
		instruction->size = size;

		m_current_segment_length += size;
    m_current_block.push_back(instruction);
		sections[m_current_section].offset += instruction->size;
		sections[m_current_section].size += instruction->size;
  }
	
	void module::add_data_block(const utility::dynamic_array<u8>& data) {
		// force a new block
		if(!m_current_block.is_empty()) {
			auto new_block = allocate_block(BB_INSTRUCTION);

			u64 memory_size = m_current_block.get_size() * sizeof(instruction_data*);
			new_block->instructions.data = static_cast<instruction_data**>(ctx->allocator.allocate(memory_size));
			new_block->instructions.size = m_current_block.get_size();
			utility::memcpy(new_block->instructions.data, m_current_block.get_data(), memory_size);

			new_block->size = m_current_segment_length;
			new_block->start_position = m_current_start_position;
			new_block->section_index = m_current_section;

			sections[m_current_section].blocks.push_back(new_block);
			m_block_count++;

			m_current_start_position += m_current_segment_length;
			m_current_segment_length = 0;

			m_current_block.clear();
		}

		auto new_block = allocate_block(BB_DATA);
		
		new_block->data.data = static_cast<u8*>(ctx->allocator.allocate(data.get_size() * sizeof(u8)));
		new_block->data.size = data.get_size();
		utility::memcpy(new_block->data.data, data.get_data(), data.get_size() * sizeof(u8));

		new_block->size = data.get_size();
		new_block->start_position = m_current_start_position;
		new_block->section_index = m_current_section;

		m_current_start_position += data.get_size();
		m_current_segment_length = 0;

		m_block_count++;
		sections[m_current_section].blocks.push_back(new_block);
		sections[m_current_section].offset += data.get_size();
		sections[m_current_section].size += data.get_size();
	}

	void module::add_symbol(utility::string_view* name) {
		sections[m_current_section].symbols[name] = { sections[m_current_section].offset,m_block_count };
	}

	void module::set_section(utility::string_view* name) {
		u64 new_index = sections.get_size();

		for(u64 i = 0; i < sections.get_size(); ++i) {
			if(name == sections[i].name) {
				new_index = i;
				break;
			}
		}

		if(new_index == sections.get_size()) {
			sections.push_back({.name = name});
		}

		// force a new block
		if(new_index != m_current_section) {
			if(!m_current_block.is_empty()) {
				auto new_block = allocate_block(BB_INSTRUCTION);

				u64 memory_size = m_current_block.get_size() * sizeof(instruction_data*);
				new_block->instructions.data = static_cast<instruction_data**>(ctx->allocator.allocate(memory_size));
				new_block->instructions.size = m_current_block.get_size();
				utility::memcpy(new_block->instructions.data, m_current_block.get_data(), memory_size);

				new_block->size = m_current_segment_length;
				new_block->start_position = m_current_start_position;
				new_block->section_index = m_current_section;

				m_block_count++;
				sections[m_current_section].blocks.push_back(new_block);

				m_current_start_position += m_current_segment_length;
				m_current_segment_length = 0;

				m_current_block.clear();
			}

			m_current_section = new_index;
		}
	}

	void module::begin_block(basic_block_type ty, utility::string_view* name) {
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
			u64 memory_size = m_current_block.get_size() * sizeof(instruction_data*);
			new_block->instructions.data = static_cast<instruction_data**>(ctx->allocator.allocate(memory_size));
			new_block->instructions.size = m_current_block.get_size();
			utility::memcpy(new_block->instructions.data, m_current_block.get_data(), memory_size);
		}

		new_block->size = m_current_segment_length;
		new_block->start_position = m_current_start_position;
		new_block->section_index = m_current_section;

		m_block_count++;
		sections[m_current_section].blocks.push_back(new_block);

		m_current_start_position += m_current_segment_length;
		m_current_segment_length = 0;

		m_current_block.clear();
	}

	auto module::allocate_block(basic_block_type type) -> basic_block* {
		basic_block* block = ctx->allocator.emplace<basic_block>();

		block->incoming_control_edge_count = 0;
		block->type = type;

		return block;
	}


	void module::print_section_info() {
		for(const auto& section : sections) {
			utility::console::print("'{}': offset: {}, blocks: {}\n", *section.name, section.offset, section.blocks.get_size());
		}
	}

	auto module::get_block_at_index(u64 i) const -> basic_block* {
		const u64 original_i = i; // debugging

		for(const section& section : sections) {
			if(i < section.blocks.get_size()) {
				return section.blocks[i];
			}

			i -= section.blocks.get_size();
		}

		ASSERT(false, "get_block_at_index: block at index {} is out of bounds\n", original_i);
		SUPPRESS_C4100(original_i);

		return nullptr;
	}

	auto module::get_symbol(utility::string_view* name) const -> section::symbol {
		ASSERT(name != nullptr, "symbol is nullptr\n");

		for(const section& section : sections) {
			const auto it = section.symbols.find(name);

			if(it != section.symbols.end()) {
				return it->second;
			}
		}

		ASSERT(false, "unknown symbol '{}'\n", *name);
		return {};
	}

	auto module::get_block_count() const -> u64 {
		return m_block_count;
	}

	void module::recalculate_block_sizes() {
		for(section& section : sections) {
			section.size = 0;

			for(const basic_block* block : section.blocks) {
				if(block->is_instruction_block()) {
					for(u64 i = 0; i < block->instructions.size; ++i) {
						section.size += block->instructions.data[i]->size;
					}
				}
				else if(block->is_data_block()){
					section.size += block->size;
				}
				else {
					// labels
					section.symbols[block->label.name].position = section.size;
				}
			}
		}
	}
} // namespace baremetal::assembler
