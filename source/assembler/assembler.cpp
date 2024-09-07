#include "assembler.h"

#include "assembler/parser.h"

#define PARSER_VERIFY(expected)																				  		 \
  if(m_lexer.current != expected) {                                 				 \
    utility::console::print("unexpected token: {}\n", (i32)m_lexer.current); \
    return false;                                                            \
  }

#define PARSER_EXIT()                            \
  utility::console::print("unexpected token\n"); \
  return false;

namespace baremetal {
	namespace detail {
		auto imm_to_scale(const imm& i) -> scale {
			switch(i.value) {
				case 1: return SCALE_1;
				case 2: return SCALE_2;
				case 4: return SCALE_4;
				case 8: return SCALE_8;
				default: utility::console::print_err("invalid memory scale specified\n"); return SCALE_NONE;
			}
		}
	
		auto inst_match(operand_type a, operand b) -> bool{
			switch(a) {
				case OP_FS:  return b.type == OP_SREG && b.r == fs.index;
				case OP_GS:  return b.type == OP_SREG && b.r == gs.index;
				case OP_AL:  return b.type == OP_R8 && b.r == al.index;
				case OP_AX:  return b.type == OP_R16 && b.r == ax.index;
				case OP_EAX: return b.type == OP_R32 && b.r == eax.index;
				case OP_RAX: return b.type == OP_R64 && b.r == rax.index;
				case OP_CL:  return b.type == OP_R8 && b.r == cl.index;
				case OP_DX:  return b.type == OP_R16 && b.r == dx.index;
				case OP_ECX: return b.type == OP_R32 && b.r == ecx.index;
				case OP_RCX: return b.type == OP_R64 && b.r == rcx.index;
				case OP_ST0: return b.type == OP_ST && b.r == st0.index;
				case OP_MEM: return b.type == OP_M128;
				default:     return a == b.type;
			}
		}
	
		auto is_operand_match(u32 inst_i, operand* operands) -> bool {
			const instruction& inst = instruction_db[inst_i];
	
			for(u8 i = 0; i < 4; ++i) {
				// if the operands at a given index are both imm we ignore their difference
				if(
					!(inst_match(inst.operands[i], operands[i])) &&
					!(is_operand_imm(inst.operands[i]) && is_operand_imm(operands[i].type)) &&
					!(is_operand_moff(inst.operands[i]) && is_operand_moff(operands[i].type)) &&
					!(is_operand_rel(inst.operands[i]) && is_operand_imm(operands[i].type)) &&
					!(inst.operands[i] == OP_M256 && operands[i].type == OP_M128) && // HACK - we don't really know if we're dealing with a mem128 or a mem256, this depends on the instruction
					!(inst.operands[i] == OP_M512 && operands[i].type == OP_M128) && // HACK - we don't really know if we're dealing with a mem128 or a mem256, this depends on the instruction
					!(inst.operands[i] == OP_TMEM && operands[i].type == OP_M128) // HACK - we don't really know if we're dealing with a mem128 or a mem256, this depends on the instruction
				) {
					return false;
				}
			}
	
			return true;
		}
	} // namespace detail

	assembler::assembler() {}

	auto assembler::assemble(const utility::dynamic_string& assembly) -> bool {
		m_lexer.set_text(assembly);
		m_lexer.get_next_token();

		while(m_lexer.current != KW_EOF) {
			if(assemble_instruction() == false) {
				return false;
			}
		}

		return true;
	}

	auto assembler::get_bytes() const -> const utility::dynamic_array<u8>& {
		return m_module.get_bytes();
	}

	void assembler::clear() {
		m_assembly.clear();
		m_module.clear();
	}

	auto assembler::assemble_instruction() -> bool {
		utility::dynamic_string instruction_identifier;

		PARSER_VERIFY(KW_IDENTIFIER);
		instruction_identifier = utility::dynamic_string(m_lexer.current_string);

		const u32 first = find_instruction_by_name(instruction_identifier.get_data());

		if(first == utility::limits<u32>::max()) {
			utility::console::print("unknown instruction '{}' found, stopping\n", instruction_identifier);
			return false;
		}

		operand operands[4] = {{}};
		u8 operand_i = 0;

		// operands
		while(m_lexer.get_next_token() != KW_EOF) {
			switch (m_lexer.current) {
				// registers
				case KW_CR0 ... KW_R15B: {
					operands[operand_i] = operand(keyword_to_register(m_lexer.current));
					
					while(parse_mask_reg(operands[operand_i])) {}

					operand_i++;
					break;
				}
				// numerical literals
				case KW_NUMBER: {
					operands[operand_i++] = operand(m_lexer.current_immediate);
					m_lexer.get_next_token();
					break;
				}
				case KW_MINUS: {
					m_lexer.get_next_token();
					PARSER_VERIFY(KW_NUMBER);

					operands[operand_i++] = operand(imm(-static_cast<i64>(m_lexer.current_immediate.value)));
					m_lexer.get_next_token();
					break;
				}
				case KW_LBRACKET: {
					switch(m_lexer.get_next_token()) {
						case KW_BYTE ... KW_QWORD: {
							m_lexer.get_next_token();
							PARSER_VERIFY(KW_NUMBER);

							operands[operand_i++] = operand(moff(m_lexer.current_immediate.value));
							m_lexer.get_next_token();
							PARSER_VERIFY(KW_RBRACKET);
							m_lexer.get_next_token();
							break;
						}
						default: {
							// large mem operand or broadcast
							operand memory;

							memory.type = OP_M128;

							parse_memory(memory.memory);
							PARSER_VERIFY(KW_RBRACKET);

							if(m_lexer.get_next_token() == KW_LBRACE) {
								// broadcast
								u8 n = 0;
								m_lexer.force_keyword = true;

								switch(m_lexer.get_next_token()) {
									case KW_1TO2: n = 2; break;
									case KW_1TO4: n = 4; break;
									case KW_1TO8: n = 8; break;
									case KW_1TO16: n = 16; break;
									case KW_1TO32: n = 32; break;
									default: PARSER_EXIT();
								}

								m_lexer.get_next_token();
								PARSER_VERIFY(KW_RBRACE);
								m_lexer.get_next_token();

								broadcast b;
								b.m = memory.memory;
								b.n = n;

								u16 op_before_width = get_operand_bit_width(operands[operand_i - 1].type);
								u16 b_width = op_before_width / n;
								operand_type ty;

								switch(b_width) {
									case 16: ty = OP_B16; break;
									case 32: ty = OP_B32; break;
									case 64: ty = OP_B64; break;
									default: utility::console::print_err("unexpected b: {} (before: {}, n: {}, ty: {})\n", b_width, op_before_width, n, (i32)operands[operand_i - 1].type); return false;
								}

								operands[operand_i++] = operand(b, ty);  
							}
							else {
								operands[operand_i++] = memory;
							}

							break;
						}
					}

					break;
				}
				// memory operands
				case KW_BYTE ... KW_TWORD: {
					keyword_type mem_type = m_lexer.current;

					m_lexer.get_next_token();
					PARSER_VERIFY(KW_LBRACKET);

					operand memory;

					switch(mem_type) {
						case KW_BYTE: memory.type = OP_M8; break;
						case KW_WORD: memory.type = OP_M16; break;
						case KW_DWORD: memory.type = OP_M32; break;
						case KW_QWORD: memory.type = OP_M64; break;
						case KW_TWORD: memory.type = OP_M80; break;
						default: ASSERT(false, "unreachable\n");
					}

					m_lexer.get_next_token();
					parse_memory(memory.memory);

					PARSER_VERIFY(KW_RBRACKET);

					operands[operand_i++] = memory;

					m_lexer.get_next_token();
					break;
				}
				default: PARSER_EXIT();
			};

			if(m_lexer.current != KW_COMMA) {
				break;
			}
		}

		u32 instruction_i = first;
		constexpr u32 db_size = sizeof(instruction_db) / sizeof(instruction);

		// locate the specific variant (dumb linear search)
		while(instruction_i < db_size && utility::compare_strings(instruction_db[instruction_i].name, instruction_db[first].name) == 0) {
			if(detail::is_operand_match(instruction_i, operands)) {
				for(u8 j = 0; j < operand_i; ++j) {
					operands[j].type = instruction_db[instruction_i].operands[j]; // HACK: just modify all instructions to the actual type (relocations, mem256)

					if(is_operand_rel(instruction_db[instruction_i].operands[j])) {
						rel r = rel(static_cast<i32>(operands[j].immediate.value));
						operands[j].relocation = r; 
					}
				}

				m_module.emit_instruction(instruction_i, operands);
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

	auto assembler::parse_mask_reg(operand& op) -> bool {
		if(m_lexer.get_next_token() == KW_LBRACE) {
			m_lexer.get_next_token();
			
			char c = m_lexer.current_string[0];

			switch(c) {
				case 'k': {
					ASSERT(m_lexer.current_string.get_size() == 2, "invalid mask register specified\n");
					char* end;
					op.mr.k  = static_cast<u8>(strtoul(m_lexer.current_string.get_data() + 1, &end, 10));
					ASSERT(op.mr.k < 8, "invalid mask register specified\n");

					if(is_operand_xmm(op.type)) { op.type = OP_XMM_K; }
					else if(is_operand_ymm(op.type)) { op.type = OP_YMM_K; }
					else if(is_operand_zmm(op.type)) { op.type = OP_ZMM_K; }
					else if(op.type == OP_K) { op.type = OP_K_K; }

					break;
				}
				case 'z': {
					ASSERT(m_lexer.current_string.get_size() == 1, "invalid mask register specified\n");
					op.mr.z = true;

					if(is_operand_xmm(op.type)) { op.type = OP_XMM_KZ; }
					else if(is_operand_ymm(op.type)) { op.type = OP_YMM_KZ; }
					else if(is_operand_zmm(op.type)) { op.type = OP_ZMM_KZ; }

					break;
				}

				default: utility::console::print_err("unknown mask register specified\n"); return false;
			}

			m_lexer.get_next_token();
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
			switch(m_lexer.current) {
				// register
				case KW_CR0 ... KW_R15B: {
					if(scale_mode && imm_set) {
						// scale * reg
						memory.index = keyword_to_register(m_lexer.current);
						memory.has_index = true;

						const auto scale = detail::imm_to_scale(current_imm);

						if(scale == SCALE_NONE) {
							return false; 
						}

						memory.s = scale;

						scale_mode = false;
						imm_set = false;
					}
					else {
						current_reg = keyword_to_register(m_lexer.current);
					}

					break;
				}
				case KW_REL: {
					// rel $
					m_lexer.get_next_token();
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

						const auto scale = detail::imm_to_scale(m_lexer.current_immediate);

						if(scale == SCALE_NONE) {
							return false; 
						}

						memory.s = scale;

						scale_mode = false;
						current_reg = reg::create_invalid();
					}
					else{
						current_imm = m_lexer.current_immediate;
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
					utility::console::print_err("unexpected token received ('{}')\n", (i32)m_lexer.current);
					return false;
				}
			}

			m_lexer.get_next_token();
		}
	}
} // namespace baremetal

