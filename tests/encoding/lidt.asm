; expect: 0f011c25000000000f011c25ff0000000f011df9ffffff0f011df80000000f011df8ff00000f01180f01180f0198ffff0000410f019fffff00000f011c300f019c30ffff0000410f019c37ffff0000420f019c38ffff00000f019c70f2ff0f000f019cb0f4ff0f000f019cf0f8ff0f000f019cc4f8ff0f00410f019cc7f8ff0f00420f019cfcf8ff0f00430f019cfef8ff0f00

bits 64

lidt [0x0]
lidt [0xFF]
lidt [rel $ + 0x0]
lidt [rel $ + 0xFF]
lidt [rel $ + 0xFFFF]
lidt [rax]
lidt [rax + 0x0]
lidt [rax + 0xFFFF]
lidt [r15 + 0xFFFF]
lidt [rax + rsi * 1  + 0x0]
lidt [rax + rsi + 0xFFFF]
lidt [r15 + rsi + 0xFFFF]
lidt [rax + r15 + 0xFFFF]
lidt [rax + rsi * 2 + 0xFFFF2]
lidt [rax + rsi * 4 + 0xFFFF4]
lidt [rax + rsi * 8 + 0xFFFF8]
lidt [rsp + rax * 8 + 0xFFFF8]
lidt [r15 + rax * 8 + 0xFFFF8]
lidt [rsp + r15 * 8 + 0xFFFF8]
lidt [r14 + r15 * 8 + 0xFFFF8]
