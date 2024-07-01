#pragma once
#include "assembler/instruction/instruction.h"
#include <utility/containers/dynamic_array.h>

namespace baremetal {
	struct block {
		//dynamic_array<instruction> instructions;
	};

	struct relocation {
		// relocates a given value to some other value located at the target
		u64 block_index;
		u64 instruction_index;
		u64 target;
	};
} // namespace baremetal

