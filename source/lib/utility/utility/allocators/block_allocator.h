#pragma once
#include "utility/allocators/allocator_base.h"

namespace utility {
	// TODO: aligned allocations
	class block_allocator : public allocator_base {
	protected:
		struct block {
			block(u8* memory) : memory(memory), position(0) {}
			~block() {
				utility::free(memory);
			}

			u8* memory;
			u64 position;
			block* next = nullptr;
		};
	public:
		class safepoint {
		public:
			safepoint() : m_block(nullptr), m_position(0) {}
			safepoint(block* block, u64 position) : m_block(block), m_position(position) {}

			[[nodiscard]] auto get_block() const -> block* {
				return m_block;
			}

			[[nodiscard]] auto get_position() const -> u64 {
				return m_position;
			}
		protected:
			block* m_block;
			u64 m_position;
		};

		block_allocator(u64 block_size) : m_block_size(block_size) {
			clear();
		}

		block_allocator(const block_allocator& other) = delete;
		block_allocator(block_allocator&& other) noexcept {
			*this = move(other);
		}

		block_allocator& operator=(const block_allocator& other) = delete;
		block_allocator& operator=(block_allocator&& other) {
			if(&other != this) {
				m_first_block = exchange(other.m_first_block, nullptr);
				m_current_block = exchange(other.m_first_block, nullptr);
				m_block_size = exchange(other.m_block_size, 0);
			}

			return *this;
		}

		~block_allocator() {
			while(m_first_block) {
				block* temp = m_first_block;
				m_first_block = m_first_block->next;
				delete temp;
			}
		}

		void clear() {
			while(m_first_block) {
				block* temp = m_first_block;
				m_first_block = m_first_block->next;
				delete temp;
			}

			m_first_block = nullptr;
			m_current_block = nullptr;

			allocate_block(m_block_size); // allocate the first block
			m_first_block = m_current_block;
		}

		[[nodiscard]] auto allocate(u64 size) -> void* {
			// ASSERT(size <= m_block_size, "insufficient block size for allocation of {}B\n", size);

			if(size == 0) {
				return nullptr;
			}

			// if this allocation incurs a buffer overflow allocate a new block
			if(m_current_block->position + size >= m_block_size) {
				allocate_block(max(m_block_size, size));
			}

			void* memory = m_current_block->memory + m_current_block->position;
			m_current_block->position += size;

			return memory;
		}

		template<typename type, typename... value_types>
		[[nodiscard]] auto emplace(value_types&&... values) -> type* {
			return new (allocate(sizeof(type))) type(forward<value_types>(values)...);
		}

		auto create_safepoint() const -> safepoint {
			return { m_current_block, m_current_block->position };
		}

		void restore_safepoint(const safepoint& safepoint) {
			// restore the first block
			m_current_block = safepoint.get_block();
			m_current_block->position = safepoint.get_position();

			block* current = m_current_block->next;

			// go through all subsequent blocks and reset them
			while(current) {
				current->position = 0;
				current = current->next;
			}
		}
	protected:
		void allocate_block(u64 size) {
			// the current block already has a valid block after it, use that, this is a
			// byproduct of safepoints
			if(m_current_block && m_current_block->next) {
				m_current_block = m_current_block->next;
				return;
			}

			const auto memory = static_cast<u8*>(utility::malloc(size));
			ASSERT(memory, "allocation failure\n");

			const auto new_block = new block(memory);

			if(m_current_block) {
				m_current_block->next = new_block;
			}

			m_current_block = new_block;
		}
	protected:
		block* m_first_block = nullptr;
		block* m_current_block = nullptr;

		u64 m_block_size;
	};
} // namespace utility
