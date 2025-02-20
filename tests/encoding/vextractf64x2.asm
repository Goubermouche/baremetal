; expect: 62f3fd2819c00062f3fd2819c00162f3fd2819c00a62f3fd2819c06462f3fd2819c07f62f3fd2819c08062f3fd2819c80062f3fd2819c80162f3fd2819c80a62f3fd2819c86462f3fd2819c87f62f3fd2819c8806273fd2819f8006273fd2819f8016273fd2819f80a6273fd2819f8646273fd2819f87f6273fd2819f8806263fd2819f8006263fd2819f8016263fd2819f80a6263fd2819f8646263fd2819f87f6263fd2819f88062f3fd2819c10062f3fd2819c10162f3fd2819c10a62f3fd2819c16462f3fd2819c17f62f3fd2819c18062f3fd2819c90062f3fd2819c90162f3fd2819c90a62f3fd2819c96462f3fd2819c97f62f3fd2819c9806273fd2819f9006273fd2819f9016273fd2819f90a6273fd2819f9646273fd2819f97f6273fd2819f9806263fd2819f9006263fd2819f9016263fd2819f90a6263fd2819f9646263fd2819f97f6263fd2819f98062d3fd2819c70062d3fd2819c70162d3fd2819c70a62d3fd2819c76462d3fd2819c77f62d3fd2819c78062d3fd2819cf0062d3fd2819cf0162d3fd2819cf0a62d3fd2819cf6462d3fd2819cf7f62d3fd2819cf806253fd2819ff006253fd2819ff016253fd2819ff0a6253fd2819ff646253fd2819ff7f6253fd2819ff806243fd2819ff006243fd2819ff016243fd2819ff0a6243fd2819ff646243fd2819ff7f6243fd2819ff806293fd2819c7006293fd2819c7016293fd2819c70a6293fd2819c7646293fd2819c77f6293fd2819c7806293fd2819cf006293fd2819cf016293fd2819cf0a6293fd2819cf646293fd2819cf7f6293fd2819cf806213fd2819ff006213fd2819ff016213fd2819ff0a6213fd2819ff646213fd2819ff7f6213fd2819ff806203fd2819ff006203fd2819ff016203fd2819ff0a6203fd2819ff646203fd2819ff7f6203fd2819ff8062f3fd2c190425000000000062f3fd2c190425000000000162f3fd2c190425000000000a62f3fd2c190425000000006462f3fd2c190425000000007f62f3fd2c190425000000008062f3fd2c190c25000000000062f3fd2c190c25000000000162f3fd2c190c25000000000a62f3fd2c190c25000000006462f3fd2c190c25000000007f62f3fd2c190c2500000000806273fd2c193c2500000000006273fd2c193c2500000000016273fd2c193c25000000000a6273fd2c193c2500000000646273fd2c193c25000000007f6273fd2c193c2500000000806263fd2c193c2500000000006263fd2c193c2500000000016263fd2c193c25000000000a6263fd2c193c2500000000646263fd2c193c25000000007f6263fd2c193c25000000008062f3fd4819c00062f3fd4819c00162f3fd4819c00a62f3fd4819c06462f3fd4819c07f62f3fd4819c08062f3fd4819c80062f3fd4819c80162f3fd4819c80a62f3fd4819c86462f3fd4819c87f62f3fd4819c8806273fd4819f8006273fd4819f8016273fd4819f80a6273fd4819f8646273fd4819f87f6273fd4819f8806263fd4819f8006263fd4819f8016263fd4819f80a6263fd4819f8646263fd4819f87f6263fd4819f88062f3fd4819c10062f3fd4819c10162f3fd4819c10a62f3fd4819c16462f3fd4819c17f62f3fd4819c18062f3fd4819c90062f3fd4819c90162f3fd4819c90a62f3fd4819c96462f3fd4819c97f62f3fd4819c9806273fd4819f9006273fd4819f9016273fd4819f90a6273fd4819f9646273fd4819f97f6273fd4819f9806263fd4819f9006263fd4819f9016263fd4819f90a6263fd4819f9646263fd4819f97f6263fd4819f98062d3fd4819c70062d3fd4819c70162d3fd4819c70a62d3fd4819c76462d3fd4819c77f62d3fd4819c78062d3fd4819cf0062d3fd4819cf0162d3fd4819cf0a62d3fd4819cf6462d3fd4819cf7f62d3fd4819cf806253fd4819ff006253fd4819ff016253fd4819ff0a6253fd4819ff646253fd4819ff7f6253fd4819ff806243fd4819ff006243fd4819ff016243fd4819ff0a6243fd4819ff646243fd4819ff7f6243fd4819ff806293fd4819c7006293fd4819c7016293fd4819c70a6293fd4819c7646293fd4819c77f6293fd4819c7806293fd4819cf006293fd4819cf016293fd4819cf0a6293fd4819cf646293fd4819cf7f6293fd4819cf806213fd4819ff006213fd4819ff016213fd4819ff0a6213fd4819ff646213fd4819ff7f6213fd4819ff806203fd4819ff006203fd4819ff016203fd4819ff0a6203fd4819ff646203fd4819ff7f6203fd4819ff8062f3fd4c190425000000000062f3fd4c190425000000000162f3fd4c190425000000000a62f3fd4c190425000000006462f3fd4c190425000000007f62f3fd4c190425000000008062f3fd4c190c25000000000062f3fd4c190c25000000000162f3fd4c190c25000000000a62f3fd4c190c25000000006462f3fd4c190c25000000007f62f3fd4c190c2500000000806273fd4c193c2500000000006273fd4c193c2500000000016273fd4c193c25000000000a6273fd4c193c2500000000646273fd4c193c25000000007f6273fd4c193c2500000000806263fd4c193c2500000000006263fd4c193c2500000000016263fd4c193c25000000000a6263fd4c193c2500000000646263fd4c193c25000000007f6263fd4c193c250000000080

bits 64

vextractf64x2 xmm0, ymm0, 0
vextractf64x2 xmm0, ymm0, 1
vextractf64x2 xmm0, ymm0, 10
vextractf64x2 xmm0, ymm0, 100
vextractf64x2 xmm0, ymm0, 127
vextractf64x2 xmm0, ymm0, -128
vextractf64x2 xmm0, ymm1, 0
vextractf64x2 xmm0, ymm1, 1
vextractf64x2 xmm0, ymm1, 10
vextractf64x2 xmm0, ymm1, 100
vextractf64x2 xmm0, ymm1, 127
vextractf64x2 xmm0, ymm1, -128
vextractf64x2 xmm0, ymm15, 0
vextractf64x2 xmm0, ymm15, 1
vextractf64x2 xmm0, ymm15, 10
vextractf64x2 xmm0, ymm15, 100
vextractf64x2 xmm0, ymm15, 127
vextractf64x2 xmm0, ymm15, -128
vextractf64x2 xmm0, ymm31, 0
vextractf64x2 xmm0, ymm31, 1
vextractf64x2 xmm0, ymm31, 10
vextractf64x2 xmm0, ymm31, 100
vextractf64x2 xmm0, ymm31, 127
vextractf64x2 xmm0, ymm31, -128
vextractf64x2 xmm1, ymm0, 0
vextractf64x2 xmm1, ymm0, 1
vextractf64x2 xmm1, ymm0, 10
vextractf64x2 xmm1, ymm0, 100
vextractf64x2 xmm1, ymm0, 127
vextractf64x2 xmm1, ymm0, -128
vextractf64x2 xmm1, ymm1, 0
vextractf64x2 xmm1, ymm1, 1
vextractf64x2 xmm1, ymm1, 10
vextractf64x2 xmm1, ymm1, 100
vextractf64x2 xmm1, ymm1, 127
vextractf64x2 xmm1, ymm1, -128
vextractf64x2 xmm1, ymm15, 0
vextractf64x2 xmm1, ymm15, 1
vextractf64x2 xmm1, ymm15, 10
vextractf64x2 xmm1, ymm15, 100
vextractf64x2 xmm1, ymm15, 127
vextractf64x2 xmm1, ymm15, -128
vextractf64x2 xmm1, ymm31, 0
vextractf64x2 xmm1, ymm31, 1
vextractf64x2 xmm1, ymm31, 10
vextractf64x2 xmm1, ymm31, 100
vextractf64x2 xmm1, ymm31, 127
vextractf64x2 xmm1, ymm31, -128
vextractf64x2 xmm15, ymm0, 0
vextractf64x2 xmm15, ymm0, 1
vextractf64x2 xmm15, ymm0, 10
vextractf64x2 xmm15, ymm0, 100
vextractf64x2 xmm15, ymm0, 127
vextractf64x2 xmm15, ymm0, -128
vextractf64x2 xmm15, ymm1, 0
vextractf64x2 xmm15, ymm1, 1
vextractf64x2 xmm15, ymm1, 10
vextractf64x2 xmm15, ymm1, 100
vextractf64x2 xmm15, ymm1, 127
vextractf64x2 xmm15, ymm1, -128
vextractf64x2 xmm15, ymm15, 0
vextractf64x2 xmm15, ymm15, 1
vextractf64x2 xmm15, ymm15, 10
vextractf64x2 xmm15, ymm15, 100
vextractf64x2 xmm15, ymm15, 127
vextractf64x2 xmm15, ymm15, -128
vextractf64x2 xmm15, ymm31, 0
vextractf64x2 xmm15, ymm31, 1
vextractf64x2 xmm15, ymm31, 10
vextractf64x2 xmm15, ymm31, 100
vextractf64x2 xmm15, ymm31, 127
vextractf64x2 xmm15, ymm31, -128
vextractf64x2 xmm31, ymm0, 0
vextractf64x2 xmm31, ymm0, 1
vextractf64x2 xmm31, ymm0, 10
vextractf64x2 xmm31, ymm0, 100
vextractf64x2 xmm31, ymm0, 127
vextractf64x2 xmm31, ymm0, -128
vextractf64x2 xmm31, ymm1, 0
vextractf64x2 xmm31, ymm1, 1
vextractf64x2 xmm31, ymm1, 10
vextractf64x2 xmm31, ymm1, 100
vextractf64x2 xmm31, ymm1, 127
vextractf64x2 xmm31, ymm1, -128
vextractf64x2 xmm31, ymm15, 0
vextractf64x2 xmm31, ymm15, 1
vextractf64x2 xmm31, ymm15, 10
vextractf64x2 xmm31, ymm15, 100
vextractf64x2 xmm31, ymm15, 127
vextractf64x2 xmm31, ymm15, -128
vextractf64x2 xmm31, ymm31, 0
vextractf64x2 xmm31, ymm31, 1
vextractf64x2 xmm31, ymm31, 10
vextractf64x2 xmm31, ymm31, 100
vextractf64x2 xmm31, ymm31, 127
vextractf64x2 xmm31, ymm31, -128
vextractf64x2 [0x0] {k4}, ymm0, 0
vextractf64x2 [0x0] {k4}, ymm0, 1
vextractf64x2 [0x0] {k4}, ymm0, 10
vextractf64x2 [0x0] {k4}, ymm0, 100
vextractf64x2 [0x0] {k4}, ymm0, 127
vextractf64x2 [0x0] {k4}, ymm0, -128
vextractf64x2 [0x0] {k4}, ymm1, 0
vextractf64x2 [0x0] {k4}, ymm1, 1
vextractf64x2 [0x0] {k4}, ymm1, 10
vextractf64x2 [0x0] {k4}, ymm1, 100
vextractf64x2 [0x0] {k4}, ymm1, 127
vextractf64x2 [0x0] {k4}, ymm1, -128
vextractf64x2 [0x0] {k4}, ymm15, 0
vextractf64x2 [0x0] {k4}, ymm15, 1
vextractf64x2 [0x0] {k4}, ymm15, 10
vextractf64x2 [0x0] {k4}, ymm15, 100
vextractf64x2 [0x0] {k4}, ymm15, 127
vextractf64x2 [0x0] {k4}, ymm15, -128
vextractf64x2 [0x0] {k4}, ymm31, 0
vextractf64x2 [0x0] {k4}, ymm31, 1
vextractf64x2 [0x0] {k4}, ymm31, 10
vextractf64x2 [0x0] {k4}, ymm31, 100
vextractf64x2 [0x0] {k4}, ymm31, 127
vextractf64x2 [0x0] {k4}, ymm31, -128
vextractf64x2 xmm0, zmm0, 0
vextractf64x2 xmm0, zmm0, 1
vextractf64x2 xmm0, zmm0, 10
vextractf64x2 xmm0, zmm0, 100
vextractf64x2 xmm0, zmm0, 127
vextractf64x2 xmm0, zmm0, -128
vextractf64x2 xmm0, zmm1, 0
vextractf64x2 xmm0, zmm1, 1
vextractf64x2 xmm0, zmm1, 10
vextractf64x2 xmm0, zmm1, 100
vextractf64x2 xmm0, zmm1, 127
vextractf64x2 xmm0, zmm1, -128
vextractf64x2 xmm0, zmm15, 0
vextractf64x2 xmm0, zmm15, 1
vextractf64x2 xmm0, zmm15, 10
vextractf64x2 xmm0, zmm15, 100
vextractf64x2 xmm0, zmm15, 127
vextractf64x2 xmm0, zmm15, -128
vextractf64x2 xmm0, zmm31, 0
vextractf64x2 xmm0, zmm31, 1
vextractf64x2 xmm0, zmm31, 10
vextractf64x2 xmm0, zmm31, 100
vextractf64x2 xmm0, zmm31, 127
vextractf64x2 xmm0, zmm31, -128
vextractf64x2 xmm1, zmm0, 0
vextractf64x2 xmm1, zmm0, 1
vextractf64x2 xmm1, zmm0, 10
vextractf64x2 xmm1, zmm0, 100
vextractf64x2 xmm1, zmm0, 127
vextractf64x2 xmm1, zmm0, -128
vextractf64x2 xmm1, zmm1, 0
vextractf64x2 xmm1, zmm1, 1
vextractf64x2 xmm1, zmm1, 10
vextractf64x2 xmm1, zmm1, 100
vextractf64x2 xmm1, zmm1, 127
vextractf64x2 xmm1, zmm1, -128
vextractf64x2 xmm1, zmm15, 0
vextractf64x2 xmm1, zmm15, 1
vextractf64x2 xmm1, zmm15, 10
vextractf64x2 xmm1, zmm15, 100
vextractf64x2 xmm1, zmm15, 127
vextractf64x2 xmm1, zmm15, -128
vextractf64x2 xmm1, zmm31, 0
vextractf64x2 xmm1, zmm31, 1
vextractf64x2 xmm1, zmm31, 10
vextractf64x2 xmm1, zmm31, 100
vextractf64x2 xmm1, zmm31, 127
vextractf64x2 xmm1, zmm31, -128
vextractf64x2 xmm15, zmm0, 0
vextractf64x2 xmm15, zmm0, 1
vextractf64x2 xmm15, zmm0, 10
vextractf64x2 xmm15, zmm0, 100
vextractf64x2 xmm15, zmm0, 127
vextractf64x2 xmm15, zmm0, -128
vextractf64x2 xmm15, zmm1, 0
vextractf64x2 xmm15, zmm1, 1
vextractf64x2 xmm15, zmm1, 10
vextractf64x2 xmm15, zmm1, 100
vextractf64x2 xmm15, zmm1, 127
vextractf64x2 xmm15, zmm1, -128
vextractf64x2 xmm15, zmm15, 0
vextractf64x2 xmm15, zmm15, 1
vextractf64x2 xmm15, zmm15, 10
vextractf64x2 xmm15, zmm15, 100
vextractf64x2 xmm15, zmm15, 127
vextractf64x2 xmm15, zmm15, -128
vextractf64x2 xmm15, zmm31, 0
vextractf64x2 xmm15, zmm31, 1
vextractf64x2 xmm15, zmm31, 10
vextractf64x2 xmm15, zmm31, 100
vextractf64x2 xmm15, zmm31, 127
vextractf64x2 xmm15, zmm31, -128
vextractf64x2 xmm31, zmm0, 0
vextractf64x2 xmm31, zmm0, 1
vextractf64x2 xmm31, zmm0, 10
vextractf64x2 xmm31, zmm0, 100
vextractf64x2 xmm31, zmm0, 127
vextractf64x2 xmm31, zmm0, -128
vextractf64x2 xmm31, zmm1, 0
vextractf64x2 xmm31, zmm1, 1
vextractf64x2 xmm31, zmm1, 10
vextractf64x2 xmm31, zmm1, 100
vextractf64x2 xmm31, zmm1, 127
vextractf64x2 xmm31, zmm1, -128
vextractf64x2 xmm31, zmm15, 0
vextractf64x2 xmm31, zmm15, 1
vextractf64x2 xmm31, zmm15, 10
vextractf64x2 xmm31, zmm15, 100
vextractf64x2 xmm31, zmm15, 127
vextractf64x2 xmm31, zmm15, -128
vextractf64x2 xmm31, zmm31, 0
vextractf64x2 xmm31, zmm31, 1
vextractf64x2 xmm31, zmm31, 10
vextractf64x2 xmm31, zmm31, 100
vextractf64x2 xmm31, zmm31, 127
vextractf64x2 xmm31, zmm31, -128
vextractf64x2 [0x0] {k4}, zmm0, 0
vextractf64x2 [0x0] {k4}, zmm0, 1
vextractf64x2 [0x0] {k4}, zmm0, 10
vextractf64x2 [0x0] {k4}, zmm0, 100
vextractf64x2 [0x0] {k4}, zmm0, 127
vextractf64x2 [0x0] {k4}, zmm0, -128
vextractf64x2 [0x0] {k4}, zmm1, 0
vextractf64x2 [0x0] {k4}, zmm1, 1
vextractf64x2 [0x0] {k4}, zmm1, 10
vextractf64x2 [0x0] {k4}, zmm1, 100
vextractf64x2 [0x0] {k4}, zmm1, 127
vextractf64x2 [0x0] {k4}, zmm1, -128
vextractf64x2 [0x0] {k4}, zmm15, 0
vextractf64x2 [0x0] {k4}, zmm15, 1
vextractf64x2 [0x0] {k4}, zmm15, 10
vextractf64x2 [0x0] {k4}, zmm15, 100
vextractf64x2 [0x0] {k4}, zmm15, 127
vextractf64x2 [0x0] {k4}, zmm15, -128
vextractf64x2 [0x0] {k4}, zmm31, 0
vextractf64x2 [0x0] {k4}, zmm31, 1
vextractf64x2 [0x0] {k4}, zmm31, 10
vextractf64x2 [0x0] {k4}, zmm31, 100
vextractf64x2 [0x0] {k4}, zmm31, 127
vextractf64x2 [0x0] {k4}, zmm31, -128
