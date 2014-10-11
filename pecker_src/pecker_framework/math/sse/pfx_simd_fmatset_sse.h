/*
 * pfx_simd_fmatset_std.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMATSET_SSE_H_
#define		PFX_SIMD_FMATSET_SSE_H_

#include "../pfx_simd_fmatset_std.h"
#include "../pfx_simd_param_sse.h"

PECKER_BEGIN

typedef struct st_matrix_set_unsafe_sse
{
	static PFX_FORCE_INLINE __m128 setmask_ss(uint_t __mask)
	{
		union
		{
			float_t m_f;
			uint_t  m_i;
		}  val;
		val.m_i = __mask;
		return 	_mm_set_ss(val.m_f);
	}
	static PFX_FORCE_INLINE __m128 setmask(uint_t __mask)
	{
		union
		{
			float_t m_f;
			uint_t  m_i;
		}  val;
		val.m_i = __mask;
		return 	_mm_set_ps1(val.m_f);
	}

	static PFX_FORCE_INLINE __m128 get_signed_mask()
	{
		static __m128 signed_mask = setmask_ss((uint_t)0x80000000);
		return signed_mask;
	}

	static PFX_FORCE_INLINE __m128 vec_signed_not(__m128 vec)
	{
		static __m128 signed_mask = setmask((uint_t)0x80000000);
		__m128 res = _mm_xor_ps(vec, signed_mask);
		return res;
	}


	static PFX_FORCE_INLINE void mat2x2_set(__m128& PARAM_OUT __mat,
		float_t m11, float_t m12,
		float_t m21, float_t m22, bool bcol = true)
	{
		if (bcol)
		{
			mat2x2_set_col_major(__mat, m11, m12, m21, m22);
		}
		else
		{
			mat2x2_set_row_major(__mat, m11, m12, m21, m22);
		}
	}

	static PFX_FORCE_INLINE void mat3x3_set(__m128 PARAM_OUT __mat[3],
		float_t m11, float_t m12, float_t m13,
		float_t m21, float_t m22, float_t m23,
		float_t m31, float_t m32, float_t m33, bool bcol = true)
	{
		if (bcol)
		{
			return mat3x3_set_col_major(__mat,
				m11, m12, m13,
				m21, m22, m23,
				m31, m32, m33);
		}
		else
		{
			return mat3x3_set_row_major(__mat,
				m11, m12, m13,
				m21, m22, m23,
				m31, m32, m33);
		}
	}

	static PFX_FORCE_INLINE void mat4x4_set(__m128 PARAM_OUT __mat[4],
		float_t m11, float_t m12, float_t m13, float_t m14,
		float_t m21, float_t m22, float_t m23, float_t m24,
		float_t m31, float_t m32, float_t m33, float_t m34,
		float_t m41, float_t m42, float_t m43, float_t m44, bool bcol = true)
	{
		if (bcol)
		{
			 mat4x4_set_col_major(__mat,
				m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44);
		}
		else
		{
			 mat4x4_set_row_major(__mat,
				m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44);
		}
	}

	static PFX_FORCE_INLINE void mat2x2_load(const MATRIX2F_t& PARAM_IN __mat, 
		__m128& PARAM_OUT vec)
	{
		vec = _mm_load_ps((float_t*)&__mat);
	}
	static PFX_FORCE_INLINE void mat3x3_load(const MATRIX3F_t& PARAM_IN __mat,
		__m128 PARAM_OUT vec[3])
	{
#define PFXMAT(__mat,row,col) __mat.m_mat[col].m_vec[row]
		vec[0] = _mm_load_ps((float_t*)&__mat);
		vec[1] = _mm_load_ps((float_t*)&__mat + 4);
		vec[2] = _mm_set_ps1(PFXMAT(__mat, 2, 2));

		vec[2] = _mm_shuffle_ps(vec[1], vec[2], _MM_SHUFFLE(3, 2, 3, 2));
		vec[1] = _mm_shuffle_ps(vec[0], vec[1], _MM_SHUFFLE(1, 0, 3, 3));
		vec[1] = _mm_shuffle_ps(vec[1], vec[1], _MM_SHUFFLE(3, 3, 2, 1));
		
#undef PFXMAT
	}
	static PFX_FORCE_INLINE void mat4x4_load(const MATRIX4F_t& PARAM_IN __mat,
		__m128 PARAM_OUT vec[4])
	{
		vec[0] = _mm_load_ps((float_t*)&__mat);
		vec[1] = _mm_load_ps((float_t*)&__mat + 4);
		vec[2] = _mm_load_ps((float_t*)&__mat + 8);
		vec[3] = _mm_load_ps((float_t*)&__mat + 12);
	}

	static PFX_FORCE_INLINE void mat2x2_store(MATRIX2F_t& PARAM_OUT __mat,
		__m128& PARAM_IN vec)
	{
		_mm_store_ps((float_t*)&__mat, vec);
	}
	static PFX_FORCE_INLINE void mat3x3_store(const MATRIX3F_t& PARAM_IN __mat,
		__m128 PARAM_OUT vec[3])
	{
		__m128 r1 = _mm_shuffle_ps(vec[0], vec[1], _MM_SHUFFLE(0, 0, 2, 3));
		r1 = _mm_shuffle_ps(vec[0], r1, _MM_SHUFFLE(2, 1, 1, 0));
		_mm_store_ps((float_t*)&__mat, r1);
		r1 = _mm_shuffle_ps(vec[1], vec[2], _MM_SHUFFLE(1, 0, 2, 1));
		_mm_store_ps((float_t*)&__mat+4, r1);
		r1 = _mm_shuffle_ps(vec[2], vec[2], _MM_SHUFFLE(2, 2, 2, 2));
		_mm_store_ss((float_t*)&__mat + 8, r1);
	}
	static PFX_FORCE_INLINE void mat4x4_store(const MATRIX4F_t& PARAM_IN __mat,
		__m128 PARAM_OUT vec[4])
	{
		 _mm_store_ps((float_t*)&__mat     , vec[0]);
		 _mm_store_ps((float_t*)&__mat + 4 , vec[1]);
		 _mm_store_ps((float_t*)&__mat + 8 , vec[2]);
		 _mm_store_ps((float_t*)&__mat + 12, vec[3]);
	}

	static PFX_FORCE_INLINE __m128 vector4_set(float_t x, float_t y,
		float_t z, float_t w)
	{
		return _mm_set_ps(w, z, y, x);
	}

	static PFX_FORCE_INLINE void mat2x2_set_col_major(__m128 PARAM_OUT __mat,
		float_t m11, float_t m12,
		float_t m21, float_t m22)
	{
		__mat = vector4_set(m11, m21, m12, m22);
	}

	static PFX_FORCE_INLINE void mat3x3_set_col_major(__m128 PARAM_OUT __mat[3],
		float_t m11, float_t m12, float_t m13,
		float_t m21, float_t m22, float_t m23,
		float_t m31, float_t m32, float_t m33)
	{
		__mat[0] = vector4_set(m11, m21, m31, 0.0);
		__mat[1] = vector4_set(m12, m22, m32, 0.0);
		__mat[2] = vector4_set(m13, m23, m33, 0.0);
	}

	static PFX_FORCE_INLINE void mat4x4_set_col_major(__m128 PARAM_OUT __mat[4],
		float_t m11, float_t m12, float_t m13, float_t m14,
		float_t m21, float_t m22, float_t m23, float_t m24,
		float_t m31, float_t m32, float_t m33, float_t m34,
		float_t m41, float_t m42, float_t m43, float_t m44)
	{
		__mat[0] = vector4_set(m11, m21, m31, m41);
		__mat[1] = vector4_set(m12, m22, m32, m42);
		__mat[2] = vector4_set(m13, m23, m33, m43);
		__mat[3] = vector4_set(m14, m24, m34, m44);
	}

	static PFX_FORCE_INLINE void mat2x2_set_row_major(__m128 PARAM_OUT __mat,
		float_t m11, float_t m12,
		float_t m21, float_t m22)
	{
		__mat = vector4_set(m11, m12,
			m21, m22);
	}

	static PFX_FORCE_INLINE void mat3x3_set_row_major(__m128 PARAM_OUT __mat[3],
		float_t m11, float_t m12, float_t m13,
		float_t m21, float_t m22, float_t m23,
		float_t m31, float_t m32, float_t m33)
	{
		__mat[0] = vector4_set(m11, m12, m13, 0.0);
		__mat[1] = vector4_set(m21, m22, m23, 0.0);
		__mat[2] = vector4_set(m31, m32, m33, 0.0);
	}

	static PFX_FORCE_INLINE void mat4x4_set_row_major(__m128 PARAM_OUT __mat[4],
		float_t m11, float_t m12, float_t m13, float_t m14,
		float_t m21, float_t m22, float_t m23, float_t m24,
		float_t m31, float_t m32, float_t m33, float_t m34,
		float_t m41, float_t m42, float_t m43, float_t m44)
	{
		__mat[0] = vector4_set(m11, m12, m13, m14);
		__mat[1] = vector4_set(m21, m22, m23, m24);
		__mat[2] = vector4_set(m31, m32, m33, m34);
		__mat[3] = vector4_set(m41, m42, m43, m44);
	}

	static PFX_FORCE_INLINE  void mat4x4_indentity(__m128 PARAM_OUT __mat[4], float_t _val = 1.0)
	{
		 mat4x4_set_row_major(__mat, MAT4_IDENTITY(_val));
	}
	static PFX_FORCE_INLINE  void mat4x4_scale(__m128 PARAM_OUT __mat[4],
		float_t x, float_t y, float_t z)
	{
		mat4x4_set_row_major(__mat, MAT4_SCALE(x, y, z));
	}
	static PFX_FORCE_INLINE  void mat4x4_translate_col_major(__m128 PARAM_OUT __mat[4],
		float_t x, float_t y, float_t z)
	{
		mat4x4_set_col_major(__mat, MAT_TRANSLATE(x, y, z));
	}
	static PFX_FORCE_INLINE  void mat4x4_translate_row_major(__m128 PARAM_OUT __mat[4],
		float_t x, float_t y, float_t z)
	{
		return mat4x4_set_row_major(__mat, MAT_TRANSLATE(x, y, z));;
	}

	static PFX_FORCE_INLINE  void mat4x4_rotateX_col_major(__m128 PARAM_OUT __mat[4], float_t rad)
	{
		float_t fSin = ::sin(rad);
		float_t fCos = ::cos(rad);
		mat4x4_set_col_major(__mat, MAT4_ROTATE_X(fCos, fSin));
	}
	static PFX_FORCE_INLINE  void mat4x4_rotateX_row_major(__m128 PARAM_OUT __mat[4], float_t rad)
	{
		float_t fSin = ::sin(rad);
		float_t fCos = ::cos(rad);
		mat4x4_set_row_major(__mat, MAT4_ROTATE_X(fCos, fSin));
	}
	static PFX_FORCE_INLINE  void mat4x4_rotateY_col_major(__m128 PARAM_OUT __mat[4], float_t rad)
	{
		float_t fSin = ::sin(rad);
		float_t fCos = ::cos(rad);
		mat4x4_set_col_major(__mat, MAT4_ROTATE_Y(fCos, fSin));
	}
	static PFX_FORCE_INLINE  void mat4x4_rotateY_row_major(__m128 PARAM_OUT __mat[4], float_t rad)
	{
		float_t fSin = ::sin(rad);
		float_t fCos = ::cos(rad);
		mat4x4_set_row_major(__mat, MAT4_ROTATE_Y(fCos, fSin));
	}
	static PFX_FORCE_INLINE  void mat4x4_rotateZ_col_major(__m128 PARAM_OUT __mat[4], float_t rad)
	{
		float_t fSin = ::sin(rad);
		float_t fCos = ::cos(rad);
		mat4x4_set_col_major(__mat, MAT4_ROTATE_Z(fCos, fSin));
	}
	static PFX_FORCE_INLINE  void mat4x4_rotateZ_row_major(__m128 PARAM_OUT __mat[4], float_t rad)
	{
		float_t fSin = ::sin(rad);
		float_t fCos = ::cos(rad);
		mat4x4_set_row_major(__mat, MAT4_ROTATE_Z(fCos, fSin));
	}

}matrix_set_unsafe_sse_t;



PECKER_END

#endif			//PFX_SIMD_FMATSET_H_
