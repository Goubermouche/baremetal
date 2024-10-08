#pragma once
#include <utility/containers/dynamic_string.h>
#include <utility/system/console.h>
#include <utility/system/file.h> 

#include <assembler/frontend.h>

using namespace utility::types;

#define TEST(name)                           \
  do {                                       \
    const auto result = run_test_ ## name(); \
    total_success += result.success_count;   \
    total_fail    += result.fail_count;      \
  } while(false)

namespace baremetal::tests {
	struct test_info {
		test_info(const char* name, u64 total_tests, bool quiet) : m_name(name), m_total_tests(total_tests), m_quiet(quiet) {
			ASSERT(m_total_tests > 0, "no tests provided\n");
		}
	
		void add_success() {
			if(m_quiet) {
				return;
			}

			m_success_count++;
			update();
		}
	
		void add_failure() {
			if(m_quiet) {
				return;
			}

			m_fail_count++;
			update();
		}
	
		void begin_test() {
			m_timer.start();
		}
	
		auto end_test() -> bool {
			if(m_quiet) {
				return m_total_tests != m_success_count;
			}

			m_timer.stop();
			update(true);
	
			utility::console::print(
				": {} ({}/{}) - {}s\n",
				m_total_tests == m_success_count ? "PASS" : "FAIL",
				m_success_count,
				m_total_tests,
				m_timer.get_elapsed_s()
			);

			return m_total_tests != m_success_count;
		}
	private:
		void update(bool force = false) {
	    constexpr u8 max_segments = 20;
	
	    const u64 finished_count = m_success_count + m_fail_count;
	    const f64 percentage = (static_cast<f64>(finished_count) / m_total_tests) * 100;
	    const u8 completed_segments = static_cast<u8>((finished_count * max_segments) / m_total_tests);
	
			// only update the bar when we've surpassed another bar segment
			if(completed_segments == m_completed_segment_count_old || force) {
				return;
			}
	
			m_completed_segment_count_old = completed_segments;
	   
			// render our progress bar
			utility::console::print("\r[", static_cast<u8>(percentage));
	
			for(u8 i = 0; i < max_segments; ++i) {
				if(i < completed_segments) {
				  utility::console::print("#");
				} else {
				  utility::console::print(".");
				}
			}
	
			utility::console::print("]");
			utility::console::print(" test '{}'", m_name);
		}
	
		const char* m_name;
		u64 m_total_tests;
		bool m_quiet;

		u64 m_fail_count = 0;
		u64 m_success_count = 0;
		u8 m_completed_segment_count_old = 1;
		utility::timer m_timer;
	};

	inline auto bytes_to_string(const utility::dynamic_array<u8>& bytes) -> utility::dynamic_string {
		utility::dynamic_string result;
		result.reserve(bytes.get_size() * 2);

		constexpr char digits[] = "0123456789abcdef";

		for(u64 i = 0; i < bytes.get_size(); ++i) {
			const u8 value = bytes[i];
			result += (digits[(value >> 4) & 0x0F]);
			result += (digits[value & 0x0F]);
		}

		return result;
	}
} // namespace baremetal::tests
