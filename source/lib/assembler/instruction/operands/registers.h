#pragma once
#include <utility/types.h>

namespace baremetal::assembler {
	using namespace utility::types;

	// register names
	// TODO: distinguish between low and high 8b GPR registers
	static constexpr const char* g_gpr8l_names[] = { "al", "bl", "cl", "dl", "sil", "dil", "spl", "bpl", "r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b" };
	static constexpr const char* g_gpr8h_names[] = { "ah", "bh", "ch", "dh" };
	static constexpr const char* g_gpr16_names[] = { "ax", "bx", "cx", "dx", "si", "di", "sp", "bp", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w" };
	static constexpr const char* g_gpr32_names[] = { "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" };
	static constexpr const char* g_gpr64_names[] = { "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" };
	static constexpr const char* g_xmm_names  [] = { "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15" };
	static constexpr const char* g_ymm_names  [] = { "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7", "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15" };
	static constexpr const char* g_zmm_names  [] = { "zmm1", "zmm2", "zmm3", "zmm4", "zmm5", "zmm6", "zmm7", "zmm8", "zmm9", "zmm10", "zmm11", "zmm12", "zmm13", "zmm14", "zmm15","zmm16", "zmm17", "zmm18", "zmm19", "zmm20", "zmm21", "zmm22", "zmm23", "zmm24", "zmm25", "zmm26", "zmm27", "zmm28", "zmm29", "zmm30", "zmm31" };
	static constexpr const char* g_tmm_names  [] = { "tmm0", "tmm1", "tmm2", "tmm3", "tmm4", "tmm5", "tmm6", "tmm7" };
	static constexpr const char* g_mmx_names  [] = { "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7" };
	static constexpr const char* g_k_names    [] = { "k0", "k1", "k2", "k3", "k4", "k5", "k6", "k7" };
	static constexpr const char* g_st_names   [] = { "st0", "st1", "st2", "st3", "st4", "st5", "st6", "st7" };
	static constexpr const char* g_sreg_names [] = { "es", "cs", "ss", "ds", "fs", "gs" };
	static constexpr const char* g_dreg_names [] = { "dr0", "dr1", "dr2", "dr3", "dr4", "dr5", "dr6", "dr7" };
	// cr1 is reserved an not used, cr5, cr6, cr7 are unused
	static constexpr const char* g_creg_names [] = { "cr0", "cr1", "cr2", "cr3", "cr4", "cr5", "cr6", "cr7", "cr8" };
	static constexpr const char* g_bnd_names  [] = { "bnd0", "bnd1", "bnd2", "bnd3" };

	enum reg_type : u8 {
		REG_NONE = 0,
		
		// general purpose registers
		REG_R8,
		REG_R16,
		REG_R32,
		REG_R64,
		
		// instruction pointer
		REG_RIP,

		// vector registers
		REG_XMM,  // 128-bit
		REG_YMM,  // 256-bit
		REG_ZMM,  // 512-bit
		REG_TMM,  // tensor (varies by ISA)

		REG_MMX,  // mmx registers
		REG_K,    // mask registers
		REG_ST,   // floating point registers
		REG_SREG, // segment registers
		REG_DREG, // debug registers
		REG_CREG, // control registers
		REG_BND   // bound registers
	};

	struct reg {
		constexpr reg() : index(0), type() {}
		constexpr explicit reg(u8 index, reg_type ty) : index(index), type(ty) {}
		[[nodiscard]] constexpr auto is_valid() const -> bool { return index != utility::limits<u8>::max(); }
		[[nodiscard]] constexpr static auto create_invalid() -> reg { return reg(utility::limits<u8>::max(), REG_NONE); }

		u8 index;
		reg_type type;
	};

	struct masked_reg {
		u8 index;
		u8 k;
	};

#define REGISTER_GP_DECL(bits)                                       \
  struct reg ## bits : reg {                                         \
    constexpr reg ## bits () = default;                              \
    constexpr explicit reg ## bits (u8 i) : reg(i, REG_R ## bits) {} \
  };

	REGISTER_GP_DECL(8);
	REGISTER_GP_DECL(16);
	REGISTER_GP_DECL(32);
	REGISTER_GP_DECL(64);

	struct xmm : reg {
		constexpr xmm() = default;
		constexpr explicit xmm(u8 i) : reg(i, REG_XMM) {}
	};

	struct ymm : reg {
		constexpr ymm() = default;
		constexpr explicit ymm(u8 i) : reg(i, REG_YMM) {}
	};

	struct zmm : reg {
		constexpr zmm() = default;
		constexpr explicit zmm(u8 i,reg_type ty) : reg(i, ty) {}
	};

	struct mmx : reg {
		constexpr mmx() = default;
		constexpr explicit mmx(u8 i) : reg(i, REG_MMX) {}
	};

	struct tmm : reg {
		constexpr tmm() = default;
		constexpr explicit tmm(u8 i) : reg(i, REG_TMM) {}
	};

	struct bnd : reg {
		constexpr bnd() = default;
		constexpr explicit bnd(u8 i) : reg(i, REG_BND) {}
	};

	struct st : reg {
		constexpr st() = default;
		constexpr explicit st(u8 i) : reg(i, REG_ST) {}
	};

	struct sreg : reg {
		constexpr sreg() = default;
		constexpr explicit sreg(u8 i) : reg(i, REG_SREG) {}
	};

	struct dreg : reg {
		constexpr dreg() = default;
		constexpr explicit dreg(u8 i) : reg(i, REG_DREG) {}
	};

	struct creg : reg {
		constexpr creg() = default;
		constexpr explicit creg(u8 i) : reg(i, REG_CREG) {}
	};

	struct kreg : reg {
		constexpr kreg() = default;
		constexpr explicit kreg(u8 i) : reg(i, REG_K) {}
	};

	constexpr u8 al = 0;
	constexpr u8 ax = 0;
	constexpr u8 eax = 0;
	constexpr u8 rax = 0;
	constexpr u8 st0 = 0;
	
	constexpr u8 cl = 1;
	constexpr u8 ecx = 1;
	constexpr u8 rcx = 1;
	
	constexpr u8 dx = 2;

	constexpr u8 spl = 4;
	constexpr u8 bpl = 5;
	constexpr u8 sil = 6;
	constexpr u8 dil = 7;
	
	constexpr u8 rsp = 4;
	constexpr u8 fs = 4;

	constexpr u8 gs = 5;
	constexpr reg rip(0, REG_RIP);

	[[nodiscard]] inline auto is_gp_reg(reg r) {
		switch(r.type) {
			case REG_R8:
			case REG_R16:
			case REG_R32:
			case REG_R64: return true;
			default: return false;
		}
	}

	[[nodiscard]] inline auto is_sse_reg(reg r) {
		switch(r.type) {
			case REG_XMM:
			case REG_YMM:
			case REG_ZMM: return true;
			default: return false;
		}
	}

	[[nodiscard]] inline auto is_stack_pointer(reg r) -> bool {
		return r.index == rsp && is_gp_reg(r);
	}

	[[nodiscard]] inline auto register_to_string(reg r) -> const char* {
		switch(r.type) {
			case REG_R8:   return g_gpr8l_names[r.index];
			case REG_R16:  return g_gpr16_names[r.index];
			case REG_R32:  return g_gpr32_names[r.index];
			case REG_R64:  return g_gpr64_names[r.index];
			case REG_RIP:  return "rel $";
			case REG_XMM:  return g_xmm_names[r.index];
			case REG_YMM:  return g_ymm_names[r.index];
			case REG_ZMM:  return g_zmm_names[r.index];
			case REG_TMM:  return g_tmm_names[r.index];
			case REG_MMX:  return g_mmx_names[r.index];
			case REG_K:    return g_k_names[r.index];
			case REG_ST:   return g_st_names[r.index];
			case REG_SREG: return g_sreg_names[r.index];
			case REG_DREG: return g_dreg_names[r.index];
			case REG_CREG: return g_creg_names[r.index];
			case REG_BND:  return g_bnd_names[r.index];
			default:       return "unknown reg class";
		}
	}
} // namespace baremetal::assembler
