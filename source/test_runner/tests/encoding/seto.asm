; expect: 0f90c10f90c20f90c30f900425000000000f900425ff0000000f9005f9ffffff0f9005f80000000f9005f8ff00000f90000f90000f9080ffff0000410f9087ffff00000f9004300f908430ffff0000410f908437ffff0000420f908438ffff00000f908470f2ff0f000f9084b0f4ff0f000f9084f0f8ff0f000f9084c4f8ff0f00410f9084c7f8ff0f00420f9084fcf8ff0f00430f9084fef8ff0f00

seto cl
seto dl
seto bl
seto byte [0x0]
seto byte [0xFF]
seto byte [rel $ + 0x0]
seto byte [rel $ + 0xFF]
seto byte [rel $ + 0xFFFF]
seto byte [rax]
seto byte [rax + 0x0]
seto byte [rax + 0xFFFF]
seto byte [r15 + 0xFFFF]
seto byte [rax + rsi * 1  + 0x0]
seto byte [rax + rsi + 0xFFFF]
seto byte [r15 + rsi + 0xFFFF]
seto byte [rax + r15 + 0xFFFF]
seto byte [rax + rsi * 2 + 0xFFFF2]
seto byte [rax + rsi * 4 + 0xFFFF4]
seto byte [rax + rsi * 8 + 0xFFFF8]
seto byte [rsp + rax * 8 + 0xFFFF8]
seto byte [r15 + rax * 8 + 0xFFFF8]
seto byte [rsp + r15 * 8 + 0xFFFF8]
seto byte [r14 + r15 * 8 + 0xFFFF8]