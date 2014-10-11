/*
 * pfx_simd_fadd_sse.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FADD_SSE_H_
#define		PFX_SIMD_FADD_SSE_H_

#include "../pfx_simd_fadd_std.h"

PECKER_BEGIN

// 加法
typedef struct st_array_fadd_unsafe_sse_mmx
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
		operate(dst_ptr->m_mat, src_ptr->m_mat, 3 * count);
		return dst_ptr;
	}


	static PFX_FORCE_INLINE MATRIX2F_t* operate(MATRIX2F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const MATRIX2F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const MATRIX2F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		operate(dst_ptr->m_mat, src1_ptr->m_mat, src2_ptr->m_mat, 2 * count);
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX2F_t* operate(MATRIX2F_t*  PARAM_INOUT dst_ptr,
		const MATRIX2F_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		operate(dst_ptr->m_mat, src_ptr->m_mat, 2 * count);
		return dst_ptr;
	}



}array_fadd_unsafe_sse_mmx_t;


PFX_INLINE simd_fadd_unsafe_t*	init_simd_fadd_sse(simd_fadd_unsafe_t& __fadd)
{
	__fadd.fadd_const_replace        = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fadd_const				 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fvec2_add_const			 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fvec2_add_const_replace	 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fvec3_add_const			 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fvec3_add_const_replace	 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fvec4_add_const			 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fvec4_add_const_replace	 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fadd						 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fadd_replace				 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fvec2_add				 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fvec2_add_replace		 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fvec3_add				 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fvec3_add_replace		 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fvec4_add				 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fvec4_add_relpace		 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fmat4_add				 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fmat4_add_relpace		 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fmat3_add				 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fmat3_add_relpace		 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fmat2_add				 = 	 array_fadd_unsafe_std_t::operate;
	__fadd.fmat2_add_relpace		 = 	 array_fadd_unsafe_std_t::operate;
	return &__fadd;
}

PECKER_END

#endif			//PFX_SIMD_FADD_SSE_H_
