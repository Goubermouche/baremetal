#pragma once
#include "assembler/instruction/operand.h"

namespace baremetal {
#pragma pack(push, 1)
	struct instruction {
		enum opcode : u16 {
			MOV,
			ADD
		};

		instruction(opcode opcode, operand a);
		instruction(opcode opcode, operand a, operand b);
		instruction(opcode opcode, operand a, operand b, operand c);

		opcode opcode;
		operand operands[3]; // expect up to 3 operands per instruction, this can technically be higher
		                     // for AVX 512 instructions, but those operands aren't actually encoded in
		                     // the instruction itself
	};
#pragma pack(pop)
} // namespace baremetal
