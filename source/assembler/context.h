#pragma once
#include "assembler/string_interner.h"

namespace baremetal {
	struct assembler_context {
		assembler_context();

		void clear();

		utility::block_allocator allocator;
		string_interner strings;
	};
} // namespace baremetal

