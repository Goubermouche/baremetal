; expect: c4e27949042500000000c4e279490425ff000000c4e2794905f7ffffffc4e2794905f6000000c4e2794905f6ff0000c4e2794900c4e2794900c4e2794980ffff0000c4c2794987ffff0000c4e279490430c4e279498430ffff0000c4c279498437ffff0000c4a279498438ffff0000c4e279498470f2ff0f00c4e2794984b0f4ff0f00c4e2794984f0f8ff0f00c4e2794984c4f8ff0f00c4c2794984c7f8ff0f00c4a2794984fcf8ff0f00c482794984fef8ff0f00

bits 64

sttilecfg [0x0]
sttilecfg [0xFF]
sttilecfg [rel $ + 0x0]
sttilecfg [rel $ + 0xFF]
sttilecfg [rel $ + 0xFFFF]
sttilecfg [rax]
sttilecfg [rax + 0x0]
sttilecfg [rax + 0xFFFF]
sttilecfg [r15 + 0xFFFF]
sttilecfg [rax + rsi * 1  + 0x0]
sttilecfg [rax + rsi + 0xFFFF]
sttilecfg [r15 + rsi + 0xFFFF]
sttilecfg [rax + r15 + 0xFFFF]
sttilecfg [rax + rsi * 2 + 0xFFFF2]
sttilecfg [rax + rsi * 4 + 0xFFFF4]
sttilecfg [rax + rsi * 8 + 0xFFFF8]
sttilecfg [rsp + rax * 8 + 0xFFFF8]
sttilecfg [r15 + rax * 8 + 0xFFFF8]
sttilecfg [rsp + r15 * 8 + 0xFFFF8]
sttilecfg [r14 + r15 * 8 + 0xFFFF8]
