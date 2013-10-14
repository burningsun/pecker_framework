/*
 * pfx_matrix4.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_MATRIX4_H_
#define		PFX_MATRIX4_H_

#include "../pfx_defines.h"
#include "pfx_fixed_point.h"
#include "pfx_vector4.h"
#include "pfx_simd_optimization.h"

PFX_C_EXTERN_BEGIN

typedef enum enumMATRIX2_INDEX_TYPE
{
	M2_00 = 0,
	M2_01,

	M2_10,
	M2_11,
	MATRIX2_INDEX_COUNT
}MATRIX2_INDEX_TYPE_t;

typedef enum enumMATRIX3_INDEX_TYPE
{
	M3_00 = 0,
	M3_01,
	M3_02,

	M3_10,
	M3_11,
	M3_12,

	M3_20,
	M3_21,
	M3_22,

	MATRIX3_INDEX_COUNT
}MATRIX3_INDEX_TYPE_t;

typedef enum enumMATRIX4_INDEX_TYPE
{
	M4_00 = 0,
	M4_01,
	M4_02,
	M4_03,

	M4_10,
	M4_11,
	M4_12,
	M4_13,

	M4_20,
	M4_21,
	M4_22,
	M4_23,

	M4_30,
	M4_31,
	M4_32,
	M4_33,

	MATRIX4_INDEX_COUNT
}MATRIX4_INDEX_TYPE_t;


typedef struct st_pfx_matrix2f pfx_marix2f_t;
typedef struct st_pfx_matrix3f pfx_marix3f_t;
typedef struct st_pfx_matrix4f pfx_marix4f_t;

typedef union un_pfx_matrix2 pfx_marix2_t;
typedef union un_pfx_matrix3 pfx_marix3_t;
typedef union un_pfx_matrix4 pfx_marix4_t;

struct st_pfx_matrix2f
{
	VEC_FLOAT m_mat[4];
};

struct st_pfx_matrix3f
{
	VEC_FLOAT m_mat[9];
};

struct st_pfx_matrix4f
{
	VEC_FLOAT m_mat[16];
};

union un_pfx_matrix2
{
	st_pfx_matrix2f m_mat;
	pfx_vector2_t	m_vec[2];
};

union un_pfx_matrix3
{
	st_pfx_matrix3f m_mat;
	pfx_vector3_t	m_vec[3];
};

union un_pfx_matrix4
{
	st_pfx_matrix4f m_mat;
	pfx_vector4_t	m_vec[4];
};


#define MATRIX_DATA(MAT,MAT_INDEX) ((MAT).m_mat.m_mat[(MAT_INDEX)])
#define PMATRIX_DATA(MAT,MAT_INDEX) ((MAT)->m_mat.m_mat[(MAT_INDEX)])

#define MATRIX_DATA_(MAT,MAT_INDEX_X,MAT_INDEX_Y) ((MAT).m_vec[(MAT_INDEX_X)].m_vec_f[(MAT_INDEX_Y)])
#define PMATRIX_DATA_(MAT,MAT_INDEX_X,MAT_INDEX_Y) ((MAT)->m_vec[(MAT_INDEX_X)].m_vec_f[(MAT_INDEX_Y)])

PFX_INLINE void init_to_identity_marix2_unsafe (pfx_marix2_t* PARAM_INOUT mat)
{
	PMATRIX_DATA (mat,M2_00) = ONE_FLOAT;   PMATRIX_DATA (mat,M2_01) = ZERO_FLOAT;
	PMATRIX_DATA (mat,M2_10) = ZERO_FLOAT;  PMATRIX_DATA (mat,M2_11) = ONE_FLOAT;
}

PFX_INLINE void init_to_identity_marix3_unsafe (pfx_marix3_t* PARAM_INOUT mat)
{
	PMATRIX_DATA (mat,M3_00) = ONE_FLOAT;  PMATRIX_DATA (mat,M3_01) = ZERO_FLOAT; PMATRIX_DATA(mat,M3_02) = ZERO_FLOAT;
	PMATRIX_DATA (mat,M3_10) = ZERO_FLOAT; PMATRIX_DATA (mat,M3_11) = ONE_FLOAT;  PMATRIX_DATA(mat,M3_12) = ZERO_FLOAT;
	PMATRIX_DATA (mat,M3_10) = ZERO_FLOAT; PMATRIX_DATA (mat,M3_11) = ZERO_FLOAT;  PMATRIX_DATA(mat,M3_12) = ONE_FLOAT;
}

PFX_INLINE void init_to_identity_marix4_unsafe (pfx_marix3_t* PARAM_INOUT mat)
{
	PMATRIX_DATA (mat,M4_00) = ONE_FLOAT;   PMATRIX_DATA (mat,M4_01) = ZERO_FLOAT; PMATRIX_DATA (mat,M4_02) = ZERO_FLOAT; PMATRIX_DATA (mat,M4_03) = ZERO_FLOAT;
	PMATRIX_DATA (mat,M4_10) = ZERO_FLOAT;  PMATRIX_DATA (mat,M4_11) = ONE_FLOAT;  PMATRIX_DATA (mat,M4_12) = ZERO_FLOAT; PMATRIX_DATA (mat,M4_13) = ZERO_FLOAT;
	PMATRIX_DATA (mat,M4_20) = ZERO_FLOAT;  PMATRIX_DATA (mat,M4_21) = ZERO_FLOAT; PMATRIX_DATA (mat,M4_22) = ONE_FLOAT;  PMATRIX_DATA (mat,M4_23) = ZERO_FLOAT;
	PMATRIX_DATA (mat,M4_10) = ZERO_FLOAT;  PMATRIX_DATA (mat,M4_30) = ZERO_FLOAT; PMATRIX_DATA (mat,M4_32) = ZERO_FLOAT; PMATRIX_DATA (mat,M4_33) = ONE_FLOAT;
}

PFX_INLINE pfx_marix2_t* init_marix2_floats_unsafe (pfx_marix2_t* PARAM_INOUT mat,
	VEC_FLOAT f00,VEC_FLOAT f01,
	VEC_FLOAT f10,VEC_FLOAT f11)
{
	PMATRIX_DATA (mat,M2_00) = f00;
	PMATRIX_DATA (mat,M2_01) = f01;
	PMATRIX_DATA (mat,M2_10) = f10;
	PMATRIX_DATA (mat,M2_11) = f11;
	return mat;
}

PFX_INLINE pfx_marix3_t* init_marix3_floats_unsafe (pfx_marix3_t* PARAM_INOUT mat,
	VEC_FLOAT f00,VEC_FLOAT f01,VEC_FLOAT f02,
	VEC_FLOAT f10,VEC_FLOAT f11,VEC_FLOAT f12,
	VEC_FLOAT f20,VEC_FLOAT f21,VEC_FLOAT f22)
{
	PMATRIX_DATA (mat,M3_00) = f00;
	PMATRIX_DATA (mat,M3_01) = f01;
	PMATRIX_DATA (mat,M3_02) = f02;

	PMATRIX_DATA (mat,M3_10) = f10;
	PMATRIX_DATA (mat,M3_11) = f11;
	PMATRIX_DATA (mat,M3_12) = f12;

	PMATRIX_DATA (mat,M3_20) = f20;
	PMATRIX_DATA (mat,M3_21) = f21;
	PMATRIX_DATA (mat,M3_22) = f22;

	return mat;
}

PFX_INLINE pfx_marix4_t* init_marix4_floats_unsafe (pfx_marix4_t* PARAM_INOUT mat,
	VEC_FLOAT f00,VEC_FLOAT f01,VEC_FLOAT f02,VEC_FLOAT f03,
	VEC_FLOAT f10,VEC_FLOAT f11,VEC_FLOAT f12,VEC_FLOAT f13,
	VEC_FLOAT f20,VEC_FLOAT f21,VEC_FLOAT f22,VEC_FLOAT f23,
	VEC_FLOAT f30,VEC_FLOAT f31,VEC_FLOAT f32,VEC_FLOAT f33)
{
	PMATRIX_DATA (mat,M4_00) = f00;
	PMATRIX_DATA (mat,M4_01) = f01;
	PMATRIX_DATA (mat,M4_02) = f02;
	PMATRIX_DATA (mat,M4_03) = f03;

	PMATRIX_DATA (mat,M4_10) = f10;
	PMATRIX_DATA (mat,M4_11) = f11;
	PMATRIX_DATA (mat,M4_12) = f12;
	PMATRIX_DATA (mat,M4_13) = f13;

	PMATRIX_DATA (mat,M4_20) = f20;
	PMATRIX_DATA (mat,M4_21) = f21;
	PMATRIX_DATA (mat,M4_22) = f22;
	PMATRIX_DATA (mat,M4_23) = f23;

	PMATRIX_DATA (mat,M4_30) = f30;
	PMATRIX_DATA (mat,M4_31) = f31;
	PMATRIX_DATA (mat,M4_32) = f32;
	PMATRIX_DATA (mat,M4_33) = f33;
	return mat;
}

PFX_INLINE void init_matrix2_by_matrix2_unsafe (pfx_marix2_t* mat_dec,pfx_marix2_t* mat_src)
{
	init_vector2_by_vector2_unsafe (&mat_dec->m_vec[0],&mat_src->m_vec[0]);
	init_vector2_by_vector2_unsafe (&mat_dec->m_vec[1],&mat_src->m_vec[1]);
}

PFX_INLINE void init_matrix3_by_matrix3_unsafe (pfx_marix3_t* mat_dec,pfx_marix3_t* mat_src)
{
	init_vector3_by_vector3_unsafe (&mat_dec->m_vec[0],&mat_src->m_vec[0]);
	init_vector3_by_vector3_unsafe (&mat_dec->m_vec[1],&mat_src->m_vec[1]);
	init_vector3_by_vector3_unsafe (&mat_dec->m_vec[2],&mat_src->m_vec[2]);
}

PFX_INLINE void init_matrix4_by_matrix4_unsafe (pfx_marix4_t* mat_dec,pfx_marix4_t* mat_src)
{
	init_vector4_by_vector4_unsafe (&mat_dec->m_vec[0],&mat_src->m_vec[0]);
	init_vector4_by_vector4_unsafe (&mat_dec->m_vec[1],&mat_src->m_vec[1]);
	init_vector4_by_vector4_unsafe (&mat_dec->m_vec[2],&mat_src->m_vec[2]);
	init_vector4_by_vector4_unsafe (&mat_dec->m_vec[3],&mat_src->m_vec[3]);
}


PFX_INLINE void init_matrix2_by_matrix2_unsafe_std (pfx_marix2_t* mat_dec,pfx_marix2_t* mat_src)
{
	init_vector2_by_vector2_unsafe_std (&mat_dec->m_vec[0],&mat_src->m_vec[0]);
	init_vector2_by_vector2_unsafe_std (&mat_dec->m_vec[1],&mat_src->m_vec[1]);
}

PFX_INLINE void init_matrix3_by_matrix3_unsafe_std (pfx_marix3_t* mat_dec,pfx_marix3_t* mat_src)
{
	init_vector3_by_vector3_unsafe_std (&mat_dec->m_vec[0],&mat_src->m_vec[0]);
	init_vector3_by_vector3_unsafe_std (&mat_dec->m_vec[1],&mat_src->m_vec[1]);
	init_vector3_by_vector3_unsafe_std (&mat_dec->m_vec[2],&mat_src->m_vec[2]);
}

PFX_INLINE void init_matrix4_by_matrix4_unsafe_std (pfx_marix4_t* mat_dec,pfx_marix4_t* mat_src)
{
	init_vector4_by_vector4_unsafe_std (&mat_dec->m_vec[0],&mat_src->m_vec[0]);
	init_vector4_by_vector4_unsafe_std (&mat_dec->m_vec[1],&mat_src->m_vec[1]);
	init_vector4_by_vector4_unsafe_std (&mat_dec->m_vec[2],&mat_src->m_vec[2]);
	init_vector4_by_vector4_unsafe_std (&mat_dec->m_vec[3],&mat_src->m_vec[3]);
}



PFX_C_EXTERN_END




#endif			//PFX_MATRIX4_H_
