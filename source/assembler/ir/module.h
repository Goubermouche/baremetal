#pragma once
#include "assembler/context.h"
#include "assembler/instruction/operands/operands.h"

namespace baremetal::assembler {
  using namespace utility::types;

  struct instruction_t {
    operand operands[4];
    u32 index;
		u8 size;
  };

  struct instruction_block {
		enum type {
			INSTRUCTION,
			BRANCH, 
			LABEL
		};

		u64 start_position; // start position of this segment in bytes
		u64 lenght;         // length of this segment in bytes

		utility::string_view* name;

    instruction_t** instructions;
    u64 size;
		type ty;

		bool new_segment = false;
  };

  struct module_t {
		struct symbol {
			u64 position;
			u64 block_index;
		};

    module_t(context* ctx);

    void add_instruction(const operand* operands, u32 index, u8 size);
		void add_symbol(utility::string_view* name);

		void begin_block(instruction_block::type ty, utility::string_view* name);

		auto emit_graph() -> utility::dynamic_string;
		auto instruction_block_to_string(const instruction_block* block);
		auto register_to_string(reg r) -> const char*;
		auto immediate_to_string(imm i) -> utility::dynamic_string;
		auto memory_to_string(mem memory) -> utility::dynamic_string;
		auto operand_to_string(const operand& op) -> utility::dynamic_string;

		// CFG stuff
		void simplify_cfg();
		auto create_new_block(instruction_block::type ty) -> instruction_block*;

		void recalculate_block_sizes();

		// optimizations 
		void optimize_instruction_size();
		void optimize_instruction_size(instruction_t* inst);
  private:
    context* m_ctx;

    utility::dynamic_array<instruction_block*> m_blocks;
    utility::dynamic_array<instruction_t*> m_current_block;
		utility::string_view* m_current_block_name = nullptr;

		u64 m_current_start_position = 0;
		u64 m_current_segment_length = 0;
		
		utility::map<utility::string_view*, symbol> m_symbols;
  };
} // namespace baremetal::assembler
