; expect: d92c2500000000d92c25ff000000d92dfaffffffd92df9000000d92df9ff0000d928d928d9a8ffff000041d9afffff0000d92c30d9ac30ffff000041d9ac37ffff000042d9ac38ffff0000d9ac70f2ff0f00d9acb0f4ff0f00d9acf0f8ff0f00d9acc4f8ff0f0041d9acc7f8ff0f0042d9acfcf8ff0f0043d9acfef8ff0f00

bits 64

fldcw word [0x0]
fldcw word [0xFF]
fldcw word [rel $ + 0x0]
fldcw word [rel $ + 0xFF]
fldcw word [rel $ + 0xFFFF]
fldcw word [rax]
fldcw word [rax + 0x0]
fldcw word [rax + 0xFFFF]
fldcw word [r15 + 0xFFFF]
fldcw word [rax + rsi * 1  + 0x0]
fldcw word [rax + rsi + 0xFFFF]
fldcw word [r15 + rsi + 0xFFFF]
fldcw word [rax + r15 + 0xFFFF]
fldcw word [rax + rsi * 2 + 0xFFFF2]
fldcw word [rax + rsi * 4 + 0xFFFF4]
fldcw word [rax + rsi * 8 + 0xFFFF8]
fldcw word [rsp + rax * 8 + 0xFFFF8]
fldcw word [r15 + rax * 8 + 0xFFFF8]
fldcw word [rsp + r15 * 8 + 0xFFFF8]
fldcw word [r14 + r15 * 8 + 0xFFFF8]
