#include "cfg_analyze_pass.h"
#include "assembler/backend.h"

namespace baremetal::assembler::pass {
	void cfg_analyze(module_t& module) {
		utility::console::print("[cfg analyze]: analyzing ({} blocks)\n", module.blocks.get_size());

		// calculate edge connections
		for(u64 i = 0; i < module.blocks.get_size(); ++i) {
			const basic_block* block = module.blocks[i];

			if(!block->is_instruction_block()) {
				continue; 
			}

			const instruction_t* last_inst = block->instructions.data[block->instructions.size - 1];

			if(is_jump_or_branch_inst(last_inst->index)) {
				// TODO: check if its an actual symbol
				// BRANCH_IN always has a priority
				// branch - pass case - incoming edge
				module.blocks[module.symbols.at(last_inst->operands[0].symbol).block_index]->incoming_control_edge_count++; 

				if(i < module.blocks.get_size() - 1) {
					// branch - fail case - incoming edge (next block)
					module.blocks[i + 1]->incoming_control_edge_count++;
				}
			}
		}
	}
} // namespace baremetal::assembler::pass

