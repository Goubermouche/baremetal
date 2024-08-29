#include "assembler.h"

#include "assembler/instruction/instruction.h"
#include "assembler/instruction/operands/memory.h"
#include "assembler/instruction/operands/registers.h"
#include "instruction/instruction.h"
#include "instruction/operands/operands.h"
#include "assembler/parser.h"
#include "parser.h"
#include "utility/containers/dynamic_string.h"
#include "utility/containers/map.h"
#include "utility/system/console.h"
#include "utility/types.h"

#include <new>
#include <utility/algorithms/sort.h>
#include <utility/assert.h>

namespace baremetal {
	assembler::assembler() : m_current_inst_begin(0) {}

	auto inst_match(opn a, opn_data b) -> bool{
		switch(a) {
			case OPN_FS:          return b.type == OPN_SREG && b.r == fs.index;
			case OPN_GS:          return b.type == OPN_SREG && b.r == gs.index;
			case OPN_AL:          return b.type == OPN_R8 && b.r == al.index;
			case OPN_AX:          return b.type == OPN_R16 && b.r == ax.index;
			case OPN_EAX:         return b.type == OPN_R32 && b.r == eax.index;
			case OPN_RAX:         return b.type == OPN_R64 && b.r == rax.index;
			case OPN_CL:          return b.type == OPN_R8 && b.r == cl.index;
			case OPN_DX:          return b.type == OPN_R16 && b.r == dx.index;
			case OPN_ECX:         return b.type == OPN_R32 && b.r == ecx.index;
			case OPN_RCX:         return b.type == OPN_R64 && b.r == rcx.index;
			case OPN_MEM:         return b.type == OPN_M128;
			default: return a == b.type;
		}
	}

	auto is_operand_match(u32 inst_i, opn_data* operands) -> bool {
		const ins& inst = inst_db[inst_i];

		for(u8 i = 0; i < 4; ++i) {
			// if the operands at a given index are both imm we ignore their difference
			if(
				!(inst_match(inst.operands[i], operands[i])) &&
				!(is_operand_imm(inst.operands[i]) && is_operand_imm(operands[i].type)) &&
				!(is_operand_moff(inst.operands[i]) && is_operand_moff(operands[i].type)) &&
				!(is_operand_rel(inst.operands[i]) && is_operand_imm(operands[i].type)) &&
				!(inst.operands[i] == OPN_M256 && operands[i].type == OPN_M128) && // HACK - we don't really know if we're dealing with a mem128 or a mem256, this depends on the instruction
				!(inst.operands[i] == OPN_M512 && operands[i].type == OPN_M128) // HACK - we don't really know if we're dealing with a mem128 or a mem256, this depends on the instruction
			) {
				return false;
			}
		}

		return true;
	}

	auto assembler::assemble(const utility::dynamic_string& assembly) -> bool {
		m_lex.set_text(assembly);
		m_lex.get_next_token();

		while(m_lex.current != KW_EOF) {
			if(assemble_instruction() == false) {
				return false;
			}
		}

		return true;
	}

#define PARSER_VERIFY(expected)																						 \
  if(m_lex.current != expected) {                                 				 \
    utility::console::print("unexpected token: {}\n", (i32)m_lex.current); \
    return false;                                                          \
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

	auto assembler::parse_mask_reg(opn_data& op) -> bool {
		if(m_lex.get_next_token() == KW_LBRACE) {
			m_lex.get_next_token();
			
			char c = m_lex.current_string[0];

			switch(c) {
				case 'k': {
					ASSERT(m_lex.current_string.get_size() == 2, "invalid mask register specified\n");
					char* end;
					op.mr.k  = static_cast<u8>(strtoul(m_lex.current_string.get_data() + 1, &end, 10));
					ASSERT(op.mr.k < 8, "invalid mask register specified\n");

					if(is_operand_xmm(op.type)) { op.type = OPN_XMM_K; }
					else if(is_operand_ymm(op.type)) { op.type = OPN_YMM_K; }
					else if(is_operand_zmm(op.type)) { op.type = OPN_ZMM_K; }

					break;
				}
				case 'z': {
					ASSERT(m_lex.current_string.get_size() == 1, "invalid mask register specified\n");
					op.mr.z = true;

					if(is_operand_xmm(op.type)) { op.type = OPN_XMM_KZ; }
					else if(is_operand_ymm(op.type)) { op.type = OPN_YMM_KZ; }
					else if(is_operand_zmm(op.type)) { op.type = OPN_ZMM_KZ; }

					break;
				}

				default: utility::console::print_err("unknown mask register specified\n"); return false;
			}

			m_lex.get_next_token();
			PARSER_VERIFY(KW_RBRACE);

			return true;
		}

		return false;
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

		opn_data operands[4] = {{}};
		u8 operand_i = 0;

		// operands
		while(m_lex.get_next_token() != KW_EOF) {
			switch (m_lex.current) {
				// registers
				case KW_CR0 ... KW_R15B: { 
					operands[operand_i] = opn_data(keyword_to_register(m_lex.current));
					
					while(parse_mask_reg(operands[operand_i])) {}

					operand_i++;
					break;
				}
				// numerical literals
				case KW_NUMBER: {
					operands[operand_i++] = opn_data(m_lex.current_immediate);
					m_lex.get_next_token();
					break;
				}
				case KW_MINUS: {
					m_lex.get_next_token();
					PARSER_VERIFY(KW_NUMBER);

					operands[operand_i++] = opn_data(imm(-static_cast<i64>(m_lex.current_immediate.value)));
					m_lex.get_next_token();
					break;
				}
				case KW_LBRACKET: {
					switch(m_lex.get_next_token()) {
						case KW_BYTE ... KW_QWORD: {
							m_lex.get_next_token();
							PARSER_VERIFY(KW_NUMBER);

							operands[operand_i++] = opn_data(moff(m_lex.current_immediate.value));
							m_lex.get_next_token();
							PARSER_VERIFY(KW_RBRACKET);
							break;
						}
						default: {
							// large mem operand
							opn_data memory = mem128();

							parse_memory(memory.memory);

							PARSER_VERIFY(KW_RBRACKET);
							operands[operand_i++] = memory;
							break;
						}
					}

					m_lex.get_next_token();
					break;
				}
				// memory operands
				case KW_BYTE ... KW_QWORD: {
					keyword_type mem_type = m_lex.current;

					m_lex.get_next_token();
					PARSER_VERIFY(KW_LBRACKET);

					opn_data memory;

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

					m_lex.get_next_token();
					break;
				}
				default: PARSER_EXIT();
			};

			if(m_lex.current != KW_COMMA) {
				break;
			}
		}

		u32 instruction_i = first;
		constexpr u32 db_size = sizeof(inst_db) / sizeof(ins);

		// locate the specific variant (dumb linear search)
		while(instruction_i < db_size && utility::compare_strings(inst_db[instruction_i].name, inst_db[first].name) == 0) {
			if(is_operand_match(instruction_i, operands)) {
				for(u8 j = 0; j < operand_i; ++j) {
					operands[j].type = inst_db[instruction_i].operands[j]; // HACK: just modify all instructions to the actual type (relocations, mem256)

					if(is_operand_rel(inst_db[instruction_i].operands[j])) {
						rel r = rel(static_cast<i32>(operands[j].immediate.value));
						operands[j].relocation = r; 
					}
				}

				emit_instruction(instruction_i, operands);
				return true;
			}

			instruction_i++;
		}

		utility::console::print("no instruction variant with the specified operands was found\n");
		utility::console::print("operands are:\n{} ", instruction_identifier);

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
		constexpr u32 db_size = sizeof(inst_db) / sizeof(ins);

		for(u32 i = 0; i < db_size; ++i) {
			if(utility::compare_strings(name, inst_db[i].name) == 0) {
				return i;
			}
		}

		return utility::limits<u32>::max();
	}

	auto assembler::get_bytes() const -> const utility::dynamic_array<u8>& {
		return m_bytes;
	}

	auto assembler::find_rex_pair(const instruction* inst, const operand* operands) -> std::pair<u8, u8> {
		if(inst->is_vex() || inst->is_evex()) {
			std::pair<u8, u8> result = { 0, 0 };

			switch(inst->get_encoding_prefix()) {
				case ENC_EVEX_RVM:
				case ENC_VEX_RVM: {
					result.first = operands[0].r;
					result.second = operands[2].r;
					break;
				}
				case ENC_VEX_VM:
				case ENC_VEX_RM:
				case ENC_VEX_RMI:
				case ENC_VEX_RMV: {
					result.first = operands[0].r;
					result.second = operands[1].r;
					break;
				}
				default: ASSERT(false, "unhandled rex case 0");
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

	auto assembler::find_instruction_info(u32 index, const opn_data* operands)  -> const ins* {
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
			return &inst_db[index];
		}

		// store a list of legal variants, from which we'll pick the best one
		utility::dynamic_array<const ins*> legal_variants = {};
		const imm& imm_op = operands[imm_index].immediate;

		// some instructions have a special optimization index, check if we have it
		// if we have a valid context index, the original index, provided as a parameter, will
		// be replaced by this index
		if(inst_db[index].has_special_index()) {
			const u16 context_index = inst_db[index].get_special_index();

			// switch on the context kind
			switch(inst_db[index].get_special_kind()) {
				case 0: {
					// if we have a destination which uses a 64 bit register, and an operand which fits into 32 bits or
					// less we can look for a smaller destination
					if(operands[0].type == OPN_R64 && imm_op.min_bits <= 32) {
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
						return &inst_db[context_index];
					}

					break; // we're not using the optimization index, continue
				}
				case 2: {
					// truncate to 8 bits, this is only used with imul instructions
					const u64 truncated = operands[2].immediate.value & 0b011111111;
					const u64 extend = sign_extend(truncated, 8);

					if(extend == operands[2].immediate.value) {
						return &inst_db[context_index];
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
			legal_variants.push_back(&inst_db[current_index++]);
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
			const u16 a_width = get_operand_bit_width(a->operands[imm_index]);
			const u16 b_width = get_operand_bit_width(b->operands[imm_index]);

			return a_width < b_width;
		});

		// multiple legal variants, determine the best one (since our data is sorted from smallest
		// source operands to largest, we can exit as soon as we get a valid match)
		for(const ins* inst : legal_variants) {
			const u16 src_bits = get_operand_bit_width(inst->operands[imm_index]);
			const u16 dst_bits = get_operand_bit_width(inst->operands[0]);

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
		const u8 operand_count = inst_db[a].operand_count - 1;

		for(u8 i = 0; i < operand_count; ++i) {
			if(!is_operand_of_same_kind(inst_db[a].operands[i], inst_db[b].operands[i])) {
				return false;
			}
		}

		return is_operand_imm(inst_db[b].operands[imm_index]);
	}

	void assembler::emit_opcode_prefix_vex(const ins* inst, const opn_data* operands) {
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

		switch((inst->opcode & 0xffff00)) {
			case 0x000f00: map_select = 0b01; break; 
			case 0x0f3800: map_select = 0b10; break;
			case 0x0f3a00: map_select = 0b11; break;
			default: ASSERT(false, "unknown leading opcode");
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

		// if(inst->has_vex_vvvv()) {
			switch(inst->encoding) {
				case ENCN_VEX: vvvv = static_cast<u8>((~operands[2].r & 0b00001111) << 3); break;
				case ENCN_VEX_VM: vvvv = static_cast<u8>((~operands[0].r & 0b00001111) << 3); break;
				case ENCN_VEX_RVM: vvvv = static_cast<u8>((~operands[1].r & 0b00001111) << 3); break;
				case ENCN_VEX_RM: vvvv = 0b1111 << 3; break; // no 'V' part, just return a negated zero
				// case ENC_VEX_RVM: vvvv = static_cast<u8>((~operands[1].r & 0b00001111) << 3); break;
				// case ENC_VEX_RMI: vvvv = static_cast<u8>((~operands[0].r & 0b00001111) << 3); break;
				// case ENC_VEX_RMV: vvvv = static_cast<u8>((~operands[2].r & 0b00001111) << 3); break;
				// case ENC_VEX_VM:  vvvv = static_cast<u8>((~operands[0].r & 0b00001111) << 3); break;
				// case ENC_VEX_RM:  vvvv = 0b1111 << 3; break; // no 'V' part, just return a negated zero
				default: ASSERT(false, "unhandled vex prefix");
			}
		// }
		// else {
		// 	vvvv = 0b01111000;
		// }

		third |= vvvv;

		// L vector length (0 = 128b, 1 = 256b)
		bool vector_len = inst->op_size == OPS_256;
		const u8 l = (0b000000001 & vector_len) << 2;
		third |= l;

		// pp - implied mandatory prefix
		if(inst->prefix == OPERAND_SIZE_OVERRIDE) {
			third |= 0b01;
		}
		else if(inst->prefix == REP) {
			third |= 0b10;
		}
		else if(inst->prefix == REPNE) {
			third |= 0b11;
		}

		m_bytes.push_back(third);
	}

	auto get_masked_operand(const instruction* inst, const operand* operands) -> masked_reg {
		for(u8 i = 0; i < inst->get_operand_count(); ++i) {
			if(is_operand_masked(operands[i].type)) {
				return operands[i].mr;
			}
		}

		return {};
	}

	auto has_masked_operand(const instruction* inst, const operand* operands) -> bool {
		for(u8 i = 0; i < inst->get_operand_count(); ++i) {
			if(is_operand_masked(operands[i].type)) {
				return true;
			}
		}

		return false;
	}

	void assembler::emit_opcode_prefix_evex(const instruction* inst, const operand* operands) {
		m_bytes.push_back(0x62); // always the same, derived from an unused opcode

		// second byte
		// ~R         [X_______]
		// ~X         [_X______]
		// ~B         [__X_____]
		// ~R'        [___X____]
		//            [____00__]
		// map select [______XX]
		u8 second = 0;
		// const u8 rex = get_instruction_rex(inst, operands);
		const u8 rex = 0;
		
		const bool r = rex & 0b00000100;
		const bool x = rex & 0b00000010;
		const bool b = rex & 0b00000001;
		const bool rr = get_mod_rm_reg(inst, operands) & 0b00010000;

		// ~R inverted REX.r
		second |= !r << 7;

		// ~X inverted REX.x
		second |= !x << 6;

		// ~B inverted REX.b
		second |= !b << 5;

		// ~R' inverted R (reg)
		second |= !rr << 4;

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
		// W                              [X_______]
		// ~vvvv                          [_XXXX___]
		//                                [_____1__]
		// operand size and type prefixes [______XX]
		u8 third = 0;

		const u8 w = static_cast<u8>((inst->is_rexw()) << 7);
		third |= w;

		// vvvv - negation of one of our v operand
		u8 vvvv = 0;

		if(inst->has_vex_vvvv()) {
			switch(inst->get_encoding_prefix()) {
				case ENC_EVEX_RVM:		
				case ENC_VEX_RVM: vvvv = static_cast<u8>((~operands[1].r & 0b00001111) << 3); break;
				case ENC_VEX_RMI: vvvv = static_cast<u8>((~operands[0].r & 0b00001111) << 3); break;
				case ENC_VEX_RMV: vvvv = static_cast<u8>((~operands[2].r & 0b00001111) << 3); break;
				case ENC_VEX_VM:  vvvv = static_cast<u8>((~operands[0].r & 0b00001111) << 3); break;
				case ENC_VEX_RM:  vvvv = 0b1111 << 3; break; // no 'V' part, just return a negated zero
				default: ASSERT(false, "unhandled vex prefix");
			}
		}
		else {
			vvvv = 0b01111000;
		}

		third |= vvvv;
		third |= 0b1 << 2;

		// operand size and operand prefixes
		if(inst->get_prefix() & OPERAND_SIZE_OVERRIDE) {
			third |= 0b00000001;
		}
		else {
			ASSERT(false, "unexpected prefix\n");
		} 

		m_bytes.push_back(third);

		// fourth
		// merge or zero                                                                  [X_______]
		// 12-bit vector length, or rounding control mode when combined with the next bit [_X______]
		// specifies 256-bit vector length                                                [__X_____]
		// source broadcast, rounding control (combined with L’L), or suppress exceptions [___X____]
		// ~V (expands vvvv)                                                              [____X___]
		// operand mask register (k0–k7) for vector instructions                          [_____XXX]
		
		u8 fourth = 0;

		// ~V
		bool v = true;

		if(inst->has_vex_vvvv()) {
			switch(inst->get_encoding_prefix()) {
				case ENC_EVEX_RVM:
				case ENC_VEX_RVM: v = static_cast<bool>((operands[1].r & 0b00010000)); break;
				default: ASSERT(false, "unhandled evex prefix");
			}
		}

		fourth |= !v << 3;

		if(has_masked_operand(inst, operands)) {
			masked_reg r = get_masked_operand(inst, operands);

			// merge or zero
			fourth |= (r.z & 0b00000001) << 7;

			// operand mask register
			fourth |= r.k;

			// operand size and type
			if(inst->get_ops() == OPS_256) {
				fourth |= 0b00100000;
			}
			else if(inst->get_ops() == OPS_512) {
				fourth |= 0b01000000;
			}
		}
		else {
			// operand size and type
			u8 ll = 0;

			if(inst->get_ops() == OPS_128) {
				ll = 0b00000010;
			}
			else if(inst->get_ops() == OPS_256) {
				ll = 0b00000001;
			}
			else {
				ASSERT(false, "unepxected operand size\n");
			}

			fourth |= ll << 5;
		}

		m_bytes.push_back(fourth);
	}

	void assembler::emit_opcode_prefix_rex(const ins* inst, const opn_data* operands) {
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

	void assembler::emit_instruction_prefix(const ins* inst) {
		if(inst->is_vex() || inst->is_evex()) {
			return;
		}

		if(inst->prefix == PREFIX_NONE) {
			return; // no prefix
		}

		// group 4
		if(inst->prefix & ADDRESS_SIZE_OVERRIDE) {
			m_bytes.push_back(0x67);
		}

		// group 3
		if(inst->prefix & OPERAND_SIZE_OVERRIDE) {
			m_bytes.push_back(0x66);
		}

		// group 2
		switch(inst->prefix & 0b00111100) {
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
		switch(inst->prefix & 0b00000011) {
			case LOCK:  m_bytes.push_back(0xF0); break;
			case REPNE: m_bytes.push_back(0xF2); break;
			case REP:   m_bytes.push_back(0xF3); break;
			default:                             break;
		}
	}

	auto inst_uses_extended_vex(const instruction* inst, const operand* operands) -> bool {
		for(u8 i = 0; i < inst->get_operand_count(); ++i) {
			if(is_operand_ymm(operands[i].type) && operands[i].r > 15) {
				return true;
			}
		}

		return false;
	}

	void assembler::emit_instruction_opcode(const ins* inst, const opn_data* operands) {
		// VEX instructions have the leading opcode encoded in themselves, so we have to skip it here
		u8 opcode_limit = 1;

		// prefix
		if(inst->is_rex()) {
			emit_opcode_prefix_rex(inst, operands);
		}
		else if(inst->is_vex()) {
			opcode_limit = 3;
		// 	if(inst_uses_extended_vex(inst, operands)) {
		// 		// when handling stuff like ymm16 we have to switch to evex
		// 		emit_opcode_prefix_evex(inst, operands);
		// 	}
		// 	else {
				emit_opcode_prefix_vex(inst, operands);
		//	}
		}
		else if(inst->is_evex()) {
			opcode_limit = 3;
			// emit_opcode_prefix_evex(inst, operands);
		}
		else {
			ASSERT(false, "invalid/unknown opcode prefix\n");
		}

		// opcode
		u64 opcode = inst->opcode;

		if(inst->is_ri()) {
			opcode += m_regs[0] & 0b00000111;
		}

		// append opcode bytes
		for(u8 i = 4; i-- > opcode_limit;) {
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

	void assembler::emit_operands(const ins* inst, const opn_data* operands) {
		for(u8 i = 0; i < inst->operand_count; ++i) {
			const opn current = inst->operands[i];

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

						for(u8 j = i; j < inst->operand_count; ++j) {
							// if we have another operand after the current one, calculate it's size
							if(is_operand_imm(inst->operands[j])) { // registers are already encoded
								new_displacement -= get_operand_bit_width(inst->operands[j]) / 8;
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

	void assembler::emit_instruction_mod_rm(const ins* inst, const opn_data* operands) {
		u8 rx = m_regs[0];
		u8 destination = m_regs[1];

		switch(inst->encoding) {
			case ENCN_VEX_RVM: destination = m_regs[2]; break;
			default: break;
		}

		if(inst->operand_count == 1) {
			rx = 0;
		}

		if(inst->is_rm()) {
			rx = inst->get_rm() - 2; // - 2 is a fixup we need for our encoding, this can be improved but isn't vital rn
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
				m_bytes.push_back(indirect(rx, 0b100));
			}
			else if(memory.base.type == REG_RIP) {
				m_bytes.push_back(indirect(rx, 0b101));
			}
			else if(memory.displacement.value == 0) {
				m_bytes.push_back(indirect(rx, has_sib ? 0b100 : memory.base.index));
			}
			else if(memory.displacement.min_bits <= 8) {
				// 8 bit displacement
				m_bytes.push_back(indirect_disp_8(rx, has_sib ? 0b100 : memory.base.index));
			}
			else {
				// 32 bit displacemen
				m_bytes.push_back(indirect_disp_32(rx, has_sib ? 0b100 : memory.base.index));
			}

			return; // nothing else to do
		}

		// forced mod/rm
		if(inst->is_r()) {
			if(inst->operand_count == 1 ) {
				m_bytes.push_back(direct(0, m_regs[0]));
			}
			else {
				m_bytes.push_back(direct(m_regs[0], destination));
			}
		}
		else if(inst->is_rm()) {
			m_bytes.push_back(direct(rx, m_regs[0]));
		}

	//	if(inst->has_variant()) {
	//		rx = inst->get_variant();
	//	}

	//	// mod rm / sib byte
	//	if(inst->is_r() || is_operand_mem(operands[0].type) || is_operand_mem(operands[1].type) || is_operand_mem(operands[2].type)) {
	//		u8 mod_rm_part;

	//		if(is_operand_mem(operands[0].type)) {
	//			const bool has_sib = has_sib_byte(operands);
	//			const auto memory = operands[0].memory;

	//			ASSERT(memory.displacement.min_bits <= 32, "too many displacement bits");

	//			// right mem
	//			if(memory.has_base == false) {
	//				// absolute address
	//				if(inst->is_ext()) {
	//					mod_rm_part = indirect(inst->get_ext(), 0b100);
	//				}
	//				else {
	//					// this may not be needed
	//					mod_rm_part = indirect(rx, 0b100); // 100 = SIB byte
	//				}
	//			}
	//			else if(memory.base.type == REG_RIP) {
	//				// rip reg
	//				if(inst->is_ext()) {
	//					mod_rm_part = indirect(inst->get_ext(), 0b101);
	//				}
	//				else {
	//					mod_rm_part = indirect(rx, 0b101); // 101 = RIP-relative
	//				}
	//			}
	//			else if(memory.displacement.value == 0) {
	//				// no displacement
	//				if(inst->is_ext()) {
	//					mod_rm_part = indirect(inst->get_ext(), has_sib ? 0b100 : memory.base.index);
	//				}
	// 				else {
	// 					mod_rm_part = indirect(rx, has_sib ? 0b100 : memory.base.index);
	// 				}
	// 			}
	// 			else if(memory.displacement.min_bits <= 8) {
	// 				// 8 bit displacement
	// 				if(inst->is_ext()) {
	// 					mod_rm_part = indirect_disp_8(inst->get_ext(), has_sib ? 0b100 : memory.base.index);
	// 				}
	// 				else {
	// 					mod_rm_part = indirect_disp_8(rx, has_sib ? 0b100 : memory.base.index);
	// 				}

	// 			}
	// 			else {
	// 				// 32 bit displacement
	// 				if(inst->is_ext()) {
	// 					mod_rm_part = indirect_disp_32(inst->get_ext(), has_sib ? 0b100 : memory.base.index);
	// 				}
	// 				else {
	// 					mod_rm_part = indirect_disp_32(rx, has_sib ? 0b100 : memory.base.index);
	// 				}
	// 			}
	// 		}
	// 		else if(is_operand_mem(operands[1].type)) {
	// 			const bool has_sib = has_sib_byte(operands);
	// 			const auto memory = operands[1].memory;

	// 			ASSERT(memory.displacement.min_bits <= 32, "too many displacement bits");

	// 			// right mem
	// 			if(memory.has_base == false) {
	// 				// absolute address
	// 				mod_rm_part = indirect(rx, 0b100); // 100 = SIB byte
	// 			}
	// 			else if(memory.base.type == REG_RIP) {
	// 				// rip reg
	// 				mod_rm_part = indirect(rx, 0b101); // 101 = RIP-relative
	// 			}
	// 			else if(memory.displacement.value == 0) {
	// 				// no displacement
	// 				mod_rm_part = indirect(rx, has_sib ? 0b100 : memory.base.index);
	// 			}
	// 			else if(memory.displacement.min_bits <= 8) {
	// 				// 8 bit displacement
	// 				mod_rm_part = indirect_disp_8(rx, has_sib ? 0b100 : memory.base.index);
	// 			}
	// 			else {
	// //				// 32 bit displacement
	//				mod_rm_part = indirect_disp_32(rx, has_sib ? 0b100 : memory.base.index);
	//			}
	//		}
	//		else if(is_operand_mem(operands[2].type)) {
	//			const bool has_sib = has_sib_byte(operands);
	//			const auto memory = operands[2].memory;

	//			ASSERT(memory.displacement.min_bits <= 32, "too many displacement bits");

	//			// right mem
	//			if(memory.has_base == false) {
	//				// absolute address
	//				mod_rm_part = indirect(rx, 0b100); // 100 = SIB byte
	//			}
	//			else if(memory.base.type == REG_RIP) {
	//				// rip reg
	//				mod_rm_part = indirect(rx, 0b101); // 101 = RIP-relative
	//			}
	//			else if(memory.displacement.value == 0) {
	//				// no displacement
	//				mod_rm_part = indirect(rx, has_sib ? 0b100 : memory.base.index);
	//			}
	//			else if(memory.displacement.min_bits <= 8) {
	//				// 8 bit displacement
	//				mod_rm_part = indirect_disp_8(rx, has_sib ? 0b100 : memory.base.index);
	//			}
	//			else {
	//				// 32 bit displacement
	//				mod_rm_part = indirect_disp_32(rx, has_sib ? 0b100 : memory.base.index);
	//			}
	//		}
	//		else {
	//			if(inst->get_direction()) {
	//				mod_rm_part = direct(rx, destination);
	//			}
	//			else {
	//				mod_rm_part = direct(destination, rx);
	//			}
	//		}

	//		m_bytes.push_back(mod_rm_part);
	//	}
	//	else if(inst->is_ext()) {
	//		m_bytes.push_back(direct(inst->get_ext(), destination));
	//	}
	}

	void assembler::emit_instruction_sib(const opn_data* operands) {
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

	void assembler::emit_instruction(u32 index, const opn_data* operands) {
		// locate the actual instruction we want to assemble (this doesn't have to match the specified
		// index, since we can apply optimizations which focus on stuff like shorter encodings)
		const ins* inst = find_instruction_info(index, operands);

		instruction_begin(inst, operands); // mark the instruction start (used for rip-relative addressing)

		// emit instruction parts
		emit_instruction_prefix(inst);
		emit_instruction_opcode(inst, operands);
		emit_instruction_mod_rm(inst, operands);
		emit_instruction_sib(operands);

		// emit immediate, displacement, and memory offset operands
		emit_operands(inst, operands);
	}

	auto assembler::has_sib_byte(const opn_data* operands) -> bool {
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

	auto extract_operand_reg(const opn_data& op) -> u8 {
		if(is_operand_reg(op.type)) {
			return op.r;
		}

		if(is_operand_mem(op.type) && op.memory.has_base) {
			return op.memory.base.index;
		}

		return 0;
	}


	auto extract_operand_reg_beg(const opn_data& op) -> u8 {
		if(is_operand_reg(op.type)) {
			return op.r;
		}

		if(is_operand_mem(op.type) && op.memory.has_base) {
			return op.memory.base.index;
		}

		return utility::limits<u8>::max();
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

	auto assembler::get_mod_rm_reg(const instruction* inst, const operand* operands) -> u8 {
		auto [rx, destination] = find_rex_pair(inst, operands);

		if(inst->has_variant()) {
			rx = inst->get_variant();
		}

		// mod rm / sib byte
		if(inst->is_r() || is_operand_mem(operands[0].type) || is_operand_mem(operands[1].type) || is_operand_mem(operands[2].type)) {
			if(is_operand_mem(operands[0].type)) {
				// 32 bit displacement
				if(inst->is_ext()) {
					return inst->get_ext();
				}
				else {
					return rx;
				}
			}
			else if(is_operand_mem(operands[1].type)) {
				return rx;
			}
			else if(is_operand_mem(operands[2].type)) {
				return rx;
			}
			else {
				if(inst->get_direction()) {
					return rx;
				}
				else {
					return destination;
				}
			}
		}
		else if(inst->is_ext()) {
			return inst->get_ext();
		}

		return 0;
	} 
	auto assembler::get_instruction_rex_rex(const ins* inst, const opn_data* operands) -> u8 {
		const bool is_rexw = inst->is_rexw();
		const u8 operand_count = inst->operand_count;

		u8 rx = 0;
		u8 base = 0;
		u8 index = 0;

		// figure out the index bit first
		if(inst->has_mem_operand()) {
			const mem mem = operands[inst->get_mem_operand()].memory;

			if(mem.has_index) {
				index = mem.index.index;
			}
		}
		
		if(m_reg_count == 1) {
			switch(inst->encoding) {
				case ENCN_NORMAL: 
				case ENCN_M:
				case ENCN_R: base = m_regs[0]; break;
				default: rx = m_regs[0]; break;
			}
		}
		else if(m_reg_count == 2) {
			// mem, x, x
			if(is_operand_mem(operands[0].type) && operands[0].memory.has_base == false && operand_count == 3) {
				rx = m_regs[1];
			}
			else if(inst->operands[1] == OPN_CL) {
				base = m_regs[0];
			}
			else if(inst->is_ri() && m_regs[0] > 7) {
				base = m_regs[0];
			}
			else {
				rx = m_regs[0];
				base = m_regs[1];
			}
		}
		else if(m_reg_count == 3) {
			rx = m_regs[0];
			base = m_regs[1];
		}
		
		return rex(is_rexw, rx, base, index);
	}

	auto assembler::get_instruction_rex_vex(const ins* inst, const opn_data* operands) -> u8 {
		const bool is_rexw = inst->is_rexw();

		u8 rx = 0;
		u8 base = 0;
		u8 index = 0;
		u8 index_byte = 0;

		// figure out the index bit first
		if(inst->has_mem_operand()) {
			const mem mem = operands[inst->get_mem_operand()].memory;

			if(mem.has_index) {
				index = mem.index.index;
			}
		}

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

		switch(inst->encoding) {
			case ENCN_VEX_RVM: {
				switch(index_byte) {
					case 0b1110: 
					case 0b1000:
					case 0b0000: rx = registers[0]; base = registers[1]; break;
					case 0b1100:
					case 0b0010: rx = registers[1]; base = registers[2]; break;
					case 0b1010:
					case 0b0110: rx = registers[0]; base = registers[2]; break;
					case 0b0100: rx = registers[2]; base = registers[0]; break;
					default: ASSERT(false, "unhandled rex case 1");
				}

				break;
			}
			case ENCN_VEX_RMV: {
				switch(index_byte) {
					case 0b00001000:
					case 0b00001010:
					case 0b00001100:
					case 0b00001110:
					case 0b00000000:
					case 0b00000010: rx = registers[0]; base = registers[1]; break;
					case 0b00000110: rx = registers[0]; base = registers[2]; break;
					case 0b00000100: rx = registers[2]; base = registers[1]; break;
					default: ASSERT(false, "unhandled rex case 2");
				}

				break;
			}
			case ENCN_VEX_VM: {
				switch(index_byte) {
					case 0b00000000:
					case 0b00000100: rx = registers[0]; base = registers[1]; break;
					case 0b00001000: rx = registers[1]; base = registers[1]; break;
					case 0b00001100: rx = 0;            base = registers[1]; break;
					default: ASSERT(false, "unhandled rex case 3");
				}

				break;
			}
			case ENCN_VEX_RM: {
				switch(index_byte) {
					case 0b00001000:
					case 0b00001100:
					case 0b00000100: rx = registers[0]; base = registers[1]; break;
					case 0b00000000: rx = registers[1]; base = registers[0]; break;
					default: ASSERT(false, "unhandled rex case 4");
				}

				break;
			}
			default: ASSERT(false, "unhandled rex case 5");
		}

		return rex(is_rexw, rx, base, index);
	}

	auto assembler::get_instruction_rex_evex(const instruction* inst, const operand* operands) -> u8 {
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

		const u8 registers[4] = {
			// extract_operand_reg(operands[0]),
			// extract_operand_reg(operands[1]),
			// extract_operand_reg(operands[2]),
			// extract_operand_reg(operands[3]),
		};

		// op[0] is extended? [____X___]
		// op[1] is extended? [_____X__]
		// op[2] is extended? [______X_]
		// op[3] is extended? [_______X]
		index_byte |= (registers[0] >= 8) << 3;
		index_byte |= (registers[1] >= 8) << 2;
		index_byte |= (registers[2] >= 8) << 1;
		index_byte |= (registers[3] >= 8) << 0;

		// utility::console::print("here {}\n", (int)index_byte);
		switch(inst->get_encoding_prefix()) {
			case ENC_VEX_RMI: {
				switch(index_byte) {
					case 0b00001000:
					case 0b00001110:
					case 0b00000000: rx = registers[0]; base = registers[1]; break;
					case 0b00001100: rx = registers[1]; base = registers[0]; break;
					case 0b00000010: rx = registers[1]; base = registers[2]; break;
					case 0b00001010:
					case 0b00000110: rx = registers[0]; base = registers[2]; break;
					case 0b00000100: rx = registers[2]; base = registers[1]; break;
					default: ASSERT(false, "unhandled rex case 1");
				}

				break;
			}
			case ENC_VEX_RVM:
			case ENC_EVEX_RVM: {
				switch(index_byte) {
					case 0b00001110: {
						rx = registers[0]; 
						base = registers[1];
						
						// minor hack - when all of our registers are > 15 (ie. ymm31), we have to use an index
						// if(operands[0].r > 15 && operands[1].r > 15 && operands[2].r > 15) {
						// 	index = registers[2];
						// }
						break;
					}
					case 0b00001000:
					case 0b00000000: rx = registers[0]; base = registers[1]; break;
					case 0b00001100:
					case 0b00000010: rx = registers[1]; base = registers[2]; break;
					case 0b00001010:
					case 0b00000110: rx = registers[0]; base = registers[2]; break;
					case 0b00000100: rx = registers[2]; base = registers[0]; break;
					default: ASSERT(false, "unhandled rex case 1");
				}

				if(operands[2].r > 15) {
					index = registers[2];
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
					default: ASSERT(false, "unhandled rex case 2");
				}

				break;
			}
			case ENC_VEX_VM: {
				switch(index_byte) {
					case 0b00000000:
					case 0b00000100: rx = registers[0]; base = registers[1]; break;
					case 0b00001000: rx = registers[1]; base = registers[1]; break;
					case 0b00001100: rx = 0;            base = registers[1]; break;
					default: ASSERT(false, "unhandled rex case 3");
				}

				break;
			}
			case ENC_VEX_RM: {
				switch(index_byte) {
					case 0b00001000:
					case 0b00001100:
					case 0b00000100: rx = registers[0]; base = registers[1]; break;
					case 0b00000000: rx = registers[1]; base = registers[0]; break;
					default: ASSERT(false, "unhandled rex case 4");
				}

				break;
			}
			default: ASSERT(false, "unhandled rex case 5");
		}

		// utility::console::print("{}\n", rx);
		// utility::console::print("{}\n", base);
		// utility::console::print("{}\n", index);
		return rex(is_rexw, rx, base, index);
	}

	auto assembler::get_instruction_rex(const ins* inst, const opn_data* operands) -> u8 {
		// THIS IS UNCHECKED, MAYBE WE'LL HAVE TO RETURN 0
		const u8 operand_count = inst->operand_count;

		if(operand_count == 0) {	
			return rex(inst->is_rexw(), 0, 0, 0);
		}

		if(inst->is_rex()) {
			return get_instruction_rex_rex(inst, operands);
		}

		if(inst->is_vex()) {
			// if(inst_uses_extended_vex(inst, operands)) {
			// 	// when handling stuff like ymm16 we have to switch to evex
			// 	return get_instruction_rex_evex(inst, operands);
			// }
			// else {
			return get_instruction_rex_vex(inst, operands);
			// }
		}

		// if(inst->is_evex()) {
		// 	return get_instruction_rex_evex(inst, operands);
		// }
		// 
		// ASSERT(false, "invalid/unknown opcode prefix\n");
	
		return 0;
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
		// ASSERT(rx < 16, "invalid rx");
		// ASSERT(base < 16, "invalid base");
		// ASSERT(index < 16, "invalid index");

		// whenever a used register is larger than 3 bits we need to mark the extension bit
		// the result will then be extended in mod R/M or the SIB byte.

		//                                     rex WRXB
		// rex prefix                         [0100____]
		// w (64 bit mode)                    [____X___]
		// r (mod R/M extension) (rx > RDI)   [_____X__]
		// x (sib extension) (index > RDI)    [______X_]
		// b (mod R/M extension) (base > RDI) [_______X]
		
		// TODO: this is a temporary hack
		rx = utility::clamp(rx, 0, 15);
		base = utility::clamp(base, 0, 15);
		index = utility::clamp(index, 0, 15);

		const u8 index_mask = static_cast<u8>((index >> 3) << 1);
		const u8 rx_mask = static_cast<u8>((rx >> 3) << 2);
		const u8 w_mask = static_cast<u8>(w << 3);
		const u8 base_mask = base >> 3;

		return 0x40 | base_mask | index_mask | rx_mask | w_mask;
	}

	auto assembler::mod_rx_rm(u8 mod, u8 rx, u8 rm) -> u8 {
		// ASSERT(mod < 4, "invalid mod");
		// ASSERT(rx < 16, "invalid rx");
		// ASSERT(rm < 16, "invalid rm");

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

	void assembler::instruction_begin(const ins* inst, const opn_data* operands) {
		m_current_inst_begin = m_bytes.get_size();
		m_reg_count = 0;

		utility::memset(m_regs, 0, sizeof(u8) * 4);

		u8 temp[4] = { 0 };

		for(u8 i = 0; i < 4; ++i) {
			u8 r = extract_operand_reg_beg(operands[i]);

			if(r != utility::limits<u8>::max()) {
				temp[m_reg_count++] = r;
			}
		}

		if(m_reg_count == 0) { /*nothing to do*/ }
		else if(m_reg_count == 1) {
			switch(inst->encoding) {
				case ENCN_NORMAL:
				case ENCN_RM:    
				case ENCN_MR:     
				case ENCN_M:     
				case ENCN_VEX_VM:     
				case ENCN_VEX_RM:     
				case ENCN_R:      m_regs[0] = temp[0]; break;
				default: ASSERT(false, "unknown encoding for 1 reg\n");
			}
		}
		else if(m_reg_count == 2) {
			switch(inst->encoding) {
				case ENCN_NORMAL: {
					if(is_operand_rax(inst->operands[0])) {
						m_regs[0] = temp[1];
					}
					else if(is_operand_rax(inst->operands[1])) {
						m_regs[0] = temp[0];
					}
					else {
						m_regs[0] = temp[0]; 
						m_regs[1] = temp[1];
					}

					break;
				}
				case ENCN_VEX:  
				case ENCN_VEX_VM: 
				case ENCN_VEX_RM:  
				case ENCN_VEX_RVM: 
				case ENCN_RM: m_regs[0] = temp[0]; m_regs[1] = temp[1]; break;
				case ENCN_MR: {
					if(inst->operands[2] == OPN_CL) {
						m_regs[0] = temp[0];
						m_regs[1] = temp[0];
					}
					else {
						m_regs[0] = temp[1]; m_regs[1] = temp[0];
					}

					break;
				}
				default: ASSERT(false, "unknown encoding for 2 regs\n");
			}
		}
		else if(m_reg_count == 3) {
			switch(inst->encoding) {
				case ENCN_RM: m_regs[0] = temp[2]; m_regs[1] = temp[1];  break;
				case ENCN_MR: m_regs[0] = temp[1]; m_regs[1] = temp[0]; m_regs[2] = temp[2]; break;
				case ENCN_VEX: 
				case ENCN_VEX_RVM: m_regs[0] = temp[0]; m_regs[1] = temp[1]; m_regs[2] = temp[2]; break;
				default: ASSERT(false, "unknown encoding for 3 regs\n");
			}
		}
		else {
			ASSERT(false, "unknown reg count {}\n", m_reg_count);
		}
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

	auto is_operand_of_same_kind(opn a, opn b) -> bool {
		switch(a) {
			// don't just consider regular equalities, focus on register bit widths as well
			case OPN_AL:  return b == OPN_AL  || b == OPN_CL  || b == OPN_R8;  // 8 bits
			case OPN_AX:  return b == OPN_AX  || b == OPN_DX  || b == OPN_R16; // 16 bits
			case OPN_EAX: return b == OPN_EAX || b == OPN_ECX || b == OPN_R32; // 32 bits
			case OPN_RAX: return b == OPN_RAX || b == OPN_RCX || b == OPN_R64; // 64 bits
			default: return a == b; // regular compares
		}
	}
} // namespace baremetal

