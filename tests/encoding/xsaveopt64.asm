; expect: 480fae342500000000480fae3425ff000000480fae35f8ffffff480fae35f7000000480fae35f7ff0000480fae30480fae30480faeb0ffff0000490faeb7ffff0000480fae3430480faeb430ffff0000490faeb437ffff00004a0faeb438ffff0000480faeb470f2ff0f00480faeb4b0f4ff0f00480faeb4f0f8ff0f00480faeb4c4f8ff0f00490faeb4c7f8ff0f004a0faeb4fcf8ff0f004b0faeb4fef8ff0f00

bits 64

xsaveopt64 [0x0]
xsaveopt64 [0xFF]
xsaveopt64 [rel $ + 0x0]
xsaveopt64 [rel $ + 0xFF]
xsaveopt64 [rel $ + 0xFFFF]
xsaveopt64 [rax]
xsaveopt64 [rax + 0x0]
xsaveopt64 [rax + 0xFFFF]
xsaveopt64 [r15 + 0xFFFF]
xsaveopt64 [rax + rsi * 1  + 0x0]
xsaveopt64 [rax + rsi + 0xFFFF]
xsaveopt64 [r15 + rsi + 0xFFFF]
xsaveopt64 [rax + r15 + 0xFFFF]
xsaveopt64 [rax + rsi * 2 + 0xFFFF2]
xsaveopt64 [rax + rsi * 4 + 0xFFFF4]
xsaveopt64 [rax + rsi * 8 + 0xFFFF8]
xsaveopt64 [rsp + rax * 8 + 0xFFFF8]
xsaveopt64 [r15 + rax * 8 + 0xFFFF8]
xsaveopt64 [rsp + r15 * 8 + 0xFFFF8]
xsaveopt64 [r14 + r15 * 8 + 0xFFFF8]
