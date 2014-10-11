/*
 * pfx_simd_fmul_sse.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMUL_SSE_H_
#define		PFX_SIMD_FMUL_SSE_H_

#include "../pfx_simd_fmul_std.h"
#include "../pfx_simd_param_sse.h"

PECKER_BEGIN

// 乘法
typedef struct st_array_fmul_unsafe_sse
{
	static PFX_FORCE_INLINE __m128 mul_const(__m128 PARAM_IN vec, float_t val)
	{
		__m128 _val = _mm_set_ps1(val);
		return _mm_mul_ps(vec, _val);
	}

	static PFX_FORCE_INLINE __m128 mul(__m128 PARAM_IN vec_a, __m128 PARAM_IN  vec_b)
	{
		return _mm_mul_ps(vec_a, vec_b);
	}


	static PFX_FORCE_INLINE float_t* operate(float_t*  PARAM_INOUT dst_ptr,
	const float_t cst,
	usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PARAM_INOUT dst_ptr,
		const float_t cst,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PARAM_INOUT dst_ptr,
		const float_t cst,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PARAM_INOUT dst_ptr,
		const float_t cst,
		usize__t count)
	{
		return dst_ptr;
	}


	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src_ptr,
		const float_t cst,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const float_t cst,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const float_t cst,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const float_t cst,
		usize__t count)
	{
		return dst_ptr;
	}




	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		return dst_ptr;
	}



	static PFX_FORCE_INLINE float_t* operate(float_t*  PARAM_INOUT dst_ptr,
		const float_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}
	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

}array_fmul_unsafe_sse_t;

PFX_INLINE simd_fmul_unsafe_t*	init_simd_fmul_sse(simd_fmul_unsafe_t& __fmul)
{
	__fmul.fmul_const_replace		 = array_fmul_unsafe_std_t::operate;
	__fmul.fvec2_mul_const_replace	 = array_fmul_unsafe_std_t::operate;
	__fmul.fvec3_mul_const_replace	 = array_fmul_unsafe_std_t::operate;
	__fmul.fvec4_mul_const_replace	 = array_fmul_unsafe_std_t::operate;
	__fmul.fmul_const				 = array_fmul_unsafe_std_t::operate;
	__fmul.fvec2_mul_const			 = array_fmul_unsafe_std_t::operate;
	__fmul.fvec3_mul_const			 = array_fmul_unsafe_std_t::operate;
	__fmul.fvec4_mul_const			 = array_fmul_unsafe_std_t::operate;
	__fmul.fmul						 = array_fmul_unsafe_std_t::operate;
	__fmul.fvec2_mul				 = array_fmul_unsafe_std_t::operate;
	__fmul.fvec3_mul				 = array_fmul_unsafe_std_t::operate;
	__fmul.fvec4_mul				 = array_fmul_unsafe_std_t::operate;
	__fmul.fmul_relpace				 = array_fmul_unsafe_std_t::operate;
	__fmul.fvec2_mul_relpace		 = array_fmul_unsafe_std_t::operate;
	__fmul.fvec3_mul_relpace		 = array_fmul_unsafe_std_t::operate;
	__fmul.fvec4_mul_relpace		 = array_fmul_unsafe_std_t::operate;
	return &__fmul;
}
PECKER_END

#endif			//PFX_SIMD_FMUL_H_
