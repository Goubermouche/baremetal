#include "./backend.h"
#include "assembler/assembler_backend.h"

namespace baremetal {
	namespace detail {
		auto mod_rm(mod_mode mod, u8 rx, u8 rm) -> u8 {
			ASSERT(mod < 4, "invalid modR/M mod specified\n");
			u8 value = 0;

			// calculate the modR/M byte
			value |= mod << 6;               // mod  [XX______]
			value |= (rx & 0b00000111) << 3; // rx   [__XXX___]
			value |= rm & 0b00000111;        // rm   [_____XXX]

			return value;
		}

		auto sib(u8 scale, u8 index, u8 base) -> u8 {
			ASSERT(scale < 4, "invalid SIB scale specified\n");
			u8 value = 0;

			// calculate the SIB byte
			value |= scale << 6;                // scale [XX______]
			value |= (index & 0b00000111) << 3; // index [__XXX___]
			value |= (base & 0b00000111);       // base  [_____XXX] 

			return value; 
		}

		auto rex(bool w, u8 rx, u8 base, u8 index) -> u8 {
			u8 value = 0;

			// calculate the REX byte
			value |= 0b01000000;                                 // rex prefix      [0100____]
			value |= w << 3;                                     // 64-bit mode     [____X___]
			value |= static_cast<bool>(rx & 0b00011000) << 2;    // rx extension    [_____X__]
			value |= static_cast<bool>(index & 0b00011000) << 1; // index extension [______X_]
			value |= static_cast<bool>(base & 0b00011000);       // base extension  [_______X]

			return value;
		}

		auto direct(u8 rx, u8 reg) -> u8 {
			return mod_rm(DIRECT, rx, reg);
		}

		auto indirect(u8 rx, u8 base) -> u8 {
			return mod_rm(INDIRECT, rx, base);
		}

		auto indirect_disp_8(u8 rx, u8 base) -> u8 {
			return mod_rm(INDIRECT_DISP8, rx, base);
		}

		auto indirect_disp_32(u8 rx, u8 base) -> u8 {
			return mod_rm(INDIRECT_DISP32, rx, base);
		}

		auto extract_operand_reg(const operand& op) -> u8 {
			if(is_operand_reg(op.type)) {
				return op.r;
			}
	
			if(is_operand_mem(op.type) && op.memory.has_base) {
				return op.memory.base.index;
			}
	
			return 0;
		}
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
		emit_instruction_sib(operands);
		emit_instruction_operands(inst, operands);

		return { .data = m_data, .size = m_data_size };
	}

	void backend::emit_instruction_operands(const instruction* inst, const operand* operands) {
		for(u8 i = 0; i < inst->operand_count; ++i) {
			const operand_type current = inst->operands[i];

			if(is_operand_imm(current)) {
				emit_data_operand(operands[i].immediate.value, get_operand_bit_width(current));
			}
			else if(is_operand_moff(current)) {
				// memory offset operand (always 64-bit)
				emit_data_operand(operands[i].memory_offset.value, 64);
			}
			else if(is_operand_rel(current)) {
				// relocation operand
				const u16 operand_size = get_operand_bit_width(current);
				emit_data_operand(operands[i].immediate.value, operand_size);
			}
			else if(is_operand_mem(current)) {
				// memory displacement operand
				const mem memory = operands[i].memory;
				imm displacement = memory.displacement;

				if(displacement.value == 0) {
					if(memory.has_base && memory.base.type != REG_RIP && !is_sse_reg(memory.base)) {
						continue; // skip 0 displacements
					}
				}

				// determine the displacement size
				operand_type ty = OP_I32;

				if(memory.has_base) {
					if(memory.base.type == REG_RIP) {
						// calculate the relative (rip) offset, this means we have to calculate the
						// offset at the end of our current instruction

						// beginning of the instruction
						i32 new_displacement = static_cast<i32>(displacement.value - (m_data_size + 4));

						for(u8 j = i; j < inst->operand_count; ++j) {
							// if we have another operand after the current one, calculate it's size
							if(is_operand_imm(inst->operands[j])) { // registers are already encoded
								new_displacement -= get_operand_bit_width(inst->operands[j]) / 8;
							}
						}

						if(inst->is_is4()) {
							new_displacement--; // account for the trailing byte introduced by /is4
						}

						displacement = imm(new_displacement);
						ty = OP_I32;
					}
					else if(is_sse_reg(memory.base)) {
						ty = OP_I32;
					}
					else if(displacement.min_bits <= 8) {
						ty = OP_I8;
					}
				}

				emit_data_operand(displacement.value, get_operand_bit_width(ty));
			}
		}

		if(inst->is_is4()) {
			// trailing register encoded as an immediate
			push_byte(operands[3].r << 4);
		}
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

		if(inst->is_rex() == false || inst->enc == ENC_NORMALD) {
			// VEX instructions have the leading opcode encoded in themselves, so we have to skip it here
			// skip the first byte, since we've already pushed it (double instruction)
			opcode &= 0xff;
		}

		// opcode extensions (add a specific register to the opcode itself)
		if(inst->is_ri()) {
			opcode += get_modrm_rm(inst, operands) & 0b00000111;
		}

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
		u8 rx = get_modrm_reg(inst, operands);
		u8 destination = get_modrm_rm(inst, operands);

		if(inst->is_rm() && !inst->is_is4()) {
			rx = inst->get_rm();
		}

		// memory operands
		for(u8 i = 0; i < inst->operand_count; ++i) {
			if(!is_operand_mem(operands[i].type)) {
				continue;
			}

			const bool sib = has_sib(operands);
			const auto memory = operands[i].memory;
		
			ASSERT(memory.displacement.min_bits <= 32, "too many displacement bits");

			if(memory.has_base == false) {
				push_byte(detail::indirect(rx, 0b100));
			}
			else if(memory.base.type == REG_RIP) {
				push_byte(detail::indirect(rx, 0b101));
			}
			else if(is_sse_reg(memory.base)) {
				push_byte(detail::indirect(rx, 0b100));
			}
			else if(memory.displacement.value == 0) {
				push_byte(detail::indirect(rx, sib ? 0b100 : memory.base.index));
			}
			else if(memory.displacement.min_bits <= 8) {
				// 8 bit displacement
				push_byte(detail::indirect_disp_8(rx, sib ? 0b100 : memory.base.index));
			}
			else {
				// 32 bit displacemen
				push_byte(detail::indirect_disp_32(rx, sib ? 0b100 : memory.base.index));
			}

			return; // nothing else to do
		}

		if(inst->has_broadcast_operand()) {
			push_byte(detail::indirect(rx, destination));
			return;
		}

		// forced mod/rm
		if(inst->is_r()) {
			push_byte(detail::direct(rx, destination));
		}
		else if(inst->is_rm()) {
			push_byte(detail::direct(rx, destination));
		}
	}

	void backend::emit_instruction_sib(const operand* operands) {
		operand operand;

		for(u8 i = 0; i < 3; ++i) {
			if(is_operand_mem(operands[i].type)) {
				operand = operands[i];
				break;
			}
		}

		if(operand.type == OP_NONE) {
			return;
		}

		const mem memory = operand.memory;
		const u8 scale = memory.has_base  ? memory.s           : 0b000;
		const u8 index = memory.has_index ? memory.index.index : 0b100;
		const u8 base  = memory.has_base  ? memory.base.index  : 0b101;

		if(
			memory.has_index || 
			is_stack_pointer(reg(memory.base)) ||
			memory.has_base == false || 
			operand.type == OP_TMEM
		) {
			push_byte(detail::sib(scale, index, base));
		}
		else if(memory.has_sse_operands()) {
			push_byte(detail::sib(scale, base, memory.has_index ? memory.index.index : 0b101));
		}
	}

	void backend::emit_opcode_prefix_evex(const instruction* inst, const operand* operands) {
		const u8 rex = get_instruction_rex(inst, operands);
		const u8 modrm = get_modrm_reg(inst, operands);
		u8 prefix[3] = {};

		push_byte(0x62); // EVEX prefix

		prefix[0] |= !(rex & 0b00000100) << 7;                  // ~R         [X_______] 
		prefix[0] |= !(rex & 0b00000010) << 6;                  // ~X         [_X______] 
		prefix[0] |= !(rex & 0b00000001) << 5;                  // ~B         [__X_____] 
		prefix[0] |= !(modrm & 0b00010000) << 4;                // ~R'        [___X____]
		prefix[0] |= inst->get_map_select();                    // map select [____0XXX]

		prefix[1] |= static_cast<u8>((inst->is_rexw()) << 7);   // W          [X_______]
		prefix[1] |= get_instruction_vvvv(inst, operands) << 3; // ~VVVV      [_XXXX___]
		prefix[1] |= 0b1 << 2;                                  //            [_____1__]
		prefix[1] |= inst->get_imp();                           // IMP        [______XX]

		prefix[2] |= inst->get_evex_zero() << 7;                // zero mask  [X_______]
		prefix[2] |= inst->get_evex_operand_type();             // size       [_XX_____]
		prefix[2] |= inst->has_broadcast_operand() << 4;        // broadcast  [___X____]
		prefix[2] |= !get_instruction_v(inst, operands) << 3;   // ~V         [____X___]
		prefix[2] |= get_mask_reg(inst, operands);              // mask       [_____XXX]

		push_byte(prefix[0]);
		push_byte(prefix[1]);
		push_byte(prefix[2]);
	}

	void backend::emit_opcode_prefix_vex(const instruction* inst, const operand* operands) {
		const u8 rex = get_instruction_rex(inst, operands);

		const bool x = rex & 0b00000010;
		const bool b = rex & 0b00000001;

		// a VEX instruction whose values for certain fields are VEX.~X == 1, VEX.~B == 1, VEX.W/E == 0
		// and map_select == b00001 may be encoded using the two byte VEX escape prefix (XOP)
		if(!x && !b && !inst->is_rexw() && ((inst->opcode & 0xffff00) == 0x000f00)) {
			emit_opcode_prefix_vex_two(inst, operands); // two byte variant
		}
		else {
			emit_opcode_prefix_vex_three(inst, operands); // three byte variant
		}
	}

	void backend::emit_opcode_prefix_rex(const instruction* inst, const operand* operands) {
		if(inst->is_rexw() || is_extended_reg(operands[0]) || is_extended_reg(operands[1]) || is_low_gpr(operands[0]) || is_low_gpr(operands[1])) {
			push_byte(get_instruction_rex(inst, operands));
		}
		else if(is_operand_mem(operands[0].type)) {
			emit_opcode_prefix_rex_mem(operands[0].memory);
		}
		else if(is_operand_mem(operands[1].type)) {
			emit_opcode_prefix_rex_mem(operands[1].memory);
		}
	}
		
	void backend:: emit_opcode_prefix_rex_mem(const mem& memory) {
		// if our memory operand contains an extended register we have to emit a rex prefix
		if((memory.has_base && memory.base.index >= 8) || (memory.has_index && memory.index.index >= 8)) {
			push_byte(detail::rex(false, 0, memory.base.index, memory.index.index));
		}
	}

	void backend::emit_opcode_prefix_vex_two(const instruction* inst, const operand* operands) {
		const u8 rex = get_instruction_rex(inst, operands);
		u8 prefix = 0;

		push_byte(0xc5); // two byte VEX prefix

		prefix |= !(rex & 0b00000100) << 7;                  // ~R    [X_______]
		prefix |= get_instruction_vvvv(inst, operands) << 3; // ~vvvv [_XXXX___]
		prefix |= inst->get_l() << 2;                        // L     [_____X__]
		prefix |= inst->get_imp();                           // IMP   [______XX]

		push_byte(prefix);
	}

	void backend::emit_opcode_prefix_vex_three(const instruction* inst, const operand* operands) {
		const u8 rex = get_instruction_rex(inst, operands);
		u8 prefix[2] = {};

		// VEX/XOP prefix
		if(inst->is_xop()) {
			push_byte(0x8f);
		} else {
			push_byte(0xc4);
		}

		prefix[0] |= !(rex & 0b00000100) << 7;                  // ~R         [X_______] 
		prefix[0] |= !(rex & 0b00000010) << 6;                  // ~X         [_X______]
		prefix[0] |= !(rex & 0b00000001) << 5;                  // ~B         [__X_____] 
		prefix[0] |= inst->get_map_select();                    // map_select [___XXXXX]

		prefix[1] |= static_cast<u8>((inst->is_rexw()) << 7);   // W/E        [X_______]
		prefix[1] |= get_instruction_vvvv(inst, operands) << 3; // ~vvvv      [_XXXX___]
		prefix[1] |= inst->get_l() << 2;                        // L          [_____X__]
		prefix[1] |= inst->get_imp();                           // pp         [______XX]
		
		push_byte(prefix[0]);
		push_byte(prefix[1]);
	}

	void backend::emit_data_operand(u64 data, u16 bit_width) {
		for(u16 i = 0; i < bit_width / 8; ++i) {
			push_byte(data >> (i * 8) & 0xFF);
		}
	}

	auto backend::get_instruction_rex(const instruction* inst, const operand* operands) -> u8 {
		const bool is_rexw = inst->is_rexw();

		u8 rx = get_modrm_reg(inst, operands);
		u8 base = get_modrm_rm(inst, operands);
		u8 index = get_sib_index(inst, operands);

		return detail::rex(is_rexw, rx, base, index);
	}

	auto backend::get_instruction_vvvv(const instruction* inst, const operand* operands) -> u8 {
		return static_cast<u8>((~get_extending_reg(inst, operands) & 0b00001111));
	}

	auto backend::get_instruction_v(const instruction* inst, const operand* operands) -> u8 {
		u8 rx = get_extending_reg(inst, operands);

		if(
			is_operand_mem(inst->operands[1]) &&
			operands[1].memory.has_sse_operands() &&
			operands[1].memory.index.index > 15
		) {
			rx = operands[1].memory.index.index;
		}

		return rx & 0b00010000;
	}

		
	auto backend::get_extending_reg(const instruction* inst, const operand* operands) -> u8 {
		u8 ext = 0;

		const u8 registers[4] = {
			detail::extract_operand_reg(operands[0]),
			detail::extract_operand_reg(operands[1]),
			detail::extract_operand_reg(operands[2]),
			detail::extract_operand_reg(operands[3]),
		};

		switch(inst->enc) {
			case ENC_VEX_VM:   return registers[0];
			case ENC_EVEX_RMZ: return registers[0];
			case ENC_XOP_VM:   return registers[0];
			case ENC_VEX_RVM:  return registers[1];
			case ENC_VEX_RVMS: return registers[1];
			case ENC_VEX_MVRR: return registers[1];
			case ENC_EVEX_MVR: return registers[1];
			case ENC_VEX:      return registers[2];
			case ENC_VEX_RMV:  return registers[2];
			case ENC_VEX_MVR:  return registers[2];
			case ENC_XOP:      return 0;
			case ENC_VEX_R:    return 0;
			case ENC_VEX_MR:   return 0;
			case ENC_EVEX_M:   return 0;
			case ENC_EVEX_MR:  return 0;
			case ENC_VEX_RVMN: return 0;
			case ENC_EVEX_RVM: ext = registers[1]; break;
			case ENC_EVEX_VM:  ext = registers[0]; break;
			case ENC_EVEX_RM:  ext = 0; break;
			default: break;
		}

		switch(inst->enc) {
			case ENC_EVEX_RVM: {
				if(inst->operand_count == 2) {
					ext = 0;
				}

				break;
			}
			case ENC_EVEX_RM: {
				if(
					inst->operand_count == 3 && 
					is_operand_imm(inst->operands[2]) == false
				) {
					ext = registers[1];
				}
				else if(
					inst->operand_count == 4 && 
					is_operand_imm(inst->operands[3])
				) {
					ext = registers[1];
				}
				
				break;
			}
			default: break;
		}

		return ext;
	}

	auto backend::get_modrm_reg(const instruction* inst, const operand* operands) -> u8 {
		const u8 registers[4] = {
			detail::extract_operand_reg(operands[0]),
			detail::extract_operand_reg(operands[1]),
			detail::extract_operand_reg(operands[2]),
			detail::extract_operand_reg(operands[3]),
		};

		u8 reg = 0;

		switch(inst->enc) {
			case ENC_VEX_RVMS: reg = registers[0]; break;
			case ENC_VEX_RVMN: reg = registers[0]; break;
			case ENC_EVEX_RVM: reg = registers[0]; break;
			case ENC_VEX_RVM:  reg = registers[0]; break;
			case ENC_VEX:      reg = registers[1]; break;
			case ENC_VEX_R:    reg = registers[0]; break;
			case ENC_VEX_MVRR: reg = registers[2]; break;
			case ENC_VEX_MVR:  reg = registers[1]; break;
			case ENC_VEX_MR:   reg = registers[1]; break;
			case ENC_VEX_RM:   reg = registers[0]; break;
			case ENC_VEX_RMV:  reg = registers[0]; break;
			case ENC_EVEX_MVR: reg = registers[1]; break; 
			case ENC_EVEX_VM:  reg = registers[2]; break; 
			case ENC_EVEX_MR:  reg = registers[1]; break;
			case ENC_EVEX_RMZ: reg = registers[0]; break;
			case ENC_EVEX_RM:  reg = registers[0]; break;
			case ENC_MR:       reg = registers[1]; break;
			case ENC_RM:       reg = registers[0]; break;
			case ENC_RMR:      reg = registers[1]; break;
			default: break;
		}

		switch(inst->enc) {
			case ENC_EVEX_RVM: {
				if(inst->operand_count == 2) {
					if(
						is_operand_reg(inst->operands[0]) && 
						is_operand_reg(inst->operands[1]) &&
						inst->has_masked_operand() == false
					) {
						reg = registers[1];
					}
					else if(
						inst->has_masked_operand() && 
						is_operand_mem(inst->operands[inst->get_masked_operand()]) &&
						operands[inst->get_masked_operand()].memory.has_base == false
					) {
						reg = registers[1];
					}
				}

				break;
			}
			case ENC_EVEX_MR: {
				if(is_operand_mem(inst->operands[1])) {
					reg = registers[0];
				}
				
				if(is_operand_reg(inst->operands[0]) && inst->has_masked_operand()) {
					reg = registers[0];
				}

				break;
			}
			default: break;
		}

		return reg;

	}

	auto backend::get_modrm_rm(const instruction* inst, const operand* operands) -> u8 {
		const u8 registers[4] = {
			detail::extract_operand_reg(operands[0]),
			detail::extract_operand_reg(operands[1]),
			detail::extract_operand_reg(operands[2]),
			detail::extract_operand_reg(operands[3]),
		};

		u8 rm = 0;

		switch(inst->enc) {
			case ENC_VEX_RVMS: rm = registers[2]; break;
			case ENC_VEX_RVMN: rm = registers[1]; break;
			case ENC_EVEX_RVM: rm = registers[2]; break;
			case ENC_VEX_RVM:  rm = registers[2]; break;
			case ENC_VEX:      rm = registers[0]; break;
			case ENC_VEX_MVRR: rm = registers[0]; break;
			case ENC_VEX_MVR:  rm = registers[0]; break;
			case ENC_VEX_MR:   rm = registers[0]; break;
			case ENC_VEX_RM:   rm = registers[1]; break;
			case ENC_VEX_VM:   rm = registers[1]; break;
			case ENC_XOP_VM:   rm = registers[1]; break;
			case ENC_XOP:      rm = registers[0]; break;
			case ENC_VEX_RMV:  rm = registers[1]; break;
			case ENC_EVEX_MVR: rm = registers[0]; break; 
			case ENC_EVEX_VM:  rm = registers[1]; break; 
			case ENC_EVEX_MR:  rm = registers[0]; break; 
			case ENC_EVEX_RMZ: rm = registers[2]; break;
			case ENC_EVEX_RM:  rm = registers[2]; break;
			case ENC_NORMAL:   rm = registers[0]; break;
			case ENC_NORMALD:  rm = registers[0]; break;
			case ENC_MR:       rm = registers[0]; break;
			case ENC_M:        rm = registers[0]; break;
			case ENC_RM:       rm = registers[1]; break;
			case ENC_RMR:      rm = registers[0]; break;
			case ENC_R:        rm = registers[0]; break;
			default: break;
		}

		switch(inst->enc) {
			case ENC_NORMAL: {
				if(inst->operands[0] == OP_EAX || inst->operands[0] == OP_RAX || inst->operands[0] == OP_AX) {
					rm = registers[1];
				}

				if(inst->operands[0] == OP_ST0) {
					rm = registers[1];
				}
				break;
			}
			case ENC_EVEX_RVM: {
				if(inst->operand_count == 2) {
					if(
						is_operand_reg(inst->operands[0]) && 
						is_operand_reg(inst->operands[1]) &&
						inst->has_masked_operand() == false
					) {
						rm = registers[0];
					}
					else if(
						inst->has_masked_operand() && 
						is_operand_mem(inst->operands[inst->get_masked_operand()]) &&
						operands[inst->get_masked_operand()].memory.has_base == false
					) {
						rm = registers[0];
					}
					else {
						rm = registers[1];
					}
				}

				break;
			}
			case ENC_EVEX_RMZ: 
			case ENC_EVEX_RM: {
				if(
					inst->operand_count == 3 &&
					!(is_operand_mem(inst->operands[2]) || is_operand_reg(inst->operands[2]))
				) {
					rm = registers[1];
				}
				else if(inst->operand_count == 2) {
					rm = registers[1];
				}

				break;
			}
			case ENC_EVEX_MR: {
				if(is_operand_mem(inst->operands[1])) {
					rm = registers[1];
				}
				
				if(is_operand_reg(inst->operands[0]) && inst->has_masked_operand()) {
					rm = registers[1];
				}

				break;
			}
			default: break;
		}

		return rm;

	}

	auto backend::get_sib_index(const instruction* inst, const operand* operands) -> u8 {
		u8 index = 0;

		const u8 registers[4] = {
			detail::extract_operand_reg(operands[0]),
			detail::extract_operand_reg(operands[1]),
			detail::extract_operand_reg(operands[2]),
			detail::extract_operand_reg(operands[3]),
		};

		switch(inst->enc) {
			case ENC_EVEX_MVR: if(registers[2] > 15) { return registers[2]; } break;
			case ENC_EVEX_VM:  if(registers[1] > 15) { return registers[1]; } break;
			case ENC_VEX_RM:   if(registers[1] > 15) { return registers[1]; } break;
			case ENC_VEX_VM:   if(registers[1] > 15) { return registers[1]; } break;
			case ENC_VEX_RVM:  if(registers[2] > 15) { return registers[2]; } break;
			case ENC_VEX_RVMN: if(registers[2] > 15) { return registers[2]; } break;
			case ENC_EVEX_MR:  if(registers[2] > 15) { return registers[2]; } break;
			case ENC_EVEX_RVM: if(registers[2] > 15) { return registers[2]; } break;
			case ENC_EVEX_RMZ: if(registers[2] > 15) { return registers[2]; } break;
			case ENC_EVEX_RM:  if(registers[2] > 15) { return registers[2]; } break;
			default: break;
		}

		if(inst->has_mem_operand()) {
			const mem mem = operands[inst->get_mem_operand()].memory;

			if(mem.has_index) {
				index = mem.index.index;
			}
		}

		switch(inst->enc) {
			case ENC_EVEX_RVM: {
				if(inst->operand_count == 2) {
					if(
						is_operand_reg(inst->operands[0]) && 
						is_operand_reg(inst->operands[1]) &&
						inst->has_masked_operand() == false &&
						registers[0] > 15
					) {
						index = registers[0];
					}
					else if(
						is_operand_reg(inst->operands[0]) && 
						is_operand_reg(inst->operands[1]) &&
						inst->has_masked_operand() == true &&
						registers[1] > 15
					) {
						index = registers[1];
					}
				}

				break;
			}
			case ENC_EVEX_MR: {
				if(
					is_operand_reg(inst->operands[0]) &&
					is_operand_reg(inst->operands[1]) &&
					registers[0] > 15
				) {
					return registers[0]; 
				}

				break;
			}
			// special case for VSIB
			case ENC_EVEX_RMZ:
			case ENC_EVEX_RM: {
				if(index > 15 && detail::extract_operand_reg(operands[1]) > 7) {
					index = 0;
				}

				if(inst->operand_count == 2 && is_operand_reg(inst->operands[1]) && registers[1] > 15) {
					index = registers[1];
				}
				else if(
					inst->operand_count == 3 &&
					is_operand_reg(inst->operands[1]) && 
					registers[1] > 15 &&
					!(is_operand_mem(inst->operands[2]) || is_operand_reg(inst->operands[2]))
				) {
					index = registers[1];
				}

				break;
				break;
			}
			case ENC_VEX_RMV: {
				if(index > 15 && detail::extract_operand_reg(operands[1]) > 7) {
					index = 0;
				}

				break;
			}
			default: break;
		}

		return index;
	}

	auto backend::get_mask_reg(const instruction* inst, const operand* operands) -> u8 {
		if(inst->has_masked_operand() == false) {
			return 0;
		}

		u8 i = inst->get_masked_operand();

		if(is_operand_mem(inst->operands[i])) {
			return operands[i].mm.k; // masked memory
		}

		return operands[i].mr.k; // masked register
	}

	auto backend::has_sib(const operand* operands) -> bool {
		operand operand;

		for(u8 i = 0; i < 3; ++i) {
			if(is_operand_mem(operands[i].type)) {
				operand = operands[i];
				break;
			}
		}

		if(operand.type == OP_NONE) {
			return false;
		}

		if(operand.type == OP_TMEM) {
			return true;
		}

		mem memory = operand.memory;
	
		if(memory.has_index) {
			return true;
		}

		if(is_stack_pointer(reg(memory.base))) {
			return true;
		}

		if(memory.has_base == false) {
			return true; // absolute address
		}

		return false;
	}

	void backend::push_byte(u8 value) {
		m_data[m_data_size++] = value;
	}
} // namespace baremetal
