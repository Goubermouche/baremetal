; expect: 75fe75ff0f857affffff757d0f85eeffffff0f85e9ffffff0f8562ffffff0f855b000000

bits 64

jnz $+0
jnz $+1
jnz $+-128
jnz $+127
jnz 0
jnz 1
jnz -128
jnz 127
