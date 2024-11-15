#pragma once
#include "assembler/ir/module.h"
#include "assembler/backend.h"

namespace baremetal::assembler::pass {
	namespace detail {
		struct unresolved {
			u64 block_index;
			u64 instruction_index;
			u8 unresolved_index;
			u64 position;
			utility::dynamic_array<inst_variant> variants;
		};

		auto collect_unresolved_in_section(const section_t& section) -> utility::dynamic_array<unresolved>;
		auto fits_into_type(i64 value, operand_type type) -> bool;
	} // namespace detail

	void symbolic_minimize(module_t& module);
} // namespace baremetal::assembler::pass
