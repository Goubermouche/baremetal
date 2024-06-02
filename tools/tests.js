"use strict"
const path = require('path');
const utility = require("./utility.js")

const tempInstructionPath = path.join(__dirname, "temp.asm")
const tempBinaryPath = path.join(__dirname, "temp.bin")

const translateOperands = (operands) => {
    const replacements = {
        "I8" : "100",
        "I16": "1000",
        "I32": "100000",
        "I64": "10000000000",
        "R8" : "cl",
        "R16": "cx",
        "R32": "ecx",
        "R64": "rcx"
    };

    const regex = new RegExp(Object.keys(replacements).join("|"), "g");
    return operands.map(str => str.replace(regex, match => replacements[match]));
}

const translateOperandsCPP = (operands) => {
    const replacements = {
        "I8" : "I8(100)",
        "I16": "I16(1000)",
        "I32": "I32(100000)",
        "I64": "I64(10000000000)",
        "R8" : "cl",
        "R16": "cx",
        "R32": "ecx",
        "R64": "rcx"
    };

    const regex = new RegExp(Object.keys(replacements).join("|"), "g");
    return operands.map(str => str.replace(regex, match => replacements[match]));
}

const compileInstruction = (instruction) => {
    const assembly = `BITS 64\n${instruction}`;
    const command = `nasm -f bin -o ${tempBinaryPath} ${tempInstructionPath}`

    try {
        utility.writeFile(tempInstructionPath, assembly);
    } catch(err) {
        console.log(`${err.message}`);
        return;
    }

    try {
        utility.executeCommand(command);
    } catch(err) {
        console.log(`${err.message} ${assembly}`);
        return;
    }

    return utility.readFileHex(tempBinaryPath);
}

const compileInstructions = (instructions) => {
    let binary = [];

    instructions.forEach((inst, i) => {
        const operands = translateOperands(inst.operands).join(", ");
        const binary = compileInstruction(`${inst.name} ${operands}`);
        const formattedOperands = translateOperandsCPP(inst.operands).join(", ");

        console.log(`TEST_INST(\"${binary}\", ${inst.name.toUpperCase()}(${formattedOperands}));`)
    });

    return binary;
}

function main() {
    const instructions = utility.filterInstructions();
    compileInstructions(instructions);
};

main();