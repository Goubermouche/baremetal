#include "inst_size_minimize_pass.h"
#include "assembler/backend.h"

namespace baremetal::assembler::pass {
	void inst_size_minimize(module_t& module) {
		for(const instruction_block* block : module.m_blocks) {
			for(u64 i = 0; i < block->size; ++i) {
				instruction_t* inst = block->instructions[i];
				u32 old_index = inst->index;
				module.optimize_instruction_size(inst);

				if(inst->index != old_index) {
					// HACK: recalculate the size, this needs to be done in a different way
					// u8 old_size = inst->size;
					inst->size = backend::emit_instruction(&instruction_db[inst->index], inst->operands).size;
					// utility::console::print("inst optimized {}B -> {}B\n", old_size, inst->size);
				}
			}
		}

		module.recalculate_block_sizes();
	}
} // namespace baremetal::assembler::pass
