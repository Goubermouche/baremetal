#pragma once
#include "utility/stream.h"

namespace utility {
	class console {
	private:
		struct printer {
			printer() {
				#ifdef _WIN32
				stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
				stderr_handle = GetStdHandle(STD_ERROR_HANDLE);
				#elif __linux__
				stdout_handle = STDOUT_FILENO;
				stderr_handle = STDERR_FILENO;
				#endif
			}

			void write(const char* data) {
				write(data, string_len(data));
			}
	
			void write(const wchar_t* data) {
				write(data, string_len(data));
			}
	
			void write(const char* data, u64 size) {
				#ifdef _WIN32
				DWORD bytes_written;
				WriteConsoleA(m_current_handle, data, static_cast<DWORD>(size), &bytes_written, nullptr);
				#elif __linux__
				auto r = ::write(m_printer.m_current_handle, data, size);
				SUPPRESS_C4100(r);
				#endif
			}
	
			void write(const wchar_t* data, u64 size) {
				#ifdef _WIN32
				DWORD bytes_written;
				WriteConsoleW(m_current_handle, data, static_cast<DWORD>(size), &bytes_written, nullptr);
				#elif __linux__
				auto r = ::write(m_printer.m_current_handle, data, size * sizeof(wchar_t));
				SUPPRESS_C4100(r);
				#endif
			}
	
			void flush() {
				#ifdef _WIN32
				FlushFileBuffers(m_current_handle);
				#elif __linux__
				fsync(m_printer.m_current_handle);
				#endif
			}

			#ifdef _WIN32
			HANDLE m_current_handle;
			#elif __linux__
			i32 m_current_handle;
			#endif

			#ifdef _WIN32
			HANDLE stdout_handle;
			HANDLE stderr_handle;
			#elif __linux__
			i32 stdout_handle;
			i32 stderr_handle;
			#endif
		};
	public:
		static void flush() {
			m_printer.flush();
		}

		template<typename type>
		static void print(const type& value) {
			m_printer.m_current_handle = m_printer.stdout_handle;
			print_impl(value);
		}

		template<typename type>
		static void print_err(const type& value) {
			m_printer.m_current_handle = m_printer.stderr_handle;
			print_impl(value);
		}

		template<typename type, typename... types>
		static void print(const char* format, const type& first, const types&... rest) {
			m_printer.m_current_handle = m_printer.stdout_handle;
			print_impl(format, first, forward<const types>(rest)...);
		}

		template<typename type, typename... types>
		static void print_err(const char* format, const type& first, const types&... rest) {
			m_printer.m_current_handle = m_printer.stderr_handle;
			print_impl(format, first, forward<const types>(rest)...);
		}
	protected:
		template<typename type, typename... types>
		static void print_impl(const char* format, const type& first, const types&... rest) {
			if(const char* open_brace = std::strstr(format, "{}")) {
				m_printer.write(format, open_brace - format);
				stream_writer<type, printer>::write(first, m_printer);
				print_impl(open_brace + 2, rest...);
			}
			else {
				m_printer.write(format);
			}
		}

		template<typename type>
		static void print_impl(const type& value) {
				stream_writer<type, printer>::write(value, m_printer);
		}
	protected:
		static printer m_printer;
	};

	inline console::printer console::m_printer;
} // namespace utility
