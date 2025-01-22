#pragma once
#include "utility/stream.h"

namespace utility {
	class error {
	public:
		error() : m_message(nullptr) {}
		error(const char* message) : m_message(message) {}

		[[nodiscard]] auto get_message() const -> const char* {
			return m_message;	
		}

		[[nodiscard]] auto has_message() const -> bool {
			return m_message != nullptr;
		}
	private:
		const char* m_message;	
	};

	template<typename type>
	class result {
	public:
		result(type value) : m_value(move(value)) {}
		result(const error& err) : m_error(err) {}

		[[nodiscard]] auto has_value() const -> bool {
			return !m_error.has_message();
		}

		[[nodiscard]] auto has_error() const -> bool {
			return m_error.has_message();
		}

		[[nodiscard]] auto get_value() const -> const type& {
			return m_value;
		}

		[[nodiscard]] auto get_value() -> type {
			return move(m_value);
		}

		[[nodiscard]] auto get_error() const -> const error& {
			return m_error;
		}
	private:
		type m_value;
		error m_error;
	};

	template<>
	class result<void> {
	public:
		result() {}
		result(const error& err) : m_error(err) {}

		[[nodiscard]] auto has_value() const -> bool {
			return !m_error.has_message();
		}

		[[nodiscard]] auto has_error() const -> bool {
			return m_error.has_message();
		}

		[[nodiscard]] auto get_error() const -> const error& {
			return m_error;
		}
	private:
		error m_error;
	};

	template<typename stream_type>
	struct stream_writer<error, stream_type> {
		static void write(const error& value, stream_type& str) {
			str.write(value.get_message());
		}
	};
} // namespace utility

// variant 1
#define TRY_1(__result)                                     \
  do {                                                      \
    auto CONCATENATE(result, __LINE__) = __result;          \
    if (CONCATENATE(result, __LINE__).has_error()) {        \
      return ((CONCATENATE(result, __LINE__)).get_error()); \
    }                                                       \
  } while(false)

// variant 2
#define TRY_2(__success, __result)                      \
auto CONCATENATE(result, __LINE__) = (__result);        \
if(CONCATENATE(result, __LINE__).has_error()) {         \
  return ((CONCATENATE(result, __LINE__)).get_error()); \
}                                                       \
__success = CONCATENATE(result, __LINE__).get_value()

// expand the macros based on the number of parameters
#define GET_MACRO(_1, _2, NAME, ...) NAME

#define TRY(...) EXPAND(GET_MACRO(__VA_ARGS__, TRY_2, TRY_1)(__VA_ARGS__))

#define SUCCESS {}
