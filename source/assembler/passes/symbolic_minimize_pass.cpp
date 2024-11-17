#include "symbolic_minimize_pass.h"

#include "assembler/backend.h"

namespace baremetal::assembler::pass {
	namespace detail {
		auto collect_unresolved_in_section(const section& section) -> utility::dynamic_array<unresolved> {
			utility::dynamic_array<unresolved> indices;

			u64 local_pos = 0;	

			for(u64 i = 0; i < section.blocks.get_size(); ++i) {
				const basic_block* block = section.blocks[i];

				if(!block->is_instruction_block()) {
					continue;
				}

				for(u64 j = 0; j < block->instructions.size; ++j) {
					instruction_data* inst = block->instructions.data[j];

					for(u8 k= 0; k < 4; ++k) {
						auto variants = backend::get_variants_i(inst->index, inst->operands);

						if(inst->operands[k].symbol) {
							const auto symbol_it = section.symbols.find(inst->operands[k].symbol);
	
							auto last = variants.pop_back();
							inst->operands[k].type = last.type;
							inst->index = last.index;
							inst->size = backend::emit_instruction(&instruction_db[inst->index], inst->operands).size;

							if(symbol_it != section.symbols.end()) {
								// we can only optimize references to symbols in the same section
	
								if(!is_operand_rel(inst->operands[k].type)) {
									variants.clear(); // no potential for optimizations
								}

								indices.push_back({ i, j, k, local_pos, variants });
							}
							else {
								// utility::console::print("[sym minimize]: skipping non-local symbol reference to symbol '{}'\n", *inst->operands[k].symbol);
							}
	
							break;
						}
					}

					local_pos += block->instructions.data[j]->size;
				}
			}

			return utility::move(indices);
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
	} // namespace detail

	void symbolic_minimize(module& module) {
		// utility::console::print("[sym minimize]: minimizing {} symbols\n", module.symbols.size());
		
		for(section& section : module.sections) {
			auto unresolved = detail::collect_unresolved_in_section(section);
			bool change = true;

			// utility::console::print("[sym minimize]: section '{}': found {} unresolved instructions:\n", *section.name, unresolved.get_size());

			// resolve and optimize symbol references within each section (we can ignore references to other sections
			// since we'll resolve them during emission)
			while(change) {
				change = false;

				// optimize symbol references, try to use the smallest possible operand
				for(auto& current : unresolved) {
					if(current.variants.is_empty()) {
						// this element is already as optimized as it can be 
						continue;
					}

					instruction_data* current_inst = section.blocks[current.block_index]->instructions.data[current.instruction_index];
					operand& operand = current_inst->operands[current.unresolved_index];
					const auto symbol_it = section.symbols.find(operand.symbol);

					if(symbol_it == section.symbols.end()) {
						// skip symbols which aren't in this section, since we can't optimize them
						continue;
					}

					const i64 distance = symbol_it->second.position - current.position + current_inst->size;
					const operand_type new_type = current.variants.get_last().type;

					if(!pass::detail::fits_into_type(distance, new_type)) {
						// we can't use a smaller operand, no optimization possible in this iteration
						continue;
					}

					// use the next smallest operand instead
					operand.type = new_type;

					u8 new_size = backend::emit_instruction(&instruction_db[current.variants.get_last().index], current_inst->operands).size;

					current_inst->index = current.variants.pop_back().index;
					change = true;

					// update our symbol table to account for the difference in code length
					for(auto& [sym_name, sym_position] : section.symbols) {
						if(sym_position.position > current.position) {
							sym_position.position -= current_inst->size - new_size;
						}	
					}

					for(auto& u : unresolved) {
						if(u.position > current.position) {
							u.position -= current_inst->size - new_size;
						}
					}
					
					current_inst->size = new_size;

					// TODO: investigate whether it's better to break immediately or continue
					break;
				}
			}
		}
	}
} // namespace baremetal::assembler::pass
