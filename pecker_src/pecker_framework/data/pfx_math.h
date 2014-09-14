/*
* pfx_math.h
*
*  Created on: 2014-9-13
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/
#ifndef		PFX_MATH_H_
#define		PFX_MATH_H_

#include "../pfx_defines.h"

#include "pfx_math_method.h"

#include "pfx_vector4_param.h"

#if (MATRIX_OPTIMIZATION_CONFIG == NO_MATRIX_OPTIMIZATION)
#include "pfx_simd_std.h"
#endif

#if (MATRIX_OPTIMIZATION_CONFIG == INTEL_SSE)
#include "pfx_simd_sse.h"
#endif

#if (MATRIX_OPTIMIZATION_CONFIG == ARM_NEON)
#include "pfx_simd_neon.h"
#endif

#endif			//PFX_MATH_H_
