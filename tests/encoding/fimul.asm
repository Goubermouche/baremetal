; expect: de0c2500000000de0c25ff000000de0dfaffffffde0df9000000de0df9ff0000de08de08de88ffff000041de8fffff0000de0c30de8c30ffff000041de8c37ffff000042de8c38ffff0000de8c70f2ff0f00de8cb0f4ff0f00de8cf0f8ff0f00de8cc4f8ff0f0041de8cc7f8ff0f0042de8cfcf8ff0f0043de8cfef8ff0f00da0c2500000000da0c25ff000000da0dfaffffffda0df9000000da0df9ff0000da08da08da88ffff000041da8fffff0000da0c30da8c30ffff000041da8c37ffff000042da8c38ffff0000da8c70f2ff0f00da8cb0f4ff0f00da8cf0f8ff0f00da8cc4f8ff0f0041da8cc7f8ff0f0042da8cfcf8ff0f0043da8cfef8ff0f00

bits 64

fimul word [0x0]
fimul word [0xFF]
fimul word [rel $ + 0x0]
fimul word [rel $ + 0xFF]
fimul word [rel $ + 0xFFFF]
fimul word [rax]
fimul word [rax + 0x0]
fimul word [rax + 0xFFFF]
fimul word [r15 + 0xFFFF]
fimul word [rax + rsi * 1  + 0x0]
fimul word [rax + rsi + 0xFFFF]
fimul word [r15 + rsi + 0xFFFF]
fimul word [rax + r15 + 0xFFFF]
fimul word [rax + rsi * 2 + 0xFFFF2]
fimul word [rax + rsi * 4 + 0xFFFF4]
fimul word [rax + rsi * 8 + 0xFFFF8]
fimul word [rsp + rax * 8 + 0xFFFF8]
fimul word [r15 + rax * 8 + 0xFFFF8]
fimul word [rsp + r15 * 8 + 0xFFFF8]
fimul word [r14 + r15 * 8 + 0xFFFF8]
fimul dword [0x0]
fimul dword [0xFF]
fimul dword [rel $ + 0x0]
fimul dword [rel $ + 0xFF]
fimul dword [rel $ + 0xFFFF]
fimul dword [rax]
fimul dword [rax + 0x0]
fimul dword [rax + 0xFFFF]
fimul dword [r15 + 0xFFFF]
fimul dword [rax + rsi * 1  + 0x0]
fimul dword [rax + rsi + 0xFFFF]
fimul dword [r15 + rsi + 0xFFFF]
fimul dword [rax + r15 + 0xFFFF]
fimul dword [rax + rsi * 2 + 0xFFFF2]
fimul dword [rax + rsi * 4 + 0xFFFF4]
fimul dword [rax + rsi * 8 + 0xFFFF8]
fimul dword [rsp + rax * 8 + 0xFFFF8]
fimul dword [r15 + rax * 8 + 0xFFFF8]
fimul dword [rsp + r15 * 8 + 0xFFFF8]
fimul dword [r14 + r15 * 8 + 0xFFFF8]
