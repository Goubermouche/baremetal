; expect: 660f17042500000000660f170c250000000066440f173c2500000000660f170425ff000000660f170c25ff00000066440f173c25ff000000660f1705f8ffffff660f170df8ffffff66440f173df7ffffff660f1705f7000000660f170df700000066440f173df6000000660f1705f7ff0000660f170df7ff000066440f173df6ff0000660f1700660f170866440f1738660f1700660f170866440f1738660f1780ffff0000660f1788ffff000066440f17b8ffff000066410f1787ffff000066410f178fffff000066450f17bfffff0000660f170430660f170c3066440f173c30660f178430ffff0000660f178c30ffff000066440f17bc30ffff000066410f178437ffff000066410f178c37ffff000066450f17bc37ffff000066420f178438ffff000066420f178c38ffff000066460f17bc38ffff0000660f178470f2ff0f00660f178c70f2ff0f0066440f17bc70f2ff0f00660f1784b0f4ff0f00660f178cb0f4ff0f0066440f17bcb0f4ff0f00660f1784f0f8ff0f00660f178cf0f8ff0f0066440f17bcf0f8ff0f00660f1784c4f8ff0f00660f178cc4f8ff0f0066440f17bcc4f8ff0f0066410f1784c7f8ff0f0066410f178cc7f8ff0f0066450f17bcc7f8ff0f0066420f1784fcf8ff0f0066420f178cfcf8ff0f0066460f17bcfcf8ff0f0066430f1784fef8ff0f0066430f178cfef8ff0f0066470f17bcfef8ff0f00660f16042500000000660f160425ff000000660f1605f8ffffff660f1605f7000000660f1605f7ff0000660f1600660f1600660f1680ffff000066410f1687ffff0000660f160430660f168430ffff000066410f168437ffff000066420f168438ffff0000660f168470f2ff0f00660f1684b0f4ff0f00660f1684f0f8ff0f00660f1684c4f8ff0f0066410f1684c7f8ff0f0066420f1684fcf8ff0f0066430f1684fef8ff0f00660f160c2500000000660f160c25ff000000660f160df8ffffff660f160df7000000660f160df7ff0000660f1608660f1608660f1688ffff000066410f168fffff0000660f160c30660f168c30ffff000066410f168c37ffff000066420f168c38ffff0000660f168c70f2ff0f00660f168cb0f4ff0f00660f168cf0f8ff0f00660f168cc4f8ff0f0066410f168cc7f8ff0f0066420f168cfcf8ff0f0066430f168cfef8ff0f0066440f163c250000000066440f163c25ff00000066440f163df7ffffff66440f163df600000066440f163df6ff000066440f163866440f163866440f16b8ffff000066450f16bfffff000066440f163c3066440f16bc30ffff000066450f16bc37ffff000066460f16bc38ffff000066440f16bc70f2ff0f0066440f16bcb0f4ff0f0066440f16bcf0f8ff0f0066440f16bcc4f8ff0f0066450f16bcc7f8ff0f0066460f16bcfcf8ff0f0066470f16bcfef8ff0f00

movhpd qword [0x0], xmm0
movhpd qword [0x0], xmm1
movhpd qword [0x0], xmm15
movhpd qword [0xFF], xmm0
movhpd qword [0xFF], xmm1
movhpd qword [0xFF], xmm15
movhpd qword [rel $ + 0x0], xmm0
movhpd qword [rel $ + 0x0], xmm1
movhpd qword [rel $ + 0x0], xmm15
movhpd qword [rel $ + 0xFF], xmm0
movhpd qword [rel $ + 0xFF], xmm1
movhpd qword [rel $ + 0xFF], xmm15
movhpd qword [rel $ + 0xFFFF], xmm0
movhpd qword [rel $ + 0xFFFF], xmm1
movhpd qword [rel $ + 0xFFFF], xmm15
movhpd qword [rax], xmm0
movhpd qword [rax], xmm1
movhpd qword [rax], xmm15
movhpd qword [rax + 0x0], xmm0
movhpd qword [rax + 0x0], xmm1
movhpd qword [rax + 0x0], xmm15
movhpd qword [rax + 0xFFFF], xmm0
movhpd qword [rax + 0xFFFF], xmm1
movhpd qword [rax + 0xFFFF], xmm15
movhpd qword [r15 + 0xFFFF], xmm0
movhpd qword [r15 + 0xFFFF], xmm1
movhpd qword [r15 + 0xFFFF], xmm15
movhpd qword [rax + rsi * 1  + 0x0], xmm0
movhpd qword [rax + rsi * 1  + 0x0], xmm1
movhpd qword [rax + rsi * 1  + 0x0], xmm15
movhpd qword [rax + rsi + 0xFFFF], xmm0
movhpd qword [rax + rsi + 0xFFFF], xmm1
movhpd qword [rax + rsi + 0xFFFF], xmm15
movhpd qword [r15 + rsi + 0xFFFF], xmm0
movhpd qword [r15 + rsi + 0xFFFF], xmm1
movhpd qword [r15 + rsi + 0xFFFF], xmm15
movhpd qword [rax + r15 + 0xFFFF], xmm0
movhpd qword [rax + r15 + 0xFFFF], xmm1
movhpd qword [rax + r15 + 0xFFFF], xmm15
movhpd qword [rax + rsi * 2 + 0xFFFF2], xmm0
movhpd qword [rax + rsi * 2 + 0xFFFF2], xmm1
movhpd qword [rax + rsi * 2 + 0xFFFF2], xmm15
movhpd qword [rax + rsi * 4 + 0xFFFF4], xmm0
movhpd qword [rax + rsi * 4 + 0xFFFF4], xmm1
movhpd qword [rax + rsi * 4 + 0xFFFF4], xmm15
movhpd qword [rax + rsi * 8 + 0xFFFF8], xmm0
movhpd qword [rax + rsi * 8 + 0xFFFF8], xmm1
movhpd qword [rax + rsi * 8 + 0xFFFF8], xmm15
movhpd qword [rsp + rax * 8 + 0xFFFF8], xmm0
movhpd qword [rsp + rax * 8 + 0xFFFF8], xmm1
movhpd qword [rsp + rax * 8 + 0xFFFF8], xmm15
movhpd qword [r15 + rax * 8 + 0xFFFF8], xmm0
movhpd qword [r15 + rax * 8 + 0xFFFF8], xmm1
movhpd qword [r15 + rax * 8 + 0xFFFF8], xmm15
movhpd qword [rsp + r15 * 8 + 0xFFFF8], xmm0
movhpd qword [rsp + r15 * 8 + 0xFFFF8], xmm1
movhpd qword [rsp + r15 * 8 + 0xFFFF8], xmm15
movhpd qword [r14 + r15 * 8 + 0xFFFF8], xmm0
movhpd qword [r14 + r15 * 8 + 0xFFFF8], xmm1
movhpd qword [r14 + r15 * 8 + 0xFFFF8], xmm15
movhpd xmm0, qword [0x0]
movhpd xmm0, qword [0xFF]
movhpd xmm0, qword [rel $ + 0x0]
movhpd xmm0, qword [rel $ + 0xFF]
movhpd xmm0, qword [rel $ + 0xFFFF]
movhpd xmm0, qword [rax]
movhpd xmm0, qword [rax + 0x0]
movhpd xmm0, qword [rax + 0xFFFF]
movhpd xmm0, qword [r15 + 0xFFFF]
movhpd xmm0, qword [rax + rsi * 1  + 0x0]
movhpd xmm0, qword [rax + rsi + 0xFFFF]
movhpd xmm0, qword [r15 + rsi + 0xFFFF]
movhpd xmm0, qword [rax + r15 + 0xFFFF]
movhpd xmm0, qword [rax + rsi * 2 + 0xFFFF2]
movhpd xmm0, qword [rax + rsi * 4 + 0xFFFF4]
movhpd xmm0, qword [rax + rsi * 8 + 0xFFFF8]
movhpd xmm0, qword [rsp + rax * 8 + 0xFFFF8]
movhpd xmm0, qword [r15 + rax * 8 + 0xFFFF8]
movhpd xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
movhpd xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
movhpd xmm1, qword [0x0]
movhpd xmm1, qword [0xFF]
movhpd xmm1, qword [rel $ + 0x0]
movhpd xmm1, qword [rel $ + 0xFF]
movhpd xmm1, qword [rel $ + 0xFFFF]
movhpd xmm1, qword [rax]
movhpd xmm1, qword [rax + 0x0]
movhpd xmm1, qword [rax + 0xFFFF]
movhpd xmm1, qword [r15 + 0xFFFF]
movhpd xmm1, qword [rax + rsi * 1  + 0x0]
movhpd xmm1, qword [rax + rsi + 0xFFFF]
movhpd xmm1, qword [r15 + rsi + 0xFFFF]
movhpd xmm1, qword [rax + r15 + 0xFFFF]
movhpd xmm1, qword [rax + rsi * 2 + 0xFFFF2]
movhpd xmm1, qword [rax + rsi * 4 + 0xFFFF4]
movhpd xmm1, qword [rax + rsi * 8 + 0xFFFF8]
movhpd xmm1, qword [rsp + rax * 8 + 0xFFFF8]
movhpd xmm1, qword [r15 + rax * 8 + 0xFFFF8]
movhpd xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
movhpd xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
movhpd xmm15, qword [0x0]
movhpd xmm15, qword [0xFF]
movhpd xmm15, qword [rel $ + 0x0]
movhpd xmm15, qword [rel $ + 0xFF]
movhpd xmm15, qword [rel $ + 0xFFFF]
movhpd xmm15, qword [rax]
movhpd xmm15, qword [rax + 0x0]
movhpd xmm15, qword [rax + 0xFFFF]
movhpd xmm15, qword [r15 + 0xFFFF]
movhpd xmm15, qword [rax + rsi * 1  + 0x0]
movhpd xmm15, qword [rax + rsi + 0xFFFF]
movhpd xmm15, qword [r15 + rsi + 0xFFFF]
movhpd xmm15, qword [rax + r15 + 0xFFFF]
movhpd xmm15, qword [rax + rsi * 2 + 0xFFFF2]
movhpd xmm15, qword [rax + rsi * 4 + 0xFFFF4]
movhpd xmm15, qword [rax + rsi * 8 + 0xFFFF8]
movhpd xmm15, qword [rsp + rax * 8 + 0xFFFF8]
movhpd xmm15, qword [r15 + rax * 8 + 0xFFFF8]
movhpd xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
movhpd xmm15, qword [r14 + r15 * 8 + 0xFFFF8]