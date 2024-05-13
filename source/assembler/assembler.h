#pragma once
#include "assembler/block.h"

namespace baremetal {
	struct assembler {
		assembler();

		void mov(gpr_reg destination, gpr_reg source);

		void mov(gpr_reg destination, byte immediate);
		void mov(gpr_reg destination, dword immediate);

		void neg(gpr_reg destination);

		void jmp(u64 block);

		auto create_block() -> u64;
		auto get_current_block() const -> u64;
		void set_current_block(u64 block);

		void emit();
	private:
		static void emit_instruction(const instruction& instruction);

		enum mod_mode {
			INDIRECT,
			INDIRECT_DISP8,
			INDIRECT_DISP32,
			DIRECT
		};

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
	private:
		// list of blocks where the current block is the index of the active block. each
		// block holds a list of instructions which it contains
		dynamic_array<block> m_blocks;
		u64 m_current_block;

		dynamic_array<relocation> m_relocations;
	};
} // namespace baremetal
