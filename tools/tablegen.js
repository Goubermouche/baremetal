// generates the contents of instruction_database.inc and assembler_database.inc

"use strict"

const { argv } = require('node:process');

const database = require("./database.js");
const utility = require("./utility.js")

function is_immediate(op) {
    switch(op) {
        case "i8":
        case "i16":
        case "i32":
        case "i64": return true;
        default:    return false;
    }
}

function get_operand_order(value) {
	const operand_order = [
		"1", "i8", "i16", "i32", "i64",
		"al", "cl", "reg8",
		"ax", "dx",  "cx","reg16",
		"eax", "ecx", "reg32", 
		"rax", "rcx", "reg64",
		"xmm", "mem128", 
		"ymm", "mem256",
		"bnd", "mmx", "sreg", "dreg", "creg",
		"moff8", "moff16", "moff32", "moff64",
		"mem8", "mem16", "mem32", "mem64", "mem128",
		"mem_address", "rel8", "rel32"
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
            case "m128":   return "mem128"
            case "m256":   return "mem256"
            case "1":      return "imm"
            default: return op;
        }
    });
}

function translate_operands_to_inst(operands) {
    return operands.filter(op => op !== "1").map(op => {
        switch(op) {
            case "m8":   return "MEM8";
            case "m16":  return "MEM16";
            case "m32":  return "MEM32";
            case "m64":  return "MEM64";
            case "m128": return "MEM128";
            case "m256": return "MEM256";
            default:     return op;
        }
    });
}

function format_instruction_operand(op) {
    switch(op) {
        case "rel8": 
        case "rel16": 
        case "rel32": return "rel";
        default: return op;
    }
}

function encode_context(id, index) {
    if (id < 0 || id > 3 || index < 0 || index > 16383) {
        throw new Error('invalid id or index');
    }

    return (id << 14) | index;
}

function get_imm_index(operands) {
    if(is_immediate(operands[3])) {
        return 3;
    }

    if(is_immediate(operands[2])) {
        return 2;
    }

    if(is_immediate(operands[1])) {
        return 1;
    }

    if(is_immediate(operands[0])) {
        return 0;
    }

    return undefined;
}

function main() {
    const assembler_db_path = process.argv[2];
    const instruction_db_path = process.argv[3]; 

    let instructions = database.instructions;

    // sort instructions (special order, dictated by imm operands)
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
    let last_inst_name = "";
    let last_operands = undefined;
    let is_imm_mode = false;

    // precalculate instruction indices
    instructions.forEach((inst, i) => {
        // new instruction
        if(last_inst_name != inst.name) {
            current_index = i;
        }

        const key = `${inst.name}:${inst.operands.join(":")}`;
        dest_to_source.set(key, i);

        const imm_index = get_imm_index(inst.operands);

        let operands = translate_operands_to_baremetal(inst.operands).join(":");

        if(imm_index !== undefined) {
            if(is_imm_mode == false) {
                is_imm_mode = true;
                current_index = i;
            }
            else if(operands != last_operands) {
                current_index = i;
            }
        }
        else {
            is_imm_mode = false;
            current_index = i;
        }

        last_operands = operands;

        // if((inst.operands.length ===  1 && is_immediate(inst.operands[0])) || (inst.operands.length > 1 && last_destination === inst.operands[0])) {
        //     if(inst.operands.length === 1 ?  is_immediate(inst.operands[0]) :  is_immediate(inst.operands[1])) {}
        //     else {
        //         current_index = i;
        //     }
        // }
        // else {
        //     current_index = i;
        // }

        // don't encode these in the assembler database
        if(inst.operands.length === 2 && inst.operands[1] === "1") {
            return;
        }

        last_inst_name = inst.name;



        indices.set(`${inst.name}${inst.operands.length > 0 ? "," : ""}${translate_operands_to_baremetal(inst.operands).join(",")}`, current_index);
    });

    let instruction_db = [];

    // instruction database table
    instructions.forEach(inst => {
        let special_index = 65535; // u16 max

        // special cases
        if(inst.name == "mov" && inst.operands[0] == "reg64" && inst.operands[1] == "i32") {
            // 0
            special_index = encode_context(0, dest_to_source.get(`${inst.name}:reg32:i32`))
        }
        else if(
            (
                inst.name == "rcl" || 
                inst.name == "rcr" ||
                inst.name == "rol" || 
                inst.name == "ror" || 
                inst.name == "sal" || 
                inst.name == "sar" || 
                inst.name == "shl" || 
                inst.name == "shr" || 
                inst.name == "rcr"
            ) && 
            inst.operands[1] !== "1"
        ) {
            // 1
            special_index = encode_context(1, dest_to_source.get(`${inst.name}:${inst.operands[0]}:1`));
        }
        else if(inst.name === "imul" && inst.operands.length === 3 && is_immediate(inst.operands[2])) {
            // 2
            const key8 = `${inst.name}:${inst.operands[0]}:${inst.operands[1]}:i8`;

            if(dest_to_source.has(key8) && inst.operands[2] !== "i8") {
                special_index = encode_context(2, dest_to_source.get(key8));
            }
        }

        //let extensions = inst.ext.map(e => { return "IEX_" + e}).join(" | ");

        let row = [
            `${utility.format_instruction_name(inst.name)}`, 
            `0x${inst.opcode}`,
            `${utility.extract_extensions(inst)}`, 
            `${utility.extract_prefix(inst)}`,
            `${special_index.toString()}`,
            `${inst.dir}`,
            `${inst.enc.map((e) => "ENC_" + e).join(" | ")}`,
            `${inst.imp}`, 
            `0x${inst.ilo}`, 
            `${inst.var}`, 
            "IEX_NONE"
            // `${extensions.length == 0 ? "IEX_NONE" : extensions}`,
        ]

        let operands = translate_operands_to_inst(inst.operands);

        operands.forEach((op, i) => {
            row.push(op.toUpperCase());
        });

        instruction_db.push(row);
    })

    const instruction_db_layout = utility.calculate_layout(instruction_db);
    const instruction_db_text = utility.apply_layout(instruction_db_layout, instruction_db, "INST(", ")");
    let assembler_db = [];

    // assembler database table
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
                    row.push(`${format_instruction_operand(op)}`)
                }
                else {
                    row.push(format_instruction_operand(op));
                }
            }
        })

        assembler_db.push(row);
    })

    const assembler_db_layout = utility.calculate_layout(assembler_db);
    const assembler_db_text = utility.apply_layout(assembler_db_layout, assembler_db, "INST(", ")");

    utility.write_file(assembler_db_path, assembler_db_text);
    utility.write_file(instruction_db_path, instruction_db_text);
}

main();
