; expect: 9bdfe09bdd3c25000000009bdd3c25ff0000009bdd3df9ffffff9bdd3df80000009bdd3df8ff00009bdd389bdd389bddb8ffff00009b41ddbfffff00009bdd3c309bddbc30ffff00009b41ddbc37ffff00009b42ddbc38ffff00009bddbc70f2ff0f009bddbcb0f4ff0f009bddbcf0f8ff0f009bddbcc4f8ff0f009b41ddbcc7f8ff0f009b42ddbcfcf8ff0f009b43ddbcfef8ff0f00

bits 64

fstsw ax
fstsw word [0x0]
fstsw word [0xFF]
fstsw word [rel $ + 0x0]
fstsw word [rel $ + 0xFF]
fstsw word [rel $ + 0xFFFF]
fstsw word [rax]
fstsw word [rax + 0x0]
fstsw word [rax + 0xFFFF]
fstsw word [r15 + 0xFFFF]
fstsw word [rax + rsi * 1  + 0x0]
fstsw word [rax + rsi + 0xFFFF]
fstsw word [r15 + rsi + 0xFFFF]
fstsw word [rax + r15 + 0xFFFF]
fstsw word [rax + rsi * 2 + 0xFFFF2]
fstsw word [rax + rsi * 4 + 0xFFFF4]
fstsw word [rax + rsi * 8 + 0xFFFF8]
fstsw word [rsp + rax * 8 + 0xFFFF8]
fstsw word [r15 + rax * 8 + 0xFFFF8]
fstsw word [rsp + r15 * 8 + 0xFFFF8]
fstsw word [r14 + r15 * 8 + 0xFFFF8]
