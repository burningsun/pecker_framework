/*
 * pfx_simd_fmat_std.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMAT_H_
#define		PFX_SIMD_FMAT_H_

#include "../pfx_defines.h"

#include "pfx_simd_param.h"
#include <math.h>
#include "pfx_simd_fadd_std.h"
#include "pfx_simd_fsub_std.h"
#include "pfx_simd_fmul_std.h"
#include "pfx_simd_fdiv_std.h"

PECKER_BEGIN

// 矩阵相关
typedef struct st_matrix_operate_unsafe_std
{
	static PFX_FORCE_INLINE float_t* mul(float_t* PARAM_INOUT dst_ptr,
	    const float_t cst,
	    usize__t count)
	{
		return array_fmul_unsafe_std_t::operate(dst_ptr, cst, count);
	}
	static PFX_FORCE_INLINE VECTOR2F_t* mul(VECTOR2F_t* PARAM_INOUT dst_ptr,
		const float_t cst,
		usize__t count)
	{
		return array_fmul_unsafe_std_t::operate(dst_ptr, cst, count);
	}
	static PFX_FORCE_INLINE VECTOR3F_t* mul(VECTOR3F_t* PARAM_INOUT dst_ptr,
		const float_t cst,
		usize__t count)
	{
		return array_fmul_unsafe_std_t::operate(dst_ptr, cst, count);
	}
	static PFX_FORCE_INLINE VECTOR4F_t* mul(VECTOR4F_t* PARAM_INOUT dst_ptr,
		const float_t cst,
		usize__t count)
	{
		return array_fmul_unsafe_std_t::operate(dst_ptr, cst, count);
	}

	static PFX_FORCE_INLINE float_t one_dot(float_t* PFX_RESTRICT PARAM_INOUT vec_ptr,
		float_t* PFX_RESTRICT PARAM_INOUT vectrans_ptr,
		usize__t count)
	{
		SIMD_FLOAT(var) = 0.0;
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			var += (vec_ptr[itr] * vectrans_ptr[itr]);
		}
		return var;
	}

	static PFX_FORCE_INLINE float_t one_dot(VECTOR2F_t* PFX_RESTRICT PARAM_INOUT vec_ptr,
		VECTOR2F_t* PFX_RESTRICT PARAM_INOUT vectrans_ptr,
		usize__t count)
	{
		SIMD_VECTOR2F(temp_vec[2]) = { { 0.0, 0.0 }, { 0.0, 0.0 } };
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			array_fmul_unsafe_std_t::operate(&temp_vec[0], &vec_ptr[itr], &vectrans_ptr[itr], 1);
			array_fadd_unsafe_std_t::operate(&temp_vec[1], &temp_vec[0], 1);
		}

		return (temp_vec[1].m_vec[0] + temp_vec[1].m_vec[1]);
	}

	static PFX_FORCE_INLINE float_t one_dot(VECTOR3F_t* PFX_RESTRICT PARAM_INOUT vec_ptr,
		VECTOR3F_t* PFX_RESTRICT PARAM_INOUT vectrans_ptr,
		usize__t count)
	{
		SIMD_VECTOR3F(temp_vec[2]) = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 } };
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			array_fmul_unsafe_std_t::operate(&temp_vec[0], &vec_ptr[itr], &vectrans_ptr[itr], 1);
			array_fadd_unsafe_std_t::operate(&temp_vec[1], &temp_vec[0], 1);
		}

		return (temp_vec[1].m_vec[0] + temp_vec[1].m_vec[1] +
			temp_vec[1].m_vec[2]);
	}

	static PFX_FORCE_INLINE float_t one_dot(VECTOR4F_t* PFX_RESTRICT PARAM_INOUT vec_ptr,
		VECTOR4F_t* PFX_RESTRICT PARAM_INOUT vectrans_ptr,
		usize__t count)
	{
		SIMD_VECTOR4F(temp_vec[2]) = {{ 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0 }};
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			array_fmul_unsafe_std_t::operate(&temp_vec[0], &vec_ptr[itr], &vectrans_ptr[itr], 1);
			array_fadd_unsafe_std_t::operate(&temp_vec[1], &temp_vec[0], 1);
		}

		return (temp_vec[1].m_vec[0] + temp_vec[1].m_vec[1] + 
			temp_vec[1].m_vec[2] + temp_vec[1].m_vec[3]);
	}

	static PFX_FORCE_INLINE float_t one_dot_row_first(
		float_t* PFX_RESTRICT PARAM_INOUT vec_ptr,		
		float_t* PFX_RESTRICT PARAM_INOUT matrix_ptr,
		uindex_t col_index,
		usize__t row_dim_count,
		usize__t col_dim_count)
	{
		SIMD_FLOAT(var) = 0.0;

		usize__t offset = col_index;

		for (uindex_t ritr = row_dim_count; ritr != 0;)
		{
			--ritr;
			var += (vec_ptr[ritr] * matrix_ptr[offset]);
			offset += col_dim_count;
		}

		return var;
	}

	static PFX_FORCE_INLINE float_t one_dot_col_first(
		float_t* PFX_RESTRICT PARAM_INOUT matrix_ptr,
		float_t* PFX_RESTRICT PARAM_INOUT vec_ptr,
		uindex_t row_index,
		usize__t row_dim_count,
		usize__t col_dim_count)
	{
		SIMD_FLOAT(var) = 0.0;

		usize__t offset = row_index;

		for (uindex_t citr = col_dim_count; citr != 0;)
		{
			--citr;
			var += (vec_ptr[citr] * matrix_ptr[offset]);
			offset += row_dim_count;
		}

		return var;
	}

	static PFX_FORCE_INLINE float_t one_dot_row_first(
		float_t* PFX_RESTRICT PARAM_INOUT vec_ptr,
		float_t** PFX_RESTRICT PARAM_INOUT matrix_ptr,
		uindex_t col_index,
		usize__t row_dim_count)
	{
		SIMD_FLOAT(var) = 0.0;

		for (uindex_t ritr = row_dim_count; ritr != 0;)
		{
			--ritr;
			var += (vec_ptr[ritr] * matrix_ptr[ritr][col_index]);
		}

		return var;
	}

	static PFX_FORCE_INLINE float_t one_dot_col_first(
		float_t** PFX_RESTRICT PARAM_INOUT matrix_ptr,
		float_t* PFX_RESTRICT PARAM_INOUT  vec_ptr,
		uindex_t row_index,
		usize__t col_dim_count)
	{
		SIMD_FLOAT(var) = 0.0;

		for (uindex_t citr = col_dim_count; citr != 0;)
		{
			--citr;
			var += (vec_ptr[citr] * matrix_ptr[citr][row_index]);
		}

		return var;
	}

	//点乘
	
	//////////////////////////////////////////////////////////////////////////
	// 行优先
	static PFX_FORCE_INLINE float_t* vector_dot_matirx_row_first
		(float_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		float_t* PFX_RESTRICT PARAM_INOUT vec_ptr,
		float_t* PFX_RESTRICT PARAM_INOUT matrix_ptr,
		usize__t row_dim_count,
		usize__t col_dim_count)
	{
		for (uindex_t citr = col_dim_count; citr != 0;)
		{
			--citr;
			dst_ptr[citr] = one_dot_row_first(vec_ptr, matrix_ptr, 
				citr, row_dim_count, col_dim_count);
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t* vector_dot_matirx_row_first
		(float_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		float_t* PFX_RESTRICT PARAM_INOUT vec_ptr,
		float_t** PFX_RESTRICT PARAM_INOUT matrix_ptr,
		usize__t row_dim_count,
		usize__t col_dim_count)
	{
		for (uindex_t citr = col_dim_count; citr != 0;)
		{
			--citr;
			dst_ptr[citr] = one_dot_row_first(vec_ptr, matrix_ptr,
				citr, row_dim_count);
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t* dot_row_first(float_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		float_t* PFX_RESTRICT PARAM_INOUT mat1_ptr,
		float_t* PFX_RESTRICT PARAM_INOUT mat2_ptr,
		usize__t mat1_row_dim_count,
		usize__t mid_dim_count,
		usize__t mat2_col_dim_count)
	{
		uindex_t real_offset = 0;


		for (uindex_t ritr = mat1_row_dim_count; ritr != 0;)
		{
			--ritr;
			vector_dot_matirx_row_first(dst_ptr, mat1_ptr, mat2_ptr, 
				mid_dim_count, mat2_col_dim_count);

			mat1_ptr += mid_dim_count;
			dst_ptr  += mat2_col_dim_count;
		}

		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t** dot_row_first(float_t** PFX_RESTRICT PARAM_INOUT dst_ptr,
		float_t** PFX_RESTRICT PARAM_INOUT src1_ptr,
		float_t** PFX_RESTRICT PARAM_INOUT src2_ptr,
		usize__t src1_row_dim_count,
		usize__t mid_dim_count,
		usize__t src2_col_dim_count)
	{
		uindex_t real_offset = 0;


		for (uindex_t ritr = src1_row_dim_count; ritr != 0;)
		{
			--ritr;
			vector_dot_matirx_row_first(dst_ptr[ritr], src1_ptr[ritr], 
				src2_ptr, mid_dim_count, src2_col_dim_count);
		}

		return dst_ptr;
	}




	//////////////////////////////////////////////////////////////////////////
	// 列优先
	static PFX_FORCE_INLINE float_t* matirx_dot_vector_col_first
		(float_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		float_t* PFX_RESTRICT PARAM_INOUT matrix_ptr,
		usize__t row_dim_count,
		usize__t col_dim_count,
		float_t* PFX_RESTRICT PARAM_INOUT vec_ptr)
	{
		for (uindex_t ritr = row_dim_count; ritr != 0;)
		{
			--ritr;
			dst_ptr[ritr] = one_dot_col_first(matrix_ptr, vec_ptr,
				ritr, row_dim_count, col_dim_count );
		}

		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t* matirx_dot_vector_col_first
		(float_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		float_t** PFX_RESTRICT PARAM_INOUT matrix_ptr,
		usize__t row_dim_count,
		usize__t col_dim_count,
		float_t* PFX_RESTRICT PARAM_INOUT vec_ptr)
	{
		for (uindex_t ritr = row_dim_count; ritr != 0;)
		{
			--ritr;
			dst_ptr[ritr] = one_dot_col_first(matrix_ptr, vec_ptr, ritr, col_dim_count);
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t* dot_col_first(float_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		float_t* PFX_RESTRICT PARAM_INOUT src1_ptr,
		float_t* PFX_RESTRICT PARAM_INOUT src2_ptr,
		usize__t src1_col_dim_count,
		usize__t mid_dim_count,
		usize__t src2_row_dim_count)
	{
		uindex_t real_offset = 0;


		for (uindex_t citr = src1_col_dim_count; citr != 0;)
		{
			--citr;
			matirx_dot_vector_col_first(dst_ptr, src2_ptr, src2_row_dim_count, mid_dim_count, src1_ptr);

			src1_ptr += mid_dim_count;
			dst_ptr += src2_row_dim_count;
		}

		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t** dot_col_first(float_t** PFX_RESTRICT PARAM_INOUT dst_ptr,
		float_t** PFX_RESTRICT PARAM_INOUT src1_ptr,
		float_t** PFX_RESTRICT PARAM_INOUT src2_ptr,
		usize__t src1_col_dim_count,
		usize__t mid_dim_count,
		usize__t src2_row_dim_count)
	{
		uindex_t real_offset = 0;


		for (uindex_t citr = src1_col_dim_count; citr != 0;)
		{
			--citr;
			matirx_dot_vector_col_first(dst_ptr[citr], src2_ptr, 
				src2_row_dim_count, mid_dim_count, src1_ptr[citr]);
		}

		return dst_ptr;
	}

	//////////////////////////////////////////////////////////////////////////
	// 
	// 多个矩阵点乘队列
	// 2x2矩阵
	// M(行，列)
	//   M11, M12
	//   M21, M22

	// 3x3矩阵 
	// M(行，列)
	//   M11, M12, M13
	//   M21, M22, M23
	//   M31, M32, M33

	// 4x4矩阵
	//   M11, M12, M13, M14
	//   M21, M22, M23, M24
	//   M31, M32, M33, M34
	//   M41, M42, M43, M44


	// 行优先
#define M11_S1 src1.m_mat[0].m_vec[0]
#define M11_S2 src2.m_mat[0].m_vec[0]
#define M11_D   dst.m_mat[0].m_vec[0]
#define M12_S1 src1.m_mat[0].m_vec[1]
#define M12_S2 src2.m_mat[0].m_vec[1]
#define M12_D   dst.m_mat[0].m_vec[1]
#define M13_S1 src1.m_mat[0].m_vec[2]
#define M13_S2 src2.m_mat[0].m_vec[2]
#define M13_D   dst.m_mat[0].m_vec[2]
#define M14_S1 src1.m_mat[0].m_vec[3]
#define M14_S2 src2.m_mat[0].m_vec[3]
#define M14_D   dst.m_mat[0].m_vec[3]


#define M21_S1 src1.m_mat[1].m_vec[0]
#define M21_S2 src2.m_mat[1].m_vec[0]
#define M21_D   dst.m_mat[1].m_vec[0]
#define M22_S1 src1.m_mat[1].m_vec[1]
#define M22_S2 src2.m_mat[1].m_vec[1]
#define M22_D   dst.m_mat[1].m_vec[1]
#define M23_S1 src1.m_mat[1].m_vec[2]
#define M23_S2 src2.m_mat[1].m_vec[2]
#define M23_D   dst.m_mat[1].m_vec[2]
#define M24_S1 src1.m_mat[1].m_vec[3]
#define M24_S2 src2.m_mat[1].m_vec[3]
#define M24_D   dst.m_mat[1].m_vec[3]

#define M31_S1 src1.m_mat[2].m_vec[0]
#define M31_S2 src2.m_mat[2].m_vec[0]
#define M31_D   dst.m_mat[2].m_vec[0]
#define M32_S1 src1.m_mat[2].m_vec[1]
#define M32_S2 src2.m_mat[2].m_vec[1]
#define M32_D   dst.m_mat[2].m_vec[1]
#define M33_S1 src1.m_mat[2].m_vec[2]
#define M33_S2 src2.m_mat[2].m_vec[2]
#define M33_D   dst.m_mat[2].m_vec[2]
#define M34_S1 src1.m_mat[2].m_vec[3]
#define M34_S2 src2.m_mat[2].m_vec[3]
#define M34_D   dst.m_mat[2].m_vec[3]

#define M41_S1 src1.m_mat[3].m_vec[0]
#define M41_S2 src2.m_mat[3].m_vec[0]
#define M41_D   dst.m_mat[3].m_vec[0]
#define M42_S1 src1.m_mat[3].m_vec[1]
#define M42_S2 src2.m_mat[3].m_vec[1]
#define M42_D   dst.m_mat[3].m_vec[1]
#define M43_S1 src1.m_mat[3].m_vec[2]
#define M43_S2 src2.m_mat[3].m_vec[2]
#define M43_D   dst.m_mat[3].m_vec[2]
#define M44_S1 src1.m_mat[3].m_vec[3]
#define M44_S2 src2.m_mat[3].m_vec[3]
#define M44_D   dst.m_mat[3].m_vec[3]





	static PFX_FORCE_INLINE MATRIX2F_t* dot_row_first
		(MATRIX2F_t& PFX_RESTRICT PARAM_INOUT dst,
		MATRIX2F_t& PFX_RESTRICT PARAM_INOUT src1,
		MATRIX2F_t& PFX_RESTRICT PARAM_INOUT src2)
	{
		M11_D = (M11_S1 * M11_S2) + (M21_S1 * M12_S2);
		M12_D = (M12_S1 * M11_S2) + (M22_S1 * M12_S2);

		M21_D = (M11_S1 * M21_S2) + (M21_S1 * M22_S2);
		M22_D = (M12_S1 * M21_S2) + (M22_S1 * M22_S2);

		return 	&dst;
	}

	static PFX_FORCE_INLINE MATRIX3F_t* dot_row_first
		(MATRIX3F_t& PFX_RESTRICT PARAM_INOUT dst,
		MATRIX3F_t& PFX_RESTRICT PARAM_INOUT src1,
		MATRIX3F_t& PFX_RESTRICT PARAM_INOUT src2)
	{
		M11_D = (M11_S1 * M11_S2) + (M21_S1 * M12_S2) + (M31_S1 * M13_S2);
		M12_D = (M12_S1 * M11_S2) + (M22_S2 * M12_S2) + (M32_S1 * M13_S2);
		M13_D = (M13_S1 * M11_S2) + (M23_S2 * M12_S2) + (M33_S1 * M13_S2);

		M21_D = (M11_S1 * M21_S2) + (M21_S1 * M22_S2) + (M31_S1 * M23_S2);
		M22_D = (M12_S1 * M21_S2) + (M22_S2 * M22_S2) + (M32_S1 * M23_S2);
		M23_D = (M13_S1 * M21_S2) + (M23_S2 * M22_S2) + (M33_S1 * M23_S2);

		M31_D = (M11_S1 * M31_S2) + (M21_S1 * M32_S2) + (M31_S1 * M33_S2);
		M32_D = (M12_S1 * M31_S2) + (M22_S2 * M32_S2) + (M32_S1 * M33_S2);
		M33_D = (M13_S1 * M31_S2) + (M23_S2 * M32_S2) + (M33_S1 * M33_S2);
		return &dst;
	}

	static PFX_FORCE_INLINE MATRIX4F_t* dot_row_first
		(MATRIX4F_t& PFX_RESTRICT PARAM_INOUT dst,
		MATRIX4F_t& PFX_RESTRICT PARAM_INOUT src1,
		MATRIX4F_t& PFX_RESTRICT PARAM_INOUT src2)
	{
		M11_D = (M11_S1 * M11_S2) + (M21_S1 * M12_S2) + (M31_S1 * M13_S2) + (M41_S1 * M14_S2);
		M12_D = (M12_S1 * M11_S2) + (M22_S2 * M12_S2) + (M32_S1 * M13_S2) + (M42_S1 * M14_S2);
		M13_D = (M13_S1 * M11_S2) + (M23_S2 * M12_S2) + (M33_S1 * M13_S2) + (M43_S1 * M14_S2);
		M14_D = (M14_S1 * M11_S2) + (M24_S2 * M12_S2) + (M34_S1 * M13_S2) + (M44_S1 * M14_S2);

		M21_D = (M11_S1 * M21_S2) + (M21_S1 * M22_S2) + (M31_S1 * M23_S2) + (M41_S1 * M24_S2);
		M22_D = (M12_S1 * M21_S2) + (M22_S2 * M22_S2) + (M32_S1 * M23_S2) + (M42_S1 * M24_S2);
		M23_D = (M13_S1 * M21_S2) + (M23_S2 * M22_S2) + (M33_S1 * M23_S2) + (M43_S1 * M24_S2);
		M24_D = (M14_S1 * M21_S2) + (M24_S2 * M22_S2) + (M34_S1 * M23_S2) + (M44_S1 * M24_S2);

		M31_D = (M11_S1 * M31_S2) + (M21_S1 * M32_S2) + (M31_S1 * M33_S2) + (M41_S1 * M34_S2);
		M32_D = (M12_S1 * M31_S2) + (M22_S2 * M32_S2) + (M32_S1 * M33_S2) + (M42_S1 * M34_S2);
		M33_D = (M13_S1 * M31_S2) + (M23_S2 * M32_S2) + (M33_S1 * M33_S2) + (M43_S1 * M34_S2);
		M34_D = (M14_S1 * M31_S2) + (M24_S2 * M32_S2) + (M34_S1 * M33_S2) + (M44_S1 * M34_S2);

		M41_D = (M11_S1 * M41_S2) + (M21_S1 * M42_S2) + (M31_S1 * M43_S2) + (M41_S1 * M44_S2);
		M42_D = (M12_S1 * M41_S2) + (M22_S2 * M42_S2) + (M32_S1 * M43_S2) + (M42_S1 * M44_S2);
		M43_D = (M13_S1 * M41_S2) + (M23_S2 * M42_S2) + (M33_S1 * M43_S2) + (M43_S1 * M44_S2);
		M44_D = (M14_S1 * M41_S2) + (M24_S2 * M42_S2) + (M34_S1 * M43_S2) + (M44_S1 * M44_S2);

		return 	&dst;
	}

	static PFX_FORCE_INLINE MATRIX2F_t* dot_row_first
		(MATRIX2F_t& PFX_RESTRICT PARAM_INOUT dst,
		MATRIX2F_t& PFX_RESTRICT PARAM_INOUT src1)
	{
		return dot_row_first(dst, dst, src1);
	}

	static PFX_FORCE_INLINE MATRIX3F_t* dot_row_first
		(MATRIX3F_t& PFX_RESTRICT PARAM_INOUT dst,
		MATRIX3F_t& PFX_RESTRICT PARAM_INOUT src1)
	{
		M11_D = M11_S1;
		M12_D = M12_S1;
		M13_D = M13_S1;
		M21_D = M21_S1;
		M22_D = M22_S1;
		M23_D = M23_S1;
		M31_D = M31_S1;
		M32_D = M32_S1;
		M33_D = M33_S1;
		return dot_row_first(dst, dst, src1);
	}


	static PFX_FORCE_INLINE MATRIX4F_t* dot_row_first
		(MATRIX4F_t& PFX_RESTRICT PARAM_INOUT dst,
		MATRIX4F_t& PFX_RESTRICT PARAM_INOUT src1)
	{
		M11_D = M11_S1;
		M12_D = M12_S1;
		M13_D = M13_S1;
		M14_D = M14_S1;
		M21_D = M21_S1;
		M22_D = M22_S1;
		M23_D = M23_S1;
		M24_D = M24_S1;
		M31_D = M31_S1;
		M32_D = M32_S1;
		M33_D = M33_S1;
		M34_D = M34_S1;
		M41_D = M41_S1;
		M42_D = M42_S1;
		M43_D = M43_S1;
		M44_D = M44_S1;
		return dot_row_first(dst, dst, src1);
	}

	static PFX_FORCE_INLINE float_t det2x2_row_first(const MATRIX2F_t& dst)
	{
		return (M11_D * M22_D - M21_D * M12_D);
	}

	static PFX_FORCE_INLINE float_t det3x3_row_first(const MATRIX3F_t& dst)
	{
		MATRIX2F_t src1 = { M22_D, M32_D, 
			                M23_D, M33_D };

		MATRIX2F_t src2 = { M21_D, M31_D, 
			                M23_D, M33_D };

		MATRIX2F_t src3 = { M21_D, M31_D, 
			                M22_D, M32_D };

		return 
		   (M11_D * det2x2_row_first(src1) -
			M12_D * det2x2_row_first(src2) + 
			M13_D * det2x2_row_first(src3));
	}

	static  PFX_FORCE_INLINE float_t  det4x4_row_first(const MATRIX4F_t& dst)
	{
		MATRIX3F_t src1 = { M22_D, M32_D, M42_D, 
			                M23_D, M33_D, M43_D, 
							M24_D, M34_D, M44_D };

		MATRIX3F_t src2 = { M21_D, M31_D, M41_D, 
			                M23_D, M33_D, M43_D,
		                    M24_D, M34_D, M44_D };

		MATRIX3F_t src3 = { M21_D, M31_D, M41_D,
			                M22_D, M32_D, M42_D,
			                M24_D, M34_D, M44_D };

		MATRIX3F_t src4 = { M21_D, M31_D, M41_D,
			                M22_D, M32_D, M42_D,
			                M23_D, M33_D, M43_D };
		return
			(M11_D * det3x3_row_first(src1) -
			 M12_D * det3x3_row_first(src2) +
			 M13_D * det3x3_row_first(src3) -
			 M14_D * det3x3_row_first(src4));
	}


#undef M11_S1
#undef M11_S2
#undef M11_D
#undef M12_S1
#undef M12_S2
#undef M12_D
#undef M13_S1
#undef M13_S2
#undef M13_D
#undef M14_S1
#undef M14_S2
#undef M14_D

#undef M21_S1
#undef M21_S2
#undef M21_D
#undef M22_S1
#undef M22_S2
#undef M22_D
#undef M23_S1
#undef M23_S2
#undef M23_D
#undef M24_S1
#undef M24_S2
#undef M24_D

#undef M31_S1
#undef M31_S2
#undef M31_D
#undef M32_S1
#undef M32_S2
#undef M32_D
#undef M33_S1
#undef M33_S2
#undef M33_D
#undef M34_S1
#undef M34_S2
#undef M34_D

#undef M41_S1
#undef M41_S2
#undef M41_D
#undef M42_S1
#undef M42_S2
#undef M42_D
#undef M43_S1
#undef M43_S2
#undef M43_D
#undef M44_S1
#undef M44_S2
#undef M44_D



 //////////////////////////////////////////////////////////////////////////
	//列优先
#define M11_S1 src1.m_mat[0].m_vec[0]
#define M11_S2 src2.m_mat[0].m_vec[0]
#define M11_D  dst.m_mat[0].m_vec[0]
#define M12_S1 src1.m_mat[1].m_vec[0]
#define M12_S2 src2.m_mat[1].m_vec[0]
#define M12_D  dst.m_mat[1].m_vec[0]
#define M13_S1 src1.m_mat[2].m_vec[0]
#define M13_S2 src2.m_mat[2].m_vec[0]
#define M13_D  dst.m_mat[2].m_vec[0]
#define M14_S1 src1.m_mat[3].m_vec[0]
#define M14_S2 src2.m_mat[3].m_vec[0]
#define M14_D  dst.m_mat[3].m_vec[0]


#define M21_S1 src1.m_mat[0].m_vec[1]
#define M21_S2 src2.m_mat[0].m_vec[1]
#define M21_D  dst.m_mat[0].m_vec[1]
#define M22_S1 src1.m_mat[1].m_vec[1]
#define M22_S2 src2.m_mat[1].m_vec[1]
#define M22_D  dst.m_mat[1].m_vec[1]
#define M23_S1 src1.m_mat[2].m_vec[1]
#define M23_S2 src2.m_mat[2].m_vec[1]
#define M23_D  dst.m_mat[2].m_vec[1]
#define M24_S1 src1.m_mat[3].m_vec[1]
#define M24_S2 src2.m_mat[3].m_vec[1]
#define M24_D  dst.m_mat[3].m_vec[1]

#define M31_S1 src1.m_mat[0].m_vec[2]
#define M31_S2 src2.m_mat[0].m_vec[2]
#define M31_D  dst.m_mat[0].m_vec[2]
#define M32_S1 src1.m_mat[1].m_vec[2]
#define M32_S2 src2.m_mat[1].m_vec[2]
#define M32_D  dst.m_mat[1].m_vec[2]
#define M33_S1 src1.m_mat[2].m_vec[2]
#define M33_S2 src2.m_mat[2].m_vec[2]
#define M33_D  dst.m_mat[2].m_vec[2]
#define M34_S1 src1.m_mat[3].m_vec[2]
#define M34_S2 src2.m_mat[3].m_vec[2]
#define M34_D  dst.m_mat[3].m_vec[2]

#define M41_S1 src1.m_mat[0].m_vec[3]
#define M41_S2 src2.m_mat[0].m_vec[3]
#define M41_D  dst.m_mat[0].m_vec[3]
#define M42_S1 src1.m_mat[1].m_vec[3]
#define M42_S2 src2.m_mat[1].m_vec[3]
#define M42_D  dst.m_mat[1].m_vec[3]
#define M43_S1 src1.m_mat[2].m_vec[3]
#define M43_S2 src2.m_mat[2].m_vec[3]
#define M43_D  dst.m_mat[2].m_vec[3]
#define M44_S1 src1.m_mat[3].m_vec[3]
#define M44_S2 src2.m_mat[3].m_vec[3]
#define M44_D  dst.m_mat[3].m_vec[3]

static PFX_FORCE_INLINE MATRIX2F_t* dot_col_first
(MATRIX2F_t& PFX_RESTRICT PARAM_INOUT dst,
MATRIX2F_t& PFX_RESTRICT PARAM_INOUT src1,
MATRIX2F_t& PFX_RESTRICT PARAM_INOUT src2)
{
	M11_D = (M11_S1 * M11_S2) + (M21_S1 * M12_S2);
	M12_D = (M12_S1 * M11_S2) + (M22_S1 * M12_S2);

	M21_D = (M11_S1 * M21_S2) + (M21_S1 * M22_S2);
	M22_D = (M12_S1 * M21_S2) + (M22_S1 * M22_S2);

	return 	&dst;
}

static PFX_FORCE_INLINE MATRIX3F_t* dot_col_first
(MATRIX3F_t& PFX_RESTRICT PARAM_INOUT dst,
MATRIX3F_t& PFX_RESTRICT PARAM_INOUT src1,
MATRIX3F_t& PFX_RESTRICT PARAM_INOUT src2)
{
	M11_D = (M11_S1 * M11_S2) + (M21_S1 * M12_S2) + (M31_S1 * M13_S2);
	M12_D = (M12_S1 * M11_S2) + (M22_S2 * M12_S2) + (M32_S1 * M13_S2);
	M13_D = (M13_S1 * M11_S2) + (M23_S2 * M12_S2) + (M33_S1 * M13_S2);

	M21_D = (M11_S1 * M21_S2) + (M21_S1 * M22_S2) + (M31_S1 * M23_S2);
	M22_D = (M12_S1 * M21_S2) + (M22_S2 * M22_S2) + (M32_S1 * M23_S2);
	M23_D = (M13_S1 * M21_S2) + (M23_S2 * M22_S2) + (M33_S1 * M23_S2);

	M31_D = (M11_S1 * M31_S2) + (M21_S1 * M32_S2) + (M31_S1 * M33_S2);
	M32_D = (M12_S1 * M31_S2) + (M22_S2 * M32_S2) + (M32_S1 * M33_S2);
	M33_D = (M13_S1 * M31_S2) + (M23_S2 * M32_S2) + (M33_S1 * M33_S2);
	return &dst;
}

static PFX_FORCE_INLINE MATRIX4F_t* dot_col_first
(MATRIX4F_t& PFX_RESTRICT PARAM_INOUT dst,
MATRIX4F_t& PFX_RESTRICT PARAM_INOUT src1,
MATRIX4F_t& PFX_RESTRICT PARAM_INOUT src2)
{
	M11_D = (M11_S1 * M11_S2) + (M21_S1 * M12_S2) + (M31_S1 * M13_S2) + (M41_S1 * M14_S2);
	M12_D = (M12_S1 * M11_S2) + (M22_S2 * M12_S2) + (M32_S1 * M13_S2) + (M42_S1 * M14_S2);
	M13_D = (M13_S1 * M11_S2) + (M23_S2 * M12_S2) + (M33_S1 * M13_S2) + (M43_S1 * M14_S2);
	M14_D = (M14_S1 * M11_S2) + (M24_S2 * M12_S2) + (M34_S1 * M13_S2) + (M44_S1 * M14_S2);

	M21_D = (M11_S1 * M21_S2) + (M21_S1 * M22_S2) + (M31_S1 * M23_S2) + (M41_S1 * M24_S2);
	M22_D = (M12_S1 * M21_S2) + (M22_S2 * M22_S2) + (M32_S1 * M23_S2) + (M42_S1 * M24_S2);
	M23_D = (M13_S1 * M21_S2) + (M23_S2 * M22_S2) + (M33_S1 * M23_S2) + (M43_S1 * M24_S2);
	M24_D = (M14_S1 * M21_S2) + (M24_S2 * M22_S2) + (M34_S1 * M23_S2) + (M44_S1 * M24_S2);

	M31_D = (M11_S1 * M31_S2) + (M21_S1 * M32_S2) + (M31_S1 * M33_S2) + (M41_S1 * M34_S2);
	M32_D = (M12_S1 * M31_S2) + (M22_S2 * M32_S2) + (M32_S1 * M33_S2) + (M42_S1 * M34_S2);
	M33_D = (M13_S1 * M31_S2) + (M23_S2 * M32_S2) + (M33_S1 * M33_S2) + (M43_S1 * M34_S2);
	M34_D = (M14_S1 * M31_S2) + (M24_S2 * M32_S2) + (M34_S1 * M33_S2) + (M44_S1 * M34_S2);

	M41_D = (M11_S1 * M41_S2) + (M21_S1 * M42_S2) + (M31_S1 * M43_S2) + (M41_S1 * M44_S2);
	M42_D = (M12_S1 * M41_S2) + (M22_S2 * M42_S2) + (M32_S1 * M43_S2) + (M42_S1 * M44_S2);
	M43_D = (M13_S1 * M41_S2) + (M23_S2 * M42_S2) + (M33_S1 * M43_S2) + (M43_S1 * M44_S2);
	M44_D = (M14_S1 * M41_S2) + (M24_S2 * M42_S2) + (M34_S1 * M43_S2) + (M44_S1 * M44_S2);

	return 	&dst;
}

static PFX_FORCE_INLINE MATRIX2F_t* dot_col_first
(MATRIX2F_t& PFX_RESTRICT PARAM_INOUT dst,
MATRIX2F_t& PFX_RESTRICT PARAM_INOUT src1)
{
	return dot_col_first(dst, dst, src1);
}

static PFX_FORCE_INLINE MATRIX3F_t* dot_col_first
(MATRIX3F_t& PFX_RESTRICT PARAM_INOUT dst,
MATRIX3F_t& PFX_RESTRICT PARAM_INOUT src1)
{
	M11_D = M11_S1;
	M12_D = M12_S1;
	M13_D = M13_S1;
	M21_D = M21_S1;
	M22_D = M22_S1;
	M23_D = M23_S1;
	M31_D = M31_S1;
	M32_D = M32_S1;
	M33_D = M33_S1;
	return dot_col_first(dst, dst, src1);
}


static PFX_FORCE_INLINE MATRIX4F_t* dot_col_first
(MATRIX4F_t& PFX_RESTRICT PARAM_INOUT dst,
MATRIX4F_t& PFX_RESTRICT PARAM_INOUT src1)
{
	M11_D = M11_S1;
	M12_D = M12_S1;
	M13_D = M13_S1;
	M14_D = M14_S1;
	M21_D = M21_S1;
	M22_D = M22_S1;
	M23_D = M23_S1;
	M24_D = M24_S1;
	M31_D = M31_S1;
	M32_D = M32_S1;
	M33_D = M33_S1;
	M34_D = M34_S1;
	M41_D = M41_S1;
	M42_D = M42_S1;
	M43_D = M43_S1;
	M44_D = M44_S1;
	return dot_col_first(dst, dst, src1);
}

static PFX_FORCE_INLINE float_t det2x2_col_first(const MATRIX2F_t& dst)
{
	return (M11_D * M22_D - M21_D * M12_D);
}

static PFX_FORCE_INLINE float_t det3x3_col_first(const MATRIX3F_t& dst)
{
	MATRIX2F_t src1 = { M22_D, M32_D,
		M23_D, M33_D };

	MATRIX2F_t src2 = { M21_D, M31_D,
		M23_D, M33_D };

	MATRIX2F_t src3 = { M21_D, M31_D,
		M22_D, M32_D };

	return
		(M11_D * det2x2_col_first(src1) -
		M12_D * det2x2_col_first(src2) +
		M13_D * det2x2_col_first(src3));
}

static  PFX_FORCE_INLINE float_t  det4x4_col_first(const MATRIX4F_t& dst)
{
	MATRIX3F_t src1 = { M22_D, M32_D, M42_D,
		M23_D, M33_D, M43_D,
		M24_D, M34_D, M44_D };

	MATRIX3F_t src2 = { M21_D, M31_D, M41_D,
		M23_D, M33_D, M43_D,
		M24_D, M34_D, M44_D };

	MATRIX3F_t src3 = { M21_D, M31_D, M41_D,
		M22_D, M32_D, M42_D,
		M24_D, M34_D, M44_D };

	MATRIX3F_t src4 = { M21_D, M31_D, M41_D,
		M22_D, M32_D, M42_D,
		M23_D, M33_D, M43_D };
	return
		(M11_D * det3x3_col_first(src1) -
		M12_D * det3x3_col_first(src2) +
		M13_D * det3x3_col_first(src3) -
		M14_D * det3x3_col_first(src4));
}

#undef M11_S1
#undef M11_S2
#undef M11_D
#undef M12_S1
#undef M12_S2
#undef M12_D
#undef M13_S1
#undef M13_S2
#undef M13_D
#undef M14_S1
#undef M14_S2
#undef M14_D

#undef M21_S1
#undef M21_S2
#undef M21_D
#undef M22_S1
#undef M22_S2
#undef M22_D
#undef M23_S1
#undef M23_S2
#undef M23_D
#undef M24_S1
#undef M24_S2
#undef M24_D

#undef M31_S1
#undef M31_S2
#undef M31_D
#undef M32_S1
#undef M32_S2
#undef M32_D
#undef M33_S1
#undef M33_S2
#undef M33_D
#undef M34_S1
#undef M34_S2
#undef M34_D

#undef M41_S1
#undef M41_S2
#undef M41_D
#undef M42_S1
#undef M42_S2
#undef M42_D
#undef M43_S1
#undef M43_S2
#undef M43_D
#undef M44_S1
#undef M44_S2
#undef M44_D

//////////////////////////////////////////////////////////////////////////
// 叉乘
#define VEC_D_X    dst.m_vec[DIMENSION_X]
#define VEC_D_Y    dst.m_vec[DIMENSION_X]
#define VEC_D_Z    dst.m_vec[DIMENSION_X]
#define VEC_S1_X   src1.m_vec[DIMENSION_X]
#define VEC_S1_Y   src1.m_vec[DIMENSION_X]
#define VEC_S1_Z   src1.m_vec[DIMENSION_X]
#define VEC_S2_X   src2.m_vec[DIMENSION_X]
#define VEC_S2_Y   src2.m_vec[DIMENSION_X]
#define VEC_S2_Z   src2.m_vec[DIMENSION_X]

	PFX_FORCE_INLINE VECTOR3F_t* cross
		(VECTOR3F_t& PFX_RESTRICT PARAM_INOUT dst,
		VECTOR3F_t& PFX_RESTRICT PARAM_INOUT src1,
		VECTOR3F_t& PFX_RESTRICT PARAM_INOUT src2)
	{
		VEC_D_X = (VEC_S1_Y * VEC_S2_Z) - (VEC_S1_Z * VEC_S2_Y);
		VEC_D_Y = (VEC_S1_Z * VEC_S2_X) - (VEC_S1_X * VEC_S2_Z);
		VEC_D_Z = (VEC_S1_X * VEC_S2_Y) - (VEC_S1_Y * VEC_S2_X);
		return &dst;
	}

	PFX_FORCE_INLINE VECTOR4F_t* cross
		(VECTOR4F_t& PFX_RESTRICT PARAM_INOUT dst,
		VECTOR4F_t& PFX_RESTRICT PARAM_INOUT src1,
		VECTOR4F_t& PFX_RESTRICT PARAM_INOUT src2)
	{
		VEC_D_X = (VEC_S1_Y * VEC_S2_Z) - (VEC_S1_Z * VEC_S2_Y);
		VEC_D_Y = (VEC_S1_Z * VEC_S2_X) - (VEC_S1_X * VEC_S2_Z);
		VEC_D_Z = (VEC_S1_X * VEC_S2_Y) - (VEC_S1_Y * VEC_S2_X);
		dst.m_vec[DIMENSION_W] = 1.0;
		return &dst;
	}

#undef VEC_D_X 
#undef VEC_D_Y 
#undef VEC_D_Z 
#undef VEC_S1_X
#undef VEC_S1_Y
#undef VEC_S1_Z
#undef VEC_S2_X
#undef VEC_S2_Y
#undef VEC_S2_Z


}matrix_operate_unsafe_std_t;

PECKER_END

#endif			//PFX_SIMD_FMAT_H_
