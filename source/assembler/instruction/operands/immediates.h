#pragma once
#include <utility/types.h>

namespace baremetal {
	using namespace utility::types;

	struct imm {
		imm() = default;
		imm(u64 i) {
			if(i >= std::numeric_limits<u8>::min() && i <= std::numeric_limits<u8>::max()) {
				min_bits = 8;
			}
			else if(i >= std::numeric_limits<u16>::min() && i <= std::numeric_limits<u16>::max()) {
				min_bits = 16;
			}
			else if(i >= std::numeric_limits<u32>::min() && i <= std::numeric_limits<u32>::max()) {
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

			if(i >= std::numeric_limits<i8>::min() && i <= std::numeric_limits<i8>::max()) {
				min_bits = 8;
			}
			else if(i >= std::numeric_limits<i16>::min() && i <= std::numeric_limits<i16>::max()) {
				min_bits = 16;
			}
			else if(i >= std::numeric_limits<i32>::min() && i <= std::numeric_limits<i32>::max()) {
				min_bits = 32;
			}
			else {
				min_bits = 64;
			}

			value = i;
			sign = true;
		}

		template<typename type, typename std::enable_if<std::is_integral<type>::value, int>::type = 0>
		imm(type i) {
			if(std::is_signed<type>::value) {
				*this = imm(static_cast<i64>(i));
			}
			else {
				*this = imm(static_cast<u64>(i));
			}
		}

		u64 value;
		u8 min_bits;
		bool sign;
	};
} // namespace baremetal