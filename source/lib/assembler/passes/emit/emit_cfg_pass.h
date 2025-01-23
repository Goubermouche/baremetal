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

		// block types
		[[nodiscard]] auto instruction_block_to_string(const basic_block* block, const section& section, const module& module) -> utility::dynamic_string;
		[[nodiscard]] auto label_block_to_string(const basic_block* block, const section& section) -> utility::dynamic_string;
		[[nodiscard]] auto data_block_to_string(const basic_block* block, const section& section) -> utility::dynamic_string;

		[[nodiscard]] auto operand_to_string(const instruction* inst, const operand& op, u8 index) -> utility::dynamic_string;
		[[nodiscard]] auto broadcast_to_string(const instruction* inst, u8 index) -> utility::dynamic_string;
	} // namespace detail

	// generates a CFG representation of the program represented by the specified module, returns a 
	// string containing the relevant Graphviz graph
	[[nodiscard]] auto emit_control_flow_graph(const module& module) -> utility::dynamic_string;
} // namespace baremetal::assembler::pass
