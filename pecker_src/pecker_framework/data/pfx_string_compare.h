/*  pfx_string_compare.h
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
	CMP_FIST_PART_SAME,
	CMP_CONTAINS_OTHER,

	STRING_CMP_TYPE_COUNT
}STRING_CMP_TYPE_t;

template < class element_t, 
					class elem_compare = pecker_value_compare < element_t > >
struct find_string_operate
{
	typedef element_t				element_t;
	typedef elem_compare		elem_compare_t;

	typedef typename const element_t* cmptype_a_t;
	typedef typename const element_t* cmptype_b_t;

	typedef typename find_string_operate< element_t, elem_compare_t >	find_string_t;

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
					class elem_compare = pecker_value_compare < stringA::element_t > >
struct find_cstrstring_operate
{
	typedef stringA		stringa_t;
	typedef stringB		stringb_t;

	typedef typename stringa_t::const_iterator_t		const_iteratorA_t;
	typedef typename stringb_t::const_iterator_t		const_iteratorB_t;

	typedef typename const stringa_t& cmptype_a_t;
	typedef typename const stringb_t& cmptype_b_t;

	typedef typename stringa_t::element_t			element_t;
	typedef elem_compare										elem_compare_t;

	typedef find_cstrstring_operate < stringa_t, stringb_t, elem_compare_t > find_string_t;

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
	class string_type2,
	const enum_int_t cmp_type = 0>  
struct PFX_DATA_TEMPALE_API string_compare
{
	PFX_INLINE int operator () (const string_type1& str1,const string_type2& str2) const;
	static PFX_INLINE int compare(const string_type1& str1,const string_type2& str2);
	static PFX_INLINE int compare(const string_type1& str1,const string_type2& str2, 
															uindex_t &__index, usize__t &__same_size);
};

PECKER_END



#endif //PECKER_STRING_COMPARE_H_
