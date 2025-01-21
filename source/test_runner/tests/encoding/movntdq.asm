; expect: 660fe7042500000000660fe70c250000000066440fe73c2500000000660fe70425ff000000660fe70c25ff00000066440fe73c25ff000000660fe705f8ffffff660fe70df8ffffff66440fe73df7ffffff660fe705f7000000660fe70df700000066440fe73df6000000660fe705f7ff0000660fe70df7ff000066440fe73df6ff0000660fe700660fe70866440fe738660fe700660fe70866440fe738660fe780ffff0000660fe788ffff000066440fe7b8ffff000066410fe787ffff000066410fe78fffff000066450fe7bfffff0000660fe70430660fe70c3066440fe73c30660fe78430ffff0000660fe78c30ffff000066440fe7bc30ffff000066410fe78437ffff000066410fe78c37ffff000066450fe7bc37ffff000066420fe78438ffff000066420fe78c38ffff000066460fe7bc38ffff0000660fe78470f2ff0f00660fe78c70f2ff0f0066440fe7bc70f2ff0f00660fe784b0f4ff0f00660fe78cb0f4ff0f0066440fe7bcb0f4ff0f00660fe784f0f8ff0f00660fe78cf0f8ff0f0066440fe7bcf0f8ff0f00660fe784c4f8ff0f00660fe78cc4f8ff0f0066440fe7bcc4f8ff0f0066410fe784c7f8ff0f0066410fe78cc7f8ff0f0066450fe7bcc7f8ff0f0066420fe784fcf8ff0f0066420fe78cfcf8ff0f0066460fe7bcfcf8ff0f0066430fe784fef8ff0f0066430fe78cfef8ff0f0066470fe7bcfef8ff0f00

movntdq [0x0], xmm0
movntdq [0x0], xmm1
movntdq [0x0], xmm15
movntdq [0xFF], xmm0
movntdq [0xFF], xmm1
movntdq [0xFF], xmm15
movntdq [rel $ + 0x0], xmm0
movntdq [rel $ + 0x0], xmm1
movntdq [rel $ + 0x0], xmm15
movntdq [rel $ + 0xFF], xmm0
movntdq [rel $ + 0xFF], xmm1
movntdq [rel $ + 0xFF], xmm15
movntdq [rel $ + 0xFFFF], xmm0
movntdq [rel $ + 0xFFFF], xmm1
movntdq [rel $ + 0xFFFF], xmm15
movntdq [rax], xmm0
movntdq [rax], xmm1
movntdq [rax], xmm15
movntdq [rax + 0x0], xmm0
movntdq [rax + 0x0], xmm1
movntdq [rax + 0x0], xmm15
movntdq [rax + 0xFFFF], xmm0
movntdq [rax + 0xFFFF], xmm1
movntdq [rax + 0xFFFF], xmm15
movntdq [r15 + 0xFFFF], xmm0
movntdq [r15 + 0xFFFF], xmm1
movntdq [r15 + 0xFFFF], xmm15
movntdq [rax + rsi * 1  + 0x0], xmm0
movntdq [rax + rsi * 1  + 0x0], xmm1
movntdq [rax + rsi * 1  + 0x0], xmm15
movntdq [rax + rsi + 0xFFFF], xmm0
movntdq [rax + rsi + 0xFFFF], xmm1
movntdq [rax + rsi + 0xFFFF], xmm15
movntdq [r15 + rsi + 0xFFFF], xmm0
movntdq [r15 + rsi + 0xFFFF], xmm1
movntdq [r15 + rsi + 0xFFFF], xmm15
movntdq [rax + r15 + 0xFFFF], xmm0
movntdq [rax + r15 + 0xFFFF], xmm1
movntdq [rax + r15 + 0xFFFF], xmm15
movntdq [rax + rsi * 2 + 0xFFFF2], xmm0
movntdq [rax + rsi * 2 + 0xFFFF2], xmm1
movntdq [rax + rsi * 2 + 0xFFFF2], xmm15
movntdq [rax + rsi * 4 + 0xFFFF4], xmm0
movntdq [rax + rsi * 4 + 0xFFFF4], xmm1
movntdq [rax + rsi * 4 + 0xFFFF4], xmm15
movntdq [rax + rsi * 8 + 0xFFFF8], xmm0
movntdq [rax + rsi * 8 + 0xFFFF8], xmm1
movntdq [rax + rsi * 8 + 0xFFFF8], xmm15
movntdq [rsp + rax * 8 + 0xFFFF8], xmm0
movntdq [rsp + rax * 8 + 0xFFFF8], xmm1
movntdq [rsp + rax * 8 + 0xFFFF8], xmm15
movntdq [r15 + rax * 8 + 0xFFFF8], xmm0
movntdq [r15 + rax * 8 + 0xFFFF8], xmm1
movntdq [r15 + rax * 8 + 0xFFFF8], xmm15
movntdq [rsp + r15 * 8 + 0xFFFF8], xmm0
movntdq [rsp + r15 * 8 + 0xFFFF8], xmm1
movntdq [rsp + r15 * 8 + 0xFFFF8], xmm15
movntdq [r14 + r15 * 8 + 0xFFFF8], xmm0
movntdq [r14 + r15 * 8 + 0xFFFF8], xmm1
movntdq [r14 + r15 * 8 + 0xFFFF8], xmm15