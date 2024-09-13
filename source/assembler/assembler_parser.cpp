#include "assembler_parser.h"

#include "assembler/instruction/instruction.h"
#include "assembler/instruction/operands/operands.h"
#include "assembler/instruction/operands/registers.h"
#include "assembler/lexer.h"
#include "utility/types.h"

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
				case OP_FS:      return b.type == OP_SREG && b.r == fs.index;
				case OP_GS:      return b.type == OP_SREG && b.r == gs.index;
				case OP_AL:      return b.type == OP_R8 && b.r == al.index;
				case OP_AX:      return b.type == OP_R16 && b.r == ax.index;
				case OP_EAX:     return b.type == OP_R32 && b.r == eax.index;
				case OP_RAX:     return b.type == OP_R64 && b.r == rax.index;
				case OP_CL:      return b.type == OP_R8 && b.r == cl.index;
				case OP_DX:      return b.type == OP_R16 && b.r == dx.index;
				case OP_ECX:     return b.type == OP_R32 && b.r == ecx.index;
				case OP_RCX:     return b.type == OP_R64 && b.r == rcx.index;
				case OP_ST0:     return b.type == OP_ST && b.r == st0.index;
				case OP_MEM:     return b.type == OP_M128;
				case OP_VM64X:   return b.type == OP_VM32X || a == b.type;
				case OP_VM64Y:   return b.type == OP_VM32Y || a == b.type;
				case OP_VM64Z:   return b.type == OP_VM32Z || a == b.type;
				case OP_VM64X_K: return b.type == OP_VM32X_K || a == b.type;
				case OP_VM64Y_K: return b.type == OP_VM32Y_K || a == b.type;
				case OP_VM64Z_K: return b.type == OP_VM32Z_K || a == b.type;
				case OP_M16_K:
				case OP_M32_K:
				case OP_M64_K:
				case OP_M128_K:
				case OP_M256_K:
				case OP_M512_K:   return b.type == OP_M128_K || a == b.type; // TODO: temp hack - we can't really parse 
																																		 // masked memory operands which have a
																																		 // specified size, hence we default to M128
				default:         return a == b.type;
			}
		}
	
		auto is_operand_match(u32 inst_i, operand* operands, u8 broadcast_n) -> bool {
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

				if(is_operand_reg(operands[i].type) && operands[i].r > 15 && !inst.is_evex()) {
					return false;
				}

				if(
					inst.has_broadcast_operand() &&
					broadcast_to_bits(inst.operands[inst.get_broadcast_operand()])  * broadcast_n != inst_size_to_int(inst.op_size)
				) {
					return false;
				}
			}
	
			return true;
		}

		auto is_operand_match_partial(u32 inst_i, operand* operands, u8 count) -> bool {
			const instruction& inst = instruction_db[inst_i];
	
			for(u8 i = 0; i < count; ++i) {
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

				if(is_operand_reg(operands[i].type) && operands[i].r > 15 && !inst.is_evex()) {
					return false;
				}
			}
	
			return true;
		}
	} // namespace detail

	assembler_parser::assembler_parser() {}

	auto assembler_parser::parse(const utility::dynamic_string& assembly) -> utility::result<void> {
		m_lexer.set_text(assembly);
		m_lexer.get_next_token();

		while(m_lexer.current != TOK_EOF) {
			TRY(parse_instruction());
		}

		return SUCCESS;
	}

	auto assembler_parser::get_bytes() const -> const utility::dynamic_array<u8>& {
		return m_assembler.get_bytes();
	}

	void assembler_parser::clear() {
		m_assembly.clear();
		m_assembler.clear();
	}

	auto assembler_parser::parse_instruction() -> utility::result<void> {
		// instruction mnemonic
		utility::dynamic_string instruction_identifier;

		// PARSER_VERIFY(KW_IDENTIFIER);
		instruction_identifier = utility::dynamic_string(m_lexer.current_string);

		first_instruction = find_instruction_by_name(instruction_identifier.get_data());

		if(first_instruction == utility::limits<u32>::max()) {
			// instruction doesn't exist
			return utility::error("unknown instruction specified");
		}

		// ensure our destination is clean
		utility::memset(operands, 0, sizeof(operand) * 4);
		operand_i = 0;

		// operands
		while(m_lexer.get_next_token() != TOK_EOF) {
			switch (m_lexer.current) {
				case TOK_DOLLARSIGN:         TRY(parse_rip_relative_rel()); break;
				case TOK_MINUS:              TRY(parse_number_negative()); break;
				case TOK_CR0 ... TOK_R15B:   TRY(parse_register()); break;
				case TOK_LBRACKET:           TRY(parse_bracket()); break; 
				case TOK_BYTE ... TOK_TWORD: TRY(parse_memory()); break;
				case TOK_NUMBER:             parse_number(); break;	
				default: return utility::error("unexpected token received as instruction operand");
			};

			// operands are separated by commas
			if(m_lexer.current != TOK_COMMA) {
				break;
			}
		}

		// locate the specific variant (dumb linear search in our specific group)
		u32 instruction_i = first_instruction;
		constexpr u32 db_size = sizeof(instruction_db) / sizeof(instruction);

		while(instruction_i < db_size && utility::compare_strings(instruction_db[instruction_i].name, instruction_db[first_instruction].name) == 0) {
			if(detail::is_operand_match(instruction_i, operands, m_broadcast_n)) {
				for(u8 j = 0; j < operand_i; ++j) {
					operands[j].type = instruction_db[instruction_i].operands[j]; // HACK: just modify all instructions to the actual type (relocations, mem256)

					if(is_operand_rel(instruction_db[instruction_i].operands[j])) {
						rel r = rel(static_cast<i32>(operands[j].immediate.value));
						operands[j].relocation = r; 
					}
				}

				m_assembler.emit_instruction(instruction_i, operands);
				return SUCCESS;
			}

			instruction_i++;
		}

		// invalid instruction and operand combination
		return utility::error("invalid operand combination for the specified instruction");
	}

	auto assembler_parser::parse_register() -> utility::result<void> {		
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

	void assembler_parser::parse_number() {
		operands[operand_i++] = operand(m_lexer.current_immediate); 
		m_lexer.get_next_token();
	}

	auto assembler_parser::parse_rip_relative_rel() -> utility::result<void> {
		if(m_lexer.get_next_token() != TOK_PLUS) {
			return utility::error("unexpected token received in rip-relative address");
		}

		operand rip_rel; 

		if(m_lexer.get_next_token() == TOK_MINUS) {
			// negative relocations are always rel32 (without being rip-relative)
			rip_rel.type = OP_REL32;

			m_lexer.get_next_token();
			EXPECT_TOKEN(TOK_NUMBER);

			rip_rel.immediate = imm(-1 * static_cast<i64>(m_lexer.current_immediate.value));
		} 
		else {
			EXPECT_TOKEN(TOK_NUMBER);

			// select the actual data type
			switch(m_lexer.current_immediate.min_bits) {
				case 8:  rip_rel.type = OP_REL8_RIP;  break;
				case 16: rip_rel.type = OP_REL16_RIP; break;
				case 32: rip_rel.type = OP_REL32_RIP; break;
				default: return utility::error("invalid rip-relative address width");
			}

			rip_rel.immediate = m_lexer.current_immediate;
		}

		operands[operand_i++] = rip_rel;
		m_lexer.get_next_token();

		return SUCCESS;
	}

	auto assembler_parser::parse_number_negative() -> utility::result<void> {
		m_lexer.get_next_token();
		EXPECT_TOKEN(TOK_NUMBER);

		operands[operand_i++] = operand(imm(-static_cast<i64>(m_lexer.current_immediate.value)));
		m_lexer.get_next_token();

		return SUCCESS;
	}

	auto assembler_parser::parse_memory() -> utility::result<void> {
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

	auto assembler_parser::parse_bracket() -> utility::result<void> {
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

				// TODO: move this over to the memory parser
				if(memory.memory.has_base) {
					switch(memory.memory.base.type) {
						case REG_XMM: memory.type = OP_VM32X; break;
						case REG_YMM: memory.type = OP_VM32Y; break;
						case REG_ZMM: memory.type = OP_VM32Z; break;
						default: break;
					}
				}
				
				if(memory.memory.has_index) {
					switch(memory.memory.index.type) {
						case REG_XMM: memory.type = OP_VM32X; break;
						case REG_YMM: memory.type = OP_VM32Y; break;
						case REG_ZMM: memory.type = OP_VM32Z; break;
						default: break;
					}
				}
			
				if(memory.memory.has_index && memory.memory.has_base) {
					if(memory.memory.index.type != memory.memory.base.type) {
						if(!is_gp_reg(memory.memory.index) && !is_gp_reg(memory.memory.base)) {
							return utility::error("invalid combination of register types in memory");
						}
					}
				}

				if(m_lexer.get_next_token() == TOK_LBRACE) {
					m_lexer.force_keyword = true;
					m_lexer.get_next_token();

					// masked memory operand
					if(is_token_k(m_lexer.current)) {
						memory.mm.k = m_lexer.current - TOK_K1 + 1;

						switch(memory.type) {
							case OP_VM32X: memory.type = OP_VM32X_K; break;
							case OP_VM32Y: memory.type = OP_VM32Y_K; break;
							case OP_VM32Z: memory.type = OP_VM32Z_K; break;
							case OP_M16:   memory.type = OP_M16_K; break;
							case OP_M32:   memory.type = OP_M32_K; break;
							case OP_M64:   memory.type = OP_M64_K; break;
							case OP_M128:  memory.type = OP_M128_K; break;
							case OP_M256:  memory.type = OP_M256_K; break;
							case OP_M512:  memory.type = OP_M512_K; break;
							default: ASSERT(false, "unhandled memory for masked memory operand\n");
						}

						m_lexer.get_next_token();
						EXPECT_TOKEN(TOK_RBRACE);
						m_lexer.get_next_token();

						operands[operand_i++] = memory;
					}
					// broadcast
					else {
						switch(m_lexer.current) {
							case TOK_1TO2:  m_broadcast_n = 2; break;
							case TOK_1TO4:  m_broadcast_n = 4; break;
							case TOK_1TO8:  m_broadcast_n = 8; break;
							case TOK_1TO16: m_broadcast_n = 16; break;
							case TOK_1TO32: m_broadcast_n = 32; break;
							default: return utility::error("invalid broadcast operand specified");
						}

						m_lexer.get_next_token();
						EXPECT_TOKEN(TOK_RBRACE);
						m_lexer.get_next_token();

						constexpr u32 db_size = sizeof(instruction_db) / sizeof(instruction);
						u32 index = first_instruction;
						bool met_broadcast = false;

						// find the bn from the current instruction
						while(index < db_size && utility::compare_strings(instruction_db[first_instruction].name, instruction_db[index].name) == 0) {
							if(detail::is_operand_match_partial(index, operands, operand_i)) {
								const instruction& current = instruction_db[index];

								if(current.has_broadcast_operand()) {
									operand_type ty = current.operands[current.get_broadcast_operand()];
									met_broadcast = true;

									if(broadcast_to_bits(ty) * m_broadcast_n == inst_size_to_int(current.op_size)) {
										operand op;
										op.type = ty;
										operands[operand_i++] = op;

										return SUCCESS;
									}
								}
							}

							index++;
						}

						if(met_broadcast) {
							return utility::error("mismatch in the number of broadcasting elements");
						}

						return utility::error("invalid broadcast operand specified");
					}
				}
				else {
					operands[operand_i++] = memory;
				}

				break;
			}
		}

		return SUCCESS;
	}

	auto assembler_parser::parse_mask_register(operand& op) -> utility::result<bool> {
		if(m_lexer.get_next_token() == TOK_LBRACE) {
			m_lexer.get_next_token();
			
			char c = m_lexer.current_string[0];

			switch(c) {
				case 'k': {
					if(m_lexer.current_string.get_size() != 2) {
						return utility::error("invalid mask register specified");
					}

					char* end;
					op.mr.k = static_cast<u8>(strtoul(m_lexer.current_string.get_data() + 1, &end, 10));

					if(op.mr.k >= 8) {
						utility::error("invalid mask register specified");
					}

					// operand {kn}
					switch(op.type) {
						case OP_XMM: op.type = OP_XMM_K; break;
						case OP_YMM: op.type = OP_YMM_K; break;
						case OP_ZMM: op.type = OP_ZMM_K; break;
						case OP_K:   op.type = OP_K_K;   break;
						default: return utility::error("invalid register for mask operation"); 
					}

					break;
				}
				case 'z': {
					if(m_lexer.current_string.get_size() != 2) {
						utility::error("invalid mask register specified");
					}

					// operand {kn} {z}
					switch(op.type) {
						case OP_XMM_K: op.type = OP_XMM_KZ; break;
						case OP_YMM_K: op.type = OP_YMM_KZ; break;
						case OP_ZMM_K: op.type = OP_ZMM_KZ; break;
						default: return utility::error("invalid register for mask operation"); 
					}

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

	auto assembler_parser::parse_memory(mem& memory) -> utility::result<void> {
		reg current_reg = reg::create_invalid();
		imm current_imm;

		bool displacement_set = false;
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
						if(memory.has_index) {
							return utility::error("memory index cannot be specified twice");
						}

						memory.index = token_to_register(m_lexer.current);
						memory.has_index = true;

						TRY(memory.s, detail::imm_to_scale(current_imm));

						scale_mode = false;
						imm_set = false;
					}
					else {
						current_reg = token_to_register(m_lexer.current);
					}

					break;
				}
				// rel $
				case TOK_REL: {
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
							if(memory.has_index) {
								return utility::error("memory index cannot be specified twice");
							}

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
						if(displacement_set) {
							return utility::error("memory displacement cannot be specified twice");
						}

						memory.displacement = current_imm;
						displacement_set = true;
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
						if(memory.has_index) {
							return utility::error("memory index cannot be specified twice");
						}

						memory.index = current_reg;
						memory.has_index = true;

						TRY(memory.s, detail::imm_to_scale(m_lexer.current_immediate));

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
							if(memory.has_index) {
								return utility::error("memory index cannot be specified twice (implicit index)");
							}

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
						if(displacement_set) {
							return utility::error("memory displacement cannot be specified twice");
						}
						
						memory.displacement = current_imm;
						displacement_set = true;
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

