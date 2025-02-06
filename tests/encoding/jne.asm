; expect: 75fe75ff0f857affffff757d0f85eeffffff0f85e9ffffff0f8562ffffff0f855b000000

bits 64

jne $+0
jne $+1
jne $+-128
jne $+127
jne 0
jne 1
jne -128
jne 127
