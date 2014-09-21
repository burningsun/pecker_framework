/*
 * pfx_cpu_x86.cpp
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_cpu_arm.h"
#include "pfx_cpuid.h"

PECKER_BEGIN
#ifdef CPU_ARM_ARCH

static bitfield_t gSIMD_SSE_MSK  = PFX_SUPPORT_SIMD_SSE_NONE;
static bitfield_t gSIMD_AVX_MSK  = PFX_SUPPORT_SIMD_AVX_NONE;
static bitfield_t gSIMD_NEON_MSK = PFX_SUPPORT_SIMD_NEON_NONE;


	


bool PRINTF_CPU_INFO()
{
	gSIMD_SSE_MSK = PFX_SUPPORT_SIMD_SSE_NONE;
	PECKER_LOG_INFO("CPU SSE: %08X", gSIMD_SSE_MSK);

	gSIMD_AVX_MSK = PFX_SUPPORT_SIMD_SSE_NONE;
	PECKER_LOG_INFO("CPU AVX: %08X", gSIMD_AVX_MSK);

	gSIMD_NEON_MSK = PFX_SUPPORT_SIMD_NEON_1;
	PECKER_LOG_INFO("CPU NEON: %08X", gSIMD_NEON_MSK);

	return true;
}



bitfield_t Get_SIMD_SSE_support_mask()
{
	return gSIMD_SSE_MSK;
}
bitfield_t Get_SIMD_AVX_support_mask()
{
	return gSIMD_AVX_MSK;
}
bitfield_t Get_SIMD_NEON_support_mask()
{
	return gSIMD_NEON_MSK;
}

#endif	 //CPU_ARM_ARCH

PECKER_END
