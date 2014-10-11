/*
 * pfx_simd_fmatnormalize_sse.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMATNORNALIZE_SSE_H_
#define		PFX_SIMD_FMATNORNALIZE_SSE_H_

#include "../pfx_simd_param_sse.h"
#include "../pfx_simd_std.h"
#include "pfx_simd_fdiv_sse.h"

PECKER_BEGIN

typedef struct st_vector_normalize_unsafe_sse
{

	static PFX_FORCE_INLINE float_t vector_length(const float_t* PARAM_IN vec_ptr, usize__t dim_count)
	{
		float_t res = 0.0;
		usize__t vec4_count = dim_count >> 2;  // /4
		usize__t vec_remain = dim_count & 0x3; // %4
		usize__t vec3_count = (3 == vec_remain) ? (1.0) : (0.0);
		usize__t vec2_count = (2 == vec_remain) ? (1.0) : (0.0);
		usize__t vec1_count = (1 == vec_remain) ? (1.0) : (0.0);

		__m128 vec = _mm_set_ps(0.0, 0.0, 0.0, 0.0);
		for (uindex_t itr = vec4_count; itr != 0; )
		{
			--itr;
			__m128 r1 = _mm_load_ps(vec_ptr);
			r1  = _mm_mul_ps(r1, r1); // r1 = (x*x, y*y, z*z, w*w)
			vec = _mm_add_ps(r1, vec);
			vec_ptr += 4;
		}
		if (vec3_count)
		{
			__m128 r1 = _mm_set_ps(vec_ptr[2], vec_ptr[1], vec_ptr[0], 0.0);
			r1 = _mm_mul_ps(r1, r1); 
			vec = _mm_add_ps(r1, vec);
		}
		else if (vec2_count)
		{
			__m128 r1 = _mm_set_ps(vec_ptr[1], vec_ptr[0], 0.0, 0.0);
			r1 = _mm_mul_ps(r1, r1); 
			vec = _mm_add_ps(r1, vec);
		}
		else if (vec1_count)
		{
			__m128 r1 = _mm_set_ps(vec_ptr[0], 0.0, 0.0, 0.0);
			r1 = _mm_mul_ps(r1, r1); 
			vec = _mm_add_ps(r1, vec);
		}

		__m128 r2 = _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(1, 1, 1, 1)); // r2 = (r1.y, r1.y, r1.y, r1.y)
		__m128 r3 = _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(2, 2, 2, 2)); // r3 = (r1.z, r1.z, r1.z, r1.z)
		__m128 r4 = _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(3, 3, 3, 3)); // r3 = (r1.w, r1.w, r1.w, r1.w)

		r2 = _mm_add_ss(vec, r2); // r2.x += r1.x = x*x + y*y;
		r2 = _mm_add_ss(r3, r2); // r2.x += r3.x = x*x + y*y + z*z + w*w;
		r2 = _mm_add_ss(r4, r2); // r2.x += r3.x = x*x + y*y + z*z + w*w;

		r4 = _mm_sqrt_ss(r2);
		_mm_store_ss(&res, r4);

		return res;
	}

	static PFX_FORCE_INLINE float_t* normalize(float_t* PFX_RESTRICT PARAM_OUT dst_ptr, 
		const float_t* PFX_RESTRICT PARAM_IN src_ptr, usize__t dim_count)
	{
		float_t* res_ptr = dst_ptr;
		float_t len = vector_length(src_ptr, dim_count);

		if (matrix_inv_unsafe_std_t::is_near_zero(len))
		{
			if (dim_count)
			{
				memcpy(dst_ptr, src_ptr, dim_count);
				return dst_ptr;
			}
			else
			{
				return null;
			}

		}
		
		usize__t vec4_count = dim_count >> 2;  // /4
		usize__t vec_remain = dim_count & 0x3; // %4
		usize__t vec3_count = (3 == vec_remain) ? (1.0) : (0.0);
		usize__t vec2_count = (2 == vec_remain) ? (1.0) : (0.0);
		usize__t vec1_count = (1 == vec_remain) ? (1.0) : (0.0);

		__m128 vlen = _mm_set_ps1(1.0/len);
		for (uindex_t itr = vec4_count; itr != 0;)
		{
			--itr;
			__m128 r1 = _mm_load_ps(src_ptr);
			r1 = _mm_mul_ps(r1, vlen);
			_mm_store_ps(dst_ptr, r1);
			dst_ptr += 4;
			src_ptr += 4;
		}
		if (vec3_count)
		{
			SIMD_128BIT(vec);
			__m128 r1 = _mm_load_ps(src_ptr);
			r1 = _mm_mul_ps(vec.m_vec128bit, vlen);
			*((VECTOR3F_t*)dst_ptr) = vec.m_vec3f;
		}
		else if (vec2_count)
		{
			SIMD_128BIT(vec);
			__m128 r1 = _mm_load_ps(src_ptr);
			r1 = _mm_mul_ps(vec.m_vec128bit, vlen);
			*((VECTOR3F_t*)dst_ptr) = vec.m_vec3f;
		}
		else if (vec1_count)
		{
			dst_ptr[0] = src_ptr[0] / len;
		}

		return res_ptr;
	}

	static PFX_FORCE_INLINE  float_t* normalize(float_t* PARAM_INOUT vec_ptr, usize__t dim_count)
	{
		float_t* res_ptr = vec_ptr;
		float_t len = vector_length(vec_ptr, dim_count);

		if (matrix_inv_unsafe_std_t::is_near_zero(len))
		{
			return res_ptr;
		}

		usize__t vec4_count = dim_count >> 2;  // /4
		usize__t vec_remain = dim_count & 0x3; // %4
		usize__t vec3_count = (3 == vec_remain) ? (1.0) : (0.0);
		usize__t vec2_count = (2 == vec_remain) ? (1.0) : (0.0);
		usize__t vec1_count = (1 == vec_remain) ? (1.0) : (0.0);

		__m128 vlen = _mm_set_ps1(1.0 / len);
		for (uindex_t itr = vec4_count; itr != 0;)
		{
			--itr;
			__m128 r1 = _mm_load_ps(vec_ptr);
			r1 = _mm_mul_ps(r1, vlen);
			_mm_store_ps(vec_ptr, r1);
			vec_ptr += 4;
		}
		if (vec3_count)
		{
			SIMD_128BIT(vec);
			__m128 r1 = _mm_load_ps(vec_ptr);
			r1 = _mm_mul_ps(vec.m_vec128bit, vlen);
			*((VECTOR3F_t*)vec_ptr) = vec.m_vec3f;
		}
		else if (vec2_count)
		{
			SIMD_128BIT(vec);
			__m128 r1 = _mm_load_ps(vec_ptr);
			r1 = _mm_mul_ps(vec.m_vec128bit, vlen);
			*((VECTOR3F_t*)vec_ptr) = vec.m_vec3f;
		}
		else if (vec1_count)
		{
			vec_ptr[0] = vec_ptr[0] / len;
		}

		return res_ptr;
	}

	static PFX_FORCE_INLINE  VECTOR2F_t* normalize(VECTOR2F_t& PFX_RESTRICT PARAM_OUT dst,
		const VECTOR2F_t& PFX_RESTRICT PARAM_IN src)
	{
		SIMD_128BIT(vec);
		vec.m_vec2f[0] = src;

		__m128 r1 = _mm_mul_ps(vec.m_vec128bit, vec.m_vec128bit); // r1 = (x*x, y*y, z*z, w*w)
		__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1)); // r2 = (r1.y, r1.y, r1.y, r1.y)
		r2 = _mm_add_ss(r1, r2); // r2.x += r1.x = x*x + y*y;

		__m128 r4 = _mm_rsqrt_ss(r2);
		r4 = _mm_shuffle_ps(r4, r4, _MM_SHUFFLE(0, 0, 0, 0));
		vec.m_vec128bit = _mm_mul_ps(vec.m_vec128bit, r4);

		dst = vec.m_vec2f[0];
		return &dst;
	}

	static PFX_FORCE_INLINE  VECTOR2F_t* normalize(VECTOR2F_t& PARAM_INOUT __vec)
	{
		SIMD_128BIT(vec);
		vec.m_vec2f[0] = __vec;

		__m128 r1 = _mm_mul_ps(vec.m_vec128bit, vec.m_vec128bit); // r1 = (x*x, y*y, z*z, w*w)
		__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1)); // r2 = (r1.y, r1.y, r1.y, r1.y)
		r2 = _mm_add_ss(r1, r2); // r2.x += r1.x = x*x + y*y;

		__m128 r4 = _mm_rsqrt_ss(r2);
		r4 = _mm_shuffle_ps(r4, r4, _MM_SHUFFLE(0, 0, 0, 0));
		vec.m_vec128bit = _mm_mul_ps(vec.m_vec128bit, r4);

		__vec = vec.m_vec2f[0];
		return &__vec;
	}
	static PFX_FORCE_INLINE  VECTOR3F_t* normalize(VECTOR3F_t& PFX_RESTRICT PARAM_OUT dst,
		const VECTOR3F_t& PFX_RESTRICT PARAM_IN src)
	{
		SIMD_128BIT(vec);
		vec.m_vec3f = src;

		__m128 r1 = _mm_mul_ps(vec.m_vec128bit, vec.m_vec128bit); // r1 = (x*x, y*y, z*z, w*w)
		__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1)); // r2 = (r1.y, r1.y, r1.y, r1.y)
		__m128 r3 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 2, 2, 2)); // r3 = (r1.z, r1.z, r1.z, r1.z)

		r2 = _mm_add_ss(r1, r2); // r2.x += r1.x = x*x + y*y;
		r2 = _mm_add_ss(r3, r2); // r2.x += r3.x = x*x + y*y + z*z;

		__m128 r4 = _mm_rsqrt_ss(r2);
		r4 = _mm_shuffle_ps(r4, r4, _MM_SHUFFLE(0, 0, 0, 0));
		vec.m_vec128bit = _mm_mul_ps(vec.m_vec128bit, r4);

		dst = vec.m_vec3f;
		return &dst;
	}

	static PFX_FORCE_INLINE  VECTOR3F_t* normalize(VECTOR3F_t& PARAM_INOUT __vec)
	{
		SIMD_128BIT(vec);
		vec.m_vec3f = __vec;

		__m128 r1 = _mm_mul_ps(vec.m_vec128bit, vec.m_vec128bit); // r1 = (x*x, y*y, z*z, w*w)
		__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1)); // r2 = (r1.y, r1.y, r1.y, r1.y)
		__m128 r3 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 2, 2, 2)); // r3 = (r1.z, r1.z, r1.z, r1.z)

		r2 = _mm_add_ss(r1, r2); // r2.x += r1.x = x*x + y*y;
		r2 = _mm_add_ss(r3, r2); // r2.x += r3.x = x*x + y*y + z*z;

		__m128 r4 = _mm_rsqrt_ss(r2);
		r4 = _mm_shuffle_ps(r4, r4, _MM_SHUFFLE(0, 0, 0, 0));
		vec.m_vec128bit = _mm_mul_ps(vec.m_vec128bit, r4);

		__vec = vec.m_vec3f;
		return &__vec;
	}
	static PFX_FORCE_INLINE  VECTOR4F_t* normalize(VECTOR4F_t& PFX_RESTRICT PARAM_OUT dst,
		const VECTOR4F_t& PFX_RESTRICT PARAM_IN src)
	{
		__m128 vec = _mm_load_ps((float_t*)&src);

		__m128 r1 = _mm_mul_ps(vec, vec); // r1 = (x*x, y*y, z*z, w*w)
		__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1)); // r2 = (r1.y, r1.y, r1.y, r1.y)
		__m128 r3 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 2, 2, 2)); // r3 = (r1.z, r1.z, r1.z, r1.z)
		__m128 r4 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(3, 3, 3, 3)); // r4 = (r1.w, r1.w, r1.w, r1.w)

		r2 = _mm_add_ss(r1, r2); // r2.x += r1.x = x*x + y*y;
		r2 = _mm_add_ss(r3, r2); // r2.x += r3.x = x*x + y*y + z*z;
		r2 = _mm_add_ss(r4, r2); // r2.x += r4.x = x*x + y*y + z*z + w*w;

		r4 = _mm_rsqrt_ss(r2);
		r4 = _mm_shuffle_ps(r4, r4, _MM_SHUFFLE(0, 0, 0, 0));
		vec = _mm_mul_ps(vec, r4);

		_mm_store_ps((float_t*)&dst, vec);
		return &dst;
	}

	static PFX_FORCE_INLINE  VECTOR4F_t* normalize(VECTOR4F_t& PARAM_INOUT __vec)
	{
		__m128 vec = _mm_load_ps((float_t*)&__vec);

		__m128 r1 = _mm_mul_ps(vec, vec); // r1 = (x*x, y*y, z*z, w*w)
		__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1)); // r2 = (r1.y, r1.y, r1.y, r1.y)
		__m128 r3 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 2, 2, 2)); // r3 = (r1.z, r1.z, r1.z, r1.z)
		__m128 r4 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(3, 3, 3, 3)); // r4 = (r1.w, r1.w, r1.w, r1.w)

		r2 = _mm_add_ss(r1, r2); // r2.x += r1.x = x*x + y*y;
		r2 = _mm_add_ss(r3, r2); // r2.x += r3.x = x*x + y*y + z*z;
		r2 = _mm_add_ss(r4, r2); // r2.x += r4.x = x*x + y*y + z*z + w*w;

		r4 = _mm_rsqrt_ss(r2);
		r4 = _mm_shuffle_ps(r4, r4, _MM_SHUFFLE(0, 0, 0, 0));
		vec = _mm_mul_ps(vec, r4);

		_mm_store_ps((float_t*)&__vec, vec);
		return &__vec;
	}

	static PFX_FORCE_INLINE  VECTOR4F_t* normalize_vec3_extern(VECTOR4F_t& PFX_RESTRICT PARAM_OUT dst,
		const VECTOR4F_t& PFX_RESTRICT PARAM_IN src)
	{
		__m128 vec = _mm_load_ps((float_t*)&src);

		__m128 r1 = _mm_mul_ps(vec, vec); // r1 = (x*x, y*y, z*z, w*w)
		__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1)); // r2 = (r1.y, r1.y, r1.y, r1.y)
		__m128 r3 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 2, 2, 2)); // r3 = (r1.z, r1.z, r1.z, r1.z)
		__m128 r4;

		r2 = _mm_add_ss(r1, r2); // r2.x += r1.x = x*x + y*y;
		r2 = _mm_add_ss(r3, r2); // r2.x += r3.x = x*x + y*y + z*z;

		r4 = _mm_rsqrt_ss(r2);
		r4 = _mm_shuffle_ps(r4, r4, _MM_SHUFFLE(0, 0, 0, 0));
		vec = _mm_mul_ps(vec, r4);

		_mm_store_ps((float_t*)&dst, vec);
		return &dst;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* normalize_vec3_extern(VECTOR4F_t& PARAM_INOUT __vec)
	{
		__m128 vec = _mm_load_ps((float_t*)&__vec);

		__m128 r1 = _mm_mul_ps(vec, vec); // r1 = (x*x, y*y, z*z, w*w)
		__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1)); // r2 = (r1.y, r1.y, r1.y, r1.y)
		__m128 r3 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 2, 2, 2)); // r3 = (r1.z, r1.z, r1.z, r1.z)
		__m128 r4;

		r2 = _mm_add_ss(r1, r2); // r2.x += r1.x = x*x + y*y;
		r2 = _mm_add_ss(r3, r2); // r2.x += r3.x = x*x + y*y + z*z;

		r4 = _mm_rsqrt_ss(r2);
		r4 = _mm_shuffle_ps(r4, r4, _MM_SHUFFLE(0, 0, 0, 0));
		vec = _mm_mul_ps(vec, r4);

		_mm_store_ps((float_t*)&__vec, vec);
		return &__vec;
	}


	static PFX_FORCE_INLINE float_t vector_length(const VECTOR2F_t& PARAM_IN __vec)
	{
		float_t res;
		SIMD_128BIT(vec);
		vec.m_vec2f[0] = __vec;

		__m128 r1 = _mm_mul_ps(vec.m_vec128bit, vec.m_vec128bit); // r1 = (x*x, y*y, z*z, w*w)
		__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1)); // r2 = (r1.y, r1.y, r1.y, r1.y)
		r2 = _mm_add_ss(r1, r2); // r2.x += r1.x = x*x + y*y;
		__m128 r4 = _mm_sqrt_ss(r2);
		_mm_store_ss(&res, r4);
	}

	static PFX_FORCE_INLINE float_t vector_length(const VECTOR3F_t& PARAM_IN __vec)
	{
		float_t res;
		SIMD_128BIT(vec);
		vec.m_vec3f = __vec;

		__m128 r1 = _mm_mul_ps(vec.m_vec128bit, vec.m_vec128bit); // r1 = (x*x, y*y, z*z, w*w)
		__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1)); // r2 = (r1.y, r1.y, r1.y, r1.y)
		__m128 r3 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 2, 2, 2)); // r3 = (r1.z, r1.z, r1.z, r1.z)

		r2 = _mm_add_ss(r1, r2); // r2.x += r1.x = x*x + y*y;
		r2 = _mm_add_ss(r3, r2); // r2.x += r3.x = x*x + y*y + z*z;

		__m128 r4 = _mm_sqrt_ss(r2);
		_mm_store_ss(&res, r4);

		return res;
	}

	static PFX_FORCE_INLINE float_t vector_length(const VECTOR4F_t& PARAM_IN __vec)
	{
		float res;
		__m128 vec = _mm_load_ps((float_t*)&__vec);
		__m128 r1 = _mm_mul_ps(vec, vec); // r1 = (x*x, y*y, z*z, w*w)
		__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1)); // r2 = (r1.y, r1.y, r1.y, r1.y)
		__m128 r3 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 2, 2, 2)); // r3 = (r1.z, r1.z, r1.z, r1.z)
		__m128 r4 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(3, 3, 3, 3)); // r3 = (r1.w, r1.w, r1.w, r1.w)

		r2 = _mm_add_ss(r1, r2); // r2.x += r1.x = x*x + y*y;
		r2 = _mm_add_ss(r3, r2); // r2.x += r3.x = x*x + y*y + z*z + w*w;
		r2 = _mm_add_ss(r4, r2); // r2.x += r3.x = x*x + y*y + z*z + w*w;

		r4 = _mm_sqrt_ss(r2);
		_mm_store_ss(&res, r4);

		return res;
	}

	static PFX_FORCE_INLINE float_t vector_length_vec3_extern(const VECTOR4F_t& PARAM_IN __vec)
	{
		float res;
		__m128 vec = _mm_load_ps((float_t*)&__vec);
		__m128 r1 = _mm_mul_ps(vec, vec); // r1 = (x*x, y*y, z*z, w*w)
		__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1)); // r2 = (r1.y, r1.y, r1.y, r1.y)
		__m128 r3 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 2, 2, 2)); // r3 = (r1.z, r1.z, r1.z, r1.z)

		r2 = _mm_add_ss(r1, r2); // r2.x += r1.x = x*x + y*y;
		r2 = _mm_add_ss(r3, r2); // r2.x += r3.x = x*x + y*y * z*z;

		__m128 r4 = _mm_sqrt_ss(r2);
		_mm_store_ss(&res, r4);

		return res;
	}

}vector_normalize_unsafe_see_t;


PFX_INLINE simd_fvec_normalize_unsafe_t* init_simd_fvec_normalize_sse(simd_fvec_normalize_unsafe_t& __fvec)
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

	return &__fvec;
}

PECKER_END

#endif			//PFX_SIMD_FMATNORNALIZE_SSE_H_
