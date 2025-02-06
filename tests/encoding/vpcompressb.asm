; expect: 62f27d0863c062f27d0863c862727d0863f862627d0863f862f27d0863c162f27d0863c962727d0863f962627d0863f962d27d0863c762d27d0863cf62527d0863ff62427d0863ff62927d0863c762927d0863cf62127d0863ff62027d0863ff62f27d0c6304250000000062f27d0c630c250000000062727d0c633c250000000062627d0c633c250000000062f27d2863c062f27d2863c862727d2863f862627d2863f862f27d2863c162f27d2863c962727d2863f962627d2863f962d27d2863c762d27d2863cf62527d2863ff62427d2863ff62927d2863c762927d2863cf62127d2863ff62027d2863ff62f27d2c6304250000000062f27d2c630c250000000062727d2c633c250000000062627d2c633c250000000062f27d4863c062f27d4863c862727d4863f862627d4863f862f27d4863c162f27d4863c962727d4863f962627d4863f962d27d4863c762d27d4863cf62527d4863ff62427d4863ff62927d4863c762927d4863cf62127d4863ff62027d4863ff62f27d4c6304250000000062f27d4c630c250000000062727d4c633c250000000062627d4c633c2500000000

bits 64

vpcompressb xmm0, xmm0
vpcompressb xmm0, xmm1
vpcompressb xmm0, xmm15
vpcompressb xmm0, xmm31
vpcompressb xmm1, xmm0
vpcompressb xmm1, xmm1
vpcompressb xmm1, xmm15
vpcompressb xmm1, xmm31
vpcompressb xmm15, xmm0
vpcompressb xmm15, xmm1
vpcompressb xmm15, xmm15
vpcompressb xmm15, xmm31
vpcompressb xmm31, xmm0
vpcompressb xmm31, xmm1
vpcompressb xmm31, xmm15
vpcompressb xmm31, xmm31
vpcompressb [0x0] {k4}, xmm0
vpcompressb [0x0] {k4}, xmm1
vpcompressb [0x0] {k4}, xmm15
vpcompressb [0x0] {k4}, xmm31
vpcompressb ymm0, ymm0
vpcompressb ymm0, ymm1
vpcompressb ymm0, ymm15
vpcompressb ymm0, ymm31
vpcompressb ymm1, ymm0
vpcompressb ymm1, ymm1
vpcompressb ymm1, ymm15
vpcompressb ymm1, ymm31
vpcompressb ymm15, ymm0
vpcompressb ymm15, ymm1
vpcompressb ymm15, ymm15
vpcompressb ymm15, ymm31
vpcompressb ymm31, ymm0
vpcompressb ymm31, ymm1
vpcompressb ymm31, ymm15
vpcompressb ymm31, ymm31
vpcompressb [0x0] {k4}, ymm0
vpcompressb [0x0] {k4}, ymm1
vpcompressb [0x0] {k4}, ymm15
vpcompressb [0x0] {k4}, ymm31
vpcompressb zmm0, zmm0
vpcompressb zmm0, zmm1
vpcompressb zmm0, zmm15
vpcompressb zmm0, zmm31
vpcompressb zmm1, zmm0
vpcompressb zmm1, zmm1
vpcompressb zmm1, zmm15
vpcompressb zmm1, zmm31
vpcompressb zmm15, zmm0
vpcompressb zmm15, zmm1
vpcompressb zmm15, zmm15
vpcompressb zmm15, zmm31
vpcompressb zmm31, zmm0
vpcompressb zmm31, zmm1
vpcompressb zmm31, zmm15
vpcompressb zmm31, zmm31
vpcompressb [0x0] {k4}, zmm0
vpcompressb [0x0] {k4}, zmm1
vpcompressb [0x0] {k4}, zmm15
vpcompressb [0x0] {k4}, zmm31
