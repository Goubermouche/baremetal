; expect: 62f27e0811c062f27e0811c862727e0811f862627e0811f862f27e0811c162f27e0811c962727e0811f962627e0811f962d27e0811c762d27e0811cf62527e0811ff62427e0811ff62927e0811c762927e0811cf62127e0811ff62027e0811ff62f27e0c1104250000000062f27e0c110c250000000062727e0c113c250000000062627e0c113c250000000062f27e2811c062f27e2811c862727e2811f862627e2811f862f27e2811c162f27e2811c962727e2811f962627e2811f962d27e2811c762d27e2811cf62527e2811ff62427e2811ff62927e2811c762927e2811cf62127e2811ff62027e2811ff62f27e2c1104250000000062f27e2c110c250000000062727e2c113c250000000062627e2c113c250000000062f27e4811c062f27e4811c862727e4811f862627e4811f862f27e4811c162f27e4811c962727e4811f962627e4811f962d27e4811c762d27e4811cf62527e4811ff62427e4811ff62927e4811c762927e4811cf62127e4811ff62027e4811ff62f27e4c1104250000000062f27e4c110c250000000062727e4c113c250000000062627e4c113c2500000000

bits 64

vpmovusdb xmm0, xmm0
vpmovusdb xmm0, xmm1
vpmovusdb xmm0, xmm15
vpmovusdb xmm0, xmm31
vpmovusdb xmm1, xmm0
vpmovusdb xmm1, xmm1
vpmovusdb xmm1, xmm15
vpmovusdb xmm1, xmm31
vpmovusdb xmm15, xmm0
vpmovusdb xmm15, xmm1
vpmovusdb xmm15, xmm15
vpmovusdb xmm15, xmm31
vpmovusdb xmm31, xmm0
vpmovusdb xmm31, xmm1
vpmovusdb xmm31, xmm15
vpmovusdb xmm31, xmm31
vpmovusdb [0x0] {k4}, xmm0
vpmovusdb [0x0] {k4}, xmm1
vpmovusdb [0x0] {k4}, xmm15
vpmovusdb [0x0] {k4}, xmm31
vpmovusdb xmm0, ymm0
vpmovusdb xmm0, ymm1
vpmovusdb xmm0, ymm15
vpmovusdb xmm0, ymm31
vpmovusdb xmm1, ymm0
vpmovusdb xmm1, ymm1
vpmovusdb xmm1, ymm15
vpmovusdb xmm1, ymm31
vpmovusdb xmm15, ymm0
vpmovusdb xmm15, ymm1
vpmovusdb xmm15, ymm15
vpmovusdb xmm15, ymm31
vpmovusdb xmm31, ymm0
vpmovusdb xmm31, ymm1
vpmovusdb xmm31, ymm15
vpmovusdb xmm31, ymm31
vpmovusdb [0x0] {k4}, ymm0
vpmovusdb [0x0] {k4}, ymm1
vpmovusdb [0x0] {k4}, ymm15
vpmovusdb [0x0] {k4}, ymm31
vpmovusdb xmm0, zmm0
vpmovusdb xmm0, zmm1
vpmovusdb xmm0, zmm15
vpmovusdb xmm0, zmm31
vpmovusdb xmm1, zmm0
vpmovusdb xmm1, zmm1
vpmovusdb xmm1, zmm15
vpmovusdb xmm1, zmm31
vpmovusdb xmm15, zmm0
vpmovusdb xmm15, zmm1
vpmovusdb xmm15, zmm15
vpmovusdb xmm15, zmm31
vpmovusdb xmm31, zmm0
vpmovusdb xmm31, zmm1
vpmovusdb xmm31, zmm15
vpmovusdb xmm31, zmm31
vpmovusdb [0x0] {k4}, zmm0
vpmovusdb [0x0] {k4}, zmm1
vpmovusdb [0x0] {k4}, zmm15
vpmovusdb [0x0] {k4}, zmm31
