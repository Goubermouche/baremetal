#include "emit_elf_pass.h"

#include "assembler/backend.h"
#include "assembler/ir/module.h"


#define PUSH_U64(value)                       \
for(u8 x = 0; x < sizeof(u64); x++) {         \
  bytes.push_back((value >> (x * 8)) & 0xFF); \
}

#define PUSH_U32(value)                       \
for(u8 x = 0; x < sizeof(u32); x++) {         \
  bytes.push_back((value >> (x * 8)) & 0xFF); \
}

namespace baremetal::assembler::pass {
	auto emit_elf(const module& module) -> utility::dynamic_array<u8> {
		utility::dynamic_array<u8> bytes;

		bytes.push_back(0x7f); // magic number
		bytes.push_back(0x45);
		bytes.push_back(0x4c);
		bytes.push_back(0x46);
		
		bytes.push_back(0x2); // 32/64 bit mode (1 = 32, 2 = 64)
		bytes.push_back(0x1); // little/big endianness (1 = little, 2 = big)
		bytes.push_back(0x1); // ELF version
		bytes.push_back(0x0); // target ABI (system-v)
		bytes.push_back(0x0); // ignored on linux 
		bytes.push_back(0x0); // padding 
		bytes.push_back(0x0); // padding 
		bytes.push_back(0x0); // padding 
		bytes.push_back(0x0); // padding 
		bytes.push_back(0x0); // padding 
		bytes.push_back(0x0); // padding 
		bytes.push_back(0x0); // padding 

		bytes.push_back(0x1); // object file type (relocatable)
		bytes.push_back(0x0); 

		bytes.push_back(0x3e); // target isa (none) 
		bytes.push_back(0x0);

		bytes.push_back(0x1); // 1 for the origin ELF version
		bytes.push_back(0x0);
		bytes.push_back(0x0);
		bytes.push_back(0x0);

		// entry point address
		const auto entry_point_name = module.ctx->strings.add("_start");

		for(const section& section : module.sections) {
			const auto it = section.symbols.find(entry_point_name);

			if(it != section.symbols.end()) {
				const u64 entry_position = section.position + it->second.position; 
				PUSH_U64(entry_position);	
				break;
			}
		}

		// program header table start
		const u64 header_table = 0x0;
		PUSH_U64(header_table);	

		const u64 section_table = 0x40;
		PUSH_U64(section_table);	

		const u64 flags = 0x00;
		PUSH_U32(flags);	
	
		// section header table entry size
		bytes.push_back(0x40);
		bytes.push_back(0x0);

		// number of section entries
		bytes.push_back(0x0);
		bytes.push_back(0x0);

		// section name table index
		bytes.push_back(0x0);
		bytes.push_back(0x0);
	
		// end of ELF header
		bytes.push_back(0x40);

		return bytes;
	}
} // namespace baremetal::assembler::pass
