; expect: d9242500000000d92425ff000000d925faffffffd925f9000000d925f9ff0000d920d920d9a0ffff000041d9a7ffff0000d92430d9a430ffff000041d9a437ffff000042d9a438ffff0000d9a470f2ff0f00d9a4b0f4ff0f00d9a4f0f8ff0f00d9a4c4f8ff0f0041d9a4c7f8ff0f0042d9a4fcf8ff0f0043d9a4fef8ff0f00

bits 64

fldenv [0x0]
fldenv [0xFF]
fldenv [rel $ + 0x0]
fldenv [rel $ + 0xFF]
fldenv [rel $ + 0xFFFF]
fldenv [rax]
fldenv [rax + 0x0]
fldenv [rax + 0xFFFF]
fldenv [r15 + 0xFFFF]
fldenv [rax + rsi * 1  + 0x0]
fldenv [rax + rsi + 0xFFFF]
fldenv [r15 + rsi + 0xFFFF]
fldenv [rax + r15 + 0xFFFF]
fldenv [rax + rsi * 2 + 0xFFFF2]
fldenv [rax + rsi * 4 + 0xFFFF4]
fldenv [rax + rsi * 8 + 0xFFFF8]
fldenv [rsp + rax * 8 + 0xFFFF8]
fldenv [r15 + rax * 8 + 0xFFFF8]
fldenv [rsp + r15 * 8 + 0xFFFF8]
fldenv [r14 + r15 * 8 + 0xFFFF8]
