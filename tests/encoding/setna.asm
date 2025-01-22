; expect: 0f96c10f96c20f96c30f960425000000000f960425ff0000000f9605f9ffffff0f9605f80000000f9605f8ff00000f96000f96000f9680ffff0000410f9687ffff00000f9604300f968430ffff0000410f968437ffff0000420f968438ffff00000f968470f2ff0f000f9684b0f4ff0f000f9684f0f8ff0f000f9684c4f8ff0f00410f9684c7f8ff0f00420f9684fcf8ff0f00430f9684fef8ff0f00

setna cl
setna dl
setna bl
setna byte [0x0]
setna byte [0xFF]
setna byte [rel $ + 0x0]
setna byte [rel $ + 0xFF]
setna byte [rel $ + 0xFFFF]
setna byte [rax]
setna byte [rax + 0x0]
setna byte [rax + 0xFFFF]
setna byte [r15 + 0xFFFF]
setna byte [rax + rsi * 1  + 0x0]
setna byte [rax + rsi + 0xFFFF]
setna byte [r15 + rsi + 0xFFFF]
setna byte [rax + r15 + 0xFFFF]
setna byte [rax + rsi * 2 + 0xFFFF2]
setna byte [rax + rsi * 4 + 0xFFFF4]
setna byte [rax + rsi * 8 + 0xFFFF8]
setna byte [rsp + rax * 8 + 0xFFFF8]
setna byte [r15 + rax * 8 + 0xFFFF8]
setna byte [rsp + r15 * 8 + 0xFFFF8]
setna byte [r14 + r15 * 8 + 0xFFFF8]