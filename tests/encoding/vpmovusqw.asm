; expect: 62f27e0814c062f27e0814c862727e0814f862627e0814f862f27e0814c162f27e0814c962727e0814f962627e0814f962d27e0814c762d27e0814cf62527e0814ff62427e0814ff62927e0814c762927e0814cf62127e0814ff62027e0814ff62f27e0c1404250000000062f27e0c140c250000000062727e0c143c250000000062627e0c143c250000000062f27e2814c062f27e2814c862727e2814f862627e2814f862f27e2814c162f27e2814c962727e2814f962627e2814f962d27e2814c762d27e2814cf62527e2814ff62427e2814ff62927e2814c762927e2814cf62127e2814ff62027e2814ff62f27e2c1404250000000062f27e2c140c250000000062727e2c143c250000000062627e2c143c250000000062f27e4814c062f27e4814c862727e4814f862627e4814f862f27e4814c162f27e4814c962727e4814f962627e4814f962d27e4814c762d27e4814cf62527e4814ff62427e4814ff62927e4814c762927e4814cf62127e4814ff62027e4814ff62f27e4c1404250000000062f27e4c140c250000000062727e4c143c250000000062627e4c143c2500000000

bits 64

vpmovusqw xmm0, xmm0
vpmovusqw xmm0, xmm1
vpmovusqw xmm0, xmm15
vpmovusqw xmm0, xmm31
vpmovusqw xmm1, xmm0
vpmovusqw xmm1, xmm1
vpmovusqw xmm1, xmm15
vpmovusqw xmm1, xmm31
vpmovusqw xmm15, xmm0
vpmovusqw xmm15, xmm1
vpmovusqw xmm15, xmm15
vpmovusqw xmm15, xmm31
vpmovusqw xmm31, xmm0
vpmovusqw xmm31, xmm1
vpmovusqw xmm31, xmm15
vpmovusqw xmm31, xmm31
vpmovusqw [0x0] {k4}, xmm0
vpmovusqw [0x0] {k4}, xmm1
vpmovusqw [0x0] {k4}, xmm15
vpmovusqw [0x0] {k4}, xmm31
vpmovusqw xmm0, ymm0
vpmovusqw xmm0, ymm1
vpmovusqw xmm0, ymm15
vpmovusqw xmm0, ymm31
vpmovusqw xmm1, ymm0
vpmovusqw xmm1, ymm1
vpmovusqw xmm1, ymm15
vpmovusqw xmm1, ymm31
vpmovusqw xmm15, ymm0
vpmovusqw xmm15, ymm1
vpmovusqw xmm15, ymm15
vpmovusqw xmm15, ymm31
vpmovusqw xmm31, ymm0
vpmovusqw xmm31, ymm1
vpmovusqw xmm31, ymm15
vpmovusqw xmm31, ymm31
vpmovusqw [0x0] {k4}, ymm0
vpmovusqw [0x0] {k4}, ymm1
vpmovusqw [0x0] {k4}, ymm15
vpmovusqw [0x0] {k4}, ymm31
vpmovusqw xmm0, zmm0
vpmovusqw xmm0, zmm1
vpmovusqw xmm0, zmm15
vpmovusqw xmm0, zmm31
vpmovusqw xmm1, zmm0
vpmovusqw xmm1, zmm1
vpmovusqw xmm1, zmm15
vpmovusqw xmm1, zmm31
vpmovusqw xmm15, zmm0
vpmovusqw xmm15, zmm1
vpmovusqw xmm15, zmm15
vpmovusqw xmm15, zmm31
vpmovusqw xmm31, zmm0
vpmovusqw xmm31, zmm1
vpmovusqw xmm31, zmm15
vpmovusqw xmm31, zmm31
vpmovusqw [0x0] {k4}, zmm0
vpmovusqw [0x0] {k4}, zmm1
vpmovusqw [0x0] {k4}, zmm15
vpmovusqw [0x0] {k4}, zmm31
