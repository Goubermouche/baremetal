#pragma once
#include <utility/containers/dynamic_array.h>
#include <utility/containers/dynamic_string.h>

namespace baremetal {
	using namespace utility::types;

	struct module {
		struct section {
			section(const char* name);

			utility::dynamic_array<u8> data;
			const char* name;
		};

		module();
		
		void clear();
		void push_byte(u8 value);

		void set_section(const char* name);
		void add_section(const char* name);

		auto emit_binary() const -> utility::dynamic_array<u8>;

		auto get_size() const -> u64;
	private:
		// sections[0] = .text
		// sections[1] = .data
		// sections    = user defined sections
		utility::dynamic_array<section> m_sections;
		u64 m_current_section;
		u64 m_byte_count;
	};
} // namespace baremetal

