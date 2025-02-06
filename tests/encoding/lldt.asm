; expect: 0f00d10f00d20f00d3410f00d70f001425000000000f001425ff0000000f0015f9ffffff0f0015f80000000f0015f8ff00000f00100f00100f0090ffff0000410f0097ffff00000f0014300f009430ffff0000410f009437ffff0000420f009438ffff00000f009470f2ff0f000f0094b0f4ff0f000f0094f0f8ff0f000f0094c4f8ff0f00410f0094c7f8ff0f00420f0094fcf8ff0f00430f0094fef8ff0f00

bits 64

lldt cx
lldt dx
lldt bx
lldt r15w
lldt word [0x0]
lldt word [0xFF]
lldt word [rel $ + 0x0]
lldt word [rel $ + 0xFF]
lldt word [rel $ + 0xFFFF]
lldt word [rax]
lldt word [rax + 0x0]
lldt word [rax + 0xFFFF]
lldt word [r15 + 0xFFFF]
lldt word [rax + rsi * 1  + 0x0]
lldt word [rax + rsi + 0xFFFF]
lldt word [r15 + rsi + 0xFFFF]
lldt word [rax + r15 + 0xFFFF]
lldt word [rax + rsi * 2 + 0xFFFF2]
lldt word [rax + rsi * 4 + 0xFFFF4]
lldt word [rax + rsi * 8 + 0xFFFF8]
lldt word [rsp + rax * 8 + 0xFFFF8]
lldt word [r15 + rax * 8 + 0xFFFF8]
lldt word [rsp + r15 * 8 + 0xFFFF8]
lldt word [r14 + r15 * 8 + 0xFFFF8]
