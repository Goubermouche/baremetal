INST(mov, 0x0000b0, EXT_OP_R, PREFIX_NONE, 0, REG8, I8)
INST(mov, 0x000088, EXT_R, PREFIX_NONE, 0, REG8, REG8)
INST(mov, 0x00008a, EXT_R, PREFIX_NONE, 0, REG8, MEM8)
INST(mov, 0x0000b8, EXT_OP_R, OPERAND_SIZE_OVERRIDE, 0, REG16, I16)
INST(mov, 0x000089, EXT_R, OPERAND_SIZE_OVERRIDE, 0, REG16, REG16)
INST(mov, 0x00008b, EXT_R, OPERAND_SIZE_OVERRIDE, 0, REG16, MEM16)
INST(mov, 0x0000b8, EXT_OP_R, PREFIX_NONE, 0, REG32, I32)
INST(mov, 0x000089, EXT_R, PREFIX_NONE, 0, REG32, REG32)
INST(mov, 0x00008b, EXT_R, PREFIX_NONE, 0, REG32, MEM32)
INST(mov, 0x0000c7, EXT_0 | EXT_REXW, PREFIX_NONE, 6, REG64, I32)
INST(mov, 0x0000b8, EXT_REXW | EXT_OP_R, PREFIX_NONE, 0, REG64, I64)
INST(mov, 0x000089, EXT_R | EXT_REXW, PREFIX_NONE, 0, REG64, REG64)
INST(mov, 0x00008b, EXT_R | EXT_REXW, PREFIX_NONE, 0, REG64, MEM64)
INST(mov, 0x0000c6, EXT_0, PREFIX_NONE, 0, MEM8, I8)
INST(mov, 0x000088, EXT_R, PREFIX_NONE, 0, MEM8, REG8)
INST(mov, 0x0000c7, EXT_0, OPERAND_SIZE_OVERRIDE, 0, MEM16, I16)
INST(mov, 0x000089, EXT_R, OPERAND_SIZE_OVERRIDE, 0, MEM16, REG16)
INST(mov, 0x0000c7, EXT_0, PREFIX_NONE, 0, MEM32, I32)
INST(mov, 0x000089, EXT_R, PREFIX_NONE, 0, MEM32, REG32)
INST(mov, 0x0000c7, EXT_0 | EXT_REXW, PREFIX_NONE, 0, MEM64, I32)
INST(mov, 0x000089, EXT_R | EXT_REXW, PREFIX_NONE, 0, MEM64, REG64)