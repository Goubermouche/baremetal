// Each module contains a list of pointers to dialects inside of itself (the base dialects from
// which the module derives). The index of a given dialect can be retrieved from the relevant 
// context. The dialect at the [0] index is always guaranteed to be the core dialect, meaning
// that all node id's, which have a dialect id of 0, all come from the core dialect. 

#pragma once
#include "baremetal/intermediate_representation/dialect.h"
#include "baremetal/dialects/core_dialect.h"
#include "baremetal/context.h"

namespace baremetal {
	namespace detail {
		// recursively derive from the template parameter list

		template<typename... types>
		struct dialect_list_derive {};

		template<typename type, typename... types>
		struct dialect_list_derive<type, types...> : type, dialect_list_derive<types...> {
			dialect_list_derive() : dialect_list_derive<types...>() {}
		};

		template<typename type>
		struct dialect_list_derive<type> : type {
			dialect_list_derive() = default;
		};
	} // namespace detail

	template<derived_from_dialect_base... dialects>
	class module : public virtual core_dialect, public virtual module_data, public detail::dialect_list_derive<dialects...> {
	public:
		module(context& context) {
			m_dialects.resize(sizeof...(dialects) + 1);
			initialize_dialect<core_dialect>(context); // initialize the core dialect first
			(initialize_dialect<dialects>(context), ...);
		}
	private:
		template<typename dialect_type>
		void initialize_dialect(context& context) {
			auto dialect_ptr = static_cast<dialect_type*>(this);

			const u8 index = context.get_dialect_index<dialect_type>();
			m_dialects[index] = dialect_ptr;
			dialect_ptr->m_index = index;
		}
	};
} // namespace baremetal
