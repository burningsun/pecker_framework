/*
 * pfx_cpu_x86.cpp
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_cpu_x86.h"
#include "pfx_cpuid.h"

PECKER_BEGIN
#ifdef CPU_X86_ARCH

void getcpuidex(unsigned int CPUInfo[4], unsigned int InfoType, unsigned int ECXValue)
{
#if defined(__GNUC__)    // GCC
	__cpuid_count(InfoType, ECXValue, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#elif defined(_MSC_VER)    // MSVC
#if defined(_WIN64) || _MSC_VER>=1600    // 64位下不支持内联汇编. 1600: VS2010, 据说VC2008 SP1之后才支持__cpuidex.
	__cpuidex((int*)(void*)CPUInfo, (int)InfoType, (int)ECXValue);
#else
	if (NULL == CPUInfo)    return;
	_asm{
		// load. 读取参数到寄存器.
		mov edi, CPUInfo;    // 准备用edi寻址CPUInfo
		mov eax, InfoType;
		mov ecx, ECXValue;
		// CPUID
		cpuid;
		// save. 将寄存器保存到CPUInfo
		mov[edi], eax;
		mov[edi + 4], ebx;
		mov[edi + 8], ecx;
		mov[edi + 12], edx;
	}
#endif
#endif    // #if defined(__GNUC__)
}

void getcpuid(unsigned int CPUInfo[4], unsigned int InfoType)
{
#if defined(__GNUC__)    // GCC
	__cpuid(InfoType, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#elif defined(_MSC_VER)    // MSVC
#if _MSC_VER>=1400    // VC2005才支持__cpuid
	__cpuid((int*)(void*)CPUInfo, (int)InfoType);
#else
	getcpuidex(CPUInfo, InfoType, 0);
#endif
#endif    // #if defined(__GNUC__)
}

// 取得CPU厂商（Vendor）.
//
// result: 成功时返回字符串的长度（一般为12）。失败时返回0.
// pvendor: 接收厂商信息的字符串缓冲区。至少为13字节.
int cpu_getvendor(char* pvendor)
{
	unsigned int dwBuf[4];
	if (NULL == pvendor)    return 0;
	// Function 0: Vendor-ID and Largest Standard Function
	getcpuid(dwBuf, 0);
	// save. 保存到pvendor
	*(unsigned int *)&pvendor[0] = dwBuf[1];    // ebx: 前四个字符.
	*(unsigned int *)&pvendor[4] = dwBuf[3];    // edx: 中间四个字符.
	*(unsigned int *)&pvendor[8] = dwBuf[2];    // ecx: 最后四个字符.
	pvendor[12] = '\0';
	return 12;
}

// 取得CPU商标（Brand）.
//
// result: 成功时返回字符串的长度（一般为48）。失败时返回0.
// pbrand: 接收商标信息的字符串缓冲区。至少为49字节.
int cpu_getbrand(char* pbrand)
{
	unsigned int dwBuf[4];
	if (NULL == pbrand)    return 0;
	// Function 0x80000000: Largest Extended Function Number
	getcpuid(dwBuf, 0x80000000U);
	if (dwBuf[0] < 0x80000004U)    return 0;
	// Function 80000002h,80000003h,80000004h: Processor Brand String
	getcpuid((unsigned int *)&pbrand[0], 0x80000002U);    // 前16个字符.
	getcpuid((unsigned int *)&pbrand[16], 0x80000003U);    // 中间16个字符.
	getcpuid((unsigned int *)&pbrand[32], 0x80000004U);    // 最后16个字符.
	pbrand[48] = '\0';
	return 48;
}

static bitfield_t gSIMD_SSE_MSK  = PFX_SUPPORT_SIMD_SSE_NONE;
static bitfield_t gSIMD_AVX_MSK  = PFX_SUPPORT_SIMD_AVX_NONE;
static bitfield_t gSIMD_NEON_MSK = PFX_SUPPORT_SIMD_NEON_NONE;


	


bool PRINTF_CPU_INFO()
{
	char szBuf[64];
	cpu_getvendor(szBuf);
	PECKER_LOG_INFO("CPU Vendor:%s", szBuf);

	cpu_getbrand(szBuf);
	PECKER_LOG_INFO("CPU Name: %s", szBuf);

	unsigned int dwBuf[4];
	getcpuid(dwBuf, 1);

	gSIMD_SSE_MSK = PFX_SUPPORT_SIMD_SSE_NONE;
	gSIMD_SSE_MSK |= (dwBuf[3] & BIT_D_SSE) ?  (PFX_SUPPORT_SIMD_SSE_1)   : (0);
	gSIMD_SSE_MSK |= (dwBuf[3] & BIT_D_SSE2) ? (PFX_SUPPORT_SIMD_SSE_2)   : (0);
	gSIMD_SSE_MSK |= (dwBuf[2] & BIT_C_SSE3) ? (PFX_SUPPORT_SIMD_SSE_3)   : (0);
	gSIMD_SSE_MSK |= (dwBuf[2] & BIT_C_SSSE3) ? (PFX_SUPPORT_SIMD_SSE_3S) : (0);
	gSIMD_SSE_MSK |= (dwBuf[2] & BIT_C_SSE41) ? (PFX_SUPPORT_SIMD_SSE_41) : (0); 
	gSIMD_SSE_MSK |= (dwBuf[2] & BIT_C_SSE42) ? (PFX_SUPPORT_SIMD_SSE_42) : (0);

	PECKER_LOG_INFO("CPU SSE: %08X", gSIMD_SSE_MSK);

	getcpuid(dwBuf, 7);

	gSIMD_AVX_MSK = PFX_SUPPORT_SIMD_SSE_NONE;
	gSIMD_AVX_MSK |= (dwBuf[2] & BIT_C_AVX) ? (PFX_SUPPORT_SIMD_AVX_1)  : (0);
	gSIMD_AVX_MSK |= (dwBuf[2] & BIT_B_AVX2) ? (PFX_SUPPORT_SIMD_AVX_2) : (0);
	PECKER_LOG_INFO("CPU AVX: %08X", gSIMD_AVX_MSK);

	gSIMD_NEON_MSK = PFX_SUPPORT_SIMD_NEON_NONE;
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

#endif	 //CPU_X86_ARCH

PECKER_END
