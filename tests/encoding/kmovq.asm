; expect: c4e1f890c9c4e1f890cac4e1f890cfc4e1f890d1c4e1f890d2c4e1f890d7c4e1f890f9c4e1f890fac4e1f890ffc4e1f8900c2500000000c4e1f8900c25ff000000c4e1f8900df7ffffffc4e1f8900df6000000c4e1f8900df6ff0000c4e1f89008c4e1f89008c4e1f89088ffff0000c4c1f8908fffff0000c4e1f8900c30c4e1f8908c30ffff0000c4c1f8908c37ffff0000c4a1f8908c38ffff0000c4e1f8908c70f2ff0f00c4e1f8908cb0f4ff0f00c4e1f8908cf0f8ff0f00c4e1f8908cc4f8ff0f00c4c1f8908cc7f8ff0f00c4a1f8908cfcf8ff0f00c481f8908cfef8ff0f00c4e1f890142500000000c4e1f8901425ff000000c4e1f89015f7ffffffc4e1f89015f6000000c4e1f89015f6ff0000c4e1f89010c4e1f89010c4e1f89090ffff0000c4c1f89097ffff0000c4e1f8901430c4e1f8909430ffff0000c4c1f8909437ffff0000c4a1f8909438ffff0000c4e1f8909470f2ff0f00c4e1f89094b0f4ff0f00c4e1f89094f0f8ff0f00c4e1f89094c4f8ff0f00c4c1f89094c7f8ff0f00c4a1f89094fcf8ff0f00c481f89094fef8ff0f00c4e1f8903c2500000000c4e1f8903c25ff000000c4e1f8903df7ffffffc4e1f8903df6000000c4e1f8903df6ff0000c4e1f89038c4e1f89038c4e1f890b8ffff0000c4c1f890bfffff0000c4e1f8903c30c4e1f890bc30ffff0000c4c1f890bc37ffff0000c4a1f890bc38ffff0000c4e1f890bc70f2ff0f00c4e1f890bcb0f4ff0f00c4e1f890bcf0f8ff0f00c4e1f890bcc4f8ff0f00c4c1f890bcc7f8ff0f00c4a1f890bcfcf8ff0f00c481f890bcfef8ff0f00c4e1fb92c9c4e1fb92cbc4c1fb92cfc4e1fb92d1c4e1fb92d3c4c1fb92d7c4e1fb92f9c4e1fb92fbc4c1fb92ffc4e1f8910c2500000000c4e1f891142500000000c4e1f8913c2500000000c4e1f8910c25ff000000c4e1f8911425ff000000c4e1f8913c25ff000000c4e1f8910df7ffffffc4e1f89115f7ffffffc4e1f8913df7ffffffc4e1f8910df6000000c4e1f89115f6000000c4e1f8913df6000000c4e1f8910df6ff0000c4e1f89115f6ff0000c4e1f8913df6ff0000c4e1f89108c4e1f89110c4e1f89138c4e1f89108c4e1f89110c4e1f89138c4e1f89188ffff0000c4e1f89190ffff0000c4e1f891b8ffff0000c4c1f8918fffff0000c4c1f89197ffff0000c4c1f891bfffff0000c4e1f8910c30c4e1f8911430c4e1f8913c30c4e1f8918c30ffff0000c4e1f8919430ffff0000c4e1f891bc30ffff0000c4c1f8918c37ffff0000c4c1f8919437ffff0000c4c1f891bc37ffff0000c4a1f8918c38ffff0000c4a1f8919438ffff0000c4a1f891bc38ffff0000c4e1f8918c70f2ff0f00c4e1f8919470f2ff0f00c4e1f891bc70f2ff0f00c4e1f8918cb0f4ff0f00c4e1f89194b0f4ff0f00c4e1f891bcb0f4ff0f00c4e1f8918cf0f8ff0f00c4e1f89194f0f8ff0f00c4e1f891bcf0f8ff0f00c4e1f8918cc4f8ff0f00c4e1f89194c4f8ff0f00c4e1f891bcc4f8ff0f00c4c1f8918cc7f8ff0f00c4c1f89194c7f8ff0f00c4c1f891bcc7f8ff0f00c4a1f8918cfcf8ff0f00c4a1f89194fcf8ff0f00c4a1f891bcfcf8ff0f00c481f8918cfef8ff0f00c481f89194fef8ff0f00c481f891bcfef8ff0f00c4e1fb93c9c4e1fb93cac4e1fb93cfc4e1fb93d9c4e1fb93dac4e1fb93dfc461fb93f9c461fb93fac461fb93ff

bits 64

kmovq k1, k1
kmovq k1, k2
kmovq k1, k7
kmovq k2, k1
kmovq k2, k2
kmovq k2, k7
kmovq k7, k1
kmovq k7, k2
kmovq k7, k7
kmovq k1, qword [0x0]
kmovq k1, qword [0xFF]
kmovq k1, qword [rel $ + 0x0]
kmovq k1, qword [rel $ + 0xFF]
kmovq k1, qword [rel $ + 0xFFFF]
kmovq k1, qword [rax]
kmovq k1, qword [rax + 0x0]
kmovq k1, qword [rax + 0xFFFF]
kmovq k1, qword [r15 + 0xFFFF]
kmovq k1, qword [rax + rsi * 1  + 0x0]
kmovq k1, qword [rax + rsi + 0xFFFF]
kmovq k1, qword [r15 + rsi + 0xFFFF]
kmovq k1, qword [rax + r15 + 0xFFFF]
kmovq k1, qword [rax + rsi * 2 + 0xFFFF2]
kmovq k1, qword [rax + rsi * 4 + 0xFFFF4]
kmovq k1, qword [rax + rsi * 8 + 0xFFFF8]
kmovq k1, qword [rsp + rax * 8 + 0xFFFF8]
kmovq k1, qword [r15 + rax * 8 + 0xFFFF8]
kmovq k1, qword [rsp + r15 * 8 + 0xFFFF8]
kmovq k1, qword [r14 + r15 * 8 + 0xFFFF8]
kmovq k2, qword [0x0]
kmovq k2, qword [0xFF]
kmovq k2, qword [rel $ + 0x0]
kmovq k2, qword [rel $ + 0xFF]
kmovq k2, qword [rel $ + 0xFFFF]
kmovq k2, qword [rax]
kmovq k2, qword [rax + 0x0]
kmovq k2, qword [rax + 0xFFFF]
kmovq k2, qword [r15 + 0xFFFF]
kmovq k2, qword [rax + rsi * 1  + 0x0]
kmovq k2, qword [rax + rsi + 0xFFFF]
kmovq k2, qword [r15 + rsi + 0xFFFF]
kmovq k2, qword [rax + r15 + 0xFFFF]
kmovq k2, qword [rax + rsi * 2 + 0xFFFF2]
kmovq k2, qword [rax + rsi * 4 + 0xFFFF4]
kmovq k2, qword [rax + rsi * 8 + 0xFFFF8]
kmovq k2, qword [rsp + rax * 8 + 0xFFFF8]
kmovq k2, qword [r15 + rax * 8 + 0xFFFF8]
kmovq k2, qword [rsp + r15 * 8 + 0xFFFF8]
kmovq k2, qword [r14 + r15 * 8 + 0xFFFF8]
kmovq k7, qword [0x0]
kmovq k7, qword [0xFF]
kmovq k7, qword [rel $ + 0x0]
kmovq k7, qword [rel $ + 0xFF]
kmovq k7, qword [rel $ + 0xFFFF]
kmovq k7, qword [rax]
kmovq k7, qword [rax + 0x0]
kmovq k7, qword [rax + 0xFFFF]
kmovq k7, qword [r15 + 0xFFFF]
kmovq k7, qword [rax + rsi * 1  + 0x0]
kmovq k7, qword [rax + rsi + 0xFFFF]
kmovq k7, qword [r15 + rsi + 0xFFFF]
kmovq k7, qword [rax + r15 + 0xFFFF]
kmovq k7, qword [rax + rsi * 2 + 0xFFFF2]
kmovq k7, qword [rax + rsi * 4 + 0xFFFF4]
kmovq k7, qword [rax + rsi * 8 + 0xFFFF8]
kmovq k7, qword [rsp + rax * 8 + 0xFFFF8]
kmovq k7, qword [r15 + rax * 8 + 0xFFFF8]
kmovq k7, qword [rsp + r15 * 8 + 0xFFFF8]
kmovq k7, qword [r14 + r15 * 8 + 0xFFFF8]
kmovq k1, rcx
kmovq k1, rbx
kmovq k1, r15
kmovq k2, rcx
kmovq k2, rbx
kmovq k2, r15
kmovq k7, rcx
kmovq k7, rbx
kmovq k7, r15
kmovq qword [0x0], k1
kmovq qword [0x0], k2
kmovq qword [0x0], k7
kmovq qword [0xFF], k1
kmovq qword [0xFF], k2
kmovq qword [0xFF], k7
kmovq qword [rel $ + 0x0], k1
kmovq qword [rel $ + 0x0], k2
kmovq qword [rel $ + 0x0], k7
kmovq qword [rel $ + 0xFF], k1
kmovq qword [rel $ + 0xFF], k2
kmovq qword [rel $ + 0xFF], k7
kmovq qword [rel $ + 0xFFFF], k1
kmovq qword [rel $ + 0xFFFF], k2
kmovq qword [rel $ + 0xFFFF], k7
kmovq qword [rax], k1
kmovq qword [rax], k2
kmovq qword [rax], k7
kmovq qword [rax + 0x0], k1
kmovq qword [rax + 0x0], k2
kmovq qword [rax + 0x0], k7
kmovq qword [rax + 0xFFFF], k1
kmovq qword [rax + 0xFFFF], k2
kmovq qword [rax + 0xFFFF], k7
kmovq qword [r15 + 0xFFFF], k1
kmovq qword [r15 + 0xFFFF], k2
kmovq qword [r15 + 0xFFFF], k7
kmovq qword [rax + rsi * 1  + 0x0], k1
kmovq qword [rax + rsi * 1  + 0x0], k2
kmovq qword [rax + rsi * 1  + 0x0], k7
kmovq qword [rax + rsi + 0xFFFF], k1
kmovq qword [rax + rsi + 0xFFFF], k2
kmovq qword [rax + rsi + 0xFFFF], k7
kmovq qword [r15 + rsi + 0xFFFF], k1
kmovq qword [r15 + rsi + 0xFFFF], k2
kmovq qword [r15 + rsi + 0xFFFF], k7
kmovq qword [rax + r15 + 0xFFFF], k1
kmovq qword [rax + r15 + 0xFFFF], k2
kmovq qword [rax + r15 + 0xFFFF], k7
kmovq qword [rax + rsi * 2 + 0xFFFF2], k1
kmovq qword [rax + rsi * 2 + 0xFFFF2], k2
kmovq qword [rax + rsi * 2 + 0xFFFF2], k7
kmovq qword [rax + rsi * 4 + 0xFFFF4], k1
kmovq qword [rax + rsi * 4 + 0xFFFF4], k2
kmovq qword [rax + rsi * 4 + 0xFFFF4], k7
kmovq qword [rax + rsi * 8 + 0xFFFF8], k1
kmovq qword [rax + rsi * 8 + 0xFFFF8], k2
kmovq qword [rax + rsi * 8 + 0xFFFF8], k7
kmovq qword [rsp + rax * 8 + 0xFFFF8], k1
kmovq qword [rsp + rax * 8 + 0xFFFF8], k2
kmovq qword [rsp + rax * 8 + 0xFFFF8], k7
kmovq qword [r15 + rax * 8 + 0xFFFF8], k1
kmovq qword [r15 + rax * 8 + 0xFFFF8], k2
kmovq qword [r15 + rax * 8 + 0xFFFF8], k7
kmovq qword [rsp + r15 * 8 + 0xFFFF8], k1
kmovq qword [rsp + r15 * 8 + 0xFFFF8], k2
kmovq qword [rsp + r15 * 8 + 0xFFFF8], k7
kmovq qword [r14 + r15 * 8 + 0xFFFF8], k1
kmovq qword [r14 + r15 * 8 + 0xFFFF8], k2
kmovq qword [r14 + r15 * 8 + 0xFFFF8], k7
kmovq rcx, k1
kmovq rcx, k2
kmovq rcx, k7
kmovq rbx, k1
kmovq rbx, k2
kmovq rbx, k7
kmovq r15, k1
kmovq r15, k2
kmovq r15, k7
