; expect: 660f64c0660f64c166410f64c7660f64c8660f64c966410f64cf66440f64f866440f64f966450f64ff660f64042500000000660f640425ff000000660f6405f8ffffff660f6405f7000000660f6405f7ff0000660f6400660f6400660f6480ffff000066410f6487ffff0000660f640430660f648430ffff000066410f648437ffff000066420f648438ffff0000660f648470f2ff0f00660f6484b0f4ff0f00660f6484f0f8ff0f00660f6484c4f8ff0f0066410f6484c7f8ff0f0066420f6484fcf8ff0f0066430f6484fef8ff0f00660f640c2500000000660f640c25ff000000660f640df8ffffff660f640df7000000660f640df7ff0000660f6408660f6408660f6488ffff000066410f648fffff0000660f640c30660f648c30ffff000066410f648c37ffff000066420f648c38ffff0000660f648c70f2ff0f00660f648cb0f4ff0f00660f648cf0f8ff0f00660f648cc4f8ff0f0066410f648cc7f8ff0f0066420f648cfcf8ff0f0066430f648cfef8ff0f0066440f643c250000000066440f643c25ff00000066440f643df7ffffff66440f643df600000066440f643df6ff000066440f643866440f643866440f64b8ffff000066450f64bfffff000066440f643c3066440f64bc30ffff000066450f64bc37ffff000066460f64bc38ffff000066440f64bc70f2ff0f0066440f64bcb0f4ff0f0066440f64bcf0f8ff0f0066440f64bcc4f8ff0f0066450f64bcc7f8ff0f0066460f64bcfcf8ff0f0066470f64bcfef8ff0f00

bits 64

pcmpgtb xmm0, xmm0
pcmpgtb xmm0, xmm1
pcmpgtb xmm0, xmm15
pcmpgtb xmm1, xmm0
pcmpgtb xmm1, xmm1
pcmpgtb xmm1, xmm15
pcmpgtb xmm15, xmm0
pcmpgtb xmm15, xmm1
pcmpgtb xmm15, xmm15
pcmpgtb xmm0, [0x0]
pcmpgtb xmm0, [0xFF]
pcmpgtb xmm0, [rel $ + 0x0]
pcmpgtb xmm0, [rel $ + 0xFF]
pcmpgtb xmm0, [rel $ + 0xFFFF]
pcmpgtb xmm0, [rax]
pcmpgtb xmm0, [rax + 0x0]
pcmpgtb xmm0, [rax + 0xFFFF]
pcmpgtb xmm0, [r15 + 0xFFFF]
pcmpgtb xmm0, [rax + rsi * 1  + 0x0]
pcmpgtb xmm0, [rax + rsi + 0xFFFF]
pcmpgtb xmm0, [r15 + rsi + 0xFFFF]
pcmpgtb xmm0, [rax + r15 + 0xFFFF]
pcmpgtb xmm0, [rax + rsi * 2 + 0xFFFF2]
pcmpgtb xmm0, [rax + rsi * 4 + 0xFFFF4]
pcmpgtb xmm0, [rax + rsi * 8 + 0xFFFF8]
pcmpgtb xmm0, [rsp + rax * 8 + 0xFFFF8]
pcmpgtb xmm0, [r15 + rax * 8 + 0xFFFF8]
pcmpgtb xmm0, [rsp + r15 * 8 + 0xFFFF8]
pcmpgtb xmm0, [r14 + r15 * 8 + 0xFFFF8]
pcmpgtb xmm1, [0x0]
pcmpgtb xmm1, [0xFF]
pcmpgtb xmm1, [rel $ + 0x0]
pcmpgtb xmm1, [rel $ + 0xFF]
pcmpgtb xmm1, [rel $ + 0xFFFF]
pcmpgtb xmm1, [rax]
pcmpgtb xmm1, [rax + 0x0]
pcmpgtb xmm1, [rax + 0xFFFF]
pcmpgtb xmm1, [r15 + 0xFFFF]
pcmpgtb xmm1, [rax + rsi * 1  + 0x0]
pcmpgtb xmm1, [rax + rsi + 0xFFFF]
pcmpgtb xmm1, [r15 + rsi + 0xFFFF]
pcmpgtb xmm1, [rax + r15 + 0xFFFF]
pcmpgtb xmm1, [rax + rsi * 2 + 0xFFFF2]
pcmpgtb xmm1, [rax + rsi * 4 + 0xFFFF4]
pcmpgtb xmm1, [rax + rsi * 8 + 0xFFFF8]
pcmpgtb xmm1, [rsp + rax * 8 + 0xFFFF8]
pcmpgtb xmm1, [r15 + rax * 8 + 0xFFFF8]
pcmpgtb xmm1, [rsp + r15 * 8 + 0xFFFF8]
pcmpgtb xmm1, [r14 + r15 * 8 + 0xFFFF8]
pcmpgtb xmm15, [0x0]
pcmpgtb xmm15, [0xFF]
pcmpgtb xmm15, [rel $ + 0x0]
pcmpgtb xmm15, [rel $ + 0xFF]
pcmpgtb xmm15, [rel $ + 0xFFFF]
pcmpgtb xmm15, [rax]
pcmpgtb xmm15, [rax + 0x0]
pcmpgtb xmm15, [rax + 0xFFFF]
pcmpgtb xmm15, [r15 + 0xFFFF]
pcmpgtb xmm15, [rax + rsi * 1  + 0x0]
pcmpgtb xmm15, [rax + rsi + 0xFFFF]
pcmpgtb xmm15, [r15 + rsi + 0xFFFF]
pcmpgtb xmm15, [rax + r15 + 0xFFFF]
pcmpgtb xmm15, [rax + rsi * 2 + 0xFFFF2]
pcmpgtb xmm15, [rax + rsi * 4 + 0xFFFF4]
pcmpgtb xmm15, [rax + rsi * 8 + 0xFFFF8]
pcmpgtb xmm15, [rsp + rax * 8 + 0xFFFF8]
pcmpgtb xmm15, [r15 + rax * 8 + 0xFFFF8]
pcmpgtb xmm15, [rsp + r15 * 8 + 0xFFFF8]
pcmpgtb xmm15, [r14 + r15 * 8 + 0xFFFF8]
