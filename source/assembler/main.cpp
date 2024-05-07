#include <numeric>
#include <string>
#include <utility/segmented_array.h>
#include <vector>

#include "utility/assert.h"
#include "utility/dynamic_array.h"

using namespace utility::types;

auto compare_vector_and_segmented(const std::vector<i32>& vec, utility::segmented_array<i32>& arr) {
	// TODO: size
	u64 index = 0;

	for(const i32 a : arr) {
		if(vec[index++] != a) {
			utility::iterator_print(vec.begin(), vec.end());
			utility::iterator_print(arr.begin(), arr.end());
			return false;
		}
	}

	return true;
}

void test_insert() {
	constexpr i32 iteration_count = 10;
	constexpr u64 segment_size = 10;

	for(i32 i = 0; i < iteration_count + 1; ++i) {
		for(i32 j = 0; j < iteration_count; ++j) {
			// std baseline
			std::vector<i32> std_destination(iteration_count);
			std::vector<i32> std_source(j, 1000);

			std::iota(std_destination.begin(), std_destination.end(), 0);
			std_destination.insert(std_destination.begin() + i, std_source.begin(), std_source.end());

			// utility
			utility::segmented_array<i32> utility_destination(segment_size);
			utility::segmented_array<i32> utility_source(segment_size);

			for(i32 k = 0; k < j; ++k) {
				utility_source.push_back(1000);
			}

			for(i32 k = 0; k < iteration_count; ++k) {
				utility_destination.push_back(k);
			}

			utility_destination.insert(utility_destination.begin() + i, utility_source.begin(), utility_source.end());

			if(!compare_vector_and_segmented(std_destination, utility_destination)) {
				std::cout << '{' << i << ", " << j << "}\n";
				DEBUG_BREAK();
			}
		}
	}
}

int main() {
	test_insert();

	return 0;
}
