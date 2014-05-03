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
	friend class pfx_square_matrix < dimension_value_operations, dimension_count, optional_type >;

	typedef typename dimension_value_operations::dimension_value_t	dimension_value_t;
	typedef typename dimension_value_operations											dimension_value_operations_t;
	typedef st_pfx_vector < dimension_value_t, dimension_count >				vector_t;
	typedef pfx_vector < dimension_value_operations, dimension_count, optional_type >	cvector_t;
	typedef typename un_pfx_matrix_square < dimension_value_t, dimension_count >		matrix_t;
	typedef struct
	{
		dimension_value_t m_factor;
		pfx_uindex_t			m_index;
	}clear_mul_factor_t;

	matrix_t*	m_mat_ptr;
	vector_t*	m_lines[ (!dimension_count?1:dimension_count)];

public:
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
	// unsafe!!!!
	pfx_matrix_square_ex (vector_t* PARAM_IN vec, pfx_nsize_t vec_count):m_mat_ptr(null)
	{
		vec_count = (vec_count > dimension_count)? dimension_count : vec_count;
		m_mat_ptr = (matrix_t*)vec;
		for (pfx_uindex_t i=0; i<vec_count; ++i)
		{
			m_lines[i] = &mat.m_vector[i];
		}
		for (pfx_uindex_t i=vec_count; i<dimension_count; ++i)
		{
			m_lines[i] = 0;
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
	PFX_INLINE pfx_result_t swap_line (pfx_uindex_t i,pfx_uindex_t j)
	{
		RETURN_INVALID_RESULT (!m_mat_ptr,PFX_STATUS_UNINIT);
		RETURN_INVALID_RESULT (((i>=dimension_count) || (j >= dimension_count)),PFX_STATUS_INVALID_PARAMS);
		swap_line_unsafe(i,j);
		return PFX_STATUS_OK;
	}

protected:
	PFX_INLINE void swap_line_unsafe (pfx_uindex_t i,pfx_uindex_t j)
	{
		vector_t* swap_ptr;
		swap_ptr = m_lines [i];
		m_lines[i] = m_lines[j];
		m_lines[j] = swap_ptr;
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
	PFX_INLINE pfx_usize_t rev_clear_oneline_unsafe (pfx_uindex_t clear_line,		
		clear_mul_factor_t* mul_factor, pfx_u32_t delta)
	{
		pfx_uindex_t fac_count = 0;
		pfx_uindex_t itr = 0;
		for (pfx_uindex_t i=dimension_count-1; i>clear_line; --i)
		{
			if (dimension_value_operations_t::equals(m_lines [clear_line]->m_value[i],0,delta))
			{
				continue;
			}
			mul_factor[itr].m_factor = dimension_value_operations_t::div(m_lines[i]->m_value[i], 
				m_lines [clear_line]->m_value[i]);

			mul_factor[itr].m_index = i;
			
			for (pfx_uindex_t j=clear_line; j<dimension_count; ++j)
			{
				dimension_value_operations_t::mul_replace(m_lines[clear_line]->m_value[j],mul_factor[itr].m_factor);
			}
			dimension_value_operations_t::sub_replace(m_lines[clear_line]->m_value[i],m_lines[i]->m_value[i]);

			++itr;
		}
		mul_factor[itr].m_index = INVALID_VALUE;
		return itr;
	}

	PFX_INLINE void rev_clear_oneline_same_unsafe (pfx_uindex_t clear_line,
		const clear_mul_factor_t* PARAM_IN mul_factor)
	{
		pfx_uindex_t fac_count = 0;
		pfx_uindex_t itr = 0;
		for (pfx_uindex_t i = clear_line; i<dimension_count; ++i)
		{
			if (INVALID_VALUE == mul_factor[itr].m_index)
			{
				break;
			}

			for (pfx_uindex_t j=0; j<dimension_count; ++j)
			{
				dimension_value_operations_t::mul_replace(m_lines[clear_line]->m_value[j],
					mul_factor[itr].m_factor);

				dimension_value_operations_t::sub_replace(m_lines[clear_line]->m_value[j],
					m_lines[mul_factor[itr].m_index]->m_value[j]);
			}

			++itr;
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

//#define  MAT_DIM_VALUE_T	typename dimension_value_operations::dimension_value_t
//#define	MAT_DIM_OP_T			typename dimension_value_operations
//#define  MAT_VEC						st_pfx_vector < MAT_DIM_VALUE_T, dimension_count >	
//#define  MAT_CVEC						pfx_vector < dimension_value_operations, dimension_count, optional_type >
//#define  MAT_UNMAT				typename un_pfx_matrix_square < MAT_DIM_VALUE_T, dimension_count >
//#define  MAT_MAT_EX				typename pfx_matrix_square_ex < dimension_value_operations, dimension_count, optional_type >
#define	MAT_CMAT					pfx_square_matrix < dimension_value_operations, dimension_count, optional_type >
#define  TYPE_CMAT					typename	pfx_square_matrix < dimension_value_operations, dimension_count, optional_type >

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
PFX_INLINE TYPE_CMAT::vector_t MAT_CMAT::row (pfx_uindex_t row_number) const
{
	TYPE_CMAT::vector_t vec;
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
PFX_INLINE TYPE_CMAT::vector_t MAT_CMAT::column (pfx_uindex_t column_number) const
{
	TYPE_CMAT::vector_t vec;
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
PFX_INLINE TYPE_CMAT::vector_t& MAT_CMAT:: row_reference (pfx_uindex_t row_number)
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
PFX_INLINE const TYPE_CMAT::cvector_t* MAT_CMAT::row_cvec_ptr (pfx_uindex_t row_number) const
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
PFX_INLINE TYPE_CMAT::cvector_t* MAT_CMAT::row_cvec_refptr (pfx_uindex_t row_number)
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
PFX_INLINE TYPE_CMAT::cvector_t MAT_CMAT::column_cvec (pfx_uindex_t column_number) const
{
	TYPE_CMAT::cvector_t vec;
	if (column_number < dimension_count)
	{
		for (pfx_uindex_t i=0; i<dimension_count; ++i)
		{
			vec.m_dim.m_value [i] = m_mat.m_vector[i].m_value[column_number];
		}
	}
	else
	{
		TYPE_CMAT::cvector_t ::set_all(vec,0);
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
PFX_INLINE  MAT_CMAT& MAT_CMAT::mul_repalce (const TYPE_CMAT::matrix_t& other_)
{
	MAT_CMAT::matrix_mul_matrix(m_mat,other_,m_mat);
	return *this;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE  MAT_CMAT& MAT_CMAT::mul_repalce (TYPE_CMAT::dimension_value_t  val)
{
	MAT_CMAT::matrix_mul_value(m_mat,val,m_mat);
	return *this;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE  MAT_CMAT& MAT_CMAT::add_repalce(const TYPE_CMAT::matrix_t& other_)
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
PFX_INLINE  MAT_CMAT& MAT_CMAT::sub_repalce(const TYPE_CMAT::matrix_t& other_)
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
PFX_INLINE  MAT_CMAT& MAT_CMAT::div_repalce (TYPE_CMAT::dimension_value_t  val)
{
	MAT_CMAT::matrix_div_value(m_mat,val,m_mat);
	return *this;
}

// 矩阵行列式的值
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::dimension_value_t  MAT_CMAT::determinant (pfx_u32_t delta)
{
	return MAT_CMAT::determinant(m_mat,delta);
}
// 子矩阵的行列式的值
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::dimension_value_t   MAT_CMAT::algebraic_cofactor_determinant 
	(pfx_uindex_t x,pfx_uindex_t y)
{
	return MAT_CMAT::algebraic_cofactor_determinant(m_mat,x,y);
}

// 使用高斯消元法求秩
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE pfx_usize_t MAT_CMAT::rank_gaussian (pfx_u32_t delta) const
{
	TYPE_CMAT::matrix_t mat_cp = m_mat;
	return MAT_CMAT::rank_gaussian(m_mat,mat_cp,delta);
}


// 使用高斯消元法求逆
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE MAT_CMAT* MAT_CMAT::inverse_matrix_gaussian_elimination 
(MAT_CMAT& PARAM_OUT mat, pfx_u32_t delta) const
{
	TYPE_CMAT::matrix_t mat_gau = m_mat;
	//TYPE_CMAT::matrix_t mat_;
	//TYPE_CMAT::matrix_t& mat_inv = (&mat == this)?(mat_):(mat.m_mat);
	TYPE_CMAT::matrix_t mat_inv;
	TYPE_CMAT::matrix_ex_t mat_inverse (mat_inv);
	TYPE_CMAT::matrix_ex_t mat_gaussian (mat_gau);
	TYPE_CMAT::matrix_ex_t* res_mat_ptr = MAT_CMAT::inverse_matrix_gaussian_elimination(mat_gaussian, mat_inverse, delta);
	if (res_mat_ptr)
	{
		//if (&mat == this)
		//{
			for (pfx_uindex_t i=0; i<dimension_count; ++i)
			{
				mat.m_mat.m_vector[i] = *mat_inverse.m_lines[i];
			}
		//}
		//else
		//{
		//	for (pfx_uindex_t i=0; i<dimension_count; ++i)
		//	{
		//		if (&mat.m_mat.m_vector[i] != mat_inverse.m_lines[i])
		//		{
		//			MAT_CMAT::vector_t vec_tmp = mat.m_mat.m_vector[i];
		//			mat.m_mat.m_vector[i] = *mat_inverse.m_lines[i];
		//			*mat_inverse.m_lines[i] = vec_tmp;
		//		}
		//	}
		//}

		return &mat;
	}
	else
	{
		return null;
	}

	
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::dimension_value_t & MAT_CMAT::transpose_matrix_value (TYPE_CMAT::matrix_t& mat,pfx_uindex_t x,pfx_uindex_t y)
{
	return mat.m_vector[y].m_value[x];
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::cvector_t & MAT_CMAT::defualt_vector ()
{
	static TYPE_CMAT::cvector_t vec;
	return vec;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::matrix_t& MAT_CMAT::sets (TYPE_CMAT::matrix_t& mat, TYPE_CMAT::dimension_value_t  val)
{
	const pfx_usize_t dim_count = dimension_count*dimension_count;
	for (pfx_uindex_t i=0; i<dim_count; ++i)
	{
		mat.m_dim[i] = val;
	}
	return mat;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::matrix_t& MAT_CMAT::sets (TYPE_CMAT::matrix_t& mat, const TYPE_CMAT::vector_t& vec)
{
	for (pfx_uindex_t i=0; i<dimension_count; ++i)
	{
		mat.m_vector[i] = vec;
	}
	return mat;
}
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::matrix_t& MAT_CMAT::Indentify_matrix (TYPE_CMAT::matrix_t& mat,
TYPE_CMAT::dimension_value_t  val)
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
PFX_INLINE TYPE_CMAT::matrix_t& MAT_CMAT::transpose_matrix (const TYPE_CMAT::matrix_t& mat,
TYPE_CMAT::matrix_t& trans_mat)
{
	if (&mat != &trans_mat)
	{
		for (pfx_uindex_t i=0; i<dimension_count; ++i)
		{
			for (pfx_uindex_t j=0; j<dimension_count; ++j)
			{
				trans_mat.m_vector[i].m_value[j] = MAT_CMAT::transpose_matrix_value((TYPE_CMAT::matrix_t&)mat,i,j);
			}
		}
	}
	else
	{
		for (pfx_uindex_t i=0; i<dimension_count; ++i)
		{
			pfx_uindex_t j=i+1;
			for (; j<dimension_count; ++j)
			{
				TYPE_CMAT::dimension_value_t  tmpval = MAT_CMAT::transpose_matrix_value(trans_mat,i,j);
				MAT_CMAT::transpose_matrix_value(trans_mat,i,j) = MAT_CMAT::transpose_matrix_value(trans_mat,j,i);
				MAT_CMAT::transpose_matrix_value(trans_mat,j,i) = tmpval;
			}
		}
	}
	return trans_mat;
}

// 矩阵行列式的值
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::dimension_value_t  MAT_CMAT::determinant_gaussian_unsafe (TYPE_CMAT::matrix_ex_t& gaussian_mat,pfx_u32_t delta)
{
	TYPE_CMAT::dimension_value_t  det = 1;
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
				TYPE_CMAT::dimension_value_t  mul_factor = gaussian_mat.clear_oneline_unsafe(i,k,i);
				gaussian_mat.restore_oneline_unsafe(k,i,mul_factor);
				
			}
		}
	} 
	return det;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::dimension_value_t  MAT_CMAT::determinant (const TYPE_CMAT::matrix_t& mat,pfx_u32_t delta)
{
	TYPE_CMAT::dimension_value_t  det = 0;
	// release 模式下会自动将没用的分支剃掉，从而达到编译时多态的效果 
	if (dimension_count == 1)
	{
		det = mat.m_vector[0].m_value[0];
	}
	else if (dimension_count < 4)
	{
		//对角线法
		TYPE_CMAT::dimension_value_t  pos;
		TYPE_CMAT::dimension_value_t  neg;
		const pfx_usize_t dim_index = dimension_count - 1;
		pfx_uindex_t neg_itr = dim_index;
		const pfx_uindex_t loop_count = ((dimension_count == 2)?1:dimension_count);
	
		for (pfx_uindex_t j=0; j<loop_count; ++j )		
		{
			pos = 1;
			neg = 1;
			
			pfx_uindex_t pos_itr = j;
			pfx_uindex_t i=0;
			while (i<dimension_count)
			{
				pos *= mat.m_vector[i].m_value[pos_itr];
				neg *= mat.m_vector[i].m_value[neg_itr];

				++i;
				if (i >= dimension_count)
				{
					break;
				}

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
		// 高斯消元法
		TYPE_CMAT::matrix_t mat_cp = mat;
		TYPE_CMAT::matrix_ex_t gaussian_mat(mat_cp);
		det = MAT_CMAT::determinant_gaussian_unsafe (gaussian_mat,delta);
	}
	return det;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::dimension_value_t  MAT_CMAT::algebraic_cofactor_determinant_gaussian_unsafe 
(matrix_ex_t& gaussian_mat,
pfx_uindex_t x,pfx_uindex_t y,pfx_u32_t delta)
{
	TYPE_CMAT::dimension_value_t  det = 1;

	gaussian_mat.m_lines[x] = null;
	pfx_uindex_t j_itr = 0;
	for (pfx_uindex_t i=0; i<dimension_count; ++i)
	{
		if (i == x)
		{
			continue;
		}
		pfx_uindex_t j;
		// 选取主元最大的一行
		j = gaussian_mat.find_test_line_unsafe(i);
		if (i != j)
		{
			// 交换行
			gaussian_mat.swap_line_unsafe(i,j);
			det = -det;
		}
		if (y == j_itr)
		{
			++j_itr;
		}
		// 当主元为0的时候，行列式的值必为0，是不可逆方阵
		if (dimension_value_operations::equals(gaussian_mat.m_lines[i]->m_value[j_itr],0,delta))
		{
			det = 0;
			break;
		}
		// 跌成行列式的值
		dimension_value_operations::mul_replace(det, gaussian_mat.m_lines[i]->m_value[j_itr]);

		// 除主元行外消除主元列位置的其他行的值
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
					// 消除变换
					TYPE_CMAT::dimension_value_t  mul_factor = gaussian_mat.clear_oneline_unsafe(i,k,j_itr,y);
					// 恢复变换
					gaussian_mat.restore_oneline_unsafe(k,j_itr,mul_factor,y);

				}
				
			}
		}
		++j_itr;
	} 
	return det;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::dimension_value_t  MAT_CMAT::algebraic_cofactor_determinant 
(const TYPE_CMAT::matrix_t& mat,pfx_uindex_t x,pfx_uindex_t y,pfx_u32_t delta)
{
	RETURN_INVALID_RESULT ((x >= dimension_count|| y>= dimension_count),0);

	TYPE_CMAT::dimension_value_t  det = 0;
	if (dimension_count == 1)
	{
		return 0;
	}
	else if (dimension_count == 2)
	{
		return det = mat.m_vector[y].m_value[x];
	}
	else if (dimension_count < 5)
	{
		//对角线法
		TYPE_CMAT::dimension_value_t  pos;
		TYPE_CMAT::dimension_value_t  neg;
		const pfx_usize_t dim_index = dimension_count - 1;
		const pfx_uindex_t loop_count = ((dimension_count == 3)?1:dim_index);
		const pfx_uindex_t loop_pos_index = (0 != y)?(0):(1);
		const pfx_uindex_t loop_neg_index = (dim_index != y)?(dim_index):(dim_index-1);

		pfx_uindex_t neg_itr_j = loop_neg_index;
		pfx_uindex_t pos_ex = 0;//(0 != y)?(0):(1);
		for (pfx_uindex_t j=0; j<loop_count; ++j )		
		{
			pos = 1;
			neg = 1;
			pfx_uindex_t pos_itr_j = pos_ex + j;
		
			if (pos_itr_j == y)
			{
				++pos_ex;
				++pos_itr_j;
			}
			
			pfx_uindex_t itr_i = 0;
			pfx_uindex_t i =0;

			while (i < dim_index)
			{
				if (itr_i == x)
				{
					++itr_i;
				}
				pos *= mat.m_vector[itr_i].m_value[pos_itr_j];
				neg *= mat.m_vector[itr_i].m_value[neg_itr_j];
				++i;

				if (i >= dim_index)
				{
					break;
				}
				++itr_i;

				pos_itr_j = (loop_neg_index == pos_itr_j)?(loop_pos_index):(++pos_itr_j);
				neg_itr_j = (loop_pos_index == neg_itr_j)?(loop_neg_index):(--neg_itr_j);
				
				if (pos_itr_j == y)
				{
					++pos_itr_j;
				}
				if (neg_itr_j == y)
				{
					--neg_itr_j;
				}
			}
			det += (pos - neg);
		}

	}
	else
	{
		// 高斯消元法
		TYPE_CMAT::matrix_t mat_cp = mat;
		TYPE_CMAT::matrix_ex_t gaussian_mat(mat_cp);
		det = MAT_CMAT::algebraic_cofactor_determinant_gaussian_unsafe (gaussian_mat,x,y,delta);
	}
	return det;
}

// 使用高斯消元法求秩
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE pfx_usize_t MAT_CMAT::rank_gaussian (const  TYPE_CMAT::matrix_t& PARAM_IN mat,
	TYPE_CMAT::matrix_t& PARAM_OUT result_mat, pfx_u32_t delta) 
{
	pfx_usize_t rank = 0;
	TYPE_CMAT::matrix_t mat_cp;
	TYPE_CMAT::matrix_ex_t gaussian_mat(result_mat);
	if (&result_mat == &mat)
	{
		mat_cp = mat;
		gaussian_mat.init(mat_cp);
	}

	for (pfx_uindex_t i=0; i<dimension_count; ++i)
	{
		pfx_uindex_t j;
		j = gaussian_mat.find_test_line_unsafe(i);
		if (i != j)
		{
			gaussian_mat.swap_line_unsafe(i,j);
		}
		if (dimension_value_operations::equals(gaussian_mat.m_lines[i]->m_value[i],0,delta))
		{
			break;
		}
		++rank;

		if (i < dimension_count-1)
		{
			for (pfx_uindex_t k=i+1; k< dimension_count;++k)
			{
				if (dimension_value_operations::equals(gaussian_mat.m_lines[k]->m_value[i],0,delta))
				{
					continue;
				}
				TYPE_CMAT::dimension_value_t  mul_factor = gaussian_mat.clear_oneline_unsafe(i,k,i);
				//gaussian_mat.restore_oneline_unsafe(k,i,mul_factor);
			}
		}
	} 
	return rank;
}


PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::matrix_t* MAT_CMAT::inverse_matrix (TYPE_CMAT::matrix_ex_t& PARAM_INOUT mat,
	TYPE_CMAT::matrix_ex_t& PARAM_OUT indt_mat, pfx_u32_t delta)
{
	RETURN_INVALID_RESULT (null == indt_mat.m_mat_ptr || null == gaussian_mat.m_mat_ptr,
		null);
	if (0 == dimension_count)
	{
		return null;
	}
	else if (1 == dimension_count)
	{
		indt_mat.m_lines[0]->m_value[0] = dimension_value_operations::div(1,indt_mat.m_lines[0]->m_value[0]);
		return &indt_mat;
	}
	else if (dimension_count < 4)
	{

		return null;
	}
	else
	{
		return inverse_matrix_gaussian_elimination(mat,indt_mat,delta);
	}
	
}

// 使用高斯消元法求逆
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::matrix_ex_t* MAT_CMAT::inverse_matrix_gaussian_elimination (TYPE_CMAT::matrix_ex_t& PARAM_INOUT gaussian_mat,
	TYPE_CMAT::matrix_ex_t& PARAM_OUT indt_mat, pfx_u32_t delta)
{
	RETURN_INVALID_RESULT (null == indt_mat.m_mat_ptr || null == gaussian_mat.m_mat_ptr,
		null);
	if (0 == dimension_count)
	{
		return null;
	}
	if (1 == dimension_count)
	{
		indt_mat.m_lines[0]->m_value[0] = dimension_value_operations::div(1,indt_mat.m_lines[0]->m_value[0]);
		return &indt_mat;
	}
	pfx_usize_t rank = 0;
	//TYPE_CMAT::matrix_t mat_cp = mat;

	//TYPE_CMAT::matrix_ex_t gaussian_mat(mat_cp);
	MAT_CMAT::Indentify_matrix(*indt_mat.m_mat_ptr,1);
	//TYPE_CMAT::matrix_ex_t indt_mat(inverse_mat);
	// 原理：
	// (A | E) ------初等变换-----> (E | A^(-1))

	// 第一步，先将原矩阵按高斯消元法三角化, 单位阵做一样的操作
	for (pfx_uindex_t i=0; i<dimension_count; ++i)
	{
		pfx_uindex_t j;
		j = gaussian_mat.find_test_line_unsafe(i);
		if (i != j)
		{
			gaussian_mat.swap_line_unsafe(i,j);
			indt_mat.swap_line_unsafe(i,j);
		}
		if (dimension_value_operations::equals(gaussian_mat.m_lines[i]->m_value[i],0,delta))
		{
			break;
		}
		++rank;

		if (i < dimension_count-1)
		{
			for (pfx_uindex_t k=i+1; k< dimension_count;++k)
			{
				if (dimension_value_operations::equals(gaussian_mat.m_lines[k]->m_value[i],0,delta))
				{
					continue;
				}
				TYPE_CMAT::dimension_value_t  mul_factor = gaussian_mat.clear_oneline_unsafe(i,k,i);
				indt_mat.clear_oneline_same_unsafe(i,k,mul_factor);
			}
		}
	} 
	// 秩为0，矩阵不可逆
	RETURN_INVALID_RESULT (0 == rank,null);
	// 第二步，将三角阵转为对角线
	TYPE_CMAT::matrix_ex_t::clear_mul_factor_t mul_factor[dimension_count+1];
	if (dimension_count > 2)
	{
		for (pfx_uindex_t i=(dimension_count-2); i>0; --i)
		{
			gaussian_mat.rev_clear_oneline_unsafe(i,mul_factor,delta);
			indt_mat.rev_clear_oneline_same_unsafe(i,mul_factor);
		}
	}

	gaussian_mat.rev_clear_oneline_unsafe(0,mul_factor,delta);
	indt_mat.rev_clear_oneline_same_unsafe(0,mul_factor);

	// 第三步,单位化
	for (pfx_uindex_t i=0; i<dimension_count;++i)
	{
		TYPE_CMAT::cvector_t::div_replace (*indt_mat.m_lines[i],gaussian_mat.m_lines[i]->m_value[i]);
	}
	return &indt_mat;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::matrix_t& MAT_CMAT::matrix_mul_value (const TYPE_CMAT::matrix_t& mat, dimension_value_t val,
	TYPE_CMAT::matrix_t& res_mat)
{
	return res_mat;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::matrix_t& MAT_CMAT::matrix_div_value (const TYPE_CMAT::matrix_t& mat, dimension_value_t val,
	TYPE_CMAT::matrix_t& res_mat)
{
	return res_mat;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::matrix_t& MAT_CMAT::matrix_add_matrix (const TYPE_CMAT::matrix_t& matA, const TYPE_CMAT::matrix_t& matB,
	TYPE_CMAT::matrix_t& res_mat)
{
	return res_mat;
}

PFX_SQUARE_MATRIX_TEMPLATE_DEFS
PFX_INLINE TYPE_CMAT::matrix_t& MAT_CMAT::matrix_sub_matrix (const TYPE_CMAT::matrix_t& matA, const TYPE_CMAT::matrix_t& matB,
	TYPE_CMAT::matrix_t& res_mat)
{
	return res_mat;
}

// 1*n矩阵 X n*n矩阵 = 1*n矩阵
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
	PFX_INLINE TYPE_CMAT::vector_t& MAT_CMAT::matrix_mul_matrix (const vector_t& mat_1xn,const matrix_t& mat_nxn, 
	vector_t& res_mat1xn)
{
	return res_mat1xn;
}
	// n*n矩阵 X n*1矩阵 = n*1矩阵
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
	PFX_INLINE TYPE_CMAT::vector_t& MAT_CMAT::matrix_mul_matrix (const matrix_t& mat_nxn,const vector_t& mat_nx1,
	vector_t& res_matnx1)
{
	return res_matnx1;
}
	// n*n矩阵 X n*n矩阵 = n*n矩阵
PFX_SQUARE_MATRIX_TEMPLATE_DEFS
	PFX_INLINE TYPE_CMAT::matrix_t& MAT_CMAT::matrix_mul_matrix (const matrix_t& matA_nxn,const matrix_t& matB_nxn,
	matrix_t& res_mat_nxn)
{
	return res_mat_nxn;
}


PECKER_END

#endif			//PFX_MATRIX_CODES_H_
