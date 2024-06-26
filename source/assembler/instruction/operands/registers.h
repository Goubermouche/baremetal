#pragma once
#include <utility/types.h>

namespace baremetal {
	using namespace utility::types;

	enum reg_type : u8 {
		REG_GP_8,
		REG_GP_16,
		REG_GP_32,
		REG_GP_64,
		REG_XMM,
		REG_BND,
		REG_MMX,
		REG_SREG, // segment registers
		REG_DREG, // debug registers
		REG_CREG, // control registers

		// special registers
		REG_RIP
	};

	struct reg {
		constexpr reg() : index(0), type() {}
		constexpr explicit reg(u8 index, reg_type ty) : index(index), type(ty) {}
		u8 index;
		reg_type type;
	};

#define REGISTER_GP_DECL(bits)                                         \
  struct reg ## bits : reg {                                           \
    constexpr reg ## bits () = default;                                \
    constexpr explicit reg ## bits (u8 i) : reg(i, REG_GP_ ## bits) {} \
  };

	REGISTER_GP_DECL(8);
	REGISTER_GP_DECL(16);
	REGISTER_GP_DECL(32);
	REGISTER_GP_DECL(64);

	struct xmm : reg {
		constexpr xmm() = default;
		constexpr explicit xmm(u8 i) : reg(i, REG_XMM) {}
	};

	struct mmx : reg {
		constexpr mmx() = default;
		constexpr explicit mmx(u8 i) : reg(i, REG_MMX) {}
	};

	struct bnd : reg {
		constexpr bnd() = default;
		constexpr explicit bnd(u8 i) : reg(i, REG_BND) {}
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

#define REGISTER_CLASS_BND_DECL(name, index) \
  struct name : bnd {                        \
    constexpr name() : bnd(index) {}         \
  };                                         \
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

	// control registers
	REGISTER_CLASS_CREG_DECL(cr0, 0);
	REGISTER_CLASS_CREG_DECL(cr1, 1);
	REGISTER_CLASS_CREG_DECL(cr2, 2);
	REGISTER_CLASS_CREG_DECL(cr3, 3);
	REGISTER_CLASS_CREG_DECL(cr4, 4);
	REGISTER_CLASS_CREG_DECL(cr8, 8);

	// debug registers
	REGISTER_CLASS_DREG_DECL(dr0, 0);
	REGISTER_CLASS_DREG_DECL(dr1, 1);
	REGISTER_CLASS_DREG_DECL(dr2, 2);
	REGISTER_CLASS_DREG_DECL(dr3, 3);
	REGISTER_CLASS_DREG_DECL(dr4, 4);
	REGISTER_CLASS_DREG_DECL(dr5, 5);
	REGISTER_CLASS_DREG_DECL(dr6, 6);
	REGISTER_CLASS_DREG_DECL(dr7, 7);

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

	// 64 bit registers
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

	// 32 bit registers
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

	// 16 bit registers
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

	// 8 bit registers
	REGISTER_CLASS_8_DECL(al, 0);
	REGISTER_CLASS_8_DECL(cl, 1);
	REGISTER_CLASS_8_DECL(dl, 2);
	REGISTER_CLASS_8_DECL(bl, 3);
	REGISTER_CLASS_8_DECL(ah, 4);
	REGISTER_CLASS_8_DECL(ch, 5);
	REGISTER_CLASS_8_DECL(dh, 6);
	REGISTER_CLASS_8_DECL(bh, 7);

	// special registers
	REGISTER_CLASS_VOID_DECL(rip, 0, REG_RIP);

	inline auto is_stack_pointer(reg r) -> bool {
		// TODO: spl
		return r.index == rsp.index; // rsp, esp, sp
	}
} // namespace baremetal
