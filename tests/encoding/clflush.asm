; expect: 0fae3c25000000000fae3c25ff0000000fae3df9ffffff0fae3df80000000fae3df8ff00000fae380fae380faeb8ffff0000410faebfffff00000fae3c300faebc30ffff0000410faebc37ffff0000420faebc38ffff00000faebc70f2ff0f000faebcb0f4ff0f000faebcf0f8ff0f000faebcc4f8ff0f00410faebcc7f8ff0f00420faebcfcf8ff0f00430faebcfef8ff0f00

bits 64

clflush [0x0]
clflush [0xFF]
clflush [rel $ + 0x0]
clflush [rel $ + 0xFF]
clflush [rel $ + 0xFFFF]
clflush [rax]
clflush [rax + 0x0]
clflush [rax + 0xFFFF]
clflush [r15 + 0xFFFF]
clflush [rax + rsi * 1  + 0x0]
clflush [rax + rsi + 0xFFFF]
clflush [r15 + rsi + 0xFFFF]
clflush [rax + r15 + 0xFFFF]
clflush [rax + rsi * 2 + 0xFFFF2]
clflush [rax + rsi * 4 + 0xFFFF4]
clflush [rax + rsi * 8 + 0xFFFF8]
clflush [rsp + rax * 8 + 0xFFFF8]
clflush [r15 + rax * 8 + 0xFFFF8]
clflush [rsp + r15 * 8 + 0xFFFF8]
clflush [r14 + r15 * 8 + 0xFFFF8]
