#include "assembler.h"
#include <utility/assert.h>

namespace baremetal {
	assembler::assembler() {}

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

	auto is_extended_register(operand op_1, operand op_2, operand op_3) -> bool {
		bool result = false;

		if(is_operand_reg(op_1.type)) {
			result |= op_1.reg >= 8;
		}

		if(is_operand_reg(op_2.type)) {
			result |= op_2.reg >= 8;
		}

		if(is_operand_reg(op_2.type)) {
			result |= op_2.reg >= 8;
		}

		return result;
	}

	void assembler::emit_instruction(u32 index, operand op_1, operand op_2, operand op_3) {
		// TODO: operand types in operand are unnecessary since we can infer them from
		//       the related instruction_info entry
		const instruction_info& inst = instruction_db[index];

		const bool is_rexw = inst.is_rexw();
		const bool is_mod_rm = inst.is_r();
		const bool is_extended_reg = is_extended_register(op_1, op_2, op_3);
		const u8 operand_count = inst.get_operand_count(); // this could be inferred ig

		ASSERT(operand_count == 2, "only instructions with 2 operands are supported");
		const operand operands[3] = { op_1, op_2, op_3 };

		const auto [is_imm, imm_index] = inst.has_imm_operands();
		auto [rx, destination] = find_rex_pair(operands);

		if(inst.extension & EXT_OP_R) {
			rx = 0;
		}

		// prefix
		if(inst.has_prefix()) {
			const u8 prefix = inst.prefix;

			// group 1
			switch(prefix & 0b00000011) {
				case LOCK:  m_bytes.push_back(0xF0); break;
				case REPNE: m_bytes.push_back(0xF2); break;
				case REP:   m_bytes.push_back(0xF3); break;
				default: break;
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

			// group 3
			if(prefix & OPERAND_SIZE_OVERRIDE) {
				m_bytes.push_back(0x66);
			}

			// group 4
			if(prefix & ADDRESS_SIZE_OVERRIDE) {
				m_bytes.push_back(0x67);
			}
		}

		// opcode - rex prefix
		if(is_rexw || is_extended_reg) {
			const utility::byte rex_part = rex(is_rexw, rx, destination, 0);
			m_bytes.push_back(rex_part);
		}

		// opcode id
		u64 opcode = inst.opcode;

		if(inst.is_opcode_ext()) {
			// extract the 3 least significant bits 
			opcode += destination & 0b00000111;
		}

		for(u8 i = 4; i-- > 0;) {
			const u8 byte = (opcode >> (i * 8)) & 0xFF;

			if(byte != 0) {
				m_bytes.push_back(byte);
			}
		}

		// mod rm / sib
		if(is_mod_rm) {
			const utility::byte mod_rm_part = direct(rx, destination);
			m_bytes.push_back(mod_rm_part);
		}
		else if(inst.is_ext()) {
			const utility::byte mod_rm_part = direct(inst.get_ext(), destination);
			m_bytes.push_back(mod_rm_part);
		}

		// immediate operand 
		if(is_imm) {
			switch(operands[imm_index].type) {
				case operand::OP_I8: {
					const u8 value = static_cast<u8>(operands[imm_index].imm);

					for(int i = 0; i < 1; ++i) {
						utility::byte b = (value >> (i * 8)) & 0xFF;
						m_bytes.push_back(b);
					}

					break;
				}
				case operand::OP_I16: {
					const u16 value = static_cast<u16>(operands[imm_index].imm);

					for(int i = 0; i < 2; ++i) {
						utility::byte b = (value >> (i * 8)) & 0xFF;
						m_bytes.push_back(b);
					}

					break;
				}
				case operand::OP_I32: {
					const u32 value = static_cast<u32>(operands[imm_index].imm);

					for(int i = 0; i < 4; ++i) {
						utility::byte b = (value >> (i * 8)) & 0xFF;
						m_bytes.push_back(b);
					}

					break;
				}
				case operand::OP_I64: {
					const u64 value = operands[imm_index].imm;

					for(int i = 0; i < 8; ++i) {
						utility::byte b = (value >> (i * 8)) & 0xFF;
						m_bytes.push_back(b);
					}

					break;
				}
				default: ASSERT(false, "ivalid operand");
			}
		}
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

		// mod  [XX______]
		// rx   [__XXX___]
		// rm   [_____XXX]
		return static_cast<u8>((rm & 7) | ((rx & 7) << 3) | (mod << 6));
	}

	auto assembler::direct(u8 rx, u8 reg) -> u8 {
		return mod_rx_rm(DIRECT, rx, reg);
	}
} // namespace baremetal
