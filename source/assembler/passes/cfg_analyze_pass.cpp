#include "cfg_analyze_pass.h"
#include "assembler/backend.h"

namespace baremetal::assembler::pass {
	void cfg_analyze(module_t& module) {
		// utility::console::print("[cfg analyze]: analyzing ({} blocks)\n", module.blocks.get_size());

		u64 global_block_offset = 0;

		// calculate edge connections
		for(u64 i = 0; i < module.sections_n.get_size(); ++i) {
			const section_t& section = module.sections_n[i];

			for(u64 j = 0; j < section.blocks.get_size(); ++j) {
				const basic_block* block = section.blocks[j];

				if(!block->is_instruction_block()) {
					continue; 
				}

				const instruction_t* last_inst = block->instructions.data[block->instructions.size - 1];

				if(is_jump_or_branch_inst(last_inst->index)) {
					// HACK: TODO: some jump instructions are used without a symbol, handle this case
					if(last_inst->operands[0].symbol == nullptr) {
						continue;
					}

					u64 block_index = module.get_symbol(last_inst->operands[0].symbol).block_index;
					basic_block* target = module.get_block_at_index(block_index);

					target->incoming_control_edge_count++;

					const u64 global_block_index = global_block_offset + j;

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

