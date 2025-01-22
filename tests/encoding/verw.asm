; expect: 0f00e90f00ea0f00eb410f00ef0f002c25000000000f002c25ff0000000f002df9ffffff0f002df80000000f002df8ff00000f00280f00280f00a8ffff0000410f00afffff00000f002c300f00ac30ffff0000410f00ac37ffff0000420f00ac38ffff00000f00ac70f2ff0f000f00acb0f4ff0f000f00acf0f8ff0f000f00acc4f8ff0f00410f00acc7f8ff0f00420f00acfcf8ff0f00430f00acfef8ff0f00

verw cx
verw dx
verw bx
verw r15w
verw word [0x0]
verw word [0xFF]
verw word [rel $ + 0x0]
verw word [rel $ + 0xFF]
verw word [rel $ + 0xFFFF]
verw word [rax]
verw word [rax + 0x0]
verw word [rax + 0xFFFF]
verw word [r15 + 0xFFFF]
verw word [rax + rsi * 1  + 0x0]
verw word [rax + rsi + 0xFFFF]
verw word [r15 + rsi + 0xFFFF]
verw word [rax + r15 + 0xFFFF]
verw word [rax + rsi * 2 + 0xFFFF2]
verw word [rax + rsi * 4 + 0xFFFF4]
verw word [rax + rsi * 8 + 0xFFFF8]
verw word [rsp + rax * 8 + 0xFFFF8]
verw word [r15 + rax * 8 + 0xFFFF8]
verw word [rsp + r15 * 8 + 0xFFFF8]
verw word [r14 + r15 * 8 + 0xFFFF8]