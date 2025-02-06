; expect: 62f27e0834c062f27e0834c862727e0834f862627e0834f862f27e0834c162f27e0834c962727e0834f962627e0834f962d27e0834c762d27e0834cf62527e0834ff62427e0834ff62927e0834c762927e0834cf62127e0834ff62027e0834ff62f27e0c3404250000000062f27e0c340c250000000062727e0c343c250000000062627e0c343c250000000062f27e2834c062f27e2834c862727e2834f862627e2834f862f27e2834c162f27e2834c962727e2834f962627e2834f962d27e2834c762d27e2834cf62527e2834ff62427e2834ff62927e2834c762927e2834cf62127e2834ff62027e2834ff62f27e2c3404250000000062f27e2c340c250000000062727e2c343c250000000062627e2c343c250000000062f27e4834c062f27e4834c862727e4834f862627e4834f862f27e4834c162f27e4834c962727e4834f962627e4834f962d27e4834c762d27e4834cf62527e4834ff62427e4834ff62927e4834c762927e4834cf62127e4834ff62027e4834ff62f27e4c3404250000000062f27e4c340c250000000062727e4c343c250000000062627e4c343c2500000000

bits 64

vpmovqw xmm0, xmm0
vpmovqw xmm0, xmm1
vpmovqw xmm0, xmm15
vpmovqw xmm0, xmm31
vpmovqw xmm1, xmm0
vpmovqw xmm1, xmm1
vpmovqw xmm1, xmm15
vpmovqw xmm1, xmm31
vpmovqw xmm15, xmm0
vpmovqw xmm15, xmm1
vpmovqw xmm15, xmm15
vpmovqw xmm15, xmm31
vpmovqw xmm31, xmm0
vpmovqw xmm31, xmm1
vpmovqw xmm31, xmm15
vpmovqw xmm31, xmm31
vpmovqw [0x0] {k4}, xmm0
vpmovqw [0x0] {k4}, xmm1
vpmovqw [0x0] {k4}, xmm15
vpmovqw [0x0] {k4}, xmm31
vpmovqw xmm0, ymm0
vpmovqw xmm0, ymm1
vpmovqw xmm0, ymm15
vpmovqw xmm0, ymm31
vpmovqw xmm1, ymm0
vpmovqw xmm1, ymm1
vpmovqw xmm1, ymm15
vpmovqw xmm1, ymm31
vpmovqw xmm15, ymm0
vpmovqw xmm15, ymm1
vpmovqw xmm15, ymm15
vpmovqw xmm15, ymm31
vpmovqw xmm31, ymm0
vpmovqw xmm31, ymm1
vpmovqw xmm31, ymm15
vpmovqw xmm31, ymm31
vpmovqw [0x0] {k4}, ymm0
vpmovqw [0x0] {k4}, ymm1
vpmovqw [0x0] {k4}, ymm15
vpmovqw [0x0] {k4}, ymm31
vpmovqw xmm0, zmm0
vpmovqw xmm0, zmm1
vpmovqw xmm0, zmm15
vpmovqw xmm0, zmm31
vpmovqw xmm1, zmm0
vpmovqw xmm1, zmm1
vpmovqw xmm1, zmm15
vpmovqw xmm1, zmm31
vpmovqw xmm15, zmm0
vpmovqw xmm15, zmm1
vpmovqw xmm15, zmm15
vpmovqw xmm15, zmm31
vpmovqw xmm31, zmm0
vpmovqw xmm31, zmm1
vpmovqw xmm31, zmm15
vpmovqw xmm31, zmm31
vpmovqw [0x0] {k4}, zmm0
vpmovqw [0x0] {k4}, zmm1
vpmovqw [0x0] {k4}, zmm15
vpmovqw [0x0] {k4}, zmm31
