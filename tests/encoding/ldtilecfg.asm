; expect: c4e27849042500000000c4e278490425ff000000c4e2784905f7ffffffc4e2784905f6000000c4e2784905f6ff0000c4e2784900c4e2784900c4e2784980ffff0000c4c2784987ffff0000c4e278490430c4e278498430ffff0000c4c278498437ffff0000c4a278498438ffff0000c4e278498470f2ff0f00c4e2784984b0f4ff0f00c4e2784984f0f8ff0f00c4e2784984c4f8ff0f00c4c2784984c7f8ff0f00c4a2784984fcf8ff0f00c482784984fef8ff0f00

bits 64

ldtilecfg [0x0]
ldtilecfg [0xFF]
ldtilecfg [rel $ + 0x0]
ldtilecfg [rel $ + 0xFF]
ldtilecfg [rel $ + 0xFFFF]
ldtilecfg [rax]
ldtilecfg [rax + 0x0]
ldtilecfg [rax + 0xFFFF]
ldtilecfg [r15 + 0xFFFF]
ldtilecfg [rax + rsi * 1  + 0x0]
ldtilecfg [rax + rsi + 0xFFFF]
ldtilecfg [r15 + rsi + 0xFFFF]
ldtilecfg [rax + r15 + 0xFFFF]
ldtilecfg [rax + rsi * 2 + 0xFFFF2]
ldtilecfg [rax + rsi * 4 + 0xFFFF4]
ldtilecfg [rax + rsi * 8 + 0xFFFF8]
ldtilecfg [rsp + rax * 8 + 0xFFFF8]
ldtilecfg [r15 + rax * 8 + 0xFFFF8]
ldtilecfg [rsp + r15 * 8 + 0xFFFF8]
ldtilecfg [r14 + r15 * 8 + 0xFFFF8]
