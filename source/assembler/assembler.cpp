#include "assembler.h"
#include "assembler/assembler_lexer.h"
#include "assembler/assembler_parser.h"

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

	assembler::assembler() : m_section_index(0) {
		section text {
			.name = m_context.strings.add("text"),
		};

		m_sections.push_back(text);
	}

	auto assembler::assemble(const utility::dynamic_string& source) -> utility::result<assembler::module> {
		TRY(tokenize(source));  // generate the token stream
		TRY(parse());           // generate the symbol table and unresolved list
		TRY(resolve_symbols()); // resolve symbols locations

		return emit_module();
	}

	auto assembler::emit_module() -> utility::result<assembler::module> {
		utility::dynamic_array<relocation> relocations;
		utility::dynamic_array<u8> bytes;
		u64 total_size = 0;

		// calculate the total section size
		for(section& section : m_sections) {
			// alignment
			total_size += utility::align(total_size, 4) - total_size;
			section.position = total_size;

			for(const subsection& subsection : section.subsections) {
				if(subsection.type == SS_NORMAL) {
					total_size += subsection.resolved.size;
				}
				else {
					total_size += section.unresolved[subsection.unresolved].size;
				}
			}
		}

		bytes.reserve(total_size);

		// generate the final binary
		for(const section& section : m_sections) {
			// append alignment bytes for the previous section
			const u64 alignment_offset = utility::align(bytes.get_size(), 4) - bytes.get_size();

			for(u64 i = 0; i < alignment_offset; ++i) {
				bytes.push_back(0);
			}

			// emit subsections
			for(const subsection& subsection : section.subsections) {
				if(subsection.type == SS_NORMAL) {
					const u8* data = subsection.resolved.data;
					bytes.insert(bytes.end(), data, data + subsection.resolved.size);
				}
				else {
					unresolved_subsection unresolved = section.unresolved[subsection.unresolved];
					assembler_backend backend(&m_context);

					// calculate the offset operand
					const operand unresolved_operand = unresolved.operands[unresolved.unresolved_operand];
					const auto symbol_it = section.symbols.find(unresolved_operand.symbol);
					i64 value = 0;

					if(symbol_it == section.symbols.end()) {
						// references a symbol in a different section, or the symbol does not exist
						symbol sym = get_symbol_global(unresolved_operand.symbol);

						switch(unresolved_operand.type) {
							case OP_I32:
							case OP_I64:   value = sym.position; break;
							case OP_REL8_RIP: 
							case OP_REL32: value = (sym.position) - (section.position + unresolved.position + unresolved.size); break;
							default: ASSERT(false, "unhandled operand type '{}' detected\n", operand_type_to_string(unresolved_operand.type));
						}
					}
					else {
						// references a symbol in the same section
						switch(unresolved_operand.type) {
							case OP_I32:
							case OP_I64:   value = get_symbol_global(unresolved_operand.symbol).position; break;
							case OP_REL8_RIP: 
							case OP_REL32: value = symbol_it->second.position - (unresolved.position + unresolved.size); break;
							default: ASSERT(false, "unhandled operand type '{}' detected\n", operand_type_to_string(unresolved_operand.type));
						}

						// utility::console::print("local symbol {}: {}\n", *unresolved_operand.symbol, value);
					}

					operand* operands = unresolved.operands;
					operands[unresolved.unresolved_operand].immediate = imm(value);

					// emit the instruction with our exact operands
					backend.emit_instruction_direct(assembler_backend::find_direct(unresolved.index, operands), operands);

					// TODO: directly emit bytes
					auto temp = backend.get_bytes();
					bytes.insert(bytes.end(), temp.begin(), temp.end());
				}
			}
		}

		return assembler::module{ .bytes = bytes };
	}

	auto assembler::resolve_symbols() -> utility::result<void> {
		for(section& section : m_sections) {
			// TODO: verify whether a symbol actually exists
			// TODO: investigate the speed improvements of removing completed subsections
			bool change = true;

			// resolve and optimize symbol references within each section (we can ignore references to other sections
			// since we'll resolve them during emission)
			while(change) {
				change = false;

				// optimize symbol references, try to use the smallest possible operand
				for(unresolved_subsection& current : section.unresolved) {
					if(current.variants.is_empty()) {
						// this element is already as optimized as it can be 
						continue;
					}

					operand& unresolved = current.operands[current.unresolved_operand];
					const auto symbol_it = section.symbols.find(unresolved.symbol);

					if(symbol_it == section.symbols.end()) {
						// skip symbols which aren't in this section, since we can't optimize them
						continue;
					}

					const i64 distance = symbol_it->second.position - current.position + current.size;
					const operand_type new_type = current.variants.get_last();

					if(!fits_into_type(distance, new_type)) {
						// we can't use a smaller operand, no optimization possible in this iteration
						continue;
					}

					// use the next smallest operand instead
					unresolved.type = new_type;
					u8 new_size = assembler_backend::get_instruction_size(current.index, current.operands);

					// update our symbol table to account for the difference in code length
					section.update_positions(current.position, current.size - new_size);

					current.variants.pop_back();
					current.size = new_size;
					change = true;

					// TODO: investigate whether it's better to break immediately or continue
					break;
				}
			}
		}

		return SUCCESS;
	}

	void section::update_positions(u64 position, i32 diff) {
		// move all symbols and unresolved instructions which are located past the specified position by diff bytes
		for(auto& [sym_name, sym_position] : symbols) {
			if(sym_position.position > position) {
				sym_position.position -= diff;
			}	
		}

		// we end up moving references which point to symbols which are not within this sections, this is fine
		// since we don't use their position in that case anyways
		for(auto& u : unresolved) {
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

			m_sections[m_section_index].subsections.push_back(p);
			m_current_resolved.clear();
		}
	}

	auto assembler::get_symbol_global(utility::string_view* name) -> symbol {
		for(const section& section : m_sections) {
			const auto it = section.symbols.find(name);

			if(it != section.symbols.end()) {
				// section position + symbol position (relative to the parent section)
				return { section.position + it->second.position, it->second.type };
			}
		}

		ASSERT(false, "unknown symbol '{}' specified\n", *name);
		return {};
	}

	void assembler::set_section(utility::string_view* name) {
		for(u64 i = 0; i < m_sections.get_size(); ++i) {
			if(m_sections[i].name == name) {
				m_section_index = i;
				return;
			}
		}

		m_section_index = m_sections.get_size();
		m_sections.push_back(section{
			.name = name,
		});
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
			m_current_identifier = nullptr;

			switch(m_current_token.type) {
				case TOK_IDENTIFIER: TRY(parse_identifier()); break;
				case TOK_SECTION:    TRY(parse_section()); break;
				case TOK_TIMES:      TRY(parse_times()); break;
				case TOK_BITS:       TRY(parse_bits()); break;
				case TOK_NEWLINE:    break;
				default: ASSERT(false, "unexpected top level token: {}\n", token_to_string(m_current_token.type)); 
			}	
		}

		create_normal_subsection(); // capture any trailing instructions
		return SUCCESS;
	}

	auto assembler::parse_define_memory() -> utility::result<void> {
		if(m_current_identifier) {
			m_sections[m_section_index].symbols.insert({ m_current_identifier, {
				m_sections[m_section_index].offset,
				SYM_GLOBAL
			}});
		}

		u8 bytes = 0;

		switch(m_current_token.type) {
			case TOK_DB: bytes = 1; break;
			case TOK_DW: bytes = 2; break;
			case TOK_DD: bytes = 4; break;
			case TOK_DQ: bytes = 8; break;
			default: ASSERT(false, "unreachable\n");
		}

		get_next_token();

		while(m_current_token != TOK_EOF) {
			switch(m_current_token.type) {
				case TOK_CHAR: 
				case TOK_STRING: {
					for(const char c : *m_current_token.identifier) {
						m_current_resolved.push_back(c);
						m_sections[m_section_index].offset++;
					}

					// apend missing bytes, so that we're aligned with our data type
					const u64 offset = m_current_token.identifier->get_size();
					const u64 alignment_offset = utility::align(offset, bytes) - offset; 

					for(u64 i = 0; i < alignment_offset; ++i) {
						m_current_resolved.push_back(0);
						m_sections[m_section_index].offset++;
					}

					break;
				}
				case TOK_MINUS: ASSERT(false, "TODO\n"); break;
				case TOK_NUMBER: {
					if(m_current_token.immediate.min_bits / 8 > bytes) {
						utility::console::print("warning: byte data exceeds bounds\n");
					}

					u64 value = m_current_token.immediate.value;

					for(u8 i = 0; i < bytes; ++i) {
			      u8 byte = static_cast<u8>(value & 0xFF);
						m_current_resolved.push_back(byte);
						m_sections[m_section_index].offset++;
			      value >>= 8;
			    }

					break;
				}
				default: return utility::error("unexpected token following memory definition");
			}
			
			get_next_token();

			// memory define operands should be comma separated
			if(m_current_token != TOK_COMMA) {
				break;
			}
		
			get_next_token();
		}

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
				case TOK_IDENTIFIER:       TRY(parse_identifier_operand()); break;
				case TOK_NUMBER:           TRY(parse_immediate_operand()); break;
				case TOK_CR0 ... TOK_R15B: TRY(parse_register_operand()); break;
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

				section& parent = m_sections[m_section_index];
				if(m_symbolic_operand) {
					// append all of our relative instructions which we've encountered before this one
					create_normal_subsection();

					// create the fixup subsection for the current instruction
					subsection fixup {
						.type = SS_FIXUP,
						.unresolved = parent.unresolved.get_size()
					};

					// remove the last potential variant (the largest one), and use it as our operand, this will
					// most likely be optimized out by the resolve_symbols() function
					m_operands[variant_index].type = backend.current_variants.pop_back();

					if(!is_operand_rel(m_operands[variant_index].type)) {
						backend.current_variants.clear(); // no potential for optimizations
					}

					// create the actual subsection the fixup points to
					unresolved_subsection unresolved = {
						.index = index,
						.operand_count = m_operand_i,
						.position = parent.offset,
						.size = size,
						.variants = backend.current_variants,
						.unresolved_operand = variant_index
					};

					utility::memcpy(unresolved.operands, m_operands, 4 * sizeof(operand));
					
					parent.unresolved.push_back(unresolved);
					parent.subsections.push_back(fixup);
				}
				else {
					auto binary = backend.get_module().emit_binary();
					m_current_resolved.insert(m_current_resolved.end(), binary.begin(), binary.end());
				}

				parent.offset += size;
				return SUCCESS;
			}

			index++;
		}

ASSERT(false, "invalid instruction\n");
		return SUCCESS;
	}

	auto assembler::parse_identifier_operand() -> utility::result<void> {
		m_operands[m_operand_i++] = operand(m_current_token.identifier); 
		m_symbolic_operand = true;
		return SUCCESS;
	}

	auto assembler::parse_immediate_operand() -> utility::result<void> {
		m_operands[m_operand_i++] = operand(m_current_token.immediate); 
		return SUCCESS;
	}

	auto assembler::parse_register_operand() -> utility::result<void> {
		operand op = operand(token_to_register(m_current_token.type));
		m_operands[m_operand_i++] = op;
		return SUCCESS;
	}

	auto assembler::parse_identifier() -> utility::result<void> {
		EXPECT_TOKEN(TOK_IDENTIFIER);
		m_current_identifier = m_current_token.identifier;

		get_next_token();

		switch(m_current_token.type) {
			case TOK_DB ... TOK_DQ: return parse_define_memory();
			case TOK_COLON:         return parse_label();
			default:                return parse_instruction();
		}

		return SUCCESS;
	}
		
	auto assembler::parse_section() -> utility::result<void> {
		EXPECT_TOKEN(TOK_SECTION);

		get_next_token();
		EXPECT_TOKEN(TOK_DOT);

		get_next_token();
		EXPECT_TOKEN(TOK_IDENTIFIER);

		create_normal_subsection(); // capture any trailing instructions
		set_section(m_current_token.identifier);

		return SUCCESS;
	}

	auto assembler::parse_label() -> utility::result<void> {
		EXPECT_TOKEN(TOK_COLON);

		m_sections[m_section_index].symbols.insert({ 
			m_current_identifier,
			{ m_sections[m_section_index].offset, SYM_RIP_RELATIVE }
		});

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
				case TOK_DB ... TOK_DQ: TRY(parse_define_memory()); break;
				default: ASSERT(false, "unexpected times token: {}\n", token_to_string(m_current_token.type)); 
			}
		}

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

