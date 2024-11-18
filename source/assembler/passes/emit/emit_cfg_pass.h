#pragma once
#include "assembler/instruction/instruction.h"
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	namespace detail {
		// register names
		static constexpr const char* g_gpr8_names[] = { "ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "al", "cl", "dl", "bl", "spl", "bpl", "sil", "dil" };
		static constexpr const char* g_gpr32_names[] = { "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" };
		static constexpr const char* g_gpr64_names[] = { "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" };

		auto instruction_block_to_string(const basic_block* block, const section& section, const module& module) -> utility::dynamic_string;
		auto operand_to_string(const instruction* inst, const operand& op, u8 index) -> utility::dynamic_string;
		auto immediate_to_string(imm i) -> utility::dynamic_string;
		auto memory_to_string(mem m) -> utility::dynamic_string;
		auto register_to_string(reg r) -> const char*;

		auto bytes_to_string(const u8* bytes, u8 count) -> utility::dynamic_string;
		auto byte_to_string(u8 byte) -> utility::dynamic_string;
	} // namespace detail

	// generates a CFG representation of the program represented by the specified module, returns a 
	// string containing the relevant Graphviz graph
	auto emit_control_flow_graph(const module& module) -> utility::dynamic_string;
} // namespace baremetal::assembler::pass
