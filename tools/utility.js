"use strict";
const fs = require("fs");
const path = require("path");
const { execSync } = require('child_process');

const asmdb = require("asmdb");

const new_database = [
    { "name": "adc"            , "operands": ["al", "i8"]              , "opcode": "000014", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["ax", "i16"]             , "opcode": "000015", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "adc"            , "operands": ["eax", "i32"]            , "opcode": "000015", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["rax", "i32"]            , "opcode": "000015", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["reg8", "i8"]            , "opcode": "000080", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["mem8", "i8"]            , "opcode": "000080", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["reg16", "i16"]          , "opcode": "000081", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "adc"            , "operands": ["mem16", "i16"]          , "opcode": "000081", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "adc"            , "operands": ["reg32", "i32"]          , "opcode": "000081", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["mem32", "i32"]          , "opcode": "000081", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["reg64", "i32"]          , "opcode": "000081", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["mem64", "i32"]          , "opcode": "000081", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["reg16", "i8"]           , "opcode": "000083", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "adc"            , "operands": ["mem16", "i8"]           , "opcode": "000083", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "adc"            , "operands": ["reg32", "i8"]           , "opcode": "000083", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["mem32", "i8"]           , "opcode": "000083", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["reg64", "i8"]           , "opcode": "000083", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["mem64", "i8"]           , "opcode": "000083", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["reg8", "reg8"]          , "opcode": "000010", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["mem8", "reg8"]          , "opcode": "000010", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["reg16", "reg16"]        , "opcode": "000011", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "adc"            , "operands": ["mem16", "reg16"]        , "opcode": "000011", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "adc"            , "operands": ["reg32", "reg32"]        , "opcode": "000011", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["mem32", "reg32"]        , "opcode": "000011", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["reg64", "reg64"]        , "opcode": "000011", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["mem64", "reg64"]        , "opcode": "000011", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["reg8", "mem8"]          , "opcode": "000012", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["reg16", "mem16"]        , "opcode": "000013", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "adc"            , "operands": ["reg32", "mem32"]        , "opcode": "000013", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "adc"            , "operands": ["reg64", "mem64"]        , "opcode": "000013", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "adcx"           , "operands": ["reg32", "reg32"]        , "opcode": "0f38f6", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "adcx"           , "operands": ["reg32", "mem32"]        , "opcode": "0f38f6", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "adcx"           , "operands": ["reg64", "reg64"]        , "opcode": "0f38f6", "rm": "r", "w": "W1", "ri": false, "pp": "66"   },
    { "name": "adcx"           , "operands": ["reg64", "mem64"]        , "opcode": "0f38f6", "rm": "r", "w": "W1", "ri": false, "pp": "66"   },
    { "name": "add"            , "operands": ["al", "i8"]              , "opcode": "000004", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["ax", "i16"]             , "opcode": "000005", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "add"            , "operands": ["eax", "i32"]            , "opcode": "000005", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["rax", "i32"]            , "opcode": "000005", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["reg8", "i8"]            , "opcode": "000080", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["mem8", "i8"]            , "opcode": "000080", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["reg16", "i16"]          , "opcode": "000081", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "add"            , "operands": ["mem16", "i16"]          , "opcode": "000081", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "add"            , "operands": ["reg32", "i32"]          , "opcode": "000081", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["mem32", "i32"]          , "opcode": "000081", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["reg64", "i32"]          , "opcode": "000081", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["mem64", "i32"]          , "opcode": "000081", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["reg16", "i8"]           , "opcode": "000083", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "add"            , "operands": ["mem16", "i8"]           , "opcode": "000083", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "add"            , "operands": ["reg32", "i8"]           , "opcode": "000083", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["mem32", "i8"]           , "opcode": "000083", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["reg64", "i8"]           , "opcode": "000083", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["mem64", "i8"]           , "opcode": "000083", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["reg8", "reg8"]          , "opcode": "000000", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["mem8", "reg8"]          , "opcode": "000000", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["reg16", "reg16"]        , "opcode": "000001", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "add"            , "operands": ["mem16", "reg16"]        , "opcode": "000001", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "add"            , "operands": ["reg32", "reg32"]        , "opcode": "000001", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["mem32", "reg32"]        , "opcode": "000001", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["reg64", "reg64"]        , "opcode": "000001", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["mem64", "reg64"]        , "opcode": "000001", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["reg8", "mem8"]          , "opcode": "000002", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["reg16", "mem16"]        , "opcode": "000003", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "add"            , "operands": ["reg32", "mem32"]        , "opcode": "000003", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "add"            , "operands": ["reg64", "mem64"]        , "opcode": "000003", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "addpd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f58", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "addpd"          , "operands": ["xmm", "mem128"]         , "opcode": "000f58", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "addps"          , "operands": ["xmm", "xmm"]            , "opcode": "000f58", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "addps"          , "operands": ["xmm", "mem128"]         , "opcode": "000f58", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "addsd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f58", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "addsd"          , "operands": ["xmm", "mem64"]          , "opcode": "000f58", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "addss"          , "operands": ["xmm", "xmm"]            , "opcode": "000f58", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "addss"          , "operands": ["xmm", "mem32"]          , "opcode": "000f58", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "addsubpd"       , "operands": ["xmm", "xmm"]            , "opcode": "000fd0", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "addsubpd"       , "operands": ["xmm", "mem128"]         , "opcode": "000fd0", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "addsubps"       , "operands": ["xmm", "xmm"]            , "opcode": "000fd0", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "addsubps"       , "operands": ["xmm", "mem128"]         , "opcode": "000fd0", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "adox"           , "operands": ["reg32", "reg32"]        , "opcode": "0f38f6", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "adox"           , "operands": ["reg32", "mem32"]        , "opcode": "0f38f6", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "adox"           , "operands": ["reg64", "reg64"]        , "opcode": "0f38f6", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "adox"           , "operands": ["reg64", "mem64"]        , "opcode": "0f38f6", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "aesdec"         , "operands": ["xmm", "xmm"]            , "opcode": "0f38de", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "aesdec"         , "operands": ["xmm", "mem128"]         , "opcode": "0f38de", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "aesdeclast"     , "operands": ["xmm", "xmm"]            , "opcode": "0f38df", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "aesdeclast"     , "operands": ["xmm", "mem128"]         , "opcode": "0f38df", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "aesenc"         , "operands": ["xmm", "xmm"]            , "opcode": "0f38dc", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "aesenc"         , "operands": ["xmm", "mem128"]         , "opcode": "0f38dc", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "aesenclast"     , "operands": ["xmm", "xmm"]            , "opcode": "0f38dd", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "aesenclast"     , "operands": ["xmm", "mem128"]         , "opcode": "0f38dd", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "aesimc"         , "operands": ["xmm", "xmm"]            , "opcode": "0f38db", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "aesimc"         , "operands": ["xmm", "mem128"]         , "opcode": "0f38db", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "and"            , "operands": ["al", "i8"]              , "opcode": "000024", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["ax", "i16"]             , "opcode": "000025", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "and"            , "operands": ["eax", "i32"]            , "opcode": "000025", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["rax", "i32"]            , "opcode": "000025", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["reg8", "i8"]            , "opcode": "000080", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["mem8", "i8"]            , "opcode": "000080", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["reg16", "i16"]          , "opcode": "000081", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "and"            , "operands": ["mem16", "i16"]          , "opcode": "000081", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "and"            , "operands": ["reg32", "i32"]          , "opcode": "000081", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["mem32", "i32"]          , "opcode": "000081", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["reg64", "i32"]          , "opcode": "000081", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["mem64", "i32"]          , "opcode": "000081", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["reg16", "i8"]           , "opcode": "000083", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "and"            , "operands": ["mem16", "i8"]           , "opcode": "000083", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "and"            , "operands": ["reg32", "i8"]           , "opcode": "000083", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["mem32", "i8"]           , "opcode": "000083", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["reg64", "i8"]           , "opcode": "000083", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["mem64", "i8"]           , "opcode": "000083", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["reg8", "reg8"]          , "opcode": "000020", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["mem8", "reg8"]          , "opcode": "000020", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["reg16", "reg16"]        , "opcode": "000021", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "and"            , "operands": ["mem16", "reg16"]        , "opcode": "000021", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "and"            , "operands": ["reg32", "reg32"]        , "opcode": "000021", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["mem32", "reg32"]        , "opcode": "000021", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["reg64", "reg64"]        , "opcode": "000021", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["mem64", "reg64"]        , "opcode": "000021", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["reg8", "mem8"]          , "opcode": "000022", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["reg16", "mem16"]        , "opcode": "000023", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "and"            , "operands": ["reg32", "mem32"]        , "opcode": "000023", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "and"            , "operands": ["reg64", "mem64"]        , "opcode": "000023", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "andnpd"         , "operands": ["xmm", "xmm"]            , "opcode": "000f55", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "andnpd"         , "operands": ["xmm", "mem128"]         , "opcode": "000f55", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "andnps"         , "operands": ["xmm", "xmm"]            , "opcode": "000f55", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "andnps"         , "operands": ["xmm", "mem128"]         , "opcode": "000f55", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "andpd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f54", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "andpd"          , "operands": ["xmm", "mem128"]         , "opcode": "000f54", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "andps"          , "operands": ["xmm", "xmm"]            , "opcode": "000f54", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "andps"          , "operands": ["xmm", "mem128"]         , "opcode": "000f54", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "blendvpd"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3815", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "blendvpd"       , "operands": ["xmm", "mem128"]         , "opcode": "0f3815", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "blendvps"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3814", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "blendvps"       , "operands": ["xmm", "mem128"]         , "opcode": "0f3814", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bndcl"          , "operands": ["bnd", "reg64"]          , "opcode": "000f1a", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "bndcl"          , "operands": ["bnd", "mem_address"]    , "opcode": "000f1a", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "bndcn"          , "operands": ["bnd", "reg64"]          , "opcode": "000f1b", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "bndcn"          , "operands": ["bnd", "mem_address"]    , "opcode": "000f1b", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "bndcu"          , "operands": ["bnd", "reg64"]          , "opcode": "000f1a", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "bndcu"          , "operands": ["bnd", "mem_address"]    , "opcode": "000f1a", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "bndldx"         , "operands": ["bnd", "mem_address"]    , "opcode": "000f1a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bndmk"          , "operands": ["bnd", "mem_address"]    , "opcode": "000f1b", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "bndmov"         , "operands": ["bnd", "bnd"]            , "opcode": "000f1a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bndmov"         , "operands": ["bnd", "mem_address"]    , "opcode": "000f1a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bndmov"         , "operands": ["mem_address", "bnd"]    , "opcode": "000f1b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bndstx"         , "operands": ["mem_address", "bnd"]    , "opcode": "000f1b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bsf"            , "operands": ["reg16", "reg16"]        , "opcode": "000fbc", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bsf"            , "operands": ["reg16", "mem16"]        , "opcode": "000fbc", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bsf"            , "operands": ["reg32", "reg32"]        , "opcode": "000fbc", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bsf"            , "operands": ["reg32", "mem32"]        , "opcode": "000fbc", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bsf"            , "operands": ["reg64", "reg64"]        , "opcode": "000fbc", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "bsf"            , "operands": ["reg64", "mem64"]        , "opcode": "000fbc", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "bsr"            , "operands": ["reg16", "reg16"]        , "opcode": "000fbd", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bsr"            , "operands": ["reg16", "mem16"]        , "opcode": "000fbd", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bsr"            , "operands": ["reg32", "reg32"]        , "opcode": "000fbd", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bsr"            , "operands": ["reg32", "mem32"]        , "opcode": "000fbd", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bsr"            , "operands": ["reg64", "reg64"]        , "opcode": "000fbd", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "bsr"            , "operands": ["reg64", "mem64"]        , "opcode": "000fbd", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "bt"             , "operands": ["reg16", "reg16"]        , "opcode": "000fa3", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bt"             , "operands": ["mem16", "reg16"]        , "opcode": "000fa3", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bt"             , "operands": ["reg32", "reg32"]        , "opcode": "000fa3", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bt"             , "operands": ["mem32", "reg32"]        , "opcode": "000fa3", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bt"             , "operands": ["reg64", "reg64"]        , "opcode": "000fa3", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "bt"             , "operands": ["mem64", "reg64"]        , "opcode": "000fa3", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "bt"             , "operands": ["reg16", "i8"]           , "opcode": "000fba", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bt"             , "operands": ["mem16", "i8"]           , "opcode": "000fba", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bt"             , "operands": ["reg32", "i8"]           , "opcode": "000fba", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bt"             , "operands": ["mem32", "i8"]           , "opcode": "000fba", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bt"             , "operands": ["reg64", "i8"]           , "opcode": "000fba", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "bt"             , "operands": ["mem64", "i8"]           , "opcode": "000fba", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "btc"            , "operands": ["reg16", "reg16"]        , "opcode": "000fbb", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "btc"            , "operands": ["mem16", "reg16"]        , "opcode": "000fbb", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "btc"            , "operands": ["reg32", "reg32"]        , "opcode": "000fbb", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "btc"            , "operands": ["mem32", "reg32"]        , "opcode": "000fbb", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "btc"            , "operands": ["reg64", "reg64"]        , "opcode": "000fbb", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "btc"            , "operands": ["mem64", "reg64"]        , "opcode": "000fbb", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "btc"            , "operands": ["reg16", "i8"]           , "opcode": "000fba", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "btc"            , "operands": ["mem16", "i8"]           , "opcode": "000fba", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "btc"            , "operands": ["reg32", "i8"]           , "opcode": "000fba", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "btc"            , "operands": ["mem32", "i8"]           , "opcode": "000fba", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "btc"            , "operands": ["reg64", "i8"]           , "opcode": "000fba", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "btc"            , "operands": ["mem64", "i8"]           , "opcode": "000fba", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "btr"            , "operands": ["reg16", "reg16"]        , "opcode": "000fb3", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "btr"            , "operands": ["mem16", "reg16"]        , "opcode": "000fb3", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "btr"            , "operands": ["reg32", "reg32"]        , "opcode": "000fb3", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "btr"            , "operands": ["mem32", "reg32"]        , "opcode": "000fb3", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "btr"            , "operands": ["reg64", "reg64"]        , "opcode": "000fb3", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "btr"            , "operands": ["mem64", "reg64"]        , "opcode": "000fb3", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "btr"            , "operands": ["reg16", "i8"]           , "opcode": "000fba", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "btr"            , "operands": ["mem16", "i8"]           , "opcode": "000fba", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "btr"            , "operands": ["reg32", "i8"]           , "opcode": "000fba", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "btr"            , "operands": ["mem32", "i8"]           , "opcode": "000fba", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "btr"            , "operands": ["reg64", "i8"]           , "opcode": "000fba", "rm": "6", "w": "W1", "ri": false, "pp": ""     },
    { "name": "btr"            , "operands": ["mem64", "i8"]           , "opcode": "000fba", "rm": "6", "w": "W1", "ri": false, "pp": ""     },
    { "name": "bts"            , "operands": ["reg16", "reg16"]        , "opcode": "000fab", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bts"            , "operands": ["mem16", "reg16"]        , "opcode": "000fab", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bts"            , "operands": ["reg32", "reg32"]        , "opcode": "000fab", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bts"            , "operands": ["mem32", "reg32"]        , "opcode": "000fab", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bts"            , "operands": ["reg64", "reg64"]        , "opcode": "000fab", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "bts"            , "operands": ["mem64", "reg64"]        , "opcode": "000fab", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "bts"            , "operands": ["reg16", "i8"]           , "opcode": "000fba", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bts"            , "operands": ["mem16", "i8"]           , "opcode": "000fba", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bts"            , "operands": ["reg32", "i8"]           , "opcode": "000fba", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bts"            , "operands": ["mem32", "i8"]           , "opcode": "000fba", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "bts"            , "operands": ["reg64", "i8"]           , "opcode": "000fba", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "bts"            , "operands": ["mem64", "i8"]           , "opcode": "000fba", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmova"          , "operands": ["reg16", "reg16"]        , "opcode": "000f47", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmova"          , "operands": ["reg16", "mem16"]        , "opcode": "000f47", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmova"          , "operands": ["reg32", "reg32"]        , "opcode": "000f47", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmova"          , "operands": ["reg32", "mem32"]        , "opcode": "000f47", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmova"          , "operands": ["reg64", "reg64"]        , "opcode": "000f47", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmova"          , "operands": ["reg64", "mem64"]        , "opcode": "000f47", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovae"         , "operands": ["reg16", "reg16"]        , "opcode": "000f43", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovae"         , "operands": ["reg16", "mem16"]        , "opcode": "000f43", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovae"         , "operands": ["reg32", "reg32"]        , "opcode": "000f43", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovae"         , "operands": ["reg32", "mem32"]        , "opcode": "000f43", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovae"         , "operands": ["reg64", "reg64"]        , "opcode": "000f43", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovae"         , "operands": ["reg64", "mem64"]        , "opcode": "000f43", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovb"          , "operands": ["reg16", "reg16"]        , "opcode": "000f42", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovb"          , "operands": ["reg16", "mem16"]        , "opcode": "000f42", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovb"          , "operands": ["reg32", "reg32"]        , "opcode": "000f42", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovb"          , "operands": ["reg32", "mem32"]        , "opcode": "000f42", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovb"          , "operands": ["reg64", "reg64"]        , "opcode": "000f42", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovb"          , "operands": ["reg64", "mem64"]        , "opcode": "000f42", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovbe"         , "operands": ["reg16", "reg16"]        , "opcode": "000f46", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovbe"         , "operands": ["reg16", "mem16"]        , "opcode": "000f46", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovbe"         , "operands": ["reg32", "reg32"]        , "opcode": "000f46", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovbe"         , "operands": ["reg32", "mem32"]        , "opcode": "000f46", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovbe"         , "operands": ["reg64", "reg64"]        , "opcode": "000f46", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovbe"         , "operands": ["reg64", "mem64"]        , "opcode": "000f46", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovc"          , "operands": ["reg16", "reg16"]        , "opcode": "000f42", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovc"          , "operands": ["reg16", "mem16"]        , "opcode": "000f42", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovc"          , "operands": ["reg32", "reg32"]        , "opcode": "000f42", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovc"          , "operands": ["reg32", "mem32"]        , "opcode": "000f42", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovc"          , "operands": ["reg64", "reg64"]        , "opcode": "000f42", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovc"          , "operands": ["reg64", "mem64"]        , "opcode": "000f42", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmove"          , "operands": ["reg16", "reg16"]        , "opcode": "000f44", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmove"          , "operands": ["reg16", "mem16"]        , "opcode": "000f44", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmove"          , "operands": ["reg32", "reg32"]        , "opcode": "000f44", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmove"          , "operands": ["reg32", "mem32"]        , "opcode": "000f44", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmove"          , "operands": ["reg64", "reg64"]        , "opcode": "000f44", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmove"          , "operands": ["reg64", "mem64"]        , "opcode": "000f44", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovg"          , "operands": ["reg16", "reg16"]        , "opcode": "000f4f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovg"          , "operands": ["reg16", "mem16"]        , "opcode": "000f4f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovg"          , "operands": ["reg32", "reg32"]        , "opcode": "000f4f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovg"          , "operands": ["reg32", "mem32"]        , "opcode": "000f4f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovg"          , "operands": ["reg64", "reg64"]        , "opcode": "000f4f", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovg"          , "operands": ["reg64", "mem64"]        , "opcode": "000f4f", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovge"         , "operands": ["reg16", "reg16"]        , "opcode": "000f4d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovge"         , "operands": ["reg16", "mem16"]        , "opcode": "000f4d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovge"         , "operands": ["reg32", "reg32"]        , "opcode": "000f4d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovge"         , "operands": ["reg32", "mem32"]        , "opcode": "000f4d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovge"         , "operands": ["reg64", "reg64"]        , "opcode": "000f4d", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovge"         , "operands": ["reg64", "mem64"]        , "opcode": "000f4d", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovl"          , "operands": ["reg16", "reg16"]        , "opcode": "000f4c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovl"          , "operands": ["reg16", "mem16"]        , "opcode": "000f4c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovl"          , "operands": ["reg32", "reg32"]        , "opcode": "000f4c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovl"          , "operands": ["reg32", "mem32"]        , "opcode": "000f4c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovl"          , "operands": ["reg64", "reg64"]        , "opcode": "000f4c", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovl"          , "operands": ["reg64", "mem64"]        , "opcode": "000f4c", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovle"         , "operands": ["reg16", "reg16"]        , "opcode": "000f4e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovle"         , "operands": ["reg16", "mem16"]        , "opcode": "000f4e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovle"         , "operands": ["reg32", "reg32"]        , "opcode": "000f4e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovle"         , "operands": ["reg32", "mem32"]        , "opcode": "000f4e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovle"         , "operands": ["reg64", "reg64"]        , "opcode": "000f4e", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovle"         , "operands": ["reg64", "mem64"]        , "opcode": "000f4e", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovna"         , "operands": ["reg16", "reg16"]        , "opcode": "000f46", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovna"         , "operands": ["reg16", "mem16"]        , "opcode": "000f46", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovna"         , "operands": ["reg32", "reg32"]        , "opcode": "000f46", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovna"         , "operands": ["reg32", "mem32"]        , "opcode": "000f46", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovna"         , "operands": ["reg64", "reg64"]        , "opcode": "000f46", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovna"         , "operands": ["reg64", "mem64"]        , "opcode": "000f46", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnae"        , "operands": ["reg16", "reg16"]        , "opcode": "000f42", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnae"        , "operands": ["reg16", "mem16"]        , "opcode": "000f42", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnae"        , "operands": ["reg32", "reg32"]        , "opcode": "000f42", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnae"        , "operands": ["reg32", "mem32"]        , "opcode": "000f42", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnae"        , "operands": ["reg64", "reg64"]        , "opcode": "000f42", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnae"        , "operands": ["reg64", "mem64"]        , "opcode": "000f42", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnb"         , "operands": ["reg16", "reg16"]        , "opcode": "000f43", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnb"         , "operands": ["reg16", "mem16"]        , "opcode": "000f43", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnb"         , "operands": ["reg32", "reg32"]        , "opcode": "000f43", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnb"         , "operands": ["reg32", "mem32"]        , "opcode": "000f43", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnb"         , "operands": ["reg64", "reg64"]        , "opcode": "000f43", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnb"         , "operands": ["reg64", "mem64"]        , "opcode": "000f43", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnbe"        , "operands": ["reg16", "reg16"]        , "opcode": "000f47", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnbe"        , "operands": ["reg16", "mem16"]        , "opcode": "000f47", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnbe"        , "operands": ["reg32", "reg32"]        , "opcode": "000f47", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnbe"        , "operands": ["reg32", "mem32"]        , "opcode": "000f47", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnbe"        , "operands": ["reg64", "reg64"]        , "opcode": "000f47", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnbe"        , "operands": ["reg64", "mem64"]        , "opcode": "000f47", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnc"         , "operands": ["reg16", "reg16"]        , "opcode": "000f43", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnc"         , "operands": ["reg16", "mem16"]        , "opcode": "000f43", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnc"         , "operands": ["reg32", "reg32"]        , "opcode": "000f43", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnc"         , "operands": ["reg32", "mem32"]        , "opcode": "000f43", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnc"         , "operands": ["reg64", "reg64"]        , "opcode": "000f43", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnc"         , "operands": ["reg64", "mem64"]        , "opcode": "000f43", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovne"         , "operands": ["reg16", "reg16"]        , "opcode": "000f45", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovne"         , "operands": ["reg16", "mem16"]        , "opcode": "000f45", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovne"         , "operands": ["reg32", "reg32"]        , "opcode": "000f45", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovne"         , "operands": ["reg32", "mem32"]        , "opcode": "000f45", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovne"         , "operands": ["reg64", "reg64"]        , "opcode": "000f45", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovne"         , "operands": ["reg64", "mem64"]        , "opcode": "000f45", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovng"         , "operands": ["reg16", "reg16"]        , "opcode": "000f4e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovng"         , "operands": ["reg16", "mem16"]        , "opcode": "000f4e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovng"         , "operands": ["reg32", "reg32"]        , "opcode": "000f4e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovng"         , "operands": ["reg32", "mem32"]        , "opcode": "000f4e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovng"         , "operands": ["reg64", "reg64"]        , "opcode": "000f4e", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovng"         , "operands": ["reg64", "mem64"]        , "opcode": "000f4e", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnge"        , "operands": ["reg16", "reg16"]        , "opcode": "000f4c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnge"        , "operands": ["reg16", "mem16"]        , "opcode": "000f4c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnge"        , "operands": ["reg32", "reg32"]        , "opcode": "000f4c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnge"        , "operands": ["reg32", "mem32"]        , "opcode": "000f4c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnge"        , "operands": ["reg64", "reg64"]        , "opcode": "000f4c", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnge"        , "operands": ["reg64", "mem64"]        , "opcode": "000f4c", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnl"         , "operands": ["reg16", "reg16"]        , "opcode": "000f4d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnl"         , "operands": ["reg16", "mem16"]        , "opcode": "000f4d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnl"         , "operands": ["reg32", "reg32"]        , "opcode": "000f4d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnl"         , "operands": ["reg32", "mem32"]        , "opcode": "000f4d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnl"         , "operands": ["reg64", "reg64"]        , "opcode": "000f4d", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnl"         , "operands": ["reg64", "mem64"]        , "opcode": "000f4d", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnle"        , "operands": ["reg16", "reg16"]        , "opcode": "000f4f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnle"        , "operands": ["reg16", "mem16"]        , "opcode": "000f4f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnle"        , "operands": ["reg32", "reg32"]        , "opcode": "000f4f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnle"        , "operands": ["reg32", "mem32"]        , "opcode": "000f4f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnle"        , "operands": ["reg64", "reg64"]        , "opcode": "000f4f", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnle"        , "operands": ["reg64", "mem64"]        , "opcode": "000f4f", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovno"         , "operands": ["reg16", "reg16"]        , "opcode": "000f41", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovno"         , "operands": ["reg16", "mem16"]        , "opcode": "000f41", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovno"         , "operands": ["reg32", "reg32"]        , "opcode": "000f41", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovno"         , "operands": ["reg32", "mem32"]        , "opcode": "000f41", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovno"         , "operands": ["reg64", "reg64"]        , "opcode": "000f41", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovno"         , "operands": ["reg64", "mem64"]        , "opcode": "000f41", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnp"         , "operands": ["reg16", "reg16"]        , "opcode": "000f4b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnp"         , "operands": ["reg16", "mem16"]        , "opcode": "000f4b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnp"         , "operands": ["reg32", "reg32"]        , "opcode": "000f4b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnp"         , "operands": ["reg32", "mem32"]        , "opcode": "000f4b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnp"         , "operands": ["reg64", "reg64"]        , "opcode": "000f4b", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnp"         , "operands": ["reg64", "mem64"]        , "opcode": "000f4b", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovns"         , "operands": ["reg16", "reg16"]        , "opcode": "000f49", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovns"         , "operands": ["reg16", "mem16"]        , "opcode": "000f49", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovns"         , "operands": ["reg32", "reg32"]        , "opcode": "000f49", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovns"         , "operands": ["reg32", "mem32"]        , "opcode": "000f49", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovns"         , "operands": ["reg64", "reg64"]        , "opcode": "000f49", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovns"         , "operands": ["reg64", "mem64"]        , "opcode": "000f49", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnz"         , "operands": ["reg16", "reg16"]        , "opcode": "000f45", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnz"         , "operands": ["reg16", "mem16"]        , "opcode": "000f45", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovnz"         , "operands": ["reg32", "reg32"]        , "opcode": "000f45", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnz"         , "operands": ["reg32", "mem32"]        , "opcode": "000f45", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovnz"         , "operands": ["reg64", "reg64"]        , "opcode": "000f45", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovnz"         , "operands": ["reg64", "mem64"]        , "opcode": "000f45", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovo"          , "operands": ["reg16", "reg16"]        , "opcode": "000f40", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovo"          , "operands": ["reg16", "mem16"]        , "opcode": "000f40", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovo"          , "operands": ["reg32", "reg32"]        , "opcode": "000f40", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovo"          , "operands": ["reg32", "mem32"]        , "opcode": "000f40", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovo"          , "operands": ["reg64", "reg64"]        , "opcode": "000f40", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovo"          , "operands": ["reg64", "mem64"]        , "opcode": "000f40", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovp"          , "operands": ["reg16", "reg16"]        , "opcode": "000f4a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovp"          , "operands": ["reg16", "mem16"]        , "opcode": "000f4a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovp"          , "operands": ["reg32", "reg32"]        , "opcode": "000f4a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovp"          , "operands": ["reg32", "mem32"]        , "opcode": "000f4a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovp"          , "operands": ["reg64", "reg64"]        , "opcode": "000f4a", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovp"          , "operands": ["reg64", "mem64"]        , "opcode": "000f4a", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovpe"         , "operands": ["reg16", "reg16"]        , "opcode": "000f4a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovpe"         , "operands": ["reg16", "mem16"]        , "opcode": "000f4a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovpe"         , "operands": ["reg32", "reg32"]        , "opcode": "000f4a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovpe"         , "operands": ["reg32", "mem32"]        , "opcode": "000f4a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovpe"         , "operands": ["reg64", "reg64"]        , "opcode": "000f4a", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovpe"         , "operands": ["reg64", "mem64"]        , "opcode": "000f4a", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovpo"         , "operands": ["reg16", "reg16"]        , "opcode": "000f4b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovpo"         , "operands": ["reg16", "mem16"]        , "opcode": "000f4b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovpo"         , "operands": ["reg32", "reg32"]        , "opcode": "000f4b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovpo"         , "operands": ["reg32", "mem32"]        , "opcode": "000f4b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovpo"         , "operands": ["reg64", "reg64"]        , "opcode": "000f4b", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovpo"         , "operands": ["reg64", "mem64"]        , "opcode": "000f4b", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovs"          , "operands": ["reg16", "reg16"]        , "opcode": "000f48", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovs"          , "operands": ["reg16", "mem16"]        , "opcode": "000f48", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovs"          , "operands": ["reg32", "reg32"]        , "opcode": "000f48", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovs"          , "operands": ["reg32", "mem32"]        , "opcode": "000f48", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovs"          , "operands": ["reg64", "reg64"]        , "opcode": "000f48", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovs"          , "operands": ["reg64", "mem64"]        , "opcode": "000f48", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovz"          , "operands": ["reg16", "reg16"]        , "opcode": "000f44", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovz"          , "operands": ["reg16", "mem16"]        , "opcode": "000f44", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmovz"          , "operands": ["reg32", "reg32"]        , "opcode": "000f44", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovz"          , "operands": ["reg32", "mem32"]        , "opcode": "000f44", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmovz"          , "operands": ["reg64", "reg64"]        , "opcode": "000f44", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmovz"          , "operands": ["reg64", "mem64"]        , "opcode": "000f44", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["al", "i8"]              , "opcode": "00003c", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["ax", "i16"]             , "opcode": "00003d", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmp"            , "operands": ["eax", "i32"]            , "opcode": "00003d", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["rax", "i32"]            , "opcode": "00003d", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["reg8", "i8"]            , "opcode": "000080", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["mem8", "i8"]            , "opcode": "000080", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["reg16", "i16"]          , "opcode": "000081", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmp"            , "operands": ["mem16", "i16"]          , "opcode": "000081", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmp"            , "operands": ["reg32", "i32"]          , "opcode": "000081", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["mem32", "i32"]          , "opcode": "000081", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["reg64", "i32"]          , "opcode": "000081", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["mem64", "i32"]          , "opcode": "000081", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["reg16", "i8"]           , "opcode": "000083", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmp"            , "operands": ["mem16", "i8"]           , "opcode": "000083", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmp"            , "operands": ["reg32", "i8"]           , "opcode": "000083", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["mem32", "i8"]           , "opcode": "000083", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["reg64", "i8"]           , "opcode": "000083", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["mem64", "i8"]           , "opcode": "000083", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["reg8", "reg8"]          , "opcode": "000038", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["mem8", "reg8"]          , "opcode": "000038", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["reg16", "reg16"]        , "opcode": "000039", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmp"            , "operands": ["mem16", "reg16"]        , "opcode": "000039", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmp"            , "operands": ["reg32", "reg32"]        , "opcode": "000039", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["mem32", "reg32"]        , "opcode": "000039", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["reg64", "reg64"]        , "opcode": "000039", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["mem64", "reg64"]        , "opcode": "000039", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["reg8", "mem8"]          , "opcode": "00003a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["reg16", "mem16"]        , "opcode": "00003b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmp"            , "operands": ["reg32", "mem32"]        , "opcode": "00003b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmp"            , "operands": ["reg64", "mem64"]        , "opcode": "00003b", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmpxchg"        , "operands": ["reg8", "reg8"]          , "opcode": "000fb0", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmpxchg"        , "operands": ["mem8", "reg8"]          , "opcode": "000fb0", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmpxchg"        , "operands": ["reg16", "reg16"]        , "opcode": "000fb1", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmpxchg"        , "operands": ["mem16", "reg16"]        , "opcode": "000fb1", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmpxchg"        , "operands": ["reg32", "reg32"]        , "opcode": "000fb1", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmpxchg"        , "operands": ["mem32", "reg32"]        , "opcode": "000fb1", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmpxchg"        , "operands": ["reg64", "reg64"]        , "opcode": "000fb1", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmpxchg"        , "operands": ["mem64", "reg64"]        , "opcode": "000fb1", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "comisd"         , "operands": ["xmm", "xmm"]            , "opcode": "000f2f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "comisd"         , "operands": ["xmm", "mem64"]          , "opcode": "000f2f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "comiss"         , "operands": ["xmm", "xmm"]            , "opcode": "000f2f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "comiss"         , "operands": ["xmm", "mem32"]          , "opcode": "000f2f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "crc32"          , "operands": ["reg32", "reg8"]         , "opcode": "0f38f0", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "crc32"          , "operands": ["reg32", "mem8"]         , "opcode": "0f38f0", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "crc32"          , "operands": ["reg32", "reg16"]        , "opcode": "0f38f1", "rm": "r", "w": ""  , "ri": false, "pp": "66F2" },
    { "name": "crc32"          , "operands": ["reg32", "mem16"]        , "opcode": "0f38f1", "rm": "r", "w": ""  , "ri": false, "pp": "66F2" },
    { "name": "crc32"          , "operands": ["reg32", "reg32"]        , "opcode": "0f38f1", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "crc32"          , "operands": ["reg32", "mem32"]        , "opcode": "0f38f1", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "crc32"          , "operands": ["reg64", "reg8"]         , "opcode": "0f38f0", "rm": "r", "w": "W1", "ri": false, "pp": "F2"   },
    { "name": "crc32"          , "operands": ["reg64", "mem8"]         , "opcode": "0f38f0", "rm": "r", "w": "W1", "ri": false, "pp": "F2"   },
    { "name": "crc32"          , "operands": ["reg64", "reg64"]        , "opcode": "0f38f1", "rm": "r", "w": "W1", "ri": false, "pp": "F2"   },
    { "name": "crc32"          , "operands": ["reg64", "mem64"]        , "opcode": "0f38f1", "rm": "r", "w": "W1", "ri": false, "pp": "F2"   },
    { "name": "cvtdq2pd"       , "operands": ["xmm", "xmm"]            , "opcode": "000fe6", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cvtdq2pd"       , "operands": ["xmm", "mem64"]          , "opcode": "000fe6", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cvtdq2ps"       , "operands": ["xmm", "xmm"]            , "opcode": "000f5b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cvtdq2ps"       , "operands": ["xmm", "mem128"]         , "opcode": "000f5b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cvtpd2dq"       , "operands": ["xmm", "xmm"]            , "opcode": "000fe6", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "cvtpd2dq"       , "operands": ["xmm", "mem128"]         , "opcode": "000fe6", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "cvtpd2pi"       , "operands": ["mmx", "xmm"]            , "opcode": "000f2d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cvtpd2pi"       , "operands": ["mmx", "mem128"]         , "opcode": "000f2d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cvtpd2ps"       , "operands": ["xmm", "xmm"]            , "opcode": "000f5a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cvtpd2ps"       , "operands": ["xmm", "mem128"]         , "opcode": "000f5a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cvtpi2pd"       , "operands": ["xmm", "mmx"]            , "opcode": "000f2a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cvtpi2pd"       , "operands": ["xmm", "mem64"]          , "opcode": "000f2a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cvtpi2ps"       , "operands": ["xmm", "mmx"]            , "opcode": "000f2a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cvtpi2ps"       , "operands": ["xmm", "mem64"]          , "opcode": "000f2a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cvtps2dq"       , "operands": ["xmm", "xmm"]            , "opcode": "000f5b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cvtps2dq"       , "operands": ["xmm", "mem128"]         , "opcode": "000f5b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cvtps2pd"       , "operands": ["xmm", "xmm"]            , "opcode": "000f5a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cvtps2pd"       , "operands": ["xmm", "mem64"]          , "opcode": "000f5a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cvtps2pi"       , "operands": ["mmx", "xmm"]            , "opcode": "000f2d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cvtps2pi"       , "operands": ["mmx", "mem64"]          , "opcode": "000f2d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cvtsd2si"       , "operands": ["reg32", "xmm"]          , "opcode": "000f2d", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "cvtsd2si"       , "operands": ["reg32", "mem64"]        , "opcode": "000f2d", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "cvtsd2si"       , "operands": ["reg64", "xmm"]          , "opcode": "000f2d", "rm": "r", "w": "W1", "ri": false, "pp": "F2"   },
    { "name": "cvtsd2si"       , "operands": ["reg64", "mem64"]        , "opcode": "000f2d", "rm": "r", "w": "W1", "ri": false, "pp": "F2"   },
    { "name": "cvtsd2ss"       , "operands": ["xmm", "xmm"]            , "opcode": "000f5a", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "cvtsd2ss"       , "operands": ["xmm", "mem64"]          , "opcode": "000f5a", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "cvtsi2sd"       , "operands": ["xmm", "reg32"]          , "opcode": "000f2a", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "cvtsi2sd"       , "operands": ["xmm", "mem32"]          , "opcode": "000f2a", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "cvtsi2sd"       , "operands": ["xmm", "reg64"]          , "opcode": "000f2a", "rm": "r", "w": "W1", "ri": false, "pp": "F2"   },
    { "name": "cvtsi2sd"       , "operands": ["xmm", "mem64"]          , "opcode": "000f2a", "rm": "r", "w": "W1", "ri": false, "pp": "F2"   },
    { "name": "cvtsi2ss"       , "operands": ["xmm", "reg32"]          , "opcode": "000f2a", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cvtsi2ss"       , "operands": ["xmm", "mem32"]          , "opcode": "000f2a", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cvtsi2ss"       , "operands": ["xmm", "reg64"]          , "opcode": "000f2a", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "cvtsi2ss"       , "operands": ["xmm", "mem64"]          , "opcode": "000f2a", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "cvtss2sd"       , "operands": ["xmm", "xmm"]            , "opcode": "000f5a", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cvtss2sd"       , "operands": ["xmm", "mem32"]          , "opcode": "000f5a", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cvtss2si"       , "operands": ["reg32", "xmm"]          , "opcode": "000f2d", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cvtss2si"       , "operands": ["reg32", "mem32"]        , "opcode": "000f2d", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cvtss2si"       , "operands": ["reg64", "xmm"]          , "opcode": "000f2d", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "cvtss2si"       , "operands": ["reg64", "mem32"]        , "opcode": "000f2d", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "cvttpd2dq"      , "operands": ["xmm", "xmm"]            , "opcode": "000fe6", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cvttpd2dq"      , "operands": ["xmm", "mem128"]         , "opcode": "000fe6", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cvttpd2pi"      , "operands": ["mmx", "xmm"]            , "opcode": "000f2c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cvttpd2pi"      , "operands": ["mmx", "mem128"]         , "opcode": "000f2c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cvttps2dq"      , "operands": ["xmm", "xmm"]            , "opcode": "000f5b", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cvttps2dq"      , "operands": ["xmm", "mem128"]         , "opcode": "000f5b", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cvttps2pi"      , "operands": ["mmx", "xmm"]            , "opcode": "000f2c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cvttps2pi"      , "operands": ["mmx", "mem64"]          , "opcode": "000f2c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cvttsd2si"      , "operands": ["reg32", "xmm"]          , "opcode": "000f2c", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "cvttsd2si"      , "operands": ["reg32", "mem64"]        , "opcode": "000f2c", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "cvttsd2si"      , "operands": ["reg64", "xmm"]          , "opcode": "000f2c", "rm": "r", "w": "W1", "ri": false, "pp": "F2"   },
    { "name": "cvttsd2si"      , "operands": ["reg64", "mem64"]        , "opcode": "000f2c", "rm": "r", "w": "W1", "ri": false, "pp": "F2"   },
    { "name": "cvttss2si"      , "operands": ["reg32", "xmm"]          , "opcode": "000f2c", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cvttss2si"      , "operands": ["reg32", "mem32"]        , "opcode": "000f2c", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cvttss2si"      , "operands": ["reg64", "xmm"]          , "opcode": "000f2c", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "cvttss2si"      , "operands": ["reg64", "mem32"]        , "opcode": "000f2c", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "divpd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "divpd"          , "operands": ["xmm", "mem128"]         , "opcode": "000f5e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "divps"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "divps"          , "operands": ["xmm", "mem128"]         , "opcode": "000f5e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "divsd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5e", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "divsd"          , "operands": ["xmm", "mem64"]          , "opcode": "000f5e", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "divss"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5e", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "divss"          , "operands": ["xmm", "mem32"]          , "opcode": "000f5e", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "enter"          , "operands": ["i16", "i8"]             , "opcode": "0000c8", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "extrq"          , "operands": ["xmm", "xmm"]            , "opcode": "000f79", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "haddpd"         , "operands": ["xmm", "xmm"]            , "opcode": "000f7c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "haddpd"         , "operands": ["xmm", "mem128"]         , "opcode": "000f7c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "haddps"         , "operands": ["xmm", "xmm"]            , "opcode": "000f7c", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "haddps"         , "operands": ["xmm", "mem128"]         , "opcode": "000f7c", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "hsubpd"         , "operands": ["xmm", "xmm"]            , "opcode": "000f7d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "hsubpd"         , "operands": ["xmm", "mem128"]         , "opcode": "000f7d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "hsubps"         , "operands": ["xmm", "xmm"]            , "opcode": "000f7d", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "hsubps"         , "operands": ["xmm", "mem128"]         , "opcode": "000f7d", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "in"             , "operands": ["al", "i8"]              , "opcode": "0000e4", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "in"             , "operands": ["ax", "i8"]              , "opcode": "0000e5", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "in"             , "operands": ["eax", "i8"]             , "opcode": "0000e5", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "in"             , "operands": ["al", "dx"]              , "opcode": "0000ec", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "in"             , "operands": ["ax", "dx"]              , "opcode": "0000ed", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "in"             , "operands": ["eax", "dx"]             , "opcode": "0000ed", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "insertq"        , "operands": ["xmm", "xmm"]            , "opcode": "000f79", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "lddqu"          , "operands": ["xmm", "mem128"]         , "opcode": "000ff0", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "lea"            , "operands": ["reg16", "mem_address"]  , "opcode": "00008d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "lea"            , "operands": ["reg32", "mem_address"]  , "opcode": "00008d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "lea"            , "operands": ["reg64", "mem_address"]  , "opcode": "00008d", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "lzcnt"          , "operands": ["reg16", "reg16"]        , "opcode": "000fbd", "rm": "r", "w": ""  , "ri": false, "pp": "66F3" },
    { "name": "lzcnt"          , "operands": ["reg16", "mem16"]        , "opcode": "000fbd", "rm": "r", "w": ""  , "ri": false, "pp": "66F3" },
    { "name": "lzcnt"          , "operands": ["reg32", "reg32"]        , "opcode": "000fbd", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "lzcnt"          , "operands": ["reg32", "mem32"]        , "opcode": "000fbd", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "lzcnt"          , "operands": ["reg64", "reg64"]        , "opcode": "000fbd", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "lzcnt"          , "operands": ["reg64", "mem64"]        , "opcode": "000fbd", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "maskmovdqu"     , "operands": ["xmm", "xmm"]            , "opcode": "000ff7", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "maskmovq"       , "operands": ["mmx", "mmx"]            , "opcode": "000ff7", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "maxpd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "maxpd"          , "operands": ["xmm", "mem128"]         , "opcode": "000f5f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "maxps"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "maxps"          , "operands": ["xmm", "mem128"]         , "opcode": "000f5f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "maxsd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5f", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "maxsd"          , "operands": ["xmm", "mem64"]          , "opcode": "000f5f", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "maxss"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5f", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "maxss"          , "operands": ["xmm", "mem32"]          , "opcode": "000f5f", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "minpd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "minpd"          , "operands": ["xmm", "mem128"]         , "opcode": "000f5d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "minps"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "minps"          , "operands": ["xmm", "mem128"]         , "opcode": "000f5d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "minsd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5d", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "minsd"          , "operands": ["xmm", "mem64"]          , "opcode": "000f5d", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "minss"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5d", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "minss"          , "operands": ["xmm", "mem32"]          , "opcode": "000f5d", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "mov"            , "operands": ["reg8", "reg8"]          , "opcode": "000088", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["mem8", "reg8"]          , "opcode": "000088", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["reg16", "reg16"]        , "opcode": "000089", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "mov"            , "operands": ["mem16", "reg16"]        , "opcode": "000089", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "mov"            , "operands": ["reg32", "reg32"]        , "opcode": "000089", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["mem32", "reg32"]        , "opcode": "000089", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["reg64", "reg64"]        , "opcode": "000089", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["mem64", "reg64"]        , "opcode": "000089", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["reg8", "mem8"]          , "opcode": "00008a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["reg16", "mem16"]        , "opcode": "00008b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "mov"            , "operands": ["reg32", "mem32"]        , "opcode": "00008b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["reg64", "mem64"]        , "opcode": "00008b", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["reg16", "sreg"]         , "opcode": "00008c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["mem16", "sreg"]         , "opcode": "00008c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["reg32", "sreg"]         , "opcode": "00008c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["reg64", "sreg"]         , "opcode": "00008c", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["mem64", "sreg"]         , "opcode": "00008c", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["sreg", "reg16"]         , "opcode": "00008e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["sreg", "mem16"]         , "opcode": "00008e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["sreg", "reg32"]         , "opcode": "00008e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["sreg", "reg64"]         , "opcode": "00008e", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["sreg", "mem64"]         , "opcode": "00008e", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["al", "moff8"]           , "opcode": "0000a0", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["ax", "moff16"]          , "opcode": "0000a1", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "mov"            , "operands": ["eax", "moff32"]         , "opcode": "0000a1", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["rax", "moff64"]         , "opcode": "0000a1", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["moff8", "al"]           , "opcode": "0000a2", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["moff16", "ax"]          , "opcode": "0000a3", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "mov"            , "operands": ["moff32", "eax"]         , "opcode": "0000a3", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["moff64", "rax"]         , "opcode": "0000a3", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["reg8", "i8"]            , "opcode": "0000b0", "rm": "" , "w": ""  , "ri": true , "pp": ""     },
    { "name": "mov"            , "operands": ["reg16", "i16"]          , "opcode": "0000b8", "rm": "" , "w": ""  , "ri": true , "pp": "66"   },
    { "name": "mov"            , "operands": ["reg32", "i32"]          , "opcode": "0000b8", "rm": "" , "w": ""  , "ri": true , "pp": ""     },
    { "name": "mov"            , "operands": ["reg64", "i64"]          , "opcode": "0000b8", "rm": "" , "w": "W1", "ri": true , "pp": ""     },
    { "name": "mov"            , "operands": ["mem8", "i8"]            , "opcode": "0000c6", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["mem16", "i16"]          , "opcode": "0000c7", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "mov"            , "operands": ["mem32", "i32"]          , "opcode": "0000c7", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["reg64", "i32"]          , "opcode": "0000c7", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["mem64", "i32"]          , "opcode": "0000c7", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["reg64", "creg"]         , "opcode": "000f20", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["creg", "reg64"]         , "opcode": "000f22", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["reg64", "dreg"]         , "opcode": "000f21", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mov"            , "operands": ["dreg", "reg64"]         , "opcode": "000f23", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movapd"         , "operands": ["xmm", "xmm"]            , "opcode": "000f28", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movapd"         , "operands": ["xmm", "mem128"]         , "opcode": "000f28", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movapd"         , "operands": ["mem128", "xmm"]         , "opcode": "000f29", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movaps"         , "operands": ["xmm", "xmm"]            , "opcode": "000f28", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movaps"         , "operands": ["xmm", "mem128"]         , "opcode": "000f28", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movaps"         , "operands": ["mem128", "xmm"]         , "opcode": "000f29", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movbe"          , "operands": ["reg16", "mem16"]        , "opcode": "0f38f0", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movbe"          , "operands": ["reg32", "mem32"]        , "opcode": "0f38f0", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movbe"          , "operands": ["reg64", "mem64"]        , "opcode": "0f38f0", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "movbe"          , "operands": ["mem16", "reg16"]        , "opcode": "0f38f1", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movbe"          , "operands": ["mem32", "reg32"]        , "opcode": "0f38f1", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movbe"          , "operands": ["mem64", "reg64"]        , "opcode": "0f38f1", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "movq"           , "operands": ["reg64", "mmx"]          , "opcode": "000f7e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movd"           , "operands": ["reg32", "xmm"]          , "opcode": "000f7e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movd"           , "operands": ["mem32", "xmm"]          , "opcode": "000f7e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movq"           , "operands": ["reg64", "xmm"]          , "opcode": "000f7e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movd"           , "operands": ["xmm", "reg32"]          , "opcode": "000f6e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movd"           , "operands": ["xmm", "mem32"]          , "opcode": "000f6e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movq"           , "operands": ["xmm", "reg64"]          , "opcode": "000f6e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movddup"        , "operands": ["xmm", "xmm"]            , "opcode": "000f12", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "movddup"        , "operands": ["xmm", "mem64"]          , "opcode": "000f12", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "movdq2q"        , "operands": ["mmx", "xmm"]            , "opcode": "000fd6", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "movdqa"         , "operands": ["xmm", "xmm"]            , "opcode": "000f6f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movdqa"         , "operands": ["xmm", "mem128"]         , "opcode": "000f6f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movdqa"         , "operands": ["mem128", "xmm"]         , "opcode": "000f7f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movdqu"         , "operands": ["xmm", "xmm"]            , "opcode": "000f6f", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movdqu"         , "operands": ["xmm", "mem128"]         , "opcode": "000f6f", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movdqu"         , "operands": ["mem128", "xmm"]         , "opcode": "000f7f", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movhlps"        , "operands": ["xmm", "xmm"]            , "opcode": "000f12", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movhpd"         , "operands": ["mem64", "xmm"]          , "opcode": "000f17", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movhpd"         , "operands": ["xmm", "mem64"]          , "opcode": "000f16", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movhps"         , "operands": ["mem64", "xmm"]          , "opcode": "000f17", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movhps"         , "operands": ["xmm", "mem64"]          , "opcode": "000f16", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movlhps"        , "operands": ["xmm", "xmm"]            , "opcode": "000f16", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movlpd"         , "operands": ["mem64", "xmm"]          , "opcode": "000f13", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movlpd"         , "operands": ["xmm", "mem64"]          , "opcode": "000f12", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movlps"         , "operands": ["mem64", "xmm"]          , "opcode": "000f13", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movlps"         , "operands": ["xmm", "mem64"]          , "opcode": "000f12", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movmskpd"       , "operands": ["reg32", "xmm"]          , "opcode": "000f50", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movmskpd"       , "operands": ["reg64", "xmm"]          , "opcode": "000f50", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movmskps"       , "operands": ["reg32", "xmm"]          , "opcode": "000f50", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movmskps"       , "operands": ["reg64", "xmm"]          , "opcode": "000f50", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movntdq"        , "operands": ["mem128", "xmm"]         , "opcode": "000fe7", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movntdqa"       , "operands": ["xmm", "mem128"]         , "opcode": "0f382a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movnti"         , "operands": ["mem32", "reg32"]        , "opcode": "000fc3", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movnti"         , "operands": ["mem64", "reg64"]        , "opcode": "000fc3", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "movntpd"        , "operands": ["mem128", "xmm"]         , "opcode": "000f2b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movntps"        , "operands": ["mem128", "xmm"]         , "opcode": "000f2b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movntq"         , "operands": ["mem64", "mmx"]          , "opcode": "000fe7", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movntsd"        , "operands": ["mem64", "xmm"]          , "opcode": "000f2b", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "movntss"        , "operands": ["mem32", "xmm"]          , "opcode": "000f2b", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movq"           , "operands": ["mmx", "mmx"]            , "opcode": "000f6f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movq"           , "operands": ["mmx", "mem64"]          , "opcode": "000f6f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movq"           , "operands": ["mem64", "mmx"]          , "opcode": "000f7f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movq"           , "operands": ["mem64", "xmm"]          , "opcode": "000fd6", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movq"           , "operands": ["xmm", "mem64"]          , "opcode": "000f7e", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movq"           , "operands": ["xmm", "xmm"]            , "opcode": "000f7e", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movq2dq"        , "operands": ["xmm", "mmx"]            , "opcode": "000fd6", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movsd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f10", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "movsd"          , "operands": ["xmm", "mem64"]          , "opcode": "000f10", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "movsd"          , "operands": ["mem64", "xmm"]          , "opcode": "000f11", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "movshdup"       , "operands": ["xmm", "xmm"]            , "opcode": "000f16", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movshdup"       , "operands": ["xmm", "mem128"]         , "opcode": "000f16", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movsldup"       , "operands": ["xmm", "xmm"]            , "opcode": "000f12", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movsldup"       , "operands": ["xmm", "mem128"]         , "opcode": "000f12", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movss"          , "operands": ["xmm", "xmm"]            , "opcode": "000f10", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movss"          , "operands": ["xmm", "mem32"]          , "opcode": "000f10", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movss"          , "operands": ["mem32", "xmm"]          , "opcode": "000f11", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "movsx"          , "operands": ["reg16", "reg8"]         , "opcode": "000fbe", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movsx"          , "operands": ["reg16", "mem8"]         , "opcode": "000fbe", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movsx"          , "operands": ["reg32", "reg8"]         , "opcode": "000fbe", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movsx"          , "operands": ["reg32", "mem8"]         , "opcode": "000fbe", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movsx"          , "operands": ["reg64", "reg8"]         , "opcode": "000fbe", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "movsx"          , "operands": ["reg64", "mem8"]         , "opcode": "000fbe", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "movsx"          , "operands": ["reg32", "reg16"]        , "opcode": "000fbf", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movsx"          , "operands": ["reg32", "mem16"]        , "opcode": "000fbf", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movsx"          , "operands": ["reg64", "reg16"]        , "opcode": "000fbf", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "movsx"          , "operands": ["reg64", "mem16"]        , "opcode": "000fbf", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "movsxd"         , "operands": ["reg64", "reg32"]        , "opcode": "000063", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "movsxd"         , "operands": ["reg64", "mem32"]        , "opcode": "000063", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "movupd"         , "operands": ["xmm", "xmm"]            , "opcode": "000f10", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movupd"         , "operands": ["xmm", "mem128"]         , "opcode": "000f10", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movupd"         , "operands": ["mem128", "xmm"]         , "opcode": "000f11", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movups"         , "operands": ["xmm", "xmm"]            , "opcode": "000f10", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movups"         , "operands": ["xmm", "mem128"]         , "opcode": "000f10", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movups"         , "operands": ["mem128", "xmm"]         , "opcode": "000f11", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movzx"          , "operands": ["reg16", "reg8"]         , "opcode": "000fb6", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movzx"          , "operands": ["reg16", "mem8"]         , "opcode": "000fb6", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "movzx"          , "operands": ["reg32", "reg8"]         , "opcode": "000fb6", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movzx"          , "operands": ["reg32", "mem8"]         , "opcode": "000fb6", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movzx"          , "operands": ["reg64", "reg8"]         , "opcode": "000fb6", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "movzx"          , "operands": ["reg64", "mem8"]         , "opcode": "000fb6", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "movzx"          , "operands": ["reg32", "reg16"]        , "opcode": "000fb7", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movzx"          , "operands": ["reg32", "mem16"]        , "opcode": "000fb7", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movzx"          , "operands": ["reg64", "reg16"]        , "opcode": "000fb7", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "movzx"          , "operands": ["reg64", "mem16"]        , "opcode": "000fb7", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "mulpd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f59", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "mulpd"          , "operands": ["xmm", "mem128"]         , "opcode": "000f59", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "mulps"          , "operands": ["xmm", "xmm"]            , "opcode": "000f59", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mulps"          , "operands": ["xmm", "mem128"]         , "opcode": "000f59", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mulsd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f59", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "mulsd"          , "operands": ["xmm", "mem64"]          , "opcode": "000f59", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "mulss"          , "operands": ["xmm", "xmm"]            , "opcode": "000f59", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "mulss"          , "operands": ["xmm", "mem32"]          , "opcode": "000f59", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "or"             , "operands": ["al", "i8"]              , "opcode": "00000c", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["ax", "i16"]             , "opcode": "00000d", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "or"             , "operands": ["eax", "i32"]            , "opcode": "00000d", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["rax", "i32"]            , "opcode": "00000d", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["reg8", "i8"]            , "opcode": "000080", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["mem8", "i8"]            , "opcode": "000080", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["reg16", "i16"]          , "opcode": "000081", "rm": "1", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "or"             , "operands": ["mem16", "i16"]          , "opcode": "000081", "rm": "1", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "or"             , "operands": ["reg32", "i32"]          , "opcode": "000081", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["mem32", "i32"]          , "opcode": "000081", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["reg64", "i32"]          , "opcode": "000081", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["mem64", "i32"]          , "opcode": "000081", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["reg16", "i8"]           , "opcode": "000083", "rm": "1", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "or"             , "operands": ["mem16", "i8"]           , "opcode": "000083", "rm": "1", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "or"             , "operands": ["reg32", "i8"]           , "opcode": "000083", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["mem32", "i8"]           , "opcode": "000083", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["reg64", "i8"]           , "opcode": "000083", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["mem64", "i8"]           , "opcode": "000083", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["reg8", "reg8"]          , "opcode": "000008", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["mem8", "reg8"]          , "opcode": "000008", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["reg16", "reg16"]        , "opcode": "000009", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "or"             , "operands": ["mem16", "reg16"]        , "opcode": "000009", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "or"             , "operands": ["reg32", "reg32"]        , "opcode": "000009", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["mem32", "reg32"]        , "opcode": "000009", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["reg64", "reg64"]        , "opcode": "000009", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["mem64", "reg64"]        , "opcode": "000009", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["reg8", "mem8"]          , "opcode": "00000a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["reg16", "mem16"]        , "opcode": "00000b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "or"             , "operands": ["reg32", "mem32"]        , "opcode": "00000b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "or"             , "operands": ["reg64", "mem64"]        , "opcode": "00000b", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "orpd"           , "operands": ["xmm", "xmm"]            , "opcode": "000f56", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "orpd"           , "operands": ["xmm", "mem128"]         , "opcode": "000f56", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "orps"           , "operands": ["xmm", "xmm"]            , "opcode": "000f56", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "orps"           , "operands": ["xmm", "mem128"]         , "opcode": "000f56", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "out"            , "operands": ["i8", "al"]              , "opcode": "0000e6", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "out"            , "operands": ["i8", "ax"]              , "opcode": "0000e7", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "out"            , "operands": ["i8", "eax"]             , "opcode": "0000e7", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "out"            , "operands": ["dx", "al"]              , "opcode": "0000ee", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "out"            , "operands": ["dx", "ax"]              , "opcode": "0000ef", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "out"            , "operands": ["dx", "eax"]             , "opcode": "0000ef", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "pabsb"          , "operands": ["mmx", "mmx"]            , "opcode": "0f381c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pabsb"          , "operands": ["mmx", "mem64"]          , "opcode": "0f381c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pabsb"          , "operands": ["xmm", "xmm"]            , "opcode": "0f381c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pabsb"          , "operands": ["xmm", "mem128"]         , "opcode": "0f381c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pabsd"          , "operands": ["mmx", "mmx"]            , "opcode": "0f381e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pabsd"          , "operands": ["mmx", "mem64"]          , "opcode": "0f381e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pabsd"          , "operands": ["xmm", "xmm"]            , "opcode": "0f381e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pabsd"          , "operands": ["xmm", "mem128"]         , "opcode": "0f381e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pabsw"          , "operands": ["mmx", "mmx"]            , "opcode": "0f381d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pabsw"          , "operands": ["mmx", "mem64"]          , "opcode": "0f381d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pabsw"          , "operands": ["xmm", "xmm"]            , "opcode": "0f381d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pabsw"          , "operands": ["xmm", "mem128"]         , "opcode": "0f381d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "packssdw"       , "operands": ["mmx", "mmx"]            , "opcode": "000f6b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "packssdw"       , "operands": ["mmx", "mem64"]          , "opcode": "000f6b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "packssdw"       , "operands": ["xmm", "xmm"]            , "opcode": "000f6b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "packssdw"       , "operands": ["xmm", "mem128"]         , "opcode": "000f6b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "packsswb"       , "operands": ["mmx", "mmx"]            , "opcode": "000f63", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "packsswb"       , "operands": ["mmx", "mem64"]          , "opcode": "000f63", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "packsswb"       , "operands": ["xmm", "xmm"]            , "opcode": "000f63", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "packsswb"       , "operands": ["xmm", "mem128"]         , "opcode": "000f63", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "packusdw"       , "operands": ["xmm", "xmm"]            , "opcode": "0f382b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "packusdw"       , "operands": ["xmm", "mem128"]         , "opcode": "0f382b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "packuswb"       , "operands": ["mmx", "mmx"]            , "opcode": "000f67", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "packuswb"       , "operands": ["mmx", "mem64"]          , "opcode": "000f67", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "packuswb"       , "operands": ["xmm", "xmm"]            , "opcode": "000f67", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "packuswb"       , "operands": ["xmm", "mem128"]         , "opcode": "000f67", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddb"          , "operands": ["mmx", "mmx"]            , "opcode": "000ffc", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddb"          , "operands": ["mmx", "mem64"]          , "opcode": "000ffc", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddb"          , "operands": ["xmm", "xmm"]            , "opcode": "000ffc", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddb"          , "operands": ["xmm", "mem128"]         , "opcode": "000ffc", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddd"          , "operands": ["mmx", "mmx"]            , "opcode": "000ffe", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddd"          , "operands": ["mmx", "mem64"]          , "opcode": "000ffe", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddd"          , "operands": ["xmm", "xmm"]            , "opcode": "000ffe", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddd"          , "operands": ["xmm", "mem128"]         , "opcode": "000ffe", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddq"          , "operands": ["mmx", "mmx"]            , "opcode": "000fd4", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddq"          , "operands": ["mmx", "mem64"]          , "opcode": "000fd4", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddq"          , "operands": ["xmm", "xmm"]            , "opcode": "000fd4", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddq"          , "operands": ["xmm", "mem128"]         , "opcode": "000fd4", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddsb"         , "operands": ["mmx", "mmx"]            , "opcode": "000fec", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddsb"         , "operands": ["mmx", "mem64"]          , "opcode": "000fec", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddsb"         , "operands": ["xmm", "xmm"]            , "opcode": "000fec", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddsb"         , "operands": ["xmm", "mem128"]         , "opcode": "000fec", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddsw"         , "operands": ["mmx", "mmx"]            , "opcode": "000fed", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddsw"         , "operands": ["mmx", "mem64"]          , "opcode": "000fed", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddsw"         , "operands": ["xmm", "xmm"]            , "opcode": "000fed", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddsw"         , "operands": ["xmm", "mem128"]         , "opcode": "000fed", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddusb"        , "operands": ["mmx", "mmx"]            , "opcode": "000fdc", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddusb"        , "operands": ["mmx", "mem64"]          , "opcode": "000fdc", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddusb"        , "operands": ["xmm", "xmm"]            , "opcode": "000fdc", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddusb"        , "operands": ["xmm", "mem128"]         , "opcode": "000fdc", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddusw"        , "operands": ["mmx", "mmx"]            , "opcode": "000fdd", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddusw"        , "operands": ["mmx", "mem64"]          , "opcode": "000fdd", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddusw"        , "operands": ["xmm", "xmm"]            , "opcode": "000fdd", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddusw"        , "operands": ["xmm", "mem128"]         , "opcode": "000fdd", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddw"          , "operands": ["mmx", "mmx"]            , "opcode": "000ffd", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddw"          , "operands": ["mmx", "mem64"]          , "opcode": "000ffd", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "paddw"          , "operands": ["xmm", "xmm"]            , "opcode": "000ffd", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "paddw"          , "operands": ["xmm", "mem128"]         , "opcode": "000ffd", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pand"           , "operands": ["mmx", "mmx"]            , "opcode": "000fdb", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pand"           , "operands": ["mmx", "mem64"]          , "opcode": "000fdb", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pand"           , "operands": ["xmm", "xmm"]            , "opcode": "000fdb", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pand"           , "operands": ["xmm", "mem128"]         , "opcode": "000fdb", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pandn"          , "operands": ["mmx", "mmx"]            , "opcode": "000fdf", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pandn"          , "operands": ["mmx", "mem64"]          , "opcode": "000fdf", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pandn"          , "operands": ["xmm", "xmm"]            , "opcode": "000fdf", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pandn"          , "operands": ["xmm", "mem128"]         , "opcode": "000fdf", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pavgb"          , "operands": ["mmx", "mmx"]            , "opcode": "000fe0", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pavgb"          , "operands": ["mmx", "mem64"]          , "opcode": "000fe0", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pavgb"          , "operands": ["xmm", "xmm"]            , "opcode": "000fe0", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pavgb"          , "operands": ["xmm", "mem128"]         , "opcode": "000fe0", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pavgw"          , "operands": ["mmx", "mmx"]            , "opcode": "000fe3", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pavgw"          , "operands": ["mmx", "mem64"]          , "opcode": "000fe3", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pavgw"          , "operands": ["xmm", "xmm"]            , "opcode": "000fe3", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pavgw"          , "operands": ["xmm", "mem128"]         , "opcode": "000fe3", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pblendvb"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3810", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pblendvb"       , "operands": ["xmm", "mem128"]         , "opcode": "0f3810", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpeqb"        , "operands": ["mmx", "mmx"]            , "opcode": "000f74", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pcmpeqb"        , "operands": ["mmx", "mem64"]          , "opcode": "000f74", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pcmpeqb"        , "operands": ["xmm", "xmm"]            , "opcode": "000f74", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpeqb"        , "operands": ["xmm", "mem128"]         , "opcode": "000f74", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpeqd"        , "operands": ["mmx", "mmx"]            , "opcode": "000f76", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pcmpeqd"        , "operands": ["mmx", "mem64"]          , "opcode": "000f76", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pcmpeqd"        , "operands": ["xmm", "xmm"]            , "opcode": "000f76", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpeqd"        , "operands": ["xmm", "mem128"]         , "opcode": "000f76", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpeqq"        , "operands": ["xmm", "xmm"]            , "opcode": "0f3829", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpeqq"        , "operands": ["xmm", "mem128"]         , "opcode": "0f3829", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpeqw"        , "operands": ["mmx", "mmx"]            , "opcode": "000f75", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pcmpeqw"        , "operands": ["mmx", "mem64"]          , "opcode": "000f75", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pcmpeqw"        , "operands": ["xmm", "xmm"]            , "opcode": "000f75", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpeqw"        , "operands": ["xmm", "mem128"]         , "opcode": "000f75", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpgtb"        , "operands": ["mmx", "mmx"]            , "opcode": "000f64", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pcmpgtb"        , "operands": ["mmx", "mem64"]          , "opcode": "000f64", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pcmpgtb"        , "operands": ["xmm", "xmm"]            , "opcode": "000f64", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpgtb"        , "operands": ["xmm", "mem128"]         , "opcode": "000f64", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpgtd"        , "operands": ["mmx", "mmx"]            , "opcode": "000f66", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pcmpgtd"        , "operands": ["mmx", "mem64"]          , "opcode": "000f66", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pcmpgtd"        , "operands": ["xmm", "xmm"]            , "opcode": "000f66", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpgtd"        , "operands": ["xmm", "mem128"]         , "opcode": "000f66", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpgtq"        , "operands": ["xmm", "xmm"]            , "opcode": "0f3837", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpgtq"        , "operands": ["xmm", "mem128"]         , "opcode": "0f3837", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpgtw"        , "operands": ["mmx", "mmx"]            , "opcode": "000f65", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pcmpgtw"        , "operands": ["mmx", "mem64"]          , "opcode": "000f65", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pcmpgtw"        , "operands": ["xmm", "xmm"]            , "opcode": "000f65", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpgtw"        , "operands": ["xmm", "mem128"]         , "opcode": "000f65", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phaddd"         , "operands": ["mmx", "mmx"]            , "opcode": "0f3802", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "phaddd"         , "operands": ["mmx", "mem64"]          , "opcode": "0f3802", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "phaddd"         , "operands": ["xmm", "xmm"]            , "opcode": "0f3802", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phaddd"         , "operands": ["xmm", "mem128"]         , "opcode": "0f3802", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phaddsw"        , "operands": ["mmx", "mmx"]            , "opcode": "0f3803", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "phaddsw"        , "operands": ["mmx", "mem64"]          , "opcode": "0f3803", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "phaddsw"        , "operands": ["xmm", "xmm"]            , "opcode": "0f3803", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phaddsw"        , "operands": ["xmm", "mem128"]         , "opcode": "0f3803", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phaddw"         , "operands": ["mmx", "mmx"]            , "opcode": "0f3801", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "phaddw"         , "operands": ["mmx", "mem64"]          , "opcode": "0f3801", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "phaddw"         , "operands": ["xmm", "xmm"]            , "opcode": "0f3801", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phaddw"         , "operands": ["xmm", "mem128"]         , "opcode": "0f3801", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phminposuw"     , "operands": ["xmm", "xmm"]            , "opcode": "0f3841", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phminposuw"     , "operands": ["xmm", "mem128"]         , "opcode": "0f3841", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phsubd"         , "operands": ["mmx", "mmx"]            , "opcode": "0f3806", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "phsubd"         , "operands": ["mmx", "mem64"]          , "opcode": "0f3806", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "phsubd"         , "operands": ["xmm", "xmm"]            , "opcode": "0f3806", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phsubd"         , "operands": ["xmm", "mem128"]         , "opcode": "0f3806", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phsubsw"        , "operands": ["mmx", "mmx"]            , "opcode": "0f3807", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "phsubsw"        , "operands": ["mmx", "mem64"]          , "opcode": "0f3807", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "phsubsw"        , "operands": ["xmm", "xmm"]            , "opcode": "0f3807", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phsubsw"        , "operands": ["xmm", "mem128"]         , "opcode": "0f3807", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phsubw"         , "operands": ["mmx", "mmx"]            , "opcode": "0f3805", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "phsubw"         , "operands": ["mmx", "mem64"]          , "opcode": "0f3805", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "phsubw"         , "operands": ["xmm", "xmm"]            , "opcode": "0f3805", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "phsubw"         , "operands": ["xmm", "mem128"]         , "opcode": "0f3805", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaddubsw"      , "operands": ["mmx", "mmx"]            , "opcode": "0f3804", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmaddubsw"      , "operands": ["mmx", "mem64"]          , "opcode": "0f3804", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmaddubsw"      , "operands": ["xmm", "xmm"]            , "opcode": "0f3804", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaddubsw"      , "operands": ["xmm", "mem128"]         , "opcode": "0f3804", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaddwd"        , "operands": ["mmx", "mmx"]            , "opcode": "000ff5", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmaddwd"        , "operands": ["mmx", "mem64"]          , "opcode": "000ff5", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmaddwd"        , "operands": ["xmm", "xmm"]            , "opcode": "000ff5", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaddwd"        , "operands": ["xmm", "mem128"]         , "opcode": "000ff5", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaxsb"         , "operands": ["xmm", "xmm"]            , "opcode": "0f383c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaxsb"         , "operands": ["xmm", "mem128"]         , "opcode": "0f383c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaxsd"         , "operands": ["xmm", "xmm"]            , "opcode": "0f383d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaxsd"         , "operands": ["xmm", "mem128"]         , "opcode": "0f383d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaxsw"         , "operands": ["mmx", "mmx"]            , "opcode": "000fee", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmaxsw"         , "operands": ["mmx", "mem64"]          , "opcode": "000fee", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmaxsw"         , "operands": ["xmm", "xmm"]            , "opcode": "000fee", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaxsw"         , "operands": ["xmm", "mem128"]         , "opcode": "000fee", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaxub"         , "operands": ["mmx", "mmx"]            , "opcode": "000fde", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmaxub"         , "operands": ["mmx", "mem64"]          , "opcode": "000fde", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmaxub"         , "operands": ["xmm", "xmm"]            , "opcode": "000fde", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaxub"         , "operands": ["xmm", "mem128"]         , "opcode": "000fde", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaxud"         , "operands": ["xmm", "xmm"]            , "opcode": "0f383f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaxud"         , "operands": ["xmm", "mem128"]         , "opcode": "0f383f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaxuw"         , "operands": ["xmm", "xmm"]            , "opcode": "0f383e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmaxuw"         , "operands": ["xmm", "mem128"]         , "opcode": "0f383e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pminsb"         , "operands": ["xmm", "xmm"]            , "opcode": "0f3838", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pminsb"         , "operands": ["xmm", "mem128"]         , "opcode": "0f3838", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pminsd"         , "operands": ["xmm", "xmm"]            , "opcode": "0f3839", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pminsd"         , "operands": ["xmm", "mem128"]         , "opcode": "0f3839", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pminsw"         , "operands": ["mmx", "mmx"]            , "opcode": "000fea", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pminsw"         , "operands": ["mmx", "mem64"]          , "opcode": "000fea", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pminsw"         , "operands": ["xmm", "xmm"]            , "opcode": "000fea", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pminsw"         , "operands": ["xmm", "mem128"]         , "opcode": "000fea", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pminub"         , "operands": ["mmx", "mmx"]            , "opcode": "000fda", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pminub"         , "operands": ["mmx", "mem64"]          , "opcode": "000fda", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pminub"         , "operands": ["xmm", "xmm"]            , "opcode": "000fda", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pminub"         , "operands": ["xmm", "mem128"]         , "opcode": "000fda", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pminud"         , "operands": ["xmm", "xmm"]            , "opcode": "0f383b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pminud"         , "operands": ["xmm", "mem128"]         , "opcode": "0f383b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pminuw"         , "operands": ["xmm", "xmm"]            , "opcode": "0f383a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pminuw"         , "operands": ["xmm", "mem128"]         , "opcode": "0f383a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovmskb"       , "operands": ["reg32", "xmm"]          , "opcode": "000fd7", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmovsxbd"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3821", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovsxbd"       , "operands": ["xmm", "mem32"]          , "opcode": "0f3821", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovsxbq"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3822", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovsxbq"       , "operands": ["xmm", "mem16"]          , "opcode": "0f3822", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovsxbw"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3820", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovsxbw"       , "operands": ["xmm", "mem64"]          , "opcode": "0f3820", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovsxdq"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3825", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovsxdq"       , "operands": ["xmm", "mem64"]          , "opcode": "0f3825", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovsxwd"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3823", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovsxwd"       , "operands": ["xmm", "mem64"]          , "opcode": "0f3823", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovsxwq"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3824", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovsxwq"       , "operands": ["xmm", "mem32"]          , "opcode": "0f3824", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovzxbd"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3831", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovzxbd"       , "operands": ["xmm", "mem32"]          , "opcode": "0f3831", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovzxbq"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3832", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovzxbq"       , "operands": ["xmm", "mem16"]          , "opcode": "0f3832", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovzxbw"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3830", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovzxbw"       , "operands": ["xmm", "mem64"]          , "opcode": "0f3830", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovzxdq"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3835", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovzxdq"       , "operands": ["xmm", "mem64"]          , "opcode": "0f3835", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovzxwd"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3833", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovzxwd"       , "operands": ["xmm", "mem64"]          , "opcode": "0f3833", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovzxwq"       , "operands": ["xmm", "xmm"]            , "opcode": "0f3834", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmovzxwq"       , "operands": ["xmm", "mem32"]          , "opcode": "0f3834", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmuldq"         , "operands": ["xmm", "xmm"]            , "opcode": "0f3828", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmuldq"         , "operands": ["xmm", "mem128"]         , "opcode": "0f3828", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmulhrsw"       , "operands": ["mmx", "mmx"]            , "opcode": "0f380b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmulhrsw"       , "operands": ["mmx", "mem64"]          , "opcode": "0f380b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmulhrsw"       , "operands": ["xmm", "xmm"]            , "opcode": "0f380b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmulhrsw"       , "operands": ["xmm", "mem128"]         , "opcode": "0f380b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmulhuw"        , "operands": ["mmx", "mmx"]            , "opcode": "000fe4", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmulhuw"        , "operands": ["mmx", "mem64"]          , "opcode": "000fe4", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmulhuw"        , "operands": ["xmm", "xmm"]            , "opcode": "000fe4", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmulhuw"        , "operands": ["xmm", "mem128"]         , "opcode": "000fe4", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmulhw"         , "operands": ["mmx", "mmx"]            , "opcode": "000fe5", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmulhw"         , "operands": ["mmx", "mem64"]          , "opcode": "000fe5", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmulhw"         , "operands": ["xmm", "xmm"]            , "opcode": "000fe5", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmulhw"         , "operands": ["xmm", "mem128"]         , "opcode": "000fe5", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmulld"         , "operands": ["xmm", "xmm"]            , "opcode": "0f3840", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmulld"         , "operands": ["xmm", "mem128"]         , "opcode": "0f3840", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmullw"         , "operands": ["mmx", "mmx"]            , "opcode": "000fd5", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmullw"         , "operands": ["mmx", "mem64"]          , "opcode": "000fd5", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmullw"         , "operands": ["xmm", "xmm"]            , "opcode": "000fd5", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmullw"         , "operands": ["xmm", "mem128"]         , "opcode": "000fd5", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmuludq"        , "operands": ["mmx", "mmx"]            , "opcode": "000ff4", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pmuludq"        , "operands": ["xmm", "xmm"]            , "opcode": "000ff4", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pmuludq"        , "operands": ["xmm", "mem128"]         , "opcode": "000ff4", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "popcnt"         , "operands": ["reg16", "reg16"]        , "opcode": "000fb8", "rm": "r", "w": ""  , "ri": false, "pp": "66F3" },
    { "name": "popcnt"         , "operands": ["reg16", "mem16"]        , "opcode": "000fb8", "rm": "r", "w": ""  , "ri": false, "pp": "66F3" },
    { "name": "popcnt"         , "operands": ["reg32", "reg32"]        , "opcode": "000fb8", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "popcnt"         , "operands": ["reg32", "mem32"]        , "opcode": "000fb8", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "popcnt"         , "operands": ["reg64", "reg64"]        , "opcode": "000fb8", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "popcnt"         , "operands": ["reg64", "mem64"]        , "opcode": "000fb8", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "por"            , "operands": ["mmx", "mmx"]            , "opcode": "000feb", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "por"            , "operands": ["mmx", "mem64"]          , "opcode": "000feb", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "por"            , "operands": ["xmm", "xmm"]            , "opcode": "000feb", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "por"            , "operands": ["xmm", "mem128"]         , "opcode": "000feb", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psadbw"         , "operands": ["mmx", "mmx"]            , "opcode": "000ff6", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psadbw"         , "operands": ["mmx", "mem64"]          , "opcode": "000ff6", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psadbw"         , "operands": ["xmm", "xmm"]            , "opcode": "000ff6", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psadbw"         , "operands": ["xmm", "mem128"]         , "opcode": "000ff6", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pshufb"         , "operands": ["mmx", "mmx"]            , "opcode": "0f3800", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pshufb"         , "operands": ["mmx", "mem64"]          , "opcode": "0f3800", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pshufb"         , "operands": ["xmm", "xmm"]            , "opcode": "0f3800", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pshufb"         , "operands": ["xmm", "mem128"]         , "opcode": "0f3800", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psignb"         , "operands": ["mmx", "mmx"]            , "opcode": "0f3808", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psignb"         , "operands": ["mmx", "mem64"]          , "opcode": "0f3808", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psignb"         , "operands": ["xmm", "xmm"]            , "opcode": "0f3808", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psignb"         , "operands": ["xmm", "mem128"]         , "opcode": "0f3808", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psignd"         , "operands": ["mmx", "mmx"]            , "opcode": "0f380a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psignd"         , "operands": ["mmx", "mem64"]          , "opcode": "0f380a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psignd"         , "operands": ["xmm", "xmm"]            , "opcode": "0f380a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psignd"         , "operands": ["xmm", "mem128"]         , "opcode": "0f380a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psignw"         , "operands": ["mmx", "mmx"]            , "opcode": "0f3809", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psignw"         , "operands": ["mmx", "mem64"]          , "opcode": "0f3809", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psignw"         , "operands": ["xmm", "xmm"]            , "opcode": "0f3809", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psignw"         , "operands": ["xmm", "mem128"]         , "opcode": "0f3809", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pslld"          , "operands": ["mmx", "i8"]             , "opcode": "000f72", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pslld"          , "operands": ["mmx", "mmx"]            , "opcode": "000ff2", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pslld"          , "operands": ["mmx", "mem64"]          , "opcode": "000ff2", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pslld"          , "operands": ["xmm", "i8"]             , "opcode": "000f72", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pslld"          , "operands": ["xmm", "xmm"]            , "opcode": "000ff2", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pslld"          , "operands": ["xmm", "mem128"]         , "opcode": "000ff2", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pslldq"         , "operands": ["xmm", "i8"]             , "opcode": "000f73", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psllq"          , "operands": ["mmx", "i8"]             , "opcode": "000f73", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psllq"          , "operands": ["mmx", "mmx"]            , "opcode": "000ff3", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psllq"          , "operands": ["mmx", "mem64"]          , "opcode": "000ff3", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psllq"          , "operands": ["xmm", "i8"]             , "opcode": "000f73", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psllq"          , "operands": ["xmm", "xmm"]            , "opcode": "000ff3", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psllq"          , "operands": ["xmm", "mem128"]         , "opcode": "000ff3", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psllw"          , "operands": ["mmx", "i8"]             , "opcode": "000f71", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psllw"          , "operands": ["mmx", "mmx"]            , "opcode": "000ff1", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psllw"          , "operands": ["mmx", "mem64"]          , "opcode": "000ff1", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psllw"          , "operands": ["xmm", "i8"]             , "opcode": "000f71", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psllw"          , "operands": ["xmm", "xmm"]            , "opcode": "000ff1", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psllw"          , "operands": ["xmm", "mem128"]         , "opcode": "000ff1", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psrad"          , "operands": ["mmx", "i8"]             , "opcode": "000f72", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psrad"          , "operands": ["mmx", "mmx"]            , "opcode": "000fe2", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psrad"          , "operands": ["mmx", "mem64"]          , "opcode": "000fe2", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psrad"          , "operands": ["xmm", "i8"]             , "opcode": "000f72", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psrad"          , "operands": ["xmm", "xmm"]            , "opcode": "000fe2", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psrad"          , "operands": ["xmm", "mem128"]         , "opcode": "000fe2", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psraw"          , "operands": ["mmx", "i8"]             , "opcode": "000f71", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psraw"          , "operands": ["mmx", "mmx"]            , "opcode": "000fe1", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psraw"          , "operands": ["mmx", "mem64"]          , "opcode": "000fe1", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psraw"          , "operands": ["xmm", "i8"]             , "opcode": "000f71", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psraw"          , "operands": ["xmm", "xmm"]            , "opcode": "000fe1", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psraw"          , "operands": ["xmm", "mem128"]         , "opcode": "000fe1", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psrld"          , "operands": ["mmx", "i8"]             , "opcode": "000f72", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psrld"          , "operands": ["mmx", "mmx"]            , "opcode": "000fd2", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psrld"          , "operands": ["mmx", "mem64"]          , "opcode": "000fd2", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psrld"          , "operands": ["xmm", "i8"]             , "opcode": "000f72", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psrld"          , "operands": ["xmm", "xmm"]            , "opcode": "000fd2", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psrld"          , "operands": ["xmm", "mem128"]         , "opcode": "000fd2", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psrldq"         , "operands": ["xmm", "i8"]             , "opcode": "000f73", "rm": "3", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psrlq"          , "operands": ["mmx", "i8"]             , "opcode": "000f73", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psrlq"          , "operands": ["mmx", "mmx"]            , "opcode": "000fd3", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psrlq"          , "operands": ["mmx", "mem64"]          , "opcode": "000fd3", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psrlq"          , "operands": ["xmm", "i8"]             , "opcode": "000f73", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psrlq"          , "operands": ["xmm", "xmm"]            , "opcode": "000fd3", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psrlq"          , "operands": ["xmm", "mem128"]         , "opcode": "000fd3", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psrlw"          , "operands": ["mmx", "i8"]             , "opcode": "000f71", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psrlw"          , "operands": ["mmx", "mmx"]            , "opcode": "000fd1", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psrlw"          , "operands": ["mmx", "mem64"]          , "opcode": "000fd1", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psrlw"          , "operands": ["xmm", "i8"]             , "opcode": "000f71", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psrlw"          , "operands": ["xmm", "xmm"]            , "opcode": "000fd1", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psrlw"          , "operands": ["xmm", "mem128"]         , "opcode": "000fd1", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubb"          , "operands": ["mmx", "mmx"]            , "opcode": "000ff8", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubb"          , "operands": ["mmx", "mem64"]          , "opcode": "000ff8", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubb"          , "operands": ["xmm", "xmm"]            , "opcode": "000ff8", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubb"          , "operands": ["xmm", "mem128"]         , "opcode": "000ff8", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubd"          , "operands": ["mmx", "mmx"]            , "opcode": "000ffa", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubd"          , "operands": ["mmx", "mem64"]          , "opcode": "000ffa", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubd"          , "operands": ["xmm", "xmm"]            , "opcode": "000ffa", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubd"          , "operands": ["xmm", "mem128"]         , "opcode": "000ffa", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubq"          , "operands": ["mmx", "mmx"]            , "opcode": "000ffb", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubq"          , "operands": ["xmm", "xmm"]            , "opcode": "000ffb", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubq"          , "operands": ["xmm", "mem128"]         , "opcode": "000ffb", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubsb"         , "operands": ["mmx", "mmx"]            , "opcode": "000fe8", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubsb"         , "operands": ["mmx", "mem64"]          , "opcode": "000fe8", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubsb"         , "operands": ["xmm", "xmm"]            , "opcode": "000fe8", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubsb"         , "operands": ["xmm", "mem128"]         , "opcode": "000fe8", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubsw"         , "operands": ["mmx", "mmx"]            , "opcode": "000fe9", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubsw"         , "operands": ["mmx", "mem64"]          , "opcode": "000fe9", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubsw"         , "operands": ["xmm", "xmm"]            , "opcode": "000fe9", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubsw"         , "operands": ["xmm", "mem128"]         , "opcode": "000fe9", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubusb"        , "operands": ["mmx", "mmx"]            , "opcode": "000fd8", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubusb"        , "operands": ["mmx", "mem64"]          , "opcode": "000fd8", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubusb"        , "operands": ["xmm", "xmm"]            , "opcode": "000fd8", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubusb"        , "operands": ["xmm", "mem128"]         , "opcode": "000fd8", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubusw"        , "operands": ["mmx", "mmx"]            , "opcode": "000fd9", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubusw"        , "operands": ["mmx", "mem64"]          , "opcode": "000fd9", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubusw"        , "operands": ["xmm", "xmm"]            , "opcode": "000fd9", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubusw"        , "operands": ["xmm", "mem128"]         , "opcode": "000fd9", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubw"          , "operands": ["mmx", "mmx"]            , "opcode": "000ff9", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubw"          , "operands": ["mmx", "mem64"]          , "opcode": "000ff9", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "psubw"          , "operands": ["xmm", "xmm"]            , "opcode": "000ff9", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "psubw"          , "operands": ["xmm", "mem128"]         , "opcode": "000ff9", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "ptest"          , "operands": ["xmm", "xmm"]            , "opcode": "0f3817", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "ptest"          , "operands": ["xmm", "mem128"]         , "opcode": "0f3817", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpckhbw"      , "operands": ["mmx", "mmx"]            , "opcode": "000f68", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "punpckhbw"      , "operands": ["mmx", "mem64"]          , "opcode": "000f68", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "punpckhbw"      , "operands": ["xmm", "xmm"]            , "opcode": "000f68", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpckhbw"      , "operands": ["xmm", "mem128"]         , "opcode": "000f68", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpckhdq"      , "operands": ["mmx", "mmx"]            , "opcode": "000f6a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "punpckhdq"      , "operands": ["mmx", "mem64"]          , "opcode": "000f6a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "punpckhdq"      , "operands": ["xmm", "xmm"]            , "opcode": "000f6a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpckhdq"      , "operands": ["xmm", "mem128"]         , "opcode": "000f6a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpckhqdq"     , "operands": ["xmm", "xmm"]            , "opcode": "000f6d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpckhqdq"     , "operands": ["xmm", "mem128"]         , "opcode": "000f6d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpckhwd"      , "operands": ["mmx", "mmx"]            , "opcode": "000f69", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "punpckhwd"      , "operands": ["mmx", "mem64"]          , "opcode": "000f69", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "punpckhwd"      , "operands": ["xmm", "xmm"]            , "opcode": "000f69", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpckhwd"      , "operands": ["xmm", "mem128"]         , "opcode": "000f69", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpcklbw"      , "operands": ["mmx", "mmx"]            , "opcode": "000f60", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "punpcklbw"      , "operands": ["mmx", "mem64"]          , "opcode": "000f60", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "punpcklbw"      , "operands": ["xmm", "xmm"]            , "opcode": "000f60", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpcklbw"      , "operands": ["xmm", "mem128"]         , "opcode": "000f60", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpckldq"      , "operands": ["mmx", "mmx"]            , "opcode": "000f62", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "punpckldq"      , "operands": ["mmx", "mem64"]          , "opcode": "000f62", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "punpckldq"      , "operands": ["xmm", "xmm"]            , "opcode": "000f62", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpckldq"      , "operands": ["xmm", "mem128"]         , "opcode": "000f62", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpcklqdq"     , "operands": ["xmm", "xmm"]            , "opcode": "000f6c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpcklqdq"     , "operands": ["xmm", "mem128"]         , "opcode": "000f6c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpcklwd"      , "operands": ["mmx", "mmx"]            , "opcode": "000f61", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "punpcklwd"      , "operands": ["mmx", "mem64"]          , "opcode": "000f61", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "punpcklwd"      , "operands": ["xmm", "xmm"]            , "opcode": "000f61", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "punpcklwd"      , "operands": ["xmm", "mem128"]         , "opcode": "000f61", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pxor"           , "operands": ["mmx", "mmx"]            , "opcode": "000fef", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pxor"           , "operands": ["mmx", "mem64"]          , "opcode": "000fef", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pxor"           , "operands": ["xmm", "xmm"]            , "opcode": "000fef", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pxor"           , "operands": ["xmm", "mem128"]         , "opcode": "000fef", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rcl"            , "operands": ["reg8", "cl"]            , "opcode": "0000d2", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["mem8", "cl"]            , "opcode": "0000d2", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["reg16", "cl"]           , "opcode": "0000d3", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rcl"            , "operands": ["mem16", "cl"]           , "opcode": "0000d3", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rcl"            , "operands": ["reg16", "i8"]           , "opcode": "0000c1", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rcl"            , "operands": ["mem16", "i8"]           , "opcode": "0000c1", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rcl"            , "operands": ["reg32", "cl"]           , "opcode": "0000d3", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["mem32", "cl"]           , "opcode": "0000d3", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["reg32", "i8"]           , "opcode": "0000c1", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["mem32", "i8"]           , "opcode": "0000c1", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["reg64", "cl"]           , "opcode": "0000d3", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["mem64", "cl"]           , "opcode": "0000d3", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["reg64", "i8"]           , "opcode": "0000c1", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["mem64", "i8"]           , "opcode": "0000c1", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcpps"          , "operands": ["xmm", "xmm"]            , "opcode": "000f53", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcpps"          , "operands": ["xmm", "mem128"]         , "opcode": "000f53", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcpss"          , "operands": ["xmm", "xmm"]            , "opcode": "000f53", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "rcpss"          , "operands": ["xmm", "mem32"]          , "opcode": "000f53", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "rcr"            , "operands": ["reg8", "cl"]            , "opcode": "0000d2", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["mem8", "cl"]            , "opcode": "0000d2", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["reg16", "cl"]           , "opcode": "0000d3", "rm": "3", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rcr"            , "operands": ["mem16", "cl"]           , "opcode": "0000d3", "rm": "3", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rcr"            , "operands": ["reg16", "i8"]           , "opcode": "0000c1", "rm": "3", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rcr"            , "operands": ["mem16", "i8"]           , "opcode": "0000c1", "rm": "3", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rcr"            , "operands": ["reg32", "cl"]           , "opcode": "0000d3", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["mem32", "cl"]           , "opcode": "0000d3", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["reg32", "i8"]           , "opcode": "0000c1", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["mem32", "i8"]           , "opcode": "0000c1", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["reg64", "cl"]           , "opcode": "0000d3", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["mem64", "cl"]           , "opcode": "0000d3", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["reg64", "i8"]           , "opcode": "0000c1", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["mem64", "i8"]           , "opcode": "0000c1", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["reg8", "cl"]            , "opcode": "0000d2", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["mem8", "cl"]            , "opcode": "0000d2", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["reg16", "cl"]           , "opcode": "0000d3", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rol"            , "operands": ["mem16", "cl"]           , "opcode": "0000d3", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rol"            , "operands": ["reg16", "i8"]           , "opcode": "0000c1", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rol"            , "operands": ["mem16", "i8"]           , "opcode": "0000c1", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rol"            , "operands": ["reg32", "cl"]           , "opcode": "0000d3", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["mem32", "cl"]           , "opcode": "0000d3", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["reg32", "i8"]           , "opcode": "0000c1", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["mem32", "i8"]           , "opcode": "0000c1", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["reg64", "cl"]           , "opcode": "0000d3", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["mem64", "cl"]           , "opcode": "0000d3", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["reg64", "i8"]           , "opcode": "0000c1", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["mem64", "i8"]           , "opcode": "0000c1", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["reg8", "cl"]            , "opcode": "0000d2", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["mem8", "cl"]            , "opcode": "0000d2", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["reg16", "cl"]           , "opcode": "0000d3", "rm": "1", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "ror"            , "operands": ["mem16", "cl"]           , "opcode": "0000d3", "rm": "1", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "ror"            , "operands": ["reg16", "i8"]           , "opcode": "0000c1", "rm": "1", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "ror"            , "operands": ["mem16", "i8"]           , "opcode": "0000c1", "rm": "1", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "ror"            , "operands": ["reg32", "cl"]           , "opcode": "0000d3", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["mem32", "cl"]           , "opcode": "0000d3", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["reg32", "i8"]           , "opcode": "0000c1", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["mem32", "i8"]           , "opcode": "0000c1", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["reg64", "cl"]           , "opcode": "0000d3", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["mem64", "cl"]           , "opcode": "0000d3", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["reg64", "i8"]           , "opcode": "0000c1", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["mem64", "i8"]           , "opcode": "0000c1", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rsqrtps"        , "operands": ["xmm", "xmm"]            , "opcode": "000f52", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rsqrtps"        , "operands": ["xmm", "mem128"]         , "opcode": "000f52", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rsqrtss"        , "operands": ["xmm", "xmm"]            , "opcode": "000f52", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "rsqrtss"        , "operands": ["xmm", "mem32"]          , "opcode": "000f52", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "sal"            , "operands": ["reg8", "cl"]            , "opcode": "0000d2", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["mem8", "cl"]            , "opcode": "0000d2", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["reg16", "cl"]           , "opcode": "0000d3", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sal"            , "operands": ["mem16", "cl"]           , "opcode": "0000d3", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sal"            , "operands": ["reg16", "i8"]           , "opcode": "0000c1", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sal"            , "operands": ["mem16", "i8"]           , "opcode": "0000c1", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sal"            , "operands": ["reg32", "cl"]           , "opcode": "0000d3", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["mem32", "cl"]           , "opcode": "0000d3", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["reg32", "i8"]           , "opcode": "0000c1", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["mem32", "i8"]           , "opcode": "0000c1", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["reg64", "cl"]           , "opcode": "0000d3", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["mem64", "cl"]           , "opcode": "0000d3", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["reg64", "i8"]           , "opcode": "0000c1", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["mem64", "i8"]           , "opcode": "0000c1", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["reg8", "cl"]            , "opcode": "0000d2", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["mem8", "cl"]            , "opcode": "0000d2", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["reg16", "cl"]           , "opcode": "0000d3", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sar"            , "operands": ["mem16", "cl"]           , "opcode": "0000d3", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sar"            , "operands": ["reg16", "i8"]           , "opcode": "0000c1", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sar"            , "operands": ["mem16", "i8"]           , "opcode": "0000c1", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sar"            , "operands": ["reg32", "cl"]           , "opcode": "0000d3", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["mem32", "cl"]           , "opcode": "0000d3", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["reg32", "i8"]           , "opcode": "0000c1", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["mem32", "i8"]           , "opcode": "0000c1", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["reg64", "cl"]           , "opcode": "0000d3", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["mem64", "cl"]           , "opcode": "0000d3", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["reg64", "i8"]           , "opcode": "0000c1", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["mem64", "i8"]           , "opcode": "0000c1", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["al", "i8"]              , "opcode": "00001c", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["ax", "i16"]             , "opcode": "00001d", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sbb"            , "operands": ["eax", "i32"]            , "opcode": "00001d", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["rax", "i32"]            , "opcode": "00001d", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["reg8", "i8"]            , "opcode": "000080", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["mem8", "i8"]            , "opcode": "000080", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["reg16", "i16"]          , "opcode": "000081", "rm": "3", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sbb"            , "operands": ["mem16", "i16"]          , "opcode": "000081", "rm": "3", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sbb"            , "operands": ["reg32", "i32"]          , "opcode": "000081", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["mem32", "i32"]          , "opcode": "000081", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["reg64", "i32"]          , "opcode": "000081", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["mem64", "i32"]          , "opcode": "000081", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["reg16", "i8"]           , "opcode": "000083", "rm": "3", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sbb"            , "operands": ["mem16", "i8"]           , "opcode": "000083", "rm": "3", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sbb"            , "operands": ["reg32", "i8"]           , "opcode": "000083", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["mem32", "i8"]           , "opcode": "000083", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["reg64", "i8"]           , "opcode": "000083", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["mem64", "i8"]           , "opcode": "000083", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["reg8", "reg8"]          , "opcode": "000018", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["mem8", "reg8"]          , "opcode": "000018", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["reg16", "reg16"]        , "opcode": "000019", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sbb"            , "operands": ["mem16", "reg16"]        , "opcode": "000019", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sbb"            , "operands": ["reg32", "reg32"]        , "opcode": "000019", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["mem32", "reg32"]        , "opcode": "000019", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["reg64", "reg64"]        , "opcode": "000019", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["mem64", "reg64"]        , "opcode": "000019", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["reg8", "mem8"]          , "opcode": "00001a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["reg16", "mem16"]        , "opcode": "00001b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sbb"            , "operands": ["reg32", "mem32"]        , "opcode": "00001b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sbb"            , "operands": ["reg64", "mem64"]        , "opcode": "00001b", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sha1msg1"       , "operands": ["xmm", "xmm"]            , "opcode": "0f38c9", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sha1msg1"       , "operands": ["xmm", "mem128"]         , "opcode": "0f38c9", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sha1msg2"       , "operands": ["xmm", "xmm"]            , "opcode": "0f38ca", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sha1msg2"       , "operands": ["xmm", "mem128"]         , "opcode": "0f38ca", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sha1nexte"      , "operands": ["xmm", "xmm"]            , "opcode": "0f38c8", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sha1nexte"      , "operands": ["xmm", "mem128"]         , "opcode": "0f38c8", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sha256msg1"     , "operands": ["xmm", "xmm"]            , "opcode": "0f38cc", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sha256msg1"     , "operands": ["xmm", "mem128"]         , "opcode": "0f38cc", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sha256msg2"     , "operands": ["xmm", "xmm"]            , "opcode": "0f38cd", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sha256msg2"     , "operands": ["xmm", "mem128"]         , "opcode": "0f38cd", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sha256rnds2"    , "operands": ["xmm", "xmm"]            , "opcode": "0f38cb", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sha256rnds2"    , "operands": ["xmm", "mem128"]         , "opcode": "0f38cb", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["reg8", "cl"]            , "opcode": "0000d2", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["mem8", "cl"]            , "opcode": "0000d2", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["reg16", "cl"]           , "opcode": "0000d3", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shl"            , "operands": ["mem16", "cl"]           , "opcode": "0000d3", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shl"            , "operands": ["reg16", "i8"]           , "opcode": "0000c1", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shl"            , "operands": ["mem16", "i8"]           , "opcode": "0000c1", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shl"            , "operands": ["reg32", "cl"]           , "opcode": "0000d3", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["mem32", "cl"]           , "opcode": "0000d3", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["reg32", "i8"]           , "opcode": "0000c1", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["mem32", "i8"]           , "opcode": "0000c1", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["reg64", "cl"]           , "opcode": "0000d3", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["mem64", "cl"]           , "opcode": "0000d3", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["reg64", "i8"]           , "opcode": "0000c1", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["mem64", "i8"]           , "opcode": "0000c1", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["reg8", "cl"]            , "opcode": "0000d2", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["mem8", "cl"]            , "opcode": "0000d2", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["reg16", "cl"]           , "opcode": "0000d3", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shr"            , "operands": ["mem16", "cl"]           , "opcode": "0000d3", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shr"            , "operands": ["reg16", "i8"]           , "opcode": "0000c1", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shr"            , "operands": ["mem16", "i8"]           , "opcode": "0000c1", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shr"            , "operands": ["reg32", "cl"]           , "opcode": "0000d3", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["mem32", "cl"]           , "opcode": "0000d3", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["reg32", "i8"]           , "opcode": "0000c1", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["mem32", "i8"]           , "opcode": "0000c1", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["reg64", "cl"]           , "opcode": "0000d3", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["mem64", "cl"]           , "opcode": "0000d3", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["reg64", "i8"]           , "opcode": "0000c1", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["mem64", "i8"]           , "opcode": "0000c1", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sqrtpd"         , "operands": ["xmm", "xmm"]            , "opcode": "000f51", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sqrtpd"         , "operands": ["xmm", "mem128"]         , "opcode": "000f51", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sqrtps"         , "operands": ["xmm", "xmm"]            , "opcode": "000f51", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sqrtps"         , "operands": ["xmm", "mem128"]         , "opcode": "000f51", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sqrtsd"         , "operands": ["xmm", "xmm"]            , "opcode": "000f51", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "sqrtsd"         , "operands": ["xmm", "mem64"]          , "opcode": "000f51", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "sqrtss"         , "operands": ["xmm", "xmm"]            , "opcode": "000f51", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "sqrtss"         , "operands": ["xmm", "mem32"]          , "opcode": "000f51", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "sub"            , "operands": ["al", "i8"]              , "opcode": "00002c", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["ax", "i16"]             , "opcode": "00002d", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sub"            , "operands": ["eax", "i32"]            , "opcode": "00002d", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["rax", "i32"]            , "opcode": "00002d", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["reg8", "i8"]            , "opcode": "000080", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["mem8", "i8"]            , "opcode": "000080", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["reg16", "i16"]          , "opcode": "000081", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sub"            , "operands": ["mem16", "i16"]          , "opcode": "000081", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sub"            , "operands": ["reg32", "i32"]          , "opcode": "000081", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["mem32", "i32"]          , "opcode": "000081", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["reg64", "i32"]          , "opcode": "000081", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["mem64", "i32"]          , "opcode": "000081", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["reg16", "i8"]           , "opcode": "000083", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sub"            , "operands": ["mem16", "i8"]           , "opcode": "000083", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sub"            , "operands": ["reg32", "i8"]           , "opcode": "000083", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["mem32", "i8"]           , "opcode": "000083", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["reg64", "i8"]           , "opcode": "000083", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["mem64", "i8"]           , "opcode": "000083", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["reg8", "reg8"]          , "opcode": "000028", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["mem8", "reg8"]          , "opcode": "000028", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["reg16", "reg16"]        , "opcode": "000029", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sub"            , "operands": ["mem16", "reg16"]        , "opcode": "000029", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sub"            , "operands": ["reg32", "reg32"]        , "opcode": "000029", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["mem32", "reg32"]        , "opcode": "000029", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["reg64", "reg64"]        , "opcode": "000029", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["mem64", "reg64"]        , "opcode": "000029", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["reg8", "mem8"]          , "opcode": "00002a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["reg16", "mem16"]        , "opcode": "00002b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sub"            , "operands": ["reg32", "mem32"]        , "opcode": "00002b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sub"            , "operands": ["reg64", "mem64"]        , "opcode": "00002b", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "subpd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "subpd"          , "operands": ["xmm", "mem128"]         , "opcode": "000f5c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "subps"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "subps"          , "operands": ["xmm", "mem128"]         , "opcode": "000f5c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "subsd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5c", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "subsd"          , "operands": ["xmm", "mem64"]          , "opcode": "000f5c", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "subss"          , "operands": ["xmm", "xmm"]            , "opcode": "000f5c", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "subss"          , "operands": ["xmm", "mem32"]          , "opcode": "000f5c", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "test"           , "operands": ["al", "i8"]              , "opcode": "0000a8", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["ax", "i16"]             , "opcode": "0000a9", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "test"           , "operands": ["eax", "i32"]            , "opcode": "0000a9", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["rax", "i32"]            , "opcode": "0000a9", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["reg8", "i8"]            , "opcode": "0000f6", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["mem8", "i8"]            , "opcode": "0000f6", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["reg16", "i16"]          , "opcode": "0000f7", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "test"           , "operands": ["mem16", "i16"]          , "opcode": "0000f7", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "test"           , "operands": ["reg32", "i32"]          , "opcode": "0000f7", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["mem32", "i32"]          , "opcode": "0000f7", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["reg64", "i32"]          , "opcode": "0000f7", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["mem64", "i32"]          , "opcode": "0000f7", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["reg8", "reg8"]          , "opcode": "000084", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["mem8", "reg8"]          , "opcode": "000084", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["reg16", "reg16"]        , "opcode": "000085", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "test"           , "operands": ["mem16", "reg16"]        , "opcode": "000085", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "test"           , "operands": ["reg32", "reg32"]        , "opcode": "000085", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["mem32", "reg32"]        , "opcode": "000085", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["reg64", "reg64"]        , "opcode": "000085", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "test"           , "operands": ["mem64", "reg64"]        , "opcode": "000085", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "tzcnt"          , "operands": ["reg16", "reg16"]        , "opcode": "000fbc", "rm": "r", "w": ""  , "ri": false, "pp": "66F3" },
    { "name": "tzcnt"          , "operands": ["reg16", "mem16"]        , "opcode": "000fbc", "rm": "r", "w": ""  , "ri": false, "pp": "66F3" },
    { "name": "tzcnt"          , "operands": ["reg32", "reg32"]        , "opcode": "000fbc", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "tzcnt"          , "operands": ["reg32", "mem32"]        , "opcode": "000fbc", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "tzcnt"          , "operands": ["reg64", "reg64"]        , "opcode": "000fbc", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "tzcnt"          , "operands": ["reg64", "mem64"]        , "opcode": "000fbc", "rm": "r", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "ucomisd"        , "operands": ["xmm", "xmm"]            , "opcode": "000f2e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "ucomisd"        , "operands": ["xmm", "mem64"]          , "opcode": "000f2e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "ucomiss"        , "operands": ["xmm", "xmm"]            , "opcode": "000f2e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ucomiss"        , "operands": ["xmm", "mem32"]          , "opcode": "000f2e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "unpckhpd"       , "operands": ["xmm", "xmm"]            , "opcode": "000f15", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "unpckhpd"       , "operands": ["xmm", "mem128"]         , "opcode": "000f15", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "unpckhps"       , "operands": ["xmm", "xmm"]            , "opcode": "000f15", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "unpckhps"       , "operands": ["xmm", "mem128"]         , "opcode": "000f15", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "unpcklpd"       , "operands": ["xmm", "xmm"]            , "opcode": "000f14", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "unpcklpd"       , "operands": ["xmm", "mem128"]         , "opcode": "000f14", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "unpcklps"       , "operands": ["xmm", "xmm"]            , "opcode": "000f14", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "unpcklps"       , "operands": ["xmm", "mem128"]         , "opcode": "000f14", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xadd"           , "operands": ["reg8", "reg8"]          , "opcode": "000fc0", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xadd"           , "operands": ["mem8", "reg8"]          , "opcode": "000fc0", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xadd"           , "operands": ["reg16", "reg16"]        , "opcode": "000fc1", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xadd"           , "operands": ["mem16", "reg16"]        , "opcode": "000fc1", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xadd"           , "operands": ["reg32", "reg32"]        , "opcode": "000fc1", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xadd"           , "operands": ["mem32", "reg32"]        , "opcode": "000fc1", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xadd"           , "operands": ["reg64", "reg64"]        , "opcode": "000fc1", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xadd"           , "operands": ["mem64", "reg64"]        , "opcode": "000fc1", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xchg"           , "operands": ["ax", "reg16"]           , "opcode": "000090", "rm": "" , "w": ""  , "ri": true , "pp": "66"   },
    { "name": "xchg"           , "operands": ["eax", "reg32"]          , "opcode": "000090", "rm": "" , "w": ""  , "ri": true , "pp": ""     },
    { "name": "xchg"           , "operands": ["rax", "reg64"]          , "opcode": "000090", "rm": "" , "w": "W1", "ri": true , "pp": ""     },
    { "name": "xchg"           , "operands": ["reg16", "ax"]           , "opcode": "000090", "rm": "" , "w": ""  , "ri": true , "pp": "66"   },
    { "name": "xchg"           , "operands": ["reg32", "eax"]          , "opcode": "000090", "rm": "" , "w": ""  , "ri": true , "pp": ""     },
    { "name": "xchg"           , "operands": ["reg64", "rax"]          , "opcode": "000090", "rm": "" , "w": "W1", "ri": true , "pp": ""     },
    { "name": "xchg"           , "operands": ["reg8", "reg8"]          , "opcode": "000086", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xchg"           , "operands": ["mem8", "reg8"]          , "opcode": "000086", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xchg"           , "operands": ["reg16", "reg16"]        , "opcode": "000087", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xchg"           , "operands": ["mem16", "reg16"]        , "opcode": "000087", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xchg"           , "operands": ["reg32", "reg32"]        , "opcode": "000087", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xchg"           , "operands": ["mem32", "reg32"]        , "opcode": "000087", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xchg"           , "operands": ["reg64", "reg64"]        , "opcode": "000087", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xchg"           , "operands": ["mem64", "reg64"]        , "opcode": "000087", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xchg"           , "operands": ["reg8", "mem8"]          , "opcode": "000086", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xchg"           , "operands": ["reg16", "mem16"]        , "opcode": "000087", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xchg"           , "operands": ["reg32", "mem32"]        , "opcode": "000087", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xchg"           , "operands": ["reg64", "mem64"]        , "opcode": "000087", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["al", "i8"]              , "opcode": "000034", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["ax", "i16"]             , "opcode": "000035", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xor"            , "operands": ["eax", "i32"]            , "opcode": "000035", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["rax", "i32"]            , "opcode": "000035", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["reg8", "i8"]            , "opcode": "000080", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["mem8", "i8"]            , "opcode": "000080", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["reg16", "i16"]          , "opcode": "000081", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xor"            , "operands": ["mem16", "i16"]          , "opcode": "000081", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xor"            , "operands": ["reg32", "i32"]          , "opcode": "000081", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["mem32", "i32"]          , "opcode": "000081", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["reg64", "i32"]          , "opcode": "000081", "rm": "6", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["mem64", "i32"]          , "opcode": "000081", "rm": "6", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["reg16", "i8"]           , "opcode": "000083", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xor"            , "operands": ["mem16", "i8"]           , "opcode": "000083", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xor"            , "operands": ["reg32", "i8"]           , "opcode": "000083", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["mem32", "i8"]           , "opcode": "000083", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["reg64", "i8"]           , "opcode": "000083", "rm": "6", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["mem64", "i8"]           , "opcode": "000083", "rm": "6", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["reg8", "reg8"]          , "opcode": "000030", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["mem8", "reg8"]          , "opcode": "000030", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["reg16", "reg16"]        , "opcode": "000031", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xor"            , "operands": ["mem16", "reg16"]        , "opcode": "000031", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xor"            , "operands": ["reg32", "reg32"]        , "opcode": "000031", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["mem32", "reg32"]        , "opcode": "000031", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["reg64", "reg64"]        , "opcode": "000031", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["mem64", "reg64"]        , "opcode": "000031", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["reg8", "mem8"]          , "opcode": "000032", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["reg16", "mem16"]        , "opcode": "000033", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xor"            , "operands": ["reg32", "mem32"]        , "opcode": "000033", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xor"            , "operands": ["reg64", "mem64"]        , "opcode": "000033", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xorpd"          , "operands": ["xmm", "xmm"]            , "opcode": "000f57", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xorpd"          , "operands": ["xmm", "mem128"]         , "opcode": "000f57", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "xorps"          , "operands": ["xmm", "xmm"]            , "opcode": "000f57", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xorps"          , "operands": ["xmm", "mem128"]         , "opcode": "000f57", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "aeskeygenassist", "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3adf", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "aeskeygenassist", "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3adf", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "blendpd"        , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a0d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "blendpd"        , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a0d", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "blendps"        , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a0c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "blendps"        , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a0c", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "bswap"          , "operands": ["reg32"]                 , "opcode": "000fc8", "rm": "" , "w": ""  , "ri": true , "pp": ""     },
    { "name": "bswap"          , "operands": ["reg64"]                 , "opcode": "000fc8", "rm": "" , "w": "W1", "ri": true , "pp": ""     },
    { "name": "call"           , "operands": ["reg64"]                 , "opcode": "0000ff", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "call"           , "operands": ["mem64"]                 , "opcode": "0000ff", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cbw"            , "operands": []                        , "opcode": "000098", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cdq"            , "operands": []                        , "opcode": "000099", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "cdqe"           , "operands": []                        , "opcode": "000098", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "clac"           , "operands": []                        , "opcode": "0000ca", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "clc"            , "operands": []                        , "opcode": "0000f8", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "cld"            , "operands": []                        , "opcode": "0000fc", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "clflush"        , "operands": ["mem_address"]           , "opcode": "000fae", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "clflushopt"     , "operands": ["mem_address"]           , "opcode": "000fae", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "clwb"           , "operands": ["mem_address"]           , "opcode": "000fae", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "clzero"         , "operands": []                        , "opcode": "0000fc", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmc"            , "operands": []                        , "opcode": "0000f5", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmppd"          , "operands": ["xmm", "xmm", "i8"]      , "opcode": "000fc2", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmppd"          , "operands": ["xmm", "mem128", "i8"]   , "opcode": "000fc2", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmpps"          , "operands": ["xmm", "xmm", "i8"]      , "opcode": "000fc2", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmpps"          , "operands": ["xmm", "mem128", "i8"]   , "opcode": "000fc2", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmpsb"          , "operands": []                        , "opcode": "0000a6", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmpsd"          , "operands": []                        , "opcode": "0000a7", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "cmpsd"          , "operands": ["xmm", "xmm", "i8"]      , "opcode": "000fc2", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "cmpsd"          , "operands": ["xmm", "mem_address", "i8"]    , "opcode": "000fc2", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "cmpsq"          , "operands": []                        , "opcode": "0000a7", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmpss"          , "operands": ["xmm", "xmm", "i8"]      , "opcode": "000fc2", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cmpss"          , "operands": ["xmm", "mem32", "i8"]    , "opcode": "000fc2", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "cmpsw"          , "operands": []                        , "opcode": "0000a7", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cmpxchg16b"     , "operands": ["mem128"]                , "opcode": "000fc7", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "cmpxchg8b"      , "operands": ["mem64"]                 , "opcode": "000fc7", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "cpuid"          , "operands": []                        , "opcode": "000fa2", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "cqo"            , "operands": []                        , "opcode": "000099", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "cwd"            , "operands": []                        , "opcode": "000099", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "cwde"           , "operands": []                        , "opcode": "000098", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "dec"            , "operands": ["reg8"]                  , "opcode": "0000fe", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "dec"            , "operands": ["mem8"]                  , "opcode": "0000fe", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "dec"            , "operands": ["reg16"]                 , "opcode": "0000ff", "rm": "1", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "dec"            , "operands": ["mem16"]                 , "opcode": "0000ff", "rm": "1", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "dec"            , "operands": ["reg32"]                 , "opcode": "0000ff", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "dec"            , "operands": ["mem32"]                 , "opcode": "0000ff", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "dec"            , "operands": ["reg64"]                 , "opcode": "0000ff", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "dec"            , "operands": ["mem64"]                 , "opcode": "0000ff", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "div"            , "operands": ["reg8"]                  , "opcode": "0000f6", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "div"            , "operands": ["mem8"]                  , "opcode": "0000f6", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "div"            , "operands": ["reg16"]                 , "opcode": "0000f7", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "div"            , "operands": ["mem16"]                 , "opcode": "0000f7", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "div"            , "operands": ["reg32"]                 , "opcode": "0000f7", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "div"            , "operands": ["mem32"]                 , "opcode": "0000f7", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "div"            , "operands": ["reg64"]                 , "opcode": "0000f7", "rm": "6", "w": "W1", "ri": false, "pp": ""     },
    { "name": "div"            , "operands": ["mem64"]                 , "opcode": "0000f7", "rm": "6", "w": "W1", "ri": false, "pp": ""     },
    { "name": "dppd"           , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a41", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "dppd"           , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a41", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "dpps"           , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a40", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "dpps"           , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a40", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "emms"           , "operands": []                        , "opcode": "000f77", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "extractps"      , "operands": ["reg32", "xmm", "i8"]    , "opcode": "0f3a17", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "extractps"      , "operands": ["mem32", "xmm", "i8"]    , "opcode": "0f3a17", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "extractps"      , "operands": ["reg64", "xmm", "i8"]    , "opcode": "0f3a17", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "extrq"          , "operands": ["xmm", "i8", "i8"]       , "opcode": "000f78", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "extrq"          , "operands": ["xmm", "xmm"]            , "opcode": "000f79", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "femms"          , "operands": []                        , "opcode": "000f0e", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "fxrstor"        , "operands": ["mem_address"]           , "opcode": "000fae", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "fxrstor64"      , "operands": ["mem_address"]           , "opcode": "000fae", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "fxsave"         , "operands": ["mem_address"]           , "opcode": "000fae", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "fxsave64"       , "operands": ["mem_address"]           , "opcode": "000fae", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "idiv"           , "operands": ["reg8"]                  , "opcode": "0000f6", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "idiv"           , "operands": ["mem8"]                  , "opcode": "0000f6", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "idiv"           , "operands": ["reg16"]                 , "opcode": "0000f7", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "idiv"           , "operands": ["mem16"]                 , "opcode": "0000f7", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "idiv"           , "operands": ["reg32"]                 , "opcode": "0000f7", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "idiv"           , "operands": ["mem32"]                 , "opcode": "0000f7", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "idiv"           , "operands": ["reg64"]                 , "opcode": "0000f7", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "idiv"           , "operands": ["mem64"]                 , "opcode": "0000f7", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
   
    { "name": "imul"           , "operands": ["reg8"]                  , "opcode": "0000f6", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "imul"           , "operands": ["mem8"]                  , "opcode": "0000f6", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    
    { "name": "imul"           , "operands": ["reg16"]                 , "opcode": "0000f7", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "imul"           , "operands": ["mem16"]                 , "opcode": "0000f7", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
   
    { "name": "imul"           , "operands": ["reg32"]                 , "opcode": "0000f7", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "imul"           , "operands": ["mem32"]                 , "opcode": "0000f7", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    
    { "name": "imul"           , "operands": ["reg64"]                 , "opcode": "0000f7", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "imul"           , "operands": ["mem64"]                 , "opcode": "0000f7", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    
    { "name": "imul"           , "operands": ["reg16", "reg16"]                 , "opcode": "0000f7", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "imul"           , "operands": ["reg16", "mem16"]                 , "opcode": "0000f7", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "imul"           , "operands": ["reg32", "reg32"]                 , "opcode": "0000f7", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "imul"           , "operands": ["reg32", "mem32"]                 , "opcode": "0000f7", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "imul"           , "operands": ["reg64", "reg64"]                 , "opcode": "0000f7", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "imul"           , "operands": ["reg64", "mem64"]                 , "opcode": "0000f7", "rm": "5", "w": "W1", "ri": false, "pp": ""     },


    { "name": "imul"           , "operands": ["reg16", "reg16", "i8"]  , "opcode": "00006b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "imul"           , "operands": ["reg16", "mem16", "i8"]  , "opcode": "00006b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    
    { "name": "imul"           , "operands": ["reg32", "reg32", "i8"]  , "opcode": "00006b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "imul"           , "operands": ["reg32", "mem32", "i8"]  , "opcode": "00006b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
   
    { "name": "imul"           , "operands": ["reg64", "reg64", "i8"]  , "opcode": "00006b", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "imul"           , "operands": ["reg64", "mem64", "i8"]  , "opcode": "00006b", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    
    { "name": "imul"           , "operands": ["reg16", "reg16", "i16"] , "opcode": "000069", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "imul"           , "operands": ["reg16", "mem16", "i16"] , "opcode": "000069", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    
    { "name": "imul"           , "operands": ["reg32", "reg32", "i32"] , "opcode": "000069", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "imul"           , "operands": ["reg32", "mem32", "i32"] , "opcode": "000069", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    
    { "name": "imul"           , "operands": ["reg64", "reg64", "i32"] , "opcode": "000069", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "imul"           , "operands": ["reg64", "mem64", "i32"] , "opcode": "000069", "rm": "r", "w": "W1", "ri": false, "pp": ""     },

    { "name": "inc"            , "operands": ["reg8"]                  , "opcode": "0000fe", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "inc"            , "operands": ["mem8"]                  , "opcode": "0000fe", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "inc"            , "operands": ["reg16"]                 , "opcode": "0000ff", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "inc"            , "operands": ["mem16"]                 , "opcode": "0000ff", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "inc"            , "operands": ["reg32"]                 , "opcode": "0000ff", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "inc"            , "operands": ["mem32"]                 , "opcode": "0000ff", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "inc"            , "operands": ["reg64"]                 , "opcode": "0000ff", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "inc"            , "operands": ["mem64"]                 , "opcode": "0000ff", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "insb"           , "operands": []                        , "opcode": "00006c", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "insd"           , "operands": []                        , "opcode": "00006d", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "insertps"       , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a21", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "insertps"       , "operands": ["xmm", "mem32", "i8"]    , "opcode": "0f3a21", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "insertq"        , "operands": ["xmm", "xmm", "i8", "i8"], "opcode": "000f78", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "insertq"        , "operands": ["xmm", "xmm"]            , "opcode": "000f79", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "insw"           , "operands": []                        , "opcode": "00006d", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "int"            , "operands": ["i8"]                    , "opcode": "0000cd", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "int3"           , "operands": []                        , "opcode": "0000cc", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "ja"             , "operands": ["rel8"]                  , "opcode": "000077", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jae"            , "operands": ["rel8"]                  , "opcode": "000073", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jb"             , "operands": ["rel8"]                  , "opcode": "000072", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jbe"            , "operands": ["rel8"]                  , "opcode": "000076", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jc"             , "operands": ["rel8"]                  , "opcode": "000072", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "je"             , "operands": ["rel8"]                  , "opcode": "000074", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jecxz"          , "operands": ["rel8"]                        , "opcode": "0000e3", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jg"             , "operands": ["rel8"]                  , "opcode": "00007f", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jge"            , "operands": ["rel8"]                  , "opcode": "00007d", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jl"             , "operands": ["rel8"]                  , "opcode": "00007c", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jle"            , "operands": ["rel8"]                  , "opcode": "00007e", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jmp"            , "operands": ["rel8"]                  , "opcode": "0000eb", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "jmp"            , "operands": ["reg64"]                 , "opcode": "0000ff", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "jmp"            , "operands": ["mem64"]                 , "opcode": "0000ff", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jna"            , "operands": ["rel8"]                  , "opcode": "000076", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jnae"           , "operands": ["rel8"]                  , "opcode": "000072", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jnb"            , "operands": ["rel8"]                  , "opcode": "000073", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jnbe"           , "operands": ["rel8"]                  , "opcode": "000077", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jnc"            , "operands": ["rel8"]                  , "opcode": "000073", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jne"            , "operands": ["rel8"]                  , "opcode": "000075", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jng"            , "operands": ["rel8"]                  , "opcode": "00007e", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jnge"           , "operands": ["rel8"]                  , "opcode": "00007c", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jnl"            , "operands": ["rel8"]                  , "opcode": "00007d", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jnle"           , "operands": ["rel8"]                  , "opcode": "00007f", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jno"            , "operands": ["rel8"]                  , "opcode": "000071", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jnp"            , "operands": ["rel8"]                  , "opcode": "00007b", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jns"            , "operands": ["rel8"]                  , "opcode": "000079", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jnz"            , "operands": ["rel8"]                  , "opcode": "000075", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jo"             , "operands": ["rel8"]                  , "opcode": "000070", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jp"             , "operands": ["rel8"]                  , "opcode": "00007a", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jpe"            , "operands": ["rel8"]                  , "opcode": "00007a", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jpo"            , "operands": ["rel8"]                  , "opcode": "00007b", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "js"             , "operands": ["rel8"]                  , "opcode": "000078", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "jz"             , "operands": ["rel8"]                  , "opcode": "000074", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "lahf"           , "operands": []                        , "opcode": "00009f", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "ldmxcsr"        , "operands": ["mem32"]                 , "opcode": "000fae", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "leave"          , "operands": []                        , "opcode": "0000c9", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "lfence"         , "operands": []                        , "opcode": "000fae", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "lodsb"          , "operands": []                        , "opcode": "0000ac", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "lodsd"          , "operands": []                        , "opcode": "0000ad", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "lodsq"          , "operands": []                        , "opcode": "0000ad", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "lodsw"          , "operands": []                        , "opcode": "0000ad", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    // { "name": "loop"           , "operands": ["rel8"]                  , "opcode": "0000e2", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "loope"          , "operands": ["rel8"]                  , "opcode": "0000e1", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    // { "name": "loopne"         , "operands": ["rel8"]                  , "opcode": "0000e0", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "mfence"         , "operands": []                        , "opcode": "000fae", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "movsb"          , "operands": []                        , "opcode": "0000a4", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "movsq"          , "operands": []                        , "opcode": "0000a5", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "movsw"          , "operands": []                        , "opcode": "0000a5", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "mpsadbw"        , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a42", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "mpsadbw"        , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a42", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "mul"            , "operands": ["reg8"]                  , "opcode": "0000f6", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mul"            , "operands": ["mem8"]                  , "opcode": "0000f6", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mul"            , "operands": ["reg16"]                 , "opcode": "0000f7", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "mul"            , "operands": ["mem16"]                 , "opcode": "0000f7", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "mul"            , "operands": ["reg32"]                 , "opcode": "0000f7", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mul"            , "operands": ["mem32"]                 , "opcode": "0000f7", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "mul"            , "operands": ["reg64"]                 , "opcode": "0000f7", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "mul"            , "operands": ["mem64"]                 , "opcode": "0000f7", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "neg"            , "operands": ["reg8"]                  , "opcode": "0000f6", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "neg"            , "operands": ["mem8"]                  , "opcode": "0000f6", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "neg"            , "operands": ["reg16"]                 , "opcode": "0000f7", "rm": "3", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "neg"            , "operands": ["mem16"]                 , "opcode": "0000f7", "rm": "3", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "neg"            , "operands": ["reg32"]                 , "opcode": "0000f7", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "neg"            , "operands": ["mem32"]                 , "opcode": "0000f7", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "neg"            , "operands": ["reg64"]                 , "opcode": "0000f7", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "neg"            , "operands": ["mem64"]                 , "opcode": "0000f7", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "nop"            , "operands": []                        , "opcode": "000090", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "nop"            , "operands": ["reg16"]                 , "opcode": "000f1f", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "nop"            , "operands": ["mem16"]                 , "opcode": "000f1f", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "nop"            , "operands": ["reg32"]                 , "opcode": "000f1f", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "nop"            , "operands": ["mem32"]                 , "opcode": "000f1f", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "not"            , "operands": ["reg8"]                  , "opcode": "0000f6", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "not"            , "operands": ["mem8"]                  , "opcode": "0000f6", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "not"            , "operands": ["reg16"]                 , "opcode": "0000f7", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "not"            , "operands": ["mem16"]                 , "opcode": "0000f7", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "not"            , "operands": ["reg32"]                 , "opcode": "0000f7", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "not"            , "operands": ["mem32"]                 , "opcode": "0000f7", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "not"            , "operands": ["reg64"]                 , "opcode": "0000f7", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "not"            , "operands": ["mem64"]                 , "opcode": "0000f7", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "outsb"          , "operands": []                        , "opcode": "00006e", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "outsd"          , "operands": []                        , "opcode": "00006f", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "outsw"          , "operands": []                        , "opcode": "00006f", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "palignr"        , "operands": ["mmx", "mmx", "i8"]      , "opcode": "0f3a0f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "palignr"        , "operands": ["mmx", "mem64", "i8"]    , "opcode": "0f3a0f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "palignr"        , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a0f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "palignr"        , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a0f", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pause"          , "operands": []                        , "opcode": "000090", "rm": "" , "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "pblendw"        , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a0e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pblendw"        , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a0e", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pclmulqdq"      , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a44", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pclmulqdq"      , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a44", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpestri"      , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a61", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpestri"      , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a61", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpestrm"      , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a60", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpestrm"      , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a60", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpistri"      , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a63", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpistri"      , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a63", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpistrm"      , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a62", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pcmpistrm"      , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a62", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pextrb"         , "operands": ["reg32", "xmm", "i8"]     , "opcode": "0f3a14", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pextrb"         , "operands": ["mem8", "xmm", "i8"]     , "opcode": "0f3a14", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pextrd"         , "operands": ["reg32", "xmm", "i8"]    , "opcode": "0f3a16", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pextrd"         , "operands": ["mem32", "xmm", "i8"]    , "opcode": "0f3a16", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pextrq"         , "operands": ["reg64", "xmm", "i8"]    , "opcode": "0f3a16", "rm": "r", "w": "W1", "ri": false, "pp": "66"   },
    { "name": "pextrq"         , "operands": ["mem64", "xmm", "i8"]    , "opcode": "0f3a16", "rm": "r", "w": "W1", "ri": false, "pp": "66"   },
    { "name": "pextrw"         , "operands": ["reg32", "mmx", "i8"]    , "opcode": "000fc5", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pextrw"         , "operands": ["reg32", "xmm", "i8"]    , "opcode": "000fc5", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pextrw"         , "operands": ["reg32", "xmm", "i8"]    , "opcode": "0f3a15", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pextrw"         , "operands": ["mem16", "xmm", "i8"]    , "opcode": "0f3a15", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pinsrb"         , "operands": ["xmm", "reg32", "i8"]    , "opcode": "0f3a20", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pinsrb"         , "operands": ["xmm", "mem8", "i8"]     , "opcode": "0f3a20", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pinsrd"         , "operands": ["xmm", "reg32", "i8"]    , "opcode": "0f3a22", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pinsrd"         , "operands": ["xmm", "mem32", "i8"]    , "opcode": "0f3a22", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pinsrq"         , "operands": ["xmm", "reg64", "i8"]    , "opcode": "0f3a22", "rm": "r", "w": "W1", "ri": false, "pp": "66"   },
    { "name": "pinsrq"         , "operands": ["xmm", "mem64", "i8"]    , "opcode": "0f3a22", "rm": "r", "w": "W1", "ri": false, "pp": "66"   },
    { "name": "pinsrw"         , "operands": ["mmx", "reg32", "i8"]    , "opcode": "000fc4", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pinsrw"         , "operands": ["mmx", "mem16", "i8"]    , "opcode": "000fc4", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pinsrw"         , "operands": ["xmm", "reg32", "i8"]    , "opcode": "000fc4", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pinsrw"         , "operands": ["xmm", "mem16", "i8"]    , "opcode": "000fc4", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pop"            , "operands": ["reg16"]                 , "opcode": "000058", "rm": "" , "w": ""  , "ri": true , "pp": "66"   },
    { "name": "pop"            , "operands": ["mem16"]                 , "opcode": "00008f", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pop"            , "operands": ["reg64"]                 , "opcode": "000058", "rm": "" , "w": ""  , "ri": true , "pp": ""     },
    { "name": "pop"            , "operands": ["mem64"]                 , "opcode": "00008f", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "popf"           , "operands": []                        , "opcode": "00009d", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "popfq"          , "operands": []                        , "opcode": "00009d", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "prefetch"       , "operands": ["mem_address"]           , "opcode": "000f0d", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "prefetchnta"    , "operands": ["mem_address"]           , "opcode": "000f18", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "prefetcht0"     , "operands": ["mem_address"]           , "opcode": "000f18", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "prefetcht1"     , "operands": ["mem_address"]           , "opcode": "000f18", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "prefetcht2"     , "operands": ["mem_address"]           , "opcode": "000f18", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "prefetchw"      , "operands": ["mem_address"]           , "opcode": "000f0d", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "prefetchwt1"    , "operands": ["mem_address"]           , "opcode": "000f0d", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pshufd"         , "operands": ["xmm", "xmm", "i8"]      , "opcode": "000f70", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pshufd"         , "operands": ["xmm", "xmm", "i8"]      , "opcode": "000f70", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pshufd"         , "operands": ["xmm", "mem128", "i8"]   , "opcode": "000f70", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pshufhw"        , "operands": ["xmm", "xmm", "i8"]      , "opcode": "000f70", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "pshufhw"        , "operands": ["xmm", "mem128", "i8"]   , "opcode": "000f70", "rm": "r", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "pshuflw"        , "operands": ["xmm", "xmm", "i8"]      , "opcode": "000f70", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "pshuflw"        , "operands": ["xmm", "mem128", "i8"]   , "opcode": "000f70", "rm": "r", "w": ""  , "ri": false, "pp": "F2"   },
    { "name": "pshufw"         , "operands": ["mmx", "mmx", "i8"]      , "opcode": "000f70", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "pshufw"         , "operands": ["mmx", "mem_address", "i8"]    , "opcode": "000f70", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "push"           , "operands": ["reg16"]                 , "opcode": "000050", "rm": "" , "w": ""  , "ri": true , "pp": "66"   },
    { "name": "push"           , "operands": ["mem16"]                 , "opcode": "0000ff", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "push"           , "operands": ["reg64"]                 , "opcode": "000050", "rm": "" , "w": ""  , "ri": true , "pp": ""     },
    { "name": "push"           , "operands": ["mem64"]                 , "opcode": "0000ff", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "push"           , "operands": ["i8"]                    , "opcode": "00006a", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "push"           , "operands": ["i16"]                   , "opcode": "000068", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "push"           , "operands": ["i32"]                   , "opcode": "000068", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "pushf"          , "operands": []                        , "opcode": "00009c", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "pushfq"         , "operands": []                        , "opcode": "00009c", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["reg8" , "1" ]                  , "opcode": "0000d0", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["mem8" , "1" ]                  , "opcode": "0000d0", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["reg16", "1"]                 , "opcode": "0000d1", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rcl"            , "operands": ["mem16", "1"]                 , "opcode": "0000d1", "rm": "2", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rcl"            , "operands": ["reg32", "1"]                 , "opcode": "0000d1", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["mem32", "1"]                 , "opcode": "0000d1", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["reg64", "1"]                 , "opcode": "0000d1", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["mem64", "1"]                 , "opcode": "0000d1", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["mem16", "i8"]           , "opcode": "0000c1", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["reg32", "i8"]           , "opcode": "0000c1", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["mem32", "i8"]           , "opcode": "0000c1", "rm": "2", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["reg64", "i8"]           , "opcode": "0000c1", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcl"            , "operands": ["mem64", "i8"]           , "opcode": "0000c1", "rm": "2", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["reg8" , "1"]                  , "opcode": "0000d0", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["mem8" , "1"]                  , "opcode": "0000d0", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["reg16", "1"]                 , "opcode": "0000d1", "rm": "3", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rcr"            , "operands": ["mem16", "1"]                 , "opcode": "0000d1", "rm": "3", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rcr"            , "operands": ["reg32", "1"]                 , "opcode": "0000d1", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["mem32", "1"]                 , "opcode": "0000d1", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["reg64", "1"]                 , "opcode": "0000d1", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["mem64", "1"]                 , "opcode": "0000d1", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["mem16", "i8"]           , "opcode": "0000c1", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["reg32", "i8"]           , "opcode": "0000c1", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["mem32", "i8"]           , "opcode": "0000c1", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["reg64", "i8"]           , "opcode": "0000c1", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rcr"            , "operands": ["mem64", "i8"]           , "opcode": "0000c1", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rdfsbase"       , "operands": ["reg32"]                 , "opcode": "000fae", "rm": "0", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "rdfsbase"       , "operands": ["reg64"]                 , "opcode": "000fae", "rm": "0", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "rdgsbase"       , "operands": ["reg32"]                 , "opcode": "000fae", "rm": "1", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "rdgsbase"       , "operands": ["reg64"]                 , "opcode": "000fae", "rm": "1", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "rdrand"         , "operands": ["reg16"]                 , "opcode": "000fc7", "rm": "6", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rdrand"         , "operands": ["reg32"]                 , "opcode": "000fc7", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rdrand"         , "operands": ["reg64"]                 , "opcode": "000fc7", "rm": "6", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rdseed"         , "operands": ["reg16"]                 , "opcode": "000fc7", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rdseed"         , "operands": ["reg32"]                 , "opcode": "000fc7", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rdseed"         , "operands": ["reg64"]                 , "opcode": "000fc7", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rdtsc"          , "operands": []                        , "opcode": "000f31", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "rdtscp"         , "operands": []                        , "opcode": "0000f9", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "ret"            , "operands": []                        , "opcode": "0000c3", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "ret"            , "operands": ["i16"]                   , "opcode": "0000c2", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["reg8" , "1"]                  , "opcode": "0000d0", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["mem8" , "1"]                  , "opcode": "0000d0", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["reg16", "1"]                 , "opcode": "0000d1", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rol"            , "operands": ["mem16", "1"]                 , "opcode": "0000d1", "rm": "0", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "rol"            , "operands": ["reg32", "1"]                 , "opcode": "0000d1", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["mem32", "1"]                 , "opcode": "0000d1", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["reg64", "1"]                 , "opcode": "0000d1", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["mem64", "1"]                 , "opcode": "0000d1", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["mem16", "i8"]           , "opcode": "0000c1", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["reg32", "i8"]           , "opcode": "0000c1", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["mem32", "i8"]           , "opcode": "0000c1", "rm": "0", "w": ""  , "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["reg64", "i8"]           , "opcode": "0000c1", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "rol"            , "operands": ["mem64", "i8"]           , "opcode": "0000c1", "rm": "0", "w": "W1", "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["reg8" , "1"]                  , "opcode": "0000d0", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["mem8" , "1"]                  , "opcode": "0000d0", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["reg16", "1"]                 , "opcode": "0000d1", "rm": "1", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "ror"            , "operands": ["mem16", "1"]                 , "opcode": "0000d1", "rm": "1", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "ror"            , "operands": ["reg32", "1"]                 , "opcode": "0000d1", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["mem32", "1"]                 , "opcode": "0000d1", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["reg64", "1"]                 , "opcode": "0000d1", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["mem64", "1"]                 , "opcode": "0000d1", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["mem16", "i8"]           , "opcode": "0000c1", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["reg32", "i8"]           , "opcode": "0000c1", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["mem32", "i8"]           , "opcode": "0000c1", "rm": "1", "w": ""  , "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["reg64", "i8"]           , "opcode": "0000c1", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "ror"            , "operands": ["mem64", "i8"]           , "opcode": "0000c1", "rm": "1", "w": "W1", "ri": false, "pp": ""     },
    { "name": "roundpd"        , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a09", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "roundpd"        , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a09", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "roundps"        , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a08", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "roundps"        , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3a08", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "roundsd"        , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a0b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "roundsd"        , "operands": ["xmm", "mem64", "i8"]    , "opcode": "0f3a0b", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "roundss"        , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3a0a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "roundss"        , "operands": ["xmm", "mem32", "i8"]    , "opcode": "0f3a0a", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sahf"           , "operands": []                        , "opcode": "00009e", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["reg8" , "1"]                  , "opcode": "0000d0", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["mem8" , "1"]                  , "opcode": "0000d0", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["reg16", "1"]                 , "opcode": "0000d1", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sal"            , "operands": ["mem16", "1"]                 , "opcode": "0000d1", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sal"            , "operands": ["reg32", "1"]                 , "opcode": "0000d1", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["mem32", "1"]                 , "opcode": "0000d1", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["reg64", "1"]                 , "opcode": "0000d1", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["mem64", "1"]                 , "opcode": "0000d1", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["mem16", "i8"]           , "opcode": "0000c1", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["reg32", "i8"]           , "opcode": "0000c1", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["mem32", "i8"]           , "opcode": "0000c1", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["reg64", "i8"]           , "opcode": "0000c1", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sal"            , "operands": ["mem64", "i8"]           , "opcode": "0000c1", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["reg8" , "1"]                  , "opcode": "0000d0", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["mem8" , "1"]                  , "opcode": "0000d0", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["reg16", "1"]                 , "opcode": "0000d1", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sar"            , "operands": ["mem16", "1"]                 , "opcode": "0000d1", "rm": "7", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "sar"            , "operands": ["reg32", "1"]                 , "opcode": "0000d1", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["mem32", "1"]                 , "opcode": "0000d1", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["reg64", "1"]                 , "opcode": "0000d1", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["mem64", "1"]                 , "opcode": "0000d1", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["reg8", "i8"]            , "opcode": "0000c0", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["mem8", "i8"]            , "opcode": "0000c0", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["mem16", "i8"]          , "opcode": "0000c1", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["reg32", "i8"]          , "opcode": "0000c1", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["mem32", "i8"]          , "opcode": "0000c1", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["reg64", "i8"]          , "opcode": "0000c1", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "sar"            , "operands": ["mem64", "i8"]          , "opcode": "0000c1", "rm": "7", "w": "W1", "ri": false, "pp": ""     },
    { "name": "scasb"          , "operands": []                        , "opcode": "0000ae", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "scasd"          , "operands": []                        , "opcode": "0000af", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "scasq"          , "operands": []                        , "opcode": "0000af", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "scasw"          , "operands": []                        , "opcode": "0000af", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "seta"           , "operands": ["reg8"]                  , "opcode": "000f97", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "seta"           , "operands": ["mem8"]                  , "opcode": "000f97", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setae"          , "operands": ["reg8"]                  , "opcode": "000f93", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setae"          , "operands": ["mem8"]                  , "opcode": "000f93", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setb"           , "operands": ["reg8"]                  , "opcode": "000f92", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setb"           , "operands": ["mem8"]                  , "opcode": "000f92", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setbe"          , "operands": ["reg8"]                  , "opcode": "000f96", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setbe"          , "operands": ["mem8"]                  , "opcode": "000f96", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setc"           , "operands": ["reg8"]                  , "opcode": "000f92", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setc"           , "operands": ["mem8"]                  , "opcode": "000f92", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sete"           , "operands": ["reg8"]                  , "opcode": "000f94", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sete"           , "operands": ["mem8"]                  , "opcode": "000f94", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setg"           , "operands": ["reg8"]                  , "opcode": "000f9f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setg"           , "operands": ["mem8"]                  , "opcode": "000f9f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setge"          , "operands": ["reg8"]                  , "opcode": "000f9d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setge"          , "operands": ["mem8"]                  , "opcode": "000f9d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setl"           , "operands": ["reg8"]                  , "opcode": "000f9c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setl"           , "operands": ["mem8"]                  , "opcode": "000f9c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setle"          , "operands": ["reg8"]                  , "opcode": "000f9e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setle"          , "operands": ["mem8"]                  , "opcode": "000f9e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setna"          , "operands": ["reg8"]                  , "opcode": "000f96", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setna"          , "operands": ["mem8"]                  , "opcode": "000f96", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnae"         , "operands": ["reg8"]                  , "opcode": "000f92", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnae"         , "operands": ["mem8"]                  , "opcode": "000f92", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnb"          , "operands": ["reg8"]                  , "opcode": "000f93", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnb"          , "operands": ["mem8"]                  , "opcode": "000f93", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnbe"         , "operands": ["reg8"]                  , "opcode": "000f97", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnbe"         , "operands": ["mem8"]                  , "opcode": "000f97", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnc"          , "operands": ["reg8"]                  , "opcode": "000f93", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnc"          , "operands": ["mem8"]                  , "opcode": "000f93", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setne"          , "operands": ["reg8"]                  , "opcode": "000f95", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setne"          , "operands": ["mem8"]                  , "opcode": "000f95", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setng"          , "operands": ["reg8"]                  , "opcode": "000f9e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setng"          , "operands": ["mem8"]                  , "opcode": "000f9e", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnge"         , "operands": ["reg8"]                  , "opcode": "000f9c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnge"         , "operands": ["mem8"]                  , "opcode": "000f9c", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnl"          , "operands": ["reg8"]                  , "opcode": "000f9d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnl"          , "operands": ["mem8"]                  , "opcode": "000f9d", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnle"         , "operands": ["reg8"]                  , "opcode": "000f9f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnle"         , "operands": ["mem8"]                  , "opcode": "000f9f", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setno"          , "operands": ["reg8"]                  , "opcode": "000f91", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setno"          , "operands": ["mem8"]                  , "opcode": "000f91", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnp"          , "operands": ["reg8"]                  , "opcode": "000f9b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnp"          , "operands": ["mem8"]                  , "opcode": "000f9b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setns"          , "operands": ["reg8"]                  , "opcode": "000f99", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setns"          , "operands": ["mem8"]                  , "opcode": "000f99", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnz"          , "operands": ["reg8"]                  , "opcode": "000f95", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setnz"          , "operands": ["mem8"]                  , "opcode": "000f95", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "seto"           , "operands": ["reg8"]                  , "opcode": "000f90", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "seto"           , "operands": ["mem8"]                  , "opcode": "000f90", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setp"           , "operands": ["reg8"]                  , "opcode": "000f9a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setp"           , "operands": ["mem8"]                  , "opcode": "000f9a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setpe"          , "operands": ["reg8"]                  , "opcode": "000f9a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setpe"          , "operands": ["mem8"]                  , "opcode": "000f9a", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setpo"          , "operands": ["reg8"]                  , "opcode": "000f9b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setpo"          , "operands": ["mem8"]                  , "opcode": "000f9b", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sets"           , "operands": ["reg8"]                  , "opcode": "000f98", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sets"           , "operands": ["mem8"]                  , "opcode": "000f98", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setz"           , "operands": ["reg8"]                  , "opcode": "000f94", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "setz"           , "operands": ["mem8"]                  , "opcode": "000f94", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sfence"         , "operands": []                        , "opcode": "000fae", "rm": "7", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sha1rnds4"      , "operands": ["xmm", "xmm", "i8"]      , "opcode": "0f3acc", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "sha1rnds4"      , "operands": ["xmm", "mem128", "i8"]   , "opcode": "0f3acc", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["reg8", "1"]                  , "opcode": "0000d0", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["mem8", "1"]                  , "opcode": "0000d0", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["reg16", "1"]                 , "opcode": "0000d1", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shl"            , "operands": ["mem16", "1"]                 , "opcode": "0000d1", "rm": "4", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shl"            , "operands": ["reg32", "1"]                 , "opcode": "0000d1", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["mem32", "1"]                 , "opcode": "0000d1", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["reg64", "1"]                 , "opcode": "0000d1", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shl"            , "operands": ["mem64", "1"]                 , "opcode": "0000d1", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shld"           , "operands": ["reg16", "reg16", "i8"]  , "opcode": "000fa4", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shld"           , "operands": ["mem16", "reg16", "i8"]  , "opcode": "000fa4", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shld"           , "operands": ["reg16", "reg16", "cl"]  , "opcode": "000fa5", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shld"           , "operands": ["mem16", "reg16", "cl"]  , "opcode": "000fa5", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shld"           , "operands": ["reg32", "reg32", "i8"]  , "opcode": "000fa4", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shld"           , "operands": ["mem32", "reg32", "i8"]  , "opcode": "000fa4", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shld"           , "operands": ["reg32", "reg32", "cl"]  , "opcode": "000fa5", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shld"           , "operands": ["mem32", "reg32", "cl"]  , "opcode": "000fa5", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shld"           , "operands": ["reg64", "reg64", "i8"]  , "opcode": "000fa4", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shld"           , "operands": ["mem64", "reg64", "i8"]  , "opcode": "000fa4", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shld"           , "operands": ["reg64", "reg64", "cl"]  , "opcode": "000fa5", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shld"           , "operands": ["mem64", "reg64", "cl"]  , "opcode": "000fa5", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["reg8", "1"]                  , "opcode": "0000d0", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["mem8", "1"]                  , "opcode": "0000d0", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["reg16", "1"]                 , "opcode": "0000d1", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shr"            , "operands": ["mem16", "1"]                 , "opcode": "0000d1", "rm": "5", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shr"            , "operands": ["reg32", "1"]                 , "opcode": "0000d1", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["mem32", "1"]                 , "opcode": "0000d1", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["reg64", "1"]                 , "opcode": "0000d1", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shr"            , "operands": ["mem64", "1"]                 , "opcode": "0000d1", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shrd"           , "operands": ["reg16", "reg16", "i8"]  , "opcode": "000fac", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shrd"           , "operands": ["mem16", "reg16", "i8"]  , "opcode": "000fac", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shrd"           , "operands": ["reg16", "reg16", "cl"]  , "opcode": "000fad", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shrd"           , "operands": ["mem16", "reg16", "cl"]  , "opcode": "000fad", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shrd"           , "operands": ["reg32", "reg32", "i8"]  , "opcode": "000fac", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shrd"           , "operands": ["mem32", "reg32", "i8"]  , "opcode": "000fac", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shrd"           , "operands": ["reg32", "reg32", "cl"]  , "opcode": "000fad", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shrd"           , "operands": ["mem32", "reg32", "cl"]  , "opcode": "000fad", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shrd"           , "operands": ["reg64", "reg64", "i8"]  , "opcode": "000fac", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shrd"           , "operands": ["mem64", "reg64", "i8"]  , "opcode": "000fac", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shrd"           , "operands": ["reg64", "reg64", "cl"]  , "opcode": "000fad", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shrd"           , "operands": ["mem64", "reg64", "cl"]  , "opcode": "000fad", "rm": "r", "w": "W1", "ri": false, "pp": ""     },
    { "name": "shufpd"         , "operands": ["xmm", "xmm", "i8"]      , "opcode": "000fc6", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shufpd"         , "operands": ["xmm", "mem128", "i8"]   , "opcode": "000fc6", "rm": "r", "w": ""  , "ri": false, "pp": "66"   },
    { "name": "shufps"         , "operands": ["xmm", "xmm", "i8"]      , "opcode": "000fc6", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "shufps"         , "operands": ["xmm", "mem128", "i8"]   , "opcode": "000fc6", "rm": "r", "w": ""  , "ri": false, "pp": ""     },
    { "name": "stac"           , "operands": []                        , "opcode": "0000cb", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "stc"            , "operands": []                        , "opcode": "0000f9", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "std"            , "operands": []                        , "opcode": "0000fd", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "sti"            , "operands": []                        , "opcode": "0000fb", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "stmxcsr"        , "operands": ["mem32"]                 , "opcode": "000fae", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "stosb"          , "operands": []                        , "opcode": "0000aa", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "stosd"          , "operands": []                        , "opcode": "0000ab", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "stosq"          , "operands": []                        , "opcode": "0000ab", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "stosw"          , "operands": []                        , "opcode": "0000ab", "rm": "" , "w": ""  , "ri": false, "pp": "66"   },
    { "name": "swapgs"         , "operands": []                        , "opcode": "0000f8", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "syscall"        , "operands": []                        , "opcode": "000f05", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "sysenter"       , "operands": []                        , "opcode": "000f34", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "sysexit"        , "operands": []                        , "opcode": "000f35", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "sysexit64"      , "operands": []                        , "opcode": "000f35", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "sysret"         , "operands": []                        , "opcode": "000f07", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "sysret64"       , "operands": []                        , "opcode": "000f07", "rm": "" , "w": "W1", "ri": false, "pp": ""     },
    { "name": "ud2"            , "operands": []                        , "opcode": "000f0b", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "wrfsbase"       , "operands": ["reg32"]                 , "opcode": "000fae", "rm": "2", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "wrfsbase"       , "operands": ["reg64"]                 , "opcode": "000fae", "rm": "2", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "wrgsbase"       , "operands": ["reg32"]                 , "opcode": "000fae", "rm": "3", "w": ""  , "ri": false, "pp": "F3"   },
    { "name": "wrgsbase"       , "operands": ["reg64"]                 , "opcode": "000fae", "rm": "3", "w": "W1", "ri": false, "pp": "F3"   },
    { "name": "xgetbv"         , "operands": []                        , "opcode": "0000d0", "rm": "" , "w": ""  , "ri": false, "pp": ""     },
    { "name": "xrstor"         , "operands": ["mem_address"]           , "opcode": "000fae", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xrstor64"       , "operands": ["mem_address"]           , "opcode": "000fae", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xrstors"        , "operands": ["mem_address"]           , "opcode": "000fc7", "rm": "3", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xrstors64"      , "operands": ["mem_address"]           , "opcode": "000fc7", "rm": "3", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xsave"          , "operands": ["mem_address"]           , "opcode": "000fae", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xsave64"        , "operands": ["mem_address"]           , "opcode": "000fae", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xsavec"         , "operands": ["mem_address"]           , "opcode": "000fc7", "rm": "4", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xsavec64"       , "operands": ["mem_address"]           , "opcode": "000fc7", "rm": "4", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xsaveopt"       , "operands": ["mem_address"]           , "opcode": "000fae", "rm": "6", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xsaveopt64"     , "operands": ["mem_address"]           , "opcode": "000fae", "rm": "6", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xsaves"         , "operands": ["mem_address"]           , "opcode": "000fc7", "rm": "5", "w": ""  , "ri": false, "pp": ""     },
    { "name": "xsaves64"       , "operands": ["mem_address"]           , "opcode": "000fc7", "rm": "5", "w": "W1", "ri": false, "pp": ""     },
    { "name": "xsetbv"         , "operands": []                        , "opcode": "0000d1", "rm": "" , "w": ""  , "ri": false, "pp": ""     }
];


// TODO: no operand instructions can't know which variant to call
// TODO: this is all non-vex

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
    return execSync(cmd, { encoding: 'utf8' });
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
    if (fs.existsSync(path)) {
        return;
    }

    return fs.mkdirSync(path);
}

const opcode_override_map = new Map([
    ["pblendvb:xmm:xmm", "0f3810"],
    ["pblendvb:xmm:mem128", "0f3810"]
]);

// utility functions related to instruction transformations
// extract the 3-byte opcode from an instruction instance
function extract_opcode(inst, operands) {
    let opcodeBytes = [0x00, 0x00, 0x00];

    const key = `${inst.name}:${operands.join(":")}`;

    if (opcode_override_map.has(key)) {
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
        switch (o) {
            case "iq": return "i64";
            case "uq": return "i64";
            case "id": return "i32";
            case "ud": return "i32";
            case "iw": return "i16";
            case "uw": return "i16";
            case "ib": return "i8";
            case "ub": return "i8";
            case "r8": return "reg8";
            case "r16": return "reg16";
            case "r32": return "reg32";
            case "r64": return "reg64";
            case "m8": return "mem8";
            case "m16": return "mem16";
            case "m32": return "mem32";
            case "m64": return "mem64";
            case "m128": return "mem128";
            case "mm": return "mmx"
            default: return o;
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

const extension_override_map = new Map([
    ["movq:reg64:mmx", "EXT_R | EXT_REXW"],
    ["movmskpd:reg64:xmm", "EXT_R | EXT_REXW"],
    ["movmskps:reg64:xmm", "EXT_R | EXT_REXW"],
    ["movq:xmm:reg64", "EXT_R | EXT_REXW"],
    ["movq:reg64:xmm", "EXT_R | EXT_REXW"],
    ["mov:sreg:reg64", "EXT_R"],
    ["mov:reg64:sreg", "EXT_R"],
]);

// extract a string which represent instruction extensions that we recognize
function extract_extensions(inst) {
    let result = [];

    const key = `${inst.name}:${inst.operands.join(":")}`;

    if (extension_override_map.has(key)) {
        return extension_override_map.get(key);
    }

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

function extract_prefix(inst, operands) {
    let result = [];

    const key = `${inst.name}:${operands.join(':')}`;

    const prefix_override_table = new Map([
        ["lea:reg16:mem_address", "OPERAND_SIZE_OVERRIDE"],
        ["pmovmskb:reg32:xmm", "OPERAND_SIZE_OVERRIDE"],
        ["mov:reg16:sreg", "OPERAND_SIZE_OVERRIDE"],
    ]);

    if(prefix_override_table.has(key)) {
        return prefix_override_table.get(key)
    }

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
       "reg8", "reg16", "reg32", "reg64",
       "i8", "i16", "i32", "i64",
       "moff8", "moff16", "moff32", "moff64", 
       "al", "ax", "eax", "rax", 
        "mem8", "mem16", "mem32", "mem64",
        "xmm",
        "mem128",
        "dx", "cl", "rcx", "ecx",
        "bnd",
        "mib",
        "mem",
        "mmx",
        "sreg", "dreg", "creg",
        "es:zdi",
        "ds:zsi",
        "rel8"
    ];

    if (operands.every(part => valid_operands.includes(part))) {
        return true;
    }
    else {
        operands.forEach(op => {
            if (valid_operands.includes(op) == false) {
                unknown_operands.add(op)
            }
        })
    }

    return false;
}

function pop_count(str) {
    for (let i = 0; i < str.length; ++i) {
        if (str[i] != 0) {
            return Math.ceil((str.length - i) / 2);
        }
    }

    return 0;
}

function calculate_code_len(inst, operands) {
    let len = 0;

    // prefix
    len += extract_prefix(inst, operands) == "PREFIX_NONE" ? 0 : 1;

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
        best.name = inst.name;
        let best_len = calculate_code_len(best, inst.operands);

        for (let i = 1; i < inst.variants.length; ++i) {
            let current = calculate_code_len(inst.variants[i], inst.operands);

            if (current < best_len) {
                best_len = current;
                best = inst.variants[i];
            }
            else if (current == best_len) {
            }
        }

        if (false) {
            inst.variants.forEach(v => {
                if (v != best) {
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
        case 0: return "";
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
        if (op.implicit == false) {
            result.push(op);
        }
    })

    return result;
}

function get_operand_size(op) {
    switch (op) {
        case "reg8": return 8;
        case "reg16": return 16;
        case "reg32": return 32;
        case "reg64": return 64;
        case "i8": return 8;
        case "i16": return 16;
        case "i32": return 32;
        case "i64": return 64;
        case "moff8": return 8;
        case "moff16": return 16;
        case "moff32": return 32;
        case "moff64": return 64;
        case "al": return 8;
        case "ax": return 16;
        case "eax": return 32;
        case "rax": return 64;
        case "mem8": return 8;
        case "mem16": return 16;
        case "mem32": return 32;
        case "mem64": return 64;
        case "mem128": return 128;
        case "xmm": return 128;
        case "mmx": return 64;
    }
}

const illegal_combinations = new Set([
    "movq:mmx:reg64",
    "movq:mmx:reg32",
    "movq:xmm:mmx",
    "movq:mmx:xmm",
    "movq:mmx:mem32",
    "movq:reg32:mmx",
    "movq:mem32:mmx",
    "pmuludq:mmx:mem64",
    "psubq:mmx:mem64",
]);

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
            let name = inst.name;
            let operands = translate_operands(combination);


            // these are incorrectly encoded in asmDB, they don't have any operands we have to specify by hand
            switch(name) {
                case "insw":
                case "insd":
                case "insb":
                case "outsw":
                case "outsd":
                case "outsb":
                case "jecxz":  operands = []; break;
                case "loop":
                case "loope":
                case "loopne": operands = ["rel8"]; break;
                default: 
            }


            if (!verify_operands(operands)) {
                return;
            }

            // special cases where we need to rename the instruction
            if (name === "movd") {
                for(let i = 0; i < operands.length; ++i) {
                    if(get_operand_size(operands[i]) == 64) {
                        name = "movq"
                        break;
                    }
                }
            }
            else if(name === "pmovmskb") {
                operands = [ 'reg32', 'xmm' ]; // force 
            }
            else if(operands.includes("mib")) {
                operands = operands.map((op) => {
                    switch(op) {
                        case "mib": return "mem_address";
                        default: return op;
                    }
                });
            }
            else if(operands.includes("mem")) {
                operands = operands.map((op) => {
                    switch(op) {
                        case "mem": return "mem_address";
                        default: return op;
                    }
                });
            }
            else if(name === "bndstx") {
                operands = [ 'mem_address', 'bnd' ]; // force 
            }
            else if(operands.includes("bnd")) {
                // remap bnd's with memory operands to just mems 
                operands = operands.map((op) => {
                    switch(op) {
                        case "mem32": return "mem_address";
                        case "mem64": return "mem_address";
                        default: return op;
                    }
                });
            }

            const key = `${name}:${operands.join(':')}`;
            if(illegal_combinations.has(key)) {
                return;
            }

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
                    name: name,
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
    switch (name) {
        case "xor": return "xor_";
        case "int": return "int_";
        case "not": return "not_";
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
    format_instruction_name,

    new_database
};
