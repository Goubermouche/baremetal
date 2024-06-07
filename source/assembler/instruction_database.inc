
// name
// opcode
// extensions
// prefixes
// context based index
// - 
// -

// op 1
// op 2

INST(mov, 0x0000b8, EXT_OP_R           , OPERAND_SIZE_OVERRIDE, 0, REG16, I16  )
INST(mov, 0x000089, EXT_R              , OPERAND_SIZE_OVERRIDE, 0, REG16, REG16)

INST(mov, 0x0000b8, EXT_OP_R           , PREFIX_NONE          , 0, REG32, I32  )
INST(mov, 0x000089, EXT_R              , PREFIX_NONE          , 0, REG32, REG32)

INST(mov, 0x0000c7, EXT_0 | EXT_REXW   , PREFIX_NONE          , 2, REG64, I32  )
INST(mov, 0x0000b8, EXT_REXW | EXT_OP_R, PREFIX_NONE          , 0, REG64, I64  )
INST(mov, 0x000089, EXT_R | EXT_REXW   , PREFIX_NONE          , 0, REG64, REG64)

INST(mov, 0x0000b0, EXT_OP_R           , PREFIX_NONE          , 0, REG8 , I8   )
INST(mov, 0x000088, EXT_R              , PREFIX_NONE          , 0, REG8 , REG8 )