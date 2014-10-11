/*
 * pfx_simd_fmatdot_sse.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMATDOT_SSE_H_
#define		PFX_SIMD_FMATDOT_SSE_H_

#include "../pfx_simd_fmatdot_std.h"
#include "pfx_simd_fmatset_sse.h"
#include "pfx_simd_fmul_sse.h"


PECKER_BEGIN


typedef struct st_matrix_dot_unsafe_sse
{

	static PFX_FORCE_INLINE void mat2x2_mul_const(__m128& PARAM_OUT mat_tag, __m128 PARAM_IN mat, float_t val)
	{
		__m128 _val = _mm_set_ps1(val);
		mat_tag = _mm_mul_ps(mat, _val);
	}

	//static PFX_FORCE_INLINE __m128 mat2x2_mul_mat2x1_0101(__m128 PARAM_IN mat_a, __m128 PARAM_IN vec)
	//{
	//	__m128 r1 = _mm_mul_ps(mat_a, vec);
	//	__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2,0,2,0));
	//	r1 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(3, 1, 3, 1));
	//	return _mm_add_ps(r1, r2);
	//}

	//static PFX_FORCE_INLINE __m128 mat1x2_0101_mul_mat2x2(__m128 PARAM_IN vec, __m128 PARAM_IN mat_b)
	//{
	//	__m128 r1 = _mm_shuffle_ps(mat_b, mat_b, _MM_SHUFFLE(3, 1, 2, 0));
	//	return mat2x2_mul_mat2x1_0101(mat_b, vec);
	//}

	//static PFX_FORCE_INLINE __m128 mat1x2_mul_mat2x1(__m128 PARAM_IN vec, __m128 PARAM_IN mat_b)
	//{
	//	__m128 r1 = _mm_shuffle_ps(mat_b, mat_b, _MM_SHUFFLE(3, 1, 2, 0));
	//	return mat2x2_mul_mat2x1_0101(mat_b, vec);
	//}

	//static PFX_FORCE_INLINE __m128 mat2x2_mul_mat2x1_0011(__m128 PARAM_IN mat_a, __m128 PARAM_IN vec)
	//{
	//	__m128 r1 = _mm_shuffle_ps(mat_a, mat_a, _MM_SHUFFLE(3, 1, 2, 0));
	//	__m128 r2 = _mm_mul_ps(vec, r1);
	//	r1 = _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(1,0,3,2));
	//	return _mm_add_ps(r1, r2);
	//}

	//static PFX_FORCE_INLINE __m128 mat1x2_0011_mul_mat2x2(__m128 PARAM_IN vec, __m128 PARAM_IN mat_b)
	//{
	//	__m128 r1 = _mm_mul_ps(vec, mat_b);
	//	__m128 r2 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 0, 3, 2));
	//	return _mm_add_ps(r1, r2);
	//}


	static PFX_FORCE_INLINE __m128 mat2x2_mul(__m128 PARAM_IN mat_a, __m128 PARAM_IN mat_b)
	{
		__m128 r1 = _mm_shuffle_ps(mat_b, mat_b, _MM_SHUFFLE(1, 0, 1, 0));
		__m128 r2 = _mm_shuffle_ps(mat_a, mat_a, _MM_SHUFFLE(2, 2, 0, 0));
		r1 = _mm_mul_ps(r1, r2);
		__m128 r3 = _mm_shuffle_ps(mat_b, mat_b, _MM_SHUFFLE(3, 2, 3, 2));
		r2 = _mm_shuffle_ps(mat_a, mat_a, _MM_SHUFFLE(3, 3, 1, 1));
		r2 = _mm_mul_ps(r2, r3);
		return _mm_add_ps(r1, r2);
	}

	static PFX_FORCE_INLINE void mat3x3_mul_const(__m128 PARAM_INOUT mat_tag[3], __m128 PARAM_IN mat[3], float_t val)
	{
		__m128 _val = _mm_set_ps1(val);
		mat_tag[0] = _mm_mul_ps(mat[0], _val);
		mat_tag[1] = _mm_mul_ps(mat[1], _val);
		mat_tag[2] = _mm_mul_ps(mat[2], _val);
	}

	static PFX_FORCE_INLINE void mat3x3_mul(__m128 PARAM_OUT mat_tag[3], __m128 PARAM_IN mat_a[4], __m128 PARAM_IN mat_b[4])
	{
		// 注：按行主元看代码
		__m128 aaaa;
		__m128 bbbb;

		// 	第1行
		aaaa = _mm_shuffle_ps(mat_a[0], mat_a[0], _MM_SHUFFLE(0, 0, 0, 0));
		bbbb = _mm_mul_ps(aaaa, mat_b[0]);
		aaaa = _mm_shuffle_ps(mat_a[0], mat_a[0], _MM_SHUFFLE(1, 1, 1, 1));
		aaaa = _mm_mul_ps(aaaa, mat_b[1]);
		bbbb = _mm_add_ps(aaaa, bbbb);
		aaaa = _mm_shuffle_ps(mat_a[0], mat_a[0], _MM_SHUFFLE(2, 2, 2, 2));
		aaaa = _mm_mul_ps(aaaa, mat_b[2]);
		mat_tag[0] = _mm_add_ps(aaaa, bbbb);

		// 	第2行
		aaaa = _mm_shuffle_ps(mat_a[1], mat_a[1], _MM_SHUFFLE(0, 0, 0, 0));
		bbbb = _mm_mul_ps(aaaa, mat_b[0]);
		aaaa = _mm_shuffle_ps(mat_a[1], mat_a[1], _MM_SHUFFLE(1, 1, 1, 1));
		aaaa = _mm_mul_ps(aaaa, mat_b[1]);
		bbbb = _mm_add_ps(aaaa, bbbb);
		aaaa = _mm_shuffle_ps(mat_a[1], mat_a[1], _MM_SHUFFLE(2, 2, 2, 2));
		aaaa = _mm_mul_ps(aaaa, mat_b[2]);
		mat_tag[1] = _mm_add_ps(aaaa, bbbb);

		// 	第3行
		aaaa = _mm_shuffle_ps(mat_a[2], mat_a[2], _MM_SHUFFLE(0, 0, 0, 0));
		bbbb = _mm_mul_ps(aaaa, mat_b[0]);
		aaaa = _mm_shuffle_ps(mat_a[2], mat_a[2], _MM_SHUFFLE(1, 1, 1, 1));
		aaaa = _mm_mul_ps(aaaa, mat_b[1]);
		bbbb = _mm_add_ps(aaaa, bbbb);
		aaaa = _mm_shuffle_ps(mat_a[2], mat_a[2], _MM_SHUFFLE(2, 2, 2, 2));
		aaaa = _mm_mul_ps(aaaa, mat_b[2]);
		mat_tag[2] = _mm_add_ps(aaaa, bbbb);
		
	}

	static PFX_FORCE_INLINE void mat4x4_mul_const(__m128 PARAM_OUT mat_tag[4], __m128 PARAM_INOUT mat[4], float_t val)
	{
		__m128 _val = _mm_set_ps1(val);
		mat_tag[0] = _mm_mul_ps(mat[0], _val);
		mat_tag[1] = _mm_mul_ps(mat[1], _val);
		mat_tag[2] = _mm_mul_ps(mat[2], _val);
		mat_tag[3] = _mm_mul_ps(mat[3], _val);
	}

	static PFX_FORCE_INLINE void mat4x4_mul(__m128 PARAM_OUT mat_tag[4], __m128 PARAM_INOUT mat[4], float_t val)
	{
		__m128 _val = _mm_set_ps1(val);
		mat_tag[0] = _mm_mul_ps(mat[0], _val);
		mat_tag[1] = _mm_mul_ps(mat[1], _val);
		mat_tag[2] = _mm_mul_ps(mat[2], _val);
		mat_tag[3] = _mm_mul_ps(mat[3], _val);
	}

	static PFX_FORCE_INLINE void mat4x4_mul(__m128 PARAM_OUT mat_tag[4], 
		__m128 PARAM_INOUT mat_a[4], 
		__m128 PARAM_INOUT mat_b[4])
	{
		// 注：按行主元看代码
		__m128 aaaa;
		__m128 bbbb;
	
		// 	第1行
		aaaa = _mm_shuffle_ps(mat_a[0], mat_a[0], _MM_SHUFFLE(0, 0, 0, 0));
		bbbb = _mm_mul_ps(aaaa, mat_b[0]);
		aaaa = _mm_shuffle_ps(mat_a[0], mat_a[0], _MM_SHUFFLE(1, 1, 1, 1));
		aaaa = _mm_mul_ps(aaaa, mat_b[1]);
		bbbb = _mm_add_ps(aaaa, bbbb);
		aaaa = _mm_shuffle_ps(mat_a[0], mat_a[0], _MM_SHUFFLE(2, 2, 2, 2));
		aaaa = _mm_mul_ps(aaaa, mat_b[2]);
		bbbb = _mm_add_ps(aaaa, bbbb);
		aaaa = _mm_shuffle_ps(mat_a[0], mat_a[0], _MM_SHUFFLE(3, 3, 3, 3));
		aaaa = _mm_mul_ps(aaaa, mat_b[3]);
		mat_tag[0] = _mm_add_ps(aaaa, bbbb);

		// 	第2行
		aaaa = _mm_shuffle_ps(mat_a[1], mat_a[1], _MM_SHUFFLE(0, 0, 0, 0));
		bbbb = _mm_mul_ps(aaaa, mat_b[0]);
		aaaa = _mm_shuffle_ps(mat_a[1], mat_a[1], _MM_SHUFFLE(1, 1, 1, 1));
		aaaa = _mm_mul_ps(aaaa, mat_b[1]);
		bbbb = _mm_add_ps(aaaa, bbbb);
		aaaa = _mm_shuffle_ps(mat_a[1], mat_a[1], _MM_SHUFFLE(2, 2, 2, 2));
		aaaa = _mm_mul_ps(aaaa, mat_b[2]);
		bbbb = _mm_add_ps(aaaa, bbbb);
		aaaa = _mm_shuffle_ps(mat_a[1], mat_a[1], _MM_SHUFFLE(3, 3, 3, 3));
		aaaa = _mm_mul_ps(aaaa, mat_b[3]);
		mat_tag[1] = _mm_add_ps(aaaa, bbbb);

		// 	第3行
		aaaa = _mm_shuffle_ps(mat_a[2], mat_a[2], _MM_SHUFFLE(0, 0, 0, 0));
		bbbb = _mm_mul_ps(aaaa, mat_b[0]);
		aaaa = _mm_shuffle_ps(mat_a[2], mat_a[2], _MM_SHUFFLE(1, 1, 1, 1));
		aaaa = _mm_mul_ps(aaaa, mat_b[1]);
		bbbb = _mm_add_ps(aaaa, bbbb);
		aaaa = _mm_shuffle_ps(mat_a[2], mat_a[2], _MM_SHUFFLE(2, 2, 2, 2));
		aaaa = _mm_mul_ps(aaaa, mat_b[2]);
		bbbb = _mm_add_ps(aaaa, bbbb);
		aaaa = _mm_shuffle_ps(mat_a[2], mat_a[2], _MM_SHUFFLE(3, 3, 3, 3));
		aaaa = _mm_mul_ps(aaaa, mat_b[3]);
		mat_tag[2] = _mm_add_ps(aaaa, bbbb);

		// 	第4行
		aaaa = _mm_shuffle_ps(mat_a[3], mat_a[3], _MM_SHUFFLE(0, 0, 0, 0));
		bbbb = _mm_mul_ps(aaaa, mat_b[0]);
		aaaa = _mm_shuffle_ps(mat_a[3], mat_a[3], _MM_SHUFFLE(1, 1, 1, 1));
		aaaa = _mm_mul_ps(aaaa, mat_b[1]);
		bbbb = _mm_add_ps(aaaa, bbbb);
		aaaa = _mm_shuffle_ps(mat_a[3], mat_a[3], _MM_SHUFFLE(2, 2, 2, 2));
		aaaa = _mm_mul_ps(aaaa, mat_b[2]);
		bbbb = _mm_add_ps(aaaa, bbbb);
		aaaa = _mm_shuffle_ps(mat_a[3], mat_a[3], _MM_SHUFFLE(3, 3, 3, 3));
		aaaa = _mm_mul_ps(aaaa, mat_b[3]);
		mat_tag[3] = _mm_add_ps(aaaa, bbbb);

	}















	static PFX_FORCE_INLINE float_t* mul (float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	                                     const float_t* PFX_RESTRICT PARAM_IN mat1_ptr,
	                                     const float_t* PFX_RESTRICT PARAM_IN mat2_ptr,
	                                     usize__t mat1_row_dim_count,
	                                     usize__t mid_dim_count,
	                                     usize__t mat2_col_dim_count,
										 bool brow_major = false)
	{
		if (brow_major)
		{
			return mul_row_major(dst_ptr, mat1_ptr, mat2_ptr, 
				mat1_row_dim_count, mid_dim_count, mat2_col_dim_count);
		}
		else
		{
			return mul_col_major(dst_ptr, mat1_ptr, mat2_ptr,
				mat1_row_dim_count, mid_dim_count, mat2_col_dim_count);
		}
	}

	static PFX_FORCE_INLINE float_t** mul(float_t** PFX_RESTRICT PARAM_OUT dst_ptr,
										  const float_t* const* PFX_RESTRICT PARAM_IN mat1_ptr,
										  const float_t* const* PFX_RESTRICT PARAM_IN mat2_ptr,
		                                  usize__t mat1_row_dim_count,
		                                  usize__t mid_dim_count,
		                                  usize__t mat2_col_dim_count,
										  bool brow_major = false)
	{
		if (brow_major)
		{
			return mul_row_major(dst_ptr, mat1_ptr, mat2_ptr,
				mat1_row_dim_count, mid_dim_count, mat2_col_dim_count);
		}
		else
		{
			return mul_col_major(dst_ptr, mat1_ptr, mat2_ptr,
				mat1_row_dim_count, mid_dim_count, mat2_col_dim_count);
		}
	}

	static PFX_FORCE_INLINE float_t* mul(float_t* PARAM_INOUT dst_ptr,
	    float_t cst,
	    usize__t count)
	{
		return array_fmul_unsafe_sse_t::operate(dst_ptr, cst, count);
	}
	static PFX_FORCE_INLINE VECTOR2F_t* mul(VECTOR2F_t* PARAM_INOUT dst_ptr,
		float_t cst,
		usize__t count)
	{
		return array_fmul_unsafe_sse_t::operate(dst_ptr, cst, count);
	}
	static PFX_FORCE_INLINE VECTOR3F_t* mul(VECTOR3F_t* PARAM_INOUT dst_ptr,
		float_t cst,
		usize__t count)
	{
		return array_fmul_unsafe_sse_t::operate(dst_ptr, cst, count);
	}
	static PFX_FORCE_INLINE VECTOR4F_t* mul(VECTOR4F_t* PARAM_INOUT dst_ptr,
		float_t cst,
		usize__t count)
	{
		return array_fmul_unsafe_sse_t::operate(dst_ptr, cst, count);
	}

	static PFX_FORCE_INLINE float_t dot(const VECTOR4F_t& PARAM_IN vec1,
		const VECTOR4F_t& PARAM_IN vec2)
	{
		float_t res;
		return res;
	}
	static PFX_FORCE_INLINE float_t dot(const VECTOR2F_t& PARAM_IN vec1,
		const VECTOR2F_t& PARAM_IN vec2)
	{
		float_t res;
		return res;
	}
	static PFX_FORCE_INLINE float_t dot(const VECTOR3F_t& PARAM_IN vec1,
		const VECTOR3F_t& PARAM_IN vec2)
	{
		float_t res;
		return res;
	}

	static PFX_FORCE_INLINE float_t dot(const float_t* PFX_RESTRICT PARAM_IN vec_ptr,
		const float_t* PFX_RESTRICT PARAM_IN vectrans_ptr,
		usize__t count)
	{
		SIMD_FLOAT(var) = 0.0;
		return var;
	}



	static PFX_FORCE_INLINE float_t one_dot_row_major(
		const float_t* PFX_RESTRICT PARAM_IN vec_ptr,		
		const float_t* PFX_RESTRICT PARAM_IN matrix_ptr,
		uindex_t col_index,
		usize__t row_dim_count,
		usize__t col_dim_count)
	{
		SIMD_FLOAT(var) = 0.0;

		return var;
	}

	static PFX_FORCE_INLINE float_t one_dot_col_major(
		const float_t* PFX_RESTRICT PARAM_IN matrix_ptr,
		const float_t* PFX_RESTRICT PARAM_IN vec_ptr,
		uindex_t row_index,
		usize__t row_dim_count,
		usize__t col_dim_count)
	{
		SIMD_FLOAT(var) = 0.0;


		return var;
	}

	static PFX_FORCE_INLINE float_t one_dot_row_major(
		const float_t* PFX_RESTRICT PARAM_IN vec_ptr,
		const float_t* const * PFX_RESTRICT PARAM_IN matrix_ptr,
		uindex_t col_index,
		usize__t row_dim_count)
	{
		SIMD_FLOAT(var) = 0.0;


		return var;
	}

	static PFX_FORCE_INLINE float_t one_dot_col_major(
		const float_t* const* PFX_RESTRICT PARAM_IN matrix_ptr,
		const float_t* PFX_RESTRICT PARAM_IN  vec_ptr,
		uindex_t row_index,
		usize__t col_dim_count)
	{
		SIMD_FLOAT(var) = 0.0;


		return var;
	}


	
	//////////////////////////////////////////////////////////////////////////
	// 行优先
	static PFX_FORCE_INLINE float_t* vector_mul_matirx_row_major
		(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN vec_ptr,
		const float_t* PFX_RESTRICT PARAM_IN matrix_ptr,
		usize__t row_dim_count,
		usize__t col_dim_count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t* vector_mul_matirx_row_major
		(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN vec_ptr,
		const float_t* const* PFX_RESTRICT PARAM_IN matrix_ptr,
		usize__t row_dim_count,
		usize__t col_dim_count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t* mul_row_major(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN mat1_ptr,
		const float_t* PFX_RESTRICT PARAM_IN mat2_ptr,
		usize__t mat1_row_dim_count,
		usize__t mid_dim_count,
		usize__t mat2_col_dim_count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t** mul_row_major(float_t** PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t* const * PFX_RESTRICT PARAM_IN src1_ptr,
		const float_t* const * PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t src1_row_dim_count,
		usize__t mid_dim_count,
		usize__t src2_col_dim_count)
	{

		return dst_ptr;
	}




	//////////////////////////////////////////////////////////////////////////
	// 列优先
	static PFX_FORCE_INLINE float_t* matirx_mul_vector_col_major
		(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN matrix_ptr,
		usize__t row_dim_count,
		usize__t col_dim_count,
		const float_t* PFX_RESTRICT PARAM_IN vec_ptr)
	{

		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t* matirx_mul_vector_col_major
		(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t* const * PFX_RESTRICT PARAM_IN matrix_ptr,
		usize__t row_dim_count,
		usize__t col_dim_count,
		const float_t* PFX_RESTRICT PARAM_IN vec_ptr)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t* mul_col_major(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t src1_col_dim_count,
		usize__t mid_dim_count,
		usize__t src2_row_dim_count)
	{

		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t** mul_col_major(float_t** PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t* const * PFX_RESTRICT PARAM_IN src1_ptr,
		const float_t* const * PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t src1_col_dim_count,
		usize__t mid_dim_count,
		usize__t src2_row_dim_count)
	{
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX2F_t* mul
	(MATRIX2F_t& PFX_RESTRICT PARAM_OUT dst,
	const MATRIX2F_t& PFX_RESTRICT PARAM_IN src1,
	const MATRIX2F_t& PFX_RESTRICT PARAM_IN src2)
	{
		__m128 mat,_mat;
		matrix_set_unsafe_sse_t::mat2x2_load(src1, mat);
		matrix_set_unsafe_sse_t::mat2x2_load(src2, _mat);
		mat = mat2x2_mul(mat, _mat);
		matrix_set_unsafe_sse_t::mat2x2_store(dst, mat);
		return 	&dst;
	}

	static PFX_FORCE_INLINE MATRIX3F_t* mul
	(MATRIX3F_t& PFX_RESTRICT PARAM_OUT dst,
	const MATRIX3F_t& PFX_RESTRICT PARAM_IN src1,
	const MATRIX3F_t& PFX_RESTRICT PARAM_IN src2)
	{
		__m128 mat[3], _mat[3];
		matrix_set_unsafe_sse_t::mat3x3_load(src1, mat);
		matrix_set_unsafe_sse_t::mat3x3_load(src2, _mat);
		mat3x3_mul(mat, mat, _mat);
		matrix_set_unsafe_sse_t::mat3x3_store(dst, mat);
		return 	&dst;
	}

	static PFX_FORCE_INLINE MATRIX4F_t* mul
	(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst,
	const MATRIX4F_t& PFX_RESTRICT PARAM_IN src1,
	const MATRIX4F_t& PFX_RESTRICT PARAM_IN src2)
	{

		__m128 mat[4], _mat[4];
		matrix_set_unsafe_sse_t::mat4x4_load(src1, mat);
		matrix_set_unsafe_sse_t::mat4x4_load(src2, _mat);
		mat4x4_mul(mat, mat, _mat);
		matrix_set_unsafe_sse_t::mat4x4_store(dst, mat);
		return 	&dst;
	}



	static PFX_FORCE_INLINE MATRIX2F_t* mul
		(MATRIX2F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX2F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		usize__t count)
	{
		SIMD_MATRIX2F(src2);
		if (!count)
		{
			return null;
		}
		dst = src1_ptr[0];
		for (uindex_t itr = 1; itr < count; ++itr)
		{
			const MATRIX2F_t& src1 = src1_ptr[itr];
			src2 = dst;
			mul(dst, src2, src1);
		}
		return &dst;
	}

	static PFX_FORCE_INLINE MATRIX3F_t* mul
		(MATRIX3F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX3F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		usize__t count)
	{
		SIMD_MATRIX3F(src2);
		if (!count)
		{
			return null;
		}
		dst = src1_ptr[0];
		for (uindex_t itr = 1; itr < count; ++itr)
		{
			const MATRIX3F_t& src1 = src1_ptr[itr];
			src2 = dst;
			mul(dst, src2, src1);
		}
		return &dst;
	}


	static PFX_FORCE_INLINE MATRIX4F_t* mul
		(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX4F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		usize__t count)
	{
		SIMD_MATRIX4F(src2);

		if (!count)
		{
			return null;
		}
		dst = src1_ptr[0];
		for (uindex_t itr = 1; itr < count; ++itr)
		{
			const MATRIX4F_t& src1 = src1_ptr[itr];
			src2 = dst;
			mul(dst, src2, src1);
		}
		return &dst;
	}

	//////////////////////////////////////////////////////////////////////////

	static PFX_FORCE_INLINE MATRIX2F_t* mul_end_first
		(MATRIX2F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX2F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		usize__t count)
	{
		SIMD_MATRIX2F(src2);
		if (!count)
		{
			return null;
		}
		--count;
		dst = src1_ptr[count];

		for (uindex_t itr = count; itr !=0; )
		{
			--itr;
			const MATRIX2F_t& src1 = src1_ptr[itr];
			src2 = dst;
			mul(dst, src2, src1);
		}
		return &dst;
	}

	static PFX_FORCE_INLINE MATRIX3F_t* mul_end_first
		(MATRIX3F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX3F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		usize__t count)
	{
		SIMD_MATRIX3F(src2);
		if (!count)
		{
			return null;
		}
		--count;
		dst = src1_ptr[count];

		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			const MATRIX3F_t& src1 = src1_ptr[itr];
			src2 = dst;
			mul(dst, src2, src1);
		}
		return &dst;
	}


	static PFX_FORCE_INLINE MATRIX4F_t* mul_end_first
		(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX4F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		usize__t count)
	{
		SIMD_MATRIX4F(src2);

		if (!count)
		{
			return null;
		}
		--count;
		dst = src1_ptr[count];

		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			const MATRIX4F_t& src1 = src1_ptr[itr];
			src2 = dst;
			mul(dst, src2, src1);
		}
		return &dst;
	}


	//////////////////////////////////////////////////////////////////////////


	static PFX_FORCE_INLINE MATRIX2F_t* mul
		(MATRIX2F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX2F_t& PFX_RESTRICT PARAM_IN src1)
	{
		SIMD_MATRIX2F(src2);
		src2 = dst;
		return mul(dst, src2, src1);
	}

	static PFX_FORCE_INLINE MATRIX3F_t* mul
		(MATRIX3F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX3F_t& PFX_RESTRICT PARAM_IN src1)
	{
		SIMD_MATRIX3F(src2);
		src2 = dst;
		return mul(dst, src2, src1);
	}


	static PFX_FORCE_INLINE MATRIX4F_t* mul
		(MATRIX4F_t& PFX_RESTRICT PARAM_OUT dst,
		const MATRIX4F_t& PFX_RESTRICT PARAM_IN src1)
	{
		SIMD_MATRIX4F(src2);
		src2 = dst;
		return mul(dst, src2, src1);
	}

}matrix_dot_unsafe_sse_t;



PFX_INLINE 	simd_fmat_dot_unsafe_t* init_simd_fmat_dot_sse(simd_fmat_dot_unsafe_t& __fmat)
{
	__fmat.mat_mul_mat_sel			         = matrix_dot_unsafe_std_t::mul;
	__fmat.vecmat_mul_vecmat_sel			 = matrix_dot_unsafe_std_t::mul;

	__fmat.fmat_mul_const					 = matrix_dot_unsafe_std_t::mul;
	__fmat.vec2mat_mul_const				 = matrix_dot_unsafe_std_t::mul;
	__fmat.vec3mat_mul_const				 = matrix_dot_unsafe_std_t::mul;
	__fmat.vec4mat_mul_const				 = matrix_dot_unsafe_std_t::mul;

	__fmat.vec4_dot							 = matrix_dot_unsafe_std_t::dot;
	__fmat.vec2_dot							 = matrix_dot_unsafe_std_t::dot;
	__fmat.vec3_dot							 = matrix_dot_unsafe_std_t::dot;
	__fmat.fvec_dot							 = matrix_dot_unsafe_std_t::dot;

	__fmat.fone_dot_row_major				 = matrix_dot_unsafe_std_t::one_dot_row_major;
	__fmat.fvec_one_dot_row_major			 = matrix_dot_unsafe_std_t::one_dot_row_major;

	__fmat.fone_dot_col_major				 = matrix_dot_unsafe_std_t::one_dot_col_major;
	__fmat.fvec_one_dot_col_major			 = matrix_dot_unsafe_std_t::one_dot_col_major;

	__fmat.vector_mul_matirx_row_major		 = matrix_dot_unsafe_std_t::vector_mul_matirx_row_major;
	__fmat.vector_mul_vecmat_row_major       = matrix_dot_unsafe_std_t::vector_mul_matirx_row_major;
	__fmat.vecmat_mul_vecmat_row_major		 = matrix_dot_unsafe_std_t::mul_row_major;
	__fmat.mat_mul_mat_row_major			 = matrix_dot_unsafe_std_t::mul_row_major;

	__fmat.matirx_mul_vector_col_major		 = matrix_dot_unsafe_std_t::matirx_mul_vector_col_major;
	__fmat.vecmat_mul_vector_col_major		 = matrix_dot_unsafe_std_t::matirx_mul_vector_col_major;
	__fmat.vecmat_mul_vecmat_col_major		 = matrix_dot_unsafe_std_t::mul_col_major;
	__fmat.mat_mul_mat_col_major			 = matrix_dot_unsafe_std_t::mul_col_major;

	__fmat.mat2_mul							 = matrix_dot_unsafe_std_t::mul;
	__fmat.mat3_mul							 = matrix_dot_unsafe_std_t::mul;
	__fmat.mat4_mul							 = matrix_dot_unsafe_std_t::mul;
											 
	__fmat.mat2_mul_replace					 = matrix_dot_unsafe_std_t::mul;
	__fmat.mat3_mul_replace					 = matrix_dot_unsafe_std_t::mul;
	__fmat.mat4_mul_replace					 = matrix_dot_unsafe_std_t::mul;
											 
	__fmat.mat2s_mul						 = matrix_dot_unsafe_std_t::mul;
	__fmat.mat3s_mul						 = matrix_dot_unsafe_std_t::mul;
	__fmat.mat4s_mul						 = matrix_dot_unsafe_std_t::mul;
	__fmat.mat2s_mul_end_first				 = matrix_dot_unsafe_std_t::mul_end_first;
	__fmat.mat3s_mul_end_first				 = matrix_dot_unsafe_std_t::mul_end_first;
	__fmat.mat4s_mul_end_first				 = matrix_dot_unsafe_std_t::mul_end_first;
	return &__fmat;
}


PECKER_END

#endif			//PFX_SIMD_FMATDOT_H_
