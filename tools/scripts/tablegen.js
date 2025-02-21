// generates a table for the instruction database

// expected arguments: {source_database.json}
const utility = require("./utility.js")
const fs = require('fs');

const constant_base = 16; // base for constants, such as flags, this can decrease the overall size of the generated file.

function get_base_prefix() {
	switch(constant_base) {
		case 2: return '0b';
		case 16: return '0x';
		default: console.error(`unknown constant base '${p}'`);
	}
}

function get_operand_order(value) {
	// operand doesn't exist
	if(value === undefined) {
		return 0;
	}

	const operand_order = [
		'1', 'i8', 'i16', 'i32', 'i64',
		'al', 'cl', 'r8', 
		'ax', 'dx', 'r16',
		'eax', 'ecx','r32',
		'rax', 'r64',
		'bnd', 'creg', 'dreg',
		'st', 'st0',
		'es', 'cs', 'ss', 'ds', 'fs', 'gs', 'sreg', 
		'xmm', 'xmm_kz', 'xmm_k',
		'ymm', 'ymm_kz', 'ymm_k',
		'zmm', 'zmm_kz', 'zmm_k',
		'mmx',
		'b16', 'b32', 'b64',
		'k', 'k_k', 'k+1',
		'moff8', 'moff16', 'moff32', 'moff64',
		'm8', 'm16', 'm32', 'm64', 'm80', 'm128', 'm256', 'm512',
		'vm32x_k',
		'vm32y_k',
		'vm32z_k',
		'vm64x_k',
		'vm64y_k',
		'vm64z_k',
		'vm64x',
		'vm64y',
		'm32_k',
		'm16_k',
		'm16_kz',
		'm32_kz',
		'm64_kz', 'm64_k',
		'm128_k', 
		'm256_k',
		'm512_k',
		'mem',
		'rel8', 'rel16', 'rel32',
		'rel8_rip', 'rel16_rip', 'rel32_rip',
		'm16_16', 'm16_32', 'm16_64'
	];

	const index = operand_order.indexOf(value);

	if(index === -1) {
		console.error(`unknown operand '${value}'`);
	}

	return index === -1 ? operand_order.length : index;
}

function get_instruction_prefix(prefix_arr) {
	// converts the prefix hexcodes into a bitboard as defined in instruction.h
	let prefix = 0;

	prefix_arr.forEach(p => {
		switch(p) {
			// IGNORE: this doesn't seem to be an issue :chad:
			// TODO: branch not taken/taken aren't reachable right now, for more, see: 
			// https://community.intel.com/t5/Software-Archive/Developer-s-manual-0x66-0xF2-instruction-prefixes/td-p/947293?profile.language=pt&countrylabel=Chile

			// group 4
			case '67': prefix |= 0b10000000; break;
			// group 3
			case '66': prefix |= 0b01000000; break;
			// group 2
			case '2E': prefix |= 0b00000100; break;
			case '36': prefix |= 0b00001000; break;
			case '3E': prefix |= 0b00001100; break;
			case '26': prefix |= 0b00010000; break;
			case '64': prefix |= 0b00010100; break;
			case '65': prefix |= 0b00011000; break;
			case '2E': prefix |= 0b00011100; break;
			case '3E': prefix |= 0b00100000; break;
			// group 1
			case 'F0': prefix |= 0b00000001; break;
			case 'F2': prefix |= 0b00000010; break;
			case 'F3': prefix |= 0b00000011; break;
			default: console.error(`unknown instruction prefix '${p}'`);
		}
	});

	return prefix.toString(constant_base);
}

function get_instruction_flags(inst) {
	// compress various flags into a single bitboard
	let flags = 0;

	if(inst.rexw) {
		flags |= 0b00000001;
	}

	switch(inst.rm) {
		//                 _____XXXX_
		case '0':   flags |= 0b00000010; break;
		case '1':   flags |= 0b00000100; break;
		case '2':   flags |= 0b00000110; break;
		case '3':   flags |= 0b00001000; break;
		case '4':   flags |= 0b00001010; break;
		case '5':   flags |= 0b00001100; break;
		case '6':   flags |= 0b00001110; break;
		case '7':   flags |= 0b00010000; break;
		case 'is4': flags |= 0b00010010; break;
		case 'r':   flags |= 0b00010100; break;
		case '':                         break;
		default: console.error(`unknown instruction rm '${inst.rm}'`);
	}

	switch(inst.ri) {
		case '': break;
		case 'i':
		case 'r': flags |= 0b00100000; break;
		default: console.error(`unknown instruction ri '${inst.ri}'`);
	}

	if(inst.l != '') {
		// MAP is only available on EVEX instructions while L1 / L0 is only available on VEX/XOP instructions
		switch(inst.l) {
			case '1': flags |= 0b01000000; break;
			case '0': flags |= 0b10000000; break;
			default: console.error(`unknown instruction l '${inst.ri}'`);
		}
	}
	else {
		switch(inst.map) {
			case '': break;
			case '5': flags |= 0b10000000; break;
			case '6': flags |= 0b01000000; break;
			default: console.error(`unknown instruction map '${inst.ri}'`);
		}
	}

	return flags.toString(constant_base);
}

function encode_special(id, index) {
	if(id < 0 || id > 3 || index < 0 || index > 16384) {
		throw new Error('invalid id or index');
	}

	return (id << 14) | index;
}

function is_immediate(op) {
	switch(op) {
		case 'i8':
		case 'i16':
		case 'i32':
		case 'i64': return true;
		default:    return false;
	}
}

function calculate_magic(inst, dest_to_source) {
	if(inst.name === 'mov' && inst.operands[0] === 'r64' && inst.operands[1] === 'i32') {
		// 0
		return encode_special(0, dest_to_source.get(`${inst.name}:r32:i32`))
	}
	
	if(['rcl', 'rcr', 'rol', 'ror', 'sal', 'sar', 'shl', 'shr'].includes(inst.name) && inst.operands[1] !== '1') {
		// 1
		return encode_special(1, dest_to_source.get(`${inst.name}:${inst.operands[0]}:1`));
	}
	
	if(inst.name === 'imul' && inst.operands.length === 3 && is_immediate(inst.operands[2])) {
		// 2
		const key = `${inst.name}:${inst.operands[0]}:${inst.operands[1]}:i8`;

		if(dest_to_source.has(key) && inst.operands[2] !== 'i8') {
			return encode_special(2, dest_to_source.get(key));
		}
	}

	return 65535; // u16 max - no special index
}

function main() {
	// handle inputs
	if(process.argv.length != 3) {
		console.error(`expected 1 argument but got ${process.argv.length - 2} arguments instead`);
		return 1;
	}
	
	let instruction_table = [];
	let instructions;
	
	try {
	  const data = fs.readFileSync(process.argv[2], 'utf8');
	  instructions = JSON.parse(data);
	} catch (err) {
	  console.error('error reading source database: ', err);
		process.exit(1);
	}
	
	// sort instructions
	instructions.sort((a, b) => {
		const a_is_evex=a.enc.includes('EVEX');
		const b_is_evex=b.enc.includes('EVEX');

		if(a.name<b.name) { return -1; }
		if(a.name>b.name) { return 1; }

		if(a_is_evex===b_is_evex) {
			const order_a_1=get_operand_order(a.operands[0]);
			const order_b_1=get_operand_order(b.operands[0]);

			if(order_a_1<order_b_1) { return -1; }
			if(order_a_1>order_b_1) { return 1; }

			const order_a_2=get_operand_order(a.operands[1]);
			const order_b_2=get_operand_order(b.operands[1]);

			if(order_a_2<order_b_2) { return -1; }
			if(order_a_2>order_b_2) { return 1; }

			return 0;
		}

		// EVEX instructions should be placed as the last ones in their mnemonic group,
		// since we want to skip EVEX variants of VEX instructions (for cases where the
		// magic index gets involved). Additionally, EVEX instructions will probably 
		// get used much less often, hence this works as an optimization, but this is 
		// just a bonus.
		return a_is_evex ? 1 : -1;
	});

	// instruction lookup
	let dest_to_source = new Map();
	let lookup = new Map();

	instructions.forEach((inst, i) => {
		dest_to_source.set(`${inst.name}:${inst.operands.join(":")}`, i);
		lookup.set(`${inst.name}:${inst.encoding}:${inst.operands.join(":")}`, i);
	});

	// generate the table
	instructions.forEach(inst => {
		let special_index = calculate_magic(inst, dest_to_source, lookup);
		let row = [];

		row.push(`"${inst.name}"`);			                                          // name
		row.push(`ENC_${inst.enc}`);    	                                        // encoding
		row.push(`${get_base_prefix()}${get_instruction_prefix(inst.prefix)}`);	  // prefix
		row.push(`0x${inst.opcode}`);                                             // opcode
		row.push(`${get_base_prefix()}${get_instruction_flags(inst)}`);	          // flags
		row.push(`${get_base_prefix()}${special_index.toString(constant_base)}`); // special index
		row.push(`OPS_${inst.size}`); // instruction size

		// operands
		inst.operands.map(op => op === '1' ? 'hidden' : op).forEach(op => {
			row.push(`OP_${op.toUpperCase()}`);	
		});

		instruction_table.push(row);
	});

	// format the table
	const instruction_table_layout = utility.calculate_layout(instruction_table);
	const instruction_table_text = utility.apply_layout(instruction_table_layout, instruction_table, 'inst(', '),');

	console.log(instruction_table_text);

	return 0;
}

process.exit(main());

