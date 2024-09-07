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
		auto assemble_instruction() -> bool;

		auto parse_memory(mem& memory) -> bool;
		auto parse_mask_reg(operand& operand) -> bool;
	private:
		module m_module;
		lexer m_lexer;

		utility::dynamic_string m_assembly;
	};
} // namespace baremetal

