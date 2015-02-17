
#include "../data/pfx_cstring_codes.h"
#include "../data/pfx_cshare_string_codes.h"
#include "../data/pfx_string_cmp_codes.h"
#include "../native/pecker_allocator.h"

#ifndef PFX_CSTRING___
#define PFX_CSTRING___
PECKER_BEGIN
typedef cstring < pecker_simple_allocator < char_t > >		cstring_ascii_t;
typedef cstring < pecker_simple_allocator < utf_char_t > >	cstring_unicode_t;
typedef ascii_string_compare< cstring_ascii_t >				cascii_string_compare_t;
typedef ascii_string_compare_withchars< cstring_ascii_t >   ascii_string_compare_withchars_t;

typedef utf_string_compare< cstring_unicode_t >				cutf_string_compare_t;
typedef utf_string_compare_withchars< cstring_unicode_t >   utf_string_compare_withchars_t;


PFX_INLINE 	cstring_ascii_t& SET_STRING(cstring_ascii_t& str, const char_t* charstr_ptr, result_t& status)
{
	if (null == charstr_ptr)
	{
		status = str.init_string((usize__t)0);
	}
	else
	{
		cstring_ascii_t::const_iterator_t itr;
		char_t nullchar = 0;
		status = str.init_string(charstr_ptr, strlen(charstr_ptr) + 1);
		str.end(itr);
		str.set_at(itr, nullchar);
	}
	return str;
}

PFX_INLINE 	cstring_unicode_t& SET_STRING(cstring_unicode_t& str, const utf_char_t* charstr_ptr, result_t& status)
{
	if (null == charstr_ptr)
	{
		status = str.init_string((usize__t)0);
	}
	else
	{
		cstring_unicode_t::const_iterator_t itr;
		utf_char_t nullchar = 0;
		status = str.init_string(charstr_ptr, wcslen(charstr_ptr) + 1);
		str.end(itr);
		str.set_at(itr, nullchar);
	}
	return str;
}

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

//////////////////////////////////////////////////////////////////////////
template < class __utf_string_cmp_value >
struct  compare_utf_string_node
{
	typedef   __utf_string_cmp_value param_type_t;

	PFX_INLINE int operator () (const param_type_t& value1,
		const param_type_t& value2) const
	{
		return cutf_string_compare_t::compare(value1.get_name(), value2.get_name());
	}
	static PFX_INLINE int compare(const param_type_t& value1,
		const param_type_t& value2)
	{
		return cutf_string_compare_t::compare(value1.get_name(), value2.get_name());
	}
};

template < class __utf_string_cmp_value >
struct  compare_utf_string_node_by_name
{
	typedef   __utf_string_cmp_value param_type_t;

	PFX_INLINE int operator () (const param_type_t& value1,
		const cstring_ascii_t& value2) const
	{
		return cutf_string_compare_t::compare(value1.get_name(), value2);
	}
	static PFX_INLINE int compare(const param_type_t& value1,
		const cstring_unicode_t& value2)
	{
		return cutf_string_compare_t::compare(value1.get_name(), value2);
	}
};

template < class __utf_string_cmp_value >
struct  compare_utf_string_node_by_chrname
{
	typedef   __utf_string_cmp_value param_type_t;
	PFX_INLINE int operator () (const param_type_t& value1,
		const utf_char_t* value2) const
	{
		return utf_string_compare_withchars_t::compare(value1.get_name(), value2);
	}
	static PFX_INLINE int compare(const param_type_t& value1,
		const utf_char_t* value2)
	{
		return utf_string_compare_withchars_t::compare(value1.get_name(), value2);
	}
};

PECKER_END

#endif //PFX_CSTRING___

