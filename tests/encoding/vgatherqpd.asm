; expect: c4e2f993040d00000000c4e2f193040d00000000c4e28193040d00000000c4e2f9930c0d00000000c4e2f1930c0d00000000c4e281930c0d00000000c462f9933c0d00000000c462f1933c0d00000000c46281933c0d00000000c4e2fd93040d00000000c4e2f593040d00000000c4e28593040d00000000c4e2fd930c0d00000000c4e2f5930c0d00000000c4e285930c0d00000000c462fd933c0d00000000c462f5933c0d00000000c46285933c0d0000000062f2fd09930c0d0000000062f2fd0a93140d000000006272fd0f933c0d0000000062f2fd29930c0d0000000062f2fd2a93140d000000006272fd2f933c0d0000000062f2fd49930c0d0000000062f2fd4a93140d000000006272fd4f933c0d00000000

bits 64

vgatherqpd xmm0, [xmm1], xmm0
vgatherqpd xmm0, [xmm1], xmm1
vgatherqpd xmm0, [xmm1], xmm15
vgatherqpd xmm1, [xmm1], xmm0
vgatherqpd xmm1, [xmm1], xmm1
vgatherqpd xmm1, [xmm1], xmm15
vgatherqpd xmm15, [xmm1], xmm0
vgatherqpd xmm15, [xmm1], xmm1
vgatherqpd xmm15, [xmm1], xmm15
vgatherqpd ymm0, [ymm1], ymm0
vgatherqpd ymm0, [ymm1], ymm1
vgatherqpd ymm0, [ymm1], ymm15
vgatherqpd ymm1, [ymm1], ymm0
vgatherqpd ymm1, [ymm1], ymm1
vgatherqpd ymm1, [ymm1], ymm15
vgatherqpd ymm15, [ymm1], ymm0
vgatherqpd ymm15, [ymm1], ymm1
vgatherqpd ymm15, [ymm1], ymm15
vgatherqpd xmm1{k1}, [xmm1]
vgatherqpd xmm2{k2}, [xmm1]
vgatherqpd xmm15{k7}, [xmm1]
vgatherqpd ymm1{k1}, [ymm1]
vgatherqpd ymm2{k2}, [ymm1]
vgatherqpd ymm15{k7}, [ymm1]
vgatherqpd zmm1{k1}, [zmm1]
vgatherqpd zmm2{k2}, [zmm1]
vgatherqpd zmm15{k7}, [zmm1]
