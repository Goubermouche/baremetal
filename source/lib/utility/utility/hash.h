#pragma once
#include "utility/types.h"

namespace utility {
	inline void mum(u64* a, u64* b) {
#if defined(__SIZEOF_INT128__)
		__uint128_t r = *a;
		r *= *b;
		*a = static_cast<u64>(r);
		*b = static_cast<u64>(r >> 64U);
#elif defined(_MSC_VER) && defined(_M_X64)
		*a = _umul128(*a, *b, b);
#else
		u64 ha = *a >> 32U;
		u64 hb = *b >> 32U;
		u64 la = static_cast<u32>(*a);
		u64 lb = static_cast<u32>(*b);
		u64 hi{};
		u64 lo{};
		u64 rh = ha * hb;
		u64 rm0 = ha * lb;
		u64 rm1 = hb * la;
		u64 rl = la * lb;
		u64 t = rl + (rm0 << 32U);
		auto c = static_cast<u64>(t < rl);
		lo = t + (rm1 << 32U);
		c += static_cast<u64>(lo < t);
		hi = rh + (rm0 >> 32U) + (rm1 >> 32U) + c;
		*a = lo;
		*b = hi;
#endif
	}

	[[nodiscard]] inline auto mix(u64 a, u64 b) -> u64 {
		mum(&a, &b);
		return a ^ b;
	}

	[[nodiscard]] inline auto compute_hash(u64 x) -> u64 {
		return mix(x, UINT64_C(0x9E3779B97F4A7C15));
	}

	[[nodiscard]] inline auto r4(const u8* p) -> u64 {
		u32 v{};
		utility::memcpy(&v, p, 4);
		return v;
	}

	[[nodiscard]] inline auto r8(const u8* p) -> u64 {
		u64 v{};
		utility::memcpy(&v, p, 8U);
		return v;
	}

	[[nodiscard]] inline auto r3(const u8* p, u64 k) -> u64 {
		return (static_cast<u64>(p[0]) << 16U) | (static_cast<u64>(p[k >> 1U]) << 8U) | p[k - 1];
	}

	[[maybe_unused]] [[nodiscard]] inline auto compute_hash(void const* key, u64 len) -> u64 {
		static constexpr u64 secret[] = { 
			UINT64_C(0xa0761d6478bd642f),
			UINT64_C(0xe7037ed1a0b428db),
			UINT64_C(0x8ebc6af09c88c6e3),
			UINT64_C(0x589965cc75374cc3)
		};

		auto const* p = static_cast<u8 const*>(key);
		u64 seed = secret[0];
		u64 a;
		u64 b;

		if((len <= 16)) {
			if((len >= 4)) {
				a = (r4(p) << 32U) | r4(p + ((len >> 3U) << 2U));
				b = (r4(p + len - 4) << 32U) | r4(p + len - 4 - ((len >> 3U) << 2U));
			}
			else if((len > 0)) {
				a = r3(p, len);
				b = 0;
			}
			else {
				a = 0;
				b = 0;
			}
		}
		else {
			u64 i = len;

			if((i > 48)) {
				u64 see1 = seed;
				u64 see2 = seed;

				do {
					seed = mix(r8(p) ^ secret[1], r8(p + 8) ^ seed);
					see1 = mix(r8(p + 16) ^ secret[2], r8(p + 24) ^ see1);
					see2 = mix(r8(p + 32) ^ secret[3], r8(p + 40) ^ see2);
					p += 48;
					i -= 48;
				} while((i > 48));

				seed ^= see1 ^ see2;
			}

			while((i > 16)) {
				seed = mix(r8(p) ^ secret[1], r8(p + 8) ^ seed);
				i -= 16;
				p += 16;
			}

			a = r8(p + i - 16);
			b = r8(p + i - 8);
		}

		return mix(secret[1] ^ len, mix(a ^ secret[1], b ^ seed));
	}

	/**
	 * \brief Base hash operator.
	 * \tparam type Type to hash
	 */
	template<typename type>
	struct hash {};

#define DETAIL_CREATE_HASH_OPERATOR(type)                    \
	template<>                                                 \
	struct hash<type> {                                        \
		auto operator()(const type& obj) const noexcept -> u64 { \
			return compute_hash(static_cast<u64>(obj));            \
		}                                                        \
	}

	DETAIL_CREATE_HASH_OPERATOR(i8);
	DETAIL_CREATE_HASH_OPERATOR(i16);
	DETAIL_CREATE_HASH_OPERATOR(i32);
	DETAIL_CREATE_HASH_OPERATOR(i64);

	DETAIL_CREATE_HASH_OPERATOR(u8);
	DETAIL_CREATE_HASH_OPERATOR(u16);
	DETAIL_CREATE_HASH_OPERATOR(u32);
	DETAIL_CREATE_HASH_OPERATOR(u64);

	DETAIL_CREATE_HASH_OPERATOR(f32);
	DETAIL_CREATE_HASH_OPERATOR(f64);

	DETAIL_CREATE_HASH_OPERATOR(char);
	DETAIL_CREATE_HASH_OPERATOR(bool);

	template<typename base_type>
	struct hash<base_type*> {
		auto operator()(const base_type* obj) const noexcept -> u64 {
			return compute_hash(reinterpret_cast<u64>(obj));
		}
	};
} // namespace utility
