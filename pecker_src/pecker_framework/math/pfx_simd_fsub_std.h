/*
 * pfx_simd_fsub_std.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FSUB_H_
#define		PFX_SIMD_FSUB_H_

#include "../pfx_defines.h"

#include "pfx_simd_param.h"
#include <math.h>

PECKER_BEGIN

// 减法
typedef struct st_array_fsub_unsafe_std
{
	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
	const float_t cst,
	usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr] -= cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr] = src_ptr[itr] - cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const VECTOR2F_t& cst, usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src_ptr[itr].m_vec[0] - cst.m_vec[0];
			dst_ptr[itr].m_vec[1] = src_ptr[itr].m_vec[1] - cst.m_vec[1];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t*  PARAM_INOUT dst_ptr,
		const VECTOR2F_t& cst, usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] -= cst.m_vec[0];
			dst_ptr[itr].m_vec[1] -= cst.m_vec[1];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const VECTOR3F_t& cst, usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src_ptr[itr].m_vec[0] - cst.m_vec[0];
			dst_ptr[itr].m_vec[1] = src_ptr[itr].m_vec[1] - cst.m_vec[1];
			dst_ptr[itr].m_vec[2] = src_ptr[itr].m_vec[2] - cst.m_vec[2];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PARAM_INOUT dst_ptr,
		const VECTOR3F_t& cst, usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] -= cst.m_vec[0];
			dst_ptr[itr].m_vec[1] -= cst.m_vec[1];
			dst_ptr[itr].m_vec[2] -= cst.m_vec[2];

		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const VECTOR4F_t& cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src_ptr[itr].m_vec[0] - cst.m_vec[0];
			dst_ptr[itr].m_vec[1] = src_ptr[itr].m_vec[1] - cst.m_vec[1];
			dst_ptr[itr].m_vec[2] = src_ptr[itr].m_vec[2] - cst.m_vec[2];
			dst_ptr[itr].m_vec[3] = src_ptr[itr].m_vec[3] - cst.m_vec[3];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PARAM_INOUT dst_ptr,
		const VECTOR4F_t& cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] -= cst.m_vec[0];
			dst_ptr[itr].m_vec[1] -= cst.m_vec[1];
			dst_ptr[itr].m_vec[2] -= cst.m_vec[2];
			dst_ptr[itr].m_vec[3] -= cst.m_vec[3];
		}
		return dst_ptr;
	}



	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr] = src1_ptr[itr] - src2_ptr[itr];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t* operate(float_t*  PARAM_INOUT dst_ptr,
		const float_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr] -= src_ptr[itr];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src1_ptr[itr].m_vec[0] - src2_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] = src1_ptr[itr].m_vec[1] - src2_ptr[itr].m_vec[1];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t*  PARAM_INOUT dst_ptr,
		const VECTOR2F_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] -= src_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] -= src_ptr[itr].m_vec[1];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src1_ptr[itr].m_vec[0] - src2_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] = src1_ptr[itr].m_vec[1] - src2_ptr[itr].m_vec[1];
			dst_ptr[itr].m_vec[2] = src1_ptr[itr].m_vec[2] - src2_ptr[itr].m_vec[2];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t*  PARAM_INOUT dst_ptr,
		const VECTOR3F_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] -= src_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] -= src_ptr[itr].m_vec[1];
			dst_ptr[itr].m_vec[2] -= src_ptr[itr].m_vec[2];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src1_ptr[itr].m_vec[0] - src2_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] = src1_ptr[itr].m_vec[1] - src2_ptr[itr].m_vec[1];
			dst_ptr[itr].m_vec[2] = src1_ptr[itr].m_vec[2] - src2_ptr[itr].m_vec[2];
			dst_ptr[itr].m_vec[3] = src1_ptr[itr].m_vec[3] - src2_ptr[itr].m_vec[3];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t*  PARAM_INOUT dst_ptr,
		const VECTOR4F_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] -= src_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] -= src_ptr[itr].m_vec[1];
			dst_ptr[itr].m_vec[2] -= src_ptr[itr].m_vec[2];
			dst_ptr[itr].m_vec[3] -= src_ptr[itr].m_vec[3];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX4F_t* operate(MATRIX4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const MATRIX4F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const MATRIX4F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		operate(dst_ptr->m_mat, src1_ptr->m_mat, src2_ptr->m_mat, 4 * count);
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX4F_t* operate(MATRIX4F_t*  PARAM_INOUT dst_ptr,
		const MATRIX4F_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		operate(dst_ptr->m_mat, src_ptr->m_mat, 4 * count);
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX3F_t* operate(MATRIX3F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const MATRIX3F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const MATRIX3F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		operate(dst_ptr->m_mat, src1_ptr->m_mat, src2_ptr->m_mat, 3 * count);
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



}array_fsub_unsafe_std_t;


typedef float_t* (*fsub_const_replace_func)(float_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
	const float_t cst,
	usize__t count);
typedef float_t* (*fsub_const_func)(float_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
	const float_t* PFX_RESTRICT PARAM_IN src_ptr,
	const float_t cst,
	usize__t count);

typedef	VECTOR2F_t* (*fvec2_sub_const_func)(VECTOR2F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
	const VECTOR2F_t* PFX_RESTRICT PARAM_IN src_ptr,
	const VECTOR2F_t& cst, usize__t count);
typedef	VECTOR2F_t* (*fvec2_sub_const_replace_func)(VECTOR2F_t*  PARAM_INOUT dst_ptr,
	const VECTOR2F_t& cst, usize__t count);


typedef	VECTOR3F_t* (*fvec3_sub_const_func)(VECTOR3F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
	const VECTOR3F_t& cst, usize__t count);
typedef	VECTOR3F_t* (*fvec3_sub_const_replace_func)(VECTOR3F_t* PARAM_INOUT dst_ptr,
	const VECTOR3F_t& cst, usize__t count);


typedef VECTOR4F_t* (*fvec4_sub_const_func)(VECTOR4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
	const VECTOR4F_t& cst,
	usize__t count);
typedef	VECTOR4F_t* (*fvec4_sub_const_replace_func)(VECTOR4F_t* PARAM_INOUT dst_ptr,
	const VECTOR4F_t& cst,
	usize__t count);


typedef	float_t* (*fsub_func)(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const float_t* PFX_RESTRICT PARAM_IN src1_ptr,
	const float_t* PFX_RESTRICT PARAM_IN src2_ptr,
	usize__t count);
typedef	float_t* (*fsub_replace_func)(float_t*  PARAM_INOUT dst_ptr,
	const float_t*  PARAM_IN src_ptr,
	usize__t count);


typedef	VECTOR2F_t* (*fvec2_sub_func)(VECTOR2F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const VECTOR2F_t* PFX_RESTRICT PARAM_IN src1_ptr,
	const VECTOR2F_t* PFX_RESTRICT PARAM_IN src2_ptr,
	usize__t count);


typedef	VECTOR2F_t* (*fvec2_sub_replace_func)(VECTOR2F_t*  PARAM_INOUT dst_ptr,
	const VECTOR2F_t*  PARAM_IN src_ptr,
	usize__t count);


typedef	VECTOR3F_t* (*fvec3_sub_func)(VECTOR3F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const VECTOR3F_t* PFX_RESTRICT PARAM_IN src1_ptr,
	const VECTOR3F_t* PFX_RESTRICT PARAM_IN src2_ptr,
	usize__t count);
typedef	VECTOR3F_t* (*fvec3_sub_replace_func)(VECTOR3F_t*  PARAM_INOUT dst_ptr,
	const VECTOR3F_t*  PARAM_IN src_ptr,
	usize__t count);

typedef	VECTOR4F_t* (*fvec4_sub_func)(VECTOR4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const VECTOR4F_t* PFX_RESTRICT PARAM_IN src1_ptr,
	const VECTOR4F_t* PFX_RESTRICT PARAM_IN src2_ptr,
	usize__t count);
typedef	VECTOR4F_t* (*fvec4_sub_relpace_func)(VECTOR4F_t*  PARAM_INOUT dst_ptr,
	const VECTOR4F_t*  PARAM_IN src_ptr,
	usize__t count);


typedef	MATRIX4F_t* (*fmat4_sub_func)(MATRIX4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const MATRIX4F_t* PFX_RESTRICT PARAM_IN src1_ptr,
	const MATRIX4F_t* PFX_RESTRICT PARAM_IN src2_ptr,
	usize__t count);
typedef	MATRIX4F_t* (*fmat4_sub_relpace_func)(MATRIX4F_t*  PARAM_INOUT dst_ptr,
	const MATRIX4F_t*  PARAM_IN src_ptr,
	usize__t count);


typedef	MATRIX3F_t* (*fmat3_sub_func)(MATRIX3F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const MATRIX3F_t* PFX_RESTRICT PARAM_IN src1_ptr,
	const MATRIX3F_t* PFX_RESTRICT PARAM_IN src2_ptr,
	usize__t count);
typedef	MATRIX3F_t* (*fmat3_sub_relpace_func)(MATRIX3F_t*  PARAM_INOUT dst_ptr,
	const MATRIX3F_t*  PARAM_IN src_ptr,
	usize__t count);



typedef	MATRIX2F_t* (*fmat2_sub_func)(MATRIX2F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const MATRIX2F_t* PFX_RESTRICT PARAM_IN src1_ptr,
	const MATRIX2F_t* PFX_RESTRICT PARAM_IN src2_ptr,
	usize__t count);
typedef	MATRIX2F_t* (*fmat2_sub_relpace_func)(MATRIX2F_t*  PARAM_INOUT dst_ptr,
	const MATRIX2F_t*  PARAM_IN src_ptr,
	usize__t count);


typedef struct st_simd_fsub_unsafe
{
	fsub_const_replace_func				fsub_const_replace;
	fsub_const_func						fsub_const;

	fvec2_sub_const_func				fvec2_sub_const;
	fvec2_sub_const_replace_func		fvec2_sub_const_replace;

	fvec3_sub_const_func				fvec3_sub_const;
	fvec3_sub_const_replace_func		fvec3_sub_const_replace;

	fvec4_sub_const_func				fvec4_sub_const;
	fvec4_sub_const_replace_func		fvec4_sub_const_replace;

	fsub_func							fsub;
	fsub_replace_func					fsub_replace;

	fvec2_sub_func						fvec2_sub;
	fvec2_sub_replace_func				fvec2_sub_replace;

	fvec3_sub_func						fvec3_sub;
	fvec3_sub_replace_func				fvec3_sub_replace;

	fvec4_sub_func						fvec4_sub;
	fvec4_sub_relpace_func				fvec4_sub_relpace;

	fmat4_sub_func						fmat4_sub;
	fmat4_sub_relpace_func				fmat4_sub_relpace;

	fmat3_sub_func						fmat3_sub;
	fmat3_sub_relpace_func				fmat3_sub_relpace;

	fmat2_sub_func						fmat2_sub;
	fmat2_sub_relpace_func				fmat2_sub_relpace;
}simd_fsub_unsafe_t;


PFX_INLINE simd_fsub_unsafe_t*	init_simd_fsub_std(simd_fsub_unsafe_t& __fsub)
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
