/*
 * pfx_simd_fmattrans_sse.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMATTRANS_SSE_H_
#define		PFX_SIMD_FMATTRANS_SSE_H_

#include "../pfx_simd_fmattrans_std.h"


PECKER_BEGIN

typedef struct st_matrix_trans_unsafe_sse
{

	static PFX_FORCE_INLINE const float_t* transpose(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const float_t* PFX_RESTRICT PARAM_IN src_ptr, usize__t dim_count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE const float_t* const* transpose(float_t** PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t** PFX_RESTRICT PARAM_IN src_ptr, usize__t dim_count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE const float_t* transpose(float_t* PARAM_INOUT mat_ptr, usize__t dim_count)
	{
		return mat_ptr;
	}

	static PFX_FORCE_INLINE const float_t* const* transpose(float_t** PARAM_INOUT mat_ptr, usize__t dim_count)
	{
		return mat_ptr;
	}

	static PFX_FORCE_INLINE const MATRIX2F_t* transpose(MATRIX2F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX2F_t& PFX_RESTRICT PARAM_IN src)
	{
		return &dst;
	}
	static PFX_FORCE_INLINE const MATRIX2F_t* transpose(MATRIX2F_t& PFX_RESTRICT PARAM_OUT dst)
	{
		return &dst;
	}

	static PFX_FORCE_INLINE const MATRIX3F_t* transpose(MATRIX3F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX3F_t& PFX_RESTRICT PARAM_IN src)
	{
		return &dst;
	}

	static PFX_FORCE_INLINE const MATRIX3F_t* transpose(MATRIX3F_t& PFX_RESTRICT PARAM_OUT dst)
	{
		return &dst;
	}

	static PFX_FORCE_INLINE const MATRIX4F_t* transpose(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX4F_t& PFX_RESTRICT PARAM_IN src)
	{
		return &dst;
	}

	static PFX_FORCE_INLINE const MATRIX4F_t* transpose(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst)
	{
		return &dst;
	}


}matrix_trans_unsafe_sse_t;


PFX_INLINE simd_fmat_transpose_unsafe_t*	init_simd_fmat_trans_sse(simd_fmat_transpose_unsafe_t& __fmat)
{
	__fmat.fmat_transpose              = matrix_trans_unsafe_std_t::transpose;
	__fmat.fmat_vec_transpose          = matrix_trans_unsafe_std_t::transpose;
	__fmat.fmat_transpose_replace      = matrix_trans_unsafe_std_t::transpose;
	__fmat.fmat_vec_transpose_replace  = matrix_trans_unsafe_std_t::transpose;
	__fmat.fmat2_transpose             = matrix_trans_unsafe_std_t::transpose;
	__fmat.fmat2_transpose_replace     = matrix_trans_unsafe_std_t::transpose;
	__fmat.fmat3_transpose             = matrix_trans_unsafe_std_t::transpose;
	__fmat.fmat3_transpose_replace     = matrix_trans_unsafe_std_t::transpose;
	__fmat.fmat4_transpose             = matrix_trans_unsafe_std_t::transpose;
	__fmat.fmat4_transpose_replace     = matrix_trans_unsafe_std_t::transpose;
	return &__fmat;
}

PECKER_END

#endif			//PFX_SIMD_FMATTRANS_H_
