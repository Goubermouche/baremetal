#include "utility/dynamic_array.h"

using namespace utility::types;

int main() {
	utility::dynamic_array<i32> values;

	values.push_back(100);

	for(const i32 value : values) {
		std::cout << value << '\n';
	}

	return 0;
}
