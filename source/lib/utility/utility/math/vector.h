#pragma once
#include "utility/stream.h"

namespace utility {
	namespace types {
		template<typename type>
		struct vec2 {
			vec2() : x(type()), y(type()) {}
			vec2(type x, type y) : x(x), y(y) {}

			type x;
			type y;
		};
	} // namespace types

	template<typename stream_type, typename type>
	struct stream_writer<vec2<type>, stream_type> {
		static void write(const vec2<type>& value) {
			stream_writer<char, stream_type>::write('{');
			stream_writer<type, stream_type>::write(value.x);
			stream_writer<char, stream_type>::write(',');
			stream_writer<type, stream_type>::write(value.y);
			stream_writer<char, stream_type>::write('}');
		}
	};
} // namespace utility
