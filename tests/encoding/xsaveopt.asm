; expect: 0fae3425000000000fae3425ff0000000fae35f9ffffff0fae35f80000000fae35f8ff00000fae300fae300faeb0ffff0000410faeb7ffff00000fae34300faeb430ffff0000410faeb437ffff0000420faeb438ffff00000faeb470f2ff0f000faeb4b0f4ff0f000faeb4f0f8ff0f000faeb4c4f8ff0f00410faeb4c7f8ff0f00420faeb4fcf8ff0f00430faeb4fef8ff0f00

bits 64

xsaveopt [0x0]
xsaveopt [0xFF]
xsaveopt [rel $ + 0x0]
xsaveopt [rel $ + 0xFF]
xsaveopt [rel $ + 0xFFFF]
xsaveopt [rax]
xsaveopt [rax + 0x0]
xsaveopt [rax + 0xFFFF]
xsaveopt [r15 + 0xFFFF]
xsaveopt [rax + rsi * 1  + 0x0]
xsaveopt [rax + rsi + 0xFFFF]
xsaveopt [r15 + rsi + 0xFFFF]
xsaveopt [rax + r15 + 0xFFFF]
xsaveopt [rax + rsi * 2 + 0xFFFF2]
xsaveopt [rax + rsi * 4 + 0xFFFF4]
xsaveopt [rax + rsi * 8 + 0xFFFF8]
xsaveopt [rsp + rax * 8 + 0xFFFF8]
xsaveopt [r15 + rax * 8 + 0xFFFF8]
xsaveopt [rsp + r15 * 8 + 0xFFFF8]
xsaveopt [r14 + r15 * 8 + 0xFFFF8]
