/*
 * pfx_math.h
 *
 *  Created on: 2013-10-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_MATH_H_
#define		PFX_MATH_H_


#include "../pfx_defines.h"

PFX_C_EXTERN_BEGIN

PFX_INLINE pfx_s64_t pfx_pow_N (pfx_sint_t X, pfx_sint_t EXP)
{
	pfx_s64_t value_ = 1;
	pfx_index_t i = 1;

	pfx_s64_t TEMPX = X;

	if (0 == EXP)
	{
		return 1;
	}
	while (EXP > 0)
	{
		if (EXP > i)
		{
			TEMPX *= X;

			value_ *= TEMPX;
			++i;
			EXP -=  i;
		}
		else
		{
			TEMPX = X;
			i = 1;
			value_ *= TEMPX;
			EXP -=  i;
		}
	}

	return value_;
}

PFX_C_EXTERN_END


#endif			//PFX_MATH_H_
