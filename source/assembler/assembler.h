#pragma once
#include "assembler/assembler_backend.h"
#include "assembler/assembler_lexer.h"
#include "assembler/context.h"

#include <utility/containers/dynamic_string.h>
#include <utility/result.h>

namespace baremetal {
	struct unresolved {
		unresolved() = default;
		unresolved(utility::dynamic_array<operand_type> v, u8 vari, u8 s, u32 pos, u32 i, operand* ops, u8 opc) {
			variants = v;
			variant_index = vari;
			size = s;
			position = pos;
			index = i;
			operand_count = opc;
			
			for(u8 i = 0; i < 4; i++) {
				operands[i] = ops[i];
			}
		}

		u8 size;
		u32 position;

		utility::dynamic_array<operand_type> variants;
		u8 variant_index;

		// instruction
		u32 index;
		operand operands[4];
		u8 operand_count;
	};

	enum patch_type : u8 {
		PATCH_NORMAL,
		PATCH_FIXUP
	};

	struct unresolved_patch {
		u64 index;
	};

	struct resolved_patch {
		u8* data;
		u64 size;
	};

	struct patch {
		patch(patch_type t) : type(t) {}


		
		patch_type type;

		union {
			resolved_patch   res;
			unresolved_patch unres;
		};
	};

	class assembler {
	public:
		auto assemble(const utility::dynamic_string& source) -> utility::result<void>;
	private:
		auto tokenize(const utility::dynamic_string& source) -> utility::result<void>;
		auto parse_first_pass() -> utility::result<void>;
		auto parse_second_pass() -> utility::result<void>;

		auto parse_instruction() -> utility::result<void>;
		auto parse_identifier() -> utility::result<void>;
		auto parse_label() -> utility::result<void>;
		auto parse_times() -> utility::result<void>;
		auto parse_bits() -> utility::result<void>;
		
		auto parse_identifier_operand() -> utility::result<void>;

		auto get_next_token() -> token;
	private:
		assembler_context m_context;

		token_buffer m_tokens;
		token m_current_token;
		u64 m_token_index;

		utility::string_view* m_current_identifier;

		operand m_operands[4];
		bool m_symbollic_operand;
		u8 m_operand_i;

		u64 m_instruction_offset = 0;

		utility::map<utility::string_view*, u64> m_symbols;
		utility::dynamic_array<unresolved> m_unresolved;

		utility::dynamic_array<u8> m_current_resolved;
		utility::dynamic_array<patch> m_patches;
	};
} // namespace baremetal


