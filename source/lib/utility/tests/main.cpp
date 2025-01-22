#include "utility/assert.h"

using namespace utility::types;

int main() {
	constexpr utility::range range = { 1, 20 };
	std::cout << range << '\n';
	return 0;
}
