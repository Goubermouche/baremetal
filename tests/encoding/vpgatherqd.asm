; expect: c4e27991040d00000000c4e27191040d00000000c4e20191040d00000000c4e279910c0d00000000c4e271910c0d00000000c4e201910c0d00000000c46279913c0d00000000c46271913c0d00000000c46201913c0d00000000c4e27d91040d00000000c4e27591040d00000000c4e20591040d00000000c4e27d910c0d00000000c4e275910c0d00000000c4e205910c0d00000000c4627d913c0d00000000c46275913c0d00000000c46205913c0d0000000062f27d09910c0d0000000062f27d0a91140d0000000062727d0f913c0d0000000062f27d29910c0d0000000062f27d2a91140d0000000062727d2f913c0d0000000062f27d49910c0d0000000062f27d4a91140d0000000062727d4f913c0d00000000

bits 64

vpgatherqd xmm0, [xmm1], xmm0
vpgatherqd xmm0, [xmm1], xmm1
vpgatherqd xmm0, [xmm1], xmm15
vpgatherqd xmm1, [xmm1], xmm0
vpgatherqd xmm1, [xmm1], xmm1
vpgatherqd xmm1, [xmm1], xmm15
vpgatherqd xmm15, [xmm1], xmm0
vpgatherqd xmm15, [xmm1], xmm1
vpgatherqd xmm15, [xmm1], xmm15
vpgatherqd xmm0, [ymm1], xmm0
vpgatherqd xmm0, [ymm1], xmm1
vpgatherqd xmm0, [ymm1], xmm15
vpgatherqd xmm1, [ymm1], xmm0
vpgatherqd xmm1, [ymm1], xmm1
vpgatherqd xmm1, [ymm1], xmm15
vpgatherqd xmm15, [ymm1], xmm0
vpgatherqd xmm15, [ymm1], xmm1
vpgatherqd xmm15, [ymm1], xmm15
vpgatherqd xmm1{k1}, [xmm1]
vpgatherqd xmm2{k2}, [xmm1]
vpgatherqd xmm15{k7}, [xmm1]
vpgatherqd xmm1{k1}, [ymm1]
vpgatherqd xmm2{k2}, [ymm1]
vpgatherqd xmm15{k7}, [ymm1]
vpgatherqd ymm1{k1}, [zmm1]
vpgatherqd ymm2{k2}, [zmm1]
vpgatherqd ymm15{k7}, [zmm1]
