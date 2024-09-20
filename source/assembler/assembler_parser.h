#pragma once
#include "assembler/assembler_backend.h"
#include "assembler/lexer.h"

#include <utility/allocators/block_allocator.h>
#include <utility/result.h>

namespace baremetal {
	namespace detail {
		auto is_operand_match(const instruction& inst, operand* operands, u8 broadcast_n, u8 count) -> bool;
		auto mask_operand(operand_type op, mask_type mask) -> utility::result<operand_type>;
		auto imm_to_scale(const imm& i) -> utility::result<scale>;
		auto inst_match(operand_type a, operand b) -> bool;
	} // namespace detail

	struct assembler_parser {
		assembler_parser(assembler_context* context);
		
		auto parse(const utility::dynamic_string& assembly) -> utility::result<void>; 

		[[nodiscard]] auto get_bytes() const -> utility::dynamic_array<u8>;
		void clear();
	private:
		// statements
		auto parse_reserve_memory(utility::string_view* symbol) -> utility::result<void>;
		auto parse_define_memory(utility::string_view* symbol) -> utility::result<void>;
		auto parse_instruction() -> utility::result<void>;
		auto parse_identifier() -> utility::result<void>;
		auto parse_section() -> utility::result<void>;
		auto parse_label() -> utility::result<void>;
		auto parse_times() -> utility::result<void>;
		auto parse_bits() -> utility::result<void>;

		// instruction operands
		auto parse_broadcast(mask_type mask) -> utility::result<void>;
		auto parse_memory(data_type type) -> utility::result<void>;
		auto parse_moff(data_type type) -> utility::result<void>;
		auto parse_identifier_operand() -> utility::result<void>;
		auto parse_rip_relative_rel() -> utility::result<void>;
		auto parse_number_negative() -> utility::result<void>;
		auto parse_register() -> utility::result<void>;
		auto parse_number() -> utility::result<void>;
		auto parse_type() -> utility::result<void>;

		// instruction operand parts
		auto parse_mask_or_broadcast() -> utility::result<mask_type>;
		auto parse_memory(operand& op) -> utility::result<void>;
	private:
		assembler_context* m_context;	
		assembler_backend m_backend;
		assembler_lexer m_lexer;

		// parser context
		utility::string_view* m_current_identifier;

		// instruction operands
		operand m_operands[4];
		u8 m_operand_i;

		bool m_relocated_operand; // specifies whether the current instruction has a relocated operand
		u32 m_instruction_i;      // best guess for the current instruction index
		u8 m_broadcast_n;         // broadcast N, if applicable
	};
} // namespace baremetal

