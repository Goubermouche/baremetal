; expect: 480fae242500000000480fae2425ff000000480fae25f8ffffff480fae25f7000000480fae25f7ff0000480fae20480fae20480faea0ffff0000490faea7ffff0000480fae2430480faea430ffff0000490faea437ffff00004a0faea438ffff0000480faea470f2ff0f00480faea4b0f4ff0f00480faea4f0f8ff0f00480faea4c4f8ff0f00490faea4c7f8ff0f004a0faea4fcf8ff0f004b0faea4fef8ff0f00

bits 64

xsave64 [0x0]
xsave64 [0xFF]
xsave64 [rel $ + 0x0]
xsave64 [rel $ + 0xFF]
xsave64 [rel $ + 0xFFFF]
xsave64 [rax]
xsave64 [rax + 0x0]
xsave64 [rax + 0xFFFF]
xsave64 [r15 + 0xFFFF]
xsave64 [rax + rsi * 1  + 0x0]
xsave64 [rax + rsi + 0xFFFF]
xsave64 [r15 + rsi + 0xFFFF]
xsave64 [rax + r15 + 0xFFFF]
xsave64 [rax + rsi * 2 + 0xFFFF2]
xsave64 [rax + rsi * 4 + 0xFFFF4]
xsave64 [rax + rsi * 8 + 0xFFFF8]
xsave64 [rsp + rax * 8 + 0xFFFF8]
xsave64 [r15 + rax * 8 + 0xFFFF8]
xsave64 [rsp + r15 * 8 + 0xFFFF8]
xsave64 [r14 + r15 * 8 + 0xFFFF8]
