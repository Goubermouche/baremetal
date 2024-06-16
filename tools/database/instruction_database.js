// generates the contents of instruction_database.inc
"use strict"
const utility = require("../utility.js")

const DEBUG_PRINT_DISCARDED_INSTRUCTIONS = false;

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

        if(DEBUG_PRINT_DISCARDED_INSTRUCTIONS) {
            inst.variants.forEach(v => {
                if(v != best) {
                    console.log(v.opcode, inst.name, inst.operands.join(", "));
                }
            })
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

const customOrder = [
    "i8", "i16", "i32", "i64",
    "al", "ax", "eax", "rax",
    "reg8", "reg16", "reg32", "reg64",
    "moff8", "moff16", "moff32", "moff64",
    "m8", "m16", "m32", "m64"
];

function get_operand_order(value) {
    const index = customOrder.indexOf(value);
    return index === -1 ? customOrder.length : index;
}

function assemblerDBImmediates(operands) {
    return operands.map(op => {
        switch(op) {
            case "i8":  return "imm"
            case "i16": return "imm"
            case "i32": return "imm"
            case "i64": return "imm"
            case "moff8":  return "moff"
            case "moff16": return "moff"
            case "moff32": return "moff"
            case "moff64": return "moff"
            case "m8":  return "mem8"
            case "m16": return "mem16"
            case "m32": return "mem32"
            case "m64": return "mem64"
            default: return op;
        }
    });
}

function translate_operands_to_inst(operands) {
    return operands.map(op => {
        switch(op) {
            case "m8":  return "MEM8"
            case "m16": return "MEM16"
            case "m32": return "MEM32"
            case "m64": return "MEM64"
            default: return op;
        }
    });
}

function main() {
    let instructions = utility.get_instructions();

    let flat_instructions = [];

    instructions.forEach(inst => {
        flat_instructions.push(inst);
    })

    flat_instructions.sort((a, b) => {
        if (a.name < b.name) return -1;
        if (a.name > b.name) return 1;

        const orderA = get_operand_order(a.operands[0]);
        const orderB = get_operand_order(b.operands[0]);
    
        if (orderA < orderB) return -1;
        if (orderA > orderB) return 1;
    
        const orderC = get_operand_order(a.operands[1]);
        const orderD = get_operand_order(b.operands[1]);
    
        if (orderC < orderD) return -1;
        if (orderC > orderD) return 1;
    
        return 0;
    });

    let indices = new Map();
    let dest_to_source = new Map();
    let current_index = 0;
    let last_destination = undefined;

    // actual array
    flat_instructions.forEach((inst, i) => {
        dest_to_source.set(`${inst.name}:${inst.operands.join(":")}`, i);

        if(last_destination === inst.operands[0]) {
            if(is_immediate(inst.operands[1])) {}
            else {
                current_index = i;
            }
        }
        else {
            current_index = i;
        }

        indices.set(`${inst.name},${assemblerDBImmediates(inst.operands).join(",")}`, current_index);
        last_destination = inst.operands[0];
    });

    flat_instructions.forEach(inst => {
        let special_index = 0;

        // special cases
        if(inst.operands[0] == "reg64" && inst.operands[1] == "i32") {
            special_index = dest_to_source.get(`${inst.name}:reg32:i32`)
        }
        // moff <- reg
        else if(inst.operands[0] == "moff8") {
            special_index = dest_to_source.get(`${inst.name}:mem8:reg8`)
        }
        else if(inst.operands[0] == "moff16") {
            special_index = dest_to_source.get(`${inst.name}:mem16:reg16`)
        }
        else if(inst.operands[0] == "moff32") {
            special_index = dest_to_source.get(`${inst.name}:mem32:reg32`)
        }
        else if(inst.operands[0] == "moff64") {
            special_index = dest_to_source.get(`${inst.name}:mem64:reg64`)
        }
        // reg -> moff
        else if(inst.operands[1] == "moff8") {
            special_index = dest_to_source.get(`${inst.name}:reg8:mem8`)
        }
        else if(inst.operands[1] == "moff16") {
            special_index = dest_to_source.get(`${inst.name}:reg16:mem16`)
        }
        else if(inst.operands[1] == "moff32") {
            special_index = dest_to_source.get(`${inst.name}:reg32:mem32`)
        }
        else if(inst.operands[1] == "moff64") {
            special_index = dest_to_source.get(`${inst.name}:reg64:mem64`)
        }

        console.log(`INST(${inst.name}, 0x${inst.opcode}, ${utility.extract_extensions(inst)}, ${utility.extract_prefix(inst)}, ${special_index}, ${translate_operands_to_inst(inst.operands).join(", ").toUpperCase()})`);
    })

    console.log("\n\ninterface:\n\n")

    // interface
    indices.forEach((value, key) => {
        console.log(`INST(${value}, ${key})`)
    })
}

main();
