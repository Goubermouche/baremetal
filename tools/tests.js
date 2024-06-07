"use strict"
const path = require('path');
const utility = require("./utility.js")

const tempInstructionPath = path.join(__dirname, "temp.asm")
const tempBinaryPath = path.join(__dirname, "temp.bin")

const translateOperands = (operands) => {
    const replacements = {
        "I8" : "255",
        "I16": "65535",
        "I32": "4294967295",
        "I64": "18446744073709551615",
        "reg8" : "cl",
        "reg16": "cx",
        "reg32": "ecx",
        "reg64": "rcx"
    };

    const regex = new RegExp(Object.keys(replacements).join("|"), "g");
    return operands.map(str => str.replace(regex, match => replacements[match]));
}

const translateOperandsCPP = (operands) => {
    const replacements = {
        "I8" : "I8(255)",
        "I16": "I16(65535)",
        "I32": "I32(4294967295)",
        "I64": "I64(18446744073709551615)",
        "reg8" : "cl",
        "reg16": "cx",
        "reg32": "ecx",
        "reg64": "rcx"
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

function generate_combinations(operands) {
     // Define the mapping between operands and their corresponding arrays
     const operandMap = {
        reg8:  [ 'cl' , 'dl'                 , 'bl'                                           ],
        reg16: [ 'cx' , 'dx'                 , 'bx'                                           ],
        reg32: [ 'ecx', 'edx'                , 'ebx'                                          ],
        reg64: [ 'rcx', 'rdx'                , 'rbx'                                          ],
        i8:    [ '0'  , '127'                , '255'                 , '-128'                 ],
        i16:   [ '0'  , '32767'              , '65535'               , '-32768'               ],
        i32:   [ '0'  , '2147483647'         , '4294967295'          , '-2147483648'          ],
        i64:   [ '0'  , '9223372036854775807', '18446744073709551615', '-9223372036854775808' ]
    };

    // Helper function to generate combinations recursively
    function generate(operands, index) {
        if (index === operands.length) {
            return [[]];
        }

        const currentOperand = operands[index];
        const currentArray = operandMap[currentOperand] || [];
        const remainingCombinations = generate(operands, index + 1);

        const combinations = [];
        for (const value of currentArray) {
            for (const combination of remainingCombinations) {
                combinations.push([value, ...combination]);
            }
        }
        return combinations;
    }

    // Generate and return combinations
    return generate(operands, 0);
}

const compileInstructions = (instructions) => {
    let binary = [];

    instructions.forEach((inst, i) => {
        // const operands = translateOperands(inst.operands).join(", ");

        generate_combinations(inst.operands).forEach(combination => {
            const operands = combination.join(", ");
            const binary = compileInstruction(`${inst.name} ${operands}`);
            // const formattedOperands = translateOperandsCPP(inst.operands).join(", ");
            console.log(`TEST_INST(\"${binary}\", ${inst.name}(${operands}));`)
        })


    });

    return binary;
}

function main() {
    const instructions = utility.filterInstructions();
    compileInstructions(instructions);
};

main();