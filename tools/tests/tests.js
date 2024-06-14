"use strict"

const os = require('os');
const path = require('path');
const utility = require("../utility.js")
const { Worker, isMainThread, parentPort, workerData, workerId } = require('worker_threads');

const TEMP_INSTRUCTION_PATH = path.join(__dirname, "temp.asm")
const TEMP_BINARY_PATH      = path.join(__dirname, "temp.bin")
const TEMP_OUTPUT_PATH      = path.join(__dirname, "temp.txt")
const OUTPUT_PATH           = path.join(__dirname, "tests.txt");
const MESSAGE_PATH          = path.join(__dirname, "messages.txt");

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

const mem_type = Object.freeze({
    absolute: 0,
    rip_relative: 1,
    register_indirect: 2,
    base_offset: 3,
    base_index_offset: 4,
    base_index_offset_scale: 5,
});

class mem {
    // base + offset
    constructor(type, bit_width, base, offset, index, scale) {
        this.type = type;
        this.bit_width = bit_width;
        this.base = base;
        this.offset = offset;
        this.index = index;
        this.scale = scale;
    }

    // address
    static absolute(bit_width, address) {
        return new mem(mem_type.absolute, bit_width, "", address, "", "");
    }

    // rip + offset
    static rip_relative(bit_width, offset) {
        return new mem(mem_type.rip_relative, bit_width, "rip", offset, "", "");
    }

    // base 
    static register_indirect(bit_width, reg) {
        return new mem(mem_type.register_indirect, bit_width, reg, 0, "", "");
    }

    // base + offset
    static base_offset(bit_width, base, offset) {
        return new mem(mem_type.base_offset, bit_width, base, offset, "", "");
    }

    // base + index + offset
    static base_index_offset(bit_width, base, index, offset) {
        return new mem(mem_type.base_offset, bit_width, base, offset, index, "");
    }

    // base + index * scale + offset
    static base_index_offset_scale(bit_width, base, index, offset, scale) {
        return new mem(mem_type.base_offset, bit_width, base, offset, index, scale);
    }

    get_nasm_string() {
        const unit = utility.bit_width_to_name(this.bit_width);

        switch (this.type) {
            case mem_type.absolute: return `${unit} [${this.offset}]`;
            case mem_type.rip_relative: return `${unit} [rel $ + ${this.offset}]`;
            case mem_type.register_indirect: return `${unit} [${this.base}]`;
            case mem_type.base_offset: return `${unit} [${this.base} + ${this.offset}]`;
            case mem_type.base_index_offset: return `${unit} [${this.base} + ${this.index} + ${this.offset}]`;
            case mem_type.base_index_offset_scale: return `${unit} [${this.base} + ${this.index} * ${this.scale} + ${this.offset}]`;
        }
    }

    get_baremetal_string() {
        switch (this.type) {
            case mem_type.absolute: return `mem${this.bit_width}::absolute(${this.offset})`;
            case mem_type.rip_relative: return `mem${this.bit_width}::ptr(${this.base}, ${this.offset})`;
            case mem_type.register_indirect: return `mem${this.bit_width}::ptr(${this.base})`;
            case mem_type.base_offset: return `mem${this.bit_width}::ptr(${this.base}, ${this.offset})`;
            case mem_type.base_index_offset: return `mem${this.bit_width}::ptr(${this.base}, ${this.index}, SCALE_1, ${this.offset})`;
            case mem_type.base_index_offset_scale: return `mem${this.bit_width}::ptr(${this.base}, ${this.index}, SCALE_${this.scale}, ${this.offset})`;
        }
    }

    type;
    bit_width;

    base;
    offset;
    index;
    scale;
}

function generate_combinations(operands) {
    const operand_map = {
        reg8: [
            new reg('cl'),
            new reg('dl'),
            new reg('bl')
        ],
        reg16: [
            new reg('cx'),
            new reg('dx'),
            new reg('bx')
        ],
        reg32: [
            new reg('ecx'),
            new reg('edx'),
            new reg('ebx')
        ],
        reg64: [
            new reg('rcx'),
            new reg('rdx'),
            new reg('rbx')
        ],
        i8: [
            new imm('0'),
            new imm('127'),
            new imm('-128')
        ],
        i16: [
            new imm('0'),
            new imm('32767'),
            new imm('-32768'),
            new imm('127'),
            new imm('-128')
        ],
        i32: [
            new imm('0'),
            new imm('2147483647'),
            new imm('-2147483648'),
            new imm('32767'),
            new imm('-32768'),
            new imm('127'),
            new imm('-128')
        ],
        i64: [
            new imm('0'),
            new imm('9223372036854775807'),
            new imm('-9223372036854775808'),
            new imm('2147483647'),
            new imm('-2147483648'),
            new imm('32767'),
            new imm('-32768'),
            new imm('127'),
            new imm('-128')
        ],
        mem8: [
            mem.rip_relative(8, '0x0'),
            mem.rip_relative(8, '0xFF'),
            mem.rip_relative(8, '0xFFFF'),
            mem.register_indirect(8, 'rax'),
            mem.base_offset(8, 'rax', '0x0'),
            mem.base_offset(8, 'rax', '0xFFFF'),
            mem.base_index_offset(8, 'rax', 'rsi', '0x0'),
            mem.base_index_offset(8, 'rax', 'rsi', '0xFFFF'),
            mem.base_index_offset_scale(8, 'rax', 'rsi', '0xFFFF', "2"),
            mem.base_index_offset_scale(8, 'rax', 'rsi', '0xFFFF', "4"),
            mem.base_index_offset_scale(8, 'rax', 'rsi', '0xFFFF', "8"),
        ],
        mem16: [
            mem.rip_relative(16, '0x0'),
            mem.rip_relative(16, '0xFF'),
            mem.rip_relative(16, '0xFFFF'),
            mem.register_indirect(16, 'rax'),
            mem.base_offset(16, 'rax', '0x0'),
            mem.base_offset(16, 'rax', '0xFFFF'),
            mem.base_index_offset(16, 'rax', 'rsi', '0x0'),
            mem.base_index_offset(16, 'rax', 'rsi', '0xFFFF'),
            mem.base_index_offset_scale(16, 'rax', 'rsi', '0xFFFF', "2"),
            mem.base_index_offset_scale(16, 'rax', 'rsi', '0xFFFF', "4"),
            mem.base_index_offset_scale(16, 'rax', 'rsi', '0xFFFF', "8"),
        ],
        mem32: [
            mem.rip_relative(32, '0x0'),
            mem.rip_relative(32, '0xFF'),
            mem.rip_relative(32, '0xFFFF'),
            mem.register_indirect(32, 'rax'),
            mem.base_offset(32, 'rax', '0x0'),
            mem.base_offset(32, 'rax', '0xFFFF'),
            mem.base_index_offset(32, 'rax', 'rsi', '0x0'),
            mem.base_index_offset(32, 'rax', 'rsi', '0xFFFF'),
            mem.base_index_offset_scale(32, 'rax', 'rsi', '0xFFFF', "2"),
            mem.base_index_offset_scale(32, 'rax', 'rsi', '0xFFFF', "4"),
            mem.base_index_offset_scale(32, 'rax', 'rsi', '0xFFFF', "8"),
        ],
        mem64: [
            mem.rip_relative(64, '0x0'),
            mem.rip_relative(64, '0xFF'),
            mem.rip_relative(64, '0xFFFF'),
            mem.register_indirect(64, 'rax'),
            mem.base_offset(64, 'rax', '0x0'),
            mem.base_offset(64, 'rax', '0xFFFF'),
            mem.base_index_offset(64, 'rax', 'rsi', '0x0'),
            mem.base_index_offset(64, 'rax', 'rsi', '0xFFFF'),
            mem.base_index_offset_scale(64, 'rax', 'rsi', '0xFFFF', "2"),
            mem.base_index_offset_scale(64, 'rax', 'rsi', '0xFFFF', "4"),
            mem.base_index_offset_scale(64, 'rax', 'rsi', '0xFFFF', "8"),
        ]
    };

    function generate(operands, index) {
        if (index === operands.length) {
            return [[]];
        }

        const current = operands[index];
        const current_array = operand_map[current] || [];
        const remaining = generate(operands, index + 1);
        const combinations = [];

        for(const value of current_array) {
            for(const combination of remaining) {
                combinations.push([value, ...combination]);
            }
        }

        return combinations;
    }

    return generate(operands, 0);
}

function compile_instruction(instruction, temp_dir, bin_dir, asm_dir) {
    const assembly = `BITS 64\n${instruction}`;
    const command = `nasm -f bin -o ${bin_dir} ${asm_dir} > ${temp_dir} 2>&1`

    try {
        utility.write_file(asm_dir, assembly);
        utility.execute(command);
        const message = utility.read_file(temp_dir);

        if(message.length > 0) {
            // throw message;
            return {
                id: "message",
                data: message
            }
        }
    } catch(err) {
        throw err;
    }

    return {
        id: "data",
        data: utility.read_file_hex(bin_dir)
    };
}

function get_asm_dir(id) {
    return path.join(__dirname, `temp${id}.asm`);
}

function get_bin_dir(id) {
    return path.join(__dirname, `temp${id}.bin`);
}

function get_temp_dir(id) {
    return path.join(__dirname, `temp${id}.txt`);
}

if (isMainThread) {
    // main thread
    const start_time = Date.now();
    const instructions = utility.get_instructions();

    let messages = [];
    let items = [];
    let tests = [];

    // generate the various combinations we'll need to assemble
    instructions.forEach((inst, index) => {
        let operands_combinations = generate_combinations(inst.operands);

        operands_combinations.forEach((combination, combinationIndex) => {
            items.push({
                name: inst.name,
                operands: combination.map(op => op.get_nasm_string()).join(", "),
                baremetal: combination.map(op => op.get_baremetal_string()).join(", "),
            });
        });
    });

    function finished_processing(data) {
        tests = tests.concat(data);

        if(tests.length === items.length) {
            // generate the final layout
            let max_binary_part_len = 0;
            let max_instruction_part_len = 0;
        
            console.log("generating layout...");
        
            tests.forEach(test => {
                max_binary_part_len = Math.max(max_binary_part_len, test.binary_part.length);
                max_instruction_part_len = Math.max(max_instruction_part_len, test.instruction_part.length);
            })
        
            let test_file = "";
        
            tests.forEach(test => {
                test_file += (
                    `TEST_INST("` +
                    `${`${test.binary_part}"`.padEnd(max_binary_part_len + 1)}, ` +
                    `${test.instruction_part.padEnd(max_instruction_part_len)});\n`
                );
            })

            // serialize messages

            if(messages.length > 0) {
                let message_file = "";

                messages.forEach(message => {
                    message_file += message + "\n\n";
                })

                utility.write_file(MESSAGE_PATH, message_file);
            }
        
            utility.write_file(OUTPUT_PATH, test_file);
            console.log(`encountered messages   ${messages.length}`);
            console.log(`tests generated in     ${(Date.now() - start_time) / 1000}s`);
            console.log(`output stored in       ${OUTPUT_PATH}`);

            if(messages.length > 0) {
                console.log(`messages stored in     ${MESSAGE_PATH}`);
            }
        }
    }

    // accept the first parameter as the number of threads we want to use
    const worker_count = process.argv[2] ? parseInt(process.argv[2]) : os.cpus().length - 1; 
    const chunk_size = Math.ceil(items.length / worker_count);
    let finished_count = 0;
    
    // assemble our tests
    for (let i = 0; i < worker_count; i++) {
        const start = i * chunk_size;
        const end = start + chunk_size;
        const workerData = {
            data: items.slice(start, end),
            id: i
        };

        const worker = new Worker(__filename, { workerData });

        worker.on('message', (message) => {
            switch(message.id) {
                case "result": finished_processing(message.data); break;
                case "update": {
                    finished_count += 10;
                    process.stdout.write(`${finished_count}/${items.length}\r`);
                    break;
                }
                case "message": {
                    messages.push(message.data);
                    break;
                }
            }
        });

        worker.on('error', (error) => {
            console.error(`worker ${i} encountered an error:`, error);
        });

        worker.on('exit', (code) => {
            if (code !== 0) {
                console.error(`worker ${i} stopped with exit code ${code}`);
            }
        });
    }
} else {
    // worker thread
    const instructions = workerData.data;
    const worker_id = workerData.id;
    const tests = [];

    const temp_dir = get_temp_dir(worker_id);
    const bin_dir = get_bin_dir(worker_id);
    const asm_dir = get_asm_dir(worker_id);

    // compile all instructions
    instructions.forEach(inst => {
        const result = compile_instruction(`${inst.name} ${inst.operands}`, temp_dir, bin_dir, asm_dir);

        if(result.id === "message") {
            parentPort.postMessage({ id: "message", data: result.data });

            tests.push({
                binary_part: "FAILED TO ASSEMBLE",
                instruction_part: `${inst.name}(${inst.baremetal})`
            });
        }
        else {
            tests.push({
                binary_part: result.data,
                instruction_part: `${inst.name}(${inst.baremetal})`
            });
        }

        if(tests.length % 10 === 0) {
            parentPort.postMessage({ id: "update" });
        }
    });

    // cleanup
    utility.delete_file(temp_dir);
    utility.delete_file(bin_dir);
    utility.delete_file(asm_dir);

    parentPort.postMessage({ id: "result", data: tests });
}