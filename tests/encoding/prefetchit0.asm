; expect: 0f183c25000000000f183c25ff0000000f183df9ffffff0f183df80000000f183df8ff00000f18380f18380f18b8ffff0000410f18bfffff00000f183c300f18bc30ffff0000410f18bc37ffff0000420f18bc38ffff00000f18bc70f2ff0f000f18bcb0f4ff0f000f18bcf0f8ff0f000f18bcc4f8ff0f00410f18bcc7f8ff0f00420f18bcfcf8ff0f00430f18bcfef8ff0f00

bits 64

prefetchit0 [0x0]
prefetchit0 [0xFF]
prefetchit0 [rel $ + 0x0]
prefetchit0 [rel $ + 0xFF]
prefetchit0 [rel $ + 0xFFFF]
prefetchit0 [rax]
prefetchit0 [rax + 0x0]
prefetchit0 [rax + 0xFFFF]
prefetchit0 [r15 + 0xFFFF]
prefetchit0 [rax + rsi * 1  + 0x0]
prefetchit0 [rax + rsi + 0xFFFF]
prefetchit0 [r15 + rsi + 0xFFFF]
prefetchit0 [rax + r15 + 0xFFFF]
prefetchit0 [rax + rsi * 2 + 0xFFFF2]
prefetchit0 [rax + rsi * 4 + 0xFFFF4]
prefetchit0 [rax + rsi * 8 + 0xFFFF8]
prefetchit0 [rsp + rax * 8 + 0xFFFF8]
prefetchit0 [r15 + rax * 8 + 0xFFFF8]
prefetchit0 [rsp + r15 * 8 + 0xFFFF8]
prefetchit0 [r14 + r15 * 8 + 0xFFFF8]
