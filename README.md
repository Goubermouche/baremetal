## baremetal
- Supported instruction sets: `x64`
- Supported instruction categories: `GP`, `Crypto`, `Hash`, `System`, `FPU`, `MMX`, `SSE`
## Planned
- [ ] VEX/EVEX instructions (`AVX`, `AVX-512`, `AMX`)
- [ ] Default operand types
- [ ] Text interface
## Notes
- Some instructions have VEX and EVEX variants, we need to determine which one to use. This could be done using the context index. We'll have to categorize every instruction into specific instruction categories and extensions.
