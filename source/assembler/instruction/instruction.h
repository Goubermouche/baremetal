#pragma once
#include <utility/assert.h>

#include "assembler/instruction/operands/operands.h"

namespace baremetal {
	enum extension : u8 {
		EXT_NONE = 0b00000000,
		EXT_0 = 0b00000001, // /0
		EXT_1 = 0b00000010, // /1
		EXT_2 = 0b00000011, // /2
		EXT_3 = 0b00000100, // /3
		EXT_4 = 0b00000101, // /4
		EXT_5 = 0b00000110, // /5
		EXT_6 = 0b00000111, // /6
		EXT_7 = 0b00001000, // /7
		EXT_R = 0b00010000, // /r (mod rm byte exists, and any register can be used)

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

#pragma pack(push, 1)
	struct instruction {
		constexpr instruction() = default;

		constexpr instruction(
			const char* name,
			u32 opcode,
			u8 ext,
			u8 prefix,
			u16 context_index,
			u8 operand_count,
			direction operand_direction,
			enum operand::type op1,
			enum operand::type op2,
			enum operand::type op3,
			enum operand::type op4
		) : m_name(name),
		m_opcode(opcode),
		m_extension(ext),
		m_prefix(prefix),
		m_special_index(context_index),
		m_operand_count(operand_count),
		m_operand_direction(operand_direction),
		m_operands{ op1, op2, op3, op4 } {}

		void print() const {
			utility::console::print("{} ", m_name);

			for(u8 i = 0; i < 4; ++i) {
				if(m_operands[i] != operand::OP_NONE) {
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

		constexpr auto get_ext() const -> u8 {
			// extract the ext_x bits and subtract one to convert them to the
			// specific value
			const u8 masked = m_extension & 0b00011111;
			return masked - 1;
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
		constexpr auto get_operand(u8 index) const -> enum operand::type {
			return m_operands[index];
		}
		constexpr auto get_special_kind() const -> u8 {
			return m_special_index >> 14;
		}
		constexpr auto get_special_index() const -> u16 {
			return m_special_index & 0b0011111111111111;
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

		constexpr auto has_prefix() const -> bool {
			return m_prefix != PREFIX_NONE;
		}
		constexpr auto has_special_index() const -> bool {
			return m_special_index != std::numeric_limits<u16>::max();
		}
	private:
		const char* m_name;

		// encoding
		u32 m_opcode;
		u8 m_extension;
		u8 m_prefix;

		// some instructions have a special optimization index, which points to an alternative variant
		// which can be used depending on the provided operands

		//           [1111111111111111] (65535) is an invalid index => that instruction does not have one
		// kind      [XX______________]
		// index     [__XXXXXXXXXXXXXX]
		u16 m_special_index;

		// operands
		u8 m_operand_count;
		direction m_operand_direction;
		enum operand::type m_operands[4];
	};
#pragma pack(pop)

// instruction generators
#define INST_0(name, opcode, ext, prefix, ctx, dir) \
  instruction(                                      \
    #name,                                          \
    opcode,                                         \
    ext,                                            \
    prefix,                                         \
    ctx,                                            \
    0,                                              \
    direction::DIR_ ## dir,                         \
    operand::OP_NONE,                               \
    operand::OP_NONE,                               \
    operand::OP_NONE,                               \
    operand::OP_NONE                                \
  ),

#define INST_1(name, opcode, ext, prefix, ctx, dir, op1) \
  instruction(                                           \
    #name,                                               \
    opcode,                                              \
    ext,                                                 \
    prefix,                                              \
    ctx,                                                 \
    1,                                                   \
    direction::DIR_ ## dir,                              \
    operand::OP_ ## op1,                                 \
    operand::OP_NONE,                                    \
    operand::OP_NONE,                                    \
    operand::OP_NONE                                     \
  ),

#define INST_2(name, opcode, ext, prefix, ctx, dir, op1, op2) \
  instruction(                                                \
    #name,                                                    \
    opcode,                                                   \
    ext,                                                      \
    prefix,                                                   \
    ctx,                                                      \
    2,                                                        \
    direction::DIR_ ## dir,                                   \
    operand::OP_ ## op1,                                      \
    operand::OP_ ## op2,                                      \
    operand::OP_NONE,                                         \
    operand::OP_NONE                                          \
  ),

#define INST_3(name, opcode, ext, prefix, ctx, dir, op1, op2, op3) \
  instruction(                                                     \
    #name,                                                         \
    opcode,                                                        \
    ext,                                                           \
    prefix,                                                        \
    ctx,                                                           \
    3,                                                             \
    direction::DIR_ ## dir,                                        \
    operand::OP_ ## op1,                                           \
    operand::OP_ ## op2,                                           \
    operand::OP_ ## op3,                                           \
    operand::OP_NONE                                               \
  ),

#define INST_4(name, opcode, ext, prefix, ctx, dir, op1, op2, op3, op4) \
  instruction(                                                          \
    #name,                                                              \
    opcode,                                                             \
    ext,                                                                \
    prefix,                                                             \
    ctx,                                                                \
    4,                                                                  \
    direction::DIR_ ## dir,                                             \
    operand::OP_ ## op1,                                                \
    operand::OP_ ## op2,                                                \
    operand::OP_ ## op3,                                                \
    operand::OP_ ## op4                                                 \
  ),

// select which INST_X to call based off of the variable argument count (0-2)
#define INST_SELECT(count) CONCATENATE(INST_, count)
#define INST_HELPER(count, name, ...) EXPAND(INST_SELECT(count)(name, __VA_ARGS__))
#define INST(name, opcode, extensions, prefix, context, dir, ...) \
  INST_HELPER(GET_ARG_COUNT(__VA_ARGS__), name, opcode, extensions, prefix, context, dir, __VA_ARGS__)

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
