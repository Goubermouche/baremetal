#pragma once
#include "assembler/instruction/operands/immediates.h"
#include "assembler/instruction/operands/registers.h"

namespace baremetal::assembler {
	enum scale : u8 {
		SCALE_1 = 0b00,
		SCALE_2 = 0b01,
		SCALE_4 = 0b10,
		SCALE_8 = 0b11,
		SCALE_NONE
	};

	struct mem {
		// this can't be a reg64 since it can contain special registers (ie. rip)
		reg base;
		reg index;

		bool has_base = false;
		bool has_index = false;

		scale s = SCALE_1;
		imm displacement;

		[[nodiscard]] constexpr auto has_sse_operands() const -> bool {
			if(has_base && is_sse_reg(base)) {
				return true;
			}

			if(has_index && is_sse_reg(index)) {
				return true;
			}

			return false;
		}
	};

	struct masked_mem {
		mem memory;
		u8 k;
	};

	[[nodiscard]] inline auto memory_to_string(mem m) -> utility::dynamic_string {
		utility::dynamic_string string = '[';
		
		// base register
		if(m.has_base) {
			string += register_to_string(m.base);
		}
	
		// index register
		if(m.has_index) {
			if(string.get_size() > 1) {
				string += " + ";
			}

			string += register_to_string(m.index);
		}

		// scale
		if(m.s != SCALE_1 && string.get_size() > 1) {
			string += " * ";
		}
	
		switch(m.s) {
			case SCALE_1:                break;
			case SCALE_2: string += "2"; break;
			case SCALE_4: string += "4"; break;
			case SCALE_8: string += "8"; break;
			default: ASSERT(false, "invalid scale specified\n");
		}
	
		// displacement
		if(string.get_size() > 1 && m.displacement.value != 0 && m.displacement.sign == false) {
			string += " + ";
		}
	
		if(m.displacement.value != 0) {
			// workaround for when we have negative displacement with other operands, this ensures
			// the operands are nicely spaced out
			if(m.displacement.sign && string.get_size() > 1) {
				string.append(" - {}", ~m.displacement.value + 1);
			}
			else {
				string += immediate_to_string(m.displacement);
			}
		}

		// empty memory operand
		if(string.get_size() == 1) {
			string += '0';
		}
	
		string += ']';

		return string;
	}
} // namespace baremetal::assembler

