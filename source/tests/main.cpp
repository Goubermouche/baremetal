#include "utilities.h"

#include "utility/system/console.h"
#include <utility/system/filepath.h>
#include <utility/system/file.h> 

using namespace baremetal::tests;

auto main() -> i32 {
	utility::timer timer;
	timer.start();

	// load up our tests
	const utility::filepath test_path = "source/tests/tests.txt"; 
	const utility::dynamic_string test_file = utility::file::read(test_path);

	utility::dynamic_string instruction;
	utility::dynamic_string result;
	utility::dynamic_string expected;

	baremetal::assembler assembler;
	u64 i = 0;	
	u64 sucess_count = 0;
	u64 fail_count = 0;

	// run individual test
	while(i < test_file.get_size()) {
		instruction.clear();
		expected.clear();
		result.clear();
		assembler.clear();

		// locate the expected encoding part
		while(test_file[i] != '\n') {
			if(test_file[i] == ';') {
				break;
			}

			instruction += test_file[i];
			i++;
		}

		i++;
		
		// semicolon located - print it
		while(test_file[i] != '\n') {
			expected += test_file[i];
			i++;
		}

		i++;

		assembler.assemble(instruction);
		result = bytes_to_string(assembler.get_bytes());

		if(result != expected) {
			fail_count++;
			utility::console::print_err("mismatch: {} - expected '{}', but got '{}'\n", instruction, expected, result); 
		}
		else {
			sucess_count++;
		}
	}
	
	timer.stop();

	utility::console::print(
		"tests finished ({} / {} tests passed in {}s)\n", 
		sucess_count,
		sucess_count + fail_count, 
		timer.get_elapsed_sec()
	);

	return 0;
}

