/*  Created on: 2012-12-1
*      Author: 李镇城  （ cut / cutxyz）
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/

#ifndef PECKER_VALUE_COMPARE_H_
#define PECKER_VALUE_COMPARE_H_

#include "../pfx_defines.h"

PFX_BEGIN

#define  COMPARE_TWO_VALUE(A,B,CMP) CMP(A,B)
typedef int (*CMP_A_AND_B)(void* A,void* B) ;
inline int cmp_a_and_b_int(int A, int B)
{
	return (A - B);
}
inline int cmp_a_and_b_char(char A, char B)
{
	return (A - B);
}
inline int cmp_a_and_b_wchar(wchar_t A, wchar_t B)
{
	return (A - B);
}
inline int cmp_a_and_b_short(short A,short B)
{
	return (A-B);
}

PFX_END

#ifdef __cplusplus

PECKER_BEGIN

// 带compare方法的类的扩展比较
template< class compare_value_ext >
struct pecker_value_compare_extern
{
inline int operator()(const compare_value_ext& value1,const compare_value_ext& value2) const
{
	return value1.compare(value2);
}
static inline int compare(const compare_value_ext& value1,const compare_value_ext& value2)
{
	return value1.compare(value2);
}
};

// 多种基本类型比较
template< class classtype >
struct pecker_value_compare
{
inline int operator () (const classtype& value1,const classtype& value2) const;
static inline int compare(const classtype& value1,const classtype& value2);
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
int pecker_value_compare<classtype>:: compare(const classtype& value1,const classtype& value2)
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
struct pecker_value_compare<char>
{
//static int tst_char_cmp_count;
inline int operator () (const char &value1,const char &value2) const
{
	return (value1 - value2);
}
static inline int compare(const char &value1,const char &value2)
{
	//++tst_char_cmp_count;
	return (value1 - value2);
}
};

template<>
struct pecker_value_compare<short>
{
inline int operator () (const short &value1,const short &value2) const
{
	return (value1 - value2);
}

static inline int compare(const short &value1,const short &value2)
{
	return (value1 - value2);
}
};

template<>
struct pecker_value_compare<int>
{
inline int operator () (const int &value1,const int &value2) const
{
	return (value1 - value2);
}

static inline int compare(const int &value1,const int &value2)
{
	return (value1 - value2);
}
};


PECKER_END

#endif

#endif //PECKER_VALUE_COMPARE_H_