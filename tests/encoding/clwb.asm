; expect: 660fae342500000000660fae3425ff000000660fae35f8ffffff660fae35f7000000660fae35f7ff0000660fae30660fae30660faeb0ffff000066410faeb7ffff0000660fae3430660faeb430ffff000066410faeb437ffff000066420faeb438ffff0000660faeb470f2ff0f00660faeb4b0f4ff0f00660faeb4f0f8ff0f00660faeb4c4f8ff0f0066410faeb4c7f8ff0f0066420faeb4fcf8ff0f0066430faeb4fef8ff0f00

bits 64

clwb [0x0]
clwb [0xFF]
clwb [rel $ + 0x0]
clwb [rel $ + 0xFF]
clwb [rel $ + 0xFFFF]
clwb [rax]
clwb [rax + 0x0]
clwb [rax + 0xFFFF]
clwb [r15 + 0xFFFF]
clwb [rax + rsi * 1  + 0x0]
clwb [rax + rsi + 0xFFFF]
clwb [r15 + rsi + 0xFFFF]
clwb [rax + r15 + 0xFFFF]
clwb [rax + rsi * 2 + 0xFFFF2]
clwb [rax + rsi * 4 + 0xFFFF4]
clwb [rax + rsi * 8 + 0xFFFF8]
clwb [rsp + rax * 8 + 0xFFFF8]
clwb [r15 + rax * 8 + 0xFFFF8]
clwb [rsp + r15 * 8 + 0xFFFF8]
clwb [r14 + r15 * 8 + 0xFFFF8]
