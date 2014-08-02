/*
 * pfx_cvector.h
 *
 *  Created on: 2013-8-25
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CVECTOR_H_
#define		PFX_CVECTOR_H_

#include "../pfx_defines.h"
#include "pfx_cvector_alg_codes.h"

PECKER_BEGIN

template < class dim_type, const usize__t dim_count >
struct vector_data
{
	typedef dim_type dim_t;
	typedef vector_data< dim_t, dim_count > vector_t;

	dim_t m_value[(0 == dim_count)?1:dim_count];

	static PFX_INLINE usize__t vector_dim_count ()
	{
		return dim_count;
	}
	PFX_INLINE dim_t& operator[] (uindex_t i)
	{
		return m_value[i];
	}
	PFX_INLINE const dim_t& operator[] (uindex_t i) const
	{
		return m_value[i];
	}
};

template < class dim_type, const usize__t dim_count, const enum_int_t optional_type = 0 >
class VectorX
{
public:
	typedef typename vector_data< dim_type, dim_count >::vector_t vector_t;
	typedef typename vector_t::dim_t dim_t;
	typedef VectorX< dim_type, dim_count, optional_type > cvector_t;
	typedef typename vector_base_op_traits < vector_t, optional_type >::vec_alg_t vec_alg_t;
	typedef typename vec_alg_t::matrix_t matrix_t;
	typedef typename vec_alg_t::matrix_ex_t matrix_ex_t;

protected:
	vector_t m_vec;
public:
	VectorX ();
	VectorX (dim_t val);
	VectorX (dim_t val1, dim_t val2);
	VectorX (dim_t val1, dim_t val2, dim_t val3);
	VectorX (dim_t val1, dim_t val2, dim_t val3, dim_t val4);
	VectorX (const dim_t* PARAM_IN vals, usize__t vals_count);
	VectorX (const vector_t& vec);
	VectorX (const cvector_t& vec);
public:
	PFX_INLINE vector_t const& reference () const;
	PFX_INLINE cvector_t& mul_replace (dim_t dim_b);
	PFX_INLINE cvector_t& div_replace (dim_t dim_b);
	PFX_INLINE cvector_t& add_replace (const cvector_t& vec_b);
	PFX_INLINE cvector_t& add_replace (const vector_t& vec_b);
	PFX_INLINE cvector_t& sub_replace (const cvector_t& vec_b);
	PFX_INLINE cvector_t& sub_replace (const vector_t& vec_b);

	PFX_INLINE cvector_t& cross (const cvector_t& vec_b, cvector_t& vec_result);
	PFX_INLINE vector_t& cross (const vector_t& vec_b, vector_t& vec_result);

	PFX_INLINE dim_t dot (const cvector_t& vec_b);
	PFX_INLINE dim_t dot (const vector_t& vec_b);

public:
	static PFX_INLINE cvector_t mul (const cvector_t& vec_a, dim_t dim_b);
	static PFX_INLINE cvector_t div (const cvector_t& vec_a, dim_t dim_b);

	static PFX_INLINE cvector_t mul (const vector_t& vec_a, dim_t dim_b);
	static PFX_INLINE cvector_t div (const vector_t& vec_a, dim_t dim_b);

	static PFX_INLINE cvector_t add (const cvector_t& vec_a, const cvector_t& vec_b);
	static PFX_INLINE cvector_t sub (const cvector_t& vec_a, const cvector_t& vec_b);

	static PFX_INLINE cvector_t add (const cvector_t& vec_a, const vector_t& vec_b);
	static PFX_INLINE cvector_t sub (const cvector_t& vec_a, const vector_t& vec_b);

	static PFX_INLINE cvector_t add (const vector_t& vec_a, const vector_t& vec_b);
	static PFX_INLINE cvector_t sub (const vector_t& vec_a, const vector_t& vec_b);

	static PFX_INLINE vector_t* vector_pointer (cvector_t* vec)
	{
		return (vector_t*)vec;
	}
	static PFX_INLINE const vector_t* vector_pointer (const cvector_t* vec)
	{
		return (const vector_t*)vec;
	}
	static PFX_INLINE cvector_t* vector_pointer (vector_t* vec)
	{
		return (cvector_t*)vec;
	}
	static PFX_INLINE const cvector_t* vector_pointer (const vector_t* vec)
	{
		return (cvector_t*)vec;
	}

	static PFX_INLINE vector_t& vector_ref (cvector_t& vec)
	{
		return vec.m_vec;
	}
	static PFX_INLINE const vector_t& vector_ref (const cvector_t& vec)
	{
		return (const vector_t&)vec;
	}
	static PFX_INLINE cvector_t& vector_ref (vector_t& vec)
	{
		return (cvector_t&)vec;
	}
	static PFX_INLINE const cvector_t& vector_ref (const vector_t& vec)
	{
		return (cvector_t&)vec;
	}

	static PFX_INLINE typename vec_alg_t::vector_t& vector_reference (cvector_t& vec);
	static PFX_INLINE const typename vec_alg_t::vector_t& vector_reference (const cvector_t& vec);
	static PFX_INLINE typename vec_alg_t::matrix_t matrix_reference (cvector_t& vec);
	static PFX_INLINE const typename vec_alg_t::matrix_t matrix_reference (const cvector_t& vec);

public:
	static PFX_INLINE usize__t vector_dim_count ()
	{
		return dim_count;
	}
	static PFX_INLINE dim_t& error_dim_value ()
	{
		static dim_t error_;
		return error_;
	}
	PFX_INLINE dim_t& operator[] (uindex_t i)
	{
		if (i < dim_count)
		{
			return m_vec[i];
		}
		else
		{
			return error_dim_value();
		}

	}
	PFX_INLINE const dim_t& operator[] (uindex_t i) const
	{
		if (i < dim_count)
		{
			return m_vec[i];
		}
		else
		{
			return error_dim_value();
		}
	}
};

//////////////////////////////////////////////////////////////////////////
#define PFX_CVEC_TEMPLATE template < class dim_type, const usize__t dim_count, const enum_int_t optional_type > 
#define PFX_CVEC VectorX< dim_type, dim_count, optional_type  >
#define PFX_CVEC_TYPE typename VectorX< dim_type, dim_count, optional_type  >

PFX_CVEC_TEMPLATE
PFX_CVEC::VectorX ()
{	;}

PFX_CVEC_TEMPLATE
PFX_CVEC::VectorX (PFX_CVEC_TYPE::dim_t val)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	vec_alg_t::init_vector (m_vec,val);
}
PFX_CVEC_TEMPLATE
PFX_CVEC::VectorX (PFX_CVEC_TYPE::dim_t val1, PFX_CVEC_TYPE::dim_t val2)
{
	switch (dim_count)
	{
		case 0:
		case 1:
		m_vec[0] = val1;
		break;
		default:
		m_vec[0] = val1;
		m_vec[1] = val2;
		break;
	}
}
PFX_CVEC_TEMPLATE
PFX_CVEC::VectorX (PFX_CVEC_TYPE::dim_t val1,
		PFX_CVEC_TYPE::dim_t val2, PFX_CVEC_TYPE::dim_t val3)
{
	switch (dim_count)
	{
		case 0:
		case 1:
		m_vec[0] = val1;
		break;
		case 2:
		m_vec[0] = val1;
		m_vec[1] = val2;
		break;
		default:
		m_vec[0] = val1;
		m_vec[1] = val2;
		m_vec[2] = val3;
		break;
	}
}
PFX_CVEC_TEMPLATE
PFX_CVEC::VectorX (PFX_CVEC_TYPE::dim_t val1, PFX_CVEC_TYPE::dim_t val2,
		PFX_CVEC_TYPE::dim_t val3, PFX_CVEC_TYPE::dim_t val4)
{
	switch (dim_count)
	{
		case 0:
		case 1:
		m_vec[0] = val1;
		break;
		case 2:
		m_vec[0] = val1;
		m_vec[1] = val2;
		break;
		case 3:
		m_vec[0] = val1;
		m_vec[1] = val2;
		m_vec[2] = val3;
		break;
		default:
		m_vec[0] = val1;
		m_vec[1] = val2;
		m_vec[2] = val3;
		m_vec[3] = val4;
		break;
	}
}
PFX_CVEC_TEMPLATE
PFX_CVEC::VectorX (const PFX_CVEC_TYPE::dim_t* PARAM_IN vals, usize__t vals_count)
{
	if (vals_count > dim_count)
	{
		vals_count = dim_count;
	}

	for (uindex_t i=0; i<vals_count; ++i)
	{
		m_vec[i] = vals[i];
	}
}
PFX_CVEC_TEMPLATE
PFX_CVEC::VectorX (const PFX_CVEC_TYPE::vector_t& vec)
{
	if (&vec != &m_vec)
	{
		typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
		vec_alg_t::init_vector (m_vec,vec);
	}
}
PFX_CVEC_TEMPLATE
PFX_CVEC::VectorX (const PFX_CVEC_TYPE::cvector_t& vec)
{
	if (&vec != this)
	{
		typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
		vec_alg_t::init_vector (m_vec,vec.m_vec);
	}
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::vector_t const& PFX_CVEC::reference () const
{
	return m_vec;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t& PFX_CVEC::mul_replace (PFX_CVEC_TYPE::dim_t dim_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	vec_alg_t::vector_mul (m_vec, dim_b, m_vec);
	return *this;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t& PFX_CVEC::div_replace (PFX_CVEC_TYPE::dim_t dim_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	vec_alg_t::vector_div (m_vec, dim_b, m_vec);
	return *this;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t& PFX_CVEC::add_replace (const PFX_CVEC_TYPE::cvector_t& vec_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	vec_alg_t::vector_add (m_vec, vec_b.m_vec, m_vec);
	return *this;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t& PFX_CVEC::add_replace (const PFX_CVEC_TYPE::vector_t& vec_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	vec_alg_t::vector_add (m_vec, vec_b, m_vec);
	return *this;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t& PFX_CVEC::sub_replace (const PFX_CVEC_TYPE::cvector_t& vec_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	vec_alg_t::vector_sub (m_vec, vec_b.m_vec, m_vec);
	return *this;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t& PFX_CVEC::sub_replace (const PFX_CVEC_TYPE::vector_t& vec_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	vec_alg_t::vector_sub (m_vec, vec_b, m_vec);
	return *this;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t& PFX_CVEC::cross (const PFX_CVEC_TYPE::cvector_t& vec_b,
		PFX_CVEC_TYPE::cvector_t& vec_result)
{
	if (3 == dim_count || 4 == dim_count)
	{
		typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
		vec_alg_t::vector3_cross (m_vec, vec_b.m_vec, vec_result.m_vec);
		if (4 == dim_count)
		{
			vec_result.m_vec[3] = 1;
		}
	}
	return vec_result;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::vector_t& PFX_CVEC::cross (const PFX_CVEC_TYPE::vector_t& vec_b,
		PFX_CVEC_TYPE::vector_t& vec_result)
{
	if (3 == dim_count || 4 == dim_count)
	{
		typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
		vec_alg_t::vector3_cross (m_vec, vec_b, vec_result);

		if (4 == dim_count)
		{
			vec_result[3] = 1;
		}
	}
	return vec_result;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::dim_t PFX_CVEC::dot (const PFX_CVEC_TYPE::cvector_t& vec_b)
{
	typedef PFX_CVEC_TYPE::dim_t dim_t;
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	dim_t result_;
	vec_alg_t::vector_dot (m_vec, vec_b.m_vec, dim_count, result_);
	return result_;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::dim_t PFX_CVEC::dot (const PFX_CVEC_TYPE::vector_t& vec_b)
{
	typedef PFX_CVEC_TYPE::dim_t dim_t;
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	dim_t result_;
	vec_alg_t::vector_dot (m_vec, vec_b, dim_count, result_);
	return result_;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t PFX_CVEC::mul (const PFX_CVEC_TYPE::cvector_t& vec_a, PFX_CVEC_TYPE::dim_t dim_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	PFX_CVEC_TYPE::cvector_t retn_vec;
	vec_alg_t::vector_mul (vec_a.m_vec, dim_b, retn_vec.m_vec);
	return retn_vec;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t PFX_CVEC::div (const PFX_CVEC_TYPE::cvector_t& vec_a, PFX_CVEC_TYPE::dim_t dim_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	PFX_CVEC_TYPE::cvector_t retn_vec;
	vec_alg_t::vector_div (vec_a.m_vec, dim_b, retn_vec.m_vec);
	return retn_vec;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t PFX_CVEC::mul (const PFX_CVEC_TYPE::vector_t& vec_a, PFX_CVEC_TYPE::dim_t dim_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	PFX_CVEC_TYPE::cvector_t retn_vec;
	vec_alg_t::vector_mul (vec_a, dim_b, retn_vec.m_vec);
	return retn_vec;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t PFX_CVEC::div (const PFX_CVEC_TYPE::vector_t& vec_a, PFX_CVEC_TYPE::dim_t dim_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	PFX_CVEC_TYPE::cvector_t retn_vec;
	vec_alg_t::vector_div (vec_a, dim_b, retn_vec.m_vec);
	return retn_vec;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t PFX_CVEC::add (const PFX_CVEC_TYPE::cvector_t& vec_a, const PFX_CVEC_TYPE::cvector_t& vec_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	PFX_CVEC_TYPE::cvector_t retn_vec;
	vec_alg_t::vector_add (vec_a.m_vec, vec_b.m_vec, retn_vec.m_vec);
	return retn_vec;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t PFX_CVEC::sub (const PFX_CVEC_TYPE::cvector_t& vec_a, const PFX_CVEC_TYPE::cvector_t& vec_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	PFX_CVEC_TYPE::cvector_t retn_vec;
	vec_alg_t::vector_sub (vec_a.m_vec, vec_b.m_vec, retn_vec.m_vec);
	return retn_vec;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t PFX_CVEC::add (const PFX_CVEC_TYPE::cvector_t& vec_a, const PFX_CVEC_TYPE::vector_t& vec_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	PFX_CVEC_TYPE::cvector_t retn_vec;
	vec_alg_t::vector_add (vec_a.m_vec, vec_b, retn_vec.m_vec);
	return retn_vec;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t PFX_CVEC::sub (const PFX_CVEC_TYPE::cvector_t& vec_a, const PFX_CVEC_TYPE::vector_t& vec_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	PFX_CVEC_TYPE::cvector_t retn_vec;
	vec_alg_t::vector_sub (vec_a.m_vec, vec_b, retn_vec.m_vec);
	return retn_vec;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t PFX_CVEC::add (const PFX_CVEC_TYPE::vector_t& vec_a, const PFX_CVEC_TYPE::vector_t& vec_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	PFX_CVEC_TYPE::cvector_t retn_vec;
	vec_alg_t::vector_add (vec_a, vec_b, retn_vec.m_vec);
	return retn_vec;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::cvector_t PFX_CVEC::sub (const PFX_CVEC_TYPE::vector_t& vec_a, const PFX_CVEC_TYPE::vector_t& vec_b)
{
	typedef PFX_CVEC_TYPE::vec_alg_t vec_alg_t;
	PFX_CVEC_TYPE::cvector_t retn_vec;
	vec_alg_t::vector_sub (vec_a, vec_b, retn_vec.m_vec);
	return retn_vec;
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::vec_alg_t::vector_t& PFX_CVEC::vector_reference (PFX_CVEC_TYPE::cvector_t& vec)
{
	return (vec.m_vec);
}

PFX_CVEC_TEMPLATE
PFX_INLINE const PFX_CVEC_TYPE::vec_alg_t::vector_t& PFX_CVEC::vector_reference (const PFX_CVEC_TYPE::cvector_t& vec)
{
	return (vec.m_vec);
}

PFX_CVEC_TEMPLATE
PFX_INLINE PFX_CVEC_TYPE::vec_alg_t::matrix_t PFX_CVEC::matrix_reference (PFX_CVEC_TYPE::cvector_t& vec)
{
	return (PFX_CVEC_TYPE::vec_alg_t::matrix_t)(&vec.m_vec);
}

PFX_CVEC_TEMPLATE
PFX_INLINE const PFX_CVEC_TYPE::vec_alg_t::matrix_t PFX_CVEC::matrix_reference (const PFX_CVEC_TYPE::cvector_t& vec)
{
	return (const PFX_CVEC_TYPE::vec_alg_t::matrix_t)(&vec.m_vec);
}

PECKER_END

#endif			//PFX_CVECTOR_H_
