; expect: 0f9fc10f9fc20f9fc30f9f0425000000000f9f0425ff0000000f9f05f9ffffff0f9f05f80000000f9f05f8ff00000f9f000f9f000f9f80ffff0000410f9f87ffff00000f9f04300f9f8430ffff0000410f9f8437ffff0000420f9f8438ffff00000f9f8470f2ff0f000f9f84b0f4ff0f000f9f84f0f8ff0f000f9f84c4f8ff0f00410f9f84c7f8ff0f00420f9f84fcf8ff0f00430f9f84fef8ff0f00

bits 64

setnle cl
setnle dl
setnle bl
setnle byte [0x0]
setnle byte [0xFF]
setnle byte [rel $ + 0x0]
setnle byte [rel $ + 0xFF]
setnle byte [rel $ + 0xFFFF]
setnle byte [rax]
setnle byte [rax + 0x0]
setnle byte [rax + 0xFFFF]
setnle byte [r15 + 0xFFFF]
setnle byte [rax + rsi * 1  + 0x0]
setnle byte [rax + rsi + 0xFFFF]
setnle byte [r15 + rsi + 0xFFFF]
setnle byte [rax + r15 + 0xFFFF]
setnle byte [rax + rsi * 2 + 0xFFFF2]
setnle byte [rax + rsi * 4 + 0xFFFF4]
setnle byte [rax + rsi * 8 + 0xFFFF8]
setnle byte [rsp + rax * 8 + 0xFFFF8]
setnle byte [r15 + rax * 8 + 0xFFFF8]
setnle byte [rsp + r15 * 8 + 0xFFFF8]
setnle byte [r14 + r15 * 8 + 0xFFFF8]
