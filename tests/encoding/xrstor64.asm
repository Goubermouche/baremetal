; expect: 480fae2c2500000000480fae2c25ff000000480fae2df8ffffff480fae2df7000000480fae2df7ff0000480fae28480fae28480faea8ffff0000490faeafffff0000480fae2c30480faeac30ffff0000490faeac37ffff00004a0faeac38ffff0000480faeac70f2ff0f00480faeacb0f4ff0f00480faeacf0f8ff0f00480faeacc4f8ff0f00490faeacc7f8ff0f004a0faeacfcf8ff0f004b0faeacfef8ff0f00

bits 64

xrstor64 [0x0]
xrstor64 [0xFF]
xrstor64 [rel $ + 0x0]
xrstor64 [rel $ + 0xFF]
xrstor64 [rel $ + 0xFFFF]
xrstor64 [rax]
xrstor64 [rax + 0x0]
xrstor64 [rax + 0xFFFF]
xrstor64 [r15 + 0xFFFF]
xrstor64 [rax + rsi * 1  + 0x0]
xrstor64 [rax + rsi + 0xFFFF]
xrstor64 [r15 + rsi + 0xFFFF]
xrstor64 [rax + r15 + 0xFFFF]
xrstor64 [rax + rsi * 2 + 0xFFFF2]
xrstor64 [rax + rsi * 4 + 0xFFFF4]
xrstor64 [rax + rsi * 8 + 0xFFFF8]
xrstor64 [rsp + rax * 8 + 0xFFFF8]
xrstor64 [r15 + rax * 8 + 0xFFFF8]
xrstor64 [rsp + r15 * 8 + 0xFFFF8]
xrstor64 [r14 + r15 * 8 + 0xFFFF8]
