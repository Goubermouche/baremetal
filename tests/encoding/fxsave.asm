; expect: 0fae0425000000000fae0425ff0000000fae05f9ffffff0fae05f80000000fae05f8ff00000fae000fae000fae80ffff0000410fae87ffff00000fae04300fae8430ffff0000410fae8437ffff0000420fae8438ffff00000fae8470f2ff0f000fae84b0f4ff0f000fae84f0f8ff0f000fae84c4f8ff0f00410fae84c7f8ff0f00420fae84fcf8ff0f00430fae84fef8ff0f00

bits 64

fxsave [0x0]
fxsave [0xFF]
fxsave [rel $ + 0x0]
fxsave [rel $ + 0xFF]
fxsave [rel $ + 0xFFFF]
fxsave [rax]
fxsave [rax + 0x0]
fxsave [rax + 0xFFFF]
fxsave [r15 + 0xFFFF]
fxsave [rax + rsi * 1  + 0x0]
fxsave [rax + rsi + 0xFFFF]
fxsave [r15 + rsi + 0xFFFF]
fxsave [rax + r15 + 0xFFFF]
fxsave [rax + rsi * 2 + 0xFFFF2]
fxsave [rax + rsi * 4 + 0xFFFF4]
fxsave [rax + rsi * 8 + 0xFFFF8]
fxsave [rsp + rax * 8 + 0xFFFF8]
fxsave [r15 + rax * 8 + 0xFFFF8]
fxsave [rsp + r15 * 8 + 0xFFFF8]
fxsave [r14 + r15 * 8 + 0xFFFF8]
