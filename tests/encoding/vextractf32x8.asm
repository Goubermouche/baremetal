; expect: 62f37d481bc00062f37d481bc00162f37d481bc06462f37d481bc07f62f37d481bc08062f37d481bc80062f37d481bc80162f37d481bc86462f37d481bc87f62f37d481bc88062737d481bf80062737d481bf80162737d481bf86462737d481bf87f62737d481bf88062637d481bf80062637d481bf80162637d481bf86462637d481bf87f62637d481bf88062f37d481bc10062f37d481bc10162f37d481bc16462f37d481bc17f62f37d481bc18062f37d481bc90062f37d481bc90162f37d481bc96462f37d481bc97f62f37d481bc98062737d481bf90062737d481bf90162737d481bf96462737d481bf97f62737d481bf98062637d481bf90062637d481bf90162637d481bf96462637d481bf97f62637d481bf98062d37d481bc70062d37d481bc70162d37d481bc76462d37d481bc77f62d37d481bc78062d37d481bcf0062d37d481bcf0162d37d481bcf6462d37d481bcf7f62d37d481bcf8062537d481bff0062537d481bff0162537d481bff6462537d481bff7f62537d481bff8062437d481bff0062437d481bff0162437d481bff6462437d481bff7f62437d481bff8062937d481bc70062937d481bc70162937d481bc76462937d481bc77f62937d481bc78062937d481bcf0062937d481bcf0162937d481bcf6462937d481bcf7f62937d481bcf8062137d481bff0062137d481bff0162137d481bff6462137d481bff7f62137d481bff8062037d481bff0062037d481bff0162037d481bff6462037d481bff7f62037d481bff8062f37d4c1b0425000000000062f37d4c1b0425000000000162f37d4c1b0425000000006462f37d4c1b0425000000007f62f37d4c1b0425000000008062f37d4c1b0c25000000000062f37d4c1b0c25000000000162f37d4c1b0c25000000006462f37d4c1b0c25000000007f62f37d4c1b0c25000000008062737d4c1b3c25000000000062737d4c1b3c25000000000162737d4c1b3c25000000006462737d4c1b3c25000000007f62737d4c1b3c25000000008062637d4c1b3c25000000000062637d4c1b3c25000000000162637d4c1b3c25000000006462637d4c1b3c25000000007f62637d4c1b3c250000000080

bits 64

vextractf32x8 ymm0, zmm0, 0
vextractf32x8 ymm0, zmm0, 1
vextractf32x8 ymm0, zmm0, 100
vextractf32x8 ymm0, zmm0, 127
vextractf32x8 ymm0, zmm0, -128
vextractf32x8 ymm0, zmm1, 0
vextractf32x8 ymm0, zmm1, 1
vextractf32x8 ymm0, zmm1, 100
vextractf32x8 ymm0, zmm1, 127
vextractf32x8 ymm0, zmm1, -128
vextractf32x8 ymm0, zmm15, 0
vextractf32x8 ymm0, zmm15, 1
vextractf32x8 ymm0, zmm15, 100
vextractf32x8 ymm0, zmm15, 127
vextractf32x8 ymm0, zmm15, -128
vextractf32x8 ymm0, zmm31, 0
vextractf32x8 ymm0, zmm31, 1
vextractf32x8 ymm0, zmm31, 100
vextractf32x8 ymm0, zmm31, 127
vextractf32x8 ymm0, zmm31, -128
vextractf32x8 ymm1, zmm0, 0
vextractf32x8 ymm1, zmm0, 1
vextractf32x8 ymm1, zmm0, 100
vextractf32x8 ymm1, zmm0, 127
vextractf32x8 ymm1, zmm0, -128
vextractf32x8 ymm1, zmm1, 0
vextractf32x8 ymm1, zmm1, 1
vextractf32x8 ymm1, zmm1, 100
vextractf32x8 ymm1, zmm1, 127
vextractf32x8 ymm1, zmm1, -128
vextractf32x8 ymm1, zmm15, 0
vextractf32x8 ymm1, zmm15, 1
vextractf32x8 ymm1, zmm15, 100
vextractf32x8 ymm1, zmm15, 127
vextractf32x8 ymm1, zmm15, -128
vextractf32x8 ymm1, zmm31, 0
vextractf32x8 ymm1, zmm31, 1
vextractf32x8 ymm1, zmm31, 100
vextractf32x8 ymm1, zmm31, 127
vextractf32x8 ymm1, zmm31, -128
vextractf32x8 ymm15, zmm0, 0
vextractf32x8 ymm15, zmm0, 1
vextractf32x8 ymm15, zmm0, 100
vextractf32x8 ymm15, zmm0, 127
vextractf32x8 ymm15, zmm0, -128
vextractf32x8 ymm15, zmm1, 0
vextractf32x8 ymm15, zmm1, 1
vextractf32x8 ymm15, zmm1, 100
vextractf32x8 ymm15, zmm1, 127
vextractf32x8 ymm15, zmm1, -128
vextractf32x8 ymm15, zmm15, 0
vextractf32x8 ymm15, zmm15, 1
vextractf32x8 ymm15, zmm15, 100
vextractf32x8 ymm15, zmm15, 127
vextractf32x8 ymm15, zmm15, -128
vextractf32x8 ymm15, zmm31, 0
vextractf32x8 ymm15, zmm31, 1
vextractf32x8 ymm15, zmm31, 100
vextractf32x8 ymm15, zmm31, 127
vextractf32x8 ymm15, zmm31, -128
vextractf32x8 ymm31, zmm0, 0
vextractf32x8 ymm31, zmm0, 1
vextractf32x8 ymm31, zmm0, 100
vextractf32x8 ymm31, zmm0, 127
vextractf32x8 ymm31, zmm0, -128
vextractf32x8 ymm31, zmm1, 0
vextractf32x8 ymm31, zmm1, 1
vextractf32x8 ymm31, zmm1, 100
vextractf32x8 ymm31, zmm1, 127
vextractf32x8 ymm31, zmm1, -128
vextractf32x8 ymm31, zmm15, 0
vextractf32x8 ymm31, zmm15, 1
vextractf32x8 ymm31, zmm15, 100
vextractf32x8 ymm31, zmm15, 127
vextractf32x8 ymm31, zmm15, -128
vextractf32x8 ymm31, zmm31, 0
vextractf32x8 ymm31, zmm31, 1
vextractf32x8 ymm31, zmm31, 100
vextractf32x8 ymm31, zmm31, 127
vextractf32x8 ymm31, zmm31, -128
vextractf32x8 [0x0] {k4}, zmm0, 0
vextractf32x8 [0x0] {k4}, zmm0, 1
vextractf32x8 [0x0] {k4}, zmm0, 100
vextractf32x8 [0x0] {k4}, zmm0, 127
vextractf32x8 [0x0] {k4}, zmm0, -128
vextractf32x8 [0x0] {k4}, zmm1, 0
vextractf32x8 [0x0] {k4}, zmm1, 1
vextractf32x8 [0x0] {k4}, zmm1, 100
vextractf32x8 [0x0] {k4}, zmm1, 127
vextractf32x8 [0x0] {k4}, zmm1, -128
vextractf32x8 [0x0] {k4}, zmm15, 0
vextractf32x8 [0x0] {k4}, zmm15, 1
vextractf32x8 [0x0] {k4}, zmm15, 100
vextractf32x8 [0x0] {k4}, zmm15, 127
vextractf32x8 [0x0] {k4}, zmm15, -128
vextractf32x8 [0x0] {k4}, zmm31, 0
vextractf32x8 [0x0] {k4}, zmm31, 1
vextractf32x8 [0x0] {k4}, zmm31, 100
vextractf32x8 [0x0] {k4}, zmm31, 127
vextractf32x8 [0x0] {k4}, zmm31, -128
