## baremetal
- Basic assembler which (currently) supports most x64 instructions, including the AVX and AVX-512 extensions. Currently the project functions as a simple instruction translator, and doesn't provide any support for more 'complex' concepts. such as labels, hence it's not ready for actual use.

## Planned
- PUSH instructions and support for default operand sizes
- Labels, data segments, etc.
- CI & GH LFS for test storage?
- Better support for memory operands with SSE registers
- Better error checking

## Acknowledgements
- The original instruction database has been ported from the [AsmJit](https://asmjit.com/) project, although it has been slightly modified. 
- Massive thanks to [Martins](https://github.com/mmozeiko), ratchetfreak, codaaaaaa, and others from the [HMN](https://handmade.network/) for guiding me through the pitfalls of x86/64.

