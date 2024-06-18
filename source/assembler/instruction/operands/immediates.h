#pragma once
#include <utility/types.h>

namespace baremetal {
	using namespace utility::types;

	struct imm {
		imm() = default;
		imm(u64 i) {
			if(i <= std::numeric_limits<u8>::max()) {
				min_bits = 8;
			}
			else if(i <= std::numeric_limits<u16>::max()) {
				min_bits = 16;
			}
			else if(i <= std::numeric_limits<u32>::max()) {
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

			if(i >= std::numeric_limits<i8>::min()) {
				min_bits = 8;
			}
			else if(i >= std::numeric_limits<i16>::min()) {
				min_bits = 16;
			}
			else if(i >= std::numeric_limits<i32>::min()) {
				min_bits = 32;
			}
			else {
				min_bits = 64;
			}

			value = i;
			sign = true;
		}

		// imm(__int128 i) {
		// 	*this = imm(static_cast<i64>(i));
		// }

		template<typename type, std::enable_if_t<std::is_integral_v<type>, i32> = 0>
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
} // namespace baremetal
