// generates the contents of instruction_database.inc

"use strict";

const fs = require("fs");
const path = require("path");
const asmdb = require("./asmdb/index.js");

// general purpose utilities
class utility {
    static readJSON(fileName) {
        const content = fs.readFileSync(fileName);
        return JSON.parse(content);
    }
}

// utility functions related to instruction transformations
class instruction {
    // extract the 3-byte opcode from an instruction instance
    static extractOpcode(inst) {
        let opcodeBytes = [0x00, 0x00, 0x00];
    
        if (inst.opcodeHex) {
            opcodeBytes[0] = parseInt(inst.opcodeHex, 16);
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
    static translateOperands(operands) {
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
    static getOperandCombinations(operands) {
        let cleanOperands = instruction.translateOperands(operands);
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
    static extractExtensions(inst) {
        let result = [];
    
        if (inst.modR) {
            result.push("EXT_" + inst.modR.toUpperCase());
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

    // validate an instruction instance, since we don't currently support every
    // instruction type
    static verify(inst) {
        return !inst.prefix && !inst.fpu;
    }
    
    // verify instruction operands, this boils down to us only supporting immediate and 
    // register operands
    static verifyOperands(operands) {
        const validOperands = ["R8", "R16", "R32", "R64", "I8", "I16", "I32", "I64"];
        return operands.length === 2 && operands.every(part => validOperands.includes(part));
    }
}

// filter instruction x operand combinations that we can generate code for
function filterInstructions(isa) {
    let instructions = [];
    let visited = new Set();

    isa.instructionNames.forEach(function (name) {
        var instructionGroup = isa.query(name);
    
        instructionGroup.forEach(inst => {
            if (!instruction.verify(inst)) {
                return;
            }

            const combinations = instruction.getOperandCombinations(inst.operands.map(op => op.data));
    
            combinations.forEach(combination => {
                const operands = combination.map(op => op.toUpperCase());

                if(!instruction.verifyOperands(operands)) {
                    return;
                }

                const key = `${inst.name}:${operands.join()}`;

                if(visited.has(key)) {
                    return;
                }

                visited.add(key);

                instructions.push({
                    name:     inst.name,
                    operands: operands,
                    opcode: instruction.extractOpcode(inst),
                    modR: inst.modR,
                    w: inst.w,
                    ri: inst.ri
                });
            });
        });
    });

    return instructions;
}

// calculate the layout of our instruction table
function calculateLayout(instructions) {
    let layout = {
        index: instructions.length.toString().length,
        name: 0,
        opcode: 6,
        extensions: 0,
        operand: [],
        totalOperand: 0
    };

    instructions.forEach(inst => {
        const extensions = instruction.extractExtensions(inst);

        layout.name = Math.max(layout.name, inst.name.length);
        layout.extensions = Math.max(layout.extensions, extensions.length);

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
            operandsHeader
        );
    
        createSeparator();
    }

    createHeader(layout);

    instructions.forEach((inst, i) => {
        const extensions = instruction.extractExtensions(inst);
        const formattedOperands = inst.operands.map((op, i) => op.padEnd(layout.operand[i])).join(", ");

        console.log(
            `INST(${i.toString().padEnd(layout.index)}, ` +
            `${inst.name.padEnd(layout.name).toUpperCase()}, ` +
            `0x${inst.opcode.padEnd(layout.opcode)}, ` +
            `${extensions.padEnd(layout.extensions)}, ` +
            `${formattedOperands.padEnd(layout.totalOperand)})`
        );

    });
}

function main() {
    // read the db
    const filepath = path.join(__dirname, "database", "..", "asmdb", asmdb.x86.dbName);
    const data = utility.readJSON(filepath);
    const isa = new asmdb.x86.ISA(data);

    // generate the table
    const instructions = filterInstructions(isa);
    const layout = calculateLayout(instructions);
    
    createTable(instructions, layout);
}

main();
