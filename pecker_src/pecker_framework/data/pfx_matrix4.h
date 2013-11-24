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
#include "pfx_util.h"

PFX_C_EXTERN_BEGIN

typedef enum PFX_DATA_API enumMATRIX2_INDEX_TYPE
{
	M2_00 = 0,
	M2_01,

	M2_10,
	M2_11,
	MATRIX2_INDEX_COUNT
}MATRIX2_INDEX_TYPE_t;

typedef enum PFX_DATA_API enumMATRIX3_INDEX_TYPE
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

typedef enum PFX_DATA_API enumMATRIX4_INDEX_TYPE
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


typedef struct PFX_DATA_API st_pfx_matrix2f pfx_marix2f_t;
typedef struct PFX_DATA_API st_pfx_matrix3f pfx_marix3f_t;
typedef struct PFX_DATA_API st_pfx_matrix4f pfx_marix4f_t;

typedef union PFX_DATA_API un_pfx_matrix2 pfx_marix2_t;
typedef union PFX_DATA_API un_pfx_matrix3 pfx_marix3_t;
typedef union PFX_DATA_API un_pfx_matrix4 pfx_marix4_t;

struct PFX_DATA_API st_pfx_matrix2f
{
	VEC_FLOAT m_mat[4];
};

struct PFX_DATA_API st_pfx_matrix3f
{
	VEC_FLOAT m_mat[9];
};

struct PFX_DATA_API st_pfx_matrix4f
{
	VEC_FLOAT m_mat[16];
};

union PFX_DATA_API un_pfx_matrix2
{
	st_pfx_matrix2f m_mat;
	pfx_vector2_t	m_vec[2];
};

union PFX_DATA_API un_pfx_matrix3
{
	st_pfx_matrix3f m_mat;
	pfx_vector3_t	m_vec[3];
};

union PFX_DATA_API un_pfx_matrix4
{
	st_pfx_matrix4f m_mat;
	pfx_vector4_t	m_vec[4];
};

typedef enum PFX_DATA_API enumClipspaceSystem
{
	D3DX_CLIPSPACE_SYSTEM = 0,
	OPENGL_CLIPSPACE_SYSTEM,
	CLIPSPACE_SYSTEM_COUNT
}CLIPSPACE_SYSTEM;

#define MATRIX_DATA(MAT,MAT_INDEX) ((MAT).m_mat.m_mat[(MAT_INDEX)])
#define PMATRIX_DATA(MAT,MAT_INDEX) ((MAT)->m_mat.m_mat[(MAT_INDEX)])

#define MATRIX_DATA_(MAT,MAT_INDEX_R,MAT_INDEX_C) ((MAT).m_vec[(MAT_INDEX_R)].m_vec_f[(MAT_INDEX_C)])
#define PMATRIX_DATA_(MAT,MAT_INDEX_R,MAT_INDEX_C) ((MAT)->m_vec[(MAT_INDEX_R)].m_vec_f[(MAT_INDEX_C)])

PFX_INLINE void init_to_identity_matrix2_unsafe_std (pfx_marix2_t* PARAM_INOUT mat)
{
	PMATRIX_DATA (mat,M2_00) = ONE_FLOAT;   PMATRIX_DATA (mat,M2_01) = ZERO_FLOAT;
	PMATRIX_DATA (mat,M2_10) = ZERO_FLOAT;  PMATRIX_DATA (mat,M2_11) = ONE_FLOAT;
}

PFX_INLINE void init_to_identity_matrix3_unsafe_std (pfx_marix3_t* PARAM_INOUT mat)
{
	PMATRIX_DATA (mat,M3_00) = ONE_FLOAT;  PMATRIX_DATA (mat,M3_01) = ZERO_FLOAT; PMATRIX_DATA(mat,M3_02) = ZERO_FLOAT;
	PMATRIX_DATA (mat,M3_10) = ZERO_FLOAT; PMATRIX_DATA (mat,M3_11) = ONE_FLOAT;  PMATRIX_DATA(mat,M3_12) = ZERO_FLOAT;
	PMATRIX_DATA (mat,M3_10) = ZERO_FLOAT; PMATRIX_DATA (mat,M3_11) = ZERO_FLOAT;  PMATRIX_DATA(mat,M3_12) = ONE_FLOAT;
}

PFX_INLINE void init_to_identity_matrix4_unsafe_std (pfx_marix4_t* PARAM_INOUT mat)
{
	PMATRIX_DATA (mat,M4_00) = ONE_FLOAT;   PMATRIX_DATA (mat,M4_01) = ZERO_FLOAT; PMATRIX_DATA (mat,M4_02) = ZERO_FLOAT; PMATRIX_DATA (mat,M4_03) = ZERO_FLOAT;
	PMATRIX_DATA (mat,M4_10) = ZERO_FLOAT;  PMATRIX_DATA (mat,M4_11) = ONE_FLOAT;  PMATRIX_DATA (mat,M4_12) = ZERO_FLOAT; PMATRIX_DATA (mat,M4_13) = ZERO_FLOAT;
	PMATRIX_DATA (mat,M4_20) = ZERO_FLOAT;  PMATRIX_DATA (mat,M4_21) = ZERO_FLOAT; PMATRIX_DATA (mat,M4_22) = ONE_FLOAT;  PMATRIX_DATA (mat,M4_23) = ZERO_FLOAT;
	PMATRIX_DATA (mat,M4_30) = ZERO_FLOAT;  PMATRIX_DATA (mat,M4_31) = ZERO_FLOAT; PMATRIX_DATA (mat,M4_32) = ZERO_FLOAT; PMATRIX_DATA (mat,M4_33) = ONE_FLOAT;
}

PFX_INLINE pfx_marix2_t* init_matrix2_floats_unsafe_std (pfx_marix2_t* PARAM_INOUT mat,
	VEC_FLOAT f00,VEC_FLOAT f01,
	VEC_FLOAT f10,VEC_FLOAT f11)
{
	PMATRIX_DATA (mat,M2_00) = f00;
	PMATRIX_DATA (mat,M2_01) = f01;
	PMATRIX_DATA (mat,M2_10) = f10;
	PMATRIX_DATA (mat,M2_11) = f11;
	return mat;
}

PFX_INLINE pfx_marix3_t* init_matrix3_floats_unsafe_std (pfx_marix3_t* PARAM_INOUT mat,
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

PFX_INLINE pfx_marix4_t* init_matrix4_floats_unsafe_std (pfx_marix4_t* PARAM_INOUT mat,
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

PFX_INLINE void init_matrix2_by_matrix2_unsafe (pfx_marix2_t* PARAM_INOUT mat_dec,const pfx_marix2_t* PARAM_IN mat_src)
{
	init_vector2_by_vector2_unsafe (&mat_dec->m_vec[0],&mat_src->m_vec[0]);
	init_vector2_by_vector2_unsafe (&mat_dec->m_vec[1],&mat_src->m_vec[1]);
}

PFX_INLINE void init_matrix3_by_matrix3_unsafe (pfx_marix3_t* PARAM_INOUT mat_dec,const pfx_marix3_t* PARAM_IN mat_src)
{
	init_vector3_by_vector3_unsafe (&mat_dec->m_vec[0],&mat_src->m_vec[0]);
	init_vector3_by_vector3_unsafe (&mat_dec->m_vec[1],&mat_src->m_vec[1]);
	init_vector3_by_vector3_unsafe (&mat_dec->m_vec[2],&mat_src->m_vec[2]);
}

PFX_INLINE void init_matrix4_by_matrix4_unsafe (pfx_marix4_t* PARAM_INOUT mat_dec,const pfx_marix4_t* PARAM_IN mat_src)
{
	init_vector4_by_vector4_unsafe (&mat_dec->m_vec[0],&mat_src->m_vec[0]);
	init_vector4_by_vector4_unsafe (&mat_dec->m_vec[1],&mat_src->m_vec[1]);
	init_vector4_by_vector4_unsafe (&mat_dec->m_vec[2],&mat_src->m_vec[2]);
	init_vector4_by_vector4_unsafe (&mat_dec->m_vec[3],&mat_src->m_vec[3]);
}


PFX_INLINE void init_matrix2_by_matrix2_unsafe_std (pfx_marix2_t* PARAM_INOUT mat_dec,const pfx_marix2_t* PARAM_IN mat_src)
{
	init_vector2_by_vector2_unsafe_std (&mat_dec->m_vec[0],&mat_src->m_vec[0]);
	init_vector2_by_vector2_unsafe_std (&mat_dec->m_vec[1],&mat_src->m_vec[1]);
}

PFX_INLINE void init_matrix3_by_matrix3_unsafe_std (pfx_marix3_t* PARAM_INOUT mat_dec,const pfx_marix3_t* PARAM_IN mat_src)
{
	init_vector3_by_vector3_unsafe_std (&mat_dec->m_vec[0],&mat_src->m_vec[0]);
	init_vector3_by_vector3_unsafe_std (&mat_dec->m_vec[1],&mat_src->m_vec[1]);
	init_vector3_by_vector3_unsafe_std (&mat_dec->m_vec[2],&mat_src->m_vec[2]);
}

PFX_INLINE void init_matrix4_by_matrix4_unsafe_std (pfx_marix4_t* PARAM_INOUT mat_dec,const pfx_marix4_t* PARAM_IN mat_src)
{
	init_vector4_by_vector4_unsafe_std (&mat_dec->m_vec[0],&mat_src->m_vec[0]);
	init_vector4_by_vector4_unsafe_std (&mat_dec->m_vec[1],&mat_src->m_vec[1]);
	init_vector4_by_vector4_unsafe_std (&mat_dec->m_vec[2],&mat_src->m_vec[2]);
	init_vector4_by_vector4_unsafe_std (&mat_dec->m_vec[3],&mat_src->m_vec[3]);
}


// v.斯特拉森 (V.Strassen) 求二价矩阵
PFX_INLINE pfx_marix2_t* _matrix2_mul_matrix2_ref_unsafe_std (pfx_marix2_t* PARAM_INOUT mat,
	const pfx_marix2_t* PARAM_IN mat1,const pfx_marix2_t* PARAM_IN mat2,
	VEC_FLOAT* PARAM_INOUT temp)
{
	temp[0] = VEC_FLOAT_MUL ((PMATRIX_DATA_(mat1,0,0) + PMATRIX_DATA_(mat1,1,1)) , 
		(PMATRIX_DATA_(mat2,0,0) + PMATRIX_DATA_(mat2,1,1)));

	temp[1] = VEC_FLOAT_MUL ((PMATRIX_DATA_(mat1,1,0)+PMATRIX_DATA_(mat1,1,1)) ,
		PMATRIX_DATA_(mat2,0,0));

	temp[2] = VEC_FLOAT_MUL (PMATRIX_DATA_(mat1,0,0),
		(PMATRIX_DATA_(mat2,0,1) - PMATRIX_DATA_(mat2,1,1)));

	temp[3] = VEC_FLOAT_MUL (PMATRIX_DATA_(mat1,1,1),
		(PMATRIX_DATA_(mat2,1,0) - PMATRIX_DATA_(mat2,0,0)));

	temp[4] = VEC_FLOAT_MUL ((PMATRIX_DATA_(mat1,0,0)+PMATRIX_DATA_(mat1,0,1)),
		PMATRIX_DATA_(mat2,1,1));

	temp[5] = VEC_FLOAT_MUL ((PMATRIX_DATA_(mat1,1,0)-PMATRIX_DATA_(mat1,0,0)),
		(PMATRIX_DATA_(mat2,0,0)+PMATRIX_DATA_(mat2,0,1)));

	temp[6] = VEC_FLOAT_MUL ((PMATRIX_DATA_(mat1,0,1)-PMATRIX_DATA_(mat1,1,1)),
		(PMATRIX_DATA_(mat2,1,0)+PMATRIX_DATA_(mat2,1,1)));

	PMATRIX_DATA_ (mat,0,0) = temp[0] + temp[3] -temp[4] + temp[6];
	PMATRIX_DATA_ (mat,0,1) = temp[2] + temp[4];
	PMATRIX_DATA_ (mat,1,0) = temp[1] + temp[3];
	PMATRIX_DATA_ (mat,1,1) = temp[0] + temp[2] - temp[1] + temp[5];

	return mat;
}

PFX_INLINE pfx_marix2_t* matrix2_mul_matrix2_ref_unsafe_std (pfx_marix2_t* PARAM_INOUT mat,
	const pfx_marix2_t* PARAM_IN mat1,const pfx_marix2_t* PARAM_IN mat2)
{
	VEC_FLOAT temp[7];
	return _matrix2_mul_matrix2_ref_unsafe_std(mat,mat1,mat2,temp);
}

PFX_INLINE pfx_marix2_t matrix2_mul_matrix2_unsafe_std (const pfx_marix2_t* PARAM_IN mat1,const pfx_marix2_t* PARAM_IN mat2)
{
	VEC_FLOAT temp[7];
	pfx_marix2_t mat;
	_matrix2_mul_matrix2_ref_unsafe_std(&mat,mat1,mat2,temp);
	return mat;
}

//PFX_INLINE pfx_vector4_t matrix4_get_column_unsafe (const pfx_marix4_t* PARAM_IN mat,pfx_index_t index_)
//{
//	pfx_vector4_t return_vec;
//	init_vector4_unsafe (&return_vec,PMATRIX_DATA_ (mat,0,index_),PMATRIX_DATA_ (mat,1,index_),
//		PMATRIX_DATA_ (mat,2,index_),PMATRIX_DATA_ (mat,3,index_));
//	return return_vec;
//}
//
//PFX_INLINE pfx_vector4_t matrix4_get_column_unsafe_std (const pfx_marix4_t* PARAM_IN mat,pfx_index_t index_)
//{
//	pfx_vector4_t return_vec;
//	init_vector4_unsafe_std (&return_vec,PMATRIX_DATA_ (mat,0,index_),PMATRIX_DATA_ (mat,1,index_),
//		PMATRIX_DATA_ (mat,2,index_),PMATRIX_DATA_ (mat,3,index_));
//	return return_vec;
//}
//
//PFX_INLINE void matrix4_set_column_unsafe (pfx_marix4_t* PARAM_IN mat,pfx_index_t index_,
//	const pfx_vector4_t* PARAM_IN column_)
//{
//	PMATRIX_DATA_ (mat,0,index_) = PVECTOR_DATA (column_,0);
//	PMATRIX_DATA_ (mat,1,index_)	= PVECTOR_DATA (column_,1);
//	PMATRIX_DATA_ (mat,2,index_) = PVECTOR_DATA (column_,2);
//	PMATRIX_DATA_ (mat,3,index_) = PVECTOR_DATA (column_,3);
//}

//#define matrix4_get_row_unsafe(MAT,ROW) ((MAT)->m_vec[(ROW)])
//#define matrix4_get_row_unsafe_std matrix4_get_row_unsafe
//#define matrix4_set_row_unsafe(MAT,ROW,VEC) ((MAT)->m_vec[(ROW)] = *(VEC))

//PFX_INLINE pfx_vector4_t matrix4_get_column_unsafe (const pfx_marix4_t* PARAM_IN mat,pfx_index_t index_)
//{
//	pfx_vector4_t return_vec;
//	init_vector4_unsafe (&return_vec,PMATRIX_DATA_ (mat,0,index_),PMATRIX_DATA_ (mat,1,index_),
//		PMATRIX_DATA_ (mat,2,index_),PMATRIX_DATA_ (mat,3,index_));
//	return return_vec;
//}
//


//PFX_INLINE pfx_vector4_t matrix4_get_row_unsafe_std (const pfx_marix4_t* PARAM_IN mat,pfx_index_t index_)
//{
//	pfx_vector4_t return_vec;
//	init_vector4_unsafe_std (&return_vec,PMATRIX_DATA_ (mat,0,index_),PMATRIX_DATA_ (mat,1,index_),
//		PMATRIX_DATA_ (mat,2,index_),PMATRIX_DATA_ (mat,3,index_));
//	return return_vec;
//}
//
//PFX_INLINE void matrix4_set_row_unsafe (pfx_marix4_t* PARAM_IN mat,pfx_index_t index_,
//	const pfx_vector4_t* PARAM_IN row_)
//{
//	PMATRIX_DATA_ (mat,index_,0) = PVECTOR_DATA (row_,0);
//	PMATRIX_DATA_ (mat,index_,1)	= PVECTOR_DATA (row_,1);
//	PMATRIX_DATA_ (mat,index_,2) = PVECTOR_DATA (row_,2);
//	PMATRIX_DATA_ (mat,index_,3) = PVECTOR_DATA (row_,3);
//}
//
//#define matrix4_get_column_unsafe(MAT,COLUMN) ((MAT)->m_vec[(COLUMN)])
//#define matrix4_get_column_unsafe_std matrix4_get_column_unsafe
//#define matrix4_set_column_unsafe(MAT,COLUMN,VEC) ((MAT)->m_vec[(COLUMN)] = *(VEC))
//

PFX_INLINE pfx_vector4_t matrix4_get_column_unsafe_std (const pfx_marix4_t* PARAM_IN mat,pfx_index_t index_)
{
	pfx_vector4_t return_vec;
	init_vector4_unsafe_std (&return_vec,PMATRIX_DATA_ (mat,0,index_),PMATRIX_DATA_ (mat,1,index_),
		PMATRIX_DATA_ (mat,2,index_),PMATRIX_DATA_ (mat,3,index_));
	return return_vec;
}

PFX_INLINE void matrix4_set_column_unsafe (pfx_marix4_t* PARAM_IN mat,pfx_index_t index_,
	const pfx_vector4_t* PARAM_IN column__)
{
	PMATRIX_DATA_ (mat,0,index_) = PVECTOR_DATA (column__,0);
	PMATRIX_DATA_ (mat,1,index_)	= PVECTOR_DATA (column__,1);
	PMATRIX_DATA_ (mat,2,index_) = PVECTOR_DATA (column__,2);
	PMATRIX_DATA_ (mat,3,index_) = PVECTOR_DATA (column__,3);
}

#define matrix4_get_row_unsafe(MAT,ROW) ((MAT)->m_vec[(ROW)])
#define matrix4_get_row_unsafe_std matrix4_get_row_unsafe
#define matrix4_set_row_unsafe(MAT,ROW,VEC) ((MAT)->m_vec[(ROW)] = *(VEC))

#define  matrix4_row_add_vector4_std(MAT,ROW,VEC) {PMATRIX_DATA_(MAT,ROW,0) += PVECTOR_DATA(VEC,0);\
	PMATRIX_DATA_(MAT,ROW,1) += PVECTOR_DATA(VEC,1);\
	PMATRIX_DATA_(MAT,ROW,2) += PVECTOR_DATA(VEC,2);\
	PMATRIX_DATA_(MAT,ROW,3) += PVECTOR_DATA(VEC,3);\
}

#define  matrix4_column_add_vector4_std(MAT,COLUMN,VEC) {PMATRIX_DATA_(MAT,0,COLUMN) += PVECTOR_DATA(VEC,0);\
	PMATRIX_DATA_(MAT,1,COLUMN) += PVECTOR_DATA(VEC,1);\
	PMATRIX_DATA_(MAT,2,COLUMN) += PVECTOR_DATA(VEC,2);\
	PMATRIX_DATA_(MAT,3,COLUMN) += PVECTOR_DATA(VEC,3);\
}

// 矩阵转置
PFX_INLINE pfx_marix4_t* matrix4_transpose_ref_unsafe_std (pfx_marix4_t* PARAM_INOUT mat)
{
	VEC_FLOAT temp;
	
	temp = PMATRIX_DATA (mat,M4_01);
	PMATRIX_DATA (mat,M4_01) = PMATRIX_DATA (mat,M4_10); 
	PMATRIX_DATA (mat,M4_10) = temp;

	temp = PMATRIX_DATA (mat,M4_02);
	PMATRIX_DATA (mat,M4_02) = PMATRIX_DATA (mat,M4_20); 
	PMATRIX_DATA (mat,M4_20) = temp;

	temp = PMATRIX_DATA (mat,M4_03);
	PMATRIX_DATA (mat,M4_03) = PMATRIX_DATA (mat,M4_30); 
	PMATRIX_DATA (mat,M4_30) = temp;

	temp = PMATRIX_DATA (mat,M4_12);
	PMATRIX_DATA (mat,M4_12) = PMATRIX_DATA (mat,M4_21); 
	PMATRIX_DATA (mat,M4_21) = temp; 

	temp = PMATRIX_DATA (mat,M4_13);
	PMATRIX_DATA (mat,M4_13) = PMATRIX_DATA (mat,M4_31); 
	PMATRIX_DATA (mat,M4_31) = temp;

	temp = PMATRIX_DATA (mat,M4_23);
	PMATRIX_DATA (mat,M4_23) = PMATRIX_DATA (mat,M4_32); 
	PMATRIX_DATA (mat,M4_32) = temp;

	return mat;
}

PFX_INLINE pfx_marix4_t matrix4_transpose_unsafe_std (pfx_marix4_t* PARAM_INOUT mat)
{
	pfx_marix4_t result_mat;

	MATRIX_DATA (result_mat,M4_00) = PMATRIX_DATA (mat,M4_00);
	MATRIX_DATA (result_mat,M4_11) = PMATRIX_DATA (mat,M4_11);
	MATRIX_DATA (result_mat,M4_22) = PMATRIX_DATA (mat,M4_22);
	MATRIX_DATA (result_mat,M4_33) = PMATRIX_DATA (mat,M4_33);

	MATRIX_DATA (result_mat,M4_01) = PMATRIX_DATA (mat,M4_10);
	MATRIX_DATA (result_mat,M4_02) = PMATRIX_DATA (mat,M4_20);
	MATRIX_DATA (result_mat,M4_03) = PMATRIX_DATA (mat,M4_30);

	MATRIX_DATA (result_mat,M4_10) = PMATRIX_DATA (mat,M4_01);
	MATRIX_DATA (result_mat,M4_12) = PMATRIX_DATA (mat,M4_21);
	MATRIX_DATA (result_mat,M4_13) = PMATRIX_DATA (mat,M4_31);

	MATRIX_DATA (result_mat,M4_20) = PMATRIX_DATA (mat,M4_02);
	MATRIX_DATA (result_mat,M4_21) = PMATRIX_DATA (mat,M4_12);
	MATRIX_DATA (result_mat,M4_23) = PMATRIX_DATA (mat,M4_32);

	MATRIX_DATA (result_mat,M4_30) = PMATRIX_DATA (mat,M4_03);
	MATRIX_DATA (result_mat,M4_31) = PMATRIX_DATA (mat,M4_13);
	MATRIX_DATA (result_mat,M4_32) = PMATRIX_DATA (mat,M4_23);

	return result_mat;
}

//						1     0    0    0
//				 [	0   cosθ sinθ 0 ]
//						0  -sinθ cosθ 0
//						0     0    0    1
PFX_INLINE pfx_marix4_t* init_rotateX_matrix_ref_opengl_unsafe_std (pfx_marix4_t* PARAM_INOUT mat, VEC_FLOAT radian)
{
	VEC_FLOAT fsin;
	VEC_FLOAT fcos;

	pfx_sincos_std (radian,fsin,fcos);
	init_matrix4_floats_unsafe_std(mat,
														ONE_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT,
														ZERO_FLOAT	,	fcos					,	fsin					,	ZERO_FLOAT,
														ZERO_FLOAT	,	-fsin					,	fcos					,	ZERO_FLOAT,
														ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT);
	return mat;
}
PFX_INLINE pfx_marix4_t* init_rotateX_matrix_ref_directX_unsafe_std (pfx_marix4_t* PARAM_INOUT mat, VEC_FLOAT radian)
{
	return init_rotateX_matrix_ref_opengl_unsafe_std (mat,-radian);
}
PFX_INLINE pfx_marix4_t   opengl_rotateX_matrix_std (VEC_FLOAT radian)
{
	pfx_marix4_t mat;
	init_rotateX_matrix_ref_opengl_unsafe_std (&mat,radian);
	return mat;
}
PFX_INLINE pfx_marix4_t   directX_rotateX_matrix_std (VEC_FLOAT radian)
{
	pfx_marix4_t mat;
	init_rotateX_matrix_ref_directX_unsafe_std (&mat,radian);
	return mat;
}

//						cosθ  0  -sinθ  0
//					 [	0     1    0     0		]
//						sinθ  0   cosθ  0
//						0     0    0     1
PFX_INLINE pfx_marix4_t* init_rotateY_matrix_ref_opengl_unsafe_std (pfx_marix4_t* PARAM_INOUT mat,VEC_FLOAT radian)
{
	VEC_FLOAT fsin;
	VEC_FLOAT fcos;

	pfx_sincos_std (radian,fsin,fcos);
	init_matrix4_floats_unsafe_std(mat,
		fcos					,	ZERO_FLOAT	,	-fsin					,	ZERO_FLOAT,
		ZERO_FLOAT	,	ONE_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT,
		fsin					,	ZERO_FLOAT	,	fcos					,	ZERO_FLOAT,
		ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT);

	return mat;
}
PFX_INLINE pfx_marix4_t* init_rotateY_matrix_ref_directX_unsafe_std (pfx_marix4_t* PARAM_INOUT mat,VEC_FLOAT radian)
{
	return init_rotateY_matrix_ref_opengl_unsafe_std (mat,-radian);
}
PFX_INLINE pfx_marix4_t   opengl_rotateY_matrix_std (VEC_FLOAT radian)
{
	pfx_marix4_t mat;
	init_rotateY_matrix_ref_opengl_unsafe_std (&mat,radian);
	return mat;
}
PFX_INLINE pfx_marix4_t   directX_rotateY_matrix_std (VEC_FLOAT radian)
{
	pfx_marix4_t mat;
	init_rotateY_matrix_ref_directX_unsafe_std (&mat,radian);
	return mat;
}

//						cosθ sinθ 0  0
//					 [	-sinθ cosθ 0  0 ]
//							0      0   1  0
//							0      0   0  1
//  
PFX_INLINE pfx_marix4_t* init_rotateZ_matrix_ref_opengl_unsafe_std (pfx_marix4_t* PARAM_INOUT mat,VEC_FLOAT radian)
{
	VEC_FLOAT fsin;
	VEC_FLOAT fcos;

	pfx_sincos_std (radian,fsin,fcos);
	init_matrix4_floats_unsafe_std(mat,
		fcos					,	fsin					,	ZERO_FLOAT	,	ZERO_FLOAT,
		-fsin					,	fcos					,	ZERO_FLOAT	,	ZERO_FLOAT,
		ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT	,	ZERO_FLOAT,
		ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT);

	return mat;
}
PFX_INLINE pfx_marix4_t* init_rotateZ_matrix_ref_directX_unsafe_std (pfx_marix4_t* PARAM_INOUT mat,VEC_FLOAT radian)
{
	return init_rotateZ_matrix_ref_opengl_unsafe_std (mat,-radian);
}
PFX_INLINE pfx_marix4_t   opengl_rotateZ_matrix_std (VEC_FLOAT radian)
{
	pfx_marix4_t mat;
	init_rotateZ_matrix_ref_opengl_unsafe_std (&mat,radian);
	return mat;
}
PFX_INLINE pfx_marix4_t   directX_rotateZ_matrix_std (VEC_FLOAT radian)
{
	pfx_marix4_t mat;
	init_rotateZ_matrix_ref_directX_unsafe_std (&mat,radian);
	return mat;
}

//// 任意轴线q(q1,q2,q3),求向量p(x,y,z)饶q旋转变换后新向量p'
//// p' = p * T
//// p'(x',y'z',1),p(x,y,z,1)为向量p',p的4D齐次坐标表示
//// T为旋转矩阵,c为旋转角度的余弦，s为旋转角度的正弦值，t = 1 - c，
////
////       t*q1*q1 + c,    t*q1*q2 + s*q3, t*q1*q3 - s*q2 , 0 
////       t*q1*q2 - s*q3, t*q2*q2 + c,    t*q2*q3 + s*q1,  0
//// T = [ t*q1*q3 + s*q2, t*q2*q3 - s*q1, t*q3*q3 + c,     0 ]
////       0,              0,              0,               1

PFX_INLINE pfx_marix4_t* init_rotate_matrix_ref_opengl_unsafe_std (pfx_marix4_t* PARAM_INOUT mat,
	VEC_FLOAT vecx,VEC_FLOAT vecy,VEC_FLOAT vecz, 
	VEC_FLOAT radian)
{
	VEC_FLOAT fsin;
	VEC_FLOAT fcos;
	VEC_FLOAT ftemp;
	pfx_sincos_std (radian,fsin,fcos);
	ftemp = ONE_FLOAT - fcos;
	init_matrix4_floats_unsafe_std(mat,
		fcos + VEC_FLOAT_MUL (VEC_FLOAT_MUL (vecx,vecx),ftemp)	, 
		VEC_FLOAT_MUL (VEC_FLOAT_MUL (vecx,vecy)	,ftemp) + VEC_FLOAT_MUL (vecz,fsin)	,	
		VEC_FLOAT_MUL (VEC_FLOAT_MUL (vecx,vecz),ftemp) - VEC_FLOAT_MUL (vecy,fsin)	,	
		ZERO_FLOAT,

		VEC_FLOAT_MUL (VEC_FLOAT_MUL (vecx,vecy),ftemp) - VEC_FLOAT_MUL (vecz,fsin),
		VEC_FLOAT_MUL (VEC_FLOAT_MUL (vecy,vecy),ftemp) + fcos,
		VEC_FLOAT_MUL (VEC_FLOAT_MUL (vecy,vecz),ftemp) + VEC_FLOAT_MUL (vecx,fsin),
		ZERO_FLOAT,

		VEC_FLOAT_MUL (VEC_FLOAT_MUL (vecx,vecz),ftemp) + VEC_FLOAT_MUL (vecy,fsin),
		VEC_FLOAT_MUL (VEC_FLOAT_MUL (vecy,vecz),ftemp) - VEC_FLOAT_MUL (vecx,fsin),
		VEC_FLOAT_MUL (VEC_FLOAT_MUL (vecz,vecz),ftemp) + fcos,
		ZERO_FLOAT,

		ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT);
	return mat;
}

PFX_INLINE pfx_marix4_t* init_rotate_matrix_ref_directX_unsafe_std (pfx_marix4_t* PARAM_INOUT mat,
	VEC_FLOAT vecx,VEC_FLOAT vecy,VEC_FLOAT vecz, 
	VEC_FLOAT radian)
{
	return init_rotate_matrix_ref_directX_unsafe_std (mat,vecx,vecy,vecz,-radian);
}

PFX_INLINE pfx_marix4_t opengl_rotate_matrix_std (VEC_FLOAT vecx,VEC_FLOAT vecy,VEC_FLOAT vecz, 
	VEC_FLOAT radian)
{
	pfx_marix4_t mat;
	init_rotate_matrix_ref_opengl_unsafe_std (&mat,vecx,vecy,vecz,radian);
	return mat;
}

PFX_INLINE pfx_marix4_t directX_rotate_matrix_std (VEC_FLOAT vecx,VEC_FLOAT vecy,VEC_FLOAT vecz, 
	VEC_FLOAT radian)
{
	pfx_marix4_t mat;
	init_rotate_matrix_ref_directX_unsafe_std (&mat,vecx,vecy,vecz,radian);
	return mat;
}

//////////////////////////////////////////////////////////////////////////
//				X	,	0	,	0	,	0
//			[	0	,	Y	,	0	,	0	]
//				0	,	0	,	Z	,	0
//				0	,	0	,	0	,	1
PFX_INLINE pfx_marix4_t* init_scale_matrix_ref_unsafe_std (pfx_marix4_t* PARAM_INOUT mat,
	VEC_FLOAT fx,VEC_FLOAT fy,VEC_FLOAT fz)
{
	init_matrix4_floats_unsafe_std(mat,
		fx						,	ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT,
		ZERO_FLOAT	,	fy						,	ZERO_FLOAT	,	ZERO_FLOAT,
		ZERO_FLOAT	,	ZERO_FLOAT	,	fz						,	ZERO_FLOAT,
		ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT);
	return mat;
}
PFX_INLINE pfx_marix4_t scale_matrix_std (VEC_FLOAT fx,VEC_FLOAT fy,VEC_FLOAT fz)
{
	pfx_marix4_t mat;
	init_scale_matrix_ref_unsafe_std (&mat,fx,fy,fz);
	return mat;
}

//////////////////////////////////////////////////////////////////////////
//				1	,	0	,	0	,	0
//			[	0	,	1	,	0	,	0	]
//				0	,	0	,	1	,	0
//				X	,	Y	,	Z	,	1
PFX_INLINE pfx_marix4_t* init_translation_matrix_ref_unsafe_std (pfx_marix4_t* PARAM_INOUT mat,
	VEC_FLOAT fx,VEC_FLOAT fy,VEC_FLOAT fz)
{
	init_matrix4_floats_unsafe_std(mat,
		ONE_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT,
		ZERO_FLOAT	,	ONE_FLOAT	,	ZERO_FLOAT	,	ZERO_FLOAT,
		ZERO_FLOAT	,	ZERO_FLOAT	,	ONE_FLOAT	,	ZERO_FLOAT,
		fx						,	fy						,	fz						,	ONE_FLOAT);
	return mat;
}
PFX_INLINE pfx_marix4_t translation_matrix_std (VEC_FLOAT fx,VEC_FLOAT fy,VEC_FLOAT fz)
{
	pfx_marix4_t mat;
	init_scale_matrix_ref_unsafe_std (&mat,fx,fy,fz);
	return mat;
}
//////////////////////////////////////////////////////////////////////////
//
//				1	,	0	,	0	,	0
//			[	0	,	1	,	0	,	0	] * MAT
//				0	,	0	,	1	,	0
//				X	,	Y	,	Z	,	1
PFX_INLINE pfx_marix4_t* matrix4_post_translation_ref_unsafe_std (pfx_marix4_t* PARAM_INOUT mat,
	VEC_FLOAT fx,VEC_FLOAT fy,VEC_FLOAT fz)
{
	//			col(3) += fx * col(0) + fy * col(1) + fz * col(2);
	pfx_vector4_t column;
	column = matrix4_get_column_unsafe_std (mat,0);
	column = vector4_mul_float_unsafe_std (&column,fx);
	matrix4_column_add_vector4_std (mat,3,&column);

	column = matrix4_get_column_unsafe_std (mat,1);
	column = vector4_mul_float_unsafe_std (&column,fy);
	matrix4_column_add_vector4_std (mat,3,&column);

	column = matrix4_get_column_unsafe_std (mat,2);
	column = vector4_mul_float_unsafe_std (&column,fz);
	matrix4_column_add_vector4_std (mat,3,&column);

	return mat;
}
PFX_INLINE pfx_marix4_t matrix4_post_translation_unsafe_std (const pfx_marix4_t* PARAM_IN mat,
	VEC_FLOAT fx,VEC_FLOAT fy,VEC_FLOAT fz)
{
	//			col(3) += fx * col(0) + fy * col(1) + fz * col(2);
	pfx_marix4_t mat_result;
	pfx_vector4_t column;
	column = matrix4_get_column_unsafe_std (mat,3);
	matrix4_set_column_unsafe (&mat_result,3,&column);

	column = matrix4_get_column_unsafe_std (mat,0);
	column = vector4_mul_float_unsafe_std (&column,fx);
	matrix4_column_add_vector4_std (&mat_result,3,&column);

	column = matrix4_get_column_unsafe_std (mat,1);
	column = vector4_mul_float_unsafe_std (&column,fy);
	matrix4_column_add_vector4_std (&mat_result,3,&column);

	column = matrix4_get_column_unsafe_std (mat,2);
	column = vector4_mul_float_unsafe_std (&column,fz);
	matrix4_column_add_vector4_std (&mat_result,3,&column);

	return mat_result;
}
//////////////////////////////////////////////////////////////////////////
//
//							1	,	0	,	0	,	0
//		MAT	*	[	0	,	1	,	0	,	0	] 
//							0	,	0	,	1	,	0
//							X	,	Y	,	Z	,	1
PFX_INLINE pfx_marix4_t* matrix4_pre_translation_ref_unsafe_std (pfx_marix4_t* PARAM_INOUT mat,
	VEC_FLOAT fx,VEC_FLOAT fy,VEC_FLOAT fz)
{
	//			row(0) += fx * row(3);
	//			row(1) += fy * row(3);
	//			row(2) += fz * row(3);
	pfx_vector4_t row3;
	pfx_vector4_t temp;
	row3 = matrix4_get_row_unsafe_std (mat,3);
	temp = vector4_mul_float_unsafe_std (&row3,fx);
	matrix4_row_add_vector4_std (mat,0,&temp);

	temp = vector4_mul_float_unsafe_std (&row3,fy);
	matrix4_row_add_vector4_std (mat,1,&temp);

	temp = vector4_mul_float_unsafe_std (&row3,fz);
	matrix4_row_add_vector4_std (mat,2,&temp);

	return mat;
}
PFX_INLINE pfx_marix4_t matrix4_pre_translation_unsafe_std (const pfx_marix4_t* PARAM_IN mat,
	VEC_FLOAT fx,VEC_FLOAT fy,VEC_FLOAT fz)
{
	pfx_marix4_t mat_result;
	init_matrix4_by_matrix4_unsafe_std (&mat_result,mat);

	return mat_result;
}



//////////////////////////////////////////////////////////////////////////
PFX_INLINE pfx_marix4_t* matrix4_mul_float_ref_unsafe_std (pfx_marix4_t* PARAM_INOUT mat,VEC_FLOAT fval)
{
	vector4_mul_float_ref_unsafe_std (&(matrix4_get_row_unsafe_std (mat,0)),fval);
	vector4_mul_float_ref_unsafe_std (&(matrix4_get_row_unsafe_std (mat,1)),fval);
	vector4_mul_float_ref_unsafe_std (&(matrix4_get_row_unsafe_std (mat,2)),fval);
	vector4_mul_float_ref_unsafe_std (&(matrix4_get_row_unsafe_std (mat,3)),fval);
	return mat;
}
PFX_INLINE pfx_marix4_t matrix4_mul_float_unsafe_std (const pfx_marix4_t* PARAM_IN mat,VEC_FLOAT fval)
{
	pfx_marix4_t mat_result;
	matrix4_get_row_unsafe_std(&mat_result,0) = vector4_mul_float_unsafe_std (&(matrix4_get_row_unsafe_std(mat,0)),fval);
	matrix4_get_row_unsafe_std(&mat_result,1) = vector4_mul_float_unsafe_std (&(matrix4_get_row_unsafe_std(mat,1)),fval);
	matrix4_get_row_unsafe_std(&mat_result,2) = vector4_mul_float_unsafe_std (&(matrix4_get_row_unsafe_std(mat,2)),fval);
	matrix4_get_row_unsafe_std(&mat_result,3) = vector4_mul_float_unsafe_std (&(matrix4_get_row_unsafe_std(mat,3)),fval);
	return mat_result;
}

//////////////////////////////////////////////////////////////////////////
#define MARIXT4_MUL_MARIXT4_ITEM_(mat1,mat2,row,column,index_) (VEC_FLOAT_MUL(PMATRIX_DATA_(mat1,row,index_),PMATRIX_DATA_(mat2,index_,column)))
#define MARIXT4_MUL_MARIXT4_ITEM(mat1,mat2,row,column) (MARIXT4_MUL_MARIXT4_ITEM_(mat1,mat2,row,column,0) + \
	MARIXT4_MUL_MARIXT4_ITEM_(mat1,mat2,row,column,1) + MARIXT4_MUL_MARIXT4_ITEM_(mat1,mat2,row,column,2) + MARIXT4_MUL_MARIXT4_ITEM_(mat1,mat2,row,column,3))

PFX_INLINE pfx_marix4_t* _matrix4_mul_matrix4_ref_unsafe_std (pfx_marix4_t* PARAM_INOUT mat,
	const pfx_marix4_t* mat1, const pfx_marix4_t* mat2,pfx_marix2_t* PARAM_INOUT temp)
{
	//init_marix2_floats_unsafe_std (,)
	VEC_FLOAT tempfloat[7];

	//////////////////////////////////////////////////////////////////////////
	init_matrix2_floats_unsafe_std (&temp[7], 
	(PMATRIX_DATA_(mat1,0,0)+PMATRIX_DATA_(mat1,2,2)) , (PMATRIX_DATA_(mat1,0,1)+PMATRIX_DATA_(mat1,2,3)),
	(PMATRIX_DATA_(mat1,1,0)+PMATRIX_DATA_(mat1,3,2)) , (PMATRIX_DATA_(mat1,1,1)+PMATRIX_DATA_(mat1,3,3)));
	
	init_matrix2_floats_unsafe_std (&temp[8], 
		(PMATRIX_DATA_(mat2,0,0)+PMATRIX_DATA_(mat2,2,2)) , (PMATRIX_DATA_(mat2,0,1)+PMATRIX_DATA_(mat2,2,3)),
		(PMATRIX_DATA_(mat2,1,0)+PMATRIX_DATA_(mat2,3,2)) , (PMATRIX_DATA_(mat2,1,1)+PMATRIX_DATA_(mat2,3,3)));

	_matrix2_mul_matrix2_ref_unsafe_std (&temp[0],&temp[7],&temp[8],tempfloat);

	//////////////////////////////////////////////////////////////////////////
	init_matrix2_floats_unsafe_std (&temp[7], 
		(PMATRIX_DATA_(mat1,2,0)+PMATRIX_DATA_(mat1,2,2)) , (PMATRIX_DATA_(mat1,2,1)+PMATRIX_DATA_(mat1,2,3)),
		(PMATRIX_DATA_(mat1,3,0)+PMATRIX_DATA_(mat1,3,2)) , (PMATRIX_DATA_(mat1,3,1)+PMATRIX_DATA_(mat1,3,3)));

	init_matrix2_floats_unsafe_std (&temp[8], 
		(PMATRIX_DATA_(mat2,0,0)) , (PMATRIX_DATA_(mat2,0,1)),
		(PMATRIX_DATA_(mat2,1,0)) , (PMATRIX_DATA_(mat2,1,1)));

	_matrix2_mul_matrix2_ref_unsafe_std (&temp[1],&temp[7],&temp[8],tempfloat);
	//////////////////////////////////////////////////////////////////////////
	init_matrix2_floats_unsafe_std (&temp[7], 
		(PMATRIX_DATA_(mat1,0,0)) , (PMATRIX_DATA_(mat1,0,1)),
		(PMATRIX_DATA_(mat1,1,0)) , (PMATRIX_DATA_(mat1,1,1)));

	init_matrix2_floats_unsafe_std (&temp[8], 
		(PMATRIX_DATA_(mat2,0,2)-PMATRIX_DATA_(mat2,2,2)) , (PMATRIX_DATA_(mat2,0,3)-PMATRIX_DATA_(mat2,2,3)),
		(PMATRIX_DATA_(mat2,1,2)-PMATRIX_DATA_(mat2,3,2)) , (PMATRIX_DATA_(mat2,1,3)-PMATRIX_DATA_(mat2,3,3)));

	_matrix2_mul_matrix2_ref_unsafe_std (&temp[2],&temp[7],&temp[8],tempfloat);
	//////////////////////////////////////////////////////////////////////////
	init_matrix2_floats_unsafe_std (&temp[7], 
		(PMATRIX_DATA_(mat1,2,2)) , (PMATRIX_DATA_(mat1,2,3)),
		(PMATRIX_DATA_(mat1,3,2)) , (PMATRIX_DATA_(mat1,3,3)));

	init_matrix2_floats_unsafe_std (&temp[8], 
		(PMATRIX_DATA_(mat2,2,0)-PMATRIX_DATA_(mat2,0,0)) , (PMATRIX_DATA_(mat2,2,1)-PMATRIX_DATA_(mat2,0,1)),
		(PMATRIX_DATA_(mat2,3,0)-PMATRIX_DATA_(mat2,1,0)) , (PMATRIX_DATA_(mat2,3,1)-PMATRIX_DATA_(mat2,1,1)));

	_matrix2_mul_matrix2_ref_unsafe_std (&temp[3],&temp[7],&temp[8],tempfloat);
	//////////////////////////////////////////////////////////////////////////
	init_matrix2_floats_unsafe_std (&temp[7], 
		(PMATRIX_DATA_(mat1,0,0)+PMATRIX_DATA_(mat1,0,2)) , (PMATRIX_DATA_(mat1,0,1)+PMATRIX_DATA_(mat1,0,3)),
		(PMATRIX_DATA_(mat1,1,0)+PMATRIX_DATA_(mat1,1,2)) , (PMATRIX_DATA_(mat1,1,1)+PMATRIX_DATA_(mat1,1,3)));

	init_matrix2_floats_unsafe_std (&temp[8], 
		(PMATRIX_DATA_(mat2,2,2)) , (PMATRIX_DATA_(mat2,2,3)),
		(PMATRIX_DATA_(mat2,3,2)) , (PMATRIX_DATA_(mat2,3,3)));

	_matrix2_mul_matrix2_ref_unsafe_std (&temp[4],&temp[7],&temp[8],tempfloat);
	//////////////////////////////////////////////////////////////////////////
	init_matrix2_floats_unsafe_std (&temp[7], 
		(PMATRIX_DATA_(mat1,2,0)-PMATRIX_DATA_(mat1,0,0)) , (PMATRIX_DATA_(mat1,2,1)-PMATRIX_DATA_(mat1,0,1)),
		(PMATRIX_DATA_(mat1,3,0)-PMATRIX_DATA_(mat1,1,0)) , (PMATRIX_DATA_(mat1,3,1)-PMATRIX_DATA_(mat1,1,1)));

	init_matrix2_floats_unsafe_std (&temp[8], 
		(PMATRIX_DATA_(mat2,0,0)+PMATRIX_DATA_(mat2,0,2)) , (PMATRIX_DATA_(mat2,0,1)+PMATRIX_DATA_(mat2,0,3)),
		(PMATRIX_DATA_(mat2,1,0)+PMATRIX_DATA_(mat2,1,2)) , (PMATRIX_DATA_(mat2,1,1)+PMATRIX_DATA_(mat2,1,3)));

	_matrix2_mul_matrix2_ref_unsafe_std (&temp[5],&temp[7],&temp[8],tempfloat);
	//////////////////////////////////////////////////////////////////////////
	init_matrix2_floats_unsafe_std (&temp[7], 
		(PMATRIX_DATA_(mat1,0,2)-PMATRIX_DATA_(mat1,2,2)) , (PMATRIX_DATA_(mat1,0,3)-PMATRIX_DATA_(mat1,2,3)),
		(PMATRIX_DATA_(mat1,1,2)-PMATRIX_DATA_(mat1,3,2)) , (PMATRIX_DATA_(mat1,1,3)-PMATRIX_DATA_(mat1,3,3)));

	init_matrix2_floats_unsafe_std (&temp[8], 
		(PMATRIX_DATA_(mat2,2,0)+PMATRIX_DATA_(mat2,2,2)) , (PMATRIX_DATA_(mat2,2,1)+PMATRIX_DATA_(mat2,2,3)),
		(PMATRIX_DATA_(mat2,3,0)+PMATRIX_DATA_(mat2,3,2)) , (PMATRIX_DATA_(mat2,3,1)+PMATRIX_DATA_(mat2,3,3)));

	_matrix2_mul_matrix2_ref_unsafe_std (&temp[5],&temp[7],&temp[8],tempfloat);
	//////////////////////////////////////////////////////////////////////////
	PMATRIX_DATA_ (mat,0,0) = MATRIX_DATA_ (temp[0],0,0) + MATRIX_DATA_ (temp[3],0,0) 
		- MATRIX_DATA_(temp[4],0,0) + MATRIX_DATA_ (temp[6],0,0);
	PMATRIX_DATA_ (mat,0,1) = MATRIX_DATA_ (temp[0],0,1) + MATRIX_DATA_ (temp[3],0,1) 
		- MATRIX_DATA_(temp[4],0,1) + MATRIX_DATA_ (temp[6],0,1);
	PMATRIX_DATA_ (mat,1,0) = MATRIX_DATA_ (temp[0],1,0) + MATRIX_DATA_ (temp[3],1,0) 
		- MATRIX_DATA_(temp[4],1,0) + MATRIX_DATA_ (temp[6],1,0);
	PMATRIX_DATA_ (mat,1,1) = MATRIX_DATA_ (temp[0],1,1) + MATRIX_DATA_ (temp[3],1,1) 
		- MATRIX_DATA_(temp[4],1,1) + MATRIX_DATA_ (temp[6],1,1);

	//////////////////////////////////////////////////////////////////////////
	PMATRIX_DATA_ (mat,0,2) = MATRIX_DATA_ (temp[2],0,0) + MATRIX_DATA_ (temp[4],0,0);
	PMATRIX_DATA_ (mat,0,3) = MATRIX_DATA_ (temp[2],0,1) + MATRIX_DATA_ (temp[4],0,1);
	PMATRIX_DATA_ (mat,1,2) = MATRIX_DATA_ (temp[2],1,0) + MATRIX_DATA_ (temp[4],1,0);
	PMATRIX_DATA_ (mat,1,3) = MATRIX_DATA_ (temp[2],1,1) + MATRIX_DATA_ (temp[4],1,1);

	//////////////////////////////////////////////////////////////////////////

	PMATRIX_DATA_ (mat,2,0) = MATRIX_DATA_ (temp[1],0,0) + MATRIX_DATA_ (temp[3],0,0);
	PMATRIX_DATA_ (mat,2,1) = MATRIX_DATA_ (temp[1],0,1) + MATRIX_DATA_ (temp[3],0,1);
	PMATRIX_DATA_ (mat,3,0) = MATRIX_DATA_ (temp[1],1,0) + MATRIX_DATA_ (temp[3],1,0);
	PMATRIX_DATA_ (mat,3,1) = MATRIX_DATA_ (temp[1],1,1) + MATRIX_DATA_ (temp[3],1,1);

	//////////////////////////////////////////////////////////////////////////
	PMATRIX_DATA_ (mat,2,2) = MATRIX_DATA_ (temp[0],0,0) - MATRIX_DATA_ (temp[1],0,0) 
		+ MATRIX_DATA_(temp[2],0,0) + MATRIX_DATA_ (temp[5],0,0);
	PMATRIX_DATA_ (mat,2,3) = MATRIX_DATA_ (temp[0],0,1) - MATRIX_DATA_ (temp[1],0,1) 
		+ MATRIX_DATA_(temp[2],0,1) + MATRIX_DATA_ (temp[5],0,1);
	PMATRIX_DATA_ (mat,3,2) = MATRIX_DATA_ (temp[0],1,0) - MATRIX_DATA_ (temp[1],1,0) 
		+ MATRIX_DATA_(temp[2],1,0) + MATRIX_DATA_ (temp[5],1,0);
	PMATRIX_DATA_ (mat,3,3) = MATRIX_DATA_ (temp[0],1,1) - MATRIX_DATA_ (temp[1],1,1) 
		+ MATRIX_DATA_(temp[2],1,1) + MATRIX_DATA_ (temp[5],1,1);

	return mat;
}

PFX_INLINE pfx_marix4_t matrix4_mul_matrix4_unsafe_std (const pfx_marix4_t* PARAM_IN mat,
	const pfx_marix4_t* PARAM_IN multimat)
{
	pfx_marix4_t mat_result;
	// 定义求法
	//MATRIX_DATA_ (mat_result,0,0) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,0,0);
	//MATRIX_DATA_ (mat_result,0,1) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,0,1);
	//MATRIX_DATA_ (mat_result,0,2) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,0,2);
	//MATRIX_DATA_ (mat_result,0,3) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,0,3);

	//MATRIX_DATA_ (mat_result,1,0) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,1,0);
	//MATRIX_DATA_ (mat_result,1,1) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,1,1);
	//MATRIX_DATA_ (mat_result,1,2) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,1,2);
	//MATRIX_DATA_ (mat_result,1,3) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,1,3);

	//MATRIX_DATA_ (mat_result,2,0) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,2,0);
	//MATRIX_DATA_ (mat_result,2,1) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,2,1);
	//MATRIX_DATA_ (mat_result,2,2) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,2,2);
	//MATRIX_DATA_ (mat_result,2,3) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,2,3);

	//MATRIX_DATA_ (mat_result,3,0) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,3,0);
	//MATRIX_DATA_ (mat_result,3,1) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,3,1);
	//MATRIX_DATA_ (mat_result,3,2) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,3,2);
	//MATRIX_DATA_ (mat_result,3,3) = MARIXT4_MUL_MARIXT4_ITEM (mat,multimat,3,3);

	// v.斯特拉森 (V.Strassen)法
	pfx_marix2_t temp[9];
	_matrix4_mul_matrix4_ref_unsafe_std (&mat_result,
		mat, multimat,temp);

	return mat_result;
}

//  4*1矩阵 X 1*4矩阵 = 4*4矩阵
PFX_INLINE pfx_marix4_t* row_vector4_mul_column_vector4_unsafe_std (const pfx_vector4_t* PARAM_IN vec_row,
	const pfx_vector4_t* PARAM_IN vec_column,
	pfx_marix4_t* PARAM_INOUT mat_result)
{
	PMATRIX_DATA (mat_result,M4_00) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,0),PVECTOR_DATA(vec_column,0));
	PMATRIX_DATA (mat_result,M4_01) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,0),PVECTOR_DATA(vec_column,1));
	PMATRIX_DATA (mat_result,M4_02) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,0),PVECTOR_DATA(vec_column,2));
	PMATRIX_DATA (mat_result,M4_03) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,0),PVECTOR_DATA(vec_column,3));

	PMATRIX_DATA (mat_result,M4_10) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,1),PVECTOR_DATA(vec_column,0));
	PMATRIX_DATA (mat_result,M4_11) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,1),PVECTOR_DATA(vec_column,1));
	PMATRIX_DATA (mat_result,M4_12) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,1),PVECTOR_DATA(vec_column,2));
	PMATRIX_DATA (mat_result,M4_13) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,1),PVECTOR_DATA(vec_column,3));

	PMATRIX_DATA (mat_result,M4_20) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,2),PVECTOR_DATA(vec_column,0));
	PMATRIX_DATA (mat_result,M4_21) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,2),PVECTOR_DATA(vec_column,1));
	PMATRIX_DATA (mat_result,M4_22) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,2),PVECTOR_DATA(vec_column,2));
	PMATRIX_DATA (mat_result,M4_23) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,2),PVECTOR_DATA(vec_column,3));

	PMATRIX_DATA (mat_result,M4_30) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,3),PVECTOR_DATA(vec_column,0));
	PMATRIX_DATA (mat_result,M4_31) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,3),PVECTOR_DATA(vec_column,1));
	PMATRIX_DATA (mat_result,M4_32) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,3),PVECTOR_DATA(vec_column,2));
	PMATRIX_DATA (mat_result,M4_33) = VEC_FLOAT_MUL (PVECTOR_DATA(vec_row,3),PVECTOR_DATA(vec_column,3));

	return mat_result;
}
// 1*4矩阵 X 4*4矩阵 = 1*4矩阵
PFX_INLINE pfx_vector4_t* vector4_mul_matrix4_ref_unsafe_std (pfx_vector4_t* PARAM_INOUT vec,
	const pfx_marix4_t* PARAM_IN mat)
{
	pfx_vector4_t temp_column;
	temp_column = matrix4_get_column_unsafe_std (mat,0);
	vector4_mul_float_ref_unsafe (&temp_column,PVECTOR_DATA (vec,0));
	PVECTOR_DATA (vec,0) = VECTOR4_DATA_SUM (temp_column);

	temp_column = matrix4_get_column_unsafe_std (mat,1);
	vector4_mul_float_ref_unsafe (&temp_column,PVECTOR_DATA (vec,1));
	PVECTOR_DATA (vec,1) = VECTOR4_DATA_SUM (temp_column);

	temp_column = matrix4_get_column_unsafe_std (mat,2);
	vector4_mul_float_ref_unsafe (&temp_column,PVECTOR_DATA (vec,2));
	PVECTOR_DATA (vec,2) = VECTOR4_DATA_SUM (temp_column);

	temp_column = matrix4_get_column_unsafe_std (mat,3);
	vector4_mul_float_ref_unsafe (&temp_column,PVECTOR_DATA (vec,3));
	PVECTOR_DATA (vec,3) = VECTOR4_DATA_SUM (temp_column);

	return vec;
}

PFX_INLINE pfx_vector4_t vector4_mul_matrix4_unsafe_std (const pfx_vector4_t* PARAM_IN vec,
	const pfx_marix4_t* PARAM_IN mat)
{
	pfx_vector4_t vec_result;

	pfx_vector4_t temp_column;
	temp_column = matrix4_get_column_unsafe_std (mat,0);
	vector4_mul_float_ref_unsafe (&temp_column,PVECTOR_DATA (vec,0));
	VECTOR_DATA (vec_result,0) = VECTOR4_DATA_SUM (temp_column);

	temp_column = matrix4_get_column_unsafe_std (mat,1);
	vector4_mul_float_ref_unsafe (&temp_column,PVECTOR_DATA (vec,1));
	VECTOR_DATA (vec_result,1) = VECTOR4_DATA_SUM (temp_column);

	temp_column = matrix4_get_column_unsafe_std (mat,2);
	vector4_mul_float_ref_unsafe (&temp_column,PVECTOR_DATA (vec,2));
	VECTOR_DATA (vec_result,2) = VECTOR4_DATA_SUM (temp_column);

	temp_column = matrix4_get_column_unsafe_std (mat,3);
	vector4_mul_float_ref_unsafe (&temp_column,PVECTOR_DATA (vec,3));
	VECTOR_DATA (vec_result,3) = VECTOR4_DATA_SUM (temp_column);

	return vec_result;
}

// 4*4矩阵 X 4*1矩阵 = 4*1矩阵
PFX_INLINE pfx_vector4_t matrix4_mul_vector4_unsafe_std (const pfx_marix4_t* PARAM_IN mat,
	const pfx_vector4_t* PARAM_IN vec)
{
	pfx_vector4_t vec_result;

	pfx_vector4_t temp_column;
	temp_column = matrix4_get_row_unsafe_std (mat,0);
	vector4_mul_vector4_ref_unsafe (&temp_column,vec);
	VECTOR_DATA (vec_result,0) = VECTOR4_DATA_SUM (temp_column);

	temp_column = matrix4_get_row_unsafe_std (mat,1);
	vector4_mul_vector4_ref_unsafe (&temp_column,vec);
	VECTOR_DATA (vec_result,1) = VECTOR4_DATA_SUM (temp_column);

	temp_column = matrix4_get_row_unsafe_std (mat,2);
	vector4_mul_vector4_ref_unsafe (&temp_column,vec);
	VECTOR_DATA (vec_result,2) = VECTOR4_DATA_SUM (temp_column);

	temp_column = matrix4_get_row_unsafe_std (mat,3);
	vector4_mul_vector4_ref_unsafe (&temp_column,vec);
	VECTOR_DATA (vec_result,3) = VECTOR4_DATA_SUM (temp_column);

	return vec_result;
}

#define MATRIX4_MUL_SUBS_ITEM(MAT,ITEM1,ITEM2,ITEM3,ITEM4) (VEC_FLOAT_MUL (PMATRIX_DATA(MAT,ITEM1),PMATRIX_DATA(MAT,ITEM2))-VEC_FLOAT_MUL(PMATRIX_DATA(MAT,ITEM3),PMATRIX_DATA(MAT,ITEM4)))
//////////////////////////////////////////////////////////////////////////
//		
//		[ A,C ]
//		   0,1
//		
PFX_INLINE pfx_result_t	matrix4_inverse_unsafe_std (const pfx_marix4_t* PARAM_IN mat,
	pfx_marix4_t* PARAM_INOUT inverse_mat)
{
	VEC_FLOAT det_1;
	VEC_FLOAT pos;
	VEC_FLOAT neg;
	VEC_FLOAT temp;
	pos = ZERO_FLOAT;
	neg = ZERO_FLOAT;
	//
	//求行列式 A
	//				A1,A2,A3		
	//			[	A4,A5,A6	]
	//				A7,A8,A9	
	// 的值
	temp = VEC_FLOAT_MUL ( VEC_FLOAT_MUL (PMATRIX_DATA(mat,M4_00),PMATRIX_DATA(mat,M4_11)), 
		PMATRIX_DATA (mat,M4_22) );
	// 目的在于减少积累误差
	if (temp >= 0){pos += temp;}else{neg += temp;}

	temp = VEC_FLOAT_MUL ( VEC_FLOAT_MUL (PMATRIX_DATA(mat,M4_01),PMATRIX_DATA(mat,M4_12)), 
		PMATRIX_DATA (mat,M4_20) );
	if (temp >= 0){pos += temp;}else{neg += temp;}

	temp = VEC_FLOAT_MUL ( VEC_FLOAT_MUL (PMATRIX_DATA(mat,M4_02),PMATRIX_DATA(mat,M4_10)), 
		PMATRIX_DATA (mat,M4_21) );
	if (temp >= 0){pos += temp;}else{neg += temp;}

	temp = VEC_FLOAT_MUL ( VEC_FLOAT_MUL (-PMATRIX_DATA(mat,M4_02),PMATRIX_DATA(mat,M4_11)), 
		PMATRIX_DATA (mat,M4_20) );
	if (temp >= 0){pos += temp;}else{neg += temp;}

	temp = VEC_FLOAT_MUL ( VEC_FLOAT_MUL (-PMATRIX_DATA(mat,M4_01),PMATRIX_DATA(mat,M4_10)), 
		PMATRIX_DATA (mat,M4_22) );
	if (temp >= 0){pos += temp;}else{neg += temp;}

	temp = VEC_FLOAT_MUL ( VEC_FLOAT_MUL (-PMATRIX_DATA(mat,M4_00),PMATRIX_DATA(mat,M4_12)), 
		PMATRIX_DATA (mat,M4_21) );
	if (temp >= 0){pos += temp;}else{neg += temp;}

	det_1 = pos + neg;

	// det ([F,G]) = det (F) det (G)
	if (0 == VEC_FLOAT_CMP (det_1,ZERO_FLOAT))
	{
		// n * n矩阵当且仅当 det (M) == 0的时候不可逆
		return PFX_STATUS_FAIL;
	}
	// A 可逆 3* 3可逆阵公式 inverse(A) = 1/det(A) * adj(A)
	//////////////////////////////////////////////////////////////////////////
	PMATRIX_DATA(inverse_mat,M4_00) = VEC_FLOAT_DIV (MATRIX4_MUL_SUBS_ITEM(mat,M4_11,M4_22,M4_12,M4_21),det_1);
	PMATRIX_DATA(inverse_mat,M4_10) = VEC_FLOAT_DIV (MATRIX4_MUL_SUBS_ITEM(mat,M4_12,M4_20,M4_10,M4_22),det_1);
	PMATRIX_DATA(inverse_mat,M4_20) = VEC_FLOAT_DIV (MATRIX4_MUL_SUBS_ITEM(mat,M4_10,M4_21,M4_11,M4_20),det_1);
	
	PMATRIX_DATA(inverse_mat,M4_01) = VEC_FLOAT_DIV (MATRIX4_MUL_SUBS_ITEM(mat,M4_02,M4_21,M4_01,M4_22),det_1);
	PMATRIX_DATA(inverse_mat,M4_11) = VEC_FLOAT_DIV (MATRIX4_MUL_SUBS_ITEM(mat,M4_00,M4_22,M4_02,M4_20),det_1);
	PMATRIX_DATA(inverse_mat,M4_21) = VEC_FLOAT_DIV (MATRIX4_MUL_SUBS_ITEM(mat,M4_01,M4_20,M4_00,M4_21),det_1);
	
	PMATRIX_DATA(inverse_mat,M4_02) = VEC_FLOAT_DIV (MATRIX4_MUL_SUBS_ITEM(mat,M4_01,M4_12,M4_02,M4_11),det_1);
	PMATRIX_DATA(inverse_mat,M4_12) = VEC_FLOAT_DIV (MATRIX4_MUL_SUBS_ITEM(mat,M4_02,M4_10,M4_00,M4_12),det_1);
	PMATRIX_DATA(inverse_mat,M4_22) = VEC_FLOAT_DIV (MATRIX4_MUL_SUBS_ITEM(mat,M4_00,M4_11,M4_01,M4_10),det_1);
	
	// MAT - C * inverse(A)
	PMATRIX_DATA(inverse_mat,M4_03) =
		VEC_FLOAT_MUL (PMATRIX_DATA(mat,M4_13),PMATRIX_DATA(inverse_mat,M4_01)) +
		VEC_FLOAT_MUL (PMATRIX_DATA(mat,M4_23),PMATRIX_DATA(inverse_mat,M4_02))  - 
		VEC_FLOAT_MUL (PMATRIX_DATA(mat,M4_03),PMATRIX_DATA(inverse_mat,M4_00));

	PMATRIX_DATA(inverse_mat,M4_13) =
		VEC_FLOAT_MUL (PMATRIX_DATA(mat,M4_13),PMATRIX_DATA(inverse_mat,M4_11)) +
		VEC_FLOAT_MUL (PMATRIX_DATA(mat,M4_23),PMATRIX_DATA(inverse_mat,M4_12))  - 
		VEC_FLOAT_MUL (PMATRIX_DATA(mat,M4_03),PMATRIX_DATA(inverse_mat,M4_10));

	PMATRIX_DATA(inverse_mat,M4_23) =
		VEC_FLOAT_MUL (PMATRIX_DATA(mat,M4_13),PMATRIX_DATA(inverse_mat,M4_21)) +
		VEC_FLOAT_MUL (PMATRIX_DATA(mat,M4_23),PMATRIX_DATA(inverse_mat,M4_22))  - 
		VEC_FLOAT_MUL (PMATRIX_DATA(mat,M4_03),PMATRIX_DATA(inverse_mat,M4_20));

	//
	PMATRIX_DATA(inverse_mat,M4_30) = ZERO_FLOAT;
	PMATRIX_DATA(inverse_mat,M4_31) = ZERO_FLOAT;
	PMATRIX_DATA(inverse_mat,M4_32) = ZERO_FLOAT;
	PMATRIX_DATA(inverse_mat,M4_33) = ONE_FLOAT;

	return PFX_STATUS_OK;
}

// 使用高斯消元法求逆
//高斯-约旦法（全选主元）求逆的步骤如下：
//
//	首先，对于 k 从 0 到 n - 1 作如下几步：
//	1.从第 k 行、第 k 列开始的右下角子阵中选取绝对值最大的元素，并记住次元素所在的行号和列号，在通过行交换和列交换将它交换到主元素位置上。这一步称为全选主元。 
//	2.m(k, k) = 1 / m(k, k) 
//	3.m(k, j) = m(k, j) * m(k, k)，j = 0, 1, ..., n-1；j != k 
//	4.m(i, j) = m(i, j) - m(i, k) * m(k, j)，i, j = 0, 1, ..., n-1；i, j != k 
//	5.m(i, k) = -m(i, k) * m(k, k)，i = 0, 1, ..., n-1；i != k
//
//	最后，根据在全选主元过程中所记录的行、列交换的信息进行恢复，恢复的原则如下：在全选主元过程中，先交换的行（列）后进行恢复；原来的行（列）交换用列（行）交换来恢复。
//
PFX_INLINE pfx_result_t matrix4_inverse_gaussian_elimination_unsafe_std (const pfx_marix4_t* PARAM_IN mat,
	pfx_marix4_t* PARAM_INOUT inverse_mat)
{
	pfx_index_t index_table_i[4];
	pfx_index_t index_table_j[4];
	pfx_index_t row_index = 0;
	VEC_FLOAT temp;


	init_matrix4_by_matrix4_unsafe_std(inverse_mat,mat);

	for (row_index = 0; row_index < 4; row_index ++)
	{
		// 第一步，全选主元
		VEC_FLOAT fMax = ZERO_FLOAT;
		pfx_index_t i = 0;
		pfx_index_t j = 0;

		for (i = row_index; i < 4; i ++)
		{
			for (j = row_index; j < 4; j ++)
			{
				VEC_FLOAT f = VEC_FLOAT_ABS(PMATRIX_DATA_(inverse_mat,i, j));
				if (f > fMax)
				{
					fMax	= f;
					index_table_i[row_index]	= i;
					index_table_j[row_index]	= j;
				}
			}
		}

		// 不可逆
		if (0 ==VEC_FLOAT_CMP (fMax,ZERO_FLOAT))
		{
			return PFX_STATUS_FAIL;
		}


		if (index_table_i[row_index] != row_index)
		{
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,row_index, 0),PMATRIX_DATA_(inverse_mat,index_table_i[row_index], 0),temp);
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,row_index, 1),PMATRIX_DATA_(inverse_mat,index_table_i[row_index], 1),temp);
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,row_index, 2),PMATRIX_DATA_(inverse_mat,index_table_i[row_index], 2),temp);
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,row_index, 3),PMATRIX_DATA_(inverse_mat,index_table_i[row_index], 3),temp);
		}
		if (index_table_j[row_index] != row_index)
		{
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,0, row_index),PMATRIX_DATA_(inverse_mat,0, index_table_j[row_index]),temp);
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,1, row_index),PMATRIX_DATA_(inverse_mat,1, index_table_j[row_index]),temp);
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,2, row_index),PMATRIX_DATA_(inverse_mat,2, index_table_j[row_index]),temp);
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,3, row_index),PMATRIX_DATA_(inverse_mat,3, index_table_j[row_index]),temp);
		}
		// 第二步
		PMATRIX_DATA_(inverse_mat,row_index,row_index) = VEC_FLOAT_DIV(ONE_FLOAT,PMATRIX_DATA_(inverse_mat,row_index,row_index));	
		// 第三步
		for (j = 0; j < 4; j ++)
		{
			if (j != row_index)
			{
				PMATRIX_DATA_(inverse_mat,row_index,j) = VEC_FLOAT_MUL(PMATRIX_DATA_(inverse_mat,row_index,j),PMATRIX_DATA_(inverse_mat,row_index,row_index));	
			}
		}

		// 第四步
		for (i = 0; i < 4; i ++)
		{
			if (i != row_index)
			{
				for	(j = 0; j < 4; j ++)
				{
					if (j != row_index)
					{
						PMATRIX_DATA_(inverse_mat,i,j) = PMATRIX_DATA_(inverse_mat,i,j) - 
							VEC_FLOAT_MUL(PMATRIX_DATA_(inverse_mat,i,row_index),PMATRIX_DATA_(inverse_mat,row_index,j));	
					}
				}
			}
		}
		// 第五步
		for (i = 0; i < 4; i ++)
		{
			if (i != row_index)
			{
				PMATRIX_DATA_(inverse_mat,i,row_index) = VEC_FLOAT_MUL(PMATRIX_DATA_(inverse_mat,i,row_index),-PMATRIX_DATA_(inverse_mat,row_index,row_index));	
			}
		}
	}

	for	(row_index = 3; row_index >= 0; row_index --)
	{
		if (index_table_j[row_index] != row_index)
		{
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,row_index,0),PMATRIX_DATA_(inverse_mat,index_table_j[row_index],0),temp);
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,row_index,1),PMATRIX_DATA_(inverse_mat,index_table_j[row_index],1),temp);
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,row_index,2),PMATRIX_DATA_(inverse_mat,index_table_j[row_index],2),temp);
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,row_index,3),PMATRIX_DATA_(inverse_mat,index_table_j[row_index],3),temp);
		}
		if (index_table_i[row_index] != row_index)
		{
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,0,row_index),PMATRIX_DATA_(inverse_mat,0,index_table_i[row_index]),temp);
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,1,row_index),PMATRIX_DATA_(inverse_mat,1,index_table_i[row_index]),temp);
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,2,row_index),PMATRIX_DATA_(inverse_mat,2,index_table_i[row_index]),temp);
			SWAP_VALUE(PMATRIX_DATA_(inverse_mat,3,row_index),PMATRIX_DATA_(inverse_mat,3,index_table_i[row_index]),temp);
		}
	}

	return PFX_STATUS_OK;
}

// 正交投影矩阵
PFX_INLINE pfx_marix4_t orthogonal_projection_matrix_opengl (VEC_FLOAT left,VEC_FLOAT top,VEC_FLOAT right,
	VEC_FLOAT bottom,VEC_FLOAT near_plane,VEC_FLOAT far_plane,pfx_bool_t bRotate)
{
	pfx_marix4_t result;
	VEC_FLOAT right_sub_left = VEC_FLOAT_DIV(ONE_FLOAT,(right - left));
	VEC_FLOAT top_sub_btn = VEC_FLOAT_DIV(ONE_FLOAT,(top - bottom));
	VEC_FLOAT far_sub_near = VEC_FLOAT_DIV(ONE_FLOAT,(far_plane - near_plane));

	if (bRotate)
	{
		MATRIX_DATA_ (result,0,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,1) = VEC_FLOAT_MUL (TWO_FLOAT,right_sub_left);
		MATRIX_DATA_ (result,0,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,3) = VEC_FLOAT_MUL (right+left,-right_sub_left);

		MATRIX_DATA_ (result,1,0) = VEC_FLOAT_MUL (TWO_FLOAT,top_sub_btn);
		MATRIX_DATA_ (result,1,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,3) = VEC_FLOAT_MUL (top+bottom,top_sub_btn);
	}
	else
	{
		MATRIX_DATA_ (result,0,0) = VEC_FLOAT_MUL (TWO_FLOAT,right_sub_left);
		MATRIX_DATA_ (result,0,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,3) = VEC_FLOAT_MUL (right+left,right_sub_left);

		MATRIX_DATA_ (result,1,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,1) = VEC_FLOAT_MUL (TWO_FLOAT,top_sub_btn);
		MATRIX_DATA_ (result,1,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,3) = VEC_FLOAT_MUL (top+bottom,top_sub_btn);
	}

	MATRIX_DATA_ (result,2,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,2,1) = ZERO_FLOAT;
	MATRIX_DATA_ (result,2,2) = VEC_FLOAT_MUL (-TWO_FLOAT,far_sub_near);
	MATRIX_DATA_ (result,2,3) = VEC_FLOAT_MUL (near_plane+far_plane,far_sub_near);

	MATRIX_DATA_ (result,3,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,3,1) = ZERO_FLOAT;
	MATRIX_DATA_ (result,3,2) = ZERO_FLOAT;
	MATRIX_DATA_ (result,3,3) = ONE_FLOAT;
	return result;
}

PFX_INLINE pfx_marix4_t orthogonal_projection_matrix_directX (VEC_FLOAT left,VEC_FLOAT top,VEC_FLOAT right,
	VEC_FLOAT bottom,VEC_FLOAT near_plane,VEC_FLOAT far_plane,pfx_bool_t bRotate)
{
	pfx_marix4_t result;
	VEC_FLOAT right_sub_left = VEC_FLOAT_DIV(ONE_FLOAT,(right - left));
	VEC_FLOAT top_sub_btn = VEC_FLOAT_DIV(ONE_FLOAT,(top - bottom));
	VEC_FLOAT far_sub_near = VEC_FLOAT_DIV(ONE_FLOAT,(far_plane - near_plane));

	if (bRotate)
	{
		MATRIX_DATA_ (result,0,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,1) = VEC_FLOAT_MUL (TWO_FLOAT,right_sub_left);
		MATRIX_DATA_ (result,0,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,3) = VEC_FLOAT_MUL (right+left,-right_sub_left);

		MATRIX_DATA_ (result,1,0) = VEC_FLOAT_MUL (TWO_FLOAT,top_sub_btn);
		MATRIX_DATA_ (result,1,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,3) = VEC_FLOAT_MUL (top+bottom,top_sub_btn);
	}
	else
	{
		MATRIX_DATA_ (result,0,0) = VEC_FLOAT_MUL (TWO_FLOAT,right_sub_left);
		MATRIX_DATA_ (result,0,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,3) = VEC_FLOAT_MUL (right+left,right_sub_left);

		MATRIX_DATA_ (result,1,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,1) = VEC_FLOAT_MUL (TWO_FLOAT,top_sub_btn);
		MATRIX_DATA_ (result,1,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,3) = VEC_FLOAT_MUL (top+bottom,top_sub_btn);
	}

	MATRIX_DATA_ (result,2,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,2,1) = ZERO_FLOAT;
	MATRIX_DATA_ (result,2,2) = far_sub_near;
	MATRIX_DATA_ (result,2,3) = VEC_FLOAT_MUL (near_plane,far_sub_near);

	MATRIX_DATA_ (result,3,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,3,1) = ZERO_FLOAT;
	MATRIX_DATA_ (result,3,2) = ZERO_FLOAT;
	MATRIX_DATA_ (result,3,3) = ONE_FLOAT;
	return result;
}

// 透视投影矩阵
PFX_INLINE pfx_marix4_t perspective_projection_matrix_opengl_by_plane (VEC_FLOAT left,VEC_FLOAT top,VEC_FLOAT right,
	VEC_FLOAT bottom,VEC_FLOAT near_plane,VEC_FLOAT far_plane,pfx_bool_t bRightHanded, pfx_bool_t bRotate)
{
	pfx_marix4_t result;
	VEC_FLOAT right_sub_left = VEC_FLOAT_DIV(ONE_FLOAT,(right - left));
	VEC_FLOAT top_sub_btn = VEC_FLOAT_DIV(ONE_FLOAT,(top - bottom));
	VEC_FLOAT far_sub_near = VEC_FLOAT_DIV(ONE_FLOAT,(far_plane - near_plane));
	VEC_FLOAT two_near = VEC_FLOAT_MUL (TWO_FLOAT,near_plane);
	if (bRotate)
	{
		MATRIX_DATA_ (result,0,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,1) = VEC_FLOAT_MUL (two_near,right_sub_left);
		MATRIX_DATA_ (result,0,2) = VEC_FLOAT_MUL (top+bottom,right_sub_left);
		MATRIX_DATA_ (result,0,3) = ZERO_FLOAT;

		MATRIX_DATA_ (result,1,0) = VEC_FLOAT_MUL (two_near,top_sub_btn);
		MATRIX_DATA_ (result,1,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,2) = VEC_FLOAT_MUL (right+left,top_sub_btn);
		MATRIX_DATA_ (result,1,3) = ZERO_FLOAT;
	}
	else
	{
		MATRIX_DATA_ (result,0,0) = VEC_FLOAT_MUL (two_near,right_sub_left);
		MATRIX_DATA_ (result,0,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,2) = VEC_FLOAT_MUL (right+left,right_sub_left);
		MATRIX_DATA_ (result,0,3) = ZERO_FLOAT;

		MATRIX_DATA_ (result,1,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,1) = VEC_FLOAT_MUL (two_near,top_sub_btn);
		MATRIX_DATA_ (result,1,2) = VEC_FLOAT_MUL (top+bottom,top_sub_btn);
		MATRIX_DATA_ (result,1,3) = ZERO_FLOAT;
	}

	MATRIX_DATA_ (result,2,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,2,1) = ZERO_FLOAT;

	MATRIX_DATA_ (result,2,3) = VEC_FLOAT_MUL (VEC_FLOAT_MUL(two_near,far_plane),-far_sub_near);

	MATRIX_DATA_ (result,3,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,3,1) = ZERO_FLOAT;

	MATRIX_DATA_ (result,3,3) = ZERO_FLOAT;

	if (bRightHanded)
	{
		MATRIX_DATA_ (result,2,2) = VEC_FLOAT_MUL (-(far_plane+near_plane),far_sub_near);
		MATRIX_DATA_ (result,3,2) = -ONE_FLOAT;
	}
	else
	{
		MATRIX_DATA_ (result,2,2) = VEC_FLOAT_MUL ((far_plane+near_plane),far_sub_near);
		MATRIX_DATA_ (result,3,2) = ONE_FLOAT;
	}
	
	return result;
}

PFX_INLINE pfx_marix4_t perspective_projection_matrix_directX_by_plane (VEC_FLOAT left,VEC_FLOAT top,VEC_FLOAT right,
	VEC_FLOAT bottom,VEC_FLOAT near_plane,VEC_FLOAT far_plane,pfx_bool_t bRightHanded, pfx_bool_t bRotate)
{
	pfx_marix4_t result;
	VEC_FLOAT right_sub_left = VEC_FLOAT_DIV(ONE_FLOAT,(right - left));
	VEC_FLOAT top_sub_btn = VEC_FLOAT_DIV(ONE_FLOAT,(top - bottom));
	VEC_FLOAT far_sub_near = VEC_FLOAT_DIV(ONE_FLOAT,(far_plane - near_plane));
	VEC_FLOAT two_near = VEC_FLOAT_MUL (TWO_FLOAT,near_plane);
	if (bRotate)
	{
		MATRIX_DATA_ (result,0,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,1) = VEC_FLOAT_MUL (two_near,right_sub_left);
		MATRIX_DATA_ (result,0,2) = VEC_FLOAT_MUL (top+bottom,right_sub_left);
		MATRIX_DATA_ (result,0,3) = ZERO_FLOAT;

		MATRIX_DATA_ (result,1,0) = VEC_FLOAT_MUL (two_near,top_sub_btn);
		MATRIX_DATA_ (result,1,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,2) = VEC_FLOAT_MUL (right+left,top_sub_btn);
		MATRIX_DATA_ (result,1,3) = ZERO_FLOAT;
	}
	else
	{
		MATRIX_DATA_ (result,0,0) = VEC_FLOAT_MUL (two_near,right_sub_left);
		MATRIX_DATA_ (result,0,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,2) = VEC_FLOAT_MUL (right+left,right_sub_left);
		MATRIX_DATA_ (result,0,3) = ZERO_FLOAT;

		MATRIX_DATA_ (result,1,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,1) = VEC_FLOAT_MUL (two_near,top_sub_btn);
		MATRIX_DATA_ (result,1,2) = VEC_FLOAT_MUL (top+bottom,top_sub_btn);
		MATRIX_DATA_ (result,1,3) = ZERO_FLOAT;
	}

	MATRIX_DATA_ (result,2,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,2,1) = ZERO_FLOAT;

	MATRIX_DATA_ (result,2,3) = VEC_FLOAT_MUL (VEC_FLOAT_MUL(near_plane,far_plane),-far_sub_near);

	MATRIX_DATA_ (result,3,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,3,1) = ZERO_FLOAT;

	MATRIX_DATA_ (result,3,3) = ZERO_FLOAT;

	if (bRightHanded)
	{
		MATRIX_DATA_ (result,2,2) = VEC_FLOAT_MUL (-far_plane,far_sub_near);
		MATRIX_DATA_ (result,3,2) = -ONE_FLOAT;
	}
	else
	{
		MATRIX_DATA_ (result,2,2) = VEC_FLOAT_MUL (far_plane,far_sub_near);
		MATRIX_DATA_ (result,3,2) = ONE_FLOAT;
	}

	return result;
}

PFX_INLINE pfx_marix4_t perspective_projection_matrix_opengl (VEC_FLOAT width, VEC_FLOAT height,
	VEC_FLOAT near_plane, VEC_FLOAT far_plane,
	pfx_bool_t bRightHanded,
	pfx_bool_t bRotate)
{
	pfx_marix4_t result;
	VEC_FLOAT right_sub_left = VEC_FLOAT_DIV(ONE_FLOAT,width);
	VEC_FLOAT top_sub_btn = VEC_FLOAT_DIV(ONE_FLOAT,height);
	VEC_FLOAT far_sub_near = VEC_FLOAT_DIV(ONE_FLOAT,(far_plane - near_plane));
	VEC_FLOAT two_near = VEC_FLOAT_MUL (TWO_FLOAT,near_plane);
	if (bRotate)
	{
		MATRIX_DATA_ (result,0,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,1) = VEC_FLOAT_MUL (two_near,right_sub_left);
		MATRIX_DATA_ (result,0,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,3) = ZERO_FLOAT;

		MATRIX_DATA_ (result,1,0) = VEC_FLOAT_MUL (two_near,top_sub_btn);
		MATRIX_DATA_ (result,1,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,3) = ZERO_FLOAT;
	}
	else
	{
		MATRIX_DATA_ (result,0,0) = VEC_FLOAT_MUL (two_near,right_sub_left);
		MATRIX_DATA_ (result,0,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,3) = ZERO_FLOAT;

		MATRIX_DATA_ (result,1,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,1) = VEC_FLOAT_MUL (two_near,top_sub_btn);
		MATRIX_DATA_ (result,1,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,3) = ZERO_FLOAT;
	}

	MATRIX_DATA_ (result,2,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,2,1) = ZERO_FLOAT;

	MATRIX_DATA_ (result,2,3) = VEC_FLOAT_MUL (VEC_FLOAT_MUL(two_near,far_plane),-far_sub_near);

	MATRIX_DATA_ (result,3,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,3,1) = ZERO_FLOAT;

	MATRIX_DATA_ (result,3,3) = ZERO_FLOAT;

	if (bRightHanded)
	{
		MATRIX_DATA_ (result,2,2) = VEC_FLOAT_MUL (-(far_plane+near_plane),far_sub_near);
		MATRIX_DATA_ (result,3,2) = -ONE_FLOAT;
	}
	else
	{
		MATRIX_DATA_ (result,2,2) = VEC_FLOAT_MUL ((far_plane+near_plane),far_sub_near);
		MATRIX_DATA_ (result,3,2) = ONE_FLOAT;
	}

	return result;
}

PFX_INLINE pfx_marix4_t perspective_projection_matrix_directX (VEC_FLOAT width, VEC_FLOAT height,
	VEC_FLOAT near_plane, VEC_FLOAT far_plane,
	pfx_bool_t bRightHanded,
	pfx_bool_t bRotate)
{
	pfx_marix4_t result;
	VEC_FLOAT right_sub_left = VEC_FLOAT_DIV(ONE_FLOAT,width);
	VEC_FLOAT top_sub_btn = VEC_FLOAT_DIV(ONE_FLOAT,height);
	VEC_FLOAT far_sub_near = VEC_FLOAT_DIV(ONE_FLOAT,(far_plane - near_plane));
	VEC_FLOAT two_near = VEC_FLOAT_MUL (TWO_FLOAT,near_plane);
	if (bRotate)
	{
		MATRIX_DATA_ (result,0,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,1) = VEC_FLOAT_MUL (two_near,right_sub_left);
		MATRIX_DATA_ (result,0,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,3) = ZERO_FLOAT;

		MATRIX_DATA_ (result,1,0) = VEC_FLOAT_MUL (two_near,top_sub_btn);
		MATRIX_DATA_ (result,1,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,3) = ZERO_FLOAT;
	}
	else
	{
		MATRIX_DATA_ (result,0,0) = VEC_FLOAT_MUL (two_near,right_sub_left);
		MATRIX_DATA_ (result,0,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,3) = ZERO_FLOAT;

		MATRIX_DATA_ (result,1,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,1) = VEC_FLOAT_MUL (two_near,top_sub_btn);
		MATRIX_DATA_ (result,1,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,3) = ZERO_FLOAT;
	}

	MATRIX_DATA_ (result,2,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,2,1) = ZERO_FLOAT;

	MATRIX_DATA_ (result,2,3) = VEC_FLOAT_MUL (VEC_FLOAT_MUL(near_plane,far_plane),-far_sub_near);

	MATRIX_DATA_ (result,3,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,3,1) = ZERO_FLOAT;

	MATRIX_DATA_ (result,3,3) = ZERO_FLOAT;

	if (bRightHanded)
	{
		MATRIX_DATA_ (result,2,2) = VEC_FLOAT_MUL (-far_plane,far_sub_near);
		MATRIX_DATA_ (result,3,2) = -ONE_FLOAT;
	}
	else
	{
		MATRIX_DATA_ (result,2,2) = VEC_FLOAT_MUL (far_plane,far_sub_near);
		MATRIX_DATA_ (result,3,2) = ONE_FLOAT;
	}

	return result;
}

PFX_INLINE pfx_marix4_t perspective_projection_matrix (VEC_FLOAT width, VEC_FLOAT height,
	VEC_FLOAT near_plane, VEC_FLOAT far_plane,
	CLIPSPACE_SYSTEM cs,
	pfx_bool_t bRightHanded,
	pfx_bool_t bRotate)
{
	pfx_marix4_t mat;
	if (OPENGL_CLIPSPACE_SYSTEM == cs)
	{
		mat = perspective_projection_matrix_opengl (width,height,near_plane,far_plane,bRightHanded,bRotate); 
	}
	else if (D3DX_CLIPSPACE_SYSTEM == cs)
	{
		mat = perspective_projection_matrix_directX (width,height,near_plane,far_plane,bRightHanded,bRotate);
	}
	return mat;
}

PFX_INLINE pfx_marix4_t perspective_projection_matrix_by_angle_of_view (VEC_FLOAT fovy,
	VEC_FLOAT aspect,VEC_FLOAT near_plane,VEC_FLOAT far_plane,CLIPSPACE_SYSTEM cs,
	pfx_bool_t bRightHanded,pfx_bool_t bRotate)
{
	VEC_FLOAT height;
	VEC_FLOAT width;
	if (bRotate)
	{
		height =  VEC_FLOAT_MUL (VEC_FLOAT_MUL(TWO_FLOAT,near_plane),pfx_tan(VEC_FLOAT_DIV(fovy,TWO_FLOAT)));
		width = VEC_FLOAT_DIV (height,aspect);
	}
	else
	{
		width =  VEC_FLOAT_MUL (VEC_FLOAT_MUL(TWO_FLOAT,near_plane),pfx_tan(VEC_FLOAT_DIV(fovy,TWO_FLOAT)));
		height = VEC_FLOAT_DIV (width,aspect);
	}

	return perspective_projection_matrix (height,width,near_plane,far_plane,cs,bRightHanded,bRotate);
}

PFX_INLINE pfx_marix4_t perspective_projection_matrix_infinite_distance_opengl (VEC_FLOAT width, VEC_FLOAT height,
	VEC_FLOAT near_plane,
	pfx_bool_t bRightHanded,
	pfx_bool_t bRotate)
{
	pfx_marix4_t result;
	VEC_FLOAT right_sub_left = VEC_FLOAT_DIV(ONE_FLOAT,width);
	VEC_FLOAT top_sub_btn = VEC_FLOAT_DIV(ONE_FLOAT,height);
	VEC_FLOAT two_near = VEC_FLOAT_MUL (TWO_FLOAT,near_plane);
	if (bRotate)
	{
		MATRIX_DATA_ (result,0,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,1) = VEC_FLOAT_MUL (two_near,right_sub_left);
		MATRIX_DATA_ (result,0,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,3) = ZERO_FLOAT;

		MATRIX_DATA_ (result,1,0) = VEC_FLOAT_MUL (two_near,top_sub_btn);
		MATRIX_DATA_ (result,1,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,3) = ZERO_FLOAT;
	}
	else
	{
		MATRIX_DATA_ (result,0,0) = VEC_FLOAT_MUL (two_near,right_sub_left);
		MATRIX_DATA_ (result,0,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,3) = ZERO_FLOAT;

		MATRIX_DATA_ (result,1,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,1) = VEC_FLOAT_MUL (two_near,top_sub_btn);
		MATRIX_DATA_ (result,1,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,3) = ZERO_FLOAT;
	}

	MATRIX_DATA_ (result,2,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,2,1) = ZERO_FLOAT;

	MATRIX_DATA_ (result,2,3) = two_near;

	MATRIX_DATA_ (result,3,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,3,1) = ZERO_FLOAT;

	MATRIX_DATA_ (result,3,3) = ZERO_FLOAT;

	if (bRightHanded)
	{
		MATRIX_DATA_ (result,2,2) = ONE_FLOAT;
		MATRIX_DATA_ (result,3,2) = -ONE_FLOAT;
	}
	else
	{
		MATRIX_DATA_ (result,2,2) = -ONE_FLOAT;
		MATRIX_DATA_ (result,3,2) = ONE_FLOAT;
	}

	return result;
}

PFX_INLINE pfx_marix4_t perspective_projection_matrix_infinite_distance_directX (VEC_FLOAT width, VEC_FLOAT height,
	VEC_FLOAT near_plane, 
	pfx_bool_t bRightHanded,
	pfx_bool_t bRotate)
{
	pfx_marix4_t result;
	VEC_FLOAT right_sub_left = VEC_FLOAT_DIV(ONE_FLOAT,width);
	VEC_FLOAT top_sub_btn = VEC_FLOAT_DIV(ONE_FLOAT,height);
	VEC_FLOAT two_near = VEC_FLOAT_MUL (TWO_FLOAT,near_plane);
	if (bRotate)
	{
		MATRIX_DATA_ (result,0,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,1) = VEC_FLOAT_MUL (two_near,right_sub_left);
		MATRIX_DATA_ (result,0,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,3) = ZERO_FLOAT;

		MATRIX_DATA_ (result,1,0) = VEC_FLOAT_MUL (two_near,top_sub_btn);
		MATRIX_DATA_ (result,1,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,3) = ZERO_FLOAT;
	}
	else
	{
		MATRIX_DATA_ (result,0,0) = VEC_FLOAT_MUL (two_near,right_sub_left);
		MATRIX_DATA_ (result,0,1) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,0,3) = ZERO_FLOAT;

		MATRIX_DATA_ (result,1,0) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,1) = VEC_FLOAT_MUL (two_near,top_sub_btn);
		MATRIX_DATA_ (result,1,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,1,3) = ZERO_FLOAT;
	}

	MATRIX_DATA_ (result,2,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,2,1) = ZERO_FLOAT;

	MATRIX_DATA_ (result,2,3) = near_plane;

	MATRIX_DATA_ (result,3,0) = ZERO_FLOAT;
	MATRIX_DATA_ (result,3,1) = ZERO_FLOAT;

	MATRIX_DATA_ (result,3,3) = ZERO_FLOAT;

	if (bRightHanded)
	{
		MATRIX_DATA_ (result,2,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,3,2) = -ONE_FLOAT;
	}
	else
	{
		MATRIX_DATA_ (result,2,2) = ZERO_FLOAT;
		MATRIX_DATA_ (result,3,2) = ONE_FLOAT;
	}

	return result;
}

PFX_INLINE pfx_marix4_t perspective_projection_matrix_infinite_distance (VEC_FLOAT width, VEC_FLOAT height,
	VEC_FLOAT near_plane,
	CLIPSPACE_SYSTEM cs,
	pfx_bool_t bRightHanded,
	pfx_bool_t bRotate)
{
	pfx_marix4_t mat;
	if (OPENGL_CLIPSPACE_SYSTEM == cs)
	{
		mat = perspective_projection_matrix_infinite_distance_opengl (width,height,near_plane,bRightHanded,bRotate); 
	}
	else if (D3DX_CLIPSPACE_SYSTEM == cs)
	{
		mat = perspective_projection_matrix_infinite_distance_directX (width,height,near_plane,bRightHanded,bRotate);
	}
	return mat;
}

PFX_INLINE pfx_marix4_t perspective_projection_matrix_infinite_distance_by_angle_of_view (VEC_FLOAT fovy,
	VEC_FLOAT aspect,VEC_FLOAT near_plane,CLIPSPACE_SYSTEM cs,
	pfx_bool_t bRightHanded,pfx_bool_t bRotate)
{
	VEC_FLOAT height;
	VEC_FLOAT width;
	if (bRotate)
	{
		height =  VEC_FLOAT_MUL (VEC_FLOAT_MUL(TWO_FLOAT,near_plane),pfx_tan(VEC_FLOAT_DIV(fovy,TWO_FLOAT)));
		width = VEC_FLOAT_DIV (height,aspect);
	}
	else
	{
		width =  VEC_FLOAT_MUL (VEC_FLOAT_MUL(TWO_FLOAT,near_plane),pfx_tan(VEC_FLOAT_DIV(fovy,TWO_FLOAT)));
		height = VEC_FLOAT_DIV (width,aspect);
	}

	return perspective_projection_matrix_infinite_distance (height,width,near_plane,cs,bRightHanded,bRotate);
}

//
PFX_INLINE pfx_marix4_t look_at_view_matrix_unsafe_std (const pfx_vector3_t* vEye,
	const pfx_vector3_t* vAt,const pfx_vector3_t* vUp,pfx_bool_t bRightHanded)
{
	pfx_marix4_t mat_result;
	pfx_vector3_t vForward;
	pfx_vector3_t vUpNorm;
	pfx_vector3_t vSize;

	if (bRightHanded)
	{
		vForward = vector3_sub_unsafe_std (vEye,vAt);
	}
	else
	{
		vForward = vector3_sub_unsafe_std (vAt,vEye);
	}

	vector3_normalize_ref_unsafe_std (&vForward);
	vSize = vector3_cross_unsafe_std (vUp,&vForward);
	vector3_normalize_ref_unsafe_std (&vSize);
	vUpNorm = vector3_cross_unsafe_std (&vForward,&vSize);
	vector3_normalize_ref_unsafe_std (&vUpNorm);

	MATRIX_DATA_ (mat_result,0,0) = VECTOR_DATA (vSize,VEC_INDEX_X);
	MATRIX_DATA_ (mat_result,0,1) = VECTOR_DATA (vSize,VEC_INDEX_Y);
	MATRIX_DATA_ (mat_result,0,2) = VECTOR_DATA (vSize,VEC_INDEX_Z);
	MATRIX_DATA_ (mat_result,0,3) = ZERO_FLOAT;

	MATRIX_DATA_ (mat_result,1,0) = VECTOR_DATA (vUpNorm,VEC_INDEX_X);
	MATRIX_DATA_ (mat_result,1,1) = VECTOR_DATA (vUpNorm,VEC_INDEX_Y);
	MATRIX_DATA_ (mat_result,1,2) = VECTOR_DATA (vUpNorm,VEC_INDEX_Z);
	MATRIX_DATA_ (mat_result,1,3) = ZERO_FLOAT;

	MATRIX_DATA_ (mat_result,2,0) = VECTOR_DATA (vForward,VEC_INDEX_X);
	MATRIX_DATA_ (mat_result,2,1) = VECTOR_DATA (vForward,VEC_INDEX_Y);
	MATRIX_DATA_ (mat_result,2,2) = VECTOR_DATA (vForward,VEC_INDEX_Z);
	MATRIX_DATA_ (mat_result,2,3) = ZERO_FLOAT;

	MATRIX_DATA_ (mat_result,3,0) = ZERO_FLOAT;
	MATRIX_DATA_ (mat_result,3,1) = ZERO_FLOAT;
	MATRIX_DATA_ (mat_result,3,2) = ZERO_FLOAT;
	MATRIX_DATA_ (mat_result,3,3) = ONE_FLOAT;

	
	matrix4_post_translation_ref_unsafe_std (&mat_result,
		-PVECTOR_DATA(vEye,VEC_INDEX_X),
		-PVECTOR_DATA(vEye,VEC_INDEX_Y),
		-PVECTOR_DATA(vEye,VEC_INDEX_Z));

	return mat_result;
}

PFX_INLINE pfx_marix4_t look_at_view_matrix_lefthand_unsafe_std (const pfx_vector3_t* vEye,
	const pfx_vector3_t* vAt,const pfx_vector3_t* vUp)
{
	return look_at_view_matrix_unsafe_std(vEye,vAt,vUp,pfx_false);
}

PFX_INLINE pfx_marix4_t look_at_view_matrix_righthand_unsafe_std (const pfx_vector3_t* vEye,
	const pfx_vector3_t* vAt,const pfx_vector3_t* vUp)
{
	return look_at_view_matrix_unsafe_std(vEye,vAt,vUp,pfx_true);
}

PFX_C_EXTERN_END



#endif			//PFX_MATRIX4_H_
