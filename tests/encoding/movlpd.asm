; expect: 660f13042500000000660f130c250000000066440f133c2500000000660f130425ff000000660f130c25ff00000066440f133c25ff000000660f1305f8ffffff660f130df8ffffff66440f133df7ffffff660f1305f7000000660f130df700000066440f133df6000000660f1305f7ff0000660f130df7ff000066440f133df6ff0000660f1300660f130866440f1338660f1300660f130866440f1338660f1380ffff0000660f1388ffff000066440f13b8ffff000066410f1387ffff000066410f138fffff000066450f13bfffff0000660f130430660f130c3066440f133c30660f138430ffff0000660f138c30ffff000066440f13bc30ffff000066410f138437ffff000066410f138c37ffff000066450f13bc37ffff000066420f138438ffff000066420f138c38ffff000066460f13bc38ffff0000660f138470f2ff0f00660f138c70f2ff0f0066440f13bc70f2ff0f00660f1384b0f4ff0f00660f138cb0f4ff0f0066440f13bcb0f4ff0f00660f1384f0f8ff0f00660f138cf0f8ff0f0066440f13bcf0f8ff0f00660f1384c4f8ff0f00660f138cc4f8ff0f0066440f13bcc4f8ff0f0066410f1384c7f8ff0f0066410f138cc7f8ff0f0066450f13bcc7f8ff0f0066420f1384fcf8ff0f0066420f138cfcf8ff0f0066460f13bcfcf8ff0f0066430f1384fef8ff0f0066430f138cfef8ff0f0066470f13bcfef8ff0f00660f12042500000000660f120425ff000000660f1205f8ffffff660f1205f7000000660f1205f7ff0000660f1200660f1200660f1280ffff000066410f1287ffff0000660f120430660f128430ffff000066410f128437ffff000066420f128438ffff0000660f128470f2ff0f00660f1284b0f4ff0f00660f1284f0f8ff0f00660f1284c4f8ff0f0066410f1284c7f8ff0f0066420f1284fcf8ff0f0066430f1284fef8ff0f00660f120c2500000000660f120c25ff000000660f120df8ffffff660f120df7000000660f120df7ff0000660f1208660f1208660f1288ffff000066410f128fffff0000660f120c30660f128c30ffff000066410f128c37ffff000066420f128c38ffff0000660f128c70f2ff0f00660f128cb0f4ff0f00660f128cf0f8ff0f00660f128cc4f8ff0f0066410f128cc7f8ff0f0066420f128cfcf8ff0f0066430f128cfef8ff0f0066440f123c250000000066440f123c25ff00000066440f123df7ffffff66440f123df600000066440f123df6ff000066440f123866440f123866440f12b8ffff000066450f12bfffff000066440f123c3066440f12bc30ffff000066450f12bc37ffff000066460f12bc38ffff000066440f12bc70f2ff0f0066440f12bcb0f4ff0f0066440f12bcf0f8ff0f0066440f12bcc4f8ff0f0066450f12bcc7f8ff0f0066460f12bcfcf8ff0f0066470f12bcfef8ff0f00

bits 64

movlpd qword [0x0], xmm0
movlpd qword [0x0], xmm1
movlpd qword [0x0], xmm15
movlpd qword [0xFF], xmm0
movlpd qword [0xFF], xmm1
movlpd qword [0xFF], xmm15
movlpd qword [rel $ + 0x0], xmm0
movlpd qword [rel $ + 0x0], xmm1
movlpd qword [rel $ + 0x0], xmm15
movlpd qword [rel $ + 0xFF], xmm0
movlpd qword [rel $ + 0xFF], xmm1
movlpd qword [rel $ + 0xFF], xmm15
movlpd qword [rel $ + 0xFFFF], xmm0
movlpd qword [rel $ + 0xFFFF], xmm1
movlpd qword [rel $ + 0xFFFF], xmm15
movlpd qword [rax], xmm0
movlpd qword [rax], xmm1
movlpd qword [rax], xmm15
movlpd qword [rax + 0x0], xmm0
movlpd qword [rax + 0x0], xmm1
movlpd qword [rax + 0x0], xmm15
movlpd qword [rax + 0xFFFF], xmm0
movlpd qword [rax + 0xFFFF], xmm1
movlpd qword [rax + 0xFFFF], xmm15
movlpd qword [r15 + 0xFFFF], xmm0
movlpd qword [r15 + 0xFFFF], xmm1
movlpd qword [r15 + 0xFFFF], xmm15
movlpd qword [rax + rsi * 1  + 0x0], xmm0
movlpd qword [rax + rsi * 1  + 0x0], xmm1
movlpd qword [rax + rsi * 1  + 0x0], xmm15
movlpd qword [rax + rsi + 0xFFFF], xmm0
movlpd qword [rax + rsi + 0xFFFF], xmm1
movlpd qword [rax + rsi + 0xFFFF], xmm15
movlpd qword [r15 + rsi + 0xFFFF], xmm0
movlpd qword [r15 + rsi + 0xFFFF], xmm1
movlpd qword [r15 + rsi + 0xFFFF], xmm15
movlpd qword [rax + r15 + 0xFFFF], xmm0
movlpd qword [rax + r15 + 0xFFFF], xmm1
movlpd qword [rax + r15 + 0xFFFF], xmm15
movlpd qword [rax + rsi * 2 + 0xFFFF2], xmm0
movlpd qword [rax + rsi * 2 + 0xFFFF2], xmm1
movlpd qword [rax + rsi * 2 + 0xFFFF2], xmm15
movlpd qword [rax + rsi * 4 + 0xFFFF4], xmm0
movlpd qword [rax + rsi * 4 + 0xFFFF4], xmm1
movlpd qword [rax + rsi * 4 + 0xFFFF4], xmm15
movlpd qword [rax + rsi * 8 + 0xFFFF8], xmm0
movlpd qword [rax + rsi * 8 + 0xFFFF8], xmm1
movlpd qword [rax + rsi * 8 + 0xFFFF8], xmm15
movlpd qword [rsp + rax * 8 + 0xFFFF8], xmm0
movlpd qword [rsp + rax * 8 + 0xFFFF8], xmm1
movlpd qword [rsp + rax * 8 + 0xFFFF8], xmm15
movlpd qword [r15 + rax * 8 + 0xFFFF8], xmm0
movlpd qword [r15 + rax * 8 + 0xFFFF8], xmm1
movlpd qword [r15 + rax * 8 + 0xFFFF8], xmm15
movlpd qword [rsp + r15 * 8 + 0xFFFF8], xmm0
movlpd qword [rsp + r15 * 8 + 0xFFFF8], xmm1
movlpd qword [rsp + r15 * 8 + 0xFFFF8], xmm15
movlpd qword [r14 + r15 * 8 + 0xFFFF8], xmm0
movlpd qword [r14 + r15 * 8 + 0xFFFF8], xmm1
movlpd qword [r14 + r15 * 8 + 0xFFFF8], xmm15
movlpd xmm0, qword [0x0]
movlpd xmm0, qword [0xFF]
movlpd xmm0, qword [rel $ + 0x0]
movlpd xmm0, qword [rel $ + 0xFF]
movlpd xmm0, qword [rel $ + 0xFFFF]
movlpd xmm0, qword [rax]
movlpd xmm0, qword [rax + 0x0]
movlpd xmm0, qword [rax + 0xFFFF]
movlpd xmm0, qword [r15 + 0xFFFF]
movlpd xmm0, qword [rax + rsi * 1  + 0x0]
movlpd xmm0, qword [rax + rsi + 0xFFFF]
movlpd xmm0, qword [r15 + rsi + 0xFFFF]
movlpd xmm0, qword [rax + r15 + 0xFFFF]
movlpd xmm0, qword [rax + rsi * 2 + 0xFFFF2]
movlpd xmm0, qword [rax + rsi * 4 + 0xFFFF4]
movlpd xmm0, qword [rax + rsi * 8 + 0xFFFF8]
movlpd xmm0, qword [rsp + rax * 8 + 0xFFFF8]
movlpd xmm0, qword [r15 + rax * 8 + 0xFFFF8]
movlpd xmm0, qword [rsp + r15 * 8 + 0xFFFF8]
movlpd xmm0, qword [r14 + r15 * 8 + 0xFFFF8]
movlpd xmm1, qword [0x0]
movlpd xmm1, qword [0xFF]
movlpd xmm1, qword [rel $ + 0x0]
movlpd xmm1, qword [rel $ + 0xFF]
movlpd xmm1, qword [rel $ + 0xFFFF]
movlpd xmm1, qword [rax]
movlpd xmm1, qword [rax + 0x0]
movlpd xmm1, qword [rax + 0xFFFF]
movlpd xmm1, qword [r15 + 0xFFFF]
movlpd xmm1, qword [rax + rsi * 1  + 0x0]
movlpd xmm1, qword [rax + rsi + 0xFFFF]
movlpd xmm1, qword [r15 + rsi + 0xFFFF]
movlpd xmm1, qword [rax + r15 + 0xFFFF]
movlpd xmm1, qword [rax + rsi * 2 + 0xFFFF2]
movlpd xmm1, qword [rax + rsi * 4 + 0xFFFF4]
movlpd xmm1, qword [rax + rsi * 8 + 0xFFFF8]
movlpd xmm1, qword [rsp + rax * 8 + 0xFFFF8]
movlpd xmm1, qword [r15 + rax * 8 + 0xFFFF8]
movlpd xmm1, qword [rsp + r15 * 8 + 0xFFFF8]
movlpd xmm1, qword [r14 + r15 * 8 + 0xFFFF8]
movlpd xmm15, qword [0x0]
movlpd xmm15, qword [0xFF]
movlpd xmm15, qword [rel $ + 0x0]
movlpd xmm15, qword [rel $ + 0xFF]
movlpd xmm15, qword [rel $ + 0xFFFF]
movlpd xmm15, qword [rax]
movlpd xmm15, qword [rax + 0x0]
movlpd xmm15, qword [rax + 0xFFFF]
movlpd xmm15, qword [r15 + 0xFFFF]
movlpd xmm15, qword [rax + rsi * 1  + 0x0]
movlpd xmm15, qword [rax + rsi + 0xFFFF]
movlpd xmm15, qword [r15 + rsi + 0xFFFF]
movlpd xmm15, qword [rax + r15 + 0xFFFF]
movlpd xmm15, qword [rax + rsi * 2 + 0xFFFF2]
movlpd xmm15, qword [rax + rsi * 4 + 0xFFFF4]
movlpd xmm15, qword [rax + rsi * 8 + 0xFFFF8]
movlpd xmm15, qword [rsp + rax * 8 + 0xFFFF8]
movlpd xmm15, qword [r15 + rax * 8 + 0xFFFF8]
movlpd xmm15, qword [rsp + r15 * 8 + 0xFFFF8]
movlpd xmm15, qword [r14 + r15 * 8 + 0xFFFF8]
