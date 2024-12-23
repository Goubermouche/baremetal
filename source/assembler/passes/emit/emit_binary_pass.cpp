#include "emit_binary_pass.h"

#include "assembler/backend.h"
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	auto emit_binary(const module& module) -> utility::dynamic_array<u8> {
		utility::dynamic_array<u8> bytes;

		// reserve enough space for the entire binary dump
		const section& last_section = module.sections[module.sections.get_size() - 1];
		bytes.reserve(last_section.position + last_section.size);

		// generate the final binary
		for(const section& section : module.sections) {
			// append alignment bytes for the previous section
			const u64 alignment_offset = utility::align(bytes.get_size(), 4) - bytes.get_size();
			u64 local_offset = 0;

			for(u64 i = 0; i < alignment_offset; ++i) {
				bytes.push_back(0);
			}

			// append individual blocks
			for(const basic_block* block : section.blocks) {
				if(block->is_instruction_block()) {
					// instruction block
					for(u64 i = 0; i < block->instructions.size; ++i) {
						// assemble every instruction and append it
						instruction_data* instruction = block->instructions.data[i];
						auto data = module.resolve_instruction(instruction, section, local_offset);

						bytes.insert(bytes.end(), data.data, data.data + data.size);
						local_offset += instruction->size;
					}
				}
				else if(block->is_data_block()) {
					// raw data block
					bytes.insert(bytes.end(), block->data.data, block->data.data + block->data.size);
					local_offset += block->data.size;
				}
			}
		}

		return bytes;
	}
} // namespace baremetal::assembler::pass
