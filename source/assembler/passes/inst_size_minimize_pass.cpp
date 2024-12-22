#include "inst_size_minimize_pass.h"

#include "assembler/backend.h"
#include <utility/algorithms/sort.h>

namespace baremetal::assembler::pass {
	namespace detail {
		auto get_instruction_using_magic(instruction_data* inst, const imm& imm_op) -> bool {
			ASSERT(g_instruction_db[inst->index].has_magic(), "instruction does not have a magic number\n");
			const u16 context_index = g_instruction_db[inst->index].get_magic_index();

			// switch on the context kind
			switch(g_instruction_db[inst->index].get_magic_kind()) {
				case 0: {
					// if we have a destination which uses a 64 bit register, and an operand which fits into 32 bits or
					// less we can look for a smaller destination
					if(inst->operands[0].type == OP_R64 && imm_op.min_bits <= 32) {
						// verify if it's safe to zero extend the operand (since we're implicitly going from 32 to 64
						// bits) we can't zero extend 
						if(imm_op.sign == false) {
							inst->index = context_index;
							return true;
						}
					}

					break;
				}
				case 1: {
					// if we have a source operand which is equal to 1, we can use a shorter encoding, in basically all
					// cases we can just return, since the operand is effectively removed
					if(inst->operands[1].immediate.value == 1) {
						inst->index = context_index;
						return true;
					}

					break; // we're not using the optimization index, continue
				}
				case 2: {
					// truncate to 8 bits, this is only used with imul instructions
					const u64 truncated = inst->operands[2].immediate.value & 0b011111111;
					const u64 extend = baremetal::assembler::detail::sign_extend(truncated, 8);

					if(extend == inst->operands[2].immediate.value) {
						inst->index = context_index;
						return true;
					}

					break;
				}
				default: ASSERT(false, "unknown context kind");
			}

			return false;
		}

		void optimize_instruction_size(instruction_data* inst) {
			u8 operand_index = utility::limits<u8>::max();
			bool has_unresolved = false;
	
			// locate the first unresolved/immediate operand
			for(u8 i = 0; i < 4; ++i) {
				if(is_operand_imm(inst->operands[i].type)) {
					operand_index = i;
					break;
				}
				else if(inst->operands[i].unknown) {
					has_unresolved = true;
					operand_index = i;
					break;
				}
			}
	
			if(operand_index == utility::limits<u8>::max()) {
				// no 'special' operand which we could optimize, return
				return;
			}
	
			const imm& imm_op = inst->operands[operand_index].immediate;
			u32 legal_variants[5];
			u8 legal_variants_index = 0;
	
			// some instructions have a special optimization index, check if we have it
			if(g_instruction_db[inst->index].has_magic() && has_unresolved == false) {
				if(get_instruction_using_magic(inst, imm_op)) {
					return;
				}
			}
	
			// locate all legal variants of our instruction
			u32 current_index = inst->index;
	
			while(is_legal_variant(inst->index, current_index, operand_index)) {
				legal_variants[legal_variants_index++] = current_index++;
			}
	
			// sort by the smallest source operands, we need to do this for cases where one of the
			// variants has a destination operand which isn't a generic register, but a specific
			// one (ie. an ax register). In these cases we lose the guarantee of them being sorted
			// from smallest to biggest immediate operands, hence we have to sort them.
			utility::stable_sort(legal_variants, legal_variants + legal_variants_index, [=](auto a, auto b) {
				const instruction* a_inst = &g_instruction_db[a];
				const instruction* b_inst = &g_instruction_db[b];
	
				const u16 a_width = get_operand_bit_width(a_inst->operands[operand_index]);
				const u16 b_width = get_operand_bit_width(b_inst->operands[operand_index]);
	
				return a_width < b_width;
			});

			if(has_unresolved) {
				// instructions with unresolved operands can just use the largest variant
				ASSERT(legal_variants_index > 0, "no variants found\n");
				inst->index = legal_variants[legal_variants_index - 1];
				return;
			}

			// multiple legal variants, determine the best one (since our data is sorted from smallest
			// source operands to largest, we can exit as soon as we get a valid match)
			for(u32 index : legal_variants) {
				const instruction* curr = &g_instruction_db[index];

				const u16 src_bits = get_operand_bit_width(curr->operands[operand_index]);
				const u16 dst_bits = get_operand_bit_width(curr->operands[0]);

				// check if there is a possibility of sign extending the immediate
				if(src_bits < dst_bits) {
					ASSERT(src_bits <= utility::limits<u8>::max(), "invalid bit range\n");

					// assume we're sign extending
					if(baremetal::assembler::detail::sign_extend_representable(imm_op.value, static_cast<u8>(src_bits))) {
						inst->index = index;
						return;
					}
				}

				// check if the source operand is representable with a smaller immediate
				if(src_bits >= imm_op.min_bits) {
					inst->index = index;
					return;
				}
			}

			ASSERT(false, "faulty instruction received\n");
		}
	} // namespace detail

	void inst_size_minimize(module& module) {
		// utility::console::print("[inst minimize]: minimizing {} blocks\n", module.blocks.get_size());
		for(const section& section : module.sections) {
			for(const basic_block* block : section.blocks) {
				if(!block->is_instruction_block()) {
					continue;
				}

				for(u64 i = 0; i < block->instructions.size; ++i) {
					instruction_data* inst = block->instructions.data[i];
					u32 old_index = inst->index;
					detail::optimize_instruction_size(inst);

					if(inst->index != old_index) {
						// HACK: recalculate the size, this needs to be done in a different way
						u8 old_size = inst->size;
						inst->size = backend::emit_instruction(&g_instruction_db[inst->index], inst->operands).size;
	
						if(old_size > inst->size) {
							ASSERT(inst->size <= old_size, "[inst minimize]: minimized instruction is bigger than the original variant {} -> {}\n", old_size, inst->size);
							// utility::console::print("[inst minimize]: inst minimized {}B -> {}B\n", old_size, inst->size);
						}
					}
				}
			}
		}

		module.recalculate_block_sizes();
	}
} // namespace baremetal::assembler::pass
