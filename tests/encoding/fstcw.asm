; expect: 9bd93c25000000009bd93c25ff0000009bd93df9ffffff9bd93df80000009bd93df8ff00009bd9389bd9389bd9b8ffff00009b41d9bfffff00009bd93c309bd9bc30ffff00009b41d9bc37ffff00009b42d9bc38ffff00009bd9bc70f2ff0f009bd9bcb0f4ff0f009bd9bcf0f8ff0f009bd9bcc4f8ff0f009b41d9bcc7f8ff0f009b42d9bcfcf8ff0f009b43d9bcfef8ff0f00

bits 64

fstcw word [0x0]
fstcw word [0xFF]
fstcw word [rel $ + 0x0]
fstcw word [rel $ + 0xFF]
fstcw word [rel $ + 0xFFFF]
fstcw word [rax]
fstcw word [rax + 0x0]
fstcw word [rax + 0xFFFF]
fstcw word [r15 + 0xFFFF]
fstcw word [rax + rsi * 1  + 0x0]
fstcw word [rax + rsi + 0xFFFF]
fstcw word [r15 + rsi + 0xFFFF]
fstcw word [rax + r15 + 0xFFFF]
fstcw word [rax + rsi * 2 + 0xFFFF2]
fstcw word [rax + rsi * 4 + 0xFFFF4]
fstcw word [rax + rsi * 8 + 0xFFFF8]
fstcw word [rsp + rax * 8 + 0xFFFF8]
fstcw word [r15 + rax * 8 + 0xFFFF8]
fstcw word [rsp + r15 * 8 + 0xFFFF8]
fstcw word [r14 + r15 * 8 + 0xFFFF8]
