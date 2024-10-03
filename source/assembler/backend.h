#pragma once
#include "assembler/instruction/instruction.h"

namespace baremetal {
	namespace detail {
		enum mod_mode : u8 {
			INDIRECT        = 0b00,
			INDIRECT_DISP8  = 0b01,
			INDIRECT_DISP32 = 0b10,
			DIRECT          = 0b11
		};

		auto mod_rm(mod_mode mod, u8 rx, u8 rm) -> u8;
		auto sib(u8 scale, u8 index, u8 base) -> u8;
		auto rex(bool w, u8 rx, u8 base, u8 index) -> u8;

		auto direct(u8 rx, u8 reg) -> u8;
		auto indirect(u8 rx, u8 base) -> u8;
		auto indirect_disp_8(u8 rx, u8 base) -> u8;
		auto indirect_disp_32(u8 rx, u8 base) -> u8;
		
		auto extract_operand_reg(const operand& op) -> u8;
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
		// instruction parts
		static void emit_instruction_operands(const instruction* inst, const operand* operands);
		static void emit_instruction_prefix(const instruction* inst, const operand* operands);
		static void emit_instruction_opcode(const instruction* inst, const operand* operands);
		static void emit_instruction_mod_rm(const instruction* inst, const operand* operands);
		static void emit_instruction_sib(const operand* operands);

		// instruction prefixes
		static void emit_opcode_prefix_evex(const instruction* inst, const operand* operands);
		static void emit_opcode_prefix_vex(const instruction* inst, const operand* operands);
		static void emit_opcode_prefix_rex(const instruction* inst, const operand* operands);

		static void emit_opcode_prefix_rex_mem(const mem& memory);
		static void emit_opcode_prefix_vex_two(const instruction* inst, const operand* operands);
		static void emit_opcode_prefix_vex_three(const instruction* inst, const operand* operands);
		static void emit_data_operand(u64 data, u16 bit_width);
		
		static auto get_instruction_rex(const instruction* inst, const operand* operands) -> u8;
		static auto get_instruction_vvvv(const instruction* inst, const operand* operands) -> u8;
		static auto get_instruction_v(const instruction* inst, const operand* operands) -> u8;

		// registers
		static auto get_extending_reg(const instruction* inst, const operand* operands) -> u8;
		static auto get_modrm_reg(const instruction* inst, const operand* operands) -> u8;
		static auto get_modrm_rm(const instruction* inst, const operand* operands) -> u8;
		static auto get_sib_index(const instruction* inst, const operand* operands) -> u8;
		static auto get_mask_reg(const instruction* inst, const operand* operands) -> u8;

		static auto has_sib(const operand* operands) -> bool;
		static void push_byte(u8 value);
	private:
		static u8 m_data_size;
		static u8 m_data[15];
	};
} // baremetal

