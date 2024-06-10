#pragma once
#include "assembler/instruction/operands/immediates.h"
#include "assembler/instruction/operands/registers.h"

namespace baremetal {
	struct mem {
		enum scale : u8 {
			SCALE_1 = 0b00,
			SCALE_2 = 0b01,
			SCALE_4 = 0b10,
			SCALE_8 = 0b11
		};

		reg base;
		reg index;

		bool has_base = false;
		bool has_index = false;

		scale scale = SCALE_1;
		imm displacement;
	};

	struct mem8  : mem {
		// [base]
		static auto absolute(i32 address) -> mem8 {
			mem8 memory = {};

			memory.displacement = address;

			return memory;
		}

		static auto ptr(rip rip, i32 offset) -> mem8 {
			mem8 memory = {};

			memory.base = rip;
			memory.has_base = true;

			memory.displacement = offset;

			return memory;
		}

		// [base_reg + offset]
		static auto ptr(reg base_reg, i32 offset) -> mem8 {
			mem8 memory = {};

			memory.base = base_reg;
			memory.has_base = true;

			memory.displacement = offset;

			return memory;
		}
		// [base_reg + (index * s) + offset]
		static auto ptr(reg base_reg, reg index_reg, enum scale s = SCALE_1, i32 offset = 0) -> mem8 {
			mem8 memory = {};

			memory.base = base_reg;
			memory.has_base = true;

			memory.index = index_reg;
			memory.has_index = true;

			memory.displacement = offset;
			memory.scale = s;

			return memory;
		}
	};

	struct mem16 : mem {};
	struct mem32 : mem {};
	struct mem64 : mem {};
} // namespace baremetal
