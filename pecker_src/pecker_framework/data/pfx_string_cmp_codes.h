/*  pfx_string_cmp_codes.h
*		Created on: 2014-5-25
*      Author: 李镇城  （ cut / cutxyz）
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/

#ifndef PECKER_STRING_CMP_CODES_H_
#define PECKER_STRING_CMP_CODES_H_

#include "pfx_string_compare.h"

PECKER_BEGIN

#define PFX_FCHR_OP_TEMPALTE	template < class element_t, class elem_compare >
#define PFX_FCHR_OP						find_string_operate < element_t, elem_compare >
#define PFX_FCHR_OP_TYPE				typename find_string_operate < element_t, elem_compare >

#define PFX_FCSTR_OP_TEMPALTE template < class stringA, class stringB, class elem_compare >
#define PFX_FCSTR_OP						find_cstrstring_operate < stringA, stringB, elem_compare >
#define PFX_FCSTR_OP_TYPE			typename find_cstrstring_operate < stringA, stringB, elem_compare >


PFX_FCHR_OP_TEMPALTE
PFX_INLINE int PFX_FCHR_OP::same_string (const PFX_FCHR_OP_TYPE::element_t* PARAM_IN str_string_ptr,
	usize__t str_size,
	const PFX_FCHR_OP_TYPE::element_t* PARAM_IN str_cmp_string_ptr,
	usize__t cmp_str_size)
{
	typedef PFX_FCHR_OP_TYPE::elem_compare_t elem_compare_t;

	if ((str_string_ptr == str_cmp_string_ptr && str_size == cmp_str_size) || 
		(!str_string_ptr && !str_cmp_string_ptr))
	{
		return 0;
	}
	usize__t min_size = (str_size > cmp_str_size)?(cmp_str_size):(str_size);
	int cmp_result = 0;

	for (uindex_t i=0; i<min_size; ++i)
	{
		cmp_result = elem_compare_t::compare (str_string_ptr[i], str_cmp_string_ptr[i]);
		if (cmp_result)
		{
			break;
		}
	}
	if (!cmp_result)
	{
		cmp_result = str_size - min_size;
	}
	return cmp_result;
}

PFX_FCHR_OP_TEMPALTE
PFX_INLINE int PFX_FCHR_OP::same_string (const PFX_FCHR_OP_TYPE::element_t* PARAM_IN str_string_ptr,
	usize__t str_size,
	const PFX_FCHR_OP_TYPE::element_t* PARAM_IN str_cmp_string_ptr,
	usize__t cmp_str_size,
	usize__t& same_count)
{
	typedef PFX_FCHR_OP_TYPE::elem_compare_t elem_compare_t;

	if (str_string_ptr == str_cmp_string_ptr && str_size == cmp_str_size)
	{
		same_count = str_size;
		return 0;
	}
	if	(!str_string_ptr && !str_cmp_string_ptr)
	{
		same_count = 0;
		return 0;
	}

	usize__t min_size = (str_size > cmp_str_size)?(cmp_str_size):(str_size);
	int cmp_result = 0;
	uindex_t i=0;
	for (; i<min_size; ++i)
	{
		cmp_result = elem_compare_t::compare (str_string_ptr[i], str_cmp_string_ptr[i]);
		if (cmp_result)
		{
			break;
		}
	}
	same_count = i;
	if (!cmp_result)
	{
		cmp_result = str_size - min_size;
	}
	return cmp_result;
}

PFX_FCHR_OP_TEMPALTE
PFX_INLINE uindex_t PFX_FCHR_OP::find_first_string (
																								const PFX_FCHR_OP_TYPE::element_t* PARAM_IN str_string_ptr,
																								usize__t str_size,
																								const PFX_FCHR_OP_TYPE::element_t* PARAM_IN str_cmp_string_ptr,
																								usize__t cmp_str_size)
{
	typedef PFX_FCHR_OP_TYPE::element_t element_t;

	if (cmp_str_size > str_size)
	{	
		return INVALID_VALUE;
	}

	const element_t* begin_ptr	= str_string_ptr;
	const element_t* end_ptr		= str_string_ptr + str_size - 1;
	if (begin_ptr <= str_cmp_string_ptr && end_ptr >= str_cmp_string_ptr)
	{
		return (uindex_t)(str_cmp_string_ptr - begin_ptr);
	}

	uindex_t i =0;
	str_size = str_size - cmp_str_size + 1;
	do
	{
		if (0 == same_string(str_string_ptr + i, cmp_str_size, str_cmp_string_ptr, cmp_str_size))
		{
			return i;
		}
		++i;
	}
	while (i < str_size);

	return INVALID_VALUE;
}

PFX_FCHR_OP_TEMPALTE
PFX_INLINE boolean_t	PFX_FCHR_OP::find_near_string (
	const PFX_FCHR_OP_TYPE::element_t* PARAM_IN str_string_ptr,
	usize__t str_size,
	const PFX_FCHR_OP_TYPE::element_t* PARAM_IN str_cmp_string_ptr,
	usize__t cmp_str_size,	
	usize__t& same_chars_count)
{
	typedef PFX_FCHR_OP_TYPE::element_t element_t;

	const element_t* begin_ptr	= str_string_ptr;
	const element_t* end_ptr		= str_string_ptr + str_size - 1;
	if (begin_ptr <= str_cmp_string_ptr && end_ptr >= str_cmp_string_ptr)
	{
		uindex_t offset =  (uindex_t)(str_cmp_string_ptr - begin_ptr);
		if (cmp_str_size + offset > str_size)
		{
			same_chars_count = str_size - offset;
		}
		else
		{
			same_chars_count = cmp_str_size;
		}
		return offset;
	}

	begin_ptr	= str_cmp_string_ptr;
	end_ptr		= str_cmp_string_ptr + cmp_str_size - 1;
	if (begin_ptr <= str_string_ptr && end_ptr >= str_string_ptr)
	{
		uindex_t offset =  (uindex_t)(str_string_ptr - begin_ptr);
		if (str_size + offset > cmp_str_size)
		{
			same_chars_count = cmp_str_size - offset;
		}
		else
		{
			same_chars_count = str_size;
		}
		return offset;
	}

	uindex_t i =0;
	usize__t min_size = (str_size > cmp_str_size)?(cmp_str_size):(str_size);
	usize__t cmp_loop = str_size - min_size;
	same_chars_count = 0;
	do
	{
		if (0 == same_string(str_string_ptr + i, min_size, str_cmp_string_ptr, min_size, same_chars_count) && same_chars_count > 0)
		{
			return i;
		}
		++i;
	}
	while (i < cmp_loop);

	if (str_size > min_size)
	{
		
		do 
		{
			usize__t cmp_size = str_size - i;
			cmp_size = (cmp_size > min_size)?min_size:cmp_size;
			if (0 == same_string(str_string_ptr + i, cmp_size, str_cmp_string_ptr, cmp_size, same_chars_count) && same_chars_count > 0)
			{
				return i;
			}
			++i;
		} while (i < str_size);
	}


	return INVALID_VALUE;
}



PFX_FCSTR_OP_TEMPALTE
PFX_INLINE int PFX_FCSTR_OP::same_string (const PFX_FCSTR_OP_TYPE::stringa_t& str1, 
const PFX_FCSTR_OP_TYPE::stringb_t& str2)
{
	typedef PFX_FCSTR_OP_TYPE::const_iteratorA_t const_iteratorA_t;
	typedef PFX_FCSTR_OP_TYPE::const_iteratorB_t const_iteratorB_t;

	typedef PFX_FCSTR_OP_TYPE::element_t				element_t;
	typedef PFX_FCSTR_OP_TYPE::elem_compare_t	elem_compare_t;

	const_iteratorA_t itrA; 
	const_iteratorB_t itrB;
	str1.begin(itrA);
	str2.begin(itrB);
	return same_string(itrA, itrB);
}

PFX_FCSTR_OP_TEMPALTE
PFX_INLINE int PFX_FCSTR_OP::same_string (const PFX_FCSTR_OP_TYPE::stringa_t& str1, 
const PFX_FCSTR_OP_TYPE::stringb_t& str2, usize__t& same_count)
{
	typedef PFX_FCSTR_OP_TYPE::const_iteratorA_t const_iteratorA_t;
	typedef PFX_FCSTR_OP_TYPE::const_iteratorB_t const_iteratorB_t;

	typedef PFX_FCSTR_OP_TYPE::element_t				element_t;
	typedef PFX_FCSTR_OP_TYPE::elem_compare_t	elem_compare_t;

	const_iteratorA_t itrA; 
	const_iteratorB_t itrB;
	str1.begin(itrA);
	str2.begin(itrB);
	return same_string(itrA, itrB, same_count);
}

PFX_FCSTR_OP_TEMPALTE
PFX_INLINE uindex_t	PFX_FCSTR_OP::find_first_string (const PFX_FCSTR_OP_TYPE::stringa_t& str1, 
const PFX_FCSTR_OP_TYPE::stringb_t& str2)
{
	typedef PFX_FCSTR_OP_TYPE::const_iteratorA_t const_iteratorA_t;
	typedef PFX_FCSTR_OP_TYPE::const_iteratorB_t const_iteratorB_t;

	typedef PFX_FCSTR_OP_TYPE::element_t				element_t;
	typedef PFX_FCSTR_OP_TYPE::elem_compare_t	elem_compare_t;

	const_iteratorA_t itrA; 
	const_iteratorB_t itrB;
	str1.begin(itrA);
	str2.begin(itrB);
	return find_first_string(itrA, itrB);
}

PFX_FCSTR_OP_TEMPALTE
PFX_INLINE uindex_t	PFX_FCSTR_OP::find_near_string (const PFX_FCSTR_OP_TYPE::stringa_t& str1, 
	const PFX_FCSTR_OP_TYPE::stringb_t& str2,
	usize__t& same_chars_count)
{
	typedef PFX_FCSTR_OP_TYPE::const_iteratorA_t const_iteratorA_t;
	typedef PFX_FCSTR_OP_TYPE::const_iteratorB_t const_iteratorB_t;

	typedef PFX_FCSTR_OP_TYPE::element_t				element_t;
	typedef PFX_FCSTR_OP_TYPE::elem_compare_t	elem_compare_t;

	const_iteratorA_t itrA; 
	const_iteratorB_t itrB;
	str1.begin(itrA);
	str2.begin(itrB);
	return find_near_string(itrA, itrB, same_chars_count);
}


PFX_FCSTR_OP_TEMPALTE
	PFX_INLINE int PFX_FCSTR_OP::same_string (PFX_FCSTR_OP_TYPE::const_iteratorA_t& str1, 
	PFX_FCSTR_OP_TYPE::const_iteratorB_t& str2)
{
	typedef PFX_FCSTR_OP_TYPE::const_iteratorA_t const_iteratorA_t;
	typedef PFX_FCSTR_OP_TYPE::const_iteratorB_t const_iteratorB_t;

	typedef PFX_FCSTR_OP_TYPE::element_t				element_t;
	typedef PFX_FCSTR_OP_TYPE::elem_compare_t	elem_compare_t;

	int cmp_result = 0;
	const_iteratorA_t* itrA_ptr = str1.cur_ptr();
	const_iteratorB_t* itrB_ptr = str2.cur_ptr();
	while (itrA_ptr && itrB_ptr)
	{
		cmp_result = elem_compare_t::compare (itrA_ptr->reference(), itrB_ptr->reference());
		if (cmp_result)
		{
			break;
		}
		itrA_ptr = itrA_ptr->increase ();
		itrB_ptr = itrB_ptr->increase ();
	}

	if (!cmp_result)
	{
		if (itrA_ptr)
		{
			cmp_result = 1;
		}
		else if (itrB_ptr)
		{
			cmp_result = -1;
		}

		//usize__t str1_size = str1.size();
		//usize__t str2_size = str2.size();
		//cmp_result = (str1_size < str2_size)?(-1):(str1_size - str2_size);
	}
	return cmp_result;
}

PFX_FCSTR_OP_TEMPALTE
	PFX_INLINE int PFX_FCSTR_OP::same_string (PFX_FCSTR_OP_TYPE::const_iteratorA_t& str1, 
	PFX_FCSTR_OP_TYPE::const_iteratorB_t& str2, usize__t& same_count)
{
	typedef PFX_FCSTR_OP_TYPE::const_iteratorA_t const_iteratorA_t;
	typedef PFX_FCSTR_OP_TYPE::const_iteratorB_t const_iteratorB_t;

	typedef PFX_FCSTR_OP_TYPE::element_t				element_t;
	typedef PFX_FCSTR_OP_TYPE::elem_compare_t	elem_compare_t;

	int cmp_result = 0;
	const_iteratorA_t* itrA_ptr = str1.cur_ptr();
	const_iteratorB_t* itrB_ptr = str2.cur_ptr();

	usize__t __same_count = 0;
	while (itrA_ptr && itrB_ptr)
	{
		cmp_result = elem_compare_t::compare (itrA_ptr->reference(), itrB_ptr->reference());
		if (cmp_result)
		{
			break;
		}
		itrA_ptr = itrA_ptr->increase ();
		itrB_ptr = itrB_ptr->increase ();
		++__same_count;
	}
	same_count = __same_count;
	if (!cmp_result)
	{
		if (itrA_ptr)
		{
			cmp_result = 1;
		}
		else if (itrB_ptr)
		{
			cmp_result = -1;
		}
		//usize__t str1_size = str1.size();
		//usize__t str2_size = str2.size();
		//cmp_result = (str1_size < str2_size)?(-1):(str1_size - str2_size);
	}
	return cmp_result;
}

PFX_FCSTR_OP_TEMPALTE
	PFX_INLINE uindex_t	PFX_FCSTR_OP::find_first_string (PFX_FCSTR_OP_TYPE::const_iteratorA_t& str1, 
	PFX_FCSTR_OP_TYPE::const_iteratorB_t& str2)
{
	typedef PFX_FCSTR_OP_TYPE::const_iteratorA_t const_iteratorA_t;
	typedef PFX_FCSTR_OP_TYPE::const_iteratorB_t const_iteratorB_t;

	typedef PFX_FCSTR_OP_TYPE::element_t				element_t;
	typedef PFX_FCSTR_OP_TYPE::elem_compare_t	elem_compare_t;
	usize__t size_a = str1.size();
	usize__t size_b = str2.size();
	 if (size_a < size_b || 0 == size_b)
	 {
		 return INVALID_VALUE;
	 }

	//int cmp_result = 0;
	const_iteratorA_t itrA; 
	const_iteratorB_t itrB;

	const_iteratorA_t* __itrA_ptr = str1.cur_ptr();
	uindex_t i=0;
	
	usize__t loop = size_a - size_b + 1;

	do
	{
		usize__t same_size = 0;
		itrA = str1;
		itrB = str2;
		same_string(itrA, itrB, same_size);
		if (same_size == size_b)
		{
			return i;
		}
		__itrA_ptr = __itrA_ptr->increase();
		++i;
	}while (i < loop);

	return INVALID_VALUE;
}

PFX_FCSTR_OP_TEMPALTE
	PFX_INLINE uindex_t	PFX_FCSTR_OP::find_near_string (const_iteratorA_t& str1, const_iteratorB_t& str2,
	usize__t& same_chars_count)
{
	typedef PFX_FCSTR_OP_TYPE::const_iteratorA_t const_iteratorA_t;
	typedef PFX_FCSTR_OP_TYPE::const_iteratorB_t const_iteratorB_t;

	typedef PFX_FCSTR_OP_TYPE::element_t				element_t;
	typedef PFX_FCSTR_OP_TYPE::elem_compare_t	elem_compare_t;

	if (0 == str1.size() || 0 == str2.size())
	{
		return INVALID_VALUE;
	}

	const_iteratorA_t itrA; 
	const_iteratorB_t itrB;

	const_iteratorA_t* __itrA_ptr = str1.cur_ptr();
	uindex_t i=0;
	same_chars_count = 0;
	while (__itrA_ptr)
	{
		itrA = str1;
		itrB = str2;
		same_string(itrA, itrB, same_chars_count);
		if (same_chars_count)
		{
			return i;
		}
		__itrA_ptr = __itrA_ptr->increase();
		++i;
	}
	return INVALID_VALUE;
}

PECKER_END



#endif //PECKER_STRING_CMP_CODES_H_
