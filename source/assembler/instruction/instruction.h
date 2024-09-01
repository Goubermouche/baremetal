#pragma once
#include <utility/assert.h>

#include "assembler/instruction/operands/operands.h"

namespace baremetal {
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

	// operand direction
	enum direction : u8 {
		DIR_NORMAL,
		DIR_REVERSE
	};

	enum encoding : u8 {
		// has VEX.vvvv [_______X]
		// encoding     [XXXXXXX_]
		ENC_VEX_NO_VVVV  = 0b00000001,

		// rex
		ENC_REX          = 0b00000010,
		ENC_REX_RM       = 0b00000100,

		// vex
		ENC_VEX_RVM      = 0b00000110,
		ENC_VEX_RMV      = 0b00001000,
		ENC_VEX_VM       = 0b00001010,
		ENC_VEX_RM       = 0b00001100,
		ENC_VEX_RMI      = 0b00001110,

		// evex
		ENC_EVEX_RVM     = 0b00010000,
	};

	enum instruction_extension : u32 {
		IEX_NONE = 0,

		IEX_X64,

		// simd
		IEX_MMX,
		IEX_MMX2,
		IEX_3DNOW,
		IEX_SSE,
		IEX_SSE2,
		IEX_SSE3,
		IEX_SSSE3,
		IEX_SSE4_1,
		IEX_SSE4_2,
		IEX_SSE4A,

		// aes / sha
		IEX_AESNI,
		IEX_SHA,

		// bmi
		IEX_BMI,
		IEX_BMI2,

		// transactional mem
		IEX_RTM,

		// xsave
		IEX_XSAVE,
		IEX_XSAVEC,
		IEX_XSAVES,
		IEX_XSAVEOPT,

		// others
		IEX_ADX,
		IEX_MPX,
		IEX_SMAP,
		IEX_CLFLUSH,
		IEX_CLFLUSHOPT,
		IEX_CLWB,
		IEX_CLZERO,
		IEX_CMOV,
		IEX_CMPXCHG16B,
		IEX_CMPXCHG8B,
		IEX_FXSR,
		IEX_LZCNT,
		IEX_LAHFSAHF,
		IEX_MOVBE,
		IEX_PCLMULQDQ,
		IEX_POPCNT,
		IEX_PREFETCHW,
		IEX_PREFETCHW1,
		IEX_FSGSBASE,
		IEX_RDRAND,
		IEX_RDSEED,
		IEX_RDTSC,
		IEX_RDTSCP,
		IEX_I486,
	};

	enum implied_mandatory_prefix : u8 {
		IMP_NONE = 0b00,
		IMP_66   = 0b01,
		IMP_F3   = 0b10,
		IMP_F2   = 0b11
	};

	enum inst_size : u8 {
		OPS_32,
		OPS_64,
		OPS_128,
		OPS_256,
		OPS_512,
	};

#pragma pack(push, 1)
	struct instruction {
		constexpr instruction() = default;

		constexpr instruction(
			const char* name,
			u32 opcode,
			u16 ilo,
			u8 ext,
			u8 prefix,
			u8 variant,
			u16 context_index,
			u8 operand_count,
			direction operand_direction,
			u8 encoding,
			inst_size ops,
			implied_mandatory_prefix imp,
			operand_type op1,
			operand_type op2,
			operand_type op3,
			operand_type op4
		) : m_name(name),
		m_encoding(encoding),
		m_opcode(opcode),
		m_ilo(ilo),
		m_extension(ext),
		m_prefix(prefix),
		m_variant(variant),
		m_ops(ops),
		m_imp(imp),
		m_special_index(context_index),
		m_operand_count(operand_count),
		m_operand_direction(operand_direction),
		m_operands{ op1, op2, op3, op4 } {}

		void print() const {
			utility::console::print("{} ", m_name);

			for(u8 i = 0; i < 4; ++i) {
				if(m_operands[i] != OP_NONE) {
					utility::console::print("{} ", operand_type_to_string(m_operands[i]));
				}
			}

			utility::console::print("\n");
		}

		constexpr auto is_rexw() const -> bool {
			return m_extension & EXT_REXW;
		}
		constexpr auto is_r() const -> bool {
			return m_extension & EXT_R;
		}
		constexpr auto is_opcode_ext() const -> bool {
			return m_extension & EXT_OP_R;
		}
		constexpr auto is_ext() const -> bool {
			return
				m_extension & EXT_0 ||
				m_extension & EXT_1 ||
				m_extension & EXT_2 ||
				m_extension & EXT_3 ||
				m_extension & EXT_4 ||
				m_extension & EXT_5 ||
				m_extension & EXT_6 ||
				m_extension & EXT_7;
		}
		constexpr auto is_vex() const -> bool {
			switch(get_encoding_prefix()) {
				case ENC_VEX_RVM:
				case ENC_VEX_RMV:
				case ENC_VEX_VM: 
				case ENC_VEX_RMI: 
				case ENC_VEX_RM: return true;
				default: return false;
			}
		}
		constexpr auto is_evex() const -> bool {
			switch(get_encoding_prefix()) {
				case ENC_EVEX_RVM: return true;
				default: return false;
			}
		}

		constexpr auto is_rex() const -> bool {
			switch(get_encoding_prefix()) {
				case ENC_REX: return true;
				default: return false;
			}
		}

		constexpr auto get_ext() const -> u8 {
			// extract the ext_x bits and subtract one to convert them to the
			// specific value
			const u8 masked = m_extension & 0b00011111;
			return masked - 1;
		}
		constexpr auto get_name() const -> const char* {
			return m_name;
		}
		constexpr auto get_direction() const -> bool {
			return m_operand_direction == DIR_NORMAL;
		}
		constexpr auto get_operand_count() const -> u8 {
			return m_operand_count;
		}
		constexpr auto get_prefix() const -> u8 {
			return m_prefix;
		}
		constexpr auto get_extension() const -> u8 {
			return m_extension;
		}
		constexpr auto get_opcode() const -> u32 {
			return m_opcode;
		}
		constexpr auto get_operand(u8 index) const -> operand_type {
			return m_operands[index];
		}
		constexpr auto get_special_kind() const -> u8 {
			return m_special_index >> 14;
		}
		constexpr auto get_special_index() const -> u16 {
			return m_special_index & 0b0011111111111111;
		}
		constexpr auto get_encoding_prefix() const -> encoding {
			return (encoding)(m_encoding & 0b11111110);
		}
		constexpr auto get_ops() const -> inst_size {
			return m_ops;
		}
		constexpr auto has_vex_vvvv() const -> bool {
			return !(m_encoding & ENC_VEX_NO_VVVV); 
		}

		auto get_imm_operand_count() const -> u8 {
			u8 count = 0;

			if(is_operand_imm(m_operands[0])) { count++; }
			if(is_operand_imm(m_operands[1])) { count++; }
			if(is_operand_imm(m_operands[2])) { count++; }
			if(is_operand_imm(m_operands[3])) { count++; }

			return count;
		}
		auto get_reg_operand_count() const -> u8 {
			u8 count = 0;

			if(is_operand_reg(m_operands[0])) { count++; }
			if(is_operand_reg(m_operands[1])) { count++; }
			if(is_operand_reg(m_operands[2])) { count++; }
			if(is_operand_reg(m_operands[3])) { count++; }

			return count;
		}
		auto get_imp() const -> u8 {
			return m_imp;
		}
		auto get_ilo() const -> u16 {
			return m_ilo;
		}
		auto get_variant() const -> u8 {
			return m_variant;
		}

		auto get_mem_operand() const -> u8 {
			if(is_operand_mem(m_operands[0])) { return 0; }
			if(is_operand_mem(m_operands[1])) { return 1; }
			if(is_operand_mem(m_operands[2])) { return 2; }
			if(is_operand_mem(m_operands[3])) { return 3; }

			return 0;
		}

		auto has_mem_operand() const -> bool {
			if(is_operand_mem(m_operands[0])) { return true; }
			if(is_operand_mem(m_operands[1])) { return true; }
			if(is_operand_mem(m_operands[2])) { return true; }
			if(is_operand_mem(m_operands[3])) { return true; }

			return false;
		}

		constexpr auto has_prefix() const -> bool {
			return m_prefix != PREFIX_NONE;
		}
		constexpr auto has_special_index() const -> bool {
			return m_special_index != utility::limits<u16>::max();
		}
		constexpr auto has_variant() const -> bool {
			return m_variant != 8;
		}
	private:
		const char* m_name;

		// encoding
		u8 m_encoding; // REX / VEX / EVEX etc.
		u32 m_opcode;
		u16 m_ilo; // implied leading opcode
		u8 m_extension;
		u8 m_prefix;
		u8 m_variant; // 8 == none
		inst_size m_ops;
		implied_mandatory_prefix m_imp;

		// some instructions have a special optimization index, which points to an alternative variant
		// which can be used depending on the provided operands

		//           [1111111111111111] (65535) is an invalid index => that instruction does not have one
		// kind      [XX______________]
		// index     [__XXXXXXXXXXXXXX]
		u16 m_special_index;

		// operands
		u8 m_operand_count;
		direction m_operand_direction;
		operand_type m_operands[4];
	};
#pragma pack(pop)

	enum encn : u8 {
		ENCN_R,
		ENCN_M,
		ENCN_MR,
		ENCN_RM,
		ENCN_RMR,
		ENCN_NORMAL,
		ENCN_NORMALD, // NORMAL encoding, but interpret the first opcode byte as a separate instruction
									// used by instructions which are formed using two other instructions (ie. fsave)

		// VEX
		ENCN_VEX,
		ENCN_VEX_VM,
		ENCN_VEX_RM,
		ENCN_VEX_MR,
		ENCN_VEX_RVM,
		ENCN_VEX_RMV,
		ENCN_VEX_MVR,
		ENCN_VEX_RVMN, // RVM: VEX, with vvvv set to 1111 (no vvvv)

		// EVEX
		ENCN_EVEX_RVM,
		ENCN_EVEX_MVR,
		ENCN_EVEX_RM,
		ENCN_EVEX_MR,

		// XOP
		ENCN_XOP_VM,
		ENCN_XOP,
	};

	enum opn : u8 {
		OPN_NONE,

		OPN_R8,
		OPN_R16,
		OPN_R32,
		OPN_R64,
		OPN_MMX,
		OPN_XMM,
		OPN_YMM,
		OPN_ZMM,
		OPN_SREG,
		OPN_DREG,
		OPN_CREG,
		OPN_ST,
		OPN_K,
		OPN_BND,

		OPN_K_K,
		OPN_ST0,
		OPN_HIDDEN,
		OPN_I8,
		OPN_M32,
		OPN_M64,
		OPN_M16,
		OPN_I16,
		OPN_M8,
		OPN_I32,
		OPN_AL,
		OPN_EAX,
		OPN_AX,
		OPN_RAX,
		OPN_MIB,
		OPN_MEM,
		OPN_REL32,
		OPN_REL16,
		OPN_M128,
		OPN_M256,
		OPN_M80,
		OPN_DX,
		OPN_REL8,
		OPN_I64,
		OPN_MOFF8,
		OPN_MOFF32,
		OPN_MOFF16,
		OPN_MOFF64,
		OPN_M512,
		OPN_GS,
		OPN_ES,
		OPN_FS,
		OPN_SS,
		OPN_DS,
		OPN_CS,
		OPN_CL,
		OPN_ECX,
		OPN_RCX,

		OPN_XMM_K, // masked XMM reg xmm{k}
		OPN_XMM_KZ, // masked XMM reg xmm{k}{z}
		OPN_YMM_K, // masked YMM reg xmm{k}
		OPN_YMM_KZ, // masked YMM reg xmm{k}{z}
		OPN_ZMM_K, // masked ZMM reg xmm{k}
		OPN_ZMM_KZ, // masked ZMM reg xmm{k}{z},
	};

	enum rmn : u8 {
		RMN_NONE = 0,
		RMN_R,
		RMN_0,
		RMN_1,
		RMN_2,
		RMN_3,
		RMN_4,
		RMN_5,
		RMN_6,
		RMN_7,
	};

	inline auto is_operand_rax(opn op) -> bool {
		switch(op) {
			case OPN_RAX:
			case OPN_EAX:
			case OPN_AX: return true;
			default: return false;
		}
	}

	inline auto is_operand_mem(opn op) -> bool {
		switch(op) {
			case OPN_MEM:
			case OPN_M8:
			case OPN_M16:
			case OPN_M32:
			case OPN_M64:
			case OPN_M80:
			case OPN_M128:
			case OPN_M256:
			case OPN_M512:  return true;
			default: return false;
		}
	}

	struct ins { 
		constexpr auto is_rex() const -> bool {
			switch(encoding) { 
				case ENCN_NORMAL:
				case ENCN_NORMALD:
				case ENCN_MR:
				case ENCN_M:
				case ENCN_RM:
				case ENCN_RMR:
				case ENCN_R: return true;
				default: return false;
			}
		}
		constexpr auto is_vex_xop() const -> bool {
			switch(encoding) {
				case ENCN_XOP:
				case ENCN_XOP_VM:
				case ENCN_VEX:
				case ENCN_VEX_MR:
				case ENCN_VEX_RM:
				case ENCN_VEX_RVM:
				case ENCN_VEX_RVMN:
				case ENCN_VEX_RMV:
				case ENCN_VEX_MVR:
				case ENCN_VEX_VM: return true;
				default: return false;
			}
		}
		constexpr auto is_xop() const -> bool {
			switch(encoding) {
				case ENCN_XOP:
				case ENCN_XOP_VM: return true;
				default: return false;
			}
		}
		constexpr auto is_evex() const -> bool {
			switch(encoding) {
				case ENCN_EVEX_RVM:
				case ENCN_EVEX_RM: return true;
				default: return false;
			}
		}

		constexpr auto is_rexw() const -> bool {
			return flags & 0b00000001;
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
			return (flags & (0b00000010)) == (flags & (0b00011110)) && ((flags & 0b00000010) != 0);
		}
		constexpr auto is_rm() const -> bool {
			u8 rm = flags & 0b00011110;

			if(rm == 0b00000010) {
				return false;
			}

			return rm;
		}
		constexpr auto get_rm() const -> u8 {
			return (flags & 0b00011110) >> 1;
		}

		constexpr auto get_special_kind() const -> u8 {
			return special_index >> 14;
		}
		constexpr auto get_special_index() const -> u16 {
			return special_index & 0b0011111111111111;
		};
		constexpr auto has_special_index() const -> bool {
			return special_index != utility::limits<u16>::max();
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

		const char* name;
		encn encoding;
		u8 prefix;
		u32 opcode;
		u8 flags;
		u16 special_index;
		u8 operand_count;
		inst_size op_size;
		opn operands[4];
	};

	// new tooling
	static constexpr auto inst(const char* name, encn encoding, u8 prefix, u32 opcode, u8 flags, u16 special_index, inst_size op_size, opn op1 = OPN_NONE, opn op2 = OPN_NONE, opn op3 = OPN_NONE, opn op4 = OPN_NONE) -> ins {
		ins result; 

		result.name = name;
		result.encoding = encoding;
		result.prefix = prefix;
		result.opcode = opcode;
		result.flags = flags;
		result.special_index = special_index;
		result.operands[0] = op1;
		result.operands[1] = op2;
		result.operands[2] = op3;
		result.operands[3] = op4;
		result.operand_count = 0;
		result.op_size = op_size;

		for(u8 i = 0; i < 4; ++i) {
			if(result.operands[i] == OPN_NONE) {
				break;
			}

			result.operand_count++;
		}

		return result;
	}

	static constexpr ins inst_db[] = {
		#include "assembler/instruction/databases/database.inc"
	};
	
	struct opn_data {
		constexpr opn_data() : type(OPN_NONE), r(0) {}

		// immediates
		constexpr opn_data(imm i) : type(OPN_I64), immediate(i) {}

		// registers
		static_assert(static_cast<u8>(REG_GP_8) == static_cast<u8>(OP_REG8));
		static_assert(static_cast<u8>(REG_GP_16) == static_cast<u8>(OP_REG16));
		static_assert(static_cast<u8>(REG_GP_32) == static_cast<u8>(OP_REG32));
		static_assert(static_cast<u8>(REG_GP_64) == static_cast<u8>(OP_REG64));
		static_assert(static_cast<u8>(REG_XMM) == static_cast<u8>(OP_XMM));
		static_assert(static_cast<u8>(REG_YMM) == static_cast<u8>(OP_YMM));
		static_assert(static_cast<u8>(REG_MMX) == static_cast<u8>(OP_MMX));

		constexpr opn_data(reg r) : type(static_cast<opn>(r.type)), r(r.index) {}

		// memory
		constexpr opn_data(mem_address m) : type(OPN_MEM), memory(m) {}
		constexpr opn_data(moff m) : type(OPN_MOFF64), memory_offset(m) {}
		constexpr opn_data(mem256 m) : type(OPN_M256), memory(m) {}
		constexpr opn_data(mem128 m) : type(OPN_M128), memory(m) {}
		constexpr opn_data(mem80 m) : type(OPN_M80), memory(m) {}
		constexpr opn_data(mem64 m) : type(OPN_M64), memory(m) {}
		constexpr opn_data(mem32 m) : type(OPN_M32), memory(m) {}
		constexpr opn_data(mem16 m) : type(OPN_M16), memory(m) {}
		constexpr opn_data(mem8 m) : type(OPN_M8), memory(m) {}

		constexpr opn_data(rel r) : type(OPN_REL32), relocation(r) {}

		opn type;

		union {
			moff memory_offset;
			rel relocation;
			imm immediate;
			mem memory;
			u8 r; // register
			masked_reg mr; // masked register
		};
	};

// instruction generators
#define INST_0(name, opcode, ext, prefix, ctx, dir, enc, ops, imp, ilo, var, empty) \
  instruction(                                                                      \
    #name,                                                                          \
    opcode,                                                                         \
    ilo,                                                                            \
    ext,                                                                            \
    prefix,                                                                         \
    var,                                                                            \
    ctx,                                                                            \
    0,                                                                              \
    direction::DIR_ ## dir,                                                         \
    enc,                                                                            \
		OPS_ ## ops,                                                                    \
    IMP_ ## imp,                                                                    \
    OP_NONE,                                                                        \
    OP_NONE,                                                                        \
    OP_NONE,                                                                        \
    OP_NONE                                                                         \
  ),

#define INST_1(name, opcode, ext, prefix, ctx, dir, enc, ops, imp, ilo, var,  op1) \
  instruction(                                                               \
    #name,                                                                   \
    opcode,                                                                  \
    ilo   ,                                                                  \
    ext,                                                                     \
    prefix,                                                                  \
    var,                                                                     \
    ctx,                                                                     \
    1,                                                                       \
    direction::DIR_ ## dir,                                                  \
		enc,                                                                     \
		OPS_ ## ops,                                                             \
    IMP_ ## imp,                                                             \
    OP_ ## op1,                                                              \
    OP_NONE,                                                                 \
    OP_NONE,                                                                 \
    OP_NONE                                                                  \
  ),

#define INST_2(name, opcode, ext, prefix, ctx, dir, enc, ops, imp, ilo, var, op1, op2) \
  instruction(                                                                    \
    #name,                                                                        \
    opcode,                                                                       \
    ilo   ,                                                                       \
    ext,                                                                          \
    prefix,                                                                       \
    var,                                                                          \
    ctx,                                                                          \
    2,                                                                            \
    direction::DIR_ ## dir,                                                       \
		enc,                                                                          \
		OPS_ ## ops,                                                                  \
		IMP_ ## imp,                                                                  \
    OP_ ## op1,                                                                   \
    OP_ ## op2,                                                                   \
    OP_NONE,                                                                      \
    OP_NONE                                                                       \
  ),

#define INST_3(name, opcode, ext, prefix, ctx, dir, enc, ops, imp, ilo, var,op1, op2, op3) \
  instruction(                                                                         \
    #name,                                                                             \
    opcode,                                                                            \
    ilo,                                                                               \
    ext,                                                                               \
    prefix,                                                                            \
    var,                                                                               \
    ctx,                                                                               \
    3,                                                                                 \
    direction::DIR_ ## dir,                                                            \
		enc,                                                                               \
		OPS_ ## ops,                                                                       \
		IMP_ ## imp,                                                                       \
    OP_ ## op1,                                                                        \
    OP_ ## op2,                                                                        \
    OP_ ## op3,                                                                        \
    OP_NONE                                                                            \
  ),

#define INST_4(name, opcode, ext, prefix, ctx, dir, enc, ops, imp, ilo, var, op1, op2, op3, op4) \
  instruction(                                                                              \
    #name,                                                                                  \
    opcode,                                                                                 \
    ilo   ,                                                                                 \
    ext,                                                                                    \
    prefix,                                                                                 \
    var,                                                                                    \
    ctx,                                                                                    \
    4,                                                                                      \
    direction::DIR_ ## dir,                                                                 \
		enc,                                                                                    \
		OPS_ ## ops,                                                                            \
		IMP_ ## imp,                                                                            \
    OP_ ## op1,                                                                             \
    OP_ ## op2,                                                                             \
    OP_ ## op3,                                                                             \
    OP_ ## op4                                                                              \
  ),

// select which INST_X to call based off of the variable argument count (0-2)
#define INST_SELECT(count) CONCATENATE(INST_, count)
#define INST_HELPER(count, name, ...) EXPAND(INST_SELECT(count)(name, __VA_ARGS__))
#define INST(name, opcode, extensions, prefix, context, dir, enc, imp, ilo, var, ops, iext, ...) \
  INST_HELPER(GET_ARG_COUNT(__VA_ARGS__), name, opcode, extensions, prefix, context, dir, enc, ops, imp, ilo, var, __VA_ARGS__)

	static constexpr instruction instruction_db[] = {
		#include "assembler/instruction/databases/instruction_database.inc"
	};

inline auto is_operand_xmm(opn op) -> bool {
	return op == OPN_XMM || op == OPN_XMM_K || op == OPN_XMM_KZ;
}

inline auto is_operand_ymm(opn op) -> bool {
	return op == OPN_YMM || op == OPN_YMM_KZ || op == OPN_YMM_K;
}

inline auto is_operand_zmm(opn op) -> bool {
	return op == OPN_ZMM || op == OPN_ZMM_K || op == OPN_ZMM_KZ;
}

inline auto is_operand_large_reg(opn op) -> bool {
	return is_operand_xmm(op) || is_operand_ymm(op) || is_operand_zmm(op);
}
 
	inline auto is_operand_moff(opn op) -> bool {
		switch(op) {
			case OPN_MOFF8:
			case OPN_MOFF16:
			case OPN_MOFF32:
			case OPN_MOFF64:  return true;
			default: return false;
		}
	}

	inline auto is_operand_imm(opn op) -> bool {
		switch(op) {
			case OPN_I8:
			case OPN_I16:
			case OPN_I32:
			case OPN_I64:  return true;
			default: return false;
		}
	}

	inline auto is_operand_rel(opn op) -> bool {
		switch(op) {
			case OPN_REL8:
			case OPN_REL16:
			case OPN_REL32: return true;
			default: return false;
		}
	}

	inline auto is_operand_reg(opn op) -> bool {
		switch(op) {
			case OPN_R8:
			case OPN_R16:
			case OPN_R32:
			case OPN_R64:
			case OPN_XMM:
			case OPN_XMM_KZ:
			case OPN_XMM_K:
			case OPN_YMM:
			case OPN_YMM_K:
			case OPN_YMM_KZ:
			case OPN_ZMM:
			case OPN_ZMM_K:
			case OPN_ZMM_KZ:
			case OPN_MMX:
			case OPN_SREG:
			case OPN_DREG:
			case OPN_CREG:
			case OPN_AL:
			case OPN_AX:
			case OPN_EAX:
			case OPN_RAX:
			case OPN_CL:
			case OPN_DX:
			case OPN_ECX:
			case OPN_RCX:
			case OPN_ST0:
			case OPN_ST:
			case OPN_K:
			case OPN_K_K:
			case OPN_BND: return true;
			default: return false;
		}
	}

	inline auto is_extended_reg(const opn_data& op) -> bool {
		if(is_operand_reg(op.type)) {
			return op.r >= 8;
		}

		return false;
	}

	inline auto get_operand_bit_width(opn op) -> u16 {
		switch(op) {
			case OPN_MEM:
			case OPN_NONE:        return 0;
			case OPN_MOFF8:
			case OPN_M8:
			case OPN_REL8:
			case OPN_R8:
			case OPN_AL:
			case OPN_CL: 
			case OPN_I8:          return 8;
			case OPN_MOFF16:
			case OPN_REL16:
			case OPN_M16:
			case OPN_R16:
			case OPN_SREG:
			case OPN_GS:
			case OPN_ES:
			case OPN_FS:
			case OPN_SS:
			case OPN_DS:
			case OPN_CS:
			case OPN_AX:
			case OPN_DX:
			case OPN_I16:         return 16;
			case OPN_MOFF32:
			case OPN_M32:
			case OPN_REL32:
			case OPN_R32:
			case OPN_EAX:
			case OPN_ECX:
			case OPN_I32:         return 32;
			case OPN_MOFF64:
			case OPN_M64:
			case OPN_R64:
			case OPN_CREG:
			case OPN_DREG:
			case OPN_MMX:
			case OPN_BND:
			case OPN_RCX:
			case OPN_RAX:
			case OPN_MIB:
			case OPN_K_K:
			case OPN_K:
			case OPN_I64:         return 64;
			case OPN_ST:
			case OPN_ST0:
			case OPN_M80:         return 80;
			case OPN_M128:
			case OPN_XMM:
			case OPN_XMM_K:
			case OPN_XMM_KZ:      return 128;
			case OPN_M256:
			case OPN_YMM_K:         
			case OPN_YMM_KZ:         
			case OPN_YMM:         return 256;
			case OPN_ZMM_K:
			case OPN_ZMM_KZ:
			case OPN_M512:
			case OPN_ZMM:       return 512;
			case OPN_HIDDEN:    return 0;
		}

		return 0; // unreachable
	}

	inline auto is_operand_masked(opn op) -> bool {
		switch(op) {
			case OPN_K_K:
			case OPN_ZMM_K:
			case OPN_ZMM_KZ:
			case OPN_YMM_K:
			case OPN_YMM_KZ:
			case OPN_XMM_K:
			case OPN_XMM_KZ: return true;
			default: return false;
		}
	}

#undef INST_0
#undef INST_1
#undef INST_2
#undef INST_3
#undef INST_4

#undef INST_SELECT
#undef INST_HELPER

#undef INST
} // namespace baremetal
