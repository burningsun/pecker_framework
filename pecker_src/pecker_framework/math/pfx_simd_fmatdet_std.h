/*
 * pfx_simd_fmatdet_std.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMATDET_H_
#define		PFX_SIMD_FMATDET_H_

#include "../pfx_defines.h"

#include "pfx_simd_param.h"
#include <math.h>
#include "pfx_simd_fadd_std.h"
#include "pfx_simd_fsub_std.h"
#include "pfx_simd_fmul_std.h"
#include "pfx_simd_fdiv_std.h"

PECKER_BEGIN

typedef struct st_matrix_det_unsafe_std
{
	//////////////////////////////////////////////////////////////////////////
	// 
#define PFXMAT(__mat,row,col) __mat.m_mat[col].m_vec[row]
#define PFXMAT_PTR(__mat,row,col) __mat[col][row]

// define出来的行列式的值得运算，只要是方便计算行列式的代数余子式的值
#define MAT2X2_DET(GetVAL,res,__mat,row1,row2,col1,col2)\
	res = (GetVAL(__mat, row1, col1) * GetVAL(__mat, row2, col2) - \
	GetVAL(__mat, row1, col2) * GetVAL(__mat, row2, col1));

#define MAT3X3_DET(GetVAL,res, tmp,__mat, row1, row2, row3, col1, col2, col3)\
	MAT2X2_DET(GetVAL, res, __mat, row2, row3, col2, col3); \
	res *= GetVAL(__mat, row1, col1); \
	MAT2X2_DET(GetVAL, tmp, __mat, row2, row3, col1, col3); \
	res -= tmp * GetVAL(__mat, row1, col2); \
	MAT2X2_DET(GetVAL, tmp, __mat, row2, row3, col1, col2); \
	res += tmp * GetVAL(__mat, row1, col3);

#define MAT4X4_DET(GetVAL,res, tmp1, tmp, __mat, row1, row2, row3, row4, col1, col2, col3, col4)\
	MAT3X3_DET(GetVAL, res, tmp1, __mat, row2, row3, row4, col2, col3, col4); \
	res *= GetVAL(__mat, row1, col1); \
	MAT3X3_DET(GetVAL, tmp, tmp1, __mat, row2, row3, row4, col1, col3, col4); \
	res -= tmp * GetVAL(__mat, row1, col2); \
	MAT3X3_DET(GetVAL, tmp, tmp1, __mat, row2, row3, row4, col1, col2, col4); \
	res += tmp * GetVAL(__mat, row1, col3); \
	MAT3X3_DET(GetVAL, tmp, tmp1, __mat, row2, row3, row4, col1, col2, col3); \
	res -= tmp * GetVAL(__mat, row1, col4);
					  
	static PFX_FORCE_INLINE float_t det2x2 (const MATRIX2F_t& __mat)
	{
		float_t res;
		MAT2X2_DET(PFXMAT,res, __mat, 0, 1, 0, 1);
		return res;
	}

	static PFX_FORCE_INLINE float_t det3x3(const MATRIX3F_t& __mat)
	{
		float_t res,tmp;
		MAT3X3_DET(PFXMAT,res, tmp, __mat, 0, 1, 2, 0, 1, 2);
		return res;
	}

	static PFX_FORCE_INLINE float_t det4x4(const MATRIX4F_t& __mat)
	{
		float_t res, tmp1, tmp2;
		MAT4X4_DET(PFXMAT,res, tmp1, tmp2, __mat, 0, 1, 2, 3, 0, 1, 2, 3);
		return res;
	}

	


#undef PFXMAT
#undef PFXMAT_PTR


}matrix_det_unsafe_std_t;



typedef float_t (*fmat_det2x2_func)(const MATRIX2F_t& __mat);
typedef float_t (*fmat_det3x3_func)(const MATRIX3F_t& __mat);
typedef float_t (*fmat_det4x4_func)(const MATRIX4F_t& __mat);


typedef struct st_simd_fmat_det_unsafe
{
	fmat_det2x2_func	fmat_det2x2;
	fmat_det3x3_func	fmat_det3x3;
	fmat_det4x4_func	fmat_det4x4;	
}simd_fmat_det_unsafe_t;


PFX_INLINE simd_fmat_det_unsafe_t*	init_simd_fmat_det_std(simd_fmat_det_unsafe_t& __fmat_det)
{
	__fmat_det.fmat_det2x2  = matrix_det_unsafe_std_t::det2x2;
	__fmat_det.fmat_det3x3  = matrix_det_unsafe_std_t::det3x3;
	__fmat_det.fmat_det4x4  = matrix_det_unsafe_std_t::det4x4;
	return &__fmat_det;
}

PECKER_END

#endif			//PFX_SIMD_FMATDET_H_
