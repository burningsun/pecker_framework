/*
 * pfx_simd_fmatdet_sse.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMATDET_SSE_H_
#define		PFX_SIMD_FMATDET_SSE_H_

#include "../pfx_simd_param_sse.h"
#include "../pfx_simd_fmatdet_std.h"
#include "pfx_simd_fmatset_sse.h"

PECKER_BEGIN

typedef struct st_matrix_det_unsafe_sse
{
	static PFX_FORCE_INLINE __m128 det2x2(__m128 PARAM_IN __mat)
	{
		__m128 r1 = _mm_shuffle_ps(__mat, __mat, _MM_SHUFFLE(0, 1, 2, 3));
		r1 = _mm_mul_ps(r1, __mat);
		__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1));
		r2 = _mm_sub_ss(r1, r2);
		return r2;
	}
	static PFX_FORCE_INLINE __m128 det3x3(__m128 PARAM_OUT __mat[3])
	{
		__m128 res;
		__m128 det2;
		// row2, row3, col2, col3
		__m128 r1 = _mm_shuffle_ps(__mat[1], __mat[2], _MM_SHUFFLE(2, 1, 2, 1));
		det2 = det2x2(r1);
		// GetVAL(__mat, row1, col1)
		r1 = _mm_shuffle_ps(__mat[0], __mat[0], _MM_SHUFFLE(0, 0, 0, 0));
		res = _mm_mul_ss(det2, r1);
		// row2, row3, col1, col3
		r1 = _mm_shuffle_ps(__mat[1], __mat[2], _MM_SHUFFLE(2, 0, 2, 0));
		det2 = det2x2(r1);
		// GetVAL(__mat,  row1, col2)
		r1 = _mm_shuffle_ps(__mat[0], __mat[0], _MM_SHUFFLE(1, 1, 1, 1));
		r1 = _mm_mul_ss(det2, r1);
		res = _mm_sub_ss(res, r1);
		// row2, row3, col1, col2
		r1 = _mm_shuffle_ps(__mat[1], __mat[2], _MM_SHUFFLE(1, 0, 1, 0));
		det2 = det2x2(r1);
		// GetVAL(__mat, row1, col3)
		r1 = _mm_shuffle_ps(__mat[0], __mat[0], _MM_SHUFFLE(2, 2, 2, 2));
		r1 = _mm_mul_ss(det2, r1);
		res = _mm_add_ss(res, r1);

		return res;
	}
	static PFX_FORCE_INLINE __m128 det4x4(__m128 PARAM_IN __mat[4])
	{
		
		__m128 mat3x3[3];
		__m128 det3;
		__m128 res;
		__m128 r1;

		//MAT3X3_DET(GetVAL, res, tmp1, __mat, row2, row3, row4, col2, col3, col4);
		mat3x3[0] = _mm_shuffle_ps(__mat[1], __mat[1], _MM_SHUFFLE(3, 3, 2, 1));
		mat3x3[1] = _mm_shuffle_ps(__mat[2], __mat[2], _MM_SHUFFLE(3, 3, 2, 1));
		mat3x3[2] = _mm_shuffle_ps(__mat[3], __mat[3], _MM_SHUFFLE(3, 3, 2, 1));

		//	GetVAL(__mat, row1, col1);
		r1 = _mm_shuffle_ps(__mat[0], __mat[0], _MM_SHUFFLE(0, 0, 0, 0));
		det3 = det3x3(mat3x3);
		res = _mm_mul_ss(det3, r1);

		//	MAT3X3_DET(GetVAL, tmp, tmp1, __mat, row2, row3, row4, col1, col3, col4); 
		//	res -= tmp * GetVAL(__mat, row1, col2);
		mat3x3[0] = _mm_shuffle_ps(__mat[1], __mat[1], _MM_SHUFFLE(3, 3, 2, 0));
		mat3x3[1] = _mm_shuffle_ps(__mat[2], __mat[2], _MM_SHUFFLE(3, 3, 2, 0));
		mat3x3[2] = _mm_shuffle_ps(__mat[3], __mat[3], _MM_SHUFFLE(3, 3, 2, 0));

		//	GetVAL(__mat, row1, col2);
		r1 = _mm_shuffle_ps(__mat[0], __mat[0], _MM_SHUFFLE(1, 1, 1, 1));
		det3 = det3x3(mat3x3);
		r1 = _mm_mul_ss(det3, r1);
		res = _mm_sub_ss(res, r1);

		//	MAT3X3_DET(GetVAL, tmp, tmp1, __mat, row2, row3, row4, col1, col2, col4);
		//	res += tmp * GetVAL(__mat, row1, col3); 
		mat3x3[0] = _mm_shuffle_ps(__mat[1], __mat[1], _MM_SHUFFLE(3, 3, 1, 0));
		mat3x3[1] = _mm_shuffle_ps(__mat[2], __mat[2], _MM_SHUFFLE(3, 3, 1, 0));
		mat3x3[2] = _mm_shuffle_ps(__mat[3], __mat[3], _MM_SHUFFLE(3, 3, 1, 0));

		//	GetVAL(__mat, row1, col3);
		r1 = _mm_shuffle_ps(__mat[0], __mat[0], _MM_SHUFFLE(2, 2, 2, 2));
		det3 = det3x3(mat3x3);
		r1 = _mm_mul_ss(det3, r1);
		res = _mm_add_ss(res, r1);

		//	MAT3X3_DET(GetVAL, tmp, tmp1, __mat, row2, row3, row4, col1, col2, col3);
		//	res -= tmp * GetVAL(__mat, row1, col4);
		//mat3x3[0] = _mm_shuffle_ps(__mat[1], __mat[1], _MM_SHUFFLE(3, 2, 1, 0));
		//mat3x3[1] = _mm_shuffle_ps(__mat[2], __mat[2], _MM_SHUFFLE(3, 2, 1, 0));
		//mat3x3[2] = _mm_shuffle_ps(__mat[3], __mat[3], _MM_SHUFFLE(3, 2, 1, 0));

		//	GetVAL(__mat, row1, col4)
		r1 = _mm_shuffle_ps(__mat[0], __mat[0], _MM_SHUFFLE(3, 3, 3, 3));
		det3 = det3x3(&__mat[1]);
		r1 = _mm_mul_ss(det3, r1);
		res = _mm_sub_ss(res, r1);

		return res;
	}



	static PFX_FORCE_INLINE float_t det2x2 (const MATRIX2F_t& __mat)
	{
		float_t res;
		__m128 vec;
		matrix_set_unsafe_sse_t::mat2x2_load(__mat, vec);
		__m128 __res = det2x2(vec);
		_mm_store_ss(&res, __res);
		return res;
	}

	static PFX_FORCE_INLINE float_t det3x3(const MATRIX3F_t& __mat)
	{
		float_t res;
		__m128 vec[3];
		matrix_set_unsafe_sse_t::mat3x3_load(__mat, vec);
		__m128 __res = det3x3(vec);
		_mm_store_ss(&res, __res);
		return res;
	}

	static PFX_FORCE_INLINE float_t det4x4(const MATRIX4F_t& __mat)
	{
		float_t res;
		__m128 vec[4];
		matrix_set_unsafe_sse_t::mat4x4_load(__mat, vec);
		__m128 __res = det4x4(vec);
		_mm_store_ss(&res, __res);
		return res;
	}

}matrix_det_unsafe_sse_t;


PFX_INLINE simd_fmat_det_unsafe_t*	init_simd_fmat_det_sse(simd_fmat_det_unsafe_t& __fmat_det)
{
	__fmat_det.fmat_det2x2  = matrix_det_unsafe_std_t::det2x2;
	__fmat_det.fmat_det3x3  = matrix_det_unsafe_std_t::det3x3;
	__fmat_det.fmat_det4x4  = matrix_det_unsafe_std_t::det4x4;
	return &__fmat_det;
}

PECKER_END

#endif			//PFX_SIMD_FMATDET_SSE_H_
