#pragma once
#include "utility/containers/dynamic_array.h"
#include "utility/type_traits.h"

namespace utility {
	template<typename iterator, typename compare>
	void merge(iterator first, iterator middle, iterator last, compare comp) {
		dynamic_array<typename iterator_traits<iterator>::element_type> buffer;

		buffer.reserve(utility::distance(first, last));

		iterator left = first;
		iterator right = middle;

		while(left != middle && right != last) {
			if(comp(*right, *left)) {
				buffer.push_back(move(*right++));
			}
			else {
				buffer.push_back(move(*left++));
			}
		}

		buffer.insert(buffer.end(), left, middle);
		buffer.insert(buffer.end(), right, last);

		move(buffer.begin(), buffer.end(), first);
	}

	template<typename iterator, typename compare>
	void merge_sort(iterator first, iterator last, compare comp) {
		auto size = distance(first, last);

		if(size < 2) {
			return;
		}

		iterator middle = first + size / 2;

		merge_sort(first, middle, comp);
		merge_sort(middle, last, comp);

		merge(first, middle, last, comp);
	}

	template<typename iterator, typename compare>
	void stable_sort(iterator begin, iterator end, const compare& comp) {
		merge_sort(begin, end, comp);
	}
} // namespace utility
