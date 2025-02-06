; expect: 0f00e10f00e20f00e3410f00e70f002425000000000f002425ff0000000f0025f9ffffff0f0025f80000000f0025f8ff00000f00200f00200f00a0ffff0000410f00a7ffff00000f0024300f00a430ffff0000410f00a437ffff0000420f00a438ffff00000f00a470f2ff0f000f00a4b0f4ff0f000f00a4f0f8ff0f000f00a4c4f8ff0f00410f00a4c7f8ff0f00420f00a4fcf8ff0f00430f00a4fef8ff0f00

bits 64

verr cx
verr dx
verr bx
verr r15w
verr word [0x0]
verr word [0xFF]
verr word [rel $ + 0x0]
verr word [rel $ + 0xFF]
verr word [rel $ + 0xFFFF]
verr word [rax]
verr word [rax + 0x0]
verr word [rax + 0xFFFF]
verr word [r15 + 0xFFFF]
verr word [rax + rsi * 1  + 0x0]
verr word [rax + rsi + 0xFFFF]
verr word [r15 + rsi + 0xFFFF]
verr word [rax + r15 + 0xFFFF]
verr word [rax + rsi * 2 + 0xFFFF2]
verr word [rax + rsi * 4 + 0xFFFF4]
verr word [rax + rsi * 8 + 0xFFFF8]
verr word [rsp + rax * 8 + 0xFFFF8]
verr word [r15 + rax * 8 + 0xFFFF8]
verr word [rsp + r15 * 8 + 0xFFFF8]
verr word [r14 + r15 * 8 + 0xFFFF8]
