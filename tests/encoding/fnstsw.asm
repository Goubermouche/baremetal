; expect: dfe0dd3c2500000000dd3c25ff000000dd3dfaffffffdd3df9000000dd3df9ff0000dd38dd38ddb8ffff000041ddbfffff0000dd3c30ddbc30ffff000041ddbc37ffff000042ddbc38ffff0000ddbc70f2ff0f00ddbcb0f4ff0f00ddbcf0f8ff0f00ddbcc4f8ff0f0041ddbcc7f8ff0f0042ddbcfcf8ff0f0043ddbcfef8ff0f00

bits 64

fnstsw ax
fnstsw word [0x0]
fnstsw word [0xFF]
fnstsw word [rel $ + 0x0]
fnstsw word [rel $ + 0xFF]
fnstsw word [rel $ + 0xFFFF]
fnstsw word [rax]
fnstsw word [rax + 0x0]
fnstsw word [rax + 0xFFFF]
fnstsw word [r15 + 0xFFFF]
fnstsw word [rax + rsi * 1  + 0x0]
fnstsw word [rax + rsi + 0xFFFF]
fnstsw word [r15 + rsi + 0xFFFF]
fnstsw word [rax + r15 + 0xFFFF]
fnstsw word [rax + rsi * 2 + 0xFFFF2]
fnstsw word [rax + rsi * 4 + 0xFFFF4]
fnstsw word [rax + rsi * 8 + 0xFFFF8]
fnstsw word [rsp + rax * 8 + 0xFFFF8]
fnstsw word [r15 + rax * 8 + 0xFFFF8]
fnstsw word [rsp + r15 * 8 + 0xFFFF8]
fnstsw word [r14 + r15 * 8 + 0xFFFF8]
