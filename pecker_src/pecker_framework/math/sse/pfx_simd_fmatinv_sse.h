/*
 * pfx_simd_fmatinv_sse.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMATINV_SSE_H_
#define		PFX_SIMD_FMATINV_SSE_H_

#include "../pfx_simd_fmatinv_std.h"
#include "pfx_simd_fmatdet_sse.h"
#include "pfx_simd_fmatdot_sse.h"

PECKER_BEGIN

typedef struct st_matrix_inv_unsafe_sse
{
	static PFX_FORCE_INLINE bool is_near_zero(__m128 x)
	{
		uint_t res;
		__m128 r1 = is_near_zero_ss(x);
		_mm_store_ss((float_t*)&res, r1);
		return res;
	}
	static PFX_FORCE_INLINE void is_near_zero(__m128 x, uint_t PARAM_OUT res[4])
	{
		__m128 r1 = is_near_zero_ss(x);
		_mm_store_ss((float_t*)res, r1);
	}
	static PFX_FORCE_INLINE __m128 is_near_zero_ss(__m128 x)
	{
		__m128 r1 = _mm_set_ps1(0.0);
		return _mm_cmpeq_ss(r1, x);	
	}
	static PFX_FORCE_INLINE __m128 is_near_zero_ps(__m128 x)
	{
		__m128 r1 = _mm_set_ps1(0.0);
		return _mm_cmpeq_ps(r1, x);
	}



	static PFX_FORCE_INLINE bool inverse2x2(__m128& PARAM_INOUT mat)
	{
		//__m128 res_det;
		__m128 det = matrix_det_unsafe_sse_t::det2x2(mat);

		if (is_near_zero(det))
		{
			return false;
		}
		//__m128 mdet = _mm_xor_ps(det, matrix_set_unsafe_sse_t::get_signed_mask());
		__m128 mdet = matrix_set_unsafe_sse_t::vec_signed_not(det);
		det = _mm_shuffle_ps(det, mdet, _MM_SHUFFLE(0, 0, 0, 0));
		det = _mm_shuffle_ps(det, det, _MM_SHUFFLE(0, 2, 2, 0));

		
		// 求倒数然后再乘法，精度损失大
		// res_det = det;
		//det = _mm_rcp_ps(det);
		//mat = _mm_mul_ps(det, mat);
		mat = _mm_div_ps(mat, det);
		
		//mat = _mm_shuffle_ps(mat, mat, _MM_SHUFFLE(0, 1, 2, 3));
		mat = _mm_shuffle_ps(mat, mat, _MM_SHUFFLE(0, 2, 1, 3));

		return true;

	}

	static PFX_FORCE_INLINE bool inverse3x3(__m128  PARAM_OUT vec[3])
	{
		//  M      = [ A, B]
		//           [ C, D]
		//	
		//  M^(-1) = [ A^(-1) + A^(-1)*B*(D - C*A^(-1)*B)^(-1) * C * A^(-1), - A^(-1)*B*(D - C*A^(-1)*B)^(-1) ]
		//			 [ 	-(D - C*A^(-1)*B)^(-1) * C * A^(-1)                ,   (D - C*A^(-1)*B)^(-1)]
		// a1 = A^(-1);
		// a1b = A^(-1)*B = a1 * B;
		// ca1 = C*A^(-1) = C * a1;
		// ca1b = C*A^(-1)*B = C * a1b = ca1 * B;
		// d1 = (D - C*A^(-1)*B)^(-1) = (D - ca1b) ^(-1);
		// 
		// 若A可逆,则M可逆充分必要条件d1可逆
		// M^(-1) = [a1+a1b*d1*ca1, -a1b*d1]
		//          [-d1 * ca1,     d1    ]
		//
		__m128 tmp, a1, a1b, ca1, d1, a1bd1, r1, r2;

		a1 = _mm_shuffle_ps(vec[0], vec[1], _MM_SHUFFLE(1, 0, 1, 0)); //a
		// tmp = a1;
		if (!inverse2x2(a1))
		{
			return false;
		}

		tmp = _mm_shuffle_ps(vec[0], vec[1], _MM_SHUFFLE(2, 2, 2, 2)); //b 2x1
		
		r1 = _mm_shuffle_ps(a1, a1, _MM_SHUFFLE(3, 1, 2, 0));
		r2 = _mm_mul_ps(tmp, r1);
		r1 = _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(1,0,3,2));
		a1b = _mm_add_ps(r1, r2);  //a1b 2x1


		tmp = _mm_shuffle_ps(vec[2], vec[2], _MM_SHUFFLE(1, 0, 1, 0)); //c 2x1
		r1 = _mm_shuffle_ps(a1, a1, _MM_SHUFFLE(3, 1, 2, 0));
		r1 = _mm_mul_ps(r1, tmp);
		r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2,0,2,0));
		r1 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(3, 1, 3, 1));
		ca1= _mm_add_ps(r1, r2); // ca1 1x2

		tmp = _mm_mul_ps(tmp, a1b);
		r1 = _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(2, 3, 0, 1));
		tmp = _mm_add_ps(r1, tmp);		   // ca1b 1x1

		d1 = _mm_shuffle_ps(vec[2], vec[2], _MM_SHUFFLE(2, 2, 2, 2)); //d	   /1x1
		d1 = _mm_sub_ps(d1, tmp); // 1/d1  1x1

		if (is_near_zero(d1))
		{
			return false;
		}

		tmp = _mm_div_ps(ca1, d1);
		tmp = matrix_set_unsafe_sse_t::vec_signed_not(tmp);	 //-d1 * ca1

		// 求倒数损失真坑爹
		//r1 = _mm_rcp_ps(d1);
		r1 = _mm_set_ss(1.0);
		r1 = _mm_div_ss(r1, d1);
		vec[2] = _mm_shuffle_ps(tmp, r1, _MM_SHUFFLE(0, 0, 1, 0));

		a1bd1 = _mm_div_ps(a1b, d1);			///a1b*d1	2x1

		r1 = _mm_shuffle_ps(a1bd1, a1bd1, _MM_SHUFFLE(1, 1, 0, 0));
		tmp = _mm_shuffle_ps(ca1, ca1, _MM_SHUFFLE(1, 0, 1, 0));
		tmp = _mm_mul_ps(r1, tmp);			   //a1b*d1*ca1 2x2

		tmp = _mm_add_ps(a1, tmp); //a1+a1b*d1*ca1

		a1bd1 = matrix_set_unsafe_sse_t::vec_signed_not(a1bd1);	// -a1b*d1
		vec[0] = _mm_shuffle_ps(tmp, a1bd1, _MM_SHUFFLE(0, 0, 1, 0));
		vec[1] = _mm_shuffle_ps(tmp, a1bd1, _MM_SHUFFLE(1, 1, 3, 2));



		return true;
	}

	static PFX_FORCE_INLINE bool inverse4x4(__m128  PARAM_INOUT vec[4])
	{
		//  M      = [ A, B]
		//           [ C, D]
		//	
		//  M^(-1) = [ A^(-1) + A^(-1)*B*(D - C*A^(-1)*B)^(-1) * C * A^(-1), - A^(-1)*B*(D - C*A^(-1)*B)^(-1) ]
		//			 [ 	-(D - C*A^(-1)*B)^(-1) * C * A^(-1)                ,   (D - C*A^(-1)*B)^(-1)]
		// a1 = A^(-1);
		// a1b = A^(-1)*B = a1 * B;
		// ca1 = C*A^(-1) = C * a1;
		// ca1b = C*A^(-1)*B = C * a1b = ca1 * B;
		// d1 = (D - C*A^(-1)*B)^(-1) = (D - ca1b) ^(-1);
		// 
		// 若A可逆,则M可逆充分必要条件d1可逆
		// M^(-1) = [a1+a1b*d1*ca1, -a1b*d1]
		//          [-d1 * ca1,     d1    ]
		//
		__m128 tmp,a1,a1b,ca1,d1,a1bd1;
		
		a1 = _mm_shuffle_ps(vec[0], vec[1], _MM_SHUFFLE(1, 0, 1, 0)); //a
		// tmp = a1;
		if (!inverse2x2(a1))
		{
			return false;
		}
		//tmp = matrix_dot_unsafe_sse_t::mat2x2_mul(tmp, a1);

		tmp = _mm_shuffle_ps(vec[0], vec[1], _MM_SHUFFLE(3, 2, 3, 2)); //b
		a1b = matrix_dot_unsafe_sse_t::mat2x2_mul(a1, tmp);

		tmp = _mm_shuffle_ps(vec[2], vec[3], _MM_SHUFFLE(1, 0, 1, 0)); //c
		ca1 = matrix_dot_unsafe_sse_t::mat2x2_mul(tmp, a1);
		tmp = matrix_dot_unsafe_sse_t::mat2x2_mul(tmp, a1b);	// ca1b

		d1  = _mm_shuffle_ps(vec[2], vec[3], _MM_SHUFFLE(3, 2, 3, 2)); //d
		d1 = _mm_sub_ps(d1, tmp);

		if (!inverse2x2(d1))
		{
			return false;
		}

		tmp = matrix_dot_unsafe_sse_t::mat2x2_mul(d1, ca1);
		tmp = matrix_set_unsafe_sse_t::vec_signed_not(tmp);	 //-d1 * ca1

		vec[2] = _mm_shuffle_ps(tmp, d1, _MM_SHUFFLE(1, 0, 1, 0));
		vec[3] = _mm_shuffle_ps(tmp, d1, _MM_SHUFFLE(3, 2, 3, 2));

		a1bd1 = matrix_dot_unsafe_sse_t::mat2x2_mul(a1b, d1);	 ///a1b*d1
		tmp   = matrix_dot_unsafe_sse_t::mat2x2_mul(a1bd1, ca1); //a1b*d1*ca1
		tmp   = _mm_add_ps(a1, tmp); //a1+a1b*d1*ca1

		a1bd1 = matrix_set_unsafe_sse_t::vec_signed_not(a1bd1);	// -a1b*d1
		vec[0] = _mm_shuffle_ps(tmp, a1bd1, _MM_SHUFFLE(1, 0, 1, 0));
		vec[1] = _mm_shuffle_ps(tmp, a1bd1, _MM_SHUFFLE(3, 2, 3, 2));



		return true;
	}


	static PFX_FORCE_INLINE MATRIX2F_t* inverse2x2(MATRIX2F_t& PFX_RESTRICT PARAM_OUT dst,
	MATRIX2F_t& PFX_RESTRICT __src)
	{
		__m128 src;
		matrix_set_unsafe_sse_t::mat2x2_load(__src, src);
		if (inverse2x2(src))
		{
			matrix_set_unsafe_sse_t::mat2x2_store(dst, src);
			return &dst;
		}
		else
		{
			return null;
		}
	}

	static PFX_FORCE_INLINE MATRIX3F_t* inverse3x3(MATRIX3F_t& PFX_RESTRICT PARAM_OUT dst,
		MATRIX3F_t& PFX_RESTRICT __src)
	{
		__m128 src[3];
		matrix_set_unsafe_sse_t::mat3x3_load(__src, src);
		if (inverse3x3(src))
		{
			matrix_set_unsafe_sse_t::mat3x3_store(dst, src);
			return &dst;
		}
		else
		{
			return null;
		}
		return &dst;

	}

	static PFX_FORCE_INLINE MATRIX4F_t* inverse4x4(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst,
		MATRIX4F_t& PFX_RESTRICT __src)
	{
		__m128 src[4];
		matrix_set_unsafe_sse_t::mat4x4_load(__src, src);
		if (inverse4x4(src))
		{
			matrix_set_unsafe_sse_t::mat4x4_store(dst, src);
			return &dst;
		}
		else
		{
			return null;
		}
		return &dst;
	}

	

}matrix_inv_unsafe_sse_t;



PFX_INLINE simd_fmat_inverse_unsafe_t*	init_simd_fmat_inv_sse(simd_fmat_inverse_unsafe_t& __fmat)
{
	//__fmat.is_near_zero = matrix_inv_unsafe_std_t::is_near_zero;
	__fmat.inverse2x2   = matrix_inv_unsafe_sse_t::inverse2x2;
	__fmat.inverse3x3   = matrix_inv_unsafe_sse_t::inverse3x3;
	__fmat.inverse4x4   = matrix_inv_unsafe_sse_t::inverse4x4;

	__fmat.inverse3x3_externAC01_col_major = matrix_inv_unsafe_sse_t::inverse4x4;
	__fmat.inverse3x3_externA0C1_col_major = matrix_inv_unsafe_sse_t::inverse4x4;
	__fmat.inverse3x3_externAC01_row_major = matrix_inv_unsafe_sse_t::inverse4x4;
	__fmat.inverse3x3_externA0C1_row_major = matrix_inv_unsafe_sse_t::inverse4x4;
	return &__fmat;
}

PECKER_END

#endif			//PFX_SIMD_FMATINV_SSE_H_
