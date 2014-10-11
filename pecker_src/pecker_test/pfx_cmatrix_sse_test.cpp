/*
 * pfx_matrix_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/native/pecker_allocator.h"
#include "../pecker_framework/data/pfx_cmatrix_codes.h"

#include "../pecker_framework/math/pfx_math.h"

#ifdef CPU_X86_SSE_ARCH
#include "../pecker_framework/math/pfx_simd_param_sse.h"
#include "../pecker_framework/math/sse/pfx_simd_fmatdet_sse.h"
#include "../pecker_framework/math/sse/pfx_simd_fmatinv_sse.h"
#include "../pecker_framework/math/sse/pfx_simd_fmatdot_sse.h"
USING_PECKER_SDK

void printf_mat(const float_t* mat_ptr, usize__t row, usize__t col, bool brow_major = true)
{
	uindex_t offset = 0;
	if (brow_major)
	{
		for (uindex_t i = 0; i < row; ++i)
		{
			PECKER_LOG_STR("[ ");
			for (uindex_t j = 0; j < col; ++j)
			{
				PECKER_LOG_("%f ", mat_ptr[offset + j]);
			}
			PECKER_LOG_STR("]\n");
			offset += col;
		}
	}
	else
	{
		for (uindex_t i = 0; i < row; ++i)
		{
			PECKER_LOG_STR("[ ");
			for (uindex_t j = 0; j < col; ++j)
			{
				PECKER_LOG_("%f ", mat_ptr[offset]);
				offset += col;
			}
			PECKER_LOG_STR("]\n");
			offset = i;
		}
	}

}

void printf_mat(const MATRIX4F_t* mat_ptr, bool brow_major = true)
{
	return printf_mat((const float_t*)mat_ptr, 4, 4, brow_major);
}

void printf_mat(const MATRIX3F_t* mat_ptr, bool brow_major = true)
{
	return printf_mat((const float_t*)mat_ptr, 3, 3, brow_major);
}

void printf_mat(const MATRIX2F_t* mat_ptr, bool brow_major = true)
{
	return printf_mat((const float_t*)mat_ptr, 2, 2, brow_major);
}

void sse_test_det()
{
	SIMD_MATRIX2F(mat2x2) = { 10, 1, 
		                      3, 5 };
	SIMD_MATRIX3F(mat3x3) = { 1,  2,  3,
		                      4,  1,  1,
	                          1,  8,  9};
	SIMD_MATRIX4F(mat4x4) = { 1, 2, 3, 10,
		                      1, 5, 1, 20,
		                      7, 8, 2, 30,
	                          4,1, 5, 100};
	float det;

	PECKER_LOG_STR("STD DET\n");
	det = matrix_det_unsafe_std_t::det2x2(mat2x2);
	PECKER_LOG_("det2x2 = %f\n", det);
	det = matrix_det_unsafe_std_t::det3x3(mat3x3);
	PECKER_LOG_("det3x3 = %f\n", det);
	det = matrix_det_unsafe_std_t::det4x4(mat4x4);
	PECKER_LOG_("det4x4 = %f\n", det);

	PECKER_LOG_STR("SSE DET\n");
	det = matrix_det_unsafe_sse_t::det2x2(mat2x2);
	PECKER_LOG_("det2x2 = %f\n", det);
	det = matrix_det_unsafe_sse_t::det3x3(mat3x3);
	PECKER_LOG_("det3x3 = %f\n", det);
	det = matrix_det_unsafe_sse_t::det4x4(mat4x4);
	PECKER_LOG_("det4x4 = %f\n", det);

}

void sse_test_inv()
{
	SIMD_MATRIX2F(mat2x2) = { 4, 4,
		                      3, 1 };
	SIMD_MATRIX3F(mat3x3) = { 5, 2, 3,
		                      4, 9, 1,
		                      1, 8, 9 };
	SIMD_MATRIX4F(mat4x4) = { 1, 2, 3, 10,
		                      1, 5, 1, 20,
		                       7, 8, 2, 30,
		                       4, 1, 5, 100 };

	SIMD_MATRIX2F(mat2x2_tag);
	SIMD_MATRIX3F(mat3x3_tag);
	SIMD_MATRIX4F(mat4x4_tag);

	SIMD_MATRIX2F(mat2x2_test);
	SIMD_MATRIX3F(mat3x3_test);
	SIMD_MATRIX4F(mat4x4_test);

	PECKER_LOG_STR("STD INV\n");

	PECKER_LOG_STR("MAT2X2\n");
	if (matrix_inv_unsafe_std_t::inverse2x2(mat2x2_tag, mat2x2))
	{
		printf_mat(&mat2x2_tag);
		matrix_dot_unsafe_std_t::mul(mat2x2_test, mat2x2, mat2x2_tag);

		PECKER_LOG_STR("TEST MAT INV\n");
		printf_mat(&mat2x2_test);
	}
	else
	{
		PECKER_LOG_STR("can't inverse!\n");
	}

	PECKER_LOG_STR("MAT3X3\n");
	if (matrix_inv_unsafe_std_t::inverse3x3(mat3x3_tag, mat3x3))
	{
		printf_mat(&mat3x3_tag);
		matrix_dot_unsafe_std_t::mul(mat3x3_test, mat3x3, mat3x3_tag);

		PECKER_LOG_STR("TEST MAT INV\n");
		printf_mat(&mat3x3_test);
	}
	else
	{
		PECKER_LOG_STR("can't inverse!\n");
	}

	PECKER_LOG_STR("MAT4X4\n");
	if (matrix_inv_unsafe_std_t::inverse4x4(mat4x4_tag, mat4x4))
	{
		printf_mat(&mat4x4_tag);
		matrix_dot_unsafe_std_t::mul(mat4x4_test, mat4x4, mat4x4_tag);
		PECKER_LOG_STR("TEST MAT INV\n");
		printf_mat(&mat4x4_test);
	}
	else
	{
		PECKER_LOG_STR("can't inverse!\n");
	}

	PECKER_LOG_STR("SSE INV\n");

	PECKER_LOG_STR("MAT2X2\n");
	if (matrix_inv_unsafe_sse_t::inverse2x2(mat2x2_tag, mat2x2))
	{
		printf_mat(&mat2x2_tag);
		matrix_dot_unsafe_sse_t::mul(mat2x2_test, mat2x2, mat2x2_tag);
		PECKER_LOG_STR("TEST MAT INV\n");
		printf_mat(&mat2x2_test);
	}
	else
	{
		PECKER_LOG_STR("can't inverse!\n");
	}

	PECKER_LOG_STR("MAT3X3\n");
	if (matrix_inv_unsafe_sse_t::inverse3x3(mat3x3_tag, mat3x3))
	{
		printf_mat(&mat3x3_tag);
		matrix_dot_unsafe_sse_t::mul(mat3x3_test, mat3x3, mat3x3_tag);

		PECKER_LOG_STR("TEST MAT INV\n");
		printf_mat(&mat3x3_test);
	}
	else
	{
		PECKER_LOG_STR("can't inverse!\n");
	}

	PECKER_LOG_STR("MAT4X4\n");
	if (matrix_inv_unsafe_sse_t::inverse4x4(mat4x4_tag, mat4x4))
	{
		printf_mat(&mat4x4_tag);
		matrix_dot_unsafe_sse_t::mul(mat4x4_test, mat4x4, mat4x4_tag);
		PECKER_LOG_STR("TEST MAT INV\n");
		printf_mat(&mat4x4_test);
	}
	else
	{
		PECKER_LOG_STR("can't inverse!\n");
	}
}


void sse_test_mul()
{
	SIMD_MATRIX2F(mat2x2) = { 1,2,3,4 };
	SIMD_MATRIX2F(mat2x2_2) = { 5,6,7,8 };
	SIMD_MATRIX3F(mat3x3) = { 1, 2, 3,
		4, 1, 1,
		1, 8, 9 };
	SIMD_MATRIX3F(mat3x3_2) = { 1, 2, 3,
		4, 16, 11,
		1, 8, 9 };
	SIMD_MATRIX4F(mat4x4) = { 1, 2, 3, 10,
		1, 5, 1, 20,
		7, 8, 2, 30,
		4, 1, 5, 100 };

	SIMD_MATRIX4F(mat4x4_2) = { 9, 10, 11, 22,
		1, 5, 1, 20,
		7, 8, 2, 30,
		4, 1, 5, 100 };

	SIMD_MATRIX2F(mat2x2_tag);
	SIMD_MATRIX3F(mat3x3_tag);
	SIMD_MATRIX4F(mat4x4_tag);

	PECKER_LOG_STR("STD MUL\n");
	PECKER_LOG_STR("MAT2X2\n");
	matrix_dot_unsafe_std_t::mul(mat2x2_tag, mat2x2, mat2x2_2);
	printf_mat(&mat2x2_tag);

	PECKER_LOG_STR("MAT3X3\n");
	matrix_dot_unsafe_std_t::mul(mat3x3_tag, mat3x3, mat3x3_2);
	printf_mat(&mat3x3_tag);

	PECKER_LOG_STR("MAT4X4\n");
	matrix_dot_unsafe_std_t::mul(mat4x4_tag, mat4x4, mat4x4_2);
	printf_mat(&mat4x4_tag);


	PECKER_LOG_STR("SSE MUL\n");
	PECKER_LOG_STR("MAT2X2\n");
	matrix_dot_unsafe_sse_t::mul(mat2x2_tag, mat2x2, mat2x2_2);
	printf_mat(&mat2x2_tag);

	PECKER_LOG_STR("MAT3X3\n");
	matrix_dot_unsafe_sse_t::mul(mat3x3_tag, mat3x3, mat3x3_2);
	printf_mat(&mat3x3_tag);

	PECKER_LOG_STR("MAT4X4\n");
	matrix_dot_unsafe_sse_t::mul(mat4x4_tag, mat4x4, mat4x4_2);
	printf_mat(&mat4x4_tag);

}


#endif

