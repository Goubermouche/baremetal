#include "parser.h"
#include "utility/types.h"
#include <utility/containers/map.h>

namespace baremetal {
	void lexer::set_text(const utility::dynamic_string& text) {
		m_index = 0;
		m_text = utility::dynamic_string(text);
		get_next_char();
	}

	auto lexer::get_next_char() -> char {
		if(m_index + 1 >= m_text.get_size()) {
			m_current_char = utility::g_eof;
			return utility::g_eof;
		}

		m_current_char = m_text[m_index++];
		return m_current_char;
	}

	auto lexer::get_next_token() -> keyword_type {
		current_string.clear();

		// consume spaces
		while(utility::is_space(m_current_char)) { get_next_char(); }

		// numbers
		if(utility::is_digit(m_current_char) && force_keyword == false) {
			i32 base = 10;

			if(m_current_char == '0') {
				get_next_char();

				// hex
				if(m_current_char == 'x') {
					base = 16;
					get_next_char();

					while(utility::is_digit_hex(m_current_char)) {
						current_string += m_current_char;
						get_next_char();
					}

					goto parse_number;
				}
				else if(m_current_char == 'b') {
					base = 2;
					get_next_char();

					while(utility::is_digit_hex(m_current_char)) {
						current_string += m_current_char;
						get_next_char();
					}

					goto parse_number;
				}
			}

			while(utility::is_digit(m_current_char)) {
				current_string += m_current_char;
				get_next_char();
			}

parse_number:
			char* end;
			u64 num = strtoull(current_string.get_data(), &end, base);
			current_immediate = imm(num);
			return current = KW_NUMBER;
		}

		// keyword or identifier
		if(utility::is_alpha(m_current_char) || (force_keyword && utility::is_digit(m_current_char))) {
			while(utility::is_alphanum(m_current_char)) {
				current_string += m_current_char;
				get_next_char();
			}

			const auto kw = get_keyword_type(current_string);
			force_keyword = false;
		
			if(kw != KW_NONE) {
				return current = kw;
			}

			return current = KW_IDENTIFIER;
		}

		// special characters
		switch(m_current_char) {
			case ',': get_next_char(); return current = KW_COMMA;
			case '[': get_next_char(); return current = KW_LBRACKET;
			case ']': get_next_char(); return current = KW_RBRACKET;
			case '{': get_next_char(); return current = KW_LBRACE;
			case '}': get_next_char(); return current = KW_RBRACE;
			case '+': get_next_char(); return current = KW_PLUS;
			case '-': get_next_char(); return current = KW_MINUS;
			case '*': get_next_char(); return current = KW_ASTERISK;
			case '$': get_next_char(); return current = KW_DOLLARSIGN;
			case '\n': get_next_char(); return current = KW_NEWLINE;
			case utility::g_eof: return current = KW_EOF;
		}

		ASSERT(false, "unknown character: '{}'\n", (i32)m_current_char);
		return {};
	}

	auto keyword_to_register(keyword_type kw) -> reg {
		switch(kw) {
			case KW_CR0: return creg(0);
			case KW_CR1: return creg(1);
			case KW_CR2: return creg(2);
			case KW_CR3: return creg(3);
			case KW_CR4: return creg(4);
			case KW_CR8: return creg(8);

			case KW_DR0: return dreg(0);
			case KW_DR1: return dreg(1);
			case KW_DR2: return dreg(2);
			case KW_DR3: return dreg(3);
			case KW_DR4: return dreg(4);
			case KW_DR5: return dreg(5);
			case KW_DR6: return dreg(6);
			case KW_DR7: return dreg(7);

			case KW_K1: return kreg(1);
			case KW_K2: return kreg(2);
			case KW_K3: return kreg(3);
			case KW_K4: return kreg(4);
			case KW_K5: return kreg(5);
			case KW_K6: return kreg(6);
			case KW_K7: return kreg(7);

			case KW_ES: return sreg(0);
			case KW_CS: return sreg(1);
			case KW_SS: return sreg(2);
			case KW_DS: return sreg(3);
			case KW_FS: return sreg(4);
			case KW_GS: return sreg(5);

			case KW_BND0: return (bnd(0));
			case KW_BND1: return (bnd(1));
			case KW_BND2: return (bnd(2));
			case KW_BND3: return (bnd(3));

			case KW_ST0: return (st(0));
			case KW_ST1: return (st(1));
			case KW_ST2: return (st(2));
			case KW_ST3: return (st(3));
			case KW_ST4: return (st(4));
			case KW_ST5: return (st(5));
			case KW_ST6: return (st(6));
			case KW_ST7: return (st(7));

			case KW_TMM0: return (tmm(0));
			case KW_TMM1: return (tmm(1));
			case KW_TMM2: return (tmm(2));
			case KW_TMM3: return (tmm(3));
			case KW_TMM4: return (tmm(4));
			case KW_TMM5: return (tmm(5));
			case KW_TMM6: return (tmm(6));
			case KW_TMM7: return (tmm(7));

			case KW_MM0: return mmx(0);
			case KW_MM1: return mmx(1);
			case KW_MM2: return mmx(2);
			case KW_MM3: return mmx(3);
			case KW_MM4: return mmx(4);
			case KW_MM5: return mmx(5);
			case KW_MM6: return mmx(6);
			case KW_MM7: return mmx(7);

			case KW_ZMM0: return zmm(0, REG_ZMM);
			case KW_ZMM1: return zmm(1, REG_ZMM);
			case KW_ZMM2: return zmm(2, REG_ZMM);
			case KW_ZMM3: return zmm(3, REG_ZMM);
			case KW_ZMM4: return zmm(4, REG_ZMM);
			case KW_ZMM5: return zmm(5, REG_ZMM);
			case KW_ZMM6: return zmm(6, REG_ZMM);
			case KW_ZMM7: return zmm(7, REG_ZMM);
			case KW_ZMM8: return zmm(8, REG_ZMM);
			case KW_ZMM9: return zmm(9, REG_ZMM);
			case KW_ZMM10: return zmm(10, REG_ZMM);
			case KW_ZMM11: return zmm(11, REG_ZMM);
			case KW_ZMM12: return zmm(12, REG_ZMM);
			case KW_ZMM13: return zmm(13, REG_ZMM);
			case KW_ZMM14: return zmm(14, REG_ZMM);
			case KW_ZMM15: return zmm(15, REG_ZMM);
			case KW_ZMM16: return zmm(16, REG_ZMM);
			case KW_ZMM17: return zmm(17, REG_ZMM);
			case KW_ZMM18: return zmm(18, REG_ZMM);
			case KW_ZMM19: return zmm(19, REG_ZMM);
			case KW_ZMM20: return zmm(20, REG_ZMM);
			case KW_ZMM21: return zmm(21, REG_ZMM);
			case KW_ZMM22: return zmm(22, REG_ZMM);
			case KW_ZMM23: return zmm(23, REG_ZMM);
			case KW_ZMM24: return zmm(24, REG_ZMM);
			case KW_ZMM25: return zmm(25, REG_ZMM);
			case KW_ZMM26: return zmm(26, REG_ZMM);
			case KW_ZMM27: return zmm(27, REG_ZMM);
			case KW_ZMM28: return zmm(28, REG_ZMM);
			case KW_ZMM29: return zmm(29, REG_ZMM);
			case KW_ZMM30: return zmm(30, REG_ZMM);
			case KW_ZMM31: return zmm(31, REG_ZMM);

			case KW_YMM0:  return ymm(0);
			case KW_YMM1:  return ymm(1);
			case KW_YMM2:  return ymm(2);
			case KW_YMM3:  return ymm(3);
			case KW_YMM4:  return ymm(4);
			case KW_YMM5:  return ymm(5);
			case KW_YMM6:  return ymm(6);
			case KW_YMM7:  return ymm(7);
			case KW_YMM8:  return ymm(8);
			case KW_YMM9:  return ymm(9);
			case KW_YMM10: return ymm(10);
			case KW_YMM11: return ymm(11);
			case KW_YMM12: return ymm(12);
			case KW_YMM13: return ymm(13);
			case KW_YMM14: return ymm(14);
			case KW_YMM15: return ymm(15);
			case KW_YMM16: return ymm(16);
			case KW_YMM17: return ymm(17);
			case KW_YMM18: return ymm(18);
			case KW_YMM19: return ymm(19);
			case KW_YMM20: return ymm(20);
			case KW_YMM21: return ymm(21);
			case KW_YMM22: return ymm(22);
			case KW_YMM23: return ymm(23);
			case KW_YMM24: return ymm(24);
			case KW_YMM25: return ymm(25);
			case KW_YMM26: return ymm(26);
			case KW_YMM27: return ymm(27);
			case KW_YMM28: return ymm(28);
			case KW_YMM29: return ymm(29);
			case KW_YMM30: return ymm(30);
			case KW_YMM31: return ymm(31);

			case KW_XMM0:  return xmm(0);
			case KW_XMM1:  return xmm(1);
			case KW_XMM2:  return xmm(2);
			case KW_XMM3:  return xmm(3);
			case KW_XMM4:  return xmm(4);
			case KW_XMM5:  return xmm(5);
			case KW_XMM6:  return xmm(6);
			case KW_XMM7:  return xmm(7);
			case KW_XMM8:  return xmm(8);
			case KW_XMM9:  return xmm(9);
			case KW_XMM10: return xmm(10);
			case KW_XMM11: return xmm(11);
			case KW_XMM12: return xmm(12);
			case KW_XMM13: return xmm(13);
			case KW_XMM14: return xmm(14);
			case KW_XMM15: return xmm(15);

			case KW_RAX: return reg64(0);
			case KW_RCX: return reg64(1);
			case KW_RDX: return reg64(2);
			case KW_RBX: return reg64(3);
			case KW_RSP: return reg64(4);
			case KW_RBP: return reg64(5);
			case KW_RSI: return reg64(6);
			case KW_RDI: return reg64(7);
			case KW_R8:  return reg64(8);
			case KW_R9:  return reg64(9);
			case KW_R10: return reg64(10);
			case KW_R11: return reg64(11);
			case KW_R12: return reg64(12);
			case KW_R13: return reg64(13);
			case KW_R14: return reg64(14);
			case KW_R15: return reg64(15);

			case KW_EAX:  return reg32(0);
			case KW_ECX:  return reg32(1);
			case KW_EDX:  return reg32(2);
			case KW_EBX:  return reg32(3);
			case KW_ESP:  return reg32(4);
			case KW_EBP:  return reg32(5);
			case KW_ESI:  return reg32(6);
			case KW_EDI:  return reg32(7);
			case KW_R8D:  return reg32(8);
			case KW_R9D:  return reg32(9);
			case KW_R10D: return reg32(10);
			case KW_R11D: return reg32(11);
			case KW_R12D: return reg32(12);
			case KW_R13D: return reg32(13);
			case KW_R14D: return reg32(14);
			case KW_R15D: return reg32(15);

			case KW_AX:   return reg16(0);
			case KW_CX:   return reg16(1);
			case KW_DX:   return reg16(2);
			case KW_BX:   return reg16(3);
			case KW_SP:   return reg16(4);
			case KW_BP:   return reg16(5);
			case KW_SI:   return reg16(6);
			case KW_DI:   return reg16(7);
			case KW_R8W:  return reg16(8);
			case KW_R9W:  return reg16(9);
			case KW_R10W: return reg16(10);
			case KW_R11W: return reg16(11);
			case KW_R12W: return reg16(12);
			case KW_R13W: return reg16(13);
			case KW_R14W: return reg16(14);
			case KW_R15W: return reg16(15);

			case KW_AL: return reg8(0);
			case KW_CL: return reg8(1);
			case KW_DL: return reg8(2);
			case KW_BL: return reg8(3);

			case KW_SPL: return reg8(0);
			case KW_BPL: return reg8(1);
			case KW_SIL: return reg8(2);
			case KW_DIL: return reg8(3);

			case KW_AH:   return reg16(4);
			case KW_CH:   return reg16(5);
			case KW_DH:   return reg16(6);
			case KW_BH:   return reg16(7);
			case KW_R8B:  return reg16(8);
			case KW_R9B:  return reg16(9);
			case KW_R10B: return reg16(10);
			case KW_R11B: return reg16(11);
			case KW_R12B: return reg16(12);
			case KW_R13B: return reg16(13);
			case KW_R14B: return reg16(14);
			case KW_R15B: return reg16(15);

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
			{ "k1",    KW_K1,    },
			{ "k2",    KW_K2,    },
			{ "k3",    KW_K3,    },
			{ "k4",    KW_K4,    },
			{ "k5",    KW_K5,    },
			{ "k6",    KW_K6,    },
			{ "k7",    KW_K7,    },
			{ "es",    KW_ES,    },
			{ "cs",    KW_CS,    },
			{ "ss",    KW_SS,    },
			{ "ds",    KW_DS,    },
			{ "fs",    KW_FS,    },
			{ "gs",    KW_GS,    },
			{ "st0",   KW_ST0,   },
			{ "st1",   KW_ST1,   },
			{ "st2",   KW_ST2,   },
			{ "st3",   KW_ST3,   },
			{ "st4",   KW_ST4,   },
			{ "st5",   KW_ST5,   },
			{ "st6",   KW_ST6,   },
			{ "st7",   KW_ST7,   },
			{ "bnd0",  KW_BND0,  },
			{ "bnd1",  KW_BND1,  },
			{ "bnd2",  KW_BND2,  },
			{ "bnd3",  KW_BND3,  },
			{ "tmm0",  KW_TMM0,  },
			{ "tmm1",  KW_TMM1,  },
			{ "tmm2",  KW_TMM2,  },
			{ "tmm3",  KW_TMM3,  },
			{ "tmm4",  KW_TMM4,  },
			{ "tmm5",  KW_TMM5,  },
			{ "tmm6",  KW_TMM6,  },
			{ "tmm7",  KW_TMM7,  },
			{ "mm0",   KW_MM0,   },
			{ "mm1",   KW_MM1,   },
			{ "mm2",   KW_MM2,   },
			{ "mm3",   KW_MM3,   },
			{ "mm4",   KW_MM4,   },
			{ "mm5",   KW_MM5,   },
			{ "mm6",   KW_MM6,   },
			{ "mm7",   KW_MM7,   },
			{ "zmm0",  KW_ZMM0,  },
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
			{ "r13",    KW_R13,   },
			{ "r14",    KW_R14,   },
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
			
			// types
			{ "byte" , KW_BYTE  },
			{ "word" , KW_WORD  },
			{ "dword", KW_DWORD },
			{ "qword", KW_QWORD },
			{ "tword", KW_TWORD },
			{ "QWORD", KW_QWORD },

			{ "1to2",  KW_1TO2  },
			{ "1to4",  KW_1TO4  },
			{ "1to8",  KW_1TO8  },
			{ "1to16", KW_1TO16 },
			{ "1to32", KW_1TO32 },

			// keywords
			{ "rel"  , KW_REL   },
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

