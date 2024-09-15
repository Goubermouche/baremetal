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

	struct reg_void : reg {
		constexpr reg_void() = default;
		constexpr explicit reg_void(u8 i, reg_type ty) : reg(i, ty) {}
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
	
	constexpr u8 rsp = 4;
	constexpr u8 fs = 4;

	constexpr u8 gs = 5;
	constexpr reg rip(0, REG_RIP);

	inline auto is_gp_reg(reg r) {
		switch(r.type) {
			case REG_R8:
			case REG_R16:
			case REG_R32:
			case REG_R64: return true;
			default: return false;
		}
	}

	inline auto is_sse_reg(reg r) {
		switch(r.type) {
			case REG_XMM:
			case REG_YMM:
			case REG_ZMM: return true;
			default: return false;
		}
	}

	inline auto is_stack_pointer(reg r) -> bool {
		return r.index == rsp && is_gp_reg(r);
	}
} // namespace baremetal
