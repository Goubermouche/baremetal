#pragma once
#include "assembler/instruction/operands/operands.h"
#include "assembler/assembler_lexer.h"
#include "assembler/context.h"
#include "utility/containers/string_view.h"

#include <utility/containers/dynamic_string.h>
#include <utility/result.h>

namespace baremetal {
	// enum symbol_type : u8 {
	// 	SYM_RIP_RELATIVE,
	// 	SYM_GLOBAL
	// };

	// struct symbol {
	// 	u64 position;
	// 	symbol_type type;
	// };

	struct relocation {
		utility::string_view* symbol;
		u64 position;
		u8 size;
	};

	struct unresolved_subsection {
		// instruction
		u32 index;           // refers to the fist valid instruction variant in the instruction database
		operand operands[4]; // operands extracted by the parser
		u8 operand_count;

		// updated by the resolve_symbols() function, on creation it should contain the pessimistic
		// (worst case) values, ie. the longest possbile encoding
		u64 position; // current position of the instruction
		u8 size;      // current size of the instruction

		utility::dynamic_array<operand_type> variants; // valid variants of the provided instruction;
		u8 unresolved_operand;                         // index of the unresolved operand
	};

	enum subsection_type : u8 {
		SS_NONE = 0,
		SS_NORMAL,
		SS_FIXUP
	};

	struct subsection {
		subsection_type type;

		union {
			struct {
				u8* data;
				u64 size;	
			} resolved;     // regular section, with assembled code
			u64 unresolved; // index into m_unresolved, references an instrucion with unresolved operands
		};
	};

	struct section {
		void update_positions(u64 position, i32 diff);

		utility::string_view* name;
		u64 position = 0; // position of the entire section within the binary
		u64 offset = 0;   // local instruction offset

		// list of subsections which is concatenated during emission
		utility::dynamic_array<subsection> subsections; 
		// list of instructions with unresolved operands, subset of 'subsections'
		utility::dynamic_array<unresolved_subsection> unresolved; 
		// symbol table, location of every symbol is relative to the respective section
		utility::map<utility::string_view*, u64> symbols;
	};

	class assembler {
	public:
		struct module {
			utility::dynamic_array<u8> bytes;	
		};

		assembler();

		auto assemble(const utility::dynamic_string& source) -> utility::result<assembler::module>;
	private:
		auto tokenize(const utility::dynamic_string& source) -> utility::result<void>;
		auto emit_module() -> utility::result<assembler::module>;
		auto resolve_symbols() -> utility::result<void>;
		auto parse() -> utility::result<void>;

		// parsing
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

		auto parse_mask_or_broadcast() -> utility::result<mask_type>; 
		auto parse_memory(operand& op) -> utility::result<void>;
		auto get_next_token() -> token;
	private:
		void set_section(utility::string_view* name);
		void create_normal_subsection();
		auto get_symbol_global(utility::string_view* name) -> u64;
		auto get_symbol_local(utility::string_view* name) -> u64;
	private:
		assembler_context m_context;

		// parsing
		utility::string_view* m_current_identifier;
		token_buffer m_tokens;
		token m_current_token;
		u64 m_token_index;

		// instruction parsing
		u32 m_instruction_i;
		operand m_operands[4];
		bool m_symbolic_operand;
		u8 m_broadcast_n;
		u8 m_operand_i;

		// temporary array with bytes representing resolved instructions
		utility::dynamic_array<u8> m_current_resolved;

		// sections
		utility::dynamic_array<section> m_sections;
		u64 m_section_index;
	};
} // namespace baremetal

