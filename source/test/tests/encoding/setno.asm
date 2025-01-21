; expect: 0f91c10f91c20f91c30f910425000000000f910425ff0000000f9105f9ffffff0f9105f80000000f9105f8ff00000f91000f91000f9180ffff0000410f9187ffff00000f9104300f918430ffff0000410f918437ffff0000420f918438ffff00000f918470f2ff0f000f9184b0f4ff0f000f9184f0f8ff0f000f9184c4f8ff0f00410f9184c7f8ff0f00420f9184fcf8ff0f00430f9184fef8ff0f00

setno cl
setno dl
setno bl
setno byte [0x0]
setno byte [0xFF]
setno byte [rel $ + 0x0]
setno byte [rel $ + 0xFF]
setno byte [rel $ + 0xFFFF]
setno byte [rax]
setno byte [rax + 0x0]
setno byte [rax + 0xFFFF]
setno byte [r15 + 0xFFFF]
setno byte [rax + rsi * 1  + 0x0]
setno byte [rax + rsi + 0xFFFF]
setno byte [r15 + rsi + 0xFFFF]
setno byte [rax + r15 + 0xFFFF]
setno byte [rax + rsi * 2 + 0xFFFF2]
setno byte [rax + rsi * 4 + 0xFFFF4]
setno byte [rax + rsi * 8 + 0xFFFF8]
setno byte [rsp + rax * 8 + 0xFFFF8]
setno byte [r15 + rax * 8 + 0xFFFF8]
setno byte [rsp + r15 * 8 + 0xFFFF8]
setno byte [r14 + r15 * 8 + 0xFFFF8]