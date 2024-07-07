#pragma once
#include <utility/system/console.h>
#include <utility/containers/dynamic_string.h>
#include <assembler.h>

using namespace utility::types;

#define TEST(name)                           \
  do {                                       \
    const auto result = run_test_ ## name(); \
    total_success += result.success_count;   \
    total_fail    += result.fail_count;      \
  } while(false)

#define TEST_INST(expected, instruction)                                                                           \
do {                                                                                                               \
  assembler.instruction;                                                                                           \
  string = bytes_to_string(assembler.get_bytes());                                                                 \
  if((expected) != string) {                                                                                       \
    utility::console::print("error: \"{}\", expected \"{}\", but got \"{}\"\n", #instruction, (expected), string); \
    result.fail_count++;                                                                                           \
  }                                                                                                                \
  else {                                                                                                           \
    result.success_count++;                                                                                        \
  }                                                                                                                \
  assembler.clear();                                                                                               \
} while(false)

namespace baremetal::tests {
	struct test_result {
		u64 fail_count = 0;
		u64 success_count = 0;
	};

	inline auto bytes_to_string(const utility::dynamic_array<u8>& bytes) -> utility::dynamic_string {
		utility::dynamic_string result;
		result.reserve(bytes.get_size() * 2);

		constexpr char digits[] = "0123456789abcdef";

		for(u64 i = 0; i < bytes.get_size(); ++i) {
			const u8 value = bytes[i];
			result += (digits[(value >> 4) & 0x0F]);
			result += (digits[value & 0x0F]);
		}

		return result;
	}
} // namespace baremetal::tests
