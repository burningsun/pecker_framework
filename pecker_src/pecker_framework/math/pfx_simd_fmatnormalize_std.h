/*
 * pfx_simd_fmatnormalize_std.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMATNORNALIZE_H_
#define		PFX_SIMD_FMATNORNALIZE_H_

#include "../pfx_defines.h"

#include "pfx_simd_param.h"
#include <math.h>
#include "pfx_simd_fadd_std.h"
#include "pfx_simd_fsub_std.h"
#include "pfx_simd_fmul_std.h"
#include "pfx_simd_fdiv_std.h"

PECKER_BEGIN

typedef struct st_vector_normalize_unsafe_std
{

	static PFX_FORCE_INLINE float_t vector_length(const float_t* PARAM_IN vec_ptr, usize__t dim_count)
	{
		float_t res = 0.0;
		for (uindex_t itr = dim_count; itr != 0;)
		{
			res += vec_ptr[itr] * vec_ptr[itr];
		}
		res = ::sqrt(res);
		return res;
	}

	static PFX_FORCE_INLINE const float_t* normalize(float_t* PFX_RESTRICT PARAM_OUT dst_ptr, 
		const float_t* PFX_RESTRICT PARAM_IN src_ptr, usize__t dim_count)
	{
		float_t len = vector_length(src_ptr, dim_count);
		return array_fdiv_unsafe_std_t::operate(dst_ptr, src_ptr, len, dim_count);
	}

	static PFX_FORCE_INLINE const float_t* normalize(float_t* PARAM_INOUT vec_ptr, usize__t dim_count)
	{
		float_t len = vector_length(vec_ptr, dim_count);
		return array_fdiv_unsafe_std_t::operate(vec_ptr, len, dim_count);
	}

	static PFX_FORCE_INLINE const VECTOR2F_t* normalize(VECTOR2F_t& PFX_RESTRICT PARAM_OUT dst,
		const VECTOR2F_t& PFX_RESTRICT PARAM_IN src)
	{
		float_t len = vector_length(src);
		return array_fdiv_unsafe_std_t::operate(&dst, &src, len, 1);
	}

	static PFX_FORCE_INLINE const VECTOR2F_t* normalize(VECTOR2F_t& PARAM_INOUT vec)
	{
		float_t len = vector_length(vec);
		return array_fdiv_unsafe_std_t::operate(&vec, len, 1);
	}
	static PFX_FORCE_INLINE const VECTOR3F_t* normalize(VECTOR3F_t& PFX_RESTRICT PARAM_OUT dst,
		const VECTOR3F_t& PFX_RESTRICT PARAM_IN src)
	{
		float_t len = vector_length(src);
		return array_fdiv_unsafe_std_t::operate(&dst, &src, len, 1);
	}

	static PFX_FORCE_INLINE const VECTOR3F_t* normalize(VECTOR3F_t& PARAM_INOUT vec)
	{
		float_t len = vector_length(vec);
		return array_fdiv_unsafe_std_t::operate(&vec, len, 1);
	}
	static PFX_FORCE_INLINE const VECTOR4F_t* normalize(VECTOR4F_t& PFX_RESTRICT PARAM_OUT dst,
		const VECTOR4F_t& PFX_RESTRICT PARAM_IN src)
	{
		float_t len = vector_length(src);
		return array_fdiv_unsafe_std_t::operate(&dst, &src, len, 1);
	}

	static PFX_FORCE_INLINE const VECTOR4F_t* normalize(VECTOR4F_t& PARAM_INOUT vec)
	{
		float_t len = vector_length(vec);
		return array_fdiv_unsafe_std_t::operate(&vec, len, 1);
	}

#define PFX_VEC(__vec,x)  __vec.m_vec[(x)]
	static PFX_FORCE_INLINE float_t vector_length(const VECTOR2F_t& PARAM_IN vec)
	{
		float_t res = PFX_VEC(vec, DIMENSION_X) * PFX_VEC(vec, DIMENSION_X) +
			          PFX_VEC(vec, DIMENSION_Y) * PFX_VEC(vec, DIMENSION_Y);
		res = ::sqrt(res);
		return res;
	}

	static PFX_FORCE_INLINE float_t vector_length(const VECTOR3F_t& PARAM_IN vec)
	{
		float_t res = PFX_VEC(vec, DIMENSION_X) * PFX_VEC(vec, DIMENSION_X) +
			          PFX_VEC(vec, DIMENSION_Y) * PFX_VEC(vec, DIMENSION_Y) +
		              PFX_VEC(vec, DIMENSION_Z) * PFX_VEC(vec, DIMENSION_Z);
		res = ::sqrt(res);
		return res;
	}
	static PFX_FORCE_INLINE float_t vector_length(const VECTOR4F_t& PARAM_IN vec)
	{
		float_t res = PFX_VEC(vec, DIMENSION_X) * PFX_VEC(vec, DIMENSION_X) +
			          PFX_VEC(vec, DIMENSION_Y) * PFX_VEC(vec, DIMENSION_Y) +
			          PFX_VEC(vec, DIMENSION_Z) * PFX_VEC(vec, DIMENSION_Z) +
		              PFX_VEC(vec, DIMENSION_W) * PFX_VEC(vec, DIMENSION_W);
		res = ::sqrt(res);
		return res;
	}


#undef PFX_VEC

}vector_normalize_unsafe_std_t;

PECKER_END

#endif			//PFX_SIMD_FMATNORNALIZE_H_
