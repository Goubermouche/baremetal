; expect: c5f890c9c5f890cac5f890cfc5f890d1c5f890d2c5f890d7c5f890f9c5f890fac5f890ffc5f8900c2500000000c5f8900c25ff000000c5f8900df8ffffffc5f8900df7000000c5f8900df7ff0000c5f89008c5f89008c5f89088ffff0000c4c178908fffff0000c5f8900c30c5f8908c30ffff0000c4c178908c37ffff0000c4a178908c38ffff0000c5f8908c70f2ff0f00c5f8908cb0f4ff0f00c5f8908cf0f8ff0f00c5f8908cc4f8ff0f00c4c178908cc7f8ff0f00c4a178908cfcf8ff0f00c48178908cfef8ff0f00c5f890142500000000c5f8901425ff000000c5f89015f8ffffffc5f89015f7000000c5f89015f7ff0000c5f89010c5f89010c5f89090ffff0000c4c1789097ffff0000c5f8901430c5f8909430ffff0000c4c178909437ffff0000c4a178909438ffff0000c5f8909470f2ff0f00c5f89094b0f4ff0f00c5f89094f0f8ff0f00c5f89094c4f8ff0f00c4c1789094c7f8ff0f00c4a1789094fcf8ff0f00c481789094fef8ff0f00c5f8903c2500000000c5f8903c25ff000000c5f8903df8ffffffc5f8903df7000000c5f8903df7ff0000c5f89038c5f89038c5f890b8ffff0000c4c17890bfffff0000c5f8903c30c5f890bc30ffff0000c4c17890bc37ffff0000c4a17890bc38ffff0000c5f890bc70f2ff0f00c5f890bcb0f4ff0f00c5f890bcf0f8ff0f00c5f890bcc4f8ff0f00c4c17890bcc7f8ff0f00c4a17890bcfcf8ff0f00c4817890bcfef8ff0f00c5f892c9c5f892cbc4c17892cfc5f892d1c5f892d3c4c17892d7c5f892f9c5f892fbc4c17892ffc5f8910c2500000000c5f891142500000000c5f8913c2500000000c5f8910c25ff000000c5f8911425ff000000c5f8913c25ff000000c5f8910df8ffffffc5f89115f8ffffffc5f8913df8ffffffc5f8910df7000000c5f89115f7000000c5f8913df7000000c5f8910df7ff0000c5f89115f7ff0000c5f8913df7ff0000c5f89108c5f89110c5f89138c5f89108c5f89110c5f89138c5f89188ffff0000c5f89190ffff0000c5f891b8ffff0000c4c178918fffff0000c4c1789197ffff0000c4c17891bfffff0000c5f8910c30c5f8911430c5f8913c30c5f8918c30ffff0000c5f8919430ffff0000c5f891bc30ffff0000c4c178918c37ffff0000c4c178919437ffff0000c4c17891bc37ffff0000c4a178918c38ffff0000c4a178919438ffff0000c4a17891bc38ffff0000c5f8918c70f2ff0f00c5f8919470f2ff0f00c5f891bc70f2ff0f00c5f8918cb0f4ff0f00c5f89194b0f4ff0f00c5f891bcb0f4ff0f00c5f8918cf0f8ff0f00c5f89194f0f8ff0f00c5f891bcf0f8ff0f00c5f8918cc4f8ff0f00c5f89194c4f8ff0f00c5f891bcc4f8ff0f00c4c178918cc7f8ff0f00c4c1789194c7f8ff0f00c4c17891bcc7f8ff0f00c4a178918cfcf8ff0f00c4a1789194fcf8ff0f00c4a17891bcfcf8ff0f00c48178918cfef8ff0f00c481789194fef8ff0f00c4817891bcfef8ff0f00c5f893c9c5f893cac5f893cfc5f893d9c5f893dac5f893dfc57893f9c57893fac57893ff

bits 64

kmovw k1, k1
kmovw k1, k2
kmovw k1, k7
kmovw k2, k1
kmovw k2, k2
kmovw k2, k7
kmovw k7, k1
kmovw k7, k2
kmovw k7, k7
kmovw k1, word [0x0]
kmovw k1, word [0xFF]
kmovw k1, word [rel $ + 0x0]
kmovw k1, word [rel $ + 0xFF]
kmovw k1, word [rel $ + 0xFFFF]
kmovw k1, word [rax]
kmovw k1, word [rax + 0x0]
kmovw k1, word [rax + 0xFFFF]
kmovw k1, word [r15 + 0xFFFF]
kmovw k1, word [rax + rsi * 1  + 0x0]
kmovw k1, word [rax + rsi + 0xFFFF]
kmovw k1, word [r15 + rsi + 0xFFFF]
kmovw k1, word [rax + r15 + 0xFFFF]
kmovw k1, word [rax + rsi * 2 + 0xFFFF2]
kmovw k1, word [rax + rsi * 4 + 0xFFFF4]
kmovw k1, word [rax + rsi * 8 + 0xFFFF8]
kmovw k1, word [rsp + rax * 8 + 0xFFFF8]
kmovw k1, word [r15 + rax * 8 + 0xFFFF8]
kmovw k1, word [rsp + r15 * 8 + 0xFFFF8]
kmovw k1, word [r14 + r15 * 8 + 0xFFFF8]
kmovw k2, word [0x0]
kmovw k2, word [0xFF]
kmovw k2, word [rel $ + 0x0]
kmovw k2, word [rel $ + 0xFF]
kmovw k2, word [rel $ + 0xFFFF]
kmovw k2, word [rax]
kmovw k2, word [rax + 0x0]
kmovw k2, word [rax + 0xFFFF]
kmovw k2, word [r15 + 0xFFFF]
kmovw k2, word [rax + rsi * 1  + 0x0]
kmovw k2, word [rax + rsi + 0xFFFF]
kmovw k2, word [r15 + rsi + 0xFFFF]
kmovw k2, word [rax + r15 + 0xFFFF]
kmovw k2, word [rax + rsi * 2 + 0xFFFF2]
kmovw k2, word [rax + rsi * 4 + 0xFFFF4]
kmovw k2, word [rax + rsi * 8 + 0xFFFF8]
kmovw k2, word [rsp + rax * 8 + 0xFFFF8]
kmovw k2, word [r15 + rax * 8 + 0xFFFF8]
kmovw k2, word [rsp + r15 * 8 + 0xFFFF8]
kmovw k2, word [r14 + r15 * 8 + 0xFFFF8]
kmovw k7, word [0x0]
kmovw k7, word [0xFF]
kmovw k7, word [rel $ + 0x0]
kmovw k7, word [rel $ + 0xFF]
kmovw k7, word [rel $ + 0xFFFF]
kmovw k7, word [rax]
kmovw k7, word [rax + 0x0]
kmovw k7, word [rax + 0xFFFF]
kmovw k7, word [r15 + 0xFFFF]
kmovw k7, word [rax + rsi * 1  + 0x0]
kmovw k7, word [rax + rsi + 0xFFFF]
kmovw k7, word [r15 + rsi + 0xFFFF]
kmovw k7, word [rax + r15 + 0xFFFF]
kmovw k7, word [rax + rsi * 2 + 0xFFFF2]
kmovw k7, word [rax + rsi * 4 + 0xFFFF4]
kmovw k7, word [rax + rsi * 8 + 0xFFFF8]
kmovw k7, word [rsp + rax * 8 + 0xFFFF8]
kmovw k7, word [r15 + rax * 8 + 0xFFFF8]
kmovw k7, word [rsp + r15 * 8 + 0xFFFF8]
kmovw k7, word [r14 + r15 * 8 + 0xFFFF8]
kmovw k1, ecx
kmovw k1, ebx
kmovw k1, r15d
kmovw k2, ecx
kmovw k2, ebx
kmovw k2, r15d
kmovw k7, ecx
kmovw k7, ebx
kmovw k7, r15d
kmovw word [0x0], k1
kmovw word [0x0], k2
kmovw word [0x0], k7
kmovw word [0xFF], k1
kmovw word [0xFF], k2
kmovw word [0xFF], k7
kmovw word [rel $ + 0x0], k1
kmovw word [rel $ + 0x0], k2
kmovw word [rel $ + 0x0], k7
kmovw word [rel $ + 0xFF], k1
kmovw word [rel $ + 0xFF], k2
kmovw word [rel $ + 0xFF], k7
kmovw word [rel $ + 0xFFFF], k1
kmovw word [rel $ + 0xFFFF], k2
kmovw word [rel $ + 0xFFFF], k7
kmovw word [rax], k1
kmovw word [rax], k2
kmovw word [rax], k7
kmovw word [rax + 0x0], k1
kmovw word [rax + 0x0], k2
kmovw word [rax + 0x0], k7
kmovw word [rax + 0xFFFF], k1
kmovw word [rax + 0xFFFF], k2
kmovw word [rax + 0xFFFF], k7
kmovw word [r15 + 0xFFFF], k1
kmovw word [r15 + 0xFFFF], k2
kmovw word [r15 + 0xFFFF], k7
kmovw word [rax + rsi * 1  + 0x0], k1
kmovw word [rax + rsi * 1  + 0x0], k2
kmovw word [rax + rsi * 1  + 0x0], k7
kmovw word [rax + rsi + 0xFFFF], k1
kmovw word [rax + rsi + 0xFFFF], k2
kmovw word [rax + rsi + 0xFFFF], k7
kmovw word [r15 + rsi + 0xFFFF], k1
kmovw word [r15 + rsi + 0xFFFF], k2
kmovw word [r15 + rsi + 0xFFFF], k7
kmovw word [rax + r15 + 0xFFFF], k1
kmovw word [rax + r15 + 0xFFFF], k2
kmovw word [rax + r15 + 0xFFFF], k7
kmovw word [rax + rsi * 2 + 0xFFFF2], k1
kmovw word [rax + rsi * 2 + 0xFFFF2], k2
kmovw word [rax + rsi * 2 + 0xFFFF2], k7
kmovw word [rax + rsi * 4 + 0xFFFF4], k1
kmovw word [rax + rsi * 4 + 0xFFFF4], k2
kmovw word [rax + rsi * 4 + 0xFFFF4], k7
kmovw word [rax + rsi * 8 + 0xFFFF8], k1
kmovw word [rax + rsi * 8 + 0xFFFF8], k2
kmovw word [rax + rsi * 8 + 0xFFFF8], k7
kmovw word [rsp + rax * 8 + 0xFFFF8], k1
kmovw word [rsp + rax * 8 + 0xFFFF8], k2
kmovw word [rsp + rax * 8 + 0xFFFF8], k7
kmovw word [r15 + rax * 8 + 0xFFFF8], k1
kmovw word [r15 + rax * 8 + 0xFFFF8], k2
kmovw word [r15 + rax * 8 + 0xFFFF8], k7
kmovw word [rsp + r15 * 8 + 0xFFFF8], k1
kmovw word [rsp + r15 * 8 + 0xFFFF8], k2
kmovw word [rsp + r15 * 8 + 0xFFFF8], k7
kmovw word [r14 + r15 * 8 + 0xFFFF8], k1
kmovw word [r14 + r15 * 8 + 0xFFFF8], k2
kmovw word [r14 + r15 * 8 + 0xFFFF8], k7
kmovw ecx, k1
kmovw ecx, k2
kmovw ecx, k7
kmovw ebx, k1
kmovw ebx, k2
kmovw ebx, k7
kmovw r15d, k1
kmovw r15d, k2
kmovw r15d, k7
