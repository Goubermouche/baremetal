const { Worker } = require('worker_threads');
const utility = require("./utility.js");
const path = require('path');
const os = require('os');
const fs = require('fs');

function generate_combinations(inst) {
	const operand_map = new Map([
		['dx', [ 'dx' ]],
		['eax', [ 'eax' ]],
		['ecx', [ 'ecx' ]],
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
		['st0', [ 'st0' ]],
		['st', [ 'st0', 'st1', 'st7' ]],
		['r8', [ 'cl', 'dl', 'bl' ]],
    ['r16', [ 'cx', 'dx', 'bx', 'r11w', 'r15w' ]],
    ['r32', [ 'ecx', 'edx', 'ebx', 'r11d', 'r15d' ]],
    ['r64', [ 'rcx', 'rdx', 'rbx', 'r11', 'r15' ]],
    ['xmm', [ 'xmm0', 'xmm1', 'xmm2', 'xmm11', 'xmm15' ]],
		['ymm', [ 'ymm0', 'ymm1', 'ymm2', 'ymm11', 'ymm15', 'ymm31']],
		['zmm', [ 'zmm0', 'zmm1', 'zmm2', 'zmm11', 'zmm15', 'zmm31']],
		['mmx', [ 'mm0', 'mm1', 'mm2', 'mm7']],
		['tmm', [ 'tmm0', 'tmm1', 'tmm2', 'tmm7']],
		['bnd', [ 'bnd0', 'bnd1', 'bnd2', 'bnd3']],
		['sreg', [ 'cs', 'ds', 'es', 'ss', 'fs', 'gs' ]],
    ['dreg', [ 'dr0', 'dr1', 'dr2', 'dr3', 'dr7' ]],
    ['creg', [ 'cr0', 'cr1', 'cr2', 'cr3', 'cr8' ]],
		['xmm_k', [ 'xmm1{k1}', 'xmm2{k2}', 'xmm15{k7}']],
		['ymm_k', [ 'ymm1{k1}', 'ymm2{k2}', 'ymm15{k7}']],
		['zmm_k', [ 'zmm1{k1}', 'zmm2{k2}', 'zmm15{k7}']],
		['xmm_kz', [ 'xmm1{k1}{z}', 'xmm2{k2}{z}', 'xmm15{k7}{z}']],
		['ymm_kz', [ 'ymm1{k1}{z}', 'ymm2{k2}{z}', 'ymm15{k7}{z}']],
		['zmm_kz', [ 'zmm1{k1}{z}', 'zmm2{k2}{z}', 'zmm15{k7}{z}']],
		['k_k', [ 'k1 {k1}', 'k2 {k7}', 'k7 {k7}', 'k7 {k4}' ]],
		['k', [ 'k1', 'k2', 'k7']],
		['k+1', [ 'k1', 'k2', 'k7']],
		['1', [ '1']],
    ['i8', [ '0', '1', '100', '127', '-128']],
    ['i16', [ '0', '1', '5000', '32767', '-32768', '127', '-128']],
    ['i32', [ '0', '1', '10000000', '2147483647', '-2147483648', '32767', '-32768', '127', '-128']],
    ['i64', [ '0', '1', '29929292929292929', '9223372036854775807', '-9223372036854775808', '2147483647', '-2147483648', '32767', '-32768', '127', '-128']],
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
		['m80', [
      'tword [0x0]', 'tword [0xFF]', 'tword [0xFFFF]',
      'tword [rel $ + 0x0]', 'tword [rel $ + 0xFF]', 'tword [rel $ + 0xFFFF]',
			'tword [rax]',
      'tword [rax + 0x0]', 'tword [rax + 0xFFFF]', 'tword [r15 + 0xFFFF]',
      'tword [rax + rsi * 1  + 0x0]', 'tword [rax + rsi + 0xFFFF]', 'tword [r15 + rsi + 0xFFFF]', 'tword [rax + r15 + 0xFFFF]',
      'tword [rax + rsi * 2 + 0xFFFF2]', 'tword [rax + rsi * 4 + 0xFFFF4]', 'tword [rax + rsi * 8 + 0xFFFF8]', 'tword [rsp + rax * 8 + 0xFFFF8]', 'tword [r15 + rax * 8 + 0xFFFF8]', 'tword [rsp + r15 * 8 + 0xFFFF8]', 'tword [r14 + r15 * 8 + 0xFFFF8]'
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
      '[rax + rsi * 2 + 0xFFFF2]', '[rax + rsi * 4 + 0xFFFF4]', '[rax + rsi * 8 + 0xFFFF8]', '[rsp + rax * 8 + 0xFFFF8]', '[r15 + rax * 8 + 0xFFFF8]', '[rsp + r15 * 8 + 0xFFFF8]', '[r14 + r15 * 8 + 0xFFFF8]'
    ]],
		['m512', [
      '[0x0]', '[0xFF]', '[0xFFFF]',
      '[rel $ + 0x0]', '[rel $ + 0xFF]', '[rel $ + 0xFFFF]',
			'[rax]',
      '[rax + 0x0]', '[rax + 0xFFFF]', '[r15 + 0xFFFF]',
      '[rax + rsi * 1  + 0x0]', '[rax + rsi + 0xFFFF]', '[r15 + rsi + 0xFFFF]', '[rax + r15 + 0xFFFF]',
      '[rax + rsi * 2 + 0xFFFF2]', '[rax + rsi * 4 + 0xFFFF4]', '[rax + rsi * 8 + 0xFFFF8]', '[rsp + rax * 8 + 0xFFFF8]', '[r15 + rax * 8 + 0xFFFF8]', '[rsp + r15 * 8 + 0xFFFF8]', '[r14 + r15 * 8 + 0xFFFF8]'
    ]],
		// NOTE: cannot be rip relative
		// TODO: verify
		['tmem', [
      '[0x0]', '[0xFF]', '[0xFFFF]',
			'[rax]',
      '[rax + 0x0]', '[rax + 0xFFFF]', '[r15 + 0xFFFF]',
      '[rax + rsi * 1  + 0x0]', '[rax + rsi + 0xFFFF]', '[r15 + rsi + 0xFFFF]', '[rax + r15 + 0xFFFF]',
      '[rax + rsi * 2 + 0xFFFF2]', '[rax + rsi * 4 + 0xFFFF4]', '[rax + rsi * 8 + 0xFFFF8]', '[rsp + rax * 8 + 0xFFFF8]', '[r15 + rax * 8 + 0xFFFF8]', '[rsp + r15 * 8 + 0xFFFF8]', '[r14 + r15 * 8 + 0xFFFF8]'
    ]],
		['vm32x', [
      '[0x0]', '[0xFF]', '[0xFFFF]',
			'[rax]',
      '[rax + 0x0]', '[rax + 0xFFFF]', '[r15 + 0xFFFF]',
      '[rax + xmm0 * 1  + 0x0]', '[rax + xmm0 + 0xFFFF]', '[r15 + xmm15 + 0xFFFF]', '[rax + xmm31 + 0xFFFF]',
      '[rax + xmm0 * 2 + 0xFFFF2]', '[rax + xmm1 * 4 + 0xFFFF4]', '[rax + xmm15 * 8 + 0xFFFF8]', '[rsp + xmm31 * 8 + 0xFFFF8]', '[r15 + xmm18 * 8 + 0xFFFF8]', '[rsp + xmm12 * 8 + 0xFFFF8]', '[r14 + xmm5 * 8 + 0xFFFF8]'
    ]],
		['vm32y', [
      '[0x0]', '[0xFF]', '[0xFFFF]',
			'[rax]',
      '[rax + 0x0]', '[rax + 0xFFFF]', '[r15 + 0xFFFF]',
      '[rax + ymm0 * 1  + 0x0]', '[rax + ymm0 + 0xFFFF]', '[r15 + ymm15 + 0xFFFF]', '[rax + ymm31 + 0xFFFF]',
      '[rax + ymm0 * 2 + 0xFFFF2]', '[rax + ymm1 * 4 + 0xFFFF4]', '[rax + ymm15 * 8 + 0xFFFF8]', '[rsp + ymm31 * 8 + 0xFFFF8]', '[r15 + ymm18 * 8 + 0xFFFF8]', '[rsp + ymm12 * 8 + 0xFFFF8]', '[r14 + ymm5 * 8 + 0xFFFF8]'
    ]],
		['vm32z', [
      '[0x0]', '[0xFF]', '[0xFFFF]',
			'[rax]',
      '[rax + 0x0]', '[rax + 0xFFFF]', '[r15 + 0xFFFF]',
      '[rax + zmm0 * 1  + 0x0]', '[rax + zmm0 + 0xFFFF]', '[r15 + zmm15 + 0xFFFF]', '[rax + zmm31 + 0xFFFF]',
      '[rax + zmm0 * 2 + 0xFFFF2]', '[rax + zmm1 * 4 + 0xFFFF4]', '[rax + zmm15 * 8 + 0xFFFF8]', '[rsp + zmm31 * 8 + 0xFFFF8]', '[r15 + zmm18 * 8 + 0xFFFF8]', '[rsp + zmm12 * 8 + 0xFFFF8]', '[r14 + zmm5 * 8 + 0xFFFF8]'
    ]],
		['vm64z', [
      '[0x0]', '[0xFF]', '[0xFFFF]',
			'[rax]',
      '[rax + 0x0]', '[rax + 0xFFFF]', '[r15 + 0xFFFF]',
      '[rax + zmm0 * 1  + 0x0]', '[rax + zmm0 + 0xFFFF]', '[r15 + zmm15 + 0xFFFF]', '[rax + zmm31 + 0xFFFF]',
      '[rax + zmm0 * 2 + 0xFFFF2]', '[rax + zmm1 * 4 + 0xFFFF4]', '[rax + zmm15 * 8 + 0xFFFF8]', '[rsp + zmm31 * 8 + 0xFFFF8]', '[r15 + zmm18 * 8 + 0xFFFF8]', '[rsp + zmm12 * 8 + 0xFFFF8]', '[r14 + zmm5 * 8 + 0xFFFF8]'
    ]],
		['rel8', [ '0', '1', '-128', '127' ]],
		['rel16', [ '0', '1', '-128', '127' ]],
		['rel32', [ '0', '1', '-128', '127' ]],
		['moff8', ['[qword 0]', '[qword 0xFF]', '[qword 0xFFFF]', '[qword 0xFFFFFFFF]', '[qword 0xFFFFFFFFFFFFFFFF]']],
		['moff16', ['[qword 0]', '[qword 0xFF]', '[qword 0xFFFF]', '[qword 0xFFFFFFFF]', '[qword 0xFFFFFFFFFFFFFFFF]']],
		['moff32', ['[qword 0]', '[qword 0xFF]', '[qword 0xFFFF]', '[qword 0xFFFFFFFF]', '[qword 0xFFFFFFFFFFFFFFFF]']],
		['moff64', ['[qword 0]', '[qword 0xFF]', '[qword 0xFFFF]', '[qword 0xFFFFFFFF]', '[qword 0xFFFFFFFFFFFFFFFF]']],
	]);

	const broadcast_map = new Map([
		['b16:128', [ '[rax]{1to8}' ]],
		['b16:256', [ '[rax]{1to16}' ]],
		['b16:512', [ '[rax]{1to32}' ]],
		['b32:128', [ '[rax]{1to4}' ]],
		['b32:256', [ '[rax]{1to8}' ]],
		['b32:512', [ '[rax]{1to16}' ]],
		['b64:128', [ '[rax]{1to2}' ]],
		['b64:256', [ '[rax]{1to4}' ]],
		['b64:512', [ '[rax]{1to8}' ]],
	]);

	function generate(operands, index) {
		if(index === operands.length) {
			return [[]];
		}

		const current = operands[index];
		let current_array = [];

		if(!operand_map.has(current)) {
			if(current.includes('b')) {
				const key = `${current}:${inst.size}`;

				if(!broadcast_map.has(key)) {
					console.error(`unknown b operand '${key}'`);
				}
				else {
					current_array = broadcast_map.get(key);
				}
			}
			else {
				console.error(`unknown operand '${current}'`);
			}
		}
		else {
			if(current === 'xmm' && inst.enc.includes('EVEX')) {
				current_array = ['xmm0', 'xmm1', 'xmm2', 'xmm11', 'xmm15', 'xmm31'];	
			}
			else {
				current_array = operand_map.get(current);
			}
		}

		const remaining = generate(operands, index + 1);
		const combinations = [];

		for(const value of current_array) {
			for(const combination of remaining) {
				combinations.push([value, ...combination]);
			}
		}

		return combinations;
	}

	return generate(inst.operands, 0);
}

function format_time(ms) {
  let total_seconds = Math.floor(ms / 1000);
  let hours = Math.floor(total_seconds / 3600);
  let minutes = Math.floor((total_seconds % 3600) / 60);
  let seconds = total_seconds % 60;
  let formatted_time = '';

  if(hours > 0) {
      formatted_time += `${hours}h `;
  }

  if(minutes > 0 || hours > 0) {
      formatted_time += `${minutes}m `;
  }

  formatted_time += `${seconds}s`;
	return formatted_time.trim();
}

function main() {
	let start_time = Date.now()

	// handle inputs 
	if(process.argv.length != 5) {
		console.error(`expected 3 arguments but got ${process.argv.length - 2} arguments instead`);
		process.exit(1);
	}
	
	let instructions;
	let tests_set = new Set();
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
		if(inst.operands.includes('hidden')) {
			return;
		}

		let operand_combinations = generate_combinations(inst);

		operand_combinations.forEach(combination => {
			tests_set.add(`${inst.name} ${combination.join(', ')}`);
		});
	});

	tests_set.forEach(test => {
		tests.push(test);
	})

	// calculate the worker count
	const worker_path = path.join(__dirname, 'testgen_worker.js');
	const worker_count = Math.max(Math.min(Math.floor(tests.length / 100), os.cpus().length - 1), 1);
	const chunk_size = Math.ceil(tests.length / worker_count);

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
			let error_text = '';
			let test_text = '';

			result.forEach(res => {
				res.errors.forEach(err => {
					error_text += `${err}`; 
				});
			});

			result.forEach(res => {
				res.results.forEach(res => {
					 test_text += `${res}\n`; 
				});
			});

			utility.write_file(process.argv[3], test_text);

			if(error_text.length > 0) {
				const now = new Date();
				const timestamp = now.toISOString().replace(/:/g, '-').substring(0, 19).replace(/:/g, '-');
				const error_path = path.join(process.argv[4], `log_${timestamp}.txt`) 

				console.error(`encountered errors (see ${error_path} for more information)`);
				utility.write_file(error_path, error_text);
			}

			console.log(`testgen finished (${format_time(Date.now() - start_time)})`);

			process.exit(0);
		})
		.catch(error => {
			console.error(error);
			process.exit(1);
		});

	return 0;
}

main();

