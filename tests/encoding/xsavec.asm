; expect: 0fc72425000000000fc72425ff0000000fc725f9ffffff0fc725f80000000fc725f8ff00000fc7200fc7200fc7a0ffff0000410fc7a7ffff00000fc724300fc7a430ffff0000410fc7a437ffff0000420fc7a438ffff00000fc7a470f2ff0f000fc7a4b0f4ff0f000fc7a4f0f8ff0f000fc7a4c4f8ff0f00410fc7a4c7f8ff0f00420fc7a4fcf8ff0f00430fc7a4fef8ff0f00

bits 64

xsavec [0x0]
xsavec [0xFF]
xsavec [rel $ + 0x0]
xsavec [rel $ + 0xFF]
xsavec [rel $ + 0xFFFF]
xsavec [rax]
xsavec [rax + 0x0]
xsavec [rax + 0xFFFF]
xsavec [r15 + 0xFFFF]
xsavec [rax + rsi * 1  + 0x0]
xsavec [rax + rsi + 0xFFFF]
xsavec [r15 + rsi + 0xFFFF]
xsavec [rax + r15 + 0xFFFF]
xsavec [rax + rsi * 2 + 0xFFFF2]
xsavec [rax + rsi * 4 + 0xFFFF4]
xsavec [rax + rsi * 8 + 0xFFFF8]
xsavec [rsp + rax * 8 + 0xFFFF8]
xsavec [r15 + rax * 8 + 0xFFFF8]
xsavec [rsp + r15 * 8 + 0xFFFF8]
xsavec [r14 + r15 * 8 + 0xFFFF8]
