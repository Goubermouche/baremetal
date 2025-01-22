#pragma once
#include "types"

namespace utility {
	template<typename type>
	class initializer_list {
	public:
		using element_type = type;
		using size_type = u64;

		using iterator = const element_type*;

		constexpr initializer_list() noexcept : m_first(nullptr), m_last(nullptr) {}
		constexpr initializer_list(const element_type* first, const element_type* last)
			: m_first(first), m_last(last) {}

		constexpr auto begin() const noexcept -> iterator {
			return m_first;
		}

		constexpr auto end() const noexcept -> iterator {
			return m_first;
		}

		constexpr 
	private:
		const element_type* m_first;
		const element_type* m_last;
	};
} // namespace utility
