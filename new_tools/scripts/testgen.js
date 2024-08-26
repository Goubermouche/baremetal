const { Worker } = require('worker_threads');
const utility = require("./utility.js");
const path = require('path');
const os = require('os');
const fs = require('fs');

function generate_combinations(operands) {
	const operand_map = new Map([
		['dx', [ 'dx' ]],
		['eax', [ 'eax' ]],
		['ax', [ 'ax' ]],
		['al', [ 'al' ]],
		['rax', [ 'rax' ]],
		['cl', [ 'cl' ]],
		['ds', [ 'ds' ]],
		['ss', [ 'ss' ]],
		['es', [ 'es' ]],
		['fs', [ 'fs' ]],
		['gs', [ 'gs' ]],
		['cs', [ 'cs' ]],
		['r8', [ 'cl', 'dl', 'bl' ]],
    ['r16', [ 'cx', 'dx', 'bx', 'r15w' ]],
    ['r32', [ 'ecx', 'edx', 'ebx', 'r15d' ]],
    ['r64', [ 'rcx', 'rdx', 'rbx', 'r15' ]],
    ['xmm', [ 'xmm0', 'xmm1', 'xmm2', 'xmm15' ]],
		['ymm', [ 'ymm0', 'ymm1', 'ymm2', 'ymm15', 'ymm31']],
		['zmm', [ 'zmm0', 'zmm1', 'zmm2', 'zmm15', 'zmm31']],
		['bnd', [ 'bnd0', 'bnd1', 'bnd2', 'bnd3']],
		['sreg', [ 'cs', 'ds', 'es', 'ss', 'fs', 'gs' ]],
    ['dreg', [ 'dr0', 'dr1', 'dr2', 'dr3', 'dr7' ]],
    ['creg', [ 'cr0', 'cr1', 'cr2', 'cr3', 'cr8' ]],
		['xmm_kz', [ 'xmm1{k1}{z}', 'xmm2{k2}{z}', 'xmm15{k7}{z}']],
		['ymm_kz', [ 'ymm1{k1}{z}', 'ymm2{k2}{z}', 'ymm15{k7}{z}']],
		['zmm_kz', [ 'zmm1{k1}{z}', 'zmm2{k2}{z}', 'zmm15{k7}{z}']],
    ['1', [ '1' ]],
    ['i8', [ '0', '1', '127', '-128' ]],
    ['i16', [ '0', '1', '32767', '-32768', '127', '-128' ]],
    ['i32', [ '0', '1', '2147483647', '-2147483648', '32767', '-32768', '127', '-128' ]],
    ['i64', [ '0', '1', '9223372036854775807', '-9223372036854775808', '2147483647', '-2147483648', '32767', '-32768', '127', '-128' ]],
		['mem', [
      '[0x0]', '[0xFF]', '[0xFFFF]',
      '[rel $ + 0x0]', '[rel $ + 0xFF]', '[rel $ + 0xFFFF]',
			'[rax]',
      '[rax + 0x0]', '[rax + 0xFFFF]', '[r15 + 0xFFFF]',
      '[rax + rsi * 1  + 0x0]', '[rax + rsi + 0xFFFF]', '[r15 + rsi + 0xFFFF]', '[rax + r15 + 0xFFFF]',
      '[rax + rsi * 2 + 0xFFFF2]', '[rax + rsi * 4 + 0xFFFF4]', '[rax + rsi * 8 + 0xFFFF8]', '[rsp + rax * 8 + 0xFFFF8]', '[r15 + rax * 8 + 0xFFFF8]', '[rsp + r15 * 8 + 0xFFFF8]', '[r14 + r15 * 8 + 0xFFFF8]'
    ]],
		['m8', [
      'byte [0x0]', 'byte [0xFF]', 'byte [0xFFFF]',
      'byte [rel $ + 0x0]', 'byte [rel $ + 0xFF]', 'byte [rel $ + 0xFFFF]',
			'byte [rax]',
      'byte [rax + 0x0]', 'byte [rax + 0xFFFF]', 'byte [r15 + 0xFFFF]',
      'byte [rax + rsi * 1  + 0x0]', 'byte [rax + rsi + 0xFFFF]', 'byte [r15 + rsi + 0xFFFF]', 'byte [rax + r15 + 0xFFFF]',
      'byte [rax + rsi * 2 + 0xFFFF2]', 'byte [rax + rsi * 4 + 0xFFFF4]', 'byte [rax + rsi * 8 + 0xFFFF8]', 'byte [rsp + rax * 8 + 0xFFFF8]', 'byte [r15 + rax * 8 + 0xFFFF8]', 'byte [rsp + r15 * 8 + 0xFFFF8]', 'byte [r14 + r15 * 8 + 0xFFFF8]'
    ]],
		['m16', [
      'word [0x0]', 'word [0xFF]', 'word [0xFFFF]',
      'word [rel $ + 0x0]', 'word [rel $ + 0xFF]', 'word [rel $ + 0xFFFF]',
			'word [rax]',
      'word [rax + 0x0]', 'word [rax + 0xFFFF]', 'word [r15 + 0xFFFF]',
      'word [rax + rsi * 1  + 0x0]', 'word [rax + rsi + 0xFFFF]', 'word [r15 + rsi + 0xFFFF]', 'word [rax + r15 + 0xFFFF]',
      'word [rax + rsi * 2 + 0xFFFF2]', 'word [rax + rsi * 4 + 0xFFFF4]', 'word [rax + rsi * 8 + 0xFFFF8]', 'word [rsp + rax * 8 + 0xFFFF8]', 'word [r15 + rax * 8 + 0xFFFF8]', 'word [rsp + r15 * 8 + 0xFFFF8]', 'word [r14 + r15 * 8 + 0xFFFF8]'
    ]],
		['m32', [
      'dword [0x0]', 'dword [0xFF]', 'dword [0xFFFF]',
      'dword [rel $ + 0x0]', 'dword [rel $ + 0xFF]', 'dword [rel $ + 0xFFFF]',
			'dword [rax]',
      'dword [rax + 0x0]', 'dword [rax + 0xFFFF]', 'dword [r15 + 0xFFFF]',
      'dword [rax + rsi * 1  + 0x0]', 'dword [rax + rsi + 0xFFFF]', 'dword [r15 + rsi + 0xFFFF]', 'dword [rax + r15 + 0xFFFF]',
      'dword [rax + rsi * 2 + 0xFFFF2]', 'dword [rax + rsi * 4 + 0xFFFF4]', 'dword [rax + rsi * 8 + 0xFFFF8]', 'dword [rsp + rax * 8 + 0xFFFF8]', 'dword [r15 + rax * 8 + 0xFFFF8]', 'dword [rsp + r15 * 8 + 0xFFFF8]', 'dword [r14 + r15 * 8 + 0xFFFF8]'
    ]],
		['m64', [
      'qword [0x0]', 'qword [0xFF]', 'qword [0xFFFF]',
      'qword [rel $ + 0x0]', 'qword [rel $ + 0xFF]', 'qword [rel $ + 0xFFFF]',
			'qword [rax]',
      'qword [rax + 0x0]', 'qword [rax + 0xFFFF]', 'qword [r15 + 0xFFFF]',
      'qword [rax + rsi * 1  + 0x0]', 'qword [rax + rsi + 0xFFFF]', 'qword [r15 + rsi + 0xFFFF]', 'qword [rax + r15 + 0xFFFF]',
      'qword [rax + rsi * 2 + 0xFFFF2]', 'qword [rax + rsi * 4 + 0xFFFF4]', 'qword [rax + rsi * 8 + 0xFFFF8]', 'qword [rsp + rax * 8 + 0xFFFF8]', 'qword [r15 + rax * 8 + 0xFFFF8]', 'qword [rsp + r15 * 8 + 0xFFFF8]', 'qword [r14 + r15 * 8 + 0xFFFF8]'
    ]],
		['m128', [
      '[0x0]', '[0xFF]', '[0xFFFF]',
      '[rel $ + 0x0]', '[rel $ + 0xFF]', '[rel $ + 0xFFFF]',
			'[rax]',
      '[rax + 0x0]', '[rax + 0xFFFF]', '[r15 + 0xFFFF]',
      '[rax + rsi * 1  + 0x0]', '[rax + rsi + 0xFFFF]', '[r15 + rsi + 0xFFFF]', '[rax + r15 + 0xFFFF]',
      '[rax + rsi * 2 + 0xFFFF2]', '[rax + rsi * 4 + 0xFFFF4]', '[rax + rsi * 8 + 0xFFFF8]', '[rsp + rax * 8 + 0xFFFF8]', '[r15 + rax * 8 + 0xFFFF8]', '[rsp + r15 * 8 + 0xFFFF8]', '[r14 + r15 * 8 + 0xFFFF8]'
    ]],
		['m256', [
      '[0x0]', '[0xFF]', '[0xFFFF]',
      '[rel $ + 0x0]', '[rel $ + 0xFF]', '[rel $ + 0xFFFF]',
			'[rax]',
      '[rax + 0x0]', '[rax + 0xFFFF]', '[r15 + 0xFFFF]',
      '[rax + rsi * 1  + 0x0]', '[rax + rsi + 0xFFFF]', '[r15 + rsi + 0xFFFF]', '[rax + r15 + 0xFFFF]',
      '[rax + rsi * 2 + 0xFFFF2', '[rax + rsi * 4 + 0xFFFF4]', '[rax + rsi * 8 + 0xFFFF8]', '[rsp + rax * 8 + 0xFFFF8]', '[r15 + rax * 8 + 0xFFFF8]', '[rsp + r15 * 8 + 0xFFFF8]', '[r14 + r15 * 8 + 0xFFFF8]'
    ]],
		['m512', [
      '[0x0]', '[0xFF]', '[0xFFFF]',
      '[rel $ + 0x0]', '[rel $ + 0xFF]', '[rel $ + 0xFFFF]',
			'[rax]',
      '[rax + 0x0]', '[rax + 0xFFFF]', '[r15 + 0xFFFF]',
      '[rax + rsi * 1  + 0x0]', '[rax + rsi + 0xFFFF]', '[r15 + rsi + 0xFFFF]', '[rax + r15 + 0xFFFF]',
      '[rax + rsi * 2 + 0xFFFF2]', '[rax + rsi * 4 + 0xFFFF4]', '[rax + rsi * 8 + 0xFFFF8]', '[rsp + rax * 8 + 0xFFFF8]', '[r15 + rax * 8 + 0xFFFF8]', '[rsp + r15 * 8 + 0xFFFF8]', '[r14 + r15 * 8 + 0xFFFF8]'
    ]],
		['rel8', [ '0', '1', '-128', '127' ]],
		['rel16', [ '0', '1', '-128', '127' ]],
		['rel32', [ '0', '1', '-128', '127' ]],
		['moff8', ['[qword 0]', '[qword 0xFF]', '[qword 0xFFFF]', '[qword 0xFFFFFFFF]', '[qword 0xFFFFFFFFFFFFFFFF]']],
		['moff16', ['[qword 0]', '[qword 0xFF]', '[qword 0xFFFF]', '[qword 0xFFFFFFFF]', '[qword 0xFFFFFFFFFFFFFFFF]']],
		['moff32', ['[qword 0]', '[qword 0xFF]', '[qword 0xFFFF]', '[qword 0xFFFFFFFF]', '[qword 0xFFFFFFFFFFFFFFFF]']],
		['moff64', ['[qword 0]', '[qword 0xFF]', '[qword 0xFFFF]', '[qword 0xFFFFFFFF]', '[qword 0xFFFFFFFFFFFFFFFF]']],
	]);

	function generate(operands, index) {
		if(index === operands.length) {
			return [[]];
		}

		const current = operands[index];

		if(!operand_map.has(current)) {
			console.error(`unknown operand '${current}'`);
		}

		const current_array = operand_map.get(current) || [];
		const remaining = generate(operands, index + 1);
		const combinations = [];

		for(const value of current_array) {
			for(const combination of remaining) {
				combinations.push([value, ...combination]);
			}
		}

		return combinations;
	}

	return generate(operands, 0);
}

function main() {
	// handle inputs
	if(process.argv.length != 4) {
		console.error(`expected 2 arguments but got ${process.argv.length - 2} arguments instead`);
		return 1;
	}
	
	let instructions;
	let tests = [];
	
	try {
	  const data = fs.readFileSync(process.argv[2], 'utf8');
	  instructions = JSON.parse(data);
	} catch (err) {
	  console.error('error reading source database: ', err);
		process.exit(1);
	}

	// generate our tests
	instructions.forEach(inst => {
		let operand_combinations = generate_combinations(inst.operands);

		operand_combinations.forEach(combination => {
			tests.push(`${inst.name} ${combination.join(', ')}`);
		});
	});

	// calculate the worker count
	const worker_path = path.join(__dirname, 'testgen_worker.js');
	const worker_count = Math.max(Math.min(Math.floor(tests.length / 1000), os.cpus().length - 1), 1);
	const chunk_size = Math.ceil(tests.length / worker_count);

	let assembled_tests = [];
	let finished_count = 0; // count of finished tests so that we can print the total %

	// initialize our workers
	const worker_promises = Array.from({ length: worker_count }, (_, i) => {
		return new Promise((resolve, reject) => {
			const start = i * chunk_size;
			const end = Math.min(start + chunk_size, tests.length);
			const worker_tests = tests.slice(start, end);
			const worker = new Worker(worker_path, { workerData: { tests: worker_tests, id: i } });

			worker.on('message', (message) => {
				switch(message.id) {
					case 'update': {
						finished_count += 10; // we send an update every 10 tests
						process.stdout.write(`${finished_count}/${tests.length}\r`);
						break;
					}
					case 'result': resolve(message.data); break;
					default: console.error(`unknown worker message id '${message.id}' received`);
				}
			});

			worker.on('error', (error) => {
				reject(error);
			});

			worker.on('exit', (code) => {
				if (code !== 0) {
					reject(new Error(`worker stopped with exit code ${code}`));
				}
			});
		});
	});

	// run all worker threads
	Promise.all(worker_promises)
		.then(result => {
			let total_errors = 0;

			result.forEach(res => {
				total_errors += res.errors.length;
			});

			if(total_errors > 0) {
				console.error(`encountered ${total_errors} errors`);

				result.forEach(res => {
					res.errors.forEach(err => {
						console.error(err);
					});
				});
			}

			let test_text = '';

			result.forEach(res => {
				res.results.forEach(res => {
					 test_text += `${res}\n`; 
				});
			});

			utility.write_file(process.argv[3], test_text);
			process.exit(0);
		})
		.catch(error => {
			console.error(error);
			process.exit(1);
		});

	return 0;
}

main();

