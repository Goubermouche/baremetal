#pragma once
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	void inst_size_minimize(module_t& module);
} // namespace baremetal::assembler::pass
