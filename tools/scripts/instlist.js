// list all unique used instruction names
const utility = require("./utility.js")

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

	let names = new Set();

	db.forEach(inst => {
		names.add(inst.name);
	})

	let names_arr = [...names].sort();

	// print the final array
	names_arr.forEach(name => {
		console.log(name);
	})

	return 0;
}

process.exit(main());

