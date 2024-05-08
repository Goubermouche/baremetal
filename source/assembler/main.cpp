#include <numeric>
#include <string>
#include <utility/segmented_array.h>
#include <vector>

#include "utility/assert.h"
#include "utility/dynamic_array.h"

using namespace utility::types;

auto compare_vector_and_segmented(const std::vector<i32>& vec, utility::segmented_array<i32>& arr) {
	u64 index = 0;

	if(vec.size() != arr.size()) {
		//std::cout << "#qn";

		utility::iterator_print(vec.begin(), vec.end());
		utility::iterator_print(arr.begin(), arr.end());
		return false;
	}

	for(const i32 a : arr) {
		if(vec[index++] != a) {
			//std::cout << "#qn";

			utility::iterator_print(vec.begin(), vec.end());
			utility::iterator_print(arr.begin(), arr.end());
			return false;
		}
	}

	return true;
}

void test_insert() {
	constexpr i32 iteration_count = 10;

	//i32 i = 0;
	//i32 j = 1;
	//i32 k = 1;

	i32 i = 6;
	i32 j = 7;
	i32 k = 6;

	for(i32 i = 0; i < iteration_count + 1; ++i) {
		for(i32 j = 0; j < iteration_count; ++j) {
			for(i32 k = 1; k < iteration_count; ++k) {
				// std baseline
				std::vector<i32> std_destination(iteration_count);
				std::vector<i32> std_source(j, 1000);

				std::iota(std_destination.begin(), std_destination.end(), 0);
				std_destination.insert(std_destination.begin() + i, std_source.begin(), std_source.end());

				// utility
				utility::segmented_array<i32> utility_destination(k);
				utility::segmented_array<i32> utility_source(k);

				for(i32 l = 0; l < j; ++l) {
					utility_source.push_back(1000);
				}

				for(i32 l = 0; l < iteration_count; ++l) {
					utility_destination.push_back(l);
				}

				utility_destination.insert(utility_destination.begin() + i, utility_source.begin(), utility_source.end());

				if(!compare_vector_and_segmented(std_destination, utility_destination)) {
					std::cout << '{' << i << ", " << j << ", " << k << "}\n";
					// DEBUG_BREAK();
					return;
				}
			}
		}
	}
}

int main() {
	test_insert();

	return 0;
}
