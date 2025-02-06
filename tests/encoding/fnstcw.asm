; expect: d93c2500000000d93c25ff000000d93dfaffffffd93df9000000d93df9ff0000d938d938d9b8ffff000041d9bfffff0000d93c30d9bc30ffff000041d9bc37ffff000042d9bc38ffff0000d9bc70f2ff0f00d9bcb0f4ff0f00d9bcf0f8ff0f00d9bcc4f8ff0f0041d9bcc7f8ff0f0042d9bcfcf8ff0f0043d9bcfef8ff0f00

bits 64

fnstcw word [0x0]
fnstcw word [0xFF]
fnstcw word [rel $ + 0x0]
fnstcw word [rel $ + 0xFF]
fnstcw word [rel $ + 0xFFFF]
fnstcw word [rax]
fnstcw word [rax + 0x0]
fnstcw word [rax + 0xFFFF]
fnstcw word [r15 + 0xFFFF]
fnstcw word [rax + rsi * 1  + 0x0]
fnstcw word [rax + rsi + 0xFFFF]
fnstcw word [r15 + rsi + 0xFFFF]
fnstcw word [rax + r15 + 0xFFFF]
fnstcw word [rax + rsi * 2 + 0xFFFF2]
fnstcw word [rax + rsi * 4 + 0xFFFF4]
fnstcw word [rax + rsi * 8 + 0xFFFF8]
fnstcw word [rsp + rax * 8 + 0xFFFF8]
fnstcw word [r15 + rax * 8 + 0xFFFF8]
fnstcw word [rsp + r15 * 8 + 0xFFFF8]
fnstcw word [r14 + r15 * 8 + 0xFFFF8]
