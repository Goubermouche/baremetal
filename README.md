## baremetal
Basic assembler which (currently) supports most x64 instructions, including the AVX and AVX-512 extensions. Currently the project functions as a simple instruction translator, and doesn't provide any support for more 'complex' concepts. such as labels, hence it's not ready for actual use.

## Getting up and running
Get started by running:
```shell
# clone the repository
$ git clone https://github.com/Goubermouche/assembler.git --recursive
$ cd assembler

# generate build files using premake5 (see premake5 targets for more info)
$ premake5 gmake  

# compile the project using gmake and run tests
$ make
$ ./output/bin/tests/tests
```

## Project structure
```shell
- source       # assembler source directory
  |- assembler # source code for the assembler implementation
  `- tests     # test runners and test cases
- tools        # utilities used for managing the instruction database and tests
  `- scripts   # implementations of the utility programs
```
To achieve overall correctness, the project utilizes a variety of tests, some of which may need to be regenerated once breaking changes to the instruction database are introduced.  

> [!IMPORTANT]
>
> **baremetal** invokes [Nasm](https://www.nasm.us/) when generating instruction tests, depending on the number of instructions the test generation process may take up to 30 minutes.  
>

The following commands are intended to be used to aid the developer when manipulating the instruction database: 
```shell
./tools/regenerate.sh        # invokes the table_generator and convert_db scripts
./tools/test_generator.sh    # generates a series of instruction tests based off of the contents of ./tools/scripts/db.json
./tools/list_instructions.sh # lists statistics about the current instruction set

./tools/table_generator.sh   # regenerates database tables used by the main assembler project 
./tools/convert_db.sh        # converts ./tools/scripts/asmjit_db.json into the format used by baremetal
```

## Planned
- Labels, data segments, etc.
- Executable/binary emission 
- Optional type prefixes
- CI & GH LFS for test storage?
- Better support for memory operands with SSE registers
- Better error checking

## Grammar
```
identifier   = letter [{ letter | digit }]
type         = { byte, word, dword, qword, tword } 

immediate    = { digit, binary, hexadecimal }
relocation   = (rip) immediate

8-bit gpr    = { al, cl, dl, bl, spl, bpl, sil, dil, ah, ch, dh, bh, r8d, r9d, r10d, r11d, r12d, r13d, r14d, r15d }
16-bit gpr   = { ax, cx, dx, bx, sp, bp, si, di, r8w, r10w, r11w, r12w, r13w, r14w, r15w  }
32-bit gpr   = { eax, ecx, edx, ebx, esp, ebp, esi, edi, r8d, r9d, r10d, r11d, r12d, r13d, r14d, r15d }
64-bit gpr   = { rax, rcx, rdx, rbx, rsp, rbp, rsi, rdi, r8, r9, r10, r11, r12, r13, r14, r15 }
gpr          = { 8-bit gpr, 16-bit gpr, 32-bit gpr, 64-bit gpr }
mmx          = { mm0, mm1, mm2, mm3. mm4, mm5, mm6, mm7 }
bnd          = { bnd0, bnd1, bnd2, bnd3  }
sreg         = { es, cs, ss, ds, fs, gs  }
dreg         = { dr0, dr1, dr2, dr3, dr4, dr5, dr6, dr7 }
creg         = { cr0, cr1, cr2, cr3, cr4, cr8 }
xmm          = { xmm0 - xmm31 }
ymm          = { ymm0 - ymm31 }
zmm          = { zmm0 - zmm31 }
k            = { k0, k1, k2, k3, k4, k5, k6, k7 }
mk           = '{' k '}'
mkz          = mk '{z}'
rip          = rel $
register     = { gpr, mmx, bnd, sreg, dreg, creg } | { xmm, ymm, zmm }(mkz, mk) | { k }(mkz)

index        = register * { 1, 2, 4, 8 }
base         = register (+ relocation)
memory       = (type) '[' <relocation, index, base>  ']'

broadcast    = memory '{' { 1to1, 1to2, 1to4, 1to8, 1to16, 1to32 } '}'
moff         = '[' type immediate ']'

operand      = { immediate, relocation, register, memory, broadcast, meoff }
statement    = identifier [operand]

program      = [statement]
```

## Acknowledgements
- The original instruction database has been ported from the [AsmJit](https://asmjit.com/) project, although it has been slightly modified. 
- Massive thanks to [Martins](https://github.com/mmozeiko), ratchetfreak, codaaaaaa, and others from the [HMN](https://handmade.network/) for guiding me through the pitfalls of x86/64.

