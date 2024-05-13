#include "assembler.h"
#include <utility/assert.h>

namespace baremetal {
	assembler::assembler() : m_current_block(create_block()) {}

	void assembler::mov(gpr_reg destination, gpr_reg source) {
		m_blocks[m_current_block].instructions.emplace_back(instruction::MOV_RR, destination, source);
	}

	void assembler::mov(gpr_reg destination, byte immediate) {
		m_blocks[m_current_block].instructions.emplace_back(instruction::MOV_R_I8, destination, static_cast<u64>(immediate));
	}

	void assembler::mov(gpr_reg destination, dword immediate) {
		m_blocks[m_current_block].instructions.emplace_back(instruction::MOV_R_I32, destination, static_cast<u64>(immediate));
	}
	void assembler::neg(gpr_reg destination) {
		// m_blocks[m_current_block].instructions.emplace_back(instruction::NEG, destination);
	}

	void assembler::jmp(u64 block) {
		m_relocations.push_back(relocation{
			.block_index = m_current_block,
			.instruction_index = m_blocks[m_current_block].instructions.size(),
			.target = block
		});

		// m_blocks[m_current_block].instructions.emplace_back(instruction::JMP);
	}

	auto assembler::create_block() -> u64 {
		const u64 index = m_blocks.size();
		m_blocks.emplace_back();
		return index;
	}

	auto assembler::get_current_block() const -> u64 {
		return m_current_block;
	}

	void assembler::set_current_block(u64 block) {
		m_current_block = block;
	}

	void assembler::emit() {
		for(const block& block : m_blocks) {
			for(const instruction& instruction : block.instructions) {
				emit_instruction(instruction);
			}
		}
	}

	void assembler::emit_instruction(const instruction& instruction) {
		const auto& info = instruction_db[instruction.opcode];
		std::cout  << instruction_db[instruction.opcode].name << ":  ";

		const byte destination = static_cast<u8>(instruction.operands[0].reg);

		// +-----+--------+------------+---------------------------+
		// | rex | opcode | r/m or s/b | displacement or immediate |
		// +-----+--------+------------+---------------------------+

		byte rx;
		byte direct_reg;

		bool imm = is_imm(info.operands[1]);

		if(imm) {
			rx = 0;
			direct_reg = static_cast<u8>(instruction.operands[0].reg);
		}
		else {
			rx = destination;
			direct_reg = static_cast<u8>(instruction.operands[1].reg); // source
		}

		std::cout << std::hex;

		if(info.rex_w) {
			const byte rex_part = rex(true, rx, destination, 0); // 1B
			std::cout << rex_part;
		}

		byte opcode = info.opcode; // up to 4B

		if(info.multi) {
			opcode = opcode + destination;
		}

		std::cout << opcode;

		if(info.mod_rm) {
			const byte extension = direct(rx, direct_reg); // 1B
			std::cout << extension;
		}

		if(imm) {
			switch(info.operands[1]) {
				case IMM_8: {
					const byte imm8 = static_cast<u8>(instruction.operands[1].immediate);
					hex_print_reverse(std::cout, imm8);
					break;
				}
				case IMM_32: {
					const dword imm32 = static_cast<u32>(instruction.operands[1].immediate);
					hex_print_reverse(std::cout, imm32);
					break;
				}
			}
		}

		std::cout << std::dec << '\n';
	}

	auto assembler::rex(bool w, u8 rx, u8 base, u8 index) -> u8 {
		ASSERT(rx < 16, "invalid rx");
		ASSERT(base < 16, "invalid base");
		ASSERT(index < 16, "invalid index");

		// whenever a used register is larger than 3 bits we need to mark the extension bit
		// the result will then be extended in mod R/M or the SIB byte.

		// rex prefix + 64 bit mode (0x48)    [0100____]
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
