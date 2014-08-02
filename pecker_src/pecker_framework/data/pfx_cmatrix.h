/*
 * pfx_cmatrix.h
 *
 *  Created on: 2013-8-25
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CMATRIX_H_
#define		PFX_CMATRIX_H_

#include "../pfx_defines.h"
#include "pfx_cvector.h"

PECKER_BEGIN

template < class dim_type, const usize__t dim_count >
struct square_matrix_data;

template < class dim_type, const usize__t dim_count >
struct square_matrix_data_table
{
	typedef dim_type dim_t;
	typedef vector_data< dim_t, dim_count > vector_t;
	typedef square_matrix_data_table< dim_t, dim_count > matrix_ex_t;
	typedef square_matrix_data< dim_t, dim_count > matrix_t;

	vector_t* m_vec[(0 == dim_count)?1:dim_count];

	square_matrix_data_table ()
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			m_vec[i] = null;
		}
	}
	square_matrix_data_table (matrix_t& attach_matrix)
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			m_vec[i] = attach_matrix[i];
		}
	}
	square_matrix_data_table (matrix_ex_t& attach_matrix)
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			m_vec[i] = attach_matrix[i];
		}
	}

	static PFX_INLINE usize__t vector_dim_count ()
	{
		return dim_count;
	}
	PFX_INLINE vector_t*& operator[] (uindex_t i)
	{
		return m_vec[i];
	}
	PFX_INLINE const vector_t* const& operator[] (uindex_t i) const
	{
		return m_vec[i];
	}

	PFX_INLINE matrix_t& to_matrix (matrix_t& PARAM_OUT tomat) const
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			if (m_vec[i] && m_vec[i] != tomat[i])
			{
				*tomat[i] = *m_vec[i];
			}
		}
		return tomat;
	}
	PFX_INLINE matrix_ex_t& copy_to_matrix_ex (matrix_ex_t& PARAM_OUT tomat) const
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			if (tomat[i] && tomat[i] != m_vec[i])
			{
				*tomat[i] = *m_vec[i];
			}
		}
		return tomat;
	}
	PFX_INLINE matrix_ex_t& copy_to_matrix_ex_unsafe (matrix_ex_t& PARAM_OUT tomat) const
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			*tomat[i] = *m_vec[i];
		}
		return tomat;
	}
};

template < class dim_type, const usize__t dim_count >
struct square_matrix_data
{
	typedef dim_type dim_t;
	typedef vector_data< dim_t, dim_count > vector_t;
	typedef square_matrix_data< dim_t, dim_count > matrix_t;
	typedef square_matrix_data_table< dim_t, dim_count > matrix_ex_t;

	vector_t m_vec[(0 == dim_count)?1:dim_count];

	square_matrix_data ()
	{}
	square_matrix_data (matrix_t& other_matrix)
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			m_vec[i] = *other_matrix[i];
		}
	}
	square_matrix_data (matrix_ex_t& other_matrix)
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			if (other_matrix[i])
			{
				m_vec[i] = *other_matrix[i];
			}
		}
	}

	static PFX_INLINE usize__t vector_dim_count ()
	{
		return dim_count;
	}
	PFX_INLINE vector_t* operator[] (uindex_t i)
	{
		return &m_vec[i];
	}
	PFX_INLINE const vector_t* operator[] (uindex_t i) const
	{
		return &m_vec[i];
	}

	PFX_INLINE matrix_ex_t& to_matrix_ex (matrix_ex_t& PARAM_OUT tomat)
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			tomat[i] = &m_vec[i];
		}
		return tomat;
	}
	PFX_INLINE matrix_ex_t& copy_to_matrix_ex (matrix_ex_t& PARAM_OUT tomat) const
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			if (tomat[i] && tomat[i] != &m_vec[i])
			{
				*tomat[i] = *m_vec[i];
			}
		}
		return tomat;
	}
	PFX_INLINE matrix_ex_t& copy_to_matrix_ex_unsafe (matrix_ex_t& PARAM_OUT tomat) const
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			*tomat[i] = *m_vec[i];
		}
		return tomat;
	}
};

template < class dim_type, const usize__t dim_count >
struct square_matrix_data_ex
{
	typedef dim_type dim_t;
	typedef vector_data< dim_t, dim_count > vector_t;
	typedef square_matrix_data< dim_t, dim_count > matrix_t;
	typedef square_matrix_data_table< dim_t, dim_count > matrix_ex_t;
	typedef square_matrix_data_ex< dim_t, dim_count > matrix_xt;

private:
	matrix_t m_mat;
	matrix_ex_t m_mat_table;
public:
	square_matrix_data_ex ()
	{
		m_mat.to_matrix_ex(m_mat_table);
	};
	square_matrix_data_ex (matrix_t& other_matrix)
	{
		m_mat.m_vec = other_matrix.m_vec;
		m_mat.to_matrix_ex(m_mat_table);
	}
	square_matrix_data_ex (matrix_ex_t& other_matrix)
	{
		m_mat.to_matrix_ex(m_mat_table);
		for (uindex_t i=0; i<dim_count; ++i)
		{
			if (other_matrix[i])
			{
				*m_mat[i] = *other_matrix[i];
			}
		}
	}
	square_matrix_data_ex (matrix_xt& other_matrix)
	{
		m_mat.to_matrix_ex(m_mat_table);
		m_mat.m_vec = other_matrix.m_mat.m_vec;
	}

	static PFX_INLINE usize__t vector_dim_count ()
	{
		return dim_count;
	}
	PFX_INLINE vector_t* operator[] (uindex_t i)
	{
		return m_mat_table[i];
	}
	PFX_INLINE const vector_t* operator[] (uindex_t i) const
	{
		return m_mat_table[i];
	}
	PFX_INLINE void swap (uindex_t i, uindex_t j)
	{
		if (i < dim_count && j < dim_count)
		{
			vector_t* temp;
			temp = m_mat_table[i];
			m_mat_table[i] = m_mat_table[j];
			m_mat_table[j] = m_mat_table[i];
		}
	}
};

template< class dim_type,
const usize__t dim_count,
const enum_int_t optional_type = 0 >
class SquareMatrixX
{
public:
	typedef dim_type dim_t;
	typedef vector_data< dim_t, dim_count > vector_t;
	typedef square_matrix_data< dim_t, dim_count > matrix_t;
	typedef square_matrix_data_table< dim_t, dim_count > matrix_ex_t;
	typedef square_matrix_data_ex< dim_t, dim_count > matrix_xt;
	typedef VectorX< dim_type, dim_count, optional_type > cvector_t;
	typedef SquareMatrixX< dim_type, dim_count, optional_type > cmatrix_t;

	typedef typename vector_base_op_traits < vector_t, optional_type >::dim_alg_t dim_alg_t;
	typedef typename vector_base_op_traits < vector_t, optional_type >::vec_alg_t vec_alg_t;
	typedef typename square_matrix_op_traits < cmatrix_t, optional_type >::matrix_alg_t matrix_alg_t;
	typedef typename matrix_alg_t::cw_buffer_t cw_buffer_t;
	typedef typename matrix_alg_t::clr_mul_factor_t clr_mul_factor_t;

	matrix_t m_mat;
public:
	SquareMatrixX ();
	SquareMatrixX (dim_t val, boolean_t bIndentify = PFX_BOOL_FALSE);
	SquareMatrixX (dim_t x00, dim_t x01, dim_t x02, dim_t x03,
			dim_t x10, dim_t x11, dim_t x12, dim_t x13,
			dim_t x20, dim_t x21, dim_t x22, dim_t x23,
			dim_t x30, dim_t x31, dim_t x32, dim_t x33);
	SquareMatrixX (const vector_t* __vectors, usize__t vector_count);
	SquareMatrixX (const cvector_t* __vectors, usize__t vector_count);
	SquareMatrixX (const matrix_ex_t& mat);
	SquareMatrixX (const matrix_t& mat);
	SquareMatrixX (const cmatrix_t& mat);
public:
	PFX_INLINE cmatrix_t& indentify_replace (dim_t val);

	PFX_INLINE cmatrix_t& transpose_replace ();

	PFX_INLINE cmatrix_t& transpose (cmatrix_t &mat) const;

	PFX_INLINE cmatrix_t& mul_replace (const cmatrix_t& other_mat, cw_buffer_t* exten_buffer = null);
	PFX_INLINE cmatrix_t& mul_replace (const matrix_ex_t& other_mat, cw_buffer_t* exten_buffer = null);
	PFX_INLINE cmatrix_t& mul_replace (const matrix_t& other_mat, cw_buffer_t* exten_buffer = null);
	PFX_INLINE cmatrix_t mul (const cmatrix_t& other_mat, cw_buffer_t* exten_buffer = null) const;
	PFX_INLINE cmatrix_t mul (const matrix_ex_t& other_mat, cw_buffer_t* exten_buffer = null) const;
	PFX_INLINE cmatrix_t mul (const matrix_t& other_mat, cw_buffer_t* exten_buffer = null) const;

	PFX_INLINE dim_t det (u32_t delta = MID_PRECISION_QUALIFER_VAL) const;
	PFX_INLINE usize__t rank (u32_t delta = MID_PRECISION_QUALIFER_VAL) const;
	PFX_INLINE cmatrix_t& inverse_matrix(cmatrix_t& inverse_matrix, cmatrix_t& extern_matrix,
			u32_t delta = MID_PRECISION_QUALIFER_VAL) const;
public:
	static PFX_INLINE usize__t vector_dim_count ()
	{
		return dim_count;
	}
	PFX_INLINE vector_t* operator[] (uindex_t i)
	{
		if (i < dim_count)
		{
			return m_mat[i];
		}
		else
		{
			return null;
		}

	}
	PFX_INLINE const vector_t* operator[] (uindex_t i) const
	{
		if (i < dim_count)
		{
			return m_mat[i];
		}
		else
		{
			return null;
		}

	}

	static PFX_INLINE cmatrix_t& indentify (cmatrix_t& mat, dim_t val);
	static PFX_INLINE cvector_t mul (const cvector_t& vec, const cmatrix_t& mat);
	static PFX_INLINE cvector_t& mul_replace (cvector_t& vec, const cmatrix_t& mat);

	static PFX_INLINE matrix_t* matrix_pointer (cmatrix_t* __matrix)
	{
		return (matrix_t*)__matrix;
	}
	static PFX_INLINE const matrix_t* matrix_pointer (const cmatrix_t* __matrix)
	{
		return (const matrix_t*)__matrix;
	}
	static PFX_INLINE cmatrix_t* matrix_pointer (matrix_t* __matrix)
	{
		return (cmatrix_t*)__matrix;
	}
	static PFX_INLINE const cmatrix_t* matrix_pointer (const matrix_t* __matrix)
	{
		return (const cmatrix_t*)__matrix;
	}
	static PFX_INLINE matrix_t& matrix_ref (cmatrix_t& __matrix)
	{
		return __matrix.m_mat;
	}
	static PFX_INLINE const matrix_t& matrix_ref (const cmatrix_t& __matrix)
	{
		return __matrix.m_mat;
	}
	static PFX_INLINE cmatrix_t& matrix_ref (matrix_t& __matrix)
	{
		return (cmatrix_t&)__matrix;
	}
	static PFX_INLINE const cmatrix_t& matrix_ref (const matrix_t& __matrix)
	{
		return (const cmatrix_t&)__matrix;
	}

	static PFX_INLINE typename matrix_alg_t::matrix_t matrix_reference (matrix_t& __matrix)
	{
		return (const typename matrix_alg_t::matrix_t)__matrix.m_vec;
	}
	static PFX_INLINE const typename matrix_alg_t::matrix_t matrix_reference
	(const matrix_t& __matrix)
	{
		return (const typename matrix_alg_t::matrix_t)__matrix.m_vec;
	}
	static PFX_INLINE typename matrix_alg_t::matrix_ex_t matrix_reference (matrix_ex_t& __matrix)
	{
		return (typename matrix_alg_t::matrix_ex_t)__matrix.m_vec;
	}
	static PFX_INLINE const typename matrix_alg_t::matrix_ex_t matrix_reference
	(const matrix_ex_t& __matrix)
	{
		return (const typename matrix_alg_t::matrix_ex_t)__matrix.m_vec;
	}

};

template< class dim_type,
const usize__t dim_count,
const enum_int_t optional_type = 0 >
class SquareMatrixEX_unsafe
{
public:
	typedef  dim_type dim_t;
	typedef  vector_data< dim_t, dim_count > vector_t;
	typedef  square_matrix_data< dim_t, dim_count > matrix_t;
	typedef  square_matrix_data_table< dim_t, dim_count > matrix_ex_t;
	typedef  square_matrix_data_ex< dim_t, dim_count > matrix_xt;
	typedef  VectorX< dim_type, dim_count, optional_type > cvector_t;
	typedef  SquareMatrixX< dim_type, dim_count, optional_type > cmatrix_t;
	typedef  SquareMatrixEX_unsafe< dim_type, dim_count, optional_type > cmatrix_ex_t;

	typedef typename vector_base_op_traits < vector_t, optional_type >::dim_alg_t dim_alg_t;
	typedef typename vector_base_op_traits < vector_t, optional_type >::vec_alg_t vec_alg_t;
	typedef typename square_matrix_op_traits < cmatrix_t, optional_type >::matrix_alg_t matrix_alg_t;

	typedef typename matrix_alg_t::cw_buffer_t cw_buffer_t;
	typedef typename matrix_alg_t::clr_mul_factor_t clr_mul_factor_t;
private:
	matrix_ex_t m_mat;
public:
	SquareMatrixEX_unsafe ();
	SquareMatrixEX_unsafe (matrix_t& mat);
	SquareMatrixEX_unsafe (matrix_ex_t& mat);
	SquareMatrixEX_unsafe (cmatrix_t& mat);
	SquareMatrixEX_unsafe (cmatrix_ex_t& mat);

	PFX_INLINE const matrix_ex_t& const_reference () const;
public:
	PFX_INLINE cmatrix_ex_t& indentify_replace (dim_t val = 1);

	PFX_INLINE cmatrix_ex_t& transpose_replace ();

	PFX_INLINE cmatrix_ex_t& transpose (cmatrix_ex_t &mat) const;

	PFX_INLINE cmatrix_ex_t& mul_replace (const cmatrix_t& other_mat, cw_buffer_t* exten_buffer = null);
	PFX_INLINE cmatrix_ex_t& mul_replace (const cmatrix_ex_t& other_mat, cw_buffer_t* exten_buffer = null);
	PFX_INLINE cmatrix_ex_t& mul_replace (const matrix_t& other_mat, cw_buffer_t* exten_buffer = null);

	PFX_INLINE dim_t det (u32_t delta = MID_PRECISION_QUALIFER_VAL) const;
	PFX_INLINE usize__t rank (u32_t delta = MID_PRECISION_QUALIFER_VAL) const;
	PFX_INLINE cmatrix_ex_t& inverse_matrix(cmatrix_ex_t& inverse_matrix, cmatrix_ex_t& extern_matrix,
			u32_t delta = MID_PRECISION_QUALIFER_VAL) const;
public:
	static PFX_INLINE usize__t vector_dim_count ()
	{
		return dim_count;
	}
	PFX_INLINE vector_t* operator[] (uindex_t i)
	{
		if (i < dim_count)
		{
			return m_mat[i];
		}
		else
		{
			return null;
		}

	}
	PFX_INLINE const vector_t* operator[] (uindex_t i) const
	{
		if (i < dim_count)
		{
			return m_mat[i];
		}
		else
		{
			return null;
		}

	}

	static PFX_INLINE typename matrix_alg_t::matrix_t matrix_reference (matrix_t& __matrix)
	{
		return (const typename matrix_alg_t::matrix_t)__matrix.m_vec;
	}
	static PFX_INLINE const typename matrix_alg_t::matrix_t matrix_reference
	(const matrix_t& __matrix)
	{
		return (const typename matrix_alg_t::matrix_t)__matrix.m_vec;
	}
	static PFX_INLINE typename matrix_alg_t::matrix_ex_t matrix_reference (matrix_ex_t& __matrix)
	{
		return (typename matrix_alg_t::matrix_ex_t)__matrix.m_vec;
	}
	static PFX_INLINE const typename matrix_alg_t::matrix_ex_t matrix_reference
	(const matrix_ex_t& __matrix)
	{
		return (const typename matrix_alg_t::matrix_ex_t)__matrix.m_vec;
	}

	static PFX_INLINE cmatrix_ex_t& indentify (cmatrix_ex_t& mat, dim_t val = 0);
	static PFX_INLINE cvector_t mul (const cvector_t& vec, const cmatrix_ex_t& mat);
	static PFX_INLINE cvector_t& mul_replace (cvector_t& vec, const cmatrix_ex_t& mat);
};

PECKER_END

#endif			//PFX_CMATRIX_H_
