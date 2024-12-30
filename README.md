## baremetal [![Tests (ubuntu-latest)](https://github.com/Goubermouche/baremetal/actions/workflows/test_ubuntu.yml/badge.svg?branch=main)](https://github.com/Goubermouche/baremetal/actions/workflows/test_ubuntu.yml)

Basic x64 assembler which currently supports the majority of x64 instructions, including pretty much all extensions as specified by the [Intel® 64 and IA-32 Architectures Software Developer’s Manual](https://cdrdv2.intel.com/v1/dl/getContent/671200). Additionally, it also supports out-of-order definition with optimal instruction selection (pretty much 1-to-1 with [Nasm](https://www.nasm.us/)), as well as labels, and memory defines. 

## Getting up and running
Get started by running:
```shell
# clone the repository
$ git clone https://github.com/Goubermouche/baremetal.git --recursive
$ cd baremetal

# generate build files using premake5 (see premake5 targets for more info)
$ premake5 gmake  

# compile the project using gmake and run tests
$ make
$ ./output/bin/test_runner/test_runner
```
You can find some basic examples in the [test directory](https://github.com/Goubermouche/baremetal/tree/f21bfa1933c139f4e8e275ac94fbe9d71f0cb09f/source/test_runner/tests/binary).

## Supported passes
### Optimization
- CFG analysis
- Instruction size minimization
- Symbollic size minimiazation

### Emission
- Binary emission (.bin)
- CFG emission (Graphviz)

## Project structure
```
- source         # assembler source directory
  |- assembler   # source code for the assembler implementation
  `- test_runner # test runners and test cases
- tools          # utilities used for managing the instruction database and tests
  `- scripts     # implementations of the utility programs
```
To achieve overall correctness, the project utilizes a variety of tests, some of which may need to be regenerated once breaking changes to the instruction database are introduced.  

> [!IMPORTANT]
>
> **baremetal** invokes [Nasm](https://www.nasm.us/) when generating encoding tests, depending on the number of instructions the test generation process may take up to 30 minutes.  
>

The following commands are intended to be used to aid the developer when manipulating the instruction database: 
```shell
./tools/regenerate.sh        # invokes the table_generator and convert_db scripts
./tools/test_generator.sh    # generates a series of instruction tests based off of the contents of ./tools/scripts/db.json
./tools/list_instructions.sh # lists statistics about the current instruction set

./tools/table_generator.sh   # regenerates database tables used by the main baremetal project 
./tools/convert_db.sh        # converts ./tools/scripts/asmjit_db.json into the format used by baremetal
```

## Planned
- Executable/Object file emission
- Optional type prefixes
- Better support for memory operands with SSE registers
- Better error checking

## Acknowledgements
- The original instruction database has been ported from the [AsmJit](https://asmjit.com/) project, although it has been slightly modified. 
- Massive thanks to [Martins](https://github.com/mmozeiko), ratchetfreak, codaaaaaa, and others from the [HMN](https://handmade.network/) for guiding me through the pitfalls of x86/64.

