#include "cfg_analyze_pass.h"
#include "assembler/backend.h"

namespace baremetal::assembler::pass {
	void cfg_analyze(module& module) {
		u64 global_block_offset = 0;

		// calculate edge connections
		for(const section& section : module.sections) {
			for(u64 i = 0; i < section.blocks.get_size(); ++i) {
				const basic_block* block = section.blocks[i];

				if(!block->is_instruction_block()) {
					continue; 
				}

				const instruction_data* last_inst = block->instructions.data[block->instructions.size - 1];

				if(is_jump_or_branch_inst(last_inst->index)) {
					// HACK: TODO: some jump instructions are used without a symbol, handle this case
					if(last_inst->operands[0].symbol == nullptr) {
						continue;
					}

					const u64 block_index = module.get_symbol(last_inst->operands[0].symbol).block_index;
					const u64 global_block_index = global_block_offset + i;

					basic_block* target = module.get_block_at_index(block_index);
					target->incoming_control_edge_count++;

					if(global_block_index < module.get_block_count() - 1) {
						// branch - fail case - incoming edge next block)
						module.get_block_at_index(global_block_index + 1)->incoming_control_edge_count++;
					}
				}
			}

			global_block_offset += section.blocks.get_size();
		}
	}
} // namespace baremetal::assembler::pass

