; expect: 70fe70ff0f807affffff707d0f80eeffffff0f80e9ffffff0f8062ffffff0f805b000000

bits 64

jo $+0
jo $+1
jo $+-128
jo $+127
jo 0
jo 1
jo -128
jo 127
