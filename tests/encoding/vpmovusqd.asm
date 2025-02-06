; expect: 62f27e0815c062f27e0815c862727e0815f862627e0815f862f27e0815c162f27e0815c962727e0815f962627e0815f962d27e0815c762d27e0815cf62527e0815ff62427e0815ff62927e0815c762927e0815cf62127e0815ff62027e0815ff62f27e0c1504250000000062f27e0c150c250000000062727e0c153c250000000062627e0c153c250000000062f27e2815c062f27e2815c862727e2815f862627e2815f862f27e2815c162f27e2815c962727e2815f962627e2815f962d27e2815c762d27e2815cf62527e2815ff62427e2815ff62927e2815c762927e2815cf62127e2815ff62027e2815ff62f27e2c1504250000000062f27e2c150c250000000062727e2c153c250000000062627e2c153c250000000062f27e4815c062f27e4815c862727e4815f862627e4815f862f27e4815c162f27e4815c962727e4815f962627e4815f962d27e4815c762d27e4815cf62527e4815ff62427e4815ff62927e4815c762927e4815cf62127e4815ff62027e4815ff62f27e4c1504250000000062f27e4c150c250000000062727e4c153c250000000062627e4c153c2500000000

bits 64

vpmovusqd xmm0, xmm0
vpmovusqd xmm0, xmm1
vpmovusqd xmm0, xmm15
vpmovusqd xmm0, xmm31
vpmovusqd xmm1, xmm0
vpmovusqd xmm1, xmm1
vpmovusqd xmm1, xmm15
vpmovusqd xmm1, xmm31
vpmovusqd xmm15, xmm0
vpmovusqd xmm15, xmm1
vpmovusqd xmm15, xmm15
vpmovusqd xmm15, xmm31
vpmovusqd xmm31, xmm0
vpmovusqd xmm31, xmm1
vpmovusqd xmm31, xmm15
vpmovusqd xmm31, xmm31
vpmovusqd [0x0] {k4}, xmm0
vpmovusqd [0x0] {k4}, xmm1
vpmovusqd [0x0] {k4}, xmm15
vpmovusqd [0x0] {k4}, xmm31
vpmovusqd xmm0, ymm0
vpmovusqd xmm0, ymm1
vpmovusqd xmm0, ymm15
vpmovusqd xmm0, ymm31
vpmovusqd xmm1, ymm0
vpmovusqd xmm1, ymm1
vpmovusqd xmm1, ymm15
vpmovusqd xmm1, ymm31
vpmovusqd xmm15, ymm0
vpmovusqd xmm15, ymm1
vpmovusqd xmm15, ymm15
vpmovusqd xmm15, ymm31
vpmovusqd xmm31, ymm0
vpmovusqd xmm31, ymm1
vpmovusqd xmm31, ymm15
vpmovusqd xmm31, ymm31
vpmovusqd [0x0] {k4}, ymm0
vpmovusqd [0x0] {k4}, ymm1
vpmovusqd [0x0] {k4}, ymm15
vpmovusqd [0x0] {k4}, ymm31
vpmovusqd ymm0, zmm0
vpmovusqd ymm0, zmm1
vpmovusqd ymm0, zmm15
vpmovusqd ymm0, zmm31
vpmovusqd ymm1, zmm0
vpmovusqd ymm1, zmm1
vpmovusqd ymm1, zmm15
vpmovusqd ymm1, zmm31
vpmovusqd ymm15, zmm0
vpmovusqd ymm15, zmm1
vpmovusqd ymm15, zmm15
vpmovusqd ymm15, zmm31
vpmovusqd ymm31, zmm0
vpmovusqd ymm31, zmm1
vpmovusqd ymm31, zmm15
vpmovusqd ymm31, zmm31
vpmovusqd [0x0] {k4}, zmm0
vpmovusqd [0x0] {k4}, zmm1
vpmovusqd [0x0] {k4}, zmm15
vpmovusqd [0x0] {k4}, zmm31
