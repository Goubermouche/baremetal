; expect: 62f27e0820c062f27e0820c862727e0820f862627e0820f862f27e0820c162f27e0820c962727e0820f962627e0820f962d27e0820c762d27e0820cf62527e0820ff62427e0820ff62927e0820c762927e0820cf62127e0820ff62027e0820ff62f27e0c2004250000000062f27e0c200c250000000062727e0c203c250000000062627e0c203c250000000062f27e2820c062f27e2820c862727e2820f862627e2820f862f27e2820c162f27e2820c962727e2820f962627e2820f962d27e2820c762d27e2820cf62527e2820ff62427e2820ff62927e2820c762927e2820cf62127e2820ff62027e2820ff62f27e2c2004250000000062f27e2c200c250000000062727e2c203c250000000062627e2c203c250000000062f27e4820c062f27e4820c862727e4820f862627e4820f862f27e4820c162f27e4820c962727e4820f962627e4820f962d27e4820c762d27e4820cf62527e4820ff62427e4820ff62927e4820c762927e4820cf62127e4820ff62027e4820ff62f27e4c2004250000000062f27e4c200c250000000062727e4c203c250000000062627e4c203c2500000000

bits 64

vpmovswb xmm0, xmm0
vpmovswb xmm0, xmm1
vpmovswb xmm0, xmm15
vpmovswb xmm0, xmm31
vpmovswb xmm1, xmm0
vpmovswb xmm1, xmm1
vpmovswb xmm1, xmm15
vpmovswb xmm1, xmm31
vpmovswb xmm15, xmm0
vpmovswb xmm15, xmm1
vpmovswb xmm15, xmm15
vpmovswb xmm15, xmm31
vpmovswb xmm31, xmm0
vpmovswb xmm31, xmm1
vpmovswb xmm31, xmm15
vpmovswb xmm31, xmm31
vpmovswb [0x0] {k4}, xmm0
vpmovswb [0x0] {k4}, xmm1
vpmovswb [0x0] {k4}, xmm15
vpmovswb [0x0] {k4}, xmm31
vpmovswb xmm0, ymm0
vpmovswb xmm0, ymm1
vpmovswb xmm0, ymm15
vpmovswb xmm0, ymm31
vpmovswb xmm1, ymm0
vpmovswb xmm1, ymm1
vpmovswb xmm1, ymm15
vpmovswb xmm1, ymm31
vpmovswb xmm15, ymm0
vpmovswb xmm15, ymm1
vpmovswb xmm15, ymm15
vpmovswb xmm15, ymm31
vpmovswb xmm31, ymm0
vpmovswb xmm31, ymm1
vpmovswb xmm31, ymm15
vpmovswb xmm31, ymm31
vpmovswb [0x0] {k4}, ymm0
vpmovswb [0x0] {k4}, ymm1
vpmovswb [0x0] {k4}, ymm15
vpmovswb [0x0] {k4}, ymm31
vpmovswb ymm0, zmm0
vpmovswb ymm0, zmm1
vpmovswb ymm0, zmm15
vpmovswb ymm0, zmm31
vpmovswb ymm1, zmm0
vpmovswb ymm1, zmm1
vpmovswb ymm1, zmm15
vpmovswb ymm1, zmm31
vpmovswb ymm15, zmm0
vpmovswb ymm15, zmm1
vpmovswb ymm15, zmm15
vpmovswb ymm15, zmm31
vpmovswb ymm31, zmm0
vpmovswb ymm31, zmm1
vpmovswb ymm31, zmm15
vpmovswb ymm31, zmm31
vpmovswb [0x0] {k4}, zmm0
vpmovswb [0x0] {k4}, zmm1
vpmovswb [0x0] {k4}, zmm15
vpmovswb [0x0] {k4}, zmm31
