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


	struct relocation {
		utility::string_view* symbol;
		u64 position;
		u8 size;
	};

	enum fixup_type : u8 {
		FIXUP_DISPLACEMENT // memory base fixup
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
		fixup_type fixup;
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
		bool is_empty = false; // whether the section contains any data
		u64 position = 0;      // position of the entire section within the binary
		u64 offset = 0;        // local instruction offset

		// list of subsections which is concatenated during emission
		utility::dynamic_array<subsection> subsections; 
		// list of instructions with unresolved operands, subset of 'subsections'
		utility::dynamic_array<unresolved_subsection> unresolved; 
		// symbol table, location of every symbol is relative to the respective section
		utility::map<utility::string_view*, u64> symbols;
	};

	class frontend {
	public:
		struct module {
			utility::dynamic_array<u8> bytes;	
		};

		frontend();

		auto assemble(const utility::dynamic_string& source) -> utility::result<frontend::module>;
	private:
		auto emit_module() -> utility::result<frontend::module>;
		auto resolve_symbols() -> utility::result<void>;
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

		void set_section(utility::string_view* name);
		void create_normal_subsection();
		auto get_symbol_global(utility::string_view* name) -> u64;
		auto get_symbol_local(utility::string_view* name) -> u64;
		void assemble_instruction(const instruction* inst);
	private:
		context m_context;
		lexer m_lexer;

		// parsing
		utility::string_view* m_current_identifier;

		// instruction parsing
		u32 m_instruction_i;
		operand m_operands[4];
		bool m_symbolic_operand;
		u8 m_broadcast_n;
		u8 m_operand_i;
		u8 m_unresolved_index;
		fixup_type m_fixup;

		// temporary array with bytes representing resolved instructions
		utility::dynamic_array<u8> m_current_resolved;

		// sections
		utility::dynamic_array<section> m_sections;
		u64 m_section_index;

		module_t m_module;
	};
} // namespace baremetal::assembler

