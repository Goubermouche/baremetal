#include "context.h"

namespace baremetal::assembler {
	context::context() : allocator(1024), strings() {}

	void context::clear() {
		allocator.clear();
		strings.clear();
	}
} // namespace baremetal::assembler

