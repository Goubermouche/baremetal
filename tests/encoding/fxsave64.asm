; expect: 480fae042500000000480fae0425ff000000480fae05f8ffffff480fae05f7000000480fae05f7ff0000480fae00480fae00480fae80ffff0000490fae87ffff0000480fae0430480fae8430ffff0000490fae8437ffff00004a0fae8438ffff0000480fae8470f2ff0f00480fae84b0f4ff0f00480fae84f0f8ff0f00480fae84c4f8ff0f00490fae84c7f8ff0f004a0fae84fcf8ff0f004b0fae84fef8ff0f00

bits 64

fxsave64 [0x0]
fxsave64 [0xFF]
fxsave64 [rel $ + 0x0]
fxsave64 [rel $ + 0xFF]
fxsave64 [rel $ + 0xFFFF]
fxsave64 [rax]
fxsave64 [rax + 0x0]
fxsave64 [rax + 0xFFFF]
fxsave64 [r15 + 0xFFFF]
fxsave64 [rax + rsi * 1  + 0x0]
fxsave64 [rax + rsi + 0xFFFF]
fxsave64 [r15 + rsi + 0xFFFF]
fxsave64 [rax + r15 + 0xFFFF]
fxsave64 [rax + rsi * 2 + 0xFFFF2]
fxsave64 [rax + rsi * 4 + 0xFFFF4]
fxsave64 [rax + rsi * 8 + 0xFFFF8]
fxsave64 [rsp + rax * 8 + 0xFFFF8]
fxsave64 [r15 + rax * 8 + 0xFFFF8]
fxsave64 [rsp + r15 * 8 + 0xFFFF8]
fxsave64 [r14 + r15 * 8 + 0xFFFF8]
