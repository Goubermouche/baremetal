#include "./backend.h"
#include <utility/algorithms/sort.h>

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

		auto sign_extend_representable(u64 value, u8 src) -> bool {
			const uint64_t mask = (1ull << src) - 1;
			const u64 shrunk = value & mask;

			const u64 extended_source   = sign_extend(shrunk, src);
			const u64 extended_original = sign_extend(value, 64);

			return extended_source == extended_original;
		}

		auto sign_extend(u64 x, u8 x_bits) -> u64 {
			if(x >> (x_bits - 1)) {
				return x | (utility::limits<u64>::max() << x_bits);
			}

			return x;
		}
	} // namespace detail

	const instruction* backend::m_inst;
	const operand* backend::m_operands;

	u8 backend::m_data_size;
	u8 backend::m_data[MAX_INSTRUCTION_SIZE];

	auto backend::get_instruction_by_name(const char* name) -> u32 {
    i32 left = 0;
    i32 right = INSTRUCTION_DB_SIZE - 1;

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

	auto is_operand_of_same_kind(operand_type a, operand_type b) -> bool {
		// TODO
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

	auto is_legal_variant(u32 a, u32 b, u8 imm_index) -> bool {
		// TODO
		const u8 operand_count = instruction_db[a].operand_count;

		if(utility::compare_strings(instruction_db[a].name, instruction_db[b].name) != 0) {
			return false;
		}

		for(u8 i = 0; i < operand_count; ++i) {
			if(i == imm_index) {
				continue;
			}

			if(!is_operand_of_same_kind(instruction_db[a].operands[i], instruction_db[b].operands[i])) {
				return false;
			}
		}

		return is_operand_imm(instruction_db[b].operands[imm_index]) || is_operand_rel(instruction_db[b].operands[imm_index]);
	}

	auto is_legal_variant_unknown(u32 a, u32 b, u8 imm_index) -> bool {
		// TODO
		const u8 operand_count = instruction_db[a].operand_count;

		if(utility::compare_strings(instruction_db[a].name, instruction_db[b].name) != 0) {
			return false;
		}

		for(u8 i = 0; i < operand_count; ++i) {
			if(i == imm_index) {
				continue;
			}

			if(!is_operand_of_same_kind(instruction_db[a].operands[i], instruction_db[b].operands[i])) {
				return false;
			}
		}

		return 
			is_operand_imm(instruction_db[b].operands[imm_index]) || 
			is_operand_rel(instruction_db[b].operands[imm_index]) || 
			is_operand_mem(instruction_db[b].operands[imm_index]); 
	}

	auto backend::get_instruction(u32 index, const operand* operands) -> const instruction* {
		// TODO
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

		if(unknown_index != utility::limits<u8>::max()) {
			ASSERT(!legal_variants.is_empty(), "no variants found\n");
			return legal_variants.get_last();
		}

		// multiple legal variants, determine the best one (since our data is sorted from smallest
		// source operands to largest, we can exit as soon as we get a valid match)
		for(const instruction* inst : legal_variants) {
			const u16 src_bits = get_operand_bit_width(inst->operands[imm_index]);
			const u16 dst_bits = get_operand_bit_width(inst->operands[0]);

			// check if there is a possibility of sign extending the immediate
			if(src_bits < dst_bits) {
				ASSERT(src_bits <= utility::limits<u8>::max(), "invalid range\n");

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

		ASSERT(false, "no instruction variant available for the provided operands\n");
		return nullptr;
	}

	auto backend::get_variants(u32 index, const operand* operands) -> utility::dynamic_array<operand_type> {
		// TODO
		utility::dynamic_array<operand_type> variants;
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

		u32 current_index = index;
		if(imm_index != utility::limits<u8>::max()) {
			while(is_legal_variant(index, current_index, imm_index)) {
				variants.push_back(instruction_db[current_index++].operands[unknown_index]);
			}
		}
		else {
			while(is_legal_variant_unknown(index, current_index, unknown_index)) {
				variants.push_back(instruction_db[current_index++].operands[unknown_index]);
			}
		}

		utility::stable_sort(variants.begin(), variants.end(), [=](auto a, auto b) {
			const u16 a_width = get_operand_bit_width(a);
			const u16 b_width = get_operand_bit_width(b);

			return a_width < b_width;
		});

		return variants;
	}

	auto backend::emit_instruction(const instruction* inst, const operand* operands) -> code {
		m_data_size = 0;
		m_operands = operands;
		m_inst = inst;

		// emit individual instruction parts
		emit_instruction_prefix();
		emit_instruction_opcode();
		emit_instruction_mod_rm();
		emit_instruction_sib();
		emit_instruction_operands();

		return { .data = m_data, .size = m_data_size };
	}

	auto backend::emit_instruction_direct(u32 index, const operand* operands) -> code {
		const instruction& first = instruction_db[index];
		u8 operand_count = 0;

		for(operand_count = 0; operand_count< 4; ++operand_count) {
			if(operands[operand_count].type == OP_NONE) {
				break;
			}
		}

		while(utility::compare_strings(first.name, instruction_db[index].name) == 0) {
			const instruction& other = instruction_db[index++];

			if(operand_count != other.operand_count) {
				continue;
			}

			for(u8 i = 0; i < operand_count; ++i) {
				if(other.operands[i] != operands[i].type) {
					goto end;
				}
			}

			return emit_instruction(&other, operands);
	end:
			continue;
		}

		ASSERT(false, "invalid instruction match\n");
		return { .data = nullptr, .size = 0 };
	}

	auto backend::emit_instruction(u32 index, const operand* operands) -> code {
		const instruction* inst = get_instruction(index, operands);
		return emit_instruction(inst, operands);
	}

	void backend::emit_instruction_operands() {
		for(u8 i = 0; i < m_inst->operand_count; ++i) {
			const operand_type current = m_inst->operands[i];

			if(is_operand_imm(current)) {
				emit_data_operand(m_operands[i].immediate.value, get_operand_bit_width(current));
			}
			else if(is_operand_moff(current)) {
				// memory offset operand (always 64-bit)
				emit_data_operand(m_operands[i].memory_offset.value, 64);
			}
			else if(is_operand_rel(current)) {
				// relocation operand
				const u16 operand_size = get_operand_bit_width(current);
				emit_data_operand(m_operands[i].immediate.value, operand_size);
			}
			else if(is_operand_mem(current)) {
				// memory displacement operand
				const mem memory = m_operands[i].memory;
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

						for(u8 j = i; j < m_inst->operand_count; ++j) {
							// if we have another operand after the current one, calculate it's size
							if(is_operand_imm(m_inst->operands[j])) { // registers are already encoded
								new_displacement -= get_operand_bit_width(m_inst->operands[j]) / 8;
							}
						}

						if(m_inst->is_is4()) {
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

		if(m_inst->is_is4()) {
			// trailing register encoded as an immediate
			push_byte(m_operands[3].r << 4);
		}
	}

	void backend::emit_instruction_prefix() {
		if(m_inst->enc == ENC_NORMALD) {
			// instruction composed of two instructions, emit the first one here (encoded as a part of the opcode)
			push_byte((m_inst->opcode & 0x0000FF00) >> 8);
		}

		if(m_inst->is_vex_xop() || m_inst->is_evex()) {
			return;
		}

		// group 4
		if(m_inst->prefix & ADDRESS_SIZE_OVERRIDE) {
			push_byte(0x67);
		}
		else if(m_inst->has_mem_operand()) {
			// memory operands with non 64-bit registers as index/base
			u8 mem_index = m_inst->get_mem_operand();
			const mem& m = m_operands[mem_index].memory;

			if(m.base.type == REG_R32 || m.index.type == REG_R32) {
				push_byte(0x67);
			}
		}

		// group 3
		if(m_inst->prefix & OPERAND_SIZE_OVERRIDE) {
			push_byte(0x66);
		}

		// group 2
		switch(m_inst->prefix & 0b00111100) {
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
		switch(m_inst->prefix & 0b00000011) {
			case LOCK:  push_byte(0xF0); break;
			case REPNE: push_byte(0xF2); break;
			case REP:   push_byte(0xF3); break;
			default:                     break;
		}
	}

	void backend::emit_instruction_opcode() {
		// instruction prefix
		if(m_inst->is_rex()) {
			emit_opcode_prefix_rex();
		}
		else if(m_inst->is_vex_xop()) {
			emit_opcode_prefix_vex();
		}
		else if(m_inst->is_evex()) {
			emit_opcode_prefix_evex();
		}
		else {
			ASSERT(false, "unknown instruction encoding '{}' specified (opcode prefix)\n", static_cast<u8>(m_inst->enc));
		}

		u64 opcode = m_inst->opcode;

		if(m_inst->is_rex() == false || m_inst->enc == ENC_NORMALD) {
			// VEX instructions have the leading opcode encoded in themselves, so we have to skip it here
			// skip the first byte, since we've already pushed it (double instruction)
			opcode &= 0xff;
		}

		// opcode extensions (add a specific register to the opcode itself)
		if(m_inst->is_ri()) {
			opcode += get_modrm_rm() & 0b00000111;
		}

		// append opcode bytes
		for(u8 i = 4; i-- > 1;) {
			const u8 byte = (opcode >> (i * 8)) & 0xff;

			if(byte != 0) {
				// only append non-zero bytes
				push_byte(byte);
			}
		}

		// always push the last byte
		push_byte(opcode & 0xff);
	}

	void backend::emit_instruction_mod_rm() {
		u8 reg = get_modrm_reg();
		u8 rm = get_modrm_rm();

		if(m_inst->is_rm() && !m_inst->is_is4()) {
			// rm-as-reg
			reg = m_inst->get_rm();
		}

		// memory operands
		for(u8 i = 0; i < m_inst->operand_count; ++i) {
			if(!is_operand_mem(m_operands[i].type)) {
				continue;
			}

			const bool sib = has_sib();
			const auto memory = m_operands[i].memory;

			ASSERT(memory.displacement.min_bits <= 32, "too many displacement bits");

			if(memory.has_base == false) {
				push_byte(detail::indirect(reg, 0b100));
			}
			else if(memory.base.type == REG_RIP) {
				push_byte(detail::indirect(reg, 0b101));
			}
			else if(is_sse_reg(memory.base)) {
				push_byte(detail::indirect(reg, 0b100));
			}
			else if(memory.displacement.value == 0) {
				push_byte(detail::indirect(reg, sib ? 0b100 : memory.base.index));
			}
			else if(memory.displacement.min_bits <= 8) {
				// 8 bit displacement
				push_byte(detail::indirect_disp_8(reg, sib ? 0b100 : memory.base.index));
			}
			else {
				// 32 bit displacemen
				push_byte(detail::indirect_disp_32(reg, sib ? 0b100 : memory.base.index));
			}

			return; // exit, we don't want more modR/M bytes; 
		}

		// forced modR/M
		if(m_inst->has_broadcast_operand()) {
			push_byte(detail::indirect(reg, rm));
		}
		else if(m_inst->is_r() || m_inst->is_rm()) {
			push_byte(detail::direct(reg, rm));
		}
	}

	void backend::emit_instruction_sib() {
		operand operand;

		// locate our memory operand
		for(u8 i = 0; i < 3; ++i) {
			if(is_operand_mem(m_operands[i].type)) {
				operand = m_operands[i];
				break;
			}
		}

		// no memory operand
		if(operand.type == OP_NONE) {
			return;
		}

		const mem memory = operand.memory;
		const u8 scale   = memory.has_base  ? memory.s           : 0b000;
		const u8 index   = memory.has_index ? memory.index.index : 0b100;
		const u8 base    = memory.has_base  ? memory.base.index  : 0b101;

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

	void backend::emit_opcode_prefix_evex() {
		const u8 rex = get_instruction_rex();
		const u8 modrm = get_modrm_reg();
		u8 prefix[3] = {};

		push_byte(0x62); // EVEX prefix

		prefix[0] |= !(rex & 0b00000100) << 7;                  // ~R         [X_______] 
		prefix[0] |= !(rex & 0b00000010) << 6;                  // ~X         [_X______] 
		prefix[0] |= !(rex & 0b00000001) << 5;                  // ~B         [__X_____] 
		prefix[0] |= !(modrm & 0b00010000) << 4;                // ~R'        [___X____]
		prefix[0] |= m_inst->get_map_select();                  // map select [____0XXX]

		prefix[1] |= static_cast<u8>((m_inst->is_rexw()) << 7); // W          [X_______]
		prefix[1] |= get_instruction_vvvv() << 3;               // ~VVVV      [_XXXX___]
		prefix[1] |= 0b1 << 2;                                  //            [_____1__]
		prefix[1] |= m_inst->get_imp();                         // IMP        [______XX]

		prefix[2] |= m_inst->get_evex_zero() << 7;              // zero mask  [X_______]
		prefix[2] |= m_inst->get_evex_operand_type();           // size       [_XX_____]
		prefix[2] |= m_inst->has_broadcast_operand() << 4;      // broadcast  [___X____]
		prefix[2] |= !get_instruction_v() << 3;                 // ~V         [____X___]
		prefix[2] |= get_mask_reg();                            // mask       [_____XXX]

		push_byte(prefix[0]);
		push_byte(prefix[1]);
		push_byte(prefix[2]);
	}

	void backend::emit_opcode_prefix_vex() {
		const u8 rex = get_instruction_rex();

		const bool x = rex & 0b00000010;
		const bool b = rex & 0b00000001;

		// a VEX instruction whose values for certain fields are VEX.~X == 1, VEX.~B == 1, VEX.W/E == 0
		// and map_select == b00001 may be encoded using the two byte VEX escape prefix (XOP)
		if(!x && !b && !m_inst->is_rexw() && ((m_inst->opcode & 0xffff00) == 0x000f00)) {
			emit_opcode_prefix_vex_two(); // two byte variant
		}
		else {
			emit_opcode_prefix_vex_three(); // three byte variant
		}
	}

	void backend::emit_opcode_prefix_rex() {
		if(
			m_inst->is_rexw() || 
			is_extended_reg(m_operands[0]) ||
			is_extended_reg(m_operands[1]) ||
			is_low_gpr(m_operands[0]) || 
			is_low_gpr(m_operands[1])
		) {
			push_byte(get_instruction_rex());
		}
		else if(is_operand_mem(m_operands[0].type)) {
			emit_opcode_prefix_rex_mem(m_operands[0].memory);
		}
		else if(is_operand_mem(m_operands[1].type)) {
			emit_opcode_prefix_rex_mem(m_operands[1].memory);
		}
	}

	void backend:: emit_opcode_prefix_rex_mem(const mem& memory) {
		// if our memory operand contains an extended register we have to emit a rex prefix for it
		if((memory.has_base && memory.base.index >= 8) || (memory.has_index && memory.index.index >= 8)) {
			push_byte(detail::rex(false, 0, memory.base.index, memory.index.index));
		}
	}

	void backend::emit_opcode_prefix_vex_two() {
		const u8 rex = get_instruction_rex();
		u8 prefix = 0;

		push_byte(0xc5); // two byte VEX prefix

		prefix |= !(rex & 0b00000100) << 7;    // ~R    [X_______]
		prefix |= get_instruction_vvvv() << 3; // ~vvvv [_XXXX___]
		prefix |= m_inst->get_l() << 2;        // L     [_____X__]
		prefix |= m_inst->get_imp();           // IMP   [______XX]

		push_byte(prefix);
	}

	void backend::emit_opcode_prefix_vex_three() {
		const u8 rex = get_instruction_rex();
		u8 prefix[2] = {};

		if(m_inst->is_xop()) {
			push_byte(0x8f); // XOP prefix
		} else {
			push_byte(0xc4); // VEX prefix
		}

		prefix[0] |= !(rex & 0b00000100) << 7;                  // ~R         [X_______] 
		prefix[0] |= !(rex & 0b00000010) << 6;                  // ~X         [_X______]
		prefix[0] |= !(rex & 0b00000001) << 5;                  // ~B         [__X_____] 
		prefix[0] |= m_inst->get_map_select();                  // map_select [___XXXXX]

		prefix[1] |= static_cast<u8>((m_inst->is_rexw()) << 7); // W/E        [X_______]
		prefix[1] |= get_instruction_vvvv() << 3;               // ~vvvv      [_XXXX___]
		prefix[1] |= m_inst->get_l() << 2;                      // L          [_____X__]
		prefix[1] |= m_inst->get_imp();                         // pp         [______XX]
		
		push_byte(prefix[0]);
		push_byte(prefix[1]);
	}

	void backend::emit_data_operand(u64 data, u16 bit_width) {
		for(u16 i = 0; i < bit_width / 8; ++i) {
			push_byte(data >> (i * 8) & 0xFF);
		}
	}

	auto backend::get_instruction_rex() -> u8 {
		const bool is_rexw = m_inst->is_rexw();

		const u8 index = get_sib_index();
		const u8 reg = get_modrm_reg();
		const u8 rm = get_modrm_rm();

		// calculate the REX prefix
		return detail::rex(is_rexw, reg, rm, index);
	}

	auto backend::get_instruction_vvvv() -> u8 {
		return static_cast<u8>((~get_extending_reg() & 0b00001111));
	}

	auto backend::get_instruction_v() -> u8 {
		u8 rx = get_extending_reg();

		if(
			is_operand_mem(m_inst->operands[1]) &&
			m_operands[1].memory.has_sse_operands() &&
			m_operands[1].memory.index.index > 15
		) {
			rx = m_operands[1].memory.index.index;
		}

		return rx & 0b00010000;
	}
	
	auto backend::get_extending_reg() -> u8 {
		u8 ext = 0;

		const u8 registers[4] = {
			detail::extract_operand_reg(m_operands[0]),
			detail::extract_operand_reg(m_operands[1]),
			detail::extract_operand_reg(m_operands[2]),
			detail::extract_operand_reg(m_operands[3]),
		};

		switch(m_inst->enc) {
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
			case ENC_EVEX_RVM: ext = registers[1]; break;
			case ENC_EVEX_VM:  ext = registers[0]; break;
			default: break;
		}

		switch(m_inst->enc) {
			case ENC_EVEX_RVM: {
				if(m_inst->operand_count == 2) {
					ext = 0;
				}

				break;
			}
			case ENC_EVEX_RM: {
				if(
					m_inst->operand_count == 3 && 
					is_operand_imm(m_inst->operands[2]) == false
				) {
					ext = registers[1];
				}
				else if(
					m_inst->operand_count == 4 && 
					is_operand_imm(m_inst->operands[3])
				) {
					ext = registers[1];
				}
				
				break;
			}
			default: break;
		}

		return ext;
	}

	auto backend::get_modrm_reg() -> u8 {
		const u8 registers[4] = {
			detail::extract_operand_reg(m_operands[0]),
			detail::extract_operand_reg(m_operands[1]),
			detail::extract_operand_reg(m_operands[2]),
			detail::extract_operand_reg(m_operands[3]),
		};

		u8 reg = 0;

		switch(m_inst->enc) {
			case ENC_VEX_RVMS: reg = registers[0]; break;
			case ENC_VEX_RVMN: reg = registers[0]; break;
			case ENC_RM:       reg = registers[0]; break;
			case ENC_EVEX_RVM: reg = registers[0]; break;
			case ENC_VEX_RVM:  reg = registers[0]; break;
			case ENC_EVEX_RMZ: reg = registers[0]; break;
			case ENC_EVEX_RM:  reg = registers[0]; break;
			case ENC_VEX_R:    reg = registers[0]; break;
			case ENC_VEX_RMV:  reg = registers[0]; break;
			case ENC_VEX_RM:   reg = registers[0]; break;
			case ENC_VEX:      reg = registers[1]; break;
			case ENC_VEX_MVR:  reg = registers[1]; break;
			case ENC_VEX_MR:   reg = registers[1]; break;
			case ENC_EVEX_MVR: reg = registers[1]; break; 
			case ENC_MR:       reg = registers[1]; break;
			case ENC_RMR:      reg = registers[1]; break;
			case ENC_EVEX_MR:  reg = registers[1]; break;
			case ENC_VEX_MVRR: reg = registers[2]; break;
			case ENC_EVEX_VM:  reg = registers[2]; break; 
			default: break;
		}

		switch(m_inst->enc) {
			case ENC_EVEX_RVM: {
				if(m_inst->operand_count == 2) {
					if(
						is_operand_reg(m_inst->operands[0]) && 
						is_operand_reg(m_inst->operands[1]) &&
						m_inst->has_masked_operand() == false
					) {
						reg = registers[1];
					}
					else if(
						m_inst->has_masked_operand() && 
						is_operand_mem(m_inst->operands[0]) &&
						m_operands[0].memory.has_base == false
					) {
						reg = registers[1];
					}
				}

				break;
			}
			case ENC_EVEX_MR: {
				if(is_operand_mem(m_inst->operands[1])) {
					reg = registers[0];
				}
				
				if(is_operand_reg(m_inst->operands[0]) && m_inst->has_masked_operand()) {
					reg = registers[0];
				}

				break;
			}
			default: break;
		}

		return reg;

	}

	auto backend::get_modrm_rm() -> u8 {
		const u8 registers[4] = {
			detail::extract_operand_reg(m_operands[0]),
			detail::extract_operand_reg(m_operands[1]),
			detail::extract_operand_reg(m_operands[2]),
			detail::extract_operand_reg(m_operands[3]),
		};

		u8 rm = 0;

		switch(m_inst->enc) {
			case ENC_VEX_MR:   rm = registers[0]; break;
			case ENC_XOP:      rm = registers[0]; break;
			case ENC_EVEX_MVR: rm = registers[0]; break; 
			case ENC_EVEX_MR:  rm = registers[0]; break; 
			case ENC_NORMAL:   rm = registers[0]; break;
			case ENC_NORMALD:  rm = registers[0]; break;
			case ENC_MR:       rm = registers[0]; break;
			case ENC_M:        rm = registers[0]; break;
			case ENC_RMR:      rm = registers[0]; break;
			case ENC_R:        rm = registers[0]; break;
			case ENC_VEX:      rm = registers[0]; break;
			case ENC_VEX_MVRR: rm = registers[0]; break;
			case ENC_VEX_MVR:  rm = registers[0]; break;
			case ENC_VEX_RVMN: rm = registers[1]; break;
			case ENC_VEX_RM:   rm = registers[1]; break;
			case ENC_RM:       rm = registers[1]; break;
			case ENC_VEX_VM:   rm = registers[1]; break;
			case ENC_XOP_VM:   rm = registers[1]; break;
			case ENC_VEX_RMV:  rm = registers[1]; break;
			case ENC_EVEX_VM:  rm = registers[1]; break; 
			case ENC_VEX_RVMS: rm = registers[2]; break;
			case ENC_EVEX_RVM: rm = registers[2]; break;
			case ENC_VEX_RVM:  rm = registers[2]; break;
			case ENC_EVEX_RMZ: rm = registers[2]; break;
			case ENC_EVEX_RM:  rm = registers[2]; break;
			default: break;
		}

		switch(m_inst->enc) {
			case ENC_NORMAL: {
				if(m_inst->operands[0] == OP_EAX || m_inst->operands[0] == OP_RAX || m_inst->operands[0] == OP_AX) {
					rm = registers[1];
				}

				if(m_inst->operands[0] == OP_ST0) {
					rm = registers[1];
				}
				break;
			}
			case ENC_EVEX_RVM: {
				if(m_inst->operand_count == 2) {
					if(
						is_operand_reg(m_inst->operands[0]) && 
						is_operand_reg(m_inst->operands[1]) &&
						m_inst->has_masked_operand() == false
					) {
						rm = registers[0];
					}
					else if(
						m_inst->has_masked_operand() && 
						is_operand_mem(m_inst->operands[0]) &&
						m_operands[0].memory.has_base == false
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
					m_inst->operand_count == 3 &&
					!(is_operand_mem(m_inst->operands[2]) || is_operand_reg(m_inst->operands[2]))
				) {
					rm = registers[1];
				}
				else if(m_inst->operand_count == 2) {
					rm = registers[1];
				}

				break;
			}
			case ENC_EVEX_MR: {
				if(is_operand_mem(m_inst->operands[1])) {
					rm = registers[1];
				}
				
				if(is_operand_reg(m_inst->operands[0]) && m_inst->has_masked_operand()) {
					rm = registers[1];
				}

				break;
			}
			default: break;
		}

		return rm;

	}

	auto backend::get_sib_index() -> u8 {
		u8 index = 0;

		const u8 registers[4] = {
			detail::extract_operand_reg(m_operands[0]),
			detail::extract_operand_reg(m_operands[1]),
			detail::extract_operand_reg(m_operands[2]),
			detail::extract_operand_reg(m_operands[3]),
		};

		switch(m_inst->enc) {
			case ENC_EVEX_VM:  if(registers[1] > 15) { return registers[1]; } break;
			case ENC_VEX_RM:   if(registers[1] > 15) { return registers[1]; } break;
			case ENC_VEX_VM:   if(registers[1] > 15) { return registers[1]; } break;
			case ENC_EVEX_MVR: if(registers[2] > 15) { return registers[2]; } break;
			case ENC_VEX_RVM:  if(registers[2] > 15) { return registers[2]; } break;
			case ENC_VEX_RVMN: if(registers[2] > 15) { return registers[2]; } break;
			case ENC_EVEX_MR:  if(registers[2] > 15) { return registers[2]; } break;
			case ENC_EVEX_RVM: if(registers[2] > 15) { return registers[2]; } break;
			case ENC_EVEX_RMZ: if(registers[2] > 15) { return registers[2]; } break;
			case ENC_EVEX_RM:  if(registers[2] > 15) { return registers[2]; } break;
			default: break;
		}

		if(m_inst->has_mem_operand()) {
			const mem mem = m_operands[m_inst->get_mem_operand()].memory;

			if(mem.has_index) {
				index = mem.index.index;
			}
		}

		switch(m_inst->enc) {
			case ENC_EVEX_RVM: {
				if(m_inst->operand_count == 2) {
					if(
						is_operand_reg(m_inst->operands[0]) && 
						is_operand_reg(m_inst->operands[1]) &&
						m_inst->has_masked_operand() == false &&
						registers[0] > 15
					) {
						index = registers[0];
					}
					else if(
						is_operand_reg(m_inst->operands[0]) && 
						is_operand_reg(m_inst->operands[1]) &&
						m_inst->has_masked_operand() == true &&
						registers[1] > 15
					) {
						index = registers[1];
					}
				}

				break;
			}
			case ENC_EVEX_MR: {
				if(
					is_operand_reg(m_inst->operands[0]) &&
					is_operand_reg(m_inst->operands[1]) &&
					registers[0] > 15
				) {
					return registers[0]; 
				}

				break;
			}
			// special case for VSIB
			case ENC_EVEX_RMZ:
			case ENC_EVEX_RM: {
				if(index > 15 && detail::extract_operand_reg(m_operands[1]) > 7) {
					index = 0;
				}

				if(m_inst->operand_count == 2 && is_operand_reg(m_inst->operands[1]) && registers[1] > 15) {
					index = registers[1];
				}
				else if(
					m_inst->operand_count == 3 &&
					is_operand_reg(m_inst->operands[1]) && 
					registers[1] > 15 &&
					!(is_operand_mem(m_inst->operands[2]) || is_operand_reg(m_inst->operands[2]))
				) {
					index = registers[1];
				}

				break;
				break;
			}
			case ENC_VEX_RMV: {
				if(index > 15 && detail::extract_operand_reg(m_operands[1]) > 7) {
					index = 0;
				}

				break;
			}
			default: break;
		}

		return index;
	}

	auto backend::get_mask_reg() -> u8 {
		if(m_inst->has_masked_operand() == false) {
			return 0;
		}

		// masked operands are always the first
		if(is_operand_mem(m_inst->operands[0])) {
			return m_operands[0].mm.k; // masked memory
		}

		return m_operands[0].mr.k; // masked register
	}

	auto backend::has_sib() -> bool {
		operand operand;

		for(u8 i = 0; i < 3; ++i) {
			if(is_operand_mem(m_operands[i].type)) {
				operand = m_operands[i];
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
