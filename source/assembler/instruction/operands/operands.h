#pragma once
#include "assembler/instruction/operands/memory.h"

namespace baremetal {
	enum operand_type : u8 {
		OP_NONE = 0,

		// register operands
		OP_R8   = REG_R8,
		OP_R16  = REG_R16,
		OP_R32  = REG_R32,
		OP_R64  = REG_R64,
		OP_XMM  = REG_XMM,
		OP_YMM  = REG_YMM,
		OP_ZMM  = REG_ZMM,
		OP_TMM  = REG_TMM,
		OP_MMX  = REG_MMX,
		OP_K    = REG_K,
		OP_ST   = REG_ST,
		OP_SREG = REG_SREG,
		OP_DREG = REG_DREG,
		OP_CREG = REG_CREG,
		OP_BND  = REG_BND,

		OP_AL,
		OP_CL,
		OP_AX,
		OP_DX,
		OP_EAX,
		OP_ECX,
		OP_EDX,
		OP_RAX,
		OP_RCX,
		OP_ST0,
		OP_ES,
		OP_CS,
		OP_SS,
		OP_DS,
		OP_FS,
		OP_GS,

		// masked register operands
		OP_K_K,    // k{k}
		OP_XMM_K,  // xmm{k}
		OP_XMM_KZ, // xmm{k}{z}
		OP_YMM_K,  // xmm{k}
		OP_YMM_KZ, // xmm{k}{z}
		OP_ZMM_K,  // xmm{k}
		OP_ZMM_KZ, // xmm{k}{z},

		// memory operands
		OP_M8,
		OP_M16,
		OP_M32,
		OP_M64,
		OP_M80,
		OP_M128,
		OP_M256,
		OP_M512,
		OP_MEM,
		OP_TMEM,
		OP_MOFF8,
		OP_MOFF32,
		OP_MOFF16,
		OP_MOFF64,
		OP_MIB,

		// immediate operands
		OP_I8,
		OP_I16,
		OP_I32,
		OP_I64,

		// broadcasts
		OP_B16,
		OP_B32,
		OP_B64,

		// relocations
		OP_REL8,
		OP_REL16,
		OP_REL32,

		OP_HIDDEN, // usually an operand which refers to an implicit value, ie a '1'
	};

	struct operand {
		constexpr operand() : type(OP_NONE), r(0) {}
		constexpr operand(imm i) : type(OP_I64), immediate(i) {}
		constexpr operand(reg r) : type(static_cast<operand_type>(r.type)), r(r.index) {}
		constexpr operand(moff m) : type(OP_MOFF64), memory_offset(m) {}
		constexpr operand(rel r) : type(OP_REL32), relocation(r) {}
		constexpr operand(broadcast b, operand_type op) : type(op), b(b) {}

		operand_type type;

		union {
			moff memory_offset;
			rel relocation;
			imm immediate;
			mem memory;
			broadcast b;
			u8 r; // register
			masked_reg mr; // masked register
		};
	};

	inline auto is_operand_xmm(operand_type op) -> bool {
		return op == OP_XMM || op == OP_XMM_K || op == OP_XMM_KZ;
	}
	
	inline auto is_operand_ymm(operand_type op) -> bool {
		return op == OP_YMM || op == OP_YMM_KZ || op == OP_YMM_K;
	}
	
	inline auto is_operand_zmm(operand_type op) -> bool {
		return op == OP_ZMM || op == OP_ZMM_K || op == OP_ZMM_KZ;
	}
	
	inline auto is_operand_large_reg(operand_type op) -> bool {
		return is_operand_xmm(op) || is_operand_ymm(op) || is_operand_zmm(op);
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

	inline auto is_operand_rax(operand_type op) -> bool {
		switch(op) {
			case OP_RAX:
			case OP_EAX:
			case OP_AX: return true;
			default: return false;
		}
	}

	inline auto is_operand_broadcast(operand_type op) -> bool {
		switch(op) {
			case OP_B16:
			case OP_B32:
			case OP_B64: return true;
			default: return false;
		}
	}

	inline auto is_operand_mem(operand_type op) -> bool {
		switch(op) {
			case OP_MEM:
			case OP_TMEM:
			case OP_M8:
			case OP_M16:
			case OP_M32:
			case OP_M64:
			case OP_M80:
			case OP_M128:
			case OP_M256:
			case OP_M512:  return true;
			default: return false;
		}
	}

	inline auto is_operand_reg(operand_type op) -> bool {
    switch(op) {
      case OP_AL:
      case OP_CL:
      case OP_AX:
      case OP_DX:
      case OP_EAX:
      case OP_ECX:
      case OP_EDX:
      case OP_RAX:
      case OP_RCX:
      case OP_R8:
      case OP_R16:
      case OP_R32:
      case OP_R64:
      case OP_XMM:
      case OP_XMM_K:
      case OP_XMM_KZ:
      case OP_YMM:
      case OP_YMM_K:
      case OP_YMM_KZ:
      case OP_ZMM:
      case OP_ZMM_K:
      case OP_ZMM_KZ:
      case OP_TMM:
      case OP_MMX:
      case OP_K:
      case OP_K_K:
      case OP_ST0:
      case OP_ST:
      case OP_SREG:
      case OP_DREG:
      case OP_CREG:
      case OP_BND: return true;
      default: return false;
    }
	}

	inline auto is_extended_reg(const operand& op) -> bool {
		if(is_operand_reg(op.type)) {
			return op.r >= 8;
		}

		return false;
	}

	inline auto get_operand_bit_width(operand_type op) -> u16 {
    switch(op) {
      case OP_NONE:
      case OP_MEM:
      case OP_HIDDEN: return 0;
      case OP_I8:
      case OP_R8:
      case OP_AL:
      case OP_CL:
      case OP_MOFF8:
      case OP_M8:
      case OP_REL8: return 8;
      case OP_I16:
      case OP_R16:
      case OP_SREG:
      case OP_GS:
      case OP_ES:
      case OP_FS:
      case OP_SS:
      case OP_DS:
      case OP_CS:
      case OP_AX:
      case OP_B16:
      case OP_DX:
      case OP_MOFF16:
      case OP_REL16:
      case OP_M16: return 16;
      case OP_I32:
      case OP_R32:
      case OP_EAX:
      case OP_ECX:
      case OP_EDX:
      case OP_B32:
      case OP_MOFF32:
      case OP_M32:
      case OP_REL32: return 32;
      case OP_I64:
      case OP_R64:
      case OP_MOFF64:
      case OP_M64:
      case OP_CREG:
      case OP_DREG:
      case OP_MMX:
      case OP_BND:
      case OP_RCX:
      case OP_RAX:
      case OP_MIB:
      case OP_K_K:
      case OP_K:
      case OP_B64: return 64;
      case OP_M80:
      case OP_ST:
      case OP_ST0: return 80;
      case OP_XMM:
      case OP_XMM_K:
      case OP_XMM_KZ:
      case OP_M128: return 128;
      case OP_YMM:
      case OP_YMM_K:
      case OP_YMM_KZ:
      case OP_M256: return 256;
      case OP_ZMM:
      case OP_ZMM_K:
      case OP_ZMM_KZ:
      case OP_M512: return 512;
      case OP_TMEM:
      case OP_TMM: return 1024;
    }

    return 0; // unreachable
	}

	inline auto is_operand_masked(operand_type op) -> bool {
		switch(op) {
			case OP_K_K:
			case OP_ZMM_K:
			case OP_ZMM_KZ:
			case OP_YMM_K:
			case OP_YMM_KZ:
			case OP_XMM_K:
			case OP_XMM_KZ: return true;
			default: return false;
		}
	}
} // namespace baremetal

