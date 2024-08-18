#pragma once
#include "assembler/instruction/instruction.h"
#include "assembler/parser.h"

#include <utility/containers/dynamic_string.h>
#include <utility/containers/dynamic_array.h>

namespace baremetal {
	struct assembler {
		assembler();

		[[nodiscard]] auto get_bytes() const -> const utility::dynamic_array<u8>&;
		
		void assemble(const utility::dynamic_string& assembly); 
		void clear();
	private:
		enum mem_parser_mode : u8 {
			MPM_NONE,
			MPM_SCALE,
		};
		// parsing
		auto assemble_instruction() -> bool;
		auto parse_memory(mem& memory) -> bool;
		auto find_instruction_by_name(const char* name) -> u32;

		void emit_instruction(u32 index, const operand& op1, const operand& op2, const operand& op3, const operand& op4);

		// opcode
		void emit_instruction_opcode(const instruction* inst, const operand* operands);
		void emit_instruction_mod_rm(const instruction* inst, const operand* operands);
		void emit_instruction_prefix(const instruction* inst);
		void emit_instruction_sib(const operand* operands);

		// opcode prefixes
		void emit_opcode_prefix_rex(const instruction* inst, const operand* operands);
		void emit_opcode_prefix_vex(const instruction* inst, const operand* operands);
		void emit_opcode_prefix_evex(const instruction* inst, const operand* operands);

		void emit_opcode_prefix_rex_mem(const mem& memory);

		// operands
		void emit_operands(const instruction* inst, const operand* operands);
		void emit_data_operand(u64 data, u16 bit_width);

		static auto find_rex_pair(const instruction* inst, const operand* operands) -> std::pair<u8, u8>;
		static auto find_instruction_info(u32 index, const operand* operands) -> const instruction*;

		static auto is_legal_variant(u32 a, u32 b, u8 imm_index) -> bool;
		static auto has_sib_byte(const operand* operands) -> bool;

		static auto get_instruction_rex(const instruction* inst, const operand* operands) -> u8;
		static auto get_instruction_rex_rex(const instruction* inst, const operand* operands) -> u8;
		static auto get_instruction_rex_vex(const instruction* inst, const operand* operands) -> u8;
		static auto get_instruction_rex_evex(const instruction* inst, const operand* operands) -> u8;

		static auto get_mod_rm_reg(const instruction* inst, const operand* operands) -> u8;

		enum mod_mode : u8 {
			INDIRECT        = 0b00,
			INDIRECT_DISP8  = 0b01,
			INDIRECT_DISP32 = 0b10,
			DIRECT          = 0b11
		};

		static auto sib(u8 scale, u8 index, u8 base) -> u8;

		/**
		 * \brief Computes the REX opcode byte.
		 * \param w REX.W bit (64 bit mode)
		 * \param rx Register register extension
		 * \param base Base register extension
		 * \param index Index register extension
		 * \return Computed REX opcode byte.
		 */
		static auto rex(bool w, u8 rx, u8 base, u8 index) -> u8;

		/**
		 * \brief Computes the mod R/M byte
		 * \param mod Addressing mode (INDIRECT, INDIRECT_DISP8, INDIRECT_DISP32, DIRECT)
		 * \param rx Opcode or register extension
		 * \param rm Register operand / displacement
		 * \return Computed mod R/M byte
		 */
		static auto mod_rx_rm(u8 mod, u8 rx, u8 rm) -> u8;

		static auto direct(u8 rx, u8 reg) -> u8;
		static auto indirect(u8 rx, u8 base) -> u8;
		static auto indirect_disp_8(u8 rx, u8 base) -> u8;
		static auto indirect_disp_32(u8 rx, u8 base) -> u8;

		void instruction_begin();
		auto get_current_inst_size() const -> u8;
	private:
		// parsing
		lexer m_lex;
		utility::dynamic_string m_assembly;
		u64 m_asm_i;

		utility::dynamic_array<u8> m_bytes;
		u64 m_current_inst_begin;
	};

	/**
	 * \brief Checks if \b value can be represented by \b src sign-extended bits in \b dst bits.
	 * \param value Immediate value to check
	 * \param src Source bit width
	 * \return True if the value is sign-representable in the specified environment, false otherwise.
	 */
	auto sign_extend_representable(u64 value, u8 src) -> bool;

	auto sign_extend(u64 x, u8 x_bits) -> u64;

	auto is_operand_of_same_kind(operand_type a, operand_type b) -> bool;
} // namespace baremetal

