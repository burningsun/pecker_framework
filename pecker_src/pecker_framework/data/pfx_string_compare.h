﻿/*  pfx_string_compare.h
*		Created on: 2014-5-25
*      Author: 李镇城  （ cut / cutxyz）
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/

#ifndef PECKER_STRING_COMPARE_H_
#define PECKER_STRING_COMPARE_H_

#include "../pfx_defines.h"
#include "pecker_value_compare.h"

PECKER_BEGIN

typedef enum enumSTRING_CMP_TYPE
{
	CMP_ALL_STRING_SAME = 0,
	CMP_SAME_AS_ONE_STRING,

	STRING_CMP_TYPE_COUNT
}STRING_CMP_TYPE_t;

template < class __element,
					class elem_compare = pecker_value_compare < __element > >
struct find_string_operate
{
	typedef __element				element_t;
	typedef elem_compare		elem_compare_t;

	typedef  const element_t* cmptype_a_t;
	typedef  const element_t* cmptype_b_t;

	typedef  find_string_operate< element_t, elem_compare_t >	find_string_t;

	static PFX_INLINE int same_string (const element_t* PARAM_IN str_string_ptr,
																				usize__t str_size,
																				const element_t* PARAM_IN str_cmp_string_ptr,
																				usize__t cmp_str_size);

	static PFX_INLINE int same_string (const element_t* PARAM_IN str_string_ptr,
																				usize__t str_size,
																				const element_t* PARAM_IN str_cmp_string_ptr,
																				usize__t cmp_str_size,
																				usize__t& same_count);

	static PFX_INLINE uindex_t	find_first_string  (
																				const element_t* PARAM_IN str_string_ptr,
																				usize__t str_size,
																				const element_t* PARAM_IN str_cmp_string_ptr,
																				usize__t cmp_str_size);


	static PFX_INLINE uindex_t	find_near_string (
																				const element_t* PARAM_IN str_string_ptr,
																				usize__t str_size,
																				const element_t* PARAM_IN str_cmp_string_ptr,
																				usize__t cmp_str_size,	
																				usize__t& same_chars_count);
};

template < class stringA, 
					class stringB = stringA, 
					class elem_compare = pecker_value_compare < typename stringA::element_t > >
struct find_cstrstring_operate
{
	typedef stringA		stringa_t;
	typedef stringB		stringb_t;

	typedef typename stringa_t::const_iterator_t		const_iteratorA_t;
	typedef typename stringb_t::const_iterator_t		const_iteratorB_t;

	typedef const stringa_t& cmptype_a_t;
	typedef const stringb_t& cmptype_b_t;

	typedef typename stringa_t::element_t			element_t;
	typedef elem_compare										elem_compare_t;

	typedef find_cstrstring_operate < stringa_t, stringb_t, elem_compare_t > find_string_t;

	typedef find_string_operate	< element_t, elem_compare_t > find_chars_t;

	static PFX_INLINE int same_string (const stringa_t& str1, const stringb_t& str2);

	static PFX_INLINE int same_string (const stringa_t& str1, const stringb_t& str2, usize__t& same_count);

	static PFX_INLINE uindex_t	find_first_string (const stringa_t& str1, const stringb_t& str2);

	static PFX_INLINE uindex_t	find_near_string (const stringa_t& str1, const stringb_t& str2,
																						usize__t& same_chars_count);
	static PFX_INLINE int same_string (const_iteratorA_t& str1, const_iteratorB_t& str2);

	static PFX_INLINE int same_string (const_iteratorA_t& str1, const_iteratorB_t& str2, usize__t& same_count);

	static PFX_INLINE uindex_t	find_first_string (const_iteratorA_t& str1, const_iteratorB_t& str2);

	static PFX_INLINE uindex_t	find_near_string (const_iteratorA_t& str1, const_iteratorB_t& str2,
																				usize__t& same_chars_count);
};



template< 
	class string_type1,
	class string_type2 = string_type1,
	class elem_compare = pecker_value_compare < typename string_type1::element_t >,
	const enum_int_t cmp_type = 0>  
struct PFX_DATA_TEMPLATE_API string_compare
{
	typedef string_type1		stringa_t;
	typedef string_type2		stringb_t;

	typedef typename stringa_t::element_t			element_t;
	typedef elem_compare										elem_compare_t;

	typedef find_cstrstring_operate< stringa_t, stringb_t, elem_compare_t >		find_t;
	typedef typename find_t::find_chars_t                                       find_chars_t;


	PFX_INLINE int operator () (const string_type1& str1,const string_type2& str2) const
	{
		return compare(str1, str2);
	}
	static PFX_INLINE int compare(const string_type1& str1,const string_type2& str2)
	{
		int cmp_result;
		switch (cmp_type)
		{
		case CMP_ALL_STRING_SAME:
			cmp_result = find_t::same_string(str1, str2);
			break;
		case CMP_SAME_AS_ONE_STRING:
			{
				usize__t same_count = 0;
				cmp_result = find_t::same_string(str1, str2, same_count);
				if (same_count)
				{
					cmp_result = 0;
				}
			}
			break;
		default:
			cmp_result = find_t::same_string(str1, str2);
			break;
		}

	
		return cmp_result;
	}
	static PFX_INLINE int compare(const string_type1& str1, const element_t* str_ptr, 
		usize__t str_size)
	{
		int cmp_result;
		switch (cmp_type)
		{
		case CMP_ALL_STRING_SAME:
			cmp_result = find_chars_t::same_string(str1.get_string(), str1.get_length(),
				str_ptr, str_size);
			break;
		case CMP_SAME_AS_ONE_STRING:
		{
			usize__t same_count = 0;
			cmp_result = find_chars_t::same_string(str1.get_string(), str1.get_length(),
				str_ptr, str_size, same_count);
			if (same_count)
			{
				cmp_result = 0;
			}
		}
			break;
		default:
			cmp_result = find_chars_t::same_string(str1.get_string(), str1.get_length(),
				str_ptr, str_size);
			break;
		}


		return cmp_result;
	}
};

#define pfx_memcmp memcmp
#define pfx_strcmp strcmp

#define pfx_wmemcmp wmemcmp
#define pfx_wstrcmp wcscmp

PFX_INLINE int compare_chr_mem(const char_t* PARAM_IN str1, unsigned int str1_len,
	const char_t* PARAM_IN str2, unsigned int str2_len)
{
	int cmp_result;
	int min_len = (str2_len > str1_len) ? str1_len : str2_len;
	cmp_result = pfx_memcmp(str1, str2, min_len);
	if (0 == cmp_result)
	{
		return (str1_len - str2_len);
	}
	else
	{
		return cmp_result;
	}
}

template < class ascii_string_typeA, class ascii_string_typeB = ascii_string_typeA >
struct PFX_DATA_TEMPLATE_API ascii_string_compare
{
	typedef ascii_string_typeA	stringa_t;
	typedef ascii_string_typeB		stringb_t;
	typedef typename stringa_t::element_t			element_t;

	PFX_INLINE int operator () (const stringa_t& str1, const stringb_t& str2) const
	{
		return compare(str1, str2);
	}

	static PFX_INLINE int compare(const stringa_t& str1,const stringb_t& str2)
	{
		return compare_chr_mem(str1.get_string(), str1.get_length(), str2.get_string(), str2.get_length());
	}

};

template < class ascii_string_typeA >
struct PFX_DATA_TEMPLATE_API ascii_string_compare_withchars
{
	typedef ascii_string_typeA	stringa_t;
	typedef typename stringa_t::element_t			element_t;

	PFX_INLINE int operator () (const stringa_t& str1, const char* PARAM_IN str2) const
	{
		return compare(str1, str2);
	}

	static PFX_INLINE int compare(const stringa_t& str1, const char* PARAM_IN str2)
	{
		return pfx_strcmp(str1.get_string(), str2);
	}
};

//////////////////////////////////////////////////////////////////////////
PFX_INLINE int compare_wchr_mem(const utf_char_t* PARAM_IN str1, unsigned int str1_len,
	const utf_char_t* PARAM_IN str2, unsigned int str2_len)
{
	int cmp_result;
	int min_len = (str2_len > str1_len) ? str1_len : str2_len;
	cmp_result = pfx_memcmp(str1, str2, min_len);
	if (0 == cmp_result)
	{
		return (str1_len - str2_len);
	}
	else
	{
		return cmp_result;
	}
}

template < class utf_string_typeA, class utf_string_typeB = utf_string_typeA >
struct PFX_DATA_TEMPLATE_API utf_string_compare
{
	typedef utf_string_typeA	stringa_t;
	typedef utf_string_typeB	stringb_t;
	typedef typename stringa_t::element_t			element_t;

	PFX_INLINE int operator () (const stringa_t& str1, const stringb_t& str2) const
	{
		return compare(str1, str2);
	}

	static PFX_INLINE int compare(const stringa_t& str1, const stringb_t& str2)
	{
		return compare_wchr_mem(str1.get_string(), str1.get_length(), str2.get_string(), str2.get_length());
	}
};

template < class utf_string_typeA >
struct PFX_DATA_TEMPLATE_API utf_string_compare_withchars
{
	typedef utf_string_typeA	stringa_t;
	typedef typename stringa_t::element_t			element_t;

	PFX_INLINE int operator () (const stringa_t& str1, const utf_char_t* PARAM_IN str2) const
	{
		return compare(str1, str2);
	}

	static PFX_INLINE int compare(const stringa_t& str1, const utf_char_t* PARAM_IN str2)
	{
		return pfx_wstrcmp(str1.get_string(), str2);
	}
};

PECKER_END



#endif //PECKER_STRING_COMPARE_H_
