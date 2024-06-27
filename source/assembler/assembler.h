#pragma once
#include "assembler/block.h"

namespace baremetal {
	struct assembler {
		assembler();

// function generators
#define INST_0(index, name)                              \
  void name() {                                          \
    emit_instruction(index, operand(), operand());       \
  }

#define INST_1(index, name, op1)                         \
  void name(struct op1 destination) {                    \
    emit_instruction(index, destination, operand());     \
  }

#define INST_2(index, name, op1, op2)                    \
  void name(struct op1 destination, struct op2 source) { \
    emit_instruction(index, destination, source);        \
  }

// select which INST_X to call based off of the variable argument count (0-2)
#define INST_SELECT(count) CONCATENATE(INST_, count)
#define INST_HELPER(count, name, ...) EXPAND(INST_SELECT(count)(name, __VA_ARGS__))
#define INST(index, name, ...) INST_HELPER(GET_ARG_COUNT(__VA_ARGS__), index, name, __VA_ARGS__)

// assembler database
#include "assembler/instruction/databases/assembler_database.inc"

#undef INST_0
#undef INST_1
#undef INST_2
#undef INST_3

#undef INST_SELECT
#undef INST_HELPER

#undef INST

		[[nodiscard]] auto get_bytes() const -> const utility::dynamic_array<utility::byte>&;

		void clear();
	private:
		void emit_instruction(u32 index, const operand& op_1, const operand& op_2);

		// opcode
		void emit_instruction_opcode(const instruction_info* inst, const operand& op_1, const operand& op_2);
		void emit_instruction_mod_rm(const instruction_info* inst, const operand& op_1, const operand& op_2);
		void emit_instruction_sib(const operand& op_1, const operand& op_2);
		void emit_instruction_prefix(const instruction_info* inst);

		void emit_operands(const operand* operands, u8 operand_count, const instruction_info* inst);
		void emit_data_operand(u64 data, u8 bit_width);
		void emit_opcode_mem(const mem& memory);

		static auto find_rex_pair(const operand* operands) -> std::pair<u8, u8>;
		static auto find_instruction_info(u32 index, const operand& op_1, const operand& op_2) -> const instruction_info*;

		static auto has_sib_byte(const operand& op_1, const operand& op_2) -> bool;

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

	/**
	 * \brief Checks if \b value can be represented by \b src sign-extended bits in \b dst bits.
	 * \param value Immediate value to check
	 * \param original Bit width of the value we're checking
	 * \param dst Destination bit width
	 * \param src Source bit width
	 * \return True if the value is sign-representable in the specified environment, false otherwise.
	 */
	auto signed_extend_representable(u64 value, u8 original, u8 dst, u8 src) -> bool;

	auto is_operand_of_same_kind(enum operand::type a, enum operand::type b) -> bool;
} // namespace baremetal
