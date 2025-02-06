; expect: 72fe72ff0f827affffff727d0f82eeffffff0f82e9ffffff0f8262ffffff0f825b000000

bits 64

jb $+0
jb $+1
jb $+-128
jb $+127
jb 0
jb 1
jb -128
jb 127
