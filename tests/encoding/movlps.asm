; expect: 0f130425000000000f130c2500000000440f133c25000000000f130425ff0000000f130c25ff000000440f133c25ff0000000f1305f9ffffff0f130df9ffffff440f133df8ffffff0f1305f80000000f130df8000000440f133df70000000f1305f8ff00000f130df8ff0000440f133df7ff00000f13000f1308440f13380f13000f1308440f13380f1380ffff00000f1388ffff0000440f13b8ffff0000410f1387ffff0000410f138fffff0000450f13bfffff00000f1304300f130c30440f133c300f138430ffff00000f138c30ffff0000440f13bc30ffff0000410f138437ffff0000410f138c37ffff0000450f13bc37ffff0000420f138438ffff0000420f138c38ffff0000460f13bc38ffff00000f138470f2ff0f000f138c70f2ff0f00440f13bc70f2ff0f000f1384b0f4ff0f000f138cb0f4ff0f00440f13bcb0f4ff0f000f1384f0f8ff0f000f138cf0f8ff0f00440f13bcf0f8ff0f000f1384c4f8ff0f000f138cc4f8ff0f00440f13bcc4f8ff0f00410f1384c7f8ff0f00410f138cc7f8ff0f00450f13bcc7f8ff0f00420f1384fcf8ff0f00420f138cfcf8ff0f00460f13bcfcf8ff0f00430f1384fef8ff0f00430f138cfef8ff0f00470f13bcfef8ff0f000f120425000000000f120425ff0000000f1205f9ffffff0f1205f80000000f1205f8ff00000f12000f12000f1280ffff0000410f1287ffff00000f1204300f128430ffff0000410f128437ffff0000420f128438ffff00000f128470f2ff0f000f1284b0f4ff0f000f1284f0f8ff0f000f1284c4f8ff0f00410f1284c7f8ff0f00420f1284fcf8ff0f00430f1284fef8ff0f000f120c25000000000f120c25ff0000000f120df9ffffff0f120df80000000f120df8ff00000f12080f12080f1288ffff0000410f128fffff00000f120c300f128c30ffff0000410f128c37ffff0000420f128c38ffff00000f128c70f2ff0f000f128cb0f4ff0f000f128cf0f8ff0f000f128cc4f8ff0f00410f128cc7f8ff0f00420f128cfcf8ff0f00430f128cfef8ff0f00440f123c2500000000440f123c25ff000000440f123df8ffffff440f123df7000000440f123df7ff0000440f1238440f1238440f12b8ffff0000450f12bfffff0000440f123c30440f12bc30ffff0000450f12bc37ffff0000460f12bc38ffff0000440f12bc70f2ff0f00440f12bcb0f4ff0f00440f12bcf0f8ff0f00440f12bcc4f8ff0f00450f12bcc7f8ff0f00460f12bcfcf8ff0f00470f12bcfef8ff0f00

movlps qword [0x0], xmm0
movlps qword [0x0], xmm1
movlps qword [0x0], xmm15
movlps qword [0xFF], xmm0
movlps qword [0xFF], xmm1
movlps qword [0xFF], xmm15
movlps qword [rel $ + 0x0], xmm0
movlps qword [rel $ + 0x0], xmm1
movlps qword [rel $ + 0x0], xmm15
movlps qword [rel $ + 0xFF], xmm0
movlps qword [rel $ + 0xFF], xmm1
movlps qword [rel $ + 0xFF], xmm15
movlps qword [rel $ + 0xFFFF], xmm0
movlps qword [rel $ + 0xFFFF], xmm1
movlps qword [rel $ + 0xFFFF], xmm15
movlps qword [rax], xmm0
movlps qword [rax], xmm1
movlps qword [rax], xmm15
movlps qword [rax + 0x0], xmm0
movlps qword [rax + 0x0], xmm1
movlps qword [rax + 0x0], xmm15
movlps qword [rax + 0xFFFF], xmm0
movlps qword [rax + 0xFFFF], xmm1
movlps qword [rax + 0xFFFF], xmm15
movlps qword [r15 + 0xFFFF], xmm0
movlps qword [r15 + 0xFFFF], xmm1
movlps qword [r15 + 0xFFFF], xmm15
movlps qword [rax + rsi * 1  + 0x0], xmm0
movlps qword [rax + rsi * 1  + 0x0], xmm1
movlps qword [rax + rsi * 1  + 0x0], xmm15
movlps qword [rax + rsi + 0xFFFF], xmm0
movlps qword [rax + rsi + 0xFFFF], xmm1
movlps qword [rax + rsi + 0xFFFF], xmm15
movlps qword [r15 + rsi + 0xFFFF], xmm0
movlps qword [r15 + rsi + 0xFFFF], xmm1
movlps qword [r15 + rsi + 0xFFFF], xmm15
movlps qword [rax + r15 + 0xFFFF], xmm0
movlps qword [rax + r15 + 0xFFFF], xmm1
movlps qword [rax + r15 + 0xFFFF], xmm15
movlps qword [rax + rsi * 2 + 0xFFFF2], xmm0
movlps qword [rax + rsi * 2 + 0xFFFF2], xmm1
movlps qword [rax + rsi * 2 + 0xFFFF2], xmm15
movlps qword [rax + rsi * 4 + 0xFFFF4], xmm0
movlps qword [rax + rsi * 4 + 0xFFFF4], xmm1
movlps qword [rax + rsi * 4 + 0xFFFF4], xmm15
movlps qword [rax + rsi * 8 + 0xFFFF8], xmm0
movlps qword [rax + rsi * 8 + 0xFFFF8], xmm1
movlps qword [rax + rsi * 8 + 0xFFFF8], xmm15
movlps qword [rsp + rax * 8 + 0xFFFF8], xmm0
movlps qword [rsp + rax * 8 + 0xFFFF8], xmm1
movlps qword [rsp + rax * 8 + 0xFFFF8], xmm15
movlps qword [r15 + rax * 8 + 0xFFFF8], xmm0
movlps qword [r15 + rax * 8 + 0xFFFF8], xmm1
movlps qword [r15 + rax * 8 + 0xFFFF8], xmm15
movlps qword [rsp + r15 * 8 + 0xFFFF8], xmm0
movlps qword [rsp + r15 * 8 + 0xFFFF8], xmm1
movlps qword [rsp + r15 * 8 + 0xFFFF8], xmm15
movlps qword [r14 + r15 * 8 + 0xFFFF8], xmm0
movlps qword [r14 + r15 * 8 + 0xFFFF8], xmm1
movlps qword [r14 + r15 * 8 + 0xFFFF8], xmm15
movlps xmm0, qword [0x0]
movlps xmm0, qword [0xFF]
movlps xmm0, qword [rel $ + 0x0]
movlps xmm0, qword [rel $ + 0xFF]
movlps xmm0, qword [rel $ + 0xFFFF]
movlps xmm0, qword [rax]
movlps xmm0, qword [rax + 0x0]
movlps xmm0, qword [rax + 0xFFFF]
movlps xmm0, qword [r15 + 0xFFFF]
movlps xmm0, qword [rax + rsi * 1  + 0x0]
movlps xmm0, qword [rax + rsi + 0xFFFF]
movlps xmm0, qword [r15 + rsi + 0xFFFF]
movlps xmm0, qword [rax + r15 + 0xFFFF]
movlps xmm0, qword [rax + rsi * 2 + 0xFFFF2]
movlps xmm0, qword [rax + rsi * 4 + 0xFFFF4]
movlps xmm0, qword [rax + rsi * 8 + 0xFFFF8]
movlps xmm0, qword [rsp + rax * 8 + 0xFFFF8]
movlps xmm0, qword [r15 + rax * 8 + 0xFFFF8]
movlps xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
movlps xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
movlps xmm1, qword [0x0]
movlps xmm1, qword [0xFF]
movlps xmm1, qword [rel $ + 0x0]
movlps xmm1, qword [rel $ + 0xFF]
movlps xmm1, qword [rel $ + 0xFFFF]
movlps xmm1, qword [rax]
movlps xmm1, qword [rax + 0x0]
movlps xmm1, qword [rax + 0xFFFF]
movlps xmm1, qword [r15 + 0xFFFF]
movlps xmm1, qword [rax + rsi * 1  + 0x0]
movlps xmm1, qword [rax + rsi + 0xFFFF]
movlps xmm1, qword [r15 + rsi + 0xFFFF]
movlps xmm1, qword [rax + r15 + 0xFFFF]
movlps xmm1, qword [rax + rsi * 2 + 0xFFFF2]
movlps xmm1, qword [rax + rsi * 4 + 0xFFFF4]
movlps xmm1, qword [rax + rsi * 8 + 0xFFFF8]
movlps xmm1, qword [rsp + rax * 8 + 0xFFFF8]
movlps xmm1, qword [r15 + rax * 8 + 0xFFFF8]
movlps xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
movlps xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
movlps xmm15, qword [0x0]
movlps xmm15, qword [0xFF]
movlps xmm15, qword [rel $ + 0x0]
movlps xmm15, qword [rel $ + 0xFF]
movlps xmm15, qword [rel $ + 0xFFFF]
movlps xmm15, qword [rax]
movlps xmm15, qword [rax + 0x0]
movlps xmm15, qword [rax + 0xFFFF]
movlps xmm15, qword [r15 + 0xFFFF]
movlps xmm15, qword [rax + rsi * 1  + 0x0]
movlps xmm15, qword [rax + rsi + 0xFFFF]
movlps xmm15, qword [r15 + rsi + 0xFFFF]
movlps xmm15, qword [rax + r15 + 0xFFFF]
movlps xmm15, qword [rax + rsi * 2 + 0xFFFF2]
movlps xmm15, qword [rax + rsi * 4 + 0xFFFF4]
movlps xmm15, qword [rax + rsi * 8 + 0xFFFF8]
movlps xmm15, qword [rsp + rax * 8 + 0xFFFF8]
movlps xmm15, qword [r15 + rax * 8 + 0xFFFF8]
movlps xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
movlps xmm15, qword [r14 + r15 * 8 + 0xFFFF8]