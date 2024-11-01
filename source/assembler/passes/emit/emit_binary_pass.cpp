#include "emit_binary_pass.h"

#include "assembler/backend.h"

namespace baremetal::assembler::pass {
	auto emit_binary(const module_t& module) -> utility::dynamic_array<u8> {
		utility::dynamic_array<u8> bytes;

		utility::console::print("[binary emit]: emitting binary\n");

		// TODO: dumb
		for(u64 i = 0; i < module.sections.get_size(); ++i) {
			// append alignment bytes for the previous section
			const u64 alignment_offset = utility::align(bytes.get_size(), 4) - bytes.get_size();
			u64 inst_pos = 0;

			for(u64 i = 0; i < alignment_offset; ++i) {
				bytes.push_back(0);
			}

			for(basic_block* block : module.blocks) {
				if(block->section_index != i) {
					continue;
				}

				if(!block->is_instruction_block()) {
					continue;
				}

				for(u64 j = 0; j < block->instructions.size; ++j) {
					instruction_t* inst = block->instructions.data[j];
					const instruction* inst_actual = &instruction_db[inst->index];

					operand temp_operands[4];
					utility::memcpy(temp_operands, inst->operands, sizeof(operand) * 4);

					// resolve symbols
					for(u8 i = 0; i < inst_actual->operand_count; ++i) {
						if(temp_operands[i].symbol) { // TODO: get rid of the HIDDEN type
							// resolve
							auto sym_it = module.symbols.find(temp_operands[i].symbol);
							ASSERT(sym_it != module.symbols.end(), "[binary emit]: invalid symbol specified ('{}')\n", *temp_operands[i].symbol);
							i64 value;


							if(!is_operand_rel(temp_operands[i].type)) {
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
						
							temp_operands[i].immediate = imm(value);
						}
						
					}

					inst_pos += inst->size;

					auto data = backend::emit_instruction(inst_actual, temp_operands);
					bytes.insert(bytes.end(), data.data, data.data + data.size);
				}
			}
		}

		return bytes;
	}
} // namespace baremetal::assembler::pass
