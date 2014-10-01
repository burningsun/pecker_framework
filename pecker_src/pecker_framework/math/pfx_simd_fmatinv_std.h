/*
 * pfx_simd_fmatinv_std.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMATINV_H_
#define		PFX_SIMD_FMATINV_H_

#include "../pfx_defines.h"

#include "pfx_simd_param.h"
#include <math.h>
#include "pfx_simd_fadd_std.h"
#include "pfx_simd_fsub_std.h"
#include "pfx_simd_fmul_std.h"
#include "pfx_simd_fdiv_std.h"

#include "pfx_simd_fmatdet_std.h"
#include "pfx_simd_fmatdot_std.h"

PECKER_BEGIN

typedef struct st_matrix_inv_unsafe_std
{
	static PFX_FORCE_INLINE bool is_near_zero(float_t x)
	{
		return (((fabs(x)) < (1e-12)) ? 1 : 0);
	}

#define PFXMAT(__mat,row,col) __mat.m_mat[col].m_vec[row]
	
	//inverse(A) = 1 / det(A) * adj(A)
	static PFX_FORCE_INLINE MATRIX2F_t* inverse2x2(MATRIX2F_t& PFX_RESTRICT PARAM_OUT dst,
	MATRIX2F_t& PFX_RESTRICT src)
	{
		float_t det = matrix_det_unsafe_std_t::det2x2(src);
		if (is_near_zero(det))
		{
			// 不可逆
			return null;
		}

		det = 1.0f / det;
		PFXMAT(dst, 0, 0) =   det * PFXMAT(src, 1, 1);		
		PFXMAT(dst, 1, 0) = - det * PFXMAT(src, 0, 1);
		PFXMAT(dst, 0, 1) = - det * PFXMAT(src, 1, 0);
		PFXMAT(dst, 1, 1) =   det * PFXMAT(src, 0, 0);

		return &dst;

	}

	static PFX_FORCE_INLINE MATRIX3F_t* inverse3x3(MATRIX3F_t& PFX_RESTRICT PARAM_OUT dst,
		MATRIX3F_t& PFX_RESTRICT src)
	{
		float_t det = matrix_det_unsafe_std_t::det3x3(src);
		if (is_near_zero(det))
		{
			// 不可逆
			return null;
		}

		det = 1.0f / det;

		MAT2X2_DET(PFXMAT, PFXMAT(dst, 0, 0), src, 1, 2, 1, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 1, 0), src, 1, 2, 0, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 2, 0), src, 1, 2, 0, 1);

		MAT2X2_DET(PFXMAT, PFXMAT(dst, 0, 1), src, 0, 2, 1, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 1, 1), src, 0, 2, 0, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 2, 1), src, 0, 2, 0, 1);

		MAT2X2_DET(PFXMAT, PFXMAT(dst, 0, 2), src, 0, 1, 1, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 1, 2), src, 0, 1, 0, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 2, 2), src, 0, 1, 0, 1);

		PFXMAT(dst, 0, 0) *= det;
		PFXMAT(dst, 1, 0) *= -det;
		PFXMAT(dst, 2, 0) *= det;

		PFXMAT(dst, 0, 1) *= -det;
		PFXMAT(dst, 1, 1) *= det;
		PFXMAT(dst, 2, 1) *= -det;

		PFXMAT(dst, 0, 2) *= det;
		PFXMAT(dst, 1, 2) *= -det;
		PFXMAT(dst, 2, 2) *= det;


		return &dst;

	}

	static PFX_FORCE_INLINE MATRIX4F_t* inverse3x3_externAC01_col_major(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst,
		MATRIX4F_t& PFX_RESTRICT src)
	{
		// MAT = [ A , C]
		//       [ 0,  1]
		//使用分块求逆可得
		//inverse(MAT) = [ inverse(A)   ,     -inverse(A) C]
		//			     [             0,	              1]
		//


		float_t temp;
		float_t det;
		MAT3X3_DET(PFXMAT, det, temp, src, 0, 1, 2, 0, 1, 2);
		
		// MAT的充分必要条件是 A可逆，所以A不可逆MAT也不可逆
		if (is_near_zero(det))
		{
			// 不可逆
			return null;
		}
		// A 可逆 3* 3可逆阵公式 inverse(A) = 1/det(A) * adj(A)
		det = 1.0f / det;

		MAT2X2_DET(PFXMAT, PFXMAT(dst, 0, 0), src, 1, 2, 1, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 1, 0), src, 1, 2, 0, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 2, 0), src, 1, 2, 0, 1);

		MAT2X2_DET(PFXMAT, PFXMAT(dst, 0, 1), src, 0, 2, 1, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 1, 1), src, 0, 2, 0, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 2, 1), src, 0, 2, 0, 1);

		MAT2X2_DET(PFXMAT, PFXMAT(dst, 0, 2), src, 0, 1, 1, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 1, 2), src, 0, 1, 0, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 2, 2), src, 0, 1, 0, 1);

		PFXMAT(dst, 0, 0) *= det;
		PFXMAT(dst, 1, 0) *= -det;
		PFXMAT(dst, 2, 0) *= det;
		PFXMAT(dst, 3, 0)  = 0.0;

		PFXMAT(dst, 0, 1) *= -det;
		PFXMAT(dst, 1, 1) *=  det;
		PFXMAT(dst, 2, 1) *= -det;
		PFXMAT(dst, 3, 1)  = 0.0;

		PFXMAT(dst, 0, 2) *= det;
		PFXMAT(dst, 1, 2) *= -det;
		PFXMAT(dst, 2, 2) *= det;
		PFXMAT(dst, 3, 2)  = 0.0;

		//-inverse(A) C
		PFXMAT(dst, 0, 3) = -(PFXMAT(src, 0, 3) * PFXMAT(dst, 0, 0) +
			                  PFXMAT(src, 1, 3) * PFXMAT(dst, 0, 1) +
			                  PFXMAT(src, 2, 3) * PFXMAT(dst, 0, 2));
		PFXMAT(dst, 1, 3) = -(PFXMAT(src, 0, 3) * PFXMAT(dst, 1, 0) +
			                  PFXMAT(src, 1, 3) * PFXMAT(dst, 1, 1) +
			                  PFXMAT(src, 2, 3) * PFXMAT(dst, 1, 2));
		PFXMAT(dst, 2, 3) = -(PFXMAT(src, 0, 3) * PFXMAT(dst, 2, 0) +
			                  PFXMAT(src, 1, 3) * PFXMAT(dst, 2, 1) +
			                  PFXMAT(src, 2, 3) * PFXMAT(dst, 2, 2));

		//
		PFXMAT(dst, 3, 3) = 1.0;



		return &dst;

	}
	static 	PFX_FORCE_INLINE MATRIX4F_t* inverse3x3_externA0C1_col_major(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst,
		MATRIX4F_t& PFX_RESTRICT src)
	{
		// MAT = [ A , 0]
		//       [ C,  1]
		return inverse3x3_externAC01_row_major(dst, src);
	}
	static PFX_FORCE_INLINE MATRIX4F_t* inverse4x4(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst,
		MATRIX4F_t& PFX_RESTRICT src)
	{
		float_t temp;
		float_t det = matrix_det_unsafe_std_t::det4x4(src);
		if (is_near_zero(det))
		{
			// 不可逆
			return null;
		}

		det = 1.0f / det;

		MAT3X3_DET(PFXMAT, PFXMAT(dst, 0, 0), temp, src, 1, 2, 3, 1, 2, 3);
		MAT3X3_DET(PFXMAT, PFXMAT(dst, 1, 0), temp, src, 1, 2, 3, 0, 2, 3);
		MAT3X3_DET(PFXMAT, PFXMAT(dst, 2, 0), temp, src, 1, 2, 3, 0, 1, 3);
		MAT3X3_DET(PFXMAT, PFXMAT(dst, 3, 0), temp, src, 1, 2, 3, 0, 1, 2);

		MAT3X3_DET(PFXMAT, PFXMAT(dst, 0, 1), temp, src, 0, 2, 3, 1, 2, 3);
		MAT3X3_DET(PFXMAT, PFXMAT(dst, 1, 1), temp, src, 0, 2, 3, 0, 2, 3);
		MAT3X3_DET(PFXMAT, PFXMAT(dst, 2, 1), temp, src, 0, 2, 3, 0, 1, 3);
		MAT3X3_DET(PFXMAT, PFXMAT(dst, 3, 1), temp, src, 0, 2, 3, 0, 1, 2);

		MAT3X3_DET(PFXMAT, PFXMAT(dst, 0, 2), temp, src, 0, 1, 3, 1, 2, 3);
		MAT3X3_DET(PFXMAT, PFXMAT(dst, 1, 2), temp, src, 0, 1, 3, 0, 2, 3);
		MAT3X3_DET(PFXMAT, PFXMAT(dst, 2, 2), temp, src, 0, 1, 3, 0, 1, 3);
		MAT3X3_DET(PFXMAT, PFXMAT(dst, 3, 2), temp, src, 0, 1, 3, 0, 1, 2);

		MAT3X3_DET(PFXMAT, PFXMAT(dst, 0, 3), temp, src, 0, 1, 2, 1, 2, 3);
		MAT3X3_DET(PFXMAT, PFXMAT(dst, 1, 3), temp, src, 0, 1, 2, 0, 2, 3);
		MAT3X3_DET(PFXMAT, PFXMAT(dst, 2, 3), temp, src, 0, 1, 2, 0, 1, 3);
		MAT3X3_DET(PFXMAT, PFXMAT(dst, 3, 3), temp, src, 0, 1, 2, 0, 1, 2);

		PFXMAT(dst, 0, 0) *=  det;
		PFXMAT(dst, 1, 0) *= -det;
		PFXMAT(dst, 2, 0) *=  det;
		PFXMAT(dst, 3, 0) *= -det;

		PFXMAT(dst, 0, 1) *= -det;
		PFXMAT(dst, 1, 1) *=  det;
		PFXMAT(dst, 2, 1) *= -det;
		PFXMAT(dst, 3, 1) *=  det;

		PFXMAT(dst, 0, 2) *=  det;
		PFXMAT(dst, 1, 2) *= -det;
		PFXMAT(dst, 2, 2) *=  det;
		PFXMAT(dst, 3, 2) *= -det;

		PFXMAT(dst, 0, 3) *= -det;
		PFXMAT(dst, 1, 3) *=  det;
		PFXMAT(dst, 2, 3) *= -det;
		PFXMAT(dst, 3, 3) *=  det;


		return &dst;

	}

#undef PFXMAT

#define PFXMAT(__mat,row,col) __mat.m_mat[row].m_vec[col]
	static PFX_FORCE_INLINE MATRIX4F_t* inverse3x3_externAC01_row_major(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst,
		MATRIX4F_t& PFX_RESTRICT src)
	{
		// MAT = [ A , C]
		//       [ 0,  1]
		//使用分块求逆可得
		//inverse(MAT) = [ inverse(A)   ,     -inverse(A) C]
		//			     [             0,	              1]
		//

		float_t temp;
		float_t det;
		MAT3X3_DET(PFXMAT, det, temp, src, 0, 1, 2, 0, 1, 2);

		// MAT的充分必要条件是 A可逆，所以A不可逆MAT也不可逆
		if (is_near_zero(det))
		{
			// 不可逆
			return null;
		}
		// A 可逆 3* 3可逆阵公式 inverse(A) = 1/det(A) * adj(A)
		det = 1.0f / det;

		MAT2X2_DET(PFXMAT, PFXMAT(dst, 0, 0), src, 1, 2, 1, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 0, 1), src, 0, 2, 1, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 0, 2), src, 0, 1, 1, 2);

		MAT2X2_DET(PFXMAT, PFXMAT(dst, 1, 0), src, 1, 2, 0, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 1, 1), src, 0, 2, 0, 2);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 1, 2), src, 0, 1, 0, 2);

		MAT2X2_DET(PFXMAT, PFXMAT(dst, 2, 0), src, 1, 2, 0, 1);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 2, 1), src, 0, 2, 0, 1);
		MAT2X2_DET(PFXMAT, PFXMAT(dst, 2, 2), src, 0, 1, 0, 1);

		PFXMAT(dst, 0, 0) *= det;
		PFXMAT(dst, 0, 1) *= -det;
		PFXMAT(dst, 0, 2) *= det;

		PFXMAT(dst, 1, 0) *= -det;
		PFXMAT(dst, 1, 1) *= det;
		PFXMAT(dst, 1, 2) *= -det;

		PFXMAT(dst, 2, 0) *= det;
		PFXMAT(dst, 2, 1) *= -det;
		PFXMAT(dst, 2, 2) *= det;

		//-inverse(A) C
		PFXMAT(dst, 0, 3) = -(PFXMAT(src, 0, 3) * PFXMAT(dst, 0, 0) +
			                  PFXMAT(src, 1, 3) * PFXMAT(dst, 0, 1) +
			                  PFXMAT(src, 2, 3) * PFXMAT(dst, 0, 2));
		PFXMAT(dst, 1, 3) = -(PFXMAT(src, 0, 3) * PFXMAT(dst, 1, 0) +
			                  PFXMAT(src, 1, 3) * PFXMAT(dst, 1, 1) +
			                  PFXMAT(src, 2, 3) * PFXMAT(dst, 1, 2));
		PFXMAT(dst, 2, 3) = -(PFXMAT(src, 0, 3) * PFXMAT(dst, 2, 0) +
			                  PFXMAT(src, 1, 3) * PFXMAT(dst, 2, 1) +
			                  PFXMAT(src, 2, 3) * PFXMAT(dst, 2, 2));

		//
		PFXMAT(dst, 3, 0) = 0.0;
		PFXMAT(dst, 3, 1) = 0.0;
		PFXMAT(dst, 3, 2) = 0.0;
		PFXMAT(dst, 3, 3) = 1.0;


		return &dst;

	}

	static 	PFX_FORCE_INLINE MATRIX4F_t* inverse3x3_externA0C1_row_major(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst,
		MATRIX4F_t& PFX_RESTRICT src)
	{
		// MAT = [ A , 0]
		//       [ C,  1]
		return inverse3x3_externAC01_col_major(dst, src);
	}
#undef PFXMAT



}matrix_inv_unsafe_std_t;

PECKER_END

#endif			//PFX_SIMD_FMATINV_H_
