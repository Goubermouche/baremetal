#pragma once
#include "assembler/context.h"

namespace baremetal {
	using namespace utility::types;

	struct module {
		enum symbol_type : u8 {
			SYM_NONE = 0, // invalid symbol
			SYM_GLOBAL,   // symbols which can be addressed by a global constant (ie. a memory location)
			SYM_RELATIVE  // symbols which are typically reffered to by rip-relative operands
		};

		struct symbol {
			symbol(symbol_type type, u64 position);
			symbol() = default;

			symbol_type type;             // symbol type
			u64 position;                 // symbol location (relative to the parent section)
		};

		struct relocation {
			relocation(utility::string_view* symbol, u64 position, u8 size);

			utility::string_view* symbol; // relocation target
			u64 position;                 // position of the relocation patch
			u8 size;                      // size of the relocation patch (bytes)
		};

		struct section {
			section(utility::string_view* name);


			utility::map<utility::string_view*, symbol> symbols;
			utility::dynamic_array<relocation> relocations;
			utility::dynamic_array<u8> data;
			utility::string_view* name;
		};

		module(assembler_context* context);
		
		// emission
		auto emit_object_elf() const -> utility::dynamic_array<u8>;
		auto emit_binary() const -> utility::dynamic_array<u8>;

		// symbols
		void add_symbol(utility::string_view* name, symbol_type type);
		auto get_symbol(utility::string_view* name) const -> symbol;

		void add_relocation(utility::string_view* symbol, u8 size);
 
		// sections
		void set_section(utility::string_view* name);

		// other
		auto get_size_current_section() const -> u64;
		auto get_current_section() const -> u64;
		auto get_size() const -> u64;
		void push_byte(u8 value);
		void clear();
	private:
		void add_section(utility::string_view* name);
	private:
		utility::dynamic_array<section> m_sections;
		u64 m_current_section;
		u64 m_byte_count;

		assembler_context* m_context;
	};
} // namespace baremetal

