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
        const prefix     = utility.extractPrefix(inst);

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

function main() {
    // read the db
    // generate the table
    const instructions = utility.filterInstructions();
    const layout = calculateLayout(instructions);
    
    createTable(instructions, layout);
}

main();
