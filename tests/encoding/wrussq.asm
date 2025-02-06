; expect: 66480f38f50c250000000066480f38f51c2500000000664c0f38f53c250000000066480f38f50c25ff00000066480f38f51c25ff000000664c0f38f53c25ff00000066480f38f50df6ffffff66480f38f51df6ffffff664c0f38f53df6ffffff66480f38f50df500000066480f38f51df5000000664c0f38f53df500000066480f38f50df5ff000066480f38f51df5ff0000664c0f38f53df5ff000066480f38f50866480f38f518664c0f38f53866480f38f50866480f38f518664c0f38f53866480f38f588ffff000066480f38f598ffff0000664c0f38f5b8ffff000066490f38f58fffff000066490f38f59fffff0000664d0f38f5bfffff000066480f38f50c3066480f38f51c30664c0f38f53c3066480f38f58c30ffff000066480f38f59c30ffff0000664c0f38f5bc30ffff000066490f38f58c37ffff000066490f38f59c37ffff0000664d0f38f5bc37ffff0000664a0f38f58c38ffff0000664a0f38f59c38ffff0000664e0f38f5bc38ffff000066480f38f58c70f2ff0f0066480f38f59c70f2ff0f00664c0f38f5bc70f2ff0f0066480f38f58cb0f4ff0f0066480f38f59cb0f4ff0f00664c0f38f5bcb0f4ff0f0066480f38f58cf0f8ff0f0066480f38f59cf0f8ff0f00664c0f38f5bcf0f8ff0f0066480f38f58cc4f8ff0f0066480f38f59cc4f8ff0f00664c0f38f5bcc4f8ff0f0066490f38f58cc7f8ff0f0066490f38f59cc7f8ff0f00664d0f38f5bcc7f8ff0f00664a0f38f58cfcf8ff0f00664a0f38f59cfcf8ff0f00664e0f38f5bcfcf8ff0f00664b0f38f58cfef8ff0f00664b0f38f59cfef8ff0f00664f0f38f5bcfef8ff0f00

bits 64

wrussq qword [0x0], rcx
wrussq qword [0x0], rbx
wrussq qword [0x0], r15
wrussq qword [0xFF], rcx
wrussq qword [0xFF], rbx
wrussq qword [0xFF], r15
wrussq qword [rel $ + 0x0], rcx
wrussq qword [rel $ + 0x0], rbx
wrussq qword [rel $ + 0x0], r15
wrussq qword [rel $ + 0xFF], rcx
wrussq qword [rel $ + 0xFF], rbx
wrussq qword [rel $ + 0xFF], r15
wrussq qword [rel $ + 0xFFFF], rcx
wrussq qword [rel $ + 0xFFFF], rbx
wrussq qword [rel $ + 0xFFFF], r15
wrussq qword [rax], rcx
wrussq qword [rax], rbx
wrussq qword [rax], r15
wrussq qword [rax + 0x0], rcx
wrussq qword [rax + 0x0], rbx
wrussq qword [rax + 0x0], r15
wrussq qword [rax + 0xFFFF], rcx
wrussq qword [rax + 0xFFFF], rbx
wrussq qword [rax + 0xFFFF], r15
wrussq qword [r15 + 0xFFFF], rcx
wrussq qword [r15 + 0xFFFF], rbx
wrussq qword [r15 + 0xFFFF], r15
wrussq qword [rax + rsi * 1  + 0x0], rcx
wrussq qword [rax + rsi * 1  + 0x0], rbx
wrussq qword [rax + rsi * 1  + 0x0], r15
wrussq qword [rax + rsi + 0xFFFF], rcx
wrussq qword [rax + rsi + 0xFFFF], rbx
wrussq qword [rax + rsi + 0xFFFF], r15
wrussq qword [r15 + rsi + 0xFFFF], rcx
wrussq qword [r15 + rsi + 0xFFFF], rbx
wrussq qword [r15 + rsi + 0xFFFF], r15
wrussq qword [rax + r15 + 0xFFFF], rcx
wrussq qword [rax + r15 + 0xFFFF], rbx
wrussq qword [rax + r15 + 0xFFFF], r15
wrussq qword [rax + rsi * 2 + 0xFFFF2], rcx
wrussq qword [rax + rsi * 2 + 0xFFFF2], rbx
wrussq qword [rax + rsi * 2 + 0xFFFF2], r15
wrussq qword [rax + rsi * 4 + 0xFFFF4], rcx
wrussq qword [rax + rsi * 4 + 0xFFFF4], rbx
wrussq qword [rax + rsi * 4 + 0xFFFF4], r15
wrussq qword [rax + rsi * 8 + 0xFFFF8], rcx
wrussq qword [rax + rsi * 8 + 0xFFFF8], rbx
wrussq qword [rax + rsi * 8 + 0xFFFF8], r15
wrussq qword [rsp + rax * 8 + 0xFFFF8], rcx
wrussq qword [rsp + rax * 8 + 0xFFFF8], rbx
wrussq qword [rsp + rax * 8 + 0xFFFF8], r15
wrussq qword [r15 + rax * 8 + 0xFFFF8], rcx
wrussq qword [r15 + rax * 8 + 0xFFFF8], rbx
wrussq qword [r15 + rax * 8 + 0xFFFF8], r15
wrussq qword [rsp + r15 * 8 + 0xFFFF8], rcx
wrussq qword [rsp + r15 * 8 + 0xFFFF8], rbx
wrussq qword [rsp + r15 * 8 + 0xFFFF8], r15
wrussq qword [r14 + r15 * 8 + 0xFFFF8], rcx
wrussq qword [r14 + r15 * 8 + 0xFFFF8], rbx
wrussq qword [r14 + r15 * 8 + 0xFFFF8], r15
