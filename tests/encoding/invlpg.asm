; expect: 0f013c25000000000f013c25ff0000000f013df9ffffff0f013df80000000f013df8ff00000f01380f01380f01b8ffff0000410f01bfffff00000f013c300f01bc30ffff0000410f01bc37ffff0000420f01bc38ffff00000f01bc70f2ff0f000f01bcb0f4ff0f000f01bcf0f8ff0f000f01bcc4f8ff0f00410f01bcc7f8ff0f00420f01bcfcf8ff0f00430f01bcfef8ff0f00

bits 64

invlpg [0x0]
invlpg [0xFF]
invlpg [rel $ + 0x0]
invlpg [rel $ + 0xFF]
invlpg [rel $ + 0xFFFF]
invlpg [rax]
invlpg [rax + 0x0]
invlpg [rax + 0xFFFF]
invlpg [r15 + 0xFFFF]
invlpg [rax + rsi * 1  + 0x0]
invlpg [rax + rsi + 0xFFFF]
invlpg [r15 + rsi + 0xFFFF]
invlpg [rax + r15 + 0xFFFF]
invlpg [rax + rsi * 2 + 0xFFFF2]
invlpg [rax + rsi * 4 + 0xFFFF4]
invlpg [rax + rsi * 8 + 0xFFFF8]
invlpg [rsp + rax * 8 + 0xFFFF8]
invlpg [r15 + rax * 8 + 0xFFFF8]
invlpg [rsp + r15 * 8 + 0xFFFF8]
invlpg [r14 + r15 * 8 + 0xFFFF8]
