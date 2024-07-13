#pragma once
#include "assembler/block.h"

namespace baremetal {
	struct assembler {
		assembler();

// function generators
#define INST_0(index, name)                  \
  void name() {                              \
    emit_instruction(index, {}, {}, {}, {}); \
  }

#define INST_1(index, name, op1)                      \
  void name(struct op1 destination) {                 \
    emit_instruction(index, destination, {}, {}, {}); \
  }

#define INST_2(index, name, op1, op2)                     \
  void name(struct op1 destination, struct op2 source) {  \
    emit_instruction(index, destination, source, {}, {}); \
  }

#define INST_3(index, name, op1, op2, op3)              \
  void name(struct op1 a, struct op2 b, struct op3 c) { \
    emit_instruction(index, a, b, c, {});               \
  }

#define INST_4(index, name, op1, op2, op3,  op4)                       \
  void name(struct op1 a, struct op2 b, struct op3 c, struct op4 d) {  \
    emit_instruction(index, a, b, c, d);                               \
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
#undef INST_4

#undef INST_SELECT
#undef INST_HELPER

#undef INST

		[[nodiscard]] auto get_bytes() const -> const utility::dynamic_array<u8>&;

		void clear();
	private:
		void emit_instruction(u32 index, const operand& op1, const operand& op2, const operand& op3, const operand& op4);

		// opcode
		void emit_instruction_opcode(const instruction* inst, const operand* operands);
		void emit_instruction_mod_rm(const instruction* inst, const operand* operands);
		void emit_instruction_prefix(const instruction* inst);
		void emit_instruction_sib(const operand* operands);

		// opcode prefixes
		void emit_opcode_prefix_rex(const instruction* inst, const operand* operands);
		void emit_opcode_prefix_vex(const instruction* inst, const operand* operands);

		void emit_opcode_prefix_rex_mem(const mem& memory);

		// operands
		void emit_operands(const instruction* inst, const operand* operands);
		void emit_data_operand(u64 data, u16 bit_width);

		static auto find_rex_pair(const instruction* inst, const operand* operands) -> std::pair<u8, u8>;
		static auto find_instruction_info(u32 index, const operand* operands) -> const instruction*;

		static auto is_legal_variant(u32 a, u32 b, u8 imm_index) -> bool;
		static auto has_sib_byte(const operand* operands) -> bool;

		static auto get_instruction_rex(const instruction* inst, const operand* operands) -> u8;

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
