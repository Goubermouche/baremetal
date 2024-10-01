#include "assembler.h"
#include "assembler/assembler_lexer.h"
#include "assembler/assembler_parser.h"
#include "assembler/instruction/operands/operands.h"
#include "assembler/backend.h"

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
			.name = m_context.strings.add(".text"),
			.subsections = {},
			.unresolved = {},
			.symbols = {}
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
			if(section.subsections.is_empty()) {
				continue;
			}

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
					operand* operands = unresolved.operands;

					// resolve the symbol position
					switch(unresolved_operand.type) {
						// immediates are absolute
						// case OP_I8:
						// case OP_I16:
						case OP_I32:
						case OP_I64: operands[unresolved.unresolved_operand].immediate = imm(get_symbol_global(unresolved_operand.symbol)); break;
						case OP_M8: 
						case OP_M16: 
						case OP_M32: 
						case OP_M64: 
						case OP_M80: {
							switch(unresolved.fixup) {
								case FIXUP_DISPLACEMENT: {
									i64 value;

									if(symbol_it == section.symbols.end()) {
										value = get_symbol_global(unresolved_operand.symbol);	
									}
									else {
										value = symbol_it->second;	
									}

									operands[unresolved.unresolved_operand].memory.displacement = value;
									// use the biggest possible displacement (MOD/RM hack)
									operands[unresolved.unresolved_operand].memory.displacement.min_bits = 32;
									break;
								}
								default: ASSERT(false, "unexpected fixup type {}\n", (i32)unresolved.fixup);
							}

							break; // TODO	
						} 
						// relocations are relative
						case OP_REL32:
						case OP_REL8:
						case OP_REL8_RIP: {
							u64 inst_pos = unresolved.position;
							u64 inst_size = unresolved.size;
							i64 value;

							if(symbol_it == section.symbols.end()) {
								// global symbol position - (section position + instruction position + instruction size)
								value = get_symbol_global(unresolved_operand.symbol) - (section.position + inst_pos + inst_size);	
							}
							else {
								// symbol position - (instruction position + instruction size)
								value = symbol_it->second - (inst_pos + inst_size);	
							}

							operands[unresolved.unresolved_operand].immediate = imm(value);
							break;
						}
						default: ASSERT(false, "unhandled unresolved operand type '{}'\n", operand_type_to_string(unresolved_operand.type));
					}

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

					const i64 distance = symbol_it->second - current.position + current.size;
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
			if(sym_position > position) {
				sym_position -= diff;
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

	auto assembler::get_symbol_global(utility::string_view* name) -> u64 {
		for(const section& section : m_sections) {
			const auto it = section.symbols.find(name);

			if(it != section.symbols.end()) {
				// section position + symbol position (relative to the parent section)
				return section.position + it->second;
			}
		}

		ASSERT(false, "unknown symbol '{}' specified\n", *name);
		return {};
	}

	auto assembler::get_symbol_local(utility::string_view* name) -> u64 {
		for(const section& section : m_sections) {
			const auto it = section.symbols.find(name);

			if(it != section.symbols.end()) {
				return it->second;
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
			.subsections = {},
			.unresolved = {},
			.symbols = {}
		});
	}

	auto assembler::tokenize(const utility::dynamic_string& source) -> utility::result<void> {
		assembler_lexer lexer(source);

		do {
			token current;
			TRY(current.type, lexer.get_next_token());

			switch(current.type) {
				case TOK_IDENTIFIER:
				case TOK_CHAR:
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

		get_next_token();

		while(m_current_token != TOK_EOF) {
			m_current_identifier = nullptr;

			switch(m_current_token.type) {
				case TOK_RESB ... TOK_RESQ: TRY(parse_reserve_memory()); break;
				case TOK_IDENTIFIER:        TRY(parse_identifier()); break;
				case TOK_SECTION:           TRY(parse_section()); break;
				case TOK_TIMES:             TRY(parse_times()); break;
				case TOK_BITS:              TRY(parse_bits()); break;
				case TOK_NEWLINE:           get_next_token(); break;
				default: ASSERT(false, "unexpected top level token: {}\n", token_to_string(m_current_token.type)); 
			}	
		}

		create_normal_subsection(); // capture any trailing instructions
		return SUCCESS;
	}

	auto assembler::parse_reserve_memory() -> utility::result<void> {
		u8 bytes = 0;

		switch(m_current_token.type) {
			case TOK_RESB: bytes = 1; break;
			case TOK_RESW: bytes = 2; break;
			case TOK_RESD: bytes = 4; break;
			case TOK_RESQ: bytes = 8; break;
			default: ASSERT(false, "unreachable\n");
		}

		SUPPRESS_C4100(bytes);

		// ignored for now, this only appears in object formats
		get_next_token();
		EXPECT_TOKEN(TOK_NUMBER);
		get_next_token();

		if(*m_sections[m_section_index].name != ".bss") {
			for(u64 i = 0; i < m_current_token.immediate.value; ++i) {
				m_current_resolved.push_back(0);
			}
		}


		return SUCCESS;
	}

	auto assembler::parse_define_memory() -> utility::result<void> {
		if(m_current_identifier) {
			m_sections[m_section_index].symbols.insert({ m_current_identifier, {
				m_sections[m_section_index].offset
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

		get_next_token();
		return SUCCESS;
	}
	
	auto assembler::parse_instruction() -> utility::result<void> {
		u32 start;
		m_instruction_i = start = backend::get_instruction_by_name(m_current_identifier->get_data());
		utility::string_view* instruction_name = m_current_identifier;

		if(m_instruction_i == utility::limits<u32>::max()) {
			ASSERT(false, "[PASS 1]: unknown instruction '{}' specified\n", *m_current_identifier);
		}

		// ensure our destination is clean
		utility::memset(m_operands, 0, sizeof(operand) * 4);
		m_unresolved_index = utility::limits<u8>::max();
		m_symbolic_operand = false;
		m_broadcast_n = 0;
		m_operand_i = 0;

		while(m_current_token != TOK_EOF && m_current_token != TOK_NEWLINE) {
			switch(m_current_token.type) {
				case TOK_LBRACKET:           TRY(parse_memory_operand(DT_NONE)); break; 
				case TOK_IDENTIFIER:         TRY(parse_identifier_operand()); break;
				case TOK_MINUS:              TRY(parse_immediate_operand()); break;
				case TOK_NUMBER:             TRY(parse_immediate_operand()); break;
				case TOK_CR0 ... TOK_R15B:   TRY(parse_register_operand()); break;
				case TOK_DOLLARSIGN:         TRY(parse_rip_rel_operand()); break;
				case TOK_BYTE ... TOK_TWORD: TRY(parse_type_operand()); break;
				case TOK_CHAR:               TRY(parse_operand_char()); break;
				default: ASSERT(false, "unexpected operand token: {}\n", token_to_string(m_current_token.type)); 
			}

			if(m_current_token != TOK_COMMA) {
				break;
			}

			get_next_token();
		}

		// locate the specific variant (dumb linear search in our specific group)
		while(m_instruction_i < instruction_db_size) {
			const instruction& current = instruction_db[m_instruction_i]; 

			// verify that the instruction names are the same and that we've not left our instruction group
			if(utility::compare_strings(instruction_name->get_data(), current.name) != 0) {
				break;
			}

			// verify that the current instruction matches the provided operands
			if(detail::is_operand_match(current, m_operands, m_broadcast_n, m_operand_i)) {
				// operands match, but, in some cases we need to retype some of them to the actual type, ie. 
				// immediates can actually be relocations
				for(u8 j = 0; j < m_operand_i; ++j) {
					if(j == m_unresolved_index) {
						continue;
					}

					m_operands[j].type = current.operands[j];

					if(is_operand_rel(current.operands[j])) {
						u8 size = assembler_backend::get_instruction_size(m_instruction_i, m_operands);
						m_operands[j].immediate = static_cast<i32>(m_operands[j].immediate.value) - size;
					}
				}

				if(m_symbolic_operand) {
					m_operands[m_unresolved_index].unknown = true;

					if(is_operand_mem(m_operands[m_unresolved_index].type) && m_fixup == FIXUP_DISPLACEMENT) {
						// force the longest possible encoding
						m_operands[m_unresolved_index].memory.displacement = 1;
						m_operands[m_unresolved_index].memory.displacement.min_bits = 32;
					}
				}

				// HACK: assemble the instruction and use that as the length
				// TODO: cleanup
				assembler_backend backend(&m_context);
				backend.emit_instruction(m_instruction_i, m_operands);
				// utility::console::print("{}\n", m_instruction_i);
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
					m_operands[m_unresolved_index].type = backend.current_variants.pop_back();

					if(!is_operand_rel(m_operands[m_unresolved_index].type)) {
						backend.current_variants.clear(); // no potential for optimizations
					}

					// create the actual subsection the fixup points to
					unresolved_subsection unresolved = {
						.index = m_instruction_i,
						.operands = {},
						.operand_count = m_operand_i,
						.position = parent.offset,
						.size = size,
						.variants = backend.current_variants,
						.unresolved_operand = m_unresolved_index,
						.fixup = m_fixup
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

			m_instruction_i++;
		}

		utility::console::print_err("'{}': ", instruction_db[start].name);
		for(u8 i = 0; i < m_operand_i; ++i) {
			utility::console::print_err("{} ", operand_type_to_string(m_operands[i].type));
		}
		utility::console::print_err("\n");
		return utility::error("invalid operand combination for instruction");
	}

	auto assembler::parse_moff_operand(data_type type) -> utility::result<void> {
		if(type != DT_NONE) {
			return utility::error("duplicate data type specified in memory/moff operand");
		}

		get_next_token();
		EXPECT_TOKEN(TOK_NUMBER);

		m_operands[m_operand_i++] = operand(moff(m_current_token.immediate.value));

		get_next_token();
		EXPECT_TOKEN(TOK_RBRACKET);

		get_next_token();
		return SUCCESS;
	}

	auto assembler::parse_broadcast_operand(mask_type mask) -> utility::result<void> {
		m_broadcast_n = mask_to_broadcast_n(mask);
		
		get_next_token();
		EXPECT_TOKEN(TOK_RBRACE);
		get_next_token();

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

	auto assembler::parse_memory_operand(data_type type) -> utility::result<void> {
		EXPECT_TOKEN(TOK_LBRACKET);
		operand op = {};

		switch(type) {
			case DT_NONE:  op.type = OP_M128; break; // M128 currently works as an infer keyword
			case DT_BYTE:  op.type = OP_M8;   break;
			case DT_WORD : op.type = OP_M16;  break;
			case DT_DWORD: op.type = OP_M32;  break;
			case DT_QWORD: op.type = OP_M64;  break;
			case DT_TWORD: op.type = OP_M80;  break;
		}
	
		get_next_token();

		// we can potentially have types in here, which means we're handling a moff
		switch(m_current_token.type) {
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

	auto assembler::parse_identifier_operand() -> utility::result<void> {
		m_unresolved_index = m_operand_i;
		m_operands[m_operand_i++] = operand(m_current_token.identifier); 
		m_symbolic_operand = true;
		get_next_token();
		return SUCCESS;
	}

	auto assembler::parse_immediate_operand() -> utility::result<void> {
		if(m_current_token == TOK_MINUS) {
			get_next_token();
			EXPECT_TOKEN(TOK_NUMBER);
			m_operands[m_operand_i++] = operand(imm(-static_cast<i64>(m_current_token.immediate.value))); 
		}
		else {
			EXPECT_TOKEN(TOK_NUMBER);
			m_operands[m_operand_i++] = operand(m_current_token.immediate); 
		}

		get_next_token();
		return SUCCESS;
	}

	auto assembler::parse_register_operand() -> utility::result<void> {
		operand op = operand(token_to_register(m_current_token.type));
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

	auto assembler::parse_type_operand() -> utility::result<void> {
		// parse an operand which begins with a type keyword 
		data_type type = token_to_data_type(m_current_token.type);

		get_next_token();

		switch(m_current_token.type) {
			case TOK_LBRACKET: parse_memory_operand(type); break;
			default: return utility::error("unexpected token following type");
		}

		return SUCCESS;
	}

	auto assembler::parse_operand_char() -> utility::result<void> {
		EXPECT_TOKEN(TOK_CHAR);
		m_operands[m_operand_i++] = imm(static_cast<i32>(m_current_token.identifier->get_data()[0]));
		get_next_token();
		return SUCCESS;
	}

	auto assembler::parse_rip_rel_operand() -> utility::result<void> {
		get_next_token();

		if(m_current_token != TOK_PLUS) {
			return utility::error("unexpected token received in rip-relative address");
		}

		operand rip_rel; 

		get_next_token();

		if(m_current_token == TOK_MINUS) {
			// negative relocations are always rel32 (without being rip-relative)
			rip_rel.type = OP_REL32;

			get_next_token();
			EXPECT_TOKEN(TOK_NUMBER);

			rip_rel.immediate = imm(-1 * static_cast<i64>(m_current_token.immediate.value));
		} 
		else {
			EXPECT_TOKEN(TOK_NUMBER);

			// select the actual data type
			switch(m_current_token.immediate.min_bits) {
				case 8:  rip_rel.type = OP_REL8_RIP;  break;
				case 16: rip_rel.type = OP_REL16_RIP; break;
				case 32: rip_rel.type = OP_REL32_RIP; break;
				default: return utility::error("invalid rip-relative address width");
			}

			rip_rel.immediate = m_current_token.immediate;
		}

		m_operands[m_operand_i++] = rip_rel;

		get_next_token();
		return SUCCESS;
	}

	auto assembler::parse_identifier() -> utility::result<void> {
		EXPECT_TOKEN(TOK_IDENTIFIER);
		m_current_identifier = m_current_token.identifier;

		get_next_token();

		// utility::console::print("{}  {}\n", *m_current_identifier, token_to_string(m_current_token.type));
		switch(m_current_token.type) {
			case TOK_DB ... TOK_DQ: return parse_define_memory();
			case TOK_COLON:         return parse_label();
			default:                return parse_instruction();
		}

		return SUCCESS;
	}
		
	auto assembler::parse_section() -> utility::result<void> {
		EXPECT_TOKEN(TOK_SECTION);

		// get_next_token();
		// EXPECT_TOKEN(TOK_DOT);

		get_next_token();
		EXPECT_TOKEN(TOK_IDENTIFIER);
		ASSERT(m_current_token.identifier->get_data()[0] == '.', "first char of a section should be a '.'\n");

		create_normal_subsection(); // capture any trailing instructions

		set_section(m_current_token.identifier);

		get_next_token();
		return SUCCESS;
	}

	auto assembler::parse_label() -> utility::result<void> {
		EXPECT_TOKEN(TOK_COLON);

		m_sections[m_section_index].symbols.insert({ 
			m_current_identifier,
			m_sections[m_section_index].offset
		});

		get_next_token();
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
			
			// TODO: traverse to the end of our current line and verify there isn't anything else here
		}

		get_next_token();
		return SUCCESS;
	}

	auto assembler::parse_bits() -> utility::result<void> {
		EXPECT_TOKEN(TOK_BITS);
		get_next_token();
		EXPECT_TOKEN(TOK_NUMBER);
		get_next_token();
		return SUCCESS;
	}

	auto assembler::parse_memory(operand& op) -> utility::result<void> {
		reg current_reg = reg::create_invalid();
		mem& memory = op.memory;
		imm current_imm;

		memory.displacement = 0;

		bool displacement_set = false;
		bool scale_mode = false;
		bool imm_set = false;
		bool negate = false;

		// TODO: this still doesn't work with negative operands

		// entry
		while(true) {
			switch(m_current_token.type) {
				// register
				case TOK_CR0 ... TOK_R15B: {
					if(scale_mode && imm_set) {
						// scale * reg
						if(memory.has_index) {
							return utility::error("memory index cannot be specified twice");
						}

						memory.index = token_to_register(m_current_token.type);
						memory.has_index = true;

						TRY(memory.s, detail::imm_to_scale(current_imm));

						scale_mode = false;
						imm_set = false;
					}
					else {
						current_reg = token_to_register(m_current_token.type);
					}

					break;
				}
				// rel $
				case TOK_REL: {
					get_next_token();
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
					get_next_token();
					EXPECT_TOKEN(TOK_NUMBER);
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

						TRY(memory.s, detail::imm_to_scale(m_current_token.immediate));

						scale_mode = false;
						current_reg = reg::create_invalid();
					}
					else{
						// immediate
						if(negate) {
							current_imm = imm(-1 * static_cast<i64>(m_current_token.immediate.value));
						}
						else {
							current_imm = m_current_token.immediate;
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
					m_symbolic_operand = true;
					m_fixup = FIXUP_DISPLACEMENT;
					op.symbol = m_current_token.identifier;
					memory.displacement.min_bits = 32;
					displacement_set = true;
					break;
				}
				default: {
					return utility::error("unexpected token received in memory operand");
				}
			}

			get_next_token();
		}
	}

	auto assembler::parse_mask_or_broadcast() -> utility::result<mask_type> {
		mask_type result = MASK_NONE;

		get_next_token();

		if(m_current_token != TOK_LBRACE) {
			return result; // no mask
		}

		get_next_token();

		// broadcast
		switch(m_current_token.type) {
			case TOK_1TO2:  return MASK_BROADCAST_1TO2;
			case TOK_1TO4:  return MASK_BROADCAST_1TO4;
			case TOK_1TO8:  return MASK_BROADCAST_1TO8;
			case TOK_1TO16: return MASK_BROADCAST_1TO16;
			case TOK_1TO32: return MASK_BROADCAST_1TO32;
			default: break; 
		}

		u8 k = 0;

		// k
		switch(m_current_token.type) {
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

		get_next_token();
		EXPECT_TOKEN(TOK_RBRACE);
		get_next_token();

		if(m_current_token != TOK_LBRACE) {
			return result; // no zero mask
		}

		// parse the second mask operand '{z}'
		get_next_token();
		EXPECT_TOKEN(TOK_Z);
		result = static_cast<mask_type>(result + 8);
		get_next_token();
		EXPECT_TOKEN(TOK_RBRACE);
		
		get_next_token();
		return result;
	}

	auto assembler::get_next_token() -> token {
		return m_current_token = m_tokens[m_token_index++];
	}
} // namespace baremetal

