; expect: 0fae2425000000000fae2425ff0000000fae25f9ffffff0fae25f80000000fae25f8ff00000fae200fae200faea0ffff0000410faea7ffff00000fae24300faea430ffff0000410faea437ffff0000420faea438ffff00000faea470f2ff0f000faea4b0f4ff0f000faea4f0f8ff0f000faea4c4f8ff0f00410faea4c7f8ff0f00420faea4fcf8ff0f00430faea4fef8ff0f00

bits 64

xsave [0x0]
xsave [0xFF]
xsave [rel $ + 0x0]
xsave [rel $ + 0xFF]
xsave [rel $ + 0xFFFF]
xsave [rax]
xsave [rax + 0x0]
xsave [rax + 0xFFFF]
xsave [r15 + 0xFFFF]
xsave [rax + rsi * 1  + 0x0]
xsave [rax + rsi + 0xFFFF]
xsave [r15 + rsi + 0xFFFF]
xsave [rax + r15 + 0xFFFF]
xsave [rax + rsi * 2 + 0xFFFF2]
xsave [rax + rsi * 4 + 0xFFFF4]
xsave [rax + rsi * 8 + 0xFFFF8]
xsave [rsp + rax * 8 + 0xFFFF8]
xsave [r15 + rax * 8 + 0xFFFF8]
xsave [rsp + r15 * 8 + 0xFFFF8]
xsave [r14 + r15 * 8 + 0xFFFF8]
