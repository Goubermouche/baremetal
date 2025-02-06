; expect: c5f9d7c8c5f9d7c9c4c179d7cfc5f9d7d8c5f9d7d9c4c179d7dfc579d7f8c579d7f9c44179d7ffc5fdd7c8c5fdd7c9c4c17dd7cfc5fdd7d8c5fdd7d9c4c17dd7dfc57dd7f8c57dd7f9c4417dd7ff

bits 64

vpmovmskb ecx, xmm0
vpmovmskb ecx, xmm1
vpmovmskb ecx, xmm15
vpmovmskb ebx, xmm0
vpmovmskb ebx, xmm1
vpmovmskb ebx, xmm15
vpmovmskb r15d, xmm0
vpmovmskb r15d, xmm1
vpmovmskb r15d, xmm15
vpmovmskb ecx, ymm0
vpmovmskb ecx, ymm1
vpmovmskb ecx, ymm15
vpmovmskb ebx, ymm0
vpmovmskb ebx, ymm1
vpmovmskb ebx, ymm15
vpmovmskb r15d, ymm0
vpmovmskb r15d, ymm1
vpmovmskb r15d, ymm15
