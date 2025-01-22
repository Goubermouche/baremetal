#pragma once

#include "utility/assert.h"

namespace utility {
	template<typename value, u64 size>
	class array {
	public:
		using element_type = value;
		using size_type = u64;

		using const_iterator = const element_type*;
		using iterator = element_type*;

		constexpr array() : m_data{ 0 } {}
		constexpr array(initializer_list<element_type> i_list) {}

		[[nodiscard]] static auto get_size() -> u64 {
			return size;
		}
		[[nodiscard]] constexpr auto get_data() const -> element_type* {
			return m_data;
		}

		[[nodiscard]] constexpr auto begin() -> iterator { return m_data; }
		[[nodiscard]] constexpr auto end() -> iterator { return m_data + size; }
		[[nodiscard]] constexpr auto begin() const -> const_iterator { return m_data; }
		[[nodiscard]] constexpr auto end() const -> const_iterator { return m_data + size; }

		[[nodiscard]] constexpr auto operator[](size_type index) -> element_type& {
			ASSERT(index < size, "index out of range");
			return m_data[index];
		}
		[[nodiscard]] constexpr auto operator[](size_type index) const -> const element_type& {
			ASSERT(index < size, "index out of range");
			return m_data[index];
		}
	private:
		value m_data[size];
	};
} // namespace utility
