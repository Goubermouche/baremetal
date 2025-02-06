; expect: 660f38f50c2500000000660f38f51c250000000066440f38f53c2500000000660f38f50c25ff000000660f38f51c25ff00000066440f38f53c25ff000000660f38f50df7ffffff660f38f51df7ffffff66440f38f53df6ffffff660f38f50df6000000660f38f51df600000066440f38f53df5000000660f38f50df6ff0000660f38f51df6ff000066440f38f53df5ff0000660f38f508660f38f51866440f38f538660f38f508660f38f51866440f38f538660f38f588ffff0000660f38f598ffff000066440f38f5b8ffff000066410f38f58fffff000066410f38f59fffff000066450f38f5bfffff0000660f38f50c30660f38f51c3066440f38f53c30660f38f58c30ffff0000660f38f59c30ffff000066440f38f5bc30ffff000066410f38f58c37ffff000066410f38f59c37ffff000066450f38f5bc37ffff000066420f38f58c38ffff000066420f38f59c38ffff000066460f38f5bc38ffff0000660f38f58c70f2ff0f00660f38f59c70f2ff0f0066440f38f5bc70f2ff0f00660f38f58cb0f4ff0f00660f38f59cb0f4ff0f0066440f38f5bcb0f4ff0f00660f38f58cf0f8ff0f00660f38f59cf0f8ff0f0066440f38f5bcf0f8ff0f00660f38f58cc4f8ff0f00660f38f59cc4f8ff0f0066440f38f5bcc4f8ff0f0066410f38f58cc7f8ff0f0066410f38f59cc7f8ff0f0066450f38f5bcc7f8ff0f0066420f38f58cfcf8ff0f0066420f38f59cfcf8ff0f0066460f38f5bcfcf8ff0f0066430f38f58cfef8ff0f0066430f38f59cfef8ff0f0066470f38f5bcfef8ff0f00

bits 64

wrussd dword [0x0], ecx
wrussd dword [0x0], ebx
wrussd dword [0x0], r15d
wrussd dword [0xFF], ecx
wrussd dword [0xFF], ebx
wrussd dword [0xFF], r15d
wrussd dword [rel $ + 0x0], ecx
wrussd dword [rel $ + 0x0], ebx
wrussd dword [rel $ + 0x0], r15d
wrussd dword [rel $ + 0xFF], ecx
wrussd dword [rel $ + 0xFF], ebx
wrussd dword [rel $ + 0xFF], r15d
wrussd dword [rel $ + 0xFFFF], ecx
wrussd dword [rel $ + 0xFFFF], ebx
wrussd dword [rel $ + 0xFFFF], r15d
wrussd dword [rax], ecx
wrussd dword [rax], ebx
wrussd dword [rax], r15d
wrussd dword [rax + 0x0], ecx
wrussd dword [rax + 0x0], ebx
wrussd dword [rax + 0x0], r15d
wrussd dword [rax + 0xFFFF], ecx
wrussd dword [rax + 0xFFFF], ebx
wrussd dword [rax + 0xFFFF], r15d
wrussd dword [r15 + 0xFFFF], ecx
wrussd dword [r15 + 0xFFFF], ebx
wrussd dword [r15 + 0xFFFF], r15d
wrussd dword [rax + rsi * 1  + 0x0], ecx
wrussd dword [rax + rsi * 1  + 0x0], ebx
wrussd dword [rax + rsi * 1  + 0x0], r15d
wrussd dword [rax + rsi + 0xFFFF], ecx
wrussd dword [rax + rsi + 0xFFFF], ebx
wrussd dword [rax + rsi + 0xFFFF], r15d
wrussd dword [r15 + rsi + 0xFFFF], ecx
wrussd dword [r15 + rsi + 0xFFFF], ebx
wrussd dword [r15 + rsi + 0xFFFF], r15d
wrussd dword [rax + r15 + 0xFFFF], ecx
wrussd dword [rax + r15 + 0xFFFF], ebx
wrussd dword [rax + r15 + 0xFFFF], r15d
wrussd dword [rax + rsi * 2 + 0xFFFF2], ecx
wrussd dword [rax + rsi * 2 + 0xFFFF2], ebx
wrussd dword [rax + rsi * 2 + 0xFFFF2], r15d
wrussd dword [rax + rsi * 4 + 0xFFFF4], ecx
wrussd dword [rax + rsi * 4 + 0xFFFF4], ebx
wrussd dword [rax + rsi * 4 + 0xFFFF4], r15d
wrussd dword [rax + rsi * 8 + 0xFFFF8], ecx
wrussd dword [rax + rsi * 8 + 0xFFFF8], ebx
wrussd dword [rax + rsi * 8 + 0xFFFF8], r15d
wrussd dword [rsp + rax * 8 + 0xFFFF8], ecx
wrussd dword [rsp + rax * 8 + 0xFFFF8], ebx
wrussd dword [rsp + rax * 8 + 0xFFFF8], r15d
wrussd dword [r15 + rax * 8 + 0xFFFF8], ecx
wrussd dword [r15 + rax * 8 + 0xFFFF8], ebx
wrussd dword [r15 + rax * 8 + 0xFFFF8], r15d
wrussd dword [rsp + r15 * 8 + 0xFFFF8], ecx
wrussd dword [rsp + r15 * 8 + 0xFFFF8], ebx
wrussd dword [rsp + r15 * 8 + 0xFFFF8], r15d
wrussd dword [r14 + r15 * 8 + 0xFFFF8], ecx
wrussd dword [r14 + r15 * 8 + 0xFFFF8], ebx
wrussd dword [r14 + r15 * 8 + 0xFFFF8], r15d
