/*
 * pfx_simd_fmatcross_sse.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMATCROSS_SSE_H_
#define		PFX_SIMD_FMATCROSS_SSE_H_

#include "../pfx_simd_fmatcross_std.h"

PECKER_BEGIN

typedef struct st_vector_cross_unsafe_sse
{
	static PFX_FORCE_INLINE VECTOR3F_t* cross
		(VECTOR3F_t& PFX_RESTRICT PARAM_INOUT dst,
		const VECTOR3F_t& PFX_RESTRICT PARAM_INOUT src1,
		const VECTOR3F_t& PFX_RESTRICT PARAM_INOUT src2)
	{
		return &dst;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* cross
		(VECTOR4F_t& PFX_RESTRICT PARAM_INOUT dst,
		const VECTOR4F_t& PFX_RESTRICT PARAM_INOUT src1,
		const VECTOR4F_t& PFX_RESTRICT PARAM_INOUT src2)
	{
		return &dst;
	}

}vector_cross_unsafe_sse_t;

PFX_INLINE simd_fvec_cross_unsafe_t*	init_simd_fvec_cross_sse(simd_fvec_cross_unsafe_t& __fcross)
{
	__fcross.fvec3_cross         = vector_cross_unsafe_std_t::cross;
	__fcross.fvec3_extern_cross  = vector_cross_unsafe_std_t::cross;
	return &__fcross;
}
PECKER_END

#endif			//PFX_SIMD_FMATCROSS_H_
