#pragma once
#include <utility/assert.h>

#include "assembler/instruction/operands/operands.h"

namespace baremetal {
	enum extension : u8 {
		EXT_NONE = 0b00000000,
		EXT_0    = 0b00000001, // /0
		EXT_1    = 0b00000010, // /1
		EXT_2    = 0b00000011, // /2
		EXT_3    = 0b00000100, // /3
		EXT_4    = 0b00000101, // /4
		EXT_5    = 0b00000110, // /5
		EXT_6    = 0b00000111, // /6
		EXT_7    = 0b00001000, // /7
		EXT_R    = 0b00010000, // /r (mod rm byte exists, and any register can be used)

		// flags
		EXT_REXW = 0b00100000,

		// opcode extensions
		EXT_OP_R = 0b01000000, // opcode + r / opcode + i
	};

	enum prefix : u8 {
		// group 1 [______XX]
		// group 2 [__XXXX__]
		// group 3 [_X______]
		// group 4 [X_______]
		PREFIX_NONE           = 0b00000000,
		// group 1
		LOCK                  = 0b00000001,
		REPNE                 = 0b00000010,
		REP                   = 0b00000011,
		// group 2
		CS_SEGMENT            = 0b00000100,
		SS_SEGMENT            = 0b00001000,
		DS_SEGMENT            = 0b00001100,
		ES_SEGMENT            = 0b00010000,
		FS_SEGMENT            = 0b00010100,
		GS_SEGMENT            = 0b00011000,
		BRANCH_NOT_TAKEN      = 0b00011100,
		BRANCH_TAKEN          = 0b00100000,
		// group 3
		OPERAND_SIZE_OVERRIDE = 0b01000000,
		// group 4
		ADDRESS_SIZE_OVERRIDE = 0b10000000
	};

	// operand direction
	enum direction : u8 {
		DIR_NORMAL,
		DIR_REVERSE
	};

	enum encoding : u8 {
		// rex
		ENC_REX,
		// vex
		ENC_VEX_RVM,
		ENC_VEX_RMV,
		ENC_VEX_VM,
		ENC_VEX_RM,
	};

	enum instruction_extension : u32 {
		IEX_NONE = 0,

		IEX_X64,

		// simd
		IEX_MMX,
		IEX_MMX2,
		IEX_3DNOW,
		IEX_SSE,
		IEX_SSE2,
		IEX_SSE3,
		IEX_SSSE3,
		IEX_SSE4_1,
		IEX_SSE4_2,
		IEX_SSE4A,

		// aes / sha
		IEX_AESNI,
		IEX_SHA,

		// bmi
		IEX_BMI,
		IEX_BMI2,

		// transactional mem
		IEX_RTM,

		// xsave
		IEX_XSAVE,
		IEX_XSAVEC,
		IEX_XSAVES,
		IEX_XSAVEOPT,

		// others
		IEX_ADX,
		IEX_MPX,
		IEX_SMAP,
		IEX_CLFLUSH,
		IEX_CLFLUSHOPT,
		IEX_CLWB,
		IEX_CLZERO,
		IEX_CMOV,
		IEX_CMPXCHG16B,
		IEX_CMPXCHG8B,
		IEX_FXSR,
		IEX_LZCNT,
		IEX_LAHFSAHF,
		IEX_MOVBE,
		IEX_PCLMULQDQ,
		IEX_POPCNT,
		IEX_PREFETCHW,
		IEX_PREFETCHW1,
		IEX_FSGSBASE,
		IEX_RDRAND,
		IEX_RDSEED,
		IEX_RDTSC,
		IEX_RDTSCP,
		IEX_I486,
	};

	enum implied_mandatory_prefix : u8 {
		IMP_NONE = 0b00,
		IMP_66   = 0b01,
		IMP_F3   = 0b10,
		IMP_F2   = 0b11
	};

#pragma pack(push, 1)
	struct instruction {
		constexpr instruction() = default;

		constexpr instruction(
			const char* name,
			u32 opcode,
			u16 ilo,
			u8 ext,
			u8 prefix,
			u8 variant,
			u16 context_index,
			u8 operand_count,
			direction operand_direction,
			encoding encoding,
			implied_mandatory_prefix imp,
			operand_type op1,
			operand_type op2,
			operand_type op3,
			operand_type op4
		) : m_name(name),
		m_encoding(encoding),
		m_opcode(opcode),
		m_ilo(ilo),
		m_extension(ext),
		m_prefix(prefix),
		m_variant(variant),
		m_imp(imp),
		m_special_index(context_index),
		m_operand_count(operand_count),
		m_operand_direction(operand_direction),
		m_operands{ op1, op2, op3, op4 } {}

		void print() const {
			utility::console::print("{} ", m_name);

			for(u8 i = 0; i < 4; ++i) {
				if(m_operands[i] != OP_NONE) {
					utility::console::print("{} ", operand_type_to_string(m_operands[i]));
				}
			}

			utility::console::print("\n");
		}

		constexpr auto is_rexw() const -> bool {
			return m_extension & EXT_REXW;
		}
		constexpr auto is_r() const -> bool {
			return m_extension & EXT_R;
		}
		constexpr auto is_opcode_ext() const -> bool {
			return m_extension & EXT_OP_R;
		}
		constexpr auto is_ext() const -> bool {
			return
				m_extension & EXT_0 ||
				m_extension & EXT_1 ||
				m_extension & EXT_2 ||
				m_extension & EXT_3 ||
				m_extension & EXT_4 ||
				m_extension & EXT_5 ||
				m_extension & EXT_6 ||
				m_extension & EXT_7;
		}
		constexpr auto is_vex() const -> bool {
			switch(m_encoding) {
				case ENC_VEX_RVM:
				case ENC_VEX_RMV:
				case ENC_VEX_VM: 
				case ENC_VEX_RM: return true;
				default: return false;
			}
		}

		constexpr auto is_rex() const -> bool {
			switch(m_encoding) {
				case ENC_REX: return true;
				default: return false;
			}
		}

		constexpr auto get_ext() const -> u8 {
			// extract the ext_x bits and subtract one to convert them to the
			// specific value
			const u8 masked = m_extension & 0b00011111;
			return masked - 1;
		}
		constexpr auto get_name() const -> const char* {
			return m_name;
		}
		constexpr auto get_direction() const -> bool {
			return m_operand_direction == DIR_NORMAL;
		}
		constexpr auto get_operand_count() const -> u8 {
			return m_operand_count;
		}
		constexpr auto get_prefix() const -> u8 {
			return m_prefix;
		}
		constexpr auto get_extension() const -> u8 {
			return m_extension;
		}
		constexpr auto get_opcode() const -> u32 {
			return m_opcode;
		}
		constexpr auto get_operand(u8 index) const -> operand_type {
			return m_operands[index];
		}
		constexpr auto get_special_kind() const -> u8 {
			return m_special_index >> 14;
		}
		constexpr auto get_special_index() const -> u16 {
			return m_special_index & 0b0011111111111111;
		}
		constexpr auto get_encoding_prefix() const -> encoding {
			return m_encoding;
		}

		auto get_imm_operand_count() const -> u8 {
			u8 count = 0;

			if(is_operand_imm(m_operands[0])) { count++; }
			if(is_operand_imm(m_operands[1])) { count++; }
			if(is_operand_imm(m_operands[2])) { count++; }
			if(is_operand_imm(m_operands[3])) { count++; }

			return count;
		}
		auto get_reg_operand_count() const -> u8 {
			u8 count = 0;

			if(is_operand_reg(m_operands[0])) { count++; }
			if(is_operand_reg(m_operands[1])) { count++; }
			if(is_operand_reg(m_operands[2])) { count++; }
			if(is_operand_reg(m_operands[3])) { count++; }

			return count;
		}
		auto get_imp() const -> u8 {
			return m_imp;
		}
		auto get_ilo() const -> u16 {
			return m_ilo;
		}
		auto get_variant() const -> u8 {
			return m_variant;
		}

		auto get_mem_operand() const -> u8 {
			if(is_operand_mem(m_operands[0])) { return 0; }
			if(is_operand_mem(m_operands[1])) { return 1; }
			if(is_operand_mem(m_operands[2])) { return 2; }
			if(is_operand_mem(m_operands[3])) { return 3; }

			return 0;
		}

		auto has_mem_operand() const -> bool {
			if(is_operand_mem(m_operands[0])) { return true; }
			if(is_operand_mem(m_operands[1])) { return true; }
			if(is_operand_mem(m_operands[2])) { return true; }
			if(is_operand_mem(m_operands[3])) { return true; }

			return false;
		}

		constexpr auto has_prefix() const -> bool {
			return m_prefix != PREFIX_NONE;
		}
		constexpr auto has_special_index() const -> bool {
			return m_special_index != utility::limits<u16>::max();
		}
		constexpr auto has_variant() const -> bool {
			return m_variant != 8;
		}
	private:
		const char* m_name;

		// encoding
		encoding m_encoding; // REX / VEX / EVEX etc.
		u32 m_opcode;
		u16 m_ilo; // implied leading opcode
		u8 m_extension;
		u8 m_prefix;
		u8 m_variant; // 8 == none
		implied_mandatory_prefix m_imp;

		// some instructions have a special optimization index, which points to an alternative variant
		// which can be used depending on the provided operands

		//           [1111111111111111] (65535) is an invalid index => that instruction does not have one
		// kind      [XX______________]
		// index     [__XXXXXXXXXXXXXX]
		u16 m_special_index;

		// operands
		u8 m_operand_count;
		direction m_operand_direction;
		operand_type m_operands[4];
	};
#pragma pack(pop)

// instruction generators
#define INST_0(name, opcode, ext, prefix, ctx, dir, enc, imp, ilo, var, empty) \
  instruction(                                                          \
    #name,                                                              \
    opcode,                                                             \
    ilo,                                                                \
    ext,                                                                \
    prefix,                                                             \
    var,                                                                \
    ctx,                                                                \
    0,                                                                  \
    direction::DIR_ ## dir,                                             \
    encoding::ENC_ ## enc,                                              \
    IMP_ ## imp,                                                        \
    OP_NONE,                                                            \
    OP_NONE,                                                            \
    OP_NONE,                                                            \
    OP_NONE                                                             \
  ),

#define INST_1(name, opcode, ext, prefix, ctx, dir, enc, imp, ilo, var,  op1) \
  instruction(                                                               \
    #name,                                                                   \
    opcode,                                                                  \
    ilo   ,                                                                  \
    ext,                                                                     \
    prefix,                                                                  \
    var,                                                                     \
    ctx,                                                                     \
    1,                                                                       \
    direction::DIR_ ## dir,                                                  \
		encoding::ENC_ ## enc,                                                   \
    IMP_ ## imp,                                                             \
    OP_ ## op1,                                                              \
    OP_NONE,                                                                 \
    OP_NONE,                                                                 \
    OP_NONE                                                                  \
  ),

#define INST_2(name, opcode, ext, prefix, ctx, dir, enc, imp, ilo, var, op1, op2) \
  instruction(                                                                    \
    #name,                                                                        \
    opcode,                                                                       \
    ilo   ,                                                                       \
    ext,                                                                          \
    prefix,                                                                       \
    var,                                                                          \
    ctx,                                                                          \
    2,                                                                            \
    direction::DIR_ ## dir,                                                       \
		encoding::ENC_ ## enc,                                                        \
		IMP_ ## imp,                                                                  \
    OP_ ## op1,                                                                   \
    OP_ ## op2,                                                                   \
    OP_NONE,                                                                      \
    OP_NONE                                                                       \
  ),

#define INST_3(name, opcode, ext, prefix, ctx, dir, enc, imp, ilo, var,op1, op2, op3) \
  instruction(                                                                         \
    #name,                                                                             \
    opcode,                                                                            \
    ilo,                                                                               \
    ext,                                                                               \
    prefix,                                                                            \
    var,                                                                               \
    ctx,                                                                               \
    3,                                                                                 \
    direction::DIR_ ## dir,                                                            \
		encoding::ENC_ ## enc,                                                             \
		IMP_ ## imp,                                                                       \
    OP_ ## op1,                                                                        \
    OP_ ## op2,                                                                        \
    OP_ ## op3,                                                                        \
    OP_NONE                                                                            \
  ),

#define INST_4(name, opcode, ext, prefix, ctx, dir, enc, imp, ilo, var, op1, op2, op3, op4) \
  instruction(                                                                              \
    #name,                                                                                  \
    opcode,                                                                                 \
    ilo   ,                                                                                 \
    ext,                                                                                    \
    prefix,                                                                                 \
    var,                                                                                    \
    ctx,                                                                                    \
    4,                                                                                      \
    direction::DIR_ ## dir,                                                                 \
		encoding::ENC_ ## enc,                                                                  \
		IMP_ ## imp,                                                                            \
    OP_ ## op1,                                                                             \
    OP_ ## op2,                                                                             \
    OP_ ## op3,                                                                             \
    OP_ ## op4                                                                              \
  ),

// select which INST_X to call based off of the variable argument count (0-2)
#define INST_SELECT(count) CONCATENATE(INST_, count)
#define INST_HELPER(count, name, ...) EXPAND(INST_SELECT(count)(name, __VA_ARGS__))
#define INST(name, opcode, extensions, prefix, context, dir, enc, imp, ilo, var, iext, ...) \
  INST_HELPER(GET_ARG_COUNT(__VA_ARGS__), name, opcode, extensions, prefix, context, dir, enc, imp, ilo, var, __VA_ARGS__)

	static constexpr instruction instruction_db[] = {
		#include "assembler/instruction/databases/instruction_database.inc"
	};

#undef INST_0
#undef INST_1
#undef INST_2
#undef INST_3
#undef INST_4

#undef INST_SELECT
#undef INST_HELPER

#undef INST
} // namespace baremetal
