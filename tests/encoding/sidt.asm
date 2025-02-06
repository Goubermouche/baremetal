; expect: 0f010c25000000000f010c25ff0000000f010df9ffffff0f010df80000000f010df8ff00000f01080f01080f0188ffff0000410f018fffff00000f010c300f018c30ffff0000410f018c37ffff0000420f018c38ffff00000f018c70f2ff0f000f018cb0f4ff0f000f018cf0f8ff0f000f018cc4f8ff0f00410f018cc7f8ff0f00420f018cfcf8ff0f00430f018cfef8ff0f00

bits 64

sidt [0x0]
sidt [0xFF]
sidt [rel $ + 0x0]
sidt [rel $ + 0xFF]
sidt [rel $ + 0xFFFF]
sidt [rax]
sidt [rax + 0x0]
sidt [rax + 0xFFFF]
sidt [r15 + 0xFFFF]
sidt [rax + rsi * 1  + 0x0]
sidt [rax + rsi + 0xFFFF]
sidt [r15 + rsi + 0xFFFF]
sidt [rax + r15 + 0xFFFF]
sidt [rax + rsi * 2 + 0xFFFF2]
sidt [rax + rsi * 4 + 0xFFFF4]
sidt [rax + rsi * 8 + 0xFFFF8]
sidt [rsp + rax * 8 + 0xFFFF8]
sidt [r15 + rax * 8 + 0xFFFF8]
sidt [rsp + r15 * 8 + 0xFFFF8]
sidt [r14 + r15 * 8 + 0xFFFF8]
