#pragma once
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	namespace detail {
		[[nodiscard]] auto get_instruction_using_magic(instruction_data* inst, const imm& imm_op) -> bool;
		void optimize_instruction_size(instruction_data* inst);
	} // namespace detail

	void inst_size_minimize(module& module);
} // namespace baremetal::assembler::pass
