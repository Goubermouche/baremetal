; expect: f30f012c2500000000f30f012c25ff000000f30f012df8fffffff30f012df7000000f30f012df7ff0000f30f0128f30f0128f30f01a8ffff0000f3410f01afffff0000f30f012c30f30f01ac30ffff0000f3410f01ac37ffff0000f3420f01ac38ffff0000f30f01ac70f2ff0f00f30f01acb0f4ff0f00f30f01acf0f8ff0f00f30f01acc4f8ff0f00f3410f01acc7f8ff0f00f3420f01acfcf8ff0f00f3430f01acfef8ff0f00

bits 64

rstorssp qword [0x0]
rstorssp qword [0xFF]
rstorssp qword [rel $ + 0x0]
rstorssp qword [rel $ + 0xFF]
rstorssp qword [rel $ + 0xFFFF]
rstorssp qword [rax]
rstorssp qword [rax + 0x0]
rstorssp qword [rax + 0xFFFF]
rstorssp qword [r15 + 0xFFFF]
rstorssp qword [rax + rsi * 1  + 0x0]
rstorssp qword [rax + rsi + 0xFFFF]
rstorssp qword [r15 + rsi + 0xFFFF]
rstorssp qword [rax + r15 + 0xFFFF]
rstorssp qword [rax + rsi * 2 + 0xFFFF2]
rstorssp qword [rax + rsi * 4 + 0xFFFF4]
rstorssp qword [rax + rsi * 8 + 0xFFFF8]
rstorssp qword [rsp + rax * 8 + 0xFFFF8]
rstorssp qword [r15 + rax * 8 + 0xFFFF8]
rstorssp qword [rsp + r15 * 8 + 0xFFFF8]
rstorssp qword [r14 + r15 * 8 + 0xFFFF8]
