; expect: 0f012425000000000f012425ff0000000f0125f9ffffff0f0125f80000000f0125f8ff00000f01200f01200f01a0ffff0000410f01a7ffff00000f0124300f01a430ffff0000410f01a437ffff0000420f01a438ffff00000f01a470f2ff0f000f01a4b0f4ff0f000f01a4f0f8ff0f000f01a4c4f8ff0f00410f01a4c7f8ff0f00420f01a4fcf8ff0f00430f01a4fef8ff0f00660f01e1660f01e2660f01e366410f01e70f01e10f01e3410f01e7480f01e1480f01e3490f01e7

bits 64

smsw word [0x0]
smsw word [0xFF]
smsw word [rel $ + 0x0]
smsw word [rel $ + 0xFF]
smsw word [rel $ + 0xFFFF]
smsw word [rax]
smsw word [rax + 0x0]
smsw word [rax + 0xFFFF]
smsw word [r15 + 0xFFFF]
smsw word [rax + rsi * 1  + 0x0]
smsw word [rax + rsi + 0xFFFF]
smsw word [r15 + rsi + 0xFFFF]
smsw word [rax + r15 + 0xFFFF]
smsw word [rax + rsi * 2 + 0xFFFF2]
smsw word [rax + rsi * 4 + 0xFFFF4]
smsw word [rax + rsi * 8 + 0xFFFF8]
smsw word [rsp + rax * 8 + 0xFFFF8]
smsw word [r15 + rax * 8 + 0xFFFF8]
smsw word [rsp + r15 * 8 + 0xFFFF8]
smsw word [r14 + r15 * 8 + 0xFFFF8]
smsw cx
smsw dx
smsw bx
smsw r15w
smsw ecx
smsw ebx
smsw r15d
smsw rcx
smsw rbx
smsw r15
