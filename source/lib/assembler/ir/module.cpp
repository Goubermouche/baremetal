#include "module.h"
#include "assembler/backend.h"

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

	module::module() {}

	module::module(context* ctx) : ctx(ctx) {
		set_section(ctx->strings.add(".text"));
	}

	void module::stage_instruction(const operand* operands, u32 index, u8 size) {
		// allocate the new instruction
		instruction_data* instruction = ctx->allocator.emplace<instruction_data>();
		utility::memcpy(instruction->operands, operands, sizeof(operand) * 4);

		instruction->index = index;
		instruction->size = size;

		// update the parent section
		sections[m_section_index].offset += instruction->size;

		// update the staging block
		m_staged_block.push_back(instruction);
		sections[m_section_index].current_block_size += size;
	}

	void module::commit_instruction_block(basic_block_type ty) {
		// commit all currently staged instructions
		if(m_staged_block.is_empty()) { 
			return; // no staged instructions
		}

		// allocate a new block for our commited instructions
		auto new_block = ctx->allocator.emplace<basic_block>();
		u64 inst_size = m_staged_block.get_size() * sizeof(instruction_data*);

		new_block->type = ty;
		new_block->size = sections[m_section_index].current_block_size;
		
		// copy over the staged instructions
		new_block->instructions.data = static_cast<instruction_data**>(ctx->allocator.allocate(inst_size));
		new_block->instructions.size = m_staged_block.get_size();

		utility::memcpy(new_block->instructions.data, m_staged_block.get_data(), inst_size);

		// update block offsets
		sections[m_section_index].size += sections[m_section_index].current_block_size;

		add_block(new_block);
	}

	void module::commit_label_block(utility::string_view* name) {
		commit_instruction_block(BB_INSTRUCTION); // commit all staged instructions 
		
		// declare the label symbol
		add_symbol(name);

		// allocate a new block for the label
		auto new_block = ctx->allocator.emplace<basic_block>();

		new_block->type = BB_LABEL;
		new_block->size = sections[m_section_index].current_block_size;
		new_block->label.name = name;

		add_block(new_block);
	}

	void module::commit_data_block(const utility::dynamic_array<u8>& data) {
		commit_instruction_block(BB_INSTRUCTION); // commit all staged instructions 

		// allocate a new block for the data segment
		auto new_block = ctx->allocator.emplace<basic_block>();
		const u64 block_size = data.get_size() * sizeof(u8);

		new_block->type = BB_DATA;
		new_block->size = data.get_size();
	
		// copy over the segment data
		new_block->data.data = static_cast<u8*>(ctx->allocator.allocate(block_size));

		utility::memcpy(new_block->data.data, data.get_data(), block_size);

		// update the section offset
		sections[m_section_index].offset += data.get_size();
		sections[m_section_index].size += data.get_size();

		add_block(new_block);
	}
		
	void module::add_block(basic_block* block) {
		block->start_position = sections[m_section_index].current_block_position;
		block->section_index = m_section_index;
		
		// update the block offset
		sections[m_section_index].current_block_position += sections[m_section_index].current_block_size;
		sections[m_section_index].current_block_size = 0;
		
		// add the new block
		sections[m_section_index].blocks.push_back(block);
		m_block_count++;

		// reset the staging zone
		m_staged_block.clear();
	}

	void module::add_symbol(utility::string_view* name, symbol_type type) {
		section& current_section = sections[m_section_index];

		// TODO: hack, we only insert a symbol the first time (temporary workaround for global 
		// symbols needed for ELF object files)
		// TODO: check for multiple definitions here, return an error otherwise
		current_section.symbols.insert({name, { current_section.offset, m_block_count, type }});
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
			sections.push_back({.name = name });
		}

		// force a new block
		if(new_index != m_section_index) {
			commit_instruction_block(BB_INSTRUCTION);
			m_section_index = new_index;
		}
	}

	void module::print_section_info() {
		for(const auto& section : sections) {
			utility::console::print("{}:\n", *section.name);
			utility::console::print("  position: {}\n", section.position);
			utility::console::print("  size: {}\n", section.size);

			if(section.symbols.is_empty() == false) {
				utility::console::print("  symbols ({}):\n", section.symbols.get_size());

				for(const auto& [symbol, location] : section.symbols) {
					utility::console::print("    '{}': pos: {}, block: {}, type: ", *symbol, location.position, location.block_index);

					switch(location.type) {
						case SYM_REGULAR: utility::console::print("R"); break;
						case SYM_GLOBAL:  utility::console::print("G"); break;
						default: ASSERT(false, "unknown symbol type specified\n");
					}

					utility::console::print("\n");
				}
			}

			if(section.blocks.is_empty() == false) {
				utility::console::print("  blocks: {}\n", section.blocks.get_size());

				for(const auto& block : section.blocks) {
					utility::console::print("    pos: {}, size: {}\n", block->start_position, block->size);
				}
			}
		}
	}

	auto module::resolve_instruction(const instruction_data* data, const section& section, u64 position) const  -> backend::code {
		const instruction* inst = &INSTRUCTION_DB[data->index];
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
			else if(is_operand_rip_rel(operands[i].type)) {
				const i64 value = operands[i].immediate.value;
				operands[i].immediate = value - data->size;
			}
			else if(is_operand_rel(operands[i].type)) {
				const i64 value = operands[i].immediate.value;
				operands[i].immediate = value - (position + data->size);
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
