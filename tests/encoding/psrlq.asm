; expect: 660f73d000660f73d001660f73d00a660f73d064660f73d07f660f73d080660f73d100660f73d101660f73d10a660f73d164660f73d17f660f73d18066410f73d70066410f73d70166410f73d70a66410f73d76466410f73d77f66410f73d780660fd3c0660fd3c166410fd3c7660fd3c8660fd3c966410fd3cf66440fd3f866440fd3f966450fd3ff660fd3042500000000660fd30425ff000000660fd305f8ffffff660fd305f7000000660fd305f7ff0000660fd300660fd300660fd380ffff000066410fd387ffff0000660fd30430660fd38430ffff000066410fd38437ffff000066420fd38438ffff0000660fd38470f2ff0f00660fd384b0f4ff0f00660fd384f0f8ff0f00660fd384c4f8ff0f0066410fd384c7f8ff0f0066420fd384fcf8ff0f0066430fd384fef8ff0f00660fd30c2500000000660fd30c25ff000000660fd30df8ffffff660fd30df7000000660fd30df7ff0000660fd308660fd308660fd388ffff000066410fd38fffff0000660fd30c30660fd38c30ffff000066410fd38c37ffff000066420fd38c38ffff0000660fd38c70f2ff0f00660fd38cb0f4ff0f00660fd38cf0f8ff0f00660fd38cc4f8ff0f0066410fd38cc7f8ff0f0066420fd38cfcf8ff0f0066430fd38cfef8ff0f0066440fd33c250000000066440fd33c25ff00000066440fd33df7ffffff66440fd33df600000066440fd33df6ff000066440fd33866440fd33866440fd3b8ffff000066450fd3bfffff000066440fd33c3066440fd3bc30ffff000066450fd3bc37ffff000066460fd3bc38ffff000066440fd3bc70f2ff0f0066440fd3bcb0f4ff0f0066440fd3bcf0f8ff0f0066440fd3bcc4f8ff0f0066450fd3bcc7f8ff0f0066460fd3bcfcf8ff0f0066470fd3bcfef8ff0f00

bits 64

psrlq xmm0, 0
psrlq xmm0, 1
psrlq xmm0, 10
psrlq xmm0, 100
psrlq xmm0, 127
psrlq xmm0, -128
psrlq xmm1, 0
psrlq xmm1, 1
psrlq xmm1, 10
psrlq xmm1, 100
psrlq xmm1, 127
psrlq xmm1, -128
psrlq xmm15, 0
psrlq xmm15, 1
psrlq xmm15, 10
psrlq xmm15, 100
psrlq xmm15, 127
psrlq xmm15, -128
psrlq xmm0, xmm0
psrlq xmm0, xmm1
psrlq xmm0, xmm15
psrlq xmm1, xmm0
psrlq xmm1, xmm1
psrlq xmm1, xmm15
psrlq xmm15, xmm0
psrlq xmm15, xmm1
psrlq xmm15, xmm15
psrlq xmm0, [0x0]
psrlq xmm0, [0xFF]
psrlq xmm0, [rel $ + 0x0]
psrlq xmm0, [rel $ + 0xFF]
psrlq xmm0, [rel $ + 0xFFFF]
psrlq xmm0, [rax]
psrlq xmm0, [rax + 0x0]
psrlq xmm0, [rax + 0xFFFF]
psrlq xmm0, [r15 + 0xFFFF]
psrlq xmm0, [rax + rsi * 1  + 0x0]
psrlq xmm0, [rax + rsi + 0xFFFF]
psrlq xmm0, [r15 + rsi + 0xFFFF]
psrlq xmm0, [rax + r15 + 0xFFFF]
psrlq xmm0, [rax + rsi * 2 + 0xFFFF2]
psrlq xmm0, [rax + rsi * 4 + 0xFFFF4]
psrlq xmm0, [rax + rsi * 8 + 0xFFFF8]
psrlq xmm0, [rsp + rax * 8 + 0xFFFF8]
psrlq xmm0, [r15 + rax * 8 + 0xFFFF8]
psrlq xmm0, [rsp + r15 * 8 + 0xFFFF8]
psrlq xmm0, [r14 + r15 * 8 + 0xFFFF8]
psrlq xmm1, [0x0]
psrlq xmm1, [0xFF]
psrlq xmm1, [rel $ + 0x0]
psrlq xmm1, [rel $ + 0xFF]
psrlq xmm1, [rel $ + 0xFFFF]
psrlq xmm1, [rax]
psrlq xmm1, [rax + 0x0]
psrlq xmm1, [rax + 0xFFFF]
psrlq xmm1, [r15 + 0xFFFF]
psrlq xmm1, [rax + rsi * 1  + 0x0]
psrlq xmm1, [rax + rsi + 0xFFFF]
psrlq xmm1, [r15 + rsi + 0xFFFF]
psrlq xmm1, [rax + r15 + 0xFFFF]
psrlq xmm1, [rax + rsi * 2 + 0xFFFF2]
psrlq xmm1, [rax + rsi * 4 + 0xFFFF4]
psrlq xmm1, [rax + rsi * 8 + 0xFFFF8]
psrlq xmm1, [rsp + rax * 8 + 0xFFFF8]
psrlq xmm1, [r15 + rax * 8 + 0xFFFF8]
psrlq xmm1, [rsp + r15 * 8 + 0xFFFF8]
psrlq xmm1, [r14 + r15 * 8 + 0xFFFF8]
psrlq xmm15, [0x0]
psrlq xmm15, [0xFF]
psrlq xmm15, [rel $ + 0x0]
psrlq xmm15, [rel $ + 0xFF]
psrlq xmm15, [rel $ + 0xFFFF]
psrlq xmm15, [rax]
psrlq xmm15, [rax + 0x0]
psrlq xmm15, [rax + 0xFFFF]
psrlq xmm15, [r15 + 0xFFFF]
psrlq xmm15, [rax + rsi * 1  + 0x0]
psrlq xmm15, [rax + rsi + 0xFFFF]
psrlq xmm15, [r15 + rsi + 0xFFFF]
psrlq xmm15, [rax + r15 + 0xFFFF]
psrlq xmm15, [rax + rsi * 2 + 0xFFFF2]
psrlq xmm15, [rax + rsi * 4 + 0xFFFF4]
psrlq xmm15, [rax + rsi * 8 + 0xFFFF8]
psrlq xmm15, [rsp + rax * 8 + 0xFFFF8]
psrlq xmm15, [r15 + rax * 8 + 0xFFFF8]
psrlq xmm15, [rsp + r15 * 8 + 0xFFFF8]
psrlq xmm15, [r14 + r15 * 8 + 0xFFFF8]
