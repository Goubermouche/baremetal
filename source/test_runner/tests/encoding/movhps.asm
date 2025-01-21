; expect: 0f170425000000000f170c2500000000440f173c25000000000f170425ff0000000f170c25ff000000440f173c25ff0000000f1705f9ffffff0f170df9ffffff440f173df8ffffff0f1705f80000000f170df8000000440f173df70000000f1705f8ff00000f170df8ff0000440f173df7ff00000f17000f1708440f17380f17000f1708440f17380f1780ffff00000f1788ffff0000440f17b8ffff0000410f1787ffff0000410f178fffff0000450f17bfffff00000f1704300f170c30440f173c300f178430ffff00000f178c30ffff0000440f17bc30ffff0000410f178437ffff0000410f178c37ffff0000450f17bc37ffff0000420f178438ffff0000420f178c38ffff0000460f17bc38ffff00000f178470f2ff0f000f178c70f2ff0f00440f17bc70f2ff0f000f1784b0f4ff0f000f178cb0f4ff0f00440f17bcb0f4ff0f000f1784f0f8ff0f000f178cf0f8ff0f00440f17bcf0f8ff0f000f1784c4f8ff0f000f178cc4f8ff0f00440f17bcc4f8ff0f00410f1784c7f8ff0f00410f178cc7f8ff0f00450f17bcc7f8ff0f00420f1784fcf8ff0f00420f178cfcf8ff0f00460f17bcfcf8ff0f00430f1784fef8ff0f00430f178cfef8ff0f00470f17bcfef8ff0f000f160425000000000f160425ff0000000f1605f9ffffff0f1605f80000000f1605f8ff00000f16000f16000f1680ffff0000410f1687ffff00000f1604300f168430ffff0000410f168437ffff0000420f168438ffff00000f168470f2ff0f000f1684b0f4ff0f000f1684f0f8ff0f000f1684c4f8ff0f00410f1684c7f8ff0f00420f1684fcf8ff0f00430f1684fef8ff0f000f160c25000000000f160c25ff0000000f160df9ffffff0f160df80000000f160df8ff00000f16080f16080f1688ffff0000410f168fffff00000f160c300f168c30ffff0000410f168c37ffff0000420f168c38ffff00000f168c70f2ff0f000f168cb0f4ff0f000f168cf0f8ff0f000f168cc4f8ff0f00410f168cc7f8ff0f00420f168cfcf8ff0f00430f168cfef8ff0f00440f163c2500000000440f163c25ff000000440f163df8ffffff440f163df7000000440f163df7ff0000440f1638440f1638440f16b8ffff0000450f16bfffff0000440f163c30440f16bc30ffff0000450f16bc37ffff0000460f16bc38ffff0000440f16bc70f2ff0f00440f16bcb0f4ff0f00440f16bcf0f8ff0f00440f16bcc4f8ff0f00450f16bcc7f8ff0f00460f16bcfcf8ff0f00470f16bcfef8ff0f00

movhps qword [0x0], xmm0
movhps qword [0x0], xmm1
movhps qword [0x0], xmm15
movhps qword [0xFF], xmm0
movhps qword [0xFF], xmm1
movhps qword [0xFF], xmm15
movhps qword [rel $ + 0x0], xmm0
movhps qword [rel $ + 0x0], xmm1
movhps qword [rel $ + 0x0], xmm15
movhps qword [rel $ + 0xFF], xmm0
movhps qword [rel $ + 0xFF], xmm1
movhps qword [rel $ + 0xFF], xmm15
movhps qword [rel $ + 0xFFFF], xmm0
movhps qword [rel $ + 0xFFFF], xmm1
movhps qword [rel $ + 0xFFFF], xmm15
movhps qword [rax], xmm0
movhps qword [rax], xmm1
movhps qword [rax], xmm15
movhps qword [rax + 0x0], xmm0
movhps qword [rax + 0x0], xmm1
movhps qword [rax + 0x0], xmm15
movhps qword [rax + 0xFFFF], xmm0
movhps qword [rax + 0xFFFF], xmm1
movhps qword [rax + 0xFFFF], xmm15
movhps qword [r15 + 0xFFFF], xmm0
movhps qword [r15 + 0xFFFF], xmm1
movhps qword [r15 + 0xFFFF], xmm15
movhps qword [rax + rsi * 1  + 0x0], xmm0
movhps qword [rax + rsi * 1  + 0x0], xmm1
movhps qword [rax + rsi * 1  + 0x0], xmm15
movhps qword [rax + rsi + 0xFFFF], xmm0
movhps qword [rax + rsi + 0xFFFF], xmm1
movhps qword [rax + rsi + 0xFFFF], xmm15
movhps qword [r15 + rsi + 0xFFFF], xmm0
movhps qword [r15 + rsi + 0xFFFF], xmm1
movhps qword [r15 + rsi + 0xFFFF], xmm15
movhps qword [rax + r15 + 0xFFFF], xmm0
movhps qword [rax + r15 + 0xFFFF], xmm1
movhps qword [rax + r15 + 0xFFFF], xmm15
movhps qword [rax + rsi * 2 + 0xFFFF2], xmm0
movhps qword [rax + rsi * 2 + 0xFFFF2], xmm1
movhps qword [rax + rsi * 2 + 0xFFFF2], xmm15
movhps qword [rax + rsi * 4 + 0xFFFF4], xmm0
movhps qword [rax + rsi * 4 + 0xFFFF4], xmm1
movhps qword [rax + rsi * 4 + 0xFFFF4], xmm15
movhps qword [rax + rsi * 8 + 0xFFFF8], xmm0
movhps qword [rax + rsi * 8 + 0xFFFF8], xmm1
movhps qword [rax + rsi * 8 + 0xFFFF8], xmm15
movhps qword [rsp + rax * 8 + 0xFFFF8], xmm0
movhps qword [rsp + rax * 8 + 0xFFFF8], xmm1
movhps qword [rsp + rax * 8 + 0xFFFF8], xmm15
movhps qword [r15 + rax * 8 + 0xFFFF8], xmm0
movhps qword [r15 + rax * 8 + 0xFFFF8], xmm1
movhps qword [r15 + rax * 8 + 0xFFFF8], xmm15
movhps qword [rsp + r15 * 8 + 0xFFFF8], xmm0
movhps qword [rsp + r15 * 8 + 0xFFFF8], xmm1
movhps qword [rsp + r15 * 8 + 0xFFFF8], xmm15
movhps qword [r14 + r15 * 8 + 0xFFFF8], xmm0
movhps qword [r14 + r15 * 8 + 0xFFFF8], xmm1
movhps qword [r14 + r15 * 8 + 0xFFFF8], xmm15
movhps xmm0, qword [0x0]
movhps xmm0, qword [0xFF]
movhps xmm0, qword [rel $ + 0x0]
movhps xmm0, qword [rel $ + 0xFF]
movhps xmm0, qword [rel $ + 0xFFFF]
movhps xmm0, qword [rax]
movhps xmm0, qword [rax + 0x0]
movhps xmm0, qword [rax + 0xFFFF]
movhps xmm0, qword [r15 + 0xFFFF]
movhps xmm0, qword [rax + rsi * 1  + 0x0]
movhps xmm0, qword [rax + rsi + 0xFFFF]
movhps xmm0, qword [r15 + rsi + 0xFFFF]
movhps xmm0, qword [rax + r15 + 0xFFFF]
movhps xmm0, qword [rax + rsi * 2 + 0xFFFF2]
movhps xmm0, qword [rax + rsi * 4 + 0xFFFF4]
movhps xmm0, qword [rax + rsi * 8 + 0xFFFF8]
movhps xmm0, qword [rsp + rax * 8 + 0xFFFF8]
movhps xmm0, qword [r15 + rax * 8 + 0xFFFF8]
movhps xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
movhps xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
movhps xmm1, qword [0x0]
movhps xmm1, qword [0xFF]
movhps xmm1, qword [rel $ + 0x0]
movhps xmm1, qword [rel $ + 0xFF]
movhps xmm1, qword [rel $ + 0xFFFF]
movhps xmm1, qword [rax]
movhps xmm1, qword [rax + 0x0]
movhps xmm1, qword [rax + 0xFFFF]
movhps xmm1, qword [r15 + 0xFFFF]
movhps xmm1, qword [rax + rsi * 1  + 0x0]
movhps xmm1, qword [rax + rsi + 0xFFFF]
movhps xmm1, qword [r15 + rsi + 0xFFFF]
movhps xmm1, qword [rax + r15 + 0xFFFF]
movhps xmm1, qword [rax + rsi * 2 + 0xFFFF2]
movhps xmm1, qword [rax + rsi * 4 + 0xFFFF4]
movhps xmm1, qword [rax + rsi * 8 + 0xFFFF8]
movhps xmm1, qword [rsp + rax * 8 + 0xFFFF8]
movhps xmm1, qword [r15 + rax * 8 + 0xFFFF8]
movhps xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
movhps xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
movhps xmm15, qword [0x0]
movhps xmm15, qword [0xFF]
movhps xmm15, qword [rel $ + 0x0]
movhps xmm15, qword [rel $ + 0xFF]
movhps xmm15, qword [rel $ + 0xFFFF]
movhps xmm15, qword [rax]
movhps xmm15, qword [rax + 0x0]
movhps xmm15, qword [rax + 0xFFFF]
movhps xmm15, qword [r15 + 0xFFFF]
movhps xmm15, qword [rax + rsi * 1  + 0x0]
movhps xmm15, qword [rax + rsi + 0xFFFF]
movhps xmm15, qword [r15 + rsi + 0xFFFF]
movhps xmm15, qword [rax + r15 + 0xFFFF]
movhps xmm15, qword [rax + rsi * 2 + 0xFFFF2]
movhps xmm15, qword [rax + rsi * 4 + 0xFFFF4]
movhps xmm15, qword [rax + rsi * 8 + 0xFFFF8]
movhps xmm15, qword [rsp + rax * 8 + 0xFFFF8]
movhps xmm15, qword [r15 + rax * 8 + 0xFFFF8]
movhps xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
movhps xmm15, qword [r14 + r15 * 8 + 0xFFFF8]