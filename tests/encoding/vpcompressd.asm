; expect: 62f27d088bc062f27d088bc862727d088bf862627d088bf862f27d088bc162f27d088bc962727d088bf962627d088bf962d27d088bc762d27d088bcf62527d088bff62427d088bff62927d088bc762927d088bcf62127d088bff62027d088bff62f27d0c8b04250000000062f27d0c8b0c250000000062727d0c8b3c250000000062627d0c8b3c250000000062f27d288bc062f27d288bc862727d288bf862627d288bf862f27d288bc162f27d288bc962727d288bf962627d288bf962d27d288bc762d27d288bcf62527d288bff62427d288bff62927d288bc762927d288bcf62127d288bff62027d288bff62f27d2c8b04250000000062f27d2c8b0c250000000062727d2c8b3c250000000062627d2c8b3c250000000062f27d488bc062f27d488bc862727d488bf862627d488bf862f27d488bc162f27d488bc962727d488bf962627d488bf962d27d488bc762d27d488bcf62527d488bff62427d488bff62927d488bc762927d488bcf62127d488bff62027d488bff62f27d4c8b04250000000062f27d4c8b0c250000000062727d4c8b3c250000000062627d4c8b3c2500000000

bits 64

vpcompressd xmm0, xmm0
vpcompressd xmm0, xmm1
vpcompressd xmm0, xmm15
vpcompressd xmm0, xmm31
vpcompressd xmm1, xmm0
vpcompressd xmm1, xmm1
vpcompressd xmm1, xmm15
vpcompressd xmm1, xmm31
vpcompressd xmm15, xmm0
vpcompressd xmm15, xmm1
vpcompressd xmm15, xmm15
vpcompressd xmm15, xmm31
vpcompressd xmm31, xmm0
vpcompressd xmm31, xmm1
vpcompressd xmm31, xmm15
vpcompressd xmm31, xmm31
vpcompressd [0x0] {k4}, xmm0
vpcompressd [0x0] {k4}, xmm1
vpcompressd [0x0] {k4}, xmm15
vpcompressd [0x0] {k4}, xmm31
vpcompressd ymm0, ymm0
vpcompressd ymm0, ymm1
vpcompressd ymm0, ymm15
vpcompressd ymm0, ymm31
vpcompressd ymm1, ymm0
vpcompressd ymm1, ymm1
vpcompressd ymm1, ymm15
vpcompressd ymm1, ymm31
vpcompressd ymm15, ymm0
vpcompressd ymm15, ymm1
vpcompressd ymm15, ymm15
vpcompressd ymm15, ymm31
vpcompressd ymm31, ymm0
vpcompressd ymm31, ymm1
vpcompressd ymm31, ymm15
vpcompressd ymm31, ymm31
vpcompressd [0x0] {k4}, ymm0
vpcompressd [0x0] {k4}, ymm1
vpcompressd [0x0] {k4}, ymm15
vpcompressd [0x0] {k4}, ymm31
vpcompressd zmm0, zmm0
vpcompressd zmm0, zmm1
vpcompressd zmm0, zmm15
vpcompressd zmm0, zmm31
vpcompressd zmm1, zmm0
vpcompressd zmm1, zmm1
vpcompressd zmm1, zmm15
vpcompressd zmm1, zmm31
vpcompressd zmm15, zmm0
vpcompressd zmm15, zmm1
vpcompressd zmm15, zmm15
vpcompressd zmm15, zmm31
vpcompressd zmm31, zmm0
vpcompressd zmm31, zmm1
vpcompressd zmm31, zmm15
vpcompressd zmm31, zmm31
vpcompressd [0x0] {k4}, zmm0
vpcompressd [0x0] {k4}, zmm1
vpcompressd [0x0] {k4}, zmm15
vpcompressd [0x0] {k4}, zmm31
