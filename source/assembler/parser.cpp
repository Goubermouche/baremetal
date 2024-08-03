#include "parser.h"
#include <utility/containers/map.h>

namespace baremetal {
	auto keyword_to_register(keyword_type kw) -> operand {
		switch(kw) {
			case KW_CR0: return operand(creg(0));
			case KW_CR1: return operand(creg(1));
			case KW_CR2: return operand(creg(2));
			case KW_CR3: return operand(creg(3));
			case KW_CR4: return operand(creg(4));
			case KW_CR8: return operand(creg(8));

			case KW_DR0: return operand(dreg(0));
			case KW_DR1: return operand(dreg(1));
			case KW_DR2: return operand(dreg(2));
			case KW_DR3: return operand(dreg(3));
			case KW_DR4: return operand(dreg(4));
			case KW_DR5: return operand(dreg(5));
			case KW_DR6: return operand(dreg(6));
			case KW_DR7: return operand(dreg(7));

			case KW_ES: return operand(sreg(0));
			case KW_CS: return operand(sreg(1));
			case KW_SS: return operand(sreg(2));
			case KW_DS: return operand(sreg(3));
			case KW_FS: return operand(sreg(4));
			case KW_GS: return operand(sreg(5));

			case KW_BND0: return operand(bnd(0));
			case KW_BND1: return operand(bnd(1));
			case KW_BND2: return operand(bnd(2));
			case KW_BND3: return operand(bnd(3));

			case KW_MM0: return operand(mmx(0));
			case KW_MM1: return operand(mmx(1));
			case KW_MM2: return operand(mmx(2));
			case KW_MM3: return operand(mmx(3));
			case KW_MM4: return operand(mmx(4));
			case KW_MM5: return operand(mmx(5));
			case KW_MM6: return operand(mmx(6));
			case KW_MM7: return operand(mmx(7));

			case KW_ZMM0: return operand(zmm(0, REG_ZMM_L));
			case KW_ZMM1: return operand(zmm(1, REG_ZMM_L));
			case KW_ZMM2: return operand(zmm(2, REG_ZMM_L));
			case KW_ZMM3: return operand(zmm(3, REG_ZMM_L));
			case KW_ZMM4: return operand(zmm(4, REG_ZMM_L));
			case KW_ZMM5: return operand(zmm(5, REG_ZMM_L));
			case KW_ZMM6: return operand(zmm(6, REG_ZMM_L));
			case KW_ZMM7: return operand(zmm(7, REG_ZMM_L));
			case KW_ZMM8: return operand(zmm(8, REG_ZMM_L));
			case KW_ZMM9: return operand(zmm(9, REG_ZMM_L));
			case KW_ZMM10: return operand(zmm(10, REG_ZMM_L));
			case KW_ZMM11: return operand(zmm(11, REG_ZMM_L));
			case KW_ZMM12: return operand(zmm(12, REG_ZMM_L));
			case KW_ZMM13: return operand(zmm(13, REG_ZMM_L));
			case KW_ZMM14: return operand(zmm(14, REG_ZMM_L));
			case KW_ZMM15: return operand(zmm(15, REG_ZMM_L));
			case KW_ZMM16: return operand(zmm(16, REG_ZMM_H));
			case KW_ZMM17: return operand(zmm(17, REG_ZMM_H));
			case KW_ZMM18: return operand(zmm(18, REG_ZMM_H));
			case KW_ZMM19: return operand(zmm(19, REG_ZMM_H));
			case KW_ZMM20: return operand(zmm(20, REG_ZMM_H));
			case KW_ZMM21: return operand(zmm(21, REG_ZMM_H));
			case KW_ZMM22: return operand(zmm(22, REG_ZMM_H));
			case KW_ZMM23: return operand(zmm(23, REG_ZMM_H));
			case KW_ZMM24: return operand(zmm(24, REG_ZMM_H));
			case KW_ZMM25: return operand(zmm(25, REG_ZMM_H));
			case KW_ZMM26: return operand(zmm(26, REG_ZMM_H));
			case KW_ZMM27: return operand(zmm(27, REG_ZMM_H));
			case KW_ZMM28: return operand(zmm(28, REG_ZMM_H));
			case KW_ZMM29: return operand(zmm(29, REG_ZMM_H));
			case KW_ZMM30: return operand(zmm(30, REG_ZMM_H));
			case KW_ZMM31: return operand(zmm(31, REG_ZMM_H));

			case KW_YMM0:  return operand(ymm(0));
			case KW_YMM1:  return operand(ymm(1));
			case KW_YMM2:  return operand(ymm(2));
			case KW_YMM3:  return operand(ymm(3));
			case KW_YMM4:  return operand(ymm(4));
			case KW_YMM5:  return operand(ymm(5));
			case KW_YMM6:  return operand(ymm(6));
			case KW_YMM7:  return operand(ymm(7));
			case KW_YMM8:  return operand(ymm(8));
			case KW_YMM9:  return operand(ymm(9));
			case KW_YMM10: return operand(ymm(10));
			case KW_YMM11: return operand(ymm(11));
			case KW_YMM12: return operand(ymm(12));
			case KW_YMM13: return operand(ymm(13));
			case KW_YMM14: return operand(ymm(14));
			case KW_YMM15: return operand(ymm(15));
			case KW_YMM16: return operand(ymm(16));
			case KW_YMM17: return operand(ymm(17));
			case KW_YMM18: return operand(ymm(18));
			case KW_YMM19: return operand(ymm(19));
			case KW_YMM20: return operand(ymm(20));
			case KW_YMM21: return operand(ymm(21));
			case KW_YMM22: return operand(ymm(22));
			case KW_YMM23: return operand(ymm(23));
			case KW_YMM24: return operand(ymm(24));
			case KW_YMM25: return operand(ymm(25));
			case KW_YMM26: return operand(ymm(26));
			case KW_YMM27: return operand(ymm(27));
			case KW_YMM28: return operand(ymm(28));
			case KW_YMM29: return operand(ymm(29));
			case KW_YMM30: return operand(ymm(30));
			case KW_YMM31: return operand(ymm(31));

			case KW_XMM0:  return operand(xmm(0));
			case KW_XMM1:  return operand(xmm(1));
			case KW_XMM2:  return operand(xmm(2));
			case KW_XMM3:  return operand(xmm(3));
			case KW_XMM4:  return operand(xmm(4));
			case KW_XMM5:  return operand(xmm(5));
			case KW_XMM6:  return operand(xmm(6));
			case KW_XMM7:  return operand(xmm(7));
			case KW_XMM8:  return operand(xmm(8));
			case KW_XMM9:  return operand(xmm(9));
			case KW_XMM10: return operand(xmm(10));
			case KW_XMM11: return operand(xmm(11));
			case KW_XMM12: return operand(xmm(12));
			case KW_XMM13: return operand(xmm(13));
			case KW_XMM14: return operand(xmm(14));
			case KW_XMM15: return operand(xmm(15));

			case KW_RAX: return operand(reg64(0));
			case KW_RCX: return operand(reg64(1));
			case KW_RDX: return operand(reg64(2));
			case KW_RBX: return operand(reg64(3));
			case KW_RSP: return operand(reg64(4));
			case KW_RBP: return operand(reg64(5));
			case KW_RSI: return operand(reg64(6));
			case KW_RDI: return operand(reg64(7));
			case KW_R8: return operand(reg64(8));
			case KW_R9: return operand(reg64(9));
			case KW_R10: return operand(reg64(10));
			case KW_R11: return operand(reg64(11));
			case KW_R12: return operand(reg64(12));
			case KW_R13: return operand(reg64(13));
			case KW_R14: return operand(reg64(14));
			case KW_R15: return operand(reg64(15));

			case KW_EAX: return operand(reg32(0));
			case KW_ECX: return operand(reg32(1));
			case KW_EDX: return operand(reg32(2));
			case KW_EBX: return operand(reg32(3));
			case KW_ESP: return operand(reg32(4));
			case KW_EBP: return operand(reg32(5));
			case KW_ESI: return operand(reg32(6));
			case KW_EDI: return operand(reg32(7));
			case KW_R8D: return operand(reg32(8));
			case KW_R9D: return operand(reg32(9));
			case KW_R10D: return operand(reg32(10));
			case KW_R11D: return operand(reg32(11));
			case KW_R12D: return operand(reg32(12));
			case KW_R13D: return operand(reg32(13));
			case KW_R14D: return operand(reg32(14));
			case KW_R15D: return operand(reg32(15));

			case KW_AX: return operand(reg16(0));
			case KW_CX: return operand(reg16(1));
			case KW_DX: return operand(reg16(2));
			case KW_BX: return operand(reg16(3));
			case KW_SP: return operand(reg16(4));
			case KW_BP: return operand(reg16(5));
			case KW_SI: return operand(reg16(6));
			case KW_DI: return operand(reg16(7));
			case KW_R8W: return operand(reg16(8));
			case KW_R9W: return operand(reg16(9));
			case KW_R10W: return operand(reg16(10));
			case KW_R11W: return operand(reg16(11));
			case KW_R12W: return operand(reg16(12));
			case KW_R13W: return operand(reg16(13));
			case KW_R14W: return operand(reg16(14));
			case KW_R15W: return operand(reg16(15));

			case KW_AL: return operand(reg8(0));
			case KW_CL: return operand(reg8(1));
			case KW_DL: return operand(reg8(2));
			case KW_BL: return operand(reg8(3));

			case KW_SPL: return operand(reg8(0));
			case KW_BPL: return operand(reg8(1));
			case KW_SIL: return operand(reg8(2));
			case KW_DIL: return operand(reg8(3));

			case KW_AH: return operand(reg16(4));
			case KW_CH: return operand(reg16(5));
			case KW_DH: return operand(reg16(6));
			case KW_BH: return operand(reg16(7));
			case KW_R8B: return operand(reg16(8));
			case KW_R9B: return operand(reg16(9));
			case KW_R10B: return operand(reg16(10));
			case KW_R11B: return operand(reg16(11));
			case KW_R12B: return operand(reg16(12));
			case KW_R13B: return operand(reg16(13));
			case KW_R14B: return operand(reg16(14));
			case KW_R15B: return operand(reg16(15));

			default: ASSERT(false, "invalid keyword: {}\n", (i32)kw);
		};

		return {};
	}

	auto get_keyword_type(const utility::dynamic_string& str) -> keyword_type {
		static utility::map<utility::dynamic_string, i32> operand_map = {
			// registers
			{ "cr0",   KW_CR0,   },
			{ "cr1",   KW_CR1,   },
			{ "cr2",   KW_CR2,   },
			{ "cr3",   KW_CR3,   },
			{ "cr4",   KW_CR4,   },
			{ "cr8",   KW_CR8,   },
			{ "dr0",   KW_DR0,   },
			{ "dr1",   KW_DR1,   },
			{ "dr2",   KW_DR2,   },
			{ "dr3",   KW_DR3,   },
			{ "dr4",   KW_DR4,   },
			{ "dr5",   KW_DR5,   },
			{ "dr6",   KW_DR6,   },
			{ "dr7",   KW_DR7,   },
			{ "es",    KW_ES,    },
			{ "cs",    KW_CS,    },
			{ "ss",    KW_SS,    },
			{ "ds",    KW_DS,    },
			{ "fs",    KW_FS,    },
			{ "gs",    KW_GS,    },
			{ "bnd0",  KW_BND0,  },
			{ "bnd1",  KW_BND1,  },
			{ "bnd2",  KW_BND2,  },
			{ "bnd3",  KW_BND3,  },
			{ "mm0",   KW_MM0,   },
			{ "mm1",   KW_MM1,   },
			{ "mm2",   KW_MM2,   },
			{ "mm3",   KW_MM3,   },
			{ "mm4",   KW_MM4,   },
			{ "mm5",   KW_MM5,   },
			{ "mm6",   KW_MM6,   },
			{ "mm7",   KW_MM7,   },
			{ "zmmi0", KW_ZMM0,  },
			{ "zmm1",  KW_ZMM1,  },
			{ "zmm2",  KW_ZMM2,  },
			{ "zmm3",  KW_ZMM3,  },
			{ "zmm4",  KW_ZMM4,  },
			{ "zmm5",  KW_ZMM5,  },
			{ "zmm6",  KW_ZMM6,  },
			{ "zmm7",  KW_ZMM7,  },
			{ "zmm8",  KW_ZMM8,  },
			{ "zmm9",  KW_ZMM9,  },
			{ "zmm10", KW_ZMM10, },
			{ "zmm11", KW_ZMM11, },
			{ "zmm12", KW_ZMM12, },
			{ "zmm13", KW_ZMM13, },
			{ "zmm14", KW_ZMM14, },
			{ "zmm15", KW_ZMM15, },
			{ "zmm16", KW_ZMM16, },
			{ "zmm17", KW_ZMM17, },
			{ "zmm18", KW_ZMM18, },
			{ "zmm19", KW_ZMM19, },
			{ "zmm20", KW_ZMM20, },
			{ "zmm21", KW_ZMM21, },
			{ "zmm22", KW_ZMM22, },
			{ "zmm23", KW_ZMM23, },
			{ "zmm24", KW_ZMM24, },
			{ "zmm25", KW_ZMM25, },
			{ "zmm26", KW_ZMM26, },
			{ "zmm27", KW_ZMM27, },
			{ "zmm28", KW_ZMM28, },
			{ "zmm29", KW_ZMM29, },
			{ "zmm30", KW_ZMM30, },
			{ "zmm31", KW_ZMM31, },
			{ "ymm0",  KW_YMM0,  },
			{ "ymm1",  KW_YMM1,  },
			{ "ymm2",  KW_YMM2,  },
			{ "ymm3",  KW_YMM3,  },
			{ "ymm4",  KW_YMM4,  },
			{ "ymm5",  KW_YMM5,  },
			{ "ymm6",  KW_YMM6,  },
			{ "ymm7",  KW_YMM7,  },
			{ "ymm8",  KW_YMM8,  },
			{ "ymm9",  KW_YMM9,  },
			{ "ymm10", KW_YMM10, },
			{ "ymm11", KW_YMM11, },
			{ "ymm12", KW_YMM12, },
			{ "ymm13", KW_YMM13, },
			{ "ymm14", KW_YMM14, },
			{ "ymm15", KW_YMM15, },
			{ "ymm16", KW_YMM16, },
			{ "ymm17", KW_YMM17, },
			{ "ymm18", KW_YMM18, },
			{ "ymm19", KW_YMM19, },
			{ "ymm20", KW_YMM20, },
			{ "ymm21", KW_YMM21, },
			{ "ymm22", KW_YMM22, },
			{ "ymm23", KW_YMM23, },
			{ "ymm24", KW_YMM24, },
			{ "ymm25", KW_YMM25, },
			{ "ymm26", KW_YMM26, },
			{ "ymm27", KW_YMM27, },
			{ "ymm28", KW_YMM28, },
			{ "ymm29", KW_YMM29, },
			{ "ymm30", KW_YMM30, },
			{ "ymm31", KW_YMM31, },
			{ "xmm0",  KW_XMM0,  },
			{ "xmm1",  KW_XMM1,  },
			{ "xmm2",  KW_XMM2,  },
			{ "xmm3",  KW_XMM3,  },
			{ "xmm4",  KW_XMM4,  },
			{ "xmm5",  KW_XMM5,  },
			{ "xmm6",  KW_XMM6,  },
			{ "xmm7",  KW_XMM7,  },
			{ "xmm8",  KW_XMM8,  },
			{ "xmm9",  KW_XMM9,  },
			{ "xmm10", KW_XMM10, },
			{ "xmm11", KW_XMM11, },
			{ "xmm12", KW_XMM12, },
			{ "xmm13", KW_XMM13, },
			{ "xmm14", KW_XMM14, },
			{ "xmm15", KW_XMM15, },
			{ "rax",   KW_RAX,   },
			{ "rcx",   KW_RCX,   },
			{ "rdx",   KW_RDX,   },
			{ "rbx",   KW_RBX,   },
			{ "rsp",   KW_RSP,   },
			{ "rbp",   KW_RBP,   },
			{ "rsi",   KW_RSI,   },
			{ "rdi",   KW_RDI,   },
			{ "r8",    KW_R8,    },
			{ "r9",    KW_R9,    },
			{ "r10",   KW_R10,   },
			{ "r11",   KW_R11,   },
			{ "r12",   KW_R12,   },
			{ "13",    KW_R13,   },
			{ "14",    KW_R14,   },
			{ "r15",   KW_R15,   },
			{ "eax",   KW_EAX,   },
			{ "ecx",   KW_ECX,   },
			{ "edx",   KW_EDX,   },
			{ "ebx",   KW_EBX,   },
			{ "esp",   KW_ESP,   },
			{ "ebp",   KW_EBP,   },
			{ "esi",   KW_ESI,   },
			{ "edi",   KW_EDI,   },
			{ "r8d",   KW_R8D,   },
			{ "r9d",   KW_R9D,   },
			{ "r10d",  KW_R10D,  },
			{ "r11d",  KW_R11D,  },
			{ "r12d",  KW_R12D,  },
			{ "r13d",  KW_R13D,  },
			{ "r14d",  KW_R14D,  },
			{ "r15d",  KW_R15D,  },
			{ "ax",    KW_AX,    },
			{ "cx",    KW_CX,    },
			{ "dx",    KW_DX,    },
			{ "bx",    KW_BX,    },
			{ "sp",    KW_SP,    },
			{ "bp",    KW_BP,    },
			{ "si",    KW_SI,    },
			{ "di",    KW_DI,    },
			{ "r8w",   KW_R8W,   },
			{ "r9w",   KW_R9W,   },
			{ "r10w",  KW_R10W,  },
			{ "r11w",  KW_R11W,  },
			{ "r12w",  KW_R12W,  },
			{ "r13w",  KW_R13W,  },
			{ "r14w",  KW_R14W,  },
			{ "r15w",  KW_R15W,  },
			{ "al",    KW_AL,    },
			{ "cl",    KW_CL,    },
			{ "dl",    KW_DL,    },
			{ "bl",    KW_BL,    },
			{ "spl",   KW_SPL,   },
			{ "bpl",   KW_BPL,   },
			{ "sil",   KW_SIL,   },
			{ "dil",   KW_DIL,   },
			{ "ah",    KW_AH,    },
			{ "ch",    KW_CH,    },
			{ "dh",    KW_DH,    },
			{ "bh",    KW_BH,    },
			{ "r8b",   KW_R8B,   },
			{ "r9b",   KW_R9B,   },
			{ "r10b",  KW_R10B,  },
			{ "r11b",  KW_R11B,  },
			{ "r12b",  KW_R12B,  },
			{ "r13b",  KW_R13B,  },
			{ "r14b",  KW_R14B,  },
			{ "r15b",  KW_R15B   },
		};
		
		const auto it = operand_map.find(str);

		if(it == operand_map.end()) {
			return (keyword_type)0;
		}

		return (keyword_type)it->second;
	}

	auto parse_operand(const utility::dynamic_string& str) -> operand {
		operand result;

		auto op = get_keyword_type(str);

		utility::console::print("parsing op '{}' : '{}'\n", str, (int)op);
		return result;
	}
} // namespace baremetal

