#pragma once
#include "assembler/assembler.h"
#include "assembler/lexer.h"

#include <utility/result.h>

namespace baremetal {
	namespace detail {
		auto is_operand_match(u32 inst_i, operand* operands) -> bool;
		auto imm_to_scale(const imm& i) -> utility::result<scale>;
		auto inst_match(operand_type a, operand b) -> bool;
	} // namespace detail

	struct assembler_parser {
		assembler_parser();
		
		auto parse(const utility::dynamic_string& assembly) -> utility::result<void>; 

		[[nodiscard]] auto get_bytes() const -> const utility::dynamic_array<u8>&;
		void clear();
	private:
		auto parse_instruction() -> utility::result<void>;

		// operands
		auto parse_number_negative() -> utility::result<void>;
		auto parse_register() -> utility::result<void>;
		auto parse_bracket() -> utility::result<void>;
		auto parse_memory() -> utility::result<void>;
		
		void parse_number();

		auto parse_mask_register(operand& op) -> utility::result<bool>;
		auto parse_memory(mem& memory) -> utility::result<void>;
	private:
		assembler m_assembler;
		lexer m_lexer;

		utility::dynamic_string m_assembly;

		operand operands[4];
		u8 operand_i = 0;
	};
} // namespace baremetal

