; expect: 660f71e000660f71e001660f71e064660f71e07f660f71e080660f71e100660f71e101660f71e164660f71e17f660f71e18066410f71e70066410f71e70166410f71e76466410f71e77f66410f71e780660fe1c0660fe1c166410fe1c7660fe1c8660fe1c966410fe1cf66440fe1f866440fe1f966450fe1ff660fe1042500000000660fe10425ff000000660fe105f8ffffff660fe105f7000000660fe105f7ff0000660fe100660fe100660fe180ffff000066410fe187ffff0000660fe10430660fe18430ffff000066410fe18437ffff000066420fe18438ffff0000660fe18470f2ff0f00660fe184b0f4ff0f00660fe184f0f8ff0f00660fe184c4f8ff0f0066410fe184c7f8ff0f0066420fe184fcf8ff0f0066430fe184fef8ff0f00660fe10c2500000000660fe10c25ff000000660fe10df8ffffff660fe10df7000000660fe10df7ff0000660fe108660fe108660fe188ffff000066410fe18fffff0000660fe10c30660fe18c30ffff000066410fe18c37ffff000066420fe18c38ffff0000660fe18c70f2ff0f00660fe18cb0f4ff0f00660fe18cf0f8ff0f00660fe18cc4f8ff0f0066410fe18cc7f8ff0f0066420fe18cfcf8ff0f0066430fe18cfef8ff0f0066440fe13c250000000066440fe13c25ff00000066440fe13df7ffffff66440fe13df600000066440fe13df6ff000066440fe13866440fe13866440fe1b8ffff000066450fe1bfffff000066440fe13c3066440fe1bc30ffff000066450fe1bc37ffff000066460fe1bc38ffff000066440fe1bc70f2ff0f0066440fe1bcb0f4ff0f0066440fe1bcf0f8ff0f0066440fe1bcc4f8ff0f0066450fe1bcc7f8ff0f0066460fe1bcfcf8ff0f0066470fe1bcfef8ff0f00

psraw xmm0, 0
psraw xmm0, 1
psraw xmm0, 100
psraw xmm0, 127
psraw xmm0, -128
psraw xmm1, 0
psraw xmm1, 1
psraw xmm1, 100
psraw xmm1, 127
psraw xmm1, -128
psraw xmm15, 0
psraw xmm15, 1
psraw xmm15, 100
psraw xmm15, 127
psraw xmm15, -128
psraw xmm0, xmm0
psraw xmm0, xmm1
psraw xmm0, xmm15
psraw xmm1, xmm0
psraw xmm1, xmm1
psraw xmm1, xmm15
psraw xmm15, xmm0
psraw xmm15, xmm1
psraw xmm15, xmm15
psraw xmm0, [0x0]
psraw xmm0, [0xFF]
psraw xmm0, [rel $ + 0x0]
psraw xmm0, [rel $ + 0xFF]
psraw xmm0, [rel $ + 0xFFFF]
psraw xmm0, [rax]
psraw xmm0, [rax + 0x0]
psraw xmm0, [rax + 0xFFFF]
psraw xmm0, [r15 + 0xFFFF]
psraw xmm0, [rax + rsi * 1  + 0x0]
psraw xmm0, [rax + rsi + 0xFFFF]
psraw xmm0, [r15 + rsi + 0xFFFF]
psraw xmm0, [rax + r15 + 0xFFFF]
psraw xmm0, [rax + rsi * 2 + 0xFFFF2]
psraw xmm0, [rax + rsi * 4 + 0xFFFF4]
psraw xmm0, [rax + rsi * 8 + 0xFFFF8]
psraw xmm0, [rsp + rax * 8 + 0xFFFF8]
psraw xmm0, [r15 + rax * 8 + 0xFFFF8]
psraw xmm0, [rsp + r15 * 8 + 0xFFFF8]
psraw xmm0, [r14 + r15 * 8 + 0xFFFF8]
psraw xmm1, [0x0]
psraw xmm1, [0xFF]
psraw xmm1, [rel $ + 0x0]
psraw xmm1, [rel $ + 0xFF]
psraw xmm1, [rel $ + 0xFFFF]
psraw xmm1, [rax]
psraw xmm1, [rax + 0x0]
psraw xmm1, [rax + 0xFFFF]
psraw xmm1, [r15 + 0xFFFF]
psraw xmm1, [rax + rsi * 1  + 0x0]
psraw xmm1, [rax + rsi + 0xFFFF]
psraw xmm1, [r15 + rsi + 0xFFFF]
psraw xmm1, [rax + r15 + 0xFFFF]
psraw xmm1, [rax + rsi * 2 + 0xFFFF2]
psraw xmm1, [rax + rsi * 4 + 0xFFFF4]
psraw xmm1, [rax + rsi * 8 + 0xFFFF8]
psraw xmm1, [rsp + rax * 8 + 0xFFFF8]
psraw xmm1, [r15 + rax * 8 + 0xFFFF8]
psraw xmm1, [rsp + r15 * 8 + 0xFFFF8]
psraw xmm1, [r14 + r15 * 8 + 0xFFFF8]
psraw xmm15, [0x0]
psraw xmm15, [0xFF]
psraw xmm15, [rel $ + 0x0]
psraw xmm15, [rel $ + 0xFF]
psraw xmm15, [rel $ + 0xFFFF]
psraw xmm15, [rax]
psraw xmm15, [rax + 0x0]
psraw xmm15, [rax + 0xFFFF]
psraw xmm15, [r15 + 0xFFFF]
psraw xmm15, [rax + rsi * 1  + 0x0]
psraw xmm15, [rax + rsi + 0xFFFF]
psraw xmm15, [r15 + rsi + 0xFFFF]
psraw xmm15, [rax + r15 + 0xFFFF]
psraw xmm15, [rax + rsi * 2 + 0xFFFF2]
psraw xmm15, [rax + rsi * 4 + 0xFFFF4]
psraw xmm15, [rax + rsi * 8 + 0xFFFF8]
psraw xmm15, [rsp + rax * 8 + 0xFFFF8]
psraw xmm15, [r15 + rax * 8 + 0xFFFF8]
psraw xmm15, [rsp + r15 * 8 + 0xFFFF8]
psraw xmm15, [r14 + r15 * 8 + 0xFFFF8]