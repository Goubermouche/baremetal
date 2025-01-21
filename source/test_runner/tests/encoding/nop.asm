; expect: 90660f1fc1660f1fc2660f1fc366410f1fc7660f1f042500000000660f1f0425ff000000660f1f05f8ffffff660f1f05f7000000660f1f05f7ff0000660f1f00660f1f00660f1f80ffff000066410f1f87ffff0000660f1f0430660f1f8430ffff000066410f1f8437ffff000066420f1f8438ffff0000660f1f8470f2ff0f00660f1f84b0f4ff0f00660f1f84f0f8ff0f00660f1f84c4f8ff0f0066410f1f84c7f8ff0f0066420f1f84fcf8ff0f0066430f1f84fef8ff0f000f1fc10f1fc3410f1fc70f1f0425000000000f1f0425ff0000000f1f05f9ffffff0f1f05f80000000f1f05f8ff00000f1f000f1f000f1f80ffff0000410f1f87ffff00000f1f04300f1f8430ffff0000410f1f8437ffff0000420f1f8438ffff00000f1f8470f2ff0f000f1f84b0f4ff0f000f1f84f0f8ff0f000f1f84c4f8ff0f00410f1f84c7f8ff0f00420f1f84fcf8ff0f00430f1f84fef8ff0f00

nop 
nop cx
nop dx
nop bx
nop r15w
nop word [0x0]
nop word [0xFF]
nop word [rel $ + 0x0]
nop word [rel $ + 0xFF]
nop word [rel $ + 0xFFFF]
nop word [rax]
nop word [rax + 0x0]
nop word [rax + 0xFFFF]
nop word [r15 + 0xFFFF]
nop word [rax + rsi * 1  + 0x0]
nop word [rax + rsi + 0xFFFF]
nop word [r15 + rsi + 0xFFFF]
nop word [rax + r15 + 0xFFFF]
nop word [rax + rsi * 2 + 0xFFFF2]
nop word [rax + rsi * 4 + 0xFFFF4]
nop word [rax + rsi * 8 + 0xFFFF8]
nop word [rsp + rax * 8 + 0xFFFF8]
nop word [r15 + rax * 8 + 0xFFFF8]
nop word [rsp + r15 * 8 + 0xFFFF8]
nop word [r14 + r15 * 8 + 0xFFFF8]
nop ecx
nop ebx
nop r15d
nop dword [0x0]
nop dword [0xFF]
nop dword [rel $ + 0x0]
nop dword [rel $ + 0xFF]
nop dword [rel $ + 0xFFFF]
nop dword [rax]
nop dword [rax + 0x0]
nop dword [rax + 0xFFFF]
nop dword [r15 + 0xFFFF]
nop dword [rax + rsi * 1  + 0x0]
nop dword [rax + rsi + 0xFFFF]
nop dword [r15 + rsi + 0xFFFF]
nop dword [rax + r15 + 0xFFFF]
nop dword [rax + rsi * 2 + 0xFFFF2]
nop dword [rax + rsi * 4 + 0xFFFF4]
nop dword [rax + rsi * 8 + 0xFFFF8]
nop dword [rsp + rax * 8 + 0xFFFF8]
nop dword [r15 + rax * 8 + 0xFFFF8]
nop dword [rsp + r15 * 8 + 0xFFFF8]
nop dword [r14 + r15 * 8 + 0xFFFF8]