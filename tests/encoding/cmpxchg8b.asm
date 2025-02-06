; expect: 0fc70c25000000000fc70c25ff0000000fc70df9ffffff0fc70df80000000fc70df8ff00000fc7080fc7080fc788ffff0000410fc78fffff00000fc70c300fc78c30ffff0000410fc78c37ffff0000420fc78c38ffff00000fc78c70f2ff0f000fc78cb0f4ff0f000fc78cf0f8ff0f000fc78cc4f8ff0f00410fc78cc7f8ff0f00420fc78cfcf8ff0f00430fc78cfef8ff0f00

bits 64

cmpxchg8b qword [0x0]
cmpxchg8b qword [0xFF]
cmpxchg8b qword [rel $ + 0x0]
cmpxchg8b qword [rel $ + 0xFF]
cmpxchg8b qword [rel $ + 0xFFFF]
cmpxchg8b qword [rax]
cmpxchg8b qword [rax + 0x0]
cmpxchg8b qword [rax + 0xFFFF]
cmpxchg8b qword [r15 + 0xFFFF]
cmpxchg8b qword [rax + rsi * 1  + 0x0]
cmpxchg8b qword [rax + rsi + 0xFFFF]
cmpxchg8b qword [r15 + rsi + 0xFFFF]
cmpxchg8b qword [rax + r15 + 0xFFFF]
cmpxchg8b qword [rax + rsi * 2 + 0xFFFF2]
cmpxchg8b qword [rax + rsi * 4 + 0xFFFF4]
cmpxchg8b qword [rax + rsi * 8 + 0xFFFF8]
cmpxchg8b qword [rsp + rax * 8 + 0xFFFF8]
cmpxchg8b qword [r15 + rax * 8 + 0xFFFF8]
cmpxchg8b qword [rsp + r15 * 8 + 0xFFFF8]
cmpxchg8b qword [r14 + r15 * 8 + 0xFFFF8]
