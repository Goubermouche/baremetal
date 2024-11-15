#include "emit_binary_pass.h"

#include "assembler/backend.h"
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	auto emit_binary(const module_t& module) -> utility::dynamic_array<u8> {
		utility::dynamic_array<u8> bytes;
		utility::dynamic_array<u64> section_positions;
		
		u64 total_size = 0;

		section_positions.reserve(module.sections_n.get_size());

		for(u64 i = 0; i < module.sections_n.get_size(); ++i) {
			total_size += utility::align(total_size, 4) - total_size;
			section_positions.push_back(total_size);
			total_size += module.sections_n[i].size;
		}

		auto get_symbol_global = [&](utility::string_view* name) -> u64 {
			for(u64 i = 0; i < module.sections_n.get_size(); ++i) {
				auto section = module.sections_n[i];
				const auto it = section.symbols.find(name);
	
				if(it != section.symbols.end()) {
					// section position + symbol position (relative to the parent section)
					utility::console::print("'{}' at {}\n", *name, it->second.position);
					return section_positions[i] + it->second.position;
				}
			}
	
			ASSERT(false, "unknown symbol '{}' specified\n", *name);
			return {};
    };

		bytes.reserve(total_size);

		u64 section_index = 0;
		// generate the final binary
		for(const section_t& section : module.sections_n) {
			// append alignment bytes for the previous section
			const u64 alignment_offset = utility::align(bytes.get_size(), 4) - bytes.get_size();
			u64 local_offset = 0;

			for(u64 i = 0; i < alignment_offset; ++i) {
				bytes.push_back(0);
			}	

			for(const basic_block* block : section.blocks) {
				if(block->is_instruction_block()) {
					for(u64 i = 0; i < block->instructions.size; ++i) {
						instruction_t* inst = block->instructions.data[i];
						const instruction* inst_actual = &instruction_db[inst->index];
	
						operand temp_operands[4];
						utility::memcpy(temp_operands, inst->operands, sizeof(operand) * 4);

						for(u8 j = 0; j < inst_actual->operand_count; ++j) {
							if(temp_operands[j].symbol) { // TODO: get rid of the HIDDEN type
								// resolve
								auto sym_it = section.symbols.find(temp_operands[j].symbol);
								// ASSERT(sym_it != section.symbols.end(), "[binary emit]: invalid symbol specified ('{}')\n", *temp_operands[j].symbol);
								i64 value = 0;
					
								switch(temp_operands[j].type) {
									// immediates are absolute
									case OP_I8:
									case OP_I16:
									case OP_I32:
									case OP_I64: value = get_symbol_global(temp_operands[j].symbol); break;
									// relocations are relative
									case OP_REL32:
									case OP_REL8:
									case OP_REL16_RIP:
									case OP_REL8_RIP: {
										if(sym_it == section.symbols.end()) {
											// global symbol position - (section position + instruction position + instruction size)
											value = get_symbol_global(temp_operands[j].symbol) - (section_positions[section_index] + local_offset + inst->size);
											utility::console::print("{} : {} {} {} {}\n", *temp_operands[j].symbol, value, section_positions[section_index], local_offset, inst->size);
										}
										else {
											// symbol position - (instruction position + instruction size)
											value = sym_it->second.position - (local_offset + inst->size);
										}

										break;
									} 
									default: ASSERT(false, "unhandled unresolved operand type '{}' (index = {})\n", operand_type_to_string(temp_operands[j].type), j);
								}
	
								temp_operands[j].immediate = imm(value);
							}
						}

						local_offset += inst->size;

						auto data = backend::emit_instruction(inst_actual, temp_operands);
						bytes.insert(bytes.end(), data.data, data.data + data.size);
					}
				}
				else if(block->is_data_block()) {
					bytes.insert(bytes.end(), block->data.data, block->data.data + block->data.size);
					local_offset += block->data.size;
				}
			}
			
			section_index++; // TODO: temp
		}

		return bytes;
	}
} // namespace baremetal::assembler::pass
