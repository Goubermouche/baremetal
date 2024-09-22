#pragma once
#include "assembler/instruction/instruction.h"
#include "assembler/binary/module.h"

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
	} // namespace detail
	
	class assembler_backend {
	public:
		assembler_backend(assembler_context* context);

		void clear();
		[[nodiscard]] auto get_bytes() const -> utility::dynamic_array<u8>;

		static auto find_direct(u32 index, const operand* operands) -> const instruction*;

		void emit_instruction(u32 index, const operand* operands);
		void emit_instruction_direct(const instruction* inst, const operand* operands);

		void push_byte(u8 value);
		void push_data(u64 value, u8 count);
		auto get_module() -> module&;

		utility::dynamic_array<operand_type> current_variants;
	private:
		// instruction emission
		auto find_optimized_instruction(u32 index, const operand* operands) -> const instruction*;
		static auto is_legal_variant(u32 a, u32 b, u8 imm_index) -> bool;
		void emit_instruction_prefix(const instruction* inst);
		void instruction_begin(const operand* operands);

		// instruction opcodes
		void emit_instruction_opcode(const instruction* inst, const operand* operands);
		void emit_instruction_opcode_prefix(const instruction* inst, const operand* operands);

		// REX opcode prefix
		void emit_opcode_prefix_rex(const instruction* inst, const operand* operands);
		void emit_opcode_prefix_rex_mem(const mem& memory);

		// pretty much all other prefixes also need a REX prefix in some shape or form, these utility
		// functions are used for generating them
		// TODO: these are a mess, we need to fix them after we implement support for enough instructions
		auto get_instruction_rex_vex_xop(const instruction* inst, const operand* operands) -> u8;
		auto get_instruction_rex_evex(const instruction* inst, const operand* operands) -> u8;
		auto get_instruction_rex_rex(const instruction* inst, const operand* operands) -> u8;

		// VEX opcode prefix
		void emit_opcode_prefix_vex_three(const instruction* inst, const operand* operands);
		void emit_opcode_prefix_vex_two(const instruction* inst, const operand* operands);
		void emit_opcode_prefix_vex(const instruction* inst, const operand* operands);

		// EVEX opcode prefix
		void emit_opcode_prefix_evex(const instruction* inst, const operand* operands);

		// instruction MOD/RM
		// TODO: these are a mess, we need to fix them after we implement support for enough instructions
		void emit_instruction_mod_rm(const instruction* inst, const operand* operands);
		auto get_mod_rm_reg(const instruction* inst, const operand* operands) -> u8;

		// instruction SIB
		void emit_instruction_sib(const operand* operands);
		auto has_sib_byte(const operand* operands) -> bool;
	
		// instruction operands
		void emit_operands(const instruction* inst, const operand* operands);
		void emit_data_operand(u64 data, u16 bit_width);
		auto get_current_inst_size() const -> u8;

		// instruction prefix helpers
		auto get_instruction_vvvv(const instruction* inst, const operand* operands) -> u8;
		auto get_instruction_v(const instruction* inst, const operand* operands) -> u8;
		auto get_mask_register(const instruction* inst, const operand* operands) -> u8;
		auto get_instruction_map_select(const instruction* inst) -> u8;
		auto get_evex_operand_type(const instruction* inst) -> u8;
		auto get_instruction_imp(const instruction* inst) -> u8;
		auto get_instruction_l(const instruction* inst) -> bool;
		auto get_evex_zero(const instruction* inst) -> bool;
	private:
		u64 m_current_inst_begin;
		u8 m_reg_count;
		u8 m_regs[4];

		module m_module;	
	};
} // namespace baremetal

