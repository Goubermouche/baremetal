; expect: 480fae0c2500000000480fae0c25ff000000480fae0df8ffffff480fae0df7000000480fae0df7ff0000480fae08480fae08480fae88ffff0000490fae8fffff0000480fae0c30480fae8c30ffff0000490fae8c37ffff00004a0fae8c38ffff0000480fae8c70f2ff0f00480fae8cb0f4ff0f00480fae8cf0f8ff0f00480fae8cc4f8ff0f00490fae8cc7f8ff0f004a0fae8cfcf8ff0f004b0fae8cfef8ff0f00

bits 64

fxrstor64 [0x0]
fxrstor64 [0xFF]
fxrstor64 [rel $ + 0x0]
fxrstor64 [rel $ + 0xFF]
fxrstor64 [rel $ + 0xFFFF]
fxrstor64 [rax]
fxrstor64 [rax + 0x0]
fxrstor64 [rax + 0xFFFF]
fxrstor64 [r15 + 0xFFFF]
fxrstor64 [rax + rsi * 1  + 0x0]
fxrstor64 [rax + rsi + 0xFFFF]
fxrstor64 [r15 + rsi + 0xFFFF]
fxrstor64 [rax + r15 + 0xFFFF]
fxrstor64 [rax + rsi * 2 + 0xFFFF2]
fxrstor64 [rax + rsi * 4 + 0xFFFF4]
fxrstor64 [rax + rsi * 8 + 0xFFFF8]
fxrstor64 [rsp + rax * 8 + 0xFFFF8]
fxrstor64 [r15 + rax * 8 + 0xFFFF8]
fxrstor64 [rsp + r15 * 8 + 0xFFFF8]
fxrstor64 [r14 + r15 * 8 + 0xFFFF8]
