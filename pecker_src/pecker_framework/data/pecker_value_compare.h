/*  Created on: 2012-12-1
*      Author: 李镇城  （ cut / cutxyz）
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/

#ifndef PECKER_VALUE_COMPARE_H_
#define PECKER_VALUE_COMPARE_H_

#include "../CPeckerObject.h"

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

#endif //PECKER_VALUE_COMPARE_H_