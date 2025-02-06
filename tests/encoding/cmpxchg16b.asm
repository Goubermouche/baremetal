; expect: 480fc70c2500000000480fc70c25ff000000480fc70df8ffffff480fc70df7000000480fc70df7ff0000480fc708480fc708480fc788ffff0000490fc78fffff0000480fc70c30480fc78c30ffff0000490fc78c37ffff00004a0fc78c38ffff0000480fc78c70f2ff0f00480fc78cb0f4ff0f00480fc78cf0f8ff0f00480fc78cc4f8ff0f00490fc78cc7f8ff0f004a0fc78cfcf8ff0f004b0fc78cfef8ff0f00

bits 64

cmpxchg16b [0x0]
cmpxchg16b [0xFF]
cmpxchg16b [rel $ + 0x0]
cmpxchg16b [rel $ + 0xFF]
cmpxchg16b [rel $ + 0xFFFF]
cmpxchg16b [rax]
cmpxchg16b [rax + 0x0]
cmpxchg16b [rax + 0xFFFF]
cmpxchg16b [r15 + 0xFFFF]
cmpxchg16b [rax + rsi * 1  + 0x0]
cmpxchg16b [rax + rsi + 0xFFFF]
cmpxchg16b [r15 + rsi + 0xFFFF]
cmpxchg16b [rax + r15 + 0xFFFF]
cmpxchg16b [rax + rsi * 2 + 0xFFFF2]
cmpxchg16b [rax + rsi * 4 + 0xFFFF4]
cmpxchg16b [rax + rsi * 8 + 0xFFFF8]
cmpxchg16b [rsp + rax * 8 + 0xFFFF8]
cmpxchg16b [r15 + rax * 8 + 0xFFFF8]
cmpxchg16b [rsp + r15 * 8 + 0xFFFF8]
cmpxchg16b [r14 + r15 * 8 + 0xFFFF8]
