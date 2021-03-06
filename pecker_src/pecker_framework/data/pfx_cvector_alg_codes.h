﻿/*
 * cvector_alg_codes.h
 *
 *  Created on: 2013-8-25
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_CVECTOR_ALG_CODES_H_
#define		PFX_CVECTOR_ALG_CODES_H_

#include "../pfx_defines.h"
#include "pfx_cvector_alg.h"
#include "pfx_fixed_point.h"
#include <math.h>

PECKER_BEGIN

#define PFX_VECDIM_ALG_TEMPLATE_DEFINES template < class dim_value, const enum_int_t optional_type >
#define PFX_VECDIM_ALG	vector_dim_op_alg < dim_value, optional_type >
#define PFX_VECDIM_ALG_TYPE	typename vector_dim_op_alg < dim_value, optional_type >

#define PFX_VEC_ALG_TEMPLATE_DEFINES template < class vector_type, const enum_int_t optional_type >
#define PFX_VEC_ALG	vector_base_op_alg < vector_type, optional_type >
#define PFX_VEC_ALG_TYPE	typename vector_base_op_alg < vector_type, optional_type >

#define PFX_SMAT_ALG_TEMPLATE_DEFINES  template < class square_matrix_type, const enum_int_t optional_type >
#define PFX_SMAT_ALG square_matrix_base_op_alg < square_matrix_type, optional_type >
#define PFX_SMAT_ALG_TYPE typename square_matrix_base_op_alg < square_matrix_type, optional_type >

PFX_VECDIM_ALG_TEMPLATE_DEFINES PFX_INLINE boolean_t PFX_VECDIM_ALG::equals (PFX_VECDIM_ALG_TYPE::dim_t X, PFX_VECDIM_ALG_TYPE::dim_t Y, u32_t delta)
{
	return (boolean_t)((bool)(X == Y));
}

// float 特例化
template <>
PFX_INLINE boolean_t vector_dim_op_alg< float, 0 > ::equals (float fX, float fY, u32_t delta)
{
	boolean_t retn_val;
#ifndef NOT_IEEE754_FLOAT
	s32_t iX, iY;
	iX = (fX>0) ? ((s32_t&)fX) : ( (s32_t&) fX - 0x80000000 );
	iY = (fY>0) ? ((s32_t&)fY) : ( (s32_t&) fY - 0x80000000 );
	retn_val = (boolean_t)(bool)((vector_dim_op_alg < s32_t >::abs(iX-iY))< (s32_t)delta);
#else

	retn_val = (boolean_t)(fX == fY);
	FOR_ONE_LOOP_BEGIN

	BREAK_LOOP_CONDITION (retn_val);

	const float delta_abs = ((float)delta) / ((float)4194304);
	retn_val = (boolean_t)((vector_dim_op_alg < float >::abs (fX-fY) <= delta_abs));

	BREAK_LOOP_CONDITION (!retn_val);

	if (X > Y)
	{
		retn_val = (boolean_t)
		(vector_dim_op_alg < float >::abs((fX-fY)/fX ) < delta_abs );
	}
	else
	{
		retn_val = (boolean_t)
		(vector_dim_op_alg < float >::abs((fX-fY)/fY) < delta_abs);
	}
	FOR_ONE_LOOP_END
#endif
	return retn_val;
}

// double 特例化
template <>
PFX_INLINE boolean_t vector_dim_op_alg< double, 0 > ::equals (double fX, double fY, u32_t delta)
{
	boolean_t retn_val;

	retn_val = (boolean_t)(fX == fY);
	FOR_ONE_LOOP_BEGIN

	BREAK_LOOP_CONDITION (retn_val);

	const double delta_abs = ((double)delta) / ((double)2251799813685248);
	retn_val = (boolean_t)((vector_dim_op_alg < double >::abs (fX-fY) <= delta_abs));

	BREAK_LOOP_CONDITION (!retn_val);

	if (fX > fY)
	{
		retn_val = (boolean_t)
		(vector_dim_op_alg <double>::abs((fX-fY)/fX ) < delta_abs );
	}
	else
	{
		retn_val = (boolean_t)
		(vector_dim_op_alg <double>::abs((fX-fY)/fY) < delta_abs);
	}
	FOR_ONE_LOOP_END

	return retn_val;
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t PFX_VECDIM_ALG :: abs (PFX_VECDIM_ALG_TYPE::dim_t val)
{
	if (val < 0)
	{
		val = -val;
	}
	return val;
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t PFX_VECDIM_ALG :: add (PFX_VECDIM_ALG_TYPE::dim_t a, PFX_VECDIM_ALG_TYPE::dim_t b)
{
	return (a + b);
}
PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t& PFX_VECDIM_ALG::add_replace (PFX_VECDIM_ALG_TYPE::dim_t& a, PFX_VECDIM_ALG_TYPE::dim_t b)
{
	a += b;
	return a;
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t PFX_VECDIM_ALG::sub (PFX_VECDIM_ALG_TYPE::dim_t a, PFX_VECDIM_ALG_TYPE::dim_t b)
{
	return (a - b);
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t& PFX_VECDIM_ALG::sub_replace (PFX_VECDIM_ALG_TYPE::dim_t& a, PFX_VECDIM_ALG_TYPE::dim_t b)
{
	a -= b;
	return a;
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t PFX_VECDIM_ALG::mul (PFX_VECDIM_ALG_TYPE::dim_t a, PFX_VECDIM_ALG_TYPE::dim_t b)
{
	return (a * b);
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t& PFX_VECDIM_ALG::mul_replace (PFX_VECDIM_ALG_TYPE::dim_t& a, PFX_VECDIM_ALG_TYPE::dim_t b)
{
	a *= b;
	return a;
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t PFX_VECDIM_ALG::div (PFX_VECDIM_ALG_TYPE::dim_t a, PFX_VECDIM_ALG_TYPE::dim_t b)
{
	return (a / b);
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t& PFX_VECDIM_ALG::div_replace (PFX_VECDIM_ALG_TYPE::dim_t& a, PFX_VECDIM_ALG_TYPE::dim_t b)
{
	a /= b;
	return a;
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t PFX_VECDIM_ALG::sin (PFX_VECDIM_ALG_TYPE::dim_t rad)
{
	return rad;
}
template <>
PFX_INLINE float vector_dim_op_alg< float, 0 > ::sin(float rad)
{
	return ::sin (rad);
}
template <>
PFX_INLINE double vector_dim_op_alg< double, 0 > ::sin(double rad)
{
	return ::sin (rad);
}
template <>
PFX_INLINE int vector_dim_op_alg< int, 0 > ::sin(int rad)
{
	return SIN_TABLE (rad);
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t PFX_VECDIM_ALG::cos (PFX_VECDIM_ALG_TYPE::dim_t rad)
{
	return rad;
}

template <>
PFX_INLINE float vector_dim_op_alg< float, 0 > ::cos (float rad)
{
	return ::cos (rad);
}
template <>
PFX_INLINE double vector_dim_op_alg< double, 0 > ::cos(double rad)
{
	return ::cos (rad);
}
template <>
PFX_INLINE int vector_dim_op_alg< int, 0 > ::cos(int rad)
{
	return COS_TABLE (rad);
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t PFX_VECDIM_ALG::tan (PFX_VECDIM_ALG_TYPE::dim_t rad)
{
	return rad;
}
template <>
PFX_INLINE float vector_dim_op_alg< float, 0 > ::tan(float rad)
{
	return ::tan (rad);
}
template <>
PFX_INLINE double vector_dim_op_alg< double, 0 > ::tan(double rad)
{
	return ::tan (rad);
}
template <>
PFX_INLINE int vector_dim_op_alg< int, 0 > ::tan(int rad)
{
	return TAN_TABLE (rad);
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t PFX_VECDIM_ALG::acos (PFX_VECDIM_ALG_TYPE::dim_t rad)
{
	return rad;
}
template <>
PFX_INLINE float vector_dim_op_alg< float, 0 > ::acos(float rad)
{
	return ::tan (rad);
}
template <>
PFX_INLINE double vector_dim_op_alg< double, 0 > ::acos(double rad)
{
	return ::tan (rad);
}
template <>
PFX_INLINE int vector_dim_op_alg< int, 0 > ::acos(int rad)
{
	return TAN_TABLE (rad);
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE void PFX_VECDIM_ALG::sincos (PFX_VECDIM_ALG_TYPE::dim_t rad,
		PFX_VECDIM_ALG_TYPE::dim_t& sin_val,
		PFX_VECDIM_ALG_TYPE::dim_t &cos_val)
{
	;
}
template <>
PFX_INLINE void vector_dim_op_alg< float,0 > ::sincos (float rad,
		float& sin_val,
		float&cos_val)
{
	sin_val = ::sin(rad);
	cos_val = ::cos (rad);
}
template <>
PFX_INLINE void vector_dim_op_alg< double, 0 > ::sincos (double rad,
		double& sin_val,
		double&cos_val)
{
	sin_val = ::sin(rad);
	cos_val = ::cos (rad);
}
template <>
PFX_INLINE void vector_dim_op_alg< int, 0 > ::sincos (int rad,
		int& sin_val,
		int&cos_val)
{
	sin_val = SIN_TABLE (rad);
	cos_val = COS_TABLE (rad);
}

PFX_VECDIM_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VECDIM_ALG_TYPE::dim_t PFX_VECDIM_ALG::sqrt (PFX_VECDIM_ALG_TYPE::dim_t val)
{
	return val;
}
template <>
PFX_INLINE float vector_dim_op_alg < float > ::
sqrt (float val)
{
	return ::sqrt (val);
}
template <>
PFX_INLINE double vector_dim_op_alg < double > ::
sqrt (double val)
{
	return ::sqrt (val);
}
template <>
PFX_INLINE int vector_dim_op_alg < int > ::
sqrt (int val)
{
	return (int)::sqrt (PFX_INTX_2_FLOAT(val));
}

//////////////////////////////////////////////////////////////////////////

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE usize__t PFX_VEC_ALG::vector_dim_count()
{
	return vector_t :: vector_dim_count ();
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::dim_t& PFX_VEC_ALG::vector_at
(PFX_VEC_ALG_TYPE::vector_t& __vector,
		uindex_t dim_index)
{
	return __vector[dim_index];
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::dim_t& PFX_VEC_ALG::matrix_at
(PFX_VEC_ALG_TYPE::matrix_t& __matrix, uindex_t i, uindex_t j)
{
	return __matrix[i][j];
}
PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::dim_t& PFX_VEC_ALG::matrix_at
(PFX_VEC_ALG_TYPE::matrix_ex_t& __matrix, uindex_t i, uindex_t j)
{
	return (*__matrix[i])[j];
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::matrix_at
(PFX_VEC_ALG_TYPE::matrix_t& __matrix, uindex_t i,
		PFX_VEC_ALG_TYPE::vector_t& PARAM_INOUT vector_out)
{
	vector_out = __matrix[i];
	return vector_out;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::matrix_at
(PFX_VEC_ALG_TYPE::matrix_ex_t& __matrix, uindex_t i,
		PFX_VEC_ALG_TYPE::vector_t& PARAM_INOUT vector_out)
{
	vector_out = (*__matrix[i]);
	return vector_out;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t* PFX_VEC_ALG::matrix_at
(PFX_VEC_ALG_TYPE::matrix_t& __matrix, uindex_t i)
{
	return &__matrix[i];
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t*& PFX_VEC_ALG::matrix_at
(PFX_VEC_ALG_TYPE::matrix_ex_t& __matrix, uindex_t i)
{
	return __matrix[i];
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t* const& PFX_VEC_ALG::matrix_at_
(PFX_VEC_ALG_TYPE::matrix_ex_t& __matrix, uindex_t i)
{
	return __matrix[i];
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE const PFX_VEC_ALG_TYPE::dim_t& PFX_VEC_ALG::vector_at_const
(const PFX_VEC_ALG_TYPE::vector_t& __vector,
		uindex_t dim_index)
{
	return __vector[dim_index];
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE const PFX_VEC_ALG_TYPE::dim_t& PFX_VEC_ALG::matrix_at_const
(const PFX_VEC_ALG_TYPE::matrix_t& __matrix, uindex_t i, uindex_t j)
{
	return __matrix[i][j];
}
PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE const PFX_VEC_ALG_TYPE::dim_t& PFX_VEC_ALG::matrix_at_const
(const PFX_VEC_ALG_TYPE::matrix_ex_t& __matrix, uindex_t i, uindex_t j)
{
	return (*__matrix[i])[j];
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE const PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::matrix_at_const
(const PFX_VEC_ALG_TYPE::matrix_t& __matrix, uindex_t i,
		PFX_VEC_ALG_TYPE::vector_t& PARAM_INOUT vector_out)
{
	vector_out = __matrix[i];
	return vector_out;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE const PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::matrix_at_const
(const PFX_VEC_ALG_TYPE::matrix_ex_t& __matrix, uindex_t i,
		PFX_VEC_ALG_TYPE::vector_t& PARAM_INOUT vector_out)
{
	vector_out = (*__matrix[i]);
	return vector_out;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE const PFX_VEC_ALG_TYPE::vector_t* PFX_VEC_ALG::matrix_at_const
(const PFX_VEC_ALG_TYPE::matrix_t& __matrix, uindex_t i)
{
	return &__matrix[i];
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE const PFX_VEC_ALG_TYPE::vector_t* const& PFX_VEC_ALG::matrix_at_const
(const PFX_VEC_ALG_TYPE::matrix_ex_t& __matrix, uindex_t i)
{
	return __matrix[i];
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::init_vector
(PFX_VEC_ALG_TYPE::vector_t& __vector, const dim_t __val)
{
	usize__t dim_count = vector_dim_count ();
	return init_vector (__vector, __val, dim_count);
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::init_vector
(PFX_VEC_ALG_TYPE::vector_t& __vector,
		const dim_t __val, usize__t dim_count)
{
	uindex_t i=dim_count;
	while (i)
	{
		--i;
		vector_at(__vector, i) = __val;
	}
	return __vector;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::init_vector
(PFX_VEC_ALG_TYPE::vector_t& __vector,
		const PFX_VEC_ALG_TYPE::vector_t& other_vec)
{
	usize__t dim_count = vector_dim_count ();
	return init_vector(__vector, other_vec, dim_count);
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::init_vector
(PFX_VEC_ALG_TYPE::vector_t& __vector,
		const PFX_VEC_ALG_TYPE::vector_t& other_vec,
		usize__t dim_count)
{
	uindex_t i = dim_count;
	while (i)
	{
		--i;
		vector_at(__vector, i) = vector_at_const(other_vec, i);
	}
	return __vector;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::matrix_ex_t& PFX_VEC_ALG::init_matrix(matrix_ex_t& __matrix,
		const dim_t __val ,
		usize__t dim_count, usize__t vector_count)
{
	uindex_t i = vector_count;
	while (i)
	{
		--i;
		PFX_VEC_ALG_TYPE::vector_t& vec = *matrix_at(__matrix,i);
		init_vector(vec,__val,dim_count);
	}
	return __matrix;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::matrix_ex_t& PFX_VEC_ALG::init_matrix(matrix_ex_t& __matrix, const dim_t __val , usize__t vector_count)
{
	uindex_t i = vector_count;
	while (i)
	{
		--i;
		PFX_VEC_ALG_TYPE::vector_t& vec = *matrix_at(__matrix,i);
		init_vector(vec,__val);
	}
	return __matrix;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::matrix_ex_t& PFX_VEC_ALG::init_matrix(matrix_ex_t& __matrix, const matrix_t& s_matrix, usize__t vector_count)
{
	uindex_t i = vector_count;
	while (i)
	{
		--i;
		matrix_at(__matrix,i) = matrix_at(s_matrix,i);
	}
	return __matrix;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::matrix_t& PFX_VEC_ALG::init_matrix(matrix_t& __matrix, const dim_t __val , usize__t vector_count)
{
	uindex_t i = vector_count;
	while (i)
	{
		--i;
		PFX_VEC_ALG_TYPE::vector_t& vec = *matrix_at(__matrix,i);
		init_vector(vec,__val);
	}
	return __matrix;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::dim_t& PFX_VEC_ALG::vector_dot
(const PFX_VEC_ALG_TYPE::vector_t& __vec_a,
		const PFX_VEC_ALG_TYPE::vector_t& __vec__b,
		usize__t dim_count, dim_t& PARAM_INOUT __dim_result)
{
	typedef PFX_VEC_ALG_TYPE::dim_alg_t dim_alg_t;

	PFX_VEC_ALG_TYPE::dim_t return_val;
	return_val = dim_alg_t::mul (vector_at_const(__vec_a, 0), vector_at_const(__vec__b, 0));

	for (usize__t i=1; i<dim_count; ++i)
	{
		PFX_VEC_ALG_TYPE::dim_t temp;
		temp = dim_alg_t::mul (vector_at_const(__vec_a, i), vector_at_const(__vec__b, i));
		dim_alg_t::add_replace(return_val, temp);
	}
	__dim_result = return_val;
	return __dim_result;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::vector3_cross
(const PFX_VEC_ALG_TYPE::vector_t& __vec_a,
		const PFX_VEC_ALG_TYPE::vector_t& __vec_b,
		PFX_VEC_ALG_TYPE::vector_t& PARAM_INOUT __vec_result)
{
	typedef PFX_VEC_ALG_TYPE::dim_alg_t dim_alg_t;

	PFX_VEC_ALG_TYPE::dim_t temp;

	vector_at(__vec_result, DIMENSION_X) = dim_alg_t::mul (vector_at_const(__vec_a,DIMENSION_Y),
			vector_at_const(__vec_b, DIMENSION_Z));
	temp = dim_alg_t::mul (vector_at_const(__vec_a, DIMENSION_Z), vector_at_const(__vec_b, DIMENSION_Y));
	dim_alg_t::sub_replace(vector_at(__vec_result, DIMENSION_X), temp);

	vector_at(__vec_result, DIMENSION_Y) = dim_alg_t::mul (vector_at_const(__vec_a, DIMENSION_Z),
			vector_at_const(__vec_b, DIMENSION_X));
	temp = dim_alg_t::mul (vector_at_const(__vec_a, DIMENSION_X), vector_at_const(__vec_b, DIMENSION_Z));
	dim_alg_t::sub_replace(vector_at(__vec_result, DIMENSION_Y), temp);

	vector_at(__vec_result, DIMENSION_Z) = dim_alg_t::mul (vector_at_const(__vec_a, DIMENSION_X),
			vector_at_const(__vec_b, DIMENSION_Y));
	temp = dim_alg_t::mul (vector_at_const(__vec_a, DIMENSION_Y),
			vector_at_const(__vec_b, DIMENSION_X));
	dim_alg_t::sub_replace(vector_at(__vec_result, DIMENSION_Z), temp);

	return __vec_result;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::dim_t& PFX_VEC_ALG::vector_dot
(usize__t dim_count,
		const PFX_VEC_ALG_TYPE::matrix_ex_t& __matrix_a, uindex_t i_index,
		const PFX_VEC_ALG_TYPE::matrix_ex_t& __matrix_b, uindex_t j_index,
		PFX_VEC_ALG_TYPE::dim_t& PARAM_INOUT __dim_result)
{
	typedef PFX_VEC_ALG_TYPE::dim_alg_t dim_alg_t;
	PFX_VEC_ALG_TYPE::dim_t tmp_result;
	tmp_result = dim_alg_t::mul (matrix_at_const(__matrix_a, i_index, 0),
			matrix_at_const(__matrix_b, 0, j_index));

	for (usize__t i=1; i<dim_count; ++i)
	{
		PFX_VEC_ALG_TYPE::dim_t temp;
		temp = dim_alg_t::mul (matrix_at_const(__matrix_a, i_index, i),
				matrix_at_const(__matrix_b, i, j_index));
		dim_alg_t::add_replace(tmp_result, temp);
	}
	__dim_result = tmp_result;
	return __dim_result;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::dim_t& PFX_VEC_ALG::vector_dot
(usize__t dim_count,
		const PFX_VEC_ALG_TYPE::matrix_t& __matrix_a, uindex_t i_index,
		const PFX_VEC_ALG_TYPE::matrix_t& __matrix_b, uindex_t j_index,
		PFX_VEC_ALG_TYPE::dim_t& PARAM_INOUT __dim_result)
{
	typedef PFX_VEC_ALG_TYPE::dim_alg_t dim_alg_t;
	PFX_VEC_ALG_TYPE::dim_t tmp_result;
	tmp_result = dim_alg_t::mul (matrix_at_const(__matrix_a, i_index, 0),
			matrix_at_const(__matrix_b, 0, j_index));

	for (usize__t i=1; i<dim_count; ++i)
	{
		PFX_VEC_ALG_TYPE::dim_t temp;
		temp = dim_alg_t::mul (matrix_at_const(__matrix_a, i_index, i),
				matrix_at_const(__matrix_b, i, j_index));
		dim_alg_t::add_replace(tmp_result, temp);
	}
	__dim_result = tmp_result;
	return __dim_result;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::vector_mul (const PFX_VEC_ALG_TYPE::vector_t& __vec_a,
		const dim_t& __dim, usize__t dim_count,
		PFX_VEC_ALG_TYPE::vector_t& PARAM_INOUT __vec_result)
{
	typedef PFX_VEC_ALG_TYPE::dim_alg_t dim_alg_t;

	uindex_t i = dim_count;
	while (i)
	{
		--i;
		vector_at(__vec_result, i) = dim_alg_t::mul (__dim, vector_at_const(__vec_a, i));
	}
	return __vec_result;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::vector_mul (const PFX_VEC_ALG_TYPE::vector_t& __vec_a,
		const dim_t& __dim,
		PFX_VEC_ALG_TYPE::vector_t& PARAM_INOUT __vec_result)
{
	return vector_mul(__vec_a, __dim, vector_dim_count(), __vec_result);
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::vector_div (const PFX_VEC_ALG_TYPE::vector_t& __vec_a,
		const dim_t& __dim, usize__t dim_count,
		PFX_VEC_ALG_TYPE::vector_t& PARAM_INOUT __vec_result)
{
	typedef PFX_VEC_ALG_TYPE::dim_alg_t dim_alg_t;
	uindex_t i = dim_count;
	while (i)
	{
		--i;
		vector_at(__vec_result, i) = dim_alg_t::div (vector_at_const(__vec_a, i), __dim);
	}
	return __vec_result;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::vector_div (const PFX_VEC_ALG_TYPE::vector_t& __vec_a,
		const dim_t& __dim,
		PFX_VEC_ALG_TYPE::vector_t& PARAM_INOUT __vec_result)
{
	return vector_div(__vec_a, __dim, vector_dim_count(), __vec_result);
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::vector_add (const PFX_VEC_ALG_TYPE::vector_t& __vec_a,
		const PFX_VEC_ALG_TYPE::vector_t& __vec_b,
		usize__t dim_count, PFX_VEC_ALG_TYPE::vector_t& PARAM_INOUT __vec_result)
{
	typedef PFX_VEC_ALG_TYPE::dim_alg_t dim_alg_t;

	uindex_t i=dim_count;
	while (i)
	{
		--i;
		vector_at(__vec_result, i) = dim_alg_t::add (vector_at_const(__vec_a, i), vector_at_const(__vec_b,i));
	}
	return __vec_result;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::vector_add (const PFX_VEC_ALG_TYPE::vector_t& __vec_a,
		const PFX_VEC_ALG_TYPE::vector_t& __vec_b,
		PFX_VEC_ALG_TYPE::vector_t& PARAM_INOUT __vec_result)
{
	return vector_add(__vec_a, __vec_b, vector_dim_count(), __vec_result);
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::vector_sub (const PFX_VEC_ALG_TYPE::vector_t& __vec_a,
		const PFX_VEC_ALG_TYPE::vector_t& __vec_b,
		usize__t dim_count, PFX_VEC_ALG_TYPE::vector_t& PARAM_INOUT __vec_result)
{
	typedef PFX_VEC_ALG_TYPE::dim_alg_t dim_alg_t;

	uindex_t i = dim_count;
	while (i)
	{
		--i;
		vector_at(__vec_result, i) = dim_alg_t::sub (vector_at_const(__vec_a, i), vector_at_const(__vec_b,i));
	}
	return __vec_result;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::vector_t& PFX_VEC_ALG::vector_sub (const PFX_VEC_ALG_TYPE::vector_t& __vec_a,
		const PFX_VEC_ALG_TYPE::vector_t& __vec_b,
		PFX_VEC_ALG_TYPE::vector_t& PARAM_INOUT __vec_result)
{
	return vector_sub(__vec_a, __vec_b, vector_dim_count(), __vec_result);
}

// 直接相乘法
PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::matrix_t& PFX_VEC_ALG::matrix_mul_matrix_direct
(const PFX_VEC_ALG_TYPE::matrix_t& __mat_a,
		usize__t ai_count, usize__t aj_count, usize__t bj_count,
		const PFX_VEC_ALG_TYPE::matrix_t& __mat_b,
		matrix_t& PARAM_INOUT __mat_result)
{
	uindex_t i=ai_count;
	while (i)
	{
		--i;
		uindex_t j = bj_count;
		while(j)
		{
			--j;
			vector_dot(aj_count, __mat_a, i, __mat_b, j, matrix_at (__mat_result, i, j));
		}
	}

	return __mat_result;
}
PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::matrix_t& PFX_VEC_ALG::matrix_mul_value_direct
(const PFX_VEC_ALG_TYPE::matrix_t& __mat_a,
		usize__t i_count, usize__t j_count,
		const PFX_VEC_ALG_TYPE::dim_t& __dim,
		PFX_VEC_ALG_TYPE::matrix_t& PARAM_INOUT __mat_result)
{
	uindex_t i = i_count;
	while (i)
	{
		--i;
		vector_mul(__mat_a, __dim, j_count, *vector_at(__mat_result, i));
	}
	return __mat_result;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::matrix_t& PFX_VEC_ALG::matrix_div_value_direct
(const PFX_VEC_ALG_TYPE::matrix_t& __mat_a,
		usize__t i_count, usize__t j_count,
		const PFX_VEC_ALG_TYPE::dim_t& __dim,
		PFX_VEC_ALG_TYPE::matrix_t& PARAM_INOUT __mat_result)
{
	uindex_t i = i_count;
	while (i)
	{
		--i;
		vector_div(__mat_a, __dim, j_count, *vector_at(__mat_result,i));
	}
	return __mat_result;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::matrix_ex_t& PFX_VEC_ALG::matrix_mul_matrix_direct
(const PFX_VEC_ALG_TYPE::matrix_ex_t& __mat_a,
		usize__t ai_count, usize__t aj_count, usize__t bj_count,
		const PFX_VEC_ALG_TYPE::matrix_ex_t& __mat_b,
		matrix_ex_t& PARAM_INOUT __mat_result)
{
	uindex_t i=ai_count;
	while (i)
	{
		--i;
		uindex_t j = bj_count;
		while(j)
		{
			--j;
			vector_dot(aj_count, __mat_a, i, __mat_b, j, matrix_at (__mat_result, i, j));
		}
	}
	return __mat_result;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::matrix_ex_t& PFX_VEC_ALG::matrix_mul_value_direct
(const PFX_VEC_ALG_TYPE::matrix_ex_t& __mat_a,
		usize__t i_count, usize__t j_count,
		const PFX_VEC_ALG_TYPE::dim_t& __dim,
		PFX_VEC_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat_result)
{
	uindex_t i = i_count;
	while (i)
	{
		--i;
		vector_mul(__mat_a, __dim, j_count, *vector_at(__mat_result, i));
	}
	return __mat_result;
}

PFX_VEC_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_VEC_ALG_TYPE::matrix_ex_t& PFX_VEC_ALG::matrix_div_value_direct
(const PFX_VEC_ALG_TYPE::matrix_ex_t& __mat_a,
		usize__t i_count, usize__t j_count,
		const PFX_VEC_ALG_TYPE::dim_t& __dim,
		PFX_VEC_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat_result)
{
	uindex_t i = i_count;
	while (i)
	{
		--i;
		vector_div(__mat_a, __dim, j_count, *vector_at(__mat_result, i));
	}
	return __mat_result;
}

//////////////////////////////////////////////////////////////////////////
PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE usize__t PFX_SMAT_ALG::get_dim_count()
{
	return PFX_SMAT_ALG_TYPE::vec_alg_t::vector_dim_count ();
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_t& PFX_SMAT_ALG::Indentify_matrix (usize__t dim_count,
		PFX_SMAT_ALG_TYPE::matrix_t& __mat, dim_t val, dim_t null_val)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	for (uindex_t i=0; i<dim_count; ++i)
	{
		for (uindex_t j=0; j<i; ++j)
		{
			vec_alg_t::matrix_at (__mat, i, j) = null_val;
		}

		vec_alg_t::matrix_at (__mat, i, i) = val;

		for (uindex_t j=i+1; j<dim_count; ++j)
		{
			vec_alg_t::matrix_at (__mat, i, j) = null_val;
		}
	}
	return __mat;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_ex_t& PFX_SMAT_ALG::Indentify_matrix (usize__t dim_count,
		PFX_SMAT_ALG_TYPE::matrix_ex_t& __mat,
		PFX_SMAT_ALG_TYPE::dim_t val,
		PFX_SMAT_ALG_TYPE::dim_t null_val)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	for (uindex_t i=0; i<dim_count; ++i)
	{
		for (uindex_t j=0; j<i; ++j)
		{
			vec_alg_t::matrix_at (__mat, i, j) = null_val;
		}

		vec_alg_t::matrix_at (__mat, i, i) = val;

		for (uindex_t j=i+1; j<dim_count; ++j)
		{
			vec_alg_t::matrix_at (__mat, i, j) = null_val;
		}
	}
	return __mat;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_t& PFX_SMAT_ALG::transpose_matrix (usize__t dim_count,
		const PFX_SMAT_ALG_TYPE::matrix_t& __mat,
		PFX_SMAT_ALG_TYPE::matrix_t& __mat_reslut)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	if (&__mat != &__mat_reslut)
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			for (uindex_t j=0; j<dim_count; ++j)
			{
				vec_alg_t::matrix_at (__mat_reslut, i, j) = vec_alg_t::matrix_at_const (__mat_reslut, j, i);
			}
		}
	}
	else
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			uindex_t j=i+1;
			for (; j<dim_count; ++j)
			{
				dim_t tmpval = vec_alg_t::matrix_at_const (__mat_reslut, i, j);
				vec_alg_t::matrix_at (__mat_reslut, i, j) = vec_alg_t::matrix_at_const (__mat_reslut, j, i);
				vec_alg_t::matrix_at (__mat_reslut, j, i) = tmpval;
			}
		}
	}
	return __mat_reslut;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_ex_t& PFX_SMAT_ALG::transpose_matrix (usize__t dim_count,
		const PFX_SMAT_ALG_TYPE::matrix_ex_t& __mat,
		PFX_SMAT_ALG_TYPE::matrix_ex_t& __mat_reslut)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	if (&__mat != &__mat_reslut)
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			for (uindex_t j=0; j<dim_count; ++j)
			{
				vec_alg_t::matrix_at (__mat_reslut, i, j) = vec_alg_t::matrix_at_const (__mat_reslut, j, i);
			}
		}
	}
	else
	{
		for (uindex_t i=0; i<dim_count; ++i)
		{
			uindex_t j=i+1;
			for (; j<dim_count; ++j)
			{
				dim_t tmpval = vec_alg_t::matrix_at_const (__mat_reslut, i, j);
				vec_alg_t::matrix_at (__mat_reslut, i, j) = vec_alg_t::matrix_at_const (__mat_reslut, j, i);
				vec_alg_t::matrix_at (__mat_reslut, j, i) = tmpval;
			}
		}
	}
	return __mat_reslut;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::vector_t& PFX_SMAT_ALG::vector4_mul
(const PFX_SMAT_ALG_TYPE::vector_t& __mat_a,
		const PFX_SMAT_ALG_TYPE::matrix_t& __mat_b,
		PFX_SMAT_ALG_TYPE::vector_t& PARAM_INOUT __mat_result,
		PFX_SMAT_ALG_TYPE::vector_t* PARAM_INOUT __tempbuffer,
		u32_t delta)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	if (__tempbuffer)
	{
		vec_alg_t::vector_mul (*vec_alg_t::matrix_at_const(__mat_b,0), vec_alg_t::vector_at_const (__mat_a, 0), __mat_result);

		vec_alg_t::vector_mul (*vec_alg_t::matrix_at_const(__mat_b,1), vec_alg_t::vector_at_const (__mat_a, 1), *__tempbuffer);
		vec_alg_t::vector_add (*__tempbuffer, __mat_result, __mat_result);

		vec_alg_t::vector_mul (*vec_alg_t::matrix_at_const(__mat_b,2), vec_alg_t::vector_at_const (__mat_a, 2), *__tempbuffer);
		vec_alg_t::vector_add (*__tempbuffer, __mat_result, __mat_result);

		vec_alg_t::vector_mul (*vec_alg_t::matrix_at_const(__mat_b,3), vec_alg_t::vector_at_const (__mat_a, 3), *__tempbuffer);
		vec_alg_t::vector_add (*__tempbuffer, __mat_result, __mat_result);
	}
	else
	{
		dim_t tmp1;
		dim_t tmp2;
		//////////////////////////////////////////////////////////////////////////
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 0));
		tmp2 = tmp1;
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 0));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 0));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 3), vec_alg_t::matrix_at_const(__mat_b, 3, 0));
		dim_alg_t::add_replace (tmp2, tmp1);
		vec_alg_t::vector_at(__mat_result, 0) = tmp2;
		//////////////////////////////////////////////////////////////////////////
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 1));
		tmp2 = tmp1;
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 1));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 1));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 3), vec_alg_t::matrix_at_const(__mat_b, 3, 1));
		dim_alg_t::add_replace (tmp2, tmp1);
		vec_alg_t::vector_at(__mat_result, 1) = tmp2;
		//////////////////////////////////////////////////////////////////////////
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 2));
		tmp2 = tmp1;
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 2));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 2));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 3), vec_alg_t::matrix_at_const(__mat_b, 3, 2));
		dim_alg_t::add_replace (tmp2, tmp1);
		vec_alg_t::vector_at(__mat_result, 2) = tmp2;
		//////////////////////////////////////////////////////////////////////////
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 3));
		tmp2 = tmp1;
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 3));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 3));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 3), vec_alg_t::matrix_at_const(__mat_b, 3, 3));
		dim_alg_t::add_replace (tmp2, tmp1);
		vec_alg_t::vector_at(__mat_result, 3) = tmp2;
	}
	return __mat_result;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::vector_t& PFX_SMAT_ALG::vector4_mul
(const PFX_SMAT_ALG_TYPE::vector_t& __mat_a,
		const PFX_SMAT_ALG_TYPE::matrix_ex_t& __mat_b,
		PFX_SMAT_ALG_TYPE::vector_t& PARAM_INOUT __mat_result,
		PFX_SMAT_ALG_TYPE::vector_t* PARAM_INOUT __tempbuffer,
		u32_t delta)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	if (__tempbuffer)
	{
		vec_alg_t::vector_mul (*vec_alg_t::matrix_at_const(__mat_b,0), vec_alg_t::vector_at_const (__mat_a, 0), __mat_result);

		vec_alg_t::vector_mul (*vec_alg_t::matrix_at_const(__mat_b,1), vec_alg_t::vector_at_const (__mat_a, 1), *__tempbuffer);
		vec_alg_t::vector_add (*__tempbuffer, __mat_result, __mat_result);

		vec_alg_t::vector_mul (*vec_alg_t::matrix_at_const(__mat_b,2), vec_alg_t::vector_at_const (__mat_a, 2), *__tempbuffer);
		vec_alg_t::vector_add (*__tempbuffer, __mat_result, __mat_result);

		vec_alg_t::vector_mul (*vec_alg_t::matrix_at_const(__mat_b,3), vec_alg_t::vector_at_const (__mat_a, 3), *__tempbuffer);
		vec_alg_t::vector_add (*__tempbuffer, __mat_result, __mat_result);
	}
	else
	{
		dim_t tmp1;
		dim_t tmp2;
		//////////////////////////////////////////////////////////////////////////
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 0));
		tmp2 = tmp1;
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 0));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 0));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 3), vec_alg_t::matrix_at_const(__mat_b, 3, 0));
		dim_alg_t::add_replace (tmp2, tmp1);
		vec_alg_t::vector_at(__mat_result, 0) = tmp2;
		//////////////////////////////////////////////////////////////////////////
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 1));
		tmp2 = tmp1;
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 1));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 1));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 3), vec_alg_t::matrix_at_const(__mat_b, 3, 1));
		dim_alg_t::add_replace (tmp2, tmp1);
		vec_alg_t::vector_at(__mat_result, 1) = tmp2;
		//////////////////////////////////////////////////////////////////////////
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 2));
		tmp2 = tmp1;
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 2));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 2));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 3), vec_alg_t::matrix_at_const(__mat_b, 3, 2));
		dim_alg_t::add_replace (tmp2, tmp1);
		vec_alg_t::vector_at(__mat_result, 2) = tmp2;
		//////////////////////////////////////////////////////////////////////////
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 3));
		tmp2 = tmp1;
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 3));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 3));
		dim_alg_t::add_replace (tmp2, tmp1);
		tmp1 = dim_alg_t::mul (vec_alg_t::vector_at_const (__mat_a, 3), vec_alg_t::matrix_at_const(__mat_b, 3, 3));
		dim_alg_t::add_replace (tmp2, tmp1);
		vec_alg_t::vector_at(__mat_result, 3) = tmp2;
	}
	return __mat_result;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_t& PFX_SMAT_ALG::matrix2x2_mul
(const PFX_SMAT_ALG_TYPE::matrix_t& __mat_a,
		const PFX_SMAT_ALG_TYPE::matrix_t& __mat_b,
		PFX_SMAT_ALG_TYPE::matrix_t& PARAM_INOUT __mat_result,
		PFX_SMAT_ALG_TYPE::cw_buffer_t* PARAM_INOUT __tempbuffer,
		u32_t delta)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;
	dim_t temp1,temp2;

	// 0, 0
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 0), vec_alg_t::matrix_at_const(__mat_b,0,0));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 1), vec_alg_t::matrix_at_const(__mat_b,1,0));
	vec_alg_t::matrix_at (__mat_result, 0, 0) = dim_alg_t::add (temp1, temp2);

	//0, 1
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 0), vec_alg_t::matrix_at_const(__mat_b,0,1));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 1), vec_alg_t::matrix_at_const(__mat_b,1,1));
	vec_alg_t::matrix_at (__mat_result, 0, 1) = dim_alg_t::add (temp1, temp2);

	// 1, 0
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 0), vec_alg_t::matrix_at_const(__mat_b,0,0));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 1), vec_alg_t::matrix_at_const(__mat_b,1,0));
	vec_alg_t::matrix_at (__mat_result, 1, 0) = dim_alg_t::add (temp1, temp2);

	// 1, 1
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 0), vec_alg_t::matrix_at_const(__mat_b,0,1));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 1), vec_alg_t::matrix_at_const(__mat_b,1,1));
	vec_alg_t::matrix_at (__mat_result, 1, 1) = dim_alg_t::add (temp1, temp2);
	return __mat_result;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_t& PFX_SMAT_ALG::matrix3x3_mul
(const PFX_SMAT_ALG_TYPE::matrix_t& __mat_a,
		const PFX_SMAT_ALG_TYPE::matrix_t& __mat_b,
		PFX_SMAT_ALG_TYPE::matrix_t& PARAM_INOUT __mat_result,
		PFX_SMAT_ALG_TYPE::cw_buffer_t* PARAM_INOUT __tempbuffer,
		u32_t delta)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;
	dim_t temp1,temp2;

	// 0, 0
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 0));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 0));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 0));

	vec_alg_t::matrix_at (__mat_result, 0, 0) = dim_alg_t::add (temp1, temp2);
	// 0, 1
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 1));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 1));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 1));

	vec_alg_t::matrix_at (__mat_result, 0, 1) = dim_alg_t::add (temp1, temp2);
	// 0, 2
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 2));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 2));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 2));

	vec_alg_t::matrix_at (__mat_result, 0, 2) = dim_alg_t::add (temp1, temp2);

	// 1, 0
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 0));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 0));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 0));

	vec_alg_t::matrix_at (__mat_result, 1, 0) = dim_alg_t::add (temp1, temp2);
	// 1, 1
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 1));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 1));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 1));

	vec_alg_t::matrix_at (__mat_result, 1, 1) = dim_alg_t::add (temp1, temp2);
	// 1, 2
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 2));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 2));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 2));

	vec_alg_t::matrix_at (__mat_result, 1, 2) = dim_alg_t::add (temp1, temp2);

	// 2, 0
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 0));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 0));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 0));

	vec_alg_t::matrix_at (__mat_result, 2, 0) = dim_alg_t::add (temp1, temp2);
	// 2, 1
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 1));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 1));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 1));

	vec_alg_t::matrix_at (__mat_result, 2, 1) = dim_alg_t::add (temp1, temp2);
	// 2, 2
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 0), vec_alg_t::matrix_at_const(__mat_b, 0, 2));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 1), vec_alg_t::matrix_at_const(__mat_b, 1, 2));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 2), vec_alg_t::matrix_at_const(__mat_b, 2, 2));

	vec_alg_t::matrix_at (__mat_result, 2, 2) = dim_alg_t::add (temp1, temp2);
	return __mat_result;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_t& PFX_SMAT_ALG::matrixNxN_mul
(const PFX_SMAT_ALG_TYPE::matrix_t& __mat_a,
		const PFX_SMAT_ALG_TYPE::matrix_t& __mat_b,
		PFX_SMAT_ALG_TYPE::matrix_t& PARAM_INOUT __mat_result,
		PFX_SMAT_ALG_TYPE::cw_buffer_t* PARAM_INOUT __tempbuffer,
		u32_t delta)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	//if (__tempbuffer)
	//{

	//}
	//else
	//{
	vec_alg_t::matrix_mul_matrix_direct (__mat_a, vec_alg_t::vector_dim_count(),
			vec_alg_t::vector_dim_count(),
			vec_alg_t::vector_dim_count(),
			__mat_b,
			__mat_result);
	//}
	return __mat_result;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_ex_t& PFX_SMAT_ALG::matrix2x2_mul
(const PFX_SMAT_ALG_TYPE::matrix_ex_t& __mat_a,
		const PFX_SMAT_ALG_TYPE::matrix_ex_t& __mat_b,
		PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat_result,
		PFX_SMAT_ALG_TYPE::cw_buffer_t* PARAM_INOUT __tempbuffer,
		u32_t delta)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;
	dim_t temp1,temp2;

	// 0, 0
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 0), vec_alg_t::matrix_at_const(__mat_b,0,0));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 1), vec_alg_t::matrix_at_const(__mat_b,1,0));
	vec_alg_t::matrix_at (__mat_result, 0, 0) = dim_alg_t::add (temp1, temp2);

	//0, 1
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 0), vec_alg_t::matrix_at_const(__mat_b,0,1));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 1), vec_alg_t::matrix_at_const(__mat_b,1,1));
	vec_alg_t::matrix_at (__mat_result, 0, 1) = dim_alg_t::add (temp1, temp2);

	// 1, 0
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 0), vec_alg_t::matrix_at_const(__mat_b,0,0));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 1), vec_alg_t::matrix_at_const(__mat_b,1,0));
	vec_alg_t::matrix_at (__mat_result, 1, 0) = dim_alg_t::add (temp1, temp2);

	// 1, 1
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 0), vec_alg_t::matrix_at_const(__mat_b,0,1));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 1), vec_alg_t::matrix_at_const(__mat_b,1,1));
	vec_alg_t::matrix_at (__mat_result, 1, 1) = dim_alg_t::add (temp1, temp2);
	return __mat_result;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_ex_t& PFX_SMAT_ALG::matrix3x3_mul
(const PFX_SMAT_ALG_TYPE::matrix_ex_t& __mat_a,
		const PFX_SMAT_ALG_TYPE::matrix_ex_t& __mat_b,
		PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat_result,
		PFX_SMAT_ALG_TYPE::cw_buffer_t* PARAM_INOUT __tempbuffer,
		u32_t delta)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;
	dim_t temp1,temp2;

	// 0, 0
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 0), vec_alg_t::matrix_at_const(__mat_b,0,0));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 1), vec_alg_t::matrix_at_const(__mat_b,1,0));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 2), vec_alg_t::matrix_at_const(__mat_b,2,0));

	vec_alg_t::matrix_at (__mat_result, 0, 0) = dim_alg_t::add (temp1, temp2);
	// 0, 1
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 0), vec_alg_t::matrix_at_const(__mat_b,0,1));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 1), vec_alg_t::matrix_at_const(__mat_b,1,1));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 2), vec_alg_t::matrix_at_const(__mat_b,2,1));

	vec_alg_t::matrix_at (__mat_result, 0, 1) = dim_alg_t::add (temp1, temp2);
	// 0, 2
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 0), vec_alg_t::matrix_at_const(__mat_b,0,2));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 1), vec_alg_t::matrix_at_const(__mat_b,1,2));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 0, 2), vec_alg_t::matrix_at_const(__mat_b,2,2));

	vec_alg_t::matrix_at (__mat_result, 0, 2) = dim_alg_t::add (temp1, temp2);

	// 1, 0
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 0), vec_alg_t::matrix_at_const(__mat_b,0,0));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 1), vec_alg_t::matrix_at_const(__mat_b,1,0));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 2), vec_alg_t::matrix_at_const(__mat_b,2,0));

	vec_alg_t::matrix_at (__mat_result, 1, 0) = dim_alg_t::add (temp1, temp2);
	// 1, 1
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 0), vec_alg_t::matrix_at_const(__mat_b,0,1));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 1), vec_alg_t::matrix_at_const(__mat_b,1,1));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 2), vec_alg_t::matrix_at_const(__mat_b,2,1));

	vec_alg_t::matrix_at (__mat_result, 1, 1) = dim_alg_t::add (temp1, temp2);
	// 1, 2
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 0), vec_alg_t::matrix_at_const(__mat_b,0,2));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 1), vec_alg_t::matrix_at_const(__mat_b,1,2));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 1, 2), vec_alg_t::matrix_at_const(__mat_b,2,2));

	vec_alg_t::matrix_at (__mat_result, 1, 2) = dim_alg_t::add (temp1, temp2);

	// 2, 0
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 0), vec_alg_t::matrix_at_const(__mat_b,0,0));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 1), vec_alg_t::matrix_at_const(__mat_b,1,0));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 2), vec_alg_t::matrix_at_const(__mat_b,2,0));

	vec_alg_t::matrix_at (__mat_result, 2, 0) = dim_alg_t::add (temp1, temp2);
	// 2, 1
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 0), vec_alg_t::matrix_at_const(__mat_b,0,1));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 1), vec_alg_t::matrix_at_const(__mat_b,1,1));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 2), vec_alg_t::matrix_at_const(__mat_b,2,1));

	vec_alg_t::matrix_at (__mat_result, 2, 1) = dim_alg_t::add (temp1, temp2);
	// 2, 2
	temp1 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 0), vec_alg_t::matrix_at_const(__mat_b,0,2));
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 1), vec_alg_t::matrix_at_const(__mat_b,1,2));
	dim_alg_t::add_replace (temp1, temp2);
	temp2 = dim_alg_t::mul
	(vec_alg_t::matrix_at_const(__mat_a, 2, 2), vec_alg_t::matrix_at_const(__mat_b,2,2));

	vec_alg_t::matrix_at (__mat_result, 2, 2) = dim_alg_t::add (temp1, temp2);
	return __mat_result;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_ex_t& PFX_SMAT_ALG::matrixNxN_mul
(const PFX_SMAT_ALG_TYPE::matrix_ex_t& __mat_a,
		const PFX_SMAT_ALG_TYPE::matrix_ex_t& __mat_b,
		PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat_result,
		PFX_SMAT_ALG_TYPE::cw_buffer_t* PARAM_INOUT __tempbuffer,
		u32_t delta)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	//if (__tempbuffer)
	//{

	//}
	//else
	//{
	vec_alg_t::matrix_mul_matrix_direct (__mat_a, vec_alg_t::vector_dim_count(),
			vec_alg_t::vector_dim_count(),
			vec_alg_t::vector_dim_count(),
			__mat_b,
			__mat_result);
	//}
	return __mat_result;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_ex_t& PFX_SMAT_ALG::matrixNxN_mul
(usize__t dim_count,
		const matrix_ex_t& __mat_a, const matrix_ex_t& __mat_b,
		matrix_ex_t& PARAM_INOUT __mat_result,
		cw_buffer_t* PARAM_INOUT __tempbuffer,
		u32_t delta)
{

	return __mat_result;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE void PFX_SMAT_ALG::swap_line (PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __matrix,
		uindex_t i, uindex_t j)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::vector_t vector_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	vector_t* swap_ptr;
	swap_ptr = vec_alg_t::matrix_at(__matrix, i);
	vec_alg_t::matrix_at(__matrix, i) = vec_alg_t::matrix_at(__matrix, j);
	vec_alg_t::matrix_at(__matrix, j) = swap_ptr;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::clear_oneline
(PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __matrix,
		uindex_t test_line, uindex_t clear_line,
		uindex_t line_index, usize__t dim_count)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::vector_t vector_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	dim_t mul_factor;
	mul_factor = dim_alg_t::div (vec_alg_t::matrix_at (__matrix, test_line, line_index),
			vec_alg_t::matrix_at (__matrix, clear_line, line_index));

	for (uindex_t i=line_index; i<dim_count; ++i)
	{
		dim_alg_t::mul_replace(vec_alg_t::matrix_at (__matrix, clear_line, i), mul_factor);
		dim_alg_t::sub_replace(vec_alg_t::matrix_at (__matrix, clear_line, i), vec_alg_t::matrix_at (__matrix, test_line, i));
	}
	return mul_factor;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE void PFX_SMAT_ALG::clear_oneline_same
(PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __matrix,
		uindex_t test_line,
		uindex_t clear_line, PFX_SMAT_ALG_TYPE::dim_t mul_factor,
		usize__t dim_count)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::vector_t vector_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	for (uindex_t i=0; i<dim_count; ++i)
	{
		dim_alg_t::mul_replace(vec_alg_t::matrix_at (__matrix, clear_line, i), mul_factor);
		dim_alg_t::sub_replace(vec_alg_t::matrix_at (__matrix, clear_line, i),
				vec_alg_t::matrix_at (__matrix, test_line, i));
	}
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE void PFX_SMAT_ALG::restore_oneline
(PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __matrix,
		uindex_t restore_line,uindex_t line_index,
		PFX_SMAT_ALG_TYPE::dim_t mul_factor,
		usize__t dim_count)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::vector_t vector_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	for (uindex_t i=line_index; i<dim_count; ++i)
	{
		dim_alg_t::div_replace(vec_alg_t::matrix_at (__matrix, restore_line, i), mul_factor);
	}
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE usize__t PFX_SMAT_ALG::rev_clear_oneline
(PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __matrix,
		uindex_t clear_line,
		usize__t dim_count,
		PFX_SMAT_ALG_TYPE::clr_mul_factor_t* mul_factor, u32_t delta)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::vector_t vector_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;
	uindex_t fac_count = 0;
	uindex_t itr = 0;
	for (uindex_t i=dim_count-1; i>clear_line; --i)
	{
		if (dim_alg_t::equals(vec_alg_t::matrix_at (__matrix, clear_line, i), 0, delta))
		{
			continue;
		}
		mul_factor[itr].m_factor = dim_alg_t::div(vec_alg_t::matrix_at (__matrix, i, i),
				vec_alg_t::matrix_at (__matrix, clear_line, i));

		mul_factor[itr].m_index = i;

		for (uindex_t j=clear_line; j<dim_count; ++j)
		{
			dim_alg_t::mul_replace(vec_alg_t::matrix_at (__matrix, clear_line, j), mul_factor[itr].m_factor);
		}
		dim_alg_t::sub_replace(vec_alg_t::matrix_at (__matrix, clear_line, i),
				vec_alg_t::matrix_at (__matrix, i, i));
		++itr;
	}
	mul_factor[itr].m_index = INVALID_VALUE;
	return itr;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE void PFX_SMAT_ALG::rev_clear_oneline_same
(PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __matrix,
		uindex_t clear_line,
		usize__t dim_count,
		const PFX_SMAT_ALG_TYPE::clr_mul_factor_t* PARAM_IN mul_factor)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::vector_t vector_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	uindex_t fac_count = 0;
	uindex_t itr = 0;
	for (uindex_t i = clear_line; i<dim_count; ++i)
	{
		if (INVALID_VALUE == mul_factor[itr].m_index)
		{
			break;
		}

		for (uindex_t j=0; j<dim_count; ++j)
		{
			dim_alg_t::mul_replace(vec_alg_t::matrix_at (__matrix, clear_line, j),
					mul_factor[itr].m_factor);

			dim_alg_t::sub_replace(vec_alg_t::matrix_at (__matrix, clear_line, j),
					vec_alg_t::matrix_at (__matrix, mul_factor[itr].m_index, j));
		}

		++itr;
	}
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE void PFX_SMAT_ALG::restore_oneline
(PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __matrix,
		uindex_t restore_line, uindex_t line_index,
		PFX_SMAT_ALG_TYPE::dim_t mul_factor,
		usize__t dim_count,
		uindex_t except_j)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::vector_t vector_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	if (except_j > line_index)
	{
		for (uindex_t i=line_index; i<except_j; ++i)
		{
			dim_alg_t::div_replace(vec_alg_t::matrix_at (__matrix, restore_line, i), mul_factor);
		}

		for (uindex_t i=except_j+1; i<dim_count; ++i)
		{
			dim_alg_t::div_replace(vec_alg_t::matrix_at (__matrix, restore_line, i), mul_factor);
		}
	}
	else
	{
		if (except_j == line_index)
		{
			++line_index;
		}
		for (uindex_t i=line_index; i<dim_count; ++i)
		{
			dim_alg_t::div_replace(vec_alg_t::matrix_at (__matrix, restore_line, i), mul_factor);
		}
	}
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::
clear_oneline (PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __matrix,
		uindex_t test_line, uindex_t clear_line,
		uindex_t line_index, usize__t dim_count,
		uindex_t except_j)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::vector_t vector_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	dim_t mul_factor;
	mul_factor = dim_alg_t::div(vec_alg_t::matrix_at (__matrix, test_line, line_index),
			vec_alg_t::matrix_at (__matrix, clear_line, line_index));

	if (except_j > line_index)
	{
		for (uindex_t i=line_index; i<except_j; ++i)
		{
			dim_alg_t::mul_replace(vec_alg_t::matrix_at (__matrix, clear_line, i), mul_factor);
			dim_alg_t::sub_replace(vec_alg_t::matrix_at (__matrix, clear_line, i),
					vec_alg_t::matrix_at (__matrix, test_line, i));
		}
		for (uindex_t i=except_j+1; i<dim_count; ++i)
		{
			dim_alg_t::mul_replace(vec_alg_t::matrix_at (__matrix, clear_line, i), mul_factor);
			dim_alg_t::sub_replace(vec_alg_t::matrix_at (__matrix, clear_line, i),
					vec_alg_t::matrix_at (__matrix, test_line, i));
		}
	}
	else
	{
		if (except_j == line_index)
		{
			++line_index;
		}
		for (uindex_t i=line_index; i<dim_count; ++i)
		{
			dim_alg_t::mul_replace(vec_alg_t::matrix_at (__matrix, clear_line, i), mul_factor);
			dim_alg_t::sub_replace(vec_alg_t::matrix_at (__matrix, clear_line, i),
					vec_alg_t::matrix_at (__matrix, test_line, i));
		}
	}

	return mul_factor;
}



PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE uindex_t PFX_SMAT_ALG::find_test_line
(PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __matrix, uindex_t line_index,
		usize__t dim_count)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::vector_t vector_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	uindex_t res_index = line_index;
	dim_t max_abs = 0;

	for (uindex_t i = line_index; i<dim_count; ++i)
	{
		if (null == vec_alg_t::matrix_at(__matrix,i))
		{
			continue;
		}
		dim_t tmp_abs = dim_alg_t::abs(vec_alg_t::matrix_at(__matrix,i,line_index));
		if ( max_abs < tmp_abs)
		{
			res_index = i;
			max_abs = tmp_abs;
		}
	}

	return res_index;
}

// 求行列式的值和行列式
// 对角线法求解
PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix1x1_det (const PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	return vec_alg_t::matrix_at_const (__mat, 0, 0);
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix2x2_det (const PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	dim_t __pos;
	dim_t __neg;
	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 0), vec_alg_t::matrix_at_const (__mat, 1, 1));
	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 1), vec_alg_t::matrix_at_const (__mat, 1, 0));
	return dim_alg_t::sub (__pos, __neg);
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix3x3_det (const PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	dim_t __pos;
	dim_t __neg;
	dim_t __res;
	//////////////////////////////////////////////////////////////////////////

	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 2),
			vec_alg_t::matrix_at_const (__mat, 1, 1));
	dim_alg_t::mul_replace (__neg, vec_alg_t::matrix_at_const (__mat, 2, 0));

	__res = __neg;

	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 0),
			vec_alg_t::matrix_at_const (__mat, 1, 2));
	dim_alg_t::mul_replace (__neg, vec_alg_t::matrix_at_const (__mat, 2, 1));

	dim_alg_t::add_replace (__res, __neg);

	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 1),
			vec_alg_t::matrix_at_const (__mat, 1, 0));
	dim_alg_t::mul_replace (__neg, vec_alg_t::matrix_at_const (__mat, 2, 2));

	dim_alg_t::add_replace (__neg, __res);

	//////////////////////////////////////////////////////////////////////////
	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 0),
			vec_alg_t::matrix_at_const (__mat, 1, 1));
	dim_alg_t::mul_replace (__pos, vec_alg_t::matrix_at_const (__mat, 2, 2));

	__res = __pos;

	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 1),
			vec_alg_t::matrix_at_const (__mat, 1, 2));
	dim_alg_t::mul_replace (__pos, vec_alg_t::matrix_at_const (__mat, 2, 0));

	dim_alg_t::add_replace (__res, __pos);

	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 2),
			vec_alg_t::matrix_at_const (__mat, 1, 0));
	dim_alg_t::mul_replace (__pos, vec_alg_t::matrix_at_const (__mat, 2, 1));

	dim_alg_t::add_replace (__res, __pos);

	dim_alg_t::sub_replace (__res, __neg);

	return __res;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix1x1_algebraic_cofactor_det
(const PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat)
{
	return 0;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix2x2_algebraic_cofactor_det
(const PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat,
		usize__t x, usize__t y)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	return vec_alg_t::matrix_at_const (__mat,(0 == x)?1:0, (0 == y)?1:0);
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix3x3_algebraic_cofactor_det
(const PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat,
		usize__t x, usize__t y)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	dim_t __pos;
	dim_t __neg;
	//dim_t __temp;

	uindex_t map_xindex[2];
	uindex_t map_yindex[2];

	map_xindex [0] = (0 == x)?1:0;
	map_xindex [1] = (1 == x)?(x+1):(map_xindex [0]+1);

	map_yindex [0] = (0 == y)?1:0;
	map_yindex [1] = (1 == y)?(y+1):(map_yindex [0]+1);

	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[0]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[1]));
	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[1]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[0]));
	return dim_alg_t::sub (__pos, __neg);
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix4x4_algebraic_cofactor_det
(const PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat,
		usize__t x, usize__t y)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	uindex_t map_xindex[3];
	uindex_t map_yindex[3];

	map_xindex [0] = (0 == x)?1:0;
	map_xindex [1] = (1 == x)?(x+1):(map_xindex [0]+1);
	map_xindex [2] = (2 == x)?(x+1):(map_xindex [1]+1);

	map_yindex [0] = (0 == y)?1:0;
	map_yindex [1] = (1 == y)?(y+1):(map_yindex [0]+1);
	map_yindex [2] = (2 == y)?(y+1):(map_yindex [1]+1);

	dim_t __pos;
	dim_t __neg;
	dim_t __res;
	//////////////////////////////////////////////////////////////////////////

	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[2]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[1]));
	dim_alg_t::mul_replace (__neg, vec_alg_t::matrix_at_const (__mat, map_xindex[2], map_yindex[0]));

	__res = __neg;

	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[0]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[2]));
	dim_alg_t::mul_replace (__neg, vec_alg_t::matrix_at_const (__mat, map_xindex[2], map_yindex[1]));

	dim_alg_t::add_replace (__res, __neg);

	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[1]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[0]));
	dim_alg_t::mul_replace (__neg, vec_alg_t::matrix_at_const (__mat, map_xindex[2], map_yindex[2]));

	dim_alg_t::add_replace (__neg, __res);

	//////////////////////////////////////////////////////////////////////////
	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[0]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[1]));
	dim_alg_t::mul_replace (__pos, vec_alg_t::matrix_at_const (__mat, map_xindex[2], map_yindex[2]));

	__res = __pos;

	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[1]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[2]));
	dim_alg_t::mul_replace (__pos, vec_alg_t::matrix_at_const (__mat, map_xindex[2], map_yindex[0]));

	dim_alg_t::add_replace (__res, __pos);

	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[2]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[0]));
	dim_alg_t::mul_replace (__pos, vec_alg_t::matrix_at_const (__mat, map_xindex[2], map_yindex[1]));

	dim_alg_t::add_replace (__res, __pos);

	dim_alg_t::sub_replace (__res, __neg);

	return __res;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix1x1_det (const PFX_SMAT_ALG_TYPE::matrix_t& PARAM_INOUT __mat)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	return vec_alg_t::matrix_at_const (__mat, 0, 0);
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix2x2_det (const PFX_SMAT_ALG_TYPE::matrix_t& PARAM_INOUT __mat)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	dim_t __pos;
	dim_t __neg;
	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 0), vec_alg_t::matrix_at_const (__mat, 1, 1));
	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 1), vec_alg_t::matrix_at_const (__mat, 1, 0));
	return dim_alg_t::sub (__pos, __neg);
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix3x3_det (const PFX_SMAT_ALG_TYPE::matrix_t& PARAM_INOUT __mat)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	dim_t __pos;
	dim_t __neg;
	dim_t __res;
	//////////////////////////////////////////////////////////////////////////

	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 2),
			vec_alg_t::matrix_at_const (__mat, 1, 1));
	dim_alg_t::mul_replace (__neg, vec_alg_t::matrix_at_const (__mat, 2, 0));

	__res = __neg;

	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 0),
			vec_alg_t::matrix_at_const (__mat, 1, 2));
	dim_alg_t::mul_replace (__neg, vec_alg_t::matrix_at_const (__mat, 2, 1));

	dim_alg_t::add_replace (__res, __neg);

	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 1),
			vec_alg_t::matrix_at_const (__mat, 1, 0));
	dim_alg_t::mul_replace (__neg, vec_alg_t::matrix_at_const (__mat, 2, 2));

	dim_alg_t::add_replace (__neg, __res);

	//////////////////////////////////////////////////////////////////////////
	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 0),
			vec_alg_t::matrix_at_const (__mat, 1, 1));
	dim_alg_t::mul_replace (__pos, vec_alg_t::matrix_at_const (__mat, 2, 2));

	__res = __pos;

	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 1),
			vec_alg_t::matrix_at_const (__mat, 1, 2));
	dim_alg_t::mul_replace (__pos, vec_alg_t::matrix_at_const (__mat, 2, 0));

	dim_alg_t::add_replace (__res, __pos);

	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, 0, 2),
			vec_alg_t::matrix_at_const (__mat, 1, 0));
	dim_alg_t::mul_replace (__pos, vec_alg_t::matrix_at_const (__mat, 2, 1));

	dim_alg_t::add_replace (__res, __pos);

	dim_alg_t::sub_replace (__res, __neg);

	return __res;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix1x1_algebraic_cofactor_det
(const PFX_SMAT_ALG_TYPE::matrix_t& PARAM_INOUT __mat)
{
	return 0;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix2x2_algebraic_cofactor_det
(const PFX_SMAT_ALG_TYPE::matrix_t& PARAM_INOUT __mat,
		usize__t x, usize__t y)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	return vec_alg_t::matrix_at_const (__mat,(0 == x)?1:0, (0 == y)?1:0);
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix3x3_algebraic_cofactor_det
(const PFX_SMAT_ALG_TYPE::matrix_t& PARAM_INOUT __mat,
		usize__t x, usize__t y)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	dim_t __pos;
	dim_t __neg;
	//dim_t __temp;

	uindex_t map_xindex[2];
	uindex_t map_yindex[2];

	map_xindex [0] = (0 == x)?1:0;
	map_xindex [1] = (1 == x)?(x+1):(map_xindex [0]+1);

	map_yindex [0] = (0 == y)?1:0;
	map_yindex [1] = (1 == y)?(y+1):(map_yindex [0]+1);

	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[0]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[1]));
	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[1]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[0]));
	return dim_alg_t::sub (__pos, __neg);
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix4x4_algebraic_cofactor_det
(const PFX_SMAT_ALG_TYPE::matrix_t& PARAM_INOUT __mat,
		usize__t x, usize__t y)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	uindex_t map_xindex[3];
	uindex_t map_yindex[3];

	map_xindex [0] = (0 == x)?1:0;
	map_xindex [1] = (1 == x)?(x+1):(map_xindex [0]+1);
	map_xindex [2] = (2 == x)?(x+1):(map_xindex [1]+1);

	map_yindex [0] = (0 == y)?1:0;
	map_yindex [1] = (1 == y)?(y+1):(map_yindex [0]+1);
	map_yindex [2] = (2 == y)?(y+1):(map_yindex [1]+1);

	dim_t __pos;
	dim_t __neg;
	dim_t __res;
	//////////////////////////////////////////////////////////////////////////

	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[2]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[1]));
	dim_alg_t::mul_replace (__neg, vec_alg_t::matrix_at_const (__mat, map_xindex[2], map_yindex[0]));

	__res = __neg;

	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[0]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[2]));
	dim_alg_t::mul_replace (__neg, vec_alg_t::matrix_at_const (__mat, map_xindex[2], map_yindex[1]));

	dim_alg_t::add_replace (__res, __neg);

	__neg = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[1]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[0]));
	dim_alg_t::mul_replace (__neg, vec_alg_t::matrix_at_const (__mat, map_xindex[2], map_yindex[2]));

	dim_alg_t::add_replace (__neg, __res);

	//////////////////////////////////////////////////////////////////////////
	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[0]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[1]));
	dim_alg_t::mul_replace (__pos, vec_alg_t::matrix_at_const (__mat, map_xindex[2], map_yindex[2]));

	__res = __pos;

	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[1]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[2]));
	dim_alg_t::mul_replace (__pos, vec_alg_t::matrix_at_const (__mat, map_xindex[2], map_yindex[0]));

	dim_alg_t::add_replace (__res, __pos);

	__pos = dim_alg_t::mul(vec_alg_t::matrix_at_const (__mat, map_xindex[0], map_yindex[2]),
			vec_alg_t::matrix_at_const (__mat, map_xindex[1], map_yindex[0]));
	dim_alg_t::mul_replace (__pos, vec_alg_t::matrix_at_const (__mat, map_xindex[2], map_yindex[1]));

	dim_alg_t::add_replace (__res, __pos);

	dim_alg_t::sub_replace (__res, __neg);

	return __res;
}

// 高斯消元法
PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix_det
(PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat_replace,
		usize__t dim_count,
		u32_t delta)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	dim_t det = 1;
	for (uindex_t i=0; i<dim_count; ++i)
	{
		uindex_t j;
		// 找出主元最大的行，并选为主元行
		j = find_test_line (__mat_replace, i, dim_count);
		if (i != j)
		{
			swap_line(__mat_replace, i, j);
			det = -det;
		}
		// 判断是否可逆，不可逆的方阵，行列式的值必为0
		if (dim_alg_t::equals(vec_alg_t::matrix_at_const(__mat_replace, i, i), 0, delta))
		{
			det = 0;
			break;
		}
		//叠加值
		dim_alg_t::mul_replace(det, vec_alg_t::matrix_at_const(__mat_replace, i, i));

		if (i < dim_count-1)
		{
			// 消元并恢复
			for (uindex_t k=i+1; k< dim_count;++k)
			{
				if (dim_alg_t::equals(vec_alg_t::matrix_at_const(__mat_replace, k, i), 0, delta))
				{
					continue;
				}
				dim_t mul_factor = clear_oneline(__mat_replace, i, k, i, dim_count);
				restore_oneline (__mat_replace, k, i, mul_factor, dim_count);
			}
		}
	}
	return det;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::dim_t PFX_SMAT_ALG::matrix_algebraic_cofactor_det
(PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat_replace,
		usize__t dim_count,
		usize__t x, usize__t y,
		u32_t delta)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	dim_t det = 1;
	vec_alg_t::matrix_at (__mat_replace, x) = null;
	uindex_t j_itr = 0;
	for (uindex_t i=0; i<dim_count; ++i)
	{
		if (i == x)
		{
			continue;
		}
		uindex_t j;
		// 选取主元最大的一行
		j = find_test_line (__mat_replace, i, dim_count);
		if (i != j)
		{
			// 交换行
			swap_line (__mat_replace, i, j);
			det = -det;
		}
		if (y == j_itr)
		{
			++j_itr;
		}
		// 当主元为0的时候，行列式的值必为0，是不可逆方阵
		if (dim_alg_t::equals(vec_alg_t::matrix_at_const(__mat_replace, i, j_itr), 0, delta))
		{
			det = 0;
			break;
		}
		// 跌成行列式的值
		dim_alg_t::mul_replace(det, vec_alg_t::matrix_at_const(__mat_replace, i, j_itr));

		// 除主元行外消除主元列位置的其他行的值
		if (i < dim_count-1)
		{
			for (uindex_t k=i+1; k< dim_count;++k)
			{
				if (vec_alg_t::matrix_at_const(__mat_replace, k))
				{
					if (dim_alg_t::equals(vec_alg_t::matrix_at_const(__mat_replace, k, j_itr), 0, delta))
					{
						continue;
					}
					// 消除变换
					dim_t mul_factor = clear_oneline (__mat_replace, i, k, j_itr, dim_count, y);
					// 恢复变换
					restore_oneline (__mat_replace, k, j_itr, mul_factor, dim_count, y);
				}

			}
		}
		++j_itr;
	}
	return det;
}
//
// 求秩 （方阵）
PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE usize__t PFX_SMAT_ALG::matrix_rank (PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat_replace,
		usize__t dim_count, u32_t delta)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;

	usize__t rank = 0;

	for (uindex_t i=0; i<dim_count; ++i)
	{
		uindex_t j;
		j = find_test_line (__mat_replace, i, dim_count);
		if (i != j)
		{
			swap_line (__mat_replace, i, j);
		}
		if (dim_alg_t::equals(vec_alg_t::matrix_at_const(__mat_replace, i, i), 0, delta))
		{
			break;
		}
		++rank;

		if (i < dim_count-1)
		{
			for (uindex_t k=i+1; k< dim_count;++k)
			{
				if (dim_alg_t::equals(vec_alg_t::matrix_at_const(__mat_replace, k, i), 0, delta))
				{
					continue;
				}
				clear_oneline (__mat_replace, i, k, i, dim_count);
			}
		}
	}
	return rank;
}

//求逆矩阵
PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_ex_t* PFX_SMAT_ALG::inverse_matrix_for_3sp
(const PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat_a,
		PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat_inverse,
		u32_t delta)
{
	// 分块求逆法，只供特殊结构的矩阵使用
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;
	// MAT = [ A , C]
	//             [ 0  , 1]
	//使用分块求逆可得
	//inverse(MAT) = [ inverse(A), -inverse(A) C]
	//								[ 0,										1]
	//
	dim_t det_a = matrix3x3_det(__mat_a);
	// MAT的充分必要条件是 A可逆，所以A不可逆MAT也不可逆
	if (dim_alg_t::equals (det_a, 0, delta))
	{
		return null;
	}
	// A 可逆 3* 3可逆阵公式 inverse(A) = 1/det(A) * adj(A)
	det_a = 1/det_a;
	dim_t temp;
	// 注：伴随阵是代数余子式的转置
	temp = matrix3x3_algebraic_cofactor_det(__mat_a, 0, 0);
	vec_alg_t::matrix_at (__mat_inverse, 0, 0) = dim_alg_t::mul (det_a, temp);

	temp = -matrix3x3_algebraic_cofactor_det(__mat_a, 0, 1);
	vec_alg_t::matrix_at (__mat_inverse, 1, 0) = dim_alg_t::mul (det_a, temp);

	temp = matrix3x3_algebraic_cofactor_det(__mat_a, 0, 2);
	vec_alg_t::matrix_at (__mat_inverse, 2, 0) = dim_alg_t::mul (det_a, temp);

	temp = -matrix3x3_algebraic_cofactor_det(__mat_a, 1, 0);
	vec_alg_t::matrix_at (__mat_inverse, 0, 1) = dim_alg_t::mul (det_a, temp);

	temp = matrix3x3_algebraic_cofactor_det(__mat_a, 1, 1);
	vec_alg_t::matrix_at (__mat_inverse, 1, 1) = dim_alg_t::mul (det_a, temp);

	temp = -matrix3x3_algebraic_cofactor_det(__mat_a, 1, 2);
	vec_alg_t::matrix_at (__mat_inverse, 2, 1) = dim_alg_t::mul (det_a, temp);

	temp = matrix3x3_algebraic_cofactor_det(__mat_a, 2, 0);
	vec_alg_t::matrix_at (__mat_inverse, 0, 2) = dim_alg_t::mul (det_a, temp);

	temp = -matrix3x3_algebraic_cofactor_det(__mat_a, 2, 1);
	vec_alg_t::matrix_at (__mat_inverse, 1, 2) = dim_alg_t::mul (det_a, temp);

	temp = matrix3x3_algebraic_cofactor_det(__mat_a, 2, 2);
	vec_alg_t::matrix_at (__mat_inverse, 2, 2) = dim_alg_t::mul (det_a, temp);
	//-inverse(A) C
	vec_alg_t::vector_dot (3,__mat_inverse, 0, __mat_a, 3, vec_alg_t::matrix_at(__mat_inverse, 0, 3));
	vec_alg_t::vector_dot (3,__mat_inverse, 1, __mat_a, 3, vec_alg_t::matrix_at(__mat_inverse, 1, 3));
	vec_alg_t::vector_dot (3,__mat_inverse, 2, __mat_a, 3, vec_alg_t::matrix_at(__mat_inverse, 2, 3));
	vec_alg_t::matrix_at(__mat_inverse, 0, 3) = -vec_alg_t::matrix_at_const(__mat_inverse, 0, 3);
	vec_alg_t::matrix_at(__mat_inverse, 1, 3) = -vec_alg_t::matrix_at_const(__mat_inverse, 1, 3);
	vec_alg_t::matrix_at(__mat_inverse, 2, 3) = -vec_alg_t::matrix_at_const(__mat_inverse, 2, 3);
	//
	vec_alg_t::matrix_at(__mat_inverse, 3, 0) = vec_alg_t::matrix_at_const(__mat_a, 3, 0);
	vec_alg_t::matrix_at(__mat_inverse, 3, 1) = vec_alg_t::matrix_at_const(__mat_a, 3, 1);
	vec_alg_t::matrix_at(__mat_inverse, 3, 2) = vec_alg_t::matrix_at_const(__mat_a, 3, 2);
	vec_alg_t::matrix_at(__mat_inverse, 3, 3) = vec_alg_t::matrix_at_const(__mat_a, 3, 3);
	return __mat_inverse;
}

PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_t* PFX_SMAT_ALG::inverse_matrix_for_3sp
(const PFX_SMAT_ALG_TYPE::matrix_t& PARAM_INOUT __mat_a,
		PFX_SMAT_ALG_TYPE::matrix_t& PARAM_INOUT __mat_inverse,
		u32_t delta)
{

	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;
	// MAT = [ A , C]
	//             [ 0  , 1]
	//使用分块求逆可得
	//inverse(MAT) = [ inverse(A), -inverse(A) C]
	//								[ 0,										1]
	//
	dim_t det_a = matrix3x3_det(__mat_a);
	// MAT的充分必要条件是 A可逆，所以A不可逆MAT也不可逆
	if (dim_alg_t::equals (det_a, 0, delta))
	{
		return null;
	}
	// A 可逆 3* 3可逆阵公式 inverse(A) = 1/det(A) * adj(A)
	det_a = 1/det_a;
	dim_t temp;
	// 注：伴随阵是代数余子式的转置
	temp = matrix3x3_algebraic_cofactor_det(__mat_a, 0, 0);
	vec_alg_t::matrix_at (__mat_inverse, 0, 0) = dim_alg_t::mul (det_a, temp);

	temp = -matrix3x3_algebraic_cofactor_det(__mat_a, 0, 1);
	vec_alg_t::matrix_at (__mat_inverse, 1, 0) = dim_alg_t::mul (det_a, temp);

	temp = matrix3x3_algebraic_cofactor_det(__mat_a, 0, 2);
	vec_alg_t::matrix_at (__mat_inverse, 2, 0) = dim_alg_t::mul (det_a, temp);

	temp = -matrix3x3_algebraic_cofactor_det(__mat_a, 1, 0);
	vec_alg_t::matrix_at (__mat_inverse, 0, 1) = dim_alg_t::mul (det_a, temp);

	temp = matrix3x3_algebraic_cofactor_det(__mat_a, 1, 1);
	vec_alg_t::matrix_at (__mat_inverse, 1, 1) = dim_alg_t::mul (det_a, temp);

	temp = -matrix3x3_algebraic_cofactor_det(__mat_a, 1, 2);
	vec_alg_t::matrix_at (__mat_inverse, 2, 1) = dim_alg_t::mul (det_a, temp);

	temp = matrix3x3_algebraic_cofactor_det(__mat_a, 2, 0);
	vec_alg_t::matrix_at (__mat_inverse, 0, 2) = dim_alg_t::mul (det_a, temp);

	temp = -matrix3x3_algebraic_cofactor_det(__mat_a, 2, 1);
	vec_alg_t::matrix_at (__mat_inverse, 1, 2) = dim_alg_t::mul (det_a, temp);

	temp = matrix3x3_algebraic_cofactor_det(__mat_a, 2, 2);
	vec_alg_t::matrix_at (__mat_inverse, 2, 2) = dim_alg_t::mul (det_a, temp);
	//-inverse(A) C
	vec_alg_t::vector_dot (3,__mat_inverse, 0, __mat_a, 3, vec_alg_t::matrix_at(__mat_inverse, 0, 3));
	vec_alg_t::vector_dot (3,__mat_inverse, 1, __mat_a, 3, vec_alg_t::matrix_at(__mat_inverse, 1, 3));
	vec_alg_t::vector_dot (3,__mat_inverse, 2, __mat_a, 3, vec_alg_t::matrix_at(__mat_inverse, 2, 3));
	vec_alg_t::matrix_at(__mat_inverse, 0, 3) = -vec_alg_t::matrix_at_const(__mat_inverse, 0, 3);
	vec_alg_t::matrix_at(__mat_inverse, 1, 3) = -vec_alg_t::matrix_at_const(__mat_inverse, 1, 3);
	vec_alg_t::matrix_at(__mat_inverse, 2, 3) = -vec_alg_t::matrix_at_const(__mat_inverse, 2, 3);
	//
	vec_alg_t::matrix_at(__mat_inverse, 3, 0) = vec_alg_t::matrix_at_const(__mat_a, 3, 0);
	vec_alg_t::matrix_at(__mat_inverse, 3, 1) = vec_alg_t::matrix_at_const(__mat_a, 3, 1);
	vec_alg_t::matrix_at(__mat_inverse, 3, 2) = vec_alg_t::matrix_at_const(__mat_a, 3, 2);
	vec_alg_t::matrix_at(__mat_inverse, 3, 3) = vec_alg_t::matrix_at_const(__mat_a, 3, 3);
	return &__mat_inverse;
}

// 高斯消元法求逆
PFX_SMAT_ALG_TEMPLATE_DEFINES
PFX_INLINE PFX_SMAT_ALG_TYPE::matrix_ex_t* PFX_SMAT_ALG::inverse_matrix
(PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat_replace,
		usize__t dim_count,
		PFX_SMAT_ALG_TYPE::matrix_ex_t& PARAM_INOUT __mat_inverse,
		PFX_SMAT_ALG_TYPE::clr_mul_factor_t* mul_factor_ptr,
		u32_t delta)
{
	typedef PFX_SMAT_ALG_TYPE::vec_alg_t vec_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_alg_t dim_alg_t;
	typedef PFX_SMAT_ALG_TYPE::dim_t dim_t;
	typedef PFX_SMAT_ALG_TYPE::clr_mul_factor_t clr_mul_factor_t;

	// 采用外部buffer传入方式更利于cache
	if (null == mul_factor_ptr)
	{
		return null;
	}
	//#define MAX_CLEAR_MUL_SIZE (50)
	//clr_mul_factor_t mul_factor[MAX_CLEAR_MUL_SIZE];
	//clr_mul_factor_t* mul_factor_ptr;

	// A * inverse(A) = E
	// 原理：
	// (A | E) ------初等变换-----> (E | A^(-1))
	if (0 == dim_count)
	{
		return null;
	}
	if (1 == dim_count)
	{
		dim_t tmp = vec_alg_t::matrix_at_const (__mat_replace, 0, 0);
		if (dim_alg_t::equals(tmp, 0, delta))
		{
			return null;
		}
		else
		{
			vec_alg_t::matrix_at (__mat_inverse, 0, 0) = tmp;
			return &__mat_inverse;
		}
	}
	usize__t rank = 0;
	// 单位化
	Indentify_matrix(dim_count, __mat_inverse, 1, 0);

	// 第一步，先将原矩阵按高斯消元法三角化, 单位阵做一样的操作
	for (uindex_t i=0; i<dim_count; ++i)
	{
		uindex_t j;
		j = find_test_line (__mat_replace, i, dim_count);
		if (i != j)
		{
			swap_line(__mat_replace, i, j);
			swap_line(__mat_inverse, i, j);
		}
		if (dim_alg_t::equals(vec_alg_t::matrix_at_const(__mat_replace, i, i), 0, delta))
		{
			break;
		}
		++rank;

		if (i < dim_count-1)
		{
			for (uindex_t k=i+1; k< dim_count;++k)
			{
				if (dim_alg_t::equals (vec_alg_t::matrix_at_const(__mat_replace, k, i), 0, delta))
				{
					continue;
				}
				dim_t mul_factor = clear_oneline (__mat_replace, i, k, i, dim_count);
				clear_oneline_same (__mat_inverse, i, k, mul_factor, dim_count);
			}
		}
	}
	// 方阵的秩不满，矩阵不可逆
	RETURN_INVALID_RESULT (dim_count != rank,null);

	//if (dim_count > MAX_CLEAR_MUL_SIZE)
	//{
	//	mul_factor_ptr = new clr_mul_factor_t[dim_count];
	//}
	//else
	//{
	//	mul_factor_ptr = mul_factor_ptr;
	//}
	// 第二步，将三角阵转为对角线
	if (dim_count > 2)
	{
		for (uindex_t i=(dim_count-2); i>0; --i)
		{
			rev_clear_oneline (__mat_replace, i, dim_count, mul_factor_ptr, delta);
			rev_clear_oneline_same (__mat_inverse, i, dim_count, mul_factor_ptr);
		}
	}
	rev_clear_oneline (__mat_replace, 0, dim_count, mul_factor_ptr, delta);
	rev_clear_oneline_same (__mat_inverse, 0, dim_count, mul_factor_ptr);

	//if (dim_count > MAX_CLEAR_MUL_SIZE)
	//{
	//	delete [] mul_factor_ptr;
	//	mul_factor_ptr = null;
	//}

	// 第三步,单位化
	for (uindex_t i=0; i<dim_count; ++i)
	{
		vec_alg_t::vector_div (*vec_alg_t::matrix_at_const (__mat_inverse,i),
				vec_alg_t::matrix_at_const(__mat_replace, i, i),
				*vec_alg_t::matrix_at(__mat_inverse,i));
	}
	return &__mat_inverse;
}
//

PECKER_END

#endif			//PFX_CVECTOR_ALG_CODES_H_
