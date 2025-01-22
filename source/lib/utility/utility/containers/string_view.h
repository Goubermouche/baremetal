#pragma once
#include "utility/stream.h"
#include "utility/assert.h"
#include "utility/hash.h"

namespace utility {
	template<typename value, typename size>
	class string_view_base {
	public:
		using element_type = value;
		using size_type = size;

		using const_iterator = const element_type*;
		using iterator = element_type*;

		constexpr string_view_base() {
			m_data = nullptr;
			m_size = 0;
		}

		constexpr string_view_base(element_type* data) {
			m_data = data;
			m_size = string_len(data);
		}

		constexpr string_view_base(element_type* data, u64 count) {
			m_data = data;
			m_size = count;
		}

		[[nodiscard]] auto begin() -> iterator { return m_data; }
		[[nodiscard]] auto end() -> iterator { return m_data + m_size; }
		[[nodiscard]] auto begin() const -> const_iterator { return m_data; }
		[[nodiscard]] auto end() const -> const_iterator { return m_data + m_size; }

		[[nodiscard]] auto get_data() const -> element_type* {
			return m_data;
		}

		[[nodiscard]] auto get_size() const -> size_type {
			return m_size;
		}

		void set_data(element_type* data) {
			m_data = data;
		}
		void set_size(size_type count) {
			m_size = count;
		}
		[[nodiscard]] auto operator[](size_type index) -> element_type& {
			ASSERT(index < m_size, "index out of range\n");
			return m_data[index];
		}
		[[nodiscard]] auto operator[](size_type index) const -> const element_type& {
			ASSERT(index < m_size, "index out of range\n");
			return m_data[index];
		}
		[[nodiscard]] auto operator==(const element_type* other) const -> bool {
			const size_type len = string_len(other);

			if(len != m_size) {
				return false;
			}

			for(size_type i = 0; i < len; ++i) {
				if(other[i] != m_data[i]) {
					return false;
				}
			}

			return true;
		}
		[[nodiscard]] auto operator==(const string_view_base& other) const -> bool {
			if(other.get_size() != m_size) {
				return false;
			}

			for(size_type i = 0; i < m_size; ++i) {
				if(other[i] != m_data[i]) {
					return false;
				}
			}

			return true;
		}
	private:
		element_type* m_data;
		size_type m_size;
	};

	template<typename stream_type, typename char_type, typename size_type>
	struct stream_writer<string_view_base<char_type, size_type>, stream_type> {
		static void write(const string_view_base<char_type, size_type>& value, stream_type& str) {
			str.write(value.get_data(), value.get_size());
		}
	};

	template<typename d, typename s>
	struct hash<string_view_base<d, s>> {
		auto operator()(const string_view_base<d, s>& obj) const noexcept -> u64 {
			return compute_hash(obj.get_data(), sizeof(char) * obj.get_size());
		}
	};

	using string_view = string_view_base<char, u64>;
} // namespace utility

