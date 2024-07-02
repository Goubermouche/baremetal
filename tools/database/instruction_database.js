// generates the contents of instruction_database.inc
"use strict"
const utility = require("../utility.js")

const DEBUG_PRINT_DISCARDED_INSTRUCTIONS = false;

const direction_map = new Map([
    ["adc", "NORMAL"],
    ["adcx", "REVERSE"],
    ["add", "NORMAL"],
    ["adox", "REVERSE"],
    ["and", "NORMAL"],
    ["bsf", "REVERSE"],
    ["bsr", "REVERSE"],
    ["bt", "NORMAL"],
    ["btc", "NORMAL"],
    ["btr", "NORMAL"],
    ["bts", "NORMAL"],
    ["cmova", "REVERSE"],
    ["cmovae", "REVERSE"],
    ["cmovb", "REVERSE"],
    ["cmovbe", "REVERSE"],
    ["cmovc", "REVERSE"],
    ["cmove", "REVERSE"],
    ["cmovg", "REVERSE"],
    ["cmovge", "REVERSE"],
    ["cmovl", "REVERSE"],
    ["cmovle", "REVERSE"],
    ["cmovna", "REVERSE"],
    ["cmovnae", "REVERSE"],
    ["cmovnb", "REVERSE"],
    ["cmovnbe", "REVERSE"],
    ["cmovnc", "REVERSE"],
    ["cmovne", "REVERSE"],
    ["cmovng", "REVERSE"],
    ["cmovnge", "REVERSE"],
    ["cmovnl", "REVERSE"],
    ["cmovnle", "REVERSE"],
    ["cmovno", "REVERSE"],
    ["cmovnp", "REVERSE"],
    ["cmovns", "REVERSE"],
    ["cmovnz", "REVERSE"],
    ["cmovo", "REVERSE"],
    ["cmovp", "REVERSE"],
    ["cmovpe", "REVERSE"],
    ["cmovpo", "REVERSE"],
    ["cmovs", "REVERSE"],
    ["cmovz", "REVERSE"],
    ["cmp", "NORMAL"],
    ["crc32", "REVERSE"],
    ["cvtsd2si", "NORMAL"],
    ["cvtss2si", "NORMAL"],
    ["cvttsd2si", "NORMAL"],
    ["cvttss2si", "NORMAL"],
    ["div", "NORMAL"],
    ["enter", "NORMAL"],
    ["idiv", "NORMAL"],
    ["imul", "REVERSE"],
    ["in", "NORMAL"],
    ["lzcnt", "REVERSE"],
    ["mov", "NORMAL"],
    ["movbe", "REVERSE"],
    ["movnti", "REVERSE"],
    ["movsx", "REVERSE"],
    ["movsxd", "REVERSE"],
    ["movzx", "REVERSE"],
    ["mul", "NORMAL"],
    ["or", "NORMAL"],
    ["out", "NORMAL"],
    ["popcnt", "REVERSE"],
    ["rcl", "NORMAL"],
    ["rcr", "NORMAL"],
    ["rol", "NORMAL"],
    ["ror", "NORMAL"],
    ["sal", "NORMAL"],
    ["sar", "NORMAL"],
    ["sbb", "NORMAL"],
    ["shl", "NORMAL"],
    ["shr", "NORMAL"],
    ["sub", "NORMAL"],
    ["test", "NORMAL"],
    ["tzcnt", "REVERSE"],
    ["xadd", "NORMAL"],
    ["xchg", "NORMAL"],
    ["xor", "NORMAL"],
    ["cmpxchg", "NORMAL"],
    // xmm
	["addpd", "REVERSE"],
	["addps", "REVERSE"],
	["addsd", "REVERSE"],
	["addss", "REVERSE"],
	["addsubpd", "REVERSE"],
	["addsubps", "REVERSE"],
	["aesdec", "REVERSE"],
	["aesdeclast", "REVERSE"],
	["aesenc", "REVERSE"],
	["aesenclast", "REVERSE"],
	["aesimc", "REVERSE"],
	["andnpd", "REVERSE"],
	["andnps", "REVERSE"],
	["rcpps", "REVERSE"],
	["rcpss", "REVERSE"],
	["rsqrtps", "REVERSE"],
	["rsqrtss", "REVERSE"],
	["sha1msg1", "REVERSE"],
	["sha1msg2", "REVERSE"],
	["sha1nexte", "REVERSE"],
	["sha256msg1", "REVERSE"],
	["sha256msg2", "REVERSE"],
	["sha256rnds2", "REVERSE"],
	["sqrtpd", "REVERSE"],
	["sqrtps", "REVERSE"],
	["sqrtsd", "REVERSE"],
	["sqrtss", "REVERSE"],
	["mulsd", "REVERSE"],
	["mulss", "REVERSE"],
	["orpd", "REVERSE"],
	["orps", "REVERSE"],
	["pabsb", "REVERSE"],
	["pabsd", "REVERSE"],
	["pabsw", "REVERSE"],
	["packssdw", "REVERSE"],
	["packsswb", "REVERSE"],
	["packusdw", "REVERSE"],
	["packuswb", "REVERSE"],
	["paddb", "REVERSE"],
	["paddd", "REVERSE"],
	["paddq", "REVERSE"],
	["subpd", "REVERSE"],
	["subps", "REVERSE"],
	["subsd", "REVERSE"],
	["subss", "REVERSE"],
	["ucomisd", "REVERSE"],
	["ucomiss", "REVERSE"],
	["unpckhpd", "REVERSE"],
	["unpckhps", "REVERSE"],
	["unpcklpd", "REVERSE"],
	["unpcklps", "REVERSE"],
	["xorpd", "REVERSE"],
	["xorps", "REVERSE"],
	["psubusb", "REVERSE"],
	["psubusw", "REVERSE"],
	["psubw", "REVERSE"],
	["ptest", "REVERSE"],
	["punpckhbw", "REVERSE"],
	["punpckhdq", "REVERSE"],
	["punpckhqdq", "REVERSE"],
	["punpckhwd", "REVERSE"],
	["punpcklbw", "REVERSE"],
	["punpckldq", "REVERSE"],
	["punpcklqdq", "REVERSE"],
	["punpcklwd", "REVERSE"],
	["pxor", "REVERSE"],
	["andpd", "REVERSE"],
	["andps", "REVERSE"],
	["blendvpd", "REVERSE"],
	["blendvps", "REVERSE"],
	["comisd", "REVERSE"],
	["comiss", "REVERSE"],
	["cvtdq2pd", "REVERSE"],
	["cvtdq2ps", "REVERSE"],
	["cvtpd2dq", "REVERSE"],
	["cvtpd2ps", "REVERSE"],
	["cvtps2dq", "REVERSE"],
	["cvtps2pd", "REVERSE"],
	["cvtsd2ss", "REVERSE"],
	["insertq", "REVERSE"],
	["maskmovdqu", "REVERSE"],
	["maxpd", "REVERSE"],
	["maxps", "REVERSE"],
	["maxsd", "REVERSE"],
	["maxss", "REVERSE"],
	["minpd", "REVERSE"],
	["minps", "REVERSE"],
	["minsd", "REVERSE"],
	["minss", "REVERSE"],
	["movapd", "REVERSE"],
	["movaps", "REVERSE"],
	["movddup", "REVERSE"],
	["movdqa", "REVERSE"],
	["movdqu", "REVERSE"],
	["movhlps", "REVERSE"],
	["movlhps", "REVERSE"],
	["movq", "REVERSE"],
	["movsd", "REVERSE"],
	["movshdup", "REVERSE"],
	["movsldup", "REVERSE"],
	["movss", "REVERSE"],
	["movupd", "REVERSE"],
	["movups", "REVERSE"],
	["mulpd", "REVERSE"],
	["mulps", "REVERSE"],
	["pmaddubsw", "REVERSE"],
	["pmaddwd", "REVERSE"],
	["pmaxsb", "REVERSE"],
	["pmaxsd", "REVERSE"],
	["pmaxsw", "REVERSE"],
	["pmaxub", "REVERSE"],
	["pmaxud", "REVERSE"],
	["pmaxuw", "REVERSE"],
	["pminsb", "REVERSE"],
	["pminsd", "REVERSE"],
	["pminsw", "REVERSE"],
	["pminub", "REVERSE"],
	["pminud", "REVERSE"],
	["pminuw", "REVERSE"],
	["pslld", "REVERSE"],
	["psllq", "REVERSE"],
	["psllw", "REVERSE"],
	["psrad", "REVERSE"],
	["psraw", "REVERSE"],
	["psrld", "REVERSE"],
	["psrlq", "REVERSE"],
	["psrlw", "REVERSE"],
	["psubb", "REVERSE"],
	["psubd", "REVERSE"],
	["psubq", "REVERSE"],
	["psubsb", "REVERSE"],
	["psubsw", "REVERSE"],
	["cvtss2sd", "REVERSE"],
	["cvttpd2dq", "REVERSE"],
	["cvttps2dq", "REVERSE"],
	["divpd", "REVERSE"],
	["divps", "REVERSE"],
	["divsd", "REVERSE"],
	["divss", "REVERSE"],
	["extrq", "REVERSE"],
	["haddpd", "REVERSE"],
	["haddps", "REVERSE"],
	["hsubpd", "REVERSE"],
	["hsubps", "REVERSE"],
	["paddsb", "REVERSE"],
	["paddsw", "REVERSE"],
	["paddusb", "REVERSE"],
	["paddusw", "REVERSE"],
	["paddw", "REVERSE"],
	["pand", "REVERSE"],
	["pandn", "REVERSE"],
	["pavgb", "REVERSE"],
	["pavgw", "REVERSE"],
	["pcmpeqb", "REVERSE"],
	["pcmpeqd", "REVERSE"],
	["pcmpeqq", "REVERSE"],
	["pmuldq", "REVERSE"],
	["pmulhrsw", "REVERSE"],
	["pmulhuw", "REVERSE"],
	["pmulhw", "REVERSE"],
	["pmulld", "REVERSE"],
	["pmullw", "REVERSE"],
	["pmuludq", "REVERSE"],
	["por", "REVERSE"],
	["psadbw", "REVERSE"],
	["pshufb", "REVERSE"],
	["psignb", "REVERSE"],
	["psignd", "REVERSE"],
	["psignw", "REVERSE"],
	["pcmpeqw", "REVERSE"],
	["pcmpgtb", "REVERSE"],
	["pcmpgtd", "REVERSE"],
	["pcmpgtq", "REVERSE"],
	["pcmpgtw", "REVERSE"],
	["phaddd", "REVERSE"],
	["phaddsw", "REVERSE"],
	["phaddw", "REVERSE"],
	["phminposuw", "REVERSE"],
	["phsubd", "REVERSE"],
	["phsubsw", "REVERSE"],
	["phsubw", "REVERSE"],
	["pmovsxbd", "REVERSE"],
	["pmovsxbq", "REVERSE"],
	["pmovsxbw", "REVERSE"],
	["pmovsxdq", "REVERSE"],
	["pmovsxwd", "REVERSE"],
	["pmovsxwq", "REVERSE"],
	["pmovzxbd", "REVERSE"],
	["pmovzxbq", "REVERSE"],
	["pmovzxbw", "REVERSE"],
	["pmovzxdq", "REVERSE"],
	["pmovzxwd", "REVERSE"],
	["pmovzxwq", "REVERSE"],
    ["pblendvb", "REVERSE"],
    ["cvtsi2sd", "REVERSE"],
    ["cvtsi2ss", "REVERSE"],
    ["cvtss2si", "REVERSE"],
    ["cvttsd2si", "REVERSE"],
    ["cvttss2si", "REVERSE"],
    ["cvtsd2si", "REVERSE"],
    ["movmskpd", "REVERSE"],
    ["movmskps", "REVERSE"],
    ["bndmov", "REVERSE"],
    ["bndmk", "REVERSE"],
    ["cvtpd2pi", "REVERSE"],
    ["cvtpi2pd", "REVERSE"],
    ["cvtpi2ps", "REVERSE"],
    ["cvtps2pi", "REVERSE"],
    ["cvttpd2pi", "REVERSE"],
    ["cvttps2pi", "REVERSE"],
    ["maskmovq", "REVERSE"],
    ["movdq2q", "REVERSE"],
    ["movntq", "REVERSE"],
    ["movq2dq", "REVERSE"],
    ["aeskeygenassist", "REVERSE"],
    ["blendpd", "REVERSE"],
    ["blendps", "REVERSE"],
    ["cmppd", "REVERSE"],
    ["cmpps", "REVERSE"],
    ["cmpsd", "REVERSE"],
    ["cmpss", "REVERSE"],
    ["dppd", "REVERSE"],
    ["dpps", "REVERSE"],
    ["insertps", "REVERSE"],
    ["mpsadbw", "REVERSE"],
    ["palignr", "REVERSE"],
    ["pblendw", "REVERSE"],
    ["pclmulqdq", "REVERSE"],
    ["pcmpestri", "REVERSE"],
    ["pcmpestrm", "REVERSE"],
    ["pcmpistri", "REVERSE"],
    ["pcmpistrm", "REVERSE"],
    ["pinsrb", "REVERSE"],
    ["pinsrd", "REVERSE"],
    ["pinsrq", "REVERSE"],
    ["pinsrw", "REVERSE"],
    ["pshufd", "REVERSE"],
    ["pshufhw", "REVERSE"],
    ["pshuflw", "REVERSE"],
    ["pshufw", "REVERSE"],
    ["roundpd", "REVERSE"],
    ["roundps", "REVERSE"],
    ["roundsd", "REVERSE"],
    ["roundss", "REVERSE"],
    ["sha1rnds4", "REVERSE"],
    ["shufpd", "REVERSE"],
    ["shufps", "REVERSE"],
]);

// overrides to the direction map
const direction_map_override = new Map([
    ["xchg:ax:reg16", "REVERSE"],
    ["xchg:eax:reg32", "REVERSE"],
    ["xchg:rax:reg64", "REVERSE"],
    ["movq:reg64:xmm", "NORMAL"],
    ["movd:xmm:reg32", "REVERSE"],
    ["pmovmskb:reg32:xmm", "REVERSE"],
    ["bndcl:bnd:reg64", "REVERSE"],
    ["bndcn:bnd:reg64", "REVERSE"],
    ["bndcu:bnd:reg64", "REVERSE"],
    ["movq:reg64:mmx", "NORMAL"],
    ["mov:sreg:reg16", "REVERSE"],
    ["mov:sreg:reg32", "REVERSE"],
    ["mov:sreg:reg64", "REVERSE"],
    ["mov:sreg:mem16", "REVERSE"],
    ["mov:sreg:mem64", "REVERSE"],
    ["mov:dreg:reg64", "REVERSE"],
    ["mov:creg:reg64", "REVERSE"],
]);

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
        "al", "cl", "reg8",
        "ax", "dx", "reg16",
        "eax", "ecx", "reg32", 
        "rax", "rcx", "reg64",
        "xmm",
        "moff8", "moff16", "moff32", "moff64",
        "mem8", "mem16", "mem32", "mem64",
        "mem128", "bnd"
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
            default:     return op;
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
    let layout_width = 0;

    layout.forEach(l => {
        layout_width += l + 2;
    });

    layout_width -= 2;

    console.log(layout_width);

    data.forEach(row => {
        result += line_prefix;
        let row_arr = [];

        row.forEach((element, column_i) => {
            row_arr.push(element.padEnd(layout[column_i], ' '));
            if(column_i + 1 !== row.length) {}
            else {
                result += row_arr.join(", ").padEnd(layout_width)
            }
        })

        
        result += line_postfix;
        result += '\n';
    })

    return result;
}

function format_instruction_operand(op) {
    switch(op) {
        default: return op;
    }
}

function encode_context(id, index) {
    if (id < 0 || id > 3 || index < 0 || index > 16383) {
        throw new Error('invalid id or index');
    }

    return (id << 14) | index;
}

function main() {
    let instructions = utility.new_database;

    // const new_set = new Set();

    // utility.new_database.forEach(inst => {
    //    new_set.add(`${inst.name}:${inst.operands.join(":")}`);
    // })

    // instructions.forEach(inst => {
    //     const key = `${inst.name}:${inst.operands.join(":")}`;

    //     if(new_set.has(key) === false) {
    //         console.log(`{${
    //             [
    //                 `"name": "${inst.name}"`,
    //                 `"operands": [${inst.operands.map(op => { return `"${op}"`; }).join(", ")}]`,
    //                 `"opcode": "${inst.opcode}"`,
    //                 `"rm": "${inst.rm}"`,
    //                 `"w": "${inst.w}"`,
    //                 `"ri": ${inst.ri}`,
    //                 `"pp": "${inst.pp}"`
    //             ].join(", ")
    //         }},`);
    //     }
    // });

    // let json_table = [];

    // instructions.forEach(inst => {
    //     json_table.push([
    //         `"name": "${inst.name}"`,
    //         `"operands": [${inst.operands.map(op => { return `"${op}"`; }).join(", ")}]`,
    //         `"opcode": "${inst.opcode}"`,
    //         `"rm": "${inst.rm}"`,
    //         `"w": "${inst.w}"`,
    //         `"ri": ${inst.ri}`,
    //         `"pp": "${inst.pp}"`
    //     ])
    // })

    // const json_layout = calculate_layout(json_table);
    // const json_text = apply_layout(json_layout, json_table, "    { ", " },");

    // console.log(`[\n${json_text.substring(0, json_text.length - 2)}\n]`)

    // return;

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

    let last_inst_name = "";

    // actual array
    instructions.forEach((inst, i) => {
        if(last_inst_name != inst.name) {
            current_index = i;
        }

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


        // don't encode these in the assembler database
        if(inst.operands.length === 2 && inst.operands[1] === "1") {
            return;
        }

        last_destination = inst.operands[0];
        last_inst_name = inst.name;

        indices.set(`${inst.name}${inst.operands.length > 0 ? "," : ""}${translate_operands_to_baremetal(inst.operands).join(",")}`, current_index);
    });

    let instruction_db = [];

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

        let row = [
            `${utility.format_instruction_name(inst.name)}`, 
            `0x${inst.opcode}`,
            `${utility.extract_extensions(inst)}`, 
            `${utility.extract_prefix(inst, inst.operands)}`,
            `${special_index.toString()}`
        ]

        let operands = translate_operands_to_inst(inst.operands);

        // directions
        const key = `${inst.name}:${inst.operands.join(":")}`;

        if(direction_map_override.has(key)) {
            row.push(direction_map_override.get(key));
        }
        else {
            if(direction_map.has(inst.name)) {
                row.push(direction_map.get(inst.name));
            }
            else {
                row.push("NORMAL")
            }
        }
        
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
                    row.push(`${format_instruction_operand(op)}`)
                }
                else {
                    row.push(format_instruction_operand(op));
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
