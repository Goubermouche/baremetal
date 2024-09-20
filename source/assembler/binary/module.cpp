#include "module.h"

namespace baremetal {
	module::module(assembler_context* context) : m_context(context) {
		clear();
	}

	module::section::section(utility::string_view* name)
		: name(name) {}

	module::symbol::symbol(symbol_type type, u64 position)
		: type(type), position(position) {}

	module::relocation::relocation(utility::string_view* symbol, u64 position, u8 size)
		: symbol(symbol), position(position), size(size) {}

	void module::clear() {
		m_sections.clear();

		m_current_section = 0;
		m_byte_count = 0;

		// only add the .text section by default
		add_section(m_context->strings.add("text"));
	}

	void module::add_symbol(utility::string_view* name, symbol_type type) {
		section& section = m_sections[m_current_section];
		u64 size = section.data.get_size();

		// insert the new symbol
		const auto result = section.symbols.insert({ name, symbol(type, size)  });

		ASSERT(result.second, "symbol '{}' has already been declared before\n", *name);
		SUPPRESS_C4100(result);
	}

	void module::add_relocation(utility::string_view* symbol, u8 size) {
		relocation relocation(symbol, get_size_current_section(), size);

		// insert the new relocation
		m_sections[m_current_section].relocations.push_back(relocation);
	}

	void module::add_section(utility::string_view* name) {
		m_sections.emplace_back(name);	
	}

	void module::push_byte(u8 value) {
		m_sections[m_current_section].data.push_back(value);
		m_byte_count++;
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

		// section doesn't exist - create a new one
		m_current_section = m_sections.get_size();
		add_section(name);
	}

	auto module::emit_object_elf() const -> utility::dynamic_array<u8> {
		ASSERT(false, "not implemented\n");
		return {};
	}

	auto module::emit_binary() const -> utility::dynamic_array<u8> {
		// updated symbols
		utility::map<utility::string_view*, symbol> symbols;
		utility::dynamic_array<relocation> relocations;

		// result
		utility::dynamic_array<u8> bytes;

		// first pass - append data and update symbol data
		for(const section& s : m_sections) {
			if(s.data.is_empty()) {
				continue; // skip empty sections
			}

			// before appending the section, realign to 4 bytes
			const u64 alignment_offset = utility::align(bytes.get_size(), 4) - bytes.get_size(); 

			for(u64 i = 0; i < alignment_offset; ++i) {
				bytes.push_back(0);
			}

			// update relocations
			for(relocation r : s.relocations) {
				r.position += bytes.get_size();
				relocations.push_back(r);
			}

			// update symbols
			for(const auto& [name, sym] : s.symbols) {
				u64 new_position = 0;

				switch(sym.type) {
					case SYM_GLOBAL:   new_position = sym.position + bytes.get_size(); break; 
					case SYM_RELATIVE: new_position = sym.position; break; 
					default: ASSERT(false, "unhandled symbol type specified\n"); 
				}

				utility::console::print("\n{}\n", new_position);

				const auto result = symbols.insert({ name, symbol(sym.type, new_position) });

				ASSERT(result.second, "symbol '{}' has already been declared before\n", *name);
				SUPPRESS_C4100(result);
			}

			// append the section
			bytes.insert(bytes.end(), s.data.begin(), s.data.end());
		}	

		// apply relocations
		for(const relocation& relocation : relocations) {
			const auto it = symbols.find(relocation.symbol);
			ASSERT(it != symbols.end(), "invalid symbol '{}' specified\n", *relocation.symbol);

			u64 value = it->second.position;

			switch(it->second.type) {
				case SYM_GLOBAL:   break; 
				case SYM_RELATIVE: value -= relocation.position + relocation.size; break;
				default: ASSERT(false, "unhandled symbol type specified\n"); 
			}

			utility::memcpy(bytes.get_data() + relocation.position, &value, relocation.size);
		}

		return bytes;
	}

	auto module::get_symbol(utility::string_view* name) const -> symbol {
		const auto it = m_sections[m_current_section].symbols.find(name);

		if(it == m_sections[m_current_section].symbols.end()) {
			return symbol(SYM_NONE, 0);
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

