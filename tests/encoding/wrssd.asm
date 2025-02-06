; expect: 0f38f60c25000000000f38f61c2500000000440f38f63c25000000000f38f60c25ff0000000f38f61c25ff000000440f38f63c25ff0000000f38f60df8ffffff0f38f61df8ffffff440f38f63df7ffffff0f38f60df70000000f38f61df7000000440f38f63df60000000f38f60df7ff00000f38f61df7ff0000440f38f63df6ff00000f38f6080f38f618440f38f6380f38f6080f38f618440f38f6380f38f688ffff00000f38f698ffff0000440f38f6b8ffff0000410f38f68fffff0000410f38f69fffff0000450f38f6bfffff00000f38f60c300f38f61c30440f38f63c300f38f68c30ffff00000f38f69c30ffff0000440f38f6bc30ffff0000410f38f68c37ffff0000410f38f69c37ffff0000450f38f6bc37ffff0000420f38f68c38ffff0000420f38f69c38ffff0000460f38f6bc38ffff00000f38f68c70f2ff0f000f38f69c70f2ff0f00440f38f6bc70f2ff0f000f38f68cb0f4ff0f000f38f69cb0f4ff0f00440f38f6bcb0f4ff0f000f38f68cf0f8ff0f000f38f69cf0f8ff0f00440f38f6bcf0f8ff0f000f38f68cc4f8ff0f000f38f69cc4f8ff0f00440f38f6bcc4f8ff0f00410f38f68cc7f8ff0f00410f38f69cc7f8ff0f00450f38f6bcc7f8ff0f00420f38f68cfcf8ff0f00420f38f69cfcf8ff0f00460f38f6bcfcf8ff0f00430f38f68cfef8ff0f00430f38f69cfef8ff0f00470f38f6bcfef8ff0f00

bits 64

wrssd dword [0x0], ecx
wrssd dword [0x0], ebx
wrssd dword [0x0], r15d
wrssd dword [0xFF], ecx
wrssd dword [0xFF], ebx
wrssd dword [0xFF], r15d
wrssd dword [rel $ + 0x0], ecx
wrssd dword [rel $ + 0x0], ebx
wrssd dword [rel $ + 0x0], r15d
wrssd dword [rel $ + 0xFF], ecx
wrssd dword [rel $ + 0xFF], ebx
wrssd dword [rel $ + 0xFF], r15d
wrssd dword [rel $ + 0xFFFF], ecx
wrssd dword [rel $ + 0xFFFF], ebx
wrssd dword [rel $ + 0xFFFF], r15d
wrssd dword [rax], ecx
wrssd dword [rax], ebx
wrssd dword [rax], r15d
wrssd dword [rax + 0x0], ecx
wrssd dword [rax + 0x0], ebx
wrssd dword [rax + 0x0], r15d
wrssd dword [rax + 0xFFFF], ecx
wrssd dword [rax + 0xFFFF], ebx
wrssd dword [rax + 0xFFFF], r15d
wrssd dword [r15 + 0xFFFF], ecx
wrssd dword [r15 + 0xFFFF], ebx
wrssd dword [r15 + 0xFFFF], r15d
wrssd dword [rax + rsi * 1  + 0x0], ecx
wrssd dword [rax + rsi * 1  + 0x0], ebx
wrssd dword [rax + rsi * 1  + 0x0], r15d
wrssd dword [rax + rsi + 0xFFFF], ecx
wrssd dword [rax + rsi + 0xFFFF], ebx
wrssd dword [rax + rsi + 0xFFFF], r15d
wrssd dword [r15 + rsi + 0xFFFF], ecx
wrssd dword [r15 + rsi + 0xFFFF], ebx
wrssd dword [r15 + rsi + 0xFFFF], r15d
wrssd dword [rax + r15 + 0xFFFF], ecx
wrssd dword [rax + r15 + 0xFFFF], ebx
wrssd dword [rax + r15 + 0xFFFF], r15d
wrssd dword [rax + rsi * 2 + 0xFFFF2], ecx
wrssd dword [rax + rsi * 2 + 0xFFFF2], ebx
wrssd dword [rax + rsi * 2 + 0xFFFF2], r15d
wrssd dword [rax + rsi * 4 + 0xFFFF4], ecx
wrssd dword [rax + rsi * 4 + 0xFFFF4], ebx
wrssd dword [rax + rsi * 4 + 0xFFFF4], r15d
wrssd dword [rax + rsi * 8 + 0xFFFF8], ecx
wrssd dword [rax + rsi * 8 + 0xFFFF8], ebx
wrssd dword [rax + rsi * 8 + 0xFFFF8], r15d
wrssd dword [rsp + rax * 8 + 0xFFFF8], ecx
wrssd dword [rsp + rax * 8 + 0xFFFF8], ebx
wrssd dword [rsp + rax * 8 + 0xFFFF8], r15d
wrssd dword [r15 + rax * 8 + 0xFFFF8], ecx
wrssd dword [r15 + rax * 8 + 0xFFFF8], ebx
wrssd dword [r15 + rax * 8 + 0xFFFF8], r15d
wrssd dword [rsp + r15 * 8 + 0xFFFF8], ecx
wrssd dword [rsp + r15 * 8 + 0xFFFF8], ebx
wrssd dword [rsp + r15 * 8 + 0xFFFF8], r15d
wrssd dword [r14 + r15 * 8 + 0xFFFF8], ecx
wrssd dword [r14 + r15 * 8 + 0xFFFF8], ebx
wrssd dword [r14 + r15 * 8 + 0xFFFF8], r15d
