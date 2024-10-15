#pragma once
#include "assembler/context.h"
#include <utility/allocators/block_allocator.h>

namespace baremetal::assembler {
  using namespace utility::types;

  struct instruction_t {
    struct operand {
			union {
				utility::string_view* branch_to;
			};
    };

    operand operands[4];
    u32 index;
  };

  struct instruction_block {
		utility::string_view* name;
    instruction_t** instructions;
    u64 size;
  };

  struct module_t {
    module_t(context* ctx);

    void add_instruction(const instruction_t::operand* operands, u32 index);
		void begin_block(utility::string_view* name);

		auto emit_graph() -> utility::dynamic_string;
  private:
    context* m_ctx;

    utility::dynamic_array<instruction_block*> m_blocks;
    utility::dynamic_array<instruction_t*> m_current_block;
		utility::string_view* m_current_block_name = nullptr;
  };
} // namespace baremetal::assembler
