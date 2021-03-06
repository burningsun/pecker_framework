﻿/*
 * pfx_cmatrix4.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CMATRIX4_H_
#define		PFX_CMATRIX4_H_

#include "../pfx_defines.h"
#include "pfx_cmatrix_codes.h"

PECKER_BEGIN

template < class dim_value >
struct PFX_CMatrix4x4_DATA
{
	typedef  dim_value															dim_t;

	typedef typename vector_data< dim_t, 2 >::vector_t					vector_d2_t;
	typedef typename square_matrix_data< dim_t, 2 >::matrix_t matrix_d2_t;

	typedef typename vector_data< dim_t, 3 >::vector_t					vector_d3_t;
	typedef typename square_matrix_data< dim_t, 3 >::matrix_t matrix_d3_t;

	typedef typename vector_data< dim_t, 4 >::vector_t					vector_d4_t;
	typedef typename square_matrix_data< dim_t, 4 >::matrix_t matrix_d4_t;
};

template < class smatrix_data, 
const boolean_t row_matrix = PFX_BOOL_TRUE, 
const enum_int_t optinal_type = 0 >
struct PFX_CMatrix4x4
{
	typedef typename smatrix_data::dim_t															dim_t;

	typedef  VectorX < dim_t, 2, optinal_type >									vector2_t;
	typedef  SquareMatrixX < dim_t, 2, optinal_type >					matrix2_t;
	typedef  SquareMatrixEX_unsafe < dim_t, 2, optinal_type >	matrix2x_t;

	typedef  VectorX < dim_t, 3, optinal_type >									vector3_t;
	typedef  SquareMatrixX < dim_t, 3, optinal_type >					matrix3_t;
	typedef  SquareMatrixEX_unsafe < dim_t, 3, optinal_type >	matrix3x_t;

	typedef  VectorX < dim_t, 4, optinal_type >									vector4_t;
	typedef  SquareMatrixX < dim_t, 4, optinal_type >					matrix4_t;
	typedef  SquareMatrixEX_unsafe < dim_t, 4, optinal_type >	matrix4x_t;

	//static PFX_INLINE vector4_t operator* (const vector4_t& __vec_a, const matrix4_t& __matrix_b)
	//{
	//	return matrix4_t::mul (__vec_a, __matrix_b);
	//}
	//static PFX_INLINE vector4_t& operator*= (vector4_t& __vec_a, const matrix4_t& __matrix_b)
	//{
	//	return matrix4_t::mul_replace (__vec_a, __matrix_b);
	//}
	//static PFX_INLINE matrix4_t& operator*= (matrix4_t& __matrix_a, const matrix4_t& __matrix_b)
	//{
	//	return __matrix_a.mul_replace (__matrix_b);
	//}
	//static PFX_INLINE matrix4_t operator = (const matrix4_t& __matrix_a, const matrix4_t& __matrix_b)
	//{
	//	return __matrix_a.mul (__matrix_b);
	//}

	static PFX_INLINE matrix4_t scale (dim_t scale_size)
	{
		dim_t ZERO_FLOAT	= 0;
		dim_t ONE_FLOAT		= 1;
		return matrix4_t
			(scale_size		,	ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT,
			ZERO_FLOAT	,	scale_size		,	ZERO_FLOAT	,	ZERO_FLOAT,
			ZERO_FLOAT	,	ZERO_FLOAT	,	scale_size		,	ZERO_FLOAT,
			ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT);
	}
	static PFX_INLINE matrix4_t scale (dim_t x, dim_t y, dim_t z)
	{
		dim_t ZERO_FLOAT	= 0;
		dim_t ONE_FLOAT		= 1;
		return matrix4_t
			(x,						ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT,
			ZERO_FLOAT	,	y						,	ZERO_FLOAT	,	ZERO_FLOAT,
			ZERO_FLOAT	,	ZERO_FLOAT	,	z						,	ZERO_FLOAT,
			ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT);
	}
	static PFX_INLINE matrix4_t scale (const vector4_t& vec)
	{
		return scale(vec[DIMENSION_X], vec[DIMENSION_Y], vec[DIMENSION_Z]);
	}
	static PFX_INLINE matrix4_t scale (const vector3_t& vec)
	{
		return scale(vec[DIMENSION_X], vec[DIMENSION_Y], vec[DIMENSION_Z]);
	}
	static PFX_INLINE matrix4_t translate (dim_t x, dim_t y, dim_t z)
	{
		dim_t ZERO_FLOAT	= 0;
		dim_t ONE_FLOAT		= 1;

		return matrix4_t
			(ONE_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT,
			ZERO_FLOAT	,	ONE_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT,
			ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT	,	ZERO_FLOAT,
			x,							y,							z,							ONE_FLOAT);
	}
	static PFX_INLINE matrix4_t translate (const vector3_t& vec)
	{
		return translate(vec[DIMENSION_X], vec[DIMENSION_Y], vec[DIMENSION_Z]);
	}
	static PFX_INLINE matrix4_t translate (const vector4_t& vec)
	{
		return translate(vec[DIMENSION_X], vec[DIMENSION_Y], vec[DIMENSION_Z]);
	}
	static PFX_INLINE matrix4_t& pre_translate(matrix4_t& PARAM_INOUT mat, const vector4_t& vec)
	{
		return mat;
	}
	static PFX_INLINE matrix4_t& post_translate(matrix4_t& PARAM_INOUT mat, const vector4_t& vec)
	{
		return mat;
	}
	static PFX_INLINE matrix4_t rotate_x (dim_t radian)
	{
		dim_t ZERO_FLOAT	= 0;
		dim_t ONE_FLOAT		= 1;
		dim_t fsin;
		dim_t fcos;

		matrix4_t::dim_alg_t::sincos (radian,fsin,fcos);
		return matrix4_t
			(ONE_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT,
			ZERO_FLOAT	,	fcos					,	fsin					,	ZERO_FLOAT,
			ZERO_FLOAT	,	-fsin				,	fcos					,	ZERO_FLOAT,
			ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT);
	}
	static PFX_INLINE matrix4_t rotate_y (dim_t radian)
	{
		dim_t ZERO_FLOAT	= 0;
		dim_t ONE_FLOAT		= 1;
		dim_t fsin;
		dim_t fcos;

		matrix4_t::dim_alg_t::sincos (radian,fsin,fcos);
		return matrix4_t
			(fcos				,	ZERO_FLOAT	,	-fsin					,	ZERO_FLOAT,
			ZERO_FLOAT	,	ONE_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT,
			fsin					,	ZERO_FLOAT	,	fcos					,	ZERO_FLOAT,
			ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT);
	}
	static PFX_INLINE matrix4_t rotate_z (dim_t radian)
	{
		dim_t ZERO_FLOAT	= 0;
		dim_t ONE_FLOAT		= 1;
		dim_t fsin;
		dim_t fcos;

		matrix4_t::dim_alg_t::sincos (radian,fsin,fcos);
		return matrix4_t
			(fcos				,	fsin					,	ZERO_FLOAT	,	ZERO_FLOAT,
			-fsin				,	fcos					,	ZERO_FLOAT	,	ZERO_FLOAT,
			ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT	,	ZERO_FLOAT,
			ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT);
	}
	static PFX_INLINE matrix4_t rotate_vector (const vector3_t& vec, dim_t rad)
	{
		return matrix4_t();
	}
	static PFX_INLINE matrix4_t rotate_vector (const vector4_t& vec, dim_t rad)
	{
		return matrix4_t();
	}

	static PFX_INLINE matrix4_t orthogonal_projection_matrix (dim_t left, dim_t top, dim_t width,
		dim_t height, dim_t near_plane, dim_t far_plane,
		boolean_t bOPENGL = PFX_BOOL_TRUE,
		boolean_t bright_handle = PFX_BOOL_TRUE, 
		boolean_t brotate = PFX_BOOL_FALSE)
	{
		return matrix4_t();
	}
	static PFX_INLINE matrix4_t perspective_projection_matrix (dim_t width, 
		dim_t hight, dim_t near_plane, dim_t far_plane, 
		boolean_t bOPENGL = PFX_BOOL_TRUE,
		boolean_t bright_handle = PFX_BOOL_TRUE, 
		boolean_t brotate = PFX_BOOL_FALSE)
	{
		return matrix4_t();
	}
	static PFX_INLINE matrix4_t perspective_projection_matrix_fov (dim_t fovy,
		dim_t aspect,dim_t near_plane,dim_t far_plane,		
		boolean_t bOPENGL = PFX_BOOL_TRUE,
		boolean_t bright_handle = PFX_BOOL_TRUE, 
		boolean_t brotate = PFX_BOOL_FALSE)
	{
		return matrix4_t();
	}

	static PFX_INLINE matrix4_t perspective_projection_matrix (dim_t width, dim_t hight, 
		dim_t near_plane, 
		boolean_t bOPENGL = PFX_BOOL_TRUE,
		boolean_t bright_handle = PFX_BOOL_TRUE, 
		boolean_t brotate = PFX_BOOL_FALSE)
	{
		return matrix4_t();
	}
	static PFX_INLINE matrix4_t perspective_projection_matrix_fov (dim_t fovy,
		dim_t aspect,dim_t near_plane,
		boolean_t bOPENGL = PFX_BOOL_TRUE,
		boolean_t bright_handle = PFX_BOOL_TRUE, 
		boolean_t brotate = PFX_BOOL_FALSE)
	{
		return matrix4_t();
	}
	static PFX_INLINE matrix4_t look_at_view_matrix (const vector3_t& vEye,
		const vector3_t& vAt,const vector3_t& vUp,boolean_t bright_handle = PFX_BOOL_TRUE)
	{
		return matrix4_t();
	}
	static PFX_INLINE matrix4_t look_at_view_matrix (const vector4_t& vEye,
		const vector4_t& vAt,const vector4_t& vUp,boolean_t bright_handle = PFX_BOOL_TRUE)
	{
		return matrix4_t();
	}

};


PECKER_END

#endif			//PFX_CMATRIX_H_
