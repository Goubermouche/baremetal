#include "cfg_minimize_pass.h"
#include "assembler/backend.h"

namespace baremetal::assembler::pass {
	void cfg_minimize(module_t& module) {
		struct edge {
			u32 in;
			u32 out;
		};
			
		utility::console::print("[cfg minimize]: minimizing {} blocks\n", module.m_blocks.get_size());

		// blocks which have an edge leading into them
		utility::dynamic_array<edge> edge_connections(module.m_blocks.get_size(), { 0, 0 });
		utility::dynamic_array<instruction_block*> blocks;

		module.m_current_block_name = nullptr;
		module.m_current_start_position = 0;
		module.m_current_segment_length = 0;
		module.m_current_block.clear();

		// calculate edge connections
		for(u64 i = 0; i < module.m_blocks.get_size(); ++i) {
			const instruction_block* block = module.m_blocks[i];

			if(block->size == 0) {
				continue; 
			}

			const instruction_t* last_inst = block->instructions[block->size - 1];

			if(is_jump_or_branch_inst(last_inst->index)) {
				// TODO: check if its an actual symbol
				// BRANCH_IN always has a priority
				edge_connections[module.m_symbols.at(last_inst->operands[0].symbol).block_index].in++; // branch - pass case - incoming edge

				if(i < module.m_blocks.get_size() - 1) {
					edge_connections[i + 1].in++; // branch - fail case - incoming edge (next block)
				}

				edge_connections[i].out++; // a branch instruction always outputs somewhere - mark us as having an outgoing edge
			}
		}

		// generate new blocks 
		for(u64 i = 0; i < edge_connections.get_size(); ++i) {
			const instruction_block* block = module.m_blocks[i];
			module.m_current_block_name = block->name;
			module.m_current_section = block->section_index;
			module.m_current_block.insert(module.m_current_block.end(), block->instructions, block->instructions + block->size);

			switch(block->ty) {
				case instruction_block::LABEL: {
					auto new_block = module.create_new_block(block->ty);
					new_block->new_segment = edge_connections[i].in > 0;
					blocks.push_back(new_block);
					break;
				}
				case instruction_block::INSTRUCTION: {
					auto new_block = module.create_new_block(block->ty);
					blocks.push_back(new_block);
					break;
				}
				case instruction_block::BRANCH: {
					auto new_block = module.create_new_block(block->ty);
					blocks.push_back(new_block);
					break;
				}
			}
		}

		for(u64 i = 0; i < module.m_blocks.get_size(); ++i) {
			const instruction_block* block = module.m_blocks[i];

			if(block->ty == instruction_block::LABEL) {
				module.m_symbols[block->name].block_index = i;
			}
		}

		module.m_blocks = blocks;
	}
} // namespace baremetal::assembler::pass

