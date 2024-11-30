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

		utility::memcpy(instruction->operands, operands, sizeof(operand) * 4);

    instruction->index = index;
		instruction->size = size;

		// update the parent section
		sections[m_section_index].offset += instruction->size;
    
		// update the current block
		m_current_block.push_back(instruction);
		m_current_block_size += size;
  }

	void module::add_symbol(utility::string_view* name) {
		section& current_section = sections[m_section_index];

		current_section.symbols[name] = { current_section.offset, m_block_count };
	}

	void module::add_instruction_block(basic_block_type ty) {
		if(m_current_block.is_empty()) { 
			return; 
		}

		auto new_block = ctx->allocator.emplace<basic_block>();
		new_block->type = ty;

		u64 memory_size = m_current_block.get_size() * sizeof(instruction_data*);
		new_block->instructions.data = static_cast<instruction_data**>(ctx->allocator.allocate(memory_size));
		new_block->instructions.size = m_current_block.get_size();
		utility::memcpy(new_block->instructions.data, m_current_block.get_data(), memory_size);

		new_block->size = m_current_block_size;
		new_block->start_position = m_current_block_position;
		new_block->section_index = m_section_index;
			
		sections[m_section_index].blocks.push_back(new_block);
		sections[m_section_index].size += m_current_block_size;
		m_block_count++;

		m_current_block_position += m_current_block_size;
		m_current_block_size = 0;
		m_current_block.clear();
	}

	void module::add_label_block(utility::string_view* name) {
		add_symbol(name);

		auto new_block = ctx->allocator.emplace<basic_block>();
		new_block->label.name = name;
		new_block->type = BB_LABEL;

		new_block->size = m_current_block_size;
		new_block->start_position = m_current_block_position;
		new_block->section_index = m_section_index;
		sections[m_section_index].blocks.push_back(new_block);
		m_block_count++;

		m_current_block_position += m_current_block_size;
		m_current_block_size = 0;
		m_current_block.clear();
	}

	void module::add_data_block(const utility::dynamic_array<u8>& data) {
		// force a new block
		add_instruction_block(BB_INSTRUCTION);

		auto new_block = ctx->allocator.emplace<basic_block>();
		new_block->type = BB_DATA;

		new_block->data.data = static_cast<u8*>(ctx->allocator.allocate(data.get_size() * sizeof(u8)));
		new_block->data.size = data.get_size();
		utility::memcpy(new_block->data.data, data.get_data(), data.get_size() * sizeof(u8));

		new_block->size = data.get_size();
		new_block->start_position = m_current_block_position;
		new_block->section_index = m_section_index;
		
		sections[m_section_index].blocks.push_back(new_block);
		sections[m_section_index].offset += data.get_size();
		sections[m_section_index].size += data.get_size();

		m_block_count++;

		m_current_block_position += m_current_block_size;
		m_current_block_size = 0;
		m_current_block.clear();
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
		if(new_index != m_section_index) {
			if(!m_current_block.is_empty()) {
				add_instruction_block(BB_INSTRUCTION);
			}

			m_section_index = new_index;
		}
	}

	void module::print_section_info() {
		for(const auto& section : sections) {
			utility::console::print("{}:\n", *section.name);
			utility::console::print("  position: {}\n", section.position);
			utility::console::print("  blocks: {}\n", section.blocks.get_size());
			utility::console::print("  size: {}\n", section.size);

			if(section.symbols.is_empty()) {
				continue;
			}

			utility::console::print("  symbols ({}):\n", section.symbols.get_size());

			for(const auto& [symbol, location] : section.symbols) {
				utility::console::print("    '{}': pos: {}, block: {}\n", *symbol, location.position, location.block_index);
			}
		}
	}

	auto module::resolve_instruction(const instruction_data* data, const section& section, u64 position) const  -> backend::code {
		const instruction* inst = &instruction_db[data->index];
		static operand operands[4];

		utility::memcpy(operands, data->operands, sizeof(operand) * 4);

		// resolve symbols
		for(u8 i = 0; i < inst->operand_count; ++i) {
			if(operands[i].symbol) {
				auto symbol_it = section.symbols.find(operands[i].symbol);
				i64 value = 0;

				switch(operands[i].type) {
					// immediates are absolute
					case OP_I8:
					case OP_I16:
					case OP_I32:
					case OP_I64: value = get_global_symbol_position(operands[i].symbol); break;
					// relocations are relative
					case OP_REL32:
					case OP_REL8:
					case OP_REL16_RIP:
					case OP_REL8_RIP: {
						if(symbol_it == section.symbols.end()) {
							// global symbol position - (section position + instruction position + instruction size)
							value = get_global_symbol_position(operands[i].symbol) - (section.position + position + data->size);
						}
						else {
							// symbol position - (instruction position + instruction size)
							value = symbol_it->second.position - (position + data->size);
						}

						break;
					} 
					default: ASSERT(false, "unhandled unresolved operand type '{}' (index = {})\n", operand_type_to_string(operands[i].type), i);
				}

				operands[i].immediate = imm(value);
			}
		}

		return backend::emit_instruction(inst, operands);
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

	auto module::get_global_symbol_position(utility::string_view* name) const -> u64 {
		for(u64 i = 0; i < sections.get_size(); ++i) {
			const auto& section = sections[i];
			const auto it = section.symbols.find(name);
	
			if(it != section.symbols.end()) {
				// section position + symbol position (relative to the parent section)
				return section.position + it->second.position;
			}
		}
	
		ASSERT(false, "unknown symbol '{}' specified\n", *name);
		return 0;
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
		u64 position = 0;

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

			position += utility::align(position, 4) - position;
			section.position = position;
			position += section.size;
		}
	}
} // namespace baremetal::assembler
