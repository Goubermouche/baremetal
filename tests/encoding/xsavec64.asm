; expect: 480fc7242500000000480fc72425ff000000480fc725f8ffffff480fc725f7000000480fc725f7ff0000480fc720480fc720480fc7a0ffff0000490fc7a7ffff0000480fc72430480fc7a430ffff0000490fc7a437ffff00004a0fc7a438ffff0000480fc7a470f2ff0f00480fc7a4b0f4ff0f00480fc7a4f0f8ff0f00480fc7a4c4f8ff0f00490fc7a4c7f8ff0f004a0fc7a4fcf8ff0f004b0fc7a4fef8ff0f00

bits 64

xsavec64 [0x0]
xsavec64 [0xFF]
xsavec64 [rel $ + 0x0]
xsavec64 [rel $ + 0xFF]
xsavec64 [rel $ + 0xFFFF]
xsavec64 [rax]
xsavec64 [rax + 0x0]
xsavec64 [rax + 0xFFFF]
xsavec64 [r15 + 0xFFFF]
xsavec64 [rax + rsi * 1  + 0x0]
xsavec64 [rax + rsi + 0xFFFF]
xsavec64 [r15 + rsi + 0xFFFF]
xsavec64 [rax + r15 + 0xFFFF]
xsavec64 [rax + rsi * 2 + 0xFFFF2]
xsavec64 [rax + rsi * 4 + 0xFFFF4]
xsavec64 [rax + rsi * 8 + 0xFFFF8]
xsavec64 [rsp + rax * 8 + 0xFFFF8]
xsavec64 [r15 + rax * 8 + 0xFFFF8]
xsavec64 [rsp + r15 * 8 + 0xFFFF8]
xsavec64 [r14 + r15 * 8 + 0xFFFF8]
