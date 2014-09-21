/*
 * pfx_cpu_x86.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CPU_X86_H_
#define		PFX_CPU_X86_H_

#include "pfx_defines.h"
#include "native/pfx_log.h"

PECKER_BEGIN
#ifdef CPU_X86_ARCH

// intrinsics
#if (defined(__GNUC__))	// GCC
#define CCPUID_X86	1	// 是x86平台.
#include <xmmintrin.h>	// MMX, SSE
//#include <cpuid.h>	// mac 中的 llvm-gcc有时找不到cpuid.h，而且它没有 __cpuid/__cpuid_count，干脆我们自己定义.
#ifndef __cpuid_count
// 下面代码出自 GCC 4.7.0(Fedora 17) 的 cpuid.h
#if defined(__i386__) && defined(__PIC__)
/* %ebx may be the PIC register.  */
#if __GNUC__ >= 3
#define __cpuid(level, a, b, c, d)			\
	__asm__("xchg{l}\t{%%}ebx, %1\n\t"			\
	"cpuid\n\t"					\
	"xchg{l}\t{%%}ebx, %1\n\t"			\
	: "=a" (a), "=r" (b), "=c" (c), "=d" (d)	\
	: "0" (level))

#define __cpuid_count(level, count, a, b, c, d)		\
	__asm__("xchg{l}\t{%%}ebx, %1\n\t"			\
	"cpuid\n\t"					\
	"xchg{l}\t{%%}ebx, %1\n\t"			\
	: "=a" (a), "=r" (b), "=c" (c), "=d" (d)	\
	: "0" (level), "2" (count))
#else
/* Host GCCs older than 3.0 weren't supporting Intel asm syntax
nor alternatives in i386 code.  */
#define __cpuid(level, a, b, c, d)			\
	__asm__("xchgl\t%%ebx, %1\n\t"			\
	"cpuid\n\t"					\
	"xchgl\t%%ebx, %1\n\t"			\
	: "=a" (a), "=r" (b), "=c" (c), "=d" (d)	\
	: "0" (level))

#define __cpuid_count(level, count, a, b, c, d)		\
	__asm__("xchgl\t%%ebx, %1\n\t"			\
	"cpuid\n\t"					\
	"xchgl\t%%ebx, %1\n\t"			\
	: "=a" (a), "=r" (b), "=c" (c), "=d" (d)	\
	: "0" (level), "2" (count))
#endif
#else
#define __cpuid(level, a, b, c, d)			\
	__asm__("cpuid\n\t"					\
	: "=a" (a), "=b" (b), "=c" (c), "=d" (d)	\
	: "0" (level))

#define __cpuid_count(level, count, a, b, c, d)		\
	__asm__("cpuid\n\t"					\
	: "=a" (a), "=b" (b), "=c" (c), "=d" (d)	\
	: "0" (level), "2" (count))
#endif	// #ifndef __cpuid_count
#endif	// #if (defined(__i386__) || defined(__x86_64__) )

#else
#if defined(_MSC_VER)	// MSVC

#define CCPUID_X86	1	// 是x86平台.
#if _MSC_VER >=1400	// VC2005
#include <intrin.h>	// CPUID, MMX, SSE
#elif _MSC_VER >=1200	// VC6
#include <xmmintrin.h>	// MMX, SSE
#endif	// #if _MSC_VER >=1400

#else
#error Only supports MSVC or GCC.
#endif

#endif	// #if defined(__GNUC__)



PFX_C_EXTERN_BEGIN
void PFX_EXPORT_API getcpuidex(unsigned int CPUInfo[4], unsigned int InfoType, unsigned int ECXValue);
void PFX_EXPORT_API getcpuid(unsigned int CPUInfo[4], unsigned int InfoType);
int PFX_EXPORT_API cpu_getvendor(char* pvendor);
int PFX_EXPORT_API cpu_getbrand(char* pbrand);
PFX_C_EXTERN_END

// FUNC ID = 1
#define BIT_D_SSE    (1<<25)	
#define BIT_D_SSE2   (1<<26)
#define BIT_C_SSE3   (1<< 0)	
#define BIT_C_SSSE3  (1<< 9)	
#define BIT_C_SSE41  (1<<19)
#define BIT_C_SSE42  (1<<20)
// FUNC ID = 7
#define BIT_C_AVX    (1<<28)	
#define BIT_B_AVX2   (1<< 5)

#endif CPU_X86_ARCH





PECKER_END

#endif	 //PFX_CPU_X86_H_
