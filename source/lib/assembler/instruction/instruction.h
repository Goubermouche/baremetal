// contains the definition of an x64 instruction, the encoding itself is implemented
// in lib/assembler/backend.cpp.
//
// some useful links: 
// - https://wiki.osdev.org/X86-64_Instruction_Encoding
// - https://en.wikipedia.org/wiki/VEX_prefix
// - https://en.wikipedia.org/wiki/EVEX_prefix

#pragma once
#include "assembler/instruction/operands/operands.h"

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

	// each instruction can have up to four (legacy) prefixes, one from each group
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

	// instruction **operand** size, in bits
	enum inst_size : u8 {
		OPS_32,
		OPS_64,
		OPS_128,
		OPS_256,
		OPS_512,
	};

	// encoding categories, they don't directly map into regular x64 instruction 
	// categories as defined by the Intel ISA manual, since we solve some edge
	// cases here
	enum encoding : u8 {
		ENC_R,
		ENC_M,
		ENC_MR,
		ENC_RM,
		ENC_RMR,
		ENC_NORMAL,
		// ENC_NORMAL but interpret the first opcode byte as a separate instruction
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
		[[nodiscard]] constexpr auto is_rex() const -> bool {
			switch(enc) { 
				case ENC_NORMAL:
				case ENC_NORMALD:
				case ENC_MR:
				case ENC_M:
				case ENC_RM:
				case ENC_RMR:
				case ENC_R: return true;
				default:    return false;
			}
		}

		[[nodiscard]] constexpr auto is_vex_xop() const -> bool {
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
				default:         return false;
			}
		}

		[[nodiscard]] constexpr auto is_xop() const -> bool {
			switch(enc) {
				case ENC_XOP:
				case ENC_XOP_VM: return true;
				default:         return false;
			}
		}

		[[nodiscard]] constexpr auto is_evex() const -> bool {
			switch(enc) {
				case ENC_EVEX_RVM:
				case ENC_EVEX_MVR:
				case ENC_EVEX_MR:
				case ENC_EVEX_VM:
				case ENC_EVEX_RMZ:
				case ENC_EVEX_M:
				case ENC_EVEX_RM: return true;
				default:          return false;
			}
		}

		[[nodiscard]] constexpr auto is_rexw() const -> bool {
			return flags & 0b00000001;
		}

		[[nodiscard]] constexpr auto is_ri() const -> bool {
			return flags & 0b00100000;
		}

		[[nodiscard]] constexpr auto is_r() const -> bool {
			return (flags & 0b00011110) == 0b00010100;
		}

		[[nodiscard]] constexpr auto is_rm() const -> bool {
			u8 rm = flags & 0b00011110;

			if(rm == 0b00010100) {
				return false;
			}

			return rm;
		}

		[[nodiscard]] constexpr auto is_is4() const -> bool {
			return (flags & 0b00011110) == 0b00010010;
		}

		[[nodiscard]] constexpr auto get_rm() const -> u8 {
			return ((flags & 0b00011110) >> 1) - 1;
		}

		[[nodiscard]] constexpr auto get_magic_kind() const -> u8 {
			return magic >> 14;
		}

		[[nodiscard]] constexpr auto get_magic_index() const -> u16 {
			return magic & 0b0011111111111111;
		};

		[[nodiscard]] constexpr auto has_magic() const -> bool {
			return magic != utility::limits<u16>::max();
		}

		[[nodiscard]] auto has_extended_vex(const operand* data) const -> bool {
			for(u8 i = 0; i < operand_count; ++i) {
				if(is_operand_large_reg(data[i].type) && data[i].r > 15) {
					return true;
				}
			}

			return false;
		}

		[[nodiscard]] constexpr auto get_opcode_map() const -> u8 {
			// specify which opcode map a VEX/XOP/EVEX instruction should use
			if(is_evex()) {
				if((flags & 0b11000000) == 0b10000000) { return 0b00101; } // map 5
				if((flags & 0b11000000) == 0b01000000) { return 0b00110; } // map 6
			}
			
			if(is_xop()) {
				switch(enc) {
					case ENC_XOP:    return 0b001001; // map 9
					case ENC_XOP_VM: return 0b001010; // map 10 
					default: ASSERT(false, "unknown xop encoding");
				}
			}

			// compact replacements for legacy 2B and 3B opcodes
			switch((opcode & 0xffff00)) {
				case 0x000f00: return 0b00001; // map 1
				case 0x0f3800: return 0b00010; // map 2
				case 0x0f3a00: return 0b00011; // map 3
				default: ASSERT(false, "unknown opcode for opcode map '{}; received", opcode & 0xffff00);
			}
	
			return 0;
		}

		[[nodiscard]] constexpr auto get_additional_prefix() const -> u8 {
			// additional prefix bytes for VEX/XOP/EVEX instructions
			switch(prefix) {
				case OPERAND_SIZE_OVERRIDE: return 0b01;
				case REP:                   return 0b10;
				case REPNE:                 return 0b11;
				default:                    return 0;
			}
		}

		[[nodiscard]] constexpr auto get_vector_length() const -> u8 {
			ASSERT(is_vex_xop(), "invalid - expected an xop or vex instruction\n");
			// vector length of a VEX/XOP instruction
			// 0 = 128b XMM 
			// 1 = 256b YMM
			if((flags & 0b11000000) == 0b01000000) {
				return true; // /l1 implies a 256b vector length
			}

			return op_size == OPS_256;
		}

		[[nodiscard]] constexpr auto get_evex_zero() const -> u8 {
			switch(operands[0]) {
				case OP_XMM_KZ:	
				case OP_YMM_KZ:	
				case OP_ZMM_KZ: return true; 
				default:        return false;
			}
		}

		[[nodiscard]] constexpr auto get_evex_operand_type() const -> u8 {
			switch(op_size) {
				case OPS_512: return 0b01000000;
				case OPS_256: return 0b00100000;
				default:      return 0;
			}
		}

		[[nodiscard]] auto get_mem_operand() const -> u8 {
			if(is_operand_mem(operands[0])) { return 0; }
			if(is_operand_mem(operands[1])) { return 1; }
			if(is_operand_mem(operands[2])) { return 2; }
			if(is_operand_mem(operands[3])) { return 3; }

			return 0;
		}

		[[nodiscard]] auto has_mem_operand() const -> bool {
			if(is_operand_mem(operands[0])) { return true; }
			if(is_operand_mem(operands[1])) { return true; }
			if(is_operand_mem(operands[2])) { return true; }
			if(is_operand_mem(operands[3])) { return true; }

			return false;
		}

		[[nodiscard]] auto get_broadcast_operand() const -> u8 {
			if(is_operand_broadcast(operands[0])) { return 0; }
			if(is_operand_broadcast(operands[1])) { return 1; }
			if(is_operand_broadcast(operands[2])) { return 2; }
			if(is_operand_broadcast(operands[3])) { return 3; }

			return 0;
		}

		[[nodiscard]] auto has_broadcast_operand() const -> bool {
			if(is_operand_broadcast(operands[0])) { return true; }
			if(is_operand_broadcast(operands[1])) { return true; }
			if(is_operand_broadcast(operands[2])) { return true; }
			if(is_operand_broadcast(operands[3])) { return true; }

			return false;
		}

		[[nodiscard]] auto has_masked_operand() const -> bool {
			if(is_operand_masked(operands[0])) { return true; }
			// only the first operand can be masked

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

	[[nodiscard]] constexpr auto inst(
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

	[[nodiscard]] inline auto inst_size_to_int(inst_size s) -> u16 {
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

	// instruction database, the instructions themselves are generated in tools/tablegen.js 
	constexpr instruction INSTRUCTION_DB[] = {
		#include "assembler/instruction/databases/database.inc"
	};

	constexpr u32 INSTRUCTION_DB_SIZE = sizeof(INSTRUCTION_DB) / sizeof(instruction);
	constexpr u8 MAX_INSTRUCTION_SIZE = 15; // max size of an encoded instruction in bytes

	static_assert(INSTRUCTION_DB_SIZE < 16384, "magic number limit reached");
} // namespace baremetal::assembler

