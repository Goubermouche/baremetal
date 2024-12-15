#pragma once
#include <utility//containers/string_interner.h>

namespace baremetal::assembler {
	struct context {
		context();

		void clear();

		utility::block_allocator allocator;
		string_interner strings;
	};
} // namespace baremetal::assembler

