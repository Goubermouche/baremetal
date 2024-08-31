inst("ldmxcsr"   , ENCN_NORMAL, 0b0, 0x0FAE, 0b1000, 0b1111111111111111, OPS_64 , OPN_M32),
inst("stmxcsr"   , ENCN_NORMAL, 0b0, 0x0FAE, 0b1010, 0b1111111111111111, OPS_64 , OPN_M32),
inst("vldmxcsr"  , ENCN_VEX   , 0b0, 0x0FAE, 0b1000, 0b1111111111111111, OPS_64 , OPN_M32),
inst("vstmxcsr"  , ENCN_VEX   , 0b0, 0x0FAE, 0b1010, 0b1111111111111111, OPS_64 , OPN_M32),
inst("vzeroall"  , ENCN_VEX   , 0b0, 0x0F77, 0b0   , 0b1111111111111111, OPS_256         ),
inst("vzeroupper", ENCN_VEX   , 0b0, 0x0F77, 0b0   , 0b1111111111111111, OPS_128         ),

