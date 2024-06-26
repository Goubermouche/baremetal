#include "x64_target.h"

namespace baremetal {
	x64_target::x64_target(context& context)
	: target(context, x64::create_architecture()) {
		m_isel_functions.resize(context.m_index_map.size());

		m_isel_functions[context.get_dialect_index<core_dialect>()] = { x64::select_instruction_core };
		m_isel_functions[context.get_dialect_index<gpu_dialect>()]  = { x64::select_instruction_gpu  };
	}
	
	void x64_target::select_instructions(machine_context& context) {
		ASSERT(
			context.work.get_size() == context.cfg.get_size(),
			"basic block work list mismatch"
		);

		context.basic_block_order.reserve(context.cfg.get_size());
		context.values.resize(context.function->get_node_count());

		m_assembler.set_allocator(*context.function);
		m_context = &context;

		define_basic_block_order();
		select_instructions();
	}

	auto x64_target::get_context() const -> ptr<machine_context> {
		return m_context;
	}

	auto x64_target::get_assembler() -> x64::assembler& {
		return m_assembler;
	}

	void x64_target::define_basic_block_order() const {
		constexpr ir::node_id exit_id(0, static_cast<u16>(core_node_id::EXIT));
		constexpr ir::node_id phi_id(0, static_cast<u16>(core_node_id::PHI));

		i32 exit_basic_block = -1;

		// define all PHIs early and sort the basic block order
		for(i32 i = 0; i < static_cast<i32>(m_context->cfg.get_size()); ++i) {
			const ptr<ir::node> basic_block = m_context->work[i];
			const ptr<ir::node> exit = m_context->cfg.at(basic_block).exit;

			for(ptr<ir::user> user = basic_block->users; user; user = user->next) {
				const ptr<ir::node> node = user->target;

				if(
					node->get_id() == phi_id &&
					node->get_data_type().get_id() != static_cast<u8>(ir::data_type_id::MEMORY)
				) {
					m_context->work.is_visited(node); // mark the current node as visited
					m_context->values[node->get_global_value_index()] = {
						.virtual_register = reg{},
						.use_count = std::numeric_limits<i32>::max()
					};
				}
			}

			if(exit->get_id() == exit_id) {
				exit_basic_block = i;
			}
			else {
				m_context->basic_block_order.push_back(i);
			}
		}

		// the exit block should be the last one we visit
		if(exit_basic_block >= 0) {
			m_context->basic_block_order.push_back(exit_basic_block);
		}
	}

	void x64_target::select_instructions() {
		for(u64 i = 0; i < m_context->work.get_size(); ++i) {
			const ptr<ir::node> basic_block = m_context->work[i];

			if(i + 1 < m_context->work.get_size()) {
				m_context->fallthrough_label = m_context->basic_block_order[i + 1];
			}
			else {
				m_context->fallthrough_label = std::numeric_limits<i32>::max();
			}

			// create the block label and append it to the instruction list
			const ptr<instruction> label = m_assembler.create_label(basic_block);
			m_context->append_instruction(label);

			// select instructions for the current block
			const ptr<ir::node> block_exit = m_context->cfg.at(basic_block).exit;
			select_region_instructions(basic_block, block_exit, i);
		}
	}

	void x64_target::greedy_schedule(ptr<ir::basic_block> block, ptr<ir::node> block_exit) const {
		constexpr ir::node_id projection_id(0, static_cast<u16>(core_node_id::PROJECTION));
		constexpr ir::node_id region_id(0, static_cast<u16>(core_node_id::REGION));
		constexpr ir::node_id phi_id(0, static_cast<u16>(core_node_id::PHI));

		const ptr<ir::user> successor = detail::get_next_control_flow_user(block_exit);
		ptr<scheduled_node> top = create_scheduled_node(nullptr, block_exit);

		// phis
		std::vector<scheduled_phi> phis;
		u64 current_phi = 0;

		// leftovers
		const u64 leftover_count = block->items.size();
		u64 leftovers = 0;

		phis.reserve(256);

		if(successor && successor->target->get_id() == region_id) {
			fill_phi_nodes(phis, successor->target, successor->slot);
		}

		m_context->work.is_visited(block_exit);

		while(top != nullptr) {
			ptr<ir::node> current = top->node;

			// resolve inputs first
			if(current->get_id() != phi_id && top->index < current->inputs.get_size()) {
				const ptr<ir::node> input = current->inputs[top->index++];

				if(input != nullptr && is_scheduled_in_block(block, input)) {
					top = create_scheduled_node(top, input);
				}

				continue;
			}

			// resolve anti dependencies
			if(top->antis) {
				const ptr<ir::user> next = top->antis->next;
				const ptr<ir::node> anti = top->antis->target;

				if(anti != current && top->antis->slot == 1 && is_scheduled_in_block(block, anti)) {
					top = create_scheduled_node(top, anti);
				}

				top->antis = next;
				continue;
			}

			// resolve phi edges & leftovers when we're at the endpoint
			if(block_exit == current) {
				// skip non-phis
				if(current_phi < phis.size()) {
					const ptr<ir::node> phi = phis[current_phi].phi;
					const ptr<ir::node> val = phis[current_phi].node;

					current_phi++;

					// reserve PHI space
					if(val->get_data_type().get_id() != static_cast<u8>(ir::data_type_id::MEMORY)) {
						phi_value p{
							.phi = phi,
							.node = val,
							.destination = {},
							.source = {}
						};

						m_context->phi_values.push_back(p);
					}

					if(is_scheduled_in_block(block, val)) {
						top = create_scheduled_node(top, val);
					}
					continue;
				}

				// resolve leftover nodes placed here by GCM
				if(leftovers < leftover_count) {
					auto it = block->items.begin();
					std::advance(it, leftovers);

					if(!m_context->work.is_visited(it->get())) {
						top = create_scheduled_node(top, it->get());
					}

					leftovers++;
					continue;
				}
			}

			m_context->work.push_back(current);
			top = top->parent;

			// push outputs (projections, if they apply)
			if(current->get_data_type().get_id() == static_cast<u8>(ir::data_type_id::TUPLE)) {
				for(ptr<ir::user> user = current->users; user; user = user->next) {
					if(
						user->target->get_id() == projection_id && 
						!m_context->work.is_visited(user->target)
					) {
						m_context->work.push_back(user->target);
					}
				}
			}
		}
	}

	void x64_target::select_region_instructions(ptr<ir::node> block_entry, ptr<ir::node> block_exit, u64 index) {
		constexpr ir::node_id projection_id(0, static_cast<u16>(core_node_id::PROJECTION));
		constexpr ir::node_id region_id(0, static_cast<u16>(core_node_id::REGION));
		constexpr ir::node_id entry_id(0, static_cast<u16>(core_node_id::ENTRY));
		constexpr ir::node_id phi_id(0, static_cast<u16>(core_node_id::PHI));

		ASSERT(m_context->work.get_size() == m_context->cfg.get_size(), "basic block work list mismatch");
		const ptr<ir::basic_block> basic_block = m_context->schedule.at(block_entry);
		std::vector<phi_value>& phi_values = m_context->phi_values;

		// topological sort
		greedy_schedule(basic_block, block_exit);

		if(index == 0) {
			for(ptr<ir::user> user = m_context->function->get_entry()->users; user; user = user->next) {
				const ptr<ir::node> node = user->target;

				if(node->get_id() == projection_id && !m_context->work.is_visited(node)) {
					// function entry blocks & their projections should be selected as well
					m_context->work.push_back(node);
				}
			}
		}

		// define all nodes in this basic block
		for(u64 i = m_context->cfg.get_size(); i < m_context->work.get_size(); ++i) {
			const ptr<ir::node> node = m_context->work[i];

			// track non-dead users
			u64 use_count = 0;
			for(ptr<ir::user> user = node->users; user; user = user->next) {
				// user is scheduled == valid user
				if(m_context->schedule.contains(user->target)) {
					use_count++;
				}
			}

			m_context->values[node->get_global_value_index()] = virtual_value{
				.virtual_register = reg{},
				.use_count = static_cast<i32>(use_count),
			};
		}

		// every phi node should view itself as the previous value, not the new one we're producing
		const u64 our_phis = phi_values.size();

		for(u64 i = 0; i < our_phis; ++i) {
			phi_value& value = phi_values[i];
			value.destination = get_virtual_register(value.phi);
		}

		if(block_entry->get_id() == region_id) {
			for(ptr<ir::user> user = block_entry->users; user; user = user->next) {
				if(
					user->target->get_id() == phi_id &&
					user->target->get_data_type().get_id() != static_cast<u8>(ir::data_type_id::MEMORY)
				) {
					const ptr<virtual_value> value = &m_context->values[user->target->get_global_value_index()];

					// copy the PHI node into a temporary
					phi_value phi = {
						.phi = user->target,
						.node = nullptr,
						.destination = get_virtual_register(user->target),
						.source = reg{}
					};

					phi_values.push_back(phi);

					const ir::data_type dt = phi.phi->get_data_type();
					const reg temp = allocate_virtual_register(nullptr, dt);
					m_context->append_instruction(m_assembler.create_move(dt, temp, phi.destination));

					// assign temporary as the PHI until the end of the BB
					value->virtual_register = temp;
				}
			}
		}

		if(index == 0) {
			// select instructions for the entry node
			select_instruction(m_context->function->get_entry(), reg{});
		}

		// walk all nodes
		const ptr<instruction> current = m_context->current_instruction;
		ptr<instruction> last = nullptr;

		for(u64 i = m_context->work.get_size(); i-- > m_context->cfg.get_size();) {
			const ptr<ir::node> node = m_context->work[i];

			if(node->get_id() == entry_id) {
				continue;
			}

			const ptr<virtual_value> value = m_context->get_virtual_value(node);
			
			if(node != block_exit && !value->virtual_register.is_valid() && detail::should_rematerialize(node)) {
				continue;
			}
			
			// attach to dummy list
			instruction dummy;
			dummy.next = nullptr;
			m_context->current_instruction = &dummy;
			 
			if(
				node->get_data_type().get_id() == static_cast<u8>(ir::data_type_id::TUPLE) || 
				node->get_data_type().get_id() == static_cast<u8>(ir::data_type_id::CONTROL) ||
				node->get_data_type().get_id() == static_cast<u8>(ir::data_type_id::MEMORY)
			) {
				select_instruction(node, value->virtual_register);
			}
			else if(value->use_count > 0 || value->virtual_register.is_valid()) {
				if(!value->virtual_register.is_valid()) {
					value->virtual_register = allocate_virtual_register(node, node->get_data_type());
				}
			
				select_instruction(node, value->virtual_register);
			}
			else {
				// dead
			}
			
			ptr<instruction> sequence_start = dummy.next;
			const ptr<instruction> sequence_end = m_context->current_instruction;
			ASSERT(sequence_end->next == nullptr, "invalid instruction detected");
			
			if(sequence_start != nullptr) {
				if(last == nullptr) {
					last = sequence_end;
					current->next = dummy.next;
				}
				else {
					const ptr<instruction> old_next = current->next;
					current->next = sequence_start;
					sequence_end->next = old_next;
				}
			}
		}

		// restore the PHI values to normal
		for(u64 i = our_phis; i < phi_values.size(); ++i) {
			const phi_value& value = phi_values[i];
			m_context->get_virtual_value(value.phi)->virtual_register = value.destination;
		}

		m_context->current_instruction = last ? last : current;

		if(!block_exit->is_control_flow_terminator()) {
			// implicit goto
			const ptr<ir::node> successor_node = detail::get_next_control(block_exit);
			m_context->append_instruction(m_assembler.create_instruction(static_cast<u16>(x64::instruction_id::TERMINATOR), ir::VOID_TYPE, 0, 0, 0));

			// write back PHIs
			for(u64 i = 0; i < our_phis; ++i) {
				const phi_value& value = phi_values[i];

				const reg source = get_virtual_register(value.node);
				const ir::data_type dt = value.phi->get_data_type();

				// hint_register(value->destination, source);
				m_context->append_instruction(m_assembler.create_move(dt, value.destination, source));
			}

			const i32 successor = static_cast<i32>(m_context->cfg.at(successor_node).id);

			// if the successor isn't our fallthrough block we have to jump to it
			if(m_context->fallthrough_label != successor) {
				m_context->append_instruction(m_assembler.create_jump(successor));
			}
		}

		// reset
		phi_values.clear();
		m_context->work.set_size(m_context->cfg.get_size());
	}

	auto x64_target::create_scheduled_node(ptr<scheduled_node> parent, ptr<ir::node> node) const -> ptr<scheduled_node> {
		constexpr ir::node_id projection_id(0, static_cast<u16>(core_node_id::PROJECTION));
		constexpr ir::node_id phi_id(0, static_cast<u16>(core_node_id::PHI));

		const auto scheduled = m_context->function->emplace<scheduled_node>();

		scheduled->parent = parent;
		scheduled->node = node;
		scheduled->index = 0;

		if(
			node->is_memory_out_operator() && 
			node->get_id() != phi_id && 
			node->get_id() != projection_id
		) {
			scheduled->antis = node->inputs[1]->users;
		}

		return scheduled;
	}

	void x64_target::fill_phi_nodes(std::vector<scheduled_phi>& phi_nodes, ptr<ir::node> successor, i32 phi_index) {
		constexpr ir::node_id phi_id(0, static_cast<u16>(core_node_id::PHI));

		for(ptr<ir::user> user = successor->users; user; user = user->next) {
			if(user->target->get_id() != phi_id) {
				continue;
			}

			phi_nodes.push_back({
				.phi = user->target,
				.node = user->target->inputs[1 + phi_index]
			});
		}
	}

	auto x64_target::get_virtual_register(ptr<ir::node> node) -> reg {
		const ptr<virtual_value> value = m_context->get_virtual_value(node);

		if(value == nullptr) {
			const reg temp = allocate_virtual_register(node, node->get_data_type());
			select_instruction(node, temp);
			return temp;
		}

		value->use_count--;

		if(value->virtual_register.is_valid()) {
			return value->virtual_register;
		}

		if(detail::should_rematerialize(node)) {
			const reg temp = allocate_virtual_register(node, node->get_data_type());
			select_instruction(node, temp);
			return temp;
		}

		const reg i = allocate_virtual_register(node, node->get_data_type());
		value->virtual_register = i;
		return i;
	}

	auto x64_target::allocate_virtual_register(ptr<ir::node> node, ir::data_type data_type) const -> reg {
		SUPPRESS_C4100(data_type);

		const u64 index = m_context->intervals.size();
		m_context->intervals.emplace_back(std::vector{ utility::range<i32>::max() }, node);

		ASSERT(index < reg::invalid_index, "invalid virtual register index");
		return { x64::GPR, static_cast<u16>(index) };
	}

	auto x64_target::is_scheduled_in_block(ptr<ir::basic_block> block, ptr<ir::node> node) const -> bool {
		const auto it = m_context->schedule.find(node);
		return it != m_context->schedule.end() && it->second == block && !m_context->work.is_visited(node);
	}
} // namespace baremetal
