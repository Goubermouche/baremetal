#pragma once
#include "assembler/instruction/operands/memory.h"

namespace baremetal {
	struct operand {
		constexpr operand() : type(OP_NONE), reg(0) {}
		operand(imm i) : type(OP_I64), immediate(i) {}
		operand(moff m) : type(OP_MOFF64), memory_offset(m) {}

		operand(reg8  r) : type(OP_REG8),  reg(r.index) {}
		operand(reg16 r) : type(OP_REG16), reg(r.index) {}
		operand(reg32 r) : type(OP_REG32), reg(r.index) {}
		operand(reg64 r) : type(OP_REG64), reg(r.index) {}
		operand(xmm r) : type(OP_XMM), reg(r.index) {}
		operand(mmx r) : type(OP_MMX), reg(r.index) {}
		operand(bnd r) : type(OP_BND), reg(r.index) {}
		operand(sreg r) : type(OP_SREG), reg(r.index) {}

		operand(mem_address m) : type(OP_MEM_ADDRESS), memory(m) {}
		operand(mem8  m) : type(OP_MEM8),  memory(m) {}
		operand(mem16 m) : type(OP_MEM16), memory(m) {}
		operand(mem32 m) : type(OP_MEM32), memory(m) {}
		operand(mem64 m) : type(OP_MEM64), memory(m) {}
		operand(mem128 m) : type(OP_MEM128), memory(m) {}

		enum type : u8 {
			OP_NONE,

			// registers
			OP_REG8,
			OP_REG16,
			OP_REG32,
			OP_REG64,
			OP_XMM, // xmm
			OP_MMX, // xmm
			OP_SREG, // segment registers
			OP_BND, // bound registers

			// memory
			OP_MEM_ADDRESS, // untyped memory address
			OP_MEM8,
			OP_MEM16,
			OP_MEM32,
			OP_MEM64,
			OP_MEM128,

			// immediates
			OP_I8,
			OP_I16,
			OP_I32,
			OP_I64,

			// moff
			OP_MOFF8,
			OP_MOFF16,
			OP_MOFF32,
			OP_MOFF64,

			// concrete registers
			OP_AL,
			OP_AX,
			OP_EAX,
			OP_RAX,
			OP_CL,
			OP_DX,
			OP_ECX,
			OP_RCX,
		};

		type type;

		union {
			u8 reg;
			imm immediate;
			mem memory;
			moff memory_offset;
		};
	};

	inline auto is_operand_mmx(enum operand::type op) -> bool {
		return op == operand::OP_MMX;
	}

	inline auto is_operand_bnd(enum operand::type op) -> bool {
		return op == operand::OP_BND;
	}

	inline auto is_operand_xmm(enum operand::type op) -> bool {
		return op == operand::OP_XMM;
	}

	inline auto is_operand_reg(enum operand::type op) -> bool {
		switch(op) {
			case operand::OP_REG8:
			case operand::OP_REG16:
			case operand::OP_REG32:
			case operand::OP_REG64:
			case operand::OP_XMM:
			case operand::OP_MMX:
			case operand::OP_SREG:
			case operand::OP_BND:   return true;
			default: return false;
		}
	}

	inline auto is_operand_gp_reg(enum operand::type op) -> bool {
		switch(op) {
			case operand::OP_REG8:
			case operand::OP_REG16:
			case operand::OP_REG32:
			case operand::OP_REG64: return true;
			default: return false;
		}
	}

	inline auto is_operand_mem(enum operand::type op) -> bool {
		switch(op) {
			case operand::OP_MEM_ADDRESS:
			case operand::OP_MEM8:
			case operand::OP_MEM16:
			case operand::OP_MEM32:
			case operand::OP_MEM64:
			case operand::OP_MEM128:  return true;
			default: return false;
		}
	}

	inline auto is_operand_moff(enum operand::type op) -> bool {
		switch(op) {
		case operand::OP_MOFF8:
		case operand::OP_MOFF16:
		case operand::OP_MOFF32:
		case operand::OP_MOFF64:  return true;
		default: return false;
		}
	}

	inline constexpr auto is_operand_imm(enum operand::type op) -> bool {
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
			case operand::OP_NONE:        return 0;
			case operand::OP_REG8:        return 8;
			case operand::OP_REG16:       return 16;
			case operand::OP_REG32:       return 32;
			case operand::OP_REG64:       return 64;
			case operand::OP_MMX:         return 64;
			case operand::OP_XMM:         return 128;
			case operand::OP_BND:         return 64; // (?)
			case operand::OP_SREG:        return 16;
			case operand::OP_MEM_ADDRESS: return 0; // (?)
			case operand::OP_MEM8:        return 8;
			case operand::OP_MEM16:       return 16;
			case operand::OP_MEM32:       return 32;
			case operand::OP_MEM64:       return 64;
			case operand::OP_MEM128:      return 128;
			case operand::OP_I8:          return 8;
			case operand::OP_I16:         return 16;
			case operand::OP_I32:         return 32;
			case operand::OP_I64:         return 64;
			case operand::OP_MOFF8:	      return 8;
			case operand::OP_MOFF16:      return 16;
			case operand::OP_MOFF32:      return 32;
			case operand::OP_MOFF64:      return 64;
			case operand::OP_AL:          return 8;
			case operand::OP_AX:          return 16;
			case operand::OP_EAX:         return 32;
			case operand::OP_RAX:         return 64;
			case operand::OP_CL:          return 8;
			case operand::OP_DX:          return 16;
			case operand::OP_ECX:         return 32;
			case operand::OP_RCX:         return 64;
			default:                      return 0;
		}
	}

	inline auto operand_type_to_string(enum operand::type op) -> const char* {
		switch(op) {
			case operand::OP_NONE:        return "none";

			case operand::OP_REG8:        return "r8";
			case operand::OP_REG16:       return "r16";
			case operand::OP_REG32:       return "r32";
			case operand::OP_REG64:       return "r64";
			case operand::OP_XMM:         return "xmm";
			case operand::OP_MMX:         return "xmm";
			case operand::OP_BND:         return "bnd";
			case operand::OP_SREG:        return "sreg";

			case operand::OP_MEM_ADDRESS: return "mem_address";
			case operand::OP_MEM8:        return "m8";
			case operand::OP_MEM16:       return "m16";
			case operand::OP_MEM32:       return "m32";
			case operand::OP_MEM64:       return "m64";
			case operand::OP_MEM128:      return "m128";

			case operand::OP_I8:          return "i8";
			case operand::OP_I16:         return "i16";
			case operand::OP_I32:         return "i32";
			case operand::OP_I64:         return "i64";

			case operand::OP_MOFF8:       return "moff8";
			case operand::OP_MOFF16:      return "moff16";
			case operand::OP_MOFF32:      return "moff32";
			case operand::OP_MOFF64:      return "moff64";

			case operand::OP_AL:          return "al";
			case operand::OP_AX:          return "ax";
			case operand::OP_EAX:         return "eax";
			case operand::OP_RAX:         return "rax";

			case operand::OP_CL:          return "cl";
			case operand::OP_DX:          return "dx";
			case operand::OP_ECX:         return "ecx";
			case operand::OP_RCX:         return "rcx";
		}

		return "unknown";
	}
} // namespace baremetal
