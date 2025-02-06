; expect: 62f27e0822c062f27e0822c862727e0822f862627e0822f862f27e0822c162f27e0822c962727e0822f962627e0822f962d27e0822c762d27e0822cf62527e0822ff62427e0822ff62927e0822c762927e0822cf62127e0822ff62027e0822ff62f27e0c2204250000000062f27e0c220c250000000062727e0c223c250000000062627e0c223c250000000062f27e2822c062f27e2822c862727e2822f862627e2822f862f27e2822c162f27e2822c962727e2822f962627e2822f962d27e2822c762d27e2822cf62527e2822ff62427e2822ff62927e2822c762927e2822cf62127e2822ff62027e2822ff62f27e2c2204250000000062f27e2c220c250000000062727e2c223c250000000062627e2c223c250000000062f27e4822c062f27e4822c862727e4822f862627e4822f862f27e4822c162f27e4822c962727e4822f962627e4822f962d27e4822c762d27e4822cf62527e4822ff62427e4822ff62927e4822c762927e4822cf62127e4822ff62027e4822ff62f27e4c2204250000000062f27e4c220c250000000062727e4c223c250000000062627e4c223c2500000000

bits 64

vpmovsqb xmm0, xmm0
vpmovsqb xmm0, xmm1
vpmovsqb xmm0, xmm15
vpmovsqb xmm0, xmm31
vpmovsqb xmm1, xmm0
vpmovsqb xmm1, xmm1
vpmovsqb xmm1, xmm15
vpmovsqb xmm1, xmm31
vpmovsqb xmm15, xmm0
vpmovsqb xmm15, xmm1
vpmovsqb xmm15, xmm15
vpmovsqb xmm15, xmm31
vpmovsqb xmm31, xmm0
vpmovsqb xmm31, xmm1
vpmovsqb xmm31, xmm15
vpmovsqb xmm31, xmm31
vpmovsqb [0x0] {k4}, xmm0
vpmovsqb [0x0] {k4}, xmm1
vpmovsqb [0x0] {k4}, xmm15
vpmovsqb [0x0] {k4}, xmm31
vpmovsqb xmm0, ymm0
vpmovsqb xmm0, ymm1
vpmovsqb xmm0, ymm15
vpmovsqb xmm0, ymm31
vpmovsqb xmm1, ymm0
vpmovsqb xmm1, ymm1
vpmovsqb xmm1, ymm15
vpmovsqb xmm1, ymm31
vpmovsqb xmm15, ymm0
vpmovsqb xmm15, ymm1
vpmovsqb xmm15, ymm15
vpmovsqb xmm15, ymm31
vpmovsqb xmm31, ymm0
vpmovsqb xmm31, ymm1
vpmovsqb xmm31, ymm15
vpmovsqb xmm31, ymm31
vpmovsqb [0x0] {k4}, ymm0
vpmovsqb [0x0] {k4}, ymm1
vpmovsqb [0x0] {k4}, ymm15
vpmovsqb [0x0] {k4}, ymm31
vpmovsqb xmm0, zmm0
vpmovsqb xmm0, zmm1
vpmovsqb xmm0, zmm15
vpmovsqb xmm0, zmm31
vpmovsqb xmm1, zmm0
vpmovsqb xmm1, zmm1
vpmovsqb xmm1, zmm15
vpmovsqb xmm1, zmm31
vpmovsqb xmm15, zmm0
vpmovsqb xmm15, zmm1
vpmovsqb xmm15, zmm15
vpmovsqb xmm15, zmm31
vpmovsqb xmm31, zmm0
vpmovsqb xmm31, zmm1
vpmovsqb xmm31, zmm15
vpmovsqb xmm31, zmm31
vpmovsqb [0x0] {k4}, zmm0
vpmovsqb [0x0] {k4}, zmm1
vpmovsqb [0x0] {k4}, zmm15
vpmovsqb [0x0] {k4}, zmm31
