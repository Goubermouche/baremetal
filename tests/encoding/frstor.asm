; expect: dd242500000000dd2425ff000000dd25faffffffdd25f9000000dd25f9ff0000dd20dd20dda0ffff000041dda7ffff0000dd2430dda430ffff000041dda437ffff000042dda438ffff0000dda470f2ff0f00dda4b0f4ff0f00dda4f0f8ff0f00dda4c4f8ff0f0041dda4c7f8ff0f0042dda4fcf8ff0f0043dda4fef8ff0f00

bits 64

frstor [0x0]
frstor [0xFF]
frstor [rel $ + 0x0]
frstor [rel $ + 0xFF]
frstor [rel $ + 0xFFFF]
frstor [rax]
frstor [rax + 0x0]
frstor [rax + 0xFFFF]
frstor [r15 + 0xFFFF]
frstor [rax + rsi * 1  + 0x0]
frstor [rax + rsi + 0xFFFF]
frstor [r15 + rsi + 0xFFFF]
frstor [rax + r15 + 0xFFFF]
frstor [rax + rsi * 2 + 0xFFFF2]
frstor [rax + rsi * 4 + 0xFFFF4]
frstor [rax + rsi * 8 + 0xFFFF8]
frstor [rsp + rax * 8 + 0xFFFF8]
frstor [r15 + rax * 8 + 0xFFFF8]
frstor [rsp + r15 * 8 + 0xFFFF8]
frstor [r14 + r15 * 8 + 0xFFFF8]
