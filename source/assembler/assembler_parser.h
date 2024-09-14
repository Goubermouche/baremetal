#pragma once
#include "assembler/assembler.h"
#include "assembler/lexer.h"

#include <utility/result.h>

namespace baremetal {
	namespace detail {
		auto is_operand_match(const instruction& inst, operand* operands, u8 broadcast_n, u8 count) -> bool;
		auto imm_to_scale(const imm& i) -> utility::result<scale>;
		auto inst_match(operand_type a, operand b) -> bool;
		auto mask_operand(operand_type op, mask_type mask) -> utility::result<operand_type>;
	} // namespace detail

	struct assembler_parser {
		assembler_parser();
		
		auto parse(const utility::dynamic_string& assembly) -> utility::result<void>; 

		[[nodiscard]] auto get_bytes() const -> const utility::dynamic_array<u8>&;
		void clear();
	private:
		// instructions
		auto parse_instruction() -> utility::result<void>;

		// operands
		auto parse_broadcast(mask_type mask) -> utility::result<void>;
		auto parse_memory(data_type type) -> utility::result<void>;
		auto parse_moff(data_type type) -> utility::result<void>;
		auto parse_rip_relative_rel() -> utility::result<void>;
		auto parse_number_negative() -> utility::result<void>;
		auto parse_register() -> utility::result<void>;
		auto parse_type() -> utility::result<void>;
		void parse_number();

		auto parse_mask_or_broadcast() -> utility::result<mask_type>;
		auto parse_memory(operand& op) -> utility::result<void>;
	private:
		utility::dynamic_string m_assembly;
		assembler m_assembler;
		lexer m_lexer;

		// instruction context
		u32 m_instruction_i; // best guess for the current instruction index
		operand m_operands[4];
		u8 m_operand_i = 0;
		u8 m_broadcast_n;
	};
} // namespace baremetal

