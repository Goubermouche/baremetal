#include "assembler.h"
#include "assembler/assembler_lexer.h"
#include "assembler/assembler_parser.h"
#include "utility/system/console.h"

#include <utility/containers/dynamic_array.h>

#define EXPECT_TOKEN(expected)                                    \
  do {                                                            \
    if(m_current_token != expected) {                             \
      return utility::error("[PASS 1]unexpected token received"); \
		}                                                             \
  }                                                               \
  while(false)

namespace baremetal {
	auto get_symbol(const operand* operands) -> utility::string_view* {
		for(u8 i = 0; i < 4; ++i) {
			if(operands[i].type == OP_REL_UNKNOWN) {
				return operands[i].symbol;
			}
		}

		return nullptr;
	}

	auto get_inst_size(u32 index, operand* operands) -> std::pair<u8, utility::dynamic_array<operand_type>> {
		assembler_context context;
		assembler_backend backend(&context);
		backend.emit_instruction_direct(assembler_backend::find_direct(index, operands), operands);

		return { backend.get_module().get_size_current_section(), backend.current_variants };
	}

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

	auto bytes_to_string(const utility::dynamic_array<u8>& bytes) -> utility::dynamic_string {
		utility::dynamic_string result;
		result.reserve(bytes.get_size() * 2);

		constexpr char digits[] = "0123456789abcdef";

		for(u64 i = 0; i < bytes.get_size(); ++i) {
			const u8 value = bytes[i];
			result += (digits[(value >> 4) & 0x0F]);
			result += (digits[value & 0x0F]);
		}

		return result;
	}

	auto bytes_to_string(const u8* bytes, u64 size) -> utility::dynamic_string {
		utility::dynamic_string result;
		result.reserve(size * 2);

		constexpr char digits[] = "0123456789abcdef";

		for(u64 i = 0; i < size; ++i) {
			const u8 value = bytes[i];
			result += (digits[(value >> 4) & 0x0F]);
			result += (digits[value & 0x0F]);
		}

		return result;
	}

	auto assembler::assemble(const utility::dynamic_string& source) -> utility::result<void> {
		TRY(tokenize(source));    // generate the token stream
		
		m_tokens.print();

		TRY(parse_first_pass());  // generate the symbol table and unresolved list

		bool change = true;

		utility::console::print("AVAILABLE VARIANTS:\n");

		for(const auto& resolved : m_unresolved) {
			utility::console::print("\{ ");
 
			for(const auto t : resolved.variants) {
				utility::console::print("{}, ", operand_type_to_string(t));
			}

			utility::console::print("}\n");
		}

		while(change) {
			change = false;

			utility::console::print("----------------------------------------------\n");
			utility::console::print("SYMBOL TABLE:\n");
			for(const auto& [name, position] : m_symbols) {
				utility::console::print("SYMBOL: '{}' {}\n", *name, position);
			}

			// resolve symbollic dependencies
			for(auto& current : m_unresolved) {
				if(current.variants.get_size() == 1) {
					continue;
				}

				utility::string_view* symbol = get_symbol(current.operands);
				const auto it = m_symbols.find(symbol);

				u64 symbol_position = it->second;
				i64 distance = symbol_position - current.position + current.size;
				auto next_closest = current.variants[current.variants.get_size() - 2];

				utility::console::print("TEST {}\n", operand_type_to_string(next_closest));

				if(fits_into_type(distance, next_closest)) {
					current.variants.pop_back();
				
					operand operands[4] = {};

					for(u8 i = 0; i < current.operand_count; ++i) {
						operands[i] = current.operands[i];
					}

					operands[current.variant_index].type = next_closest;
					auto res = get_inst_size(current.index, operands);

					i32 diff = current.size - res.first;
					utility::console::print("GO SMALLER {} -> {} ({}, dist: {})\n", current.size, res.first, diff, distance);

					// update symbols which have been defined after this instruction
					for(auto& [name, position] : m_symbols) {
						if(position > current.position) {
							position -= diff;
							// utility::console::print("  MOVE UP {}\n", *name);
						}	
					}

					// same with unresolved instructions, move them up
					for(auto& u : m_unresolved) {
						if(u.position > current.position) {
							u.position -= diff;
							utility::console::print("  MOVE UP\n");
						}
					}

					current.size = res.first;
					change = true;
					break;
				}	
				
				utility::console::print("UNRESOLVED: '{}' dist: {}\n", *symbol, distance);
			}
		}

		// final printout
		for(const auto& resolved : m_unresolved) {
			utility::console::print("using {}\n", operand_type_to_string(resolved.variants.get_last()));
		}

		utility::console::print("----------------------------------------------\n");
		utility::console::print("final: {} patches\n", m_patches.get_size());

		for(const patch& patch : m_patches) {
			if(patch.type == PATCH_NORMAL) {
				utility::console::print(bytes_to_string(patch.res.data, patch.res.size));
			}
			else {
				unresolved unres = m_unresolved[patch.unres.index];

				assembler_context context;
				assembler_backend backend(&context);

				auto operand = unres.operands[unres.variant_index];
				i64 value = m_symbols[operand.symbol] - (unres.position + unres.size);
				
				unres.operands[unres.variant_index] = imm(value);
				unres.operands[unres.variant_index].type = unres.variants.get_last();
				backend.emit_instruction_direct(assembler_backend::find_direct(unres.index, unres.operands), unres.operands);

				utility::console::print(bytes_to_string(backend.get_bytes()));
			}
		}

		utility::console::print("\n");

		return SUCCESS;
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

	auto assembler::parse_first_pass() -> utility::result<void> {
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

		if(!m_current_resolved.is_empty()) {
			patch p(PATCH_NORMAL);

			p.res.size = m_current_resolved.get_size();
			p.res.data = static_cast<u8*>(m_context.allocator.allocate(m_current_resolved.get_size()));
			utility::memcpy(p.res.data, m_current_resolved.get_data(), m_current_resolved.get_size());

			m_patches.push_back(p);
			m_current_resolved.clear();
		}

		return SUCCESS;	
	}

	auto assembler::parse_second_pass() -> utility::result<void> {
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
		m_symbollic_operand = false;
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

				assembler_context context;
				assembler_backend backend(&context);
				backend.emit_instruction(index, m_operands);

				u8 size = backend.get_module().get_size_current_section();
				utility::console::print("[PASS 1]: parsing instruction '{}'  {}\n", *m_current_identifier, m_instruction_offset);

				if(m_symbollic_operand) {
					if(!m_current_resolved.is_empty()) {
						utility::console::print("here\n");
						patch p(PATCH_NORMAL);

						p.res.size = m_current_resolved.get_size();
						p.res.data = static_cast<u8*>(m_context.allocator.allocate(m_current_resolved.get_size()));
						utility::memcpy(p.res.data, m_current_resolved.get_data(), m_current_resolved.get_size());

						utility::console::print("here\n");
						m_patches.push_back(p);
						utility::console::print("here\n");
						m_current_resolved.clear();
						utility::console::print("here\n");
					}

					patch p(PATCH_FIXUP);
					p.unres.index = m_unresolved.get_size();
					m_patches.push_back(p);

					m_unresolved.emplace_back(backend.current_variants, variant_index, size, m_instruction_offset, index, m_operands, m_operand_i);
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
		// utility::console::print("[PASS 1]: symbollic operand '{}'\n", *m_current_token.identifier);
		EXPECT_TOKEN(TOK_IDENTIFIER);

		m_operands[m_operand_i++] = operand(m_current_token.identifier); 
		m_symbollic_operand = true;
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
		utility::console::print("[PASS 1]: parsing label   '{}'  {}\n", *m_current_identifier, m_instruction_offset);
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

