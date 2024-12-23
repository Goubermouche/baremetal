#include "symbolic_minimize_pass.h"

#include "assembler/backend.h"

namespace baremetal::assembler::pass {
	namespace detail {
		auto collect_unresolved_symbols(const section& section) -> utility::dynamic_array<unresolved_symbol> {
			utility::dynamic_array<unresolved_symbol> unresolved;
			u64 local_pos = 0;

			// for every instruction block in this section
			for(u64 i = 0; i < section.blocks.get_size(); ++i) {
				const basic_block* block = section.blocks[i];

				if(!block->is_instruction_block()) {
					continue;
				}

				// check for symbolic references in all instructions
				// TODO: collect these references when constructing the module?
				for(u64 j = 0; j < block->instructions.size; ++j) {
					instruction_data* inst = block->instructions.data[j];

					for(u8 k= 0; k < 4; ++k) {
						auto variants = backend::get_variants_i(inst->index, inst->operands);

						// skip operands which don't have a symbol
						if(inst->operands[k].symbol == nullptr) {
							continue;
						}

						const auto symbol_it = section.symbols.find(inst->operands[k].symbol);
						
						auto last = variants.pop_back();
						inst->operands[k].type = last.type;
						inst->index = last.index;
						inst->size = backend::emit_instruction(&g_instruction_db[inst->index], inst->operands).size;

						// we can only optimize references to symbols in the same section
						if(symbol_it == section.symbols.end()) {
							break;
						}

						// right now we can only optimize relative offsets
						if(!is_operand_rel(inst->operands[k].type)) {
							break;
						}

						unresolved.push_back({ i, j, k, local_pos, variants });
						
						// TODO: we can't optimize multiple symbols per instruction yet
						break;
					}

					local_pos += block->instructions.data[j]->size;
				}
			}

			return utility::move(unresolved);
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
		
		void shift_symbols(section& section, u64 position, i64 shift) {
			for(auto& [sym_name, sym_position] : section.symbols) {
				if(sym_position.position > position) {
					sym_position.position -= shift;
				}
			}
		}

		void shift_unresolved(utility::dynamic_array<unresolved_symbol>& unresolved, u64 position, i64 shift) {
			for(auto& u : unresolved) {
				if(u.position > position) {
					u.position -= shift;
				}
			}
		}
	} // namespace detail

	void symbolic_minimize(module& module) {
		// minimize individual sections (we can't optimize symbolic references across sections) 
		for(section& section : module.sections) {
			auto unresolved = detail::collect_unresolved_symbols(section);
			bool change = true;

			// resolve and optimize symbol references within each section
			while(change) {
				change = false;

				// optimize symbol references, try to use the smallest possible operand
				for(auto& current : unresolved) {
					if(current.variants.is_empty()) {
						// this element is already as optimized as it can be 
						continue;
					}

					basic_block* current_block = section.blocks[current.block_index];
					instruction_data* current_inst = current_block->instructions.data[current.instruction_index];
					operand& operand = current_inst->operands[current.unresolved_index];
					const auto symbol_it = section.symbols.find(operand.symbol);

					// we shouldn't receive symbols from different sections
					ASSERT(symbol_it != section.symbols.end(), "symbol from a different section received\n");

					// calculate the distance to the target symbol
					const i64 distance = symbol_it->second.position - current.position + current_inst->size;
					const operand_type new_type = current.variants.get_last().type;

					if(!pass::detail::fits_into_type(distance, new_type)) {
						// we can't use a smaller operand, no optimization possible in this iteration
						continue;
					}

					// success, we can use the smaller variant
					operand.type = new_type;

					const instruction* inst = &g_instruction_db[current.variants.get_last().index];
					const u8 new_size = backend::emit_instruction(inst, current_inst->operands).size;

					// update our symbol table to account for the difference in code length
					detail::shift_symbols(section, current.position, current_inst->size - new_size);
					detail::shift_unresolved(unresolved, current.position, current_inst->size - new_size);

					current_inst->index = current.variants.pop_back().index;
					current_inst->size = new_size;
					change = true;

					// TODO: investigate whether it's better to break immediately or continue
					break;
				}
			}
		}
	}
} // namespace baremetal::assembler::pass
