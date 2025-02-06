; expect: 660ff7c0660ff7c166410ff7c7660ff7c8660ff7c966410ff7cf66440ff7f866440ff7f966450ff7ff

bits 64

maskmovdqu xmm0, xmm0
maskmovdqu xmm0, xmm1
maskmovdqu xmm0, xmm15
maskmovdqu xmm1, xmm0
maskmovdqu xmm1, xmm1
maskmovdqu xmm1, xmm15
maskmovdqu xmm15, xmm0
maskmovdqu xmm15, xmm1
maskmovdqu xmm15, xmm15
