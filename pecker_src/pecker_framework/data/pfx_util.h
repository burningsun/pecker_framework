/*
 * pfx_util.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_UTIL_H_
#define		PFX_UTIL_H_

#include "../pfx_defines.h"

PFX_C_EXTERN_BEGIN

#define SWAP_VALUE(x,y,temp) \
{														\
	temp = x;									\
	x = y;											\
	y = temp;									\
};

PFX_C_EXTERN_END

#endif			//PFX_UTIL_H_
