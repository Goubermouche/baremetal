#include "assembler/assembler.h"

#include <utility/streams/console.h>
#include <utility/dynamic_string.h>

using namespace utility::types;

auto bytes_to_string(const utility::dynamic_array<utility::byte>& bytes) -> utility::dynamic_string {
	utility::dynamic_string result;
	result.reserve(bytes.size() * 2);

	constexpr char digits[] = "0123456789abcdef";

	for(u64 i = 0; i < bytes.size(); ++i) {
		const byte value = bytes[i];
		result.push_back(digits[(value >> 4) & 0x0F]);
		result.push_back(digits[value & 0x0F]);
	}

	return result;
}

#define TEST_INST(expected, instruction)                                                                             \
do {                                                                                                                 \
  assembler assembler;                                                                                               \
  assembler.instruction;                                                                                             \
  utility::dynamic_string result = bytes_to_string(assembler.get_bytes());                                           \
	if((expected) != result) {                                                                                         \
		utility::console::print("error: \"{}\", expected \"{}\", but got \"{}\"\n", ###instruction, (expected), result); \
	}                                                                                                                  \
} while(false)

void run_tests() {
	using namespace baremetal;

	TEST_INST("48b86400000000000000", MOVABS(rax, I64(100)));
	TEST_INST("48b96400000000000000", MOVABS(rcx, I64(100)));
	TEST_INST("48ba6400000000000000", MOVABS(rdx, I64(100)));
	TEST_INST("48bb6400000000000000", MOVABS(rbx, I64(100)));
	TEST_INST("48bc6400000000000000", MOVABS(rsp, I64(100)));
	TEST_INST("48bd6400000000000000", MOVABS(rbp, I64(100)));
	TEST_INST("48be6400000000000000", MOVABS(rsi, I64(100)));
	TEST_INST("48bf6400000000000000", MOVABS(rdi, I64(100)));
	TEST_INST("49b86400000000000000", MOVABS(r8 , I64(100)));
	TEST_INST("49b96400000000000000", MOVABS(r9 , I64(100)));
	TEST_INST("49ba6400000000000000", MOVABS(r10, I64(100)));
	TEST_INST("49bb6400000000000000", MOVABS(r11, I64(100)));
	TEST_INST("49bc6400000000000000", MOVABS(r12, I64(100)));
	TEST_INST("49bd6400000000000000", MOVABS(r13, I64(100)));
	TEST_INST("49be6400000000000000", MOVABS(r14, I64(100)));
	TEST_INST("49bf6400000000000000", MOVABS(r15, I64(100)));

	TEST_INST("0f78c8",   VMREAD(rax, rcx));
	TEST_INST("0f78c1",   VMREAD(rcx, rax));
	TEST_INST("410f78cc", VMREAD(r12, rcx));
	TEST_INST("440f78e1", VMREAD(rcx, r12));
}

int main() {
	run_tests();

	using namespace  baremetal;

	assembler assembler;
	assembler.VMREAD(rax, rcx);
	utility::console::print("{}\n", bytes_to_string(assembler.get_bytes()));

	return 0;
}
