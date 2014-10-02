/*
 * pfx_simd_fmul_std.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMUL_H_
#define		PFX_SIMD_FMUL_H_

#include "../pfx_defines.h"

#include "pfx_simd_param.h"
#include <math.h>

PECKER_BEGIN

// 乘法
typedef struct st_array_fmul_unsafe_std
{
	static PFX_FORCE_INLINE float_t* operate(float_t*  PARAM_INOUT dst_ptr,
	const float_t cst,
	usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr] *= cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PARAM_INOUT dst_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] *= cst;
			dst_ptr[itr].m_vec[1] *= cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PARAM_INOUT dst_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] *= cst;
			dst_ptr[itr].m_vec[1] *= cst;
			dst_ptr[itr].m_vec[2] *= cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PARAM_INOUT dst_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] *= cst;
			dst_ptr[itr].m_vec[1] *= cst;
			dst_ptr[itr].m_vec[2] *= cst;
			dst_ptr[itr].m_vec[3] *= cst;
		}
		return dst_ptr;
	}


	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr] = src_ptr[itr] * cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src_ptr[itr].m_vec[0] * cst;
			dst_ptr[itr].m_vec[1] = src_ptr[itr].m_vec[1] * cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src_ptr[itr].m_vec[0] * cst;
			dst_ptr[itr].m_vec[1] = src_ptr[itr].m_vec[1] * cst;
			dst_ptr[itr].m_vec[2] = src_ptr[itr].m_vec[2] * cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src_ptr[itr].m_vec[0] * cst;
			dst_ptr[itr].m_vec[1] = src_ptr[itr].m_vec[1] * cst;
			dst_ptr[itr].m_vec[2] = src_ptr[itr].m_vec[2] * cst;
			dst_ptr[itr].m_vec[3] = src_ptr[itr].m_vec[3] * cst;
		}
		return dst_ptr;
	}




	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr] = src1_ptr[itr] * src2_ptr[itr];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src1_ptr[itr].m_vec[0] * src2_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] = src1_ptr[itr].m_vec[1] * src2_ptr[itr].m_vec[1];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src1_ptr[itr].m_vec[0] * src2_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] = src1_ptr[itr].m_vec[1] * src2_ptr[itr].m_vec[1];
			dst_ptr[itr].m_vec[2] = src1_ptr[itr].m_vec[2] * src2_ptr[itr].m_vec[2];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src1_ptr[itr].m_vec[0] * src2_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] = src1_ptr[itr].m_vec[1] * src2_ptr[itr].m_vec[1];
			dst_ptr[itr].m_vec[2] = src1_ptr[itr].m_vec[2] * src2_ptr[itr].m_vec[2];
			dst_ptr[itr].m_vec[3] = src1_ptr[itr].m_vec[3] * src2_ptr[itr].m_vec[3];
		}
		return dst_ptr;
	}



	static PFX_FORCE_INLINE float_t* operate(float_t*  PARAM_INOUT dst_ptr,
		const float_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr] *= src_ptr[itr];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] *= src_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] *= src_ptr[itr].m_vec[1];
		}
		return dst_ptr;
	}
	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] *= src_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] *= src_ptr[itr].m_vec[1];
			dst_ptr[itr].m_vec[2] *= src_ptr[itr].m_vec[2];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] *= src_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] *= src_ptr[itr].m_vec[1];
			dst_ptr[itr].m_vec[2] *= src_ptr[itr].m_vec[2];
			dst_ptr[itr].m_vec[3] *= src_ptr[itr].m_vec[3];
		}
		return dst_ptr;
	}

}array_fmul_unsafe_std_t;

typedef float_t* (*fmul_const_replace_func)(float_t*  PARAM_INOUT dst_ptr,
	const float_t cst,
	usize__t count);

typedef VECTOR2F_t* (*fvec2_mul_const_replace_func)(VECTOR2F_t* PARAM_INOUT dst_ptr,
	const float_t cst,
	usize__t count);

typedef VECTOR3F_t* (*fvec3_mul_const_replace_func)(VECTOR3F_t* PARAM_INOUT dst_ptr,
	const float_t cst,
	usize__t count);

typedef VECTOR4F_t* (*fvec4_mul_const_replace_func)(VECTOR4F_t* PARAM_INOUT dst_ptr,
	const float_t cst,
	usize__t count);

typedef float_t* (*fmul_const_func)(float_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
	const float_t* PFX_RESTRICT PARAM_IN src_ptr,
	const float_t cst,
	usize__t count);

typedef VECTOR2F_t* (*fvec2_mul_const_func)(VECTOR2F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
	const VECTOR2F_t* PFX_RESTRICT PARAM_IN src_ptr,
	const float_t cst,
	usize__t count);

typedef VECTOR3F_t* (*fvec3_mul_const_func)(VECTOR3F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
	const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
	const float_t cst,
	usize__t count);

typedef VECTOR4F_t* (*fvec4_mul_const_func)(VECTOR4F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
	const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
	const float_t cst,
	usize__t count);

typedef float_t* (*fmul_func)(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const float_t* PFX_RESTRICT PARAM_IN src1_ptr,
	const float_t* PFX_RESTRICT PARAM_IN src2_ptr,
	usize__t count);

typedef VECTOR2F_t* (*fvec2_mul_func)(VECTOR2F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
	const VECTOR2F_t* PFX_RESTRICT PARAM_IN src1_ptr,
	const VECTOR2F_t* PFX_RESTRICT PARAM_IN src2_ptr,
	usize__t count);

typedef VECTOR3F_t* (*fvec3_mul_func)(VECTOR3F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
	const VECTOR3F_t* PFX_RESTRICT PARAM_IN src1_ptr,
	const VECTOR3F_t* PFX_RESTRICT PARAM_IN src2_ptr,
	usize__t count);

typedef VECTOR4F_t* (*fvec4_mul_func)(VECTOR4F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
	const VECTOR4F_t* PFX_RESTRICT PARAM_IN src1_ptr,
	const VECTOR4F_t* PFX_RESTRICT PARAM_IN src2_ptr,
	usize__t count);

typedef float_t* (*fmul_relpace_func)(float_t*  PARAM_INOUT dst_ptr,
	const float_t*  PARAM_IN src_ptr,
	usize__t count);

typedef VECTOR2F_t* (*fvec2_mul_relpace_func)(VECTOR2F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
	const VECTOR2F_t* PFX_RESTRICT PARAM_IN src_ptr,
	usize__t count);

typedef VECTOR3F_t* (*fvec3_mul_relpace_func)(VECTOR3F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
	const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
	usize__t count);

typedef VECTOR4F_t* (*fvec4_mul_relpace_func)(VECTOR4F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
	const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
	usize__t count);


typedef struct st_simd_fmul_unsafe
{
	fmul_const_replace_func			  fmul_const_replace;
	fvec2_mul_const_replace_func	  fvec2_mul_const_replace;
	fvec3_mul_const_replace_func	  fvec3_mul_const_replace;
	fvec4_mul_const_replace_func	  fvec4_mul_const_replace;

	fmul_const_func					  fmul_const;
	fvec2_mul_const_func			  fvec2_mul_const;
	fvec3_mul_const_func			  fvec3_mul_const;
	fvec4_mul_const_func			  fvec4_mul_const;

	fmul_func						  fmul;
	fvec2_mul_func					  fvec2_mul;
	fvec3_mul_func					  fvec3_mul;
	fvec4_mul_func					  fvec4_mul;

	fmul_relpace_func				  fmul_relpace;
	fvec2_mul_relpace_func			  fvec2_mul_relpace;
	fvec3_mul_relpace_func			  fvec3_mul_relpace;
	fvec4_mul_relpace_func			  fvec4_mul_relpace;

}simd_fmul_unsafe_t;

PFX_INLINE simd_fmul_unsafe_t*	init_simd_fmul_std(simd_fmul_unsafe_t& __fmul)
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
