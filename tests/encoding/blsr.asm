; expect: c4e270f3c9c4e270f3cbc4c270f3cfc4e260f3c9c4e260f3cbc4c260f3cfc4e200f3c9c4e200f3cbc4c200f3cfc4e270f30c2500000000c4e270f30c25ff000000c4e270f30df7ffffffc4e270f30df6000000c4e270f30df6ff0000c4e270f308c4e270f308c4e270f388ffff0000c4c270f38fffff0000c4e270f30c30c4e270f38c30ffff0000c4c270f38c37ffff0000c4a270f38c38ffff0000c4e270f38c70f2ff0f00c4e270f38cb0f4ff0f00c4e270f38cf0f8ff0f00c4e270f38cc4f8ff0f00c4c270f38cc7f8ff0f00c4a270f38cfcf8ff0f00c48270f38cfef8ff0f00c4e260f30c2500000000c4e260f30c25ff000000c4e260f30df7ffffffc4e260f30df6000000c4e260f30df6ff0000c4e260f308c4e260f308c4e260f388ffff0000c4c260f38fffff0000c4e260f30c30c4e260f38c30ffff0000c4c260f38c37ffff0000c4a260f38c38ffff0000c4e260f38c70f2ff0f00c4e260f38cb0f4ff0f00c4e260f38cf0f8ff0f00c4e260f38cc4f8ff0f00c4c260f38cc7f8ff0f00c4a260f38cfcf8ff0f00c48260f38cfef8ff0f00c4e200f30c2500000000c4e200f30c25ff000000c4e200f30df7ffffffc4e200f30df6000000c4e200f30df6ff0000c4e200f308c4e200f308c4e200f388ffff0000c4c200f38fffff0000c4e200f30c30c4e200f38c30ffff0000c4c200f38c37ffff0000c4a200f38c38ffff0000c4e200f38c70f2ff0f00c4e200f38cb0f4ff0f00c4e200f38cf0f8ff0f00c4e200f38cc4f8ff0f00c4c200f38cc7f8ff0f00c4a200f38cfcf8ff0f00c48200f38cfef8ff0f00c4e2f0f3c9c4e2f0f3cbc4c2f0f3cfc4e2e0f3c9c4e2e0f3cbc4c2e0f3cfc4e280f3c9c4e280f3cbc4c280f3cfc4e2f0f30c2500000000c4e2f0f30c25ff000000c4e2f0f30df7ffffffc4e2f0f30df6000000c4e2f0f30df6ff0000c4e2f0f308c4e2f0f308c4e2f0f388ffff0000c4c2f0f38fffff0000c4e2f0f30c30c4e2f0f38c30ffff0000c4c2f0f38c37ffff0000c4a2f0f38c38ffff0000c4e2f0f38c70f2ff0f00c4e2f0f38cb0f4ff0f00c4e2f0f38cf0f8ff0f00c4e2f0f38cc4f8ff0f00c4c2f0f38cc7f8ff0f00c4a2f0f38cfcf8ff0f00c482f0f38cfef8ff0f00c4e2e0f30c2500000000c4e2e0f30c25ff000000c4e2e0f30df7ffffffc4e2e0f30df6000000c4e2e0f30df6ff0000c4e2e0f308c4e2e0f308c4e2e0f388ffff0000c4c2e0f38fffff0000c4e2e0f30c30c4e2e0f38c30ffff0000c4c2e0f38c37ffff0000c4a2e0f38c38ffff0000c4e2e0f38c70f2ff0f00c4e2e0f38cb0f4ff0f00c4e2e0f38cf0f8ff0f00c4e2e0f38cc4f8ff0f00c4c2e0f38cc7f8ff0f00c4a2e0f38cfcf8ff0f00c482e0f38cfef8ff0f00c4e280f30c2500000000c4e280f30c25ff000000c4e280f30df7ffffffc4e280f30df6000000c4e280f30df6ff0000c4e280f308c4e280f308c4e280f388ffff0000c4c280f38fffff0000c4e280f30c30c4e280f38c30ffff0000c4c280f38c37ffff0000c4a280f38c38ffff0000c4e280f38c70f2ff0f00c4e280f38cb0f4ff0f00c4e280f38cf0f8ff0f00c4e280f38cc4f8ff0f00c4c280f38cc7f8ff0f00c4a280f38cfcf8ff0f00c48280f38cfef8ff0f00

bits 64

blsr ecx, ecx
blsr ecx, ebx
blsr ecx, r15d
blsr ebx, ecx
blsr ebx, ebx
blsr ebx, r15d
blsr r15d, ecx
blsr r15d, ebx
blsr r15d, r15d
blsr ecx, dword [0x0]
blsr ecx, dword [0xFF]
blsr ecx, dword [rel $ + 0x0]
blsr ecx, dword [rel $ + 0xFF]
blsr ecx, dword [rel $ + 0xFFFF]
blsr ecx, dword [rax]
blsr ecx, dword [rax + 0x0]
blsr ecx, dword [rax + 0xFFFF]
blsr ecx, dword [r15 + 0xFFFF]
blsr ecx, dword [rax + rsi * 1  + 0x0]
blsr ecx, dword [rax + rsi + 0xFFFF]
blsr ecx, dword [r15 + rsi + 0xFFFF]
blsr ecx, dword [rax + r15 + 0xFFFF]
blsr ecx, dword [rax + rsi * 2 + 0xFFFF2]
blsr ecx, dword [rax + rsi * 4 + 0xFFFF4]
blsr ecx, dword [rax + rsi * 8 + 0xFFFF8]
blsr ecx, dword [rsp + rax * 8 + 0xFFFF8]
blsr ecx, dword [r15 + rax * 8 + 0xFFFF8]
blsr ecx, dword [rsp + r15 * 8 + 0xFFFF8]
blsr ecx, dword [r14 + r15 * 8 + 0xFFFF8]
blsr ebx, dword [0x0]
blsr ebx, dword [0xFF]
blsr ebx, dword [rel $ + 0x0]
blsr ebx, dword [rel $ + 0xFF]
blsr ebx, dword [rel $ + 0xFFFF]
blsr ebx, dword [rax]
blsr ebx, dword [rax + 0x0]
blsr ebx, dword [rax + 0xFFFF]
blsr ebx, dword [r15 + 0xFFFF]
blsr ebx, dword [rax + rsi * 1  + 0x0]
blsr ebx, dword [rax + rsi + 0xFFFF]
blsr ebx, dword [r15 + rsi + 0xFFFF]
blsr ebx, dword [rax + r15 + 0xFFFF]
blsr ebx, dword [rax + rsi * 2 + 0xFFFF2]
blsr ebx, dword [rax + rsi * 4 + 0xFFFF4]
blsr ebx, dword [rax + rsi * 8 + 0xFFFF8]
blsr ebx, dword [rsp + rax * 8 + 0xFFFF8]
blsr ebx, dword [r15 + rax * 8 + 0xFFFF8]
blsr ebx, dword [rsp + r15 * 8 + 0xFFFF8]
blsr ebx, dword [r14 + r15 * 8 + 0xFFFF8]
blsr r15d, dword [0x0]
blsr r15d, dword [0xFF]
blsr r15d, dword [rel $ + 0x0]
blsr r15d, dword [rel $ + 0xFF]
blsr r15d, dword [rel $ + 0xFFFF]
blsr r15d, dword [rax]
blsr r15d, dword [rax + 0x0]
blsr r15d, dword [rax + 0xFFFF]
blsr r15d, dword [r15 + 0xFFFF]
blsr r15d, dword [rax + rsi * 1  + 0x0]
blsr r15d, dword [rax + rsi + 0xFFFF]
blsr r15d, dword [r15 + rsi + 0xFFFF]
blsr r15d, dword [rax + r15 + 0xFFFF]
blsr r15d, dword [rax + rsi * 2 + 0xFFFF2]
blsr r15d, dword [rax + rsi * 4 + 0xFFFF4]
blsr r15d, dword [rax + rsi * 8 + 0xFFFF8]
blsr r15d, dword [rsp + rax * 8 + 0xFFFF8]
blsr r15d, dword [r15 + rax * 8 + 0xFFFF8]
blsr r15d, dword [rsp + r15 * 8 + 0xFFFF8]
blsr r15d, dword [r14 + r15 * 8 + 0xFFFF8]
blsr rcx, rcx
blsr rcx, rbx
blsr rcx, r15
blsr rbx, rcx
blsr rbx, rbx
blsr rbx, r15
blsr r15, rcx
blsr r15, rbx
blsr r15, r15
blsr rcx, qword [0x0]
blsr rcx, qword [0xFF]
blsr rcx, qword [rel $ + 0x0]
blsr rcx, qword [rel $ + 0xFF]
blsr rcx, qword [rel $ + 0xFFFF]
blsr rcx, qword [rax]
blsr rcx, qword [rax + 0x0]
blsr rcx, qword [rax + 0xFFFF]
blsr rcx, qword [r15 + 0xFFFF]
blsr rcx, qword [rax + rsi * 1  + 0x0]
blsr rcx, qword [rax + rsi + 0xFFFF]
blsr rcx, qword [r15 + rsi + 0xFFFF]
blsr rcx, qword [rax + r15 + 0xFFFF]
blsr rcx, qword [rax + rsi * 2 + 0xFFFF2]
blsr rcx, qword [rax + rsi * 4 + 0xFFFF4]
blsr rcx, qword [rax + rsi * 8 + 0xFFFF8]
blsr rcx, qword [rsp + rax * 8 + 0xFFFF8]
blsr rcx, qword [r15 + rax * 8 + 0xFFFF8]
blsr rcx, qword [rsp + r15 * 8 + 0xFFFF8]
blsr rcx, qword [r14 + r15 * 8 + 0xFFFF8]
blsr rbx, qword [0x0]
blsr rbx, qword [0xFF]
blsr rbx, qword [rel $ + 0x0]
blsr rbx, qword [rel $ + 0xFF]
blsr rbx, qword [rel $ + 0xFFFF]
blsr rbx, qword [rax]
blsr rbx, qword [rax + 0x0]
blsr rbx, qword [rax + 0xFFFF]
blsr rbx, qword [r15 + 0xFFFF]
blsr rbx, qword [rax + rsi * 1  + 0x0]
blsr rbx, qword [rax + rsi + 0xFFFF]
blsr rbx, qword [r15 + rsi + 0xFFFF]
blsr rbx, qword [rax + r15 + 0xFFFF]
blsr rbx, qword [rax + rsi * 2 + 0xFFFF2]
blsr rbx, qword [rax + rsi * 4 + 0xFFFF4]
blsr rbx, qword [rax + rsi * 8 + 0xFFFF8]
blsr rbx, qword [rsp + rax * 8 + 0xFFFF8]
blsr rbx, qword [r15 + rax * 8 + 0xFFFF8]
blsr rbx, qword [rsp + r15 * 8 + 0xFFFF8]
blsr rbx, qword [r14 + r15 * 8 + 0xFFFF8]
blsr r15, qword [0x0]
blsr r15, qword [0xFF]
blsr r15, qword [rel $ + 0x0]
blsr r15, qword [rel $ + 0xFF]
blsr r15, qword [rel $ + 0xFFFF]
blsr r15, qword [rax]
blsr r15, qword [rax + 0x0]
blsr r15, qword [rax + 0xFFFF]
blsr r15, qword [r15 + 0xFFFF]
blsr r15, qword [rax + rsi * 1  + 0x0]
blsr r15, qword [rax + rsi + 0xFFFF]
blsr r15, qword [r15 + rsi + 0xFFFF]
blsr r15, qword [rax + r15 + 0xFFFF]
blsr r15, qword [rax + rsi * 2 + 0xFFFF2]
blsr r15, qword [rax + rsi * 4 + 0xFFFF4]
blsr r15, qword [rax + rsi * 8 + 0xFFFF8]
blsr r15, qword [rsp + rax * 8 + 0xFFFF8]
blsr r15, qword [r15 + rax * 8 + 0xFFFF8]
blsr r15, qword [rsp + r15 * 8 + 0xFFFF8]
blsr r15, qword [r14 + r15 * 8 + 0xFFFF8]
