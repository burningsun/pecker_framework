/*
 * pfx_simd_fabs_std.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FABS_STD_H_
#define		PFX_SIMD_FABS_STD_H_

#include "../pfx_defines.h"

#include "pfx_simd_param.h"
#include <math.h>


PECKER_BEGIN

// 绝对值
typedef struct st_array_fabs_std
{
	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
	usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr] = ::abs(dst_ptr[itr]);
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr] = ::abs(src_ptr[itr]);
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] = ::abs(src_ptr[itr].m_vec[0]);
			dst_ptr[itr].m_vec[1] = ::abs(src_ptr[itr].m_vec[1]);
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t*  PARAM_INOUT dst_ptr,
		 usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] = ::abs(dst_ptr[itr].m_vec[0]);
			dst_ptr[itr].m_vec[1] = ::abs(dst_ptr[itr].m_vec[1]);
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] = ::abs(src_ptr[itr].m_vec[0]);
			dst_ptr[itr].m_vec[1] = ::abs(src_ptr[itr].m_vec[1]);
			dst_ptr[itr].m_vec[2] = ::abs(src_ptr[itr].m_vec[2]);
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PARAM_INOUT dst_ptr, usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] = ::abs(dst_ptr[itr].m_vec[0]);
			dst_ptr[itr].m_vec[1] = ::abs(dst_ptr[itr].m_vec[1]); 
			dst_ptr[itr].m_vec[2] = ::abs(dst_ptr[itr].m_vec[2]);
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] = ::abs(src_ptr[itr].m_vec[0]);
			dst_ptr[itr].m_vec[1] = ::abs(src_ptr[itr].m_vec[1]);
			dst_ptr[itr].m_vec[2] = ::abs(src_ptr[itr].m_vec[2]);
			dst_ptr[itr].m_vec[3] = ::abs(src_ptr[itr].m_vec[3]);
		}
		return dst_ptr;
	}
	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PARAM_INOUT dst_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0; )
		{
			--itr;
			dst_ptr[itr].m_vec[0] = ::abs(dst_ptr[itr].m_vec[0]);
			dst_ptr[itr].m_vec[1] = ::abs(dst_ptr[itr].m_vec[1]);
			dst_ptr[itr].m_vec[2] = ::abs(dst_ptr[itr].m_vec[2]);
			dst_ptr[itr].m_vec[3] = ::abs(dst_ptr[itr].m_vec[3]);
		}
		return dst_ptr;
	}
}array_fabs_std_unsafe_t;

typedef  float_t* (*fabs_replace_func)(float_t* PFX_RESTRICT PARAM_INOUT dst_ptr, usize__t count);
typedef  float_t* (*fabs_func)(float_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
	                           const float_t* PFX_RESTRICT PARAM_IN src_ptr, usize__t count);

typedef  VECTOR2F_t* (*fvec2_abs_func)(VECTOR2F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
	                               const VECTOR2F_t* PFX_RESTRICT PARAM_IN src_ptr,
	                               usize__t count);
typedef  VECTOR2F_t* (*fvec2_abs_replace_func)(VECTOR2F_t*  PARAM_INOUT dst_ptr,
	                                 usize__t count);

typedef  VECTOR3F_t* (*fvec3_abs_func)(VECTOR3F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	                        const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
	                        usize__t count);
typedef VECTOR3F_t* (*fvec3_abs_replace_func)(VECTOR3F_t* PARAM_INOUT dst_ptr, usize__t count);

typedef VECTOR4F_t* (*fvec4_abs_func)(VECTOR4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		                      const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
		                      usize__t count);
typedef VECTOR4F_t* (*fvec4_abs_replace_func)(VECTOR4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		                      usize__t count);

typedef struct st_simd_fabs_unsafe
{
	fabs_replace_func			 fabs_replace;
	fabs_func					 fabs;

	fvec2_abs_func				 fvec2_abs;
	fvec2_abs_replace_func		 fvec2_abs_replace;

	fvec3_abs_func				 fvec3_abs;
	fvec3_abs_replace_func		 fvec3_abs_replace;

	fvec4_abs_func				 fvec4_abs;
	fvec4_abs_replace_func 		 fvec4_abs_replace;
}simd_fabs_unsafe_t;


PFX_INLINE simd_fabs_unsafe_t*	init_simd_fabs_std(simd_fabs_unsafe_t& __fabs)
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





#endif			//PFX_SIMD_FABS_STD_H_
