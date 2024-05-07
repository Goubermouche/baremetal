#include "instruction.h"

namespace baremetal {
	instruction::operand::operand(const memory& memory) : m_memory(memory), m_type(MEMORY) {}
	instruction::operand::operand(const u64& immediate) : m_immediate(immediate), m_type(IMMEDIATE) {}
	instruction::operand::operand(const reg& reg) : m_reg(reg), m_type(REG) {}

	instruction::instruction() : m_type(NONE) {}
	instruction::instruction(type type, const operand_type& operands) : m_type(type), m_operands(operands) {}

	auto operator<<(std::ostream& stream, const instruction::operand& operand) -> std::ostream& {
		switch(operand.m_type) {
			case instruction::operand::MEMORY:    stream << operand.m_memory;    break;
			case instruction::operand::IMMEDIATE: stream << operand.m_immediate; break;
			case instruction::operand::REG:       stream << operand.m_reg;       break;
		}

		return stream;
	}

	auto operator<<(std::ostream& stream, const instruction& instruction) -> std::ostream& {
		stream << static_cast<i32>(instruction.m_type) << ' ';

		for(u8 i = 0; i < instruction.m_operands.size(); ++i) {
			stream << instruction.m_operands[i];

			if(i + 1 != instruction.m_operands.size()) {
				stream << ", ";
			}
		}

		return stream;
	}
} // namespace baremetal
