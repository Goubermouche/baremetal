; expect: c5f547c9c5f547cac5f547cfc5ed47c9c5ed47cac5ed47cfc5c547c9c5c547cac5c547cfc5f547d1c5f547d2c5f547d7c5ed47d1c5ed47d2c5ed47d7c5c547d1c5c547d2c5c547d7c5f547f9c5f547fac5f547ffc5ed47f9c5ed47fac5ed47ffc5c547f9c5c547fac5c547ff

bits 64

kxorb k1, k1, k1
kxorb k1, k1, k2
kxorb k1, k1, k7
kxorb k1, k2, k1
kxorb k1, k2, k2
kxorb k1, k2, k7
kxorb k1, k7, k1
kxorb k1, k7, k2
kxorb k1, k7, k7
kxorb k2, k1, k1
kxorb k2, k1, k2
kxorb k2, k1, k7
kxorb k2, k2, k1
kxorb k2, k2, k2
kxorb k2, k2, k7
kxorb k2, k7, k1
kxorb k2, k7, k2
kxorb k2, k7, k7
kxorb k7, k1, k1
kxorb k7, k1, k2
kxorb k7, k1, k7
kxorb k7, k2, k1
kxorb k7, k2, k2
kxorb k7, k2, k7
kxorb k7, k7, k1
kxorb k7, k7, k2
kxorb k7, k7, k7
