/*  Created on: 2012-12-1
*      Author: 李镇城  （ cut / cutxyz）
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/

#ifndef PECKER_VALUE_COMPARE_H_
#define PECKER_VALUE_COMPARE_H_

#include "../pfx_defines.h"

#define  COMPARE_TWO_VALUE(A,B,CMP) CMP(A,B)
typedef int (*CMP_A_AND_B)(void* A,void* B) ;
typedef int (*compare_two_value_func)(long_t A,long_t B) ;
typedef int (*compare_two_string_func)(const char_t* pstr_a,nsize__t nstr_a_len,
	const char_t* pstr_b,nsize__t nstr_b_len);
typedef int (*compare_two_string_ex_func)(const char_t* pstr_a,nsize__t nstr_a_len,
	const char_t* pstr_b,nsize__t nstr_b_len,nsize__t* psame_count);


PFX_INLINE int cmp_a_and_b_long (long_t A, long_t B)
{
	return (A - B);
}

PFX_INLINE int cmp_a_and_b_int (sint_t A, sint_t B)
{
	return (A - B);
}
PFX_INLINE int cmp_a_and_b_char (char_t A, char_t B)
{
	return (A - B);
}
PFX_INLINE int cmp_a_and_b_wchar (wchar_t A, wchar_t B)
{
	return (A - B);
}
PFX_INLINE int cmp_a_and_b_short (short_t A,short_t B)
{
	return (A-B);
}

PFX_INLINE int cmp_a_and_b_string_a(const char_t* pstr_a,nsize__t nstr_a_len,
	const char_t* pstr_b,nsize__t nstr_b_len)
{
	nsize__t min_len = 0;
	index_t i;
	int cmp_result = 0;
	int len_cmp_result = 0;

	RETURN_RESULT (null == pstr_a && null == pstr_b,0);
	RETURN_RESULT ((pstr_a == pstr_b),(nstr_a_len - nstr_b_len));

	min_len = (nstr_a_len>nstr_b_len) ? nstr_b_len : nstr_a_len;

	for (i=0;i<min_len;++i)
	{
		cmp_result = pstr_a[i] - pstr_b[i];
		if (0 != cmp_result)
		{
			break;
		}
	}

	RETURN_RESULT (0 != cmp_result,cmp_result);
	return (nstr_a_len - nstr_b_len);
}

PFX_INLINE int cmp_a_and_b_string_a_ex(const char_t* pstr_a,
	nsize__t nstr_a_len,const char_t* pstr_b,
	nsize__t nstr_b_len,nsize__t* psame_count)
{
	nsize__t min_len = 0;
	index_t i;
	int cmp_result = 0;
	int len_cmp_result = 0;

	RETURN_RESULT (null == pstr_a && null == pstr_b,0);
	RETURN_RESULT ((pstr_a == pstr_b),(nstr_a_len - nstr_b_len));

	min_len = (nstr_a_len>nstr_b_len) ? nstr_b_len : nstr_a_len;

	for (i=0;i<min_len;++i)
	{
		cmp_result = pstr_a[i] - pstr_b[i];
		if (0 != cmp_result)
		{
			break;
		}
	}

	SET_POINTER_VALUE (psame_count,i);

	RETURN_RESULT (0 != cmp_result,cmp_result);
	return (nstr_a_len - nstr_b_len);
}

PFX_INLINE int cmp_a_and_b_string_w(const utf_char_t* pstr_a,nsize__t nstr_a_len,
	const utf_char_t* pstr_b,nsize__t nstr_b_len)
{
	nsize__t min_len = 0;
	index_t i;
	int cmp_result = 0;
	int len_cmp_result = 0;

	RETURN_RESULT (null == pstr_a && null == pstr_b,0);
	RETURN_RESULT ((pstr_a == pstr_b),(nstr_a_len - nstr_b_len));

	min_len = (nstr_a_len>nstr_b_len) ? nstr_b_len : nstr_a_len;

	for (i=0;i<min_len;++i)
	{
		cmp_result = pstr_a[i] - pstr_b[i];
		if (0 != cmp_result)
		{
			break;
		}
	}

	RETURN_RESULT (0 != cmp_result,cmp_result);
	return (nstr_a_len - nstr_b_len);
}

PFX_INLINE int cmp_a_and_b_string_w_ex(const utf_char_t* pstr_a,
	nsize__t nstr_a_len,const utf_char_t* pstr_b,
	nsize__t nstr_b_len,nsize__t* psame_count)
{
	nsize__t min_len = 0;
	index_t i;
	int cmp_result = 0;
	int len_cmp_result = 0;

	RETURN_RESULT (null == pstr_a && null == pstr_b,0);
	RETURN_RESULT ((pstr_a == pstr_b),(nstr_a_len - nstr_b_len));

	min_len = (nstr_a_len>nstr_b_len) ? nstr_b_len : nstr_a_len;

	for (i=0;i<min_len;++i)
	{
		cmp_result = pstr_a[i] - pstr_b[i];
		if (0 != cmp_result)
		{
			break;
		}
	}

	SET_POINTER_VALUE (psame_count,i);

	RETURN_RESULT (0 != cmp_result,cmp_result);
	return (nstr_a_len - nstr_b_len);
}


PECKER_BEGIN

template< class  compare_type, typename compare_method >
PFX_DATA_TEMPLATE_API int  cmp_a_and_b_string_a_template(const compare_type* pstr_a,nsize__t nstr_a_len,
	const compare_type* pstr_b,nsize__t nstr_b_len)
{
	nsize__t min_len = 0;
	index_t i;
	int cmp_result = 0;
	int len_cmp_result = 0;

	RETURN_RESULT (null == pstr_a && null == pstr_b,0);
	RETURN_RESULT ((pstr_a == pstr_b),(nstr_a_len - nstr_b_len));

	min_len = (nstr_a_len>nstr_b_len) ? nstr_b_len : nstr_a_len;

	for (i=0;i<min_len;++i)
	{
		cmp_result = compare_method (pstr_a[i],pstr_b[i]);
		if (0 != cmp_result)
		{
			break;
		}
	}

	RETURN_RESULT (0 != cmp_result,cmp_result);
	return (nstr_a_len - nstr_b_len);
}

template< class  compare_type, typename compare_method >
PFX_DATA_TEMPLATE_API int  cmp_a_and_b_string_a_template_ex(const compare_type* pstr_a,nsize__t nstr_a_len,
	const compare_type* pstr_b,nsize__t nstr_b_len,nsize__t& same_count)
{
	nsize__t min_len = 0;
	index_t i;
	int cmp_result = 0;
	int len_cmp_result = 0;

	RETURN_RESULT (null == pstr_a && null == pstr_b,0);
	RETURN_RESULT ((pstr_a == pstr_b),(nstr_a_len - nstr_b_len));

	min_len = (nstr_a_len>nstr_b_len) ? nstr_b_len : nstr_a_len;

	for (i=0;i<min_len;++i)
	{
		cmp_result = compare_method (pstr_a[i],pstr_b[i]);
		if (0 != cmp_result)
		{
			break;
		}
	}
	same_count = i;

	RETURN_RESULT (0 != cmp_result,cmp_result);
	return (nstr_a_len - nstr_b_len);
}


// 带compare方法的类的扩展比较
template< class compare_value_ext >
struct PFX_DATA_TEMPLATE_API pecker_value_compare_extern
{
PFX_INLINE int operator() (const compare_value_ext& value1,const compare_value_ext& value2) const
{
	return value1.compare (value2);
}
static PFX_INLINE int compare (const compare_value_ext& value1,const compare_value_ext& value2)
{
	return value1.compare (value2);
}

PFX_INLINE int operator() (const compare_value_ext* value1,const compare_value_ext* value2) const
{
	if (value1)
	{
		return value1->compare (value2);
	}
	else if (!value2)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}
static PFX_INLINE int compare (const compare_value_ext* value1,const compare_value_ext* value2)
{
	if (value1 && value2)
	{
		return value1->compare (value2);
	}
	else if (!value2)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

};

// 多种基本类型比较
template< class classtype >
struct PFX_DATA_TEMPLATE_API pecker_value_compare
{
PFX_INLINE int operator () (const classtype& value1,const classtype& value2) const;
static PFX_INLINE int compare (const classtype& value1,const classtype& value2);
};

template< class classtype >
int pecker_value_compare<classtype>::operator () (const classtype& value1,const classtype& value2) const
{
if (value1 > value2)
{
	return 1;
}
else if (value1 < value2)
{
	return -1;
}
else
{
	return 0;
}

}
template< class classtype >
int pecker_value_compare<classtype>:: compare (const classtype& value1,const classtype& value2)
{
if (value1 > value2)
{
	return 1;
}
else if (value1 < value2)
{
	return -1;
}
else
{
	return 0;
}
}

template<>
struct PFX_DATA_TEMPLATE_API pecker_value_compare<char>
{
//static int tst_char_cmp_count;
PFX_INLINE int operator () (const char &value1,const char &value2) const
{
	return (value1 - value2);
}
static PFX_INLINE int compare (const char &value1,const char &value2)
{
	//++tst_char_cmp_count;
	return (value1 - value2);
}
};

template<>
struct PFX_DATA_TEMPLATE_API pecker_value_compare<short>
{
PFX_INLINE int operator () (const short &value1,const short &value2) const
{
	return (value1 - value2);
}

static PFX_INLINE int compare (const short &value1,const short &value2)
{
	return (value1 - value2);
}
};

template<>
struct PFX_DATA_TEMPLATE_API pecker_value_compare<int>
{
PFX_INLINE int operator () (const int &value1,const int &value2) const
{
	return (value1 - value2);
}

static PFX_INLINE int compare (const int &value1,const int &value2)
{
	return (value1 - value2);
}
};


PECKER_END



#endif //PECKER_VALUE_COMPARE_H_
