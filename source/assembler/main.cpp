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

u64 g_fail_counter = 0;
u64 g_success_counter = 0;
#define TEST_INST(expected, instruction)                                                                             \
do {                                                                                                                 \
  assembler assembler;                                                                                               \
  assembler.instruction;                                                                                             \
  utility::dynamic_string result = bytes_to_string(assembler.get_bytes());                                           \
	if((expected) != result) {                                                                                         \
		utility::console::print("error: \"{}\", expected \"{}\", but got \"{}\"\n", ###instruction, (expected), result); \
    g_fail_counter++;                                                                                                \
	}                                                                                                                  \
	else {                                                                                                             \
    g_success_counter++;                                                                                             \
	}                                                                                                                  \
} while(false)

void run_tests() {
	using namespace baremetal;

	TEST_INST("88c9", mov(cl, cl));
	TEST_INST("88d1", mov(cl, dl));
	TEST_INST("88d9", mov(cl, bl));
	TEST_INST("88ca", mov(dl, cl));
	TEST_INST("88d2", mov(dl, dl));
	TEST_INST("88da", mov(dl, bl));
	TEST_INST("88cb", mov(bl, cl));
	TEST_INST("88d3", mov(bl, dl));
	TEST_INST("88db", mov(bl, bl));
	TEST_INST("6689c9", mov(cx, cx));
	TEST_INST("6689d1", mov(cx, dx));
	TEST_INST("6689d9", mov(cx, bx));
	TEST_INST("6689ca", mov(dx, cx));
	TEST_INST("6689d2", mov(dx, dx));
	TEST_INST("6689da", mov(dx, bx));
	TEST_INST("6689cb", mov(bx, cx));
	TEST_INST("6689d3", mov(bx, dx));
	TEST_INST("6689db", mov(bx, bx));
	TEST_INST("89c9", mov(ecx, ecx));
	TEST_INST("89d1", mov(ecx, edx));
	TEST_INST("89d9", mov(ecx, ebx));
	TEST_INST("89ca", mov(edx, ecx));
	TEST_INST("89d2", mov(edx, edx));
	TEST_INST("89da", mov(edx, ebx));
	TEST_INST("89cb", mov(ebx, ecx));
	TEST_INST("89d3", mov(ebx, edx));
	TEST_INST("89db", mov(ebx, ebx));
	TEST_INST("4889c9", mov(rcx, rcx));
	TEST_INST("4889d1", mov(rcx, rdx));
	TEST_INST("4889d9", mov(rcx, rbx));
	TEST_INST("4889ca", mov(rdx, rcx));
	TEST_INST("4889d2", mov(rdx, rdx));
	TEST_INST("4889da", mov(rdx, rbx));
	TEST_INST("4889cb", mov(rbx, rcx));
	TEST_INST("4889d3", mov(rbx, rdx));
	TEST_INST("4889db", mov(rbx, rbx));
	TEST_INST("b100", mov(cl, 0));
	TEST_INST("b17f", mov(cl, 127));
	TEST_INST("b1ff", mov(cl, 255));
	TEST_INST("b180", mov(cl, -128));
	TEST_INST("b200", mov(dl, 0));
	TEST_INST("b27f", mov(dl, 127));
	TEST_INST("b2ff", mov(dl, 255));
	TEST_INST("b280", mov(dl, -128));
	TEST_INST("b300", mov(bl, 0));
	TEST_INST("b37f", mov(bl, 127));
	TEST_INST("b3ff", mov(bl, 255));
	TEST_INST("b380", mov(bl, -128));
	TEST_INST("66b90000", mov(cx, 0));
	TEST_INST("66b9ff7f", mov(cx, 32767));
	TEST_INST("66b9ffff", mov(cx, 65535));
	TEST_INST("66b90080", mov(cx, -32768));
	TEST_INST("66ba0000", mov(dx, 0));
	TEST_INST("66baff7f", mov(dx, 32767));
	TEST_INST("66baffff", mov(dx, 65535));
	TEST_INST("66ba0080", mov(dx, -32768));
	TEST_INST("66bb0000", mov(bx, 0));
	TEST_INST("66bbff7f", mov(bx, 32767));
	TEST_INST("66bbffff", mov(bx, 65535));
	TEST_INST("66bb0080", mov(bx, -32768));
	TEST_INST("b900000000", mov(ecx, 0));
	TEST_INST("b9ffffff7f", mov(ecx, 2147483647));
	TEST_INST("b9ffffffff", mov(ecx, 4294967295));
	TEST_INST("b900000080", mov(ecx, -2147483648));
	TEST_INST("ba00000000", mov(edx, 0));
	TEST_INST("baffffff7f", mov(edx, 2147483647));
	TEST_INST("baffffffff", mov(edx, 4294967295));
	TEST_INST("ba00000080", mov(edx, -2147483648));
	TEST_INST("bb00000000", mov(ebx, 0));
	TEST_INST("bbffffff7f", mov(ebx, 2147483647));
	TEST_INST("bbffffffff", mov(ebx, 4294967295));
	TEST_INST("bb00000080", mov(ebx, -2147483648));
	TEST_INST("b900000000", mov(rcx, 0));
	TEST_INST("48b9ffffffffffffff7f", mov(rcx, 9223372036854775807));
	TEST_INST("48c7c1ffffffff", mov(rcx, 18446744073709551615));
	TEST_INST("48b90000000000000080", mov(rcx, -9223372036854775808));
	TEST_INST("ba00000000", mov(rdx, 0));
	TEST_INST("48baffffffffffffff7f", mov(rdx, 9223372036854775807));
	TEST_INST("48c7c2ffffffff", mov(rdx, 18446744073709551615));
	TEST_INST("48ba0000000000000080", mov(rdx, -9223372036854775808));
	TEST_INST("bb00000000", mov(rbx, 0));
	TEST_INST("48bbffffffffffffff7f", mov(rbx, 9223372036854775807));
	TEST_INST("48c7c3ffffffff", mov(rbx, 18446744073709551615));
	TEST_INST("48bb0000000000000080", mov(rbx, -9223372036854775808));
	TEST_INST("b900000000", mov(rcx, 0));
	TEST_INST("b9ffffff7f", mov(rcx, 2147483647));
	TEST_INST("b9ffffffff", mov(rcx, 4294967295));
	TEST_INST("48c7c100000080", mov(rcx, -2147483648));
	TEST_INST("ba00000000", mov(rdx, 0));
	TEST_INST("baffffff7f", mov(rdx, 2147483647));
	TEST_INST("baffffffff", mov(rdx, 4294967295));
	TEST_INST("48c7c200000080", mov(rdx, -2147483648));
	TEST_INST("bb00000000", mov(rbx, 0));
	TEST_INST("bbffffff7f", mov(rbx, 2147483647));
	TEST_INST("bbffffffff", mov(rbx, 4294967295));
	TEST_INST("48c7c300000080", mov(rbx, -2147483648));

	utility::console::print(
		"{}/{} tests passed\n",
		g_success_counter,
		g_success_counter + g_fail_counter
	);
}


int main() {
	run_tests();
	using namespace baremetal;

	// TODO: test all previous immediates as well

	return 0;
}
