; expect: 62f27e0833c062f27e0833c862727e0833f862627e0833f862f27e0833c162f27e0833c962727e0833f962627e0833f962d27e0833c762d27e0833cf62527e0833ff62427e0833ff62927e0833c762927e0833cf62127e0833ff62027e0833ff62f27e0c3304250000000062f27e0c330c250000000062727e0c333c250000000062627e0c333c250000000062f27e2833c062f27e2833c862727e2833f862627e2833f862f27e2833c162f27e2833c962727e2833f962627e2833f962d27e2833c762d27e2833cf62527e2833ff62427e2833ff62927e2833c762927e2833cf62127e2833ff62027e2833ff62f27e2c3304250000000062f27e2c330c250000000062727e2c333c250000000062627e2c333c250000000062f27e4833c062f27e4833c862727e4833f862627e4833f862f27e4833c162f27e4833c962727e4833f962627e4833f962d27e4833c762d27e4833cf62527e4833ff62427e4833ff62927e4833c762927e4833cf62127e4833ff62027e4833ff62f27e4c3304250000000062f27e4c330c250000000062727e4c333c250000000062627e4c333c2500000000

bits 64

vpmovdw xmm0, xmm0
vpmovdw xmm0, xmm1
vpmovdw xmm0, xmm15
vpmovdw xmm0, xmm31
vpmovdw xmm1, xmm0
vpmovdw xmm1, xmm1
vpmovdw xmm1, xmm15
vpmovdw xmm1, xmm31
vpmovdw xmm15, xmm0
vpmovdw xmm15, xmm1
vpmovdw xmm15, xmm15
vpmovdw xmm15, xmm31
vpmovdw xmm31, xmm0
vpmovdw xmm31, xmm1
vpmovdw xmm31, xmm15
vpmovdw xmm31, xmm31
vpmovdw [0x0] {k4}, xmm0
vpmovdw [0x0] {k4}, xmm1
vpmovdw [0x0] {k4}, xmm15
vpmovdw [0x0] {k4}, xmm31
vpmovdw xmm0, ymm0
vpmovdw xmm0, ymm1
vpmovdw xmm0, ymm15
vpmovdw xmm0, ymm31
vpmovdw xmm1, ymm0
vpmovdw xmm1, ymm1
vpmovdw xmm1, ymm15
vpmovdw xmm1, ymm31
vpmovdw xmm15, ymm0
vpmovdw xmm15, ymm1
vpmovdw xmm15, ymm15
vpmovdw xmm15, ymm31
vpmovdw xmm31, ymm0
vpmovdw xmm31, ymm1
vpmovdw xmm31, ymm15
vpmovdw xmm31, ymm31
vpmovdw [0x0] {k4}, ymm0
vpmovdw [0x0] {k4}, ymm1
vpmovdw [0x0] {k4}, ymm15
vpmovdw [0x0] {k4}, ymm31
vpmovdw ymm0, zmm0
vpmovdw ymm0, zmm1
vpmovdw ymm0, zmm15
vpmovdw ymm0, zmm31
vpmovdw ymm1, zmm0
vpmovdw ymm1, zmm1
vpmovdw ymm1, zmm15
vpmovdw ymm1, zmm31
vpmovdw ymm15, zmm0
vpmovdw ymm15, zmm1
vpmovdw ymm15, zmm15
vpmovdw ymm15, zmm31
vpmovdw ymm31, zmm0
vpmovdw ymm31, zmm1
vpmovdw ymm31, zmm15
vpmovdw ymm31, zmm31
vpmovdw [0x0] {k4}, zmm0
vpmovdw [0x0] {k4}, zmm1
vpmovdw [0x0] {k4}, zmm15
vpmovdw [0x0] {k4}, zmm31
