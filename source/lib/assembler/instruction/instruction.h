#pragma once
#include "assembler/instruction/operands/operands.h"

#include <utility/assert.h>

namespace baremetal::assembler {
	enum extension : u8 {
		EXT_NONE = 0b00000000,
		EXT_0    = 0b00000001, // /0
		EXT_1    = 0b00000010, // /1
		EXT_2    = 0b00000011, // /2
		EXT_3    = 0b00000100, // /3
		EXT_4    = 0b00000101, // /4
		EXT_5    = 0b00000110, // /5
		EXT_6    = 0b00000111, // /6
		EXT_7    = 0b00001000, // /7
		EXT_R    = 0b00010000, // /r (mod rm byte exists, and any register can be used)

		// flags
		EXT_REXW = 0b00100000,

		// opcode extensions
		EXT_OP_R = 0b01000000, // opcode + r / opcode + i
	};

	enum prefix : u8 {
		// group 1 [______XX]
		// group 2 [__XXXX__]
		// group 3 [_X______]
		// group 4 [X_______]
		PREFIX_NONE           = 0b00000000,
		// group 1
		LOCK                  = 0b00000001,
		REPNE                 = 0b00000010,
		REP                   = 0b00000011,
		// group 2
		CS_SEGMENT            = 0b00000100,
		SS_SEGMENT            = 0b00001000,
		DS_SEGMENT            = 0b00001100,
		ES_SEGMENT            = 0b00010000,
		FS_SEGMENT            = 0b00010100,
		GS_SEGMENT            = 0b00011000,
		BRANCH_NOT_TAKEN      = 0b00011100,
		BRANCH_TAKEN          = 0b00100000,
		// group 3
		OPERAND_SIZE_OVERRIDE = 0b01000000,
		// group 4
		ADDRESS_SIZE_OVERRIDE = 0b10000000
	};

	enum inst_size : u8 {
		OPS_32,
		OPS_64,
		OPS_128,
		OPS_256,
		OPS_512,
	};

	enum encoding : u8 {
		ENC_R,
		ENC_M,
		ENC_MR,
		ENC_RM,
		ENC_RMR,
		ENC_NORMAL,
		// NORMAL encoding, but interpret the first opcode byte as a separate instruction
		// used by instructions which are formed using two other instructions (ie. fsave)
		ENC_NORMALD, 

		// VEX
		ENC_VEX,
		ENC_VEX_R,
		ENC_VEX_VM,
		ENC_VEX_RM,
		ENC_VEX_MR,
		ENC_VEX_RVM,
		ENC_VEX_RMV,
		ENC_VEX_MVR,
		ENC_VEX_MVRR,
		ENC_VEX_RVMN, // RVM: VEX, with vvvv set to 1111 (no vvvv)
		ENC_VEX_RVMS,

		// EVEX
		ENC_EVEX_RVM,
		ENC_EVEX_MVR,
		ENC_EVEX_RM,
		ENC_EVEX_MR,
		ENC_EVEX_VM,
		ENC_EVEX_RMZ,
		ENC_EVEX_M,
		// XOP
		ENC_XOP_VM,
		ENC_XOP,
	};

	struct instruction { 
		constexpr auto is_rex() const -> bool {
			switch(enc) { 
				case ENC_NORMAL:
				case ENC_NORMALD:
				case ENC_MR:
				case ENC_M:
				case ENC_RM:
				case ENC_RMR:
				case ENC_R: return true;
				default: return false;
			}
		}

		constexpr auto is_vex_xop() const -> bool {
			switch(enc) {
				case ENC_XOP:
				case ENC_XOP_VM:
				case ENC_VEX:
				case ENC_VEX_R:
				case ENC_VEX_MR:
				case ENC_VEX_RM:
				case ENC_VEX_RVM:
				case ENC_VEX_RVMN:
				case ENC_VEX_RVMS:
				case ENC_VEX_RMV:
				case ENC_VEX_MVR:
				case ENC_VEX_MVRR:
				case ENC_VEX_VM: return true;
				default: return false;
			}
		}

		constexpr auto is_xop() const -> bool {
			switch(enc) {
				case ENC_XOP:
				case ENC_XOP_VM: return true;
				default: return false;
			}
		}

		constexpr auto is_evex() const -> bool {
			switch(enc) {
				case ENC_EVEX_RVM:
				case ENC_EVEX_MVR:
				case ENC_EVEX_MR:
				case ENC_EVEX_VM:
				case ENC_EVEX_RMZ:
				case ENC_EVEX_M:
				case ENC_EVEX_RM: return true;
				default: return false;
			}
		}

		constexpr auto is_rexw() const -> bool {
			return flags & 0b00000001;
		}

		constexpr auto is_l0() const -> bool {
			ASSERT(is_vex_xop(), "invalid - expected a xop or vex instruction\n");
			return (flags & 0b11000000) == 0b10000000;
		}

		constexpr auto is_l1() const -> bool {
			ASSERT(is_vex_xop(), "invalid - expected a xop or vex instruction\n");
			return (flags & 0b11000000) == 0b01000000;
		}

		constexpr auto is_map5() const -> bool {
			return (flags & 0b11000000) == 0b10000000;
		}

		constexpr auto is_map6() const -> bool {
			return (flags & 0b11000000) == 0b01000000;
		}

		constexpr auto is_ri() const -> bool {
			return flags & 0b00100000;
		}

		constexpr auto is_r() const -> bool {
			return (flags & 0b00011110) == 0b00010100;
		}

		constexpr auto is_rm() const -> bool {
			u8 rm = flags & 0b00011110;

			if(rm == 0b00010100) {
				return false;
			}

			return rm;
		}

		constexpr auto is_is4() const -> bool {
			return (flags & 0b00011110) == 0b00010010;
		}

		constexpr auto get_rm() const -> u8 {
			return ((flags & 0b00011110) >> 1) - 1;
		}

		constexpr auto get_magic_kind() const -> u8 {
			return magic >> 14;
		}

		constexpr auto get_magic_index() const -> u16 {
			return magic & 0b0011111111111111;
		};

		constexpr auto has_magic() const -> bool {
			return magic != utility::limits<u16>::max();
		}

		auto has_extended_vex(const operand* data) const -> bool {
			for(u8 i = 0; i < operand_count; ++i) {
				if(is_operand_large_reg(data[i].type) && data[i].r > 15) {
					return true;
				}
			}

			return false;
		}

		constexpr auto get_map_select() const -> u8 {
			if(is_evex()) {
				if(is_map6()) {
					return 0b110; 
				}
	
				if(is_map5()) {
					return 0b101; 
				}
			}
			
			if(is_xop()) {
				switch(enc) {
					case ENC_XOP:    return 0b01001;
					case ENC_XOP_VM: return 0b01010;
					default: ASSERT(false, "unknown xop encoding");
				}
			}
	
			switch((opcode & 0xffff00)) {
				case 0x000000: return 0b000; 
				case 0x000f00: return 0b001; 
				case 0x0f3800: return 0b010;
				case 0x0f3a00: return 0b011;
				default: ASSERT(false, "unknown leading opcode 1 {}", opcode & 0xffff00);
			}
	
			return 0;
		}

		constexpr auto get_imp() const -> u8 {
			if(prefix == OPERAND_SIZE_OVERRIDE) {
				return 0b01;
			}

			if(prefix == REP) {
				return 0b10;
			}

			if(prefix == REPNE) {
				return 0b11;
			}

			return 0;
		}

		constexpr auto get_l() const -> u8 {
			if(is_l1()) {
				return true;
			}

			if(is_l0()) {
				return false;
			}

			// vector length (0 = 128b, 1 = 256b)
			return op_size == OPS_256;
		}

		constexpr auto get_evex_zero() const -> u8 {
			switch (operands[0]) {
				case OP_XMM_KZ:	
				case OP_YMM_KZ:	
				case OP_ZMM_KZ: return true; 
				default:        return false;
			}
		}

		constexpr auto get_evex_operand_type() const -> u8 {
			if(op_size == OPS_256) {
				return 0b00100000;
			}
	
			if(op_size == OPS_512) {
				return  0b01000000;
			}
	
			return 0;
		}

		auto get_mem_operand() const -> u8 {
			if(is_operand_mem(operands[0])) { return 0; }
			if(is_operand_mem(operands[1])) { return 1; }
			if(is_operand_mem(operands[2])) { return 2; }
			if(is_operand_mem(operands[3])) { return 3; }

			return 0;
		}

		auto has_mem_operand() const -> bool {
			if(is_operand_mem(operands[0])) { return true; }
			if(is_operand_mem(operands[1])) { return true; }
			if(is_operand_mem(operands[2])) { return true; }
			if(is_operand_mem(operands[3])) { return true; }

			return false;
		}

		auto get_broadcast_operand() const -> u8 {
			if(is_operand_broadcast(operands[0])) { return 0; }
			if(is_operand_broadcast(operands[1])) { return 1; }
			if(is_operand_broadcast(operands[2])) { return 2; }
			if(is_operand_broadcast(operands[3])) { return 3; }

			return 0;
		}

		auto has_broadcast_operand() const -> bool {
			if(is_operand_broadcast(operands[0])) { return true; }
			if(is_operand_broadcast(operands[1])) { return true; }
			if(is_operand_broadcast(operands[2])) { return true; }
			if(is_operand_broadcast(operands[3])) { return true; }

			return false;
		}

		auto has_masked_operand() const -> bool {
			if(is_operand_masked(operands[0])) { return true; }
			//if(is_operand_masked(operands[1])) { return true; }
			//if(is_operand_masked(operands[2])) { return true; }
			//if(is_operand_masked(operands[3])) { return true; }

			return false;
		}

		const char* name;         // instruction mnemonic
		encoding enc;             // instruction encoding
		u8 prefix;                // instruction prefix encoded in binary (see prefix)
		u32 opcode;               // opcode, including the opcode prefix
		u8 flags;                 // instruction flags encoded in binary (see get_instruction_flags)
		u16 magic;                // magic index, used for alternative versions of special instructions
		u8 operand_count;         // total operand count
		inst_size op_size;        // default instruction size
		operand_type operands[4]; // operand types
	};

	static constexpr auto inst(
		const char* name, 
		encoding enc,
		u8 prefix,
		u32 opcode,
		u8 flags, 
		u16 magic, 
		inst_size op_size, 
		operand_type op1 = OP_NONE,
		operand_type op2 = OP_NONE,
		operand_type op3 = OP_NONE,
		operand_type op4 = OP_NONE
	) -> instruction {
		instruction result; 

		result.name = name;
		result.enc = enc;
		result.prefix = prefix;
		result.opcode = opcode;
		result.flags = flags;
		result.magic = magic;
		result.operands[0] = op1;
		result.operands[1] = op2;
		result.operands[2] = op3;
		result.operands[3] = op4;
		result.operand_count = 0;
		result.op_size = op_size;

		for(u8 i = 0; i < 4; ++i) {
			if(result.operands[i] == OP_NONE) {
				break;
			}

			result.operand_count++;
		}

		return result;
	}

	inline auto inst_size_to_int(inst_size s) -> u16 {
		switch(s) {
			case OPS_32:  return 32;
			case OPS_64:  return 64;
			case OPS_128: return 128;
			case OPS_256: return 256;
			case OPS_512: return 512;
			default: ASSERT(false, "unhandled size\n");
		}

		return 0; // unreachable
	}

	// main isntruction database
	static constexpr instruction g_instruction_db[] = {
		#include "assembler/instruction/databases/database.inc"
	};

	constexpr u32 INSTRUCTION_DB_SIZE = sizeof(g_instruction_db) / sizeof(instruction);
	constexpr u8 MAX_INSTRUCTION_SIZE = 15;

	static_assert(INSTRUCTION_DB_SIZE < 16384, "magic number limit reached");
} // namespace baremetal::assembler

