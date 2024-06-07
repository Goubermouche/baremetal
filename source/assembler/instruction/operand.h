#pragma once
#include <utility/types.h>

#include "utility/streams/console.h"

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

	struct imm {
		imm(u64 i) {
			if(i >= std::numeric_limits<u8>::min() && i <= std::numeric_limits<u8>::max()) {
				min_bits = 8;
			}
			else if(i >= std::numeric_limits<u16>::min() && i <= std::numeric_limits<u16>::max()) {
				min_bits = 16;
			}
			else if(i >= std::numeric_limits<u32>::min() && i <= std::numeric_limits<u32>::max()) {
				min_bits = 32;
			}
			else {
				min_bits = 64;
			}

			value = i;
			sign = false;
		}

		imm(i64 i) {
			if(i >= 0) {
				*this = imm(static_cast<u64>(i));
				return;
			}

			if(i >= std::numeric_limits<i8>::min() && i <= std::numeric_limits<i8>::max()) {
				min_bits = 8;
			}
			else if(i >= std::numeric_limits<i16>::min() && i <= std::numeric_limits<i16>::max()) {
				min_bits = 16;
			}
			else if(i >= std::numeric_limits<i32>::min() && i <= std::numeric_limits<i32>::max()) {
				min_bits = 32;
			}
			else {
				min_bits = 64;
			}

			value = i;
			sign = true;
		}

		template<typename type, typename std::enable_if<std::is_integral<type>::value, int>::type = 0>
		imm(type i) {
			if(std::is_signed<type>::value) {
				*this = imm(static_cast<i64>(i));
			}
			else {
				*this = imm(static_cast<u64>(i));
			}
		}

		u64 value;
		u8 min_bits;
		bool sign;
	};

	struct operand {
		constexpr operand() : type(OP_NONE), reg(0) {}
		 operand(imm i) : type(OP_I64), imm(i) {}

		enum type : u8 {
			OP_NONE,
			OP_REG8,
			OP_REG16,
			OP_REG32,
			OP_REG64,
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
			imm imm;
		};
	};


	struct reg8  : operand {
		constexpr explicit reg8(u8 index) { reg = index; type = OP_REG8; }
	};

	struct reg16 : operand {
		constexpr explicit reg16(u8 index) { reg = index; type = OP_REG16; }
	};

	struct reg32 : operand {
		constexpr explicit reg32(u8 index) { reg = index; type = OP_REG32; }
	};

	struct reg64 : operand {
		constexpr explicit reg64(u8 index) { reg = index; type = OP_REG64; }
	};

	static constexpr reg64 rax = reg64(0);
	static constexpr reg64 rcx = reg64(1);
	static constexpr reg64 rdx = reg64(2);
	static constexpr reg64 rbx = reg64(3);
	static constexpr reg64 rsp = reg64(4);
	static constexpr reg64 rbp = reg64(5);
	static constexpr reg64 rsi = reg64(6);
	static constexpr reg64 rdi = reg64(7);
	static constexpr reg64 r8  = reg64(8);
	static constexpr reg64 r9  = reg64(9);
	static constexpr reg64 r10 = reg64(10);
	static constexpr reg64 r11 = reg64(11);
	static constexpr reg64 r12 = reg64(12);
	static constexpr reg64 r13 = reg64(13);
	static constexpr reg64 r14 = reg64(14);
	static constexpr reg64 r15 = reg64(15);

	static constexpr reg32 eax  = reg32(0);
	static constexpr reg32 ecx  = reg32(1);
	static constexpr reg32 edx  = reg32(2);
	static constexpr reg32 ebx  = reg32(3);
	static constexpr reg32 esp  = reg32(4);
	static constexpr reg32 ebp  = reg32(5);
	static constexpr reg32 esi  = reg32(6);
	static constexpr reg32 edi  = reg32(7);
	static constexpr reg32 r8d  = reg32(8);
	static constexpr reg32 r9d  = reg32(9);
	static constexpr reg32 r10d = reg32(10);
	static constexpr reg32 r11d = reg32(11);
	static constexpr reg32 r12d = reg32(12);
	static constexpr reg32 r13d = reg32(13);
	static constexpr reg32 r14d = reg32(14);
	static constexpr reg32 r15d = reg32(15);

	static constexpr reg16 ax   = reg16(0);
	static constexpr reg16 cx   = reg16(1);
	static constexpr reg16 dx   = reg16(2);
	static constexpr reg16 bx   = reg16(3);
	static constexpr reg16 sp   = reg16(4);
	static constexpr reg16 bp   = reg16(5);
	static constexpr reg16 si   = reg16(6);
	static constexpr reg16 di   = reg16(7);
	static constexpr reg16 r8w  = reg16(8);
	static constexpr reg16 r9w  = reg16(9);
	static constexpr reg16 r10w = reg16(10);
	static constexpr reg16 r11w = reg16(11);
	static constexpr reg16 r12w = reg16(12);
	static constexpr reg16 r13w = reg16(13);
	static constexpr reg16 r14w = reg16(14);
	static constexpr reg16 r15w = reg16(15);

	static constexpr reg8 al   = reg8(0);
	static constexpr reg8 cl   = reg8(1);
	static constexpr reg8 dl   = reg8(2);
	static constexpr reg8 bl   = reg8(3);
	static constexpr reg8 ah   = reg8(4);
	static constexpr reg8 ch   = reg8(5);
	static constexpr reg8 dh   = reg8(6);
	static constexpr reg8 bh   = reg8(7);
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
			case operand::OP_REG8:
			case operand::OP_REG16:
			case operand::OP_REG32:
			case operand::OP_REG64:  return true;
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

	inline auto get_operand_bit_width(enum operand::type op) -> u8 {
		switch(op) {
			case operand::OP_I8:  return 8;
			case operand::OP_I16: return 16;
			case operand::OP_I32: return 32;
			case operand::OP_I64: return 64;
			case operand::OP_REG8:  return 8;
			case operand::OP_REG16: return 16;
			case operand::OP_REG32: return 32;
			case operand::OP_REG64: return 64;
			default:              return 0;
		}
	}

	inline auto operand_type_to_string(enum operand::type op) -> const char* {
		switch(op) {
			case operand::OP_NONE: return "none";
			case operand::OP_REG8:   return "r8";
			case operand::OP_REG16:  return "r16";
			case operand::OP_REG32:  return "r32";
			case operand::OP_REG64:  return "r64";
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

	//	constexpr operand(u64 imm) : imm(imm) {}
	//	constexpr operand(mem memory)  : memory(memory) {}
	//	constexpr operand(gpr_reg reg) : reg(reg) {}

	//	union {
	//		mem memory;
	//		gpr_reg reg;
	//		u64 imm;
	//	};
	//};
#pragma pack(pop)
} // namespace baremetal
