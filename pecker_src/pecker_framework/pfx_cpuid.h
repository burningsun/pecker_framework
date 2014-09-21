/*
 * pfx_cpuid.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CPUID_H_
#define		PFX_CPUID_H_

#include "pfx_defines.h"

#define PFX_SUPPORT_SIMD_SSE_NONE	(0)	    // 不支持.
#define PFX_SUPPORT_SIMD_SSE_1	    (1)	    // SSE
#define PFX_SUPPORT_SIMD_SSE_2	    (1<<1)	// SSE2
#define PFX_SUPPORT_SIMD_SSE_3	    (1<<2)	// SSE3
#define PFX_SUPPORT_SIMD_SSE_3S	    (1<<3)	// SSSE3
#define PFX_SUPPORT_SIMD_SSE_41	    (1<<4)	// SSE4.1
#define PFX_SUPPORT_SIMD_SSE_42	    (1<<5)	// SSE4.2

#define PFX_SUPPORT_SIMD_AVX_NONE	        (0)     // 不支持
#define PFX_SUPPORT_SIMD_AVX_1	            (1)	    // AVX
#define PFX_SUPPORT_SIMD_AVX_2		        (1 << 1)// AVX2

#define PFX_SUPPORT_SIMD_NEON_NONE          (0)
#define PFX_SUPPORT_SIMD_NEON_1	            (1)	    // NEON
#define PFX_SUPPORT_SIMD_NEON_2		        (1 << 1)// NEONX2

bitfield_t Get_SIMD_SSE_support_mask();
bitfield_t Get_SIMD_AVX_support_mask();
bitfield_t Get_SIMD_NEON_support_mask();

#ifdef CPU_X86_ARCH
#include "pfx_cpu_x86.h"
#endif

#ifdef CPU_ARM_ARCH
#include "pfx_cpu_arm.h"
#endif


#endif			//PFX_CPUID_H_
