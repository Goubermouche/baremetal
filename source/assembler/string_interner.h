#pragma once
#include <utility/allocators/block_allocator.h>
#include <utility/containers/map.h>

namespace baremetal {
	class string_interner {
	public:
		string_interner();

		auto add(const utility::dynamic_string& string) -> utility::string_view*;
		auto contains(utility::string_view string) const -> bool;

		void clear();
		void print();
	private:
		utility::map<utility::string_view, utility::string_view*> m_strings;
		utility::block_allocator m_allocator;
	};
} // namespace baremetal

