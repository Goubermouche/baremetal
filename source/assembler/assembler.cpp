#include "assembler.h"

#include "assembler/instruction/instruction.h"
#include "assembler/instruction/operands/memory.h"
#include "instruction/operands/operands.h"
#include "assembler/parser.h"
#include "parser.h"
#include "utility/containers/dynamic_string.h"
#include "utility/system/console.h"

#include <utility/algorithms/sort.h>
#include <utility/assert.h>

namespace baremetal {
	assembler::assembler() : m_current_inst_begin(0) {}

	auto inst_match(operand_type a, operand b) -> bool{
		switch(a) {
			case OP_AL:          return b.type == OP_REG8 && b.r == al.index;
			case OP_AX:          return b.type == OP_REG16 && b.r == ax.index;
			case OP_EAX:         return b.type == OP_REG32 && b.r == eax.index;
			case OP_RAX:         return b.type == OP_REG64 && b.r == rax.index;
			case OP_CL:          return b.type == OP_REG8 && b.r == cl.index;
			case OP_DX:          return b.type == OP_REG16 && b.r == dx.index;
			case OP_ECX:         return b.type == OP_REG32 && b.r == ecx.index;
			case OP_RCX:         return b.type == OP_REG64 && b.r == rcx.index;
			case OP_MEM_ADDRESS: return b.type == OP_MEM128;
			default: return a == b.type;
		}
	}

	auto is_operand_match(u32 inst_i, operand* operands) -> bool {
		const instruction& inst = instruction_db[inst_i];

		for(u8 i = 0; i < 4; ++i) {
			// if the operands at a given index are both imm we ignore their difference
			if(
				!(inst_match(inst.get_operand(i), operands[i])) &&
				!(is_operand_imm(inst.get_operand(i)) && is_operand_imm(operands[i].type)) &&
				!(is_operand_moff(inst.get_operand(i)) && is_operand_moff(operands[i].type)) &&
				!(is_operand_rel(inst.get_operand(i)) && is_operand_imm(operands[i].type))
			) {
				return false;
			}
		}

		return true;
	}

	void assembler::assemble(const utility::dynamic_string& assembly) {
		m_lex.set_text(assembly);
		m_lex.get_next_token();

		while(m_lex.current != KW_EOF) {
			if(assemble_instruction() == false) {
				return;
			}
		}
	}

#define PARSER_VERIFY(expected)                  \
  if(m_lex.current != expected) {                \
    utility::console::print("{}\n", m_assembly); \
    return false;                                \
  }

#define PARSER_EXIT()                            \
  utility::console::print("unexpected token\n"); \
  return false;

	auto imm_to_scale(const imm& i) -> scale {
		switch(i.value) {
			case 1: return  SCALE_1;
			case 2: return  SCALE_2;
			case 4: return  SCALE_4;
			case 8: return  SCALE_8;
			default: utility::console::print_err("invalid memory scale specified\n"); return SCALE_NONE;
		}
	}

	auto assembler::parse_memory(mem& memory) -> bool {
		reg current_reg = reg::create_invalid();
		imm current_imm;

		bool scale_mode = false;
		bool imm_set = false;

		// TODO: this still doesn't work with negative operands

		// entry
		while(true) {
			switch(m_lex.current) {
				// register
				case KW_CR0 ... KW_R15B: {
					if(scale_mode && imm_set) {
						// scale * reg
						memory.index = keyword_to_register(m_lex.current);
						memory.has_index = true;

						const auto scale = imm_to_scale(current_imm);

						if(scale == SCALE_NONE) {
							return false; 
						}

						memory.s = scale;

						scale_mode = false;
						imm_set = false;
					}
					else {
						current_reg = keyword_to_register(m_lex.current);
					}

					break;
				}
				case KW_REL: {
					// rel $
					m_lex.get_next_token();
					PARSER_VERIFY(KW_DOLLARSIGN);
					current_reg = rip;
					break;
				}
				case KW_ASTERISK: {
					scale_mode = true;
					break;
				}
				case KW_PLUS: {
					if(current_reg.is_valid()) {
						if(memory.has_base) {
							// index * 1
							memory.index = current_reg;
							memory.has_index = true;
							memory.s = SCALE_1;
						}
						else {
							// base
							memory.base = current_reg;
							memory.has_base = true;
						}

						current_reg = reg::create_invalid();
					}
					else if(imm_set) {
						// displacement
						memory.displacement = current_imm;
						imm_set = false;
					}

					break;
				}
				case KW_MINUS: {
					ASSERT(false, "not implemented\n");
					break;
				}
				case KW_NUMBER: {
					if(scale_mode && current_reg.is_valid()) {
						// reg * scale
						memory.index = current_reg;
						memory.has_index = true;

						const auto scale = imm_to_scale(m_lex.current_immediate);

						if(scale == SCALE_NONE) {
							return false; 
						}

						memory.s = scale;

						scale_mode = false;
						current_reg = reg::create_invalid();
					}
					else{
						current_imm = m_lex.current_immediate;
						imm_set = true;
					}

					break;
				}
				case KW_RBRACKET: {
					if(current_reg.is_valid()) {
						if(memory.has_base) {
							// index * 1
							memory.index = current_reg;
							memory.has_index = true;
							memory.s = SCALE_1;
						}
						else {
							// base
							memory.base = current_reg;
							memory.has_base = true;
						}
					}
					else if(imm_set) {
						// displacement
						memory.displacement = current_imm;
					}

					return true;
				}
				default: {
					utility::console::print_err("unexpected token received ('{}')\n", (i32)m_lex.current);
					return false;
				}
			}

			m_lex.get_next_token();
		}
	}

	auto assembler::assemble_instruction() -> bool {
		utility::dynamic_string instruction_identifier;

		PARSER_VERIFY(KW_IDENTIFIER);
		instruction_identifier = utility::dynamic_string(m_lex.current_string);

		const u32 first = find_instruction_by_name(instruction_identifier.get_data());

		if(first == utility::limits<u32>::max()) {
			utility::console::print("unknown instruction '{}' found, stopping\n", instruction_identifier);
			return false;
		}

		operand operands[4] = {{}};
		u8 operand_i = 0;

		// operands
		while(m_lex.get_next_token() != KW_EOF) {
			switch (m_lex.current) {
				// registers
				case KW_CR0 ... KW_R15B: operands[operand_i++] = operand(keyword_to_register(m_lex.current)); break;
				// numerical literals
				case KW_NUMBER:          operands[operand_i++] = operand(m_lex.current_immediate); break;
				case KW_MINUS: {
					m_lex.get_next_token();
					PARSER_VERIFY(KW_NUMBER);

					operands[operand_i++] = operand(imm(-static_cast<i64>(m_lex.current_immediate.value)));
					break;
				}
				case KW_LBRACKET: {
					switch(m_lex.get_next_token()) {
						case KW_BYTE ... KW_QWORD: {
							m_lex.get_next_token();
							PARSER_VERIFY(KW_NUMBER);

							operands[operand_i++] = operand(moff(m_lex.current_immediate.value));
							m_lex.get_next_token();
							PARSER_VERIFY(KW_RBRACKET);
							break;
						}
						default: {
							// large mem operand
							operand memory = mem128();

							parse_memory(memory.memory);

							PARSER_VERIFY(KW_RBRACKET);
							operands[operand_i++] = memory;
							break;
						}
					}
					break;
				}
				// memory operands
				case KW_BYTE ... KW_QWORD: {
					keyword_type mem_type = m_lex.current;

					m_lex.get_next_token();
					PARSER_VERIFY(KW_LBRACKET);

					operand memory;

					switch(mem_type) {
						case KW_BYTE: memory = mem8(); break;
						case KW_WORD: memory = mem16(); break;
						case KW_DWORD: memory = mem32(); break;
						case KW_QWORD: memory = mem64(); break;
						default: ASSERT(false, "unreachable\n");
					}

					m_lex.get_next_token();
					parse_memory(memory.memory);

					PARSER_VERIFY(KW_RBRACKET);

					operands[operand_i++] = memory;
					break;
				}
				default: PARSER_EXIT();
			};

			if(m_lex.get_next_token() != KW_COMMA) {
				break;
			}
		}

		u32 instruction_i = first;

		// locate the specific variant (dumb linear search)
		while(utility::compare_strings(instruction_db[instruction_i].get_name(), instruction_db[first].get_name()) == 0) {
			if(is_operand_match(instruction_i, operands)) {
				for(u8 j = 0; j < operand_i; ++j) {
					if(is_operand_rel(instruction_db[instruction_i].get_operand(j))) {
						rel r = rel(static_cast<i32>(operands[j].immediate.value));
						operands[j].type = instruction_db[instruction_i].get_operand(j);
						operands[j].relocation = r; 
					}
				}

				emit_instruction(instruction_i, operands[0], operands[1], operands[2], operands[3]);
				return true;
			}

			instruction_i++;
		}

		utility::console::print("no instruction variant with the specified operands was found\n");
		utility::console::print("operands are:\n");

		for(u8 i = 0; i < operand_i; ++i) {
			utility::console::print("{} ", (i32)operands[i].type);
		}
		
		utility::console::print("\n");
		return false;
	}

	auto assembler::find_instruction_by_name(const char* name) -> u32 {
		// look for the first instruction with that name, just a dumb linear search for the sake of simplicity
		// TODO: update this to a more performant search	
		// TODO: this can be in the instruction.h file
		constexpr u32 db_size = sizeof(instruction_db) / sizeof(instruction);

		for(u32 i = 0; i < db_size; ++i) {
			if(utility::compare_strings(name, instruction_db[i].get_name()) == 0) {
				return i;
			}
		}

		return utility::limits<u32>::max();
	}

	auto assembler::get_bytes() const -> const utility::dynamic_array<u8>& {
		return m_bytes;
	}

	auto assembler::find_rex_pair(const instruction* inst, const operand* operands) -> std::pair<u8, u8> {
		if(inst->is_vex()) {
			std::pair<u8, u8> result = { 0, 0 };

			switch(inst->get_encoding_prefix()) {
				case ENC_VEX_RVM: {
					result.first = operands[0].r;
					result.second = operands[2].r;
					break;
				}
				case ENC_VEX_VM:
				case ENC_VEX_RM:
				case ENC_VEX_RMV: {
					result.first = operands[0].r;
					result.second = operands[1].r;
					break;
				}
				default: ASSERT(false, "unhandled rex case");
			}

			return result;
		}

		if(inst->get_reg_operand_count() == 0) {
			return { 0, 0 };
		}

		if(inst->get_operand_count() == 1) {
			return { 0, operands[0].r };
		}

		if(inst->get_operand_count() == 3 && inst->get_imm_operand_count() == 0) {
			std::pair<u8, u8> result = { 0, 0 };

			if(inst->get_reg_operand_count() == 3) {
				return { operands[1].r, operands[0].r };
			}

			i8 i = 0;

			for(; i < 4; ++i) {
				if(is_operand_reg(operands[i].type)) {
					result.first = operands[i].r;
					result.second = operands[i].r;
					break;
				}
			}

			for(; i < 4; ++i) {
				if(is_operand_reg(operands[i].type)) {
					result.first = operands[i].r;
					break;
				}
			}

			return result;
		}

		// locate the first registers from the back
		std::pair<u8, u8> result = { 0, 0 };
		i8 i = 4;

		while(i-- > 0) {
			if(is_operand_reg(operands[i].type)) {
				result.first = operands[i].r;
				result.second = operands[i].r;
				break;
			}
		}

		while(i-- > 0) {
			if(is_operand_reg(operands[i].type)) {
				result.second = operands[i].r;
				break;
			}
		}

		return result;
	}

	auto assembler::find_instruction_info(u32 index, const operand* operands)  -> const instruction* {
		u8 imm_index = utility::limits<u8>::max();

		// locate the first immediate operand
		for(u8 i = 0; i < 4; ++i) {
			if(is_operand_imm(operands[i].type)) {
				imm_index = i;
				break;
			}
		}

		// no immediate operand, return the original variant
		if(imm_index == utility::limits<u8>::max()) {
			return &instruction_db[index];
		}

		// store a list of legal variants, from which we'll pick the best one
		utility::dynamic_array<const instruction*> legal_variants = {};
		const imm& imm_op = operands[imm_index].immediate;

		// some instructions have a special optimization index, check if we have it
		// if we have a valid context index, the original index, provided as a parameter, will
		// be replaced by this index
		if(instruction_db[index].has_special_index()) {
			const u16 context_index = instruction_db[index].get_special_index();

			// switch on the context kind
			switch(instruction_db[index].get_special_kind()) {
				case 0: {
					// if we have a destination which uses a 64 bit register, and an operand which fits into 32 bits or
					// less we can look for a smaller destination
					if(operands[0].type == OP_REG64 && imm_op.min_bits <= 32) {
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
					const u64 extend = sign_extend(truncated, 8);

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
		while(is_legal_variant(index, current_index, imm_index)) {
			legal_variants.push_back(&instruction_db[current_index++]);
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
			const u16 a_width = get_operand_bit_width(a->get_operand(imm_index));
			const u16 b_width = get_operand_bit_width(b->get_operand(imm_index));

			return a_width < b_width;
		});

		// multiple legal variants, determine the best one (since our data is sorted from smallest
		// source operands to largest, we can exit as soon as we get a valid match)
		for(const instruction* inst : legal_variants) {
			const u16 src_bits = get_operand_bit_width(inst->get_operand(imm_index));
			const u16 dst_bits = get_operand_bit_width(inst->get_operand(0));

			// check if there is a possibility of sign extending the immediate
			if(src_bits < dst_bits) {
				ASSERT(src_bits <= utility::limits<u8>::max(), "invalid range");

				// assume we're sign extending
				if(sign_extend_representable(imm_op.value, static_cast<u8>(src_bits))) {
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

	auto assembler::is_legal_variant(u32 a, u32 b, u8 imm_index) -> bool {
		const u8 operand_count = instruction_db[a].get_operand_count() - 1;

		for(u8 i = 0; i < operand_count; ++i) {
			if(!is_operand_of_same_kind(
				instruction_db[a].get_operand(i), 
				instruction_db[b].get_operand(i)
			)) {
				return false;
			}
		}

		return is_operand_imm(instruction_db[b].get_operand(imm_index));
	}

	void assembler::emit_opcode_prefix_vex(const instruction* inst, const operand* operands) {
		m_bytes.push_back(0xc4); // three byte prefix

		// second byte
		// ~R          [X_______]
		// ~X          [_X______]
		// ~B          [__X_____]
		// map_select  [___XXXXX]
		u8 second = 0;
		const u8 rex = get_instruction_rex(inst, operands);

		const bool r = rex & 0b00000100;
		const bool x = rex & 0b00000010;
		const bool b = rex & 0b00000001;

		// ~R inverted REX.r
		second |= !r << 7;

		// ~X inverted REX.x
		second |= !x << 6;

		// ~B inverted REX.b
		second |= !b << 5;

		// map_select
		u8 map_select = 0;

		switch(inst->get_ilo()) {
			case 0x0f:   map_select = 0b01; break;
			case 0x0f38: map_select = 0b10; break;
			case 0x0f3a: map_select = 0b11; break;
			default: ASSERT(false, "unknown ilo");
		}

		second |= map_select;
		m_bytes.push_back(second);

		// third byte
		// W/E   [X_______]
		// ~vvvv [_XXXX___]
		// L     [_____X__]
		// pp    [______XX]

		u8 third = 0;

		// W/E
		const u8 we = static_cast<u8>((inst->is_rexw()) << 7);
		third |= we;

		// vvvv - negation of one of our v operand
		u8 vvvv = 0;

		switch(inst->get_encoding_prefix()) {
			case ENC_VEX_RVM: vvvv = static_cast<u8>((~operands[1].r & 0b00001111) << 3); break;
			case ENC_VEX_RMV: vvvv = static_cast<u8>((~operands[2].r & 0b00001111) << 3); break;
			case ENC_VEX_VM:  vvvv = static_cast<u8>((~operands[0].r & 0b00001111) << 3); break;
			case ENC_VEX_RM:  vvvv = 0b1111 << 3; break; // no 'V' part, just return a negated zero
			default: ASSERT(false, "unhandled vex prefix");
		}

		third |= vvvv;

		 // L vector length (0 = 128b, 1 = 256b)
		const u8 l = 0 << 2;
		third |= l;

		// pp - implied mandatory prefix
		third |= inst->get_imp();
		
		m_bytes.push_back(third);
	}

	void assembler::emit_opcode_prefix_rex(const instruction* inst, const operand* operands) {
		const bool is_rexw = inst->is_rexw();

		if(is_rexw || is_extended_reg(operands[0]) || is_extended_reg(operands[1])) {
			m_bytes.push_back(get_instruction_rex(inst, operands));
		}
		else if(is_operand_mem(operands[0].type)) {
			emit_opcode_prefix_rex_mem(operands[0].memory);
		}
		else if(is_operand_mem(operands[1].type)) {
			emit_opcode_prefix_rex_mem(operands[1].memory);
		}
	}

	void assembler::emit_instruction_prefix(const instruction* inst) {
		if(inst->has_prefix() == false) {
			return; // no prefix
		}

		const u8 prefix = inst->get_prefix();

		// group 4
		if(prefix & ADDRESS_SIZE_OVERRIDE) {
			m_bytes.push_back(0x67);
		}

		// group 3
		if(prefix & OPERAND_SIZE_OVERRIDE) {
			m_bytes.push_back(0x66);
		}

		// group 2
		switch(prefix & 0b00111100) {
			case CS_SEGMENT:       m_bytes.push_back(0x2E); break;
			case SS_SEGMENT:       m_bytes.push_back(0x36); break;
			case DS_SEGMENT:       m_bytes.push_back(0x3E); break;
			case ES_SEGMENT:       m_bytes.push_back(0x26); break;
			case FS_SEGMENT:       m_bytes.push_back(0x64); break;
			case GS_SEGMENT:       m_bytes.push_back(0x65); break;
			case BRANCH_NOT_TAKEN: m_bytes.push_back(0x2E); break;
			case BRANCH_TAKEN:     m_bytes.push_back(0x3E); break;
			default:                                        break;
		}

		// group 1
		switch(prefix & 0b00000011) {
			case LOCK:  m_bytes.push_back(0xF0); break;
			case REPNE: m_bytes.push_back(0xF2); break;
			case REP:   m_bytes.push_back(0xF3); break;
			default:                             break;
		}
	}

	void assembler::emit_instruction_opcode(const instruction* inst, const operand* operands) {
		auto [rx, destination] = find_rex_pair(inst, operands);

		// prefix
		if(inst->is_rex()) {
			emit_opcode_prefix_rex(inst, operands);
		}
		else if(inst->is_vex()) {
			emit_opcode_prefix_vex(inst, operands);
		}

		// opcode
		u64 opcode = inst->get_opcode();

		if(inst->is_opcode_ext()) {
			// extract the 3 least significant reg bits 
			if(inst->get_direction()) {
				opcode += destination & 0b00000111;
			}
			else {
				opcode += rx & 0b00000111;
			}
		}

		// append opcode bytes
		for(u8 i = 4; i-- > 1;) {
			const u8 byte = (opcode >> (i * 8)) & 0xFF;

			if(byte != 0) {
				m_bytes.push_back(byte);
			}
		}

		// always push the last byte
		const u8 byte = opcode & 0xFF;
		m_bytes.push_back(byte);
	}

	void assembler::emit_opcode_prefix_rex_mem(const mem& memory) {
		// extended base
		if(
			(memory.has_base && memory.base.index >= 8) || 
			(memory.has_index && memory.index.index >= 8)
		) {
			m_bytes.push_back(rex(false, 0, memory.base.index, memory.index.index));
		}
	}

	void assembler::emit_operands(const instruction* inst, const operand* operands) {
		for(u8 i = 0; i < inst->get_operand_count(); ++i) {
			const operand_type current = inst->get_operand(i);

			if(is_operand_imm(current)) {
				// immediate operand
				emit_data_operand(operands[i].immediate.value, get_operand_bit_width(current));
			}
			else if(is_operand_moff(current)) {
				// memory offset operand (always 64-bit)
				emit_data_operand(operands[i].memory_offset.value, 64);
			}
			else if(is_operand_rel(current)) {
				// relocation operand
				const u16 operand_size = get_operand_bit_width(current);
				const i32 new_displacement = operands[i].relocation.value - (get_current_inst_size() + operand_size / 8);

				emit_data_operand(new_displacement, operand_size);
			}
			else if(is_operand_mem(current)) {
				// memory displacement operand
				const mem memory = operands[i].memory;
				imm displacement = memory.displacement;

				if(displacement.value == 0) {
					if(memory.has_base && memory.base.type != REG_RIP) {
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

						for(u8 j = i; j < inst->get_operand_count(); ++j) {
							// if we have another operand after the current one, calculate it's size
							if(is_operand_imm(inst->get_operand(j))) { // registers are already encoded
								new_displacement -= get_operand_bit_width(inst->get_operand(j)) / 8;
							}
						}

						displacement = imm(new_displacement);
						ty = OP_I32;
					}
					else if(displacement.min_bits <= 8) {
						ty = OP_I8;
					}
				}

				emit_data_operand(displacement.value, get_operand_bit_width(ty));
			}
		}
	}

	void assembler::emit_instruction_mod_rm(const instruction* inst, const operand* operands) {
		auto [rx, destination] = find_rex_pair(inst, operands);

		if(inst->has_variant()) {
			rx = inst->get_variant();
		}

		// mod rm / sib byte
		if(inst->is_r() || is_operand_mem(operands[0].type) || is_operand_mem(operands[1].type) || is_operand_mem(operands[2].type)) {
			u8 mod_rm_part;

			if(is_operand_mem(operands[0].type)) {
				const bool has_sib = has_sib_byte(operands);
				const auto memory = operands[0].memory;

				ASSERT(memory.displacement.min_bits <= 32, "too many displacement bits");

				// right mem
				if(memory.has_base == false) {
					// absolute address
					if(inst->is_ext()) {
						mod_rm_part = indirect(inst->get_ext(), 0b100);
					}
					else {
						// this may not be needed
						mod_rm_part = indirect(rx, 0b100); // 100 = SIB byte
					}
				}
				else if(memory.base.type == REG_RIP) {
					// rip reg
					if(inst->is_ext()) {
						mod_rm_part = indirect(inst->get_ext(), 0b101);
					}
					else {
						mod_rm_part = indirect(rx, 0b101); // 101 = RIP-relative
					}
				}
				else if(memory.displacement.value == 0) {
					// no displacement
					if(inst->is_ext()) {
						mod_rm_part = indirect(inst->get_ext(), has_sib ? 0b100 : memory.base.index);
					}
					else {
						mod_rm_part = indirect(rx, has_sib ? 0b100 : memory.base.index);
					}
				}
				else if(memory.displacement.min_bits <= 8) {
					// 8 bit displacement
					if(inst->is_ext()) {
						mod_rm_part = indirect_disp_8(inst->get_ext(), has_sib ? 0b100 : memory.base.index);
					}
					else {
						mod_rm_part = indirect_disp_8(rx, has_sib ? 0b100 : memory.base.index);
					}

				}
				else {
					// 32 bit displacement
					if(inst->is_ext()) {
						mod_rm_part = indirect_disp_32(inst->get_ext(), has_sib ? 0b100 : memory.base.index);
					}
					else {
						mod_rm_part = indirect_disp_32(rx, has_sib ? 0b100 : memory.base.index);
					}
				}
			}
			else if(is_operand_mem(operands[1].type)) {
				const bool has_sib = has_sib_byte(operands);
				const auto memory = operands[1].memory;

				ASSERT(memory.displacement.min_bits <= 32, "too many displacement bits");

				// right mem
				if(memory.has_base == false) {
					// absolute address
					mod_rm_part = indirect(rx, 0b100); // 100 = SIB byte
				}
				else if(memory.base.type == REG_RIP) {
					// rip reg
					mod_rm_part = indirect(rx, 0b101); // 101 = RIP-relative
				}
				else if(memory.displacement.value == 0) {
					// no displacement
					mod_rm_part = indirect(rx, has_sib ? 0b100 : memory.base.index);
				}
				else if(memory.displacement.min_bits <= 8) {
					// 8 bit displacement
					mod_rm_part = indirect_disp_8(rx, has_sib ? 0b100 : memory.base.index);
				}
				else {
					// 32 bit displacement
					mod_rm_part = indirect_disp_32(rx, has_sib ? 0b100 : memory.base.index);
				}
			}
			else if(is_operand_mem(operands[2].type)) {
				const bool has_sib = has_sib_byte(operands);
				const auto memory = operands[2].memory;

				ASSERT(memory.displacement.min_bits <= 32, "too many displacement bits");

				// right mem
				if(memory.has_base == false) {
					// absolute address
					mod_rm_part = indirect(rx, 0b100); // 100 = SIB byte
				}
				else if(memory.base.type == REG_RIP) {
					// rip reg
					mod_rm_part = indirect(rx, 0b101); // 101 = RIP-relative
				}
				else if(memory.displacement.value == 0) {
					// no displacement
					mod_rm_part = indirect(rx, has_sib ? 0b100 : memory.base.index);
				}
				else if(memory.displacement.min_bits <= 8) {
					// 8 bit displacement
					mod_rm_part = indirect_disp_8(rx, has_sib ? 0b100 : memory.base.index);
				}
				else {
					// 32 bit displacement
					mod_rm_part = indirect_disp_32(rx, has_sib ? 0b100 : memory.base.index);
				}
			}
			else {
				if(inst->get_direction()) {
					mod_rm_part = direct(rx, destination);
				}
				else {
					mod_rm_part = direct(destination, rx);
				}
			}

			m_bytes.push_back(mod_rm_part);
		}
		else if(inst->is_ext()) {
			m_bytes.push_back(direct(inst->get_ext(), destination));
		}
	}

	void assembler::emit_instruction_sib(const operand* operands) {
		mem memory;

		if(is_operand_mem(operands[0].type)) {
			memory = operands[0].memory;
		}
		else if(is_operand_mem(operands[1].type)) {
			memory = operands[1].memory;
		}
		else if(is_operand_mem(operands[2].type)) {
			memory = operands[2].memory;
		}
		else {
			return; // no sib byte
		}

		const u8 scale = memory.has_base  ? memory.s       : 0b000;
		const u8 index = memory.has_index ? memory.index.index : 0b100;
		const u8 base  = memory.has_base ? memory.base.index   : 0b101;

		if(memory.has_index || is_stack_pointer(reg(memory.base)) || memory.has_base == false) {
			m_bytes.push_back(sib(scale, index, base));
		}
	}

	void assembler::emit_instruction(u32 index, const operand& op1, const operand& op2, const operand& op3, const operand& op4) {
		const operand operands[4] = { op1, op2, op3, op4 };

		// NOTE: operand count can be inferred from overloaded functions
		instruction_begin(); // mark the instruction start (used for rip-relative addressing)

		// locate the actual instruction we want to assemble (this doesn't have to match the specified
		// index, since we can apply optimizations which focus on stuff like shorter encodings)
		const instruction* inst = find_instruction_info(index, operands);

		// emit instruction parts
		emit_instruction_prefix(inst);
		emit_instruction_opcode(inst, operands);
		emit_instruction_mod_rm(inst, operands);
		emit_instruction_sib(operands);

		// emit immediate, displacement, and memory offset operands
		emit_operands(inst, operands);
	}

	auto assembler::has_sib_byte(const operand* operands) -> bool {
		mem memory;

		if(is_operand_mem(operands[0].type)) {
			memory = operands[0].memory;
		}
		else if(is_operand_mem(operands[1].type)) {
			memory = operands[1].memory;
		}
		else if(is_operand_mem(operands[2].type)) {
			memory = operands[2].memory;
		}
		else {
			return false;
		}

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

	auto get_first_extended_reg(const operand* operands) -> u8 {
		for(u8 i = 0; i < 4; ++i) {
			if(is_extended_reg(operands[i])) {
				return i;
			}
		}

		// no extended reg, get last regular reg
		for(u8 i = 4; i-- > 0;) {
			if(is_operand_reg(operands[i].type)) {
				return i;
			}
		}

		ASSERT(false, "invalid instruction");
		return 0;
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

	auto encode_operand_type(const operand& op) -> u16 {
		if(is_operand_mem(op.type)) {
			return 0b11;
		}

		if(is_operand_imm(op.type)) {
			return 0b00;
		}

		if(is_operand_xmm(op.type)) {
			return 0b10;
		}

		return 0b01;
	}

	auto assembler::get_instruction_rex(const instruction* inst, const operand* operands) -> u8 {
		// THIS IS UNCHECKED, MAYBE WE'LL HAVE TO RETURN 0
		const bool is_rexw = inst->is_rexw();

		u8 rx = 0;
		u8 base = 0;
		u8 index = 0;
		u16 index_byte = 0;

		// figure out the index bit first
		if(inst->has_mem_operand()) {
			const mem mem = operands[inst->get_mem_operand()].memory;

			if(mem.has_index) {
				index = mem.index.index;
			}
		}

		if(inst->is_vex()) {
			const u8 registers[4] = {
				extract_operand_reg(operands[0]),
				extract_operand_reg(operands[1]),
				extract_operand_reg(operands[2]),
				extract_operand_reg(operands[3]),
			};

			// op[0] is extended? [____X___]
			// op[1] is extended? [_____X__]
			// op[2] is extended? [______X_]
			// op[3] is extended? [_______X]
			index_byte |= (registers[0] >= 8) << 3;
			index_byte |= (registers[1] >= 8) << 2;
			index_byte |= (registers[2] >= 8) << 1;
			index_byte |= (registers[3] >= 8) << 0;

			switch(inst->get_encoding_prefix()) {
				case ENC_VEX_RVM: {
					switch(index_byte) {
						case 0b00001000:
						case 0b00001110:
						case 0b00000000: rx = registers[0]; base = registers[1]; break;
						case 0b00001100:
						case 0b00000010: rx = registers[1]; base = registers[2]; break;
						case 0b00001010:
						case 0b00000110: rx = registers[0]; base = registers[2]; break;
						case 0b00000100: rx = registers[2]; base = registers[0]; break;
						default: ASSERT(false, "unhandled rex case");
					}

					break;
				}
				case ENC_VEX_RMV: {
					switch(index_byte) {
						case 0b00001000:
						case 0b00001010:
						case 0b00001100:
						case 0b00001110:
						case 0b00000000:
						case 0b00000010: rx = registers[0]; base = registers[1]; break;
						case 0b00000110: rx = registers[0]; base = registers[2]; break;
						case 0b00000100: rx = registers[2]; base = registers[1]; break;
						default: ASSERT(false, "unhandled rex case");
					}

					break;
				}
				case ENC_VEX_VM: {
					switch(index_byte) {
						case 0b00000000:
						case 0b00000100: rx = registers[0]; base = registers[1]; break;
						case 0b00001000: rx = registers[1]; base = registers[1]; break;
						case 0b00001100: rx = 0;            base = registers[1]; break;
						default: ASSERT(false, "unhandled rex case");
					}

					break;
				}
				case ENC_VEX_RM: {
					switch(index_byte) {
						case 0b00001000:
						case 0b00001100:
						case 0b00000100: rx = registers[0]; base = registers[1]; break;
						case 0b00000000: rx = registers[1]; base = registers[0]; break;
						default: ASSERT(false, "unhandled rex case");
					}

					break;
				}
				default: ASSERT(false, "unhandled rex case");
			}
		}
		else {
			const u8 registers[4] = {
				extract_operand_reg(operands[0]),
				extract_operand_reg(operands[1]),
				extract_operand_reg(operands[2]),
				extract_operand_reg(operands[3]),
			};

			// KK = kind
			// 00 = imm
			// 01 = gpr
			// 10 = xmm
			// 11 = mem

			// op[0] type         [KK__________]
			// op[0] is extended? [__X_________]
			// op[1] type         [___KK_______]
			// op[1] is extended? [_____X______]
			// op[2] type         [______KK____]
			// op[2] is extended? [________X___]
			// op[3] type         [_________KK_]
			// op[3] is extended? [___________X]

			index_byte |= encode_operand_type(operands[0]) << 10;
			index_byte |= (registers[0] >= 8) << 9;
			index_byte |= encode_operand_type(operands[1]) << 7;
			index_byte |= (registers[1] >= 8) << 6;
			index_byte |= encode_operand_type(operands[2]) << 4;
			index_byte |= (registers[2] >= 8) << 3;
			index_byte |= encode_operand_type(operands[3]) << 1;
			index_byte |= (registers[3] >= 8) << 0;

			const u8 operand_count = inst->get_operand_count();
			const u8 a = inst->get_direction() ? 0 : 1;
			const u8 b = inst->get_direction() ? 1 : 0;

			if(operand_count == 0) {
				return rex(is_rexw, 0, 0, 0);
			}

			if(operand_count == 1 || operand_count == 2 || operand_count == 4) {
				switch(index_byte) {
					case 0b010'000'010'010:
					case 0b110'000'010'010:
					case 0b011'011'010'010:
					case 0b111'011'010'010:
					case 0b110'010'010'010:
					case 0b010'010'010'010:
					case 0b011'110'010'010:
					case 0b011'111'010'010:
					case 0b010'110'010'010:
					case 0b010'111'010'010:
					case 0b100'101'010'010:
					case 0b101'100'010'010:
					case 0b101'101'010'010:
					case 0b101'110'010'010:
					case 0b101'111'010'010:
					case 0b100'101'000'010:
					case 0b101'100'000'010:
					case 0b101'101'000'010:
					case 0b101'110'000'010:
					case 0b101'111'000'010:
					case 0b011'101'000'010:
					case 0b101'010'010'010:
					case 0b011'101'010'010:
					case 0b010'100'010'010:
					case 0b100'011'010'010:
					case 0b101'011'010'010:
					case 0b100'010'010'010:
					case 0b100'110'010'010:
					case 0b100'111'010'010:
					case 0b111'101'010'010:
					case 0b011'100'000'010:
					case 0b010'101'000'010:
					case 0b110'101'000'010:
					case 0b111'101'000'010:
					case 0b010'100'000'010:
					case 0b101'000'000'010:
					case 0b100'101'000'000:
					case 0b101'100'000'000:
					case 0b101'101'000'000: rx = registers[0]; base = registers[1]; break;
					case 0b011'000'010'010:
					case 0b111'000'010'010:
					case 0b110'011'010'010:
					case 0b111'010'010'010:
					case 0b110'101'010'010:
					case 0b101'000'010'010: rx = registers[1]; base = registers[0]; break;
					case 0b010'011'010'010:
					case 0b011'010'010'010:
					case 0b010'101'010'010:
					case 0b011'100'010'010: rx = registers[b]; base = registers[a]; break;
					default: ASSERT(false, "unhandled rex case");
				}
			}
			else if(operand_count == 3) {
				switch(index_byte) {
					case 0b010'000'010'010:
					case 0b110'000'010'010:
					case 0b011'011'010'010:
					case 0b111'011'010'010:
					case 0b110'010'010'010:
					case 0b010'010'010'010:
					case 0b011'110'010'010:
					case 0b011'111'010'010:
					case 0b010'110'010'010:
					case 0b010'111'010'010:
					case 0b100'101'010'010:
					case 0b101'100'010'010:
					case 0b101'101'010'010:
					case 0b101'110'010'010:
					case 0b101'111'010'010:
					case 0b100'101'000'010:
					case 0b101'100'000'010:
					case 0b101'101'000'010:
					case 0b101'110'000'010:
					case 0b101'111'000'010:
					case 0b011'101'000'010:
					case 0b111'101'000'010:
					case 0b010'100'000'010:
					case 0b110'100'000'010:
					case 0b100'011'000'010:
					case 0b101'010'000'010:
					case 0b101'011'000'010:
					case 0b100'010'000'010:
					case 0b010'010'000'010:
					case 0b011'011'000'010:
					case 0b100'110'000'010:
					case 0b100'111'000'010:
					case 0b110'010'000'010:
					case 0b011'110'000'010:
					case 0b011'111'000'010:
					case 0b010'110'000'010:
					case 0b010'111'000'010:
					case 0b111'011'000'010: rx = registers[0]; base = registers[1]; break;
					case 0b011'000'010'010:
					case 0b111'000'010'010:
					case 0b111'010'010'010:
					case 0b110'101'000'010:
					case 0b101'000'000'010:
					case 0b111'100'000'010:
					case 0b110'011'000'010:
					case 0b111'010'000'010: rx = registers[1]; base = registers[0]; break;
					case 0b010'011'010'010:
					case 0b011'010'010'010:
					case 0b110'011'010'010:
					case 0b010'101'000'010:
					case 0b011'100'000'010:
					case 0b011'010'000'010:
					case 0b010'011'000'010: rx = registers[b]; base = registers[a]; break;
					default: ASSERT(false, "unhandled rex case");
				}
			}
			else {
				ASSERT(false, "unhandled op count");
			}
		}

		return rex(is_rexw, rx, base, index);
	}

	void assembler::emit_data_operand(u64 data, u16 bit_width) {
		for(u16 i = 0; i < bit_width / 8; ++i) {
			m_bytes.push_back(data >> (i * 8) & 0xFF);
		}
	}

	auto assembler::sib(u8 scale, u8 index, u8 base) -> u8 {
		ASSERT(scale <= 3, "invalid scale");

		// scale [XX______]
		// index [__XXX___]
		// base  [_____XXX]

		return static_cast<u8>((scale << 6) | ((index & 0x7) << 3) | (base & 0x7));
	}

	auto assembler::rex(bool w, u8 rx, u8 base, u8 index) -> u8 {
		ASSERT(rx < 16, "invalid rx");
		ASSERT(base < 16, "invalid base");
		ASSERT(index < 16, "invalid index");

		// whenever a used register is larger than 3 bits we need to mark the extension bit
		// the result will then be extended in mod R/M or the SIB byte.

		//                                     rex WRXB
		// rex prefix                         [0100____]
		// w (64 bit mode)                    [____X___]
		// r (mod R/M extension) (rx > RDI)   [_____X__]
		// x (sib extension) (index > RDI)    [______X_]
		// b (mod R/M extension) (base > RDI) [_______X]

		const u8 index_mask = static_cast<u8>((index >> 3) << 1);
		const u8 rx_mask = static_cast<u8>((rx >> 3) << 2);
		const u8 w_mask = static_cast<u8>(w << 3);
		const u8 base_mask = base >> 3;

		return 0x40 | base_mask | index_mask | rx_mask | w_mask;
	}

	auto assembler::mod_rx_rm(u8 mod, u8 rx, u8 rm) -> u8 {
		ASSERT(mod < 4, "invalid mod");
		ASSERT(rx < 16, "invalid rx");
		ASSERT(rm < 16, "invalid rm");

		// registers 0 - 7  primary registers
		// registers 8 - 16 extended registers

		// mod  [XX______] (addressing mode)
		// rx   [__XXX___]
		// rm   [_____XXX]

		return static_cast<u8>((rm & 7) | ((rx & 7) << 3) | (mod << 6));
	}

	auto assembler::direct(u8 rx, u8 reg) -> u8 {
		return mod_rx_rm(DIRECT, rx, reg);
	}

	auto assembler::indirect(u8 rx, u8 base) -> u8 {
		return mod_rx_rm(INDIRECT, rx, base);
	}

	auto assembler::indirect_disp_8(u8 rx, u8 base) -> u8 {
		return mod_rx_rm(INDIRECT_DISP8, rx, base);
	}

	auto assembler::indirect_disp_32(u8 rx, u8 base) -> u8 {
		return mod_rx_rm(INDIRECT_DISP32, rx, base);
	}

	void assembler::instruction_begin() {
		m_current_inst_begin = m_bytes.get_size();
	}

	void assembler::clear() {
		m_assembly.clear();
		m_asm_i = 0;

		m_bytes.clear();
		m_current_inst_begin = 0;
	}

	auto assembler::get_current_inst_size() const -> u8 {
		return static_cast<u8>(m_bytes.get_size() - m_current_inst_begin);
	}

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
			case OP_AL:  return b == OP_AL  || b == OP_CL  || b == OP_REG8;  // 8 bits
			case OP_AX:  return b == OP_AX  || b == OP_DX  || b == OP_REG16; // 16 bits
			case OP_EAX: return b == OP_EAX || b == OP_ECX || b == OP_REG32; // 32 bits
			case OP_RAX: return b == OP_RAX || b == OP_RCX || b == OP_REG64; // 64 bits
			default: return a == b; // regular compares
		}
	}
} // namespace baremetal
