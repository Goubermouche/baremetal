; expect: 0f010425000000000f010425ff0000000f0105f9ffffff0f0105f80000000f0105f8ff00000f01000f01000f0180ffff0000410f0187ffff00000f0104300f018430ffff0000410f018437ffff0000420f018438ffff00000f018470f2ff0f000f0184b0f4ff0f000f0184f0f8ff0f000f0184c4f8ff0f00410f0184c7f8ff0f00420f0184fcf8ff0f00430f0184fef8ff0f00

bits 64

sgdt [0x0]
sgdt [0xFF]
sgdt [rel $ + 0x0]
sgdt [rel $ + 0xFF]
sgdt [rel $ + 0xFFFF]
sgdt [rax]
sgdt [rax + 0x0]
sgdt [rax + 0xFFFF]
sgdt [r15 + 0xFFFF]
sgdt [rax + rsi * 1  + 0x0]
sgdt [rax + rsi + 0xFFFF]
sgdt [r15 + rsi + 0xFFFF]
sgdt [rax + r15 + 0xFFFF]
sgdt [rax + rsi * 2 + 0xFFFF2]
sgdt [rax + rsi * 4 + 0xFFFF4]
sgdt [rax + rsi * 8 + 0xFFFF8]
sgdt [rsp + rax * 8 + 0xFFFF8]
sgdt [r15 + rax * 8 + 0xFFFF8]
sgdt [rsp + r15 * 8 + 0xFFFF8]
sgdt [r14 + r15 * 8 + 0xFFFF8]
