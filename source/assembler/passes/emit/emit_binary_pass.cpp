#include "emit_binary_pass.h"

#include "assembler/backend.h"
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	auto emit_binary(const module_t& module) -> utility::dynamic_array<u8> {
		utility::dynamic_array<u8> bytes;

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
									utility::console::print("xd {}\n",sym_it->second.position);
									value = sym_it->second.position;
								}
								else {
									if(block->section_index == sym_it->second.section_index) {
										// same sections
										value = sym_it->second.position - (inst_pos + inst->size);
									}
									else {
										// different sections
										ASSERT(false, "todo\n");
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
