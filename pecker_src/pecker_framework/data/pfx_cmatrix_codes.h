﻿/*
 * pfx_cmatrix_codes.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CMATRIX_CODES_H_
#define		PFX_CMATRIX_CODES_H_

#include "../pfx_defines.h"
#include "pfx_cmatrix.h"

PECKER_BEGIN

//////////////////////////////////////////////////////////////////////////
#define PFX_SQE_CMAT_TEMPLATE template< class dim_type, const usize__t dim_count, const enum_int_t optional_type >
#define  PFX_SQE_CMAT  SquareMatrixX< dim_type, dim_count, optional_type  >
#define  PFX_SQE_CMAT_TYPE typename SquareMatrixX< dim_type, dim_count, optional_type  >

PFX_SQE_CMAT_TEMPLATE
PFX_SQE_CMAT:: SquareMatrixX ()
{
	;
}

PFX_SQE_CMAT_TEMPLATE
PFX_SQE_CMAT::SquareMatrixX (PFX_SQE_CMAT_TYPE::dim_t val, 
boolean_t bIndentify)
{
	typedef PFX_SQE_CMAT_TYPE::vec_alg_t		vec_alg_t;
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t	matrix_alg_t;
	if (bIndentify)
	{
		matrix_alg_t::Indentify_matrix(dim_count, m_mat.m_vec, val, 0);
	}
	else
	{
		vec_alg_t::init_matrix (m_mat, val, dim_count);
	}
	
}
PFX_SQE_CMAT_TEMPLATE
PFX_SQE_CMAT::SquareMatrixX (PFX_SQE_CMAT_TYPE::dim_t x00, PFX_SQE_CMAT_TYPE::dim_t x01, 
	PFX_SQE_CMAT_TYPE::dim_t x02, PFX_SQE_CMAT_TYPE::dim_t x03,
	PFX_SQE_CMAT_TYPE::dim_t x10, PFX_SQE_CMAT_TYPE::dim_t x11, 
	PFX_SQE_CMAT_TYPE::dim_t x12, PFX_SQE_CMAT_TYPE::dim_t x13,
	PFX_SQE_CMAT_TYPE::dim_t x20, PFX_SQE_CMAT_TYPE::dim_t x21, 
	PFX_SQE_CMAT_TYPE::dim_t x22, PFX_SQE_CMAT_TYPE::dim_t x23,
	PFX_SQE_CMAT_TYPE::dim_t x30, PFX_SQE_CMAT_TYPE::dim_t x31, 
	PFX_SQE_CMAT_TYPE::dim_t x32, PFX_SQE_CMAT_TYPE::dim_t x33)
{
	switch (dim_count)
	{
	case 0:
	case 1:
		m_mat.m_vec[0][0] = x00;
		break;
	case 2:
		m_mat.m_vec[0][0] = x00;
		m_mat.m_vec[0][1] = x01;
		m_mat.m_vec[1][0] = x02;
		m_mat.m_vec[1][1] = x03;
		break;
	case 3:
		m_mat.m_vec[0][0] = x00;
		m_mat.m_vec[0][1] = x01;
		m_mat.m_vec[0][2] = x02;
		m_mat.m_vec[1][0] = x03;
		m_mat.m_vec[1][1] = x10;
		m_mat.m_vec[1][2] = x11;
		m_mat.m_vec[2][0] = x12;
		m_mat.m_vec[2][1] = x13;
		m_mat.m_vec[2][2] = x20;
		break;
	default:
		m_mat.m_vec[0][0] = x00;
		m_mat.m_vec[0][1] = x01;
		m_mat.m_vec[0][2] = x02;
		m_mat.m_vec[0][3] = x03;
		m_mat.m_vec[1][0] = x10;
		m_mat.m_vec[1][1] = x11;
		m_mat.m_vec[1][2] = x12;
		m_mat.m_vec[1][3] = x13;
		m_mat.m_vec[2][0] = x20;
		m_mat.m_vec[2][1] = x21;
		m_mat.m_vec[2][2] = x22;
		m_mat.m_vec[2][3] = x23;
		m_mat.m_vec[3][0] = x30;
		m_mat.m_vec[3][1] = x31;
		m_mat.m_vec[3][2] = x32;
		m_mat.m_vec[3][3] = x33;
		break;
	}
}

PFX_SQE_CMAT_TEMPLATE
PFX_SQE_CMAT::SquareMatrixX (const PFX_SQE_CMAT_TYPE::vector_t* __vectors, 
usize__t vector_count)
{
	typedef PFX_SQE_CMAT_TYPE::vec_alg_t		vec_alg_t;
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t	matrix_alg_t;
	if (vector_count > dim_count)
	{
		vector_count = dim_count;
	}

	for (uindex_t i=0; i<dim_count; ++i)
	{
		*m_mat[i] = __vectors[i];
	}
}

PFX_SQE_CMAT_TEMPLATE
PFX_SQE_CMAT::SquareMatrixX (const PFX_SQE_CMAT_TYPE::cvector_t* __vectors, 
	usize__t vector_count)
{
	typedef PFX_SQE_CMAT_TYPE::vec_alg_t		vec_alg_t;
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t	matrix_alg_t;
	if (vector_count > dim_count)
	{
		vector_count = dim_count;
	}

	for (uindex_t i=0; i<dim_count; ++i)
	{
		*m_mat[i] = __vectors[i].reference();
	}
}

PFX_SQE_CMAT_TEMPLATE
PFX_SQE_CMAT::SquareMatrixX (const PFX_SQE_CMAT_TYPE::matrix_ex_t& mat)
{
	typedef PFX_SQE_CMAT_TYPE::vec_alg_t		vec_alg_t;
	typedef PFX_SQE_CMAT_TYPE::matrix_ex_t	matrix_ex_t;
	mat.to_matrix (m_mat);
}

PFX_SQE_CMAT_TEMPLATE
PFX_SQE_CMAT::SquareMatrixX (const PFX_SQE_CMAT_TYPE::matrix_t& mat)
{
	if (&m_mat != &mat)
	{
		m_mat = mat;
	}
}

PFX_SQE_CMAT_TEMPLATE
PFX_SQE_CMAT::SquareMatrixX (const PFX_SQE_CMAT_TYPE::cmatrix_t& mat)
{
	if (this != &mat)
	{
		m_mat = mat.m_mat;
	}
}

PFX_SQE_CMAT_TEMPLATE
PFX_INLINE PFX_SQE_CMAT_TYPE::cmatrix_t& PFX_SQE_CMAT::
indentify_replace (PFX_SQE_CMAT_TYPE::dim_t val)
{
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t matrix_alg_t;
	typename matrix_alg_t::matrix_t mat = matrix_reference (this->m_mat);
	typename matrix_alg_t::Indentify_matrix (dim_count, mat, val, 0);
	return *this;
}

PFX_SQE_CMAT_TEMPLATE
PFX_INLINE PFX_SQE_CMAT_TYPE::cmatrix_t& PFX_SQE_CMAT::transpose_replace ()
{
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t matrix_alg_t;
	typename matrix_alg_t::matrix_t mat = matrix_reference (this->m_mat);
	typename matrix_alg_t::transpose_matrix (dim_count, mat, mat);
	return *this;
}

PFX_SQE_CMAT_TEMPLATE
PFX_INLINE PFX_SQE_CMAT_TYPE::cmatrix_t& PFX_SQE_CMAT::transpose 
(PFX_SQE_CMAT_TYPE::cmatrix_t &mat) const
{
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t matrix_alg_t;
	typename matrix_alg_t::matrix_t mat_this = matrix_reference (this->m_mat);
	typename matrix_alg_t::matrix_t mat_other = matrix_reference (mat->m_mat);
	typename matrix_alg_t::transpose_matrix (dim_count, mat_this, mat_other);
	return mat;
}

PFX_SQE_CMAT_TEMPLATE
PFX_INLINE PFX_SQE_CMAT_TYPE::cmatrix_t& PFX_SQE_CMAT::mul_replace 
(const PFX_SQE_CMAT_TYPE::cmatrix_t& other_mat, 
PFX_SQE_CMAT_TYPE::matrix_alg_t::cw_buffer_t* exten_buffer)
{
	*this = mul(other_mat, exten_buffer);
	return *this;
}

PFX_SQE_CMAT_TEMPLATE
PFX_INLINE PFX_SQE_CMAT_TYPE::cmatrix_t& PFX_SQE_CMAT::mul_replace 
(const PFX_SQE_CMAT_TYPE::matrix_ex_t& other_mat, 
PFX_SQE_CMAT_TYPE::matrix_alg_t::cw_buffer_t* exten_buffer)
{
	*this = mul(other_mat, exten_buffer);
	return *this;
}

PFX_SQE_CMAT_TEMPLATE
PFX_INLINE PFX_SQE_CMAT_TYPE::cmatrix_t& PFX_SQE_CMAT::mul_replace 
(const PFX_SQE_CMAT_TYPE::matrix_t& other_mat, 
PFX_SQE_CMAT_TYPE::matrix_alg_t::cw_buffer_t* exten_buffer)
{
	*this = mul(other_mat, exten_buffer);
	return *this;
}

PFX_SQE_CMAT_TEMPLATE
PFX_INLINE PFX_SQE_CMAT_TYPE::cmatrix_t PFX_SQE_CMAT::mul 
(const PFX_SQE_CMAT_TYPE::cmatrix_t& other_mat, 
PFX_SQE_CMAT_TYPE::matrix_alg_t::cw_buffer_t* exten_buffer) const
{
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t matrix_alg_t;
	typedef PFX_SQE_CMAT_TYPE::dim_alg_t		 dim_alg_t;
	typedef PFX_SQE_CMAT_TYPE::cmatrix_t		cmatrix_t;
	typedef typename matrix_alg_t::matrix_t		matrix_t;
	 
	cmatrix_t retn_mat;
	matrix_t __retn_mat = matrix_reference (retn_mat.m_mat);
	matrix_t __other_mat = matrix_reference (other_mat.m_mat);
	matrix_t __this_mat = matrix_reference (this->m_mat);

	switch (dim_count)
	{
	case 0:
		break;
	case 1:
		retn_mat.m_mat[0]->m_value[0] = dim_alg_t::mul (this->m_mat[0]->m_value[0], other_mat.m_mat[0]->m_value[0]);
		break;
	case 2:
		matrix_alg_t::matrix2x2_mul (__this_mat, __other_mat, __retn_mat, exten_buffer);
		break;
	case 3:
		matrix_alg_t::matrix3x3_mul (__this_mat, __other_mat, __retn_mat, exten_buffer);
		break;
	default:
		matrix_alg_t::matrixNxN_mul (__this_mat, __other_mat, __retn_mat, exten_buffer);
		break;
	}

	return retn_mat;
}

PFX_SQE_CMAT_TEMPLATE
PFX_INLINE PFX_SQE_CMAT_TYPE::cmatrix_t PFX_SQE_CMAT::mul 
(const PFX_SQE_CMAT_TYPE::matrix_ex_t& other_mat, 
PFX_SQE_CMAT_TYPE::matrix_alg_t::cw_buffer_t* exten_buffer) const
{
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t matrix_alg_t;
	typedef PFX_SQE_CMAT_TYPE::dim_alg_t		 dim_alg_t;
	typedef PFX_SQE_CMAT_TYPE::cmatrix_t		cmatrix_t;
	typedef typename matrix_alg_t::matrix_t							matrix_t;

	cmatrix_t retn_mat;
	matrix_t __retn_mat = matrix_reference (retn_mat.m_mat);
	matrix_t __other_mat = matrix_reference (other_mat);
	matrix_t __this_mat = matrix_reference (this->m_mat);

	switch (dim_count)
	{
	case 0:
		break;
	case 1:
		retn_mat.m_mat[0]->m_value[0] = dim_alg_t::mul (this->m_mat[0]->m_value[0], other_mat.m_mat[0]->m_value[0]);
		break;
	case 2:
		matrix_alg_t::matrix2x2_mul (__this_mat, __other_mat, __retn_mat, exten_buffer);
		break;
	case 3:
		matrix_alg_t::matrix3x3_mul (__this_mat, __other_mat, __retn_mat, exten_buffer);
		break;
	default:
		matrix_alg_t::matrixNxN_mul (__this_mat, __other_mat, __retn_mat, exten_buffer);
		break;
	}

	return retn_mat;
}

PFX_SQE_CMAT_TEMPLATE
PFX_INLINE PFX_SQE_CMAT_TYPE::cmatrix_t PFX_SQE_CMAT::mul 
(const PFX_SQE_CMAT_TYPE::matrix_t& other_mat, 
PFX_SQE_CMAT_TYPE::matrix_alg_t::cw_buffer_t* exten_buffer) const
{
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t matrix_alg_t;
	typedef PFX_SQE_CMAT_TYPE::dim_alg_t		 dim_alg_t;
	typedef PFX_SQE_CMAT_TYPE::cmatrix_t		cmatrix_t;
	typedef typename matrix_alg_t::matrix_t							matrix_t;

	cmatrix_t retn_mat;
	matrix_t __retn_mat = matrix_reference (retn_mat.m_mat);
	matrix_t __other_mat = matrix_reference (other_mat);
	matrix_t __this_mat = matrix_reference (this->m_mat);

	switch (dim_count)
	{
	case 0:
		break;
	case 1:
		retn_mat.m_mat[0]->m_value[0] = dim_alg_t::mul (this->m_mat[0]->m_value[0], other_mat.m_mat[0]->m_value[0]);
		break;
	case 2:
		matrix_alg_t::matrix2x2_mul (__this_mat, __other_mat, __retn_mat, exten_buffer);
		break;
	case 3:
		matrix_alg_t::matrix3x3_mul (__this_mat, __other_mat, __retn_mat, exten_buffer);
		break;
	default:
		matrix_alg_t::matrixNxN_mul (__this_mat, __other_mat, __retn_mat, exten_buffer);
		break;
	}

	return retn_mat;
}

PFX_SQE_CMAT_TEMPLATE
PFX_INLINE PFX_SQE_CMAT_TYPE::dim_t PFX_SQE_CMAT::det (u32_t delta) const
{
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t matrix_alg_t;
	typedef PFX_SQE_CMAT_TYPE::dim_alg_t		 dim_alg_t;
	
	PFX_SQE_CMAT_TYPE::dim_t		retn_det;
	//const matrix_alg_t::matrix_t			mat;
	switch (dim_count)
	{
	case 0:
		retn_det = 0;
		break;
	case 1:
		retn_det = matrix_alg_t::matrix1x1_det (matrix_reference(m_mat));
		break;
	case 2:
		retn_det = matrix_alg_t::matrix2x2_det (matrix_reference(m_mat));
		break;
	case 3:
		retn_det = matrix_alg_t::matrix3x3_det (matrix_reference(m_mat));
		break;
	default:
		{
			PFX_SQE_CMAT_TYPE::cmatrix_t tmp_mat(*this);
			PFX_SQE_CMAT_TYPE::matrix_ex_t mat_ex(tmp_mat.m_mat);
			PFX_SQE_CMAT_TYPE::matrix_alg_t::matrix_ex_t mat_ex__ = matrix_reference(mat_ex);
			retn_det = matrix_alg_t::matrix_det (mat_ex__, dim_count,delta);
		}
		break;
	}

	return retn_det;
}
PFX_SQE_CMAT_TEMPLATE
PFX_INLINE usize__t PFX_SQE_CMAT::rank (u32_t delta) const
{
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t matrix_alg_t;
	PFX_SQE_CMAT_TYPE::cmatrix_t tmp_mat(*this);
	PFX_SQE_CMAT_TYPE::matrix_ex_t mat_ex(tmp_mat.m_mat);
	PFX_SQE_CMAT_TYPE::matrix_alg_t::matrix_ex_t mat_ex__ = matrix_reference(mat_ex);
	return matrix_alg_t::matrix_rank (mat_ex__, dim_count, delta);
}
PFX_SQE_CMAT_TEMPLATE
PFX_INLINE PFX_SQE_CMAT_TYPE::cmatrix_t& PFX_SQE_CMAT::
inverse_matrix(PFX_SQE_CMAT_TYPE::cmatrix_t& inverse_matrix, 
PFX_SQE_CMAT_TYPE::cmatrix_t& extern_matrix, 
	u32_t delta) const
{
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t matrix_alg_t;

	PFX_SQE_CMAT_TYPE::matrix_ex_t mat_inverse (extern_matrix.m_mat);
	PFX_SQE_CMAT_TYPE::matrix_ex_t mat_extern (inverse_matrix.m_mat);
	PFX_SQE_CMAT_TYPE::matrix_alg_t::matrix_ex_t __mat_inverse = matrix_reference (mat_inverse);
	PFX_SQE_CMAT_TYPE::matrix_alg_t::matrix_ex_t __mat_extern = matrix_reference (mat_extern);
	inverse_matrix = *this;
	
	//matrix_alg_t::Indentify_matrix (dim_count, __mat_inverse, 1, 0);
	typename matrix_alg_t::clr_mul_factor_t mul_factor[0 == dim_count?1:dim_count];
	matrix_alg_t::inverse_matrix (__mat_extern, dim_count, __mat_inverse, mul_factor, delta);
	mat_inverse.to_matrix (inverse_matrix.m_mat);
	return inverse_matrix;
}

PFX_SQE_CMAT_TEMPLATE
PFX_SQE_CMAT_TYPE::cmatrix_t& PFX_SQE_CMAT::indentify 
(PFX_SQE_CMAT_TYPE::cmatrix_t& mat, PFX_SQE_CMAT_TYPE::dim_t val)
{
	return mat.indentify_replace(val);
}

PFX_SQE_CMAT_TEMPLATE
PFX_INLINE PFX_SQE_CMAT_TYPE::cvector_t PFX_SQE_CMAT::mul 
(const PFX_SQE_CMAT_TYPE::cvector_t& vec, const PFX_SQE_CMAT_TYPE::cmatrix_t& mat)
{
	typedef PFX_SQE_CMAT_TYPE::vec_alg_t		vec_alg_t;
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t	matrix_alg_t;
	typedef PFX_SQE_CMAT_TYPE::cvector_t		cvector_t;
	typedef typename matrix_alg_t::matrix_t							matrix_t;
	typedef typename matrix_alg_t::vector_t							vector_t;
	cvector_t	retn_vec;
	cvector_t	tempbuffer;

	const matrix_t __mat = matrix_reference (mat.m_mat);

	if (4 == dim_count)
	{
		matrix_alg_t::vector4_mul (cvector_t::vector_reference (vec), 
			__mat, cvector_t::vector_reference (retn_vec), 
			&cvector_t::vector_reference (tempbuffer));
	}
	else
	{
		const matrix_t __mata = cvector_t::matrix_reference (vec);
		matrix_t __retn_vec = cvector_t::matrix_reference (retn_vec);
		vec_alg_t::matrix_mul_matrix_direct ( __mata,
			 1, dim_count, dim_count, __mat,
			__retn_vec);
	}

	return retn_vec;
}

PFX_SQE_CMAT_TEMPLATE
PFX_INLINE PFX_SQE_CMAT_TYPE::cvector_t& PFX_SQE_CMAT::mul_replace 
(PFX_SQE_CMAT_TYPE::cvector_t& vec, const PFX_SQE_CMAT_TYPE::cmatrix_t& mat)
{
	vec = mul(vec,mat);
	return vec;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define PFX_SQEX_CMAT_TEMPLATE template< class dim_type, const usize__t dim_count, const enum_int_t optional_type >
#define  PFX_SQEX_CMAT  SquareMatrixEX_unsafe< dim_type, dim_count, optional_type  >
#define  PFX_SQEX_CMAT_TYPE typename SquareMatrixEX_unsafe< dim_type, dim_count, optional_type  >

PFX_SQEX_CMAT_TEMPLATE
	PFX_SQEX_CMAT:: SquareMatrixEX_unsafe ()
{
	for (uindex_t i=0; i<dim_count; ++i)
	{
		m_mat[i] = null;		
	}
}

PFX_SQEX_CMAT_TEMPLATE
	PFX_SQEX_CMAT::SquareMatrixEX_unsafe (PFX_SQEX_CMAT_TYPE::matrix_ex_t& mat)
{
	typedef PFX_SQEX_CMAT_TYPE::vec_alg_t		vec_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::matrix_ex_t	matrix_ex_t;
	for (uindex_t i=0; i<dim_count; ++i)
	{
		m_mat[i] = mat[i];		
	}
}

PFX_SQEX_CMAT_TEMPLATE
	PFX_SQEX_CMAT::SquareMatrixEX_unsafe (PFX_SQEX_CMAT_TYPE::matrix_t& mat)
{
	typedef PFX_SQEX_CMAT_TYPE::vec_alg_t		vec_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::matrix_ex_t	matrix_ex_t;
	for (uindex_t i=0; i<dim_count; ++i)
	{
		m_mat[i] = mat[i];		
	}
}

PFX_SQEX_CMAT_TEMPLATE
	PFX_SQEX_CMAT::SquareMatrixEX_unsafe (PFX_SQEX_CMAT_TYPE::cmatrix_t& mat)
{
	mat.m_mat.to_matrix_ex (m_mat);
}

PFX_SQEX_CMAT_TEMPLATE
PFX_SQEX_CMAT::SquareMatrixEX_unsafe (PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& mat)
{
	typedef PFX_SQEX_CMAT_TYPE::vec_alg_t		vec_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::matrix_ex_t	matrix_ex_t;
	for (uindex_t i=0; i<dim_count; ++i)
	{
		m_mat[i] = mat[i];		
	}
}

PFX_SQEX_CMAT_TEMPLATE
PFX_INLINE const PFX_SQEX_CMAT_TYPE::matrix_ex_t& PFX_SQEX_CMAT::const_reference () const
{
	return this->m_mat;
}

PFX_SQEX_CMAT_TEMPLATE
	PFX_INLINE PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& PFX_SQEX_CMAT::
	indentify_replace (PFX_SQEX_CMAT_TYPE::dim_t val)
{
	typedef PFX_SQEX_CMAT_TYPE::matrix_alg_t matrix_alg_t;
	typename matrix_alg_t::matrix_ex_t mat = matrix_reference (this->m_mat);
	matrix_alg_t::Indentify_matrix (dim_count, mat, val, 0);
	return *this;
}

PFX_SQEX_CMAT_TEMPLATE
	PFX_INLINE PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& PFX_SQEX_CMAT::transpose_replace ()
{
	typedef PFX_SQEX_CMAT_TYPE::matrix_alg_t matrix_alg_t;
	typename matrix_alg_t::matrix_ex_t mat = matrix_reference (this->m_mat);
	matrix_alg_t::transpose_matrix (dim_count, mat, mat);
	return *this;
}

PFX_SQEX_CMAT_TEMPLATE
	PFX_INLINE PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& PFX_SQEX_CMAT::transpose 
	(PFX_SQEX_CMAT_TYPE::cmatrix_ex_t &mat) const
{
	typedef PFX_SQEX_CMAT_TYPE::matrix_alg_t matrix_alg_t;
	if (&mat != this)
	{
		typename matrix_alg_t::matrix_ex_t mat_this = matrix_reference (this->m_mat);
		typename matrix_alg_t::matrix_ex_t mat_other = matrix_reference (mat->m_mat);
		matrix_alg_t::transpose_matrix (dim_count, mat_this, mat_other);
	}
	else
	{
		transpose_replace();
	}
	
	return mat;
}

PFX_SQEX_CMAT_TEMPLATE
	PFX_INLINE PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& PFX_SQEX_CMAT::mul_replace 
	(const PFX_SQEX_CMAT_TYPE::cmatrix_t& other_mat, 
	PFX_SQEX_CMAT_TYPE::cw_buffer_t* exten_buffer)
{
	typedef PFX_SQEX_CMAT_TYPE::dim_alg_t		dim_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::matrix_alg_t	matrix_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::dim_alg_t		dim_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::cmatrix_t		cmatrix_t;
	typedef PFX_SQEX_CMAT_TYPE::cmatrix_ex_t	cmatrix_ex_t;
	typedef typename matrix_alg_t::matrix_ex_t						matrix_ex_t;


	cmatrix_t		__result_cmat;
	cmatrix_ex_t	__result_matex(__result_cmat);
	cmatrix_ex_t	__other_matex(other_mat);

	matrix_ex_t __result_mat = matrix_reference (__result_matex.m_mat);
	matrix_ex_t __other_mat = matrix_reference (__other_matex.m_mat);
	matrix_ex_t __this_mat = matrix_reference (this->m_mat);

	switch (dim_count)
	{
	case 0:
		break;
	case 1:
		this->m_mat[0]->m_value[0] = 
			dim_alg_t::mul (this->m_mat[0]->m_value[0], other_mat.m_mat[0]->m_value[0]);
		break;
	case 2:
		matrix_alg_t::matrix2x2_mul (__this_mat, __other_mat, __result_mat, exten_buffer);
		__result_matex.m_mat.copy_to_matrix_ex_unsafe(this->m_mat);
		break;
	case 3:
		matrix_alg_t::matrix3x3_mul (__this_mat, __other_mat, __result_mat, exten_buffer);
		__result_matex.m_mat.copy_to_matrix_ex_unsafe(this->m_mat);
		break;
	default:
		matrix_alg_t::matrixNxN_mul (__this_mat, __other_mat, __result_mat, exten_buffer);
		__result_matex.m_mat.copy_to_matrix_ex_unsafe(this->m_mat);
		break;
	}

	return *this;
}

PFX_SQEX_CMAT_TEMPLATE
	PFX_INLINE PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& PFX_SQEX_CMAT::mul_replace 
	(const PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& other_mat, 
	PFX_SQEX_CMAT_TYPE::cw_buffer_t* exten_buffer)
{
	typedef PFX_SQEX_CMAT_TYPE::dim_alg_t		dim_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::matrix_alg_t	matrix_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::dim_alg_t		dim_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::cmatrix_t		cmatrix_t;
	typedef PFX_SQEX_CMAT_TYPE::cmatrix_ex_t	cmatrix_ex_t;
	typedef typename matrix_alg_t::matrix_ex_t						matrix_ex_t;


	cmatrix_t				__result_cmat;
	cmatrix_ex_t		__result_matex(__result_cmat);

	matrix_ex_t __result_mat = matrix_reference (__result_matex.m_mat);
	matrix_ex_t __other_mat = matrix_reference (other_mat.m_mat);
	matrix_ex_t __this_mat = matrix_reference (this->m_mat);

	switch (dim_count)
	{
	case 0:
		break;
	case 1:
		this->m_mat[0]->m_value[0] = 
			dim_alg_t::mul (this->m_mat[0]->m_value[0], other_mat.m_mat[0]->m_value[0]);
		break;
	case 2:
		matrix_alg_t::matrix2x2_mul (__this_mat, __other_mat, __result_mat, exten_buffer);
		__result_matex.m_mat.copy_to_matrix_ex_unsafe(this->m_mat);
		break;
	case 3:
		matrix_alg_t::matrix3x3_mul (__this_mat, __other_mat, __result_mat, exten_buffer);
		__result_matex.m_mat.copy_to_matrix_ex_unsafe(this->m_mat);
		break;
	default:
		matrix_alg_t::matrixNxN_mul (__this_mat, __other_mat, __result_mat, exten_buffer);
		__result_matex.m_mat.copy_to_matrix_ex_unsafe(this->m_mat);
		break;
	}

	return *this;
}

PFX_SQEX_CMAT_TEMPLATE
	PFX_INLINE PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& PFX_SQEX_CMAT::mul_replace 
	(const PFX_SQEX_CMAT_TYPE::matrix_t& other_mat, 
	PFX_SQEX_CMAT_TYPE::cw_buffer_t* exten_buffer)
{
	typedef PFX_SQEX_CMAT_TYPE::dim_alg_t		dim_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::matrix_alg_t	matrix_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::dim_alg_t		dim_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::cmatrix_t		cmatrix_t;
	typedef PFX_SQEX_CMAT_TYPE::cmatrix_ex_t	cmatrix_ex_t;
	typedef typename matrix_alg_t::matrix_ex_t						matrix_ex_t;


	cmatrix_t			__result_cmat;
	cmatrix_ex_t		__result_matex(__result_cmat);
	cmatrix_ex_t		__other_matex(other_mat);

	matrix_ex_t __result_mat = matrix_reference (__result_matex.m_mat);
	matrix_ex_t __other_mat = matrix_reference (__other_matex.m_mat);
	matrix_ex_t __this_mat = matrix_reference (this->m_mat);

	switch (dim_count)
	{
	case 0:
		break;
	case 1:
		this->m_mat[0]->m_value[0] = 
			dim_alg_t::mul (this->m_mat[0]->m_value[0], other_mat.m_mat[0]->m_value[0]);
		break;
	case 2:
		matrix_alg_t::matrix2x2_mul (__this_mat, __other_mat, __result_mat, exten_buffer);
		__result_matex.m_mat.copy_to_matrix_ex_unsafe(this->m_mat);
		break;
	case 3:
		matrix_alg_t::matrix3x3_mul (__this_mat, __other_mat, __result_mat, exten_buffer);
		__result_matex.m_mat.copy_to_matrix_ex_unsafe(this->m_mat);
		break;
	default:
		matrix_alg_t::matrixNxN_mul (__this_mat, __other_mat, __result_mat, exten_buffer);
		__result_matex.m_mat.copy_to_matrix_ex_unsafe(this->m_mat);
		break;
	}

	return *this;
}

PFX_SQEX_CMAT_TEMPLATE
	PFX_INLINE PFX_SQEX_CMAT_TYPE::dim_t PFX_SQEX_CMAT::det (u32_t delta) const
{
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t matrix_alg_t;
	typedef PFX_SQE_CMAT_TYPE::dim_alg_t		 dim_alg_t;

	PFX_SQE_CMAT_TYPE::dim_t		retn_det;
	//const matrix_alg_t::matrix_t			mat;
	switch (dim_count)
	{
	case 0:
		retn_det = 0;
		break;
	case 1:
		retn_det = matrix_alg_t::matrix1x1_det (matrix_reference(m_mat));
		break;
	case 2:
		retn_det = matrix_alg_t::matrix2x2_det (matrix_reference(m_mat));
		break;
	case 3:
		retn_det = matrix_alg_t::matrix3x3_det (matrix_reference(m_mat));
		break;
	default:
		{
			PFX_SQE_CMAT_TYPE::cmatrix_t tmp_mat(this->m_mat);
			PFX_SQE_CMAT_TYPE::matrix_ex_t mat_ex(tmp_mat.m_mat);
			PFX_SQE_CMAT_TYPE::matrix_alg_t::matrix_ex_t mat_ex__ = matrix_reference(mat_ex);
			retn_det = matrix_alg_t::matrix_det (mat_ex__, dim_count, delta);
		}
		break;
	}

	return retn_det;
}
PFX_SQEX_CMAT_TEMPLATE
	PFX_INLINE usize__t PFX_SQEX_CMAT::rank (u32_t delta) const
{
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t matrix_alg_t;
	PFX_SQE_CMAT_TYPE::cmatrix_t tmp_mat(this->m_mat);
	PFX_SQE_CMAT_TYPE::matrix_ex_t mat_ex(tmp_mat.m_mat);
	PFX_SQE_CMAT_TYPE::matrix_alg_t::matrix_ex_t mat_ex__ = matrix_reference(mat_ex);
	return matrix_alg_t::matrix_rank (mat_ex__, dim_count, delta);
}
PFX_SQEX_CMAT_TEMPLATE
	PFX_INLINE PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& PFX_SQEX_CMAT::
	inverse_matrix(PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& inv_matrix, 
	PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& extern_matrix, 
	u32_t delta) const
{
	typedef PFX_SQE_CMAT_TYPE::matrix_alg_t matrix_alg_t;

	PFX_SQE_CMAT_TYPE::matrix_alg_t::matrix_ex_t __mat_inverse = matrix_reference(inv_matrix.m_mat);
	PFX_SQE_CMAT_TYPE::matrix_alg_t::matrix_ex_t __mat_extern = matrix_reference (extern_matrix.m_mat);
	this->m_mat.copy_to_matrix_ex(extern_matrix.m_mat);
	//inv_matrix.indentify_replace (1);
	typename matrix_alg_t::clr_mul_factor_t mul_factor[0 == dim_count?1:dim_count];
	matrix_alg_t::inverse_matrix (__mat_extern, dim_count, __mat_inverse, mul_factor, delta);
	return inv_matrix;
}

PFX_SQEX_CMAT_TEMPLATE
	PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& PFX_SQEX_CMAT::indentify 
	(PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& mat, PFX_SQEX_CMAT_TYPE::dim_t val)
{
	return mat.indentify_replace(val);
}

PFX_SQEX_CMAT_TEMPLATE
	PFX_INLINE PFX_SQEX_CMAT_TYPE::cvector_t PFX_SQEX_CMAT::mul 
	(const PFX_SQEX_CMAT_TYPE::cvector_t& vec, const PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& mat)
{
	typedef PFX_SQEX_CMAT_TYPE::vec_alg_t		vec_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::matrix_alg_t	matrix_alg_t;
	typedef PFX_SQEX_CMAT_TYPE::cvector_t		cvector_t;
	typedef typename matrix_alg_t::matrix_t							matrix_t;
	typedef typename matrix_alg_t::vector_t							vector_t;
	typedef typename matrix_alg_t::matrix_ex_t					matrix_ex_t;
	cvector_t	retn_vec;
	cvector_t	tempbuffer;

	const matrix_ex_t __mat = matrix_reference (mat.m_mat);

	if (4 == dim_count)
	{
		matrix_alg_t::vector4_mul (cvector_t::vector_reference (vec), 
			__mat, cvector_t::vector_reference (retn_vec), 
			&cvector_t::vector_reference (tempbuffer));
	}
	else
	{
		matrix_t						__retn_vec	= cvector_t::matrix_reference (retn_vec);
		const matrix_t			__mata			= cvector_t::matrix_reference (vec);
		const matrix_ex_t	__mata_ex	= (const matrix_ex_t)&__mata;
		matrix_ex_t				__retn_mat	= (matrix_ex_t)&__retn_vec;

		vec_alg_t::matrix_mul_matrix_direct ( __mata_ex,
			1, dim_count, dim_count, __mat,
			__retn_mat);
	}

	return retn_vec;
}

PFX_SQEX_CMAT_TEMPLATE
	PFX_INLINE PFX_SQEX_CMAT_TYPE::cvector_t& PFX_SQEX_CMAT::mul_replace 
	(PFX_SQEX_CMAT_TYPE::cvector_t& vec, const PFX_SQEX_CMAT_TYPE::cmatrix_ex_t& mat)
{
	vec = mul(vec, mat);
	return vec;
}

PECKER_END

#endif			//PFX_CMATRIX_CODES_H_
