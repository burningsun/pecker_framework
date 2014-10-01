/*
 * pfx_simd_fmatset_std.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMATSET_H_
#define		PFX_SIMD_FMATSET_H_

#include "../pfx_defines.h"

#include "pfx_simd_param.h"
#include "pfx_simd_fsub_std.h"
#include "pfx_simd_fmatcross_std.h"
#include "pfx_simd_fmatnormalize_std.h"
#include "pfx_simd_fmatdot_std.h"
#include "pfx_simd_fmatinv_std.h"

#include <math.h>

PECKER_BEGIN

typedef struct st_matrix_set_unsafe_std
{

	static PFX_FORCE_INLINE float_t* load_data(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
	const float_t* PFX_RESTRICT PARAM_OUT src_ptr, usize__t count)
	{
		count = sizeof(float_t)* count;
		memcpy(dst_ptr, src_ptr, count);
		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t** load_data_row_major (float_t** PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t** PFX_RESTRICT PARAM_OUT src_ptr, usize__t row, usize__t col)
	{
		for (uindex_t itr = row; itr != 0; )
		{
			--itr;
			load_data(dst_ptr[itr], src_ptr[itr], col);
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE float_t** load_data_col_major(float_t** PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t** PFX_RESTRICT PARAM_OUT src_ptr, usize__t row, usize__t col)
	{
		for (uindex_t itr = col; itr != 0;)
		{
			--itr;
			load_data(dst_ptr[itr], src_ptr[itr], row);
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX2F_t* load_mat2(MATRIX2F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const MATRIX2F_t* PFX_RESTRICT PARAM_OUT src_ptr, usize__t count)
	{
		count = sizeof(MATRIX2F_t)* count;
		memcpy(dst_ptr, src_ptr, count);
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX3F_t* load_mat3(MATRIX3F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const MATRIX3F_t* PFX_RESTRICT PARAM_OUT src_ptr, usize__t count)
	{
		count = sizeof(MATRIX3F_t)* count;
		memcpy(dst_ptr, src_ptr, count);
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX4F_t* load_mat4(MATRIX4F_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const MATRIX4F_t* PFX_RESTRICT PARAM_OUT src_ptr, usize__t count)
	{
		count = sizeof(MATRIX4F_t)* count;
		memcpy(dst_ptr, src_ptr, count);
		return dst_ptr;
	}

	static PFX_FORCE_INLINE MATRIX2F_t* mat2x2_set(MATRIX2F_t& PARAM_OUT __mat,
		float_t m11, float_t m12,
		float_t m21, float_t m22, bool bcol = true)
	{
		if (bcol)
		{
			return mat2x2_set_col_major(__mat, m11, m12, m21, m22);
		}
		else
		{
			return mat2x2_set_row_major(__mat, m11, m12, m21, m22);
		}
	}

	static PFX_FORCE_INLINE MATRIX3F_t* mat3x3_set(MATRIX3F_t& PARAM_OUT __mat,
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

	static PFX_FORCE_INLINE MATRIX4F_t* mat4x4_set(MATRIX4F_t& PARAM_OUT __mat,
		float_t m11, float_t m12, float_t m13, float_t m14,
		float_t m21, float_t m22, float_t m23, float_t m24,
		float_t m31, float_t m32, float_t m33, float_t m34,
		float_t m41, float_t m42, float_t m43, float_t m44, bool bcol = true)
	{
		if (bcol)
		{
			return mat4x4_set_col_major(__mat,
				m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44);
		}
		else
		{
			return mat4x4_set_row_major(__mat,
				m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44);
		}
	}

#define PFXMAT(__mat,row,col) __mat.m_mat[col].m_vec[row]
	static PFX_FORCE_INLINE MATRIX2F_t* mat2x2_set_col_major(MATRIX2F_t& PARAM_OUT __mat,
	                                                        float_t m11, float_t m12, 
															float_t m21, float_t m22)
	{
		PFXMAT(__mat, 0, 0) = m11;
		PFXMAT(__mat, 1, 0) = m21;
		PFXMAT(__mat, 0, 1) = m12;
		PFXMAT(__mat, 1, 1) = m22;
		return &__mat;
	}

	static PFX_FORCE_INLINE MATRIX3F_t* mat3x3_set_col_major(MATRIX3F_t& PARAM_OUT __mat,
		float_t m11, float_t m12, float_t m13,
		float_t m21, float_t m22, float_t m23,
		float_t m31, float_t m32, float_t m33 )
	{
		PFXMAT(__mat, 0, 0) = m11;
		PFXMAT(__mat, 1, 0) = m21;
		PFXMAT(__mat, 2, 0) = m31;
		PFXMAT(__mat, 0, 1) = m12;
		PFXMAT(__mat, 1, 1) = m22;
		PFXMAT(__mat, 2, 1) = m32;
		PFXMAT(__mat, 0, 2) = m13;
		PFXMAT(__mat, 1, 2) = m23;
		PFXMAT(__mat, 2, 2) = m33;

		return &__mat;
	}

	static PFX_FORCE_INLINE MATRIX4F_t* mat4x4_set_col_major(MATRIX4F_t& PARAM_OUT __mat,
		float_t m11, float_t m12, float_t m13, float_t m14,
		float_t m21, float_t m22, float_t m23, float_t m24,
		float_t m31, float_t m32, float_t m33, float_t m34,
		float_t m41, float_t m42, float_t m43, float_t m44)
	{
		PFXMAT(__mat, 0, 0) = m11;
		PFXMAT(__mat, 1, 0) = m21;
		PFXMAT(__mat, 2, 0) = m31;
		PFXMAT(__mat, 3, 0) = m41;
		PFXMAT(__mat, 0, 1) = m12;
		PFXMAT(__mat, 1, 1) = m22;
		PFXMAT(__mat, 2, 1) = m32;
		PFXMAT(__mat, 3, 1) = m42;
		PFXMAT(__mat, 0, 2) = m13;
		PFXMAT(__mat, 1, 2) = m23;
		PFXMAT(__mat, 2, 2) = m33;
		PFXMAT(__mat, 3, 2) = m43;
		PFXMAT(__mat, 0, 3) = m14;
		PFXMAT(__mat, 1, 3) = m24;
		PFXMAT(__mat, 2, 3) = m34;
		PFXMAT(__mat, 3, 3) = m44;

		return &__mat;
	}
#undef PFXMAT

#define PFXMAT(__mat,row,col) __mat.m_mat[row].m_vec[col]
	static PFX_FORCE_INLINE MATRIX2F_t* mat2x2_set_row_major(MATRIX2F_t& PARAM_OUT __mat,
		float_t m11, float_t m12,
		float_t m21, float_t m22)
	{
		PFXMAT(__mat, 0, 0) = m11;
		PFXMAT(__mat, 1, 0) = m21;
		PFXMAT(__mat, 0, 1) = m12;
		PFXMAT(__mat, 1, 1) = m22;
		return &__mat;
	}

	static PFX_FORCE_INLINE MATRIX3F_t* mat3x3_set_row_major(MATRIX3F_t& PARAM_OUT __mat,
		float_t m11, float_t m12, float_t m13,
		float_t m21, float_t m22, float_t m23,
		float_t m31, float_t m32, float_t m33)
	{
		PFXMAT(__mat, 0, 0) = m11;
		PFXMAT(__mat, 1, 0) = m21;
		PFXMAT(__mat, 2, 0) = m31;
		PFXMAT(__mat, 0, 1) = m12;
		PFXMAT(__mat, 1, 1) = m22;
		PFXMAT(__mat, 2, 1) = m32;
		PFXMAT(__mat, 0, 2) = m13;
		PFXMAT(__mat, 1, 2) = m23;
		PFXMAT(__mat, 2, 2) = m33;

		return &__mat;
	}

	static PFX_FORCE_INLINE MATRIX4F_t* mat4x4_set_row_major(MATRIX4F_t& PARAM_OUT __mat,
		float_t m11, float_t m12, float_t m13, float_t m14,
		float_t m21, float_t m22, float_t m23, float_t m24,
		float_t m31, float_t m32, float_t m33, float_t m34,
		float_t m41, float_t m42, float_t m43, float_t m44)
	{
		PFXMAT(__mat, 0, 0) = m11;
		PFXMAT(__mat, 1, 0) = m21;
		PFXMAT(__mat, 2, 0) = m31;
		PFXMAT(__mat, 3, 0) = m41;
		PFXMAT(__mat, 0, 1) = m12;
		PFXMAT(__mat, 1, 1) = m22;
		PFXMAT(__mat, 2, 1) = m32;
		PFXMAT(__mat, 3, 1) = m42;
		PFXMAT(__mat, 0, 2) = m13;
		PFXMAT(__mat, 1, 2) = m23;
		PFXMAT(__mat, 2, 2) = m33;
		PFXMAT(__mat, 3, 2) = m43;
		PFXMAT(__mat, 0, 3) = m14;
		PFXMAT(__mat, 1, 3) = m24;
		PFXMAT(__mat, 2, 3) = m34;
		PFXMAT(__mat, 3, 3) = m44;

		return &__mat;
	}
#undef PFXMAT

#define MAT4_IDENTITY(X) (X), 0.0, 0.0, 0.0, \
	                     0.0, (X), 0.0, 0.0, \
						 0.0, 0.0, (X), 0.0, \
						 0.0, 0.0, 0.0, (X)

#define MAT4_SCALE(X,Y,Z) (X), 0.0, 0.0, 0.0, \
	                      0.0, (Y), 0.0, 0.0, \
	                      0.0, 0.0, (Z), 0.0, \
	                      0.0, 0.0, 0.0, 1.0

#define MAT3_ROTATE(fCos, fSin)(fCos), (fSin),  0.0,\
	                           -(fSin),  (fCos),  0.0, \
	                              0.0,     0.0,  1.0


#define MAT4_ROTATE_X(fCos, fSin)   1.0,     0.0,     0.0, 0.0,\
	                                0.0,  (fCos),  -(fSin), 0.0,\
	                                0.0,  (fSin),   (fCos), 0.0,\
	                                0.0,     0.0,     0.0, 1.0

#define MAT4_ROTATE_Y(fCos, fSin)(fCos),     0.0,  (fSin), 0.0,\
	                                0.0,     1.0,     0.0, 0.0, \
							     -(fSin),     0.0,  (fCos), 0.0, \
	                                0.0,     0.0,     0.0, 1.0

#define MAT4_ROTATE_Z(fCos, fSin)(fCos),  (fSin),     0.0, 0.0,\
	                             -(fSin),  (fCos),     0.0, 0.0, \
	                                0.0,     0.0,     1.0, 0.0, \
	                                0.0,     0.0,     0.0, 1.0

#define MAT_TRANSLATE(X,Y,Z)   	 1.0,   0.0,  0.0,  (X), \
								 0.0,   1.0,  0.0,  (Y), \
								 0.0,   0.0,  1.0,  (Z), \
								 0.0,   0.0,  0.0,  1.0




	static PFX_FORCE_INLINE const MATRIX4F_t* mat4x4_indentity()
	{
		static SIMD_MATRIX4F(__mat) = { MAT4_IDENTITY(1.0) };
		return &__mat;
	}
	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_indentity(MATRIX4F_t& PARAM_OUT __mat, float_t _val = 1.0)
	{
		mat4x4_set_col_major(__mat, MAT4_IDENTITY(_val));
		return &__mat;
	}
	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_scale(MATRIX4F_t& PARAM_OUT __mat,
		                                             float_t x, float_t y, float_t z)
	{
		mat4x4_set_col_major(__mat, MAT4_SCALE(x,y,z));
		return &__mat;
	}
	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_translate_col_major(MATRIX4F_t& PARAM_OUT __mat,
		                                                    float_t x, float_t y, float_t z)
	{
		mat4x4_set_col_major(__mat, MAT_TRANSLATE(x,y,z));
		return &__mat;
	}
	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_translate_row_major(MATRIX4F_t& PARAM_OUT __mat,
		                                                float_t x, float_t y, float_t z)
	{
		mat4x4_set_row_major(__mat, MAT_TRANSLATE(x, y, z));
		return &__mat;
	}

	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_rotateX_col_major(MATRIX4F_t& PARAM_OUT __mat, float_t rad)
	{
		float_t fSin = ::sin(rad);
		float_t fCos = ::cos(rad);
		mat4x4_set_col_major(__mat, MAT4_ROTATE_X(fCos, fSin));
		return &__mat;
	}
	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_rotateX_row_major(MATRIX4F_t& PARAM_OUT __mat, float_t rad)
	{
		float_t fSin = ::sin(rad);
		float_t fCos = ::cos(rad);
		mat4x4_set_row_major(__mat, MAT4_ROTATE_X(fCos, fSin));
		return &__mat;
	}
	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_rotateY_col_major(MATRIX4F_t& PARAM_OUT __mat, float_t rad)
	{
		float_t fSin = ::sin(rad);
		float_t fCos = ::cos(rad);
		mat4x4_set_col_major(__mat, MAT4_ROTATE_Y(fCos, fSin));
		return &__mat;
	}
	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_rotateY_row_major(MATRIX4F_t& PARAM_OUT __mat, float_t rad)
	{
		float_t fSin = ::sin(rad);
		float_t fCos = ::cos(rad);
		mat4x4_set_row_major(__mat, MAT4_ROTATE_Y(fCos, fSin));
		return &__mat;
	}
	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_rotateZ_col_major(MATRIX4F_t& PARAM_OUT __mat, float_t rad)
	{
		float_t fSin = ::sin(rad);
		float_t fCos = ::cos(rad);
		mat4x4_set_col_major(__mat, MAT4_ROTATE_Z(fCos, fSin));
		return &__mat;
	}
	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_rotateZ_row_major(MATRIX4F_t& PARAM_OUT __mat, float_t rad)
	{
		float_t fSin = ::sin(rad);
		float_t fCos = ::cos(rad);
		mat4x4_set_row_major(__mat, MAT4_ROTATE_Z(fCos, fSin));
		return &__mat;
	}


#define PFX_VEC(__vec,x)  __vec.m_vec[(x)]

#define PFXMAT(__mat,row,col) __mat.m_mat[col].m_vec[row]
	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_LookAtLH_col_major(MATRIX4F_t& PARAM_OUT __mat,
		const VECTOR3F_t& vPosition, const VECTOR3F_t& vLookAt, const VECTOR3F_t& vUp)
	{
		VECTOR3F_t ZAxis;
		VECTOR3F_t XAxis;
		VECTOR3F_t YAxis;
		VECTOR3F_t NormailUP;
		vector_normalize_unsafe_std_t::normalize(NormailUP, vUp);
		array_fsub_unsafe_std_t::operate(&ZAxis, &vPosition, &vLookAt, 1);
		vector_normalize_unsafe_std_t::normalize(ZAxis);

		vector_cross_unsafe_std_t::cross(XAxis, NormailUP, ZAxis);
		vector_cross_unsafe_std_t::cross(YAxis, ZAxis, XAxis);



		PFXMAT(__mat, 0, 0) = -PFX_VEC(XAxis, DIMENSION_X);
		PFXMAT(__mat, 0, 1) = PFX_VEC(YAxis, DIMENSION_X);
		PFXMAT(__mat, 0, 2) = -PFX_VEC(ZAxis, DIMENSION_X);
		PFXMAT(__mat, 0, 3) = 0.0f;

		PFXMAT(__mat, 1, 0) = -PFX_VEC(XAxis, DIMENSION_Y);
		PFXMAT(__mat, 1, 1) = PFX_VEC(YAxis, DIMENSION_Y);
		PFXMAT(__mat, 1, 2) = -PFX_VEC(ZAxis, DIMENSION_Y);
		PFXMAT(__mat, 1, 3) = 0.0f;

		PFXMAT(__mat, 2, 0) = -PFX_VEC(XAxis, DIMENSION_Z);
		PFXMAT(__mat, 2, 1) = PFX_VEC(YAxis, DIMENSION_Z);
		PFXMAT(__mat, 2, 2) = -PFX_VEC(ZAxis, DIMENSION_Z);
		PFXMAT(__mat, 2, 3) = 0.0f;

		PFXMAT(__mat, 3, 0) = matrix_dot_unsafe_std_t::dot(XAxis, vPosition);
		PFXMAT(__mat, 3, 1) = -matrix_dot_unsafe_std_t::dot(YAxis, vPosition);
		PFXMAT(__mat, 3, 2) = matrix_dot_unsafe_std_t::dot(ZAxis, vPosition);
		PFXMAT(__mat, 3, 3) = 1.0f;

		return &__mat;
	}

	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_LookAtRH_col_major(MATRIX4F_t& PARAM_OUT __mat,
		const VECTOR3F_t& vPosition, const VECTOR3F_t& vLookAt, const VECTOR3F_t& vUp)
	{
		VECTOR3F_t ZAxis;
		VECTOR3F_t XAxis;
		VECTOR3F_t YAxis;
		VECTOR3F_t NormailUP;
		vector_normalize_unsafe_std_t::normalize(NormailUP, vUp);
		array_fsub_unsafe_std_t::operate(&ZAxis, &vLookAt, &vPosition, 1);
		vector_normalize_unsafe_std_t::normalize(ZAxis);

		vector_cross_unsafe_std_t::cross(XAxis, NormailUP, ZAxis);
		vector_cross_unsafe_std_t::cross(YAxis, ZAxis, XAxis);



		PFXMAT(__mat, 0, 0) = -PFX_VEC(XAxis, DIMENSION_X);
		PFXMAT(__mat, 0, 1) = PFX_VEC(YAxis, DIMENSION_X);
		PFXMAT(__mat, 0, 2) = -PFX_VEC(ZAxis, DIMENSION_X);
		PFXMAT(__mat, 0, 3) = 0.0f;

		PFXMAT(__mat, 1, 0) = -PFX_VEC(XAxis, DIMENSION_Y);
		PFXMAT(__mat, 1, 1) = PFX_VEC(YAxis, DIMENSION_Y);
		PFXMAT(__mat, 1, 2) = -PFX_VEC(ZAxis, DIMENSION_Y);
		PFXMAT(__mat, 1, 3) = 0.0f;

		PFXMAT(__mat, 2, 0) = -PFX_VEC(XAxis, DIMENSION_Z);
		PFXMAT(__mat, 2, 1) = PFX_VEC(YAxis, DIMENSION_Z);
		PFXMAT(__mat, 2, 2) = -PFX_VEC(ZAxis, DIMENSION_Z);
		PFXMAT(__mat, 2, 3) = 0.0f;

		PFXMAT(__mat, 3, 0) = matrix_dot_unsafe_std_t::dot(XAxis, vPosition);
		PFXMAT(__mat, 3, 1) = -matrix_dot_unsafe_std_t::dot(YAxis, vPosition);
		PFXMAT(__mat, 3, 2) = matrix_dot_unsafe_std_t::dot(ZAxis, vPosition);
		PFXMAT(__mat, 3, 3) = 1.0f;
		return &__mat;
	}

	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_orthogonalRH_opengl(MATRIX4F_t& PARAM_OUT __mat,
		float_t width, float_t height,
		float_t nearPlane, float_t farPlane)
	{
		float_t  rcpnmf = (nearPlane - farPlane);
		if (matrix_inv_unsafe_std_t::is_near_zero(width) ||
			matrix_inv_unsafe_std_t::is_near_zero(height) ||
			matrix_inv_unsafe_std_t::is_near_zero(rcpnmf)
			)
		{
			// 没法算
			mat4x4_indentity(__mat);
			return null;
		}

		mat4x4_set_col_major(__mat,
			      (2.0 / width),         0.0,                           0.0,  0.0,
			             0.0, (2.0 / height),                           0.0,  0.0,
						 0.0,           0.0,                     2.0/rcpnmf,  0.0,
						 0.0,           0.0,    (nearPlane+farPlane)/rcpnmf,  1.0
						 );
		return &__mat;
	}

	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_orthogonalLH_opengl(MATRIX4F_t& PARAM_OUT __mat,
		float_t width, float_t height,
		float_t nearPlane, float_t farPlane)
	{
		float_t  rcpnmf = (nearPlane - farPlane);
		if (matrix_inv_unsafe_std_t::is_near_zero(width) ||
			matrix_inv_unsafe_std_t::is_near_zero(height) ||
			matrix_inv_unsafe_std_t::is_near_zero(rcpnmf)
			)
		{
			// 没法算
			mat4x4_indentity(__mat);
			return null;
		}

		mat4x4_set_col_major(__mat,
			      (2.0 / width),         0.0,                           0.0,  0.0,
			             0.0, (2.0 / height),                           0.0,  0.0,
						 0.0,           0.0,                   - 2.0/rcpnmf,  0.0,
						 0.0,           0.0,   -(nearPlane+farPlane)/rcpnmf,  1.0
						 );
		return &__mat;
	}

	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_perspectiveRH_opengl(MATRIX4F_t& PARAM_OUT __mat, 
		float_t width, float_t height,
		float_t nearPlane, float_t farPlane)
	{
		float_t  rcpnmf = (nearPlane - farPlane);
		if (matrix_inv_unsafe_std_t::is_near_zero(width) ||
			matrix_inv_unsafe_std_t::is_near_zero(height) ||
			matrix_inv_unsafe_std_t::is_near_zero(rcpnmf)
			)
		{
			// 没法算
			mat4x4_indentity(__mat);
			return null;
		}

		float_t n2;
		n2          = 2.0f * nearPlane;

		mat4x4_set_col_major(__mat,
			      (n2 / width),         0.0,                           0.0,   0.0,
			             0.0, (n2 / height),                           0.0,   0.0,
						 0.0,           0.0, (farPlane + nearPlane)/rcpnmf,  -1.0,
						 0.0,           0.0,          (farPlane*n2/rcpnmf),   0.0
						 );
		return &__mat;
	}

	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_perspectiveLH_opengl(MATRIX4F_t& PARAM_OUT __mat,
		float_t width, float_t height,
		float_t nearPlane, float_t farPlane)
	{
		float_t  rcpnmf = (nearPlane - farPlane);
		if (matrix_inv_unsafe_std_t::is_near_zero(width) ||
			matrix_inv_unsafe_std_t::is_near_zero(height) ||
			matrix_inv_unsafe_std_t::is_near_zero(rcpnmf)
			)
		{
			// 没法算
			mat4x4_indentity(__mat);
			return null;
		}

		float_t n2;
		n2 = 2.0f * nearPlane;
		mat4x4_set_col_major(__mat,
			      (n2 / width),         0.0,                           0.0,   0.0,
			             0.0, (n2 / height),                           0.0,   0.0,
						 0.0,           0.0, -(farPlane + nearPlane)/rcpnmf,  1.0,
						 0.0,           0.0,          -(farPlane*n2/rcpnmf),   0.0
						 );

		return &__mat;
	}

	// 	 aspect = width / height 
	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_perspective_fov_RH_opengl(MATRIX4F_t& PARAM_OUT __mat,
		float_t fovy, float_t aspect,
		float_t nearPlane, float_t farPlane)
	{
		float_t  rcpnmf = (nearPlane - farPlane);
		float_t  height = ::tan(fovy / 2.0);
		float_t  width;

		if (matrix_inv_unsafe_std_t::is_near_zero(aspect) ||
			matrix_inv_unsafe_std_t::is_near_zero(height) ||
			matrix_inv_unsafe_std_t::is_near_zero(rcpnmf)
			)
		{
			// 没法算
			mat4x4_indentity(__mat);
			return null;
		}
		height = 1.0 / height; // cot(fovy/2.0)
		width = height / aspect;	  //

		mat4x4_set_col_major(__mat,
			width,    0.0,                                  0.0,    0.0,
			0.0,   height,                                  0.0,    0.0,
			0.0,      0.0,      (farPlane + nearPlane) / rcpnmf,   -1.0,
			0.0,      0.0, 2.0f * nearPlane * farPlane / rcpnmf,    0.0
			);
		return &__mat;
	}

	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_perspective_fov_LH_opengl(MATRIX4F_t& PARAM_OUT __mat,
		float_t fovy, float_t aspect,
		float_t nearPlane, float_t farPlane)
	{
		float_t  rcpnmf = (nearPlane - farPlane);
		float_t  height = ::tan(fovy / 2.0);
		float_t  width;

		if (matrix_inv_unsafe_std_t::is_near_zero(aspect) ||
			matrix_inv_unsafe_std_t::is_near_zero(height) ||
			matrix_inv_unsafe_std_t::is_near_zero(rcpnmf)
			)
		{
			// 没法算
			mat4x4_indentity(__mat);
			return null;
		}
		height = 1.0 / height; // cot(fovy/2.0)
		width = height / aspect;	  //

		mat4x4_set_col_major(__mat,
			width,    0.0,                                  0.0,     0.0,
			0.0,   height,                                  0.0,     0.0,
			0.0,      0.0, -(farPlane + nearPlane)/rcpnmf,           1.0,
			0.0,      0.0, -(2.0f * farPlane*nearPlane/rcpnmf),      0.0
			);
		return &__mat;
	}


#undef PFXMAT


#define PFXMAT(__mat,row,col) __mat.m_mat[row].m_vec[col]
	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_LookAtLH_row_major(MATRIX4F_t& PARAM_OUT __mat,
		const VECTOR3F_t& vPosition, const VECTOR3F_t& vLookAt, const VECTOR3F_t& vUp)
	{
		VECTOR3F_t ZAxis;
		VECTOR3F_t XAxis;
		VECTOR3F_t YAxis;
		VECTOR3F_t NormailUP;
		vector_normalize_unsafe_std_t::normalize(NormailUP, vUp);
		array_fsub_unsafe_std_t::operate(&ZAxis, &vPosition, &vLookAt, 1);
		vector_normalize_unsafe_std_t::normalize(ZAxis);

		vector_cross_unsafe_std_t::cross(XAxis, NormailUP, ZAxis);
		vector_cross_unsafe_std_t::cross(YAxis, ZAxis, XAxis);


		PFXMAT(__mat, 0, 0) = PFX_VEC(XAxis, DIMENSION_X);
		PFXMAT(__mat, 0, 1) = PFX_VEC(YAxis, DIMENSION_X);
		PFXMAT(__mat, 0, 2) = PFX_VEC(ZAxis, DIMENSION_X);
		PFXMAT(__mat, 0, 3) = 0.0f;

		PFXMAT(__mat, 1, 0) = PFX_VEC(XAxis, DIMENSION_Y);
		PFXMAT(__mat, 1, 1) = PFX_VEC(YAxis, DIMENSION_Y);
		PFXMAT(__mat, 1, 2) = PFX_VEC(ZAxis, DIMENSION_Y);
		PFXMAT(__mat, 1, 3) = 0.0f;

		PFXMAT(__mat, 2, 0) = PFX_VEC(XAxis, DIMENSION_Z);
		PFXMAT(__mat, 2, 1) = PFX_VEC(YAxis, DIMENSION_Z);
		PFXMAT(__mat, 2, 2) = PFX_VEC(ZAxis, DIMENSION_Z);
		PFXMAT(__mat, 2, 3) = 0.0f;

		PFXMAT(__mat, 3, 0) = -matrix_dot_unsafe_std_t::dot(XAxis, vPosition);
		PFXMAT(__mat, 3, 1) = -matrix_dot_unsafe_std_t::dot(YAxis, vPosition);
		PFXMAT(__mat, 3, 2) = -matrix_dot_unsafe_std_t::dot(ZAxis, vPosition);
		PFXMAT(__mat, 3, 3) = 1.0f;
		return &__mat;
	}

	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_LookAtRH_row_major(MATRIX4F_t& PARAM_OUT __mat,
		const VECTOR3F_t& vPosition, const VECTOR3F_t& vLookAt, const VECTOR3F_t& vUp)
	{
		VECTOR3F_t ZAxis;
		VECTOR3F_t XAxis;
		VECTOR3F_t YAxis;
		VECTOR3F_t NormailUP;
		vector_normalize_unsafe_std_t::normalize(NormailUP, vUp);
		array_fsub_unsafe_std_t::operate(&ZAxis, &vPosition, &vLookAt, 1);
		vector_normalize_unsafe_std_t::normalize(ZAxis);

		vector_cross_unsafe_std_t::cross(XAxis, NormailUP, ZAxis);
		vector_cross_unsafe_std_t::cross(YAxis, ZAxis, XAxis);


		PFXMAT(__mat, 0, 0) = -PFX_VEC(XAxis, DIMENSION_X);
		PFXMAT(__mat, 0, 1) =  PFX_VEC(YAxis, DIMENSION_X);
		PFXMAT(__mat, 0, 2) = -PFX_VEC(ZAxis, DIMENSION_X);
		PFXMAT(__mat, 0, 3) =  0.0f;

		PFXMAT(__mat, 1, 0) = -PFX_VEC(XAxis, DIMENSION_Y);
		PFXMAT(__mat, 1, 1) =  PFX_VEC(YAxis, DIMENSION_Y);
		PFXMAT(__mat, 1, 2) = -PFX_VEC(ZAxis, DIMENSION_Y);
		PFXMAT(__mat, 1, 3) =  0.0f;

		PFXMAT(__mat, 2, 0) = -PFX_VEC(XAxis, DIMENSION_Z);
		PFXMAT(__mat, 2, 1) =  PFX_VEC(YAxis, DIMENSION_Z);
		PFXMAT(__mat, 2, 2) = -PFX_VEC(ZAxis, DIMENSION_Z);
		PFXMAT(__mat, 2, 3) =  0.0f;

		PFXMAT(__mat, 3, 0) =  matrix_dot_unsafe_std_t::dot(XAxis, vPosition);
		PFXMAT(__mat, 3, 1) = -matrix_dot_unsafe_std_t::dot(YAxis, vPosition);
		PFXMAT(__mat, 3, 2) =  matrix_dot_unsafe_std_t::dot(ZAxis, vPosition);
		PFXMAT(__mat, 3, 3) =  1.0f;
		return &__mat;
	}

	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_orthogonalRH_directX(MATRIX4F_t& PARAM_OUT __mat,
		float_t width, float_t height,
		float_t nearPlane, float_t farPlane)
	{
		float_t  rcpnmf = (nearPlane - farPlane);
		if (matrix_inv_unsafe_std_t::is_near_zero(width) ||
			matrix_inv_unsafe_std_t::is_near_zero(height) ||
			matrix_inv_unsafe_std_t::is_near_zero(rcpnmf)
			)
		{
			// 没法算
			mat4x4_indentity(__mat);
			return null;
		}

		mat4x4_set_row_major(__mat,
			      (2.0 / width),         0.0,                           0.0,     0.0,
			             0.0, (2.0 / height),                           0.0,     0.0,
						 0.0,           0.0,                     1.0/rcpnmf,     0.0,
						 0.0,           0.0,               nearPlane/rcpnmf,     1.0
						 );
		return &__mat;
	}

	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_orthogonalLH_directX(MATRIX4F_t& PARAM_OUT __mat,
		float_t width, float_t height,
		float_t nearPlane, float_t farPlane)
	{
		MATRIX4F_t* mat_ptr = mat4x4_orthogonalRH_directX(__mat, width, height, nearPlane, farPlane);
		if (mat_ptr)
		{
			PFXMAT(__mat, 2, 2) = -PFXMAT(__mat, 2, 2);
			PFXMAT(__mat, 3, 2) = -PFXMAT(__mat, 3, 2);
		}
		return mat_ptr;
	}

	static PFX_FORCE_INLINE MATRIX4F_t* mat4x4_perspectiveRH_directX(MATRIX4F_t& PARAM_OUT __mat, 
		float_t width, float_t height,
		float_t nearPlane, float_t farPlane)
	{
		float_t  rcpnmf = (nearPlane - farPlane);
		if (matrix_inv_unsafe_std_t::is_near_zero(width) ||
			matrix_inv_unsafe_std_t::is_near_zero(height) ||
			matrix_inv_unsafe_std_t::is_near_zero(rcpnmf)
			)
		{
			// 没法算
		    mat4x4_indentity(__mat);
			return null;
		}

		float_t n2, n2divheight, n2divwidth;

		n2          = 2.0f * nearPlane;

	    mat4x4_set_row_major(__mat,
	        (n2 / width),         0.0,                           0.0,  0.0,
	               0.0, (n2 / height),                           0.0,  0.0,
				 0.0,           0.0,               farPlane / rcpnmf, -1.0,
				 0.0,           0.0,     (nearPlane*farPlane/ rcpnmf),  0.0
				 );
		return &__mat;
	}

	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_perspectiveLH_directX(MATRIX4F_t& PARAM_OUT __mat,
			float_t width, float_t height,
			float_t nearPlane, float_t farPlane)
		{
			MATRIX4F_t* mat_ptr = mat4x4_perspectiveRH_directX(__mat, width, height, nearPlane, farPlane);
			if (mat_ptr)
			{
				PFXMAT(__mat, 2, 2) = -PFXMAT(__mat, 2, 2);
				PFXMAT(__mat, 2, 3) = -PFXMAT(__mat, 2, 3);
				PFXMAT(__mat, 3, 2) = -PFXMAT(__mat, 3, 2);
			}
			return mat_ptr;
		}

		// 	 aspect = width / height 
	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_perspective_fov_RH_directX(MATRIX4F_t& PARAM_OUT __mat,
			float_t fovy, float_t aspect,
			float_t nearPlane, float_t farPlane)
		{
			float_t  rcpnmf = (nearPlane - farPlane);
			float_t  height =  ::tan(fovy / 2.0);
			float_t  width;

			if (matrix_inv_unsafe_std_t::is_near_zero(aspect) ||
				matrix_inv_unsafe_std_t::is_near_zero(height) ||
				matrix_inv_unsafe_std_t::is_near_zero(rcpnmf)
				)
			{
				// 没法算
				mat4x4_indentity(__mat);
				return null;
			}
			height = 1.0 / height; // cot(fovy/2.0)
			width = height / aspect;	  //


			mat4x4_set_row_major(__mat,
				width,    0.0,                            0.0,   0.0,
				  0.0, height,                            0.0,   0.0,
				  0.0,    0.0,              farPlane / rcpnmf, 	-1.0,
				  0.0,    0.0,  nearPlane * farPlane / rcpnmf,   0.0
				);
			return &__mat;
		}

	static PFX_FORCE_INLINE  MATRIX4F_t* mat4x4_perspective_fov_LH_directX(MATRIX4F_t& PARAM_OUT __mat,
			float_t fovy, float_t aspect,
			float_t nearPlane, float_t farPlane)
		{
			MATRIX4F_t* mat_ptr = mat4x4_perspective_fov_RH_directX(__mat, fovy, aspect, nearPlane, farPlane);
			if (mat_ptr)
			{
				PFXMAT(__mat, 2, 2) = -PFXMAT(__mat, 2, 2);
				PFXMAT(__mat, 2, 3) = -PFXMAT(__mat, 2, 3);
				PFXMAT(__mat, 3, 2) = -PFXMAT(__mat, 3, 2);
			}
			return mat_ptr;
		}
#undef PFXMAT


#undef PFX_VEC



}matrix_set_unsafe_std_t;



PECKER_END

#endif			//PFX_SIMD_FMATSET_H_
