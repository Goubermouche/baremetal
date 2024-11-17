#include "frontend.h"
#include "assembler/backend.h"

#include <utility/system/file.h>

#include "assembler/passes/cfg_analyze_pass.h"
#include "assembler/passes/inst_size_minimize_pass.h"
#include "assembler/passes/symbolic_minimize_pass.h"

#include "assembler/passes/emit/emit_binary_pass.h"
#include "assembler/passes/emit/emit_cfg_pass.h"

#define EXPECT_TOKEN(expected)                                    \
  do {                                                            \
    if(m_lexer.current != expected) {                             \
      return utility::error("[PASS 1]unexpected token received"); \
		}                                                             \
  }                                                               \
  while(false)

namespace baremetal::assembler {
	namespace detail {
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

		auto imm_to_scale(const imm& i) -> utility::result<scale> {
			switch(i.value) {
				case 1: return SCALE_1;
				case 2: return SCALE_2;
				case 4: return SCALE_4;
				case 8: return SCALE_8;
				default: return utility::error("invalid memory scale");
			}
		}
		
		auto is_operand_match(operand_type a, operand b) -> bool {
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
			for(u8 i = 0; i < count; ++i) {
				const operand_type left = inst.operands[i];
				const operand_type right = operands[i].type;

				if(
					!(is_operand_match(left, operands[i])) &&
					!(is_operand_imm(left) && is_operand_imm(right)) &&
					!(is_operand_moff(left) && is_operand_moff(right)) &&
					!(is_operand_masked_mem(left) && is_operand_masked_mem(right)) &&
					!(is_operand_rel(left) && is_operand_imm(right)) &&
					!(is_operand_imm(left) && operands[i].unknown) &&
					!(is_operand_rel(left) && operands[i].unknown)
				) {
					return false;
				}

				if(is_operand_reg(right) && operands[i].r > 15 && !inst.is_evex()) {
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
	} // namespace detail

	frontend::frontend() : m_module(&m_context) {}

	auto frontend::assemble(const utility::dynamic_string& source) -> utility::result<utility::dynamic_array<u8>> {
		m_lexer.set_text(source);
		TRY(parse());

		// m_module.print_section_info();

		// apply optimizations
		pass::cfg_analyze(m_module);
		pass::inst_size_minimize(m_module);
		pass::symbolic_minimize(m_module);

		// emission
		// auto graph  = pass::emit_control_flow_graph(m_module);
		// utility::file::write("./cfg2.dot", graph);

		return pass::emit_binary(m_module); 
	}

	auto frontend::parse() -> utility::result<void> {
		TRY(m_lexer.get_next_token());

		while(m_lexer.current != TOK_EOF) {
			m_current_identifier = nullptr;

			switch(m_lexer.current) {
				case TOK_NEWLINE:           TRY(m_lexer.get_next_token()); break;
				case TOK_RESB ... TOK_RESQ: TRY(parse_reserve_memory()); break;
				case TOK_IDENTIFIER:        TRY(parse_identifier()); break;
				case TOK_SECTION:           TRY(parse_section()); break;
				case TOK_TIMES:             TRY(parse_times()); break;
				case TOK_BITS:              TRY(parse_bits()); break;
				default: ASSERT(false, "unexpected top level token: {}\n", token_to_string(m_lexer.current)); 
			}	
		}

		m_module.begin_block(BB_INSTRUCTION, nullptr);
		return SUCCESS;
	}

	auto frontend::parse_reserve_memory() -> utility::result<void> {
		u8 bytes = 0;

		switch(m_lexer.current) {
			case TOK_RESB: bytes = 1; break;
			case TOK_RESW: bytes = 2; break;
			case TOK_RESD: bytes = 4; break;
			case TOK_RESQ: bytes = 8; break;
			default: ASSERT(false, "unreachable\n");
		}

		SUPPRESS_C4100(bytes);

		// ignored for now, this only appears in object formats
		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_NUMBER);
		TRY(m_lexer.get_next_token());

		//if(*m_sections[m_section_index].name != ".bss") {
		//	for(u64 i = 0; i < m_lexer.current_immediate.value; ++i) {
		//		m_current_resolved.push_back(0);
		//	}
		//}

		return SUCCESS;
	}

	auto frontend::parse_define_memory() -> utility::result<void> {
		if(m_current_identifier) {
			m_module.add_symbol(m_current_identifier);
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
		utility::dynamic_array<u8> data;

		while(m_lexer.current != TOK_EOF) {
			switch(m_lexer.current) {
				case TOK_CHAR: 
				case TOK_STRING: {
					for(const char c : m_lexer.current_string) {
						data.push_back(c);
					}

					// apend missing bytes, so that we're aligned with our data type
					const u64 offset = m_lexer.current_string.get_size();
					const u64 alignment_offset = utility::align(offset, bytes) - offset; 

					for(u64 i = 0; i < alignment_offset; ++i) {
						data.push_back(0);
					}

					break;
				}
				case TOK_MINUS: ASSERT(false, "TODO\n"); break;
				case TOK_NUMBER: {
					if(m_lexer.current_immediate.min_bits / 8 > bytes) {
						utility::console::print("warning: byte data exceeds bounds\n");
					}

					u64 value = m_lexer.current_immediate.value;

					for(u8 i = 0; i < bytes; ++i) {
			      u8 byte = static_cast<u8>(value & 0xFF);
						data.push_back(byte);
			      value >>= 8;
			    }

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

		m_module.add_data_block(data);
		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}
	
	auto frontend::parse_instruction() -> utility::result<void> {
		u32 start = m_instruction_i = backend::get_instruction_by_name(m_current_identifier->get_data());
		utility::string_view* instruction_name = m_current_identifier;

		if(m_instruction_i == utility::limits<u32>::max()) {
			ASSERT(false, "[PASS 1]: unknown instruction '{}' specified\n", *m_current_identifier);
		}

		// ensure our destination is clean
		utility::memset(m_operands, 0, sizeof(operand) * 4);

		m_unresolved_index = utility::limits<u8>::max();
		m_broadcast_n = 0;
		m_operand_i = 0;

		// parse instruction operands
		while(m_lexer.current != TOK_EOF && m_lexer.current != TOK_NEWLINE) {
			switch(m_lexer.current) {
				case TOK_LBRACKET:           TRY(parse_memory_operand(DT_NONE)); break; 
				case TOK_IDENTIFIER:         TRY(parse_identifier_operand()); break;
				case TOK_MINUS:              TRY(parse_immediate_operand()); break;
				case TOK_NUMBER:             TRY(parse_immediate_operand()); break;
				case TOK_CR0 ... TOK_R15B:   TRY(parse_register_operand()); break;
				case TOK_DOLLARSIGN:         TRY(parse_rip_rel_operand()); break;
				case TOK_BYTE ... TOK_TWORD: TRY(parse_type_operand()); break;
				case TOK_CHAR:               TRY(parse_operand_char()); break;
				default: ASSERT(false, "unexpected operand token: {}\n", token_to_string(m_lexer.current)); 
			}

			if(m_lexer.current != TOK_COMMA) {
				break;
			}

			TRY(m_lexer.get_next_token());
		}

		// locate the specific variant (dumb linear search in our specific group)
		while(m_instruction_i < INSTRUCTION_DB_SIZE) {
			const instruction& current = instruction_db[m_instruction_i]; 

			// verify that the instruction names are the same and that we've not left our instruction group
			if(*instruction_name != current.name) {
				break;
			}

			// verify that the current instruction matches the provided operands
			if(detail::is_operand_match(current, m_operands, m_broadcast_n, m_operand_i)) {
				assemble_instruction(&current);
				return SUCCESS;
			}

			m_instruction_i++;
		}

		utility::console::print_err("'{}': ", instruction_db[start].name);
		for(u8 i = 0; i < m_operand_i; ++i) {
			utility::console::print_err("{} ", operand_type_to_string(m_operands[i].type));
		}

		utility::console::print_err("\n");

		return utility::error("invalid operand combination for instruction");
	}

	void frontend::assemble_instruction(const instruction* inst) {
		// operands match, but, in some cases we need to retype some of them to the actual type, ie. 
		// immediates can actually be relocations
		for(u8 j = 0; j < m_operand_i; ++j) {
			if(j == m_unresolved_index) {
				continue;
			}

			m_operands[j].type = inst->operands[j];

			if(is_operand_rel(inst->operands[j])) {
				u8 size = backend::emit_instruction(m_instruction_i, m_operands, false).size;
				m_operands[j].immediate = static_cast<i32>(m_operands[j].immediate.value) - size;
			}
		}

		//if(m_symbolic_operand) {
		//	if(is_operand_mem(m_operands[m_unresolved_index].type) && m_fixup == FIXUP_DISPLACEMENT) {
		//		// force the longest possible encoding
		//		m_operands[m_unresolved_index].memory.displacement = 1;
		//		m_operands[m_unresolved_index].memory.displacement.min_bits = 32;
		//	}
		//}

		// HACK: assemble the instruction and use that as the length
		// TODO: cleanup
		auto code = backend::emit_instruction(m_instruction_i, m_operands, true);

		u8 size = code.size;

		// NOTE: unoptimized instruction handle, fix this	
		m_module.add_instruction(m_operands, m_instruction_i, size);
	
		if(is_jump_or_branch_inst(m_instruction_i)) {
			m_module.begin_block(BB_BRANCH, nullptr);
		}
	}

	auto frontend::parse_moff_operand(data_type type) -> utility::result<void> {
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

	auto frontend::parse_broadcast_operand(mask_type mask) -> utility::result<void> {
		m_broadcast_n = mask_to_broadcast_n(mask);
		
		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_RBRACE);
		TRY(m_lexer.get_next_token());

		u32 index = m_instruction_i;
		bool met_broadcast = false;

		// find the bn from the current instruction
		while(index < INSTRUCTION_DB_SIZE) {
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

	auto frontend::parse_memory_operand(data_type type) -> utility::result<void> {
		EXPECT_TOKEN(TOK_LBRACKET);
		operand op = {};

		switch(type) {
			case DT_BYTE:  op.type = OP_M8;   break;
			case DT_WORD : op.type = OP_M16;  break;
			case DT_DWORD: op.type = OP_M32;  break;
			case DT_QWORD: op.type = OP_M64;  break;
			case DT_TWORD: op.type = OP_M80;  break;
			case DT_NONE:  op.type = OP_M128; break; // M128 currently works as an infer keyword
		}
	
		TRY(m_lexer.get_next_token());

		// we can potentially have types in here, which means we're handling a moff
		switch(m_lexer.current) {
			case TOK_BYTE ... TOK_TWORD: return parse_moff_operand(type);
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
			return parse_broadcast_operand(mask);
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

	auto frontend::parse_identifier_operand() -> utility::result<void> {
		m_unresolved_index = m_operand_i;
		m_operands[m_operand_i++] = operand(m_context.strings.add(m_lexer.current_string)); 
		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto frontend::parse_immediate_operand() -> utility::result<void> {
		if(m_lexer.current == TOK_MINUS) {
			TRY(m_lexer.get_next_token());
			EXPECT_TOKEN(TOK_NUMBER);
			m_operands[m_operand_i++] = operand(imm(-static_cast<i64>(m_lexer.current_immediate.value))); 
		}
		else {
			EXPECT_TOKEN(TOK_NUMBER);
			m_operands[m_operand_i++] = operand(m_lexer.current_immediate); 
		}

		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto frontend::parse_register_operand() -> utility::result<void> {
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

	auto frontend::parse_type_operand() -> utility::result<void> {
		// parse an operand which begins with a type keyword 
		data_type type = token_to_data_type(m_lexer.current);

		TRY(m_lexer.get_next_token());

		switch(m_lexer.current) {
			case TOK_LBRACKET: parse_memory_operand(type); break;
			default: return utility::error("unexpected token following type");
		}

		return SUCCESS;
	}

	auto frontend::parse_operand_char() -> utility::result<void> {
		EXPECT_TOKEN(TOK_CHAR);
		m_operands[m_operand_i++] = imm(static_cast<i32>(m_lexer.current_string[0]));
		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto frontend::parse_rip_rel_operand() -> utility::result<void> {
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

	auto frontend::parse_identifier() -> utility::result<void> {
		EXPECT_TOKEN(TOK_IDENTIFIER);
		m_current_identifier = m_context.strings.add(m_lexer.current_string);

		TRY(m_lexer.get_next_token());

		// utility::console::print("{}  {}\n", *m_current_identifier, token_to_string(m_current_token.type));
		switch(m_lexer.current) {
			case TOK_DB ... TOK_DQ: return parse_define_memory();
			case TOK_COLON:         return parse_label();
			default:                return parse_instruction();
		}

		return SUCCESS;
	}
		
	auto frontend::parse_section() -> utility::result<void> {
		EXPECT_TOKEN(TOK_SECTION);

		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_IDENTIFIER);
		ASSERT(m_lexer.current_string[0] == '.', "first char of a section should be a '.'\n");

		m_module.set_section(m_context.strings.add(m_lexer.current_string));

		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto frontend::parse_label() -> utility::result<void> {
		EXPECT_TOKEN(TOK_COLON);

		m_module.begin_block(BB_INSTRUCTION, nullptr);
		m_module.add_symbol(m_current_identifier);
		m_module.begin_block(BB_LABEL, m_current_identifier);
		TRY(m_lexer.get_next_token());

		return SUCCESS;
	}
	
	auto frontend::parse_times() -> utility::result<void> {
		EXPECT_TOKEN(TOK_TIMES);
		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_NUMBER);
		u64 times = m_lexer.current_immediate.value;
		auto safepoint = m_lexer.create_safepoint();

		for(u64 i = 0; i < times; ++i) {
			m_lexer.restore_safepoint(safepoint);
			TRY(m_lexer.get_next_token());

			switch(m_lexer.current) {
				case TOK_IDENTIFIER: {
					m_current_identifier = m_context.strings.add(m_lexer.current_string);
					TRY(m_lexer.get_next_token());
					TRY(parse_instruction());
					break; 
				}
				case TOK_DB ... TOK_DQ: TRY(parse_define_memory()); break;
				default: ASSERT(false, "unexpected times token: {}\n", token_to_string(m_lexer.current)); 
			}
			
			// TODO: traverse to the end of our current line and verify there isn't anything else here
		}

		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto frontend::parse_bits() -> utility::result<void> {
		EXPECT_TOKEN(TOK_BITS);
		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_NUMBER);
		TRY(m_lexer.get_next_token());
		return SUCCESS;
	}

	auto frontend::parse_memory(operand& op) -> utility::result<void> {
		reg current_reg = reg::create_invalid();
		mem& memory = op.memory;
		imm current_imm;

		memory.displacement = 0;

		bool displacement_set = false;
		bool scale_mode = false;
		bool imm_set = false;
		bool negate = false;

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
					negate = true;
					TRY(m_lexer.get_next_token());
					EXPECT_TOKEN(TOK_NUMBER);
					[[fallthrough]];
				}
				case TOK_NUMBER: {
					if(scale_mode && current_reg.is_valid()) {
						// reg * scale
						if(memory.has_index) {
							return utility::error("memory index cannot be specified twice");
						}

						if(negate) {
							return utility::error("memory index cannot be negative");
						}

						memory.index = current_reg;
						memory.has_index = true;

						TRY(memory.s, detail::imm_to_scale(m_lexer.current_immediate));

						scale_mode = false;
						current_reg = reg::create_invalid();
					}
					else{
						// immediate
						if(negate) {
							current_imm = imm(-1 * static_cast<i64>(m_lexer.current_immediate.value));
						}
						else {
							current_imm = m_lexer.current_immediate;
						}

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
					
					if(imm_set) {
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
				case TOK_IDENTIFIER: {
					m_unresolved_index = m_operand_i;
					op.symbol = m_context.strings.add(m_lexer.current_string);
					op.unknown = true;
					memory.displacement.min_bits = 32;
					displacement_set = true;

					break;
				}
				default: {
					return utility::error("unexpected token received in memory operand");
				}
			}

			TRY(m_lexer.get_next_token());
		}
	}

	auto frontend::parse_mask_or_broadcast() -> utility::result<mask_type> {
		mask_type result = MASK_NONE;

		TRY(m_lexer.get_next_token());

		if(m_lexer.current != TOK_LBRACE) {
			return result; // no mask
		}

		TRY(m_lexer.get_next_token());

		// broadcast
		switch(m_lexer.current) {
			case TOK_1TO2:  return MASK_BROADCAST_1TO2;
			case TOK_1TO4:  return MASK_BROADCAST_1TO4;
			case TOK_1TO8:  return MASK_BROADCAST_1TO8;
			case TOK_1TO16: return MASK_BROADCAST_1TO16;
			case TOK_1TO32: return MASK_BROADCAST_1TO32;
			default: break; 
		}

		u8 k = 0;

		// k
		switch(m_lexer.current) {
			case TOK_K1: k = 1; break;
			case TOK_K2: k = 2; break;
			case TOK_K3: k = 3; break;
			case TOK_K4: k = 4; break;
			case TOK_K5: k = 5; break;
			case TOK_K6: k = 6; break;
			case TOK_K7: k = 7; break;
			default: return utility::error("ill-formed mask register, expected 'k0-k7'"); 
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
		EXPECT_TOKEN(TOK_Z);
		result = static_cast<mask_type>(result + 8);
		TRY(m_lexer.get_next_token());
		EXPECT_TOKEN(TOK_RBRACE);
		
		TRY(m_lexer.get_next_token());
		return result;
	}
} // namespace baremetal::assembler

