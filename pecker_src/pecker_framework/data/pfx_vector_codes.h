/*
 * pfx_vector.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_VECTOR_CODES_H_
#define		PFX_VECTOR_CODES_H_

#include "pfx_vector.h"
#include "pfx_fixed_point.h"
#include <math.h>
PECKER_BEGIN

#define DIMENSION_VAL_OP_TEMPLATE_DEFS template < class dimension_value >
#define DIMENSION_VAL_OP_TEMPLATE_PARAMS < dimension_value >

#define VERCOTOR_TEMPLATE_DEFS	template < class dimension_value_operations, const pfx_usize_t	dimensional_count, const pfx_enum_int_t optional_type >
#define VERCOTOR_TEMPLATE_PARAMS < dimension_value_operations, dimensional_count, optional_type >
#define DIM_VALUE_TYPE typename dimension_value_operations::dimension_value_t

DIMENSION_VAL_OP_TEMPLATE_DEFS
PFX_INLINE pfx_boolean_t dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS::
	equals (dimension_value X, dimension_value Y, pfx_u32_t delta)
{
	return (pfx_boolean_t)((bool)(X == Y));
}

// float 特例化
template <>
PFX_INLINE pfx_boolean_t dimension_value_operations < float >::
	equals (float fX, float fY, pfx_u32_t delta)
{
	pfx_boolean_t retn_val;
#ifndef NOT_IEEE754_FLOAT
	pfx_s32_t iX, iY;
	iX = (fX>0) ? ((pfx_s32_t&)fX)  : ( (pfx_s32_t&) fX - 0x80000000 );
	iY = (fY>0) ? ((pfx_s32_t&)fY)  : ( (pfx_s32_t&) fY - 0x80000000 );
	retn_val =  (pfx_boolean_t)((bool)((dimension_value_operations < float >::abs(iX-iY))<delta));
#else
	
	retn_val =  (pfx_boolean_t)(fX == fY);
	FOR_ONE_LOOP_BEGIN
		
	BREAK_LOOP_CONDITION (retn_val);
	
	
	const float delta_abs = ((float)delta) / ((float)4194304);
	retn_val =  (pfx_boolean_t)((dimension_value_operations < float >::abs (fX-fY) <= delta_abs));
	
	BREAK_LOOP_CONDITION (!retn_val);

	if (X > Y)
	{
		retn_val = (pfx_boolean_t)
			(dimension_value_operations < float >::abs((fX-fY)/fX ) < delta_abs ); 
	}
	else
	{
		retn_val =  (pfx_boolean_t)
			(dimension_value_operations < float >::abs((fX-fY)/fY) < delta_abs); 
	}
	FOR_ONE_LOOP_END
#endif
	return retn_val;
}

// double 特例化
template <>
PFX_INLINE pfx_boolean_t dimension_value_operations < double >::
	equals (double fX, double fY, pfx_u32_t delta)
{
	pfx_boolean_t retn_val;

	retn_val =  (pfx_boolean_t)(fX == fY);
	FOR_ONE_LOOP_BEGIN

		BREAK_LOOP_CONDITION (retn_val);


	const double delta_abs = ((double)delta) / ((double)2251799813685248);
	retn_val =  (pfx_boolean_t)((dimension_value_operations < double >::abs (fX-fY) <= delta_abs));

	BREAK_LOOP_CONDITION (!retn_val);

	if (fX > fY)
	{
		retn_val = (pfx_boolean_t)
			(dimension_value_operations <double>::abs((fX-fY)/fX ) < delta_abs ); 
	}
	else
	{
		retn_val =  (pfx_boolean_t)
			(dimension_value_operations <double>::abs((fX-fY)/fY) < delta_abs); 
	}
	FOR_ONE_LOOP_END

	return retn_val;
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
PFX_INLINE dimension_value dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS::
	abs (dimension_value val)
{
	if (val < 0)
	{
		val = -val;
	}
	return val;
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
PFX_INLINE dimension_value dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS::
	add (dimension_value a,dimension_value b)
{
	return (a + b);
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
PFX_INLINE dimension_value& dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS::
	add_replace (dimension_value& a,dimension_value b)
{
	a+=b;
	return a; 
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
PFX_INLINE dimension_value dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS::
	sub (dimension_value a,dimension_value b)
{
	return (a-b);
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
PFX_INLINE dimension_value& dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS::
	sub_replace (dimension_value& a,dimension_value b)
{
	a -= b;
	return a;
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
PFX_INLINE dimension_value dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS::
	mul (dimension_value a,dimension_value b)
{
	return (a * b);
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
PFX_INLINE dimension_value& dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS::
	mul_replace (dimension_value& a,dimension_value b)
{
	a *= b;
	return a;
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
PFX_INLINE dimension_value dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS::
	div (dimension_value a,dimension_value b)
{
	return (a / b);
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
PFX_INLINE dimension_value& dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS::
	div_replace (dimension_value& a,dimension_value b)
{
	a /= b;
	return a; 
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
PFX_INLINE dimension_value dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS::sin (dimension_value rad)
{
	return rad;
}

template <>
PFX_INLINE float dimension_value_operations< float > ::sin(float rad)
{
	return ::sin (rad);
}
template <>
PFX_INLINE double dimension_value_operations< double > ::sin(double rad)
{
	return ::sin (rad);
}
template <>
PFX_INLINE int dimension_value_operations< int > ::sin(int rad)
{
	return SIN_TABLE (rad);
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
	PFX_INLINE dimension_value dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS::cos (dimension_value rad)
{
	return rad;
}

template <>
PFX_INLINE float dimension_value_operations< float > ::cos (float rad)
{
	return ::cos (rad);
}
template <>
PFX_INLINE double dimension_value_operations< double > ::cos(double rad)
{
	return ::cos (rad);
}
template <>
PFX_INLINE int dimension_value_operations< int > ::cos(int rad)
{
	return COS_TABLE (rad);
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
	PFX_INLINE dimension_value dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS::tan (dimension_value rad)
{
	return rad;
}

template <>
PFX_INLINE float dimension_value_operations< float > ::tan(float rad)
{
	return ::tan (rad);
}
template <>
PFX_INLINE double dimension_value_operations< double > ::tan(double rad)
{
	return ::tan (rad);
}
template <>
PFX_INLINE int dimension_value_operations< int > ::tan(int rad)
{
	return TAN_TABLE (rad);
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
	PFX_INLINE void dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS ::
	sincos (dimension_value rad,
			dimension_value& sin_val,
			dimension_value &cos_val)
{
	;
}

template <>
PFX_INLINE void dimension_value_operations< float > ::sincos (float rad,
	float& sin_val,
	float&cos_val)
{
	sin_val = ::sin(rad);
	cos_val = ::cos (rad);
}
template <>
PFX_INLINE void dimension_value_operations< double > ::sincos (double rad,
	double& sin_val,
	double&cos_val)
{
	sin_val = ::sin(rad);
	cos_val = ::cos (rad);
}
template <>
PFX_INLINE void dimension_value_operations< int > ::sincos (int rad,
	int& sin_val,
	int&cos_val)
{
	sin_val = SIN_TABLE (rad);
	cos_val = COS_TABLE (rad);
}

DIMENSION_VAL_OP_TEMPLATE_DEFS
PFX_INLINE dimension_value dimension_value_operations DIMENSION_VAL_OP_TEMPLATE_PARAMS ::
sqrt (dimension_value val)
{
	return val;
}

template <>
PFX_INLINE float dimension_value_operations < float > ::
	sqrt (float val)
{
	return ::sqrt (val);
}
template <>
PFX_INLINE double dimension_value_operations < double > ::
	sqrt (double val)
{
	return ::sqrt (val);
}
template <>
PFX_INLINE int dimension_value_operations < int > ::
	sqrt (int val)
{
	return ::sqrt (PFX_INTX_2_FLOAT(val));
}

template < class vector_type,
	const pfx_enum_int_t optional_type >
PFX_INLINE st_pfx_vector <typename vector_type::dimension_value_t, 3>
	cross_vec3_unsafe (const st_pfx_vector <typename vector_type::dimension_value_t, 3>* vec_a,
	const st_pfx_vector <typename vector_type::dimension_value_t, 3>* vec_b)
{
	typedef typename vector_type::dimension_value_operations_t dimension_value_operations_t; 
	st_pfx_vector <typename vector_type::dimension_value_t, 3> res_vec;

	typename vector_type::dimension_value_t* vec_res_ptr = res_vec.m_value;
	const typename vector_type::dimension_value_t* vec_a_dim_ptr = vec_a->m_value;
	const typename vector_type::dimension_value_t* vec_b_dim_ptr = vec_b->m_value;

	typename vector_type::dimension_value_t temp;

	vec_res_ptr[DIMENSION_X] = dimension_value_operations_t ::mul (vec_a_dim_ptr[DIMENSION_Y],
		vec_b_dim_ptr[DIMENSION_Z]);
	temp = dimension_value_operations_t ::mul (vec_a_dim_ptr[DIMENSION_Z],
		vec_b_dim_ptr[DIMENSION_Y]);
	dimension_value_operations_t ::sub_replace(vec_res_ptr[DIMENSION_X],temp);

	vec_res_ptr[DIMENSION_Y] = dimension_value_operations_t ::mul (vec_a_dim_ptr[DIMENSION_Z],
		vec_b_dim_ptr[DIMENSION_X]);
	temp = dimension_value_operations_t ::mul (vec_a_dim_ptr[DIMENSION_X],
		vec_b_dim_ptr[DIMENSION_Z]);
	dimension_value_operations_t ::sub_replace(vec_res_ptr[DIMENSION_Y],temp);


	vec_res_ptr[DIMENSION_Z] = dimension_value_operations_t ::mul (vec_a_dim_ptr[DIMENSION_X],
		vec_b_dim_ptr[DIMENSION_Y]);
	temp = dimension_value_operations_t ::mul (vec_a_dim_ptr[DIMENSION_Y],
		vec_b_dim_ptr[DIMENSION_X]);
	dimension_value_operations_t ::sub_replace(vec_res_ptr[DIMENSION_Z],temp);

	return res_vec;
}

template < class vector_type,
	const pfx_enum_int_t optional_type >
	PFX_INLINE st_pfx_vector <typename vector_type::dimension_value_t, 3>
	cross_vec3 (const st_pfx_vector <typename vector_type::dimension_value_t, 3>& vec3,
	const vector_type* vec_ptr)
{
	return cross_vec3 < vector_type, optional_type > (&vec3,vec_ptr);
}

template < class vector_type,
	const pfx_enum_int_t optional_type >
	PFX_INLINE st_pfx_vector <typename vector_type::dimension_value_t, 3>
	cross_vec (const vector_type* vec_a, const vector_type* vec_b)
{
	if (vec_a && vec_b && 
		vec_a->get_dimensional_count () >= 3 && 
		vec_b->get_dimensional_count () >= 3)
	{
		return cross_vec3_unsafe (
			(const st_pfx_vector <typename vector_type::dimension_value_t, 3>*)vec_a,
			(const st_pfx_vector <typename vector_type::dimension_value_t, 3>*)vec_b);
	}
	else
	{
		st_pfx_vector <typename vector_type::dimension_value_t, 3> res_vec;
		return res_vec;
	}
}

template < class vector_type,
	const pfx_enum_int_t optional_type >
	PFX_INLINE vector_type*
	cross_vec_replace (vector_type* vec_a, const vector_type* vec_b)
{
	if (vec_a && vec_b && 
		vec_a->get_dimensional_count () >= 3 && 
		vec_b->get_dimensional_count () >= 3)
	{
		st_pfx_vector <typename vector_type::dimension_value_t, 3> res_vec
			cross_vec3_unsafe (
			(const st_pfx_vector <typename vector_type::dimension_value_t, 3>*)vec_a,
			(const st_pfx_vector <typename vector_type::dimension_value_t, 3>*)vec_b);

		((st_pfx_vector <typename vector_type::dimension_value_t, 3>*)vec_a)[0] = res_vec;
		return vec_a;
	}
	else
	{
		return null;
	}
}

//	DIM_VALUE_TYPE
VERCOTOR_TEMPLATE_DEFS
	pfx_vector VERCOTOR_TEMPLATE_PARAMS::pfx_vector () 
{
	memset (&m_dim,0,sizeof (m_dim));
}

VERCOTOR_TEMPLATE_DEFS
pfx_vector VERCOTOR_TEMPLATE_PARAMS::pfx_vector(dimension_value_t dim_set)
{
	for (pfx_uindex_t i=0; i<dimensional_count; ++i)
	{
		m_dim.m_value[i] = dim_set;
	}
}

VERCOTOR_TEMPLATE_DEFS
	pfx_vector VERCOTOR_TEMPLATE_PARAMS::pfx_vector (const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& dim)
{
	if (&dim != &m_dim)
	{
		m_dim = dim;
	}
}
VERCOTOR_TEMPLATE_DEFS
pfx_vector VERCOTOR_TEMPLATE_PARAMS::pfx_vector (const pfx_vector < dimension_value_operations, dimensional_count, optional_type >& other_)
{
	if (&other_ != this)
	{
		m_dim = other_.m_dim;
	}
}
VERCOTOR_TEMPLATE_DEFS
pfx_vector VERCOTOR_TEMPLATE_PARAMS::~pfx_vector()
{
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE pfx_usize_t	pfx_vector VERCOTOR_TEMPLATE_PARAMS::get_dimensional_count () const
{
	return dimensional_count;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE const DIM_VALUE_TYPE&	pfx_vector VERCOTOR_TEMPLATE_PARAMS::get (pfx_uindex_t dimensional) const
{
	if (dimensional < dimensional_count)
	{
		return m_dim.m_value[dimensional];
	}
	else
	{
		return pfx_vector VERCOTOR_TEMPLATE_PARAMS::default_dimension_value ();
	}
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE DIM_VALUE_TYPE&	pfx_vector VERCOTOR_TEMPLATE_PARAMS::
	reference (pfx_uindex_t dimensional)
{
	if (dimensional < dimensional_count)
	{
		return m_dim.m_value[dimensional];
	}
	else
	{
		return pfx_vector VERCOTOR_TEMPLATE_PARAMS::default_dimension_value ();
	}
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE void	pfx_vector VERCOTOR_TEMPLATE_PARAMS::set_all (dimension_value_t dim_set)
{
	for (pfx_uindex_t i=0; i<dimensional_count; ++i)
	{
		m_dim.m_value[i] = dim_set;
	}
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE pfx_vector VERCOTOR_TEMPLATE_PARAMS & pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
	sets(const dimension_value_t* dim_ptr,
	pfx_usize_t dim_count)
{
	pfx_vector VERCOTOR_TEMPLATE_PARAMS ::sets (&m_dim,dim_ptr,dim_count);
	return *this;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE pfx_vector VERCOTOR_TEMPLATE_PARAMS& pfx_vector VERCOTOR_TEMPLATE_PARAMS::
normalize_repalce ()
{
	pfx_vector VERCOTOR_TEMPLATE_PARAMS::normalize_replace (m_dim.m_value);
	return *this;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE pfx_boolean_t pfx_vector VERCOTOR_TEMPLATE_PARAMS::
	equals (const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& other_, 
	pfx_u32_t delta)
{
	return pfx_vector VERCOTOR_TEMPLATE_PARAMS::equals (m_dim, other_,delta);
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE DIM_VALUE_TYPE pfx_vector VERCOTOR_TEMPLATE_PARAMS::cacluate_vector_size () const
{
	return pfx_vector VERCOTOR_TEMPLATE_PARAMS::cacluate_vector_size (m_dim);
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE DIM_VALUE_TYPE pfx_vector VERCOTOR_TEMPLATE_PARAMS::cacluate_vector_size_square () const
{
	return pfx_vector VERCOTOR_TEMPLATE_PARAMS::cacluate_vector_size_square (m_dim);
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE DIM_VALUE_TYPE pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
	dot (const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& other_)
{
	return pfx_vector VERCOTOR_TEMPLATE_PARAMS::dot (m_dim);
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE pfx_vector VERCOTOR_TEMPLATE_PARAMS& pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
cross_replace (const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& other_)
{
	pfx_vector VERCOTOR_TEMPLATE_PARAMS::cross_replace (m_dim,other_);
	return *this;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE pfx_vector VERCOTOR_TEMPLATE_PARAMS& pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
add_replace (const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& a)
{
	pfx_vector VERCOTOR_TEMPLATE_PARAMS::add_replace (m_dim,a);
	return *this;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE pfx_vector VERCOTOR_TEMPLATE_PARAMS& pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
	sub_replace (const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& a)
{
	pfx_vector VERCOTOR_TEMPLATE_PARAMS::sub_replace (m_dim,a);
	return *this;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE pfx_vector VERCOTOR_TEMPLATE_PARAMS & pfx_vector VERCOTOR_TEMPLATE_PARAMS ::mul_replace 
	(DIM_VALUE_TYPE b)
{
	pfx_vector VERCOTOR_TEMPLATE_PARAMS::mul_replace (m_dim,b);
	return *this;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE pfx_vector VERCOTOR_TEMPLATE_PARAMS & pfx_vector VERCOTOR_TEMPLATE_PARAMS ::div_replace 
	(DIM_VALUE_TYPE b)
{
	pfx_vector VERCOTOR_TEMPLATE_PARAMS::div_replace (m_dim,b);
	return *this;
}

VERCOTOR_TEMPLATE_DEFS
st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
sets(st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec, 
	const DIM_VALUE_TYPE* dim_ptr,
	pfx_usize_t dim_count)
{
	if (dim_count > dimensional_count)
	{
		dim_count = dimensional_count;
	}
	for (pfx_uindex_t i=0;i<dim_count;++i)
	{
		vec.m_value[i] = dim_ptr[i];
	}
	return vec;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE DIM_VALUE_TYPE& pfx_vector VERCOTOR_TEMPLATE_PARAMS ::default_dimension_value ()
{
	static DIM_VALUE_TYPE defualt_dim_val;
	return defualt_dim_val;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE pfx_boolean_t pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
	check_default_dimension_value (const DIM_VALUE_TYPE& value_)
{
	DIM_VALUE_TYPE& defualt_val = default_dimension_value();
	return (pfx_boolean_t)((bool)(&defualt_val == &value_));
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE DIM_VALUE_TYPE pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
cacluate_vector_size  (const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec)
{
	return dimension_value_operations::sqrt
		(pfx_vector VERCOTOR_TEMPLATE_PARAMS ::cacluate_vector_size_square (vec));
}
VERCOTOR_TEMPLATE_DEFS
PFX_INLINE DIM_VALUE_TYPE pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
cacluate_vector_size_square (const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec)
{
	DIM_VALUE_TYPE return_val;
	return_val = dimension_value_operations::mul (vec.m_value[0],vec.m_value[0]);
	for (pfx_usize_t i=1;i<dimensional_count;++i)
	{
		DIM_VALUE_TYPE temp;
		temp = dimension_value_operations::mul (vec.m_value[i],vec.m_value[i]);
		dimension_value_operations::add_replace(return_val,temp); 
	}
	return return_val;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE DIM_VALUE_TYPE pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
dot (const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& a,
const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& b)
{
	DIM_VALUE_TYPE return_val;
	return_val = dimension_value_operations::mul (a.m_value[0],b.m_value[0]);

	for (pfx_usize_t i=1;i<dimensional_count;++i)
	{
		DIM_VALUE_TYPE temp;
		temp = dimension_value_operations::mul (a.m_value[i],b.m_value[i]);
		dimension_value_operations::add_replace(return_val,temp); 
	}

	return return_val;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE pfx_boolean_t pfx_vector VERCOTOR_TEMPLATE_PARAMS ::equals 
	(const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_a,
		const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_b, 
		pfx_u32_t delta)
{
	pfx_boolean_t result_ = PFX_BOOL_FALSE;
	for (pfx_uindex_t i=0; i<dimensional_count; ++i)
	{
		result_ = dimension_value_operations::equals(vec_a.m_value[i],vec_b.m_value[i],delta);
		if (!result_)
		{
			break;
		}
	}
	return result_;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE st_pfx_vector < DIM_VALUE_TYPE, dimensional_count > pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
normalize (st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& to_normalize)
{
	st_pfx_vector < DIM_VALUE_TYPE, dimensional_count > retn_vec = to_normalize;
	pfx_vector VERCOTOR_TEMPLATE_PARAMS ::normalize_repalce(retn);
	return retn_vec;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
normalize_replace (st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& to_normalize)
{
	DIM_VALUE_TYPE vec_size = pfx_vector VERCOTOR_TEMPLATE_PARAMS ::cacluate_vector_size (to_normalize);
	return pfx_vector VERCOTOR_TEMPLATE_PARAMS ::div_replace (to_normalize,vec_size);
}
//
VERCOTOR_TEMPLATE_DEFS
PFX_INLINE st_pfx_vector < DIM_VALUE_TYPE, dimensional_count > pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
cross (const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_a,
	const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_b)
{
	
	typedef pfx_vector VERCOTOR_TEMPLATE_PARAMS vec_t;

	if (3 <= dimensional_count)
	{
		st_pfx_vector < DIM_VALUE_TYPE, dimensional_count > res_vec;
		((st_pfx_vector <typename vec_t::dimension_value_t, 3>*)&res_vec)[0]
		= cross_vec3_unsafe < vec_t, optional_type > (
			(const st_pfx_vector < vec_t::dimension_value_t, 3>*)&vec_a,
			(const st_pfx_vector < vec_t::dimension_value_t, 3>*)&vec_b);

		return res_vec;
	}
	else
	{
		return vec_a;
	}
}
//template < class dimension_value_operations,  , const pfx_enum_int_t optional_type >
template <>
PFX_INLINE st_pfx_vector < float, 3 > pfx_vector < dimension_value_operations < float >, 3, 0 > ::
	cross (const st_pfx_vector < float, 3 >& vec_a,
	const st_pfx_vector < float, 3 >& vec_b)
{
	typedef pfx_vector < dimension_value_operations < float >, 3, 0 > vec_t;
	return cross_vec3_unsafe < vec_t,0  > (&vec_a,&vec_b);
}

template <>
PFX_INLINE st_pfx_vector < int, 3 > pfx_vector <dimension_value_operations < int >, 3, 0 > ::
	cross (const st_pfx_vector < int, 3 >& vec_a,
	const st_pfx_vector < int, 3 >& vec_b)
{
	typedef pfx_vector < dimension_value_operations < int >, 3, 0 > vec_t;
	return cross_vec3_unsafe < vec_t,0  > (&vec_a,&vec_b);
}

template <>
PFX_INLINE st_pfx_vector < double, 3 > pfx_vector <dimension_value_operations < double >, 3, 0 > ::
	cross (const st_pfx_vector < double, 3 >& vec_a,
	const st_pfx_vector < double, 3 >& vec_b)
{
	typedef pfx_vector < dimension_value_operations < double >, 3, 0 > vec_t;
	return cross_vec3_unsafe < vec_t,0  > (&vec_a,&vec_b);
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
	cross_replace (st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_a,
	const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_b)
{
	vec_a = pfx_vector VERCOTOR_TEMPLATE_PARAMS ::cross (vec_a,vec_b);
	return vec_a;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE st_pfx_vector < DIM_VALUE_TYPE, dimensional_count > pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
	add(const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_a, 
			const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_b)
{
	st_pfx_vector < DIM_VALUE_TYPE, dimensional_count > res_vec = vec_a;
	pfx_vector VERCOTOR_TEMPLATE_PARAMS ::add_replace (vec_a,vec_b);
	return res_vec;
}

VERCOTOR_TEMPLATE_DEFS
PFX_INLINE st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
add_replace (st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_a, 
const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_b)
{
	for (pfx_uindex_t i=0; i<dimensional_count; ++i)
	{
		dimension_value_operations::add_replace (vec_a.m_value[i],vec_b.m_value[i]);
	}
	return vec_a;
}

VERCOTOR_TEMPLATE_DEFS
	PFX_INLINE st_pfx_vector < DIM_VALUE_TYPE, dimensional_count > pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
	sub(const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_a, 
	const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_b)
{
	st_pfx_vector < DIM_VALUE_TYPE, dimensional_count > res_vec = vec_a;
	pfx_vector VERCOTOR_TEMPLATE_PARAMS ::sub_replace (vec_a,vec_b);
	return res_vec;
}

VERCOTOR_TEMPLATE_DEFS
	PFX_INLINE st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
	sub_replace (st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_a, 
	const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_b)
{
	for (pfx_uindex_t i=0; i<dimensional_count; ++i)
	{
		dimension_value_operations::sub_replace (vec_a.m_value[i],vec_b.m_value[i]);
	}
	return vec_a;
}

VERCOTOR_TEMPLATE_DEFS
	PFX_INLINE st_pfx_vector < DIM_VALUE_TYPE, dimensional_count > pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
	mul(const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_a, 
	DIM_VALUE_TYPE val_b)
{
	st_pfx_vector < DIM_VALUE_TYPE, dimensional_count > res_vec = vec_a;
	pfx_vector VERCOTOR_TEMPLATE_PARAMS ::mul_replace (vec_a,val_b);
	return res_vec;
}

VERCOTOR_TEMPLATE_DEFS
	PFX_INLINE st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
	mul_replace (st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_a, 
	DIM_VALUE_TYPE val_b)
{
	for (pfx_uindex_t i=0; i<dimensional_count; ++i)
	{
		dimension_value_operations::mul_replace (vec_a.m_value[i],vec_b);
	}
	return vec_a;
}

VERCOTOR_TEMPLATE_DEFS
	PFX_INLINE st_pfx_vector < DIM_VALUE_TYPE, dimensional_count > pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
	div(const st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_a, 
	DIM_VALUE_TYPE val_b)
{
	st_pfx_vector < DIM_VALUE_TYPE, dimensional_count > res_vec = vec_a;
	pfx_vector VERCOTOR_TEMPLATE_PARAMS ::div_replace (vec_a,val_b);
	return res_vec;
}

VERCOTOR_TEMPLATE_DEFS
	PFX_INLINE st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& pfx_vector VERCOTOR_TEMPLATE_PARAMS ::
	div_replace (st_pfx_vector < DIM_VALUE_TYPE, dimensional_count >& vec_a, 
	DIM_VALUE_TYPE val_b)
{
	for (pfx_uindex_t i=0; i<dimensional_count; ++i)
	{
		dimension_value_operations::div_replace (vec_a.m_value[i],vec_b);
	}
	return vec_a;
}



PECKER_END

#endif			//PFX_VECTOR_CODES_H_
