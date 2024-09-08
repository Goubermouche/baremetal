#pragma once
#include "assembler/instruction/instruction.h"

#include <utility/containers/dynamic_string.h>
#include <utility/containers/dynamic_array.h>

namespace baremetal {
	namespace detail {
		/**
		 * \brief Checks if \b value can be represented by \b src sign-extended bits in \b dst bits.
		 * \param value Immediate value to check
		 * \param src Source bit width
		 * \return True if the value is sign-representable in the specified environment, false otherwise.
		 */
		auto sign_extend_representable(u64 value, u8 src) -> bool;
		auto sign_extend(u64 x, u8 x_bits) -> u64;
	
		auto is_operand_of_same_kind(operand_type a, operand_type b) -> bool;
		auto extract_operand_reg_beg(const operand& op) -> u8;
		auto extract_operand_reg(const operand& op) -> u8;
	} // namespace detail
	
	class assembler {
	public:
		assembler();

		void clear();
		[[nodiscard]] auto get_bytes() const -> const utility::dynamic_array<u8>&;

		void emit_instruction(u32 index, const operand* operands);
		void emit_instruction_prefix(const instruction* inst);
		void emit_instruction_opcode(const instruction* inst, const operand* operands);
		void emit_instruction_mod_rm(const instruction* inst, const operand* operands);
		void emit_instruction_sib(const operand* operands);
		void emit_operands(const instruction* inst, const operand* operands);

		auto find_instruction_info(u32 index, const operand* operands) -> const instruction*;
		auto is_legal_variant(u32 a, u32 b, u8 imm_index) -> bool;
		void emit_data_operand(u64 data, u16 bit_width);

		// opcode prefixes
		void emit_opcode_prefix_rex(const instruction* inst, const operand* operands);
		void emit_opcode_prefix_vex(const instruction* inst, const operand* operands);
		void emit_opcode_prefix_evex(const instruction* inst, const operand* operands);

		void emit_opcode_prefix_vex_three(const instruction* inst, const operand* operands);
		void emit_opcode_prefix_vex_two(const instruction* inst, const operand* operands);

		void emit_opcode_prefix_rex_mem(const mem& memory);

		// rex
		auto get_instruction_rex(const instruction* inst, const operand* operands) -> u8;

		auto get_instruction_rex_rex(const instruction* inst, const operand* operands) -> u8;
		auto get_instruction_rex_vex(const instruction* inst, const operand* operands) -> u8;
		auto get_instruction_rex_evex(const instruction* inst, const operand* operands) -> u8;

		// other
		auto get_mod_rm_reg(const instruction* inst, const operand* operands) -> u8;
		auto has_sib_byte(const operand* operands) -> bool;

		auto get_instruction_vvvv(const instruction* inst, const operand* operands) -> u8;
		auto get_instruction_v(const instruction* inst, const operand* operands) -> u8;
		auto get_instruction_map_select(const instruction* inst) -> u8;
		auto get_instruction_imp(const instruction* inst) -> u8;
		auto get_instruction_l(const instruction* inst) -> bool;

		enum mod_mode : u8 {
			INDIRECT        = 0b00,
			INDIRECT_DISP8  = 0b01,
			INDIRECT_DISP32 = 0b10,
			DIRECT          = 0b11
		};

		static auto mod_rx_rm(u8 mod, u8 rx, u8 rm) -> u8;
		static auto sib(u8 scale, u8 index, u8 base) -> u8;
		static auto rex(bool w, u8 rx, u8 base, u8 index) -> u8;

		static auto direct(u8 rx, u8 reg) -> u8;
		static auto indirect(u8 rx, u8 base) -> u8;
		static auto indirect_disp_8(u8 rx, u8 base) -> u8;
		static auto indirect_disp_32(u8 rx, u8 base) -> u8;

		void instruction_begin(const instruction* inst, const operand* operands);
		auto get_current_inst_size() const -> u8;
	private:
		u8 m_reg_count;
		u8 m_regs[4];

		utility::dynamic_array<u8> m_bytes;
		u64 m_current_inst_begin;
	};
} // namespace baremetal

