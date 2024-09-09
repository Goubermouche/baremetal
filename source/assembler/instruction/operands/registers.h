#pragma once
#include <utility/types.h>

namespace baremetal {
	using namespace utility::types;

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
    REG_K,    // mask registers:w
    REG_ST,   // floating point registers
    REG_SREG, // segment registers
    REG_DREG, // debug registers
    REG_CREG, // control registers
    REG_BND   // bound registers
};

	struct reg {
		constexpr reg() : index(0), type() {}
		constexpr explicit reg(u8 index, reg_type ty) : index(index), type(ty) {}
		constexpr auto is_valid() const -> bool { return index != utility::limits<u8>::max(); }
		constexpr static auto create_invalid() -> reg { return reg(utility::limits<u8>::max(), REG_NONE); }

		u8 index;
		reg_type type;
	};

	struct masked_reg {
		u8 index;
		u8 k;
	};

#define REGISTER_GP_DECL(bits)                                         \
  struct reg ## bits : reg {                                           \
    constexpr reg ## bits () = default;                                \
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

	struct reg_void : reg {
		constexpr reg_void() = default;
		constexpr explicit reg_void(u8 i, reg_type ty) : reg(i, ty) {}
	};

#define REGISTER_CLASS_CREG_DECL(name, index) \
  struct name : creg {                        \
    constexpr name() : creg(index) {}         \
  };                                          \
                                              \
  static inline constexpr name name;

#define REGISTER_CLASS_ST_DECL(name, index) \
  struct name : st {                        \
    constexpr name() : st(index) {}         \
  };                                        \
                                            \
  static inline constexpr name name;

#define REGISTER_CLASS_DREG_DECL(name, index) \
  struct name : dreg {                        \
    constexpr name() : dreg(index) {}         \
  };                                          \
                                              \
  static inline constexpr name name;

#define REGISTER_CLASS_SREG_DECL(name, index) \
  struct name : sreg {                        \
    constexpr name() : sreg(index) {}         \
  };                                          \
                                              \
  static inline constexpr name name;

#define REGISTER_CLASS_MMX_DECL(name, index) \
  struct name : mmx {                        \
    constexpr name() : mmx(index) {}         \
  };                                         \
                                             \
  static inline constexpr name name;

#define REGISTER_CLASS_XMM_DECL(name, index) \
  struct name : xmm {                        \
    constexpr name() : xmm(index) {}         \
  };                                         \
                                             \
  static inline constexpr name name;

#define REGISTER_CLASS_TMM_DECL(name, index) \
  struct name : tmm {                        \
    constexpr name() : tmm(index) {}         \
  };                                         \
                                             \
  static inline constexpr name name;

#define REGISTER_CLASS_YMM_DECL(name, index) \
  struct name : ymm {                        \
    constexpr name() : ymm(index) {}         \
  };                                         \
                                             \
  static inline constexpr name name;

#define REGISTER_CLASS_ZMM_DECL(name, index)  \
  struct name : zmm {                         \
    constexpr name() : zmm(index, REG_ZMM) {} \
  };                                          \
                                              \
  static inline constexpr name name;

#define REGISTER_CLASS_BND_DECL(name, index) \
  struct name : bnd {                        \
    constexpr name() : bnd(index) {}         \
  };                                         \
                                             \
  static inline constexpr name name;

#define REGISTER_CLASS_K_DECL(name, index) \
  struct name : kreg {                     \
    constexpr name() : kreg(index) {}      \
  };                                       \
                                           \
  static inline constexpr name name;

#define REGISTER_CLASS_64_DECL(name, index) \
  struct name : reg64 {                     \
    constexpr name() : reg64(index) {}      \
  };                                        \
                                            \
  static inline constexpr name name;

#define REGISTER_CLASS_32_DECL(name, index) \
  struct name : reg32 {                     \
    constexpr name() : reg32(index) {}      \
  };                                        \
                                            \
  static inline constexpr name name;

#define REGISTER_CLASS_16_DECL(name, index) \
  struct name : reg16 {                     \
    constexpr name() : reg16(index) {}      \
  };                                        \
                                            \
  static inline constexpr name name;

#define REGISTER_CLASS_8_DECL(name, index) \
  struct name : reg8 {                     \
    constexpr name() : reg8(index) {}      \
  };                                       \
                                           \
  static inline constexpr name name;

#define REGISTER_CLASS_VOID_DECL(name, index, type) \
  struct name : reg_void {                          \
    constexpr name() : reg_void(index, type) {}     \
  };                                                \
                                                    \
  static inline constexpr name name;

	// special registers
	REGISTER_CLASS_VOID_DECL(rip, 0, REG_RIP);

	// control registers
	REGISTER_CLASS_CREG_DECL(cr0, 0);
	REGISTER_CLASS_CREG_DECL(cr1, 1);
	REGISTER_CLASS_CREG_DECL(cr2, 2);
	REGISTER_CLASS_CREG_DECL(cr3, 3);
	REGISTER_CLASS_CREG_DECL(cr4, 4);
	REGISTER_CLASS_CREG_DECL(cr8, 8);
	// cr5, cr6, cr7 are typically not implemented
	
	REGISTER_CLASS_ST_DECL(st0, 0);
	REGISTER_CLASS_ST_DECL(st1, 1);
	REGISTER_CLASS_ST_DECL(st2, 2);
	REGISTER_CLASS_ST_DECL(st3, 3);
	REGISTER_CLASS_ST_DECL(st4, 4);
	REGISTER_CLASS_ST_DECL(st5, 5);
	REGISTER_CLASS_ST_DECL(st6, 6);
	REGISTER_CLASS_ST_DECL(st7, 7);

	// debug registers
	REGISTER_CLASS_DREG_DECL(dr0, 0);
	REGISTER_CLASS_DREG_DECL(dr1, 1);
	REGISTER_CLASS_DREG_DECL(dr2, 2);
	REGISTER_CLASS_DREG_DECL(dr3, 3);
	REGISTER_CLASS_DREG_DECL(dr4, 4);
	REGISTER_CLASS_DREG_DECL(dr5, 5);
	REGISTER_CLASS_DREG_DECL(dr6, 6);
	REGISTER_CLASS_DREG_DECL(dr7, 7);
	// dr8 to dr15 are typically not implemented

	REGISTER_CLASS_K_DECL(k1, 1);
	REGISTER_CLASS_K_DECL(k2, 2);
	REGISTER_CLASS_K_DECL(k3, 3);
	REGISTER_CLASS_K_DECL(k4, 4);
	REGISTER_CLASS_K_DECL(k5, 5);
	REGISTER_CLASS_K_DECL(k6, 6);
	REGISTER_CLASS_K_DECL(k7, 7);

	// segment registers
	REGISTER_CLASS_SREG_DECL(es, 0);
	REGISTER_CLASS_SREG_DECL(cs, 1);
	REGISTER_CLASS_SREG_DECL(ss, 2);
	REGISTER_CLASS_SREG_DECL(ds, 3);
	REGISTER_CLASS_SREG_DECL(fs, 4);
	REGISTER_CLASS_SREG_DECL(gs, 5);

	// bound registers
	REGISTER_CLASS_BND_DECL(bnd0, 0);
	REGISTER_CLASS_BND_DECL(bnd1, 1);
	REGISTER_CLASS_BND_DECL(bnd2, 2);
	REGISTER_CLASS_BND_DECL(bnd3, 3);

	// mmx registers
	REGISTER_CLASS_MMX_DECL(mm0, 0);
	REGISTER_CLASS_MMX_DECL(mm1, 1);
	REGISTER_CLASS_MMX_DECL(mm2, 2);
	REGISTER_CLASS_MMX_DECL(mm3, 3);
	REGISTER_CLASS_MMX_DECL(mm4, 4);
	REGISTER_CLASS_MMX_DECL(mm5, 5);
	REGISTER_CLASS_MMX_DECL(mm6, 6);
	REGISTER_CLASS_MMX_DECL(mm7, 7);

	REGISTER_CLASS_TMM_DECL(tmm0, 0);
	REGISTER_CLASS_TMM_DECL(tmm1, 1);
	REGISTER_CLASS_TMM_DECL(tmm2, 2);
	REGISTER_CLASS_TMM_DECL(tmm3, 3);
	REGISTER_CLASS_TMM_DECL(tmm4, 4);
	REGISTER_CLASS_TMM_DECL(tmm5, 5);
	REGISTER_CLASS_TMM_DECL(tmm6, 6);
	REGISTER_CLASS_TMM_DECL(tmm7, 7);

	// zmm registers
	REGISTER_CLASS_ZMM_DECL(zmm0, 0);
	REGISTER_CLASS_ZMM_DECL(zmm1, 1);
	REGISTER_CLASS_ZMM_DECL(zmm2, 2);
	REGISTER_CLASS_ZMM_DECL(zmm3, 3);
	REGISTER_CLASS_ZMM_DECL(zmm4, 4);
	REGISTER_CLASS_ZMM_DECL(zmm5, 5);
	REGISTER_CLASS_ZMM_DECL(zmm6, 6);
	REGISTER_CLASS_ZMM_DECL(zmm7, 7);
	REGISTER_CLASS_ZMM_DECL(zmm8, 8);
	REGISTER_CLASS_ZMM_DECL(zmm9, 9);
	REGISTER_CLASS_ZMM_DECL(zmm10, 10);
	REGISTER_CLASS_ZMM_DECL(zmm11, 11);
	REGISTER_CLASS_ZMM_DECL(zmm12, 12);
	REGISTER_CLASS_ZMM_DECL(zmm13, 13);
	REGISTER_CLASS_ZMM_DECL(zmm14, 14);
	REGISTER_CLASS_ZMM_DECL(zmm15, 15);
	REGISTER_CLASS_ZMM_DECL(zmm16, 16);
	REGISTER_CLASS_ZMM_DECL(zmm17, 17);
	REGISTER_CLASS_ZMM_DECL(zmm18, 18);
	REGISTER_CLASS_ZMM_DECL(zmm19, 19);
	REGISTER_CLASS_ZMM_DECL(zmm20, 20);
	REGISTER_CLASS_ZMM_DECL(zmm21, 21);
	REGISTER_CLASS_ZMM_DECL(zmm22, 22);
	REGISTER_CLASS_ZMM_DECL(zmm23, 23);
	REGISTER_CLASS_ZMM_DECL(zmm24, 24);
	REGISTER_CLASS_ZMM_DECL(zmm25, 25);
	REGISTER_CLASS_ZMM_DECL(zmm26, 26);
	REGISTER_CLASS_ZMM_DECL(zmm27, 27);
	REGISTER_CLASS_ZMM_DECL(zmm28, 28);
	REGISTER_CLASS_ZMM_DECL(zmm29, 29);
	REGISTER_CLASS_ZMM_DECL(zmm30, 30);
	REGISTER_CLASS_ZMM_DECL(zmm31, 31);

	// ymm registers
	REGISTER_CLASS_YMM_DECL(ymm0, 0);
	REGISTER_CLASS_YMM_DECL(ymm1, 1);
	REGISTER_CLASS_YMM_DECL(ymm2, 2);
	REGISTER_CLASS_YMM_DECL(ymm3, 3);
	REGISTER_CLASS_YMM_DECL(ymm4, 4);
	REGISTER_CLASS_YMM_DECL(ymm5, 5);
	REGISTER_CLASS_YMM_DECL(ymm6, 6);
	REGISTER_CLASS_YMM_DECL(ymm7, 7);
	REGISTER_CLASS_YMM_DECL(ymm8, 8);
	REGISTER_CLASS_YMM_DECL(ymm9, 9);
	REGISTER_CLASS_YMM_DECL(ymm10, 10);
	REGISTER_CLASS_YMM_DECL(ymm11, 11);
	REGISTER_CLASS_YMM_DECL(ymm12, 12);
	REGISTER_CLASS_YMM_DECL(ymm13, 13);
	REGISTER_CLASS_YMM_DECL(ymm14, 14);
	REGISTER_CLASS_YMM_DECL(ymm15, 15);
	REGISTER_CLASS_YMM_DECL(ymm16, 16);
	REGISTER_CLASS_YMM_DECL(ymm17, 17);
	REGISTER_CLASS_YMM_DECL(ymm18, 18);
	REGISTER_CLASS_YMM_DECL(ymm19, 19);
	REGISTER_CLASS_YMM_DECL(ymm20, 20);
	REGISTER_CLASS_YMM_DECL(ymm21, 21);
	REGISTER_CLASS_YMM_DECL(ymm22, 22);
	REGISTER_CLASS_YMM_DECL(ymm23, 23);
	REGISTER_CLASS_YMM_DECL(ymm24, 24);
	REGISTER_CLASS_YMM_DECL(ymm25, 25);
	REGISTER_CLASS_YMM_DECL(ymm26, 26);
	REGISTER_CLASS_YMM_DECL(ymm27, 27);
	REGISTER_CLASS_YMM_DECL(ymm28, 28);
	REGISTER_CLASS_YMM_DECL(ymm29, 29);
	REGISTER_CLASS_YMM_DECL(ymm30, 30);
	REGISTER_CLASS_YMM_DECL(ymm31, 31);

	// xmm registers
	REGISTER_CLASS_XMM_DECL(xmm0, 0);
	REGISTER_CLASS_XMM_DECL(xmm1, 1);
	REGISTER_CLASS_XMM_DECL(xmm2, 2);
	REGISTER_CLASS_XMM_DECL(xmm3, 3);
	REGISTER_CLASS_XMM_DECL(xmm4, 4);
	REGISTER_CLASS_XMM_DECL(xmm5, 5);
	REGISTER_CLASS_XMM_DECL(xmm6, 6);
	REGISTER_CLASS_XMM_DECL(xmm7, 7);
	REGISTER_CLASS_XMM_DECL(xmm8, 8);
	REGISTER_CLASS_XMM_DECL(xmm9, 9);
	REGISTER_CLASS_XMM_DECL(xmm10, 10);
	REGISTER_CLASS_XMM_DECL(xmm11, 11);
	REGISTER_CLASS_XMM_DECL(xmm12, 12);
	REGISTER_CLASS_XMM_DECL(xmm13, 13);
	REGISTER_CLASS_XMM_DECL(xmm14, 14);
	REGISTER_CLASS_XMM_DECL(xmm15, 15);

	// 64 bit gp registers
	REGISTER_CLASS_64_DECL(rax, 0);
	REGISTER_CLASS_64_DECL(rcx, 1);
	REGISTER_CLASS_64_DECL(rdx, 2);
	REGISTER_CLASS_64_DECL(rbx, 3);
	REGISTER_CLASS_64_DECL(rsp, 4);
	REGISTER_CLASS_64_DECL(rbp, 5);
	REGISTER_CLASS_64_DECL(rsi, 6);
	REGISTER_CLASS_64_DECL(rdi, 7);
	REGISTER_CLASS_64_DECL(r8, 8);
	REGISTER_CLASS_64_DECL(r9, 9);
	REGISTER_CLASS_64_DECL(r10, 10);
	REGISTER_CLASS_64_DECL(r11, 11);
	REGISTER_CLASS_64_DECL(r12, 12);
	REGISTER_CLASS_64_DECL(r13, 13);
	REGISTER_CLASS_64_DECL(r14, 14);
	REGISTER_CLASS_64_DECL(r15, 15);

	// 32 bit gp registers
	REGISTER_CLASS_32_DECL(eax, 0);
	REGISTER_CLASS_32_DECL(ecx, 1);
	REGISTER_CLASS_32_DECL(edx, 2);
	REGISTER_CLASS_32_DECL(ebx, 3);
	REGISTER_CLASS_32_DECL(esp, 4);
	REGISTER_CLASS_32_DECL(ebp, 5);
	REGISTER_CLASS_32_DECL(esi, 6);
	REGISTER_CLASS_32_DECL(edi, 7);
	REGISTER_CLASS_32_DECL(r8d, 8);
	REGISTER_CLASS_32_DECL(r9d, 9);
	REGISTER_CLASS_32_DECL(r10d, 10);
	REGISTER_CLASS_32_DECL(r11d, 11);
	REGISTER_CLASS_32_DECL(r12d, 12);
	REGISTER_CLASS_32_DECL(r13d, 13);
	REGISTER_CLASS_32_DECL(r14d, 14);
	REGISTER_CLASS_32_DECL(r15d, 15);

	// 16 bit gp registers
	REGISTER_CLASS_16_DECL(ax, 0);
	REGISTER_CLASS_16_DECL(cx, 1);
	REGISTER_CLASS_16_DECL(dx, 2);
	REGISTER_CLASS_16_DECL(bx, 3);
	REGISTER_CLASS_16_DECL(sp, 4);
	REGISTER_CLASS_16_DECL(bp, 5);
	REGISTER_CLASS_16_DECL(si, 6);
	REGISTER_CLASS_16_DECL(di, 7);
	REGISTER_CLASS_16_DECL(r8w, 8);
	REGISTER_CLASS_16_DECL(r9w, 9);
	REGISTER_CLASS_16_DECL(r10w, 10);
	REGISTER_CLASS_16_DECL(r11w, 11);
	REGISTER_CLASS_16_DECL(r12w, 12);
	REGISTER_CLASS_16_DECL(r13w, 13);
	REGISTER_CLASS_16_DECL(r14w, 14);
	REGISTER_CLASS_16_DECL(r15w, 15);

	// 8 bit gp registers
	REGISTER_CLASS_8_DECL(al, 0);
	REGISTER_CLASS_8_DECL(cl, 1);
	REGISTER_CLASS_8_DECL(dl, 2);
	REGISTER_CLASS_8_DECL(bl, 3);

	// when any the REX prefix is used, SPL, BPL, SIL and DIL are used, otherwise, without any REX
	// prefix AH, CH, DH and BH are used
	REGISTER_CLASS_8_DECL(spl, 0);
	REGISTER_CLASS_8_DECL(bpl, 1);
	REGISTER_CLASS_8_DECL(sil, 2);
	REGISTER_CLASS_8_DECL(dil, 3);

	REGISTER_CLASS_8_DECL(ah, 4);
	REGISTER_CLASS_8_DECL(ch, 5);
	REGISTER_CLASS_8_DECL(dh, 6);
	REGISTER_CLASS_8_DECL(bh, 7);
	REGISTER_CLASS_8_DECL(r8b, 8);
	REGISTER_CLASS_8_DECL(r9b, 9);
	REGISTER_CLASS_8_DECL(r10b, 10);
	REGISTER_CLASS_8_DECL(r11b, 11);
	REGISTER_CLASS_8_DECL(r12b, 12);
	REGISTER_CLASS_8_DECL(r13b, 13);
	REGISTER_CLASS_8_DECL(r14b, 14);
	REGISTER_CLASS_8_DECL(r15b, 15);

	inline auto is_gp_reg(reg r) {
		switch(r.type) {
			case REG_R8:
			case REG_R16:
			case REG_R32:
			case REG_R64: return true;
			default: return false;
		}
	}

	inline auto is_stack_pointer(reg r) -> bool {
		return r.index == rsp.index && is_gp_reg(r);
	}
} // namespace baremetal
