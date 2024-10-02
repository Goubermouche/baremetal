#include "assembler_backend.h"
#include "assembler/instruction/instruction.h"
#include "assembler/instruction/operands/operands.h"
#include "utility/types.h"

#include <utility/algorithms/sort.h>

namespace baremetal {
	namespace detail {
		auto sign_extend_representable(u64 value, u8 src) -> bool {
			const uint64_t mask = (1ULL << src) - 1;
			const u64 shrunk = value & mask;

			const u64 extended_source   = sign_extend(shrunk, src);
			const u64 extended_original = sign_extend(value, 64);

			return extended_source == extended_original;
		}

		auto sign_extend(u64 x, u8 x_bits) -> u64 {
			if(x >> (x_bits - 1)) {
				// u8 diff = n - x_bits;
				return x | (utility::limits<u64>::max() << x_bits);
			}

			return x;
		}

		auto is_operand_of_same_kind(operand_type a, operand_type b) -> bool {
			switch(a) {
				// don't just consider regular equalities, focus on register bit widths as well
				case OP_AL:  return b == OP_AL  || b == OP_CL  || b == OP_R8;  // 8 bits
				case OP_AX:  return b == OP_AX  || b == OP_DX  || b == OP_R16; // 16 bits
				case OP_EAX: return b == OP_EAX || b == OP_ECX || b == OP_R32; // 32 bits
				case OP_RAX: return b == OP_RAX || b == OP_RCX || b == OP_R64; // 64 bits
				case OP_REL_UNKNOWN: return is_operand_rip_rel(b);
				default: return a == b; // regular compares
			}
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
	
		auto extract_operand_reg_beg(const operand& op) -> u8 {
			if(is_operand_reg(op.type)) {
				return op.r;
			}
	
			if(is_operand_mem(op.type) && op.memory.has_base) {
				return op.memory.base.index;
			}
	
			return utility::limits<u8>::max();
		}

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
	} // namespace detail

	assembler_backend::assembler_backend(assembler_context* context)
		: m_current_inst_begin(0), m_module(context) {}

	void assembler_backend::clear() {
		m_module.clear();
		m_current_inst_begin = 0;
	}

	auto assembler_backend::get_bytes() const -> utility::dynamic_array<u8> {
		return m_module.emit_binary();
	}

	auto assembler_backend::get_instruction_size(u32 index, const operand* operands) -> u8 {
		assembler_context temp;
		assembler_backend backend(&temp);

		backend.emit_instruction_direct(assembler_backend::find_direct(index, operands), operands);

		return backend.get_module().get_size_current_section();
	}
	void assembler_backend::emit_instruction(u32 index, const operand* operands) {
		// locate the actual instruction we want to assemble (this doesn't have to match the specified
		// index, since we can apply optimizations which focus on stuff like shorter encodings)
		const instruction* inst = find_optimized_instruction(index, operands);
		emit_instruction_direct(inst, operands);
	}

	void assembler_backend::emit_instruction_direct(const instruction* inst, const operand* operands) {
		// mark the instruction start
		instruction_begin(operands); 

		// emit individual instruction parts
		emit_instruction_prefix(inst, operands);
		emit_instruction_opcode(inst, operands);
		emit_instruction_mod_rm(inst, operands);
		emit_instruction_sib(operands);
		emit_operands(inst, operands);
	}

	auto assembler_backend::get_module() -> module& {
		return m_module;
	}

	auto assembler_backend::find_direct(u32 index, const operand* operands) -> const instruction* {
		const instruction& first = instruction_db[index];
		u8 operand_count = 0;

		for(operand_count = 0; operand_count< 4; ++operand_count) {
			// utility::console::print("is {}\n", operand_type_to_string(operands[operand_count].type));
			if(operands[operand_count].type == OP_NONE) {
				break;
			}
		}

		// utility::console::print("enter\n");

		while(utility::compare_strings(first.name, instruction_db[index].name) == 0) {
			// utility::console::print("iter\n");
			const instruction& other = instruction_db[index++];

			if(operand_count != other.operand_count) {
				// utility::console::print("{}\n", operand_count);
				continue;
			}

			for(u8 i = 0; i < operand_count; ++i) {
				if(other.operands[i] != operands[i].type) {
					// utility::console::print("{} vs {}\n", operand_type_to_string(other.operands[i]), operand_type_to_string(operands[i].type));
					goto end;
				}
			}

			return &other;

	end:
			continue;
		}


		ASSERT(false, "invalid instruction match");
		return nullptr;
	}

	auto assembler_backend::find_optimized_instruction(u32 index, const operand* operands)  -> const instruction* {
		u8 imm_index = utility::limits<u8>::max();
		u8 unknown_index = utility::limits<u8>::max();

		// locate the first immediate operand
		for(u8 i = 0; i < 4; ++i) {
			if(is_operand_imm(operands[i].type)) {
				imm_index = i;
				break;
			}
		}

		for(u8 i = 0; i < 4; ++i) {
			if(operands[i].unknown) {
				unknown_index = i;
				break;
			}
		}

		// no immediate operand, return the original variant
		if(imm_index == utility::limits<u8>::max() && unknown_index == utility::limits<u8>::max()) {
			return &instruction_db[index];
		}

		// store a list of legal variants, from which we'll pick the best one
		utility::dynamic_array<const instruction*> legal_variants = {};
		const imm& imm_op = operands[imm_index].immediate;

		// some instructions have a special optimization index, check if we have it
		// if we have a valid context index, the original index, provided as a parameter, will
		// be replaced by this index
		if(instruction_db[index].has_special_index() && unknown_index == utility::limits<u8>::max()) {
			const u16 context_index = instruction_db[index].get_special_index();

			// switch on the context kind
			switch(instruction_db[index].get_special_kind()) {
				case 0: {
					// if we have a destination which uses a 64 bit register, and an operand which fits into 32 bits or
					// less we can look for a smaller destination
					if(operands[0].type == OP_R64 && imm_op.min_bits <= 32) {
						// verify if it's safe to zero extend the operand (since we're implicitly going from 32 to 64
						// bits) we can't zero extend 
						if(imm_op.sign == false) {
							index = context_index;
						}
					}

					break;
				}
				case 1: {
					// if we have a source operand which is equal to 1, we can use a shorter encoding, in basically all
					// cases we can just return, since the operand is effectively removed
					if(operands[1].immediate.value == 1) {
						return &instruction_db[context_index];
					}

					break; // we're not using the optimization index, continue
				}
				case 2: {
					// truncate to 8 bits, this is only used with imul instructions
					const u64 truncated = operands[2].immediate.value & 0b011111111;
					const u64 extend = detail::sign_extend(truncated, 8);

					if(extend == operands[2].immediate.value) {
						return &instruction_db[context_index];
					}

					break;
				}
				default: {
					ASSERT(false, "unknown context kind");
				}
			}
		}

		u32 current_index = index; // index of the current variant

		// locate all legal variants of our instruction, since our instructions are sorted
		// by their operands we can just increment the index as long as the two variants
		// are legal
		u8 imm_or_unresolved = imm_index == utility::limits<u8>::max() ? unknown_index : imm_index;

		if(imm_index != utility::limits<u8>::max()) {
			while(is_legal_variant(index, current_index, imm_index)) {
				legal_variants.push_back(&instruction_db[current_index++]);
			}
		}
		else {
			while(is_legal_variant_unknown(index, current_index, unknown_index)) {
				legal_variants.push_back(&instruction_db[current_index++]);
			}
		}

		// one legal variant
		if(legal_variants.get_size() == 1) {
			current_variants.push_back(legal_variants[0]->operands[unknown_index]);
			return legal_variants[0];
		}

		// sort by the smallest source operands, we need to do this for cases where one of the
		// variants has a destination operand which isn't a generic register, but a specific
		// one (ie. an ax register). In these cases we lose the guarantee of them being sorted
		// from smallest to biggest immediate operands, hence we have to sort them.
		utility::stable_sort(legal_variants.begin(), legal_variants.end(), [=](auto a, auto b) {
			const u16 a_width = get_operand_bit_width(a->operands[imm_or_unresolved]);
			const u16 b_width = get_operand_bit_width(b->operands[imm_or_unresolved]);

			return a_width < b_width;
		});

		for(const auto& inst : legal_variants) {
			current_variants.push_back(inst->operands[unknown_index]);
		}

		if(unknown_index != utility::limits<u8>::max()) {
			ASSERT(!legal_variants.is_empty(), "no variants found\n");
			// largest legal variant - pessimistic 
			return legal_variants.get_last();
		}

		// multiple legal variants, determine the best one (since our data is sorted from smallest
		// source operands to largest, we can exit as soon as we get a valid match)
		for(const instruction* inst : legal_variants) {
			const u16 src_bits = get_operand_bit_width(inst->operands[imm_index]);
			const u16 dst_bits = get_operand_bit_width(inst->operands[0]);

			// check if there is a possibility of sign extending the immediate
			if(src_bits < dst_bits) {
				ASSERT(src_bits <= utility::limits<u8>::max(), "invalid range");

				// assume we're sign extending
				if(detail::sign_extend_representable(imm_op.value, static_cast<u8>(src_bits))) {
					return inst;
				}
			}

			// check if the source operand is representable with a smaller immediate
			if(src_bits >= imm_op.min_bits) {
				return inst;
			}
		}

		ASSERT(false, "invalid instruction match");
		return nullptr;
	}

	auto assembler_backend::is_legal_variant(u32 a, u32 b, u8 imm_index) -> bool {
		const u8 operand_count = instruction_db[a].operand_count;

		if(utility::compare_strings(instruction_db[a].name, instruction_db[b].name) != 0) {
			return false;
		}

		for(u8 i = 0; i < operand_count; ++i) {
			if(i == imm_index) {
				continue;
			}

			if(!detail::is_operand_of_same_kind(instruction_db[a].operands[i], instruction_db[b].operands[i])) {
				return false;
			}
		}

		return is_operand_imm(instruction_db[b].operands[imm_index]) || is_operand_rel(instruction_db[b].operands[imm_index]);
	}

	auto assembler_backend::is_legal_variant_unknown(u32 a, u32 b, u8 imm_index) -> bool {
		const u8 operand_count = instruction_db[a].operand_count;

		if(utility::compare_strings(instruction_db[a].name, instruction_db[b].name) != 0) {
			return false;
		}

		for(u8 i = 0; i < operand_count; ++i) {
			if(i == imm_index) {
				continue;
			}

			if(!detail::is_operand_of_same_kind(instruction_db[a].operands[i], instruction_db[b].operands[i])) {
				return false;
			}
		}

		return 
			is_operand_imm(instruction_db[b].operands[imm_index]) || 
			is_operand_rel(instruction_db[b].operands[imm_index]) || 
			is_operand_mem(instruction_db[b].operands[imm_index]); 
	}

	void assembler_backend::emit_instruction_prefix(const instruction* inst, const operand* operands) {
		if(inst->enc == ENC_NORMALD) {
			// instruction composed of two instructions, emit the first one here
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
			u8 mem_index = inst->get_mem_operand();
			const mem& m = operands[mem_index].memory;

			if(
				((m.base.type == REG_R32) || (m.index.type == REG_R32))
			) {
				// utility::console::print("{} {} {} {} {}\n", m.has_base, m.has_index, (int)m.s, m.displacement.value, inst->is_rexw());
				//if(m.has_base && m.has_index == false && m.s == SCALE_1 && m.displacement.value == 0) {}
				//// else if(m.has_base == false && m.has_index && m.s == SCALE_1 && m.displacement.value == 0) {}
				//else {
					push_byte(0x67);
				//}
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
			default:                                        break;
		}

		// group 1
		switch(inst->prefix & 0b00000011) {
			case LOCK:  push_byte(0xF0); break;
			case REPNE: push_byte(0xF2); break;
			case REP:   push_byte(0xF3); break;
			default:                             break;
		}
	}
	
	void assembler_backend::instruction_begin(const operand* operands) {
		m_current_inst_begin = m_module.get_size();

		utility::memset(m_regs, 0, sizeof(u8) * 4);
		m_reg_count = 0;

		for(u8 i = 0; i < 4; ++i) {
			u8 r = detail::extract_operand_reg_beg(operands[i]);

			if(r != utility::limits<u8>::max()) {
				m_regs[m_reg_count++] = r;
			}
		}
	}

	void assembler_backend::emit_instruction_opcode(const instruction* inst, const operand* operands) {
		emit_instruction_opcode_prefix(inst, operands);
		
		// emit the instruction opcode
		u64 opcode = inst->opcode;

		if(inst->is_rex() == false) {
			// VEX instructions have the leading opcode encoded in themselves, so we have to skip it here
			opcode &= 0xff;
		}
		else if(inst->enc == ENC_NORMALD) {
			// skip the first byte, since we've already pushed it (double instruction)
			opcode &= 0xff;
		}

		// opcode extensions (add a specific register to the opcode itself)
		if(inst->is_ri()) {
			if(inst->operands[0] == OP_ST0) {
				opcode += m_regs[1] & 0b00000111;
			}
			else if(inst->enc == ENC_NORMAL && is_operand_rax(inst->operands[0])) {
				opcode += m_regs[1] & 0b00000111;
			}
			else if(inst->enc == ENC_XOP_VM || inst->enc == ENC_VEX_VM) {
				opcode += m_regs[1] & 0b00000111;
			}
			else {
				opcode += m_regs[0] & 0b00000111;
			}
		}

		// append opcode bytes
		for(u8 i = 4; i-- > 1;) {
			const u8 byte = (opcode >> (i * 8)) & 0xFF;

			if(byte != 0) {
				push_byte(byte);
			}
		}

		// always push the last byte
		push_byte(opcode & 0xFF);
	}

	void assembler_backend::emit_instruction_opcode_prefix(const instruction* inst, const operand* operands) {
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
			ASSERT(false, "unknown instruction encoding specified (opcode prefix)\n");
		}
	}

	void assembler_backend::emit_opcode_prefix_rex(const instruction* inst, const operand* operands) {
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

	void assembler_backend::emit_opcode_prefix_rex_mem(const mem& memory) {
		// if our memory operand contains an extended register we have to emit a rex prefix
		if((memory.has_base && memory.base.index >= 8) || (memory.has_index && memory.index.index >= 8)) {
			push_byte(detail::rex(false, 0, memory.base.index, memory.index.index));
		}
	}

	auto extract_sib_index_reg(const instruction* inst, const operand* operands) -> u8 {
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

	auto extract_modrm_reg(const instruction* inst, const operand* operands) -> u8 {
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

	auto extract_modrm_rm(const instruction* inst, const operand* operands) -> u8 {
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

	auto assembler_backend::get_instruction_rex(const instruction* inst, const operand* operands) -> u8 {
		const bool is_rexw = inst->is_rexw();

		u8 rx = extract_modrm_reg(inst, operands);
		u8 base = extract_modrm_rm(inst, operands);
		u8 index = extract_sib_index_reg(inst, operands);

		return detail::rex(is_rexw, rx, base, index);
	}

	void assembler_backend::emit_opcode_prefix_vex_three(const instruction* inst, const operand* operands) {
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
		prefix[0] |= get_instruction_map_select(inst);          // map_select [___XXXXX]

		prefix[1] |= static_cast<u8>((inst->is_rexw()) << 7);   // W/E        [X_______]
		prefix[1] |= get_instruction_vvvv(inst, operands) << 3; // ~vvvv      [_XXXX___]
		prefix[1] |= get_instruction_l(inst) << 2;              // L          [_____X__]
		prefix[1] |= get_instruction_imp(inst);                 // pp         [______XX]
		
		push_byte(prefix[0]);
		push_byte(prefix[1]);
	}

	void assembler_backend::emit_opcode_prefix_vex_two(const instruction* inst, const operand* operands) {
		const u8 rex = get_instruction_rex(inst, operands);
		u8 prefix = 0;

		push_byte(0xc5); // two byte VEX prefix

		prefix |= !(rex & 0b00000100) << 7;                     // ~R    [X_______]
		prefix |= get_instruction_vvvv(inst, operands) << 3;    // ~vvvv [_XXXX___]
		prefix |= get_instruction_l(inst) << 2;                 // L     [_____X__]
		prefix |= get_instruction_imp(inst);                    // IMP    [______XX]

		push_byte(prefix);
	}

	void assembler_backend::emit_opcode_prefix_vex(const instruction* inst, const operand* operands) {
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

	void assembler_backend::emit_opcode_prefix_evex(const instruction* inst, const operand* operands) {
		const u8 rex = get_instruction_rex(inst, operands);
		const u8 modrm = extract_modrm_reg(inst, operands);
		u8 prefix[3] = {};

		push_byte(0x62); // EVEX prefix

		prefix[0] |= !(rex & 0b00000100) << 7;                  // ~R         [X_______] 
		prefix[0] |= !(rex & 0b00000010) << 6;                  // ~X         [_X______] 
		prefix[0] |= !(rex & 0b00000001) << 5;                  // ~B         [__X_____] 
		prefix[0] |= !(modrm & 0b00010000) << 4;                // ~R'        [___X____]
		prefix[0] |= get_instruction_map_select(inst);          // map select [____0XXX]

		prefix[1] |= static_cast<u8>((inst->is_rexw()) << 7);   // W          [X_______]
		prefix[1] |= get_instruction_vvvv(inst, operands) << 3; // ~VVVV      [_XXXX___]
		prefix[1] |= 0b1 << 2;                                  //            [_____1__]
		prefix[1] |= get_instruction_imp(inst);                 // IMP        [______XX]

		prefix[2] |= get_evex_zero(inst) << 7;                  // zero mask  [X_______]
		prefix[2] |= get_evex_operand_type(inst);               // size       [_XX_____]
		prefix[2] |= inst->has_broadcast_operand() << 4;        // broadcast  [___X____]
		prefix[2] |= !get_instruction_v(inst, operands) << 3;   // ~V         [____X___]
		prefix[2] |= get_mask_register(inst, operands);         // mask       [_____XXX]

		push_byte(prefix[0]);
		push_byte(prefix[1]);
		push_byte(prefix[2]);
	}

	void assembler_backend::emit_instruction_mod_rm(const instruction* inst, const operand* operands) {
		u8 rx = extract_modrm_reg(inst, operands);
		u8 destination = extract_modrm_rm(inst, operands);

		if(inst->is_rm() && !inst->is_is4()) {
			rx = inst->get_rm();
		}

		// memory operands
		for(u8 i = 0; i < inst->operand_count; ++i) {
			if(!is_operand_mem(operands[i].type)) {
				continue;
			}

			const bool has_sib = has_sib_byte(operands);
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
				push_byte(detail::indirect(rx, has_sib ? 0b100 : memory.base.index));
			}
			else if(memory.displacement.min_bits <= 8) {
				// 8 bit displacement
				push_byte(detail::indirect_disp_8(rx, has_sib ? 0b100 : memory.base.index));
			}
			else {
				// 32 bit displacemen
				push_byte(detail::indirect_disp_32(rx, has_sib ? 0b100 : memory.base.index));
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

	void assembler_backend::emit_instruction_sib(const operand* operands) {
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

	auto assembler_backend::has_sib_byte(const operand* operands) -> bool {
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

	void assembler_backend::emit_operands(const instruction* inst, const operand* operands) {
		for(u8 i = 0; i < inst->operand_count; ++i) {
			const operand_type current = inst->operands[i];

			if(is_operand_imm(current)) {
				if(operands[i].type == OP_REL_UNKNOWN) {
					m_module.add_relocation(operands[i].symbol, get_operand_bit_width(current) / 8);
					emit_data_operand(0, get_operand_bit_width(current));
				}
				else {
					// immediate operand
					emit_data_operand(operands[i].immediate.value, get_operand_bit_width(current));
				}
			}
			else if(is_operand_moff(current)) {
				// memory offset operand (always 64-bit)
				emit_data_operand(operands[i].memory_offset.value, 64);
			}
			else if(is_operand_rel(current)) {
				// relocation operand
				const u16 operand_size = get_operand_bit_width(current);

				if(operands[i].type == OP_REL_UNKNOWN) {
					m_module.add_relocation(operands[i].symbol, get_operand_bit_width(current) / 8);
					emit_data_operand(0, operand_size);
				}
				else {
					// const i32 new_displacement = operands[i].relocation.value - (get_current_inst_size() + operand_size / 8);
					emit_data_operand(operands[i].immediate.value, operand_size);
				}
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
						i32 new_displacement = static_cast<i32>(displacement.value - (get_current_inst_size() + 4));

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

	void assembler_backend::emit_data_operand(u64 data, u16 bit_width) {
		for(u16 i = 0; i < bit_width / 8; ++i) {
			push_byte(data >> (i * 8) & 0xFF);
		}
	}

	auto assembler_backend::get_instruction_vvvv(const instruction* inst, const operand* operands) -> u8 {
		switch(inst->enc) {
			case ENC_VEX_VM:
			case ENC_EVEX_RMZ:
			case ENC_XOP_VM:   return static_cast<u8>((~operands[0].r & 0b00001111));
			case ENC_VEX_RVM:  
			case ENC_VEX_RVMS: 
			case ENC_VEX_MVRR: 
			case ENC_EVEX_MVR: return static_cast<u8>((~operands[1].r & 0b00001111));
			case ENC_VEX:      
			case ENC_VEX_RMV:  
			case ENC_VEX_MVR:  return static_cast<u8>((~operands[2].r & 0b00001111));
			case ENC_XOP:      
			case ENC_VEX_R:    
			case ENC_VEX_MR:   
			case ENC_VEX_RM:    
			case ENC_EVEX_M:
			case ENC_EVEX_MR:  
			case ENC_VEX_RVMN: return 0b1111; 
			case ENC_EVEX_RVM: {
				if(inst->operand_count == 2) {
					return 0b1111; 
				}

				return static_cast<u8>((~operands[1].r & 0b00001111));
			}
			case ENC_EVEX_VM: {
				if(is_operand_mem(inst->operands[0])) {
					return 0;
				}

				if(is_operand_mem(inst->operands[1])) {
					return static_cast<u8>((~m_regs[0] & 0b00001111));
				}

				if(inst->operand_count == 3) {
					return static_cast<u8>((~m_regs[0] & 0b00001111));
				}

				return static_cast<u8>((~m_regs[m_reg_count - 1] & 0b00001111));
			}
			case ENC_EVEX_RM: {
				if(m_reg_count == 3 || (is_operand_mem(inst->operands[2]) && operands[2].memory.has_base == false)) {
					return static_cast<u8>((~operands[1].r & 0b00001111));
				}

				return 0b1111 ;
			} 
			default: ASSERT(false, "unhandled vvvv encoding {}\n", (i32)inst->enc);
		}

		return 0; // unreachable
	}

	auto assembler_backend::get_instruction_v(const instruction* inst, const operand* operands) -> u8 {
		switch(inst->enc) {
			case ENC_VEX_VM:
			case ENC_EVEX_M:
			case ENC_EVEX_VM:  return static_cast<bool>((operands[0].r & 0b00010000));
			case ENC_VEX_RVM:   
			case ENC_EVEX_MVR: return static_cast<bool>((operands[1].r & 0b00010000));
			case ENC_VEX_RM:  
			case ENC_EVEX_RMZ:
			case ENC_VEX_MR:   return 0;
			case ENC_EVEX_RVM: {
				if(inst->operand_count == 2) {
					return 0; 
				}

				return static_cast<bool>((operands[1].r & 0b00010000));
			}
			case ENC_EVEX_RM:{
				if(
					is_operand_mem(inst->operands[1]) &&
					operands[1].memory.has_index && 
					is_sse_reg(operands[1].memory.index)
				) {
					return static_cast<bool>((operands[1].memory.index.index & 0b00010000));
				}

				if(inst->operand_count == 2 || (m_reg_count == 2 && !is_operand_mem(inst->operands[2]))) {
					return 0;
				}

				return static_cast<bool>((operands[1].r & 0b00010000));
			}
			case ENC_EVEX_MR: {
				if(
					inst->operand_count == 2 || 
					(inst->operand_count == 3 && is_operand_imm(inst->operands[inst->operand_count - 1]))
				) {
					return 0; 
				}

				return static_cast<bool>((operands[1].r & 0b00010000));
			} 
			default: ASSERT(false, "unhandled evex prefix\n");
		}

		return 0; // unreachable
	}

	auto assembler_backend::get_mask_register(const instruction* inst, const operand* operands) -> u8 {
		if(inst->has_masked_operand() == false) {
			return 0;
		}

		u8 i = inst->get_masked_operand();

		if(is_operand_mem(inst->operands[i])) {
			return operands[i].mm.k; // masked memory
		}

		return operands[i].mr.k; // masked register
	}

	auto assembler_backend::get_instruction_map_select(const instruction* inst) -> u8 {
		if(inst->is_evex()) {
			if(inst->is_map6()) {
				return 0b110; 
			}

			if(inst->is_map5()) {
				return 0b101; 
			}
		}
		
		if(inst->is_xop()) {
			switch(inst->enc) {
				case ENC_XOP:    return 0b01001;
				case ENC_XOP_VM: return 0b01010;
				default: ASSERT(false, "unknown xop encoding");
			}
		}

		switch((inst->opcode & 0xffff00)) {
			case 0x000000: return 0b000; 
			case 0x000f00: return 0b001; 
			case 0x0f3800: return 0b010;
			case 0x0f3a00: return 0b011;
			default: ASSERT(false, "unknown leading opcode 1 {}", inst->opcode & 0xffff00);
		}

		return 0;
	}

	auto assembler_backend::get_evex_operand_type(const instruction* inst) -> u8 {
		if(inst->op_size == OPS_256) {
			return 0b00100000;
		}

		if(inst->op_size == OPS_512) {
			return  0b01000000;
		}

		return 0;
	}

	auto assembler_backend::get_instruction_imp(const instruction* inst) -> u8 {
		if(inst->prefix == OPERAND_SIZE_OVERRIDE) {
			return 0b01;
		}

		if(inst->prefix == REP) {
			return 0b10;
		}

		if(inst->prefix == REPNE) {
			return 0b11;
		}

		return 0;
	}

	auto assembler_backend::get_instruction_l(const instruction* inst) -> bool {
		if(inst->is_l1()) {
			return true;
		}

		if(inst->is_l0()) {
			return false;
		}

		// vector length (0 = 128b, 1 = 256b)
		return inst->op_size == OPS_256;
	}

	auto assembler_backend::get_evex_zero(const instruction* inst) -> bool {
		switch (inst->operands[0]) {
			case OP_XMM_KZ:	
			case OP_YMM_KZ:	
			case OP_ZMM_KZ: return true; 
			default:        return false;
		}
	}

	void assembler_backend::push_byte(u8 value) {
		m_module.push_byte(value);
	}

	void assembler_backend::push_data(u64 value, u8 count) {
		for(u8 i = 0; i < count; ++i) {
      u8 byte = static_cast<u8>(value & 0xFF);
      push_byte(byte);
      value >>= 8;
    }
	}

	auto assembler_backend::get_current_inst_size() const -> u8 {
		return static_cast<u8>(m_module.get_size() - m_current_inst_begin);
	}
} // namespace baremetal

