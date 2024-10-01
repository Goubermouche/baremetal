#include "./backend.h"

namespace baremetal {
	namespace detail {

	} // namespace detail

	u8 backend::m_data_size;
	u8 backend::m_data[15];

	auto backend::get_instruction_by_name(const char* name) -> u32 {
    i32 left = 0;
    i32 right = instruction_db_size - 1;

		// since our instructions are sorted alphabetically, we can just do a quick binary search
    while(left <= right) {
      u32 mid = (static_cast<u32>(left) + static_cast<u32>(right)) >> 1;
      i32 cmp = utility::compare_strings(name, instruction_db[mid].name);

      if(cmp == 0) {
				// found an element with the specified name, loccate the first one
        while(mid > 0 && utility::compare_strings(name, instruction_db[mid - 1].name) == 0) {
          --mid;
        }

        return mid;
      }
      else if(cmp < 0) {
        right = static_cast<i32>(mid) - 1;
      }
      else {
				left = static_cast<i32>(mid) + 1;
      }
    }

    return utility::limits<u32>::max();
	}

	auto backend::emit_instruction(const instruction* inst, const operand* operands, bool optimize) -> code {
		m_data_size = 0;

		// emit individual instruction parts
		emit_instruction_prefix(inst, operands);
		emit_instruction_opcode(inst, operands);
		emit_instruction_mod_rm(inst, operands);
		emit_instruction_sib(inst, operands);
		emit_instruction_operands(inst, operands);

		return { .data = m_data, .size = m_data_size };
	}

	void backend::emit_instruction_operands(const instruction* inst, const operand* operands) {
		
	}

	void backend::emit_instruction_prefix(const instruction* inst, const operand* operands) {
		if(inst->enc == ENC_NORMALD) {
			// instruction composed of two instructions, emit the first one here (encoded as a part of the opcode)
			push_byte((inst->opcode & 0x0000FF00) >> 8);
		}

		if(inst->is_vex_xop() || inst->is_evex()) {
			return;
		}

		// group 4
		if(inst->prefix & ADDRESS_SIZE_OVERRIDE) {
			push_byte(0x67);
		}
		else if(inst->has_mem_operand()) {
			// memory operands with non 64-bit registers as index/base
			u8 mem_index = inst->get_mem_operand();
			const mem& m = operands[mem_index].memory;

			if(m.base.type == REG_R32 || m.index.type == REG_R32) {
				push_byte(0x67);
			}
		}

		// group 3
		if(inst->prefix & OPERAND_SIZE_OVERRIDE) {
			push_byte(0x66);
		}

		// group 2
		switch(inst->prefix & 0b00111100) {
			case CS_SEGMENT:       push_byte(0x2E); break;
			case SS_SEGMENT:       push_byte(0x36); break;
			case DS_SEGMENT:       push_byte(0x3E); break;
			case ES_SEGMENT:       push_byte(0x26); break;
			case FS_SEGMENT:       push_byte(0x64); break;
			case GS_SEGMENT:       push_byte(0x65); break;
			case BRANCH_NOT_TAKEN: push_byte(0x2E); break;
			case BRANCH_TAKEN:     push_byte(0x3E); break;
			default:                                break;
		}

		// group 1
		switch(inst->prefix & 0b00000011) {
			case LOCK:  push_byte(0xF0); break;
			case REPNE: push_byte(0xF2); break;
			case REP:   push_byte(0xF3); break;
			default:                     break;
		}
	}

	void backend::emit_instruction_opcode(const instruction* inst, const operand* operands) {
		// instruction prefix
		if(inst->is_rex()) {
			emit_opcode_prefix_rex(inst, operands);
		}
		else if(inst->is_vex_xop()) {
			emit_opcode_prefix_vex(inst, operands);
		}
		else if(inst->is_evex()) {
			emit_opcode_prefix_evex(inst, operands);
		}
		else {
			ASSERT(false, "unknown instruction encoding '{}' specified (opcode prefix)\n", static_cast<u8>(inst->enc));
		}

		u64 opcode = inst->opcode;

		if(inst->is_rex() == false && inst->enc == ENC_NORMALD) {
			// VEX instructions have the leading opcode encoded in themselves, so we have to skip it here
			// skip the first byte, since we've already pushed it (double instruction)
			opcode &= 0xff;
		}

		// TODO: 
		// opcode extensions (add a specific register to the opcode itself)
		
		// append opcode bytes
		for(u8 i = 4; i-- > 1;) {
			const u8 byte = (opcode >> (i * 8)) & 0xff;

			if(byte != 0) {
				push_byte(byte);
			}
		}

		// always push the last byte
		push_byte(opcode & 0xff);
	}

	void backend::emit_instruction_mod_rm(const instruction* inst, const operand* operands) {

	}

	void backend::emit_instruction_sib(const instruction* inst, const operand* operands) {

	}

	void backend::emit_opcode_prefix_evex(const instruction* inst, const operand* operands) {

	}

	void backend::emit_opcode_prefix_vex(const instruction* inst, const operand* operands) {

	}

	void backend::emit_opcode_prefix_rex(const instruction* inst, const operand* operands) {

	}

	void backend::push_byte(u8 value) {
		m_data[m_data_size++] = value;
	}
} // namespace baremetal
