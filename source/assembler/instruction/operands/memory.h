#pragma once
#include "assembler/instruction/operands/immediates.h"
#include "assembler/instruction/operands/registers.h"

namespace baremetal {
	enum scale : u8 {
		SCALE_1 = 0b00,
		SCALE_2 = 0b01,
		SCALE_4 = 0b10,
		SCALE_8 = 0b11,
		SCALE_NONE
	};

	struct mem {
		// this can't be a reg64 since it can contain special registers (ie. rip)
		reg base;
		reg index;

		bool has_base = false;
		bool has_index = false;

		scale s = SCALE_1;
		imm displacement;
	};

	struct broadcast {
		mem m; // referenced memory
		u8 n; 
	};
} // namespace baremetal

