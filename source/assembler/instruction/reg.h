#pragma once
#include <utility/types.h>

namespace baremetal {
	using namespace utility::types;

	class reg {
	public:
		using index_type = u8;
		using class_type = u8;

		static constexpr auto invalid_index = std::numeric_limits<index_type>::max();
		static constexpr auto invalid_class = std::numeric_limits<class_type>::max();

		constexpr reg() : m_index(invalid_index), m_class(invalid_class) {}
		constexpr reg(index_type index, class_type class_index) : m_index(index), m_class(class_index) {}

		[[nodiscard]] constexpr auto get_index() const -> index_type {
			return m_index;
		}

		[[nodiscard]] constexpr auto get_class() const -> class_type {
			return m_class;
		}

		[[nodiscard]] constexpr auto is_valid() const -> bool {
			return m_index != invalid_index && m_class != invalid_class;
		}

		friend auto operator<<(std::ostream& stream, const reg& reg) -> std::ostream& {
			stream << 'R' << static_cast<u64>(reg.get_index()) << '(' << static_cast<u64>(reg.get_class()) << ')';
			return stream;
		}
	protected:
		index_type m_index;
		class_type m_class;
	};
} // namespace baremetal
