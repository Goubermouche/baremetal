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
	const rm = ['x:', 'r:', 'w:', 'R:', 'X:', 'W:', '~', '[127:16]', '[31:0]', '[15:0]', ',', '[127:64]', '[127:32]', '[63:0]', '[7:0]', '[ilock|xacqrel]', '[bnd|repIgnore]', '[ilock|xacquire]', '[lock|xacqrel]', '[rep|repne]', '[lock]', '[bnd]', '[xrelease]', '[rep]'].map(r => escape_exp(r));
	const masks = ['{kz}', '{k}'];
	const replacements = [
    { s: 'ib/ub', r: 'i8' },
    { s: 'iw/uw', r: 'i16' },
    { s: 'iw/ud', r: 'i32' },
    { s: 'iq/uq', r: 'i64' },
    { s: 'ib', r: 'i8' },
    { s: 'iw', r: 'i16' },
    { s: 'id', r: 'i32' },
    { s: 'iq', r: 'i64' },
		{ s: 'ub', r: 'i8' },
    { s: 'uw', r: 'i16' },
    { s: 'ud', r: 'i32' },
    { s: 'uq', r: 'i64' },
	];

	let parts = inst.split(/[\s,]+/).map(p => remove_str(p, rm)).filter(p => p !== '').map(p => replace_all(p, replacements)).filter(p => !(/^<.*>$/.test(p))).filter(p => !(/^[^\(]+\([^\)]+\)$/.test(p)));
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

	let result = {
		opcode: [],
		prefix: [],
		rexw: false,
		enc: undefined, // encoding id
		rm: undefined, // /r or /1 /2 /3 ...
		opcode_extend: undefined, // opcode + i or r
		ilo: undefined, 
		imp: undefined,
		size: undefined, 
	};

	for(let i = 0; i < parts.length; ++i) {
		let part = parts[i];

		// prefixes
		if(met_opcode === false && ['F0', 'F2', 'F3', '2E', '36', '3E', '26' ,'64' ,'65' ,'2E', '3E', '66', '67'].some(p => p === part)) {
			result.prefix.push(part)
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

			for(let p of pp) {
				if(p === 'VEX') {
					result.enc = 'VEX_' + result.enc ? result.enc : '';
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
					result.ilo = p;
				}
				else if(['66', 'F3', 'F2'].some(i => i == p)) {
					result.imp = p;
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

			for(let p of pp) {
				if(p === 'EVEX') {
					result.enc = 'EVEX_' + result.enc ? result.enc : '';
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
					result.ilo = p;
				}
				else if(['66', 'F3', 'F2'].some(i => i == p)) {
					result.imp = p;
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

			for(let p of pp) {
				if(p === 'XOP') {
					result.enc = 'XOP_' + result.enc ? result.enc : '';
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

if(process.argv.length != 3) {
	console.error(`expected 1 argument but got ${process.argv.length - 2} arguments instead`);
	process.exit(1);
}

let db;

try {
  const data = fs.readFileSync(process.argv[2], 'utf8');
  db = JSON.parse(data);
} catch (err) {
  console.error('Error reading the file:', err);
}

let instructions = [];

db.instructions.forEach(group => {
	group.data.forEach(inst => {
		const combinations = generate_combinations(extract_inst_operands(inst.inst));

		let variant = {
			name: combinations[0][0],
			operands: [],
			enc: extract_encoding(inst.op),
			extension: [],
			category: group.category
		};

		combinations.forEach(comb => {
			variant.extension = [];

			if(group.ext) {
				variant.extension.push(group.ext);
			}

			if(inst.ext) {
				variant.extension.push(inst.ext);
			}

			if(group.arch) {
				variant.extension.push(group.arch);
			}

			if(inst.arch) {
				variant.extension.push(inst.arch);
			}
	
			variant.operands = comb.slice(1);
			instructions.push(variant);
		});
	});
});

gp_inst = [];

instructions.forEach(inst => {
	if(inst.category.includes('GP')) {
		gp_inst.push(inst);
	}
});


let rows = [];

gp_inst.forEach(inst => {
	let row = [];

	row.push(`"name": "${inst.name}"`);
	row.push(`"operands": [${inst.operands.map(op => `"${op}"`).join(", ")}]`);
	row.push(`"enc": "${inst.enc.enc}"`);
	row.push(`"opcode": "${inst.enc.opcode.join('').padStart(6, '0')}"`);
	row.push(`"prefix": [${inst.enc.prefix.map(p => `"${p}"`).join(", ")}]`);
	row.push(`"rexw": ${inst.enc.rexw}`);
	row.push(`"rm": "${inst.enc.rm === undefined ? "" : inst.enc.rm}"`);
	row.push(`"ri": "${inst.enc.opcode_extend === undefined ? "" : inst.enc.opcode_extend}"`);

	rows.push(`\t{ ${row.join(', ')} }`);
});


console.log(`[\n${rows.join(',\n')}\n]\n`);