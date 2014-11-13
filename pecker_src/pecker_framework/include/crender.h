#include "../data/pfx_cstring_codes.h"
#include "../data/pfx_cshare_string_codes.h"
#include "../data/pfx_string_cmp_codes.h"
#include "../native/pecker_allocator.h"

#ifndef PFX_CSTRING___
#define PFX_CSTRING___
PECKER_BEGIN
typedef cstring < pecker_simple_allocator < char_t > >		cstring_ascii_t;
typedef cstring < pecker_simple_allocator < widechar_t > >	cstring_unicode16_t;
typedef ascii_string_compare< cstring_ascii_t >				cascii_string_compare_t;
typedef ascii_string_compare_withchars< cstring_ascii_t >   ascii_string_compare_withchars_t;

template < class __ascii_string_cmp_value >
struct  compare_ascii_string_node
{
	typedef   __ascii_string_cmp_value param_type_t;

	PFX_INLINE int operator () (const param_type_t& value1,
		const param_type_t& value2) const
	{
		return cascii_string_compare_t::compare(value1.get_name(), value2.get_name());
	}
	static PFX_INLINE int compare(const param_type_t& value1,
		const param_type_t& value2)
	{
		return cascii_string_compare_t::compare(value1.get_name(), value2.get_name());
	}
};

template < class __ascii_string_cmp_value >
struct  compare_ascii_string_node_by_name
{
	typedef   __ascii_string_cmp_value param_type_t;

	PFX_INLINE int operator () (const param_type_t& value1,
	const cstring_ascii_t& value2) const
	{
		return cascii_string_compare_t::compare(value1.get_name(), value2);
	}
	static PFX_INLINE int compare(const param_type_t& value1,
		const cstring_ascii_t& value2)
	{
		return cascii_string_compare_t::compare(value1.get_name(), value2);
	}
};

template < class __ascii_string_cmp_value >
struct  compare_ascii_string_node_by_chrname
{
	typedef   __ascii_string_cmp_value param_type_t;
	PFX_INLINE int operator () (const param_type_t& value1,
	const char_t* value2) const
	{
		return ascii_string_compare_withchars_t::compare(value1.get_name(), value2);
	}
	static PFX_INLINE int compare(const param_type_t& value1,
		const char_t* value2)
	{
		return ascii_string_compare_withchars_t::compare(value1.get_name(), value2);
	}
};

PECKER_END

#endif //PFX_CSTRING___

