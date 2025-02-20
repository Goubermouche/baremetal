; expect: 62f3fd481bc00062f3fd481bc00162f3fd481bc00a62f3fd481bc06462f3fd481bc07f62f3fd481bc08062f3fd481bc80062f3fd481bc80162f3fd481bc80a62f3fd481bc86462f3fd481bc87f62f3fd481bc8806273fd481bf8006273fd481bf8016273fd481bf80a6273fd481bf8646273fd481bf87f6273fd481bf8806263fd481bf8006263fd481bf8016263fd481bf80a6263fd481bf8646263fd481bf87f6263fd481bf88062f3fd481bc10062f3fd481bc10162f3fd481bc10a62f3fd481bc16462f3fd481bc17f62f3fd481bc18062f3fd481bc90062f3fd481bc90162f3fd481bc90a62f3fd481bc96462f3fd481bc97f62f3fd481bc9806273fd481bf9006273fd481bf9016273fd481bf90a6273fd481bf9646273fd481bf97f6273fd481bf9806263fd481bf9006263fd481bf9016263fd481bf90a6263fd481bf9646263fd481bf97f6263fd481bf98062d3fd481bc70062d3fd481bc70162d3fd481bc70a62d3fd481bc76462d3fd481bc77f62d3fd481bc78062d3fd481bcf0062d3fd481bcf0162d3fd481bcf0a62d3fd481bcf6462d3fd481bcf7f62d3fd481bcf806253fd481bff006253fd481bff016253fd481bff0a6253fd481bff646253fd481bff7f6253fd481bff806243fd481bff006243fd481bff016243fd481bff0a6243fd481bff646243fd481bff7f6243fd481bff806293fd481bc7006293fd481bc7016293fd481bc70a6293fd481bc7646293fd481bc77f6293fd481bc7806293fd481bcf006293fd481bcf016293fd481bcf0a6293fd481bcf646293fd481bcf7f6293fd481bcf806213fd481bff006213fd481bff016213fd481bff0a6213fd481bff646213fd481bff7f6213fd481bff806203fd481bff006203fd481bff016203fd481bff0a6203fd481bff646203fd481bff7f6203fd481bff8062f3fd4c1b0425000000000062f3fd4c1b0425000000000162f3fd4c1b0425000000000a62f3fd4c1b0425000000006462f3fd4c1b0425000000007f62f3fd4c1b0425000000008062f3fd4c1b0c25000000000062f3fd4c1b0c25000000000162f3fd4c1b0c25000000000a62f3fd4c1b0c25000000006462f3fd4c1b0c25000000007f62f3fd4c1b0c2500000000806273fd4c1b3c2500000000006273fd4c1b3c2500000000016273fd4c1b3c25000000000a6273fd4c1b3c2500000000646273fd4c1b3c25000000007f6273fd4c1b3c2500000000806263fd4c1b3c2500000000006263fd4c1b3c2500000000016263fd4c1b3c25000000000a6263fd4c1b3c2500000000646263fd4c1b3c25000000007f6263fd4c1b3c250000000080

bits 64

vextractf64x4 ymm0, zmm0, 0
vextractf64x4 ymm0, zmm0, 1
vextractf64x4 ymm0, zmm0, 10
vextractf64x4 ymm0, zmm0, 100
vextractf64x4 ymm0, zmm0, 127
vextractf64x4 ymm0, zmm0, -128
vextractf64x4 ymm0, zmm1, 0
vextractf64x4 ymm0, zmm1, 1
vextractf64x4 ymm0, zmm1, 10
vextractf64x4 ymm0, zmm1, 100
vextractf64x4 ymm0, zmm1, 127
vextractf64x4 ymm0, zmm1, -128
vextractf64x4 ymm0, zmm15, 0
vextractf64x4 ymm0, zmm15, 1
vextractf64x4 ymm0, zmm15, 10
vextractf64x4 ymm0, zmm15, 100
vextractf64x4 ymm0, zmm15, 127
vextractf64x4 ymm0, zmm15, -128
vextractf64x4 ymm0, zmm31, 0
vextractf64x4 ymm0, zmm31, 1
vextractf64x4 ymm0, zmm31, 10
vextractf64x4 ymm0, zmm31, 100
vextractf64x4 ymm0, zmm31, 127
vextractf64x4 ymm0, zmm31, -128
vextractf64x4 ymm1, zmm0, 0
vextractf64x4 ymm1, zmm0, 1
vextractf64x4 ymm1, zmm0, 10
vextractf64x4 ymm1, zmm0, 100
vextractf64x4 ymm1, zmm0, 127
vextractf64x4 ymm1, zmm0, -128
vextractf64x4 ymm1, zmm1, 0
vextractf64x4 ymm1, zmm1, 1
vextractf64x4 ymm1, zmm1, 10
vextractf64x4 ymm1, zmm1, 100
vextractf64x4 ymm1, zmm1, 127
vextractf64x4 ymm1, zmm1, -128
vextractf64x4 ymm1, zmm15, 0
vextractf64x4 ymm1, zmm15, 1
vextractf64x4 ymm1, zmm15, 10
vextractf64x4 ymm1, zmm15, 100
vextractf64x4 ymm1, zmm15, 127
vextractf64x4 ymm1, zmm15, -128
vextractf64x4 ymm1, zmm31, 0
vextractf64x4 ymm1, zmm31, 1
vextractf64x4 ymm1, zmm31, 10
vextractf64x4 ymm1, zmm31, 100
vextractf64x4 ymm1, zmm31, 127
vextractf64x4 ymm1, zmm31, -128
vextractf64x4 ymm15, zmm0, 0
vextractf64x4 ymm15, zmm0, 1
vextractf64x4 ymm15, zmm0, 10
vextractf64x4 ymm15, zmm0, 100
vextractf64x4 ymm15, zmm0, 127
vextractf64x4 ymm15, zmm0, -128
vextractf64x4 ymm15, zmm1, 0
vextractf64x4 ymm15, zmm1, 1
vextractf64x4 ymm15, zmm1, 10
vextractf64x4 ymm15, zmm1, 100
vextractf64x4 ymm15, zmm1, 127
vextractf64x4 ymm15, zmm1, -128
vextractf64x4 ymm15, zmm15, 0
vextractf64x4 ymm15, zmm15, 1
vextractf64x4 ymm15, zmm15, 10
vextractf64x4 ymm15, zmm15, 100
vextractf64x4 ymm15, zmm15, 127
vextractf64x4 ymm15, zmm15, -128
vextractf64x4 ymm15, zmm31, 0
vextractf64x4 ymm15, zmm31, 1
vextractf64x4 ymm15, zmm31, 10
vextractf64x4 ymm15, zmm31, 100
vextractf64x4 ymm15, zmm31, 127
vextractf64x4 ymm15, zmm31, -128
vextractf64x4 ymm31, zmm0, 0
vextractf64x4 ymm31, zmm0, 1
vextractf64x4 ymm31, zmm0, 10
vextractf64x4 ymm31, zmm0, 100
vextractf64x4 ymm31, zmm0, 127
vextractf64x4 ymm31, zmm0, -128
vextractf64x4 ymm31, zmm1, 0
vextractf64x4 ymm31, zmm1, 1
vextractf64x4 ymm31, zmm1, 10
vextractf64x4 ymm31, zmm1, 100
vextractf64x4 ymm31, zmm1, 127
vextractf64x4 ymm31, zmm1, -128
vextractf64x4 ymm31, zmm15, 0
vextractf64x4 ymm31, zmm15, 1
vextractf64x4 ymm31, zmm15, 10
vextractf64x4 ymm31, zmm15, 100
vextractf64x4 ymm31, zmm15, 127
vextractf64x4 ymm31, zmm15, -128
vextractf64x4 ymm31, zmm31, 0
vextractf64x4 ymm31, zmm31, 1
vextractf64x4 ymm31, zmm31, 10
vextractf64x4 ymm31, zmm31, 100
vextractf64x4 ymm31, zmm31, 127
vextractf64x4 ymm31, zmm31, -128
vextractf64x4 [0x0] {k4}, zmm0, 0
vextractf64x4 [0x0] {k4}, zmm0, 1
vextractf64x4 [0x0] {k4}, zmm0, 10
vextractf64x4 [0x0] {k4}, zmm0, 100
vextractf64x4 [0x0] {k4}, zmm0, 127
vextractf64x4 [0x0] {k4}, zmm0, -128
vextractf64x4 [0x0] {k4}, zmm1, 0
vextractf64x4 [0x0] {k4}, zmm1, 1
vextractf64x4 [0x0] {k4}, zmm1, 10
vextractf64x4 [0x0] {k4}, zmm1, 100
vextractf64x4 [0x0] {k4}, zmm1, 127
vextractf64x4 [0x0] {k4}, zmm1, -128
vextractf64x4 [0x0] {k4}, zmm15, 0
vextractf64x4 [0x0] {k4}, zmm15, 1
vextractf64x4 [0x0] {k4}, zmm15, 10
vextractf64x4 [0x0] {k4}, zmm15, 100
vextractf64x4 [0x0] {k4}, zmm15, 127
vextractf64x4 [0x0] {k4}, zmm15, -128
vextractf64x4 [0x0] {k4}, zmm31, 0
vextractf64x4 [0x0] {k4}, zmm31, 1
vextractf64x4 [0x0] {k4}, zmm31, 10
vextractf64x4 [0x0] {k4}, zmm31, 100
vextractf64x4 [0x0] {k4}, zmm31, 127
vextractf64x4 [0x0] {k4}, zmm31, -128
