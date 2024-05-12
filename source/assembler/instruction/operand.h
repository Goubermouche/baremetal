#pragma once
#include <utility/types.h>

namespace baremetal {
	using namespace utility;

	enum class gpr_reg : u8 {
		RAX = 0,
		RBX,
		RCX,
		RDX,
		RSI,
		RDI,
		RBP,
		RSP,
		R8,
		R9,
		R10,
		R11,
		R12,
		R13,
		R14,
		R15
	};

#pragma pack(push, 1)
	/**
	 * \brief Represents a basic memory operand. 
	 */
	struct mem {
		enum scale : u8 {
			SCALE_1 = 0b00,
			SCALE_2 = 0b01,
			SCALE_4 = 0b10,
			SCALE_8 = 0b11
		};

		//              [000011110011111111111111111111111111111111000000]
		//       offset  0   4   8 10                            42    48
		//         base  |<->|   |  |                             |     |
		//        index      |<->|  |                             |     |
		//        scale          |<>|                             |     |
		// displacement             |<--------------------------->|     |
		//       unused                                           |<--->|
		gpr_reg base  : 4;
		gpr_reg index : 4;
		scale scale   : 2;
		i32 displacement;
		// extra 6 bits for whatever
	};

	struct operand {
		constexpr operand() = default;

		constexpr operand(u64 immediate) : immediate(immediate) {}
		constexpr operand(mem memory)  : memory(memory) {}
		constexpr operand(gpr_reg reg) : reg(reg) {}

		union {
			mem memory;
			gpr_reg reg;
			u64 immediate;
		};
	};
#pragma pack(pop)
} // namespace baremetal
