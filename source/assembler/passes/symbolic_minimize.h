#pragma once
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	void symbolic_minimize(module_t& module);
} // namespace baremetal::assembler::pass
