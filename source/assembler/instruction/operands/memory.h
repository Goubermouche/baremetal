#pragma once
#include "assembler/instruction/operands/immediates.h"
#include "assembler/instruction/operands/registers.h"

namespace baremetal {
	struct mem {
		enum scale : u8 {
			SCALE_1 = 0b00,
			SCALE_2 = 0b01,
			SCALE_4 = 0b10,
			SCALE_8 = 0b11
		};

		// this can't be a reg64 since it can contain special registers (ie. rip)
		reg base;
		reg64 index;

		bool has_base = false;
		bool has_index = false;

		scale scale = SCALE_1;
		imm displacement;
	};

#define MEM_DECL(bit_width)                                                                                      \
  struct mem ## bit_width : mem {                                                                                \
    static auto absolute(i32 address) -> mem ## bit_width {                                                      \
      mem ## bit_width memory = {};                                                                              \
      memory.displacement = address;                                                                             \
      return memory;                                                                                             \
    }                                                                                                            \
                                                                                                                 \
  static auto ptr(struct rip base_reg, i32 offset) -> mem ## bit_width {                                         \
    mem ## bit_width memory = {};                                                                                \
    memory.base = base_reg;                                                                                      \
    memory.has_base = true;                                                                                      \
    memory.displacement = offset;                                                                                \
    return memory;                                                                                               \
  }                                                                                                              \
                                                                                                                 \
  static auto ptr(reg64 base_reg, i32 offset = 0) -> mem ## bit_width {                                          \
    mem ## bit_width memory = {};                                                                                \
    memory.base = base_reg;                                                                                      \
    memory.has_base = true;                                                                                      \
    memory.displacement = offset;                                                                                \
    return memory;                                                                                               \
  }                                                                                                              \
                                                                                                                 \
  static auto ptr(reg64 base_reg, reg64 index_reg, enum scale s = SCALE_1, i32 offset = 0) -> mem ## bit_width { \
    mem ## bit_width memory = {};                                                                                \
    memory.base = base_reg;                                                                                      \
    memory.has_base = true;                                                                                      \
    memory.index = index_reg;                                                                                    \
    memory.has_index = true;                                                                                     \
    memory.displacement = offset;                                                                                \
    memory.scale = s;                                                                                            \
    return memory;                                                                                               \
  }                                                                                                              \
};

	MEM_DECL(8)
	MEM_DECL(16)
	MEM_DECL(32)
	MEM_DECL(64)
	MEM_DECL(128)
	MEM_DECL(_address)
} // namespace baremetal
