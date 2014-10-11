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

#include "pfx_simd_param.h"

#if (MATRIX_OPTIMIZATION_CONFIG == NO_MATRIX_OPTIMIZATION)
#include "pfx_simd_std.h"
#endif

#if (MATRIX_OPTIMIZATION_CONFIG == INTEL_SSE)
#include "pfx_simd_sse.h"
#endif

#if (MATRIX_OPTIMIZATION_CONFIG == ARM_NEON)
#include "pfx_simd_neon.h"
#endif

PECKER_BEGIN
PFX_C_EXTERN_BEGIN
PFX_MATH_API result_t math_simd_init();
PFX_MATH_API const simd_fabs_unsafe_t          *  get_simd_fabs_unsafe();
PFX_MATH_API const simd_fadd_unsafe_t          *  get_simd_fadd_unsafe();
PFX_MATH_API const simd_fdiv_unsafe_t          *  get_simd_fdiv_unsafe();
PFX_MATH_API const simd_fvec_cross_unsafe_t    *  get_simd_fvec_cross_unsafe();
PFX_MATH_API const simd_fmat_det_unsafe_t      *  get_simd_fmat_det_unsafe();
PFX_MATH_API const simd_fmat_dot_unsafe_t      *  get_simd_fmat_dot_unsafe();
PFX_MATH_API const simd_fmat_inverse_unsafe_t  *  get_simd_fmat_inverse_unsafe();
PFX_MATH_API const simd_fvec_normalize_unsafe_t*  get_simd_fvec_normalize_unsafe();
PFX_MATH_API const simd_fmat_set_unsafe_t      *  get_simd_fmat_set_unsafe();
PFX_MATH_API const simd_fmat_transpose_unsafe_t*  get_simd_fmat_transpose_unsafe();
PFX_MATH_API const simd_fmul_unsafe_t          *  get_simd_fmul_unsafe();
PFX_MATH_API const simd_fsub_unsafe_t          *  get_simd_fsub_unsafe();
PFX_C_EXTERN_END


PECKER_END

#endif			//PFX_MATH_H_
