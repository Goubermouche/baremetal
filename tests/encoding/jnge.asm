; expect: 7cfe7cff0f8c7affffff7c7d0f8ceeffffff0f8ce9ffffff0f8c62ffffff0f8c5b000000

bits 64

jnge $+0
jnge $+1
jnge $+-128
jnge $+127
jnge 0
jnge 1
jnge -128
jnge 127
