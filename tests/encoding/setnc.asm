; expect: 0f93c10f93c20f93c30f930425000000000f930425ff0000000f9305f9ffffff0f9305f80000000f9305f8ff00000f93000f93000f9380ffff0000410f9387ffff00000f9304300f938430ffff0000410f938437ffff0000420f938438ffff00000f938470f2ff0f000f9384b0f4ff0f000f9384f0f8ff0f000f9384c4f8ff0f00410f9384c7f8ff0f00420f9384fcf8ff0f00430f9384fef8ff0f00

bits 64

setnc cl
setnc dl
setnc bl
setnc byte [0x0]
setnc byte [0xFF]
setnc byte [rel $ + 0x0]
setnc byte [rel $ + 0xFF]
setnc byte [rel $ + 0xFFFF]
setnc byte [rax]
setnc byte [rax + 0x0]
setnc byte [rax + 0xFFFF]
setnc byte [r15 + 0xFFFF]
setnc byte [rax + rsi * 1  + 0x0]
setnc byte [rax + rsi + 0xFFFF]
setnc byte [r15 + rsi + 0xFFFF]
setnc byte [rax + r15 + 0xFFFF]
setnc byte [rax + rsi * 2 + 0xFFFF2]
setnc byte [rax + rsi * 4 + 0xFFFF4]
setnc byte [rax + rsi * 8 + 0xFFFF8]
setnc byte [rsp + rax * 8 + 0xFFFF8]
setnc byte [r15 + rax * 8 + 0xFFFF8]
setnc byte [rsp + r15 * 8 + 0xFFFF8]
setnc byte [r14 + r15 * 8 + 0xFFFF8]
