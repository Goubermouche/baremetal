; expect: 660fae3c2500000000660fae3c25ff000000660fae3df8ffffff660fae3df7000000660fae3df7ff0000660fae38660fae38660faeb8ffff000066410faebfffff0000660fae3c30660faebc30ffff000066410faebc37ffff000066420faebc38ffff0000660faebc70f2ff0f00660faebcb0f4ff0f00660faebcf0f8ff0f00660faebcc4f8ff0f0066410faebcc7f8ff0f0066420faebcfcf8ff0f0066430faebcfef8ff0f00

bits 64

clflushopt [0x0]
clflushopt [0xFF]
clflushopt [rel $ + 0x0]
clflushopt [rel $ + 0xFF]
clflushopt [rel $ + 0xFFFF]
clflushopt [rax]
clflushopt [rax + 0x0]
clflushopt [rax + 0xFFFF]
clflushopt [r15 + 0xFFFF]
clflushopt [rax + rsi * 1  + 0x0]
clflushopt [rax + rsi + 0xFFFF]
clflushopt [r15 + rsi + 0xFFFF]
clflushopt [rax + r15 + 0xFFFF]
clflushopt [rax + rsi * 2 + 0xFFFF2]
clflushopt [rax + rsi * 4 + 0xFFFF4]
clflushopt [rax + rsi * 8 + 0xFFFF8]
clflushopt [rsp + rax * 8 + 0xFFFF8]
clflushopt [r15 + rax * 8 + 0xFFFF8]
clflushopt [rsp + r15 * 8 + 0xFFFF8]
clflushopt [r14 + r15 * 8 + 0xFFFF8]
