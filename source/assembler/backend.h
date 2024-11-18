#pragma once
#include "assembler/instruction/instruction.h"

#include <utility/containers/dynamic_array.h>

namespace baremetal::assembler {
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

		/**
		 * \brief Checks if \b value can be represented by \b src sign-extended bits in \b dst bits.
		 * \param value Immediate value to check
		 * \param src Source bit width
		 * \return True if the value is sign-representable in the specified environment, false otherwise.
		 */
		auto sign_extend_representable(u64 value, u8 src) -> bool;
		auto sign_extend(u64 x, u8 x_bits) -> u64;
	} // namespace detail

	using namespace utility::types;

	struct inst_variant {
		operand_type type;
		u32 index;
	};

	struct backend {
		struct code {
			u8* data;
			u8 size;
		};

		static auto get_instruction_by_name(const char* name) -> u32;
		static auto get_variants(u32 index, const operand* operands) -> utility::dynamic_array<operand_type>;
		static auto get_variants_i(u32 index, const operand* operands) -> utility::dynamic_array<inst_variant>;

		static auto emit_instruction(const instruction* inst, const operand* operands) -> code;
		static auto emit_instruction(u32 index, const operand* operands) -> code;
	private:
		// instruction selection
		static auto get_instruction_direct(u32 index, const operand* operands) -> const instruction*;

		// instruction parts
		static void emit_instruction_prefix();
		static void emit_instruction_opcode();
		static void emit_instruction_mod_rm();
		static void emit_instruction_sib();
		static void emit_instruction_operands();

		// instruction prefixes
		static void emit_opcode_prefix_evex();
		static void emit_opcode_prefix_vex();
		static void emit_opcode_prefix_rex();

		// misc
		static void emit_opcode_prefix_vex_two();
		static void emit_opcode_prefix_vex_three();

		static void emit_opcode_prefix_rex_mem(const mem& memory);
		static void emit_data_operand(u64 data, u16 bit_width);
		
		static auto get_instruction_vvvv() -> u8;
		static auto get_instruction_rex() -> u8;
		static auto get_instruction_v() -> u8;

		// registers
		static auto get_extending_reg() -> u8;
		static auto get_sib_index() -> u8;
		static auto get_modrm_reg() -> u8;
		static auto get_modrm_rm() -> u8;
		static auto get_mask_reg() -> u8;

		static auto has_sib() -> bool;
		static void push_byte(u8 value);
	private:
		static const instruction* m_inst;
		static const operand* m_operands;

		static u8 m_data_size;
		static u8 m_data[MAX_INSTRUCTION_SIZE];
	};

	auto is_jump_or_branch_inst(u32 index) -> bool;
	auto is_legal_operand_variant(operand_type a, operand_type b) -> bool;
	auto is_legal_variant(u32 a, u32 b, u8 operand_index) -> bool;
} // baremetal::assembler 

