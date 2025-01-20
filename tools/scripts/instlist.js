// list all unique used instruction names
const { info } = require("console");
const utility = require("./utility.js")

function format_encoding(enc) {
	return enc === 'NORMAL' ? '' : enc;
}

function format_opcode(opcode) {
	return opcode.replace(/(..)/g, '$1 ').trim();
}

function main() {
	if(process.argv.length != 3) {
		console.error(`expected 1 argument but got ${process.argv.length - 2} arguments instead`);
		return 1;
	}

	let db;
	
	try {
	  const data = utility.read_file(process.argv[2]);
	  db = JSON.parse(data);
	} catch (err) {
	  console.error('error reading source database', err);
	}

	let variants = new Map();
	let names = new Set();
	let names_total = 0;

	db.forEach(inst => {
		names.add(inst.name);

		const key = `${inst.name}:${inst.operands.length}:${inst.enc}:${inst.opcode}:${inst.prefix}:${inst.rexw}:${inst.rm}:${inst.ri}:${inst.size}:${inst.map}:${inst.l}`;

		if(variants.has(key)) {
			variants.get(key).variants.push(inst.operands);
		}
		else {
			const variant = {
				variants: [inst.operands],
				name: inst.name,
				enc: inst.enc,
				opcode: inst.opcode,
				prefix: inst.prefix,
				rexw: inst.rexw,
				rm: inst.rm,
				ri: inst.ri,
				size: inst.size, 
				map: inst.map,
				l: inst.l
			};

			variants.set(key, variant);
		}

		names_total++;
	})

	console.log(`${names_total} total instruction variants`);
	console.log(`${names.size} instruction instances`);

	variants.forEach((value) => {
		if(value.variants.length == 0 || value.variants[0].length == 0 || value.name !== "mov") {
			return;
		}

		let operand_variants = [];

		for(let i = 0; i < value.variants[0].length; i++) {
			operand_variants.push(new Set());
		}

		value.variants.forEach((variant) => {
			variant.forEach((operand, i) => {
				operand_variants[i].add(operand);
			});
		});

		const operands = operand_variants.map(set => Array.from(set).join('/')).join(', ');
		let opcode = [];

		if(value.rexw) {
			opcode.push('REX.W +')
		}

		opcode.push(format_opcode(value.opcode));

		if(value.ri !== '') {
			opcode.push(`+ ${value.ri}`);
		}

		if(value.rm !== '') {
			opcode.push(`/${value.rm}`);
		}

		console.log(`${opcode.join(' ').padEnd(20, ' ')} ${value.name.padEnd(5, ' ')} ${operands.padEnd(20, ' ')} ${format_encoding(value.enc)}`);
	});

	return 0;
}

process.exit(main());

