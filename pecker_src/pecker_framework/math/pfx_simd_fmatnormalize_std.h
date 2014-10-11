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

	static PFX_FORCE_INLINE  float_t* normalize(float_t* PFX_RESTRICT PARAM_OUT dst_ptr, 
		const float_t* PFX_RESTRICT PARAM_IN src_ptr, usize__t dim_count)
	{
		float_t len = vector_length(src_ptr, dim_count);
		return array_fdiv_unsafe_std_t::operate(dst_ptr, src_ptr, len, dim_count);
	}

	static PFX_FORCE_INLINE  float_t* normalize(float_t* PARAM_INOUT vec_ptr, usize__t dim_count)
	{
		float_t len = vector_length(vec_ptr, dim_count);
		return array_fdiv_unsafe_std_t::operate(vec_ptr, len, dim_count);
	}

	static PFX_FORCE_INLINE  VECTOR2F_t* normalize(VECTOR2F_t& PFX_RESTRICT PARAM_OUT dst,
		const VECTOR2F_t& PFX_RESTRICT PARAM_IN src)
	{
		float_t len = vector_length(src);
		return array_fdiv_unsafe_std_t::operate(&dst, &src, len, 1);
	}

	static PFX_FORCE_INLINE VECTOR2F_t* normalize(VECTOR2F_t& PARAM_INOUT vec)
	{
		float_t len = vector_length(vec);
		return array_fdiv_unsafe_std_t::operate(&vec, len, 1);
	}
	static PFX_FORCE_INLINE VECTOR3F_t* normalize(VECTOR3F_t& PFX_RESTRICT PARAM_OUT dst,
		const VECTOR3F_t& PFX_RESTRICT PARAM_IN src)
	{
		float_t len = vector_length(src);
		return array_fdiv_unsafe_std_t::operate(&dst, &src, len, 1);
	}

	static PFX_FORCE_INLINE  VECTOR3F_t* normalize(VECTOR3F_t& PARAM_INOUT vec)
	{
		float_t len = vector_length(vec);
		return array_fdiv_unsafe_std_t::operate(&vec, len, 1);
	}

	static PFX_FORCE_INLINE  VECTOR4F_t* normalize_vec3_extern(VECTOR4F_t& PFX_RESTRICT PARAM_OUT dst,
		const VECTOR4F_t& PFX_RESTRICT PARAM_IN src)
	{
		float_t len = vector_length((VECTOR3F_t&)src);
		dst.m_vec[3] = 0.0;
		return (VECTOR4F_t*)array_fdiv_unsafe_std_t::operate((VECTOR3F_t*)(&dst), (VECTOR3F_t*)(&src), len, 1);
	}

	static PFX_FORCE_INLINE  VECTOR4F_t* normalize_vec3_extern(VECTOR4F_t& PARAM_INOUT vec)
	{
		float_t len = vector_length((VECTOR3F_t&)vec);
		return (VECTOR4F_t*)array_fdiv_unsafe_std_t::operate((VECTOR3F_t*)(&vec), (VECTOR3F_t*)(&vec), len, 1);
	}

	static PFX_FORCE_INLINE  VECTOR4F_t* normalize(VECTOR4F_t& PFX_RESTRICT PARAM_OUT dst,
		const VECTOR4F_t& PFX_RESTRICT PARAM_IN src)
	{
		float_t len = vector_length(src);
		return array_fdiv_unsafe_std_t::operate(&dst, &src, len, 1);
	}

	static PFX_FORCE_INLINE  VECTOR4F_t* normalize(VECTOR4F_t& PARAM_INOUT vec)
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
	static PFX_FORCE_INLINE float_t vector_length_vec3_extern(const VECTOR4F_t& PARAM_IN vec)
	{
		return vector_length((VECTOR3F_t&)vec);
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


								 
typedef  float_t (*fvector_length_func)(const float_t* PARAM_IN vec_ptr, usize__t dim_count);
typedef   float_t* (*fnormalize_func)(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const float_t* PFX_RESTRICT PARAM_IN src_ptr, usize__t dim_count);
typedef   float_t* (*fnormalize_replace_func)(float_t* PARAM_INOUT vec_ptr, usize__t dim_count);
typedef   VECTOR2F_t* (*fvec2_normalize_func)(VECTOR2F_t& PFX_RESTRICT PARAM_OUT dst,
	const VECTOR2F_t& PFX_RESTRICT PARAM_IN src);
typedef   VECTOR2F_t* (*fvec2_normalize_replace_func)(VECTOR2F_t& PARAM_INOUT vec);
typedef   VECTOR3F_t* (*fvec3_normalize_func)(VECTOR3F_t& PFX_RESTRICT PARAM_OUT dst,
	const VECTOR3F_t& PFX_RESTRICT PARAM_IN src);
typedef   VECTOR3F_t* (*fvec3_normalize_replace_func)(VECTOR3F_t& PARAM_INOUT vec);
typedef   VECTOR4F_t* (*fvec4_normalize_func)(VECTOR4F_t& PFX_RESTRICT PARAM_OUT dst,
	const VECTOR4F_t& PFX_RESTRICT PARAM_IN src);
typedef   VECTOR4F_t* (*fvec4_normalize_replace_func)(VECTOR4F_t& PARAM_INOUT vec);
typedef  float_t (*vector2_length_func)(const VECTOR2F_t& PARAM_IN vec);
typedef  float_t (*vector3_length_func)(const VECTOR3F_t& PARAM_IN vec);
typedef  float_t (*vector4_length_func)(const VECTOR4F_t& PARAM_IN vec);

typedef struct st_simd_fvec_normalize_unsafe
{
	fvector_length_func				 fvector_length;
	fnormalize_func					 fnormalize;
	fnormalize_replace_func			 fnormalize_replace;
	fvec2_normalize_func			 fvec2_normalize;
	fvec2_normalize_replace_func	 fvec2_normalize_replace;
	fvec3_normalize_func			 fvec3_normalize;
	fvec3_normalize_replace_func	 fvec3_normalize_replace;
	fvec4_normalize_func			 fvec4_normalize;
	fvec4_normalize_replace_func	 fvec4_normalize_replace;
	fvec4_normalize_func			 fvec3_extern_normalize;
	fvec4_normalize_replace_func	 fvec3_extern_normalize_replace;
	vector2_length_func				 vector2_length;
	vector3_length_func				 vector3_length;
	vector4_length_func				 vector4_length;
	vector4_length_func				 vector3_extern_length;
}simd_fvec_normalize_unsafe_t;


PFX_INLINE simd_fvec_normalize_unsafe_t* init_simd_fvec_normalize_std(simd_fvec_normalize_unsafe_t& __fvec)
{
	__fvec.fvector_length               = vector_normalize_unsafe_std_t::vector_length;
	__fvec.fnormalize				    = vector_normalize_unsafe_std_t::normalize;
	__fvec.fnormalize_replace		    = vector_normalize_unsafe_std_t::normalize;
	__fvec.fvec2_normalize			    = vector_normalize_unsafe_std_t::normalize;
	__fvec.fvec2_normalize_replace	    = vector_normalize_unsafe_std_t::normalize;
	__fvec.fvec3_normalize			    = vector_normalize_unsafe_std_t::normalize;
	__fvec.fvec3_normalize_replace	    = vector_normalize_unsafe_std_t::normalize;
	__fvec.fvec4_normalize			    = vector_normalize_unsafe_std_t::normalize;
	__fvec.fvec4_normalize_replace	    = vector_normalize_unsafe_std_t::normalize;
	__fvec.vector2_length			    = vector_normalize_unsafe_std_t::vector_length;
	__fvec.vector3_length			    = vector_normalize_unsafe_std_t::vector_length;
	__fvec.vector4_length			    = vector_normalize_unsafe_std_t::vector_length;

	__fvec.fvec3_extern_normalize            = 	vector_normalize_unsafe_std_t::normalize_vec3_extern;
	__fvec.fvec3_extern_normalize_replace	 = 	vector_normalize_unsafe_std_t::normalize_vec3_extern;
	__fvec.vector3_extern_length			 = 	vector_normalize_unsafe_std_t::vector_length_vec3_extern;


	return &__fvec;
}

PECKER_END

#endif			//PFX_SIMD_FMATNORNALIZE_H_
