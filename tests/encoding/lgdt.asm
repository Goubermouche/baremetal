; expect: 0f011425000000000f011425ff0000000f0115f9ffffff0f0115f80000000f0115f8ff00000f01100f01100f0190ffff0000410f0197ffff00000f0114300f019430ffff0000410f019437ffff0000420f019438ffff00000f019470f2ff0f000f0194b0f4ff0f000f0194f0f8ff0f000f0194c4f8ff0f00410f0194c7f8ff0f00420f0194fcf8ff0f00430f0194fef8ff0f00

bits 64

lgdt [0x0]
lgdt [0xFF]
lgdt [rel $ + 0x0]
lgdt [rel $ + 0xFF]
lgdt [rel $ + 0xFFFF]
lgdt [rax]
lgdt [rax + 0x0]
lgdt [rax + 0xFFFF]
lgdt [r15 + 0xFFFF]
lgdt [rax + rsi * 1  + 0x0]
lgdt [rax + rsi + 0xFFFF]
lgdt [r15 + rsi + 0xFFFF]
lgdt [rax + r15 + 0xFFFF]
lgdt [rax + rsi * 2 + 0xFFFF2]
lgdt [rax + rsi * 4 + 0xFFFF4]
lgdt [rax + rsi * 8 + 0xFFFF8]
lgdt [rsp + rax * 8 + 0xFFFF8]
lgdt [r15 + rax * 8 + 0xFFFF8]
lgdt [rsp + r15 * 8 + 0xFFFF8]
lgdt [r14 + r15 * 8 + 0xFFFF8]
