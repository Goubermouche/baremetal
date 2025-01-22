#pragma once
#include "utility/types.h"

namespace utility {
	template <typename destination_it_type, typename source_it_type>
	void construct_range(destination_it_type destination, source_it_type begin, source_it_type end) {
		while(begin != end) {
			utility::construct_at(destination, *begin);
			++destination;
			++begin;
		}
	}

	template <typename iterator_type>
	void destruct_range(iterator_type begin, iterator_type end) {
		while(begin != end) {
			utility::destroy_at(begin);
			++begin;
		}
	}

	template<typename iterator_type>
	auto distance(iterator_type begin, iterator_type end) -> u64 {
		u64 diff = 0;

		while(begin != end) {
			++begin;
			diff++;
		}

		return diff;
	}
} // namespace utility
