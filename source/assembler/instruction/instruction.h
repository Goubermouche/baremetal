#pragma once
#include "assembler/instruction/memory.h"
#include <utility/dynamic_array.h>

namespace baremetal {
	class instruction {
	public:
		class operand {
		public:
			enum type {
				MEMORY,
				IMMEDIATE,
				REG
			};

			operand() = delete;

			operand(const memory& memory);
			operand(const u64& immediate);
			operand(const reg& reg);

			friend auto operator<<(std::ostream& stream, const operand& operand) -> std::ostream&;
		protected:
			union {
				memory m_memory;
				u64 m_immediate;
				reg m_reg;
			};

			type m_type;
		};

		enum type {
			NONE = 0,
			MOV,
			ADD,
		};

		using operand_type = utility::dynamic_array<operand, u8>;

		instruction();
		instruction(type type, const operand_type& operands);

		friend auto operator<<(std::ostream& stream, const instruction& instruction) -> std::ostream&;
	protected:
		type m_type;
		operand_type m_operands;
	};
} // namespace baremetal
