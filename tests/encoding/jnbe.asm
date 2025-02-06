; expect: 77fe77ff0f877affffff777d0f87eeffffff0f87e9ffffff0f8762ffffff0f875b000000

bits 64

jnbe $+0
jnbe $+1
jnbe $+-128
jnbe $+127
jnbe 0
jnbe 1
jnbe -128
jnbe 127
