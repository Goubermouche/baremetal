#include "utilities.h"

using namespace baremetal::tests;

const utility::filepath g_test_path = "source/test_runner/tests";
bool g_quiet = false;

namespace detail {
	auto run_test_encoding() -> bool {
		const utility::filepath test_path = g_test_path / "encoding/test.asm"; 
		const utility::dynamic_string test_file = utility::file::read(test_path);

		baremetal::assembler::context context;
		// baremetal::assembler_parser assembler(&context);

		utility::dynamic_string instruction;
		utility::dynamic_string hex_result;
		utility::dynamic_string expected;
	
		u64 i = 0;

		test_info info("encoding", utility::file::get_file_line_count(test_path), g_quiet);
	
		info.begin_test();
	
		// run individual tests
		while(i < test_file.get_size()) {
			instruction.clear();
			expected.clear();
			hex_result.clear();
			// assembler.clear();
	
			// locate the expected encoding part
			while(i + 1 < test_file.get_size() && test_file[i] != '\n') {
				if(test_file[i] == ';') {
					break;
				}
	
				instruction += test_file[i];
				i++;
			}
	
			i++;
			
			// semicolon located - print it
			while(i + 1 < test_file.get_size() && test_file[i] != '\n') {
				expected += test_file[i];
				i++;
			}
	
			i++;
	
			// empty instructions mean we've reached the end of our test file
			if(instruction.get_size() == 0) {
				break;
			}

			baremetal::assembler::frontend assembler;
			const auto result = assembler.assemble(instruction);
	
			if(result.has_error()) {
				utility::console::print_err("error: '{}'\n", result.get_error());
				info.add_failure();
			}
			else {
				hex_result = bytes_to_string(result.get_value().bytes);
	
				if(hex_result != expected) {
					info.add_failure();
					utility::console::print_err("mismatch: {} - expected '{}', but got '{}'\n", instruction, expected, hex_result); 
				}
				else {
					info.add_success();
				}
			}
		}
	
		return info.end_test();
	}

	auto run_test_binary() -> bool {
		// various tests related to binary layout
		// test format:
		//   ; description
		//   ; expect: expected_output_in_hex
		//   assembly
	
		const auto tests = utility::directory::read(g_test_path / "binary");

		baremetal::assembler::context context;

		utility::dynamic_string test_text;
		utility::dynamic_string hex_result;
		utility::dynamic_string expected;

		test_info info("binary", tests.get_size(), g_quiet);

		info.begin_test();

		for(const auto& test : tests) {
			hex_result.clear();
			expected.clear();
			test_text.clear();

			if(test.get_string().find("ns_2") == utility::dynamic_string::invalid_pos) {
				continue;
			}

			test_text = utility::file::read(test);

			// locate the 'expect' directive
			u64 expected_pos = test_text.find("expect:");

			if(expected_pos == utility::dynamic_string::invalid_pos) {
				utility::console::print_err("cannot find the 'expect:' directive in test '{}'\n", test);
				info.add_failure();
				continue;
			}

			expected_pos += 7; // move past the 'expect' directive
			
			// read to the end of the current line
			while(expected_pos < test_text.get_size() && test_text[expected_pos] != '\n') {
				expected += test_text[expected_pos++];	
			}

			expected = expected.trim();

			// utility::console::print("running {}\n", test);
			baremetal::assembler::frontend assembler;
			const auto result = assembler.assemble(test_text);

			if(result.has_error()) {
				utility::console::print_err("error: {}\n", result.get_error());
				info.add_failure();
			}
			else {
				hex_result = bytes_to_string(result.get_value().bytes);

				if(hex_result != expected) {
					info.add_failure();
					utility::console::print_err("mismatch: {} - expected '{}', but got '{}'\n", test, expected, hex_result); 
				}
				else {
					info.add_success();
				}
				// utility::console::print("{}\n", bytes_to_string(result.get_value().bytes));
			}
		}
		
		return info.end_test();
	}
} // namespace detail

auto get_all_groups() -> utility::dynamic_array<utility::dynamic_string> {
	const auto group_paths = utility::directory::read(g_test_path);
	utility::dynamic_array<utility::dynamic_string> groups;
	
	groups.reserve(group_paths.get_size());

	for(const auto& path : group_paths) {
		groups.push_back(path.get_filename().get_string());
	}

	return groups;
}

void print_help() {
	if(g_quiet) {
		return;
	}

	utility::console::print("test_runner [FLAG] [OPTION] [ARGUMENT]\n\n");
	utility::console::print("flags:\n");
	utility::console::print("  -q, --quiet   don't produce any stdout outputs\n\n");
	utility::console::print("options:\n");
	utility::console::print("  -h, --help    show this help message\n");
	utility::console::print("  -g, --group   specify one or more test groups to run (comma-separated)\n");
	utility::console::print("  -a, --all     run tests in all groups\n");
	utility::console::print("  -l, --list    list all test groups\n\n");
	utility::console::print("examples:\n");
	utility::console::print("  test_runner --all\n");
	utility::console::print("  test_runner --group \"encoding, binary\"\n");
}

auto compare_commands(const char* shortform, const char* longform, const char* input) -> bool {
	return utility::compare_strings(shortform, input) == 0 || utility::compare_strings(longform, input) == 0;
}

auto run_tests(const utility::dynamic_array<utility::dynamic_string>& groups) -> i32 {
	bool result = false;

	for(u64 i = 0; i < groups.get_size(); ++i) {
		if(groups[i] == "encoding") {
			result |= detail::run_test_encoding();
		}
		else if(groups[i] == "binary") {
			result |= detail::run_test_binary();
		}
		else {
			utility::console::print_err("error: unknown instruction group '{}', exiting (type '--help' for help)\n", groups[i]);
			return 1;
		}
	}

	return result;
}

auto check_invalid_option(i32 argc, i32 argi) -> i32 {
	if(argc - 1 - argi == 0) {
		return 0;
	}

	utility::console::print_err("error: too many options specified (type '--help' for help)\n");
	return 1;
}

auto list_groups() -> i32 {
	if(g_quiet) {
		return 0;
	} 

	for(const auto& g : get_all_groups()) {
		utility::console::print("{}\n", g);
	}

	return 0;
}

auto main(i32 argc, const char** argv) -> i32 {
	u8 argi = 1;

	if(argc == 1) {
		return run_tests(get_all_groups());
	}

	// quiet
	if(compare_commands("-q", "--quiet", argv[argi])) {
		g_quiet = true;
		argi++;

		if(argi == argc) {
			utility::console::print_err("error: flag cannot be the only argument  (type '--help' for help)\n");
			return 1;
		}
	}

	// help
	if(compare_commands("-h", "--help", argv[argi])) {
		print_help();
		return 0;
	}

	// run all tests
	if(compare_commands("-a", "--all", argv[argi])) {
		if(check_invalid_option(argc, argi)) {
			return 1;
		}

		return run_tests(get_all_groups());
	}

	// list available groups
	if(compare_commands("-l", "--list", argv[argi])) {
		if(check_invalid_option(argc, argi)) {
			return 1;
		}

		return list_groups();
	}

	// run specific test groups
	if(compare_commands("-g", "--group", argv[argi])) {
		utility::dynamic_array<utility::dynamic_string> groups;
		utility::dynamic_string current_group = "";

		if(argi + 1 == argc) {
			utility::console::print_err("error: no groups were specified (type '--help' for help)\n");
			return 1;
		}

		const char* input = argv[++argi];

		u64 length = utility::string_len(input);
		u64 i = 0;

		while(i < length) {
			if(input[i] == ',') {
				current_group = current_group.trim();

				if(!current_group.is_empty()) {
					groups.push_back(current_group);
					current_group.clear();
				}

				i++;
				continue;
			}

			current_group += input[i++];	
		}

		current_group = current_group.trim();

		if(!current_group.is_empty()) {
			groups.push_back(current_group);
		}

		if(groups.is_empty()) {
			utility::console::print_err("error: no groups were provided, exiting (type '--help' for help)\n");
			return 1;
		}

		if(check_invalid_option(argc, argi)) {
			return 1;
		}

		return run_tests(groups);
	}

	// unknown option
	utility::console::print_err("error: unknown option '{}' specified (type '--help' for help)\n", argv[argi]);
	return 1;
}

