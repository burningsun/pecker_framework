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



template < class dimension_value_operations, 
	const pfx_usize_t			dimensional_count,
	const pfx_enum_int_t optional_type = 0>
class pfx_matrix
{
public:
	typedef typename dimension_value_operations::dimension_value_t	dimension_value_t;
	typedef typename dimension_value_operations											dimension_value_operations_t;
	typedef st_pfx_vector < dimension_value_t, dimension_count >				vector_t;
	typedef pfx_vector < dimension_value_operations, dimension_count, optional_type >	cvector_t;
	typedef typename un_pfx_matrix_square < dimension_value_t, dimension_count >		matrix_t;
	
	matrix_t m_mat;
public:
	pfx_matrix (pfx_boolean_t bIndentify = PFX_BOOL_TRUE);
	pfx_matrix (dimension_value_t dim_set, 
		pfx_boolean_t bIndentify);
	pfx_matrix (const dimension_value_t* dim_sets_ptr,
		pfx_usize_t dim_val_count);
	pfx_matrix (const dimension_value_t* dim_sets_ptr,
		pfx_usize_t dim_val_count);
	pfx_matrix (const vector_t* vecs_ptr,pfx_usize_t vecs_count);
	pfx_matrix (const cvector_t* vecs_ptr,pfx_usize_t vecs_count);
	pfx_matrix (const matrix_t& mat);
	pfx_matrix (const pfx_matrix& other_);
public:
	PFX_INLINE vector_t row (pfx_uindex_t row_number) const;
	PFX_INLINE vector_t column (pfx_uindex_t column_number) const;
	PFX_INLINE vector_t& row_reference (pfx_uindex_t row_number);

	PFX_INLINE const cvector_t* row_cvec_ptr (pfx_uindex_t row_number) const;
	PFX_INLINE cvector_t* row_cvec_refptr (pfx_uindex_t row_number);
	PFX_INLINE cvector_t column_cvec (pfx_uindex_t column_number) const;

	
	
};

PECKER_END

#endif			//PFX_MATRIX_H_
