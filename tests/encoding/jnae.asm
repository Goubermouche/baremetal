; expect: 72fe72ff0f827affffff727d0f82eeffffff0f82e9ffffff0f8262ffffff0f825b000000

bits 64

jnae $+0
jnae $+1
jnae $+-128
jnae $+127
jnae 0
jnae 1
jnae -128
jnae 127
