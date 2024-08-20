"use strict"

const os = require('os');
const path = require('path');
const utility = require("./utility.js");
const { Worker, isMainThread, parentPort, workerData } = require('worker_threads');
const database= require("./database.js");

const TEST_PATH = path.join(__dirname, "../source/tests/tests.txt")

const reg_type = Object.freeze({
	regular:  0,
	mask_kz:  1,
});

class reg {
  constructor(type, name, k, z) {
    this.name = name;
		this.type = type;
		this.k_reg = k;
		this.z_reg = z;
  }

	static normal(name) {
		return new reg(reg_type.regular, name);
	}

	static mask_kz(name, k, z) {
		return new reg(reg_type.mask_kz, name, k, z);
	}

  get_nasm_string() {
		switch(this.type) {
			case reg_type.regular: return this.name;
			case reg_type.mask_kz: return `${this.name}{${this.k_reg}}{${this.z_reg}}`;
		}

    return this.name;
  }

  name;
	type;
	k_reg;
	z_reg;
}

class imm {
  constructor(value) {
    this.value = value;
  }

  get_nasm_string() {
    return this.value;
  }

  get_baremetal_string() {
    switch(this.value) {
      // edge case: -9223372036854775808 - most compilers interpret this as an unsigned number
      case "-9223372036854775808": return "-9223372036854775807 - 1";
      default: return this.value;
    }
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
    return new mem(mem_type.base_index_offset, bit_width, base, offset, index, "");
  }

  // base + index * scale + offset
  static base_index_offset_scale(bit_width, base, index, offset, scale) {
    return new mem(mem_type.base_index_offset_scale, bit_width, base, offset, index, scale);
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

  type;
  bit_width;

  base;
  offset;
  index;
  scale;
}

class moff {
  constructor(offset) {
    this.offset = offset;
  }

  get_nasm_string() {
    return `[QWORD ${this.offset}]`;
  }

  offset;
}

class rel {
  constructor(offset) {
    this.offset = offset;
  }

  get_nasm_string() {
    return `${this.offset}`;
  }

  offset;
}

function generate_combinations(operands) {
  const operand_map = new Map([
    ["reg8", [
      reg.normal('cl'),
      reg.normal('dl'),
      reg.normal('bl'),
    ]],
    ["reg16", [
      reg.normal('cx'),
      reg.normal('dx'),
      reg.normal('bx'),
      reg.normal('r15w'),
    ]],
    ["reg32", [
      reg.normal('ecx'),
      reg.normal('edx'),
      reg.normal('ebx'),
      reg.normal('r15d'),
    ]],
    ["reg64", [
      reg.normal('rcx'),
      reg.normal('rdx'),
      reg.normal('rbx'),
      reg.normal('r15'),
    ]],
    ["xmm", [
      reg.normal('xmm0'),
      reg.normal('xmm1'),
      reg.normal('xmm2'),
      reg.normal('xmm15')
    ]],
		["xmm_kz", [
			// NOTE: k0 isn't valid
      reg.mask_kz('xmm1', 'k1', 'z'),
      reg.mask_kz('xmm2', 'k2', 'z'),
      reg.mask_kz('xmm15', 'k7', 'z')
    ]],
		["ymm_kz", [
      reg.mask_kz('ymm1', 'k1', 'z'),
      reg.mask_kz('ymm2', 'k2', 'z'),
      reg.mask_kz('ymm15', 'k7', 'z')
    ]],
		["zmm_kz", [
      reg.mask_kz('zmm1', 'k1', 'z'),
      reg.mask_kz('zmm2', 'k2', 'z'),
      reg.mask_kz('zmm15', 'k7', 'z')
    ]],  
		["ymm", [
      reg.normal('ymm0'),
      reg.normal('ymm1'),
      reg.normal('ymm2'),
      reg.normal('ymm15'),
      reg.normal('ymm31')
    ]],
		["zmm", [
      reg.normal('zmm0'),
      reg.normal('zmm1'),
      reg.normal('zmm2'),
      reg.normal('zmm15'),
      reg.normal('zmm31')
    ]],
    ["mmx", [
			reg.normal('mm0'),
      reg.normal('mm1'),
      reg.normal('mm2'),
      reg.normal('mm7')
    ]],
    ["bnd", [
      reg.normal('bnd0'),
      reg.normal('bnd1'),
      reg.normal('bnd2'),
      reg.normal('bnd3')
    ]],
    ["sreg", [
      reg.normal('cs'),
      reg.normal('ds'),
      reg.normal('es'),
      reg.normal('ss'),
      reg.normal('fs'),
      reg.normal('gs')
    ]],
    ["dreg", [
      reg.normal('dr0'),
      reg.normal('dr1'),
      reg.normal('dr2'),
      reg.normal('dr3'),
      reg.normal('dr7'),
    ]],
    ["creg", [
      reg.normal('cr0'),
      reg.normal('cr1'),
      reg.normal('cr2'),
      reg.normal('cr3'),
      reg.normal('cr8'),
    ]],
    ["moff8", [
      new moff('0'),
      new moff('0xFF'),
      new moff('0xFFFF'),
      new moff('0xFFFFFFFF'),
      new moff('0xFFFFFFFFFFFFFFFF'),
    ]],
    ["moff16", [
      new moff('0'),
      new moff('0xFF'),
      new moff('0xFFFF'),
      new moff('0xFFFFFFFF'),
      new moff('0xFFFFFFFFFFFFFFFF'),
    ]],
    ["moff32", [
      new moff('0'),
      new moff('0xFF'),
			new moff('0xFFFF'),
      new moff('0xFFFFFFFF'),
      new moff('0xFFFFFFFFFFFFFFFF'),
    ]],
    ["moff64", [
      new moff('0'),
      new moff('0xFF'),
      new moff('0xFFFF'),
      new moff('0xFFFFFFFF'),
      new moff('0xFFFFFFFFFFFFFFFF'),
    ]],
    ["al", [ reg.normal('al') ]],
    ["cx", [ reg.normal('cx') ]],
    ["ax", [ reg.normal('ax') ]],
    ["eax", [ reg.normal('eax') ]],
    ["rax", [ reg.normal('rax') ]],
    ["dx", [ reg.normal('dx') ]],
    ["cl", [ reg.normal('cl') ]],
    ["rcx", [ reg.normal('rcx') ]],
    ["ecx", [ reg.normal('ecx') ]],
    ["1", [new imm('1')]],
    ["i8", [
      new imm('0'),
      new imm('127'),
      new imm('-128')
    ]],
    ["i16", [
      new imm('0'),
      new imm('32767'),
      new imm('-32768'),
      new imm('127'),
      new imm('-128')
    ]],
    ["i32", [
			new imm('0'),
      new imm('2147483647'),
      new imm('-2147483648'),
      new imm('32767'),
      new imm('-32768'),
      new imm('127'),
      new imm('-128')
    ]],
    ["i64", [
      new imm('0'),
      new imm('9223372036854775807'),
      new imm('-9223372036854775808'),
      new imm('2147483647'),
      new imm('-2147483648'),
      new imm('32767'),
      new imm('-32768'),
      new imm('127'),
      new imm('-128')
    ]],
    ["mem_address", [
      mem.absolute(0, '0x0'),
      mem.absolute(0, '0xFF'),
      mem.absolute(0, '0xFFFF'),
      mem.rip_relative(0, '0x0'),
      mem.rip_relative(0, '0xFF'),
      mem.rip_relative(0, '0xFFFF'),
      mem.register_indirect(0, 'rax'),
      mem.base_offset(0, 'rax', '0x0'),
      mem.base_offset(0, 'rax', '0xFFFF'),
      mem.base_offset(0, 'r15', '0xFFFF'),
      mem.base_index_offset(0, 'rax', 'rsi', '0xFFFF'),
      mem.base_index_offset(0, 'rax', 'rsi', '0x0'),
      mem.base_index_offset(0, 'r15', 'rsi', '0xFFFF'),
      mem.base_index_offset(0, 'rax', 'r15', '0xFFFF'),
      mem.base_index_offset_scale(0, 'rax', 'rsi', '0xFFFF', "2"),
      mem.base_index_offset_scale(0, 'rax', 'rsi', '0xFFFF', "4"),
      mem.base_index_offset_scale(0, 'rax', 'rsi', '0xFFFF', "8"),
      mem.base_index_offset_scale(0, 'rsp', 'rax', '0xFFFF', "8"),
      mem.base_index_offset_scale(0, 'r15', 'rax', '0xFFFF', "8"),
      mem.base_index_offset_scale(0, 'rsp', 'r15', '0xFFFF', "8"),
      mem.base_index_offset_scale(0, 'r14', 'r15', '0xFFFF', "8"),
    ]],
    ["mem8", [
      mem.absolute(8, '0x0'),
      mem.absolute(8, '0xFF'),
      mem.absolute(8, '0xFFFF'),
      mem.rip_relative(8, '0x0'),
      mem.rip_relative(8, '0xFF'),
      mem.rip_relative(8, '0xFFFF'),
      mem.register_indirect(8, 'rax'),
      mem.base_offset(8, 'rax', '0x0'),
      mem.base_offset(8, 'rax', '0xFFFF'),
      mem.base_offset(8, 'r15', '0xFFFF'),
      mem.base_index_offset(8, 'rax', 'rsi', '0x0'),
      mem.base_index_offset(8, 'rax', 'rsi', '0xFFFF'),
      mem.base_index_offset(8, 'r15', 'rsi', '0xFFFF'),
      mem.base_index_offset(8, 'rax', 'r15', '0xFFFF'),
      mem.base_index_offset_scale(8, 'rax', 'rsi', '0xFFFF', "2"),
      mem.base_index_offset_scale(8, 'rax', 'rsi', '0xFFFF', "4"),
      mem.base_index_offset_scale(8, 'rax', 'rsi', '0xFFFF', "8"),
      mem.base_index_offset_scale(8, 'rsp', 'rax', '0xFFFF', "8"),
      mem.base_index_offset_scale(8, 'r15', 'rax', '0xFFFF', "8"),
      mem.base_index_offset_scale(8, 'rsp', 'r15', '0xFFFF', "8"),
      mem.base_index_offset_scale(8, 'r14', 'r15', '0xFFFF', "8"),
    ]],
    ["mem16", [
      mem.absolute(16, '0x0'),
      mem.absolute(16, '0xFF'),
      mem.absolute(16, '0xFFFF'),
      mem.rip_relative(16, '0x0'),
      mem.rip_relative(16, '0xFF'),
      mem.rip_relative(16, '0xFFFF'),
      mem.register_indirect(16, 'rax'),
      mem.base_offset(16, 'rax', '0x0'),
      mem.base_offset(16, 'rax', '0xFFFF'),
      mem.base_offset(16, 'r15', '0xFFFF'),
      mem.base_index_offset(16, 'rax', 'rsi', '0x0'),
      mem.base_index_offset(16, 'rax', 'rsi', '0xFFFF'),
      mem.base_index_offset(16, 'r15', 'rsi', '0xFFFF'),
      mem.base_index_offset(16, 'rax', 'r15', '0xFFFF'),
      mem.base_index_offset_scale(16, 'rax', 'rsi', '0xFFFF', "2"),
      mem.base_index_offset_scale(16, 'rax', 'rsi', '0xFFFF', "4"),
      mem.base_index_offset_scale(16, 'rax', 'rsi', '0xFFFF', "8"),
      mem.base_index_offset_scale(16, 'rsp', 'rax', '0xFFFF', "8"),
      mem.base_index_offset_scale(16, 'r15', 'rax', '0xFFFF', "8"),
      mem.base_index_offset_scale(16, 'rsp', 'r15', '0xFFFF', "8"),
      mem.base_index_offset_scale(16, 'r14', 'r15', '0xFFFF', "8"),
    ]],
    ["mem32", [
      mem.absolute(32, '0x0'),
      mem.absolute(32, '0xFF'),
      mem.absolute(32, '0xFFFF'),
      mem.rip_relative(32, '0x0'),
      mem.rip_relative(32, '0xFF'),
      mem.rip_relative(32, '0xFFFF'),
      mem.register_indirect(32, 'rax'),
      mem.base_offset(32, 'rax', '0x0'),
      mem.base_offset(32, 'rax', '0xFFFF'),
      mem.base_offset(32, 'r15', '0xFFFF'),
      mem.base_index_offset(32, 'rax', 'rsi', '0x0'),
      mem.base_index_offset(32, 'rax', 'rsi', '0xFFFF'),
      mem.base_index_offset(32, 'r15', 'rsi', '0xFFFF'),
      mem.base_index_offset(32, 'rax', 'r15', '0xFFFF'),
      mem.base_index_offset_scale(32, 'rax', 'rsi', '0xFFFF', "2"),
      mem.base_index_offset_scale(32, 'rax', 'rsi', '0xFFFF', "4"),
      mem.base_index_offset_scale(32, 'rax', 'rsi', '0xFFFF', "8"),
      mem.base_index_offset_scale(32, 'rsp', 'rax', '0xFFFF', "8"),
      mem.base_index_offset_scale(32, 'r15', 'rax', '0xFFFF', "8"),
      mem.base_index_offset_scale(32, 'rsp', 'r15', '0xFFFF', "8"),
      mem.base_index_offset_scale(32, 'r14', 'r15', '0xFFFF', "8"),
    ]],
    ["mem64", [
      mem.absolute(64, '0x0'),
      mem.absolute(64, '0xFF'),
      mem.absolute(64, '0xFFFF'),
      mem.rip_relative(64, '0x0'),
      mem.rip_relative(64, '0xFF'),
      mem.rip_relative(64, '0xFFFF'),
      mem.register_indirect(64, 'rax'),
      mem.base_offset(64, 'rax', '0x0'),
      mem.base_offset(64, 'rax', '0xFFFF'),
      mem.base_offset(64, 'r15', '0xFFFF'),
      mem.base_index_offset(64, 'rax', 'rsi', '0x0'),
      mem.base_index_offset(64, 'rax', 'rsi', '0xFFFF'),
      mem.base_index_offset(64, 'r15', 'rsi', '0xFFFF'),
      mem.base_index_offset(64, 'rax', 'r15', '0xFFFF'),
      mem.base_index_offset_scale(64, 'rax', 'rsi', '0xFFFF', "2"),
      mem.base_index_offset_scale(64, 'rax', 'rsi', '0xFFFF', "4"),
      mem.base_index_offset_scale(64, 'rax', 'rsi', '0xFFFF', "8"),
      mem.base_index_offset_scale(64, 'rsp', 'rax', '0xFFFF', "8"),
      mem.base_index_offset_scale(64, 'r15', 'rax', '0xFFFF', "8"),
      mem.base_index_offset_scale(64, 'rsp', 'r15', '0xFFFF', "8"),
      mem.base_index_offset_scale(64, 'r14', 'r15', '0xFFFF', "8"),
    ]],
    ["mem128", [
      mem.absolute(128, '0x0'),
      mem.absolute(128, '0xFF'),
      mem.absolute(128, '0xFFFF'),
      mem.rip_relative(128, '0x0'),
      mem.rip_relative(128, '0xFF'),
      mem.rip_relative(128, '0xFFFF'),
      mem.register_indirect(128, 'rax'),
      mem.base_offset(128, 'rax', '0x0'),
      mem.base_offset(128, 'rax', '0xFFFF'),
      mem.base_offset(128, 'r15', '0xFFFF'),
      mem.base_index_offset(128, 'rax', 'rsi', '0x0'),
      mem.base_index_offset(128, 'rax', 'rsi', '0xFFFF'),
      mem.base_index_offset(128, 'r15', 'rsi', '0xFFFF'),
      mem.base_index_offset(128, 'rax', 'r15', '0xFFFF'),
      mem.base_index_offset_scale(128, 'rax', 'rsi', '0xFFFF', "2"),
      mem.base_index_offset_scale(128, 'rax', 'rsi', '0xFFFF', "4"),
      mem.base_index_offset_scale(128, 'rax', 'rsi', '0xFFFF', "8"),
      mem.base_index_offset_scale(128, 'rsp', 'rax', '0xFFFF', "8"),
      mem.base_index_offset_scale(128, 'r15', 'rax', '0xFFFF', "8"),
      mem.base_index_offset_scale(128, 'rsp', 'r15', '0xFFFF', "8"),
      mem.base_index_offset_scale(128, 'r14', 'r15', '0xFFFF', "8"),
    ]],
		["mem256", [
			mem.absolute(256, '0x0'),
    	mem.absolute(256, '0xFF'),
    	mem.absolute(256, '0xFFFF'),
    	mem.rip_relative(256, '0x0'),
    	mem.rip_relative(256, '0xFF'),
    	mem.rip_relative(256, '0xFFFF'),
    	mem.register_indirect(256, 'rax'),
    	mem.base_offset(256, 'rax', '0x0'),
    	mem.base_offset(256, 'rax', '0xFFFF'),
    	mem.base_offset(256, 'r15', '0xFFFF'),
    	mem.base_index_offset(256, 'rax', 'rsi', '0x0'),
    	mem.base_index_offset(256, 'rax', 'rsi', '0xFFFF'),
    	mem.base_index_offset(256, 'r15', 'rsi', '0xFFFF'),
    	mem.base_index_offset(256, 'rax', 'r15', '0xFFFF'),
    	mem.base_index_offset_scale(256, 'rax', 'rsi', '0xFFFF', "2"),
    	mem.base_index_offset_scale(256, 'rax', 'rsi', '0xFFFF', "4"),
    	mem.base_index_offset_scale(256, 'rax', 'rsi', '0xFFFF', "8"),
    	mem.base_index_offset_scale(256, 'rsp', 'rax', '0xFFFF', "8"),
    	mem.base_index_offset_scale(256, 'r15', 'rax', '0xFFFF', "8"),
    	mem.base_index_offset_scale(256, 'rsp', 'r15', '0xFFFF', "8"),
    	mem.base_index_offset_scale(256, 'r14', 'r15', '0xFFFF', "8"),
    ]],
		["mem256", [
			mem.absolute(512, '0x0'),
    	mem.absolute(512, '0xFF'),
    	mem.absolute(512, '0xFFFF'),
    	mem.rip_relative(512, '0x0'),
    	mem.rip_relative(512, '0xFF'),
    	mem.rip_relative(512, '0xFFFF'),
    	mem.register_indirect(512, 'rax'),
    	mem.base_offset(512, 'rax', '0x0'),
    	mem.base_offset(512, 'rax', '0xFFFF'),
    	mem.base_offset(512, 'r15', '0xFFFF'),
    	mem.base_index_offset(512, 'rax', 'rsi', '0x0'),
    	mem.base_index_offset(512, 'rax', 'rsi', '0xFFFF'),
    	mem.base_index_offset(512, 'r15', 'rsi', '0xFFFF'),
    	mem.base_index_offset(512, 'rax', 'r15', '0xFFFF'),
    	mem.base_index_offset_scale(512, 'rax', 'rsi', '0xFFFF', "2"),
    	mem.base_index_offset_scale(512, 'rax', 'rsi', '0xFFFF', "4"),
    	mem.base_index_offset_scale(512, 'rax', 'rsi', '0xFFFF', "8"),
    	mem.base_index_offset_scale(512, 'rsp', 'rax', '0xFFFF', "8"),
    	mem.base_index_offset_scale(512, 'r15', 'rax', '0xFFFF', "8"),
    	mem.base_index_offset_scale(512, 'rsp', 'r15', '0xFFFF', "8"),
    	mem.base_index_offset_scale(512, 'r14', 'r15', '0xFFFF', "8"),
    ]],
    ["rel8", [
      new rel(0),
      new rel(1),
      new rel(-128),
      new rel(127),
    ]],
    ["rel32", [
      new rel(0),
      new rel(1),
      new rel(-128),
      new rel(127),
    ]]
  ]);

  function generate(operands, index) {
		if(index === operands.length) {
			return [[]];
		}

    const current = operands[index];
    const current_array = operand_map.get(current.toString()) || [];
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
  const command = `nasm -w+all -f bin -o ${bin_dir} ${asm_dir} > ${temp_dir} 2>&1`

  try {
    utility.write_file(asm_dir, assembly);
    utility.execute(command);
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
  // const instructions = database.instructions.filter((inst) => inst.name === "mov");
  const instructions = database.instructions;

  let messages = [];
  let items = [];
  let tests = [];

  // generate the various combinations we'll need to assemble
  instructions.forEach((inst) => {
    let operands_combinations = generate_combinations(inst.operands);

    operands_combinations.forEach((combination) => {
      items.push({
        name: inst.name,
        operands: combination.map(op => op.get_nasm_string()).join(", ")
      }); 
    });
  });

  function finished_processing(data) {
    tests = tests.concat(data);

    if(tests.length === items.length) {
      // generate the final layout
      console.log("generating layout...");

      let name_to_tests = new Map();
      tests.forEach(test => {
        if(name_to_tests.has(test.name)) {
          name_to_tests.get(test.name).push({
            binary_part: test.binary_part,
            instruction_part: test.instruction_part
          })
        }
        else {
          name_to_tests.set(test.name, [{
            binary_part: test.binary_part,
            instruction_part: test.instruction_part
          }])
        }
      })

      let test_file = "";

      for(let [name, tests] of name_to_tests) {
        tests.forEach(test => {
          test_file += `${test.instruction_part} ;${test.binary_part}\n`;
        })
      }

      utility.write_file(TEST_PATH, test_file);
    }
  }

  // accept the first parameter as the number of threads we want to use
  const worker_count = process.argv[2] ? parseInt(process.argv[2]) : os.cpus().length - 1; 
  const chunk_size = Math.ceil(items.length / worker_count);
  let finished_count = 0;
  
  // assemble our tests
  for(let i = 0; i < worker_count; i++) {
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
      if(code !== 0) {
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
    let result = {
      id: "data",
      data: "none"
    }

    try {
      result = compile_instruction(`${inst.name} ${inst.operands}`, temp_dir, bin_dir, asm_dir);
  
      if(tests.length % 10 === 0) {
        parentPort.postMessage({ id: "update" });
      }
    } catch(message) {
      console.log(`${inst.name} ${inst.operands}`)

      parentPort.postMessage({ id: "message", data: {
        text: message,
        command: `worker error`
      } });
    }

    if(result.id === "message") {
      parentPort.postMessage({ id: "message", data: {
        text: result.data,
        command: `${inst.name}(${inst.operands})`
      } });

      tests.push({
        binary_part: "FAILED TO ASSEMBLE",
        instruction_part: `${inst.name}(${inst.baremetal})`
      });
    }
    else {
			tests.push({
        name: utility.format_instruction_name(inst.name),
        binary_part: result.data,
        instruction_part: `${inst.name} ${inst.operands}`
      });
    }
  });

  // cleanup
	utility.delete_file(temp_dir);
  utility.delete_file(bin_dir);
  utility.delete_file(asm_dir);

  parentPort.postMessage({ id: "result", data: tests });
}



