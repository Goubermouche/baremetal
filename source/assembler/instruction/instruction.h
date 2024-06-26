#pragma once
#include "assembler/instruction/operands/operands.h"
#include <utility/assert.h>

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
		PREFIX_NONE = 0b00000000,
		// group 1
		LOCK = 0b00000001,
		REPNE = 0b00000010,
		REP = 0b00000011,
		// group 2
		CS_SEGMENT = 0b00000100,
		SS_SEGMENT = 0b00001000,
		DS_SEGMENT = 0b00001100,
		ES_SEGMENT = 0b00010000,
		FS_SEGMENT = 0b00010100,
		GS_SEGMENT = 0b00011000,
		BRANCH_NOT_TAKEN = 0b00011100,
		BRANCH_TAKEN = 0b00100000,
		// group 3
		OPERAND_SIZE_OVERRIDE = 0b01000000,
		// group 4
		ADDRESS_SIZE_OVERRIDE = 0b10000000
	};

	enum direction : u8 {
		DIR_NORMAL,
		DIR_REVERSE,
		DIR_ENCODED
	};

#pragma pack(push, 1)
	struct instruction_info {
		void print() const {
			utility::console::print("{} {} {}\n", name, operand_type_to_string(op1), operand_type_to_string(op2));
		}

		constexpr auto is_rexw() const -> bool {
			return extension & EXT_REXW;

			if(extension& EXT_REXW) {
				return true;
			}

			// TODO: this can be replaced by a fake REX.W flag
			if(is_operand_gp_reg(op1) && get_operand_bit_width(op1) == 64) {
				return true;
			}

			if(is_operand_gp_reg(op2) && get_operand_bit_width(op2) == 64) {
				return true;
			}

			return false;
		}

		constexpr auto is_r() const -> bool {
			return extension & EXT_R;
		}

		constexpr auto is_opcode_ext() const -> bool {
			return extension & EXT_OP_R;
		}

		constexpr auto get_ext() const -> u8 {
			// extract the ext_x bits and subtract one to convert them to the
			// specific value
			const u8 masked = extension & 0b00011111;
			return masked - 1;
		}

		constexpr auto get_direction() const -> bool {
			switch(dir) {
				case DIR_NORMAL:  return true;
				case DIR_REVERSE: return false;
				case DIR_ENCODED: return !(opcode & 0b000000000000000000000010);
			}

			ASSERT(false, "not implemented", "xd");

			return false;
		}

		constexpr auto is_ext() const -> bool {
			return
				extension & EXT_0 ||
				extension & EXT_1 ||
				extension & EXT_2 ||
				extension & EXT_3 ||
				extension & EXT_4 ||
				extension & EXT_5 ||
				extension & EXT_6 ||
				extension & EXT_7;
		}

		constexpr auto has_prefix() const -> bool {
			return prefix != PREFIX_NONE;
		}

		constexpr auto get_operand_count() const -> u8 {
			u8 count = 0;

			if(op1 != operand::OP_NONE) { count++; }
			if(op2 != operand::OP_NONE) { count++; }

			return count;
		}

		auto has_imm_operands() const -> std::pair<bool, u8> {
			if(is_operand_imm(op2)) {
				return { true, 1 };
			}

			if(is_operand_imm(op1)) {
				return { true, 0 };
			}

			return { false, 0 };
		}

		const char* name;
		u32 opcode; // 3 bytes
		u8 extension;
		u8 prefix;
		u16 context_index;
		enum operand::type op1;
		enum operand::type op2;
		direction dir;
	};
#pragma pack(pop)

#define INST(name, opcode, extensions, prefix, context, op1, op2, dir) { #name, opcode, extensions, prefix, context, operand::OP_ ## op1, operand::OP_ ## op2, direction::DIR_ ## dir },

	static constexpr instruction_info instruction_db[] = {
		#include "assembler/instruction/databases/instruction_database.inc"
	};

#undef INST
} // namespace baremetal
