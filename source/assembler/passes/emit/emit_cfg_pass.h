#pragma once
#include "assembler/instruction/instruction.h"
#include "assembler/ir/module.h"

namespace baremetal::assembler::pass {
	namespace detail {
		// long format strings
		constexpr const char* g_instruction_label = "<tr><td align=\"left\" width=\"50px\">{}</td><td align=\"left\" width=\"100px\">{}</td><td align=\"left\" width=\"100px\"><font COLOR=\"black\"><b>{}</b></font></td><td align=\"left\"><font COLOR=\"black\"> ";
		constexpr const char* g_label_header = "<tr><td align=\"left\">{}</td><td></td><td COLSPAN=\"100%\" align=\"left\"><b><font color=\"blue\">{}</font></b></td></tr>";
		constexpr const char* g_block_header = "\t\"{}\"[label=<<table border=\"1\" cellborder=\"0\" cellspacing=\"0\"><tr PORT=\"top\"><td></td></tr>";
		constexpr const char* g_row_header = "<tr PORT=\"bottom\"><td></td></tr></table>>]\n";

		// register names
		static constexpr const char* g_gpr8l_names[] = { "al", "bl", "cl", "dl", "sil", "dil", "spl", "bpl", "r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b" };
		static constexpr const char* g_gpr8h_names[] = { "ah", "bh", "ch", "dh" };
		static constexpr const char* g_gpr16_names[] = { "ax", "bx", "cx", "dx", "si", "di", "sp", "bp", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w" };
		static constexpr const char* g_gpr32_names[] = { "eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" };
		static constexpr const char* g_gpr64_names[] = { "rax", "rcx", "rdx", "rbx", "rsp", "rbp", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" };

		// block types
		auto instruction_block_to_string(const basic_block* block, const section& section, const module& module) -> utility::dynamic_string;
		auto label_block_to_string(const basic_block* block) -> utility::dynamic_string;
		auto data_block_to_string(const basic_block* block) -> utility::dynamic_string;

		auto operand_to_string(const instruction* inst, const operand& op, u8 index) -> utility::dynamic_string;
		auto immediate_to_string(imm i) -> utility::dynamic_string;
		auto memory_to_string(mem m) -> utility::dynamic_string;
		auto register_to_string(reg r) -> const char*;
	} // namespace detail

	// generates a CFG representation of the program represented by the specified module, returns a 
	// string containing the relevant Graphviz graph
	auto emit_control_flow_graph(const module& module) -> utility::dynamic_string;
} // namespace baremetal::assembler::pass
