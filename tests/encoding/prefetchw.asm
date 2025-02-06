; expect: 0f0d0c25000000000f0d0c25ff0000000f0d0df9ffffff0f0d0df80000000f0d0df8ff00000f0d080f0d080f0d88ffff0000410f0d8fffff00000f0d0c300f0d8c30ffff0000410f0d8c37ffff0000420f0d8c38ffff00000f0d8c70f2ff0f000f0d8cb0f4ff0f000f0d8cf0f8ff0f000f0d8cc4f8ff0f00410f0d8cc7f8ff0f00420f0d8cfcf8ff0f00430f0d8cfef8ff0f00

bits 64

prefetchw [0x0]
prefetchw [0xFF]
prefetchw [rel $ + 0x0]
prefetchw [rel $ + 0xFF]
prefetchw [rel $ + 0xFFFF]
prefetchw [rax]
prefetchw [rax + 0x0]
prefetchw [rax + 0xFFFF]
prefetchw [r15 + 0xFFFF]
prefetchw [rax + rsi * 1  + 0x0]
prefetchw [rax + rsi + 0xFFFF]
prefetchw [r15 + rsi + 0xFFFF]
prefetchw [rax + r15 + 0xFFFF]
prefetchw [rax + rsi * 2 + 0xFFFF2]
prefetchw [rax + rsi * 4 + 0xFFFF4]
prefetchw [rax + rsi * 8 + 0xFFFF8]
prefetchw [rsp + rax * 8 + 0xFFFF8]
prefetchw [r15 + rax * 8 + 0xFFFF8]
prefetchw [rsp + r15 * 8 + 0xFFFF8]
prefetchw [r14 + r15 * 8 + 0xFFFF8]
