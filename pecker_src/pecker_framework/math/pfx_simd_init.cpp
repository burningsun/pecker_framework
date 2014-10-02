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
static volatile result_t binit_math = math_simd_init();

static simd_fmat_dot_unsafe_t gfmat_dot;

result_t math_simd_init()
{

	result_t res;
	if (!cpu_simd_finded)
	{
		cpu_simd_finded = PRINTF_CPU_INFO();
	}

	if (cpu_simd_finded)
	{
		res = PFX_STATUS_OK;
	}
	else
	{
		res = PFX_STATUS_FAIL;
	}

	init_simd_fmat_dot_std(gfmat_dot);

	return res;
};
PECKER_END



