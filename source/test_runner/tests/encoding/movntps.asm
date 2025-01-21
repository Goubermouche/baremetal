; expect: 0f2b0425000000000f2b0c2500000000440f2b3c25000000000f2b0425ff0000000f2b0c25ff000000440f2b3c25ff0000000f2b05f9ffffff0f2b0df9ffffff440f2b3df8ffffff0f2b05f80000000f2b0df8000000440f2b3df70000000f2b05f8ff00000f2b0df8ff0000440f2b3df7ff00000f2b000f2b08440f2b380f2b000f2b08440f2b380f2b80ffff00000f2b88ffff0000440f2bb8ffff0000410f2b87ffff0000410f2b8fffff0000450f2bbfffff00000f2b04300f2b0c30440f2b3c300f2b8430ffff00000f2b8c30ffff0000440f2bbc30ffff0000410f2b8437ffff0000410f2b8c37ffff0000450f2bbc37ffff0000420f2b8438ffff0000420f2b8c38ffff0000460f2bbc38ffff00000f2b8470f2ff0f000f2b8c70f2ff0f00440f2bbc70f2ff0f000f2b84b0f4ff0f000f2b8cb0f4ff0f00440f2bbcb0f4ff0f000f2b84f0f8ff0f000f2b8cf0f8ff0f00440f2bbcf0f8ff0f000f2b84c4f8ff0f000f2b8cc4f8ff0f00440f2bbcc4f8ff0f00410f2b84c7f8ff0f00410f2b8cc7f8ff0f00450f2bbcc7f8ff0f00420f2b84fcf8ff0f00420f2b8cfcf8ff0f00460f2bbcfcf8ff0f00430f2b84fef8ff0f00430f2b8cfef8ff0f00470f2bbcfef8ff0f00

movntps [0x0], xmm0
movntps [0x0], xmm1
movntps [0x0], xmm15
movntps [0xFF], xmm0
movntps [0xFF], xmm1
movntps [0xFF], xmm15
movntps [rel $ + 0x0], xmm0
movntps [rel $ + 0x0], xmm1
movntps [rel $ + 0x0], xmm15
movntps [rel $ + 0xFF], xmm0
movntps [rel $ + 0xFF], xmm1
movntps [rel $ + 0xFF], xmm15
movntps [rel $ + 0xFFFF], xmm0
movntps [rel $ + 0xFFFF], xmm1
movntps [rel $ + 0xFFFF], xmm15
movntps [rax], xmm0
movntps [rax], xmm1
movntps [rax], xmm15
movntps [rax + 0x0], xmm0
movntps [rax + 0x0], xmm1
movntps [rax + 0x0], xmm15
movntps [rax + 0xFFFF], xmm0
movntps [rax + 0xFFFF], xmm1
movntps [rax + 0xFFFF], xmm15
movntps [r15 + 0xFFFF], xmm0
movntps [r15 + 0xFFFF], xmm1
movntps [r15 + 0xFFFF], xmm15
movntps [rax + rsi * 1  + 0x0], xmm0
movntps [rax + rsi * 1  + 0x0], xmm1
movntps [rax + rsi * 1  + 0x0], xmm15
movntps [rax + rsi + 0xFFFF], xmm0
movntps [rax + rsi + 0xFFFF], xmm1
movntps [rax + rsi + 0xFFFF], xmm15
movntps [r15 + rsi + 0xFFFF], xmm0
movntps [r15 + rsi + 0xFFFF], xmm1
movntps [r15 + rsi + 0xFFFF], xmm15
movntps [rax + r15 + 0xFFFF], xmm0
movntps [rax + r15 + 0xFFFF], xmm1
movntps [rax + r15 + 0xFFFF], xmm15
movntps [rax + rsi * 2 + 0xFFFF2], xmm0
movntps [rax + rsi * 2 + 0xFFFF2], xmm1
movntps [rax + rsi * 2 + 0xFFFF2], xmm15
movntps [rax + rsi * 4 + 0xFFFF4], xmm0
movntps [rax + rsi * 4 + 0xFFFF4], xmm1
movntps [rax + rsi * 4 + 0xFFFF4], xmm15
movntps [rax + rsi * 8 + 0xFFFF8], xmm0
movntps [rax + rsi * 8 + 0xFFFF8], xmm1
movntps [rax + rsi * 8 + 0xFFFF8], xmm15
movntps [rsp + rax * 8 + 0xFFFF8], xmm0
movntps [rsp + rax * 8 + 0xFFFF8], xmm1
movntps [rsp + rax * 8 + 0xFFFF8], xmm15
movntps [r15 + rax * 8 + 0xFFFF8], xmm0
movntps [r15 + rax * 8 + 0xFFFF8], xmm1
movntps [r15 + rax * 8 + 0xFFFF8], xmm15
movntps [rsp + r15 * 8 + 0xFFFF8], xmm0
movntps [rsp + r15 * 8 + 0xFFFF8], xmm1
movntps [rsp + r15 * 8 + 0xFFFF8], xmm15
movntps [r14 + r15 * 8 + 0xFFFF8], xmm0
movntps [r14 + r15 * 8 + 0xFFFF8], xmm1
movntps [r14 + r15 * 8 + 0xFFFF8], xmm15