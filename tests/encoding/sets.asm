; expect: 0f98c10f98c20f98c30f980425000000000f980425ff0000000f9805f9ffffff0f9805f80000000f9805f8ff00000f98000f98000f9880ffff0000410f9887ffff00000f9804300f988430ffff0000410f988437ffff0000420f988438ffff00000f988470f2ff0f000f9884b0f4ff0f000f9884f0f8ff0f000f9884c4f8ff0f00410f9884c7f8ff0f00420f9884fcf8ff0f00430f9884fef8ff0f00

bits 64

sets cl
sets dl
sets bl
sets byte [0x0]
sets byte [0xFF]
sets byte [rel $ + 0x0]
sets byte [rel $ + 0xFF]
sets byte [rel $ + 0xFFFF]
sets byte [rax]
sets byte [rax + 0x0]
sets byte [rax + 0xFFFF]
sets byte [r15 + 0xFFFF]
sets byte [rax + rsi * 1  + 0x0]
sets byte [rax + rsi + 0xFFFF]
sets byte [r15 + rsi + 0xFFFF]
sets byte [rax + r15 + 0xFFFF]
sets byte [rax + rsi * 2 + 0xFFFF2]
sets byte [rax + rsi * 4 + 0xFFFF4]
sets byte [rax + rsi * 8 + 0xFFFF8]
sets byte [rsp + rax * 8 + 0xFFFF8]
sets byte [r15 + rax * 8 + 0xFFFF8]
sets byte [rsp + r15 * 8 + 0xFFFF8]
sets byte [r14 + r15 * 8 + 0xFFFF8]
