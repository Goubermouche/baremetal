#pragma once
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	namespace detail {
		auto get_instruction_using_magic(instruction_t* inst, const imm& imm_op) -> bool;
		void optimize_instruction_size(instruction_t* inst);
	} // namespace detail

	void inst_size_minimize(module_t& module);
} // namespace baremetal::assembler::pass
