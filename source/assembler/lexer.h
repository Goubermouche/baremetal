#pragma once
#include "assembler/instruction/operands/immediates.h"
#include "assembler/instruction/operands/registers.h"

#include <utility/containers/dynamic_string.h> 

namespace baremetal {
	enum token_type : u16 {
		TOK_NONE = 0,

		// registers
		TOK_CR0,
		TOK_CR1,
		TOK_CR2,
		TOK_CR3,
		TOK_CR4,
		TOK_CR8,
		TOK_DR0,
		TOK_DR1,
		TOK_DR2,
		TOK_DR3,
		TOK_DR4,
		TOK_DR5,
		TOK_DR6,
		TOK_DR7,
		TOK_K1,
		TOK_K2,
		TOK_K3,
		TOK_K4,
		TOK_K5,
		TOK_K6,
		TOK_K7,
		TOK_ES,
		TOK_CS,
		TOK_SS,
		TOK_DS,
		TOK_FS,
		TOK_GS,
		TOK_ST0,
		TOK_ST1,
		TOK_ST2,
		TOK_ST3,
		TOK_ST4,
		TOK_ST5,
		TOK_ST6,
		TOK_ST7,
		TOK_TMM0,
		TOK_TMM1,
		TOK_TMM2,
		TOK_TMM3,
		TOK_TMM4,
		TOK_TMM5,
		TOK_TMM6,
		TOK_TMM7,
		TOK_BND0,
		TOK_BND1,
		TOK_BND2,
		TOK_BND3,
		TOK_MM0,
		TOK_MM1,
		TOK_MM2,
		TOK_MM3,
		TOK_MM4,
		TOK_MM5,
		TOK_MM6,
		TOK_MM7,
		TOK_ZMM0,
		TOK_ZMM1,
		TOK_ZMM2,
		TOK_ZMM3,
		TOK_ZMM4,
		TOK_ZMM5,
		TOK_ZMM6,
		TOK_ZMM7,
		TOK_ZMM8,
		TOK_ZMM9,
		TOK_ZMM10,
		TOK_ZMM11,
		TOK_ZMM12,
		TOK_ZMM13,
		TOK_ZMM14,
		TOK_ZMM15,
		TOK_ZMM16,
		TOK_ZMM17,
		TOK_ZMM18,
		TOK_ZMM19,
		TOK_ZMM20,
		TOK_ZMM21,
		TOK_ZMM22,
		TOK_ZMM23,
		TOK_ZMM24,
		TOK_ZMM25,
		TOK_ZMM26,
		TOK_ZMM27,
		TOK_ZMM28,
		TOK_ZMM29,
		TOK_ZMM30,
		TOK_ZMM31,
		TOK_YMM0,
		TOK_YMM1,
		TOK_YMM2,
		TOK_YMM3,
		TOK_YMM4,
		TOK_YMM5,
		TOK_YMM6,
		TOK_YMM7,
		TOK_YMM8,
		TOK_YMM9,
		TOK_YMM10,
		TOK_YMM11,
		TOK_YMM12,
		TOK_YMM13,
		TOK_YMM14,
		TOK_YMM15,
		TOK_YMM16,
		TOK_YMM17,
		TOK_YMM18,
		TOK_YMM19,
		TOK_YMM20,
		TOK_YMM21,
		TOK_YMM22,
		TOK_YMM23,
		TOK_YMM24,
		TOK_YMM25,
		TOK_YMM26,
		TOK_YMM27,
		TOK_YMM28,
		TOK_YMM29,
		TOK_YMM30,
		TOK_YMM31,
		TOK_XMM0,
		TOK_XMM1,
		TOK_XMM2,
		TOK_XMM3,
		TOK_XMM4,
		TOK_XMM5,
		TOK_XMM6,
		TOK_XMM7,
		TOK_XMM8,
		TOK_XMM9,
		TOK_XMM10,
		TOK_XMM11,
		TOK_XMM12,
		TOK_XMM13,
		TOK_XMM14,
		TOK_XMM15,
		TOK_XMM16,
		TOK_XMM17,
		TOK_XMM18,
		TOK_XMM19,
		TOK_XMM20,
		TOK_XMM21,
		TOK_XMM22,
		TOK_XMM23,
		TOK_XMM24,
		TOK_XMM25,
		TOK_XMM26,
		TOK_XMM27,
		TOK_XMM28,
		TOK_XMM29,
		TOK_XMM30,
		TOK_XMM31,
		TOK_RAX,
		TOK_RCX,
		TOK_RDX,
		TOK_RBX,
		TOK_RSP,
		TOK_RBP,
		TOK_RSI,
		TOK_RDI,
		TOK_R8,
		TOK_R9,
		TOK_R10,
		TOK_R11,
		TOK_R12,
		TOK_R13,
		TOK_R14,
		TOK_R15,
		TOK_EAX,
		TOK_ECX,
		TOK_EDX,
		TOK_EBX,
		TOK_ESP,
		TOK_EBP,
		TOK_ESI,
		TOK_EDI,
		TOK_R8D,
		TOK_R9D,
		TOK_R10D,
		TOK_R11D,
		TOK_R12D,
		TOK_R13D,
		TOK_R14D,
		TOK_R15D,
		TOK_AX,
		TOK_CX,
		TOK_DX,
		TOK_BX,
		TOK_SP,
		TOK_BP,
		TOK_SI,
		TOK_DI,
		TOK_R8W,
		TOK_R9W,
		TOK_R10W,
		TOK_R11W,
		TOK_R12W,
		TOK_R13W,
		TOK_R14W,
		TOK_R15W,
		TOK_AL,
		TOK_CL,
		TOK_DL,
		TOK_BL,
		TOK_SPL,
		TOK_BPL,
		TOK_SIL,
		TOK_DIL,
		TOK_AH,
		TOK_CH,
		TOK_DH,
		TOK_BH,
		TOK_R8B,
		TOK_R9B,
		TOK_R10B,
		TOK_R11B,
		TOK_R12B,
		TOK_R13B,
		TOK_R14B,
		TOK_R15B,

		// types
		TOK_BYTE,
		TOK_WORD,
		TOK_DWORD,
		TOK_QWORD,
		TOK_TWORD,

		TOK_IDENTIFIER,
		TOK_STRING,
		TOK_CHAR,
		TOK_NUMBER,

		// special characters
		TOK_EOF,
		TOK_LBRACKET,    // [ 
		TOK_RBRACKET,    // ]
		TOK_LBRACE,      // {
		TOK_RBRACE,      // }
		TOK_PLUS,        // +
		TOK_MINUS,       // -
		TOK_ASTERISK,    // *
		TOK_COMMA,       // ,
		TOK_NEWLINE,     // \n
		TOK_DOLLARSIGN,  // $
		TOK_DOT,         // .

		// broadcast keywords
		TOK_1TO2,  // 1to2
		TOK_1TO4,  // 1to4
		TOK_1TO8,  // 1to8
		TOK_1TO16, // 1to16
		TOK_1TO32, // 1to32

		TOK_REL,     // rel
		TOK_SECTION, // section
		TOK_DB,      // db
		TOK_DW,      // dw
		TOK_DD,      // dd
		TOK_DQ,      // dq
	};

	enum data_type : u8 {
		DT_NONE = 0,
		DT_BYTE,
		DT_WORD,
		DT_DWORD,
		DT_QWORD,
		DT_TWORD,
	};

	enum mask_type : u8 {
		MASK_NONE = 0, 
		MASK_K0, // {k0}
		MASK_K1,
		MASK_K2,
		MASK_K3,
		MASK_K4,
		MASK_K5,
		MASK_K6,
		MASK_K7, 
		MASK_K0_Z, // {k0} {z}
		MASK_K1_Z,
		MASK_K2_Z,
		MASK_K3_Z,
		MASK_K4_Z,
		MASK_K5_Z,
		MASK_K6_Z,
		MASK_K7_Z,
		// since masks and broadcasts are the only thing which can be in trailing braces we can store 
		// broadcasts in here as well
		MASK_BROADCAST_1TO2,
		MASK_BROADCAST_1TO4,
		MASK_BROADCAST_1TO8,
		MASK_BROADCAST_1TO16,
		MASK_BROADCAST_1TO32,
	};

	auto is_mask_broadcast(mask_type mask) -> bool;

	auto mask_to_k(mask_type mask) -> u8;
	auto mask_to_broadcast_n(mask_type mask) -> u8;

	class lexer {
	public:
		void set_text(const utility::dynamic_string& text);
		auto get_next_token() -> token_type;
	private:
		auto get_next_char() -> char;
		auto get_next_char_escaped() -> char;
	private:
		u64 m_index;
		utility::dynamic_string m_text;
		char m_current_char;
	public:
		token_type current;
		imm current_immediate;
		utility::dynamic_string current_string;
		bool force_keyword = false; // consider the next number as a keyword instead of a numerical literal
	};

	auto token_to_data_type(token_type token) -> data_type;
	auto token_to_register(token_type token) -> reg;

	auto string_to_token(const utility::dynamic_string& str) -> token_type;

	auto is_token_broadcast(token_type token) -> bool;
	auto is_token_k(token_type token) -> bool;
} // namespace baremetal

