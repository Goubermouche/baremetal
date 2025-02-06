; expect: d83c2500000000d83c25ff000000d83dfaffffffd83df9000000d83df9ff0000d838d838d8b8ffff000041d8bfffff0000d83c30d8bc30ffff000041d8bc37ffff000042d8bc38ffff0000d8bc70f2ff0f00d8bcb0f4ff0f00d8bcf0f8ff0f00d8bcc4f8ff0f0041d8bcc7f8ff0f0042d8bcfcf8ff0f0043d8bcfef8ff0f00dc3c2500000000dc3c25ff000000dc3dfaffffffdc3df9000000dc3df9ff0000dc38dc38dcb8ffff000041dcbfffff0000dc3c30dcbc30ffff000041dcbc37ffff000042dcbc38ffff0000dcbc70f2ff0f00dcbcb0f4ff0f00dcbcf0f8ff0f00dcbcc4f8ff0f0041dcbcc7f8ff0f0042dcbcfcf8ff0f0043dcbcfef8ff0f00dcf0d8f9d8ffdcf1dcf7

bits 64

fdivr dword [0x0]
fdivr dword [0xFF]
fdivr dword [rel $ + 0x0]
fdivr dword [rel $ + 0xFF]
fdivr dword [rel $ + 0xFFFF]
fdivr dword [rax]
fdivr dword [rax + 0x0]
fdivr dword [rax + 0xFFFF]
fdivr dword [r15 + 0xFFFF]
fdivr dword [rax + rsi * 1  + 0x0]
fdivr dword [rax + rsi + 0xFFFF]
fdivr dword [r15 + rsi + 0xFFFF]
fdivr dword [rax + r15 + 0xFFFF]
fdivr dword [rax + rsi * 2 + 0xFFFF2]
fdivr dword [rax + rsi * 4 + 0xFFFF4]
fdivr dword [rax + rsi * 8 + 0xFFFF8]
fdivr dword [rsp + rax * 8 + 0xFFFF8]
fdivr dword [r15 + rax * 8 + 0xFFFF8]
fdivr dword [rsp + r15 * 8 + 0xFFFF8]
fdivr dword [r14 + r15 * 8 + 0xFFFF8]
fdivr qword [0x0]
fdivr qword [0xFF]
fdivr qword [rel $ + 0x0]
fdivr qword [rel $ + 0xFF]
fdivr qword [rel $ + 0xFFFF]
fdivr qword [rax]
fdivr qword [rax + 0x0]
fdivr qword [rax + 0xFFFF]
fdivr qword [r15 + 0xFFFF]
fdivr qword [rax + rsi * 1  + 0x0]
fdivr qword [rax + rsi + 0xFFFF]
fdivr qword [r15 + rsi + 0xFFFF]
fdivr qword [rax + r15 + 0xFFFF]
fdivr qword [rax + rsi * 2 + 0xFFFF2]
fdivr qword [rax + rsi * 4 + 0xFFFF4]
fdivr qword [rax + rsi * 8 + 0xFFFF8]
fdivr qword [rsp + rax * 8 + 0xFFFF8]
fdivr qword [r15 + rax * 8 + 0xFFFF8]
fdivr qword [rsp + r15 * 8 + 0xFFFF8]
fdivr qword [r14 + r15 * 8 + 0xFFFF8]
fdivr st0, st0
fdivr st0, st1
fdivr st0, st7
fdivr st1, st0
fdivr st7, st0
