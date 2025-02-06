; expect: 76fe76ff0f867affffff767d0f86eeffffff0f86e9ffffff0f8662ffffff0f865b000000

bits 64

jna $+0
jna $+1
jna $+-128
jna $+127
jna 0
jna 1
jna -128
jna 127
