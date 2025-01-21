; expect: 62f57e081104250000000062f57e08110c250000000062757e08113c250000000062657e08113c250000000062f57e08110425ff00000062f57e08110c25ff00000062757e08113c25ff00000062657e08113c25ff00000062f57e081105f6ffffff62f57e08110df6ffffff62757e08113df6ffffff62657e08113df6ffffff62f57e081105f500000062f57e08110df500000062757e08113df500000062657e08113df500000062f57e081105f5ff000062f57e08110df5ff000062757e08113df5ff000062657e08113df5ff000062f57e08110062f57e08110862757e08113862657e08113862f57e08110062f57e08110862757e08113862657e08113862f57e081180ffff000062f57e081188ffff000062757e0811b8ffff000062657e0811b8ffff000062d57e081187ffff000062d57e08118fffff000062557e0811bfffff000062457e0811bfffff000062f57e0811043062f57e08110c3062757e08113c3062657e08113c3062f57e08118430ffff000062f57e08118c30ffff000062757e0811bc30ffff000062657e0811bc30ffff000062d57e08118437ffff000062d57e08118c37ffff000062557e0811bc37ffff000062457e0811bc37ffff000062b57e08118438ffff000062b57e08118c38ffff000062357e0811bc38ffff000062257e0811bc38ffff000062f57e08118470f2ff0f0062f57e08118c70f2ff0f0062757e0811bc70f2ff0f0062657e0811bc70f2ff0f0062f57e081184b0f4ff0f0062f57e08118cb0f4ff0f0062757e0811bcb0f4ff0f0062657e0811bcb0f4ff0f0062f57e081184f0f8ff0f0062f57e08118cf0f8ff0f0062757e0811bcf0f8ff0f0062657e0811bcf0f8ff0f0062f57e081184c4f8ff0f0062f57e08118cc4f8ff0f0062757e0811bcc4f8ff0f0062657e0811bcc4f8ff0f0062d57e081184c7f8ff0f0062d57e08118cc7f8ff0f0062557e0811bcc7f8ff0f0062457e0811bcc7f8ff0f0062b57e081184fcf8ff0f0062b57e08118cfcf8ff0f0062357e0811bcfcf8ff0f0062257e0811bcfcf8ff0f0062957e081184fef8ff0f0062957e08118cfef8ff0f0062157e0811bcfef8ff0f0062057e0811bcfef8ff0f0062f57e89100c250000000062f57e89100c25ff00000062f57e89100df6ffffff62f57e89100df500000062f57e89100df5ff000062f57e89100862f57e89100862f57e891088ffff000062d57e89108fffff000062f57e89100c3062f57e89108c30ffff000062d57e89108c37ffff000062b57e89108c38ffff000062f57e89108c70f2ff0f0062f57e89108cb0f4ff0f0062f57e89108cf0f8ff0f0062f57e89108cc4f8ff0f0062d57e89108cc7f8ff0f0062b57e89108cfcf8ff0f0062957e89108cfef8ff0f0062f57e8a1014250000000062f57e8a101425ff00000062f57e8a1015f6ffffff62f57e8a1015f500000062f57e8a1015f5ff000062f57e8a101062f57e8a101062f57e8a1090ffff000062d57e8a1097ffff000062f57e8a10143062f57e8a109430ffff000062d57e8a109437ffff000062b57e8a109438ffff000062f57e8a109470f2ff0f0062f57e8a1094b0f4ff0f0062f57e8a1094f0f8ff0f0062f57e8a1094c4f8ff0f0062d57e8a1094c7f8ff0f0062b57e8a1094fcf8ff0f0062957e8a1094fef8ff0f0062757e8f103c250000000062757e8f103c25ff00000062757e8f103df6ffffff62757e8f103df500000062757e8f103df5ff000062757e8f103862757e8f103862757e8f10b8ffff000062557e8f10bfffff000062757e8f103c3062757e8f10bc30ffff000062557e8f10bc37ffff000062357e8f10bc38ffff000062757e8f10bc70f2ff0f0062757e8f10bcb0f4ff0f0062757e8f10bcf0f8ff0f0062757e8f10bcc4f8ff0f0062557e8f10bcc7f8ff0f0062357e8f10bcfcf8ff0f0062157e8f10bcfef8ff0f0062f57e8910c862f57e8910c962d57e8910cf62957e8910cf62f5768910c862f5768910c962d5768910cf6295768910cf62f5068910c862f5068910c962d5068910cf6295068910cf62f5068110c862f5068110c962d5068110cf6295068110cf62f57e8a10d062f57e8a10d162d57e8a10d762957e8a10d762f5768a10d062f5768a10d162d5768a10d76295768a10d762f5068a10d062f5068a10d162d5068a10d76295068a10d762f5068210d062f5068210d162d5068210d76295068210d762757e8f10f862757e8f10f962557e8f10ff62157e8f10ff6275768f10f86275768f10f96255768f10ff6215768f10ff6275068f10f86275068f10f96255068f10ff6215068f10ff6275068710f86275068710f96255068710ff6215068710ff

vmovsh word [0x0], xmm0
vmovsh word [0x0], xmm1
vmovsh word [0x0], xmm15
vmovsh word [0x0], xmm31
vmovsh word [0xFF], xmm0
vmovsh word [0xFF], xmm1
vmovsh word [0xFF], xmm15
vmovsh word [0xFF], xmm31
vmovsh word [rel $ + 0x0], xmm0
vmovsh word [rel $ + 0x0], xmm1
vmovsh word [rel $ + 0x0], xmm15
vmovsh word [rel $ + 0x0], xmm31
vmovsh word [rel $ + 0xFF], xmm0
vmovsh word [rel $ + 0xFF], xmm1
vmovsh word [rel $ + 0xFF], xmm15
vmovsh word [rel $ + 0xFF], xmm31
vmovsh word [rel $ + 0xFFFF], xmm0
vmovsh word [rel $ + 0xFFFF], xmm1
vmovsh word [rel $ + 0xFFFF], xmm15
vmovsh word [rel $ + 0xFFFF], xmm31
vmovsh word [rax], xmm0
vmovsh word [rax], xmm1
vmovsh word [rax], xmm15
vmovsh word [rax], xmm31
vmovsh word [rax + 0x0], xmm0
vmovsh word [rax + 0x0], xmm1
vmovsh word [rax + 0x0], xmm15
vmovsh word [rax + 0x0], xmm31
vmovsh word [rax + 0xFFFF], xmm0
vmovsh word [rax + 0xFFFF], xmm1
vmovsh word [rax + 0xFFFF], xmm15
vmovsh word [rax + 0xFFFF], xmm31
vmovsh word [r15 + 0xFFFF], xmm0
vmovsh word [r15 + 0xFFFF], xmm1
vmovsh word [r15 + 0xFFFF], xmm15
vmovsh word [r15 + 0xFFFF], xmm31
vmovsh word [rax + rsi * 1  + 0x0], xmm0
vmovsh word [rax + rsi * 1  + 0x0], xmm1
vmovsh word [rax + rsi * 1  + 0x0], xmm15
vmovsh word [rax + rsi * 1  + 0x0], xmm31
vmovsh word [rax + rsi + 0xFFFF], xmm0
vmovsh word [rax + rsi + 0xFFFF], xmm1
vmovsh word [rax + rsi + 0xFFFF], xmm15
vmovsh word [rax + rsi + 0xFFFF], xmm31
vmovsh word [r15 + rsi + 0xFFFF], xmm0
vmovsh word [r15 + rsi + 0xFFFF], xmm1
vmovsh word [r15 + rsi + 0xFFFF], xmm15
vmovsh word [r15 + rsi + 0xFFFF], xmm31
vmovsh word [rax + r15 + 0xFFFF], xmm0
vmovsh word [rax + r15 + 0xFFFF], xmm1
vmovsh word [rax + r15 + 0xFFFF], xmm15
vmovsh word [rax + r15 + 0xFFFF], xmm31
vmovsh word [rax + rsi * 2 + 0xFFFF2], xmm0
vmovsh word [rax + rsi * 2 + 0xFFFF2], xmm1
vmovsh word [rax + rsi * 2 + 0xFFFF2], xmm15
vmovsh word [rax + rsi * 2 + 0xFFFF2], xmm31
vmovsh word [rax + rsi * 4 + 0xFFFF4], xmm0
vmovsh word [rax + rsi * 4 + 0xFFFF4], xmm1
vmovsh word [rax + rsi * 4 + 0xFFFF4], xmm15
vmovsh word [rax + rsi * 4 + 0xFFFF4], xmm31
vmovsh word [rax + rsi * 8 + 0xFFFF8], xmm0
vmovsh word [rax + rsi * 8 + 0xFFFF8], xmm1
vmovsh word [rax + rsi * 8 + 0xFFFF8], xmm15
vmovsh word [rax + rsi * 8 + 0xFFFF8], xmm31
vmovsh word [rsp + rax * 8 + 0xFFFF8], xmm0
vmovsh word [rsp + rax * 8 + 0xFFFF8], xmm1
vmovsh word [rsp + rax * 8 + 0xFFFF8], xmm15
vmovsh word [rsp + rax * 8 + 0xFFFF8], xmm31
vmovsh word [r15 + rax * 8 + 0xFFFF8], xmm0
vmovsh word [r15 + rax * 8 + 0xFFFF8], xmm1
vmovsh word [r15 + rax * 8 + 0xFFFF8], xmm15
vmovsh word [r15 + rax * 8 + 0xFFFF8], xmm31
vmovsh word [rsp + r15 * 8 + 0xFFFF8], xmm0
vmovsh word [rsp + r15 * 8 + 0xFFFF8], xmm1
vmovsh word [rsp + r15 * 8 + 0xFFFF8], xmm15
vmovsh word [rsp + r15 * 8 + 0xFFFF8], xmm31
vmovsh word [r14 + r15 * 8 + 0xFFFF8], xmm0
vmovsh word [r14 + r15 * 8 + 0xFFFF8], xmm1
vmovsh word [r14 + r15 * 8 + 0xFFFF8], xmm15
vmovsh word [r14 + r15 * 8 + 0xFFFF8], xmm31
vmovsh xmm1{k1}{z}, word [0x0]
vmovsh xmm1{k1}{z}, word [0xFF]
vmovsh xmm1{k1}{z}, word [rel $ + 0x0]
vmovsh xmm1{k1}{z}, word [rel $ + 0xFF]
vmovsh xmm1{k1}{z}, word [rel $ + 0xFFFF]
vmovsh xmm1{k1}{z}, word [rax]
vmovsh xmm1{k1}{z}, word [rax + 0x0]
vmovsh xmm1{k1}{z}, word [rax + 0xFFFF]
vmovsh xmm1{k1}{z}, word [r15 + 0xFFFF]
vmovsh xmm1{k1}{z}, word [rax + rsi * 1  + 0x0]
vmovsh xmm1{k1}{z}, word [rax + rsi + 0xFFFF]
vmovsh xmm1{k1}{z}, word [r15 + rsi + 0xFFFF]
vmovsh xmm1{k1}{z}, word [rax + r15 + 0xFFFF]
vmovsh xmm1{k1}{z}, word [rax + rsi * 2 + 0xFFFF2]
vmovsh xmm1{k1}{z}, word [rax + rsi * 4 + 0xFFFF4]
vmovsh xmm1{k1}{z}, word [rax + rsi * 8 + 0xFFFF8]
vmovsh xmm1{k1}{z}, word [rsp + rax * 8 + 0xFFFF8]
vmovsh xmm1{k1}{z}, word [r15 + rax * 8 + 0xFFFF8]
vmovsh xmm1{k1}{z}, word [rsp + r15 * 8 + 0xFFFF8]
vmovsh xmm1{k1}{z}, word [r14 + r15 * 8 + 0xFFFF8]
vmovsh xmm2{k2}{z}, word [0x0]
vmovsh xmm2{k2}{z}, word [0xFF]
vmovsh xmm2{k2}{z}, word [rel $ + 0x0]
vmovsh xmm2{k2}{z}, word [rel $ + 0xFF]
vmovsh xmm2{k2}{z}, word [rel $ + 0xFFFF]
vmovsh xmm2{k2}{z}, word [rax]
vmovsh xmm2{k2}{z}, word [rax + 0x0]
vmovsh xmm2{k2}{z}, word [rax + 0xFFFF]
vmovsh xmm2{k2}{z}, word [r15 + 0xFFFF]
vmovsh xmm2{k2}{z}, word [rax + rsi * 1  + 0x0]
vmovsh xmm2{k2}{z}, word [rax + rsi + 0xFFFF]
vmovsh xmm2{k2}{z}, word [r15 + rsi + 0xFFFF]
vmovsh xmm2{k2}{z}, word [rax + r15 + 0xFFFF]
vmovsh xmm2{k2}{z}, word [rax + rsi * 2 + 0xFFFF2]
vmovsh xmm2{k2}{z}, word [rax + rsi * 4 + 0xFFFF4]
vmovsh xmm2{k2}{z}, word [rax + rsi * 8 + 0xFFFF8]
vmovsh xmm2{k2}{z}, word [rsp + rax * 8 + 0xFFFF8]
vmovsh xmm2{k2}{z}, word [r15 + rax * 8 + 0xFFFF8]
vmovsh xmm2{k2}{z}, word [rsp + r15 * 8 + 0xFFFF8]
vmovsh xmm2{k2}{z}, word [r14 + r15 * 8 + 0xFFFF8]
vmovsh xmm15{k7}{z}, word [0x0]
vmovsh xmm15{k7}{z}, word [0xFF]
vmovsh xmm15{k7}{z}, word [rel $ + 0x0]
vmovsh xmm15{k7}{z}, word [rel $ + 0xFF]
vmovsh xmm15{k7}{z}, word [rel $ + 0xFFFF]
vmovsh xmm15{k7}{z}, word [rax]
vmovsh xmm15{k7}{z}, word [rax + 0x0]
vmovsh xmm15{k7}{z}, word [rax + 0xFFFF]
vmovsh xmm15{k7}{z}, word [r15 + 0xFFFF]
vmovsh xmm15{k7}{z}, word [rax + rsi * 1  + 0x0]
vmovsh xmm15{k7}{z}, word [rax + rsi + 0xFFFF]
vmovsh xmm15{k7}{z}, word [r15 + rsi + 0xFFFF]
vmovsh xmm15{k7}{z}, word [rax + r15 + 0xFFFF]
vmovsh xmm15{k7}{z}, word [rax + rsi * 2 + 0xFFFF2]
vmovsh xmm15{k7}{z}, word [rax + rsi * 4 + 0xFFFF4]
vmovsh xmm15{k7}{z}, word [rax + rsi * 8 + 0xFFFF8]
vmovsh xmm15{k7}{z}, word [rsp + rax * 8 + 0xFFFF8]
vmovsh xmm15{k7}{z}, word [r15 + rax * 8 + 0xFFFF8]
vmovsh xmm15{k7}{z}, word [rsp + r15 * 8 + 0xFFFF8]
vmovsh xmm15{k7}{z}, word [r14 + r15 * 8 + 0xFFFF8]
vmovsh xmm1{k1}{z}, xmm0, xmm0
vmovsh xmm1{k1}{z}, xmm0, xmm1
vmovsh xmm1{k1}{z}, xmm0, xmm15
vmovsh xmm1{k1}{z}, xmm0, xmm31
vmovsh xmm1{k1}{z}, xmm1, xmm0
vmovsh xmm1{k1}{z}, xmm1, xmm1
vmovsh xmm1{k1}{z}, xmm1, xmm15
vmovsh xmm1{k1}{z}, xmm1, xmm31
vmovsh xmm1{k1}{z}, xmm15, xmm0
vmovsh xmm1{k1}{z}, xmm15, xmm1
vmovsh xmm1{k1}{z}, xmm15, xmm15
vmovsh xmm1{k1}{z}, xmm15, xmm31
vmovsh xmm1{k1}{z}, xmm31, xmm0
vmovsh xmm1{k1}{z}, xmm31, xmm1
vmovsh xmm1{k1}{z}, xmm31, xmm15
vmovsh xmm1{k1}{z}, xmm31, xmm31
vmovsh xmm2{k2}{z}, xmm0, xmm0
vmovsh xmm2{k2}{z}, xmm0, xmm1
vmovsh xmm2{k2}{z}, xmm0, xmm15
vmovsh xmm2{k2}{z}, xmm0, xmm31
vmovsh xmm2{k2}{z}, xmm1, xmm0
vmovsh xmm2{k2}{z}, xmm1, xmm1
vmovsh xmm2{k2}{z}, xmm1, xmm15
vmovsh xmm2{k2}{z}, xmm1, xmm31
vmovsh xmm2{k2}{z}, xmm15, xmm0
vmovsh xmm2{k2}{z}, xmm15, xmm1
vmovsh xmm2{k2}{z}, xmm15, xmm15
vmovsh xmm2{k2}{z}, xmm15, xmm31
vmovsh xmm2{k2}{z}, xmm31, xmm0
vmovsh xmm2{k2}{z}, xmm31, xmm1
vmovsh xmm2{k2}{z}, xmm31, xmm15
vmovsh xmm2{k2}{z}, xmm31, xmm31
vmovsh xmm15{k7}{z}, xmm0, xmm0
vmovsh xmm15{k7}{z}, xmm0, xmm1
vmovsh xmm15{k7}{z}, xmm0, xmm15
vmovsh xmm15{k7}{z}, xmm0, xmm31
vmovsh xmm15{k7}{z}, xmm1, xmm0
vmovsh xmm15{k7}{z}, xmm1, xmm1
vmovsh xmm15{k7}{z}, xmm1, xmm15
vmovsh xmm15{k7}{z}, xmm1, xmm31
vmovsh xmm15{k7}{z}, xmm15, xmm0
vmovsh xmm15{k7}{z}, xmm15, xmm1
vmovsh xmm15{k7}{z}, xmm15, xmm15
vmovsh xmm15{k7}{z}, xmm15, xmm31
vmovsh xmm15{k7}{z}, xmm31, xmm0
vmovsh xmm15{k7}{z}, xmm31, xmm1
vmovsh xmm15{k7}{z}, xmm31, xmm15
vmovsh xmm15{k7}{z}, xmm31, xmm31