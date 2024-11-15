#include "emit_binary_pass.h"

#include "assembler/backend.h"
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	auto emit_binary(const module_t& module) -> utility::dynamic_array<u8> {
		utility::dynamic_array<u8> bytes;
		utility::dynamic_array<u64> section_sizes;
		utility::dynamic_array<u64> section_positions;

		section_sizes.reserve(module.sections.get_size());
		section_positions.reserve(module.sections.get_size());

		u64 total_size = 0;

		for(u64 i = 0; i < module.sections.get_size(); ++i) {
			section_sizes.push_back(0);
			section_positions.push_back(0);
		}

		for(const auto& block : module.blocks) {
			section_sizes[block->section_index] += block->size;
		}
		
		for(u64 i = 0; i < module.sections.get_size(); ++i) {
			total_size += utility::align(total_size, 4) - total_size;
			section_positions[i] = total_size;
			total_size += section_sizes[i];

			utility::console::print("section: {} at: {}\n", *module.sections[i], section_positions[i]);
		}

		utility::console::print("[binary emit]: emitting binary ({} sections)\n", module.sections.get_size());

		// TODO: dumb
		for(u64 i = 0; i < module.sections.get_size(); ++i) {
			// append alignment bytes for the previous section
			const u64 alignment_offset = utility::align(bytes.get_size(), 4) - bytes.get_size();
			u64 inst_pos = 0;

			utility::console::print("[binary emit]: emitting section '{}' {}\n", *module.sections[i], i);

			for(u64 j = 0; j < alignment_offset; ++j) {
				bytes.push_back(0);
			}

			for(basic_block* block : module.blocks) {
				if(block->section_index != i) {
					continue;
				}

				if(block->type == BB_LABEL) {
					continue;
				}

				if(block->is_instruction_block()) {
					for(u64 j = 0; j < block->instructions.size; ++j) {
						instruction_t* inst = block->instructions.data[j];
						const instruction* inst_actual = &instruction_db[inst->index];
	
						operand temp_operands[4];
						utility::memcpy(temp_operands, inst->operands, sizeof(operand) * 4);
	
						// resolve symbols
						for(u8 k = 0; k < inst_actual->operand_count; ++k) {
							if(temp_operands[k].symbol) { // TODO: get rid of the HIDDEN type
								// resolve
								auto sym_it = module.symbols.find(temp_operands[k].symbol);
								ASSERT(sym_it != module.symbols.end(), "[binary emit]: invalid symbol specified ('{}')\n", *temp_operands[k].symbol);
								i64 value;
	
								if(!is_operand_rel(temp_operands[k].type)) {
									value = sym_it->second.position + section_positions[sym_it->second.section_index];
								}
								else {
									if(block->section_index == sym_it->second.section_index) {
										// same sections
										value = sym_it->second.position - (inst_pos + inst->size);
									}
									else {
										// different sections
										value = sym_it->second.position + section_positions[sym_it->second.section_index];
									}
								}
							
								temp_operands[k].immediate = imm(value);
							}
						}
	
						inst_pos += inst->size;
	
						auto data = backend::emit_instruction(inst_actual, temp_operands);
						bytes.insert(bytes.end(), data.data, data.data + data.size);
					}
				}
				else if(block->is_data_block()) {
					bytes.insert(bytes.end(), block->data.data, block->data.data + block->data.size);
					inst_pos += block->data.size;
				}
			}
		}

		return bytes;
	}
} // namespace baremetal::assembler::pass
