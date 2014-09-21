/*
* pfx_simd_init.cpp
*
*  Created on: 2014-9-13
*      Author: ¿Ó’Ú≥«  £® cut / cutxyz£© (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#include "pfx_math.h"
#include "../pfx_cpuid.h"

PECKER_BEGIN

extern bool PRINTF_CPU_INFO();
static volatile bool cpu_simd_finded = PRINTF_CPU_INFO();

result_t math_simd_init()
{
	if (cpu_simd_finded)
	{
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_ERROR_;
	}
};
PECKER_END



