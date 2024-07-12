// regenerates the contents of the main instruction database located in ./utility.js

"use strict"

const database = require("./database.js");
const utility = require("./utility.js")

let json_table = [];

database.instructions.forEach(inst => {
    json_table.push([
        `"name": "${inst.name}"`,
        `"ext": []`,
        `"operands": [${inst.operands.map(op => { return `"${op}"`; }).join(", ")}]`,
        `"opcode": "${inst.opcode}"`,
        `"rm": "${inst.rm}"`,
        `"w": ${inst.w}`,
        `"ri": ${inst.ri}`,
        `"pp": "${inst.pp}"`,
        `"dir": "${inst.dir}"`,
        `"enc": "${inst.enc}"`,
        `"ops": ${inst.ops}`,
        `"imp": "${inst.imp}"`,
        `"ilo": "${inst.ilo}"`,
        `"var": ${inst.var}`,
    ])
})

json_table.sort();

// calculate the new table alignment
const json_layout = utility.calculate_layout(json_table);
const json_text = utility.apply_layout(json_layout, json_table, "    { ", " },");

console.log(`[\n${json_text.substring(0, json_text.length - 2)}\n]`)
