#include "assembler.h"

namespace baremetal {
	void assembler::mov(gpr_reg destination, gpr_reg source) {
		instructions.emplace_back(instruction::MOV, destination, source);
	}

	void assembler::mov(gpr_reg destination, u64 immediate) {
		instructions.emplace_back(instruction::MOV, destination, immediate);
	}
} // namespace baremetal
