#include "module.h"

namespace baremetal {
	module::module() {
		add_section("text");
		add_section("data");

		m_current_section = 0;
		m_byte_count = 0;
	}

	module::section::section(const char* name) : name(name) {}

	void module::clear() {
		// NOTE: doesn't clear user-declared sections
		for(section& s : m_sections) {
			s.data.clear();
		}	
	}

	void module::push_byte(u8 value) {
		m_sections[m_current_section].data.push_back(value);
		m_byte_count++;
	}

	void module::add_symbol(utility::string_view name) {
		m_sections[m_current_section].symbols[name] = m_sections[m_current_section].data.get_size();
	}

	void module::add_relocation(utility::string_view symbol, u8 size) {
		relocation r = { .symbol = symbol, .position = get_size_current_section(), .size = size };
		m_sections[m_current_section].relocations.push_back(r);
	}

	void module::add_section(const char* name) {
		m_sections.emplace_back(name);	
	}

	void module::set_section(const char* name) {
		// basic linear search for the next section, we don't really care about doing a linear search,
		// since there won't be many sections and this is a rarely called function
		for(u64 i = 0; i < m_sections.get_size(); ++i) {
			if(utility::compare_strings(name, m_sections[i].name) == 0) {
				m_current_section = i;
				return; 
			}
		}

		ASSERT(false, "unknown section '{}' specified\n", name);
	}

	auto module::emit_binary() const -> utility::dynamic_array<u8> {
		utility::map<utility::string_view, u64> symbols;
		utility::dynamic_array<relocation> relocations;
		utility::dynamic_array<u8> bytes;

		for(const section& s : m_sections) {
			if(s.data.is_empty()) {
				continue; // skip empty sections
			}

			// before appending the section, realign to 8 bytes
			const u64 alignment_offset = utility::align(bytes.get_size(), 4) - bytes.get_size(); 

			for(u64 i = 0; i < alignment_offset; ++i) {
				bytes.push_back(0);
			}

			// relocations
			for(relocation r : s.relocations) {
				r.position += bytes.get_size();
				relocations.push_back(r);
			}

			// symbols
			for(const auto& [symbol, position] : s.symbols) {
				symbols[symbol] = position + bytes.get_size();
			}

			// append the section
			bytes.insert(bytes.end(), s.data.begin(), s.data.end());
		}	

		// apply relocations
		for(const relocation& r : relocations) {
			const auto it = symbols.find(r.symbol);
			ASSERT(it != symbols.end(), "invalid symbol '{}' specified\n", r.symbol);
			utility::memcpy(bytes.get_data() + r.position, &it->second, r.size);
		}

		return bytes;
	}

	auto module::get_size() const -> u64 {
		return m_byte_count;
	}


	auto module::get_size_current_section() const -> u64 {
		return m_sections[m_current_section].data.get_size();
	}
} // namespace baremetal

