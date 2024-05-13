#pragma once
#include <utility/types.h>

namespace baremetal {
	using namespace utility;

	enum class gpr_reg : u8 {
		RAX = 0,
		RCX,
		RDX,
		RBX,
		RSP,
		RBP,
		RSI,
		RDI,
		R8,
		R9,
		R10,
		R11,
		R12,
		R13,
		R14,
		R15,
	};

	struct reg_base {};

	struct gp : reg_base {};
	struct gp_64 : reg_base {};
	struct gp_l32 : reg_base {};
	struct gp_l16 : reg_base {};
	struct gp_l8 : reg_base {};
	struct gp_h8 : reg_base {};

	static constexpr gp_64 rax = gp_64();
	static constexpr gp_64 rbx = gp_64();
	static constexpr gp_64 rcx = gp_64();
	static constexpr gp_64 rdx = gp_64();
	static constexpr gp_64 rsi = gp_64();
	static constexpr gp_64 rdi = gp_64();
	static constexpr gp_64 rbp = gp_64();
	static constexpr gp_64 rsp = gp_64();
	static constexpr gp_64 r8  = gp_64();
	static constexpr gp_64 r9  = gp_64();
	static constexpr gp_64 r10 = gp_64();
	static constexpr gp_64 r11 = gp_64();
	static constexpr gp_64 r12 = gp_64();
	static constexpr gp_64 r13 = gp_64();
	static constexpr gp_64 r14 = gp_64();
	static constexpr gp_64 r15 = gp_64();

	static constexpr gp_l32 eax  = gp_l32();
	static constexpr gp_l32 ebx  = gp_l32();
	static constexpr gp_l32 ecx  = gp_l32();
	static constexpr gp_l32 edx  = gp_l32();
	static constexpr gp_l32 esi  = gp_l32();
	static constexpr gp_l32 edi  = gp_l32();
	static constexpr gp_l32 ebp  = gp_l32();
	static constexpr gp_l32 esp  = gp_l32();
	static constexpr gp_l32 r8d  = gp_l32();
	static constexpr gp_l32 r9d  = gp_l32();
	static constexpr gp_l32 r10d = gp_l32();
	static constexpr gp_l32 r11d = gp_l32();
	static constexpr gp_l32 r12d = gp_l32();
	static constexpr gp_l32 r13d = gp_l32();
	static constexpr gp_l32 r14d = gp_l32();
	static constexpr gp_l32 r15d = gp_l32();

	static constexpr gp_l16 ax   = gp_l16();
	static constexpr gp_l16 bx   = gp_l16();
	static constexpr gp_l16 cx   = gp_l16();
	static constexpr gp_l16 dx   = gp_l16();
	static constexpr gp_l16 si   = gp_l16();
	static constexpr gp_l16 di   = gp_l16();
	static constexpr gp_l16 bp   = gp_l16();
	static constexpr gp_l16 sp   = gp_l16();
	static constexpr gp_l16 r8w  = gp_l16();
	static constexpr gp_l16 r9w  = gp_l16();
	static constexpr gp_l16 r10w = gp_l16();
	static constexpr gp_l16 r11w = gp_l16();
	static constexpr gp_l16 r12w = gp_l16();
	static constexpr gp_l16 r13w = gp_l16();
	static constexpr gp_l16 r14w = gp_l16();
	static constexpr gp_l16 r15w = gp_l16();

	static constexpr gp_l8 al   = gp_l8();
	static constexpr gp_l8 bl   = gp_l8();
	static constexpr gp_l8 cl   = gp_l8();
	static constexpr gp_l8 dl   = gp_l8();
	static constexpr gp_l8 sil  = gp_l8();
	static constexpr gp_l8 dil  = gp_l8();
	static constexpr gp_l8 bpl  = gp_l8();
	static constexpr gp_l8 spl  = gp_l8();
	static constexpr gp_l8 r8b  = gp_l8();
	static constexpr gp_l8 r9b  = gp_l8();
	static constexpr gp_l8 r10b = gp_l8();
	static constexpr gp_l8 r11b = gp_l8();
	static constexpr gp_l8 r12b = gp_l8();
	static constexpr gp_l8 r13b = gp_l8();
	static constexpr gp_l8 r14b = gp_l8();
	static constexpr gp_l8 r15b = gp_l8();

	static constexpr gp_h8 ah = gp_h8();
	static constexpr gp_h8 bh = gp_h8();
	static constexpr gp_h8 ch = gp_h8();
	static constexpr gp_h8 dh = gp_h8();

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
