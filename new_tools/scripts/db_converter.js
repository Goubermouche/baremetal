const utility = require("./utility.js")
const fs = require('fs');

function escape_exp(string) {
  return string.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
}

function remove_str(target, strings_to_remove) {
  for(let str of strings_to_remove) {
    let regex = new RegExp(str, 'g');
    target = target.replace(regex, '');
  }

  return target;
}

function is_hex(str) {
  return Boolean(str.match(/^[0-9a-fA-F]+$/i))
}

function generate_combinations(arr) {
  function combine(prefix, elements) {
    if (elements.length === 0) {
      result.push(prefix);
      return;
    }

    const [first, ...rest] = elements;
    const parts = first.split(/\/|\|/);

    parts.forEach(part => {
      combine(prefix.concat(part), rest);
    });
  }

  const result = [];
  combine([], arr);
  return result;
}


function replace_all(input, rules) {
	for(let rule of rules) {
		if(rule.s === input) {
			return rule.r;
		}
	}

  return input;
}

function extract_inst_operands(inst) {
	const rm = [
		'x:', 'r:', 'w:', 'R:', 'X:', 'W:', '~', '[127:16]', '[31:0]', '[15:0]', ',',
		'[127:64]', '[127:32]', '[63:0]', '[7:0]', '[ilock|xacqrel]', '[bnd|repIgnore]', '[18:0]', '[3:0]', '[1:0]',
		'[ilock|xacquire]', '[lock|xacqrel]', '[rep|repne]', '[lock]', '[bnd]', '[xrelease]',
		'[rep]', '{er}', '{sae}'
	].map(r => escape_exp(r));

	const replacements = [
    { s: 'ib/ub', r: 'i8' },
    { s: 'iw/uw', r: 'i16' },
    { s: 'id/ud', r: 'i32' },
    { s: 'iq/uq', r: 'i64' },
    { s: 'ib', r: 'i8' },
    { s: 'iw', r: 'i16' },
    { s: 'id', r: 'i32' },
    { s: 'iq', r: 'i64' },
		{ s: 'ub', r: 'i8' },
    { s: 'uw', r: 'i16' },
    { s: 'ud', r: 'i32' },
    { s: 'uq', r: 'i64' },
    { s: 'mm', r: 'mmx' },
    { s: 'mm/m64', r: 'mmx/m64' },
    { s: 'st(0)', r: 'st0' },
    { s: 'st(i)', r: 'st' },
	];

	const masks = ['{kz}', '{k}'];

	let parts = inst.split(/[\s,]+/)
		.map(p => remove_str(p, rm))
		.filter(p => p !== '')
		.map(p => replace_all(p, replacements))
		.filter(p => !(/^<.*>$/.test(p)))
		.filter(p => p.includes("st") || !(/^[^\(]+\([^\)]+\)$/.test(p)))

	let result = [];

	for(let i = 0; i < parts.length; ++i) {
		let current = parts[i];

		masks.some(mask => {
		  if(current.startsWith(mask)) {
		    current = current.slice(mask.length);
				result[result.length - 1] += '_' + mask.slice(1, -1);

		    return true; 		
			}

			return false;
		});

		if(current.length !== 0) {
			result.push(current)
		}
	}

	return result;
}

function extract_encoding(enc) {
	let parts = enc.split(' ');
	let met_opcode = false;
	let is_special = false;

	let result = {
		opcode: [],
		prefix: [],
		rexw: false,
		enc: undefined, // encoding id
		rm: undefined, // /r or /1 /2 /3 ...
		opcode_extend: undefined, // opcode + i or r
		size: undefined, 
	};

	for(let i = 0; i < parts.length; ++i) {
		let part = parts[i];

		// prefixes
		if(is_special === false && met_opcode === false && ['F0', 'F2', 'F3', '2E', '36', '3E', '26' ,'64' ,'65' ,'2E', '3E', '66', '67'].some(p => p === part)) {
			result.prefix.push(part);
		}
		else if(is_hex(part)) {
			met_opcode = true;
			result.opcode.push(part);
		}
		else if(part === 'REX.W') {
			result.rexw = true;
		}
		else if(part.endsWith(':')) {
			result.enc = part.slice(0, -1).replace('-', '_');
		}
		else if(part.startsWith('/')) {
			result.rm = part.slice(1);
		}
		else if(part.includes('+')) {
			let pp = part.split('+');

			result.opcode.push(pp[0]);
			result.opcode_extend = pp[1];
		}
		else if(['ib', 'iw', 'id', 'iq', 'cw', 'moff'].some(i => i == part)) {}
		else if(part.startsWith('VEX')) {
			let pp = part.split('.');
			is_special = true;

			for(let p of pp) {
				if(p === 'VEX') {
					result.enc = ['VEX', result.enc].filter(e => { return e !== undefined; }).join('_');
				}
				else if(p === 'W1') {
					result.rexw = true;
				}
				else if(p === 'W0') {
					result.rexw = false;
				}
				else if(p === '128') {
					result.size = 128;
				}
				else if(p === '256') {
					result.size = 256;
				}
				else if(['0F38', '0F', '0F3A'].some(i => i == p)) {
					result.opcode.push(p);
				}
				else if(['66', 'F3', 'F2'].some(i => i == p)) {
					result.prefix.push(p);
				}				
				else if(p === 'WIG') {}
				else if(p === 'LIG') {}				
				else if(p === 'LZ') {}
				else if(p === 'L0') {}
				else if(p === 'L1') {}
				else if(p === 'NP') {}
				else {
					console.log(p);
				}
			}
		}
		else if(part.startsWith('EVEX')) {
			let pp = part.split('.');
			is_special = true;

			for(let p of pp) {
				if(p === 'EVEX') {
					result.enc = ['EVEX', result.enc].filter(e => { return e !== undefined; }).join('_');
				}
				else if(p === 'W1') {
					result.rexw = true;
				}
				else if(p === 'W0') {
					result.rexw = false;
				}
				else if(p === 'NP') {}					
				else if(p === 'LIG') {}					
				else if(p === 'WIG') {}
				else if(p === 'MAP5') {}
				else if(p === 'MAP6') {}
				else if(['0F38', '0F', '0F3A'].some(i => i == p)) {
					result.opcode.push(p);
				}
				else if(['66', 'F3', 'F2'].some(i => i == p)) {
					result.prefix.push(p);
				}				
				else if(p === '128') {
					result.size = 128;
				}
				else if(p === '256') {
					result.size = 256;
				}
				else if(p === '512') {
					result.size = 512;
				}
				else {
					console.log(p);
				}
			}
		}
		else if(part.startsWith('XOP')) {
			let pp = part.split('.');
			is_special = true;

			for(let p of pp) {
				if(p === 'XOP') {
					result.enc = ['XOP', result.enc].filter(e => { return e !== undefined; }).join('_');
				}
				else if(p === 'L0') {}
				else if(p === 'L1') {}
				else if(p === 'P0') {}
				else if(p === 'M09') {}
				else if(p === 'M08') {}
				else if(p === 'M0A') {}
				else if(p === 'LZ') {}
				else if(p === 'W1') {
					result.rexw = true;
				}
				else if(p === 'W0') {
					result.rexw = false;
				}
				else {
					console.log(p);
				}
			}
		}
		else {
			console.log(part)
		}
	}

	if(result.enc === undefined) {
		result.enc = 'NORMAL';
	}

	return result;
}

function main() {
	if(process.argv.length != 3) {
		console.error(`expected 1 argument but got ${process.argv.length - 2} arguments instead`);
		return 1;
	}

	let db;
	
	try {
	  const data = fs.readFileSync(process.argv[2], 'utf8');
	  db = JSON.parse(data);
	} catch (err) {
	  console.error('error reading source database', err);
	}
	
	let instructions = [];
	
	db.instructions.forEach(group => {
		if(group.deprecated) {
			return; // skip deprecated groups
		}

		group.data.forEach(inst => {
			const operands = extract_inst_operands(inst.inst);
			const combinations = generate_combinations(operands);
	
			combinations.forEach(comb => {
				let variant = {
					name: comb[0],
					operands: comb.slice(1),
					enc: extract_encoding(inst.op),
					extension: [],
					category: group.category.split(' ')
				};

				if(group.ext) { variant.extension.push(group.ext); }
				if(inst.ext) { variant.extension.push(inst.ext); }
				if(group.arch) { variant.extension.push(group.arch); }
				if(inst.arch) { variant.extension.push(inst.arch); }
	
				instructions.push(variant);
			});
		});
	})

	gp_inst = [];

	// VIRTUALIZATION
	const supported_categories = [
		'GP', 'GP_IN_OUT', 'GP_EXT', 'CRYPTO_HASH', 'VIRTUALIZATION', 'FPU', 'SSE', 'STATE'
	];
	
	const supported_extensions = [
		'RM',
		'MR', 
		'M', 
		'NORMAL',
		'R',
		'VEX', 
		'VEX_VM',
		'VEX_RM',
		'VEX_RVM',
		'VEX_RMV',
		'VEX_MVR',
		'XOP',
		'XOP_VM',
		'EVEX_RVM',
		'VEX_RVMN'
	];

	// missing categories: 
	// - 
	// - SIMD
	// - AVX
	// - AVX512
	// - MASK
	// - AMX
	
	// VEX_MR
	// VEX_MVR
	// EVEX_RVM
	// EVEX_RM
	// EVEX_MR
	// EVEX_MVR

	instructions.forEach(inst => {
		// test all categories
		// if(
		// 	inst.category.some(r => supported_categories.includes(r)) && 
		// 	!inst.extension.includes('X86')
		// ) {
		// 	gp_inst.push(inst);
		// }

		// test specific categories
		if(
			inst.category.includes('SCALAR') &&
			!inst.extension.includes('X86') && 
			inst.enc.enc == 'VEX_MR'
		) {
			gp_inst.push(inst);
		}
	});

	let rows = [];
	
	gp_inst.forEach(inst => {
		let row = [];
	
		row.push(`"name": "${inst.name}"`);
		row.push(`"operands": [${inst.operands.map(op => `"${op}"`).join(", ")}]`);
		row.push(`"enc": "${inst.enc.enc}"`);
		row.push(`"opcode": "${inst.enc.opcode.join('')}"`);
		row.push(`"prefix": [${inst.enc.prefix.map(p => `"${p}"`).join(", ")}]`);
		row.push(`"rexw": ${inst.enc.rexw}`);
		row.push(`"rm": "${inst.enc.rm === undefined ? "" : inst.enc.rm}"`);
		row.push(`"ri": "${inst.enc.opcode_extend === undefined ? "" : inst.enc.opcode_extend}"`);
		row.push(`"size": ${inst.enc.size === undefined ? "64" : inst.enc.size}`);
		
		rows.push(row);
	});

	const db_layout = utility.calculate_layout(rows);
	const db_text = utility.apply_layout(db_layout, rows, '\t{ ', ' },');

	console.log(`[\n${db_text.slice(0, -2)}\n]\n`);

	return 0;
}

process.exit(main());

