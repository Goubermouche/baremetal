// implementation lifted from: https://github.com/martinus/unordered_dense (MIT license)

#pragma once
#include "utility/containers/map.h"

namespace utility {
	template<typename key, typename hash = hash<key>, typename key_equal = std::equal_to<key>>
	using set = map<key, void, hash, key_equal>;
} // namespace utility

