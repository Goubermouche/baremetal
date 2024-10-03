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
	} // namespace detail
	
	class assembler_backend {
	public:
		assembler_backend(assembler_context* context);

		void clear();
		[[nodiscard]] auto get_bytes() const -> utility::dynamic_array<u8>;

		static auto find_direct(u32 index, const operand* operands) -> const instruction*;
		static auto get_instruction_size(u32 index, const operand* operands) -> u8;

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
		static auto is_legal_variant_unknown(u32 a, u32 b, u8 imm_index) -> bool;
	private:
		u64 m_current_inst_begin;
		u8 m_reg_count;
		u8 m_regs[4];

		module m_module;	
	};
} // namespace baremetal

