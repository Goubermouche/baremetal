"use strict";
const fs = require("fs");
const path = require("path");
const { execSync } = require('child_process');

const asmdb = require("asmdb");

let database = new asmdb.x86util.X86DataBase();
database.addDefault();

// general purpose utilities
function readJSON(fileName) {
    const content = fs.readFileSync(fileName);
    return JSON.parse(content);
}

function writeFile(filePath, data) {
    fs.writeFileSync(filePath, data);
};

function readFile(filePath) {
    return fs.readFileSync(filePath, 'utf8');
};

function readFileHex(filePath) {
    return fs.readFileSync(filePath, 'hex');
};

function executeCommand(cmd) {
    return execSync(cmd, { encoding: 'utf8' });
}

// utility functions related to instruction transformations
// extract the 3-byte opcode from an instruction instance
function extractOpcode(inst) {
    let opcodeBytes = [0x00, 0x00, 0x00];

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

// translate asmdb immediate operands over to our format
function translateImmOperands(operands) {
    const replacements = {
        "iq": "i64",
        "uq": "i64",
        "id": "i32",
        "ud": "i32",
        "iw": "i16",
        "uw": "i16",
        "ib": "i8",
        "ub": "i8"
    };

    const regex = new RegExp(Object.keys(replacements).join("|"), "g");
    return operands.map(str => str.replace(regex, match => replacements[match]));
}

// retrieve valid operand combinations for a given instruction instance
function getOperandCombinations(operands) {
    let cleanOperands = translateImmOperands(operands);
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
function extractExtensions(inst) {
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

function extractPrefix(inst) {
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
function verifyInstruction(inst) {
    return !inst.prefix && !inst.fpu && (inst.arch === "ANY" || inst.arch === "X64");
}

// verify instruction operands, this boils down to us only supporting immediate and 
// register operands
function verifyOperands(operands) {
    const validOperands = [
        "reg8", "reg16", "reg32", "reg64",
        "i8", "i16", "i32", "i64", 
        //"moff8", "moff16", "moff32", "moff64", 
        //"al", "ax", "eax", "rax",
        "mem8", "mem16", "mem32", "mem64"
    ];
    return operands.length === 2 && operands.every(part => validOperands.includes(part));
}

function translateOperands(op) {
    return op.map(o => {
        switch(o) {
            case "r8":  return "reg8"
            case "r16": return "reg16"
            case "r32": return "reg32"
            case "r64": return "reg64"
            case "m8":  return "mem8"
            case "m16": return "mem16"
            case "m32": return "mem32"
            case "m64": return "mem64"
            default:    return o;
        }
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

function calculate_code_len(inst) {
    let len = 0;

    // prefix
    len += extractPrefix(inst) == "PREFIX_NONE" ? 0 : 1;

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

// filter instruction x operand combinations that we can generate code for
function get_instructions() {
    let instructions = new Map();

    database.forEach((name, inst) => {
        //if (!verifyInstruction(inst)) {
        //    return;
        //}
        if(inst.name != "mov") {
            return;
        }

        const combinations = getOperandCombinations(inst.operands.map(op => op.data));

        combinations.forEach(combination => {
            const operands = translateOperands(combination);

            if (!verifyOperands(operands)) {
                return;
            }

            const key = `${inst.name}:${operands.join(':')}`;

            if (instructions.has(key)) {
                instructions.get(key).variants.push({
                    opcode: extractOpcode(inst),
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
                        opcode: extractOpcode(inst),
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

    return flat_instructions;
}

module.exports = {
    readJSON,
    writeFile,
    readFile,
    readFileHex,
    executeCommand,
    extractExtensions,
    extractOpcode,
    translateImmOperands,
    getOperandCombinations,
    extractExtensions,
    verifyInstruction,
    verifyOperands,
    extractPrefix,

    get_instructions,
};
