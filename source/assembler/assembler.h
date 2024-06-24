#pragma once
#include "assembler/block.h"

namespace baremetal {
	struct assembler {
		assembler();

#define INST(index, name, op1, op2)                      \
  void name(struct op1 destination, struct op2 source) { \
    emit_instruction(index, destination, source);        \
  }

 #include "assembler/instruction/databases/assembler_database.inc"

#undef INST
		[[nodiscard]] auto get_bytes() const -> const utility::dynamic_array<utility::byte>&;

		void clear();
	private:
		static auto find_rex_pair(const operand* operands) -> std::pair<u8, u8>;

		static auto get_instruction_info(u32 index, operand op_1, operand op_2) -> const instruction_info*;

		void emit_instruction_prefix(const instruction_info* inst);
		void emit_instruction_opcode(const instruction_info* inst, operand op_1, operand op_2);
		void emit_instruction_modrm(const instruction_info* inst, operand op_1, operand op_2);
		void emit_instruction_sib(operand op_1, operand op_2);
		void emit_immediate_operand(u64 imm, enum operand::type type);

		void emit_instruction(u32 index, operand op_1, operand op_2);

		static auto has_sib_byte(operand op_1, operand op_2) -> bool;

		enum mod_mode {
			INDIRECT,
			INDIRECT_DISP8,
			INDIRECT_DISP32,
			DIRECT
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
		utility::dynamic_array<utility::byte> m_bytes;
		u64 m_current_inst_begin;
	};
} // namespace baremetal
