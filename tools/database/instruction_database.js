// generates the contents of instruction_database.inc
"use strict"
const utility = require("../utility.js")

const DEBUG_PRINT_DISCARDED_INSTRUCTIONS = false;

function pop_count(str) {
    for(let i = 0; i < str.length; ++i) {
        if(str[i] != 0) {
            return Math.ceil((str.length - i) / 2); 
        }
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

function is_immediate(op) {
    switch(op) {
        case "i8":
        case "i16":
        case "i32":
        case "i64": return true;
        default: return false;
    }
}

function get_operand_order(value) {
    const operand_order = [
        "i8", "i16", "i32", "i64",
        "al", "ax", "eax", "rax",
        "reg8", "reg16", "reg32", "reg64",
        "moff8", "moff16", "moff32", "moff64",
        "m8", "m16", "m32", "m64"
    ];

    const index = operand_order.indexOf(value);
    return index === -1 ? operand_order.length : index;
}

function translate_operands_to_baremetal(operands) {
    return operands.map(op => {
        switch(op) {
            case "i8":     return "imm"
            case "i16":    return "imm"
            case "i32":    return "imm"
            case "i64":    return "imm"
            case "moff8":  return "moff"
            case "moff16": return "moff"
            case "moff32": return "moff"
            case "moff64": return "moff"
            case "m8":     return "mem8"
            case "m16":    return "mem16"
            case "m32":    return "mem32"
            case "m64":    return "mem64"
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

function calculate_layout(data) {
    let layout = [];

    data.forEach(row => {
        while(layout.length < row.length) {
            layout.push(0);
        }

        row.forEach((element, column_i) => {
            layout[column_i] = Math.max(layout[column_i], element.length);
        });
    });

    return layout;
}

function apply_layout(layout, data, line_prefix, line_postfix) {
    let result = "";

    data.forEach(row => {
        result += line_prefix;

        row.forEach((element, column_i) => {
            result += element.padEnd(layout[column_i], ' ');
            if(column_i + 1 !== row.length) {
                result += ", "
            }
        })

        result += line_postfix;
        result += '\n';
    })

    return result;
}

function main() {
    let instructions = utility.get_instructions();

    instructions.sort((a, b) => {
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
    instructions.forEach((inst, i) => {
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

        indices.set(`${inst.name},${translate_operands_to_baremetal(inst.operands).join(",")}`, current_index);
        last_destination = inst.operands[0];
    });

    let instruction_db = [];

    instructions.forEach(inst => {
        let special_index = 0;

        // special cases
        if(inst.operands[0] == "reg64" && inst.operands[1] == "i32") {
            special_index = dest_to_source.get(`${inst.name}:reg32:i32`)
        }

        let row = [
            `${utility.format_instruction_name(inst.name)}`, 
            `0x${inst.opcode}`,
            `${utility.extract_extensions(inst)}`, 
            `${utility.extract_prefix(inst)}`,
            `${special_index.toString()}`
        ]

        let operands = translate_operands_to_inst(inst.operands);

        operands.forEach((op, i) => {
            row.push(op.toUpperCase());
        });

        instruction_db.push(row);
    })

    const instruction_db_layout = calculate_layout(instruction_db);
    const instruction_db_text = apply_layout(instruction_db_layout, instruction_db, "INST(", ")");

    let assembler_db = [];

    indices.forEach((value, key) => {
        let row = [
            `${value.toString()}`
        ];

        const operands = key.split(",");

        operands.forEach((op, i) => {
            if(i === 0) {
                row.push(utility.format_instruction_name(op));
            }
            else {
                if(i + 1 !== operands.length) {
                    row.push(`${op}`)
                }
                else {
                    row.push(op);
                }
            }
        })

        assembler_db.push(row);
    })

    const assembler_db_layout = calculate_layout(assembler_db);
    const assembler_db_text = apply_layout(assembler_db_layout, assembler_db, "INST(", ")");

    console.log(instruction_db_text)
    console.log(assembler_db_text)
}

main();
