#pragma once
#include "assembler/instruction/operands/memory.h"

#include <utility/containers/string_view.h>
#include <utility/assert.h>

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

		// memory operands with SSE registers
		OP_VM32X,
		OP_VM32Y,
		OP_VM32Z,
		OP_VM64X,
		OP_VM64Y,
		OP_VM64Z,

		// masked memory operands
		OP_M16_K,
		OP_M32_K,
		OP_M64_K,
		OP_M128_K,
		OP_M256_K,
		OP_M512_K,

		// masked memory operands with SSE registers
		OP_VM32X_K,
		OP_VM32Y_K,
		OP_VM32Z_K,
		OP_VM64X_K,
		OP_VM64Y_K,
		OP_VM64Z_K,

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
		OP_REL8_RIP,  // rel8  + rip
		OP_REL16_RIP, // rel16 + rip
		OP_REL32_RIP, // rel32 + rip
		OP_REL_UNKNOWN,

		OP_HIDDEN, // usually an operand which refers to an implicit value, ie a '1'
	};

	struct operand {
		constexpr operand() : type(OP_NONE), r(0) {}
		constexpr operand(imm i) : type(OP_I64), immediate(i) {}
		constexpr operand(reg r) : type(static_cast<operand_type>(r.type)), r(r.index) {}
		constexpr operand(moff m) : type(OP_MOFF64), memory_offset(m) {}
		constexpr operand(rel r) : type(OP_REL32), relocation(r) {}
		constexpr operand(utility::string_view* symbol) : type(OP_REL_UNKNOWN), symbol(symbol) {}

		operand_type type;
		bool unknown = false;
		utility::string_view* symbol;

		union {
			masked_mem mm; // masked memory location
			masked_reg mr; // masked register

			moff memory_offset;
			mem memory;

			rel relocation;
			imm immediate;
			u8 r; // register
		};
	};

	inline auto operand_type_to_string(operand_type op) -> const char* {
		switch(op) {
			case OP_NONE:        return "NONE"; 
			case OP_R8:          return "R8"; 
			case OP_R16:         return "R16"; 
			case OP_R32:         return "R32"; 
			case OP_R64:         return "R64"; 
			case OP_XMM:         return "XMM"; 
			case OP_YMM:         return "YMM"; 
			case OP_ZMM:         return "ZMM"; 
			case OP_TMM:         return "TMM"; 
			case OP_MMX:         return "MMX"; 
			case OP_K:           return "K"; 
			case OP_ST:          return "ST"; 
			case OP_SREG:        return "SREG"; 
			case OP_DREG:        return "DREG"; 
			case OP_CREG:        return "CREG"; 
			case OP_BND:         return "BND"; 
			case OP_AL:          return "AL"; 
			case OP_CL:          return "CL"; 
			case OP_AX:          return "AX"; 
			case OP_DX:          return "DX"; 
			case OP_EAX:         return "EAX"; 
			case OP_ECX:         return "ECX"; 
			case OP_EDX:         return "EDX"; 
			case OP_RAX:         return "RAX"; 
			case OP_RCX:         return "RCX"; 
			case OP_ST0:         return "ST0"; 
			case OP_ES:          return "ES"; 
			case OP_CS:          return "CS"; 
			case OP_SS:          return "SS"; 
			case OP_DS:          return "DS"; 
			case OP_FS:          return "FS"; 
			case OP_GS:          return "GS"; 
			case OP_K_K:         return "K_K"; 
			case OP_XMM_K:       return "XMM_K"; 
			case OP_XMM_KZ:      return "XMM_KZ"; 
			case OP_YMM_K:       return "YMM_K"; 
			case OP_YMM_KZ:      return "YMM_KZ"; 
			case OP_ZMM_K:       return "ZMM_K"; 
			case OP_ZMM_KZ:      return "ZMM_KZ"; 
			case OP_M8:          return "M8"; 
			case OP_M16:         return "M16"; 
			case OP_M32:         return "M32"; 
			case OP_M64:         return "M64"; 
			case OP_M80:         return "M80"; 
			case OP_M128:        return "M128"; 
			case OP_M256:        return "M256"; 
			case OP_M512:        return "M512"; 
			case OP_MEM:         return "MEM"; 
			case OP_TMEM:        return "TMEM"; 
			case OP_MOFF8:       return "MOFF8"; 
			case OP_MOFF16:      return "MOFF16"; 
			case OP_MOFF32:      return "MOFF32"; 
			case OP_MOFF64:      return "MOFF64"; 
			case OP_MIB:         return "MIB"; 
			case OP_VM32X:       return "VM32X"; 
			case OP_VM32Y:       return "VM32Y"; 
			case OP_VM32Z:       return "VM32Z"; 
			case OP_VM64X:       return "VM64X"; 
			case OP_VM64Y:       return "VM64Y"; 
			case OP_VM64Z:       return "VM64Z"; 
			case OP_M16_K:       return "M16_K"; 
			case OP_M32_K:       return "M32_K"; 
			case OP_M64_K:       return "M64_K"; 
			case OP_M128_K:      return "M128_K"; 
			case OP_M256_K:      return "M256_K"; 
			case OP_M512_K:      return "M512_K"; 
			case OP_VM32X_K:     return "VM32X_K"; 
			case OP_VM32Y_K:     return "VM32Y_K"; 
			case OP_VM32Z_K:     return "VM32Z_K"; 
			case OP_VM64X_K:     return "VM64X_K"; 
			case OP_VM64Y_K:     return "VM64Y_K"; 
			case OP_VM64Z_K:     return "VM64Z_K"; 
			case OP_I8:          return "I8"; 
			case OP_I16:         return "I16"; 
			case OP_I32:         return "I32"; 
			case OP_I64:         return "I64"; 
			case OP_B16:         return "B16"; 
			case OP_B32:         return "B32"; 
			case OP_B64:         return "B64"; 
			case OP_REL8:        return "REL8"; 
			case OP_REL16:       return "REL16"; 
			case OP_REL32:       return "REL32"; 
			case OP_REL8_RIP:    return "REL8_RIP"; 
			case OP_REL16_RIP:   return "REL16_RIP"; 
			case OP_REL32_RIP:   return "REL32_RIP"; 
			case OP_REL_UNKNOWN: return "REL_UNKNOWN"; 
			case OP_HIDDEN:      return "HIDDEN"; 
		}

		return "";
	}

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

	inline auto is_operand_rip_rel(operand_type op) -> bool {
		switch(op) {
			case OP_REL8_RIP:
			case OP_REL16_RIP:
			case OP_REL32_RIP: return true;
			default: return false;
		}
	}

	inline auto is_operand_rel(operand_type op) -> bool {
		switch(op) {
			case OP_REL8:
			case OP_REL16:
			case OP_REL32: 
			case OP_REL8_RIP:
			case OP_REL16_RIP:
			case OP_REL32_RIP: return true;
			default: return false;
		}
	}

	inline auto is_operand_masked_mem(operand_type op) -> bool {
		switch(op) {
			case OP_M16_K: 
			case OP_M32_K: 
			case OP_M64_K: 
			case OP_M128_K: 
			case OP_M256_K: 
			case OP_M512_K: return true;
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

	inline auto broadcast_to_bits(operand_type op) -> u8 {
		switch(op) {
			case OP_B16: return 16;
			case OP_B32: return 32;
			case OP_B64: return 64;
			default: return 0;
		}
	}

	inline auto is_operand_mem(operand_type op) -> bool {
		switch(op) {
			case OP_MEM:
			case OP_TMEM:
			case OP_M8:
			case OP_M16:
			case OP_M16_K:
			case OP_M32:
			case OP_M32_K:
			case OP_VM32X:
			case OP_VM32Y:
			case OP_VM32Z:
			case OP_VM32X_K:
			case OP_VM32Y_K:
			case OP_VM32Z_K:
			case OP_M64:
			case OP_M64_K:
			case OP_VM64X:
			case OP_VM64Y:
			case OP_VM64Z:
			case OP_VM64X_K:
			case OP_VM64Y_K:
			case OP_VM64Z_K:
			case OP_M80:
			case OP_M128:
			case OP_M128_K:
			case OP_M256:
			case OP_M256_K:
			case OP_M512:
			case OP_M512_K: return true;
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
			return op.r > 7;
		}

		return false;
	}

	inline auto get_operand_bit_width(operand_type op) -> u16 {
    switch(op) {
      case OP_NONE:
      case OP_MEM:
			case OP_REL_UNKNOWN:
      case OP_HIDDEN: return 0;
      case OP_I8:
      case OP_R8:
      case OP_AL:
      case OP_CL:
      case OP_MOFF8:
      case OP_M8:
      case OP_REL8_RIP:
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
      case OP_REL16_RIP:
      case OP_M16:
      case OP_M16_K: return 16;
      case OP_I32:
      case OP_R32:
      case OP_EAX:
      case OP_ECX:
      case OP_EDX:
      case OP_B32:
      case OP_MOFF32:
      case OP_M32:
      case OP_M32_K:
      case OP_REL32_RIP:
			case OP_VM32X:
			case OP_VM32Y:
			case OP_VM32Z:
			case OP_VM32X_K:
			case OP_VM32Y_K:
			case OP_VM32Z_K:
      case OP_REL32: return 32;
      case OP_I64:
      case OP_R64:
      case OP_MOFF64:
      case OP_M64:
      case OP_M64_K:
      case OP_CREG:
      case OP_DREG:
      case OP_MMX:
      case OP_BND:
      case OP_RCX:
      case OP_RAX:
      case OP_MIB:
      case OP_K_K:
			case OP_K:
			case OP_VM64X:
			case OP_VM64Y:
			case OP_VM64Z:
			case OP_VM64X_K:
			case OP_VM64Y_K:
			case OP_VM64Z_K:
      case OP_B64: return 64;
      case OP_M80:
      case OP_ST:
      case OP_ST0: return 80;
      case OP_XMM:
      case OP_XMM_K:
      case OP_XMM_KZ:
      case OP_M128:
      case OP_M128_K: return 128;
      case OP_YMM:
      case OP_YMM_K:
      case OP_YMM_KZ:
      case OP_M256:
      case OP_M256_K: return 256;
      case OP_ZMM:
      case OP_ZMM_K:
      case OP_ZMM_KZ:
      case OP_M512:
      case OP_M512_K: return 512;
      case OP_TMEM:
      case OP_TMM: return 1024;
    }

    return 0; // unreachable
	}

	inline auto is_operand_masked(operand_type op) -> bool {
		switch(op) {
			case OP_M16_K:
			case OP_M32_K:
			case OP_M64_K:
			case OP_M128_K:
			case OP_M256_K:
			case OP_M512_K:
			case OP_VM32X_K:
			case OP_VM32Y_K:
			case OP_VM32Z_K:
			case OP_VM64X_K:
			case OP_VM64Y_K:
			case OP_VM64Z_K:
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

