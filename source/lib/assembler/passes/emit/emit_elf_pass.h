#pragma once
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	auto emit_elf(const module& module) -> utility::dynamic_array<u8>;
} // namespace baremetal::assembler::pass
