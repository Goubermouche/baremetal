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

const compile_instruction = (instruction) => {
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

class reg {
    constructor(name) {
        this.name = name;
    }

    get_nasm_string() {
        return this.name;
    }

    get_baremetal_string() {
        return this.name;
    }

    name;
}

class imm {
    constructor(value) {
        this.value = value;
    }

    get_nasm_string() {
        return this.value;
    }

    get_baremetal_string() {
        return this.value;
    }

    value;
}

function bit_width_to_unit(bit_width) {
    switch(bit_width) {
        case 8: return "byte";
        case 16: return "word";
        case 32: return "dword";
        case 64: return "qword";
    }

    return "";
}

class mem {
    // base + offset
    constructor(bit_width, base, offset) {
       this.bit_width = bit_width;
       this.base = base;
       this.offset = offset;
    }

    get_nasm_string() {
        const unit = bit_width_to_unit(this.bit_width);

        if(this.base == "rip") {
            return `${unit} [rel $ + ${this.offset}]`;
        }

        return `${unit} [${this.base} + ${this.offset}]`;
    }

    get_baremetal_string() {
        return `mem${this.bit_width}::ptr(${this.base}, ${this.offset})`;
    }
    

    bit_width;
    base;
    offset;
}

function generate_combinations(operands) {
     // Define the mapping between operands and their corresponding arrays
     const operand_map = {
        reg8:  [ new reg('cl'),  new reg('dl'),  new reg('bl')  ],
        reg16: [ new reg('cx') , new reg('dx'),  new reg('bx')  ],
        reg32: [ new reg('ecx'), new reg('edx'), new reg('ebx') ],
        reg64: [ new reg('rcx'), new reg('rdx'), new reg('rbx') ],
        i8:    [ new imm('0')  , new imm('127')                , new imm('-128')                                                                                                                                                                                                ],
        i16:   [ new imm('0')  , new imm('32767')              , new imm('-32768'),               new imm('127'),        new imm('-128')                                                                                                                 ],
        i32:   [ new imm('0')  , new imm('2147483647')         , new imm('-2147483648'),          new imm('32767'),      new imm('-32768'),      new imm('127'),   new imm('-128')                                                     ],
        i64:   [ new imm('0')  , new imm('9223372036854775807'), new imm('-9223372036854775808'), new imm('2147483647'), new imm('-2147483648'), new imm('32767'), new imm('-32768'), new imm('127'), new imm('-128')  ],
        mem8:  [ new mem(8, 'rip', '0x0') ],
        mem16: [ new mem(16, 'rip', '0x0') ],
        mem32: [ new mem(32, 'rip', '0x0') ],
        mem64: [ new mem(64, 'rip', '0x0') ]
    };

    // Helper function to generate combinations recursively
    function generate(operands, index) {
        if (index === operands.length) {
            return [[]];
        }

        const currentOperand = operands[index];
        const currentArray = operand_map[currentOperand] || [];
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


function compile_instructions(instructions) {
    instructions.forEach(inst => {
        let operands_combinations = generate_combinations(inst.operands);

        operands_combinations.forEach(combination => {
            const nams_combinations = combination.map(c => c.get_nasm_string());
            const baremetal_combinations = combination.map(c => c.get_baremetal_string());

            const nasm_operands = nams_combinations.join(", ");
            const baremetal_operands = baremetal_combinations.join(", ");

            // compile the nasm instruction
            const binary = compile_instruction(`${inst.name} ${nasm_operands}`);

            console.log(`TEST_INST("${binary}", ${inst.name}(${baremetal_operands}));`)
        });
    });
}


function main() {
    const instructions = utility.get_instructions();
    compile_instructions(instructions);

    // console.log(instructions)
    return;
    compileInstructions(instructions);
};

main();