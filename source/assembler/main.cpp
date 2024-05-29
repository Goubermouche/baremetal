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

	TEST_INST("1464", ADC(al, I8(100)));
	TEST_INST("6683d064", ADC(ax, I16(100)));
	TEST_INST("83d064", ADC(eax, I32(100)));
	TEST_INST("4883d064", ADC(rax, I32(100)));
	TEST_INST("6683d064", ADC(ax, I8(100)));
	TEST_INST("83d064", ADC(eax, I8(100)));
	TEST_INST("4883d064", ADC(rax, I8(100)));
	TEST_INST("10c0", ADC(al, al));
	TEST_INST("6611c0", ADC(ax, ax));
	TEST_INST("11c0", ADC(eax, eax));
	TEST_INST("4811c0", ADC(rax, rax));
	TEST_INST("660f38f6c0", ADCX(eax, eax));
	TEST_INST("66480f38f6c0", ADCX(rax, rax));
	TEST_INST("0464", ADD(al, I8(100)));
	TEST_INST("6683c064", ADD(ax, I16(100)));
	TEST_INST("83c064", ADD(eax, I32(100)));
	TEST_INST("4883c064", ADD(rax, I32(100)));
	TEST_INST("6683c064", ADD(ax, I8(100)));
	TEST_INST("83c064", ADD(eax, I8(100)));
	TEST_INST("4883c064", ADD(rax, I8(100)));
	TEST_INST("00c0", ADD(al, al));
	TEST_INST("6601c0", ADD(ax, ax));
	TEST_INST("01c0", ADD(eax, eax));
	TEST_INST("4801c0", ADD(rax, rax));
	TEST_INST("f30f38f6c0", ADOX(eax, eax));
	TEST_INST("f3480f38f6c0", ADOX(rax, rax));
	TEST_INST("2464", AND(al, I8(100)));
	TEST_INST("6683e064", AND(ax, I16(100)));
	TEST_INST("83e064", AND(eax, I32(100)));
	TEST_INST("4883e064", AND(rax, I32(100)));
	TEST_INST("6683e064", AND(ax, I8(100)));
	TEST_INST("83e064", AND(eax, I8(100)));
	TEST_INST("4883e064", AND(rax, I8(100)));
	TEST_INST("20c0", AND(al, al));
	TEST_INST("6621c0", AND(ax, ax));
	TEST_INST("21c0", AND(eax, eax));
	TEST_INST("4821c0", AND(rax, rax));
	TEST_INST("660fbcc0", BSF(ax, ax));
	TEST_INST("0fbcc0", BSF(eax, eax));
	TEST_INST("480fbcc0", BSF(rax, rax));
	TEST_INST("660fbdc0", BSR(ax, ax));
	TEST_INST("0fbdc0", BSR(eax, eax));
	TEST_INST("480fbdc0", BSR(rax, rax));
	TEST_INST("660fa3c0", BT(ax, ax));
	TEST_INST("0fa3c0", BT(eax, eax));
	TEST_INST("480fa3c0", BT(rax, rax));
	TEST_INST("660fbae064", BT(ax, I8(100)));
	TEST_INST("0fbae064", BT(eax, I8(100)));
	TEST_INST("480fbae064", BT(rax, I8(100)));
	TEST_INST("660fbbc0", BTC(ax, ax));
	TEST_INST("0fbbc0", BTC(eax, eax));
	TEST_INST("480fbbc0", BTC(rax, rax));
	TEST_INST("660fbaf864", BTC(ax, I8(100)));
	TEST_INST("0fbaf864", BTC(eax, I8(100)));
	TEST_INST("480fbaf864", BTC(rax, I8(100)));
	TEST_INST("660fb3c0", BTR(ax, ax));
	TEST_INST("0fb3c0", BTR(eax, eax));
	TEST_INST("480fb3c0", BTR(rax, rax));
	TEST_INST("660fbaf064", BTR(ax, I8(100)));
	TEST_INST("0fbaf064", BTR(eax, I8(100)));
	TEST_INST("480fbaf064", BTR(rax, I8(100)));
	TEST_INST("660fabc0", BTS(ax, ax));
	TEST_INST("0fabc0", BTS(eax, eax));
	TEST_INST("480fabc0", BTS(rax, rax));
	TEST_INST("660fbae864", BTS(ax, I8(100)));
	TEST_INST("0fbae864", BTS(eax, I8(100)));
	TEST_INST("480fbae864", BTS(rax, I8(100)));
	TEST_INST("660f47c0", CMOVA(ax, ax));
	TEST_INST("0f47c0", CMOVA(eax, eax));
	TEST_INST("480f47c0", CMOVA(rax, rax));
	TEST_INST("660f43c0", CMOVAE(ax, ax));
	TEST_INST("0f43c0", CMOVAE(eax, eax));
	TEST_INST("480f43c0", CMOVAE(rax, rax));
	TEST_INST("660f42c0", CMOVB(ax, ax));
	TEST_INST("0f42c0", CMOVB(eax, eax));
	TEST_INST("480f42c0", CMOVB(rax, rax));
	TEST_INST("660f46c0", CMOVBE(ax, ax));
	TEST_INST("0f46c0", CMOVBE(eax, eax));
	TEST_INST("480f46c0", CMOVBE(rax, rax));
	TEST_INST("660f42c0", CMOVC(ax, ax));
	TEST_INST("0f42c0", CMOVC(eax, eax));
	TEST_INST("480f42c0", CMOVC(rax, rax));
	TEST_INST("660f44c0", CMOVE(ax, ax));
	TEST_INST("0f44c0", CMOVE(eax, eax));
	TEST_INST("480f44c0", CMOVE(rax, rax));
	TEST_INST("660f4fc0", CMOVG(ax, ax));
	TEST_INST("0f4fc0", CMOVG(eax, eax));
	TEST_INST("480f4fc0", CMOVG(rax, rax));
	TEST_INST("660f4dc0", CMOVGE(ax, ax));
	TEST_INST("0f4dc0", CMOVGE(eax, eax));
	TEST_INST("480f4dc0", CMOVGE(rax, rax));
	TEST_INST("660f4cc0", CMOVL(ax, ax));
	TEST_INST("0f4cc0", CMOVL(eax, eax));
	TEST_INST("480f4cc0", CMOVL(rax, rax));
	TEST_INST("660f4ec0", CMOVLE(ax, ax));
	TEST_INST("0f4ec0", CMOVLE(eax, eax));
	TEST_INST("480f4ec0", CMOVLE(rax, rax));
	TEST_INST("660f46c0", CMOVNA(ax, ax));
	TEST_INST("0f46c0", CMOVNA(eax, eax));
	TEST_INST("480f46c0", CMOVNA(rax, rax));
	TEST_INST("660f42c0", CMOVNAE(ax, ax));
	TEST_INST("0f42c0", CMOVNAE(eax, eax));
	TEST_INST("480f42c0", CMOVNAE(rax, rax));
	TEST_INST("660f43c0", CMOVNB(ax, ax));
	TEST_INST("0f43c0", CMOVNB(eax, eax));
	TEST_INST("480f43c0", CMOVNB(rax, rax));
	TEST_INST("660f47c0", CMOVNBE(ax, ax));
	TEST_INST("0f47c0", CMOVNBE(eax, eax));
	TEST_INST("480f47c0", CMOVNBE(rax, rax));
	TEST_INST("660f43c0", CMOVNC(ax, ax));
	TEST_INST("0f43c0", CMOVNC(eax, eax));
	TEST_INST("480f43c0", CMOVNC(rax, rax));
	TEST_INST("660f45c0", CMOVNE(ax, ax));
	TEST_INST("0f45c0", CMOVNE(eax, eax));
	TEST_INST("480f45c0", CMOVNE(rax, rax));
	TEST_INST("660f4ec0", CMOVNG(ax, ax));
	TEST_INST("0f4ec0", CMOVNG(eax, eax));
	TEST_INST("480f4ec0", CMOVNG(rax, rax));
	TEST_INST("660f4cc0", CMOVNGE(ax, ax));
	TEST_INST("0f4cc0", CMOVNGE(eax, eax));
	TEST_INST("480f4cc0", CMOVNGE(rax, rax));
	TEST_INST("660f4dc0", CMOVNL(ax, ax));
	TEST_INST("0f4dc0", CMOVNL(eax, eax));
	TEST_INST("480f4dc0", CMOVNL(rax, rax));
	TEST_INST("660f4fc0", CMOVNLE(ax, ax));
	TEST_INST("0f4fc0", CMOVNLE(eax, eax));
	TEST_INST("480f4fc0", CMOVNLE(rax, rax));
	TEST_INST("660f41c0", CMOVNO(ax, ax));
	TEST_INST("0f41c0", CMOVNO(eax, eax));
	TEST_INST("480f41c0", CMOVNO(rax, rax));
	TEST_INST("660f4bc0", CMOVNP(ax, ax));
	TEST_INST("0f4bc0", CMOVNP(eax, eax));
	TEST_INST("480f4bc0", CMOVNP(rax, rax));
	TEST_INST("660f49c0", CMOVNS(ax, ax));
	TEST_INST("0f49c0", CMOVNS(eax, eax));
	TEST_INST("480f49c0", CMOVNS(rax, rax));
	TEST_INST("660f45c0", CMOVNZ(ax, ax));
	TEST_INST("0f45c0", CMOVNZ(eax, eax));
	TEST_INST("480f45c0", CMOVNZ(rax, rax));
	TEST_INST("660f40c0", CMOVO(ax, ax));
	TEST_INST("0f40c0", CMOVO(eax, eax));
	TEST_INST("480f40c0", CMOVO(rax, rax));
	TEST_INST("660f4ac0", CMOVP(ax, ax));
	TEST_INST("0f4ac0", CMOVP(eax, eax));
	TEST_INST("480f4ac0", CMOVP(rax, rax));
	TEST_INST("660f4ac0", CMOVPE(ax, ax));
	TEST_INST("0f4ac0", CMOVPE(eax, eax));
	TEST_INST("480f4ac0", CMOVPE(rax, rax));
	TEST_INST("660f4bc0", CMOVPO(ax, ax));
	TEST_INST("0f4bc0", CMOVPO(eax, eax));
	TEST_INST("480f4bc0", CMOVPO(rax, rax));
	TEST_INST("660f48c0", CMOVS(ax, ax));
	TEST_INST("0f48c0", CMOVS(eax, eax));
	TEST_INST("480f48c0", CMOVS(rax, rax));
	TEST_INST("660f44c0", CMOVZ(ax, ax));
	TEST_INST("0f44c0", CMOVZ(eax, eax));
	TEST_INST("480f44c0", CMOVZ(rax, rax));
	TEST_INST("3c64", CMP(al, I8(100)));
	TEST_INST("6683f864", CMP(ax, I16(100)));
	TEST_INST("83f864", CMP(eax, I32(100)));
	TEST_INST("4883f864", CMP(rax, I32(100)));
	TEST_INST("6683f864", CMP(ax, I8(100)));
	TEST_INST("83f864", CMP(eax, I8(100)));
	TEST_INST("4883f864", CMP(rax, I8(100)));
	TEST_INST("38c0", CMP(al, al));
	TEST_INST("6639c0", CMP(ax, ax));
	TEST_INST("39c0", CMP(eax, eax));
	TEST_INST("4839c0", CMP(rax, rax));
	TEST_INST("f20f38f0c0", CRC32(eax, al));
	TEST_INST("66f20f38f1c0", CRC32(eax, ax));
	TEST_INST("f20f38f1c0", CRC32(eax, eax));
	TEST_INST("f2480f38f0c0", CRC32(rax, al));
	TEST_INST("f2480f38f1c0", CRC32(rax, rax));
	TEST_INST("c8640064", ENTER(I16(100), I8(100)));
	TEST_INST("660fafc0", IMUL(ax, ax));
	TEST_INST("0fafc0", IMUL(eax, eax));
	TEST_INST("480fafc0", IMUL(rax, rax));
	TEST_INST("66f30fbdc0", LZCNT(ax, ax));
	TEST_INST("f30fbdc0", LZCNT(eax, eax));
	TEST_INST("f3480fbdc0", LZCNT(rax, rax));
	TEST_INST("88c0", MOV(al, al));
	TEST_INST("6689c0", MOV(ax, ax));
	TEST_INST("89c0", MOV(eax, eax));
	TEST_INST("4889c0", MOV(rax, rax));
	TEST_INST("b064", MOV(al, I8(100)));
	TEST_INST("66b86400", MOV(ax, I16(100)));
	TEST_INST("b864000000", MOV(eax, I32(100)));
	TEST_INST("b864000000", MOV(rax, I64(100)));
	TEST_INST("b864000000", MOV(rax, I32(100)));
	TEST_INST("660fbec0", MOVSX(ax, al));
	TEST_INST("0fbec0", MOVSX(eax, al));
	TEST_INST("480fbec0", MOVSX(rax, al));
	TEST_INST("0fbfc0", MOVSX(eax, ax));
	TEST_INST("480fbfc0", MOVSX(rax, ax));
	TEST_INST("4863c0", MOVSXD(rax, eax));
	TEST_INST("660fb6c0", MOVZX(ax, al));
	TEST_INST("0fb6c0", MOVZX(eax, al));
	TEST_INST("480fb6c0", MOVZX(rax, al));
	TEST_INST("0fb7c0", MOVZX(eax, ax));
	TEST_INST("480fb7c0", MOVZX(rax, ax));
	TEST_INST("0c64", OR(al, I8(100)));
	TEST_INST("6683c864", OR(ax, I16(100)));
	TEST_INST("83c864", OR(eax, I32(100)));
	TEST_INST("4883c864", OR(rax, I32(100)));
	TEST_INST("6683c864", OR(ax, I8(100)));
	TEST_INST("83c864", OR(eax, I8(100)));
	TEST_INST("4883c864", OR(rax, I8(100)));
	TEST_INST("08c0", OR(al, al));
	TEST_INST("6609c0", OR(ax, ax));
	TEST_INST("09c0", OR(eax, eax));
	TEST_INST("4809c0", OR(rax, rax));
	TEST_INST("66f30fb8c0", POPCNT(ax, ax));
	TEST_INST("f30fb8c0", POPCNT(eax, eax));
	TEST_INST("f3480fb8c0", POPCNT(rax, rax));
	TEST_INST("c0d064", RCL(al, I8(100)));
	TEST_INST("66c1d064", RCL(ax, I8(100)));
	TEST_INST("c1d064", RCL(eax, I8(100)));
	TEST_INST("48c1d064", RCL(rax, I8(100)));
	TEST_INST("c0d864", RCR(al, I8(100)));
	TEST_INST("66c1d864", RCR(ax, I8(100)));
	TEST_INST("c1d864", RCR(eax, I8(100)));
	TEST_INST("48c1d864", RCR(rax, I8(100)));
	TEST_INST("c0c064", ROL(al, I8(100)));
	TEST_INST("66c1c064", ROL(ax, I8(100)));
	TEST_INST("c1c064", ROL(eax, I8(100)));
	TEST_INST("48c1c064", ROL(rax, I8(100)));
	TEST_INST("c0c864", ROR(al, I8(100)));
	TEST_INST("66c1c864", ROR(ax, I8(100)));
	TEST_INST("c1c864", ROR(eax, I8(100)));
	TEST_INST("48c1c864", ROR(rax, I8(100)));
	TEST_INST("c0e064", SAL(al, I8(100)));
	TEST_INST("66c1e064", SAL(ax, I8(100)));
	TEST_INST("c1e064", SAL(eax, I8(100)));
	TEST_INST("48c1e064", SAL(rax, I8(100)));
	TEST_INST("c0f864", SAR(al, I8(100)));
	TEST_INST("66c1f864", SAR(ax, I8(100)));
	TEST_INST("c1f864", SAR(eax, I8(100)));
	TEST_INST("48c1f864", SAR(rax, I8(100)));
	TEST_INST("1c64", SBB(al, I8(100)));
	TEST_INST("6683d864", SBB(ax, I16(100)));
	TEST_INST("83d864", SBB(eax, I32(100)));
	TEST_INST("4883d864", SBB(rax, I32(100)));
	TEST_INST("6683d864", SBB(ax, I8(100)));
	TEST_INST("83d864", SBB(eax, I8(100)));
	TEST_INST("4883d864", SBB(rax, I8(100)));
	TEST_INST("18c0", SBB(al, al));
	TEST_INST("6619c0", SBB(ax, ax));
	TEST_INST("19c0", SBB(eax, eax));
	TEST_INST("4819c0", SBB(rax, rax));
	TEST_INST("c0e064", SHL(al, I8(100)));
	TEST_INST("66c1e064", SHL(ax, I8(100)));
	TEST_INST("c1e064", SHL(eax, I8(100)));
	TEST_INST("48c1e064", SHL(rax, I8(100)));
	TEST_INST("c0e864", SHR(al, I8(100)));
	TEST_INST("66c1e864", SHR(ax, I8(100)));
	TEST_INST("c1e864", SHR(eax, I8(100)));
	TEST_INST("48c1e864", SHR(rax, I8(100)));
	TEST_INST("2c64", SUB(al, I8(100)));
	TEST_INST("6683e864", SUB(ax, I16(100)));
	TEST_INST("83e864", SUB(eax, I32(100)));
	TEST_INST("4883e864", SUB(rax, I32(100)));
	TEST_INST("6683e864", SUB(ax, I8(100)));
	TEST_INST("83e864", SUB(eax, I8(100)));
	TEST_INST("4883e864", SUB(rax, I8(100)));
	TEST_INST("28c0", SUB(al, al));
	TEST_INST("6629c0", SUB(ax, ax));
	TEST_INST("29c0", SUB(eax, eax));
	TEST_INST("4829c0", SUB(rax, rax));
	TEST_INST("a864", TEST(al, I8(100)));
	TEST_INST("66a96400", TEST(ax, I16(100)));
	TEST_INST("a964000000", TEST(eax, I32(100)));
	TEST_INST("48a964000000", TEST(rax, I32(100)));
	TEST_INST("84c0", TEST(al, al));
	TEST_INST("6685c0", TEST(ax, ax));
	TEST_INST("85c0", TEST(eax, eax));
	TEST_INST("4885c0", TEST(rax, rax));
	TEST_INST("66f30fbcc0", TZCNT(ax, ax));
	TEST_INST("f30fbcc0", TZCNT(eax, eax));
	TEST_INST("f3480fbcc0", TZCNT(rax, rax));
	TEST_INST("0fc0c0", XADD(al, al));
	TEST_INST("660fc1c0", XADD(ax, ax));
	TEST_INST("0fc1c0", XADD(eax, eax));
	TEST_INST("480fc1c0", XADD(rax, rax));
	TEST_INST("86c0", XCHG(al, al));
	TEST_INST("6690", XCHG(ax, ax));
	TEST_INST("87c0", XCHG(eax, eax));
	TEST_INST("4890", XCHG(rax, rax));
	TEST_INST("3464", XOR(al, I8(100)));
	TEST_INST("6683f064", XOR(ax, I16(100)));
	TEST_INST("83f064", XOR(eax, I32(100)));
	TEST_INST("4883f064", XOR(rax, I32(100)));
	TEST_INST("6683f064", XOR(ax, I8(100)));
	TEST_INST("83f064", XOR(eax, I8(100)));
	TEST_INST("4883f064", XOR(rax, I8(100)));
	TEST_INST("30c0", XOR(al, al));
	TEST_INST("6631c0", XOR(ax, ax));
	TEST_INST("31c0", XOR(eax, eax));
	TEST_INST("4831c0", XOR(rax, rax));

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
