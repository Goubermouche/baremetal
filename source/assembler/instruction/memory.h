#pragma once
#include "assembler/instruction/reg.h"

namespace baremetal {
	class memory {
	public:
		using displacement_type = i32;

		enum scale {
			X1,
			X2,
			X4,
			X8
		};

		memory() : m_scale(X1), m_displacement(0) {}
		memory(const reg& base, const reg& index, scale scale, displacement_type displacement)
			: m_base(base), m_index(index), m_scale(scale), m_displacement(displacement) {}

		[[nodiscard]] constexpr auto get_base() const -> reg {
			return m_base;
		}

		[[nodiscard]] constexpr auto get_index() const -> reg {
			return m_base;
		}

		[[nodiscard]] constexpr auto get_displacement() const -> displacement_type {
			return m_displacement;
		}

		friend auto operator<<(std::ostream& stream, const memory& memory) -> std::ostream& {
			stream << memory.m_base << " + " << memory.m_index << " * " << memory.m_scale << " + " << memory.m_displacement;
			return stream;
		}

		friend auto operator<<(std::ostream& stream, scale scale) -> std::ostream& {
			switch(scale) {
				case X1: stream << '1'; break;
				case X2: stream << '2'; break;
				case X4: stream << '4'; break;
				case X8: stream << '8'; break;
			}

			return stream;
		}
	protected:
		reg m_base;
		reg m_index;
		scale m_scale;
		displacement_type m_displacement;
	};
} // namespace baremetal
