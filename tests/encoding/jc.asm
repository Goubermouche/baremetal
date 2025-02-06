; expect: 72fe72ff0f827affffff727d0f82eeffffff0f82e9ffffff0f8262ffffff0f825b000000

bits 64

jc $+0
jc $+1
jc $+-128
jc $+127
jc 0
jc 1
jc -128
jc 127
