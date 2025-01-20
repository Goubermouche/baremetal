#include "utilities.h"

#include <utility/algorithms/sort.h>

using namespace baremetal::tests;

const utility::filepath g_test_path = "source/test_runner/tests";
bool g_quiet = false; // TODO: not used yet

enum test_result : u8 {
	RES_PASS,
	RES_FAIL,
	RES_SKIP
};

auto compare_commands(const char* shortform, const char* longform, const char* input) -> bool {
	return utility::compare_strings(shortform, input) == 0 || utility::compare_strings(longform, input) == 0;
}

auto get_all_groups() -> utility::dynamic_array<utility::dynamic_string> {
	const auto group_paths = utility::directory::read(g_test_path);
	utility::dynamic_array<utility::dynamic_string> groups;
	
	groups.reserve(group_paths.get_size());

	for(const auto& path : group_paths) {
		groups.push_back(path.get_filename().get_string());
	}

	return groups;
}

auto run_test(const utility::filepath& path) -> test_result {
	baremetal::assembler::frontend assembler;
	
	utility::dynamic_string test_text = utility::file::read(path);
	utility::dynamic_string expected;

	// skip tests with the 'skip' directive
	if(test_text.find("skip") != utility::dynamic_string::invalid_pos) {
		// utility::console::print("skipping test '{}'\n", path);
		return RES_SKIP;
	}

	// locate the 'expect' directive
	u64 expected_pos = test_text.find("expect:");

	if(expected_pos == utility::dynamic_string::invalid_pos) {
		utility::console::print_err("cannot find the 'expect:' directive in test '{}'\n", path);
		return RES_FAIL;
	}

	expected_pos += 7; // move past the 'expect' directive
	
	// read to the end of the current line
	while(expected_pos < test_text.get_size() && test_text[expected_pos] != '\n') {
		expected += test_text[expected_pos++];	
	}

	expected = expected.trim();

	// assemble the source file
	const auto result = assembler.assemble(test_text);

	// check for assembly errors
	if(result.has_error()) {
		utility::console::print_err("error: {}\n", result.get_error());
		return RES_FAIL;
	}

	// compare against the expected hex encoding
	utility::dynamic_string hex_result = utility::bytes_to_string(result.get_value(), result.get_value().get_size());

	if(hex_result != expected) {
		utility::console::print_err("mismatch: {} - expected '{}', but got '{}'\n", path, expected, hex_result); 
		return RES_FAIL;
	}

	return RES_PASS;
}

auto run_tests_groups(const utility::dynamic_array<utility::dynamic_string>& groups) -> i32 {
	utility::timer timer;

	u64 pass_count = 0;
	u64 skip_count = 0;
	u64 fail_count = 0;

	timer.start();

	for(const auto& group : groups) {
		for(const auto& test : utility::directory::read(g_test_path / group)) {
			test_result result = run_test(test);

			switch(result) {
				case RES_PASS: pass_count++; break;
				case RES_FAIL: fail_count++; break;
				case RES_SKIP: skip_count++; break;
			}
		}
	}

	timer.stop();

	utility::console::print(
		"{}/{} tests successfully finished ({} tests skipped) in {}s\n",
		pass_count, pass_count + fail_count, skip_count, timer.get_elapsed_s()
	);

	return fail_count;
}

auto run_tests_specific(const utility::dynamic_array<utility::dynamic_string>& tests) -> i32 {
	utility::timer timer;
	
	u64 pass_count = 0;
	u64 skip_count = 0;
	u64 fail_count = 0;

	timer.start();

	for(const auto& group : get_all_groups()) {
		for(const auto& test : utility::directory::read(g_test_path / group)) {
			const auto test_name = test.get_filename().get_string();

			// TODO: use a set
			for(const auto& specified : tests) {
				if(test_name == specified) {
					test_result result  = run_test(test);

					switch(result) {
						case RES_PASS: pass_count++; break;
						case RES_FAIL: fail_count++; break;
						case RES_SKIP: skip_count++; break;
					}

					break;
				}
			}
		}
	}

	timer.stop();

	utility::console::print(
		"{}/{} tests successfully finished ({} tests skipped) in {}s\n",
		pass_count, pass_count + fail_count, skip_count, timer.get_elapsed_s()
	);

	return fail_count;
}

void display_help() {
	utility::console::print(
		"usage: test [-l|-h|[[-q][-s test_names...|-g group_names...]]]\n"
		"  -s --specific   specify one or more specific tests to run\n"
		"  -g --group      specify one or more test groups to run\n"
		"  -q --quiet      don't produce any console outputs\n"
		"  -l --list       list all available test groups and tests\n"
		"  -h --help       display this help message\n"
		"\n"
		"for bug reports and issues, please see:\n"
		"<https://github.com/Goubermouche/baremetal/issues>\n"
	);
}

void list_tests() {
	// groups
	for(const auto& group : utility::directory::read(g_test_path)) {
		auto tests = utility::directory::read(group);

		utility::stable_sort(tests.begin(), tests.end(), [](const auto& left, const auto& right) {
			return left < right;
		});

		utility::console::print("{}:\n", group.get_filename());

		// individual tests
		for(const auto& test : tests) {
			utility::console::print("  {}\n", test.get_filename());
		}
	}
}

auto main(i32 argc, const char** argv) -> i32 {
	utility::dynamic_array<utility::dynamic_string> operands; // TODO: this should be a set
	u8 argi = 1;

	if(argc == 1) { 
		return run_tests_groups(get_all_groups()); 
	}
	else if(compare_commands("-h", "--help", argv[argi])) { 
		display_help();
		return 0; 
	}
	else if(compare_commands("-l", "--list", argv[argi])) { 
		list_tests();
		return 0;
	}
	else if(compare_commands("-q", "--quiet", argv[argi])) { 
		g_quiet = true;
		argi++;
	}

	if(argc == argi) { 
		utility::console::print_err("error: '{}' cannot be used alone (type '--help' for help)\n", argv[argi - 1]); 
		return 1;
	}

	// collect operands
	operands.reserve(argc - argi - 1);

	for(i32 i = argi + 1; i < argc; ++i) {
		operands.push_back(argv[i]);
	}

	// options with operands
	if(compare_commands("-g", "--group", argv[argi])) { 
		return run_tests_groups(operands); 
	}
	else if(compare_commands("-s", "--specific", argv[argi])) {
		return run_tests_specific(operands); 
	}

	utility::console::print_err("error: unknown option '{}' specified (type '--help' for help)\n", argv[argi]);
	return 1;
}

