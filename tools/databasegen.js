// regenerates the contents of the main instruction database located in ./utility.js

"use strict"

const database = require("./database.js");
const utility = require("./utility.js")

let json_table = [];

database.instructions.forEach(inst => {
	json_table.push([
		`"name": "${inst.name}"`,
		`"operands": [${inst.operands.map(op => { return `"${op}"`; }).join(", ")}]`,
		`"enc": [${inst.enc.map(e => { return `"${e}"`; }).join(", ")}]`,
		`"opcode": "${inst.opcode}"`,
		`"rm": "${inst.rm}"`,
		`"w": ${inst.w}`,
		`"ri": ${inst.ri}`,
		`"pp": "${inst.pp}"`,
		`"dir": "${inst.dir}"`,
		`"ops": ${inst.ops}`,
		`"imp": "${inst.imp}"`,
		`"ilo": "${inst.ilo}"`,
		`"var": ${inst.var}`,
		`"ext": [${inst.ext.map(op => { return `"${op}"`; }).join(", ")}]`,
	])
})

json_table.sort((a, b) => {
	return a.name < b.name;
});

// calculate the new table alignment
const json_layout = utility.calculate_layout(json_table);
const json_text = utility.apply_layout(json_layout, json_table, "    { ", " },");

console.log(`[\n${json_text.substring(0, json_text.length - 2)}\n]`)
