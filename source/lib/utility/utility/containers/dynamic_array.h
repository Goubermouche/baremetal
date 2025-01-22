#pragma once
#include "utility/ranges.h"
#include "utility/assert.h"

namespace utility {
	template<typename value, typename size = u64>
	class dynamic_array {
	public:
		using element_type = value;
		using size_type = size;

		using const_iterator = const element_type*;
		using iterator = element_type*;

		dynamic_array() : m_data(nullptr), m_capacity(0), m_size(0) {}
		dynamic_array(initializer_list<element_type> i_list)
			: m_data(nullptr), m_capacity(0), m_size(0) {
			reserve(i_list.size());
			construct(i_list.begin(), i_list.end(), i_list.size());

			m_size = i_list.size();
		}
		dynamic_array(size_type s, const element_type& v) 
			: m_data(nullptr), m_capacity(0), m_size(0) {
			reserve(s);

			for(size_type i = 0; i < s; ++i) {
				m_data[i] = v;
			}

			m_size = s;
		}
		dynamic_array(const dynamic_array& other)
			: m_data(nullptr), m_capacity(0), m_size(0) {
			reserve(other.get_size());
			construct(other.begin(), other.end(), other.get_size());

			m_size = other.get_size();
		}
		dynamic_array(dynamic_array&& other) noexcept {
			m_data = exchange(other.m_data, nullptr);
			m_capacity = exchange(other.m_capacity, 0);
			m_size = exchange(other.m_size, 0);
		}

		~dynamic_array() {
			clear();
			utility::free(m_data);
		}
		
		void push_back(const element_type& val) {
			if(m_size >= m_capacity) {
				reserve(m_capacity > 0 ? m_capacity * 2 : 1);
			}

			if constexpr(is_trivial_v<element_type>) {
				m_data[m_size++] = val;
			}
			else {
				construct_at(&m_data[m_size++], val);
			}
		}
		auto pop_back() -> element_type {
			if(is_empty()) {
				return {};
			}

			--m_size;

			return utility::move(m_data[m_size]);
		}

		template<typename... Args>
		auto emplace_back(Args&&... args) -> element_type& {
			if(m_size >= m_capacity) {
				reserve(m_capacity > 0 ? m_capacity * 2 : 1);
			}

			new(m_data + m_size) element_type(utility::forward<Args>(args)...);
			m_size++;
			// std::memset(m_data + m_size, 0, sizeof(element_type));
			// m_data[m_size++] = element_type(utility::forward<Args>(args)...);
			return m_data[m_size - 1];
		}

		template<typename iterator_type>
		void insert(iterator pos, iterator_type first, iterator_type last) {
			if(first == last) {
				return;
			}

			size_type num_elements_to_insert = utility::distance(first, last);
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
					new (m_data + i + num_elements_to_insert - 1) element_type(utility::move(m_data[i - 1]));
					m_data[i - 1].~element_type(); // destroy the old object after moving
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
			if(new_capacity <= m_capacity) {
				return;
			}

			element_type* new_data = static_cast<element_type*>(utility::malloc(new_capacity * sizeof(element_type)));
			ASSERT(new_data, "allocation failure");

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
		void clear() {
			if constexpr(!is_trivial_v<element_type>) {
				destruct_range(begin(), end());
			}

			m_size = 0;
		}

		[[nodiscard]] auto is_empty() const -> bool {
			return m_size == 0;
		}

		[[nodiscard]] auto get_data() const -> element_type* {
			return m_data;
		}
		[[nodiscard]] auto get_last() const -> const element_type& {
			return m_data[m_size - 1];
		}
		[[nodiscard]] auto get_capacity() const -> size_type { return m_capacity; }
		[[nodiscard]] auto get_size() const -> size_type { return m_size; }
		void set_size(size_type s)  { m_size = s; }

		[[nodiscard]] auto begin() -> iterator { return m_data; }
		[[nodiscard]] auto end() -> iterator { return m_data + m_size; }
		[[nodiscard]] auto begin() const -> const_iterator { return m_data; }
		[[nodiscard]] auto end() const -> const_iterator { return m_data + m_size; }

		auto operator=(const dynamic_array& other) -> dynamic_array& {
			if(this != &other) {
				clear();
				reserve(other.m_size);
				construct(other.begin(), other.end(), other.get_size());

				m_size = other.get_size();
			}

			return *this;
		}
		auto operator=(dynamic_array&& other) noexcept -> dynamic_array& {
			m_data = exchange(other.m_data, nullptr);
			m_capacity = exchange(other.m_capacity, 0);
			m_size = exchange(other.m_size, 0);
			return *this;
		}
		[[nodiscard]] auto operator[](size_type index) -> element_type& {
			ASSERT(index < m_size, "index out of range");
			return m_data[index];
		}
		[[nodiscard]] auto operator[](size_type index) const -> const element_type& {
			ASSERT(index < m_size, "index out of range");
			return m_data[index];
		}
	protected:
		void construct(const_iterator begin, const_iterator end, size_type count) {
			if constexpr(is_trivial_v<element_type>) {
				utility::memcpy(m_data, begin, count * sizeof(element_type));
			}
			else {
				construct_range(m_data, begin, end);
			}
		}
	protected:
		element_type* m_data;
		size_type m_capacity;
		size_type m_size;
	};
} // namespace utility
