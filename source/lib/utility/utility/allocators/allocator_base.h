#pragma once
#include "utility/assert.h"

namespace utility {
	class allocator_base {};

	template<typename type>
	concept allocator = std::derived_from<type, allocator_base>;
} // namespace utility
