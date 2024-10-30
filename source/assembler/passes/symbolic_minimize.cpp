#include "symbolic_minimize.h"
#include "assembler/backend.h"

namespace baremetal::assembler::pass {
	void symbolic_minimize(module_t& module) {
		struct unresolved {
			u64 block_index;
			u64 instruction_index;
			u8 unresolved_index;
			u64 position;
			utility::dynamic_array<inst_variant> variants;
		};


		utility::dynamic_array<unresolved> indices;

		// locate all references to symbols
		for(u64 i = 0; i < module.m_blocks.get_size(); ++i) {
			const instruction_block* block = module.m_blocks[i];

			for(u64 j = 0; j < block->size; ++j) {
				instruction_t* inst = block->instructions[j];
				u64 local_position = 0;

				for(u8 k = 0; k < 4; ++k) {
					if(inst->operands[k].symbol) {
						const auto symbol_it = module.m_symbols.find(inst->operands[k].symbol);

						if(symbol_it->second.section_index == block->section_index) {
							// we can only optimize references to symbols in the same section
							auto variants = backend::get_variants_i(inst->index, inst->operands);

							auto last = variants.pop_back();
							inst->operands[k].type = last.type;
							inst->index = last.index;
							inst->size = backend::emit_instruction(&instruction_db[inst->index], inst->operands).size;

							if(!is_operand_rel(inst->operands[k].type)) {
								variants.clear(); // no potential for optimizations
							}

							indices.push_back({i, j, k, local_position, variants });
						}
						else {
							utility::console::print("[SYMRES] skipping non-local symbol reference to symbol '{}'\n", *inst->operands[k].symbol);
						}

						break;
					}
				}

				local_position += inst->size;
			}
		}

		utility::console::print("[SYMRES] found {} unresolved symbols:\n", indices.get_size());

		for(const auto& unres : indices) {
			instruction_t* current_inst = module.m_blocks[unres.block_index]->instructions[unres.instruction_index];
			operand& unresolved = current_inst->operands[unres.unresolved_index];
			utility::console::print("[SYMRES] '{}' ({} variants)\n", *unresolved.symbol, unres.variants.get_size());
		}

		bool change = true;
		module.recalculate_block_sizes();

		// greedy optimizations
		while(change) {
			change = false;

			for(unresolved& unres : indices) {
				if(unres.variants.is_empty()) {
					continue;
				}

				instruction_t* current_inst = module.m_blocks[unres.block_index]->instructions[unres.instruction_index];
				operand& unresolved = current_inst->operands[unres.unresolved_index];
				const auto symbol_it = module.m_symbols.find(unresolved.symbol);

				const i64 distance = symbol_it->second.position - unres.position + current_inst->size;
				const operand_type new_type = unres.variants.get_last().type;

				if(!fits_into_type(distance, new_type)) {
					// we can't use a smaller operand, no optimization possible in this iteration
					continue;
				}
				
				// use the next smallest operand instead
				unresolved.type = new_type;
				
				u8 new_size = backend::emit_instruction(&instruction_db[unres.variants.get_last().index], current_inst->operands).size;

				utility::console::print("[SYMRES] reference to '{}' optimized {} -> {}\n", *unresolved.symbol, current_inst->size, new_size);
				
				current_inst->size = new_size;
				current_inst->index = unres.variants.get_last().index;
				change = true;

				unres.variants.pop_back();

				// update our symbol table to account for the difference in code length
				module.recalculate_block_sizes(); // TODO: don't recalculate everything

				// TODO: investigate whether it's better to break immediately or to continue
				break;
			}
		}
	}
} // namespace baremetal::assembler::pass
