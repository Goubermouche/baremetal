; expect: 0f95c10f95c20f95c30f950425000000000f950425ff0000000f9505f9ffffff0f9505f80000000f9505f8ff00000f95000f95000f9580ffff0000410f9587ffff00000f9504300f958430ffff0000410f958437ffff0000420f958438ffff00000f958470f2ff0f000f9584b0f4ff0f000f9584f0f8ff0f000f9584c4f8ff0f00410f9584c7f8ff0f00420f9584fcf8ff0f00430f9584fef8ff0f00

setnz cl
setnz dl
setnz bl
setnz byte [0x0]
setnz byte [0xFF]
setnz byte [rel $ + 0x0]
setnz byte [rel $ + 0xFF]
setnz byte [rel $ + 0xFFFF]
setnz byte [rax]
setnz byte [rax + 0x0]
setnz byte [rax + 0xFFFF]
setnz byte [r15 + 0xFFFF]
setnz byte [rax + rsi * 1  + 0x0]
setnz byte [rax + rsi + 0xFFFF]
setnz byte [r15 + rsi + 0xFFFF]
setnz byte [rax + r15 + 0xFFFF]
setnz byte [rax + rsi * 2 + 0xFFFF2]
setnz byte [rax + rsi * 4 + 0xFFFF4]
setnz byte [rax + rsi * 8 + 0xFFFF8]
setnz byte [rsp + rax * 8 + 0xFFFF8]
setnz byte [r15 + rax * 8 + 0xFFFF8]
setnz byte [rsp + r15 * 8 + 0xFFFF8]
setnz byte [r14 + r15 * 8 + 0xFFFF8]