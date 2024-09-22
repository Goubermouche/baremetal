#pragma once
#include "assembler/instruction/operands/operands.h"
#include "assembler/assembler_lexer.h"
#include "assembler/context.h"

#include <utility/containers/dynamic_string.h>
#include <utility/result.h>

namespace baremetal {
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

	class assembler {
	public:
		struct module {
			utility::dynamic_array<u8> bytes;	
		};

		auto assemble(const utility::dynamic_string& source) -> utility::result<assembler::module>;
	private:
		auto tokenize(const utility::dynamic_string& source) -> utility::result<void>;
		auto emit_module() -> utility::result<assembler::module>;
		auto resolve_symbols() -> utility::result<void>;
		auto parse() -> utility::result<void>;

		// parsing
		auto parse_instruction() -> utility::result<void>;
		auto parse_identifier() -> utility::result<void>;
		auto parse_label() -> utility::result<void>;
		auto parse_times() -> utility::result<void>;
		auto parse_bits() -> utility::result<void>;
		
		auto parse_identifier_operand() -> utility::result<void>;
		auto get_next_token() -> token;
	private:
		void recalculate_symbol_positions(u64 position, i32 diff);
		void create_normal_subsection();
	private:
		assembler_context m_context;

		// parsing
		utility::string_view* m_current_identifier;
		token_buffer m_tokens;
		token m_current_token;
		u64 m_token_index;

		// instruction parsing
		operand m_operands[4];
		bool m_symbolic_operand;
		u8 m_operand_i;

		// symbol table
		utility::map<utility::string_view*, u64> m_symbols;

		// list of instructions with unresolved operands
		utility::dynamic_array<unresolved_subsection> m_unresolved; 

		// temporary array with bytes representing resolved instructions
		utility::dynamic_array<u8> m_current_resolved;

		// list of subsections which is concatenated during emission
		utility::dynamic_array<subsection> m_subsections; 

		u64 m_instruction_offset = 0;
	};
} // namespace baremetal


