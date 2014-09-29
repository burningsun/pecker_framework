﻿/*
 * pfx_simd_fmattrans_std.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMATTRANS_H_
#define		PFX_SIMD_FMATTRANS_H_

#include "../pfx_defines.h"

#include "pfx_simd_param.h"
#include <math.h>
#include "pfx_simd_fadd_std.h"
#include "pfx_simd_fsub_std.h"
#include "pfx_simd_fmul_std.h"
#include "pfx_simd_fdiv_std.h"


PECKER_BEGIN

typedef struct st_matrix_trans_unsafe_std
{


	static PFX_FORCE_INLINE const float_t* transpose(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const float_t* PFX_RESTRICT PARAM_IN src_ptr, usize__t dim_count)
	{
		usize__t dst_offset = 0;
		for (uindex_t citr = 0; citr < dim_count; ++citr)
		{
			uindex_t src_offset = citr;
			for (uindex_t ritr = 0; ritr < dim_count; ++ritr)
			{
				
				dst_ptr[dst_offset] = src_ptr[src_offset];
				src_offset += dim_count;
				++dst_offset;
			}
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE const float_t* const* transpose(float_t** PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t** PFX_RESTRICT PARAM_IN src_ptr, usize__t dim_count)
	{
		for (uindex_t citr = dim_count; citr != 0;)
		{
			--citr;
			for (uindex_t ritr = dim_count; ritr != 0;)
			{
				--ritr;
				dst_ptr[citr][ritr] = src_ptr[ritr][citr];
			}

		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE const float_t* transpose(float_t* PARAM_INOUT mat_ptr, usize__t dim_count)
	{
		usize__t dst_offset = 0;
		for (uindex_t citr = 0; citr < dim_count; ++citr)
		{
			uindex_t src_offset = citr;
			for (uindex_t ritr = 0; ritr < dim_count; ++ritr)
			{
				float_t tmp = mat_ptr[src_offset];
				mat_ptr[src_offset] = mat_ptr[dst_offset];
				mat_ptr[dst_offset] = tmp;
				src_offset += dim_count;
				++dst_offset;
			}
		}
		return mat_ptr;
	}

	static PFX_FORCE_INLINE const float_t* const* transpose(float_t** PARAM_INOUT mat_ptr, usize__t dim_count)
	{
		for (uindex_t citr = dim_count; citr != 0;)
		{
			--citr;
			for (uindex_t ritr = dim_count; ritr != 0;)
			{
				float_t tmp;
				--ritr;
				tmp = mat_ptr[ritr][citr];
				mat_ptr[ritr][citr] = mat_ptr[citr][ritr];
				mat_ptr[citr][ritr] = tmp;
			}

		}
		return mat_ptr;
	}

#define PFXMAT(__mat,row,col) __mat.m_mat[col].m_vec[row]
	static PFX_FORCE_INLINE const MATRIX2F_t* transpose(MATRIX2F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX2F_t& PFX_RESTRICT PARAM_IN src)
	{
		PFXMAT(dst, 0, 0) = PFXMAT(src, 0, 0);
		PFXMAT(dst, 0, 1) = PFXMAT(src, 1, 0);
		PFXMAT(dst, 1, 0) = PFXMAT(src, 0, 1);
		PFXMAT(dst, 1, 1) = PFXMAT(src, 1, 1);
		return &dst;
	}
	static PFX_FORCE_INLINE const MATRIX2F_t* transpose(MATRIX2F_t& PFX_RESTRICT PARAM_OUT dst)
	{
		float_t tmp;

		tmp = PFXMAT(dst, 1, 0);
		PFXMAT(dst, 1, 0) = PFXMAT(dst, 0, 1);
		PFXMAT(dst, 0, 1) = tmp;
		
		return &dst;
	}

	static PFX_FORCE_INLINE const MATRIX3F_t* transpose(MATRIX3F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX3F_t& PFX_RESTRICT PARAM_IN src)
	{
		PFXMAT(dst, 0, 0) = PFXMAT(src, 0, 0);
		PFXMAT(dst, 0, 1) = PFXMAT(src, 1, 0);
		PFXMAT(dst, 0, 2) = PFXMAT(src, 2, 0);
		PFXMAT(dst, 1, 0) = PFXMAT(src, 0, 1);
		PFXMAT(dst, 1, 1) = PFXMAT(src, 1, 1);
		PFXMAT(dst, 1, 2) = PFXMAT(src, 2, 1);
		PFXMAT(dst, 2, 0) = PFXMAT(src, 0, 2);
		PFXMAT(dst, 2, 1) = PFXMAT(src, 1, 2);
		PFXMAT(dst, 2, 2) = PFXMAT(src, 2, 2);
		return &dst;
	}

	static PFX_FORCE_INLINE const MATRIX3F_t* transpose(MATRIX3F_t& PFX_RESTRICT PARAM_OUT dst)
	{
		float_t tmp;

		tmp = PFXMAT(dst, 1, 0);
		PFXMAT(dst, 1, 0) = PFXMAT(dst, 0, 1);
		PFXMAT(dst, 0, 1) = tmp;

		tmp = PFXMAT(dst, 2, 0);
		PFXMAT(dst, 2, 0) = PFXMAT(dst, 0, 2);
		PFXMAT(dst, 0, 2) = tmp;

		tmp = PFXMAT(dst, 1, 2);
		PFXMAT(dst, 1, 2) = PFXMAT(dst, 2, 1);
		PFXMAT(dst, 2, 1) = tmp;

		return &dst;
	}

	static PFX_FORCE_INLINE const MATRIX4F_t* transpose(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX4F_t& PFX_RESTRICT PARAM_IN src)
	{
		PFXMAT(dst, 0, 0) = PFXMAT(src, 0, 0);
		PFXMAT(dst, 0, 1) = PFXMAT(src, 1, 0);
		PFXMAT(dst, 0, 2) = PFXMAT(src, 2, 0);
		PFXMAT(dst, 0, 3) = PFXMAT(src, 3, 0);

		PFXMAT(dst, 1, 0) = PFXMAT(src, 0, 1);
		PFXMAT(dst, 1, 1) = PFXMAT(src, 1, 1);
		PFXMAT(dst, 1, 2) = PFXMAT(src, 2, 1);
		PFXMAT(dst, 1, 3) = PFXMAT(src, 3, 1);

		PFXMAT(dst, 2, 0) = PFXMAT(src, 0, 2);
		PFXMAT(dst, 2, 1) = PFXMAT(src, 1, 2);
		PFXMAT(dst, 2, 2) = PFXMAT(src, 2, 2);
		PFXMAT(dst, 2, 3) = PFXMAT(src, 3, 2);

		PFXMAT(dst, 3, 0) = PFXMAT(src, 0, 3);
		PFXMAT(dst, 3, 1) = PFXMAT(src, 1, 3);
		PFXMAT(dst, 3, 2) = PFXMAT(src, 2, 3);
		PFXMAT(dst, 3, 3) = PFXMAT(src, 3, 3);

		return &dst;
	}

	static PFX_FORCE_INLINE const MATRIX4F_t* transpose(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst)
	{
		float_t tmp;

		tmp = PFXMAT(dst, 1, 0);
		PFXMAT(dst, 1, 0) = PFXMAT(dst, 0, 1);
		PFXMAT(dst, 0, 1) = tmp;

		tmp = PFXMAT(dst, 2, 0);
		PFXMAT(dst, 2, 0) = PFXMAT(dst, 0, 2);
		PFXMAT(dst, 0, 2) = tmp;

		tmp = PFXMAT(dst, 3, 0);
		PFXMAT(dst, 3, 0) = PFXMAT(dst, 0, 3);
		PFXMAT(dst, 0, 3) = tmp;

		tmp = PFXMAT(dst, 1, 2);
		PFXMAT(dst, 1, 2) = PFXMAT(dst, 2, 1);
		PFXMAT(dst, 2, 1) = tmp;

		tmp = PFXMAT(dst, 1, 3);
		PFXMAT(dst, 1, 3) = PFXMAT(dst, 3, 1);
		PFXMAT(dst, 3, 1) = tmp;

		tmp = PFXMAT(dst, 2, 3);
		PFXMAT(dst, 2, 3) = PFXMAT(dst, 3, 2);
		PFXMAT(dst, 3, 2) = tmp;

		return &dst;
	}

#undef 	PFXMAT

}matrix_trans_unsafe_std_t;

PECKER_END

#endif			//PFX_SIMD_FMATTRANS_H_