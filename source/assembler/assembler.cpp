#include "assembler.h"

#include "assembler/parser.h"
#include "utility/result.h"

#define EXPECT_TOKEN(expected)                            \
  do {                                                    \
    if(m_lexer.current != expected) {                     \
      return utility::error("unexpected token received"); \
		}                                                     \
  }                                                       \
  while(false)

namespace baremetal {
	namespace detail {
		auto imm_to_scale(const imm& i) -> utility::result<scale> {
			switch(i.value) {
				case 1: return SCALE_1;
				case 2: return SCALE_2;
				case 4: return SCALE_4;
				case 8: return SCALE_8;
				default: return utility::error("invalid memory scale");
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

	auto assembler::assemble(const utility::dynamic_string& assembly) -> utility::result<void> {
		m_lexer.set_text(assembly);
		m_lexer.get_next_token();

		while(m_lexer.current != TOK_EOF) {
			TRY(parse_instruction());
		}

		return SUCCESS;
	}

	auto assembler::get_bytes() const -> const utility::dynamic_array<u8>& {
		return m_module.get_bytes();
	}

	void assembler::clear() {
		m_assembly.clear();
		m_module.clear();
	}

	auto assembler::parse_instruction() -> utility::result<void> {
		// instruction mnemonic
		utility::dynamic_string instruction_identifier;

		// PARSER_VERIFY(KW_IDENTIFIER);
		instruction_identifier = utility::dynamic_string(m_lexer.current_string);

		const u32 first = find_instruction_by_name(instruction_identifier.get_data());

		if(first == utility::limits<u32>::max()) {
			// instruction doesn't exist
			return utility::error("unknown instruction specified");
		}

		// ensure our destination is clean
		utility::memset(operands, 0, sizeof(operand) * 4);
		operand_i = 0;

		// operands
		while(m_lexer.get_next_token() != TOK_EOF) {
			switch (m_lexer.current) {
				case TOK_MINUS:             TRY(parse_number_negative()); break;
				case TOK_CR0 ... TOK_R15B:   TRY(parse_register()); break;
				case TOK_LBRACKET:          TRY(parse_bracket()); break; 
				case TOK_BYTE ... TOK_TWORD: TRY(parse_memory()); break;
				case TOK_NUMBER:            parse_number(); break;	
				default: return utility::error("unexpected token received as instruction operand");
			};

			// operands are separated by commas
			if(m_lexer.current != TOK_COMMA) {
				break;
			}
		}

		// locate the specific variant (dumb linear search in our specific group)
		u32 instruction_i = first;
		constexpr u32 db_size = sizeof(instruction_db) / sizeof(instruction);

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
				return SUCCESS;
			}

			instruction_i++;
		}

		// invalid instruction and operand combination
		return utility::error("invalid operand combination for the specified instruction");
	}

	auto assembler::parse_register() -> utility::result<void> {		
		operands[operand_i] = operand(token_to_register(m_lexer.current));

		// parse mask operands (ie. "{k1} {z0}")
		while(true) {
			TRY(bool result, parse_mask_register(operands[operand_i]));

			if(result == false) {
				break;
			}
		}

		operand_i++;
		return SUCCESS;
	}

	void assembler::parse_number() {
		operands[operand_i++] = operand(m_lexer.current_immediate); 
		m_lexer.get_next_token();
	}

	auto assembler::parse_number_negative() -> utility::result<void> {
		m_lexer.get_next_token();
		EXPECT_TOKEN(TOK_NUMBER);

		operands[operand_i++] = operand(imm(-static_cast<i64>(m_lexer.current_immediate.value)));
		m_lexer.get_next_token();

		return SUCCESS;
	}

	auto assembler::parse_memory() -> utility::result<void> {
		token_type mem_type = m_lexer.current;
		operand op;

		m_lexer.get_next_token();
		EXPECT_TOKEN(TOK_LBRACKET);

		switch(mem_type) {
			case TOK_BYTE:  op.type = OP_M8;  break;
			case TOK_WORD:  op.type = OP_M16; break;
			case TOK_DWORD: op.type = OP_M32; break;
			case TOK_QWORD: op.type = OP_M64; break;
			case TOK_TWORD: op.type = OP_M80; break;
			default: ASSERT(false, "unreachable\n");
		}

		m_lexer.get_next_token();
		TRY(parse_memory(op.memory));
		
		EXPECT_TOKEN(TOK_RBRACKET);
		m_lexer.get_next_token();

		operands[operand_i++] = op;
		return SUCCESS;
	}

	auto assembler::parse_bracket() -> utility::result<void> {
		switch(m_lexer.get_next_token()) {
			case TOK_BYTE ... TOK_QWORD: {
				m_lexer.get_next_token();
				EXPECT_TOKEN(TOK_NUMBER);

				operands[operand_i++] = operand(moff(m_lexer.current_immediate.value));
				m_lexer.get_next_token();
				EXPECT_TOKEN(TOK_RBRACKET);
				m_lexer.get_next_token();
				break;
			}
			default: {
				// large mem operand or broadcast
				operand memory;

				memory.type = OP_M128;

				TRY(parse_memory(memory.memory));
				EXPECT_TOKEN(TOK_RBRACKET);

				if(m_lexer.get_next_token() == TOK_LBRACE) {
					// broadcast
					u8 n = 0;
					m_lexer.force_keyword = true;

					switch(m_lexer.get_next_token()) {
						case TOK_1TO2: n = 2; break;
						case TOK_1TO4: n = 4; break;
						case TOK_1TO8: n = 8; break;
						case TOK_1TO16: n = 16; break;
						case TOK_1TO32: n = 32; break;
						default: return utility::error("invalid broadcast specified");
					}

					m_lexer.get_next_token();
					EXPECT_TOKEN(TOK_RBRACE);
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
						default: return utility::error("invalid broadcast width specified");
					}

					operands[operand_i++] = operand(b, ty);  
				}
				else {
					operands[operand_i++] = memory;
				}

				break;
			}
		}

		return SUCCESS;
	}

	auto assembler::parse_mask_register(operand& op) -> utility::result<bool> {
		if(m_lexer.get_next_token() == TOK_LBRACE) {
			m_lexer.get_next_token();
			
			char c = m_lexer.current_string[0];

			switch(c) {
				case 'k': {
					if(m_lexer.current_string.get_size() != 2) {
						return utility::error("invalid mask register specified");
					}

					char* end;
					op.mr.z = false;
					op.mr.k = static_cast<u8>(strtoul(m_lexer.current_string.get_data() + 1, &end, 10));

					if(op.mr.k >= 8) {
						utility::error("invalid mask register specified");
					}

					if(is_operand_xmm(op.type)) { op.type = OP_XMM_K; }
					else if(is_operand_ymm(op.type)) { op.type = OP_YMM_K; }
					else if(is_operand_zmm(op.type)) { op.type = OP_ZMM_K; }
					else if(op.type == OP_K) { op.type = OP_K_K; }

					break;
				}
				case 'z': {
					if(m_lexer.current_string.get_size() != 2) {
						utility::error("invalid mask register specified");
					}

					op.mr.z = true; // TODO: technically not needed, as we can interpret it from the type

					if(is_operand_xmm(op.type)) { op.type = OP_XMM_KZ; }
					else if(is_operand_ymm(op.type)) { op.type = OP_YMM_KZ; }
					else if(is_operand_zmm(op.type)) { op.type = OP_ZMM_KZ; }

					break;
				}

				return utility::error("unknown mask register specified");
			}

			m_lexer.get_next_token();
			EXPECT_TOKEN(TOK_RBRACE);

			return true;
		}

		return false;
	}

	auto assembler::parse_memory(mem& memory) -> utility::result<void> {
		reg current_reg = reg::create_invalid();
		imm current_imm;

		bool scale_mode = false;
		bool imm_set = false;

		// TODO: this still doesn't work with negative operands

		// entry
		while(true) {
			switch(m_lexer.current) {
				// register
				case TOK_CR0 ... TOK_R15B: {
					if(scale_mode && imm_set) {
						// scale * reg
						memory.index = token_to_register(m_lexer.current);
						memory.has_index = true;

						TRY(const auto scale, detail::imm_to_scale(current_imm));
						memory.s = scale;

						scale_mode = false;
						imm_set = false;
					}
					else {
						current_reg = token_to_register(m_lexer.current);
					}

					break;
				}
				case TOK_REL: {
					// rel $
					m_lexer.get_next_token();
					EXPECT_TOKEN(TOK_DOLLARSIGN);
					current_reg = rip;
					break;
				}
				case TOK_ASTERISK: {
					scale_mode = true;
					break;
				}
				case TOK_PLUS: {
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
				case TOK_MINUS: {
					ASSERT(false, "not implemented\n");
					break;
				}
				case TOK_NUMBER: {
					if(scale_mode && current_reg.is_valid()) {
						// reg * scale
						memory.index = current_reg;
						memory.has_index = true;

						TRY(const auto scale, detail::imm_to_scale(m_lexer.current_immediate));
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
				case TOK_RBRACKET: {
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

					return SUCCESS;
				}
				default: {
					return utility::error("unexpected token received in memory operand");
				}
			}

			m_lexer.get_next_token();
		}
	}
} // namespace baremetal

