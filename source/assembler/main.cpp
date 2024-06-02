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

	TEST_INST("80d164", ADC(cl, I8(100)));
	TEST_INST("6681d1e803", ADC(cx, I16(1000)));
	TEST_INST("81d1a0860100", ADC(ecx, I32(100000)));
	TEST_INST("4881d1a0860100", ADC(rcx, I32(100000)));
	TEST_INST("6683d164", ADC(cx, I8(100)));
	TEST_INST("83d164", ADC(ecx, I8(100)));
	TEST_INST("4883d164", ADC(rcx, I8(100)));
	TEST_INST("10c9", ADC(cl, cl));
	TEST_INST("6611c9", ADC(cx, cx));
	TEST_INST("11c9", ADC(ecx, ecx));
	TEST_INST("4811c9", ADC(rcx, rcx));
	TEST_INST("660f38f6c9", ADCX(ecx, ecx));
	TEST_INST("66480f38f6c9", ADCX(rcx, rcx));
	TEST_INST("80c164", ADD(cl, I8(100)));
	TEST_INST("6681c1e803", ADD(cx, I16(1000)));
	TEST_INST("81c1a0860100", ADD(ecx, I32(100000)));
	TEST_INST("4881c1a0860100", ADD(rcx, I32(100000)));
	TEST_INST("6683c164", ADD(cx, I8(100)));
	TEST_INST("83c164", ADD(ecx, I8(100)));
	TEST_INST("4883c164", ADD(rcx, I8(100)));
	TEST_INST("00c9", ADD(cl, cl));
	TEST_INST("6601c9", ADD(cx, cx));
	TEST_INST("01c9", ADD(ecx, ecx));
	TEST_INST("4801c9", ADD(rcx, rcx));
	TEST_INST("f30f38f6c9", ADOX(ecx, ecx));
	TEST_INST("f3480f38f6c9", ADOX(rcx, rcx));
	TEST_INST("80e164", AND(cl, I8(100)));
	TEST_INST("6681e1e803", AND(cx, I16(1000)));
	TEST_INST("81e1a0860100", AND(ecx, I32(100000)));
	TEST_INST("4881e1a0860100", AND(rcx, I32(100000)));
	TEST_INST("6683e164", AND(cx, I8(100)));
	TEST_INST("83e164", AND(ecx, I8(100)));
	TEST_INST("4883e164", AND(rcx, I8(100)));
	TEST_INST("20c9", AND(cl, cl));
	TEST_INST("6621c9", AND(cx, cx));
	TEST_INST("21c9", AND(ecx, ecx));
	TEST_INST("4821c9", AND(rcx, rcx));
	TEST_INST("660fbcc9", BSF(cx, cx));
	TEST_INST("0fbcc9", BSF(ecx, ecx));
	TEST_INST("480fbcc9", BSF(rcx, rcx));
	TEST_INST("660fbdc9", BSR(cx, cx));
	TEST_INST("0fbdc9", BSR(ecx, ecx));
	TEST_INST("480fbdc9", BSR(rcx, rcx));
	TEST_INST("660fa3c9", BT(cx, cx));
	TEST_INST("0fa3c9", BT(ecx, ecx));
	TEST_INST("480fa3c9", BT(rcx, rcx));
	TEST_INST("660fbae164", BT(cx, I8(100)));
	TEST_INST("0fbae164", BT(ecx, I8(100)));
	TEST_INST("480fbae164", BT(rcx, I8(100)));
	TEST_INST("660fbbc9", BTC(cx, cx));
	TEST_INST("0fbbc9", BTC(ecx, ecx));
	TEST_INST("480fbbc9", BTC(rcx, rcx));
	TEST_INST("660fbaf964", BTC(cx, I8(100)));
	TEST_INST("0fbaf964", BTC(ecx, I8(100)));
	TEST_INST("480fbaf964", BTC(rcx, I8(100)));
	TEST_INST("660fb3c9", BTR(cx, cx));
	TEST_INST("0fb3c9", BTR(ecx, ecx));
	TEST_INST("480fb3c9", BTR(rcx, rcx));
	TEST_INST("660fbaf164", BTR(cx, I8(100)));
	TEST_INST("0fbaf164", BTR(ecx, I8(100)));
	TEST_INST("480fbaf164", BTR(rcx, I8(100)));
	TEST_INST("660fabc9", BTS(cx, cx));
	TEST_INST("0fabc9", BTS(ecx, ecx));
	TEST_INST("480fabc9", BTS(rcx, rcx));
	TEST_INST("660fbae964", BTS(cx, I8(100)));
	TEST_INST("0fbae964", BTS(ecx, I8(100)));
	TEST_INST("480fbae964", BTS(rcx, I8(100)));
	TEST_INST("660f47c9", CMOVA(cx, cx));
	TEST_INST("0f47c9", CMOVA(ecx, ecx));
	TEST_INST("480f47c9", CMOVA(rcx, rcx));
	TEST_INST("660f43c9", CMOVAE(cx, cx));
	TEST_INST("0f43c9", CMOVAE(ecx, ecx));
	TEST_INST("480f43c9", CMOVAE(rcx, rcx));
	TEST_INST("660f42c9", CMOVB(cx, cx));
	TEST_INST("0f42c9", CMOVB(ecx, ecx));
	TEST_INST("480f42c9", CMOVB(rcx, rcx));
	TEST_INST("660f46c9", CMOVBE(cx, cx));
	TEST_INST("0f46c9", CMOVBE(ecx, ecx));
	TEST_INST("480f46c9", CMOVBE(rcx, rcx));
	TEST_INST("660f42c9", CMOVC(cx, cx));
	TEST_INST("0f42c9", CMOVC(ecx, ecx));
	TEST_INST("480f42c9", CMOVC(rcx, rcx));
	TEST_INST("660f44c9", CMOVE(cx, cx));
	TEST_INST("0f44c9", CMOVE(ecx, ecx));
	TEST_INST("480f44c9", CMOVE(rcx, rcx));
	TEST_INST("660f4fc9", CMOVG(cx, cx));
	TEST_INST("0f4fc9", CMOVG(ecx, ecx));
	TEST_INST("480f4fc9", CMOVG(rcx, rcx));
	TEST_INST("660f4dc9", CMOVGE(cx, cx));
	TEST_INST("0f4dc9", CMOVGE(ecx, ecx));
	TEST_INST("480f4dc9", CMOVGE(rcx, rcx));
	TEST_INST("660f4cc9", CMOVL(cx, cx));
	TEST_INST("0f4cc9", CMOVL(ecx, ecx));
	TEST_INST("480f4cc9", CMOVL(rcx, rcx));
	TEST_INST("660f4ec9", CMOVLE(cx, cx));
	TEST_INST("0f4ec9", CMOVLE(ecx, ecx));
	TEST_INST("480f4ec9", CMOVLE(rcx, rcx));
	TEST_INST("660f46c9", CMOVNA(cx, cx));
	TEST_INST("0f46c9", CMOVNA(ecx, ecx));
	TEST_INST("480f46c9", CMOVNA(rcx, rcx));
	TEST_INST("660f42c9", CMOVNAE(cx, cx));
	TEST_INST("0f42c9", CMOVNAE(ecx, ecx));
	TEST_INST("480f42c9", CMOVNAE(rcx, rcx));
	TEST_INST("660f43c9", CMOVNB(cx, cx));
	TEST_INST("0f43c9", CMOVNB(ecx, ecx));
	TEST_INST("480f43c9", CMOVNB(rcx, rcx));
	TEST_INST("660f47c9", CMOVNBE(cx, cx));
	TEST_INST("0f47c9", CMOVNBE(ecx, ecx));
	TEST_INST("480f47c9", CMOVNBE(rcx, rcx));
	TEST_INST("660f43c9", CMOVNC(cx, cx));
	TEST_INST("0f43c9", CMOVNC(ecx, ecx));
	TEST_INST("480f43c9", CMOVNC(rcx, rcx));
	TEST_INST("660f45c9", CMOVNE(cx, cx));
	TEST_INST("0f45c9", CMOVNE(ecx, ecx));
	TEST_INST("480f45c9", CMOVNE(rcx, rcx));
	TEST_INST("660f4ec9", CMOVNG(cx, cx));
	TEST_INST("0f4ec9", CMOVNG(ecx, ecx));
	TEST_INST("480f4ec9", CMOVNG(rcx, rcx));
	TEST_INST("660f4cc9", CMOVNGE(cx, cx));
	TEST_INST("0f4cc9", CMOVNGE(ecx, ecx));
	TEST_INST("480f4cc9", CMOVNGE(rcx, rcx));
	TEST_INST("660f4dc9", CMOVNL(cx, cx));
	TEST_INST("0f4dc9", CMOVNL(ecx, ecx));
	TEST_INST("480f4dc9", CMOVNL(rcx, rcx));
	TEST_INST("660f4fc9", CMOVNLE(cx, cx));
	TEST_INST("0f4fc9", CMOVNLE(ecx, ecx));
	TEST_INST("480f4fc9", CMOVNLE(rcx, rcx));
	TEST_INST("660f41c9", CMOVNO(cx, cx));
	TEST_INST("0f41c9", CMOVNO(ecx, ecx));
	TEST_INST("480f41c9", CMOVNO(rcx, rcx));
	TEST_INST("660f4bc9", CMOVNP(cx, cx));
	TEST_INST("0f4bc9", CMOVNP(ecx, ecx));
	TEST_INST("480f4bc9", CMOVNP(rcx, rcx));
	TEST_INST("660f49c9", CMOVNS(cx, cx));
	TEST_INST("0f49c9", CMOVNS(ecx, ecx));
	TEST_INST("480f49c9", CMOVNS(rcx, rcx));
	TEST_INST("660f45c9", CMOVNZ(cx, cx));
	TEST_INST("0f45c9", CMOVNZ(ecx, ecx));
	TEST_INST("480f45c9", CMOVNZ(rcx, rcx));
	TEST_INST("660f40c9", CMOVO(cx, cx));
	TEST_INST("0f40c9", CMOVO(ecx, ecx));
	TEST_INST("480f40c9", CMOVO(rcx, rcx));
	TEST_INST("660f4ac9", CMOVP(cx, cx));
	TEST_INST("0f4ac9", CMOVP(ecx, ecx));
	TEST_INST("480f4ac9", CMOVP(rcx, rcx));
	TEST_INST("660f4ac9", CMOVPE(cx, cx));
	TEST_INST("0f4ac9", CMOVPE(ecx, ecx));
	TEST_INST("480f4ac9", CMOVPE(rcx, rcx));
	TEST_INST("660f4bc9", CMOVPO(cx, cx));
	TEST_INST("0f4bc9", CMOVPO(ecx, ecx));
	TEST_INST("480f4bc9", CMOVPO(rcx, rcx));
	TEST_INST("660f48c9", CMOVS(cx, cx));
	TEST_INST("0f48c9", CMOVS(ecx, ecx));
	TEST_INST("480f48c9", CMOVS(rcx, rcx));
	TEST_INST("660f44c9", CMOVZ(cx, cx));
	TEST_INST("0f44c9", CMOVZ(ecx, ecx));
	TEST_INST("480f44c9", CMOVZ(rcx, rcx));
	TEST_INST("80f964", CMP(cl, I8(100)));
	TEST_INST("6681f9e803", CMP(cx, I16(1000)));
	TEST_INST("81f9a0860100", CMP(ecx, I32(100000)));
	TEST_INST("4881f9a0860100", CMP(rcx, I32(100000)));
	TEST_INST("6683f964", CMP(cx, I8(100)));
	TEST_INST("83f964", CMP(ecx, I8(100)));
	TEST_INST("4883f964", CMP(rcx, I8(100)));
	TEST_INST("38c9", CMP(cl, cl));
	TEST_INST("6639c9", CMP(cx, cx));
	TEST_INST("39c9", CMP(ecx, ecx));
	TEST_INST("4839c9", CMP(rcx, rcx));
	TEST_INST("f20f38f0c9", CRC32(ecx, cl));
	TEST_INST("66f20f38f1c9", CRC32(ecx, cx));
	TEST_INST("f20f38f1c9", CRC32(ecx, ecx));
	TEST_INST("f2480f38f0c9", CRC32(rcx, cl));
	TEST_INST("f2480f38f1c9", CRC32(rcx, rcx));
	TEST_INST("c8e80364", ENTER(I16(1000), I8(100)));
	TEST_INST("660fafc9", IMUL(cx, cx));
	TEST_INST("0fafc9", IMUL(ecx, ecx));
	TEST_INST("480fafc9", IMUL(rcx, rcx));
	TEST_INST("66f30fbdc9", LZCNT(cx, cx));
	TEST_INST("f30fbdc9", LZCNT(ecx, ecx));
	TEST_INST("f3480fbdc9", LZCNT(rcx, rcx));
	TEST_INST("88c9", MOV(cl, cl));
	TEST_INST("6689c9", MOV(cx, cx));
	TEST_INST("89c9", MOV(ecx, ecx));
	TEST_INST("4889c9", MOV(rcx, rcx));
	TEST_INST("b164", MOV(cl, I8(100)));
	TEST_INST("66b9e803", MOV(cx, I16(1000)));
	TEST_INST("b9a0860100", MOV(ecx, I32(100000)));
	TEST_INST("48b900e40b5402000000", MOV(rcx, I64(10000000000)));
	TEST_INST("b9a0860100", MOV(rcx, I32(100000)));
	TEST_INST("660fbec9", MOVSX(cx, cl));
	TEST_INST("0fbec9", MOVSX(ecx, cl));
	TEST_INST("480fbec9", MOVSX(rcx, cl));
	TEST_INST("0fbfc9", MOVSX(ecx, cx));
	TEST_INST("480fbfc9", MOVSX(rcx, cx));
	TEST_INST("4863c9", MOVSXD(rcx, ecx));
	TEST_INST("660fb6c9", MOVZX(cx, cl));
	TEST_INST("0fb6c9", MOVZX(ecx, cl));
	TEST_INST("480fb6c9", MOVZX(rcx, cl));
	TEST_INST("0fb7c9", MOVZX(ecx, cx));
	TEST_INST("480fb7c9", MOVZX(rcx, cx));
	TEST_INST("80c964", OR(cl, I8(100)));
	TEST_INST("6681c9e803", OR(cx, I16(1000)));
	TEST_INST("81c9a0860100", OR(ecx, I32(100000)));
	TEST_INST("4881c9a0860100", OR(rcx, I32(100000)));
	TEST_INST("6683c964", OR(cx, I8(100)));
	TEST_INST("83c964", OR(ecx, I8(100)));
	TEST_INST("4883c964", OR(rcx, I8(100)));
	TEST_INST("08c9", OR(cl, cl));
	TEST_INST("6609c9", OR(cx, cx));
	TEST_INST("09c9", OR(ecx, ecx));
	TEST_INST("4809c9", OR(rcx, rcx));
	TEST_INST("66f30fb8c9", POPCNT(cx, cx));
	TEST_INST("f30fb8c9", POPCNT(ecx, ecx));
	TEST_INST("f3480fb8c9", POPCNT(rcx, rcx));
	TEST_INST("c0d164", RCL(cl, I8(100)));
	TEST_INST("66c1d164", RCL(cx, I8(100)));
	TEST_INST("c1d164", RCL(ecx, I8(100)));
	TEST_INST("48c1d164", RCL(rcx, I8(100)));
	TEST_INST("c0d964", RCR(cl, I8(100)));
	TEST_INST("66c1d964", RCR(cx, I8(100)));
	TEST_INST("c1d964", RCR(ecx, I8(100)));
	TEST_INST("48c1d964", RCR(rcx, I8(100)));
	TEST_INST("c0c164", ROL(cl, I8(100)));
	TEST_INST("66c1c164", ROL(cx, I8(100)));
	TEST_INST("c1c164", ROL(ecx, I8(100)));
	TEST_INST("48c1c164", ROL(rcx, I8(100)));
	TEST_INST("c0c964", ROR(cl, I8(100)));
	TEST_INST("66c1c964", ROR(cx, I8(100)));
	TEST_INST("c1c964", ROR(ecx, I8(100)));
	TEST_INST("48c1c964", ROR(rcx, I8(100)));
	TEST_INST("c0e164", SAL(cl, I8(100)));
	TEST_INST("66c1e164", SAL(cx, I8(100)));
	TEST_INST("c1e164", SAL(ecx, I8(100)));
	TEST_INST("48c1e164", SAL(rcx, I8(100)));
	TEST_INST("c0f964", SAR(cl, I8(100)));
	TEST_INST("66c1f964", SAR(cx, I8(100)));
	TEST_INST("c1f964", SAR(ecx, I8(100)));
	TEST_INST("48c1f964", SAR(rcx, I8(100)));
	TEST_INST("80d964", SBB(cl, I8(100)));
	TEST_INST("6681d9e803", SBB(cx, I16(1000)));
	TEST_INST("81d9a0860100", SBB(ecx, I32(100000)));
	TEST_INST("4881d9a0860100", SBB(rcx, I32(100000)));
	TEST_INST("6683d964", SBB(cx, I8(100)));
	TEST_INST("83d964", SBB(ecx, I8(100)));
	TEST_INST("4883d964", SBB(rcx, I8(100)));
	TEST_INST("18c9", SBB(cl, cl));
	TEST_INST("6619c9", SBB(cx, cx));
	TEST_INST("19c9", SBB(ecx, ecx));
	TEST_INST("4819c9", SBB(rcx, rcx));
	TEST_INST("c0e164", SHL(cl, I8(100)));
	TEST_INST("66c1e164", SHL(cx, I8(100)));
	TEST_INST("c1e164", SHL(ecx, I8(100)));
	TEST_INST("48c1e164", SHL(rcx, I8(100)));
	TEST_INST("c0e964", SHR(cl, I8(100)));
	TEST_INST("66c1e964", SHR(cx, I8(100)));
	TEST_INST("c1e964", SHR(ecx, I8(100)));
	TEST_INST("48c1e964", SHR(rcx, I8(100)));
	TEST_INST("80e964", SUB(cl, I8(100)));
	TEST_INST("6681e9e803", SUB(cx, I16(1000)));
	TEST_INST("81e9a0860100", SUB(ecx, I32(100000)));
	TEST_INST("4881e9a0860100", SUB(rcx, I32(100000)));
	TEST_INST("6683e964", SUB(cx, I8(100)));
	TEST_INST("83e964", SUB(ecx, I8(100)));
	TEST_INST("4883e964", SUB(rcx, I8(100)));
	TEST_INST("28c9", SUB(cl, cl));
	TEST_INST("6629c9", SUB(cx, cx));
	TEST_INST("29c9", SUB(ecx, ecx));
	TEST_INST("4829c9", SUB(rcx, rcx));
	TEST_INST("f6c164", TEST(cl, I8(100)));
	TEST_INST("66f7c1e803", TEST(cx, I16(1000)));
	TEST_INST("f7c1a0860100", TEST(ecx, I32(100000)));
	TEST_INST("48f7c1a0860100", TEST(rcx, I32(100000)));
	TEST_INST("84c9", TEST(cl, cl));
	TEST_INST("6685c9", TEST(cx, cx));
	TEST_INST("85c9", TEST(ecx, ecx));
	TEST_INST("4885c9", TEST(rcx, rcx));
	TEST_INST("66f30fbcc9", TZCNT(cx, cx));
	TEST_INST("f30fbcc9", TZCNT(ecx, ecx));
	TEST_INST("f3480fbcc9", TZCNT(rcx, rcx));
	TEST_INST("0fc0c9", XADD(cl, cl));
	TEST_INST("660fc1c9", XADD(cx, cx));
	TEST_INST("0fc1c9", XADD(ecx, ecx));
	TEST_INST("480fc1c9", XADD(rcx, rcx));
	TEST_INST("86c9", XCHG(cl, cl));
	TEST_INST("6687c9", XCHG(cx, cx));
	TEST_INST("87c9", XCHG(ecx, ecx));
	TEST_INST("4887c9", XCHG(rcx, rcx));
	TEST_INST("80f164", XOR(cl, I8(100)));
	TEST_INST("6681f1e803", XOR(cx, I16(1000)));
	TEST_INST("81f1a0860100", XOR(ecx, I32(100000)));
	TEST_INST("4881f1a0860100", XOR(rcx, I32(100000)));
	TEST_INST("6683f164", XOR(cx, I8(100)));
	TEST_INST("83f164", XOR(ecx, I8(100)));
	TEST_INST("4883f164", XOR(rcx, I8(100)));
	TEST_INST("30c9", XOR(cl, cl));
	TEST_INST("6631c9", XOR(cx, cx));
	TEST_INST("31c9", XOR(ecx, ecx));
	TEST_INST("4831c9", XOR(rcx, rcx));

	utility::console::print(
		"{}/{} tests passed\n",
		g_success_counter,
		g_success_counter + g_fail_counter
	);
}

int main() {
	run_tests();

	using namespace  baremetal;

	return 0;
}
