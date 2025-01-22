// implementation lifted from: https://github.com/martinus/unordered_dense (MIT license)

#pragma once
#include "utility/containers/dynamic_array.h"
#include "utility/hash.h"

namespace utility {
	template <typename mapped>
	constexpr bool is_map_v = !is_void_v<mapped>;

	/**
	 * \brief Hash-based unordered map. Maps a \b key to a specific \b value.
	 * \tparam key Type to use as a key type
	 * \tparam value Type to use as the value type
	 * \tparam hash Hash to use when hashing the key type. A hash operator ("()") has to be implemented in order for the
	 * map to work correctly. Some basic hash operators are provided by default. 
	 * \tparam key_equal Key equality operator. Uses std::equal by default. 
	 */
	template<typename key, typename value, typename hash = hash<key>, typename key_equal = std::equal_to<key>>
	class map {
		struct bucket {
			static constexpr u32 dist_inc = 1U << 8U;             // skip 1 byte fingerprint
			static constexpr u32 fingerprint_mask = dist_inc - 1; // mask for 1 byte of fingerprint

			u32 m_dist_and_fingerprint;                           // upper 3 byte: distance to original bucket. lower byte: fingerprint from hash
			u32 m_value_idx;                                      // index into the m_values vector.
		};
	public:
		using bucket_type = typename std::conditional_t<is_map_v<value>, std::pair<key, value>, key>;
		using bucket_container_type = dynamic_array<bucket_type>;

		using const_iterator = typename bucket_container_type::const_iterator;
		using iterator = typename bucket_container_type::iterator;

		using dist_and_fingerprint_type = decltype(bucket::m_dist_and_fingerprint);
		using value_idx_type = decltype(bucket::m_value_idx);
		using element_type = value;
		using key_type = key;

		map() : map(0) {}

		map(u64 bucket_count) : m_buckets(nullptr), m_num_buckets(0), m_max_bucket_capacity(0) {
			if(bucket_count != 0) {
				reserve(bucket_count);
			}
			else {
				allocate_buckets_from_shift();
				clear_buckets();
			}
		}

		map(initializer_list<bucket_type> ilist, u64 bucket_count = 0)
			: map(bucket_count) {
			for(const auto& i : ilist) {
				emplace(i);
			}
		}

		map(const map& other)
		: m_values(other.m_values), m_equal(other.m_equal), m_hash(other.m_hash) {
			copy_buckets(other);
		}

		map(map&& other) noexcept : m_buckets(nullptr) {
			*this = utility::move(other);
		}

		~map() {
			utility::free(m_buckets);
		}

		auto operator=(const map& other) -> map& {
			if(&other != this) {
				deallocate_buckets();

				m_values = other.m_values;
				m_hash = other.m_hash;
				m_equal = other.m_equal;
				m_shifts = initial_shifts;

				copy_buckets(other);
			}

			return *this;
		}

		auto operator=(map&& other) noexcept -> map& {
			if(&other != this) {
				deallocate_buckets();

				m_values = utility::move(other.m_values);
				other.m_values.clear();
				m_buckets = exchange(other.m_buckets, nullptr);
				m_num_buckets = exchange(other.m_num_buckets, 0);
				m_max_bucket_capacity = exchange(other.m_max_bucket_capacity, 0);
				m_shifts = exchange(other.m_shifts, initial_shifts);
				m_hash = exchange(other.m_hash, {});
				m_equal = exchange(other.m_equal, {});

				other.allocate_buckets_from_shift();
				other.clear_buckets();
			}
				
			return *this;
		}

		template <typename q = value, enable_if_t<is_map_v<q>, bool> = true>
		auto operator[](const key_type& k) -> q& {
			return try_emplace(k).first->second;
		}

		template <typename q = value, enable_if_t<is_map_v<q>, bool> = true>
		auto operator[](key_type&& k) -> q& {
			return try_emplace(move(k)).first->second;
		}

		template <typename q = value, enable_if_t<is_map_v<q>, bool> = true>
		[[nodiscard]] auto at(const key_type& k) -> const q& {
			return do_at(k);
		}

		auto contains(const key_type& k) const -> bool {
			return find(k) != end();
		}

		auto insert(bucket_type const& v) -> std::pair<iterator, bool> {
			return emplace(v);
    }

		auto insert(bucket_type&& v) -> std::pair<iterator, bool> {
			return emplace(utility::move(v));
		}

		[[nodiscard]] auto find(const key& k) const -> const_iterator {
			return do_find(k);
		}

		template<class... Args>
		auto emplace(Args&&... args) -> std::pair<iterator, bool> {
			auto& k = get_key(m_values.emplace_back(utility::forward<Args>(args)...));
			auto h = mixed_hash(k);
			auto dist_and_fingerprint = dist_and_fingerprint_from_hash(h);
			auto bucket_idx = bucket_idx_from_hash(h);

			while(dist_and_fingerprint <= at(m_buckets, bucket_idx).m_dist_and_fingerprint) {
				if(
					dist_and_fingerprint == at(m_buckets, bucket_idx).m_dist_and_fingerprint &&
					m_equal(k, get_key(m_values[at(m_buckets, bucket_idx).m_value_idx]))
				) {
					m_values.pop_back();
					return {
						begin() + static_cast<u64>(at(m_buckets, bucket_idx).m_value_idx),
						false
					};
				}

				dist_and_fingerprint = dist_inc(dist_and_fingerprint);
				bucket_idx = next(bucket_idx);
			}

			auto value_idx = static_cast<value_idx_type>(m_values.get_size() - 1);

			if(is_full()) {
				increase_size();
			}
			else {
				place_and_shift_up({ dist_and_fingerprint, value_idx }, bucket_idx);
			}

			return { begin() + static_cast<u64>(value_idx), true };
		}

		void reserve(u64 capacity) {
			capacity = min(capacity, max_size());
			m_values.reserve(capacity);
			const auto shifts = calc_shifts_for_size(max(capacity, get_size()));

			if(0 == m_num_buckets || shifts < m_shifts) {
				m_shifts = shifts;

				deallocate_buckets();
				allocate_buckets_from_shift();
				clear_and_fill_buckets_from_values();
			}
		}

		[[nodiscard]] auto begin() noexcept -> iterator {
			return m_values.begin();
		}

		[[nodiscard]] auto begin() const noexcept -> const_iterator {
			return m_values.begin();
		}

		[[nodiscard]] auto cbegin() const noexcept -> const_iterator {
			return m_values.cbegin();
		}

		[[nodiscard]] auto end() noexcept -> iterator {
			return m_values.end();
		}

		[[nodiscard]] auto cend() const noexcept -> const_iterator {
			return m_values.cend();
		}

		[[nodiscard]] auto end() const noexcept -> const_iterator {
			return m_values.end();
		}

		[[nodiscard]] auto get_size() const noexcept -> u64 {
			return m_values.get_size();
		}
		[[nodiscard]] auto is_full() const -> bool {
			return get_size() > m_max_bucket_capacity;
		}
		[[nodiscard]] auto is_empty() const noexcept -> bool {
			return m_values.is_empty();
		}

		void clear() {
			m_values.clear();
			clear_buckets();
		}
	protected:
		template <class... Args>
		auto try_emplace(const key_type& k, Args&&... args) -> std::pair<iterator, bool> {
			return do_try_emplace(k, utility::forward<Args>(args)...);
		}	

		template <typename q = value, enable_if_t<is_map_v<q>, bool> = true>
		auto do_at(const key_type& k) -> const q& {
			if(auto it = find(k); (end() != it)) {
				return it->second;
			}
			 
			static const element_type default_element{};
			ASSERT(false, "key not found\n");

			return default_element;
		}

		template <typename K, typename... Args>
		auto do_try_emplace(K&& k, Args&&... args) -> std::pair<iterator, bool> {
			auto h = mixed_hash(k);
			auto dist_and_fingerprint = dist_and_fingerprint_from_hash(h);
			auto bucket_idx = bucket_idx_from_hash(h);

			while(true) {
				auto* b = &at(m_buckets, bucket_idx);

				if(dist_and_fingerprint == b->m_dist_and_fingerprint) {
					if(m_equal(k, get_key(m_values[b->m_value_idx]))) {
						return { begin() + static_cast<u64>(b->m_value_idx), false };
					}
				}
				else if(dist_and_fingerprint > b->m_dist_and_fingerprint) {
					return do_place_element(
						dist_and_fingerprint,
						bucket_idx,
						std::piecewise_construct,
						std::forward_as_tuple(utility::forward<K>(k)),
						std::forward_as_tuple(utility::forward<Args>(args)...)
					);
				}

				dist_and_fingerprint = dist_inc(dist_and_fingerprint);
				bucket_idx = next(bucket_idx);
			}
		}

		template <typename... Args>
		auto do_place_element(dist_and_fingerprint_type dist_and_fingerprint, value_idx_type bucket_idx, Args&&... args) -> std::pair<iterator, bool> {
			m_values.emplace_back(utility::forward<Args>(args)...);
			auto value_idx = static_cast<value_idx_type>(m_values.get_size() - 1);

			if(is_full()) {
				increase_size();
			}
			else {
				place_and_shift_up({ dist_and_fingerprint, value_idx }, bucket_idx);
			}

			return { begin() + static_cast<u64>(value_idx), true };
		}

		auto do_find(const key& k) const -> const_iterator {
			if(is_empty()) {
				return end();
			}

			auto mh = mixed_hash(k);
			auto dist_and_fingerprint = dist_and_fingerprint_from_hash(mh);
			auto bucket_idx = bucket_idx_from_hash(mh);
			auto* b = &at(m_buckets, bucket_idx);

			if(dist_and_fingerprint == b->m_dist_and_fingerprint && m_equal(k, get_key(m_values[b->m_value_idx]))) {
				return begin() + static_cast<u64>(b->m_value_idx);
			}

			dist_and_fingerprint = dist_inc(dist_and_fingerprint);
			bucket_idx = next(bucket_idx);
			b = &at(m_buckets, bucket_idx);

			if(dist_and_fingerprint == b->m_dist_and_fingerprint && m_equal(k, get_key(m_values[b->m_value_idx]))) {
				return begin() + static_cast<u64>(b->m_value_idx);
			}

			dist_and_fingerprint = dist_inc(dist_and_fingerprint);
			bucket_idx = next(bucket_idx);
			b = &at(m_buckets, bucket_idx);

			while(true) {
				if(dist_and_fingerprint == b->m_dist_and_fingerprint) {
					if(m_equal(k, get_key(m_values[b->m_value_idx]))) {
						return begin() + static_cast<u64>(b->m_value_idx);
					}
				}
				else if(dist_and_fingerprint > b->m_dist_and_fingerprint) {
					return end();
				}

				dist_and_fingerprint = dist_inc(dist_and_fingerprint);
				bucket_idx = next(bucket_idx);
				b = &at(m_buckets, bucket_idx);
			}
		}

		[[nodiscard]] static constexpr auto at(bucket* bucket_ptr, u64 offset) -> bucket& {
			return *(bucket_ptr + offset);
		}

		void increase_size() {
			if(m_max_bucket_capacity == max_bucket_count()) {
				m_values.pop_back();

				ASSERT(false, "map ran into an overflow");
				return;
			}

			--m_shifts;
			deallocate_buckets();
			allocate_buckets_from_shift();
			clear_and_fill_buckets_from_values();
		}

		void deallocate_buckets() {
			utility::free(m_buckets);
			m_buckets = nullptr;

			m_num_buckets = 0;
			m_max_bucket_capacity = 0;
		}

		void clear_and_fill_buckets_from_values() {
			clear_buckets();

			for(value_idx_type value_idx = 0, end_idx = static_cast<value_idx_type>(m_values.get_size()); value_idx < end_idx; ++value_idx) {
				auto const& k = get_key(m_values[value_idx]);
				auto [dist_and_fingerprint, b] = next_while_less(k);

				place_and_shift_up({ dist_and_fingerprint, value_idx }, b);
			}
		}

		template <typename K>
		[[nodiscard]] auto next_while_less(const K& k) const -> bucket {
			auto h = mixed_hash(k);
			auto dist_and_fingerprint = dist_and_fingerprint_from_hash(h);
			auto bucket_idx = bucket_idx_from_hash(h);

			while(dist_and_fingerprint < at(m_buckets, bucket_idx).m_dist_and_fingerprint) {
				dist_and_fingerprint = dist_inc(dist_and_fingerprint);
				bucket_idx = next(bucket_idx);
			}

			return { dist_and_fingerprint, bucket_idx };
		}

		[[nodiscard]] static constexpr auto dist_inc(dist_and_fingerprint_type x) -> dist_and_fingerprint_type {
			return static_cast<dist_and_fingerprint_type>(x + bucket::dist_inc);
		}

		[[nodiscard]] static constexpr auto get_key(const bucket_type& vt) -> const key_type& {
			if constexpr (is_map_v<value>) {
				return vt.first;
			}
			else {
				return vt;
			}
		}

		[[nodiscard]] auto next(value_idx_type bucket_idx) const -> value_idx_type {
			return bucket_idx + 1U == m_num_buckets ? 0 : static_cast<value_idx_type>(bucket_idx + 1U);
		}

		template<typename K>
		[[nodiscard]] constexpr auto mixed_hash(const K& k) const -> u64 {
			return compute_hash(m_hash(k));
		}

		[[nodiscard]] constexpr auto dist_and_fingerprint_from_hash(u64 h) const -> dist_and_fingerprint_type {
			return bucket::dist_inc | (static_cast<dist_and_fingerprint_type>(h) & bucket::fingerprint_mask);
		}

		[[nodiscard]] constexpr auto bucket_idx_from_hash(u64 h) const -> value_idx_type {
			return static_cast<value_idx_type>(h >> m_shifts);
		}

		[[nodiscard]] static constexpr auto max_size() noexcept -> u64 {
			if constexpr((utility::limits<value_idx_type>::max)() == (utility::limits<u64>::max)()) {
				return u64{ 1 } << (sizeof(value_idx_type) * 8 - 1);
			}
			else {
				return u64{ 1 } << (sizeof(value_idx_type) * 8);
			}
		}

		[[nodiscard]] static constexpr auto calc_shifts_for_size(u64 s) -> u8 {
			auto shifts = initial_shifts;

			while(shifts > 0 && static_cast<u64>(static_cast<float>(calc_num_buckets(shifts)) * default_max_load_factor) < s) {
				--shifts;
			}

			return shifts;
		}

		static constexpr auto max_bucket_count() noexcept -> u64 {
			return max_size();
		}

		auto bucket_count() const noexcept -> u64 {
			return m_num_buckets;
		}

		void clear_buckets() {
			if(m_buckets != nullptr) {
				utility::memset(&*m_buckets, 0, sizeof(bucket) * bucket_count());
			}
		}

		[[nodiscard]] static constexpr auto calc_num_buckets(u8 shifts) -> u64 {
			return min(max_bucket_count(), u64{ 1 } << (64U - shifts));
		}

		void place_and_shift_up(bucket b, value_idx_type place) {
			while(0 != at(m_buckets, place).m_dist_and_fingerprint) {
				b = exchange(at(m_buckets, place), b);
				b.m_dist_and_fingerprint = dist_inc(b.m_dist_and_fingerprint);
				place = next(place);
			}

			at(m_buckets, place) = b;
		}

		void allocate_buckets_from_shift() {
			m_num_buckets = calc_num_buckets(m_shifts);
			m_buckets = static_cast<bucket*>(utility::malloc(m_num_buckets * sizeof(bucket)));

			if(m_num_buckets == max_bucket_count()) {
				m_max_bucket_capacity = max_bucket_count();
			}
			else {
				m_max_bucket_capacity = static_cast<value_idx_type>(static_cast<float>(m_num_buckets) * default_max_load_factor);
			}
		}

		void copy_buckets(const map& other) {
			if(is_empty()) {
				allocate_buckets_from_shift();
				clear_buckets();
			}
			else {
				m_shifts = other.m_shifts;
				allocate_buckets_from_shift();
				utility::memcpy(m_buckets, other.m_buckets, sizeof(bucket) * bucket_count());
			}
		}
	protected:
		static constexpr f32 default_max_load_factor = 0.8f;
		static constexpr u8 initial_shifts = 64 - 2;

		bucket_container_type m_values;
		bucket* m_buckets;

		key_equal m_equal;
		hash m_hash;

		u64 m_num_buckets;
		u64 m_max_bucket_capacity;
		u8 m_shifts = initial_shifts;
	};
} // namespace utility
