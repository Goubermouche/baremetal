; expect: 668f042500000000668f0425ff000000668f05f9ffffff668f05f8000000668f05f8ff0000668f00668f00668f80ffff000066418f87ffff0000668f0430668f8430ffff000066418f8437ffff000066428f8438ffff0000668f8470f2ff0f00668f84b0f4ff0f00668f84f0f8ff0f00668f84c4f8ff0f0066418f84c7f8ff0f0066428f84fcf8ff0f0066438f84fef8ff0f008f0425000000008f0425ff0000008f05faffffff8f05f90000008f05f9ff00008f008f008f80ffff0000418f87ffff00008f04308f8430ffff0000418f8437ffff0000428f8438ffff00008f8470f2ff0f008f84b0f4ff0f008f84f0f8ff0f008f84c4f8ff0f00418f84c7f8ff0f00428f84fcf8ff0f00438f84fef8ff0f006659665a665b66415f595b415f0fa10fa9

bits 64

pop word [0x0]
pop word [0xFF]
pop word [rel $ + 0x0]
pop word [rel $ + 0xFF]
pop word [rel $ + 0xFFFF]
pop word [rax]
pop word [rax + 0x0]
pop word [rax + 0xFFFF]
pop word [r15 + 0xFFFF]
pop word [rax + rsi * 1  + 0x0]
pop word [rax + rsi + 0xFFFF]
pop word [r15 + rsi + 0xFFFF]
pop word [rax + r15 + 0xFFFF]
pop word [rax + rsi * 2 + 0xFFFF2]
pop word [rax + rsi * 4 + 0xFFFF4]
pop word [rax + rsi * 8 + 0xFFFF8]
pop word [rsp + rax * 8 + 0xFFFF8]
pop word [r15 + rax * 8 + 0xFFFF8]
pop word [rsp + r15 * 8 + 0xFFFF8]
pop word [r14 + r15 * 8 + 0xFFFF8]
pop qword [0x0]
pop qword [0xFF]
pop qword [rel $ + 0x0]
pop qword [rel $ + 0xFF]
pop qword [rel $ + 0xFFFF]
pop qword [rax]
pop qword [rax + 0x0]
pop qword [rax + 0xFFFF]
pop qword [r15 + 0xFFFF]
pop qword [rax + rsi * 1  + 0x0]
pop qword [rax + rsi + 0xFFFF]
pop qword [r15 + rsi + 0xFFFF]
pop qword [rax + r15 + 0xFFFF]
pop qword [rax + rsi * 2 + 0xFFFF2]
pop qword [rax + rsi * 4 + 0xFFFF4]
pop qword [rax + rsi * 8 + 0xFFFF8]
pop qword [rsp + rax * 8 + 0xFFFF8]
pop qword [r15 + rax * 8 + 0xFFFF8]
pop qword [rsp + r15 * 8 + 0xFFFF8]
pop qword [r14 + r15 * 8 + 0xFFFF8]
pop cx
pop dx
pop bx
pop r15w
pop rcx
pop rbx
pop r15
pop fs
pop gs
