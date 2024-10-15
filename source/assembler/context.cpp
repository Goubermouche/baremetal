#include "context.h"

namespace baremetal::assembler {
	context::context() : allocator(2048), strings() {}

	void context::clear() {
		allocator.clear();
		strings.clear();
	}
} // namespace baremetal::assembler

