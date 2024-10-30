#pragma once
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	auto emit_binary(const module_t& module) -> utility::dynamic_array<u8>;
} // namespace baremetal::assembler::pass
