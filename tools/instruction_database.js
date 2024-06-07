// generates the contents of instruction_database.inc
"use strict"
const utility = require("./utility.js")

// calculate the layout of our instruction table
function calculateLayout(instructions) {
    let layout = {
        index: instructions.length.toString().length,
        name: 0,
        opcode: 6,
        extensions: 0,
        prefix: 0,
        operand: [],
        totalOperand: 0
    };

    instructions.forEach(inst => {
        const extensions = utility.extractExtensions(inst);
        const prefix = utility.extractPrefix(inst);

        layout.name = Math.max(layout.name, inst.name.length);
        layout.extensions = Math.max(layout.extensions, extensions.length);
        layout.prefix = Math.max(layout.prefix, prefix.length);

        inst.operands.forEach((op, i) => {
            layout.operand[i] = Math.max(layout.operand[i] || 0, Math.max(op.length, 5));
        });

        const formattedOperands = inst.operands.map((op, i) => op.padEnd(layout.operand[i])).join(", ");
        layout.totalOperand = Math.max(layout.totalOperand, formattedOperands.length);
    });

    return layout;
}

// create (print) the instruction table using the provided layout
function createTable(instructions, layout) {
    function createHeader(layout) {
        function createSeparator() {
            const operandsSeparator = layout.operand.map(op => `+${"-".repeat(op + 1)}`).join("");

            console.log(
                "//" + " ".repeat(layout.index + 3) +
                `+${"-".repeat(layout.name + 1)}` +
                `+${"-".repeat(layout.opcode + 3)}` +
                `+${"-".repeat(layout.extensions + 1)}` +
                `+${"-".repeat(layout.prefix + 1)}` +
                operandsSeparator + "+"
            );
        }

        createSeparator();

        let operandsHeader = layout.operand.map((op, i) => `|${(" op" + i).padEnd(op + 1, " ")}`).join("") + "|";

        console.log(
            "//" + " ".repeat(layout.index + 3) +
            `| name`.padEnd(layout.name + 2, " ") +
            `| opcode`.padEnd(layout.opcode + 4, " ") +
            `| extension`.padEnd(layout.extensions + 2, " ") +
            `| prefix`.padEnd(layout.prefix + 2, " ") +
            operandsHeader
        );

        createSeparator();
    }

    createHeader(layout);

    instructions.forEach((inst, i) => {
        const extensions = utility.extractExtensions(inst);
        const prefix = utility.extractPrefix(inst);
        const formattedOperands = inst.operands.map((op, i) => op.padEnd(layout.operand[i])).join(", ");

        console.log(
            `INST(${i.toString().padEnd(layout.index)}, ` +
            `${inst.name.padEnd(layout.name).toUpperCase()}, ` +
            `0x${inst.opcode.padEnd(layout.opcode)}, ` +
            `${extensions.padEnd(layout.extensions)}, ` +
            `${prefix.padEnd(layout.prefix)}, ` +
            `${formattedOperands.padEnd(layout.totalOperand)})`
        );
    });
}

function pop_count(str) {
    for(let i = 0; i < str.length; ++i) {
        if(str[i] != 0) {
            return Math.ceil((str.length - i) / 2); 
        }
    }

    return 0;
}

function get_operand_size(op) {
    switch (op) {
        case "reg8": return 8;
        case "reg16": return 16;
        case "reg32": return 32;
        case "reg64": return 64;
        case "m8": return 8;
        case "m16": return 16;
        case "m32": return 32;
        case "m64": return 64;
        case "i8": return 8;
        case "i16": return 16;
        case "i32": return 32;
        case "i64": return 64;
    }

    return 0;
}

function calculate_code_len(inst) {
    let len = 0;

    // prefix
    len += utility.extractPrefix(inst) == "PREFIX_NONE" ? 0 : 1;

    // opcode
    len += pop_count(inst.opcode);

    // extension
    if (inst.rm) {
        len++;
    }

    if (inst.w) {
        len++;
    }

    return len;
}

function optimize_away_duplicates(instructions) {
    instructions.forEach(inst => {
        let best = inst.variants[0];
        let best_len = calculate_code_len(best);

        for(let i = 1; i < inst.variants.length; ++i) {
            let current = calculate_code_len(inst.variants[i]);

            if(current < best_len) {
                best_len = current;
                best = inst.variants[i];
            }
        }

        delete inst.variants;
        inst.opcode = best.opcode;
        inst.rm = best.rm;
        inst.w = best.w;
        inst.ri = best.ri;
        inst.pp = best.pp;
    });
}

function is_immediate(op) {
    switch(op) {
        case "i8":
        case "i16":
        case "i32":
        case "i64": return true;
        default: return false;
    }
}

const customOrder = ["i8", "i16", "i32", "i64"];

function customOperandOrder(value) {
    const index = customOrder.indexOf(value);
    return index === -1 ? customOrder.length : index;
}

function main() {
    // read the db
    // generate the table
    // const instructions = utility.filterInstructions();
    // const layout = calculateLayout(instructions);

    // createTable(instructions, layout);

    let instructions = utility.filterInstructions();
    optimize_away_duplicates(instructions)

    let flat_instructions = [];

    instructions.forEach(inst => {
        flat_instructions.push(inst);
    })

    flat_instructions.sort((a, b) => {
        if (a.name < b.name) return -1;
        if (a.name > b.name) return 1;
    
        if (a.operands[0] < b.operands[0]) return -1;
        if (a.operands[0] > b.operands[0]) return 1;
    
        const orderA = customOperandOrder(a.operands[1]);
        const orderB = customOperandOrder(b.operands[1]);
    
        if (orderA < orderB) return -1;
        if (orderA > orderB) return 1;
    
        return 0;
    });

    let indices = new Map();
    let current_index = 0;
    let last_destination = undefined;

    // actual array
    flat_instructions.forEach((inst, i) => {
        console.log(`INST(${inst.name}, 0x${inst.opcode}, ${utility.extractExtensions(inst)}, ${utility.extractPrefix(inst)}, ${inst.operands.join(", ").toUpperCase()})`);

        if(last_destination === inst.operands[0]) {
            if(is_immediate(inst.operands[1])) {}
            else {
                current_index = i;
            }
        }
        else {
            current_index = i;
        }

        indices.set(`${inst.name},${inst.operands.join(",")}`, current_index);
        last_destination = inst.operands[0];
    });

    console.log("\n\ninterface:\n\n")

    // interface
    indices.forEach((value, key) => {
        console.log(`INST(${value}, ${key})`)
    })
}

main();
