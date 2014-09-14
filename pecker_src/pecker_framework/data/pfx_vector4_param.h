/*
 * pfx_vector4_param.h
 *
 *  Created on: 2013-8-25
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_VECTOR4_PARAM_H_
#define		PFX_VECTOR4_PARAM_H_

#include "../pfx_defines.h"
PECKER_BEGIN

typedef enum enumDIMENSION_NAME
{
	DIMENSION_X = 0,
	DIMENSION_Y,
	DIMENSION_Z,
	DIMENSION_W,

	DIMENSION_OTHER
}PFX_DIMENSION_NAME_t;

template < class _value, const usize__t dim_count >
struct st_vector_data
{
	// vc,intel,arm的编译器均不支持定义数组的时候大小为0，除了gcc
	_value m_vec[(dim_count > 0) ? dim_count : 1];
};

typedef st_vector_data< float, 4 > VECTOR4F_t;
typedef st_vector_data< float, 3 > VECTOR3F_t;
typedef st_vector_data< float, 2 > VECTOR2F_t;
typedef st_vector_data< int, 4 >   VECTOR4I_t;
typedef st_vector_data< int, 3 >   VECTOR3I_t;
typedef st_vector_data< int, 2 >   VECTOR2I_t;

template < class _value, 
	const usize__t xdim_count, 
	const usize__t ydim_count = xdim_count >
struct st_matrix_data
{
	// vc,intel,arm的编译器均不支持定义数组的时候大小为0，除了gcc
	st_vector_data< _value, xdim_count > m_mat[(ydim_count > 0) ? ydim_count : 1];
};

typedef st_matrix_data< float, 4 > MATRIX4F_t;
typedef st_matrix_data< float, 3 > MATRIX3F_t;
typedef st_matrix_data< float, 2 > MATRIX2F_t;
typedef st_matrix_data< int, 4 >   MATRIX4I_t;
typedef st_matrix_data< int, 3 >   MATRIX3I_t;
typedef st_matrix_data< int, 2 >   MATRIX2I_t;

template < class _value,
	const usize__t xdim_count,
	const usize__t ydim_count = xdim_count >
struct st_matrix_data_ref
{
	st_vector_data< _value, xdim_count >* m_mat[(ydim_count > 0) ? ydim_count : 1];
	st_matrix_data< _value, xdim_count, ydim_count >* mat_ptr;

	st_matrix_data_ref() :mat_ptr(null)
	{
		ZeroMemory(m_mat, sizeof(m_mat));
	}
	st_matrix_data_ref(st_matrix_data< _value, xdim_count, ydim_count >& mat)
	{
		mat_ptr = &mat;
		for (uindex_t i = 0; i < ydim_count; ++i)
		{
			m_mat[i] = &mat.m_mat[i];
		}
	}
};


PECKER_END

#endif			//PFX_VECTOR4_PARAM_H_
