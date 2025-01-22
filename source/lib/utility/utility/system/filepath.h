#pragma once
#include "utility/containers/dynamic_string.h"

namespace utility {
	class filepath {
	public:
		using base_type = dynamic_string;
		using size_type = base_type::size_type;
		using element_type = base_type::element_type;

		filepath() = default;
		filepath(const element_type* str) : m_data(str) {}
		filepath(const base_type& str) : m_data(str) {}
		
		[[nodiscard]] auto get_filename() const -> filepath {
			const size_type last_slash_pos = m_data.find_last_of('/');
			const size_type last_dot_pos = m_data.find_last_of('.');

			if(last_slash_pos != base_type::invalid_pos) {
				const size_type start_pos = last_slash_pos + 1;
				size_type length = base_type::invalid_pos;

				if(last_dot_pos != base_type::invalid_pos && last_dot_pos > last_slash_pos) {
					length = last_dot_pos - start_pos;
				}

				return { m_data.substring(start_pos, length) };
			}

			return *this; // if no '/' found, return the entire path
		}
		[[nodiscard]] auto get_parent_path() const -> filepath {
			const size_type last_slash_pos = m_data.find_last_of('/');

			if(last_slash_pos != base_type::invalid_pos) {
				// if the path ends with a slash and is the root directory ("/"), return "/"
				if(last_slash_pos == 0 && m_data.get_size() == 1) {
					return "/";
				}

				// trim the path to exclude the trailing slash if it's not the root directory
				size_type parent_length = last_slash_pos;
				if(parent_length == 0) {
					parent_length = 1;
				}

				return { m_data.substring(0, parent_length) };
			}

			// no slash found, return an is_empty filepath or the current path if it's a root directory
			return is_directory() ? *this : filepath();
		}
		[[nodiscard]] auto get_extension() const -> filepath {
			const size_type pos = m_data.find_last_of('.');

			if(pos != base_type::invalid_pos) {
				return { m_data.substring(pos) };
			}

			return {};
		}
		[[nodiscard]] auto replace_extension(const dynamic_string& extension) const -> filepath {
			const size_type last_dot_pos = m_data.find_last_of('.');

			if(last_dot_pos != base_type::invalid_pos) {
				return { m_data.substring(0, last_dot_pos + 1) + extension };
			}

			// no existing extension found
			return *this;
		}
		
		[[nodiscard]] auto is_directory() const -> bool {
			return !m_data.is_empty() && m_data.get_last() == '/';
		}
		[[nodiscard]] auto is_file() const -> bool {
			return !is_directory();
		}

		[[nodiscard]] auto get_string() const -> const base_type& {
			return m_data;
		}
		[[nodiscard]] auto get_data() const -> const element_type* {
			return m_data.get_data();
		}

		friend auto operator+(const filepath& left, const filepath& right) -> filepath {
			filepath result = left;
			result.m_data += right.get_string();
			return result;
		}
		friend auto operator/(const filepath& left, const filepath& right) -> filepath {
			filepath result = left;

			if(result.m_data.get_last() != '/') {
				result.m_data += '/';
			}

			result.m_data += right.get_string();
			return result;
		}
		friend auto operator<(const filepath& left, const filepath& right) -> bool {
			size_type min_size = left.m_data.get_size() < right.m_data.get_size() ? left.m_data.get_size() : right.m_data.get_size();

			for(size_t i = 0; i < min_size; ++i) {
				if(left.m_data.get_data()[i] < right.m_data.get_data()[i]) {
					return true;
				}

				if(left.m_data.get_data()[i] > right.m_data.get_data()[i]) {
					return false;
				}
			}

			return left.m_data.get_size() < right.m_data.get_size();
		}
	private:
		base_type m_data;
	};

	template<typename stream_type>
	struct stream_writer<filepath, stream_type> {
		static void write(const filepath& value, stream_type& str) {
			const auto& string = value.get_string();
			str.write(string.get_data(), string.get_size());
		}
	};
} // namespace utility
