#pragma once
#include "utility/containers/string_view.h"
#include "utility/ranges.h"

namespace utility {
	template<typename value, typename size>
	class dynamic_string_base {
	public:
		using element_type = value;
		using size_type = size;

		using const_iterator = const element_type*;
		using iterator = element_type*;

		dynamic_string_base() {
			reserve(0);
			m_data[0] = 0;
			m_size = 0;
		}
		dynamic_string_base(const element_type* str) {
			const size_type length = string_len(str);
			reserve(length);
			m_size = length;
			utility::memcpy(m_data, str, m_size * sizeof(element_type));
			m_data[m_size] = 0;
		}
		dynamic_string_base(element_type c) {
			reserve(1);
			m_size = 1;
			m_data[0] = c;
			m_data[m_size] = 0;
		}
		dynamic_string_base(const dynamic_string_base& other) {
			reserve(other.get_size());
			m_size = other.get_size();
			utility::memcpy(m_data, other.get_data(), (m_size + 1) * sizeof(element_type));
		}
		dynamic_string_base(dynamic_string_base&& other) noexcept :
		m_data(exchange(other.m_data, nullptr)), m_capacity(exchange(other.m_capacity, 0)), m_size(exchange(other.m_size, 0)) {}

		~dynamic_string_base() {
			if(m_data) {
				utility::free(m_data);
				m_size = 0;
				m_capacity = 0;
				m_data = nullptr;
			}
		}

		template<typename type>
		void append(const type& first) {
			append_impl(first);
		}

		template<typename type, typename... types>
		void append(const char* format, const type& first, const types&... rest) {
			append_impl(format, first, forward<const types>(rest)...);
		}

		template<typename iterator_type>
		void insert(iterator pos, iterator_type first, iterator_type last) {
			if(first == last) {
				return;
			}

			size_type num_elements_to_insert = distance(first, last);
			size_type index = distance(begin(), pos);

			// ensure there is enough space for the new elements
			if(m_size + num_elements_to_insert > m_capacity) {
				reserve(m_size + num_elements_to_insert);
			}

			// move existing elements to make space for the new elements
			if constexpr(is_trivial_v<element_type>) {
				utility::memmove(
					m_data + index + num_elements_to_insert,
					m_data + index,
					(m_size - index) * sizeof(element_type)
				);
			}
			else {
				// move construct elements from end to start to prevent overwriting
				for(size_type i = m_size; i > index; --i) {
					new (m_data + i + num_elements_to_insert - 1) element_type(move(m_data[i - 1]));
					m_data[i - 1].~value_type(); // destroy the old object after moving
				}
			}

			// copy new elements into the space created
			auto insert_pos = m_data + index;

			for(auto it = first; it != last; ++it, ++insert_pos) {
				new (insert_pos) element_type(*it); // copy construct new elements
			}

			m_size += num_elements_to_insert;
		}

		void reserve(size_type new_capacity) {
			new_capacity += 1; // zero termination

			if(new_capacity <= m_capacity) {
				return;
			}

			element_type* new_data = static_cast<element_type*>(utility::malloc(new_capacity * sizeof(element_type)));
			ASSERT(new_data, "allocation failure\n");

			if constexpr(is_trivial_v<element_type>) {
				utility::memcpy(new_data, m_data, m_size * sizeof(element_type));
			}
			else {
				construct_range(new_data, begin(), end());
				destruct_range(begin(), end());
			}

			utility::free(m_data);
			m_data = new_data;
			m_capacity = new_capacity;
		}
		void resize(u64 new_size) {
			if(m_size < new_size) {
				reserve(new_size);
			}

			m_data[new_size] = 0;
			m_size = new_size;
		}
		void replace(size_type start, size_type count, const dynamic_string_base& new_content) {
			if(start >= m_size) {
				return;
			}

			size_type new_size = m_size - count + new_content.get_size();

			if(new_size > m_capacity) {
				reserve(new_size);
			}

			if constexpr(is_trivial_v<element_type>) {
				utility::memmove(
					m_data + start + new_content.get_size(),
					m_data + start + count,
					(m_size - start - count) * sizeof(element_type)
				);
			}
			else {
				for(size_type i = start + new_content.get_size(); i < m_size; ++i) {
					new (m_data + i) element_type(move(m_data[i - count]));
					m_data[i - count].~element_type(); // destroy the old object after moving
				}
			}

			utility::memcpy(m_data + start, new_content.begin(), new_content.get_size() * sizeof(element_type));

			m_size = new_size;
			m_data[m_size] = 0;
		}
		void clear() {
			if(is_empty()) {
				return;
			}

			m_data[0] = 0;
			m_size = 0;
		}
		auto trim() -> dynamic_string_base {
			dynamic_string_base result;
			size_type index = {};
			size_type start_index;

			// leading whitespace
			while(is_space(m_data[index])) {
				++index;
			}

			// all spaces
			if(m_data[index] == 0) {
				return {};
			}

			start_index = index;

			// trailing whitespace
			index = m_size - 1;

			while(index > start_index && is_space(m_data[index])) {
				--index;
			}

			const size_type length = index - start_index + 1;
			result.resize(length);
			utility::memcpy(result.m_data, begin() + start_index, length * sizeof(element_type));

			return result;
		}
		auto remove_trailing(element_type c) -> dynamic_string_base {
			size_type i;

			for(i = get_size(); i-- > 0;) {
				if(m_data[i] != c) {
					break;
				}
			}

			return substring(0, i + 1);
		}

		[[nodiscard]] auto find(element_type c, size_type start_index = 0) const -> size_type {
			if(start_index >= get_size()) {
				return invalid_pos;
			}

			for(size_type i = start_index; i < get_size(); ++i) {
				if(m_data[i] == c) {
					return i;
				}
			}

			return invalid_pos;
		}
		[[nodiscard]] auto find(const dynamic_string_base& substr, size_type start_index = 0) const -> size_type {
			if(start_index >= get_size() || substr.get_size() == 0) {
				return invalid_pos;
			}

			size_type substr_len = substr.get_size();

			if(substr_len > get_size() - start_index) {
				return invalid_pos; 
			}

			for(size_type i = start_index; i <= get_size() - substr_len; ++i) {
				bool match = true;

				for(size_type j = 0; j < substr_len; ++j) {
					if(m_data[i + j] != substr.m_data[j]) {
						match = false;
						break;
					}
				}

				if(match) {
					return i;
				}
			}

			return invalid_pos;
		}
		[[nodiscard]] auto find_last_of(element_type c, size_type start_index = 0) const -> size_type {
			if(start_index >= get_size()) {
				return invalid_pos;
			}

			for(size_type i = get_size(); i-- > start_index;) {
				if(m_data[i] == c) {
					return i;
				}
			}

			return invalid_pos;
		}
		[[nodiscard]] auto substring(size_type start, size_type count = invalid_pos) const -> dynamic_string_base {
			size_type length;

			if(count == invalid_pos) {
				length = get_size() - start;
			}
			else {
				length = count;
			}

			dynamic_string_base new_string;
			new_string.reserve(length);
			new_string.m_size = length;

			utility::memcpy(new_string.m_data, begin() + start, length * sizeof(element_type));
			new_string.m_data[length] = 0;

			return new_string;
		}

		[[nodiscard]] auto is_empty() const -> bool {
			return m_size == 0;
		}

		[[nodiscard]] auto get_data() const -> element_type* {
			return m_data;
		}
		[[nodiscard]] auto get_last() const -> element_type {
			if(is_empty()) {
				return g_eof;
			}

			return m_data[m_size - 1];
		}
		[[nodiscard]] auto get_capacity() const -> size_type { return m_capacity; }
		[[nodiscard]] auto get_size() const -> size_type { return m_size; }
		[[nodiscard]] auto begin() -> iterator { return m_data; }
		[[nodiscard]] auto end() -> iterator { return m_data + m_size; }
		[[nodiscard]] auto begin() const -> const_iterator { return m_data; }
		[[nodiscard]] auto end() const -> const_iterator { return m_data + m_size; }

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
		[[nodiscard]] auto operator==(const dynamic_string_base& other) const -> bool {
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
		[[nodiscard]] auto operator[](size_type index) -> element_type& {
			// utility::console::print("{}, {}\n", index, m_size);
			ASSERT(index < m_size, "index out of range\n");
			return m_data[index];
		}
		[[nodiscard]] auto operator[](size_type index) const -> const element_type& {
			ASSERT(index < m_size, "index out of range\n");
			return m_data[index];
		}

		auto operator+=(element_type c) -> dynamic_string_base& {
			reserve(m_size + 1);
			++m_size;
			m_data[m_size] = 0;
			m_data[m_size - 1] = c;

			return *this;
		}
		auto operator+=(const element_type* other) -> dynamic_string_base& {
			size_type length = string_len(other);
			reserve(m_size + length);
			utility::memcpy(m_data + m_size, other, sizeof(element_type) * (length + 1));
			m_size += length;

			return *this;
		}
		auto operator+=(const dynamic_string_base& other) -> dynamic_string_base& {
			reserve(m_size + other.get_size());
			utility::memcpy(m_data + m_size, other.begin(), sizeof(element_type) * (other.get_size() + 1));
			m_size += other.get_size();

			return *this;
		}
		auto operator+=(const string_view& other) -> dynamic_string_base& {
			reserve(m_size + other.get_size());
			utility::memcpy(m_data + m_size, other.begin(), sizeof(element_type) * (other.get_size() + 1));
			m_size += other.get_size();

			return *this;
		}
		auto operator=(const dynamic_string_base& other) -> dynamic_string_base& {
			if(this != &other) {
				utility::free(m_data);

				reserve(other.get_size());
				m_size = other.get_size();
				utility::memcpy(m_data, other.get_data(), (m_size + 1) * sizeof(element_type));
			}

			return *this;
		}
		auto operator=(dynamic_string_base&& other) noexcept -> dynamic_string_base& {
			if(this != &other) {
				utility::free(m_data);

				m_capacity = exchange(other.m_capacity, 0);
				m_size = exchange(other.m_size, 0);
				m_data = exchange(other.m_data, nullptr);
			}

			return *this;
		}

		friend auto operator+(const dynamic_string_base& left, const dynamic_string_base& right) ->dynamic_string_base {
			dynamic_string_base result = left;

			result.reserve(result.m_size + right.get_size());
			utility::memcpy(result.m_data + result.m_size, right.begin(), sizeof(element_type) * (right.get_size() + 1));
			result.m_size += right.get_size();

			return result;
		}
		friend auto operator+(const dynamic_string_base& left, element_type c) ->dynamic_string_base {
			dynamic_string_base result = left;

			result.reserve(result.m_size + 1);
			++result.m_size;
			result.m_data[result.m_size] = 0;
			result.m_data[result.m_size - 1] = c;

			return result;
		}
		friend auto operator<(const dynamic_string_base& left, const dynamic_string_base& right) -> bool {
			size_type min_size = left.get_size() < right.get_size() ? left.get_size() : right.get_size();

			for(size_t i = 0; i < min_size; ++i) {
				if(left.get_data()[i] < right.get_data()[i]) {
					return true;
				}

				if(left.get_data()[i] > right.get_data()[i]) {
					return false;
				}
			}

			return left.get_size() < right.get_size();
		}
		void write(const char* data) {
			write(data, string_len(data));
		}
		
		void write(const char* data, u64 s) {
			insert(end(), data, data + s);
		}
	protected:
		template<typename type, typename... types>
		void append_impl(const char* format, const type& first, const types&... rest) {
			if(const char* open_brace = std::strstr(format, "{}")) {
				write(format, open_brace - format);
				stream_writer<type, dynamic_string_base<value, size>>::write(first, *this);
				append_impl(open_brace + 2, rest...);
			}
			else {
				write(format);
			}
		}

		template<typename type>
		void append_impl(const type& first) {
			stream_writer<type, dynamic_string_base<value, size>>::write(first, *this);
		}
	public:
		static constexpr size_type invalid_pos = limits<size_type>::max();
	protected:
		element_type* m_data = nullptr;
		size_type m_capacity = size_type();
		size_type m_size = size_type();
	};

	template<typename stream_type, typename char_type, typename size_type>
	struct stream_writer<dynamic_string_base<char_type, size_type>, stream_type> {
		static void write(const dynamic_string_base<char_type, size_type>& value, stream_type& str) {
			str.write(value.get_data(), value.get_size());
		}
	};

	template<typename d, typename s>
	struct hash<dynamic_string_base<d, s>> {
		auto operator()(const dynamic_string_base<d, s>& obj) const noexcept -> u64 {
			return compute_hash(obj.get_data(), sizeof(char) * obj.get_size());
		}
	};

	using dynamic_string = dynamic_string_base<char, u64>;
	using dynamic_string_w = dynamic_string_base<wchar_t, u64>;

	inline auto string_to_string_w(const dynamic_string& str) -> dynamic_string_w {
		dynamic_string_w result;
		result.resize(str.get_size());

		const i32 written = swprintf(result.get_data(), str.get_size() + 1, L"%hs", str.get_data());

		ASSERT(written == static_cast<i32>(str.get_size()), "invalid string");
		SUPPRESS_C4100(written);

		return result;
	}

	inline auto string_w_to_string(const dynamic_string_w& str) -> dynamic_string {
		dynamic_string result;
		result.resize(str.get_size());

		const u64 written = wcstombs(result.get_data(), str.get_data(), str.get_size() + 1);

		ASSERT(written == str.get_size(), "invalid string");
		SUPPRESS_C4100(written);

		return result;
	}

	[[nodiscard]] inline auto byte_to_string(u8 byte) -> const char* {
		constexpr char digits[] = "0123456789abcdef";
		static char string[3];

		string[0] = (digits[(byte >> 4) & 0x0F]);
		string[1] = (digits[byte & 0x0F]);
		string[2] = '\0';

		return string;
	}

	template<typename byte_type>
	[[nodiscard]] inline auto bytes_to_string(const byte_type& bytes, u64 count) -> dynamic_string {
		dynamic_string string;
		string.reserve(count * 2);

		for(u64 i = 0; i < count; ++i) {
			string += byte_to_string(bytes[i]);
		}

		return string;
	}

	template<typename byte_type>
	[[nodiscard]] inline auto bytes_to_string(const byte_type& bytes, u64 count, char separator) -> dynamic_string {
		dynamic_string string;
		string.reserve(count * 3);

		for(u64 i = 0; i < count; ++i) {
			string += byte_to_string(bytes[i]);
			string += separator;
		}

		return string;
	}
} // namespace utility
