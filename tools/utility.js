"use strict";
const fs = require("fs");
const path = require("path");
const { execSync } = require('child_process');

const asmdb = require("asmdb");

let database = new asmdb.x86util.X86DataBase();
database.addDefault();

// general purpose utilities
function read_json(path) {
    const content = fs.readFileSync(path);
    return JSON.parse(content);
}

function write_file(path, data) {
    fs.writeFileSync(path, data);
};

function delete_file(path) {
    return fs.unlinkSync(path)
}

function read_file(path) {
    return fs.readFileSync(path, 'utf8');
};

function read_file_hex(path) {
    return fs.readFileSync(path, 'hex');
};

function execute(cmd) {
    return execSync(cmd, { encoding: 'utf8'});
}

function delete_files_in_directory(directory) {
    fs.readdirSync(directory, (err, files) => {
        if (err) throw err;

        for (const file of files) {
            delete_file(path.join(directory, file));
        }
    });
}

function create_directory(path) {
    if(fs.existsSync(path)) {
        return;
    }

    return fs.mkdirSync(path);
}

const opcode_override_map = new Map([
    ["pblendvb:xmm:xmm", "0f3810"]
]);

// utility functions related to instruction transformations
// extract the 3-byte opcode from an instruction instance
function extract_opcode(inst, operands) {
    let opcodeBytes = [0x00, 0x00, 0x00];

    const key = `${inst.name}:${operands.join(":")}`;

    if(opcode_override_map.has(key)) {
        return opcode_override_map.get(key);
    }

    if (inst.opcode) {
        opcodeBytes[0] = parseInt(inst.opcode, 16);
    }

    if (inst.mm === "0F") {
        opcodeBytes[1] = 0x0F;
    }
    else if (inst.mm === "0F38") {
        opcodeBytes[1] = 0x38;
        opcodeBytes[2] = 0x0F;
    }
    else if (inst.mm === "0F3A") {
        opcodeBytes[1] = 0x3A;
        opcodeBytes[2] = 0x0F;
    }

    return opcodeBytes.reverse().map(byte => byte.toString(16).padStart(2, '0')).join('');
}

// translate asmdb operands over to our format
function translate_operands(op) {
    return op.map(o => {
        switch(o) {
            case "iq":  return "i64";
            case "uq":  return "i64";
            case "id":  return "i32";
            case "ud":  return "i32";
            case "iw":  return "i16";
            case "uw":  return "i16";
            case "ib":  return "i8";
            case "ub":  return "i8";
            case "r8":  return "reg8";
            case "r16": return "reg16";
            case "r32": return "reg32";
            case "r64": return "reg64";
            case "m8":  return "mem8";
            case "m16": return "mem16";
            case "m32": return "mem32";
            case "m64": return "mem64";
            default:    return o;
        }
    });
}

// retrieve valid operand combinations for a given instruction instance
function generate_operand_combinations(operands) {
    let cleanOperands = translate_operands(operands);
    let result = [];

    function generateCombinations(current, index) {
        if (index === cleanOperands.length) {
            result.push(current.slice());
            return;
        }

        let types = cleanOperands[index].split('/');
        for (let type of types) {
            current.push(type);
            generateCombinations(current, index + 1);
            current.pop();
        }
    }

    generateCombinations([], 0);
    return result;
}

// extract a string which represent instruction extensions that we recognize
function extract_extensions(inst) {
    let result = [];

    if (inst.rm) {
        result.push("EXT_" + inst.rm.toUpperCase());
    }

    if (inst.w) {
        result.push("EXT_REXW");
    }

    if (inst.ri) {
        result.push("EXT_OP_R");
    }

    if (result.length === 0) {
        return "EXT_NONE";
    }

    return result.join(" | ");
}

function extract_prefix(inst) {
    let result = [];

    if (inst._67h || (inst.pp && inst.pp.includes("66"))) {
        result.push("OPERAND_SIZE_OVERRIDE");
    }

    if (inst.lock) {
        result.push("LOCK");
    }

    if (inst.rep || inst.repz || (inst.pp && inst.pp.includes("F3"))) {
        result.push("REP");
    }

    if (inst.repnz || (inst.pp && inst.pp.includes("F2"))) {
        result.push("REPNE");
    }

    if (result.length === 0) {
        return "PREFIX_NONE";
    }

    return result.join(" | ");
}

// validate an instruction instance, since we don't currently support every
// instruction type
function verify_instruction(inst) {
    return !inst.prefix && !inst.fpu && (inst.arch === "ANY" || inst.arch === "X64");
}

let unknown_operands = new Set();

// verify instruction operands, this boils down to us only supporting immediate and 
// register operands
function verify_operands(operands) {
    const valid_operands = [
        // "reg8", "reg16", "reg32", "reg64",
        // "i8", "i16", "i32", "i64", 
        // "moff8", "moff16", "moff32", "moff64", 
        // "al", "ax", "eax", "rax",
        // "mem8", "mem16", "mem32", "mem64"
        "xmm"
    ];

    if(operands.length === 2) {
        if(operands.every(part => valid_operands.includes(part))) {
            return true;
        }
        else {
            operands.forEach(op => {
                if(valid_operands.includes(op) == false) {
                    unknown_operands.add(op)
                }
            })
        }
    }

    return false;
}

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
    len += extract_prefix(inst) == "PREFIX_NONE" ? 0 : 1;

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
    let flat_instructions = [];

    instructions.forEach(inst => {
        let best = inst.variants[0];
        let best_len = calculate_code_len(best);

        for(let i = 1; i < inst.variants.length; ++i) {
            let current = calculate_code_len(inst.variants[i]);

            if(current < best_len) {
                best_len = current;
                best = inst.variants[i];
            }
            else if(current == best_len) {
            }
        }

        if(false) {
            inst.variants.forEach(v => {
                if(v != best) {
                    console.log(v.opcode, inst.name, inst.operands.join(", "));
                }
            })
        }

        flat_instructions.push({
            name: inst.name,
            operands: inst.operands,
            opcode: best.opcode,
            rm: best.rm,
            w: best.w,
            ri: best.ri,
            pp: best.pp
        });
    });

    return flat_instructions;
}

function bit_width_to_name(bit_width) {
    switch (bit_width) {
        case 8: return "byte";
        case 16: return "word";
        case 32: return "dword";
        case 64: return "qword";
    }

    return "";
}

function get_required_operands(operands) {
    let result = [];

    operands.forEach(op => {
        if(op.implicit == false) {
            result.push(op);
        }
    })

    return result;
}

// filter instruction x operand combinations that we can generate code for
function get_instructions() {
    let instructions = new Map();

    database.forEach((name, inst) => {
        if (!verify_instruction(inst)) {
            return;
        }

        const required_operands = get_required_operands(inst.operands);
        const combinations = generate_operand_combinations(required_operands.map(op => op.data));

        combinations.forEach(combination => {
            const operands = translate_operands(combination);

            if (!verify_operands(operands)) {
                return;
            }

            const key = `${inst.name}:${operands.join(':')}`;

            if (instructions.has(key)) {
                instructions.get(key).variants.push({
                    opcode: extract_opcode(inst, operands),
                    rm: inst.rm,
                    w: inst.w,
                    ri: inst.ri,
                    pp: inst.pp
                })
            }
            else {
                instructions.set(key, {
                    name: inst.name,
                    operands: operands,
                    variants: [{
                        opcode: extract_opcode(inst, operands),
                        rm: inst.rm,
                        w: inst.w,
                        ri: inst.ri,
                        pp: inst.pp
                    }]
                });
            }
        });
    })

    let flat_instructions = optimize_away_duplicates(instructions);

    unknown_operands.forEach(un => {
        console.log(un)
    })

    return flat_instructions;
}

function format_instruction_name(name) {
    switch(name) {
        case "xor": return "xor_";
        case "and": return "and_";
        case "or": return "or_";
        default: return name;
    }
}

module.exports = {
    read_json,
    write_file,
    delete_file,
    read_file,
    read_file_hex,
    execute,
    bit_width_to_name,
    delete_files_in_directory,
    create_directory, 

    // instructions
    get_instructions,
    verify_instruction,

    // operands
    verify_operands,
    translate_operands,
    generate_operand_combinations,

    extract_extensions,
    extract_prefix,
    extract_opcode,
    format_instruction_name
};
