; expect: 0f00d90f00da0f00db410f00df0f001c25000000000f001c25ff0000000f001df9ffffff0f001df80000000f001df8ff00000f00180f00180f0098ffff0000410f009fffff00000f001c300f009c30ffff0000410f009c37ffff0000420f009c38ffff00000f009c70f2ff0f000f009cb0f4ff0f000f009cf0f8ff0f000f009cc4f8ff0f00410f009cc7f8ff0f00420f009cfcf8ff0f00430f009cfef8ff0f00

bits 64

ltr cx
ltr dx
ltr bx
ltr r15w
ltr word [0x0]
ltr word [0xFF]
ltr word [rel $ + 0x0]
ltr word [rel $ + 0xFF]
ltr word [rel $ + 0xFFFF]
ltr word [rax]
ltr word [rax + 0x0]
ltr word [rax + 0xFFFF]
ltr word [r15 + 0xFFFF]
ltr word [rax + rsi * 1  + 0x0]
ltr word [rax + rsi + 0xFFFF]
ltr word [r15 + rsi + 0xFFFF]
ltr word [rax + r15 + 0xFFFF]
ltr word [rax + rsi * 2 + 0xFFFF2]
ltr word [rax + rsi * 4 + 0xFFFF4]
ltr word [rax + rsi * 8 + 0xFFFF8]
ltr word [rsp + rax * 8 + 0xFFFF8]
ltr word [r15 + rax * 8 + 0xFFFF8]
ltr word [rsp + r15 * 8 + 0xFFFF8]
ltr word [r14 + r15 * 8 + 0xFFFF8]
