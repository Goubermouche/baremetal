; expect: f30faee1f30faee3f3410faee7f30fae242500000000f30fae2425ff000000f30fae25f8fffffff30fae25f7000000f30fae25f7ff0000f30fae20f30fae20f30faea0ffff0000f3410faea7ffff0000f30fae2430f30faea430ffff0000f3410faea437ffff0000f3420faea438ffff0000f30faea470f2ff0f00f30faea4b0f4ff0f00f30faea4f0f8ff0f00f30faea4c4f8ff0f00f3410faea4c7f8ff0f00f3420faea4fcf8ff0f00f3430faea4fef8ff0f00f3480faee1f3480faee3f3490faee7f3480fae242500000000f3480fae2425ff000000f3480fae25f7fffffff3480fae25f6000000f3480fae25f6ff0000f3480fae20f3480fae20f3480faea0ffff0000f3490faea7ffff0000f3480fae2430f3480faea430ffff0000f3490faea437ffff0000f34a0faea438ffff0000f3480faea470f2ff0f00f3480faea4b0f4ff0f00f3480faea4f0f8ff0f00f3480faea4c4f8ff0f00f3490faea4c7f8ff0f00f34a0faea4fcf8ff0f00f34b0faea4fef8ff0f00

bits 64

ptwrite ecx
ptwrite ebx
ptwrite r15d
ptwrite dword [0x0]
ptwrite dword [0xFF]
ptwrite dword [rel $ + 0x0]
ptwrite dword [rel $ + 0xFF]
ptwrite dword [rel $ + 0xFFFF]
ptwrite dword [rax]
ptwrite dword [rax + 0x0]
ptwrite dword [rax + 0xFFFF]
ptwrite dword [r15 + 0xFFFF]
ptwrite dword [rax + rsi * 1  + 0x0]
ptwrite dword [rax + rsi + 0xFFFF]
ptwrite dword [r15 + rsi + 0xFFFF]
ptwrite dword [rax + r15 + 0xFFFF]
ptwrite dword [rax + rsi * 2 + 0xFFFF2]
ptwrite dword [rax + rsi * 4 + 0xFFFF4]
ptwrite dword [rax + rsi * 8 + 0xFFFF8]
ptwrite dword [rsp + rax * 8 + 0xFFFF8]
ptwrite dword [r15 + rax * 8 + 0xFFFF8]
ptwrite dword [rsp + r15 * 8 + 0xFFFF8]
ptwrite dword [r14 + r15 * 8 + 0xFFFF8]
ptwrite rcx
ptwrite rbx
ptwrite r15
ptwrite qword [0x0]
ptwrite qword [0xFF]
ptwrite qword [rel $ + 0x0]
ptwrite qword [rel $ + 0xFF]
ptwrite qword [rel $ + 0xFFFF]
ptwrite qword [rax]
ptwrite qword [rax + 0x0]
ptwrite qword [rax + 0xFFFF]
ptwrite qword [r15 + 0xFFFF]
ptwrite qword [rax + rsi * 1  + 0x0]
ptwrite qword [rax + rsi + 0xFFFF]
ptwrite qword [r15 + rsi + 0xFFFF]
ptwrite qword [rax + r15 + 0xFFFF]
ptwrite qword [rax + rsi * 2 + 0xFFFF2]
ptwrite qword [rax + rsi * 4 + 0xFFFF4]
ptwrite qword [rax + rsi * 8 + 0xFFFF8]
ptwrite qword [rsp + rax * 8 + 0xFFFF8]
ptwrite qword [r15 + rax * 8 + 0xFFFF8]
ptwrite qword [rsp + r15 * 8 + 0xFFFF8]
ptwrite qword [r14 + r15 * 8 + 0xFFFF8]
