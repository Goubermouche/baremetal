; expect: 62f27e0813c062f27e0813c862727e0813f862627e0813f862f27e0813c162f27e0813c962727e0813f962627e0813f962d27e0813c762d27e0813cf62527e0813ff62427e0813ff62927e0813c762927e0813cf62127e0813ff62027e0813ff62f27e0c1304250000000062f27e0c130c250000000062727e0c133c250000000062627e0c133c250000000062f27e2813c062f27e2813c862727e2813f862627e2813f862f27e2813c162f27e2813c962727e2813f962627e2813f962d27e2813c762d27e2813cf62527e2813ff62427e2813ff62927e2813c762927e2813cf62127e2813ff62027e2813ff62f27e2c1304250000000062f27e2c130c250000000062727e2c133c250000000062627e2c133c250000000062f27e4813c062f27e4813c862727e4813f862627e4813f862f27e4813c162f27e4813c962727e4813f962627e4813f962d27e4813c762d27e4813cf62527e4813ff62427e4813ff62927e4813c762927e4813cf62127e4813ff62027e4813ff62f27e4c1304250000000062f27e4c130c250000000062727e4c133c250000000062627e4c133c2500000000

bits 64

vpmovusdw xmm0, xmm0
vpmovusdw xmm0, xmm1
vpmovusdw xmm0, xmm15
vpmovusdw xmm0, xmm31
vpmovusdw xmm1, xmm0
vpmovusdw xmm1, xmm1
vpmovusdw xmm1, xmm15
vpmovusdw xmm1, xmm31
vpmovusdw xmm15, xmm0
vpmovusdw xmm15, xmm1
vpmovusdw xmm15, xmm15
vpmovusdw xmm15, xmm31
vpmovusdw xmm31, xmm0
vpmovusdw xmm31, xmm1
vpmovusdw xmm31, xmm15
vpmovusdw xmm31, xmm31
vpmovusdw [0x0] {k4}, xmm0
vpmovusdw [0x0] {k4}, xmm1
vpmovusdw [0x0] {k4}, xmm15
vpmovusdw [0x0] {k4}, xmm31
vpmovusdw xmm0, ymm0
vpmovusdw xmm0, ymm1
vpmovusdw xmm0, ymm15
vpmovusdw xmm0, ymm31
vpmovusdw xmm1, ymm0
vpmovusdw xmm1, ymm1
vpmovusdw xmm1, ymm15
vpmovusdw xmm1, ymm31
vpmovusdw xmm15, ymm0
vpmovusdw xmm15, ymm1
vpmovusdw xmm15, ymm15
vpmovusdw xmm15, ymm31
vpmovusdw xmm31, ymm0
vpmovusdw xmm31, ymm1
vpmovusdw xmm31, ymm15
vpmovusdw xmm31, ymm31
vpmovusdw [0x0] {k4}, ymm0
vpmovusdw [0x0] {k4}, ymm1
vpmovusdw [0x0] {k4}, ymm15
vpmovusdw [0x0] {k4}, ymm31
vpmovusdw ymm0, zmm0
vpmovusdw ymm0, zmm1
vpmovusdw ymm0, zmm15
vpmovusdw ymm0, zmm31
vpmovusdw ymm1, zmm0
vpmovusdw ymm1, zmm1
vpmovusdw ymm1, zmm15
vpmovusdw ymm1, zmm31
vpmovusdw ymm15, zmm0
vpmovusdw ymm15, zmm1
vpmovusdw ymm15, zmm15
vpmovusdw ymm15, zmm31
vpmovusdw ymm31, zmm0
vpmovusdw ymm31, zmm1
vpmovusdw ymm31, zmm15
vpmovusdw ymm31, zmm31
vpmovusdw [0x0] {k4}, zmm0
vpmovusdw [0x0] {k4}, zmm1
vpmovusdw [0x0] {k4}, zmm15
vpmovusdw [0x0] {k4}, zmm31
