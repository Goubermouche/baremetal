; expect: 7afe7aff0f8a7affffff7a7d0f8aeeffffff0f8ae9ffffff0f8a62ffffff0f8a5b000000

bits 64

jpe $+0
jpe $+1
jpe $+-128
jpe $+127
jpe 0
jpe 1
jpe -128
jpe 127
