#include "context.h"

namespace baremetal {
	assembler_context::assembler_context() : allocator(1024), strings() {}

	void assembler_context::clear() {
		allocator.clear();
		strings.clear();
	}
}
