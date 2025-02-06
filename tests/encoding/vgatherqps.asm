; expect: c4e27993040d00000000c4e27193040d00000000c4e20193040d00000000c4e279930c0d00000000c4e271930c0d00000000c4e201930c0d00000000c46279933c0d00000000c46271933c0d00000000c46201933c0d00000000c4e27d93040d00000000c4e27593040d00000000c4e20593040d00000000c4e27d930c0d00000000c4e275930c0d00000000c4e205930c0d00000000c4627d933c0d00000000c46275933c0d00000000c46205933c0d0000000062f27d09930c0d0000000062f27d0a93140d0000000062727d0f933c0d0000000062f27d29930c0d0000000062f27d2a93140d0000000062727d2f933c0d0000000062f27d49930c0d0000000062f27d4a93140d0000000062727d4f933c0d00000000

bits 64

vgatherqps xmm0, [xmm1], xmm0
vgatherqps xmm0, [xmm1], xmm1
vgatherqps xmm0, [xmm1], xmm15
vgatherqps xmm1, [xmm1], xmm0
vgatherqps xmm1, [xmm1], xmm1
vgatherqps xmm1, [xmm1], xmm15
vgatherqps xmm15, [xmm1], xmm0
vgatherqps xmm15, [xmm1], xmm1
vgatherqps xmm15, [xmm1], xmm15
vgatherqps xmm0, [ymm1], xmm0
vgatherqps xmm0, [ymm1], xmm1
vgatherqps xmm0, [ymm1], xmm15
vgatherqps xmm1, [ymm1], xmm0
vgatherqps xmm1, [ymm1], xmm1
vgatherqps xmm1, [ymm1], xmm15
vgatherqps xmm15, [ymm1], xmm0
vgatherqps xmm15, [ymm1], xmm1
vgatherqps xmm15, [ymm1], xmm15
vgatherqps xmm1{k1}, [xmm1]
vgatherqps xmm2{k2}, [xmm1]
vgatherqps xmm15{k7}, [xmm1]
vgatherqps xmm1{k1}, [ymm1]
vgatherqps xmm2{k2}, [ymm1]
vgatherqps xmm15{k7}, [ymm1]
vgatherqps ymm1{k1}, [zmm1]
vgatherqps ymm2{k2}, [zmm1]
vgatherqps ymm15{k7}, [zmm1]
