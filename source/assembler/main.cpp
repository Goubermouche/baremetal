
#include "assembler/assembler.h"

int main() {
	using namespace baremetal;

	assembler assembler;

	assembler.mov(gpr_reg::RAX, gpr_reg::RDI);

	assembler.mov(gpr_reg::RDI, byte(100));
	assembler.mov(gpr_reg::RDI, dword(100));

	const u64 block = assembler.create_block();
	assembler.set_current_block(block);

	// assembler.mov(gpr_reg::RBP, 100);
	// assembler.neg(gpr_reg::R10);
	// assembler.jmp(block);

	assembler.emit();

	return 0;
}
