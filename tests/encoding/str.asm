; expect: 0f000c25000000000f000c25ff0000000f000df9ffffff0f000df80000000f000df8ff00000f00080f00080f0088ffff0000410f008fffff00000f000c300f008c30ffff0000410f008c37ffff0000420f008c38ffff00000f008c70f2ff0f000f008cb0f4ff0f000f008cf0f8ff0f000f008cc4f8ff0f00410f008cc7f8ff0f00420f008cfcf8ff0f00430f008cfef8ff0f00660f00c9660f00ca660f00cb66410f00cf0f00c90f00cb410f00cf480f00c9480f00cb490f00cf

bits 64

str word [0x0]
str word [0xFF]
str word [rel $ + 0x0]
str word [rel $ + 0xFF]
str word [rel $ + 0xFFFF]
str word [rax]
str word [rax + 0x0]
str word [rax + 0xFFFF]
str word [r15 + 0xFFFF]
str word [rax + rsi * 1  + 0x0]
str word [rax + rsi + 0xFFFF]
str word [r15 + rsi + 0xFFFF]
str word [rax + r15 + 0xFFFF]
str word [rax + rsi * 2 + 0xFFFF2]
str word [rax + rsi * 4 + 0xFFFF4]
str word [rax + rsi * 8 + 0xFFFF8]
str word [rsp + rax * 8 + 0xFFFF8]
str word [r15 + rax * 8 + 0xFFFF8]
str word [rsp + r15 * 8 + 0xFFFF8]
str word [r14 + r15 * 8 + 0xFFFF8]
str cx
str dx
str bx
str r15w
str ecx
str ebx
str r15d
str rcx
str rbx
str r15
