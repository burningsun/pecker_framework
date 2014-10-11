/*
 * pfx_simd_fabs_sse.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FABS_SSE_H_
#define		PFX_SIMD_FABS_SSE_H_

#include "../pfx_simd_fabs_std.h"


PECKER_BEGIN

// 绝对值
typedef struct st_array_fabs_ssse3
{
	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
	usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t*  PARAM_INOUT dst_ptr,
		 usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PARAM_INOUT dst_ptr, usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}
	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PARAM_INOUT dst_ptr,
		usize__t count)
	{
		return dst_ptr;
	}
}array_fabs_ssse3_unsafe_t;


PFX_INLINE simd_fabs_unsafe_t*	init_simd_fabs_sse(simd_fabs_unsafe_t& __fabs)
{
	__fabs.fabs              = array_fabs_std_unsafe_t::operate;
	__fabs.fabs 			 = array_fabs_std_unsafe_t::operate;
							
	__fabs.fvec2_abs		 = array_fabs_std_unsafe_t::operate;
	__fabs.fvec2_abs_replace = array_fabs_std_unsafe_t::operate;
							
	__fabs.fvec3_abs		 = array_fabs_std_unsafe_t::operate;
	__fabs.fvec3_abs_replace = array_fabs_std_unsafe_t::operate;
						
	__fabs.fvec4_abs		 = array_fabs_std_unsafe_t::operate;
	__fabs.fvec4_abs_replace = array_fabs_std_unsafe_t::operate;

	return &__fabs;
}










PECKER_END





#endif			//PFX_SIMD_FABS_SSE_H_
