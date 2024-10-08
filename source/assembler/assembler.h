#pragma once
#include "assembler/instruction/instruction.h"
#include "assembler/assembler_lexer.h"
#include "assembler/context.h"

namespace baremetal {
	namespace detail {
		// TODO:
		inline auto inst_match(operand_type a, operand b) -> bool{
			switch(a) {
				case OP_FS:      return b.type == OP_SREG && b.r == fs;
				case OP_GS:      return b.type == OP_SREG && b.r == gs;
				case OP_AL:      return b.type == OP_R8 && b.r == al;
				case OP_AX:      return b.type == OP_R16 && b.r == ax;
				case OP_EAX:     return b.type == OP_R32 && b.r == eax;
				case OP_RAX:     return b.type == OP_R64 && b.r == rax;
				case OP_CL:      return b.type == OP_R8 && b.r == cl;
				case OP_DX:      return b.type == OP_R16 && b.r == dx;
				case OP_ECX:     return b.type == OP_R32 && b.r == ecx;
				case OP_RCX:     return b.type == OP_R64 && b.r == rcx;
				case OP_ST0:     return b.type == OP_ST && b.r == st0;
				case OP_MEM:     return b.type == OP_M128;
				case OP_VM64X:   return b.type == OP_VM32X || a == b.type;
				case OP_VM64Y:   return b.type == OP_VM32Y || a == b.type;
				case OP_VM64Z:   return b.type == OP_VM32Z || a == b.type;
				case OP_VM64X_K: return b.type == OP_VM32X_K || a == b.type;
				case OP_VM64Y_K: return b.type == OP_VM32Y_K || a == b.type;
				case OP_VM64Z_K: return b.type == OP_VM32Z_K || a == b.type;
				case OP_M256:    return b.type == OP_M128;
				case OP_M512:    return b.type == OP_M128;
				case OP_TMEM:    return b.type == OP_M128;
				default:         return a == b.type;
			}
		}

		inline auto mask_operand(operand_type op, mask_type mask) -> utility::result<operand_type> {
			ASSERT(is_mask_broadcast(mask) == false, "cannot mask operand using a broadcast\n");

			if(mask > 8) {
				// {k} {z}
				switch(op) {
					case OP_XMM: return OP_XMM_KZ;
					case OP_YMM: return OP_YMM_KZ;
					case OP_ZMM: return OP_ZMM_KZ;
					default:     return utility::error("operand cannot have a zeroing mask");
				}
			}
			else {
				// {k}
				switch(op) {
					case OP_VM32X: return OP_VM32X_K;
					case OP_VM32Y: return OP_VM32Y_K;
					case OP_VM32Z: return OP_VM32Z_K;
					case OP_M16:   return OP_M16_K;
					case OP_M32:   return OP_M32_K;
					case OP_M64:   return OP_M64_K;
					case OP_M128:  return OP_M128_K; 
					case OP_M256:  return OP_M256_K; 
					case OP_M512:  return OP_M512_K;
					case OP_XMM:   return OP_XMM_K;
					case OP_YMM:   return OP_YMM_K;
					case OP_ZMM:   return OP_ZMM_K;
					case OP_K:     return OP_K_K;  
					default:       return utility::error("operand cannot have a mask");
				}	
			}

			return OP_NONE; // unreachable
		}

		inline auto imm_to_scale(const imm& i) -> utility::result<scale> {
			switch(i.value) {
				case 1: return SCALE_1;
				case 2: return SCALE_2;
				case 4: return SCALE_4;
				case 8: return SCALE_8;
				default: return utility::error("invalid memory scale");
			}
		}

		inline auto is_operand_match(const instruction& inst, operand* operands, u8 broadcast_n, u8 count) -> bool {
		// TODO: this entire thing needs to go
			for(u8 i = 0; i < count; ++i) {
				if(
					!(inst_match(inst.operands[i], operands[i])) &&
					!(is_operand_imm(inst.operands[i]) && is_operand_imm(operands[i].type)) &&
					!(is_operand_moff(inst.operands[i]) && is_operand_moff(operands[i].type)) &&
					!(is_operand_masked_mem(inst.operands[i]) && is_operand_masked_mem(operands[i].type)) &&
					!(is_operand_rel(inst.operands[i]) && is_operand_imm(operands[i].type)) &&
					!(is_operand_imm(inst.operands[i]) && operands[i].unknown) &&
					!(is_operand_rel(inst.operands[i]) && operands[i].unknown)
				) {
					return false;
				}

				if(is_operand_reg(operands[i].type) && operands[i].r > 15 && !inst.is_evex()) {
					return false;
				}

				if(
					inst.has_broadcast_operand() &&
					broadcast_to_bits(inst.operands[inst.get_broadcast_operand()]) * broadcast_n != inst_size_to_int(inst.op_size)
				) {
					return false;
				}
			}
	
			return true;
		}
	}

	struct relocation {
		utility::string_view* symbol;
		u64 position;
		u8 size;
	};

	enum fixup_type : u8 {
		FIXUP_DISPLACEMENT // memory base fixup
	};

	struct unresolved_subsection {
		// instruction
		u32 index;           // refers to the fist valid instruction variant in the instruction database
		operand operands[4]; // operands extracted by the parser
		u8 operand_count;

		// updated by the resolve_symbols() function, on creation it should contain the pessimistic
		// (worst case) values, ie. the longest possbile encoding
		u64 position; // current position of the instruction
		u8 size;      // current size of the instruction

		utility::dynamic_array<operand_type> variants; // valid variants of the provided instruction;
		u8 unresolved_operand;                         // index of the unresolved operand
		fixup_type fixup;
	};

	enum subsection_type : u8 {
		SS_NONE = 0,
		SS_NORMAL,
		SS_FIXUP
	};

	struct subsection {
		subsection_type type;

		union {
			struct {
				u8* data;
				u64 size;	
			} resolved;     // regular section, with assembled code
			u64 unresolved; // index into m_unresolved, references an instrucion with unresolved operands
		};
	};

	struct section {
		void update_positions(u64 position, i32 diff);

		utility::string_view* name;
		bool is_empty = false; // whether the section contains any data
		u64 position = 0;      // position of the entire section within the binary
		u64 offset = 0;        // local instruction offset

		// list of subsections which is concatenated during emission
		utility::dynamic_array<subsection> subsections; 
		// list of instructions with unresolved operands, subset of 'subsections'
		utility::dynamic_array<unresolved_subsection> unresolved; 
		// symbol table, location of every symbol is relative to the respective section
		utility::map<utility::string_view*, u64> symbols;
	};

	class assembler {
	public:
		struct module {
			utility::dynamic_array<u8> bytes;	
		};

		assembler();

		auto assemble(const utility::dynamic_string& source) -> utility::result<assembler::module>;
	private:
		auto tokenize(const utility::dynamic_string& source) -> utility::result<void>;
		auto emit_module() -> utility::result<assembler::module>;
		auto resolve_symbols() -> utility::result<void>;
		auto parse() -> utility::result<void>;

		// parsing
		auto parse_reserve_memory() -> utility::result<void>;
		auto parse_define_memory() -> utility::result<void>;
		auto parse_instruction() -> utility::result<void>;
		auto parse_identifier() -> utility::result<void>;
		auto parse_section() -> utility::result<void>;
		auto parse_label() -> utility::result<void>;
		auto parse_times() -> utility::result<void>;
		auto parse_bits() -> utility::result<void>;
	
		auto parse_broadcast_operand(mask_type mask) -> utility::result<void>;
		auto parse_memory_operand(data_type type) -> utility::result<void>;
		auto parse_moff_operand(data_type type) -> utility::result<void>;
		auto parse_identifier_operand() -> utility::result<void>;
		auto parse_immediate_operand() -> utility::result<void>;
		auto parse_register_operand() -> utility::result<void>;
		auto parse_rip_rel_operand() -> utility::result<void>;
		auto parse_type_operand() -> utility::result<void>;
		auto parse_operand_char() -> utility::result<void>;

		auto parse_mask_or_broadcast() -> utility::result<mask_type>; 
		auto parse_memory(operand& op) -> utility::result<void>;
		auto get_next_token() -> token;
	private:
		void set_section(utility::string_view* name);
		void create_normal_subsection();
		auto get_symbol_global(utility::string_view* name) -> u64;
		auto get_symbol_local(utility::string_view* name) -> u64;
	private:
		assembler_context m_context;

		// parsing
		utility::string_view* m_current_identifier;
		token_buffer m_tokens;
		token m_current_token;
		u64 m_token_index;

		// instruction parsing
		u32 m_instruction_i;
		operand m_operands[4];
		bool m_symbolic_operand;
		u8 m_broadcast_n;
		u8 m_operand_i;
		u8 m_unresolved_index;
		fixup_type m_fixup;

		// temporary array with bytes representing resolved instructions
		utility::dynamic_array<u8> m_current_resolved;

		// sections
		utility::dynamic_array<section> m_sections;
		u64 m_section_index;
	};
} // namespace baremetal

