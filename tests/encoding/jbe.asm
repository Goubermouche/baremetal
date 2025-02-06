; expect: 76fe76ff0f867affffff767d0f86eeffffff0f86e9ffffff0f8662ffffff0f865b000000

bits 64

jbe $+0
jbe $+1
jbe $+-128
jbe $+127
jbe 0
jbe 1
jbe -128
jbe 127
