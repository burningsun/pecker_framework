/*
 * pfx_simd_fsub_see.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FSUB_SSE_H_
#define		PFX_SIMD_FSUB_SSE_H_

#include "../pfx_simd_fsub_std.h"

PECKER_BEGIN

// 减法
typedef struct st_array_fsub_unsafe_sse
{
	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
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
		const VECTOR2F_t& cst, usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t*  PARAM_INOUT dst_ptr,
		const VECTOR2F_t& cst, usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const VECTOR3F_t& cst, usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PARAM_INOUT dst_ptr,
		const VECTOR3F_t& cst, usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const VECTOR4F_t& cst,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PARAM_INOUT dst_ptr,
		const VECTOR4F_t& cst,
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

	static PFX_FORCE_INLINE float_t* operate(float_t*  PARAM_INOUT dst_ptr,
		const float_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t*  PARAM_INOUT dst_ptr,
		const VECTOR2F_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t*  PARAM_INOUT dst_ptr,
		const VECTOR3F_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t*  PARAM_INOUT dst_ptr,
		const VECTOR4F_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX4F_t* operate(MATRIX4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const MATRIX4F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const MATRIX4F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX4F_t* operate(MATRIX4F_t*  PARAM_INOUT dst_ptr,
		const MATRIX4F_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX3F_t* operate(MATRIX3F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const MATRIX3F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const MATRIX3F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX3F_t* operate(MATRIX3F_t*  PARAM_INOUT dst_ptr,
		const MATRIX3F_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}


	static PFX_FORCE_INLINE MATRIX2F_t* operate(MATRIX2F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const MATRIX2F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const MATRIX2F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX2F_t* operate(MATRIX2F_t*  PARAM_INOUT dst_ptr,
		const MATRIX2F_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		return dst_ptr;
	}



}array_fsub_unsafe_sse_t;



PFX_INLINE simd_fsub_unsafe_t*	init_simd_fsub_sse(simd_fsub_unsafe_t& __fsub)
{
	__fsub.fsub_const_replace        = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fsub_const				 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fvec2_sub_const			 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fvec2_sub_const_replace	 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fvec3_sub_const			 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fvec3_sub_const_replace	 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fvec4_sub_const			 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fvec4_sub_const_replace	 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fsub						 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fsub_replace				 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fvec2_sub				 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fvec2_sub_replace		 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fvec3_sub				 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fvec3_sub_replace		 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fvec4_sub				 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fvec4_sub_relpace		 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fmat4_sub				 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fmat4_sub_relpace		 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fmat3_sub				 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fmat3_sub_relpace		 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fmat2_sub				 = 	 array_fsub_unsafe_std_t::operate;
	__fsub.fmat2_sub_relpace		 = 	 array_fsub_unsafe_std_t::operate;
	return &__fsub;
}

PECKER_END

#endif			//PFX_SIMD_H_
