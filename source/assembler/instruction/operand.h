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

#define REGISTER_CLASS_64_DECL(name, index) \
  struct name : reg64 {                     \
    constexpr name() : reg64(index) {}      \
  };                                        \
                                            \
  static constexpr name name

#define REGISTER_CLASS_32_DECL(name, index) \
  struct name : reg32 {                     \
    constexpr name() : reg32(index) {}      \
  };                                        \
                                            \
  static constexpr name name

#define REGISTER_CLASS_16_DECL(name, index) \
  struct name : reg16 {                     \
    constexpr name() : reg16(index) {}      \
  };                                        \
                                           \
  static constexpr name name

#define REGISTER_CLASS_8_DECL(name, index) \
  struct name : reg8 {                     \
    constexpr name() : reg8(index) {}      \
  };                                       \
                                           \
  static constexpr name name

	REGISTER_CLASS_64_DECL(rax, 0 );
	REGISTER_CLASS_64_DECL(rcx, 1 );
	REGISTER_CLASS_64_DECL(rdx, 2 );
	REGISTER_CLASS_64_DECL(rbx, 3 );
	REGISTER_CLASS_64_DECL(rsp, 4 );
	REGISTER_CLASS_64_DECL(rbp, 5 );
	REGISTER_CLASS_64_DECL(rsi, 6 );
	REGISTER_CLASS_64_DECL(rdi, 7 );
	REGISTER_CLASS_64_DECL(r8 , 8 );
	REGISTER_CLASS_64_DECL(r9 , 9 );
	REGISTER_CLASS_64_DECL(r10, 10);
	REGISTER_CLASS_64_DECL(r11, 11);
	REGISTER_CLASS_64_DECL(r12, 12);
	REGISTER_CLASS_64_DECL(r13, 13);
	REGISTER_CLASS_64_DECL(r14, 14);
	REGISTER_CLASS_64_DECL(r15, 15);

	REGISTER_CLASS_32_DECL(eax , 0 );
	REGISTER_CLASS_32_DECL(ecx , 1 );
	REGISTER_CLASS_32_DECL(edx , 2 );
	REGISTER_CLASS_32_DECL(ebx , 3 );
	REGISTER_CLASS_32_DECL(esp , 4 );
	REGISTER_CLASS_32_DECL(ebp , 5 );
	REGISTER_CLASS_32_DECL(esi , 6 );
	REGISTER_CLASS_32_DECL(edi , 7 );
	REGISTER_CLASS_32_DECL(r8d , 8 );
	REGISTER_CLASS_32_DECL(r9d , 9 );
	REGISTER_CLASS_32_DECL(r10d, 10);
	REGISTER_CLASS_32_DECL(r11d, 11);
	REGISTER_CLASS_32_DECL(r12d, 12);
	REGISTER_CLASS_32_DECL(r13d, 13);
	REGISTER_CLASS_32_DECL(r14d, 14);
	REGISTER_CLASS_32_DECL(r15d, 15);

	REGISTER_CLASS_16_DECL(ax  , 0 );
	REGISTER_CLASS_16_DECL(cx  , 1 );
	REGISTER_CLASS_16_DECL(dx  , 2 );
	REGISTER_CLASS_16_DECL(bx  , 3 );
	REGISTER_CLASS_16_DECL(sp  , 4 );
	REGISTER_CLASS_16_DECL(bp  , 5 );
	REGISTER_CLASS_16_DECL(si  , 6 );
	REGISTER_CLASS_16_DECL(di  , 7 );
	REGISTER_CLASS_16_DECL(r8w , 8 );
	REGISTER_CLASS_16_DECL(r9w , 9 );
	REGISTER_CLASS_16_DECL(r10w, 10);
	REGISTER_CLASS_16_DECL(r11w, 11);
	REGISTER_CLASS_16_DECL(r12w, 12);
	REGISTER_CLASS_16_DECL(r13w, 13);
	REGISTER_CLASS_16_DECL(r14w, 14);
	REGISTER_CLASS_16_DECL(r15w, 15);

	REGISTER_CLASS_8_DECL(al, 0);
	REGISTER_CLASS_8_DECL(cl, 1);
	REGISTER_CLASS_8_DECL(dl, 2);
	REGISTER_CLASS_8_DECL(bl, 3);
	REGISTER_CLASS_8_DECL(ah, 4);
	REGISTER_CLASS_8_DECL(ch, 5);
	REGISTER_CLASS_8_DECL(dh, 6);
	REGISTER_CLASS_8_DECL(bh, 7);

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
