; expect: 660fe9c0660fe9c166410fe9c7660fe9c8660fe9c966410fe9cf66440fe9f866440fe9f966450fe9ff660fe9042500000000660fe90425ff000000660fe905f8ffffff660fe905f7000000660fe905f7ff0000660fe900660fe900660fe980ffff000066410fe987ffff0000660fe90430660fe98430ffff000066410fe98437ffff000066420fe98438ffff0000660fe98470f2ff0f00660fe984b0f4ff0f00660fe984f0f8ff0f00660fe984c4f8ff0f0066410fe984c7f8ff0f0066420fe984fcf8ff0f0066430fe984fef8ff0f00660fe90c2500000000660fe90c25ff000000660fe90df8ffffff660fe90df7000000660fe90df7ff0000660fe908660fe908660fe988ffff000066410fe98fffff0000660fe90c30660fe98c30ffff000066410fe98c37ffff000066420fe98c38ffff0000660fe98c70f2ff0f00660fe98cb0f4ff0f00660fe98cf0f8ff0f00660fe98cc4f8ff0f0066410fe98cc7f8ff0f0066420fe98cfcf8ff0f0066430fe98cfef8ff0f0066440fe93c250000000066440fe93c25ff00000066440fe93df7ffffff66440fe93df600000066440fe93df6ff000066440fe93866440fe93866440fe9b8ffff000066450fe9bfffff000066440fe93c3066440fe9bc30ffff000066450fe9bc37ffff000066460fe9bc38ffff000066440fe9bc70f2ff0f0066440fe9bcb0f4ff0f0066440fe9bcf0f8ff0f0066440fe9bcc4f8ff0f0066450fe9bcc7f8ff0f0066460fe9bcfcf8ff0f0066470fe9bcfef8ff0f00

bits 64

psubsw xmm0, xmm0
psubsw xmm0, xmm1
psubsw xmm0, xmm15
psubsw xmm1, xmm0
psubsw xmm1, xmm1
psubsw xmm1, xmm15
psubsw xmm15, xmm0
psubsw xmm15, xmm1
psubsw xmm15, xmm15
psubsw xmm0, [0x0]
psubsw xmm0, [0xFF]
psubsw xmm0, [rel $ + 0x0]
psubsw xmm0, [rel $ + 0xFF]
psubsw xmm0, [rel $ + 0xFFFF]
psubsw xmm0, [rax]
psubsw xmm0, [rax + 0x0]
psubsw xmm0, [rax + 0xFFFF]
psubsw xmm0, [r15 + 0xFFFF]
psubsw xmm0, [rax + rsi * 1  + 0x0]
psubsw xmm0, [rax + rsi + 0xFFFF]
psubsw xmm0, [r15 + rsi + 0xFFFF]
psubsw xmm0, [rax + r15 + 0xFFFF]
psubsw xmm0, [rax + rsi * 2 + 0xFFFF2]
psubsw xmm0, [rax + rsi * 4 + 0xFFFF4]
psubsw xmm0, [rax + rsi * 8 + 0xFFFF8]
psubsw xmm0, [rsp + rax * 8 + 0xFFFF8]
psubsw xmm0, [r15 + rax * 8 + 0xFFFF8]
psubsw xmm0, [rsp + r15 * 8 + 0xFFFF8]
psubsw xmm0, [r14 + r15 * 8 + 0xFFFF8]
psubsw xmm1, [0x0]
psubsw xmm1, [0xFF]
psubsw xmm1, [rel $ + 0x0]
psubsw xmm1, [rel $ + 0xFF]
psubsw xmm1, [rel $ + 0xFFFF]
psubsw xmm1, [rax]
psubsw xmm1, [rax + 0x0]
psubsw xmm1, [rax + 0xFFFF]
psubsw xmm1, [r15 + 0xFFFF]
psubsw xmm1, [rax + rsi * 1  + 0x0]
psubsw xmm1, [rax + rsi + 0xFFFF]
psubsw xmm1, [r15 + rsi + 0xFFFF]
psubsw xmm1, [rax + r15 + 0xFFFF]
psubsw xmm1, [rax + rsi * 2 + 0xFFFF2]
psubsw xmm1, [rax + rsi * 4 + 0xFFFF4]
psubsw xmm1, [rax + rsi * 8 + 0xFFFF8]
psubsw xmm1, [rsp + rax * 8 + 0xFFFF8]
psubsw xmm1, [r15 + rax * 8 + 0xFFFF8]
psubsw xmm1, [rsp + r15 * 8 + 0xFFFF8]
psubsw xmm1, [r14 + r15 * 8 + 0xFFFF8]
psubsw xmm15, [0x0]
psubsw xmm15, [0xFF]
psubsw xmm15, [rel $ + 0x0]
psubsw xmm15, [rel $ + 0xFF]
psubsw xmm15, [rel $ + 0xFFFF]
psubsw xmm15, [rax]
psubsw xmm15, [rax + 0x0]
psubsw xmm15, [rax + 0xFFFF]
psubsw xmm15, [r15 + 0xFFFF]
psubsw xmm15, [rax + rsi * 1  + 0x0]
psubsw xmm15, [rax + rsi + 0xFFFF]
psubsw xmm15, [r15 + rsi + 0xFFFF]
psubsw xmm15, [rax + r15 + 0xFFFF]
psubsw xmm15, [rax + rsi * 2 + 0xFFFF2]
psubsw xmm15, [rax + rsi * 4 + 0xFFFF4]
psubsw xmm15, [rax + rsi * 8 + 0xFFFF8]
psubsw xmm15, [rsp + rax * 8 + 0xFFFF8]
psubsw xmm15, [r15 + rax * 8 + 0xFFFF8]
psubsw xmm15, [rsp + r15 * 8 + 0xFFFF8]
psubsw xmm15, [r14 + r15 * 8 + 0xFFFF8]
