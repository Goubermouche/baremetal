#pragma once
#include <utility/containers/dynamic_string.h>

namespace baremetal::assembler {
	using namespace utility::types;

	struct imm {
		imm() = default;
		imm(u64 i) {
			if(i <= utility::limits<u8>::max()) {
				min_bits = 8;
			}
			else if(i <= utility::limits<u16>::max()) {
				min_bits = 16;
			}
			else if(i <= utility::limits<u32>::max()) {
				min_bits = 32;
			}
			else {
				min_bits = 64;
			}

			value = i;
			sign = false;
		}

		imm(i64 i) {
			if(i >= 0) {
				*this = imm(static_cast<u64>(i));
				return;
			}

			if(i >= utility::limits<i8>::min()) {
				min_bits = 8;
			}
			else if(i >= utility::limits<i16>::min()) {
				min_bits = 16;
			}
			else if(i >= utility::limits<i32>::min()) {
				min_bits = 32;
			}
			else {
				min_bits = 64;
			}

			value = i;
			sign = true;
		}

		template<typename type>
		imm(type i) {
			if(std::is_signed_v<type>) {
				*this = imm(static_cast<i64>(i));
			}
			else {
				*this = imm(static_cast<u64>(i));
			}
		}

		u64 value;
		u8 min_bits; // 8, 16, 32, 64
		bool sign;
	};

	struct moff {
		constexpr moff() = default;
		constexpr moff(u64 address) : value(address) {}

		u64 value;
	};

	[[nodiscard]] inline auto immediate_to_string(imm i) -> utility::dynamic_string {
		utility::dynamic_string string;

		if(i.sign) {
			string.append("-{}", ~i.value + 1); // two's complement
		}
		else {
			string.append("{}", i.value);
		}
	
		return string;
	}
} // namespace baremetal::assembler
