; expect: d80c2500000000d80c25ff000000d80dfaffffffd80df9000000d80df9ff0000d808d808d888ffff000041d88fffff0000d80c30d88c30ffff000041d88c37ffff000042d88c38ffff0000d88c70f2ff0f00d88cb0f4ff0f00d88cf0f8ff0f00d88cc4f8ff0f0041d88cc7f8ff0f0042d88cfcf8ff0f0043d88cfef8ff0f00dc0c2500000000dc0c25ff000000dc0dfaffffffdc0df9000000dc0df9ff0000dc08dc08dc88ffff000041dc8fffff0000dc0c30dc8c30ffff000041dc8c37ffff000042dc8c38ffff0000dc8c70f2ff0f00dc8cb0f4ff0f00dc8cf0f8ff0f00dc8cc4f8ff0f0041dc8cc7f8ff0f0042dc8cfcf8ff0f0043dc8cfef8ff0f00dcc8d8c9d8cfdcc9dccf

bits 64

fmul dword [0x0]
fmul dword [0xFF]
fmul dword [rel $ + 0x0]
fmul dword [rel $ + 0xFF]
fmul dword [rel $ + 0xFFFF]
fmul dword [rax]
fmul dword [rax + 0x0]
fmul dword [rax + 0xFFFF]
fmul dword [r15 + 0xFFFF]
fmul dword [rax + rsi * 1  + 0x0]
fmul dword [rax + rsi + 0xFFFF]
fmul dword [r15 + rsi + 0xFFFF]
fmul dword [rax + r15 + 0xFFFF]
fmul dword [rax + rsi * 2 + 0xFFFF2]
fmul dword [rax + rsi * 4 + 0xFFFF4]
fmul dword [rax + rsi * 8 + 0xFFFF8]
fmul dword [rsp + rax * 8 + 0xFFFF8]
fmul dword [r15 + rax * 8 + 0xFFFF8]
fmul dword [rsp + r15 * 8 + 0xFFFF8]
fmul dword [r14 + r15 * 8 + 0xFFFF8]
fmul qword [0x0]
fmul qword [0xFF]
fmul qword [rel $ + 0x0]
fmul qword [rel $ + 0xFF]
fmul qword [rel $ + 0xFFFF]
fmul qword [rax]
fmul qword [rax + 0x0]
fmul qword [rax + 0xFFFF]
fmul qword [r15 + 0xFFFF]
fmul qword [rax + rsi * 1  + 0x0]
fmul qword [rax + rsi + 0xFFFF]
fmul qword [r15 + rsi + 0xFFFF]
fmul qword [rax + r15 + 0xFFFF]
fmul qword [rax + rsi * 2 + 0xFFFF2]
fmul qword [rax + rsi * 4 + 0xFFFF4]
fmul qword [rax + rsi * 8 + 0xFFFF8]
fmul qword [rsp + rax * 8 + 0xFFFF8]
fmul qword [r15 + rax * 8 + 0xFFFF8]
fmul qword [rsp + r15 * 8 + 0xFFFF8]
fmul qword [r14 + r15 * 8 + 0xFFFF8]
fmul st0, st0
fmul st0, st1
fmul st0, st7
fmul st1, st0
fmul st7, st0
