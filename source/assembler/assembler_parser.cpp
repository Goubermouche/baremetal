#include "assembler_parser.h"
#include "utility/result.h"

#include <utility/algorithms/sort.h>

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
				case OP_FS:      return b.type == OP_SREG && b.r == fs;
				case OP_GS:      return b.type == OP_SREG && b.r == gs;
				case OP_AL:      return b.type == OP_R8 && b.r == al;
				case OP_AX:      return b.type == OP_R16 && b.r == ax;
				case OP_EAX:     return b.type == OP_R32 && b.r == eax;
				case OP_RAX:     return b.type == OP_R64 && b.r == rax;
				case OP_CL:      return b.type == OP_R8 && b.r == cl;
				case OP_DX:      return b.type == OP_R16 && b.r == dx;
				case OP_ECX:     return b.type == OP_R32 && b.r == ecx;
				case OP_RCX:     return b.type == OP_R64 && b.r == rcx;
				case OP_ST0:     return b.type == OP_ST && b.r == st0;
				case OP_MEM:     return b.type == OP_M128;
				case OP_VM64X:   return b.type == OP_VM32X || a == b.type;
				case OP_VM64Y:   return b.type == OP_VM32Y || a == b.type;
				case OP_VM64Z:   return b.type == OP_VM32Z || a == b.type;
				case OP_VM64X_K: return b.type == OP_VM32X_K || a == b.type;
				case OP_VM64Y_K: return b.type == OP_VM32Y_K || a == b.type;
				case OP_VM64Z_K: return b.type == OP_VM32Z_K || a == b.type;
				case OP_M256:    return b.type == OP_M128;
				case OP_M512:    return b.type == OP_M128;
				case OP_TMEM:    return b.type == OP_M128;
				default:         return a == b.type;
			}
		}
	
		auto is_operand_match(const instruction& inst, operand* operands, u8 broadcast_n, u8 count) -> bool {
			// TODO: this entire thing needs to go
			for(u8 i = 0; i < count; ++i) {
				if(
					!(inst_match(inst.operands[i], operands[i])) &&
					!(is_operand_imm(inst.operands[i]) && is_operand_imm(operands[i].type)) &&
					!(is_operand_moff(inst.operands[i]) && is_operand_moff(operands[i].type)) &&
					!(is_operand_masked_mem(inst.operands[i]) && is_operand_masked_mem(operands[i].type)) &&
					!(is_operand_rel(inst.operands[i]) && is_operand_imm(operands[i].type)) &&
					!(is_operand_imm(inst.operands[i]) && operands[i].type == OP_REL_UNKNOWN) &&
					!(is_operand_rip_rel(inst.operands[i]) && operands[i].type == OP_REL_UNKNOWN)
				) {
					return false;
				}

				if(is_operand_reg(operands[i].type) && operands[i].r > 15 && !inst.is_evex()) {
					return false;
				}

				if(
					inst.has_broadcast_operand() &&
					broadcast_to_bits(inst.operands[inst.get_broadcast_operand()]) * broadcast_n != inst_size_to_int(inst.op_size)
				) {
					return false;
				}
			}
	
			return true;
		}

		auto mask_operand(operand_type op, mask_type mask) -> utility::result<operand_type> {
			ASSERT(is_mask_broadcast(mask) == false, "cannot mask operand using a broadcast\n");

			if(mask > 8) {
				// {k} {z}
				switch(op) {
					case OP_XMM: return OP_XMM_KZ;
					case OP_YMM: return OP_YMM_KZ;
					case OP_ZMM: return OP_ZMM_KZ;
					default:     return utility::error("operand cannot have a zeroing mask");
				}
			}
			else {
				// {k}
				switch(op) {
					case OP_VM32X: return OP_VM32X_K;
					case OP_VM32Y: return OP_VM32Y_K;
					case OP_VM32Z: return OP_VM32Z_K;
					case OP_M16:   return OP_M16_K;
					case OP_M32:   return OP_M32_K;
					case OP_M64:   return OP_M64_K;
					case OP_M128:  return OP_M128_K; 
					case OP_M256:  return OP_M256_K; 
					case OP_M512:  return OP_M512_K;
					case OP_XMM:   return OP_XMM_K;
					case OP_YMM:   return OP_YMM_K;
					case OP_ZMM:   return OP_ZMM_K;
					case OP_K:     return OP_K_K;  
					default:       return utility::error("operand cannot have a mask");
				}	
			}

			return OP_NONE; // unreachable
		}
	} // namespace detail

	assembler_parser::assembler_parser(assembler_context* context) : m_context(context), m_backend(context) {}

	auto assembler_parser::parse(const utility::dynamic_string& assembly) -> utility::result<void> {
		m_lexer.set_text(assembly);
		TRY(m_lexer.get_next_token());

		while(m_lexer.current != TOK_EOF) {
			switch(m_lexer.current) {
				case TOK_NEWLINE:    m_lexer.get_next_token(); break;
				case TOK_IDENTIFIER: TRY(parse_identifier()); break;
				case TOK_SECTION:    TRY(parse_section()); break;
				case TOK_TIMES:      TRY(parse_times()); break;
				case TOK_BITS:       TRY(parse_bits()); break;
				default: return utility::error("unexpected top-level token received");
			}
		}

		// m_interner.print();
		return SUCCESS;
	}

	auto assembler_parser::get_bytes() const -> utility::dynamic_array<u8> {
		return m_backend.get_bytes();
	}

	void assembler_parser::clear() {
		m_context->clear();
		m_backend.clear();
	}

	auto assembler_parser::parse_identifier() -> utility::result<void> {
		EXPECT_TOKEN(TOK_IDENTIFIER);

		m_instruction_i = find_instruction_by_name(m_lexer.current_string.get_data());

		if(m_instruction_i != utility::limits<u32>::max()) {
			return parse_instruction();
		}

		m_current_identifier = m_context->strings.add(m_lexer.current_string);

		// TODO: check for multiple symbols
		
		TRY(m_lexer.get_next_token());

		// other identifiers
		switch(m_lexer.current) {
			case TOK_RESB ... TOK_RESQ: return parse_reserve_memory(m_current_identifier); 
			case TOK_DB ... TOK_DQ:     return parse_define_memory(m_current_identifier); 
			case TOK_COLON:             return parse_label(); 
			case TOK_EOF:               return SUCCESS;
			default:                    return utility::error("unexpected token received after an identifier");
		}
	}

	auto assembler_parser::parse_instruction() -> utility::result<void> {
		// ensure our destination is clean
		utility::memset(m_operands, 0, sizeof(operand) * 4);
		m_relocated_operand = false;
		m_operand_i = 0;

		TRY(m_lexer.get_next_token());

		// parse individual operands
		while(m_lexer.current != TOK_EOF && m_lexer.current != TOK_NEWLINE) {
			switch(m_lexer.current) {
				case TOK_IDENTIFIER:         TRY(parse_identifier_operand()); break;
				case TOK_DOLLARSIGN:         TRY(parse_rip_relative_rel()); break;
				case TOK_MINUS:              TRY(parse_number_negative()); break;
				case TOK_LBRACKET:           TRY(parse_memory(DT_NONE)); break; 
				case TOK_CR0 ... TOK_R15B:   TRY(parse_register()); break;
				case TOK_BYTE ... TOK_TWORD: TRY(parse_type()); break;
				case TOK_NUMBER:             parse_number(); break;	
				default: return utility::error("unexpected token received as instruction operand");
			};

			// operands are separated by commas
			if(m_lexer.current != TOK_COMMA) {
				break;
			}

			TRY(m_lexer.get_next_token());
		}

		u32 first_instruction = m_instruction_i; 

		if(m_relocated_operand) {
			utility::dynamic_array<const instruction*> legal_variants;
			u8 imm_index = 0;

			// locate the first immediate operand
			for(u8 i = 0; i < 4; ++i) {
				if(m_operands[i].type == OP_REL_UNKNOWN) {
					imm_index = i;
					break;
				}
			}

			while(m_instruction_i < instruction_db_size) {
				const instruction& current = instruction_db[m_instruction_i]; 

				// verify that the instruction names are the same and that we've not left our instruction group
				if(utility::compare_strings(instruction_db[first_instruction].name, current.name) != 0) {
					break;
				}

				// verify that the current instruction matches the provided operands
				if(detail::is_operand_match(current, m_operands, m_broadcast_n, m_operand_i)) {
					legal_variants.push_back(&current);
				}

				m_instruction_i++;
			}

			utility::stable_sort(legal_variants.begin(), legal_variants.end(), [=](auto a, auto b) {
				const u16 a_width = get_operand_bit_width(a->operands[imm_index]);
				const u16 b_width = get_operand_bit_width(b->operands[imm_index]);

				return a_width > b_width;
			});

			// TODO: we can probably get rid of this eventually
			// this either picks the largest non-rel variant, or the smallest rel variant
			const auto& temp = legal_variants[0];
			const instruction* inst = legal_variants[0];

			if(is_operand_rel(temp->operands[temp->operand_count - 1])) {
			    inst = legal_variants[legal_variants.get_size() - 1];
			}

			for(u8 j = 0; j < m_operand_i; ++j) {
				if(j == imm_index) {
					continue;
				}

				m_operands[j].type = inst->operands[j];

				if(is_operand_rel(inst->operands[j])) {
					rel r = rel(static_cast<i32>(m_operands[j].immediate.value));
					m_operands[j].relocation = r; 
				}
			}

			m_backend.emit_instruction_direct(inst, m_operands);
			return SUCCESS;
		}
		else {
			// locate the specific variant (dumb linear search in our specific group)
			while(m_instruction_i < instruction_db_size) {
				const instruction& current = instruction_db[m_instruction_i]; 

				// verify that the instruction names are the same and that we've not left our instruction group
				if(utility::compare_strings(instruction_db[first_instruction].name, current.name) != 0) {
					break;
				}

				// verify that the current instruction matches the provided operands
				if(detail::is_operand_match(current, m_operands, m_broadcast_n, m_operand_i)) {
					// operands match, but, in some cases we need to retype some of them to the actual type, ie. 
					// immediates can actually be relocations
					for(u8 j = 0; j < m_operand_i; ++j) {
						m_operands[j].type = current.operands[j];

						if(is_operand_rel(current.operands[j])) {
							rel r = rel(static_cast<i32>(m_operands[j].immediate.value));
							m_operands[j].relocation = r; 
						}
					}

					// emit the final instruction
					m_backend.emit_instruction(m_instruction_i, m_operands);
					return SUCCESS;
				}

				m_instruction_i++;
			}
		}

		// invalid instruction and operand combination
		return utility::error("invalid operand combination for the specified instruction");
	}

	auto assembler_parser::parse_label() -> utility::result<void> {
		EXPECT_TOKEN(TOK_COLON);
		m_backend.get_module().add_symbol(m_current_identifier, module::SYM_RELATIVE);
		TRY(m_lexer.get_next_token());
		return SUCCESS;	
	}

	auto assembler_parser::parse_times() -> utility::result<void> {
		EXPECT_TOKEN(TOK_TIMES);

		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_NUMBER);

		u64 times = m_lexer.current_immediate.value;
		auto safepoint = m_lexer.create_safepoint();

		for(u64 i = 0; i < times; ++i) {
			m_lexer.restore_safepoint(safepoint);

			TRY(m_lexer.get_next_token());

			switch(m_lexer.current) {
				case TOK_RESB ... TOK_RESQ: TRY(parse_reserve_memory(nullptr)); break;
				case TOK_DB ... TOK_DQ:     TRY(parse_define_memory(nullptr)); break;
				case TOK_IDENTIFIER: {
					m_instruction_i = find_instruction_by_name(m_lexer.current_string.get_data());

					if(m_instruction_i == utility::limits<u32>::max()) {
						return utility::error("expected instruction");
					}

					TRY(parse_instruction());
					break;
				}
				default: return utility::error("unexpected token received after times keyword");
			}
		}

		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto assembler_parser::parse_section() -> utility::result<void> {
		EXPECT_TOKEN(TOK_SECTION);

		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_DOT);

		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_IDENTIFIER);

		// NOTE: we don't care if a section is 'declared' multiple times
		m_backend.get_module().set_section(m_context->strings.add(m_lexer.current_string));

		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto assembler_parser::parse_reserve_memory(utility::string_view* symbol) -> utility::result<void> {
		if(symbol) {
			m_backend.get_module().add_symbol(symbol, module::SYM_GLOBAL);
		}

		// u8 bytes = 0;

		// switch(m_lexer.current) {
		// 	case TOK_RESB: bytes = 1; break;
		// 	case TOK_RESW: bytes = 2; break;
		// 	case TOK_RESD: bytes = 4; break;
		// 	case TOK_RESQ: bytes = 8; break;
		// 	default: ASSERT(false, "unreachable\n");
		// }

		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_NUMBER);

		// NOTE: do nothing for now, when we begin implementing some more complex formats we can focus on 
		// actually doing stuff with the .bss section
		// for(u64 i = 0; i < m_lexer.current_immediate.value; ++i) {
		// 	for(u8 j = 0; j < bytes; ++j) { 
		// 		m_assembler.push_byte(0);
		// 	}
		// }

		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto assembler_parser::parse_define_memory(utility::string_view* symbol) -> utility::result<void> {
		if(symbol) {
			m_backend.get_module().add_symbol(symbol, module::SYM_GLOBAL);
		}

		u8 bytes = 0;

		switch(m_lexer.current) {
			case TOK_DB: bytes = 1; break;
			case TOK_DW: bytes = 2; break;
			case TOK_DD: bytes = 4; break;
			case TOK_DQ: bytes = 8; break;
			default: ASSERT(false, "unreachable\n");
		}

		TRY(m_lexer.get_next_token());

		while(m_lexer.current != TOK_EOF) {
			switch(m_lexer.current) {
				case TOK_CHAR: 
				case TOK_STRING: {
					for(const char c : m_lexer.current_string) {
						m_backend.push_byte(c);
					}

					// apend missing bytes, so that we're aligned with our data type
					const u64 offset = m_lexer.current_string.get_size();
					const u64 alignment_offset = utility::align(offset, bytes) - offset; 

					for(u64 i = 0; i < alignment_offset; ++i) {
						m_backend.push_byte(0);
					}

					break;
				}
				case TOK_MINUS: ASSERT(false, "TODO\n"); break;
				case TOK_NUMBER: {
					if(m_lexer.current_immediate.min_bits / 8 > bytes) {
						utility::console::print("warning: byte data exceeds bounds\n");
					}

					m_backend.push_data(m_lexer.current_immediate.value, bytes);
					break;
				}
				default: return utility::error("unexpected token following memory definition");
			}
			
			TRY(m_lexer.get_next_token());

			// memory define operands should be comma separated
			if(m_lexer.current != TOK_COMMA) {
				break;
			}
			
			TRY(m_lexer.get_next_token());
		}

		// TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto assembler_parser::parse_bits() -> utility::result<void> {
		// parse 'bits 64' - we ignore it for now, but it's just nicer to be on par with NASM here
		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_NUMBER);

		if(m_lexer.current_immediate.value != 64) {
			return utility::error("unexpected bit count received");
		}

		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto assembler_parser::parse_type() -> utility::result<void> {
		// parse an operand which begins with a type keyword 
		data_type type = token_to_data_type(m_lexer.current);

		TRY(m_lexer.get_next_token());

		switch(m_lexer.current) {
			case TOK_LBRACKET: parse_memory(type); break;
			default: return utility::error("unexpected token following type");
		}

		return SUCCESS;
	}

	auto assembler_parser::parse_identifier_operand() -> utility::result<void> {
		utility::string_view* identifier = m_context->strings.add(m_lexer.current_string);	
		// const auto& module = m_backend.get_module();

		// .text section
		// if(module.get_current_section() == 0) {
		// 	const auto symbol = module.get_symbol(identifier);
		// 	operand op;

		// 	// symbol exists in .text section
		// 	if(symbol.type == module::SYM_RELATIVE) {
		// 		const i32 offset = static_cast<i32>(symbol.position) - static_cast<i32>(module.get_size_current_section());
		// 		op = imm(offset);

		// 		switch(m_lexer.current_immediate.min_bits) {
		// 			case 8:  op.type = OP_REL8_RIP;  break;
		// 			case 16: op.type = OP_REL16_RIP; break;
		// 			case 32: op.type = OP_REL32_RIP; break;
		// 			default: return utility::error("invalid rip-relative address width");
		// 		}
		// 		
		// 		m_operands[m_operand_i++] = op;
		// 		TRY(m_lexer.get_next_token());
		// 		return SUCCESS;
		// 	}
		// }

		m_operands[m_operand_i++] = operand(identifier);
		m_relocated_operand = true;
		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto assembler_parser::parse_moff(data_type type) -> utility::result<void> {
		if(type != DT_NONE) {
			return utility::error("duplicate data type specified in memory/moff operand");
		}

		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_NUMBER);

		m_operands[m_operand_i++] = operand(moff(m_lexer.current_immediate.value));

		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_RBRACKET);

		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto assembler_parser::parse_memory(data_type type) -> utility::result<void> {
		EXPECT_TOKEN(TOK_LBRACKET);
		operand op;

		switch(type) {
			case DT_NONE:  op.type = OP_M128; break; // M128 currently works as an infer keyword
			case DT_BYTE:  op.type = OP_M8;   break;
			case DT_WORD : op.type = OP_M16;  break;
			case DT_DWORD: op.type = OP_M32;  break;
			case DT_QWORD: op.type = OP_M64;  break;
			case DT_TWORD: op.type = OP_M80;  break;
		}
		
		TRY(m_lexer.get_next_token());

		// we can potentially have types in here, which means we're handling a moff
		switch(m_lexer.current) {
			case TOK_BYTE ... TOK_TWORD: return parse_moff(type);
			default: break;
		}

		TRY(parse_memory(op));

		EXPECT_TOKEN(TOK_RBRACKET);

		// trailing mask or broadcast
		TRY(mask_type mask, parse_mask_or_broadcast());

		if(mask == MASK_NONE) {
			m_operands[m_operand_i++] = op;
			return SUCCESS; // no mask or broadcast
		}

		if(is_mask_broadcast(mask)) {
			// broadcast
			return parse_broadcast(mask);
		}
		else {
			// mask
			if(mask > 8) {
				return utility::error("cannot encode memory operand with zeroing mask");
			}

			op.mm.k = mask_to_k(mask);
			TRY(op.type, detail::mask_operand(op.type, mask));

			m_operands[m_operand_i++] = op;
		}

		return SUCCESS;
	}

	auto assembler_parser::parse_broadcast(mask_type mask) -> utility::result<void> {
		m_broadcast_n = mask_to_broadcast_n(mask);
		
		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_RBRACE);
		TRY(m_lexer.get_next_token());

		u32 index = m_instruction_i;
		bool met_broadcast = false;

		// find the bn from the current instruction
		while(index < instruction_db_size) {
			const instruction& current = instruction_db[index];

			if(utility::compare_strings(instruction_db[m_instruction_i].name, current.name) != 0) {
				break;
			}

			if(detail::is_operand_match(current, m_operands, m_broadcast_n, m_operand_i)) {
				operand_type ty = current.operands[current.get_broadcast_operand()];
				met_broadcast = true;

				if(broadcast_to_bits(ty) * m_broadcast_n == inst_size_to_int(current.op_size)) {
					operand op;
					op.type = ty;
					m_operands[m_operand_i++] = op;

					return SUCCESS;
				}
			}

			index++;
		}

		if(met_broadcast) {
			return utility::error("mismatch in the number of broadcasting elements");
		}

		return utility::error("invalid broadcast operand specified");
	}

	auto assembler_parser::parse_mask_or_broadcast() -> utility::result<mask_type> {
		mask_type result = MASK_NONE;
		char* end;

		TRY(m_lexer.get_next_token());

		if(m_lexer.current != TOK_LBRACE) {
			return result; // no mask
		}

		// parse the first mask operand '{' { k0, k1, k2, k3, k4, k5, k6, k7 } '}' or
		// broadcast '{1to' { 2, 4, 8, 16, 32 } '}'
		m_lexer.force_keyword = true;

		TRY(m_lexer.get_next_token());

		switch(m_lexer.current) {
			case TOK_1TO2:  return MASK_BROADCAST_1TO2;
			case TOK_1TO4:  return MASK_BROADCAST_1TO4;
			case TOK_1TO8:  return MASK_BROADCAST_1TO8;
			case TOK_1TO16: return MASK_BROADCAST_1TO16;
			case TOK_1TO32: return MASK_BROADCAST_1TO32;
			default: break; 
		}

		if(m_lexer.current_string.get_size() != 2 || m_lexer.current_string[0] != 'k') {
			return utility::error("ill-formed mask register, expected 'k0-k7'");
		}

		u8 k = static_cast<u8>(strtoul(m_lexer.current_string.get_data() + 1, &end, 10));

		if(k > 7) {
			return utility::error("ill-formed mask register, expected 'k0-k7'");
		}

		result = static_cast<mask_type>(k + 1);

		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_RBRACE);

		TRY(m_lexer.get_next_token());

		if(m_lexer.current != TOK_LBRACE) {
			return result; // no zero mask
		}

		// parse the second mask operand '{z}'
		TRY(m_lexer.get_next_token());

		if(m_lexer.current_string.get_size() != 1 || m_lexer.current_string[0] != 'z') {
			return utility::error("ill-formed mask register, expected 'z'");
		}

		result = static_cast<mask_type>(result + 8);
		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_RBRACE);

		m_lexer.get_next_token(); // prime the next token
		return result;
	}

	auto assembler_parser::parse_register() -> utility::result<void> {		
		operand op = operand(token_to_register(m_lexer.current));
		TRY(mask_type mask, parse_mask_or_broadcast());

		if(mask == MASK_NONE) {
			m_operands[m_operand_i++] = op;
			return SUCCESS; // no mask
		}

		if(is_mask_broadcast(mask)) {
			return utility::error("unexpected broadcast on register operand, register operands are only eligible for masks");
		}

		op.mr.k = mask_to_k(mask);
		TRY(op.type, detail::mask_operand(op.type, mask));

		m_operands[m_operand_i++] = op;
		return SUCCESS;
	}

	auto assembler_parser::parse_number() -> utility::result<void> {
		m_operands[m_operand_i++] = operand(m_lexer.current_immediate); 
		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto assembler_parser::parse_rip_relative_rel() -> utility::result<void> {
		TRY(m_lexer.get_next_token());

		if(m_lexer.current != TOK_PLUS) {
			return utility::error("unexpected token received in rip-relative address");
		}

		operand rip_rel; 

		TRY(m_lexer.get_next_token());

		if(m_lexer.current == TOK_MINUS) {
			// negative relocations are always rel32 (without being rip-relative)
			rip_rel.type = OP_REL32;

			TRY(m_lexer.get_next_token());
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

		m_operands[m_operand_i++] = rip_rel;

		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto assembler_parser::parse_number_negative() -> utility::result<void> {
		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_NUMBER);

		m_operands[m_operand_i++] = operand(imm(-static_cast<i64>(m_lexer.current_immediate.value)));
		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto assembler_parser::parse_memory(operand& op) -> utility::result<void> {
		reg current_reg = reg::create_invalid();
		mem& memory = op.memory;
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
					TRY(m_lexer.get_next_token());
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

					if(memory.has_base) {
						switch(memory.base.type) {
							case REG_XMM: op.type = OP_VM32X; break;
							case REG_YMM: op.type = OP_VM32Y; break;
							case REG_ZMM: op.type = OP_VM32Z; break;
							default: break;
						}
					}
					
					if(memory.has_index) {
						switch(memory.index.type) {
							case REG_XMM: op.type = OP_VM32X; break;
							case REG_YMM: op.type = OP_VM32Y; break;
							case REG_ZMM: op.type = OP_VM32Z; break;
							default: break;
						}
					}
				
					if(memory.has_index && memory.has_base) {
						if(memory.index.type != memory.base.type) {
							if(!is_gp_reg(memory.index) && !is_gp_reg(memory.base)) {
								return utility::error("invalid combination of register types in memory");
							}
						}
					}

					return SUCCESS;
				}
				default: {
					return utility::error("unexpected token received in memory operand");
				}
			}

			TRY(m_lexer.get_next_token());
		}
	}
} // namespace baremetal

