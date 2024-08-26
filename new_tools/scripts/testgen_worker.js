// worker implementation for the testgen utility
const { parentPort, workerData } = require('worker_threads');
const utility = require("./utility.js");

let results = [];
let errors = [];

function assemble_test(test, bin_path, asm_path, temp_path) {
	const assembly = `BITS 64\n${test}`; 
  const command = `nasm -w+all -f bin -o ${bin_path} ${asm_path} > ${temp_path} 2>&1`;

	try {
		utility.write_file(asm_path, assembly);
		utility.execute(command);
	} catch(error) {
		errors.push(`${test} ${utility.read_file(temp_path)}`);
	}

	try {
		results.push(`${test} ;${utility.read_file_hex(bin_path)}`);
	} catch(error) {
		errors.push(`${test} ${utility.read_file(temp_path)}`);
	}
}

function main() {
	const temp_path = utility.get_temp_path(workerData.id);
	const asm_path = utility.get_asm_path(workerData.id);
	const bin_path = utility.get_bin_path(workerData.id);

	// assemble all test cases
	workerData.tests.forEach(test => {
		assemble_test(test, bin_path, asm_path, temp_path);

		if((results.length + errors.length) % 10 === 0) {
			// push an update every 10 tests
			parentPort.postMessage({ id: 'update' });
		}
	})

	// cleanup
	utility.delete_file(temp_path);
  utility.delete_file(bin_path);
  utility.delete_file(asm_path);

	// post results
	parentPort.postMessage({ id: 'result', data: { results: results, errors: errors } });
}

main();
