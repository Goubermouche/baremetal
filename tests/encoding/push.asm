; expect: 66ff34250000000066ff3425ff00000066ff35f9ffffff66ff35f800000066ff35f8ff000066ff3066ff3066ffb0ffff00006641ffb7ffff000066ff343066ffb430ffff00006641ffb437ffff00006642ffb438ffff000066ffb470f2ff0f0066ffb4b0f4ff0f0066ffb4f0f8ff0f0066ffb4c4f8ff0f006641ffb4c7f8ff0f006642ffb4fcf8ff0f006643ffb4fef8ff0f00ff342500000000ff3425ff000000ff35faffffffff35f9000000ff35f9ff0000ff30ff30ffb0ffff000041ffb7ffff0000ff3430ffb430ffff000041ffb437ffff000042ffb438ffff0000ffb470f2ff0f00ffb4b0f4ff0f00ffb4f0f8ff0f00ffb4c4f8ff0f0041ffb4c7f8ff0f0042ffb4fcf8ff0f0043ffb4fef8ff0f00665166526653664157515341576a006a016a0a6a646a7f6a80688096980068ffffff7f680000008068ff7f0000680080ffff0fa00fa8

bits 64

push word [0x0]
push word [0xFF]
push word [rel $ + 0x0]
push word [rel $ + 0xFF]
push word [rel $ + 0xFFFF]
push word [rax]
push word [rax + 0x0]
push word [rax + 0xFFFF]
push word [r15 + 0xFFFF]
push word [rax + rsi * 1  + 0x0]
push word [rax + rsi + 0xFFFF]
push word [r15 + rsi + 0xFFFF]
push word [rax + r15 + 0xFFFF]
push word [rax + rsi * 2 + 0xFFFF2]
push word [rax + rsi * 4 + 0xFFFF4]
push word [rax + rsi * 8 + 0xFFFF8]
push word [rsp + rax * 8 + 0xFFFF8]
push word [r15 + rax * 8 + 0xFFFF8]
push word [rsp + r15 * 8 + 0xFFFF8]
push word [r14 + r15 * 8 + 0xFFFF8]
push qword [0x0]
push qword [0xFF]
push qword [rel $ + 0x0]
push qword [rel $ + 0xFF]
push qword [rel $ + 0xFFFF]
push qword [rax]
push qword [rax + 0x0]
push qword [rax + 0xFFFF]
push qword [r15 + 0xFFFF]
push qword [rax + rsi * 1  + 0x0]
push qword [rax + rsi + 0xFFFF]
push qword [r15 + rsi + 0xFFFF]
push qword [rax + r15 + 0xFFFF]
push qword [rax + rsi * 2 + 0xFFFF2]
push qword [rax + rsi * 4 + 0xFFFF4]
push qword [rax + rsi * 8 + 0xFFFF8]
push qword [rsp + rax * 8 + 0xFFFF8]
push qword [r15 + rax * 8 + 0xFFFF8]
push qword [rsp + r15 * 8 + 0xFFFF8]
push qword [r14 + r15 * 8 + 0xFFFF8]
push cx
push dx
push bx
push r15w
push rcx
push rbx
push r15
push 0
push 1
push 10
push 100
push 127
push -128
push 10000000
push 2147483647
push -2147483648
push 32767
push -32768
push fs
push gs
