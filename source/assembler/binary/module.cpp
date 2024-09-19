#include "module.h"

namespace baremetal {
	module::module(string_interner* strings) : m_strings(strings) {
		clear();
	}

	module::section::section(utility::string_view* name) : name(name) {}

	void module::clear() {
		m_sections.clear();

		m_current_section = 0;
		m_byte_count = 0;

		// only add the .text section by default
		add_section(m_strings->add("text"));
	}

	void module::push_byte(u8 value) {
		m_sections[m_current_section].data.push_back(value);
		m_byte_count++;
	}

	void module::add_symbol(utility::string_view* name, symbol_type type) {
		u64 size = m_sections[m_current_section].data.get_size();
		symbol sym = { .type = type, .position = size };
		const auto result = m_sections[m_current_section].symbols.insert({ name, sym  });

		ASSERT(result.second, "symbol '{}' has already been declared before\n", *name);
		SUPPRESS_C4100(result);
	}

	void module::add_relocation(utility::string_view* symbol, u8 size, u8 inst_len) {
		relocation r = { .symbol = symbol, .position = get_size_current_section(), .size = size, .inst_len = inst_len };
		m_sections[m_current_section].relocations.push_back(r);
	}

	void module::add_section(utility::string_view* name) {
		m_sections.emplace_back(name);	
	}

	void module::set_section(utility::string_view* name) {
		// basic linear search for the next section, we don't really care about doing a linear search,
		// since there won't be many sections and this is a rarely called function
		for(u64 i = 0; i < m_sections.get_size(); ++i) {
			if(name == m_sections[i].name) {
				m_current_section = i;
				return; 
			}
		}

		// new section
		m_current_section = m_sections.get_size();
		add_section(name);
	}

	auto module::emit_binary() const -> utility::dynamic_array<u8> {
		utility::map<utility::string_view*, symbol> symbols;
		utility::dynamic_array<relocation> relocations;
		utility::dynamic_array<u8> bytes;

		for(const section& s : m_sections) {
			if(s.data.is_empty()) {
				continue; // skip empty sections
			}

			// before appending the section, realign to 4 bytes
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
			for(const auto& [name, symbol] : s.symbols) {
				u64 new_position = 0;

				switch(symbol.type) {
					case SYM_GLOBAL:   new_position = symbol.position + bytes.get_size(); break; 
					case SYM_RELATIVE: new_position = symbol.position; break; 
					default: ASSERT(false, "unhandled symbol type specified\n"); 
				}

				symbols[name] = { .type = symbol.type, .position = new_position };
			}

			// append the section
			bytes.insert(bytes.end(), s.data.begin(), s.data.end());
		}	

		// apply relocations
		for(const relocation& r : relocations) {
			const auto it = symbols.find(r.symbol);
			ASSERT(it != symbols.end(), "invalid symbol '{}' specified\n", *r.symbol);

			u64 value = it->second.position;

			switch(it->second.type) {
				case SYM_GLOBAL:   break; 
				case SYM_RELATIVE: value -= r.position + r.inst_len; break;
				default: ASSERT(false, "unhandled symbol type specified\n"); 
			}

			utility::memcpy(bytes.get_data() + r.position, &value, r.size);
		}

		return bytes;
	}

	auto module::get_symbol(utility::string_view* name) const -> symbol {
		const auto it = m_sections[m_current_section].symbols.find(name);

		if(it == m_sections[m_current_section].symbols.end()) {
			return { .type = SYM_NONE, .position = utility::limits<u64>::max() };
		}

		return it->second;
	}

	auto module::get_size() const -> u64 {
		return m_byte_count;
	}

	auto module::get_size_current_section() const -> u64 {
		return m_sections[m_current_section].data.get_size();
	}

	auto module::get_current_section() const -> u64 {
		return m_current_section;
	}
} // namespace baremetal

