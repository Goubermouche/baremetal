#include "emit_elf_pass.h"

#include "assembler/backend.h"
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	auto emit_elf(const module& module) -> utility::dynamic_array<u8> {
		utility::dynamic_array<u8> bytes;

		utility::console::print("emitting elf\n");

		bytes.push_back(0);
		bytes.push_back(1);
		bytes.push_back(100);
		bytes.push_back(255);

		return bytes;
	}
} // namespace baremetal::assembler::pass
