; expect: e8fbffffffe8f7ffffffe871ffffffe86b000000ffd1ffd341ffd7ff142500000000ff1425ff000000ff15faffffffff15f9000000ff15f9ff0000ff10ff10ff90ffff000041ff97ffff0000ff1430ff9430ffff000041ff9437ffff000042ff9438ffff0000ff9470f2ff0f00ff94b0f4ff0f00ff94f0f8ff0f00ff94c4f8ff0f0041ff94c7f8ff0f0042ff94fcf8ff0f0043ff94fef8ff0f00

call 0
call 1
call -128
call 127
call rcx
call rbx
call r15
call qword [0x0]
call qword [0xFF]
call qword [rel $ + 0x0]
call qword [rel $ + 0xFF]
call qword [rel $ + 0xFFFF]
call qword [rax]
call qword [rax + 0x0]
call qword [rax + 0xFFFF]
call qword [r15 + 0xFFFF]
call qword [rax + rsi * 1  + 0x0]
call qword [rax + rsi + 0xFFFF]
call qword [r15 + rsi + 0xFFFF]
call qword [rax + r15 + 0xFFFF]
call qword [rax + rsi * 2 + 0xFFFF2]
call qword [rax + rsi * 4 + 0xFFFF4]
call qword [rax + rsi * 8 + 0xFFFF8]
call qword [rsp + rax * 8 + 0xFFFF8]
call qword [r15 + rax * 8 + 0xFFFF8]
call qword [rsp + r15 * 8 + 0xFFFF8]
call qword [r14 + r15 * 8 + 0xFFFF8]