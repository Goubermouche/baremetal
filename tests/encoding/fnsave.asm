; expect: dd342500000000dd3425ff000000dd35faffffffdd35f9000000dd35f9ff0000dd30dd30ddb0ffff000041ddb7ffff0000dd3430ddb430ffff000041ddb437ffff000042ddb438ffff0000ddb470f2ff0f00ddb4b0f4ff0f00ddb4f0f8ff0f00ddb4c4f8ff0f0041ddb4c7f8ff0f0042ddb4fcf8ff0f0043ddb4fef8ff0f00

bits 64

fnsave [0x0]
fnsave [0xFF]
fnsave [rel $ + 0x0]
fnsave [rel $ + 0xFF]
fnsave [rel $ + 0xFFFF]
fnsave [rax]
fnsave [rax + 0x0]
fnsave [rax + 0xFFFF]
fnsave [r15 + 0xFFFF]
fnsave [rax + rsi * 1  + 0x0]
fnsave [rax + rsi + 0xFFFF]
fnsave [r15 + rsi + 0xFFFF]
fnsave [rax + r15 + 0xFFFF]
fnsave [rax + rsi * 2 + 0xFFFF2]
fnsave [rax + rsi * 4 + 0xFFFF4]
fnsave [rax + rsi * 8 + 0xFFFF8]
fnsave [rsp + rax * 8 + 0xFFFF8]
fnsave [r15 + rax * 8 + 0xFFFF8]
fnsave [rsp + r15 * 8 + 0xFFFF8]
fnsave [r14 + r15 * 8 + 0xFFFF8]
