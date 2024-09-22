#include "assembler.h"
#include "assembler/assembler_lexer.h"
#include "assembler/assembler_parser.h"

#include <utility/containers/dynamic_array.h>

#define EXPECT_TOKEN(expected)                                    \
  do {                                                            \
    if(m_current_token != expected) {                             \
      return utility::error("[PASS 1]unexpected token received"); \
		}                                                             \
  }                                                               \
  while(false)

namespace baremetal {
	auto fits_into_type(i64 value, operand_type type) -> bool {
		switch(type) {
			case OP_REL8:
			case OP_REL8_RIP:  return value >= utility::limits<i8>::min() && value <= utility::limits<i8>::max();
			case OP_REL16_RIP: return value >= utility::limits<i16>::min() && value <= utility::limits<i16>::max();
			case OP_REL32:     return value >= utility::limits<i32>::min() && value <= utility::limits<i32>::max();
			default: ASSERT(false, "unexpected operand type {}\n", operand_type_to_string(type));
		}

		return false;
	}

	auto assembler::assemble(const utility::dynamic_string& source) -> utility::result<assembler::module> {
		TRY(tokenize(source));  // generate the token stream
		TRY(parse());           // generate the symbol table and unresolved list
		TRY(resolve_symbols()); // resolve symbols locations

		return emit_module();
	}

	auto assembler::emit_module() -> utility::result<assembler::module> {
		utility::dynamic_array<u8> bytes;
		u64 total_size = 0;

		// calculate the total section size
		for(const subsection& subsection : m_subsections) {
			if(subsection.type == SS_NORMAL) {
				total_size += subsection.resolved.size;
			}
			else {
				total_size += m_unresolved[subsection.unresolved].size;
			}
		}

		bytes.reserve(total_size);

		// emit our subsections
		for(const subsection& subsection : m_subsections) {
			if(subsection.type == SS_NORMAL) {
				const u8* data = subsection.resolved.data;
				bytes.insert(bytes.end(), data, data + subsection.resolved.size);
			}
			else {
				unresolved_subsection unresolved = m_unresolved[subsection.unresolved];
				assembler_backend backend(&m_context);

				// calculate the offset operand
				const operand unresolved_operand = unresolved.operands[unresolved.unresolved_operand];
				const i64 value = m_symbols[unresolved_operand.symbol] - (unresolved.position + unresolved.size);
				operand* operands = unresolved.operands;

				operands[unresolved.unresolved_operand].immediate = imm(value);

				// emit the instruction with our exact operands
				backend.emit_instruction_direct(assembler_backend::find_direct(unresolved.index, operands), operands);

				// TODO: directly emit bytes
				auto temp = backend.get_bytes();
				bytes.insert(bytes.end(), temp.begin(), temp.end());
			}
		}

		return assembler::module{ .bytes = bytes };
	}

	auto assembler::resolve_symbols() -> utility::result<void> {
		// TODO: verify whether a symbol actually exists
		bool change = true;

		while(change) {
			change = false;

			// optimize symbol references, try to use the smallest possible operand
			for(unresolved_subsection& current : m_unresolved) {
				if(current.variants.is_empty()) {
					// this element is already as optimized as it can be 
					continue;
				}

				const u64 symbol_position = m_symbols.at(current.operands[current.unresolved_operand].symbol);
				const i64 distance = symbol_position - current.position + current.size;
				const operand_type new_type = current.variants.get_last();

				if(!fits_into_type(distance, new_type)) {
					// we can't use a smaller operand, no optimization possible in this iteration
					continue;
				}

				// use the next smallest operand instead
				current.operands[current.unresolved_operand].type = new_type;
				u8 new_size = assembler_backend::get_instruction_size(current.index, current.operands);

				// update our symbol table to account for the difference in code length
				recalculate_symbol_positions(current.position, current.size - new_size);

				current.variants.pop_back();
				current.size = new_size;

				change = true;

				// TODO: investigate whether it's better to break immediately or continue
				break;
			}
		}

		return SUCCESS;
	}

	void assembler::recalculate_symbol_positions(u64 position, i32 diff) {
		// move all symbols and unresolved instructions which are located past the specified position by diff bytes
		for(auto& [name, pos] : m_symbols) {
			if(pos > position) {
				pos -= diff;
			}	
		}

		for(auto& u : m_unresolved) {
			if(u.position > position) {
				u.position -= diff;
			}
		}	
	}

	void assembler::create_normal_subsection() {
		if(!m_current_resolved.is_empty()) {
			subsection p;
			p.type = SS_NORMAL;
			p.resolved.size = m_current_resolved.get_size();
			p.resolved.data = static_cast<u8*>(m_context.allocator.allocate(m_current_resolved.get_size()));
			utility::memcpy(p.resolved.data, m_current_resolved.get_data(), m_current_resolved.get_size());

			m_subsections.push_back(p);
			m_current_resolved.clear();
		}
	}

	auto assembler::tokenize(const utility::dynamic_string& source) -> utility::result<void> {
		assembler_lexer lexer(source);

		do {
			token current;
			TRY(current.type, lexer.get_next_token());

			switch(current.type) {
				case TOK_IDENTIFIER:
				case TOK_STRING:     current.identifier = m_context.strings.add(lexer.current_string); break;
				case TOK_NUMBER:     current.immediate  = lexer.current_immediate;                     break;
				default:                                                                               break;
			}

			m_tokens.value.push_back(current);
		} while(lexer.current != TOK_EOF);

		return SUCCESS;
	}

	auto assembler::parse() -> utility::result<void> {
		m_token_index = 0;

		while(get_next_token() != TOK_EOF) {
			switch(m_current_token.type) {
				case TOK_IDENTIFIER: TRY(parse_identifier()); break;
				case TOK_TIMES:      TRY(parse_times()); break;
				case TOK_BITS:       TRY(parse_bits()); break;
				case TOK_NEWLINE:    break;
				default: ASSERT(false, "unexpected top level token: {}\n", token_to_string(m_current_token.type)); 
			}	
		}

		create_normal_subsection(); // capture any trailing instructions
		return SUCCESS;
	}

	auto assembler::parse_instruction() -> utility::result<void> {
		u32 start;
		u32 index = start = find_instruction_by_name(m_current_identifier->get_data());
		utility::string_view* instruction_name = m_current_identifier;

		if(index == utility::limits<u32>::max()) {
			ASSERT(false, "[PASS 1]: unknown instruction '{}' specified\n", *m_current_identifier);
		}

		// ensure our destination is clean
		utility::memset(m_operands, 0, sizeof(operand) * 4);
		m_symbolic_operand = false;
		m_operand_i = 0;

		while(m_current_token != TOK_EOF && m_current_token != TOK_NEWLINE) {
			switch(m_current_token.type) {
				case TOK_IDENTIFIER: TRY(parse_identifier_operand()); break;
				default: ASSERT(false, "unexpected operand token: {}\n", token_to_string(m_current_token.type)); 
			}

			get_next_token();

			if(m_current_token != TOK_COMMA) {
				break;
			}

			get_next_token();
		}

		// locate the specific variant (dumb linear search in our specific group)
		while(index < instruction_db_size) {
			const instruction& current = instruction_db[index]; 

			// verify that the instruction names are the same and that we've not left our instruction group
			if(utility::compare_strings(instruction_name->get_data(), current.name) != 0) {
				break;
			}

			// verify that the current instruction matches the provided operands
			if(detail::is_operand_match(current, m_operands, 0, m_operand_i)) {
				u8 variant_index = 0;
				// operands match, but, in some cases we need to retype some of them to the actual type, ie. 
				// immediates can actually be relocations
				for(u8 j = 0; j < m_operand_i; ++j) {
					if(m_operands[j].type == OP_REL_UNKNOWN) {
						variant_index = j;
						continue;
					}

					m_operands[j].type = current.operands[j];

					if(is_operand_rel(current.operands[j])) {
						rel r = rel(static_cast<i32>(m_operands[j].immediate.value));
						m_operands[j].relocation = r; 
					}
				}

				// HACK: assemble the instruction and use that as the length
				// TODO: cleanup
				assembler_backend backend(&m_context);

				backend.emit_instruction(index, m_operands);

				u8 size = backend.get_module().get_size_current_section();

				if(m_symbolic_operand) {
					// append all of our relative instructions which we've encountered before this one
					create_normal_subsection();

					// create the fixup subsection for the current instruction
					subsection fixup {
						.type = SS_FIXUP,
						.unresolved = m_unresolved.get_size()
					};

					// remove the last potential variant (the largest one), and use it as our operand, this will
					// most likely be optimized out by the resolve_symbols() function
					m_operands[variant_index].type = backend.current_variants.pop_back();

					// create the actual subsection the fixup points to
					unresolved_subsection unresolved = {
						.index = index,
						.operand_count = m_operand_i,
						.position = m_instruction_offset,
						.size = size,
						.variants = backend.current_variants,
						.unresolved_operand = variant_index
					};

					utility::memcpy(unresolved.operands, m_operands, 4 * sizeof(operand));
					
					m_unresolved.push_back(unresolved);
					m_subsections.push_back(fixup);
				}
				else {
					auto binary = backend.get_module().emit_binary();
					m_current_resolved.insert(m_current_resolved.end(), binary.begin(), binary.end());
				}

				m_instruction_offset += size;
				return SUCCESS;
			}

			index++;
		}

		ASSERT(false, "invalid instruction\n");
		return SUCCESS;
	}

	auto assembler::parse_identifier_operand() -> utility::result<void> {
		// utility::console::print("[PASS 1]: symbolic operand '{}'\n", *m_current_token.identifier);
		EXPECT_TOKEN(TOK_IDENTIFIER);

		m_operands[m_operand_i++] = operand(m_current_token.identifier); 
		m_symbolic_operand = true;
		return SUCCESS;
	}

	auto assembler::parse_identifier() -> utility::result<void> {
		EXPECT_TOKEN(TOK_IDENTIFIER);
		m_current_identifier = m_current_token.identifier;

		get_next_token();

		switch(m_current_token.type) {
			case TOK_COLON: return parse_label();
			default: return parse_instruction();
		}

		return SUCCESS;
	}
		
	auto assembler::parse_label() -> utility::result<void> {
		EXPECT_TOKEN(TOK_COLON);
		m_symbols.insert({ m_current_identifier, m_instruction_offset });
		return SUCCESS;
	}
	
	auto assembler::parse_times() -> utility::result<void> {
		EXPECT_TOKEN(TOK_TIMES);
		get_next_token();
		EXPECT_TOKEN(TOK_NUMBER);
		u64 times = m_current_token.immediate.value;
		u64 index = m_token_index;

		for(u64 i = 0; i < times; ++i) {
			m_token_index = index;
			get_next_token();

			switch(m_current_token.type) {
				case TOK_IDENTIFIER: {
					m_current_identifier = m_current_token.identifier;
					get_next_token();
					TRY(parse_instruction()); 
					break; 
				}
				default: ASSERT(false, "unexpected times token: {}\n", token_to_string(m_current_token.type)); 
			}
		}

		get_next_token();
		return SUCCESS;
	}

	auto assembler::parse_bits() -> utility::result<void> {
		EXPECT_TOKEN(TOK_BITS);
		get_next_token();
		EXPECT_TOKEN(TOK_NUMBER);
		return SUCCESS;
	}

	auto assembler::get_next_token() -> token {
		return m_current_token = m_tokens[m_token_index++];
	}
} // namespace baremetal

