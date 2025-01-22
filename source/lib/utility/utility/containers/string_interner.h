#pragma once
#include "utility/allocators/block_allocator.h"
#include "utility/containers/dynamic_string.h"
#include "utility/containers/map.h"

namespace utility {
	class string_interner {
	public:
		string_interner() : m_allocator(1024) {}

		auto add(const dynamic_string& string) -> string_view* {
			// since the allocation in a block allocator is effectively an increment we can afford to 
			// temporarily allocate a block
			auto safepoint = m_allocator.create_safepoint();

			char* memory = static_cast<char*>(m_allocator.allocate(string.get_size() + 1));
			memcpy(memory, string.get_data(), string.get_size() + 1);

			string_view* view = m_allocator.emplace<string_view>(memory, string.get_size());
			auto result = m_strings.insert({ *view, view });
	
			if(result.second == false) {
				// string already exists, undo the allocation
				m_allocator.restore_safepoint(safepoint);
				return result.first->second;
			}
	
			// new string added
			return view;
		}

		auto contains(string_view string) const -> bool {
			return m_strings.find(string) != m_strings.end();
		}

		void clear() {
			m_allocator.clear();
			m_strings.clear();
		}

		void print() {
			for(const auto& [key, value] : m_strings) {
				console::print("{}\n", key);
			}
		}
	private:
		map<string_view, string_view*> m_strings;
		block_allocator m_allocator;
	};
} // namespace utility 

