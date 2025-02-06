; expect: c5f44ac9c5f44acac5f44acfc5ec4ac9c5ec4acac5ec4acfc5c44ac9c5c44acac5c44acfc5f44ad1c5f44ad2c5f44ad7c5ec4ad1c5ec4ad2c5ec4ad7c5c44ad1c5c44ad2c5c44ad7c5f44af9c5f44afac5f44affc5ec4af9c5ec4afac5ec4affc5c44af9c5c44afac5c44aff

bits 64

kaddw k1, k1, k1
kaddw k1, k1, k2
kaddw k1, k1, k7
kaddw k1, k2, k1
kaddw k1, k2, k2
kaddw k1, k2, k7
kaddw k1, k7, k1
kaddw k1, k7, k2
kaddw k1, k7, k7
kaddw k2, k1, k1
kaddw k2, k1, k2
kaddw k2, k1, k7
kaddw k2, k2, k1
kaddw k2, k2, k2
kaddw k2, k2, k7
kaddw k2, k7, k1
kaddw k2, k7, k2
kaddw k2, k7, k7
kaddw k7, k1, k1
kaddw k7, k1, k2
kaddw k7, k1, k7
kaddw k7, k2, k1
kaddw k7, k2, k2
kaddw k7, k2, k7
kaddw k7, k7, k1
kaddw k7, k7, k2
kaddw k7, k7, k7
