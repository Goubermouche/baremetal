const { parentPort, workerData } = require('worker_threads');
const utility = require("./utility.js");

const tests = workerData.tests;
let results = [];

function assemble_test(test, bin_path, asm_path, temp_path) {
	const assembly = `BITS 64\n${test}`; 
	const command = `nasm -w+all -f bin -o ${bin_path} ${asm_path} > ${temp_path} 2>&1`;

	utility.write_file(asm_path, assembly);
	utility.execute(command);
	results.push(utility.read_file_hex(bin_path));
}

function main() {
	const temp_path = utility.get_temp_path(workerData.id);
	const asm_path = utility.get_asm_path(workerData.id);
	const bin_path = utility.get_bin_path(workerData.id);
	
	try {
		tests.forEach(test => {
			assemble_test(test.test, bin_path, asm_path, temp_path);
		
			if(results.length % 10 === 0) {
				// push an update every 10 tests
				parentPort.postMessage({ id: 'update' });
			}
		});
	} catch(err) {
	} finally {
		// cleanup
		try {
			utility.delete_file(temp_path);
			utility.delete_file(bin_path);
			utility.delete_file(asm_path);
		} catch(err) {}
	}
	
	// post results
	parentPort.postMessage({ id: 'result', data: results });
}

main();
