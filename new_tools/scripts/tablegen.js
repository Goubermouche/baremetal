// generates a table for the instruction database

// expected arguments: {source_database.json}
const utility = require("./utility.js")
const fs = require('fs');

function get_operand_order(value) {
	// const operand_order = [
	// 	"1", "i8", "i16", "i32", "i64",
	// 	"al", "cl", "reg8",
	// 	"ax", "dx",  "cx","reg16",
	// 	"eax", "ecx", "reg32", 
	// 	"rax", "rcx", "reg64",
	// 	"xmm", "xmm_kz", "mem128", 
	// 	"ymm", "ymm_kz", "mem256",
	// 	"zmm", "zmm_kz",
	// 	"bnd", "mmx", "sreg", "dreg", "creg",
	// 	"moff8", "moff16", "moff32", "moff64",
	// 	"mem8", "mem16", "mem32", "mem64", "mem128",
	// 	"mem_address", "rel8", "rel32"
	// ];

	// operand doesn't exist
	if(value === undefined) {
		return 0;
	}

	const operand_order = [
		'm32', 'r64', 'r32', 'mem', 'bnd', 'i8', 'm16', 'cl', 'm8', 'm64', 'r16', '1', 'rel32', 'rel16', 'dx',
		'al', 'eax', 'ax', 'm512', 'r8', 'ud', 'i16', 'i32', 'rax', 'sreg', 'creg', 'dreg', 'gs', 'es', 'fs', 'ds',
		'ss', 'cs', 'moff64', 'moff8', 'i64', 'moff16', 'moff32', 'rel8', 'm16_16', 'm16_32', 'm16_64'
	];

	const index = operand_order.indexOf(value);

	if(index === -1) {
		console.error(`unknown operand '${value}'`);
	}

	return index === -1 ? operand_order.length : index;
}

// TODO: to compress our encoding we should use hex instead of bin forms

function get_instruction_prefix(prefix_arr) {
	// converts the prefix hexcodes into a bitboard as defined in instruction.h
	let prefix = 0;

	prefix_arr.forEach(p => {
		switch(p) {
			// TODO: branch not take/taken aren't reachable right now, for more, see: 
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

	return prefix.toString(2).padStart(8, '0');
}

function get_instruction_flags(inst) {
	// compress various flags into a single bitboard
	let flags = 0;

	if(inst.rexw) {
		flags |= 0b00000001;
	}

	switch(inst.rm) {
		case '':  break;
		case 'r': flags |= 0b00000010; break;
		case '0': flags |= 0b00000100; break;
		case '1': flags |= 0b00000110; break;
		case '2': flags |= 0b00001000; break;
		case '3': flags |= 0b00001010; break;
		case '4': flags |= 0b00001100; break;
		case '5': flags |= 0b00001110; break;
		case '6': flags |= 0b00010000; break;
		case '7': flags |= 0b00010010; break;
		default: console.error(`unknown instruction rm '${inst.rm}'`);
	}

	switch(inst.ri) {
		case '': break;
		case 'r': flags |= 0b00100000; break;
		case 'i': flags |= 0b01000000; break;
		default: console.error(`unknown instruction ri '${inst.ri}'`);
	}

	return flags.toString(2).padStart(8, '0');
}

function main() {
	// handle inputs
	if(process.argv.length != 3) {
		console.error(`expected 1 argument but got ${process.argv.length - 2} arguments instead`);
		return 1;
	}
	
	const source = process.argv[2];
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
	  if(a.name < b.name) return -1;
	  if(a.name > b.name) return 1;
	
	  const order_a = get_operand_order(a.operands[0]);
	  const order_b = get_operand_order(b.operands[0]);
	  
	  if(order_a < order_b) return -1;
	  if(order_a > order_b) return 1;
	  
	  const order_c = get_operand_order(a.operands[1]);
	  const order_d = get_operand_order(b.operands[1]);
	  
	  if(order_c < order_d) return -1;
	  if(order_c > order_d) return 1;
	  
	  return 0;
	});

	instructions.forEach(inst => {
		let row = [];

		row.push(`"${inst.name}"`);			                      // name
		row.push(`ENCN_${inst.enc}`);    	                    // encoding
		row.push(`0b${get_instruction_prefix(inst.prefix)}`);	// prefix
		row.push(`0x${inst.opcode}`);	                        // opcode
		row.push(`0b${get_instruction_flags(inst)}`);	        // flags

		// operands
		inst.operands.forEach(op => {
			row.push(`OPN_${op.toUpperCase()}`);	
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

