#pragma once
#include "assembler/instruction/instruction.h"
#include "assembler/ir/module.h"
#include "assembler/lexer.h"

namespace baremetal::assembler {
	namespace detail {
		auto mask_operand(operand_type op, mask_type mask) -> utility::result<operand_type>; 
		auto imm_to_scale(const imm& i) -> utility::result<scale>;

		auto is_operand_match(operand_type a, operand b) -> bool;
		auto is_operand_match(const instruction& inst, operand* operands, u8 broadcast_n, u8 count) -> bool;
	} // namespace detail

	class frontend {
	public:
		frontend();

		auto assemble(const utility::dynamic_string& source) -> utility::result<utility::dynamic_array<u8>>;
	private:
		auto parse() -> utility::result<void>;

		// parsing
		auto parse_reserve_memory() -> utility::result<void>;
		auto parse_define_memory() -> utility::result<void>;
		auto parse_instruction() -> utility::result<void>;
		auto parse_identifier() -> utility::result<void>;
		auto parse_section() -> utility::result<void>;
		auto parse_label() -> utility::result<void>;
		auto parse_times() -> utility::result<void>;
		auto parse_bits() -> utility::result<void>;
	
		auto parse_broadcast_operand(mask_type mask) -> utility::result<void>;
		auto parse_memory_operand(data_type type) -> utility::result<void>;
		auto parse_moff_operand(data_type type) -> utility::result<void>;
		auto parse_identifier_operand() -> utility::result<void>;
		auto parse_immediate_operand() -> utility::result<void>;
		auto parse_register_operand() -> utility::result<void>;
		auto parse_rip_rel_operand() -> utility::result<void>;
		auto parse_type_operand() -> utility::result<void>;
		auto parse_operand_char() -> utility::result<void>;

		auto parse_mask_or_broadcast() -> utility::result<mask_type>; 
		auto parse_memory(operand& op) -> utility::result<void>;

		void assemble_instruction(const instruction* inst);
	private:
		context m_context;
		module m_module;
		lexer m_lexer;

		// parsing
		utility::string_view* m_current_identifier;

		// instruction parsing
		u32 m_instruction_i;
		operand m_operands[4];
		u8 m_broadcast_n;
		u8 m_operand_i;
		u8 m_unresolved_index;
	};
} // namespace baremetal::assembler

