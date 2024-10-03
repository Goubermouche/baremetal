#include "assembler_backend.h"
#include "assembler/instruction/instruction.h"
#include "assembler/instruction/operands/operands.h"
#include "utility/types.h"

#include <utility/algorithms/sort.h>

#include "assembler/backend.h"

namespace baremetal {
	namespace detail {
		auto sign_extend_representable(u64 value, u8 src) -> bool {
			const uint64_t mask = (1ULL << src) - 1;
			const u64 shrunk = value & mask;

			const u64 extended_source   = sign_extend(shrunk, src);
			const u64 extended_original = sign_extend(value, 64);

			return extended_source == extended_original;
		}

		auto sign_extend(u64 x, u8 x_bits) -> u64 {
			if(x >> (x_bits - 1)) {
				// u8 diff = n - x_bits;
				return x | (utility::limits<u64>::max() << x_bits);
			}

			return x;
		}

		auto is_operand_of_same_kind(operand_type a, operand_type b) -> bool {
			switch(a) {
				// don't just consider regular equalities, focus on register bit widths as well
				case OP_AL:  return b == OP_AL  || b == OP_CL  || b == OP_R8;  // 8 bits
				case OP_AX:  return b == OP_AX  || b == OP_DX  || b == OP_R16; // 16 bits
				case OP_EAX: return b == OP_EAX || b == OP_ECX || b == OP_R32; // 32 bits
				case OP_RAX: return b == OP_RAX || b == OP_RCX || b == OP_R64; // 64 bits
				case OP_REL_UNKNOWN: return is_operand_rip_rel(b);
				default: return a == b; // regular compares
			}
		}


	} // namespace detail

	assembler_backend::assembler_backend(assembler_context* context)
		: m_current_inst_begin(0), m_module(context) {}

	void assembler_backend::clear() {
		m_module.clear();
		m_current_inst_begin = 0;
	}

	auto assembler_backend::get_bytes() const -> utility::dynamic_array<u8> {
		return m_module.emit_binary();
	}

	auto assembler_backend::get_instruction_size(u32 index, const operand* operands) -> u8 {
		assembler_context temp;
		assembler_backend backend(&temp);

		backend.emit_instruction_direct(assembler_backend::find_direct(index, operands), operands);

		return backend.get_module().get_size_current_section();
	}
	void assembler_backend::emit_instruction(u32 index, const operand* operands) {
		// locate the actual instruction we want to assemble (this doesn't have to match the specified
		// index, since we can apply optimizations which focus on stuff like shorter encodings)
		const instruction* inst = find_optimized_instruction(index, operands);
		emit_instruction_direct(inst, operands);
	}

	void assembler_backend::emit_instruction_direct(const instruction* inst, const operand* operands) {
		// mark the instruction start
		auto c = backend::emit_instruction(inst, operands, false);

		for(u8 i = 0; i < c.size; ++i) {
			push_byte(c.data[i]);
		}
	}

	auto assembler_backend::get_module() -> module& {
		return m_module;
	}

	auto assembler_backend::find_direct(u32 index, const operand* operands) -> const instruction* {
		const instruction& first = instruction_db[index];
		u8 operand_count = 0;

		for(operand_count = 0; operand_count< 4; ++operand_count) {
			// utility::console::print("is {}\n", operand_type_to_string(operands[operand_count].type));
			if(operands[operand_count].type == OP_NONE) {
				break;
			}
		}

		// utility::console::print("enter\n");

		while(utility::compare_strings(first.name, instruction_db[index].name) == 0) {
			// utility::console::print("iter\n");
			const instruction& other = instruction_db[index++];

			if(operand_count != other.operand_count) {
				// utility::console::print("{}\n", operand_count);
				continue;
			}

			for(u8 i = 0; i < operand_count; ++i) {
				if(other.operands[i] != operands[i].type) {
					// utility::console::print("{} vs {}\n", operand_type_to_string(other.operands[i]), operand_type_to_string(operands[i].type));
					goto end;
				}
			}

			return &other;

	end:
			continue;
		}


		ASSERT(false, "invalid instruction match");
		return nullptr;
	}

	auto assembler_backend::find_optimized_instruction(u32 index, const operand* operands)  -> const instruction* {
		u8 imm_index = utility::limits<u8>::max();
		u8 unknown_index = utility::limits<u8>::max();

		// locate the first immediate operand
		for(u8 i = 0; i < 4; ++i) {
			if(is_operand_imm(operands[i].type)) {
				imm_index = i;
				break;
			}
		}

		for(u8 i = 0; i < 4; ++i) {
			if(operands[i].unknown) {
				unknown_index = i;
				break;
			}
		}

		// no immediate operand, return the original variant
		if(imm_index == utility::limits<u8>::max() && unknown_index == utility::limits<u8>::max()) {
			return &instruction_db[index];
		}

		// store a list of legal variants, from which we'll pick the best one
		utility::dynamic_array<const instruction*> legal_variants = {};
		const imm& imm_op = operands[imm_index].immediate;

		// some instructions have a special optimization index, check if we have it
		// if we have a valid context index, the original index, provided as a parameter, will
		// be replaced by this index
		if(instruction_db[index].has_special_index() && unknown_index == utility::limits<u8>::max()) {
			const u16 context_index = instruction_db[index].get_special_index();

			// switch on the context kind
			switch(instruction_db[index].get_special_kind()) {
				case 0: {
					// if we have a destination which uses a 64 bit register, and an operand which fits into 32 bits or
					// less we can look for a smaller destination
					if(operands[0].type == OP_R64 && imm_op.min_bits <= 32) {
						// verify if it's safe to zero extend the operand (since we're implicitly going from 32 to 64
						// bits) we can't zero extend 
						if(imm_op.sign == false) {
							index = context_index;
						}
					}

					break;
				}
				case 1: {
					// if we have a source operand which is equal to 1, we can use a shorter encoding, in basically all
					// cases we can just return, since the operand is effectively removed
					if(operands[1].immediate.value == 1) {
						return &instruction_db[context_index];
					}

					break; // we're not using the optimization index, continue
				}
				case 2: {
					// truncate to 8 bits, this is only used with imul instructions
					const u64 truncated = operands[2].immediate.value & 0b011111111;
					const u64 extend = detail::sign_extend(truncated, 8);

					if(extend == operands[2].immediate.value) {
						return &instruction_db[context_index];
					}

					break;
				}
				default: {
					ASSERT(false, "unknown context kind");
				}
			}
		}

		u32 current_index = index; // index of the current variant

		// locate all legal variants of our instruction, since our instructions are sorted
		// by their operands we can just increment the index as long as the two variants
		// are legal
		u8 imm_or_unresolved = imm_index == utility::limits<u8>::max() ? unknown_index : imm_index;

		if(imm_index != utility::limits<u8>::max()) {
			while(is_legal_variant(index, current_index, imm_index)) {
				legal_variants.push_back(&instruction_db[current_index++]);
			}
		}
		else {
			while(is_legal_variant_unknown(index, current_index, unknown_index)) {
				legal_variants.push_back(&instruction_db[current_index++]);
			}
		}

		// one legal variant
		if(legal_variants.get_size() == 1) {
			current_variants.push_back(legal_variants[0]->operands[unknown_index]);
			return legal_variants[0];
		}

		// sort by the smallest source operands, we need to do this for cases where one of the
		// variants has a destination operand which isn't a generic register, but a specific
		// one (ie. an ax register). In these cases we lose the guarantee of them being sorted
		// from smallest to biggest immediate operands, hence we have to sort them.
		utility::stable_sort(legal_variants.begin(), legal_variants.end(), [=](auto a, auto b) {
			const u16 a_width = get_operand_bit_width(a->operands[imm_or_unresolved]);
			const u16 b_width = get_operand_bit_width(b->operands[imm_or_unresolved]);

			return a_width < b_width;
		});

		for(const auto& inst : legal_variants) {
			current_variants.push_back(inst->operands[unknown_index]);
		}

		if(unknown_index != utility::limits<u8>::max()) {
			ASSERT(!legal_variants.is_empty(), "no variants found\n");
			// largest legal variant - pessimistic 
			return legal_variants.get_last();
		}

		// multiple legal variants, determine the best one (since our data is sorted from smallest
		// source operands to largest, we can exit as soon as we get a valid match)
		for(const instruction* inst : legal_variants) {
			const u16 src_bits = get_operand_bit_width(inst->operands[imm_index]);
			const u16 dst_bits = get_operand_bit_width(inst->operands[0]);

			// check if there is a possibility of sign extending the immediate
			if(src_bits < dst_bits) {
				ASSERT(src_bits <= utility::limits<u8>::max(), "invalid range");

				// assume we're sign extending
				if(detail::sign_extend_representable(imm_op.value, static_cast<u8>(src_bits))) {
					return inst;
				}
			}

			// check if the source operand is representable with a smaller immediate
			if(src_bits >= imm_op.min_bits) {
				return inst;
			}
		}

		ASSERT(false, "invalid instruction match");
		return nullptr;
	}

	auto assembler_backend::is_legal_variant(u32 a, u32 b, u8 imm_index) -> bool {
		const u8 operand_count = instruction_db[a].operand_count;

		if(utility::compare_strings(instruction_db[a].name, instruction_db[b].name) != 0) {
			return false;
		}

		for(u8 i = 0; i < operand_count; ++i) {
			if(i == imm_index) {
				continue;
			}

			if(!detail::is_operand_of_same_kind(instruction_db[a].operands[i], instruction_db[b].operands[i])) {
				return false;
			}
		}

		return is_operand_imm(instruction_db[b].operands[imm_index]) || is_operand_rel(instruction_db[b].operands[imm_index]);
	}

	auto assembler_backend::is_legal_variant_unknown(u32 a, u32 b, u8 imm_index) -> bool {
		const u8 operand_count = instruction_db[a].operand_count;

		if(utility::compare_strings(instruction_db[a].name, instruction_db[b].name) != 0) {
			return false;
		}

		for(u8 i = 0; i < operand_count; ++i) {
			if(i == imm_index) {
				continue;
			}

			if(!detail::is_operand_of_same_kind(instruction_db[a].operands[i], instruction_db[b].operands[i])) {
				return false;
			}
		}

		return 
			is_operand_imm(instruction_db[b].operands[imm_index]) || 
			is_operand_rel(instruction_db[b].operands[imm_index]) || 
			is_operand_mem(instruction_db[b].operands[imm_index]); 
	}
	
	void assembler_backend::push_byte(u8 value) {
		m_module.push_byte(value);
	}

	void assembler_backend::push_data(u64 value, u8 count) {
		for(u8 i = 0; i < count; ++i) {
      u8 byte = static_cast<u8>(value & 0xFF);
      push_byte(byte);
      value >>= 8;
    }
	}
} // namespace baremetal

