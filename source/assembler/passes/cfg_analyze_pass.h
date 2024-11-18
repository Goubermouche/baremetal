#pragma once
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	void cfg_analyze(module& module);
} // namespace baremetal::assembler::pass

