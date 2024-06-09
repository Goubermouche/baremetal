#pragma once
#include "assembler/instruction/operands/registers.h"

namespace baremetal {
	struct mem {
		enum scale : u8 {
			SCALE_1 = 0b00,
			SCALE_2 = 0b01,
			SCALE_4 = 0b10,
			SCALE_8 = 0b11
		};

		u8 base;
		u8 index;

		scale scale;
		i32 displacement;
	};

	struct mem8  : mem {};
	struct mem16 : mem {};
	struct mem32 : mem {};
	struct mem64 : mem {};
} // namespace baremetal
