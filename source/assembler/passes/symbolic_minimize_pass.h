#pragma once
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	namespace detail {
		auto fits_into_type(i64 value, operand_type type) -> bool;
	} // namespace detail

	void symbolic_minimize(module_t& module);
} // namespace baremetal::assembler::pass
