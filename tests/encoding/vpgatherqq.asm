; expect: c4e2f991040d00000000c4e2f191040d00000000c4e28191040d00000000c4e2f9910c0d00000000c4e2f1910c0d00000000c4e281910c0d00000000c462f9913c0d00000000c462f1913c0d00000000c46281913c0d00000000c4e2fd91040d00000000c4e2f591040d00000000c4e28591040d00000000c4e2fd910c0d00000000c4e2f5910c0d00000000c4e285910c0d00000000c462fd913c0d00000000c462f5913c0d00000000c46285913c0d0000000062f2fd09910c0d0000000062f2fd0a91140d000000006272fd0f913c0d0000000062f2fd29910c0d0000000062f2fd2a91140d000000006272fd2f913c0d0000000062f2fd49910c0d0000000062f2fd4a91140d000000006272fd4f913c0d00000000

vpgatherqq xmm0, [xmm1], xmm0
vpgatherqq xmm0, [xmm1], xmm1
vpgatherqq xmm0, [xmm1], xmm15
vpgatherqq xmm1, [xmm1], xmm0
vpgatherqq xmm1, [xmm1], xmm1
vpgatherqq xmm1, [xmm1], xmm15
vpgatherqq xmm15, [xmm1], xmm0
vpgatherqq xmm15, [xmm1], xmm1
vpgatherqq xmm15, [xmm1], xmm15
vpgatherqq ymm0, [ymm1], ymm0
vpgatherqq ymm0, [ymm1], ymm1
vpgatherqq ymm0, [ymm1], ymm15
vpgatherqq ymm1, [ymm1], ymm0
vpgatherqq ymm1, [ymm1], ymm1
vpgatherqq ymm1, [ymm1], ymm15
vpgatherqq ymm15, [ymm1], ymm0
vpgatherqq ymm15, [ymm1], ymm1
vpgatherqq ymm15, [ymm1], ymm15
vpgatherqq xmm1{k1}, [xmm1]
vpgatherqq xmm2{k2}, [xmm1]
vpgatherqq xmm15{k7}, [xmm1]
vpgatherqq ymm1{k1}, [ymm1]
vpgatherqq ymm2{k2}, [ymm1]
vpgatherqq ymm15{k7}, [ymm1]
vpgatherqq zmm1{k1}, [zmm1]
vpgatherqq zmm2{k2}, [zmm1]
vpgatherqq zmm15{k7}, [zmm1]