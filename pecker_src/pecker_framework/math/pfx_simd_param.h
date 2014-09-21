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



#ifdef _MSC_VER
#define PFX_SIMD_INTRIN __declspec(intrin_type)
#define PFX_SIMD_ALIGN(x) __declspec(align(x))
#else
#ifdef __GNUC__
#define PFX_SIMD_ALIGN(x) __attribute__ ((aligned (x)))
#endif
#define PFX_SIMD_INTRIN 
#endif

// 作为 __declspec 的参数，不能加括号
#define PFX_SIMD256BIT_ALIGH   32
#define PFX_SIMD128BIT_ALIGH   16
#define PFX_SIMD64BIT_ALIGH    16
#define PFX_SIMD32BIT_ALIGH    16

//typedef PFX_SIMD_ALIGN(PFX_SIMD32BIT_ALIGH) float SIMD_FLOAT_t;
//typedef PFX_SIMD_ALIGN(PFX_SIMD32BIT_ALIGH) int   SIMD_INT_t;
#ifdef __GNUC__
#define DECLARE_SIMD_ALIGN_BUF(TYPE_NAME, DATANAME, ALIGH)	TYPE_NAME  DATANAME	 PFX_SIMD_ALIGN(ALIGH)
#else
#ifdef _MSC_VER
#define DECLARE_SIMD_ALIGN_BUF(TYPE_NAME, DATANAME, ALIGH)	PFX_SIMD_ALIGN(ALIGH)TYPE_NAME  DATANAME
#else
#define DECLARE_SIMD_ALIGN_BUF(TYPE_NAME, DATANAME, ALIGH) 
#endif
#endif

#define  SIMD_FLOAT(NAME) DECLARE_SIMD_ALIGN_BUF(float_t, NAME, PFX_SIMD32BIT_ALIGH)
#define  SIMD_INT(NAME)   DECLARE_SIMD_ALIGN_BUF(sint_t,  NAME, PFX_SIMD32BIT_ALIGH)


PFX_FORCE_INLINE bool CHECK_ADDR_ALIGH(enum_int_t ALIGH_CODE, void* addr_ptr)
{
	return (!((lpointer_t)addr_ptr & (ALIGH_CODE - 1)));	 // laddr % ALIGH_CODE == 0;
}
PFX_FORCE_INLINE nsize__t GET_ADDR_ALIGH_OFFSET(enum_int_t ALIGH_CODE, void* addr_ptr)
{
	nsize__t remain = ((lpointer_t)addr_ptr & (ALIGH_CODE - 1));

	if (!remain)
	{
		return 0;
	}
	else
	{
		return (ALIGH_CODE - remain);
	}
}


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

//typedef PFX_SIMD_ALIGN(PFX_SIMD128BIT_ALIGH) VECTOR4F_t SIMD_VECTOR4F_t;
//typedef PFX_SIMD_ALIGN(PFX_SIMD64BIT_ALIGH)  VECTOR3F_t SIMD_VECTOR3F_t;
//typedef PFX_SIMD_ALIGN(PFX_SIMD64BIT_ALIGH)  VECTOR2F_t SIMD_VECTOR2F_t;
//typedef PFX_SIMD_ALIGN(PFX_SIMD128BIT_ALIGH) VECTOR4I_t SIMD_VECTOR4I_t;
//typedef PFX_SIMD_ALIGN(PFX_SIMD64BIT_ALIGH)  VECTOR3I_t SIMD_VECTOR3I_t;
//typedef PFX_SIMD_ALIGN(PFX_SIMD64BIT_ALIGH)  VECTOR2I_t SIMD_VECTOR2I_t;

#define SIMD_VECTOR4F(NAME)  DECLARE_SIMD_ALIGN_BUF(VECTOR4F_t, NAME,  PFX_SIMD128BIT_ALIGH)
#define SIMD_VECTOR3F(NAME)  DECLARE_SIMD_ALIGN_BUF(VECTOR3F_t, NAME,  PFX_SIMD64BIT_ALIGH )
#define SIMD_VECTOR2F(NAME)  DECLARE_SIMD_ALIGN_BUF(VECTOR2F_t, NAME,  PFX_SIMD64BIT_ALIGH )
#define SIMD_VECTOR4I(NAME)  DECLARE_SIMD_ALIGN_BUF(VECTOR4I_t, NAME,  PFX_SIMD128BIT_ALIGH)
#define SIMD_VECTOR3I(NAME)  DECLARE_SIMD_ALIGN_BUF(VECTOR3I_t, NAME,  PFX_SIMD64BIT_ALIGH )
#define SIMD_VECTOR2I(NAME)  DECLARE_SIMD_ALIGN_BUF(VECTOR2I_t, NAME,  PFX_SIMD64BIT_ALIGH )

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

//typedef PFX_SIMD_ALIGN(PFX_SIMD128BIT_ALIGH) MATRIX4F_t SIMD_MATRIX4F_t;
//typedef PFX_SIMD_ALIGN(PFX_SIMD64BIT_ALIGH)  MATRIX3F_t SIMD_MATRIX3F_t;
//typedef PFX_SIMD_ALIGN(PFX_SIMD64BIT_ALIGH)  MATRIX2F_t SIMD_MATRIX2F_t;
//typedef PFX_SIMD_ALIGN(PFX_SIMD128BIT_ALIGH) MATRIX4I_t SIMD_MATRIX4I_t;
//typedef PFX_SIMD_ALIGN(PFX_SIMD64BIT_ALIGH)  MATRIX3I_t SIMD_MATRIX3I_t;
//typedef PFX_SIMD_ALIGN(PFX_SIMD64BIT_ALIGH)  MATRIX2I_t SIMD_MATRIX2I_t;

#define SIMD_MATRIX4F(NAME)  DECLARE_SIMD_ALIGN_BUF(MATRIX4F_t, NAME,  PFX_SIMD128BIT_ALIGH)
#define SIMD_MATRIX3F(NAME)  DECLARE_SIMD_ALIGN_BUF(MATRIX3F_t, NAME,  PFX_SIMD64BIT_ALIGH )
#define SIMD_MATRIX2F(NAME)  DECLARE_SIMD_ALIGN_BUF(MATRIX2F_t, NAME,  PFX_SIMD64BIT_ALIGH )
#define SIMD_MATRIX4I(NAME)  DECLARE_SIMD_ALIGN_BUF(MATRIX4I_t, NAME,  PFX_SIMD128BIT_ALIGH)
#define SIMD_MATRIX3I(NAME)  DECLARE_SIMD_ALIGN_BUF(MATRIX3I_t, NAME,  PFX_SIMD64BIT_ALIGH )
#define SIMD_MATRIX2I(NAME)  DECLARE_SIMD_ALIGN_BUF(MATRIX2I_t, NAME,  PFX_SIMD64BIT_ALIGH )

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
