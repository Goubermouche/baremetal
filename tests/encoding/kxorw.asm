; expect: c5f447c9c5f447cac5f447cfc5ec47c9c5ec47cac5ec47cfc5c447c9c5c447cac5c447cfc5f447d1c5f447d2c5f447d7c5ec47d1c5ec47d2c5ec47d7c5c447d1c5c447d2c5c447d7c5f447f9c5f447fac5f447ffc5ec47f9c5ec47fac5ec47ffc5c447f9c5c447fac5c447ff

bits 64

kxorw k1, k1, k1
kxorw k1, k1, k2
kxorw k1, k1, k7
kxorw k1, k2, k1
kxorw k1, k2, k2
kxorw k1, k2, k7
kxorw k1, k7, k1
kxorw k1, k7, k2
kxorw k1, k7, k7
kxorw k2, k1, k1
kxorw k2, k1, k2
kxorw k2, k1, k7
kxorw k2, k2, k1
kxorw k2, k2, k2
kxorw k2, k2, k7
kxorw k2, k7, k1
kxorw k2, k7, k2
kxorw k2, k7, k7
kxorw k7, k1, k1
kxorw k7, k1, k2
kxorw k7, k1, k7
kxorw k7, k2, k1
kxorw k7, k2, k2
kxorw k7, k2, k7
kxorw k7, k7, k1
kxorw k7, k7, k2
kxorw k7, k7, k7
