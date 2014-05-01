/*
 * pfx_matrix_codes.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_MATRIX_CODES_H_
#define		PFX_MATRIX_CODES_H_

#include "pfx_vector_codes.h"
#include "pfx_matrix.h"

PECKER_BEGIN

// 主要用于高斯消元法交换优化
template < class dimension_value_operations, const pfx_usize_t dimension_count,const pfx_enum_int_t optional_type = 0 >
struct pfx_matrix_square_ex
{
	typedef typename dimension_value_operations::dimension_value_t	dimension_value_t;
	typedef typename dimension_value_operations											dimension_value_operations_t;
	typedef st_pfx_vector < dimension_value_t, dimension_count >				vector_t;
	typedef pfx_vector < dimension_value_operations, dimension_count, optional_type >	cvector_t;
	typedef typename un_pfx_matrix_square < dimension_value_t, dimension_count >		matrix_t;

	matrix_t*	m_mat_ptr;
	vector_t*	m_lines[ (!dimension_count?1:dimension_count)];

	pfx_matrix_square_ex ()
	{
		m_mat_ptr = null;
		for (pfx_uindex_t i=0; i<dimension_count; ++i)
		{
			m_lines[i] = 0;
		}
	}
	pfx_matrix_square_ex (matrix_t& mat)
	{
		m_mat_ptr = &mat;
		for (pfx_uindex_t i=0; i<dimension_count; ++i)
		{
			m_lines[i] = &mat.m_vector[i];
		}
	}
	PFX_INLINE void init(matrix_t& mat)
	{
		m_mat_ptr = &mat;
		for (pfx_uindex_t i=0; i<dimension_count; ++i)
		{
			m_lines[i] = &mat.m_vector[i];
		}
	}
	PFX_INLINE void swap_line_unsafe (pfx_uindex_t i,pfx_uindex_t j)
	{
		vector_t* swap_ptr;
		swap_ptr = m_lines [i];
		m_lines[i] = m_lines[j];
		m_lines[j] = swap_ptr;
	}
	PFX_INLINE pfx_result_t swap_line (pfx_uindex_t i,pfx_uindex_t j)
	{
		RETURN_INVALID_RESULT (!m_mat_ptr,PFX_STATUS_UNINIT);
		RETURN_INVALID_RESULT (((i>=dimension_count) || (j >= dimension_count)),PFX_STATUS_INVALID_PARAMS);
		swap_line_unsafe(i,j);
		return PFX_STATUS_OK;
	}
	PFX_INLINE dimension_value_t clear_oneline_unsafe (pfx_uindex_t test_line, pfx_uindex_t clear_line,
		pfx_uindex_t line_index)
	{
		dimension_value_t mul_factor;
		mul_factor = dimension_value_operations_t::div(m_lines[test_line]->m_value[line_index], m_lines [clear_line]->m_value[line_index]);
		//cvector_t ::mul_replace(*m_lines[clear_line],mul_factor);
		//cvector_t::sub_replace(*m_lines [clear_line],*m_lines[test_line]);
		for (pfx_uindex_t i=line_index; i<dimension_count; ++i)
		{
			dimension_value_operations_t::mul_replace(m_lines[clear_line]->m_value[i],mul_factor);
			dimension_value_operations_t::sub_replace(m_lines[clear_line]->m_value[i],m_lines[test_line]->m_value[i]);
		}
		return mul_factor;
	}
	PFX_INLINE void clear_oneline_same_unsafe (pfx_uindex_t test_line, 
		pfx_uindex_t clear_line,dimension_value_t mul_factor)
	{
		//cvector_t ::mul_replace(*m_lines[clear_line],mul_factor)
		//cvector_t::sub_replace(*m_lines [clear_line],*m_lines[test_line][line_index]);
		for (pfx_uindex_t i=0; i<dimension_count; ++i)
		{
			dimension_value_operations_t::mul_replace(m_lines[clear_line]->m_value[i],mul_factor);
			dimension_value_operations_t::sub_replace(m_lines[clear_line]->m_value[i],m_lines[test_line]->m_value[i]);
		}
	}
	PFX_INLINE void restore_oneline_unsafe (pfx_uindex_t restore_line,pfx_uindex_t line_index,
		dimension_value_t mul_factor)
	{
		for (pfx_uindex_t i=line_index; i<dimension_count; ++i)
		{
			dimension_value_operations_t::div_replace(m_lines[restore_line]->m_value[i],mul_factor);
		}
	}

	PFX_INLINE void restore_oneline_unsafe (pfx_uindex_t restore_line,pfx_uindex_t line_index,
		dimension_value_t mul_factor, pfx_uindex_t except_j)
	{

		if (except_j > line_index)
		{
			for (pfx_uindex_t i=line_index; i<except_j; ++i)
			{
				dimension_value_operations_t::div_replace(m_lines[restore_line]->m_value[i],mul_factor);
			}

			for (pfx_uindex_t i=except_j+1; i<dimension_count; ++i)
			{
				dimension_value_operations_t::div_replace(m_lines[restore_line]->m_value[i],mul_factor);
			}
		}
		else
		{		
			if (except_j == line_index)
			{
				++line_index;
			}
			for (pfx_uindex_t i=line_index; i<dimension_count; ++i)
			{
				dimension_value_operations_t::div_replace(m_lines[restore_line]->m_value[i],mul_factor);
			}
		}
	}

	PFX_INLINE dimension_value_t clear_oneline_unsafe (pfx_uindex_t test_line, pfx_uindex_t clear_line,
		pfx_uindex_t line_index, pfx_uindex_t except_j)
	{
		dimension_value_t mul_factor;
		mul_factor = dimension_value_operations_t::div(m_lines[test_line]->m_value[line_index], 
			m_lines [clear_line]->m_value[line_index]);

		if (except_j > line_index)
		{
			for (pfx_uindex_t i=line_index; i<except_j; ++i)
			{
				dimension_value_operations_t::mul_replace(m_lines[clear_line]->m_value[i],mul_factor);
				dimension_value_operations_t::sub_replace(m_lines[clear_line]->m_value[i],m_lines[test_line]->m_value[i]);
			}
			for (pfx_uindex_t i=except_j+1; i<dimension_count; ++i)
			{
				dimension_value_operations_t::mul_replace(m_lines[clear_line]->m_value[i],mul_factor);
				dimension_value_operations_t::sub_replace(m_lines[clear_line]->m_value[i],m_lines[test_line]->m_value[i]);
			}
		}
		else
		{		
			if (except_j == line_index)
			{
				++line_index;
			}
			for (pfx_uindex_t i=line_index; i<dimension_count; ++i)
			{
				dimension_value_operations_t::mul_replace(m_lines[clear_line]->m_value[i],mul_factor);
				dimension_value_operations_t::sub_replace(m_lines[clear_line]->m_value[i],m_lines[test_line]->m_value[i]);
			}
		}

		return mul_factor;
	}

	PFX_INLINE void clear_oneline_same_unsafe (pfx_uindex_t test_line, 
		pfx_uindex_t clear_line,dimension_value_t mul_factor, pfx_uindex_t except_j)
	{
		for (pfx_uindex_t i=0; i<except_j; ++i)
		{
			dimension_value_operations_t::mul_replace(m_lines[clear_line]->m_value[i],mul_factor);
			dimension_value_operations_t::sub_replace(m_lines[clear_line]->m_value[i],m_lines[test_line]->m_value[i]);
		}
		for (pfx_uindex_t i=except_j+1; i<dimension_count; ++i)
		{
			dimension_value_operations_t::mul_replace(m_lines[clear_line]->m_value[i],mul_factor);
			dimension_value_operations_t::sub_replace(m_lines[clear_line]->m_value[i],m_lines[test_line]->m_value[i]);
		}
	}
	PFX_INLINE pfx_uindex_t find_test_line_unsafe (pfx_uindex_t line_index)
	{
		pfx_uindex_t res_index = line_index;
		dimension_value_t max_abs = 0;

		for (pfx_uindex_t i = line_index; i<dimension_count; ++i)
		{
			if (null == m_lines[i])
			{
				continue;
			}
			dimension_value_t tmp_abs = dimension_value_operations::abs(m_lines[i]->m_value[line_index]);
			if ( max_abs < tmp_abs)
			{
				res_index = i;
				max_abs = tmp_abs;
			}
		}

		return res_index;
	}
};

#define PFX_SQUARE_MATRIX_TEMPLATE_DEFS \
	template < class dimension_value_operations, \
	const pfx_usize_t			dimension_count, \
	const pfx_enum_int_t optional_type > 
#define PFX_SQUARE_MATRIX_TEMPLATE_PARAMS  <  dimension_value_operations, dimension_count, optional_type > 

#define  MAT_DIM_VALUE_T	typename dimension_value_operations::dimension_value_t
#define	MAT_DIM_OP_T			typename dimension_value_operations
#define  MAT_VEC						st_pfx_vector < MAT_DIM_VALUE_T, dimension_count >	
#define  MAT_CVEC						pfx_vector < dimension_value_operations, dimension_count, optional_type >
#define  MAT_UNMAT				typename un_pfx_matrix_square < MAT_DIM_VALUE_T, dimension_count >
#define  MAT_MAT_EX				typename pfx_matrix_square_ex < dimension_value_operations, dimension_count, optional_type >
#define	MAT_CMAT					pfx_square_matrix < dimension_value_operations, dimension_count, optional_type >

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
MAT_CMAT::pfx_square_matrix (pfx_boolean_t bIndentify /*= PFX_BOOL_TRUE*/)
{
	if (bIndentify)
	{
		MAT_CMAT::Indentify_matrix(m_mat,1);
	}
	else
	{
		MAT_CMAT::sets(m_mat,0);
	}
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
MAT_CMAT::pfx_square_matrix (dimension_value_t dim_set, pfx_boolean_t bIndentify)
{
	if (bIndentify)
	{
		MAT_CMAT::Indentify_matrix(m_mat,dim_set);
	}
	else
	{
		MAT_CMAT::sets(m_mat,dim_set);
	}
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
MAT_CMAT :: pfx_square_matrix (const dimension_value_t* dim_sets_ptr,
		pfx_usize_t dim_val_count)
{
	if (dim_sets_ptr)
	{
		const pfx_usize_t dim_count = dimension_count*dimension_count;
		if (dim_val_count > dim_count)
		{
			dim_val_count = dim_count;
		}
		for (pfx_uindex_t i=0; i<dim_val_count; ++i)
		{
			m_mat.m_dim[i] = dim_sets_ptr[i];
		}
	}
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
MAT_CMAT :: pfx_square_matrix (const vector_t* vecs_ptr,pfx_usize_t vecs_count)
{
	if (vecs_ptr)
	{
		if (vecs_count > dimension_count)
		{
			vecs_count = dimension_count;
		}
		for (pfx_uindex_t i=0; i<vecs_count; ++i)
		{
			m_mat.m_vector[i] = vecs_ptr[i];
		}
	}

}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
MAT_CMAT :: pfx_square_matrix (const cvector_t* vecs_ptr,pfx_usize_t vecs_count)
{
	if (vecs_ptr)
	{
		if (vecs_count > dimension_count)
		{
			vecs_count = dimension_count;
		}
		for (pfx_uindex_t i=0; i<vecs_count; ++i)
		{
			m_mat.m_vector[i] = vecs_ptr[i].m_dim;
		}
	}
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
MAT_CMAT :: pfx_square_matrix (const vector_t& vec)
{
	for (pfx_uindex_t i=0; i<dimensional_count; ++i)
	{
		m_mat.m_vector[i] = vec;
	}
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
MAT_CMAT :: pfx_square_matrix (const cvector_t& vec)
{
	for (pfx_uindex_t i=0; i<dimension_count; ++i)
	{
		m_mat.m_vector[i] = vec.m_dim;
	}
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
MAT_CMAT :: pfx_square_matrix (const matrix_t& mat)
{
	if (&mat != &m_mat)
	{
		m_mat = mat;
	}
	
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
MAT_CMAT::pfx_square_matrix (const MAT_CMAT& other_)
{
	if (&other_ != this)
	{
		m_mat = other_.m_mat;
	}
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE pfx_usize_t	MAT_CMAT::get_dimensional_count () const
{
	return dimension_count;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE pfx_usize_t	MAT_CMAT::dimensional_count ()
{
	return dimension_count;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_VEC MAT_CMAT::row (pfx_uindex_t row_number) const
{
	MAT_VEC vec;
	if (row_number < dimension_count)
	{
		vec = m_mat.m_vector[row_number];
	}
	else
	{
		MAT_CVEC ::set_all(vec,0);
	}
	return vec;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_VEC MAT_CMAT::column (pfx_uindex_t column_number) const
{
	MAT_VEC vec;
	if (column_number < dimension_count)
	{
		for (pfx_uindex_t i=0; i<dimension_count; ++i)
		{
			vec.m_value [i] = m_mat.m_vector[i].m_value[column_number];
		}
	}
	else
	{
		MAT_CVEC ::set_all(vec,0);
	}
	return vec;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_VEC& MAT_CMAT:: row_reference (pfx_uindex_t row_number)
{
	if (row_number < dimension_count)
	{
		return m_mat.m_vector[row_number];
	}
	else
	{
		return (MAT_CMAT::defualt_vector().m_dim);
	}
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE const MAT_CVEC* MAT_CMAT::row_cvec_ptr (pfx_uindex_t row_number) const
{
	if (row_number < dimension_count)
	{
		return &m_mat.m_vector[row_number];
	}
	else
	{
		return null;
	}
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_CVEC* MAT_CMAT::row_cvec_refptr (pfx_uindex_t row_number)
{
	if (row_number < dimension_count)
	{
		return &m_mat.m_vector[row_number];
	}
	else
	{
		return null;
	}
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_CVEC MAT_CMAT::column_cvec (pfx_uindex_t column_number) const
{
	MAT_CVEC vec;
	if (column_number < dimension_count)
	{
		for (pfx_uindex_t i=0; i<dimension_count; ++i)
		{
			vec.m_dim.m_value [i] = m_mat.m_vector[i].m_value[column_number];
		}
	}
	else
	{
		MAT_CVEC ::set_all(vec,0);
	}
	return vec;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_CMAT& MAT_CMAT::transpose_replace ()
{
	 MAT_CMAT::transpose_matrix(m_mat,m_mat);
	 return *this;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_CMAT MAT_CMAT:: transpose_matrix () const
{
	MAT_CMAT mat;
	MAT_CMAT::transpose_matrix(m_mat,mat.m_mat);
	return mat;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE  MAT_CMAT& MAT_CMAT::mul_repalce (const MAT_CMAT& other_)
{
	MAT_CMAT::matrix_mul_matrix(m_mat,other_.m_mat,m_mat);
	return *this;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE  MAT_CMAT& MAT_CMAT::mul_repalce (const MAT_UNMAT& other_)
{
	MAT_CMAT::matrix_mul_matrix(m_mat,other_,m_mat);
	return *this;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE  MAT_CMAT& MAT_CMAT::mul_repalce (MAT_DIM_VALUE_T val)
{
	MAT_CMAT::matrix_mul_value(m_mat,val,m_mat);
	return *this;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE  MAT_CMAT& MAT_CMAT::add_repalce(const MAT_UNMAT& other_)
{
	MAT_CMAT::matrix_add_matrix(m_mat,other_,m_mat);
	return *this;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
	PFX_INLINE  MAT_CMAT& MAT_CMAT::add_repalce(const MAT_CMAT& other_)
{
	MAT_CMAT::matrix_add_matrix(m_mat,other_.m_mat,m_mat);
	return *this;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE  MAT_CMAT& MAT_CMAT::sub_repalce(const MAT_UNMAT& other_)
{
	MAT_CMAT::matrix_sub_matrix(m_mat,other_,m_mat);
	return *this;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE  MAT_CMAT& MAT_CMAT::sub_repalce(const MAT_CMAT& other_)
{
	MAT_CMAT::matrix_sub_matrix(m_mat,other_.m_mat,m_mat);
	return *this;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE  MAT_CMAT& MAT_CMAT::div_repalce (MAT_DIM_VALUE_T val)
{
	MAT_CMAT::matrix_div_value(m_mat,val,m_mat);
	return *this;
}

// 矩阵行列式的值
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_DIM_VALUE_T MAT_CMAT::determinant (pfx_u32_t delta)
{
	return MAT_CMAT::determinant(m_mat,delta);
}
// 子矩阵的行列式的值
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_DIM_VALUE_T  MAT_CMAT::algebraic_cofactor_determinant 
	(pfx_uindex_t x,pfx_uindex_t y)
{
	return MAT_CMAT::algebraic_cofactor_determinant(m_mat,x,y);
}
// 求伴随矩阵 （方阵）
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_CMAT MAT_CMAT::adjoint_matrix () const
{
	MAT_CMAT res_mat;
	MAT_CMAT::adjoint_matrix(m_mat,res_mat.m_mat);
	return res_mat;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_CMAT* MAT_CMAT::sub_adjoint_matrix 
(cmatrix_t& PARAM_OUT mat,
	pfx_uindex_t offset,
	pfx_usize_t size_) const
{
	MAT_CMAT::adjoint_matrix(m_mat,res_mat.m_mat,offset,size_);
	return &mat;
}

// 使用高斯消元法求秩
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE pfx_usize_t MAT_CMAT::rank_gaussian_elimination (MAT_CMAT& PARAM_OUT result_mat) const
{
	return MAT_CMAT::rank_gaussian_elimination(m_mat,result_mat.m_mat);
}

// 求逆矩阵			样式为 [ A|C ]的矩阵的逆矩阵
//												 0|1
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_CMAT* MAT_CMAT::spec_inverse_matrix (MAT_CMAT& PARAM_OUT mat) const
{
	return MAT_CMAT::spec_inverse_matrix(m_mat,mat.m_mat);
}
// 分块求逆
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_CMAT* MAT_CMAT::inverse_matrix (MAT_CMAT& PARAM_OUT mat) const
{
	return MAT_CMAT::inverse_matrix(m_mat,mat);
}
// 使用高斯消元法求逆
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_CMAT* MAT_CMAT::inverse_matrix_gaussian_elimination 
(MAT_CMAT& PARAM_OUT mat) const
{
	return MAT_CMAT::inverse_matrix_gaussian_elimination(m_mat,mat.m_mat);
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_DIM_VALUE_T& MAT_CMAT::adjoint_matrix_value (const MAT_UNMAT& mat,pfx_uindex_t x,pfx_uindex_t y)
{
	return mat.m_vector[y].m_value[x];
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_DIM_VALUE_T& MAT_CMAT::transpose_matrix_value (const MAT_UNMAT& mat,pfx_uindex_t x,pfx_uindex_t y)
{
	return mat.m_vector[y].m_value[x];
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_CVEC & MAT_CMAT::defualt_vector ()
{
	static MAT_CVEC vec;
	return vec;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT& MAT_CMAT::sets (MAT_UNMAT& mat, MAT_DIM_VALUE_T val)
{
	const pfx_usize_t dim_count = dimension_count*dimension_count;
	for (pfx_uindex_t i=0; i<dim_count; ++i)
	{
		mat.m_dim[i] = val;
	}
	return mat;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT& MAT_CMAT::sets (MAT_UNMAT& mat, const MAT_VEC& vec)
{
	for (pfx_uindex_t i=0; i<dimension_count; ++i)
	{
		mat.m_vector[i] = vec;
	}
	return mat;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT& MAT_CMAT::Indentify_matrix (MAT_UNMAT& mat,
MAT_DIM_VALUE_T val)
{
	pfx_uindex_t ival_index = 0;
	for (pfx_uindex_t i=0; i<dimension_count; ++i)
	{
		for (pfx_uindex_t j=0; j<ival_index; ++j)
		{
			mat.m_vector[i].m_value[j] = 0;
		}
		
		mat.m_vector[i].m_value[ival_index] = val;
		++ival_index;

		for (pfx_uindex_t j=ival_index; j<dimension_count; ++j)
		{
			mat.m_vector[i].m_value[j] = 0;
		}
	}
	return mat;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT& MAT_CMAT::transpose_matrix (const MAT_UNMAT& mat,
MAT_UNMAT& trans_mat)
{
	if (&mat != &trans_mat)
	{
		for (pfx_uindex_t i=0; i<dimension_count; ++i)
		{
			for (pfx_uindex_t j=0; j<dimension_count; ++j)
			{
				trans_mat.m_vector[i].m_value[j] = MAT_CMAT::transpose_matrix_value(mat,i,j);
			}
		}
	}
	else
	{
		const pfx_usize_t half_dim_count = dimension_count/2;
		for (pfx_uindex_t i=0; i<half_dim_count; ++i)
		{
			for (pfx_uindex_t j=0; j<half_dim_count; ++j)
			{
				MAT_DIM_VALUE_T tmpval = MAT_CMAT::transpose_matrix_value(mat,i,j);
				MAT_CMAT::transpose_matrix_value(mat,i,j) = MAT_CMAT::transpose_matrix_value(mat,j,i);
				MAT_CMAT::transpose_matrix_value(mat,j,i) = tmpval;
			}
		}
	}
	return trans_mat;
}

// 矩阵行列式的值
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_DIM_VALUE_T MAT_CMAT::determinant_gaussian_unsafe (MAT_MAT_EX& gaussian_mat,pfx_u32_t delta)
{
	MAT_DIM_VALUE_T det = 1;
	for (pfx_uindex_t i=0; i<dimension_count; ++i)
	{
		pfx_uindex_t j;
		j = gaussian_mat.find_test_line_unsafe(i);
		if (i != j)
		{
			gaussian_mat.swap_line_unsafe(i,j);
			det = -det;
		}
		if (dimension_value_operations::equals(gaussian_mat.m_lines[i]->m_value[i],0,delta))
		{
			det = 0;
			break;
		}
		dimension_value_operations::mul_replace(det, gaussian_mat.m_lines[i]->m_value[i]);		
		
		if (i < dimension_count-1)
		{
			for (pfx_uindex_t k=i+1; k< dimension_count;++k)
			{
				if (dimension_value_operations::equals(gaussian_mat.m_lines[k]->m_value[i],0,delta))
				{
					continue;
				}
				MAT_DIM_VALUE_T mul_factor = gaussian_mat.clear_oneline_unsafe(i,k,i);
				gaussian_mat.restore_oneline_unsafe(k,i,mul_factor);
				
			}
		}
	} 
	return det;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_DIM_VALUE_T MAT_CMAT::determinant (const MAT_UNMAT& mat,pfx_u32_t delta)
{
	MAT_DIM_VALUE_T det;
	if (dimension_count < 4)
	{
		//对角线法
		MAT_DIM_VALUE_T pos;
		MAT_DIM_VALUE_T neg;
		for (pfx_uindex_t j=0; j<dimension_count; ++j )
		{
			pos = 1;
			neg = 1;
			const pfx_usize_t dim_index = dimension_count - 1;
			pfx_uindex_t pos_itr = j;
			pfx_uindex_t neg_itr = dim_index;
			for (pfx_uindex_t i=0; i<dimension_count;++i)
			{
				pos *= mat.m_vector[i].m_value[pos_itr];
				neg *= mat.m_vector[i].m_value[neg_itr];

				if (dim_index == pos_itr)
				{
					pos_itr = 0;
				}
				else
				{
					++pos_itr;
				}

				if (0 == neg_itr)
				{
					neg_itr = dim_index;
				}
				else
				{
					--neg_itr;
				}
			}
			det += (pos - neg);
		}
	}
	else
	{
		MAT_UNMAT mat_cp = mat;
		MAT_MAT_EX gaussian_mat(mat_cp);
		det = MAT_CMAT::determinant_gaussian_unsafe (gaussian_mat,delta);
	}
	return det;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_DIM_VALUE_T MAT_CMAT::algebraic_cofactor_determinant_gaussian 
(matrix_ex_t& gaussian_mat,
pfx_uindex_t x,pfx_uindex_t y,pfx_u32_t delta)
{
	MAT_DIM_VALUE_T det = 1;

	gaussian_mat.m_lines[x] = null;
	pfx_uindex_t j_itr = 0;
	for (pfx_uindex_t i=0; i<dimension_count; ++i)
	{
		if (i == x)
		{
			continue;
		}
		pfx_uindex_t j;
		j = gaussian_mat.find_test_line_unsafe(i);
		if (i != j)
		{
			gaussian_mat.swap_line_unsafe(i,j);
			det = -det;
		}
		if (y == j_itr)
		{
			++j_itr;
		}
		if (dimension_value_operations::equals(gaussian_mat.m_lines[i]->m_value[j_itr],0,delta))
		{
			det = 0;
			break;
		}

		dimension_value_operations::mul_replace(det, gaussian_mat.m_lines[i]->m_value[j_itr]);

		if (i < dimension_count-1)
		{
			for (pfx_uindex_t k=i+1; k< dimension_count;++k)
			{
				if (gaussian_mat.m_lines[k])
				{
					if (dimension_value_operations::equals(gaussian_mat.m_lines[k]->m_value[j_itr],0,delta))
					{
						continue;
					}
					MAT_DIM_VALUE_T mul_factor = gaussian_mat.clear_oneline_unsafe(i,k,j_itr,y);
					gaussian_mat.restore_oneline_unsafe(k,j_itr,mul_factor,y);

				}
				
			}
		}
		++j_itr;
	} 
	return det;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_DIM_VALUE_T MAT_CMAT::algebraic_cofactor_determinant 
(const MAT_UNMAT& mat,pfx_uindex_t x,pfx_uindex_t y,pfx_u32_t delta)
{
	MAT_DIM_VALUE_T det;
	if (dimension_count < 5)
	{
		//对角线法
		MAT_DIM_VALUE_T pos;
		MAT_DIM_VALUE_T neg;
		for (pfx_uindex_t j=0; j<dimension_count; ++j )
		{
			if (j == y)
			{
				continue;
			}
			pos = 1;
			neg = 1;
			const dim_index = dimension_count - 1;
			pfx_uindex_t pos_itr = j;
			pfx_uindex_t neg_itr = dim_index;
			for (pfx_uindex_t i=0; i<dimension_count;++i)
			{
				if (i == x)
				{
					continue;
				}

				if (y != pos_itr)
				{
					pos *= mat.m_vector[i].m_value[pos_itr];
				}

				if (y != neg_itr)
				{
					neg *= mat.m_vector[i].m_value[neg_itr];
				}
				

				if (dim_index = pos_itr)
				{
					pos_itr = 0;
				}
				else
				{
					++pos_itr;
				}

				if (0 == neg_itr)
				{
					neg_itr = dim_index;
				}
				else
				{
					--neg_itr;
				}
			}
			det += (pos - neg);
		}

	}
	return det;
}
// 求伴随矩阵 （方阵）
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT* MAT_CMAT::adjoint_matrix (const MAT_UNMAT& PARAM_IN mat,
	MAT_UNMAT& PARAM_OUT adjoint_mat)
{
	return null;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT* MAT_CMAT::sub_adjoint_matrix (const MAT_UNMAT& PARAM_IN mat,
		MAT_UNMAT& PARAM_OUT adjoint_mat,
		pfx_uindex_t offset,
		pfx_usize_t size_)
{
	return null;
}
// 使用高斯消元法求秩
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE pfx_usize_t MAT_CMAT::rank_gaussian_elimination (const  MAT_UNMAT& PARAM_IN mat,
	MAT_UNMAT& PARAM_OUT result_mat) 
{
	return 0;
}

// 求逆矩阵			样式为 [ A|C ]的矩阵的逆矩阵
//												 0|1
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT* MAT_CMAT::spec_inverse_matrix (const  MAT_UNMAT& PARAM_IN mat,
	MAT_UNMAT& PARAM_OUT inverse_mat)
{
	return null;
}

// 分块求逆
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT* MAT_CMAT::inverse_matrix (const  MAT_UNMAT& PARAM_IN mat,
	MAT_UNMAT& PARAM_OUT inverse_mat)
{
	return null;
}

// 使用高斯消元法求逆
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT* MAT_CMAT::inverse_matrix_gaussian_elimination (const  MAT_UNMAT& PARAM_IN mat,
	MAT_UNMAT& PARAM_OUT inverse_mat)
{
	return null;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT& MAT_CMAT::matrix_mul_value (const MAT_UNMAT& mat, dimension_value_t val,
	MAT_UNMAT& res_mat)
{
	return res_mat;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT& MAT_CMAT::matrix_div_value (const MAT_UNMAT& mat, dimension_value_t val,
	MAT_UNMAT& res_mat)
{
	return res_mat;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT& MAT_CMAT::matrix_add_matrix (const MAT_UNMAT& matA, const MAT_UNMAT& matB,
	MAT_UNMAT& res_mat)
{
	return res_mat;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT& MAT_CMAT::matrix_sub_matrix (const MAT_UNMAT& matA, const MAT_UNMAT& matB,
	MAT_UNMAT& res_mat)
{
	return res_mat;
}

//	// 1*4矩阵 X 4*4矩阵 = 1*4矩阵
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_VEC& MAT_CMAT::matrix_mul_matrix (const MAT_VEC& mat_1x4,const MAT_UNMAT& mat_4x4, 
		MAT_VEC& res_mat1x4)
{
	return res_mat1x4;
}
// 4*4矩阵 X 4*1矩阵 = 4*1矩阵
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_VEC& MAT_CMAT::matrix_mul_matrix (const MAT_UNMAT& mat_4x4,const MAT_VEC& mat_4x1,
	MAT_VEC& res_mat4x1)
{
	return res_mat4x1;
}
// 4*4矩阵 X 4*4矩阵 = 4*4矩阵
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_UNMAT& MAT_CMAT::matrix_mul_matrix (const MAT_UNMAT& matA_4x4,const MAT_UNMAT& matB_4x4,
	MAT_UNMAT& res_mat_4x4)
{
	return res_mat_4x4;
}


PECKER_END

#endif			//PFX_MATRIX_CODES_H_
