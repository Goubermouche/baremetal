; expect: 660f3824c0660f3824c166410f3824c7660f3824c8660f3824c966410f3824cf66440f3824f866440f3824f966450f3824ff660f3824042500000000660f38240425ff000000660f382405f7ffffff660f382405f6000000660f382405f6ff0000660f382400660f382400660f382480ffff000066410f382487ffff0000660f38240430660f38248430ffff000066410f38248437ffff000066420f38248438ffff0000660f38248470f2ff0f00660f382484b0f4ff0f00660f382484f0f8ff0f00660f382484c4f8ff0f0066410f382484c7f8ff0f0066420f382484fcf8ff0f0066430f382484fef8ff0f00660f38240c2500000000660f38240c25ff000000660f38240df7ffffff660f38240df6000000660f38240df6ff0000660f382408660f382408660f382488ffff000066410f38248fffff0000660f38240c30660f38248c30ffff000066410f38248c37ffff000066420f38248c38ffff0000660f38248c70f2ff0f00660f38248cb0f4ff0f00660f38248cf0f8ff0f00660f38248cc4f8ff0f0066410f38248cc7f8ff0f0066420f38248cfcf8ff0f0066430f38248cfef8ff0f0066440f38243c250000000066440f38243c25ff00000066440f38243df6ffffff66440f38243df500000066440f38243df5ff000066440f38243866440f38243866440f3824b8ffff000066450f3824bfffff000066440f38243c3066440f3824bc30ffff000066450f3824bc37ffff000066460f3824bc38ffff000066440f3824bc70f2ff0f0066440f3824bcb0f4ff0f0066440f3824bcf0f8ff0f0066440f3824bcc4f8ff0f0066450f3824bcc7f8ff0f0066460f3824bcfcf8ff0f0066470f3824bcfef8ff0f00

bits 64

pmovsxwq xmm0, xmm0
pmovsxwq xmm0, xmm1
pmovsxwq xmm0, xmm15
pmovsxwq xmm1, xmm0
pmovsxwq xmm1, xmm1
pmovsxwq xmm1, xmm15
pmovsxwq xmm15, xmm0
pmovsxwq xmm15, xmm1
pmovsxwq xmm15, xmm15
pmovsxwq xmm0, dword [0x0]
pmovsxwq xmm0, dword [0xFF]
pmovsxwq xmm0, dword [rel $ + 0x0]
pmovsxwq xmm0, dword [rel $ + 0xFF]
pmovsxwq xmm0, dword [rel $ + 0xFFFF]
pmovsxwq xmm0, dword [rax]
pmovsxwq xmm0, dword [rax + 0x0]
pmovsxwq xmm0, dword [rax + 0xFFFF]
pmovsxwq xmm0, dword [r15 + 0xFFFF]
pmovsxwq xmm0, dword [rax + rsi * 1  + 0x0]
pmovsxwq xmm0, dword [rax + rsi + 0xFFFF]
pmovsxwq xmm0, dword [r15 + rsi + 0xFFFF]
pmovsxwq xmm0, dword [rax + r15 + 0xFFFF]
pmovsxwq xmm0, dword [rax + rsi * 2 + 0xFFFF2]
pmovsxwq xmm0, dword [rax + rsi * 4 + 0xFFFF4]
pmovsxwq xmm0, dword [rax + rsi * 8 + 0xFFFF8]
pmovsxwq xmm0, dword [rsp + rax * 8 + 0xFFFF8]
pmovsxwq xmm0, dword [r15 + rax * 8 + 0xFFFF8]
pmovsxwq xmm0, dword [rsp + r15 * 8 + 0xFFFF8]
pmovsxwq xmm0, dword [r14 + r15 * 8 + 0xFFFF8]
pmovsxwq xmm1, dword [0x0]
pmovsxwq xmm1, dword [0xFF]
pmovsxwq xmm1, dword [rel $ + 0x0]
pmovsxwq xmm1, dword [rel $ + 0xFF]
pmovsxwq xmm1, dword [rel $ + 0xFFFF]
pmovsxwq xmm1, dword [rax]
pmovsxwq xmm1, dword [rax + 0x0]
pmovsxwq xmm1, dword [rax + 0xFFFF]
pmovsxwq xmm1, dword [r15 + 0xFFFF]
pmovsxwq xmm1, dword [rax + rsi * 1  + 0x0]
pmovsxwq xmm1, dword [rax + rsi + 0xFFFF]
pmovsxwq xmm1, dword [r15 + rsi + 0xFFFF]
pmovsxwq xmm1, dword [rax + r15 + 0xFFFF]
pmovsxwq xmm1, dword [rax + rsi * 2 + 0xFFFF2]
pmovsxwq xmm1, dword [rax + rsi * 4 + 0xFFFF4]
pmovsxwq xmm1, dword [rax + rsi * 8 + 0xFFFF8]
pmovsxwq xmm1, dword [rsp + rax * 8 + 0xFFFF8]
pmovsxwq xmm1, dword [r15 + rax * 8 + 0xFFFF8]
pmovsxwq xmm1, dword [rsp + r15 * 8 + 0xFFFF8]
pmovsxwq xmm1, dword [r14 + r15 * 8 + 0xFFFF8]
pmovsxwq xmm15, dword [0x0]
pmovsxwq xmm15, dword [0xFF]
pmovsxwq xmm15, dword [rel $ + 0x0]
pmovsxwq xmm15, dword [rel $ + 0xFF]
pmovsxwq xmm15, dword [rel $ + 0xFFFF]
pmovsxwq xmm15, dword [rax]
pmovsxwq xmm15, dword [rax + 0x0]
pmovsxwq xmm15, dword [rax + 0xFFFF]
pmovsxwq xmm15, dword [r15 + 0xFFFF]
pmovsxwq xmm15, dword [rax + rsi * 1  + 0x0]
pmovsxwq xmm15, dword [rax + rsi + 0xFFFF]
pmovsxwq xmm15, dword [r15 + rsi + 0xFFFF]
pmovsxwq xmm15, dword [rax + r15 + 0xFFFF]
pmovsxwq xmm15, dword [rax + rsi * 2 + 0xFFFF2]
pmovsxwq xmm15, dword [rax + rsi * 4 + 0xFFFF4]
pmovsxwq xmm15, dword [rax + rsi * 8 + 0xFFFF8]
pmovsxwq xmm15, dword [rsp + rax * 8 + 0xFFFF8]
pmovsxwq xmm15, dword [r15 + rax * 8 + 0xFFFF8]
pmovsxwq xmm15, dword [rsp + r15 * 8 + 0xFFFF8]
pmovsxwq xmm15, dword [r14 + r15 * 8 + 0xFFFF8]
