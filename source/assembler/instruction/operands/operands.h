#pragma once
#include "assembler/instruction/operands/memory.h"

namespace baremetal {
	enum operand_type : u8 {
		OP_NONE,

		// registers
		OP_REG8,
		OP_REG16,
		OP_REG32,
		OP_REG64,
		OP_MMX,
		OP_XMM,
		OP_YMM,
		OP_ZMM_L, // zmm0-zmm15
		OP_ZMM_H, // zmm16-zmm31
		OP_SREG,  // segment registers
		OP_DREG,  // debug registers
		OP_CREG,  // control registers
		OP_BND,   // bound registers

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

		// specific registers
		OP_AL,
		OP_AX,
		OP_EAX,
		OP_RAX,
		OP_CL,
		OP_DX,
		OP_ECX,
		OP_RCX,

		// relocations
		OP_REL8,
		OP_REL16,
		OP_REL32,
	};

	struct operand {
		constexpr operand() : type(OP_NONE), r(0) {}

		// immediates
		constexpr operand(imm i) : type(OP_I64), immediate(i) {}

		// registers
		static_assert(static_cast<u8>(REG_GP_8) == static_cast<u8>(OP_REG8));
		static_assert(static_cast<u8>(REG_GP_16) == static_cast<u8>(OP_REG16));
		static_assert(static_cast<u8>(REG_GP_32) == static_cast<u8>(OP_REG32));
		static_assert(static_cast<u8>(REG_GP_64) == static_cast<u8>(OP_REG64));
		static_assert(static_cast<u8>(REG_XMM) == static_cast<u8>(OP_XMM));
		static_assert(static_cast<u8>(REG_YMM) == static_cast<u8>(OP_YMM));
		static_assert(static_cast<u8>(REG_ZMM_L) == static_cast<u8>(OP_ZMM_L));
		static_assert(static_cast<u8>(REG_ZMM_H) == static_cast<u8>(OP_ZMM_H));
		static_assert(static_cast<u8>(REG_BND) == static_cast<u8>(OP_BND));
		static_assert(static_cast<u8>(REG_MMX) == static_cast<u8>(OP_MMX));
		static_assert(static_cast<u8>(REG_SREG) == static_cast<u8>(OP_SREG));
		static_assert(static_cast<u8>(REG_DREG) == static_cast<u8>(OP_DREG));
		static_assert(static_cast<u8>(REG_CREG) == static_cast<u8>(OP_CREG));

		constexpr operand(reg r) : type(static_cast<operand_type>(r.type)), r(r.index) {}

		// memory
		constexpr operand(mem_address m) : type(OP_MEM_ADDRESS), memory(m) {}
		constexpr operand(moff m) : type(OP_MOFF64), memory_offset(m) {}
		constexpr operand(mem128 m) : type(OP_MEM128), memory(m) {}
		constexpr operand(mem64 m) : type(OP_MEM64), memory(m) {}
		constexpr operand(mem32 m) : type(OP_MEM32), memory(m) {}
		constexpr operand(mem16 m) : type(OP_MEM16), memory(m) {}
		constexpr operand(mem8 m) : type(OP_MEM8), memory(m) {}

		constexpr operand(rel r) : type(OP_REL32), relocation(r) {}

		operand_type type;

		union {
			moff memory_offset;
			rel relocation;
			imm immediate;
			mem memory;
			u8 r; // register
		};
	};

	inline auto is_operand_creg(operand_type op) -> bool {
		return op == OP_CREG;
	}

	inline auto is_operand_mmx(operand_type op) -> bool {
		return op == OP_MMX;
	}

	inline auto is_operand_bnd(operand_type op) -> bool {
		return op == OP_BND;
	}

	inline auto is_operand_xmm(operand_type op) -> bool {
		return op == OP_XMM;
	}

	inline auto is_operand_reg(operand_type op) -> bool {
		switch(op) {
			case OP_REG8:
			case OP_REG16:
			case OP_REG32:
			case OP_REG64:
			case OP_XMM:
			case OP_YMM:
			case OP_ZMM_L:
			case OP_ZMM_H:
			case OP_MMX:
			case OP_SREG:
			case OP_DREG:
			case OP_CREG:
			case OP_AL:
			case OP_AX:
			case OP_EAX:
			case OP_RAX:
			case OP_CL:
			case OP_DX:
			case OP_ECX:
			case OP_RCX:
			case OP_BND: return true;
			default: return false;
		}
	}

	inline auto is_operand_gp_reg(operand_type op) -> bool {
		switch(op) {
			case OP_REG8:
			case OP_REG16:
			case OP_REG32:
			case OP_REG64: return true;
			default: return false;
		}
	}

	inline auto is_operand_mem(operand_type op) -> bool {
		switch(op) {
			case OP_MEM_ADDRESS:
			case OP_MEM8:
			case OP_MEM16:
			case OP_MEM32:
			case OP_MEM64:
			case OP_MEM128:  return true;
			default: return false;
		}
	}

	inline auto is_operand_moff(operand_type op) -> bool {
		switch(op) {
			case OP_MOFF8:
			case OP_MOFF16:
			case OP_MOFF32:
			case OP_MOFF64:  return true;
			default: return false;
		}
	}

	inline auto is_operand_imm(operand_type op) -> bool {
		switch(op) {
			case OP_I8:
			case OP_I16:
			case OP_I32:
			case OP_I64:  return true;
			default: return false;
		}
	}

	inline auto is_operand_rel(operand_type op) -> bool {
		switch(op) {
			case OP_REL8:
			case OP_REL16:
			case OP_REL32: return true;
			default: return false;
		}
	}

	inline auto is_extended_reg(const operand& op) -> bool {
		if(is_operand_reg(op.type)) {
			return op.r >= 8;
		}

		return false;
	}

	inline auto is_extended_xmm_reg(const operand& op) -> bool {
		if(is_operand_xmm(op.type)) {
			return op.r >= 8;
		}

		return false;
	}

	inline auto is_extended_gp_reg(const operand& op) -> bool {
		if(is_operand_gp_reg(op.type)) {
			return op.r >= 8;
		}

		return false;
	}

	inline auto get_operand_bit_width(operand_type op) -> u16 {
		switch(op) {
			case OP_MEM_ADDRESS:
			case OP_NONE:        return 0;
			case OP_MOFF8:
			case OP_MEM8:
			case OP_REL8:
			case OP_REG8:
			case OP_AL:
			case OP_CL: 
			case OP_I8:          return 8;
			case OP_MOFF16:
			case OP_REL16:
			case OP_MEM16:
			case OP_REG16:
			case OP_SREG:
			case OP_AX:
			case OP_DX:
			case OP_I16:         return 16;
			case OP_MOFF32:
			case OP_MEM32:
			case OP_REL32:
			case OP_REG32:
			case OP_EAX:
			case OP_ECX:
			case OP_I32:         return 32;
			case OP_MOFF64:
			case OP_MEM64:
			case OP_REG64:
			case OP_CREG:
			case OP_DREG:
			case OP_MMX:
			case OP_BND:
			case OP_RCX:
			case OP_RAX:
			case OP_I64:         return 64;
			case OP_MEM128:
			case OP_XMM:         return 128;
			case OP_ZMM_H:
			case OP_YMM:         return 256;
			case OP_ZMM_L:       return 512;
		}

		return 0; // unreachable
	}

	inline auto operand_type_to_string(operand_type op) -> const char* {
		switch(op) {
			case OP_NONE:        return "none";
			case OP_REG8:        return "r8";
			case OP_REG16:       return "r16";
			case OP_REG32:       return "r32";
			case OP_REG64:       return "r64";
			case OP_XMM:         return "xmm";
			case OP_MMX:         return "mmx";
			case OP_BND:         return "bnd";
			case OP_SREG:        return "sreg";
			case OP_DREG:        return "dreg";
			case OP_CREG:        return "creg";
			case OP_MEM_ADDRESS: return "mem_address";
			case OP_MEM8:        return "m8";
			case OP_MEM16:       return "m16";
			case OP_MEM32:       return "m32";
			case OP_MEM64:       return "m64";
			case OP_MEM128:      return "m128";
			case OP_I8:          return "i8";
			case OP_I16:         return "i16";
			case OP_I32:         return "i32";
			case OP_I64:         return "i64";
			case OP_MOFF8:       return "moff8";
			case OP_MOFF16:      return "moff16";
			case OP_MOFF32:      return "moff32";
			case OP_MOFF64:      return "moff64";
			case OP_AL:          return "al";
			case OP_AX:          return "ax";
			case OP_EAX:         return "eax";
			case OP_RAX:         return "rax";
			case OP_CL:          return "cl";
			case OP_DX:          return "dx";
			case OP_ECX:         return "ecx";
			case OP_RCX:         return "rcx";
			case OP_REL8:        return "rel8";
			case OP_REL16:       return "rel16";
			case OP_REL32:       return "rel32";
			case OP_YMM:         return "ymm";
			case OP_ZMM_L:       
			case OP_ZMM_H:       return "zmm";
		}

		return "unknown";
	}
} // namespace baremetal
