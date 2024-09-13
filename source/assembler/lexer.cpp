#include "lexer.h"

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

	auto lexer::get_next_token() -> token_type {
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
			return current = TOK_NUMBER;
		}

		// keyword or identifier
		if(utility::is_alpha(m_current_char) || (force_keyword && utility::is_digit(m_current_char))) {
			while(utility::is_alphanum(m_current_char)) {
				current_string += m_current_char;
				get_next_char();
			}

			const auto token = string_to_token(current_string);
			force_keyword = false;
		
			if(token != TOK_NONE) {
				return current = token;
			}

			return current = TOK_IDENTIFIER;
		}

		// special characters
		switch(m_current_char) {
			case ',': get_next_char();  return current = TOK_COMMA;
			case '[': get_next_char();  return current = TOK_LBRACKET;
			case ']': get_next_char();  return current = TOK_RBRACKET;
			case '{': get_next_char();  return current = TOK_LBRACE;
			case '}': get_next_char();  return current = TOK_RBRACE;
			case '+': get_next_char();  return current = TOK_PLUS;
			case '-': get_next_char();  return current = TOK_MINUS;
			case '*': get_next_char();  return current = TOK_ASTERISK;
			case '$': get_next_char();  return current = TOK_DOLLARSIGN;
			case '\n': get_next_char(); return current = TOK_NEWLINE;
			case utility::g_eof:        return current = TOK_EOF;
		}

		ASSERT(false, "unknown character: '{}'\n", (i32)m_current_char);
		return {};
	}

	auto token_to_register(token_type token) -> reg {
		switch(token) {
			case TOK_CR0: return creg(0);
			case TOK_CR1: return creg(1);
			case TOK_CR2: return creg(2);
			case TOK_CR3: return creg(3);
			case TOK_CR4: return creg(4);
			case TOK_CR8: return creg(8);

			case TOK_DR0: return dreg(0);
			case TOK_DR1: return dreg(1);
			case TOK_DR2: return dreg(2);
			case TOK_DR3: return dreg(3);
			case TOK_DR4: return dreg(4);
			case TOK_DR5: return dreg(5);
			case TOK_DR6: return dreg(6);
			case TOK_DR7: return dreg(7);

			case TOK_K1: return kreg(1);
			case TOK_K2: return kreg(2);
			case TOK_K3: return kreg(3);
			case TOK_K4: return kreg(4);
			case TOK_K5: return kreg(5);
			case TOK_K6: return kreg(6);
			case TOK_K7: return kreg(7);

			case TOK_ES: return sreg(0);
			case TOK_CS: return sreg(1);
			case TOK_SS: return sreg(2);
			case TOK_DS: return sreg(3);
			case TOK_FS: return sreg(4);
			case TOK_GS: return sreg(5);

			case TOK_BND0: return (bnd(0));
			case TOK_BND1: return (bnd(1));
			case TOK_BND2: return (bnd(2));
			case TOK_BND3: return (bnd(3));

			case TOK_ST0: return (st(0));
			case TOK_ST1: return (st(1));
			case TOK_ST2: return (st(2));
			case TOK_ST3: return (st(3));
			case TOK_ST4: return (st(4));
			case TOK_ST5: return (st(5));
			case TOK_ST6: return (st(6));
			case TOK_ST7: return (st(7));

			case TOK_TMM0: return (tmm(0));
			case TOK_TMM1: return (tmm(1));
			case TOK_TMM2: return (tmm(2));
			case TOK_TMM3: return (tmm(3));
			case TOK_TMM4: return (tmm(4));
			case TOK_TMM5: return (tmm(5));
			case TOK_TMM6: return (tmm(6));
			case TOK_TMM7: return (tmm(7));

			case TOK_MM0: return mmx(0);
			case TOK_MM1: return mmx(1);
			case TOK_MM2: return mmx(2);
			case TOK_MM3: return mmx(3);
			case TOK_MM4: return mmx(4);
			case TOK_MM5: return mmx(5);
			case TOK_MM6: return mmx(6);
			case TOK_MM7: return mmx(7);

			case TOK_ZMM0: return zmm(0, REG_ZMM);
			case TOK_ZMM1: return zmm(1, REG_ZMM);
			case TOK_ZMM2: return zmm(2, REG_ZMM);
			case TOK_ZMM3: return zmm(3, REG_ZMM);
			case TOK_ZMM4: return zmm(4, REG_ZMM);
			case TOK_ZMM5: return zmm(5, REG_ZMM);
			case TOK_ZMM6: return zmm(6, REG_ZMM);
			case TOK_ZMM7: return zmm(7, REG_ZMM);
			case TOK_ZMM8: return zmm(8, REG_ZMM);
			case TOK_ZMM9: return zmm(9, REG_ZMM);
			case TOK_ZMM10: return zmm(10, REG_ZMM);
			case TOK_ZMM11: return zmm(11, REG_ZMM);
			case TOK_ZMM12: return zmm(12, REG_ZMM);
			case TOK_ZMM13: return zmm(13, REG_ZMM);
			case TOK_ZMM14: return zmm(14, REG_ZMM);
			case TOK_ZMM15: return zmm(15, REG_ZMM);
			case TOK_ZMM16: return zmm(16, REG_ZMM);
			case TOK_ZMM17: return zmm(17, REG_ZMM);
			case TOK_ZMM18: return zmm(18, REG_ZMM);
			case TOK_ZMM19: return zmm(19, REG_ZMM);
			case TOK_ZMM20: return zmm(20, REG_ZMM);
			case TOK_ZMM21: return zmm(21, REG_ZMM);
			case TOK_ZMM22: return zmm(22, REG_ZMM);
			case TOK_ZMM23: return zmm(23, REG_ZMM);
			case TOK_ZMM24: return zmm(24, REG_ZMM);
			case TOK_ZMM25: return zmm(25, REG_ZMM);
			case TOK_ZMM26: return zmm(26, REG_ZMM);
			case TOK_ZMM27: return zmm(27, REG_ZMM);
			case TOK_ZMM28: return zmm(28, REG_ZMM);
			case TOK_ZMM29: return zmm(29, REG_ZMM);
			case TOK_ZMM30: return zmm(30, REG_ZMM);
			case TOK_ZMM31: return zmm(31, REG_ZMM);

			case TOK_YMM0:  return ymm(0);
			case TOK_YMM1:  return ymm(1);
			case TOK_YMM2:  return ymm(2);
			case TOK_YMM3:  return ymm(3);
			case TOK_YMM4:  return ymm(4);
			case TOK_YMM5:  return ymm(5);
			case TOK_YMM6:  return ymm(6);
			case TOK_YMM7:  return ymm(7);
			case TOK_YMM8:  return ymm(8);
			case TOK_YMM9:  return ymm(9);
			case TOK_YMM10: return ymm(10);
			case TOK_YMM11: return ymm(11);
			case TOK_YMM12: return ymm(12);
			case TOK_YMM13: return ymm(13);
			case TOK_YMM14: return ymm(14);
			case TOK_YMM15: return ymm(15);
			case TOK_YMM16: return ymm(16);
			case TOK_YMM17: return ymm(17);
			case TOK_YMM18: return ymm(18);
			case TOK_YMM19: return ymm(19);
			case TOK_YMM20: return ymm(20);
			case TOK_YMM21: return ymm(21);
			case TOK_YMM22: return ymm(22);
			case TOK_YMM23: return ymm(23);
			case TOK_YMM24: return ymm(24);
			case TOK_YMM25: return ymm(25);
			case TOK_YMM26: return ymm(26);
			case TOK_YMM27: return ymm(27);
			case TOK_YMM28: return ymm(28);
			case TOK_YMM29: return ymm(29);
			case TOK_YMM30: return ymm(30);
			case TOK_YMM31: return ymm(31);

			case TOK_XMM0:  return xmm(0);
			case TOK_XMM1:  return xmm(1);
			case TOK_XMM2:  return xmm(2);
			case TOK_XMM3:  return xmm(3);
			case TOK_XMM4:  return xmm(4);
			case TOK_XMM5:  return xmm(5);
			case TOK_XMM6:  return xmm(6);
			case TOK_XMM7:  return xmm(7);
			case TOK_XMM8:  return xmm(8);
			case TOK_XMM9:  return xmm(9);
			case TOK_XMM10: return xmm(10);
			case TOK_XMM11: return xmm(11);
			case TOK_XMM12: return xmm(12);
			case TOK_XMM13: return xmm(13);
			case TOK_XMM14: return xmm(14);
			case TOK_XMM15: return xmm(15);
			case TOK_XMM16: return xmm(16);
			case TOK_XMM17: return xmm(17);
			case TOK_XMM18: return xmm(18);
			case TOK_XMM19: return xmm(19);
			case TOK_XMM20: return xmm(20);
			case TOK_XMM21: return xmm(21);
			case TOK_XMM22: return xmm(22);
			case TOK_XMM23: return xmm(23);
			case TOK_XMM24: return xmm(24);
			case TOK_XMM25: return xmm(25);
			case TOK_XMM26: return xmm(26);
			case TOK_XMM27: return xmm(27);
			case TOK_XMM28: return xmm(28);
			case TOK_XMM29: return xmm(29);
			case TOK_XMM30: return xmm(30);
			case TOK_XMM31: return xmm(31);

			case TOK_RAX: return reg64(0);
			case TOK_RCX: return reg64(1);
			case TOK_RDX: return reg64(2);
			case TOK_RBX: return reg64(3);
			case TOK_RSP: return reg64(4);
			case TOK_RBP: return reg64(5);
			case TOK_RSI: return reg64(6);
			case TOK_RDI: return reg64(7);
			case TOK_R8:  return reg64(8);
			case TOK_R9:  return reg64(9);
			case TOK_R10: return reg64(10);
			case TOK_R11: return reg64(11);
			case TOK_R12: return reg64(12);
			case TOK_R13: return reg64(13);
			case TOK_R14: return reg64(14);
			case TOK_R15: return reg64(15);

			case TOK_EAX:  return reg32(0);
			case TOK_ECX:  return reg32(1);
			case TOK_EDX:  return reg32(2);
			case TOK_EBX:  return reg32(3);
			case TOK_ESP:  return reg32(4);
			case TOK_EBP:  return reg32(5);
			case TOK_ESI:  return reg32(6);
			case TOK_EDI:  return reg32(7);
			case TOK_R8D:  return reg32(8);
			case TOK_R9D:  return reg32(9);
			case TOK_R10D: return reg32(10);
			case TOK_R11D: return reg32(11);
			case TOK_R12D: return reg32(12);
			case TOK_R13D: return reg32(13);
			case TOK_R14D: return reg32(14);
			case TOK_R15D: return reg32(15);

			case TOK_AX:   return reg16(0);
			case TOK_CX:   return reg16(1);
			case TOK_DX:   return reg16(2);
			case TOK_BX:   return reg16(3);
			case TOK_SP:   return reg16(4);
			case TOK_BP:   return reg16(5);
			case TOK_SI:   return reg16(6);
			case TOK_DI:   return reg16(7);
			case TOK_R8W:  return reg16(8);
			case TOK_R9W:  return reg16(9);
			case TOK_R10W: return reg16(10);
			case TOK_R11W: return reg16(11);
			case TOK_R12W: return reg16(12);
			case TOK_R13W: return reg16(13);
			case TOK_R14W: return reg16(14);
			case TOK_R15W: return reg16(15);

			case TOK_AL: return reg8(0);
			case TOK_CL: return reg8(1);
			case TOK_DL: return reg8(2);
			case TOK_BL: return reg8(3);

			case TOK_SPL: return reg8(0);
			case TOK_BPL: return reg8(1);
			case TOK_SIL: return reg8(2);
			case TOK_DIL: return reg8(3);

			case TOK_AH:   return reg16(4);
			case TOK_CH:   return reg16(5);
			case TOK_DH:   return reg16(6);
			case TOK_BH:   return reg16(7);
			case TOK_R8B:  return reg16(8);
			case TOK_R9B:  return reg16(9);
			case TOK_R10B: return reg16(10);
			case TOK_R11B: return reg16(11);
			case TOK_R12B: return reg16(12);
			case TOK_R13B: return reg16(13);
			case TOK_R14B: return reg16(14);
			case TOK_R15B: return reg16(15);

			default: ASSERT(false, "invalid token: {}\n", (i32)token);
		};

		return {};
	}

	auto string_to_token(const utility::dynamic_string& str) -> token_type {
		static utility::map<utility::dynamic_string, token_type> operand_map = {
			// registers
			{ "cr0",   TOK_CR0,   },
			{ "cr1",   TOK_CR1,   },
			{ "cr2",   TOK_CR2,   },
			{ "cr3",   TOK_CR3,   },
			{ "cr4",   TOK_CR4,   },
			{ "cr8",   TOK_CR8,   },
			{ "dr0",   TOK_DR0,   },
			{ "dr1",   TOK_DR1,   },
			{ "dr2",   TOK_DR2,   },
			{ "dr3",   TOK_DR3,   },
			{ "dr4",   TOK_DR4,   },
			{ "dr5",   TOK_DR5,   },
			{ "dr6",   TOK_DR6,   },
			{ "dr7",   TOK_DR7,   },
			{ "k1",    TOK_K1,    },
			{ "k2",    TOK_K2,    },
			{ "k3",    TOK_K3,    },
			{ "k4",    TOK_K4,    },
			{ "k5",    TOK_K5,    },
			{ "k6",    TOK_K6,    },
			{ "k7",    TOK_K7,    },
			{ "es",    TOK_ES,    },
			{ "cs",    TOK_CS,    },
			{ "ss",    TOK_SS,    },
			{ "ds",    TOK_DS,    },
			{ "fs",    TOK_FS,    },
			{ "gs",    TOK_GS,    },
			{ "st0",   TOK_ST0,   },
			{ "st1",   TOK_ST1,   },
			{ "st2",   TOK_ST2,   },
			{ "st3",   TOK_ST3,   },
			{ "st4",   TOK_ST4,   },
			{ "st5",   TOK_ST5,   },
			{ "st6",   TOK_ST6,   },
			{ "st7",   TOK_ST7,   },
			{ "bnd0",  TOK_BND0,  },
			{ "bnd1",  TOK_BND1,  },
			{ "bnd2",  TOK_BND2,  },
			{ "bnd3",  TOK_BND3,  },
			{ "tmm0",  TOK_TMM0,  },
			{ "tmm1",  TOK_TMM1,  },
			{ "tmm2",  TOK_TMM2,  },
			{ "tmm3",  TOK_TMM3,  },
			{ "tmm4",  TOK_TMM4,  },
			{ "tmm5",  TOK_TMM5,  },
			{ "tmm6",  TOK_TMM6,  },
			{ "tmm7",  TOK_TMM7,  },
			{ "mm0",   TOK_MM0,   },
			{ "mm1",   TOK_MM1,   },
			{ "mm2",   TOK_MM2,   },
			{ "mm3",   TOK_MM3,   },
			{ "mm4",   TOK_MM4,   },
			{ "mm5",   TOK_MM5,   },
			{ "mm6",   TOK_MM6,   },
			{ "mm7",   TOK_MM7,   },
			{ "zmm0",  TOK_ZMM0,  },
			{ "zmm1",  TOK_ZMM1,  },
			{ "zmm2",  TOK_ZMM2,  },
			{ "zmm3",  TOK_ZMM3,  },
			{ "zmm4",  TOK_ZMM4,  },
			{ "zmm5",  TOK_ZMM5,  },
			{ "zmm6",  TOK_ZMM6,  },
			{ "zmm7",  TOK_ZMM7,  },
			{ "zmm8",  TOK_ZMM8,  },
			{ "zmm9",  TOK_ZMM9,  },
			{ "zmm10", TOK_ZMM10, },
			{ "zmm11", TOK_ZMM11, },
			{ "zmm12", TOK_ZMM12, },
			{ "zmm13", TOK_ZMM13, },
			{ "zmm14", TOK_ZMM14, },
			{ "zmm15", TOK_ZMM15, },
			{ "zmm16", TOK_ZMM16, },
			{ "zmm17", TOK_ZMM17, },
			{ "zmm18", TOK_ZMM18, },
			{ "zmm19", TOK_ZMM19, },
			{ "zmm20", TOK_ZMM20, },
			{ "zmm21", TOK_ZMM21, },
			{ "zmm22", TOK_ZMM22, },
			{ "zmm23", TOK_ZMM23, },
			{ "zmm24", TOK_ZMM24, },
			{ "zmm25", TOK_ZMM25, },
			{ "zmm26", TOK_ZMM26, },
			{ "zmm27", TOK_ZMM27, },
			{ "zmm28", TOK_ZMM28, },
			{ "zmm29", TOK_ZMM29, },
			{ "zmm30", TOK_ZMM30, },
			{ "zmm31", TOK_ZMM31, },
			{ "ymm0",  TOK_YMM0,  },
			{ "ymm1",  TOK_YMM1,  },
			{ "ymm2",  TOK_YMM2,  },
			{ "ymm3",  TOK_YMM3,  },
			{ "ymm4",  TOK_YMM4,  },
			{ "ymm5",  TOK_YMM5,  },
			{ "ymm6",  TOK_YMM6,  },
			{ "ymm7",  TOK_YMM7,  },
			{ "ymm8",  TOK_YMM8,  },
			{ "ymm9",  TOK_YMM9,  },
			{ "ymm10", TOK_YMM10, },
			{ "ymm11", TOK_YMM11, },
			{ "ymm12", TOK_YMM12, },
			{ "ymm13", TOK_YMM13, },
			{ "ymm14", TOK_YMM14, },
			{ "ymm15", TOK_YMM15, },
			{ "ymm16", TOK_YMM16, },
			{ "ymm17", TOK_YMM17, },
			{ "ymm18", TOK_YMM18, },
			{ "ymm19", TOK_YMM19, },
			{ "ymm20", TOK_YMM20, },
			{ "ymm21", TOK_YMM21, },
			{ "ymm22", TOK_YMM22, },
			{ "ymm23", TOK_YMM23, },
			{ "ymm24", TOK_YMM24, },
			{ "ymm25", TOK_YMM25, },
			{ "ymm26", TOK_YMM26, },
			{ "ymm27", TOK_YMM27, },
			{ "ymm28", TOK_YMM28, },
			{ "ymm29", TOK_YMM29, },
			{ "ymm30", TOK_YMM30, },
			{ "ymm31", TOK_YMM31, },
			{ "xmm0",  TOK_XMM0,  },
			{ "xmm1",  TOK_XMM1,  },
			{ "xmm2",  TOK_XMM2,  },
			{ "xmm3",  TOK_XMM3,  },
			{ "xmm4",  TOK_XMM4,  },
			{ "xmm5",  TOK_XMM5,  },
			{ "xmm6",  TOK_XMM6,  },
			{ "xmm7",  TOK_XMM7,  },
			{ "xmm8",  TOK_XMM8,  },
			{ "xmm9",  TOK_XMM9,  },
			{ "xmm10", TOK_XMM10, },
			{ "xmm11", TOK_XMM11, },
			{ "xmm12", TOK_XMM12, },
			{ "xmm13", TOK_XMM13, },
			{ "xmm14", TOK_XMM14, },
			{ "xmm15", TOK_XMM15, },
			{ "xmm16", TOK_XMM16, },
			{ "xmm17", TOK_XMM17, },
			{ "xmm18", TOK_XMM18, },
			{ "xmm19", TOK_XMM19, },
			{ "xmm20", TOK_XMM20, },
			{ "xmm21", TOK_XMM21, },
			{ "xmm22", TOK_XMM22, },
			{ "xmm23", TOK_XMM23, },
			{ "xmm24", TOK_XMM24, },
			{ "xmm25", TOK_XMM25, },
			{ "xmm26", TOK_XMM26, },
			{ "xmm27", TOK_XMM27, },
			{ "xmm28", TOK_XMM28, },
			{ "xmm29", TOK_XMM29, },
			{ "xmm30", TOK_XMM30, },
			{ "xmm31", TOK_XMM31, },
			{ "rax",   TOK_RAX,   },
			{ "rcx",   TOK_RCX,   },
			{ "rdx",   TOK_RDX,   },
			{ "rbx",   TOK_RBX,   },
			{ "rsp",   TOK_RSP,   },
			{ "rbp",   TOK_RBP,   },
			{ "rsi",   TOK_RSI,   },
			{ "rdi",   TOK_RDI,   },
			{ "r8",    TOK_R8,    },
			{ "r9",    TOK_R9,    },
			{ "r10",   TOK_R10,   },
			{ "r11",   TOK_R11,   },
			{ "r12",   TOK_R12,   },
			{ "r13",   TOK_R13,   },
			{ "r14",   TOK_R14,   },
			{ "r15",   TOK_R15,   },
			{ "eax",   TOK_EAX,   },
			{ "ecx",   TOK_ECX,   },
			{ "edx",   TOK_EDX,   },
			{ "ebx",   TOK_EBX,   },
			{ "esp",   TOK_ESP,   },
			{ "ebp",   TOK_EBP,   },
			{ "esi",   TOK_ESI,   },
			{ "edi",   TOK_EDI,   },
			{ "r8d",   TOK_R8D,   },
			{ "r9d",   TOK_R9D,   },
			{ "r10d",  TOK_R10D,  },
			{ "r11d",  TOK_R11D,  },
			{ "r12d",  TOK_R12D,  },
			{ "r13d",  TOK_R13D,  },
			{ "r14d",  TOK_R14D,  },
			{ "r15d",  TOK_R15D,  },
			{ "ax",    TOK_AX,    },
			{ "cx",    TOK_CX,    },
			{ "dx",    TOK_DX,    },
			{ "bx",    TOK_BX,    },
			{ "sp",    TOK_SP,    },
			{ "bp",    TOK_BP,    },
			{ "si",    TOK_SI,    },
			{ "di",    TOK_DI,    },
			{ "r8w",   TOK_R8W,   },
			{ "r9w",   TOK_R9W,   },
			{ "r10w",  TOK_R10W,  },
			{ "r11w",  TOK_R11W,  },
			{ "r12w",  TOK_R12W,  },
			{ "r13w",  TOK_R13W,  },
			{ "r14w",  TOK_R14W,  },
			{ "r15w",  TOK_R15W,  },
			{ "al",    TOK_AL,    },
			{ "cl",    TOK_CL,    },
			{ "dl",    TOK_DL,    },
			{ "bl",    TOK_BL,    },
			{ "spl",   TOK_SPL,   },
			{ "bpl",   TOK_BPL,   },
			{ "sil",   TOK_SIL,   },
			{ "dil",   TOK_DIL,   },
			{ "ah",    TOK_AH,    },
			{ "ch",    TOK_CH,    },
			{ "dh",    TOK_DH,    },
			{ "bh",    TOK_BH,    },
			{ "r8b",   TOK_R8B,   },
			{ "r9b",   TOK_R9B,   },
			{ "r10b",  TOK_R10B,  },
			{ "r11b",  TOK_R11B,  },
			{ "r12b",  TOK_R12B,  },
			{ "r13b",  TOK_R13B,  },
			{ "r14b",  TOK_R14B,  },
			{ "r15b",  TOK_R15B   },
			
			// types
			{ "byte" , TOK_BYTE  },
			{ "word" , TOK_WORD  },
			{ "dword", TOK_DWORD },
			{ "qword", TOK_QWORD },
			{ "tword", TOK_TWORD },

			{ "1to2",  TOK_1TO2  },
			{ "1to4",  TOK_1TO4  },
			{ "1to8",  TOK_1TO8  },
			{ "1to16", TOK_1TO16 },
			{ "1to32", TOK_1TO32 },

			// keywords
			{ "rel"  , TOK_REL   },
		};
		
		const auto it = operand_map.find(str);

		if(it == operand_map.end()) {
			return TOK_NONE;
		}

		return it->second;
	}

	auto is_token_k(token_type token) -> bool {
		switch(token) {
			case TOK_K1 ... TOK_K7: return true;
			default: return false;
		}
	}
} // namespace baremetal

