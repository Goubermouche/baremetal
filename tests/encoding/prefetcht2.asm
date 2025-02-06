; expect: 0f181c25000000000f181c25ff0000000f181df9ffffff0f181df80000000f181df8ff00000f18180f18180f1898ffff0000410f189fffff00000f181c300f189c30ffff0000410f189c37ffff0000420f189c38ffff00000f189c70f2ff0f000f189cb0f4ff0f000f189cf0f8ff0f000f189cc4f8ff0f00410f189cc7f8ff0f00420f189cfcf8ff0f00430f189cfef8ff0f00

bits 64

prefetcht2 [0x0]
prefetcht2 [0xFF]
prefetcht2 [rel $ + 0x0]
prefetcht2 [rel $ + 0xFF]
prefetcht2 [rel $ + 0xFFFF]
prefetcht2 [rax]
prefetcht2 [rax + 0x0]
prefetcht2 [rax + 0xFFFF]
prefetcht2 [r15 + 0xFFFF]
prefetcht2 [rax + rsi * 1  + 0x0]
prefetcht2 [rax + rsi + 0xFFFF]
prefetcht2 [r15 + rsi + 0xFFFF]
prefetcht2 [rax + r15 + 0xFFFF]
prefetcht2 [rax + rsi * 2 + 0xFFFF2]
prefetcht2 [rax + rsi * 4 + 0xFFFF4]
prefetcht2 [rax + rsi * 8 + 0xFFFF8]
prefetcht2 [rsp + rax * 8 + 0xFFFF8]
prefetcht2 [r15 + rax * 8 + 0xFFFF8]
prefetcht2 [rsp + r15 * 8 + 0xFFFF8]
prefetcht2 [r14 + r15 * 8 + 0xFFFF8]
