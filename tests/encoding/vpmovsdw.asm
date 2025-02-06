; expect: 62f27e0823c062f27e0823c862727e0823f862627e0823f862f27e0823c162f27e0823c962727e0823f962627e0823f962d27e0823c762d27e0823cf62527e0823ff62427e0823ff62927e0823c762927e0823cf62127e0823ff62027e0823ff62f27e0c2304250000000062f27e0c230c250000000062727e0c233c250000000062627e0c233c250000000062f27e2823c062f27e2823c862727e2823f862627e2823f862f27e2823c162f27e2823c962727e2823f962627e2823f962d27e2823c762d27e2823cf62527e2823ff62427e2823ff62927e2823c762927e2823cf62127e2823ff62027e2823ff62f27e2c2304250000000062f27e2c230c250000000062727e2c233c250000000062627e2c233c250000000062f27e4823c062f27e4823c862727e4823f862627e4823f862f27e4823c162f27e4823c962727e4823f962627e4823f962d27e4823c762d27e4823cf62527e4823ff62427e4823ff62927e4823c762927e4823cf62127e4823ff62027e4823ff62f27e4c2304250000000062f27e4c230c250000000062727e4c233c250000000062627e4c233c2500000000

bits 64

vpmovsdw xmm0, xmm0
vpmovsdw xmm0, xmm1
vpmovsdw xmm0, xmm15
vpmovsdw xmm0, xmm31
vpmovsdw xmm1, xmm0
vpmovsdw xmm1, xmm1
vpmovsdw xmm1, xmm15
vpmovsdw xmm1, xmm31
vpmovsdw xmm15, xmm0
vpmovsdw xmm15, xmm1
vpmovsdw xmm15, xmm15
vpmovsdw xmm15, xmm31
vpmovsdw xmm31, xmm0
vpmovsdw xmm31, xmm1
vpmovsdw xmm31, xmm15
vpmovsdw xmm31, xmm31
vpmovsdw [0x0] {k4}, xmm0
vpmovsdw [0x0] {k4}, xmm1
vpmovsdw [0x0] {k4}, xmm15
vpmovsdw [0x0] {k4}, xmm31
vpmovsdw xmm0, ymm0
vpmovsdw xmm0, ymm1
vpmovsdw xmm0, ymm15
vpmovsdw xmm0, ymm31
vpmovsdw xmm1, ymm0
vpmovsdw xmm1, ymm1
vpmovsdw xmm1, ymm15
vpmovsdw xmm1, ymm31
vpmovsdw xmm15, ymm0
vpmovsdw xmm15, ymm1
vpmovsdw xmm15, ymm15
vpmovsdw xmm15, ymm31
vpmovsdw xmm31, ymm0
vpmovsdw xmm31, ymm1
vpmovsdw xmm31, ymm15
vpmovsdw xmm31, ymm31
vpmovsdw [0x0] {k4}, ymm0
vpmovsdw [0x0] {k4}, ymm1
vpmovsdw [0x0] {k4}, ymm15
vpmovsdw [0x0] {k4}, ymm31
vpmovsdw ymm0, zmm0
vpmovsdw ymm0, zmm1
vpmovsdw ymm0, zmm15
vpmovsdw ymm0, zmm31
vpmovsdw ymm1, zmm0
vpmovsdw ymm1, zmm1
vpmovsdw ymm1, zmm15
vpmovsdw ymm1, zmm31
vpmovsdw ymm15, zmm0
vpmovsdw ymm15, zmm1
vpmovsdw ymm15, zmm15
vpmovsdw ymm15, zmm31
vpmovsdw ymm31, zmm0
vpmovsdw ymm31, zmm1
vpmovsdw ymm31, zmm15
vpmovsdw ymm31, zmm31
vpmovsdw [0x0] {k4}, zmm0
vpmovsdw [0x0] {k4}, zmm1
vpmovsdw [0x0] {k4}, zmm15
vpmovsdw [0x0] {k4}, zmm31
