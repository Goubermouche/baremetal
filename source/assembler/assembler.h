#pragma once
#include "assembler/instruction/instruction.h"
#include <utility/dynamic_array.h>

namespace baremetal {
	struct assembler {
		void mov(gpr_reg destination, gpr_reg source);
		void mov(gpr_reg destination, u64 immediate);

		dynamic_array<instruction> instructions;
	};
} // namespace baremetal
