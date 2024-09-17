#pragma once
#include <utility/containers/dynamic_array.h>
#include <utility/containers/string_view.h>
#include <utility/containers/map.h>

namespace baremetal {
	using namespace utility::types;

	struct module {
		struct relocation {
			utility::string_view symbol;
			u64 position;
			u8 size;
		};

		struct section {
			section(const char* name);

			utility::map<utility::string_view, u64> symbols;
			utility::dynamic_array<relocation> relocations;
			utility::dynamic_array<u8> data;

			const char* name;
		};

		module();
		
		void clear();
		void push_byte(u8 value);

		void set_section(const char* name);

		void add_symbol(utility::string_view name);
		void add_relocation(utility::string_view symbol, u8 size);
		void add_section(const char* name);

		auto emit_binary() const -> utility::dynamic_array<u8>;

		auto get_size() const -> u64;
		auto get_size_current_section() const -> u64;
	private:
		// sections[0] = .text
		// sections[1] = .data
		// sections    = user defined sections
		utility::dynamic_array<section> m_sections;
		u64 m_current_section;
		u64 m_byte_count;
	};
} // namespace baremetal

