#include "string_interner.h"

namespace baremetal {
	string_interner::string_interner() : m_allocator(1024) {}

	void string_interner::clear() {
		m_allocator.clear();
		m_strings.clear();
	}

	void string_interner::print() {
		for(const auto& [key, value] : m_strings) {
			utility::console::print("{}\n", key);
		}
	}

	auto string_interner::add(const utility::dynamic_string& string) -> utility::string_view* {
		// TODO: potentially hash the string before, so that we can dodge the memcpy

		// since the allocation in a block allocator is effectively an increment we can afford to 
		// temporarily allocate a block
		auto safepoint = m_allocator.create_safepoint();

		char* memory = static_cast<char*>(m_allocator.allocate(string.get_size() + 1));
		utility::memcpy(memory, string.get_data(), string.get_size() + 1);

	  utility::string_view* view = m_allocator.emplace<utility::string_view>(memory, string.get_size());
		auto result = m_strings.insert({ *view, view });

		if(result.second == false) {
			// string already exists, undo the allocation
			m_allocator.restore_safepoint(safepoint);
			return result.first->second;
		}

		// new string added
		return view;
	}
} // namespace baremetal

