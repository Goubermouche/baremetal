; expect: 660f71d000660f71d001660f71d064660f71d07f660f71d080660f71d100660f71d101660f71d164660f71d17f660f71d18066410f71d70066410f71d70166410f71d76466410f71d77f66410f71d780660fd1c0660fd1c166410fd1c7660fd1c8660fd1c966410fd1cf66440fd1f866440fd1f966450fd1ff660fd1042500000000660fd10425ff000000660fd105f8ffffff660fd105f7000000660fd105f7ff0000660fd100660fd100660fd180ffff000066410fd187ffff0000660fd10430660fd18430ffff000066410fd18437ffff000066420fd18438ffff0000660fd18470f2ff0f00660fd184b0f4ff0f00660fd184f0f8ff0f00660fd184c4f8ff0f0066410fd184c7f8ff0f0066420fd184fcf8ff0f0066430fd184fef8ff0f00660fd10c2500000000660fd10c25ff000000660fd10df8ffffff660fd10df7000000660fd10df7ff0000660fd108660fd108660fd188ffff000066410fd18fffff0000660fd10c30660fd18c30ffff000066410fd18c37ffff000066420fd18c38ffff0000660fd18c70f2ff0f00660fd18cb0f4ff0f00660fd18cf0f8ff0f00660fd18cc4f8ff0f0066410fd18cc7f8ff0f0066420fd18cfcf8ff0f0066430fd18cfef8ff0f0066440fd13c250000000066440fd13c25ff00000066440fd13df7ffffff66440fd13df600000066440fd13df6ff000066440fd13866440fd13866440fd1b8ffff000066450fd1bfffff000066440fd13c3066440fd1bc30ffff000066450fd1bc37ffff000066460fd1bc38ffff000066440fd1bc70f2ff0f0066440fd1bcb0f4ff0f0066440fd1bcf0f8ff0f0066440fd1bcc4f8ff0f0066450fd1bcc7f8ff0f0066460fd1bcfcf8ff0f0066470fd1bcfef8ff0f00

psrlw xmm0, 0
psrlw xmm0, 1
psrlw xmm0, 100
psrlw xmm0, 127
psrlw xmm0, -128
psrlw xmm1, 0
psrlw xmm1, 1
psrlw xmm1, 100
psrlw xmm1, 127
psrlw xmm1, -128
psrlw xmm15, 0
psrlw xmm15, 1
psrlw xmm15, 100
psrlw xmm15, 127
psrlw xmm15, -128
psrlw xmm0, xmm0
psrlw xmm0, xmm1
psrlw xmm0, xmm15
psrlw xmm1, xmm0
psrlw xmm1, xmm1
psrlw xmm1, xmm15
psrlw xmm15, xmm0
psrlw xmm15, xmm1
psrlw xmm15, xmm15
psrlw xmm0, [0x0]
psrlw xmm0, [0xFF]
psrlw xmm0, [rel $ + 0x0]
psrlw xmm0, [rel $ + 0xFF]
psrlw xmm0, [rel $ + 0xFFFF]
psrlw xmm0, [rax]
psrlw xmm0, [rax + 0x0]
psrlw xmm0, [rax + 0xFFFF]
psrlw xmm0, [r15 + 0xFFFF]
psrlw xmm0, [rax + rsi * 1  + 0x0]
psrlw xmm0, [rax + rsi + 0xFFFF]
psrlw xmm0, [r15 + rsi + 0xFFFF]
psrlw xmm0, [rax + r15 + 0xFFFF]
psrlw xmm0, [rax + rsi * 2 + 0xFFFF2]
psrlw xmm0, [rax + rsi * 4 + 0xFFFF4]
psrlw xmm0, [rax + rsi * 8 + 0xFFFF8]
psrlw xmm0, [rsp + rax * 8 + 0xFFFF8]
psrlw xmm0, [r15 + rax * 8 + 0xFFFF8]
psrlw xmm0, [rsp + r15 * 8 + 0xFFFF8]
psrlw xmm0, [r14 + r15 * 8 + 0xFFFF8]
psrlw xmm1, [0x0]
psrlw xmm1, [0xFF]
psrlw xmm1, [rel $ + 0x0]
psrlw xmm1, [rel $ + 0xFF]
psrlw xmm1, [rel $ + 0xFFFF]
psrlw xmm1, [rax]
psrlw xmm1, [rax + 0x0]
psrlw xmm1, [rax + 0xFFFF]
psrlw xmm1, [r15 + 0xFFFF]
psrlw xmm1, [rax + rsi * 1  + 0x0]
psrlw xmm1, [rax + rsi + 0xFFFF]
psrlw xmm1, [r15 + rsi + 0xFFFF]
psrlw xmm1, [rax + r15 + 0xFFFF]
psrlw xmm1, [rax + rsi * 2 + 0xFFFF2]
psrlw xmm1, [rax + rsi * 4 + 0xFFFF4]
psrlw xmm1, [rax + rsi * 8 + 0xFFFF8]
psrlw xmm1, [rsp + rax * 8 + 0xFFFF8]
psrlw xmm1, [r15 + rax * 8 + 0xFFFF8]
psrlw xmm1, [rsp + r15 * 8 + 0xFFFF8]
psrlw xmm1, [r14 + r15 * 8 + 0xFFFF8]
psrlw xmm15, [0x0]
psrlw xmm15, [0xFF]
psrlw xmm15, [rel $ + 0x0]
psrlw xmm15, [rel $ + 0xFF]
psrlw xmm15, [rel $ + 0xFFFF]
psrlw xmm15, [rax]
psrlw xmm15, [rax + 0x0]
psrlw xmm15, [rax + 0xFFFF]
psrlw xmm15, [r15 + 0xFFFF]
psrlw xmm15, [rax + rsi * 1  + 0x0]
psrlw xmm15, [rax + rsi + 0xFFFF]
psrlw xmm15, [r15 + rsi + 0xFFFF]
psrlw xmm15, [rax + r15 + 0xFFFF]
psrlw xmm15, [rax + rsi * 2 + 0xFFFF2]
psrlw xmm15, [rax + rsi * 4 + 0xFFFF4]
psrlw xmm15, [rax + rsi * 8 + 0xFFFF8]
psrlw xmm15, [rsp + rax * 8 + 0xFFFF8]
psrlw xmm15, [r15 + rax * 8 + 0xFFFF8]
psrlw xmm15, [rsp + r15 * 8 + 0xFFFF8]
psrlw xmm15, [r14 + r15 * 8 + 0xFFFF8]