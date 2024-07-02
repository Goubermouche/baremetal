#include "assembler.h"

#include "instruction/operands/operands.h"

#include <utility/algorithms/sort.h>
#include <utility/assert.h>

namespace baremetal {
	assembler::assembler() : m_current_inst_begin(0) {}

	auto assembler::get_bytes() const -> const utility::dynamic_array<utility::byte>& {
		return m_bytes;
	}

	auto assembler::find_rex_pair(const operand* operands) -> std::pair<u8, u8> {
		// locate the first registers from the back
		std::pair<u8, u8> result = { 0, 0 };
		i8 i = 4;

		while(i-- > 0) {
			if(is_operand_reg(operands[i].type)) {
				result.first = operands[i].reg;
				result.second = operands[i].reg;
				break;
			}
		}

		while(i-- > 0) {
			if(is_operand_reg(operands[i].type)) {
				result.second = operands[i].reg;
				break;
			}
		}

		return result;
	}

	auto assembler::find_instruction_info(u32 index, const operand& op1, const operand& op2, const operand& op3, const operand& op4)  -> const instruction_info* {
		// instruction optimizations are only applicable if the last operand is an immediate
		if(is_operand_imm(op2.type) == false) {
			return &instruction_db[index];
		}

		// store a list of legal variants, from which we'll pick the best one
		utility::dynamic_array<const instruction_info*> legal_variants = {};
		const u8 source_bit_width = get_operand_bit_width(op2.type);
		const imm& source = op2.immediate;

		// some instructions have a special optimization index, check if we have it
		// if we have a valid context index the original index, provided as a parameter, will
		// be replaced by this index
		if(instruction_db[index].context_index != std::numeric_limits<u16>::max()) {
			//           [1111111111111111] (65535) is an invalid index => that instruction does not have one
			// kind      [XX______________]
			// index     [__XXXXXXXXXXXXXX]

			const u16 context = instruction_db[index].context_index;
			const u8 kind = static_cast<u8>(context >> 14);
			const u16 context_index = context & 0b0011111111111111;

			switch(kind) {
				case 0: {
					// if we have a destination which uses a 64 bit register, and an operand which fits into 32 bits or
					// less we can look for a smaller destination
					if(op1.type == operand::OP_REG64 && source.min_bits <= 32) {
						// verify if it's safe to zero extend the operand (since we're implicitly going from 32 to 64
						// bits) we can't zero extend 
						if(source.sign == false) {
							index = context_index;
						}
					}

					break;
				}
				case 1: {
					// if we have a source operand which is equal to 1, we can use a shorter encoding, in basically all
					// cases we can just return, since the operand is effectively removed
					if(op2.immediate.value == 1) {
						return &instruction_db[context_index];
					}

					break; // we're not using the optimization index, continue
				}
				default: {
					utility::console::print_err("unknown context kind specified ({})\n", kind);
				}
			}
		}

		u32 current_index = index; // index of the first variant

		// locate all legal variants of our instruction
		while(is_operand_of_same_kind(instruction_db[index].operands[0], instruction_db[current_index].operands[0])) {
			if(is_operand_imm(instruction_db[current_index].operands[1])) {
				legal_variants.push_back(&instruction_db[current_index++]);
			}
			else {
				break;
			}
		}

		// sort by the smallest source operands
		utility::stable_sort(legal_variants.begin(), legal_variants.end(), [](const instruction_info* a, const instruction_info* b) {
			return get_operand_bit_width(a->operands[1]) < get_operand_bit_width(b->operands[1]);
		});

		if(legal_variants.get_size() == 1) {
			// one legal variant, use that
			return legal_variants[0];
		}

		// multiple legal variants, determine the best one (since our data is sorted from smallest
		// source operands to largest, we can exit as soon as we get a valid match)
		for(const instruction_info* i : legal_variants) {
			const u8 current_source_bits = get_operand_bit_width(i->operands[1]);
			const u8 current_dest_bits = get_operand_bit_width(i->operands[0]);

			// check if there is a possibility of sign extending the immediate
			if(current_source_bits < current_dest_bits) {
				// assume we're sign extending
				if(signed_extend_representable(source.value, source_bit_width, current_dest_bits, current_source_bits)) {
					return i;
				}
			}

			// check if the source operand is representable with a smaller immediate
			if(current_source_bits >= source.min_bits) {
				return i;
			}
		}

		ASSERT(false, "invalid instruction match");
		return nullptr;
	}

	void assembler::emit_instruction_prefix(const instruction_info* inst) {
		if(!inst->has_prefix()) {
			return; // no prefix
		}

		const u8 prefix = inst->prefix;

		// group 4
		if(prefix & ADDRESS_SIZE_OVERRIDE) {
			m_bytes.push_back(0x67);
		}

		// group 3
		if(prefix & OPERAND_SIZE_OVERRIDE) {
			m_bytes.push_back(0x66);
		}

		// group 2
		switch(prefix & 0b00111100) {
			case CS_SEGMENT:       m_bytes.push_back(0x2E); break;
			case SS_SEGMENT:       m_bytes.push_back(0x36); break;
			case DS_SEGMENT:       m_bytes.push_back(0x3E); break;
			case ES_SEGMENT:       m_bytes.push_back(0x26); break;
			case FS_SEGMENT:       m_bytes.push_back(0x64); break;
			case GS_SEGMENT:       m_bytes.push_back(0x65); break;
			case BRANCH_NOT_TAKEN: m_bytes.push_back(0x2E); break;
			case BRANCH_TAKEN:     m_bytes.push_back(0x3E); break;
			default:                                        break;
		}

		// group 1
		switch(prefix & 0b00000011) {
			case LOCK:  m_bytes.push_back(0xF0); break;
			case REPNE: m_bytes.push_back(0xF2); break;
			case REP:   m_bytes.push_back(0xF3); break;
			default:                             break;
		}
	}

	void assembler::emit_instruction_opcode(const instruction_info* inst, const operand& op1, const operand& op2, const operand& op3, const operand& op4) {
		const bool is_rexw = inst->is_rexw();
		const operand operands[4] = { op1, op2, op3, op4 };
		auto [rx, destination] = find_rex_pair(operands);

		// opcode - rex prefix
		if(is_rexw || is_extended_reg(op1) || is_extended_reg(op2)) {
			// extended gp | register
			if(is_extended_gp_reg(op1) && is_operand_reg(op2.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op2.reg, op1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op1.reg, op2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// gp | extended gp
			else if(is_extended_gp_reg(op2) && is_operand_gp_reg(op1.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op2.reg, op1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op1.reg, op2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// extended gp | mem
			else if(is_operand_gp_reg(op1.type) && is_operand_mem(op2.type)) {
				const utility::byte rex_part = rex(is_rexw, op1.reg, op2.memory.base.index, op2.memory.index.index);
				m_bytes.push_back(rex_part);
			}
			// mem | extended gp
			else if(is_operand_mem(op1.type) && is_operand_gp_reg(op2.type)) {
				const utility::byte rex_part = rex(is_rexw, op2.reg, op1.memory.base.index, op1.memory.index.index);
				m_bytes.push_back(rex_part);
			}
			// extended xmm | xmm
			else if(is_extended_xmm_reg(op1) && is_operand_xmm(op2.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op2.reg, op1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op1.reg, op2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// xmm | extended xmm
			else if(is_extended_xmm_reg(op2) && is_operand_xmm(op1.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op2.reg, op1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op1.reg, op2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// extended xmm | gp
			else if(is_extended_xmm_reg(op1) && is_operand_gp_reg(op2.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op2.reg, op1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op1.reg, op2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// gp | extended xmm
			else if(is_extended_xmm_reg(op2) && is_operand_gp_reg(op1.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op2.reg, op1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op1.reg, op2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// extended xmm | imm
			else if(is_extended_xmm_reg(op1) && is_operand_imm(op2.type)) {
				const utility::byte rex_part = rex(is_rexw, 0, op1.reg, 0);
				m_bytes.push_back(rex_part);
			}
			else if(is_extended_xmm_reg(op1) && is_operand_mem(op2.type)) {
				const utility::byte rex_part = rex(is_rexw, op1.reg, op2.memory.base.index, op2.memory.index.index);
				m_bytes.push_back(rex_part);
			}
			else if(is_extended_xmm_reg(op2) && is_operand_mem(op1.type)) {
				const utility::byte rex_part = rex(is_rexw, op2.reg, op1.memory.base.index, op1.memory.index.index);
				m_bytes.push_back(rex_part);
			}
			else if(is_extended_xmm_reg(op2) && is_operand_reg(op1.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op2.reg, op1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op1.reg, op2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			else if(is_extended_xmm_reg(op1) && is_operand_reg(op2.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op2.reg, op1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op1.reg, op2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// gp | xmm
			else if(is_operand_gp_reg(op1.type) && is_operand_xmm(op2.type)) {
				const utility::byte rex_part = rex(is_rexw, op2.reg, op1.reg, 0);
				m_bytes.push_back(rex_part);
			}
			// x | creg
			else if(is_operand_creg(op2.type)) {
				const utility::byte rex_part = rex(is_rexw, op2.reg, op1.reg, 0);
				m_bytes.push_back(rex_part);
			}
			// creg | x
			else if(is_operand_creg(op1.type)) {
				const utility::byte rex_part = rex(is_rexw, op1.reg, op2.reg, 0);
				m_bytes.push_back(rex_part);
				}
			// reg x
			else if(is_operand_gp_reg(op1.type)) {
				const utility::byte rex_part = rex(is_rexw, 0, op1.reg, 0);
				m_bytes.push_back(rex_part);
			}
			// x reg
			else if(is_operand_gp_reg(op2.type)) {
				const utility::byte rex_part = rex(is_rexw, 0, op2.reg, 0);
				m_bytes.push_back(rex_part);
			}
			// mem x
			else if(is_operand_mem(op1.type)) {
				const utility::byte rex_part = rex(is_rexw, 0, op1.memory.base.index, op1.memory.index.index);
				m_bytes.push_back(rex_part);
			}
			// mem x
			else if(is_operand_mem(op2.type)) {
				const utility::byte rex_part = rex(is_rexw, 0, op2.memory.base.index, op2.memory.index.index);
				m_bytes.push_back(rex_part);
				}
			// x x
			else {
				const utility::byte rex_part = rex(is_rexw, rx, destination, 0);
				m_bytes.push_back(rex_part);
			}
		}
		else if(is_operand_mem(op1.type)) {
			emit_opcode_mem(op1.memory);
		}
		else if(is_operand_mem(op2.type)) {
			emit_opcode_mem(op2.memory);
		}

		// emit the opcode
		u64 opcode = inst->opcode;

		if(inst->is_opcode_ext()) {
			// extract the 3 least significant bits 
			if(inst->get_direction()) {
				opcode += destination & 0b00000111;
			}
			else {
				opcode += rx & 0b00000111;
			}
		}

		// append opcode bytes
		for(u8 i = 4; i-- > 1;) {
			const u8 byte = (opcode >> (i * 8)) & 0xFF;

			if(byte != 0) {
				m_bytes.push_back(byte);
			}
		}

		// always push the last byte
		const u8 byte = opcode & 0xFF;
		m_bytes.push_back(byte);
	}

	void assembler::emit_opcode_mem(const mem& memory) {
		// extended base
		if((memory.has_base && memory.base.index >= 8) || (memory.has_index && memory.index.index >= 8)) {
			m_bytes.push_back(rex(false, 0, memory.base.index, memory.index.index));
		}
	}

	void assembler::emit_operands(const operand* operands, u8 operand_count, const instruction_info* inst) {
		for(u8 i = 0; i < operand_count; ++i) {
			if(is_operand_imm(operands[i].type)) {
				// immediate operand
				emit_data_operand(operands[i].immediate.value, get_operand_bit_width(inst->operands[i]));
			}
			else if(is_operand_moff(operands[i].type)) {
				// memory offset operand (always 64-bit)
				emit_data_operand(operands[i].memory_offset.value, 64);
			}
			else if(is_operand_mem(operands[i].type)) {
				// memory displacement operand
				const mem memory = operands[i].memory;
				imm displacement = memory.displacement;

				if(displacement.value == 0) {
					if(memory.has_base && memory.base.type != REG_RIP) {
						continue; // skip 0 displacements
					}
				}

				// determine the displacement size
				enum operand::type ty;

				if(memory.has_base == false) {
					ty = operand::type::OP_I32;
				}
				else if(memory.base.type == REG_RIP) {
					// calculate the relative (rip) offset
					ty = operand::type::OP_I32;

					// beginning of the instruction
					i32 new_displacement = static_cast<i32>(displacement.value - (get_current_inst_size() + 4));

					if(i + 1 != operand_count) {
						// if we have another operand after the current one, calculate it's size
						if(is_operand_imm(inst->operands[i + 1])) { // registers are already encoded
							new_displacement -= get_operand_bit_width(inst->operands[i + 1]) / 8;
						}
					}

					displacement = imm(new_displacement);
				}
				else if(displacement.min_bits <= 8) {
					ty = operand::type::OP_I8;
				}
				else {
					ty = operand::type::OP_I32;
				}

				emit_data_operand(displacement.value, get_operand_bit_width(ty));
			}
		}
	}

	void assembler::emit_instruction_mod_rm(const instruction_info* inst, const operand& op1, const operand& op2, const operand& op3, const operand& op4) {
		const operand operands[4] = { op1, op2, op3, op4 };
		auto [rx, destination] = find_rex_pair(operands);

		// mod rm / sib
		if(inst->is_r() || is_operand_mem(op1.type) || is_operand_mem(op2.type)) {
			utility::byte mod_rm_part;

			if(is_operand_mem(op1.type)) {
				const bool has_sib = has_sib_byte(op1, op2);
				const auto memory = op1.memory;

				ASSERT(memory.displacement.min_bits <= 32, "too many displacement bits");

				// right mem
				if(memory.has_base == false) {
					// absolute address
					if(inst->is_ext()) {
						mod_rm_part = indirect(inst->get_ext(), 0b100);
					}
					else {
						// this may not be needed
						mod_rm_part = indirect(rx, 0b100); // 100 = SIB byte
					}
				}
				else if(memory.base.type == REG_RIP) {
					// rip reg
					if(inst->is_ext()) {
						mod_rm_part = indirect(inst->get_ext(), 0b101);
					}
					else {
						mod_rm_part = indirect(rx, 0b101); // 101 = RIP-relative
					}
				}
				else if(memory.displacement.value == 0) {
					// no displacement
					if(inst->is_ext()) {
						mod_rm_part = indirect(inst->get_ext(), has_sib ? 0b100 : memory.base.index);
					}
					else {
						mod_rm_part = indirect(rx, has_sib ? 0b100 : memory.base.index);
					}
				}
				else if(memory.displacement.min_bits <= 8) {
					// 8 bit displacement
					if(inst->is_ext()) {
						mod_rm_part = indirect_disp_8(inst->get_ext(), has_sib ? 0b100 : memory.base.index);
					}
					else {
						mod_rm_part = indirect_disp_8(rx, has_sib ? 0b100 : memory.base.index);
					}

				}
				else {
					// 32 bit displacement
					if(inst->is_ext()) {
						mod_rm_part = indirect_disp_32(inst->get_ext(), has_sib ? 0b100 : memory.base.index);
					}
					else {
						mod_rm_part = indirect_disp_32(rx, has_sib ? 0b100 : memory.base.index);
					}
				}
			}
			else if(is_operand_mem(op2.type)) {
				const bool has_sib = has_sib_byte(op1, op2);
				const auto memory = op2.memory;

				ASSERT(memory.displacement.min_bits <= 32, "too many displacement bits");

				// right mem
				if(memory.has_base == false) {
					// absolute address
					mod_rm_part = indirect(rx, 0b100); // 100 = SIB byte
				}
				else if(memory.base.type == REG_RIP) {
					// rip reg
					mod_rm_part = indirect(rx, 0b101); // 101 = RIP-relative
				}
				else if(memory.displacement.value == 0) {
				// no displacement
				mod_rm_part = indirect(rx, has_sib ? 0b100 : memory.base.index);
				}
				else if(memory.displacement.min_bits <= 8) {
					// 8 bit displacement
					mod_rm_part = indirect_disp_8(rx, has_sib ? 0b100 : memory.base.index);
				}
				else {
					// 32 bit displacement
					mod_rm_part = indirect_disp_32(rx, has_sib ? 0b100 : memory.base.index);
				}
			}
			else {
				if(inst->get_direction()) {
					mod_rm_part = direct(rx, destination);
				}
				else {
					mod_rm_part = direct(destination, rx);
				}
			}

			m_bytes.push_back(mod_rm_part);
		}
		else if(inst->is_ext()) {
			m_bytes.push_back(direct(inst->get_ext(), destination));
		}
	}

	void assembler::emit_instruction_sib(const operand& op1, const operand& op2) {
		mem memory;

		if(is_operand_mem(op1.type)) {
			memory = op1.memory;
		}
		else if(is_operand_mem(op2.type)) {
			memory = op2.memory;
		}
		else {
			return; // no sib byte
		}

		const u8 scale = memory.has_base  ? memory.scale       : 0b00;
		const u8 index = memory.has_index ? memory.index.index : 0b100;
		const u8 base   = memory.has_base ? memory.base.index  : 0b101;

		if(memory.has_index || is_stack_pointer(reg(memory.base)) || memory.has_base == false) {
			m_bytes.push_back(sib(scale, index, base));
		}
	}

	void assembler::emit_instruction(u32 index, const operand& op1, const operand& op2, const operand& op3, const operand& op4) {
		// NOTE: operand count can be inferred from overloaded functions

		instruction_begin(); // mark the instruction start (used for rip-relative addressing)

		// locate the actual instruction we want to assemble (this doesn't have to match the specified
		// index, since we can apply optimizations which focus on stuff like shorter encodings)
		const instruction_info* inst = find_instruction_info(index, op1, op2, op3, op4);

		const u8 operand_count = inst->get_operand_count(); // TODO: infer this
		const operand operands[4] = { op1, op2, op3, op4 }; // TODO: pass this instead of the individual operands

		// emit instruction parts
		emit_instruction_prefix(inst);
		emit_instruction_opcode(inst, op1, op2, op3, op4);
		emit_instruction_mod_rm(inst, op1, op2, op3, op4);
		emit_instruction_sib(op1, op2);

		// emit immediate, displacement, and memory offset operands
		emit_operands(operands, operand_count, inst);
	}

	auto assembler::has_sib_byte(const operand& op1, const operand& op2) -> bool {
		mem memory;

		if(is_operand_mem(op1.type)) {
			memory = op1.memory;
		}
		else if(is_operand_mem(op2.type)) {
			memory = op2.memory;
		}
		else {
			return false;
		}

		if(memory.has_index) {
			return true;
		}

		if(is_stack_pointer(reg(memory.base))) {
			return true;
		}

		if(memory.has_base == false) {
			return true; // absolute address
		}

		return false;
	}

	void assembler::emit_data_operand(u64 data, u8 bit_width) {
		for(u8 i = 0; i < bit_width / 8; ++i) {
			m_bytes.push_back(data >> (i * 8) & 0xFF);
		}
	}

	auto assembler::sib(u8 scale, u8 index, u8 base) -> u8 {
		ASSERT(scale <= 3, "invalid scale");

		// scale [XX______]
		// index [__XXX___]
		// base  [_____XXX]

		return static_cast<u8>((scale << 6) | ((index & 0x7) << 3) | (base & 0x7));
	}

	auto assembler::rex(bool w, u8 rx, u8 base, u8 index) -> u8 {
		ASSERT(rx < 16, "invalid rx");
		ASSERT(base < 16, "invalid base");
		ASSERT(index < 16, "invalid index");

		// whenever a used register is larger than 3 bits we need to mark the extension bit
		// the result will then be extended in mod R/M or the SIB byte.

		//                                     rex WRXB
		// rex prefix                         [0100____]
		// w (64 bit mode)                    [____X___]
		// r (mod R/M extension) (rx > RDI)   [_____X__]
		// x (sib extension) (index > RDI)    [______X_]
		// b (mod R/M extension) (base > RDI) [_______X]

		const u8 index_mask = static_cast<u8>((index >> 3) << 1);
		const u8 rx_mask = static_cast<u8>((rx >> 3) << 2);
		const u8 w_mask = static_cast<u8>(w << 3);
		const u8 base_mask = base >> 3;

		return 0x40 | base_mask | index_mask | rx_mask | w_mask;
	}

	auto assembler::mod_rx_rm(u8 mod, u8 rx, u8 rm) -> u8 {
		ASSERT(mod < 4, "invalid mod");
		ASSERT(rx < 16, "invalid rx");
		ASSERT(rm < 16, "invalid rm");

		// registers 0 - 7  primary registers
		// registers 8 - 16 extended registers

		// mod  [XX______] (addressing mode)
		// rx   [__XXX___]
		// rm   [_____XXX]

		return static_cast<u8>((rm & 7) | ((rx & 7) << 3) | (mod << 6));
	}

	auto assembler::direct(u8 rx, u8 reg) -> u8 {
		return mod_rx_rm(DIRECT, rx, reg);
	}

	auto assembler::indirect(u8 rx, u8 base) -> u8 {
		return mod_rx_rm(INDIRECT, rx, base);
	}

	auto assembler::indirect_disp_8(u8 rx, u8 base) -> u8 {
		return mod_rx_rm(INDIRECT_DISP8, rx, base);
	}

	auto assembler::indirect_disp_32(u8 rx, u8 base) -> u8 {
		return mod_rx_rm(INDIRECT_DISP32, rx, base);
	}

	void assembler::instruction_begin() {
		m_current_inst_begin = m_bytes.get_size();
	}

	void assembler::clear() {
		m_bytes.clear();
		m_current_inst_begin = 0;
	}

	auto assembler::get_current_inst_size() const -> u8 {
		return static_cast<u8>(m_bytes.get_size() - m_current_inst_begin);
	}

	auto signed_extend_representable(u64 value, u8 original, u8 dst, u8 src) -> bool {
		const uint64_t mask = (1ULL << src) - 1;
		const u64 shrunk = value & mask;

		const u64 extended_source   = utility::sign_extend(shrunk, src, dst);
		const u64 extended_original = utility::sign_extend(value, original, dst);

		return extended_source == extended_original;
	}

	auto is_operand_of_same_kind(enum operand::type a, enum operand::type b) -> bool {
		switch(a) {
			// don't just consider regular equalities, focus on register bit widths as well
			case operand::OP_AL:  return b == operand::OP_AL  || b == operand::OP_CL  || b == operand::OP_REG8;  // 8 bits
			case operand::OP_AX:  return b == operand::OP_AX  || b == operand::OP_DX  || b == operand::OP_REG16; // 16 bits
			case operand::OP_EAX: return b == operand::OP_EAX || b == operand::OP_ECX || b == operand::OP_REG32; // 32 bits
			case operand::OP_RAX: return b == operand::OP_RAX || b == operand::OP_RCX || b == operand::OP_REG64; // 64 bits
			default: return a == b; // regular compares
		}
	}
} // namespace baremetal
