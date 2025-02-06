#include <utility/algorithms/sort.h>
#include <utility/containers/set.h>
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
const utility::filepath g_test_path = "./tests";

using namespace utility::types;

enum test_result : u8 {
	RES_PASS,
	RES_FAIL,
	RES_SKIP
};

[[nodiscard]] auto compare_commands(const char* shortform, const char* longform, const char* input) -> bool {
	return utility::compare_strings(shortform, input) == 0 || utility::compare_strings(longform, input) == 0;
}

[[nodiscard]] auto get_all_groups() -> utility::set<utility::dynamic_string> {
	const auto group_paths = utility::directory::read(g_test_path);
	utility::set<utility::dynamic_string> groups;
	
	for(const auto& path : group_paths) {
		groups.insert(path.get_filename().get_string());
	}

	return groups;
}

[[nodiscard]] auto run_test(const utility::filepath& path) -> test_result {
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
	
	u64 end_pos = test_text.find("\n", expected_pos);

	if(end_pos == utility::dynamic_string::invalid_pos) {
    end_pos = test_text.get_size();
	}

	expected = test_text.substring(expected_pos + 1, end_pos - expected_pos - 1);

	// parse the source file
	baremetal::assembler::frontend assembler(test_text);
	const auto result = assembler.parse();

	// check for assembly errors
	if(result.has_error()) {
		utility::console::print_err("error: {}\n", result.get_error());
		return RES_FAIL;
	}

	// optimize the resulting module
	auto module = result.get_value();

	baremetal::assembler::pass::cfg_analyze(module);
	baremetal::assembler::pass::inst_size_minimize(module);
	baremetal::assembler::pass::symbolic_minimize(module);

	utility::dynamic_array<u8> output = baremetal::assembler::pass::emit_binary(module);

	// compare against the expected hex encoding
	utility::dynamic_string hex_result = utility::bytes_to_string(output, output.get_size());

	if(hex_result != expected) {
		utility::console::print_err("mismatch: {} - expected '{}', but got '{}'\n", path, expected, hex_result); 
		// utility::console::print_err("mismatch: {}\n", path); 
		return RES_FAIL;
	}

	return RES_PASS;
}

[[nodiscard]] auto run_tests_groups(const utility::set<utility::dynamic_string>& groups) -> i32 {
	utility::timer timer;

	u64 pass_count = 0;
	u64 skip_count = 0;
	u64 fail_count = 0;

	timer.start();

	for(const auto& group : groups) {
		if(!utility::directory::exists(g_test_path / group)) {
			utility::console::print("skipping unknown test group '{}'\n", group);
			continue;
		}

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

[[nodiscard]] auto run_tests_specific(const utility::set<utility::dynamic_string>& tests) -> i32 {
	utility::timer timer;
	
	u64 pass_count = 0;
	u64 skip_count = 0;
	u64 fail_count = 0;

	timer.start();

	for(const auto& group : get_all_groups()) {
		for(const auto& test : utility::directory::read(g_test_path / group)) {
			const auto test_name = test.get_filename().get_string();

			if(tests.contains(test_name)) {
				test_result result  = run_test(test);

				switch(result) {
					case RES_PASS: pass_count++; break;
					case RES_FAIL: fail_count++; break;
					case RES_SKIP: skip_count++; break;
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
		"usage: test [-l|-h|-v|-p|-s <test_names...>|-g <group_names...>]\n"
		"  -s --specific   specify one or more specific tests to run\n"
		"  -v --version    print the test runner version number\n"
		"  -g --group      specify one or more test groups to run\n"
		"  -l --list       list all available test groups and tests\n"
		"  -p --path       display the path of the test directory\n"
		"  -h --help       display this help message\n"
		"\n"
		"for bug reports and issues, please see:\n"
		"<https://github.com/Goubermouche/baremetal/issues>\n"
	);
}

void display_version() {
	utility::console::print("test runner version {} compiled on {}\n", g_version, __DATE__);
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
	utility::set<utility::dynamic_string> operands;
	u8 argi = 1;

	if(argc == 1) { 
		return run_tests_groups(get_all_groups()); 
	}
	else if(compare_commands("-h", "--help", argv[argi])) { 
		display_help();
		return 0; 
	}
	else if(compare_commands("-v", "--version", argv[argi])) { 
		display_version();
		return 0; 
	}
	else if(compare_commands("-l", "--list", argv[argi])) { 
		list_tests();
		return 0;
	}
	else if(compare_commands("-p", "--path", argv[argi])) { 
		utility::console::print("{}\n", g_test_path);
		return 0;
	}

	// collect operands
	for(i32 i = argi + 1; i < argc; ++i) {
		operands.insert(argv[i]);
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

