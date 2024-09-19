#pragma once
#include "assembler/string_interner.h"

namespace baremetal {
	using namespace utility::types;

	struct module {
		enum symbol_type : u8 {
			SYM_NONE = 0,
			SYM_GLOBAL,
			SYM_RELATIVE
		};

		struct symbol {
			symbol_type type;
			u64 position;
		};

		struct relocation {
			utility::string_view* symbol;
			u64 position;
			u8 size;
			u8 inst_len;
		};

		struct section {
			section(utility::string_view* name);

			utility::map<utility::string_view*, symbol> symbols;
			utility::dynamic_array<relocation> relocations;
			utility::dynamic_array<u8> data;
			utility::string_view* name;
		};

		module(string_interner* strings);
		
		void push_byte(u8 value);
		void clear();

		void set_section(utility::string_view* name);

		void add_relocation(utility::string_view* symbol, u8 size, u8 inst_len);
		void add_section(utility::string_view* name);
		void add_symbol(utility::string_view* name, symbol_type type);

		auto emit_binary() const -> utility::dynamic_array<u8>;

		auto get_symbol(utility::string_view* name) const -> symbol;
		auto get_size_current_section() const -> u64;
		auto get_current_section() const -> u64;
		auto get_size() const -> u64;
	private:
		string_interner* m_strings;

		// sections[0] = .text
		// sections[1] = .data
		// sections    = user defined sections
		utility::dynamic_array<section> m_sections;
		u64 m_current_section;
		u64 m_byte_count;
	};
} // namespace baremetal

