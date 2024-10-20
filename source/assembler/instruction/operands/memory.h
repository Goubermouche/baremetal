#pragma once
#include "assembler/instruction/operands/immediates.h"
#include "assembler/instruction/operands/registers.h"

namespace baremetal::assembler {
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

		constexpr auto has_sse_operands() const -> bool {
			if(has_base && is_sse_reg(base)) {
				return true;
			}

			if(has_index && is_sse_reg(index)) {
				return true;
			}

			return false;
		}
	};

	struct masked_mem {
		mem memory;
		u8 k;
	};
} // namespace baremetal::assembler

