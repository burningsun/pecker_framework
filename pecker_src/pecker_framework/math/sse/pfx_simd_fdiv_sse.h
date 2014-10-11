/*
 * pfx_simd_fdiv_sse.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FDIV_SSE_H_
#define		PFX_SIMD_FDIV_SSE_H_

#include "../pfx_simd_fdiv_std.h"

PECKER_BEGIN

//除法
typedef struct st_array_fdiv_unsafe_sse
{
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

}array_fdiv_unsafe_sse_t;


PFX_INLINE simd_fdiv_unsafe_t*	init_simd_fdiv_sse(simd_fdiv_unsafe_t& __fdiv)
{
	__fdiv.fdiv_const_replace		 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fvec2_div_const_replace	 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fvec3_div_const_replace	 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fvec4_div_const_replace	 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fdiv_const				 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fvec2_div_const			 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fvec3_div_const			 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fvec4_div_const			 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fdiv						 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fvec2_div				 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fvec3_div				 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fvec4_div				 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fdiv_relpace				 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fvec2_div_relpace		 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fvec3_div_relpace		 = array_fdiv_unsafe_std_t::operate;
	__fdiv.fvec4_div_relpace		 = array_fdiv_unsafe_std_t::operate;
	return &__fdiv;
}

PECKER_END

#endif			//PFX_SIMD_FDIV_SSE_H_
