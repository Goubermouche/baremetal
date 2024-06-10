#include "assembler.h"
#include <utility/assert.h>

namespace baremetal {
	assembler::assembler() : m_current_inst_begin(0) {}

	auto assembler::get_bytes() const -> const utility::dynamic_array<utility::byte>& {
		return m_bytes;
	}

	auto assembler::find_rex_pair(const operand* operands) -> std::pair<u8, u8> {
		// locate the first registers from the back
		std::pair<u8, u8> result = { 0, 0 };
		u8 i = 4;

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

	auto is_extended_register(operand op_1, operand op_2) -> bool {
		bool result = false;

		if(is_operand_reg(op_1.type)) {
			result |= op_1.reg >= 8;
		}

		if(is_operand_reg(op_2.type)) {
			result |= op_2.reg >= 8;
		}

		return result;
	}

	static auto min_bits(u64 value) -> u8 {
		if(value == 0) {
			return 1;
		}

		u8 bits = 0;

		while(value != 0) {
			bits++;
			value >>= 1;
		}

		return bits;
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

	auto assembler::get_instruction_info(u32 index, operand op_1, operand op_2)  -> const instruction_info* {
		const instruction_info* info = nullptr;

		if(is_operand_imm(op_2.type)) {
			std::vector<const instruction_info*> possible_infos = {};

			const imm& immediate = op_2.imm;
			const u8 bits = get_operand_bit_width(op_2.type);

			// if we have a destination which uses a 64 bit register, and an operand which fits into 32 bits or
			// less we can look for a smaller destination

			if(op_1.type == operand::OP_REG64 && immediate.min_bits <= 32) {
				// verify if it's safe to zero extend the operand (since we're implicitly going from 32 to 64 bits)
				// we can't zero extend 
				if(immediate.sign == false) {
					index = instruction_db[index].context_index;
				}
			}

			u32 current_index = index;

			while(instruction_db[current_index].op1 == instruction_db[index].op1) {
				possible_infos.push_back(&instruction_db[current_index++]);
			}

			if(possible_infos.size() == 1) {
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
		const bool is_extended_reg = is_extended_register(op_1, op_2);
		const u8 operand_count = inst->get_operand_count(); // this could be inferred ig

		ASSERT(operand_count == 2, "only instructions with 2 operands are supported");
		const operand operands[2] = { op_1, op_2 };

		auto [rx, destination] = find_rex_pair(operands);

		// opcode - rex prefix
		if(is_rexw || is_extended_reg) {
			const utility::byte rex_part = rex(is_rexw, rx, destination, 0);
			m_bytes.push_back(rex_part);
		}

		// opcode id
		u64 opcode = inst->opcode;

		if(inst->is_opcode_ext()) {
			// extract the 3 least significant bits 
			opcode += destination & 0b00000111;
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
		if(inst->is_r()) {
			utility::byte mod_rm_part;

			if(is_operand_mem(op_1.type)) {
				ASSERT(false, "not implemented");
			}
			else if(is_operand_mem(op_2.type)) {
				const bool has_sib = has_sib_byte(inst, op_1, op_2);
				ASSERT(op_2.mem.displacement.min_bits <= 32, "too many displacement bits");

				// right mem
				
				if(op_2.mem.has_base == false) {
					// absolute address
					mod_rm_part = indirect(rx, 0b100); // 100 = SIB byte
				}
				else if(op_2.mem.base.type == REG_RIP) {
					// rip reg
					mod_rm_part = indirect(rx, 0b101); // 101 = RIP-relative
				}
				else if(op_2.mem.displacement.value == 0) {
				// no displacement
				mod_rm_part = indirect(rx, has_sib ? 0b100 : op_2.mem.base.index);
				}
				else if(op_2.mem.displacement.min_bits <= 8) {
					// 8 bit displacement
					mod_rm_part = indirect_disp_8(rx, has_sib ? 0b100 : op_2.mem.base.index);
				}
				else {
					// 32 bit displacement
					mod_rm_part = indirect_disp_32(rx, has_sib ? 0b100 : op_2.mem.base.index);
				}
			}
			else {
				mod_rm_part = direct(rx, destination);
			}

			m_bytes.push_back(mod_rm_part);
		}
		else if(inst->is_ext()) {
			const utility::byte mod_rm_part = direct(inst->get_ext(), destination);
			m_bytes.push_back(mod_rm_part);
		}
	}

	void assembler::emit_instruction_sib(const instruction_info* inst, operand op_1, operand op_2) {
		mem memory;

		if(is_operand_mem(op_1.type)) {
			memory = op_1.mem;
		}
		else if(is_operand_mem(op_2.type)) {
			memory = op_2.mem;
		}
		else {
			return; // no sib byte
		}

		if(memory.has_index) {
			m_bytes.push_back(sib(memory.scale, memory.index.index, memory.base.index));
		}
		else if(is_stack_pointer(reg(memory.base))) {
			m_bytes.push_back(sib(memory.scale, memory.index.index, memory.base.index)); // may not be correct
		}
		else if(memory.has_base == false) {
			// no scale, no index, displacement-only mode
			m_bytes.push_back(sib(0b00, 0b100, 0b101));
		}
	}

	void assembler::emit_instruction(u32 index, operand op_1, operand op_2) {
		instruction_begin();

		const instruction_info* inst = get_instruction_info(index, op_1, op_2);
		utility::console::print("assembling as: {} {} {}\n", inst->name, operand_type_to_string(inst->op1), operand_type_to_string(inst->op2));

		emit_instruction_prefix(inst);
		emit_instruction_opcode(inst, op_1, op_2);
		emit_instruction_modrm(inst, op_1, op_2);
		emit_instruction_sib(inst, op_1, op_2);

		const u8 operand_count = inst->get_operand_count(); // this could be inferred ig

		ASSERT(operand_count == 2, "only instructions with 2 operands are supported");
		const operand operands[2] = { op_1, op_2 };
		const enum operand::type operands_actual[2] = { inst->op1, inst->op2 };

		// integral values
		for(u8 i = 0; i < operand_count; ++i) {
			if(is_operand_imm(operands[i].type)) {
				// imm operands
				emit_immediate_operand(operands[i].imm.value, operands_actual[i]);
			}
			else if(is_operand_mem(operands[i].type)) {
				// memory displacement
				const auto memory = operands[i].mem;
				auto displacement = memory.displacement;

				if(displacement.value == 0 && memory.base.type != REG_RIP) {
					continue; // skip 0 displacements
				}

				enum operand::type ty;

				if(memory.has_base == false) {
					ty = operand::type::OP_I32;
				}
				else if(memory.base.type == REG_RIP) {
					ty = operand::type::OP_I32;

					// beginning of the instruction
					displacement = imm(displacement.value - (get_current_inst_size() + 4));
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

	auto assembler::has_sib_byte(const instruction_info* inst, operand op_1, operand op_2) -> bool {
		mem memory;

		if(is_operand_mem(op_1.type)) {
			memory = op_1.mem;
		}
		else if(is_operand_mem(op_2.type)) {
			memory = op_2.mem;
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
		m_current_inst_begin = m_bytes.size();
	}

	auto assembler::get_current_inst_size() const -> u8 {
		return m_bytes.size() - m_current_inst_begin;
	}
} // namespace baremetal
