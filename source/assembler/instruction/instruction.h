#pragma once
#include "assembler/instruction/operand.h"

#include <array>

namespace baremetal {
#pragma pack(push, 1)
	struct instruction {
		enum opcode : u16 {
			MOV_RR,
			MOV_R_I8,
			MOV_R_I32,
		};

		instruction(opcode opcode);
		instruction(opcode opcode, operand a);
		instruction(opcode opcode, operand a, operand b);
		instruction(opcode opcode, operand a, operand b, operand c);

		opcode opcode;
		operand operands[3]; // expect up to 3 operands per instruction, this can technically be higher
		                     // for AVX 512 instructions, but those operands aren't actually encoded in
		                     // the instruction itself
	};
#pragma pack(pop)

	enum operand_type : u8 {
		NONE = 0,
		// registers
		REG, // any register
		REG_8,
		REG_16,
		REG_32,
		REG_64,

		// immediates
		IMM_8,
		IMM_16,
		IMM_32,
		IMM_64,

		// memory
		MEM_8,
		MEM_16,
		MEM_32,
		MEM_64,
	};

	inline auto is_imm(operand_type operand) -> bool {
		switch(operand) {
			case IMM_8:
			case IMM_16:
			case IMM_32:
			case IMM_64: return true;
			default: return false;
		}
	}

	inline auto is_reg(operand_type operand) -> bool {
		switch(operand) {
			case REG: 
			case REG_8:
			case REG_16:
			case REG_32:
			case REG_64: return true;
			default: return false;
		}
	}


	inline auto is_multiple_reg(const operand_type* operands) -> bool {
		u8 count = 0;

		for(u8 i = 0; i < 3; ++i) {
			count += is_reg(operands[i]);
		}

		return count > 1;
	}

	//struct instruction_info {
	//	constexpr instruction_info() = default;
	//	constexpr instruction_info(const char* name, bool rex_w, u8 opcode, operand_type operands[2])
	//	: name(name), rex_w(rex_w), opcode(opcode), operands(operands) {}

	//	const char* name;
	//	bool rex_w;
	//	u8 opcode;
	//	operand_type operands[2];
	//};

	struct instruction_info {
		const char* name;
		operand_type operands[3];

		u8 opcode;
		bool wide_mode;
		bool mod_rm;
		bool rex_w;
		bool multi; // additional opcode range
	};

	constexpr auto generate_instruction_db() -> std::array<instruction_info, 3> {
		std::array<instruction_info, 3> result;

		result[instruction::MOV_RR]    = instruction_info{ "mov", { REG_64, REG  }, 0x8B, true,  true,  true,  false };
		result[instruction::MOV_R_I8]  = instruction_info{ "mov", { REG_8, IMM_8 }, 0xB0, false, false, false, true  };
		result[instruction::MOV_R_I32] = instruction_info{ "mov", { REG, IMM_32  }, 0xC7, false, true,  true,  false };

		return result;
	}

	constexpr static std::array<instruction_info, 3> instruction_db = generate_instruction_db();
} // namespace baremetal
