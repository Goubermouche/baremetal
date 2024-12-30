#pragma once
#include "assembler/context.h"
#include "assembler/backend.h"

namespace baremetal::assembler {
	using namespace utility::types;

	struct instruction_data {
		operand operands[4];
		u32 index;
		u8 size;
	};

	enum basic_block_type : u8 {
		BB_INSTRUCTION, // block containing at least one instruction
		BB_BRANCH,      // subset of BB_INSTRUCTION, contains one branch/jump instruction
		BB_LABEL,       // basic label block, contains no instructions
		BB_DATA         // block containing arbitrary binary data
	};

	struct basic_block {
		struct instruction_block {
			instruction_data** data; // instructions 
			u64 size;                // number of instructions
		};

		struct label_block {
			utility::string_view* name;
		};

		struct data_block {
			u8* data;
			u64 size;
		};

		auto is_instruction_block() const -> bool;
		auto is_data_block() const -> bool;

		basic_block_type type;

		u64 section_index;  // index of the parent section
		u64 start_position; // start position of this block in bytes
		u64 size;           // block size in bytes 

		u64 incoming_control_edge_count = 0;

		union {
			instruction_block instructions;
			label_block label;
			data_block data;
		};
  };

	struct section {
		struct symbol {
			u64 position;    // offset within the local section
			u64 block_index; // global block index (across all sections)
		};

		utility::string_view* name;

		u64 position = 0;  // aligned section position
		u64 offset = 0;    // current offset of the section, only used when a section is being constructed
		u64 size = 0;      // unaligned size of this section, in bytes

		utility::map<utility::string_view*, symbol> symbols;
		utility::dynamic_array<basic_block*> blocks;

		u64 current_block_position = 0;
		u64 current_block_size = 0;
	};

	struct module {
		module(context* ctx);

		void add_instruction(const operand* operands, u32 index, u8 size);
		void add_symbol(utility::string_view* name);
		
		void add_instruction_block(basic_block_type ty);
		void add_label_block(utility::string_view* name);
		void add_data_block(const utility::dynamic_array<u8>& data);

		void set_section(utility::string_view* name);
	
		auto get_global_symbol_position(utility::string_view* name) const -> u64;
		auto get_symbol(utility::string_view* name) const -> section::symbol;
		auto get_block_at_index(u64 i) const -> basic_block*;
		auto get_block_count() const -> u64;

		void recalculate_block_sizes();
		void print_section_info();

		auto resolve_instruction(const instruction_data* data, const section& section, u64 position) const -> backend::code;

		utility::dynamic_array<section> sections;
		context* ctx;
	private:
		u64 m_block_count = 0; // total block count
		u64 m_section_index = 0;

		utility::dynamic_array<instruction_data*> m_current_block;
	};
} // namespace baremetal::assembler
