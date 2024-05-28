#pragma once
#include <utility/types.h>

namespace baremetal {
	using namespace utility::types;

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

	struct operand {
		constexpr operand() : type(OP_NONE), reg(0) {}

		enum type : u8 {
			OP_NONE,
			OP_R8,
			OP_R16,
			OP_R32,
			OP_R64,
			OP_M8,
			OP_M16,
			OP_M32,
			OP_M64,
			OP_I8,
			OP_I16,
			OP_I32,
			OP_I64
		};

		type type;

		union {
			u8 reg;
			u64 imm;
		};
	};

	struct R8  : operand {
		constexpr R8(u8 index) { reg = index; type = OP_R8; }
	};

	struct R16 : operand {
		constexpr R16(u8 index) { reg = index; type = OP_R16; }
	};

	struct R32 : operand {
		constexpr R32(u8 index) { reg = index; type = OP_R32; }
	};

	struct R64 : operand {
		constexpr R64(u8 index) { reg = index; type = OP_R64; }
	};

	static constexpr R64 rax = R64(0);
	static constexpr R64 rcx = R64(1);
	static constexpr R64 rdx = R64(2);
	static constexpr R64 rbx = R64(3);
	static constexpr R64 rsp = R64(4);
	static constexpr R64 rbp = R64(5);
	static constexpr R64 rsi = R64(6);
	static constexpr R64 rdi = R64(7);
	static constexpr R64 r8  = R64(8);
	static constexpr R64 r9  = R64(9);
	static constexpr R64 r10 = R64(10);
	static constexpr R64 r11 = R64(11);
	static constexpr R64 r12 = R64(12);
	static constexpr R64 r13 = R64(13);
	static constexpr R64 r14 = R64(14);
	static constexpr R64 r15 = R64(15);

	static constexpr R32 eax  = R32(0);
	static constexpr R32 ecx  = R32(1);
	static constexpr R32 edx  = R32(2);
	static constexpr R32 ebx  = R32(3);
	static constexpr R32 esp  = R32(4);
	static constexpr R32 ebp  = R32(5);
	static constexpr R32 esi  = R32(6);
	static constexpr R32 edi  = R32(7);
	static constexpr R32 r8d  = R32(8);
	static constexpr R32 r9d  = R32(9);
	static constexpr R32 r10d = R32(10);
	static constexpr R32 r11d = R32(11);
	static constexpr R32 r12d = R32(12);
	static constexpr R32 r13d = R32(13);
	static constexpr R32 r14d = R32(14);
	static constexpr R32 r15d = R32(15);

	static constexpr R16 ax   = R16(0);
	static constexpr R16 cx   = R16(1);
	static constexpr R16 dx   = R16(2);
	static constexpr R16 bx   = R16(3);
	static constexpr R16 sp   = R16(4);
	static constexpr R16 bp   = R16(5);
	static constexpr R16 si   = R16(6);
	static constexpr R16 di   = R16(7);
	static constexpr R16 r8w  = R16(8);
	static constexpr R16 r9w  = R16(9);
	static constexpr R16 r10w = R16(10);
	static constexpr R16 r11w = R16(11);
	static constexpr R16 r12w = R16(12);
	static constexpr R16 r13w = R16(13);
	static constexpr R16 r14w = R16(14);
	static constexpr R16 r15w = R16(15);

	static constexpr R8 al   = R8(0);
	static constexpr R8 cl   = R8(1);
	static constexpr R8 dl   = R8(2);
	static constexpr R8 bl   = R8(3);
	static constexpr R8 ah   = R8(4);
	static constexpr R8 ch   = R8(5);
	static constexpr R8 dh   = R8(6);
	static constexpr R8 bh   = R8(7);
	// static constexpr R8 r8l  = R8(8);
	// static constexpr R8 r9l  = R8(9);
	// static constexpr R8 r10l = R8(10);
	// static constexpr R8 r11l = R8(11);
	// static constexpr R8 r12l = R8(12);
	// static constexpr R8 r13l = R8(13);
	// static constexpr R8 r14l = R8(14);
	// static constexpr R8 r15l = R8(15);

	struct I8  : operand {
		I8(u8 value) { imm = value; type = OP_I8; }
	};

	struct I16 : operand {
		I16(u16 value) { imm = value; type = OP_I16; }
	};

	struct I32 : operand {
		I32(u32 value) { imm = value; type = OP_I32; }
	};

	struct I64 : operand {
		I64(u64 value) { imm = value; type = OP_I64; }
	};

	struct M8 : operand {};
	struct M16 : operand {};
	struct M32 : operand {};
	struct M64 : operand {};

	inline auto is_operand_reg(enum operand::type op) -> bool {
		switch(op) {
			case operand::OP_R8:
			case operand::OP_R16:
			case operand::OP_R32:
			case operand::OP_R64:  return true;
			default: return false;
		}
	}

	inline auto is_operand_imm(enum operand::type op) -> bool {
		switch(op) {
		case operand::OP_I8:
		case operand::OP_I16:
		case operand::OP_I32:
		case operand::OP_I64:  return true;
		default: return false;
		}
	}

	inline auto operand_type_to_string(enum operand::type op) -> std::string_view {
		switch(op) {
			case operand::OP_NONE: return "none";
			case operand::OP_R8:   return "r8";
			case operand::OP_R16:  return "r16";
			case operand::OP_R32:  return "r32";
			case operand::OP_R64:  return "r64";
			case operand::OP_M8:   return "m8";
			case operand::OP_M16:  return "m16";
			case operand::OP_M32:  return "m32";
			case operand::OP_M64:  return "m64";
			case operand::OP_I8:   return "i8";
			case operand::OP_I16:  return "i16";
			case operand::OP_I32:  return "i32";
			case operand::OP_I64:  return "i64";
		}

		return "unknown";
	}

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

	//struct operand {
	//	constexpr operand() = default;

	//	constexpr operand(u64 immediate) : immediate(immediate) {}
	//	constexpr operand(mem memory)  : memory(memory) {}
	//	constexpr operand(gpr_reg reg) : reg(reg) {}

	//	union {
	//		mem memory;
	//		gpr_reg reg;
	//		u64 immediate;
	//	};
	//};
#pragma pack(pop)
} // namespace baremetal
