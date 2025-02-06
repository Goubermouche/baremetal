; expect: 79fe79ff0f897affffff797d0f89eeffffff0f89e9ffffff0f8962ffffff0f895b000000

bits 64

jns $+0
jns $+1
jns $+-128
jns $+127
jns 0
jns 1
jns -128
jns 127
