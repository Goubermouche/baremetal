#include "assembler.h"

#include <algorithm>

#include "instruction/operands/operands.h"
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

	auto is_extended_reg(operand op) -> bool {
		if(is_operand_reg(op.type)) {
			return op.reg >= 8;
		}

		return false;
	}

	auto is_extended_xmm_reg(operand op) -> bool {
		if(is_operand_xmm(op.type)) {
			return op.reg >= 8;
		}

		return false;
	}

	auto is_extended_gp_reg(operand op) -> bool {
		if(is_operand_gp_reg(op.type)) {
			return op.reg >= 8;
		}

		return false;
	}

	u64 sign_extend(u64 x, u8 x_bits, u8 n) {
		const bool sign = (x >> (x_bits - 1)) & 1;

		// utility::console::print("sign {}\n", (int)sign);

		if(sign) {
			x |= ((std::numeric_limits<u64>::max()) << x_bits) >> n;
		}

		return x;
	}

	static auto signed_extend_representable(u64 value, u8 original, u8 dst, u8 src) -> bool {
		const uint64_t mask = (1ULL << src) - 1;
		const u64 shrunk = value & mask;

		const u64 extended_source   = sign_extend(shrunk, src, dst);
		const u64 extended_original = sign_extend(value, original, dst);

		// utility::console::print("v   {}\n", value);
		// utility::console::print("s   {}\n", shrunk);
		// utility::console::print("exs {}\n", extended_source);
		// utility::console::print("exo {} {}\n", extended_original, original);

		return extended_source == extended_original;
	}

	auto is_operand_of_same_kind(enum operand::type a, enum operand::type b) -> bool {
		switch(a) {
			case operand::OP_AL:  return b == operand::OP_AL  || b == operand::OP_CL || b == operand::OP_REG8;
			case operand::OP_AX:  return b == operand::OP_AX  || b == operand::OP_DX || b == operand::OP_REG16;
			case operand::OP_EAX: return b == operand::OP_EAX || b == operand::OP_ECX || b == operand::OP_REG32;
			case operand::OP_RAX: return b == operand::OP_RAX || b == operand::OP_RCX || b == operand::OP_REG64;
			default: return a == b;
		}
	}

	auto assembler::get_instruction_info(u32 index, operand op_1, operand op_2)  -> const instruction_info* {
		const instruction_info* info = nullptr;

		// utility::console::print("index: {}\n", index);

		if(is_operand_imm(op_2.type)) {
			utility::dynamic_array<const instruction_info*> possible_infos = {};

			const imm& immediate = op_2.immediate;
			const u8 bits = get_operand_bit_width(op_2.type);

			// if we have an optimization index
			if(instruction_db[index].context_index != std::numeric_limits<u16>::max()) {
				// if we have a destination which uses a 64 bit register, and an operand which fits into 32 bits or
				// less we can look for a smaller destination
				if(op_1.type == operand::OP_REG64 && immediate.min_bits <= 32) {
					// verify if it's safe to zero extend the operand (since we're implicitly going
					// from 32 to 64 bits) we can't zero extend 
					if(immediate.sign == false) {
						index = instruction_db[index].context_index;
					}
				}
			}

			// utility::console::print("index: {}\n", index);

			u32 current_index = index;
			// instruction_db[index].print();

			while(is_operand_of_same_kind(instruction_db[index].op1, instruction_db[current_index].op1)) {
				if(is_operand_imm(instruction_db[current_index].op2)) {
					possible_infos.push_back(&instruction_db[current_index++]);
				}
				else {
					break;
				}
			}

			// for(const auto& inst : possible_infos) {
			// 	inst->print();
			// }

			// reorder to smallest source operands
			std::sort(possible_infos.begin(), possible_infos.end(), [](const instruction_info* a, const instruction_info* b) {
				return get_operand_bit_width(a->op2) < get_operand_bit_width(b->op2);
			});

			if(possible_infos.get_size() == 1) {
				info = possible_infos[0];
			}
			else {
				for(const instruction_info* i : possible_infos) {
					const u8 src_bits = get_operand_bit_width(i->op2);
					const u8 dst_bits = get_operand_bit_width(i->op1);

					// sign extension
					if(src_bits < dst_bits) {
						// assume we're sign extending
						if(signed_extend_representable(immediate.value, bits, dst_bits, src_bits)) {
							info = i;
							break;
						}
					}

					// value is representable with a smaller imm
					if(src_bits >= immediate.min_bits) {
						info = i;
						break;
					}
				}
			}
		}
		else {
			info = &instruction_db[index];
		}

		return info;
	}

	void assembler::emit_instruction_prefix(const instruction_info* inst) {
		if(!inst->has_prefix()) {
			return;
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
			default: break;
		}

		// group 1
		switch(prefix & 0b00000011) {
			case LOCK:  m_bytes.push_back(0xF0); break;
			case REPNE: m_bytes.push_back(0xF2); break;
			case REP:   m_bytes.push_back(0xF3); break;
			default: break;
		}
	}

	void assembler::emit_instruction_opcode(const instruction_info* inst, operand op_1, operand op_2) {
		const bool is_rexw = inst->is_rexw();
		const operand operands[2] = { op_1, op_2 };

		auto [rx, destination] = find_rex_pair(operands);

		// opcode - rex prefix
		if(is_rexw || is_extended_reg(op_1) || is_extended_reg(op_2)) {
			// extended gp | register
			if(is_extended_gp_reg(op_1) && is_operand_reg(op_2.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op_2.reg, op_1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op_1.reg, op_2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// gp | extended gp
			else if(is_extended_gp_reg(op_2) && is_operand_gp_reg(op_1.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op_2.reg, op_1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op_1.reg, op_2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// extended gp | mem
			else if(is_operand_gp_reg(op_1.type) && is_operand_mem(op_2.type)) {
				const utility::byte rex_part = rex(is_rexw, op_1.reg, op_2.memory.base.index, op_2.memory.index.index);
				m_bytes.push_back(rex_part);
			}
			// mem | extended gp
			else if(is_operand_mem(op_1.type) && is_operand_gp_reg(op_2.type)) {
				const utility::byte rex_part = rex(is_rexw, op_2.reg, op_1.memory.base.index, op_1.memory.index.index);
				m_bytes.push_back(rex_part);
			}
			// extended xmm | xmm
			else if(is_extended_xmm_reg(op_1) && is_operand_xmm(op_2.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op_2.reg, op_1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op_1.reg, op_2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// xmm | extended xmm
			else if(is_extended_xmm_reg(op_2) && is_operand_xmm(op_1.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op_2.reg, op_1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op_1.reg, op_2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// extended xmm | gp
			else if(is_extended_xmm_reg(op_1) && is_operand_gp_reg(op_2.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op_2.reg, op_1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op_1.reg, op_2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// gp | extended xmm
			else if(is_extended_xmm_reg(op_2) && is_operand_gp_reg(op_1.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op_2.reg, op_1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op_1.reg, op_2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// extended xmm | imm
			else if(is_extended_xmm_reg(op_1) && is_operand_imm(op_2.type)) {
				const utility::byte rex_part = rex(is_rexw, 0, op_1.reg, 0);
				m_bytes.push_back(rex_part);
			}
			else if(is_extended_xmm_reg(op_1) && is_operand_mem(op_2.type)) {
				const utility::byte rex_part = rex(is_rexw, op_1.reg, op_2.memory.base.index, op_2.memory.index.index);
				m_bytes.push_back(rex_part);
			}
			else if(is_extended_xmm_reg(op_2) && is_operand_mem(op_1.type)) {
				const utility::byte rex_part = rex(is_rexw, op_2.reg, op_1.memory.base.index, op_1.memory.index.index);
				m_bytes.push_back(rex_part);
			}
			else if(is_extended_xmm_reg(op_2) && is_operand_reg(op_1.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op_2.reg, op_1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op_1.reg, op_2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			else if(is_extended_xmm_reg(op_1) && is_operand_reg(op_2.type)) {
				if(inst->get_direction()) {
					const utility::byte rex_part = rex(is_rexw, op_2.reg, op_1.reg, 0);
					m_bytes.push_back(rex_part);
				}
				else {
					const utility::byte rex_part = rex(is_rexw, op_1.reg, op_2.reg, 0);
					m_bytes.push_back(rex_part);
				}
			}
			// gp | xmm
			else if(is_operand_gp_reg(op_1.type) && is_operand_xmm(op_2.type)) {
				const utility::byte rex_part = rex(is_rexw, op_2.reg, op_1.reg, 0);
				m_bytes.push_back(rex_part);
			}
			// reg x
			else if(is_operand_gp_reg(op_1.type)) {
				const utility::byte rex_part = rex(is_rexw, 0, op_1.reg, 0);
				m_bytes.push_back(rex_part);
			}
			// x reg
			else if(is_operand_gp_reg(op_2.type)) {
				const utility::byte rex_part = rex(is_rexw, 0, op_2.reg, 0);
				m_bytes.push_back(rex_part);
			}
			// mem x
			else if(is_operand_mem(op_1.type)) {
				const utility::byte rex_part = rex(is_rexw, 0, op_1.memory.base.index, op_1.memory.index.index);
				m_bytes.push_back(rex_part);
			}
			// mem x
			else if(is_operand_mem(op_2.type)) {
				const utility::byte rex_part = rex(is_rexw, 0, op_2.memory.base.index, op_2.memory.index.index);
				m_bytes.push_back(rex_part);
				}
			// x x
			else {
				const utility::byte rex_part = rex(is_rexw, rx, destination, 0);
				m_bytes.push_back(rex_part);
			}
		}
		else if(is_operand_mem(op_1.type)) {
			const auto memory = op_1.memory;

			// extended base
			if(memory.has_base && memory.base.index >= 8) {
				m_bytes.push_back(rex(false, 0, memory.base.index, memory.index.index));
			}
			else if(memory.has_index &&  memory.index.index >= 8) {
				m_bytes.push_back(rex(false, 0, memory.base.index, memory.index.index));
			}
		}
		else if(is_operand_mem(op_2.type)) {
			const auto memory = op_2.memory;

			// extended base
			if(memory.has_base && memory.base.index >= 8) {
				m_bytes.push_back(rex(false, 0, memory.base.index, memory.index.index));
			}
			else if(memory.has_index &&  memory.index.index >= 8) {
				m_bytes.push_back(rex(false, 0, memory.base.index, memory.index.index));
			}
		}

		// opcode id
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

		for(u8 i = 4; i-- > 1;) {
			const u8 byte = (opcode >> (i * 8)) & 0xFF;

			if(byte != 0) {
				m_bytes.push_back(byte);
			}
		}

		// always push the last byte
		const u8 byte = (opcode >> (0 * 8)) & 0xFF;
		m_bytes.push_back(byte);
	}

	void assembler::emit_instruction_modrm(const instruction_info* inst, operand op_1, operand op_2) {
		const operand operands[2] = { op_1, op_2 };
		auto [rx, destination] = find_rex_pair(operands);

		// mod rm / sib
		if(inst->is_r() || is_operand_mem(op_1.type) || is_operand_mem(op_2.type)) {
			utility::byte mod_rm_part;

			if(is_operand_mem(op_1.type)) {
				const bool has_sib = has_sib_byte(op_1, op_2);
				const auto memory = op_1.memory;

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
			else if(is_operand_mem(op_2.type)) {
				const bool has_sib = has_sib_byte(op_1, op_2);
				const auto memory = op_2.memory;

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
				// extract the direction bit
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
			const utility::byte mod_rm_part = direct(inst->get_ext(), destination);
			m_bytes.push_back(mod_rm_part);
		}
	}

	void assembler::emit_instruction_sib(operand op_1, operand op_2) {
		mem memory;

		if(is_operand_mem(op_1.type)) {
			memory = op_1.memory;
		}
		else if(is_operand_mem(op_2.type)) {
			memory = op_2.memory;
		}
		else {
			return; // no sib byte
		}

		if(memory.has_index) {
			m_bytes.push_back(sib(memory.scale, memory.index.index, memory.base.index));
		}
		else if(is_stack_pointer(reg(memory.base))) {
			m_bytes.push_back(sib(memory.scale, memory.has_index ? memory.index.index : 0b100, memory.base.index));
		}
		else if(memory.has_base == false) {
			// no scale, no index, displacement-only mode
			m_bytes.push_back(sib(0b00, 0b100, 0b101));
		}
	}

	void assembler::emit_instruction(u32 index, operand op_1, operand op_2) {
		instruction_begin();

		// utility::console::print("original operands {} {}\n", operand_type_to_string(op_1.type), operand_type_to_string(op_2.type));
		const instruction_info* inst = get_instruction_info(index, op_1, op_2);
		// inst->print();

		emit_instruction_prefix(inst);
		emit_instruction_opcode(inst, op_1, op_2);
		emit_instruction_modrm(inst, op_1, op_2);
		return;
		emit_instruction_sib(op_1, op_2);

		const u8 operand_count = inst->get_operand_count(); // this could be inferred ig

		ASSERT(operand_count == 2, "only instructions with 2 operands are supported");
		const operand operands[2] = { op_1, op_2 };
		const enum operand::type operands_actual[2] = { inst->op1, inst->op2 };

		// integral values
		for(u8 i = 0; i < operand_count; ++i) {
			if(is_operand_imm(operands[i].type)) {
				// imm operands
				emit_immediate_operand(operands[i].immediate.value, operands_actual[i]);
			}
			else if(is_operand_moff(operands[i].type)) {
				emit_immediate_operand(operands[i].memory_offset.value, operand::type::OP_I64);
			}
			else if(is_operand_mem(operands[i].type)) {
				// memory displacement
				const auto memory = operands[i].memory;
				auto displacement = memory.displacement;

				if(displacement.value == 0) {
					if(memory.has_base && memory.base.type != REG_RIP) {
						continue; // skip 0 displacements
					}
				}

				enum operand::type ty;

				if(memory.has_base == false) {
					ty = operand::type::OP_I32;
				}
				else if(memory.base.type == REG_RIP) {
					ty = operand::type::OP_I32;

					// beginning of the instruction
					i32 new_displacement = static_cast<i32>(displacement.value - (get_current_inst_size() + 4));

					if(i + 1 != operand_count) {
						// if we have another operand after the current one, calculate it's size
						if(is_operand_imm(operands_actual[i + 1])) { // regs are already encoded
							new_displacement -= get_operand_bit_width(operands_actual[i + 1]) / 8;
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

				emit_immediate_operand(displacement.value, ty);
			}
		}
	}

	auto assembler::has_sib_byte(operand op_1, operand op_2) -> bool {
		mem memory;

		if(is_operand_mem(op_1.type)) {
			memory = op_1.memory;
		}
		else if(is_operand_mem(op_2.type)) {
			memory = op_2.memory;
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

	void assembler::emit_immediate_operand(u64 imm, enum operand::type type) {
		switch(type) {
			case operand::type::OP_I8: {
				const u8 value = static_cast<u8>(imm);

				for(int i = 0; i < 1; ++i) {
					utility::byte b = (value >> (i * 8)) & 0xFF;
					m_bytes.push_back(b);
				}

				break;
			}
			case operand::type::OP_I16: {
				const u16 value = static_cast<u16>(imm);

				for(int i = 0; i < 2; ++i) {
					utility::byte b = (value >> (i * 8)) & 0xFF;
					m_bytes.push_back(b);
				}

				break;
			}
			case operand::type::OP_I32: {
				const u32 value = static_cast<u32>(imm);

				for(int i = 0; i < 4; ++i) {
					utility::byte b = (value >> (i * 8)) & 0xFF;
					m_bytes.push_back(b);
				}

				break;
			}
			case operand::type::OP_I64: {
				const u64 value = imm;

				for(int i = 0; i < 8; ++i) {
					utility::byte b = (value >> (i * 8)) & 0xFF;
					m_bytes.push_back(b);
				}

				break;
			}
			default: ASSERT(false, "ivalid operand");
		}
	}

	auto assembler::sib(u8 scale, u8 index, u8 base) -> u8 {
		ASSERT(scale <= 3, "invalid scale");

		// scale [XX______]
		// index [__XXX___]
		// base  [_____XXX]

		return (scale << 6) | ((index & 0x7) << 3) | (base & 0x7);
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
} // namespace baremetal
