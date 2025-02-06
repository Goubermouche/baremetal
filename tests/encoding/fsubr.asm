; expect: d82c2500000000d82c25ff000000d82dfaffffffd82df9000000d82df9ff0000d828d828d8a8ffff000041d8afffff0000d82c30d8ac30ffff000041d8ac37ffff000042d8ac38ffff0000d8ac70f2ff0f00d8acb0f4ff0f00d8acf0f8ff0f00d8acc4f8ff0f0041d8acc7f8ff0f0042d8acfcf8ff0f0043d8acfef8ff0f00dc2c2500000000dc2c25ff000000dc2dfaffffffdc2df9000000dc2df9ff0000dc28dc28dca8ffff000041dcafffff0000dc2c30dcac30ffff000041dcac37ffff000042dcac38ffff0000dcac70f2ff0f00dcacb0f4ff0f00dcacf0f8ff0f00dcacc4f8ff0f0041dcacc7f8ff0f0042dcacfcf8ff0f0043dcacfef8ff0f00dce0d8e9d8efdce1dce7

bits 64

fsubr dword [0x0]
fsubr dword [0xFF]
fsubr dword [rel $ + 0x0]
fsubr dword [rel $ + 0xFF]
fsubr dword [rel $ + 0xFFFF]
fsubr dword [rax]
fsubr dword [rax + 0x0]
fsubr dword [rax + 0xFFFF]
fsubr dword [r15 + 0xFFFF]
fsubr dword [rax + rsi * 1  + 0x0]
fsubr dword [rax + rsi + 0xFFFF]
fsubr dword [r15 + rsi + 0xFFFF]
fsubr dword [rax + r15 + 0xFFFF]
fsubr dword [rax + rsi * 2 + 0xFFFF2]
fsubr dword [rax + rsi * 4 + 0xFFFF4]
fsubr dword [rax + rsi * 8 + 0xFFFF8]
fsubr dword [rsp + rax * 8 + 0xFFFF8]
fsubr dword [r15 + rax * 8 + 0xFFFF8]
fsubr dword [rsp + r15 * 8 + 0xFFFF8]
fsubr dword [r14 + r15 * 8 + 0xFFFF8]
fsubr qword [0x0]
fsubr qword [0xFF]
fsubr qword [rel $ + 0x0]
fsubr qword [rel $ + 0xFF]
fsubr qword [rel $ + 0xFFFF]
fsubr qword [rax]
fsubr qword [rax + 0x0]
fsubr qword [rax + 0xFFFF]
fsubr qword [r15 + 0xFFFF]
fsubr qword [rax + rsi * 1  + 0x0]
fsubr qword [rax + rsi + 0xFFFF]
fsubr qword [r15 + rsi + 0xFFFF]
fsubr qword [rax + r15 + 0xFFFF]
fsubr qword [rax + rsi * 2 + 0xFFFF2]
fsubr qword [rax + rsi * 4 + 0xFFFF4]
fsubr qword [rax + rsi * 8 + 0xFFFF8]
fsubr qword [rsp + rax * 8 + 0xFFFF8]
fsubr qword [r15 + rax * 8 + 0xFFFF8]
fsubr qword [rsp + r15 * 8 + 0xFFFF8]
fsubr qword [r14 + r15 * 8 + 0xFFFF8]
fsubr st0, st0
fsubr st0, st1
fsubr st0, st7
fsubr st1, st0
fsubr st7, st0
