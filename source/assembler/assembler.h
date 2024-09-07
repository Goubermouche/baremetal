#pragma once
#include "assembler/module.h"
#include "assembler/parser.h"

namespace baremetal {
	struct assembler {
		assembler();
		
		auto assemble(const utility::dynamic_string& assembly) -> bool; 

		[[nodiscard]] auto get_bytes() const -> const utility::dynamic_array<u8>&;
		void clear();
	private:
		auto parse_instruction() -> bool;

		// operands
		void parse_number_negative();
		void parse_register();
		void parse_bracket();
		void parse_number();
		void parse_memory();
		
		auto parse_mask_register(operand& op) -> bool;
		auto parse_memory(mem& memory) -> bool;
	private:
		module m_module;
		lexer m_lexer;

		utility::dynamic_string m_assembly;

		operand operands[4];
		u8 operand_i = 0;
	};
} // namespace baremetal

