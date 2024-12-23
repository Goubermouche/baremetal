#pragma once
#include "assembler/ir/module.h"
#include "assembler/backend.h"

namespace baremetal::assembler::pass {
	namespace detail {
		struct unresolved_symbol {
			u64 block_index;       // source block
			u64 instruction_index; // source instruction
			u8 unresolved_index;   // source operand
			u64 position;          // byte position within the parent section
			
			// possible variants for the unresolved operand, sorted by size
			utility::dynamic_array<inst_variant> variants; 
		};

		auto collect_unresolved_symbols(const section& section) -> utility::dynamic_array<unresolved_symbol>;
		auto fits_into_type(i64 value, operand_type type) -> bool;
		
		void shift_unresolved(utility::dynamic_array<unresolved_symbol>& unresolved, u64 position, i64 shift);
		void shift_symbols(section& section, u64 position, i64 shift);
	} // namespace detail

	void symbolic_minimize(module& module);
} // namespace baremetal::assembler::pass
