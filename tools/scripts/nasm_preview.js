const utility = require("./utility.js");

function main() {
	// handle inputs 
	if(process.argv.length != 3 && process.argv.length != 4) {
		console.error(`expected 1 or 2 arguments but got ${process.argv.length - 2} arguments instead`);
		process.exit(1);
	}

	const asm_path = process.argv[2];
	const temp_path = 'tmp.txt';
	const bin_path = 'tmp.bin';
	const out_path = 'out.txt';

  const nasm_command = `nasm -w+all -f bin -o ${bin_path} ${asm_path} > ${temp_path} 2>&1`;
  let hexdump_command = `xxd -g 999999 ${bin_path} > ${out_path}`;

	if(process.argv.length === 4) {
		switch(process.argv[3]) {
			case '-p':
			case '--plain': hexdump_command = `xxd -p ${bin_path} > ${out_path}`; break;
			case '-n':
			case '--normal': break;
			default: {
				console.log('usage: nasm_preview.sh { filepath } ( mode )')
				console.log('       filepath: mandatory path of the file to assemble')
				console.log('       mode    : optional mode specifier (--plain/-p or --normal/-n)')
				return 1;
			} 
		}	
	}

	try {
		utility.execute(nasm_command);
		utility.execute(hexdump_command);
		console.log(utility.read_file(out_path));
	} catch(error) {
		console.error(utility.read_file(temp_path));
	} finally {
		// cleanup
		try {
			utility.delete_file(temp_path);
  		utility.delete_file(bin_path);
  		utility.delete_file(out_path);
		} catch(err) {}
	}

	return 0;
}

process.exit(main());

