/*
 * pfx_matrix.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_MATRIX_H_
#define		PFX_MATRIX_H_

#include "pfx_vector.h"

PECKER_BEGIN

template < class dimension_value, const pfx_usize_t dimension_count >
struct st_pfx_matrix_square
{
	typedef typename dimension_value dimension_value_t;
	typedef st_pfx_vector < dimension_value, dimension_count > vector_t;
	vector_t m_vector[ (!dimension_count?1:dimension_count) ];
};

template < class dimension_value, const pfx_usize_t dimension_count >
union un_pfx_matrix_square
{
	typedef typename dimension_value dimension_value_t;
	typedef st_pfx_vector < dimension_value, dimension_count > vector_t;
	typedef st_pfx_matrix_square < dimension_value, dimension_count > matrix_t;

	matrix_t						m_matrix;
	vector_t						m_vector[ (!dimension_count?1:dimension_count) ];
	dimension_value_t	m_dim [ ((!dimension_count)?(1):(dimension_count * dimension_count)) ];
};

template < class dimension_value_operations, const pfx_usize_t dimension_count, const pfx_enum_int_t optional_type >
struct pfx_matrix_square_ex;

typedef enum enumMATRIX_DIM_NAME
{
	MAT_DIM_1 = 0,
	MAT_DIM_2,
	MAT_DIM_3,
	MAT_DIM_4,

	MAT_DIM_OTHER
}MATRIX_DIM_NAME_t;


template < class dimension_value_operations, 
	const pfx_usize_t			dimension_count,
	const pfx_enum_int_t optional_type = 0>
class pfx_square_matrix
{
public:
	typedef typename dimension_value_operations::dimension_value_t	dimension_value_t;
	typedef typename dimension_value_operations											dimension_value_operations_t;
	typedef st_pfx_vector < dimension_value_t, dimension_count >				vector_t;
	typedef pfx_vector < dimension_value_operations, dimension_count, optional_type >	cvector_t;
	typedef typename un_pfx_matrix_square < dimension_value_t, dimension_count >		matrix_t;
	typedef typename pfx_matrix_square_ex < dimension_value_operations, dimension_count, optional_type > 		matrix_ex_t;
	typedef pfx_square_matrix < dimension_value_operations, dimension_count, optional_type > cmatrix_t;

	matrix_t m_mat;
public:
	pfx_square_matrix (pfx_boolean_t bIndentify = PFX_BOOL_TRUE);
	pfx_square_matrix (dimension_value_t dim_set, 
		pfx_boolean_t bIndentify);
	pfx_square_matrix (const dimension_value_t* dim_sets_ptr,
		pfx_usize_t dim_val_count);
	pfx_square_matrix (const vector_t* vecs_ptr,pfx_usize_t vecs_count);
	pfx_square_matrix (const cvector_t* vecs_ptr,pfx_usize_t vecs_count);
	pfx_square_matrix (const vector_t& vec);
	pfx_square_matrix (const cvector_t& vec);
	pfx_square_matrix (const matrix_t& mat);
	pfx_square_matrix (const cmatrix_t& other_);
public:
	PFX_INLINE pfx_usize_t	get_dimensional_count () const;
	PFX_INLINE vector_t row (pfx_uindex_t row_number) const;
	PFX_INLINE vector_t column (pfx_uindex_t column_number) const;
	PFX_INLINE vector_t& row_reference (pfx_uindex_t row_number);

	PFX_INLINE const cvector_t* row_cvec_ptr (pfx_uindex_t row_number) const;
	PFX_INLINE cvector_t* row_cvec_refptr (pfx_uindex_t row_number);
	PFX_INLINE cvector_t column_cvec (pfx_uindex_t column_number) const;

	PFX_INLINE cmatrix_t& transpose_replace ();
	PFX_INLINE cmatrix_t transpose_matrix () const;

	PFX_INLINE  cmatrix_t& mul_repalce (const cmatrix_t& other_);
	PFX_INLINE  cmatrix_t& mul_repalce (const matrix_t& other_);
	PFX_INLINE  cmatrix_t& mul_repalce (dimension_value_t val);

	PFX_INLINE  cmatrix_t& add_repalce (const cmatrix_t& other_);
	PFX_INLINE  cmatrix_t& add_repalce (const matrix_t& other_);

	PFX_INLINE  cmatrix_t& sub_repalce (const cmatrix_t& other_);
	PFX_INLINE  cmatrix_t& sub_repalce (const matrix_t& other_);

	PFX_INLINE  cmatrix_t& div_repalce (dimension_value_t val);
	
	// 矩阵行列式的值
	PFX_INLINE dimension_value_t determinant (pfx_u32_t delta = MID_PRECISION_QUALIFER_VAL);
	// 行列式的代数余子式值
	PFX_INLINE dimension_value_t algebraic_cofactor_determinant (pfx_uindex_t x,pfx_uindex_t y);
	// 求伴随矩阵 （方阵）
	PFX_INLINE cmatrix_t adjoint_matrix () const;
	PFX_INLINE cmatrix_t* sub_adjoint_matrix (cmatrix_t& PARAM_OUT mat,
		pfx_uindex_t offset,
		pfx_usize_t size_) const;

	// 使用高斯消元法求秩
	PFX_INLINE pfx_usize_t rank_gaussian_elimination (cmatrix_t& PARAM_OUT result_mat) const;

	// 求逆矩阵			样式为 [ A|C ]的矩阵的逆矩阵
	//												 0|1
	PFX_INLINE cmatrix_t* spec_inverse_matrix (cmatrix_t& PARAM_OUT mat) const;
	// 分块求逆
	PFX_INLINE cmatrix_t* inverse_matrix (cmatrix_t& PARAM_OUT mat) const;
	// 使用高斯消元法求逆
	PFX_INLINE cmatrix_t* inverse_matrix_gaussian_elimination (cmatrix_t& PARAM_OUT mat) const;

protected:
	static PFX_INLINE dimension_value_t& adjoint_matrix_value (const matrix_t& mat,pfx_uindex_t x,pfx_uindex_t y);
	static PFX_INLINE dimension_value_t& transpose_matrix_value (const matrix_t& mat,pfx_uindex_t x,pfx_uindex_t y);
public:
	static PFX_INLINE pfx_usize_t dimensional_count ();
	static PFX_INLINE cvector_t& defualt_vector ();
	//
	static PFX_INLINE matrix_t& sets (matrix_t& mat, dimension_value_t val);
	static PFX_INLINE matrix_t& sets (matrix_t& mat, const vector_t& vec);
	static PFX_INLINE matrix_t& Indentify_matrix (matrix_t& mat,dimension_value_t val);
	static PFX_INLINE matrix_t& transpose_matrix (const matrix_t& mat,matrix_t& trans_mat);

	// 矩阵行列式的值
	static PFX_INLINE dimension_value_t determinant_gaussian_unsafe 
		(matrix_ex_t& gaussian_mat, pfx_u32_t delta = MID_PRECISION_QUALIFER_VAL);

	static PFX_INLINE dimension_value_t determinant (const matrix_t& mat, 
		pfx_u32_t delta = MID_PRECISION_QUALIFER_VAL);

	static PFX_INLINE dimension_value_t algebraic_cofactor_determinant_gaussian 
		(matrix_ex_t& gaussian_mat,
		pfx_uindex_t x,pfx_uindex_t y,pfx_u32_t delta = MID_PRECISION_QUALIFER_VAL);

	static PFX_INLINE dimension_value_t algebraic_cofactor_determinant 
		(const matrix_t& mat,
		pfx_uindex_t x,pfx_uindex_t y,pfx_u32_t delta = MID_PRECISION_QUALIFER_VAL);
	// 求伴随矩阵 （方阵）
	static PFX_INLINE matrix_t* adjoint_matrix (const matrix_t& PARAM_IN mat,
		matrix_t& PARAM_OUT adjoint_mat);
	static PFX_INLINE matrix_t* sub_adjoint_matrix (const matrix_t& PARAM_IN mat,
		matrix_t& PARAM_OUT adjoint_mat,
		pfx_uindex_t offset,
		pfx_usize_t size_);
	// 使用高斯消元法求秩
	static PFX_INLINE pfx_usize_t rank_gaussian_elimination (const  matrix_t& PARAM_IN mat,
		matrix_t& PARAM_OUT result_mat) ;

	// 求逆矩阵			样式为 [ A|C ]的矩阵的逆矩阵
	//												 0|1
	static PFX_INLINE matrix_t* spec_inverse_matrix (const  matrix_t& PARAM_IN mat,
		matrix_t& PARAM_OUT inverse_mat);

	// 分块求逆
	static PFX_INLINE matrix_t* inverse_matrix (const  matrix_t& PARAM_IN mat,
		matrix_t& PARAM_OUT inverse_mat);

	// 使用高斯消元法求逆
	static PFX_INLINE matrix_t* inverse_matrix_gaussian_elimination (const  matrix_t& PARAM_IN mat,
		matrix_t& PARAM_OUT inverse_mat);

public:
	static PFX_INLINE matrix_t& matrix_mul_value (const matrix_t& mat, dimension_value_t val,
		matrix_t& res_mat); 
	static PFX_INLINE matrix_t& matrix_div_value (const matrix_t& mat, dimension_value_t val,
		matrix_t& res_mat); 
	static PFX_INLINE matrix_t& matrix_add_matrix (const matrix_t& matA, const matrix_t& matB,
		matrix_t& res_mat); 
	static PFX_INLINE matrix_t& matrix_sub_matrix (const matrix_t& matA, const matrix_t& matB,
		matrix_t& res_mat); 

	// 1*4矩阵 X 4*4矩阵 = 1*4矩阵
	static PFX_INLINE vector_t& matrix_mul_matrix (const vector_t& mat_1x4,const matrix_t& mat_4x4, 
		vector_t& res_mat1x4);  
	// 4*4矩阵 X 4*1矩阵 = 4*1矩阵
	static PFX_INLINE vector_t& matrix_mul_matrix (const matrix_t& mat_4x4,const vector_t& mat_4x1,
		vector_t& res_mat4x1); 
	// 4*4矩阵 X 4*4矩阵 = 4*4矩阵
	static PFX_INLINE matrix_t& matrix_mul_matrix (const matrix_t& matA_4x4,const matrix_t& matB_4x4,
		matrix_t& res_mat_4x4);

};

PECKER_END

#endif			//PFX_MATRIX_H_
