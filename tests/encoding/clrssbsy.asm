; expect: f30fae342500000000f30fae3425ff000000f30fae35f8fffffff30fae35f7000000f30fae35f7ff0000f30fae30f30fae30f30faeb0ffff0000f3410faeb7ffff0000f30fae3430f30faeb430ffff0000f3410faeb437ffff0000f3420faeb438ffff0000f30faeb470f2ff0f00f30faeb4b0f4ff0f00f30faeb4f0f8ff0f00f30faeb4c4f8ff0f00f3410faeb4c7f8ff0f00f3420faeb4fcf8ff0f00f3430faeb4fef8ff0f00

bits 64

clrssbsy qword [0x0]
clrssbsy qword [0xFF]
clrssbsy qword [rel $ + 0x0]
clrssbsy qword [rel $ + 0xFF]
clrssbsy qword [rel $ + 0xFFFF]
clrssbsy qword [rax]
clrssbsy qword [rax + 0x0]
clrssbsy qword [rax + 0xFFFF]
clrssbsy qword [r15 + 0xFFFF]
clrssbsy qword [rax + rsi * 1  + 0x0]
clrssbsy qword [rax + rsi + 0xFFFF]
clrssbsy qword [r15 + rsi + 0xFFFF]
clrssbsy qword [rax + r15 + 0xFFFF]
clrssbsy qword [rax + rsi * 2 + 0xFFFF2]
clrssbsy qword [rax + rsi * 4 + 0xFFFF4]
clrssbsy qword [rax + rsi * 8 + 0xFFFF8]
clrssbsy qword [rsp + rax * 8 + 0xFFFF8]
clrssbsy qword [r15 + rax * 8 + 0xFFFF8]
clrssbsy qword [rsp + r15 * 8 + 0xFFFF8]
clrssbsy qword [r14 + r15 * 8 + 0xFFFF8]
