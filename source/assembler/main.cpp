
#include "assembler/assembler.h"

int main() {
	using namespace baremetal;

	assembler assembler;

	assembler.mov(gpr_reg::RAX, gpr_reg::R10);
	assembler.mov(gpr_reg::RBP, 42);

	return 0;
}
