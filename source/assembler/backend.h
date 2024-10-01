#pragma once
#include "assembler/instruction/instruction.h"

namespace baremetal {
	namespace detail {
		// enum mod_mode : u8 {
		// 	INDIRECT        = 0b00,
		// 	INDIRECT_DISP8  = 0b01,
		// 	INDIRECT_DISP32 = 0b10,
		// 	DIRECT          = 0b11
		// };

		// auto mod_rm(mod_mode mod, u8 rx, u8 rm) -> u8;
		// auto sib(u8 scale, u8 index, u8 base) -> u8;
		// auto rex(bool w, u8 rx, u8 base, u8 index) -> u8;

		// auto direct(u8 rx, u8 reg) -> u8;
		// auto indirect(u8 rx, u8 base) -> u8;
		// auto indirect_disp_8(u8 rx, u8 base) -> u8;
		// auto indirect_disp_32(u8 rx, u8 base) -> u8;
	} // namespace detail

	using namespace utility::types;

	struct backend {
		struct code {
			u8* data;
			u8 size;
		};

		static auto get_instruction_by_name(const char* name) -> u32;

		static auto emit_instruction(const instruction* inst, const operand* operands, bool optimize) -> code;
	private:
		static void emit_instruction_operands(const instruction* inst, const operand* operands);
		static void emit_instruction_prefix(const instruction* inst, const operand* operands);
		static void emit_instruction_opcode(const instruction* inst, const operand* operands);
		static void emit_instruction_mod_rm(const instruction* inst, const operand* operands);
		static void emit_instruction_sib(const instruction* inst, const operand* operands);

		static void emit_opcode_prefix_evex(const instruction* inst, const operand* operands);
		static void emit_opcode_prefix_vex(const instruction* inst, const operand* operands);
		static void emit_opcode_prefix_rex(const instruction* inst, const operand* operands);

		static void push_byte(u8 value);
	private:
		static u8 m_data_size;
		static u8 m_data[15];
	};
} // baremetal

