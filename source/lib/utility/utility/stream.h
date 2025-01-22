#pragma once
#include "utility/types.h"

namespace utility {
	template<typename type, typename stream_type>
	struct stream_writer {
		static void write(const type& value, stream_type& str) {
			str.write(value);
		}
	};
	
	template<typename stream_type>
	struct stream_writer<char, stream_type> {
		static void write(char value, stream_type& str) {
			str.write(&value, 1);
		}
	};

	template<typename stream_type>
	struct stream_writer<bool, stream_type> {
		static void write(bool value, stream_type& str) {
			str.write(value ? "true" : "false");
		}
	};

	template<typename stream_type>
	struct stream_writer<i64, stream_type> {
		static void write(i64 value, stream_type& str) {
			char buffer[20];
			const i32 size = snprintf(buffer, sizeof(buffer), "%ld", value);
			str.write(buffer, size);
		}
	};

	template<typename stream_type>
	struct stream_writer<i32, stream_type> {
		static void write(i32 value, stream_type& str) {
			char buffer[20];
			const i32 size = snprintf(buffer, sizeof(buffer), "%d", value);
			str.write(buffer, size);
		}
	};

	template<typename stream_type>
	struct stream_writer<i16, stream_type> {
		static void write(i16 value, stream_type& str) {
			char buffer[20];
			const i32 size = snprintf(buffer, sizeof(buffer), "%hd", value);
			str.write(buffer, size);
		}
	};

	template<typename stream_type>
	struct stream_writer<i8, stream_type> {
		static void write(i8 value, stream_type& str) {
			char buffer[20];
			const i32 size = snprintf(buffer, sizeof(buffer), "%hhd", value);
			str.write(buffer, size);
		}
	};

	template<typename stream_type>
	struct stream_writer<u64, stream_type> {
		static void write(u64 value, stream_type& str) {
			char buffer[30];
			const i32 size = snprintf(buffer, sizeof(buffer), "%lu", value);
			str.write(buffer, size);
		}
	};

	template<typename stream_type>
	struct stream_writer<u32, stream_type> {
		static void write(u32 value, stream_type& str) {
			char buffer[30];
			const i32 size = snprintf(buffer, sizeof(buffer), "%u", value);
			str.write(buffer, size);
		}
	};

	template<typename stream_type>
	struct stream_writer<u16, stream_type> {
		static void write(u16 value, stream_type& str) {
			char buffer[30];
			const i32 size = snprintf(buffer, sizeof(buffer), "%hu", value);
			str.write(buffer, size);
		}
	};

	template<typename stream_type>
	struct stream_writer<u8, stream_type> {
		static void write(u8 value, stream_type& str) {
			char buffer[30];
			const i32 size = snprintf(buffer, sizeof(buffer), "%hhu", value);
			str.write(buffer, size);
		}
	};

	template<typename stream_type>
	struct stream_writer<f32, stream_type> {
		static void write(f32 value, stream_type& str) {
			char buffer[30];
			const i32 size = snprintf(buffer, sizeof(buffer), "%.2f", value);
			str.write(buffer, size);
		}
	};

	template<typename stream_type>
	struct stream_writer<f64, stream_type> {
		static void write(f64 value, stream_type& str) {
			char buffer[30];
			const i32 size = snprintf(buffer, sizeof(buffer), "%.2f", value);
			str.write(buffer, size);
		}
	};
} // namespace utility

