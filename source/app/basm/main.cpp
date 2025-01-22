#include <utility/system/file.h>

constexpr const char* g_version = "0.1.0";

using namespace utility::types;

struct arguments {
	enum output_format_type : u8 {
		OUT_BIN,
		OUT_ELF,
		OUT_INVALID // invalid output format
	};

	enum flags_type : u8 {
		FLAGS_NONE = 0,
		FLAGS_CFG = 0b00000001 // emit a graphviz CFG
	};

	output_format_type output_format = OUT_BIN; // output file format
	flags_type flags = FLAGS_NONE;              // misc flags

	utility::filepath output_path = "a"; // destination file
	utility::dynamic_string source;      // source program to assemble
};

void display_help() {
	utility::console::print(
		"usage: basm [-h|-v|[[-c][-f format][-o outfile] filename]]\n"
		"  -v --version    print the BASM version number\n"
		"  -o --output     write the output to outfile\n"
		"  -f --format     select output file format { bin, elf } [bin]\n"
		"  -h --help       display this help message\n"
		"  -c --cfg        generate a graphviz CFG of the processed program\n"
		"\n"
		"for bug reports and issues, please see:\n"
		"<https://github.com/Goubermouche/baremetal/issues>\n"
	);
}

void display_version() {
	utility::console::print("BASM version {} compiled on {}\n", g_version, __DATE__);
}

auto compare_commands(const char* shortform, const char* longform, const char* input) -> bool {
	return utility::compare_strings(shortform, input) == 0 || utility::compare_strings(longform, input) == 0;
}

auto parse_output_format(const char* format) -> arguments::output_format_type {
	if(utility::compare_strings("bin", format) == 0) {
		return arguments::OUT_BIN;
	}
	else if(utility::compare_strings("elf", format) == 0) {
		return arguments::OUT_ELF;
	}

	return arguments::OUT_INVALID;
}

auto main(i32 argc, const char** argv) -> i32 {
	arguments args;
	i32 argi = 1;

	// parse optional operands
	for(; argi < argc; ++argi) {
		if(compare_commands("-c", "--cfg", argv[argi])) {
			args.flags = static_cast<arguments::flags_type>(static_cast<u8>(args.flags) | static_cast<u8>(arguments::FLAGS_CFG));
		}
		else if(compare_commands("-h", "--help", argv[argi])) {
			display_help();
			return 0;
		}
		else if(compare_commands("-v", "--version", argv[argi])) {
			display_version();
			return 0;
		}
		else if(compare_commands("-f", "--format", argv[argi])) {
			if(++argi == argc) {
				utility::console::print_err("error: option '{}' requires an argument (type '--help' for help)\n", argv[argi - 1]);
				return 1;
			}

			args.output_format = parse_output_format(argv[argi]);

			if(args.output_format == arguments::OUT_INVALID) {
				utility::console::print_err("error: unrecognized output format '{}' (type '--help' for help)\n", argv[argi]);
				return 1;
			}
		}
		else if(compare_commands("-o", "--output", argv[argi])) {
			if(++argi == argc) {
				utility::console::print_err("error: option '{}' requires an argument (type '--help' for help)\n", argv[argi - 1]);
				return 1;
			}

			args.output_path = argv[argi];
			utility::console::print("PARSED out {}\n", argv[argi]);
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

	utility::console::print("output: {}\n", args.output_path);
	utility::console::print("flags : {}\n", static_cast<u8>(args.flags));
	utility::console::print("source: {}\n", args.source);

	return 0;
}
