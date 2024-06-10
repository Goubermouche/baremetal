#pragma once
#include <utility/types.h>

namespace baremetal {
	using namespace utility::types;

	enum reg_type : u8 {
		REG_I8,
		REG_I16,
		REG_I32,
		REG_I64,
		REG_RIP
	};

	struct reg {
		constexpr reg() : index(0) {}
		constexpr explicit reg(u8 index, reg_type ty) : index(index), type(ty) {}
		u8 index;
		reg_type type;
	};

	struct reg8 : reg {
		constexpr explicit reg8(u8 i) : reg(i, REG_I8) {}
	};

	struct reg16 : reg {
		constexpr explicit reg16(u8 i) : reg(i, REG_I16) {}
	};

	struct reg32 : reg {
		constexpr explicit reg32(u8 i) : reg(i, REG_I32) {}
	};

	struct reg64 : reg {
		constexpr explicit reg64(u8 i) : reg(i, REG_I64) {}
	};

	struct reg_void : reg {
		constexpr explicit reg_void(u8 i, reg_type ty) : reg(i, ty) {}
	};

#define REGISTER_CLASS_64_DECL(name, index) \
  struct name : reg64 {                     \
    constexpr name() : reg64(index) {}      \
  };

#define REGISTER_CLASS_32_DECL(name, index) \
  struct name : reg32 {                     \
    constexpr name() : reg32(index) {}      \
  };

#define REGISTER_CLASS_16_DECL(name, index) \
  struct name : reg16 {                     \
    constexpr name() : reg16(index) {}      \
  };

#define REGISTER_CLASS_8_DECL(name, index) \
  struct name : reg8 {                     \
    constexpr name() : reg8(index) {}      \
  };

#define REGISTER_CLASS_VOID_DECL(name, index, type) \
  struct name : reg_void {                          \
    constexpr name() : reg_void(index, type) {}     \
  };

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

	REGISTER_CLASS_8_DECL(al, 0);
	REGISTER_CLASS_8_DECL(cl, 1);
	REGISTER_CLASS_8_DECL(dl, 2);
	REGISTER_CLASS_8_DECL(bl, 3);
	REGISTER_CLASS_8_DECL(ah, 4);
	REGISTER_CLASS_8_DECL(ch, 5);
	REGISTER_CLASS_8_DECL(dh, 6);
	REGISTER_CLASS_8_DECL(bh, 7);

	REGISTER_CLASS_VOID_DECL(rip, 0, REG_RIP);


} // namespace baremetal
