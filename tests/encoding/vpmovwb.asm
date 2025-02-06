; expect: 62f27e0830c062f27e0830c862727e0830f862627e0830f862f27e0830c162f27e0830c962727e0830f962627e0830f962d27e0830c762d27e0830cf62527e0830ff62427e0830ff62927e0830c762927e0830cf62127e0830ff62027e0830ff62f27e0c3004250000000062f27e0c300c250000000062727e0c303c250000000062627e0c303c250000000062f27e2830c062f27e2830c862727e2830f862627e2830f862f27e2830c162f27e2830c962727e2830f962627e2830f962d27e2830c762d27e2830cf62527e2830ff62427e2830ff62927e2830c762927e2830cf62127e2830ff62027e2830ff62f27e2c3004250000000062f27e2c300c250000000062727e2c303c250000000062627e2c303c250000000062f27e4830c062f27e4830c862727e4830f862627e4830f862f27e4830c162f27e4830c962727e4830f962627e4830f962d27e4830c762d27e4830cf62527e4830ff62427e4830ff62927e4830c762927e4830cf62127e4830ff62027e4830ff62f27e4c3004250000000062f27e4c300c250000000062727e4c303c250000000062627e4c303c2500000000

bits 64

vpmovwb xmm0, xmm0
vpmovwb xmm0, xmm1
vpmovwb xmm0, xmm15
vpmovwb xmm0, xmm31
vpmovwb xmm1, xmm0
vpmovwb xmm1, xmm1
vpmovwb xmm1, xmm15
vpmovwb xmm1, xmm31
vpmovwb xmm15, xmm0
vpmovwb xmm15, xmm1
vpmovwb xmm15, xmm15
vpmovwb xmm15, xmm31
vpmovwb xmm31, xmm0
vpmovwb xmm31, xmm1
vpmovwb xmm31, xmm15
vpmovwb xmm31, xmm31
vpmovwb [0x0] {k4}, xmm0
vpmovwb [0x0] {k4}, xmm1
vpmovwb [0x0] {k4}, xmm15
vpmovwb [0x0] {k4}, xmm31
vpmovwb xmm0, ymm0
vpmovwb xmm0, ymm1
vpmovwb xmm0, ymm15
vpmovwb xmm0, ymm31
vpmovwb xmm1, ymm0
vpmovwb xmm1, ymm1
vpmovwb xmm1, ymm15
vpmovwb xmm1, ymm31
vpmovwb xmm15, ymm0
vpmovwb xmm15, ymm1
vpmovwb xmm15, ymm15
vpmovwb xmm15, ymm31
vpmovwb xmm31, ymm0
vpmovwb xmm31, ymm1
vpmovwb xmm31, ymm15
vpmovwb xmm31, ymm31
vpmovwb [0x0] {k4}, ymm0
vpmovwb [0x0] {k4}, ymm1
vpmovwb [0x0] {k4}, ymm15
vpmovwb [0x0] {k4}, ymm31
vpmovwb ymm0, zmm0
vpmovwb ymm0, zmm1
vpmovwb ymm0, zmm15
vpmovwb ymm0, zmm31
vpmovwb ymm1, zmm0
vpmovwb ymm1, zmm1
vpmovwb ymm1, zmm15
vpmovwb ymm1, zmm31
vpmovwb ymm15, zmm0
vpmovwb ymm15, zmm1
vpmovwb ymm15, zmm15
vpmovwb ymm15, zmm31
vpmovwb ymm31, zmm0
vpmovwb ymm31, zmm1
vpmovwb ymm31, zmm15
vpmovwb ymm31, zmm31
vpmovwb [0x0] {k4}, zmm0
vpmovwb [0x0] {k4}, zmm1
vpmovwb [0x0] {k4}, zmm15
vpmovwb [0x0] {k4}, zmm31
