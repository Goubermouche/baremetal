#include "assembler.h"

namespace baremetal::x64 {
	auto assembler::create_label(ptr<ir::node> node) const -> ptr<instruction> {
		const ptr<instruction> inst = allocate_instruction(0, 0, 0);

		return inst;
	}

	auto assembler::create_jump(i32 successor) const -> ptr<instruction> {
		const ptr<instruction> inst = allocate_instruction(0, 0, 0);

		return inst;
	}

	auto assembler::create_imm(instruction_id kind, ir::data_type dt, reg destination, i32 imm) const -> ptr<instruction> {
		const ptr<instruction> inst = allocate_instruction(1, 0, 0);

		inst->flags |= IMMEDIATE;

		return inst;
	}

	auto assembler::create_abs(instruction_id kind, ir::data_type dt, reg destination, u64 imm) const -> ptr<instruction> {
		const ptr<instruction> inst = allocate_instruction(1, 0, 0);

		inst->flags |= ABSOLUTE;

		return inst;
	}

	auto assembler::create_move(ir::data_type dt, reg destination, reg source) const -> ptr<instruction> {
		const ptr<instruction> inst = allocate_instruction(1, 1, 0);

		return inst;
	}

	auto assembler::create_rm(instruction_id id, ir::data_type dt, reg destination, reg base, i32 index, i32 displacement) const -> ptr<instruction> {
		const ptr<instruction> inst = allocate_instruction(1, index >= 0 ? 2 : 1, 0);

		inst->flags = static_cast<instruction_flags>(MEMORY | (index != reg::invalid_index ? INDEXED : NONE));

		return inst;
	}

	auto assembler::create_mr(instruction_id id, ir::data_type dt, reg base, i32 index, i32 displacement, reg source) const -> ptr<instruction> {
		const ptr<instruction> inst = allocate_instruction(0, index != reg::invalid_index ? 3 : 2, 0);

		inst->flags = static_cast<instruction_flags>(MEMORY | (index != reg::invalid_index ? INDEXED : NONE));

		return inst;
	}

	auto assembler::create_instruction(u16 instruction_id, ir::data_type data_type, u8 out, u8 in, u8 temp) const -> ptr<instruction> {
		const ptr<instruction> inst = allocate_instruction(out, in, temp);
		return inst;
	}
} // namespace baremetal::x64
