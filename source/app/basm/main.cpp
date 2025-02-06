#include <utility/system/file.h>

#include <assembler/frontend.h>

// assembler passes
// optimization
#include <assembler/passes/cfg_analyze_pass.h>
#include <assembler/passes/inst_size_minimize_pass.h>
#include <assembler/passes/symbolic_minimize_pass.h>

// emission
#include <assembler/passes/emit/emit_binary_pass.h>
#include <assembler/passes/emit/emit_elf_pass.h>
#include <assembler/passes/emit/emit_cfg_pass.h>

constexpr const char* g_version = "0.1.0";

using namespace utility::types;

#define MISSING_ARG_VERIFY()                                                                                           \
  if(++argi == argc) {                                                                                                 \
    utility::console::print_err("error: option '{}' requires an argument (type '--help' for help)\n", argv[argi - 1]); \
    return 1;                                                                                                          \
  }

struct arguments {
	enum output_format_type : u8 {
		OUT_BIN,
		OUT_ELF,
		OUT_INVALID // invalid output format
	};

	// output 
	output_format_type output_format = OUT_BIN;
	utility::filepath output_path = "a";

	// control flow graph (emitted when the path is not empty)
	utility::filepath cfg_output_path;

	// source code of the program to assemble
	utility::dynamic_string source;
};

void display_help() {
	utility::console::print(
		"usage: basm [-h|-v|[[-c <outfile>][-f <format>][-o <outfile>] <filename>]]\n"
		"  -v --version    print the BASM version number\n"
		"  -o --output     write the output to outfile\n"
		"  -f --format     select output file format { bin, elf } [bin]\n"
		"  -h --help       display this help message\n"
		"  -c --cfg        generate a graphviz CFG of the processed program and write it to outfile\n"
		"\n"
		"for bug reports and issues, please see:\n"
		"<https://github.com/Goubermouche/baremetal/issues>\n"
	);
}

void display_version() {
	utility::console::print("BASM version {} compiled on {}\n", g_version, __DATE__);
}

[[nodiscard]] auto compare_commands(const char* shortform, const char* longform, const char* input) -> bool {
	return utility::compare_strings(shortform, input) == 0 || utility::compare_strings(longform, input) == 0;
}

[[nodiscard]] auto parse_output_format(const char* format) -> arguments::output_format_type {
	if(utility::compare_strings("bin", format) == 0) {
		return arguments::OUT_BIN;
	}
	else if(utility::compare_strings("elf", format) == 0) {
		return arguments::OUT_ELF;
	}

	return arguments::OUT_INVALID;
}

[[nodiscard]] auto assemble(const arguments& args) -> i32 {
	baremetal::assembler::frontend frontend(args.source);
	const auto result = frontend.parse();

	if(result.has_error()) {
		utility::console::print_err("error: {}\n", result.get_error());
		return 1;
	}

	auto module = result.get_value();

	// apply optimizations
	baremetal::assembler::pass::cfg_analyze(module);
	baremetal::assembler::pass::inst_size_minimize(module);
	baremetal::assembler::pass::symbolic_minimize(module);

	// emission
	// control flow graph
	if(!args.cfg_output_path.is_empty()) {
		const auto graph = baremetal::assembler::pass::emit_control_flow_graph(module);
		utility::file::write(args.cfg_output_path, graph);
	}

	// output
	utility::dynamic_array<u8> output;

	switch(args.output_format) {
		case arguments::OUT_BIN: output = baremetal::assembler::pass::emit_binary(module); break;
		case arguments::OUT_ELF: output = baremetal::assembler::pass::emit_elf(module); break;
		default: ASSERT(false, "unrecognized output format\n");
	}

	utility::file::write(args.output_path, output);
	return 0;
}

auto main(i32 argc, const char** argv) -> i32 {
	arguments args;
	i32 argi = 1;

	// parse optional operands
	for(; argi < argc; ++argi) {
		if(compare_commands("-h", "--help", argv[argi])) {
			display_help();
			return 0;
		}
		else if(compare_commands("-v", "--version", argv[argi])) {
			display_version();
			return 0;
		}
		else if(compare_commands("-f", "--format", argv[argi])) {
			MISSING_ARG_VERIFY();
			args.output_format = parse_output_format(argv[argi]);

			if(args.output_format == arguments::OUT_INVALID) {
				utility::console::print_err("error: unrecognized output format '{}' (type '--help' for help)\n", argv[argi]);
				return 1;
			}
		}
		else if(compare_commands("-c", "--cfg", argv[argi])) {
			MISSING_ARG_VERIFY();
			args.cfg_output_path = argv[argi];
		}
		else if(compare_commands("-o", "--output", argv[argi])) {
			MISSING_ARG_VERIFY();
			args.output_path = argv[argi];
		}
		else {
			break;
		}
	}

	// parse the source operand
	// missing source operand
	if(argi >= argc) {
		utility::console::print_err("error: no input file specified (type '--help' for help)\n");
		return 1;
	}

	const utility::filepath source_path = argv[argi++];

	// source file doesn't exist
	if(!utility::file::exists(source_path)) {
		utility::console::print_err("error: unable to open input file '{}', no such file or directory\n", source_path);
		return 1;
	}

	args.source = utility::file::read(source_path);

	// not all arguments have been processed
	if(argi < argc) {
		utility::console::print_err("error: unknown option '{}' specified (type '--help' for help)\n", argv[argi]);
		return 1;
	}
	
	return assemble(args);
}
