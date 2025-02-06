; expect: 62f27e0825c062f27e0825c862727e0825f862627e0825f862f27e0825c162f27e0825c962727e0825f962627e0825f962d27e0825c762d27e0825cf62527e0825ff62427e0825ff62927e0825c762927e0825cf62127e0825ff62027e0825ff62f27e0c2504250000000062f27e0c250c250000000062727e0c253c250000000062627e0c253c250000000062f27e2825c062f27e2825c862727e2825f862627e2825f862f27e2825c162f27e2825c962727e2825f962627e2825f962d27e2825c762d27e2825cf62527e2825ff62427e2825ff62927e2825c762927e2825cf62127e2825ff62027e2825ff62f27e2c2504250000000062f27e2c250c250000000062727e2c253c250000000062627e2c253c250000000062f27e4825c062f27e4825c862727e4825f862627e4825f862f27e4825c162f27e4825c962727e4825f962627e4825f962d27e4825c762d27e4825cf62527e4825ff62427e4825ff62927e4825c762927e4825cf62127e4825ff62027e4825ff62f27e4c2504250000000062f27e4c250c250000000062727e4c253c250000000062627e4c253c2500000000

bits 64

vpmovsqd xmm0, xmm0
vpmovsqd xmm0, xmm1
vpmovsqd xmm0, xmm15
vpmovsqd xmm0, xmm31
vpmovsqd xmm1, xmm0
vpmovsqd xmm1, xmm1
vpmovsqd xmm1, xmm15
vpmovsqd xmm1, xmm31
vpmovsqd xmm15, xmm0
vpmovsqd xmm15, xmm1
vpmovsqd xmm15, xmm15
vpmovsqd xmm15, xmm31
vpmovsqd xmm31, xmm0
vpmovsqd xmm31, xmm1
vpmovsqd xmm31, xmm15
vpmovsqd xmm31, xmm31
vpmovsqd [0x0] {k4}, xmm0
vpmovsqd [0x0] {k4}, xmm1
vpmovsqd [0x0] {k4}, xmm15
vpmovsqd [0x0] {k4}, xmm31
vpmovsqd xmm0, ymm0
vpmovsqd xmm0, ymm1
vpmovsqd xmm0, ymm15
vpmovsqd xmm0, ymm31
vpmovsqd xmm1, ymm0
vpmovsqd xmm1, ymm1
vpmovsqd xmm1, ymm15
vpmovsqd xmm1, ymm31
vpmovsqd xmm15, ymm0
vpmovsqd xmm15, ymm1
vpmovsqd xmm15, ymm15
vpmovsqd xmm15, ymm31
vpmovsqd xmm31, ymm0
vpmovsqd xmm31, ymm1
vpmovsqd xmm31, ymm15
vpmovsqd xmm31, ymm31
vpmovsqd [0x0] {k4}, ymm0
vpmovsqd [0x0] {k4}, ymm1
vpmovsqd [0x0] {k4}, ymm15
vpmovsqd [0x0] {k4}, ymm31
vpmovsqd ymm0, zmm0
vpmovsqd ymm0, zmm1
vpmovsqd ymm0, zmm15
vpmovsqd ymm0, zmm31
vpmovsqd ymm1, zmm0
vpmovsqd ymm1, zmm1
vpmovsqd ymm1, zmm15
vpmovsqd ymm1, zmm31
vpmovsqd ymm15, zmm0
vpmovsqd ymm15, zmm1
vpmovsqd ymm15, zmm15
vpmovsqd ymm15, zmm31
vpmovsqd ymm31, zmm0
vpmovsqd ymm31, zmm1
vpmovsqd ymm31, zmm15
vpmovsqd ymm31, zmm31
vpmovsqd [0x0] {k4}, zmm0
vpmovsqd [0x0] {k4}, zmm1
vpmovsqd [0x0] {k4}, zmm15
vpmovsqd [0x0] {k4}, zmm31
