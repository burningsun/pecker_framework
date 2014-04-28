/*
 * pfx_vector.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_VECTOR_H_
#define		PFX_VECTOR_H_

#include "../pfx_defines.h"

PECKER_BEGIN

typedef enum enumDIMENSION_NAME
{
	DIMENSION_X = 0,
	DIMENSION_Y,
	DIMENSION_Z,
	DIMENSION_W,

	DIMENSION_OTHER
}PFX_DIMENSION_NAME_t;

typedef enum enumFLOAT_PRECISION_QUALIFER
{
	LOW_PRECISION_QUALIFER = 0,
	MID_PRECISION_QUALIFER,
	HIGH_PRECISION_QUALIFER,
	VARY_HIGH_PRECISION_QUALIFER,

	PFX_FLOAT_PRECISION_QUALIFER_COUNT
}PFX_FLOAT_PRECISION_QUALIFER_t;

#define LOW_PRECISION_QUALIFER_VAL (20)
#define MID_PRECISION_QUALIFER_VAL (10)
#define HIGH_PRECISION_QUALIFER_VAL (5)
#define VARY_HIGH_PRECISION_QUALIFER_VAL (1)


PFX_INLINE pfx_u32_t FLOAT_PRECISION_QUALIFIER (PFX_FLOAT_PRECISION_QUALIFER_t PQ)
{
	static const pfx_u32_t precision_qualifer_table [] = 
	{LOW_PRECISION_QUALIFER_VAL,MID_PRECISION_QUALIFER_VAL,HIGH_PRECISION_QUALIFER_VAL,VARY_HIGH_PRECISION_QUALIFER_VAL,0};
	return precision_qualifer_table[PQ];
};

template < class dimension_value >
struct PFX_DATA_TEMPALE_API dimension_value_operations
{
	typedef dimension_value dimension_value_t;

	static PFX_INLINE pfx_boolean_t equals (dimension_value X, dimension_value Y, pfx_u32_t delta);

	static PFX_INLINE dimension_value abs (dimension_value val);

	static PFX_INLINE dimension_value add (dimension_value a,dimension_value b);
	static PFX_INLINE dimension_value& add_replace (dimension_value& a,dimension_value b);

	static PFX_INLINE dimension_value sub (dimension_value a,dimension_value b);
	static PFX_INLINE dimension_value& sub_replace (dimension_value& a,dimension_value b);


	static PFX_INLINE dimension_value mul (dimension_value a,dimension_value b);
	static PFX_INLINE dimension_value& mul_replace (dimension_value& a,dimension_value b);

	static PFX_INLINE dimension_value div (dimension_value a,dimension_value b);
	static PFX_INLINE dimension_value& div_replace (dimension_value& a,dimension_value b);

	static PFX_INLINE dimension_value sin (dimension_value rad);
	static PFX_INLINE dimension_value cos (dimension_value rad);
	static PFX_INLINE dimension_value tan (dimension_value rad);
	static PFX_INLINE dimension_value acos (dimension_value rad);


	static PFX_INLINE void sincos (dimension_value rad,
		dimension_value& sin_val,
		dimension_value &cos_val);

	static PFX_INLINE dimension_value sqrt (dimension_value val);
};

template < class dimension_value, const pfx_usize_t dimension_count >
struct st_pfx_vector
{
	typedef typename dimension_value dimension_value_t;

	dimension_value m_value[ (!dimension_count?1:dimension_count) ];
};

template < class vector_type,
	const pfx_enum_int_t optional_type >
	PFX_INLINE st_pfx_vector <typename vector_type::dimension_value_t, 3>
	cross_vec3_unsafe (const st_pfx_vector <typename vector_type::dimension_value_t, 3>* vec_a,
	const st_pfx_vector <typename vector_type::dimension_value_t, 3>* vec_b);

template < class vector_type,
	const pfx_enum_int_t optional_type >
PFX_INLINE st_pfx_vector <typename vector_type::dimension_value_t, 3>
cross_vec3 (const st_pfx_vector <typename vector_type::dimension_value_t, 3>& vec3,
const vector_type* vec_ptr);

template < class vector_type,
	const pfx_enum_int_t optional_type >
PFX_INLINE st_pfx_vector <typename vector_type::dimension_value_t, 3>
	cross_vec (const vector_type* vec_a, const vector_type* vec_b);

template < class vector_type,
	const pfx_enum_int_t optional_type >
PFX_INLINE vector_type*
	cross_vec_replace (vector_type* vec_a, const vector_type* vec_b);

template < class dimension_value_operations, 
					const pfx_usize_t			dimensional_count,
					const pfx_enum_int_t optional_type = 0>
class PFX_DATA_TEMPALE_API pfx_vector
{
public:
	typedef typename dimension_value_operations::dimension_value_t	dimension_value_t;
	typedef typename dimension_value_operations											dimension_value_operations_t;
public:
	st_pfx_vector < dimension_value_t, dimensional_count > m_dim;
public:
	pfx_vector ();
	pfx_vector (dimension_value_t dim_set);
	pfx_vector (const st_pfx_vector < dimension_value_t, dimensional_count >& dim);
	pfx_vector (const pfx_vector < dimension_value_operations, dimensional_count, optional_type >& other_);
	~pfx_vector();
public:	
	PFX_INLINE pfx_usize_t								get_dimensional_count () const;
	PFX_INLINE const dimension_value_t&	get (pfx_uindex_t dimensional) const;
	PFX_INLINE dimension_value_t&				reference (pfx_uindex_t dimensional);
	PFX_INLINE void											set_all (dimension_value_t dim_set);
	PFX_INLINE pfx_vector < dimension_value_operations, dimensional_count, optional_type >& sets(const dimension_value_t* dim_ptr,
			pfx_usize_t dim_count);

	PFX_INLINE pfx_vector < dimension_value_operations, dimensional_count, optional_type >& normalize_repalce ();

	PFX_INLINE pfx_boolean_t equals (const st_pfx_vector < dimension_value_t, dimensional_count >& other_, 
		pfx_u32_t delta = MID_PRECISION_QUALIFER_VAL);

	PFX_INLINE dimension_value_t cacluate_vector_size () const;
	PFX_INLINE dimension_value_t cacluate_vector_size_square () const;
	PFX_INLINE dimension_value_t dot (const st_pfx_vector < dimension_value_t, dimensional_count >& other_);
	
	PFX_INLINE pfx_vector < dimension_value_operations, dimensional_count, optional_type >& cross_replace 
		(const st_pfx_vector < dimension_value_t, dimensional_count >& other_);

	PFX_INLINE pfx_vector < dimension_value_operations, dimensional_count, optional_type >& add_replace 
		(const st_pfx_vector < dimension_value_t, dimensional_count >& a);

	PFX_INLINE pfx_vector < dimension_value_operations, dimensional_count, optional_type >& sub_replace 
		(const st_pfx_vector < dimension_value_t, dimensional_count >& a);

	PFX_INLINE pfx_vector < dimension_value_operations, dimensional_count, optional_type >& mul_replace 
		(dimension_value_t b);

	PFX_INLINE pfx_vector < dimension_value_operations, dimensional_count, optional_type >& div_replace 
		(dimension_value_t b);


public:
	static st_pfx_vector < dimension_value_t, dimensional_count >& sets(st_pfx_vector < dimension_value_t, dimensional_count >& vec, 
		const dimension_value_t* dim_ptr,
		pfx_usize_t dim_count);

	static PFX_INLINE dimension_value_t& default_dimension_value ();

	static PFX_INLINE pfx_boolean_t check_default_dimension_value (const dimension_value_t& value_);

	static PFX_INLINE dimension_value_t cacluate_vector_size  (const st_pfx_vector < dimension_value_t, dimensional_count >& vec);

	static PFX_INLINE dimension_value_t cacluate_vector_size_square (const st_pfx_vector < dimension_value_t, dimensional_count >& vec);

	static PFX_INLINE dimension_value_t dot (const st_pfx_vector < dimension_value_t, dimensional_count >& a,const st_pfx_vector < dimension_value_t, dimensional_count >& b);

	PFX_INLINE pfx_boolean_t equals (const st_pfx_vector < dimension_value_t, dimensional_count >& vec_a,
		const st_pfx_vector < dimension_value_t, dimensional_count >& vec_b, 
		pfx_u32_t delta = MID_PRECISION_QUALIFER_VAL);

	static PFX_INLINE st_pfx_vector < dimension_value_t, dimensional_count > normalize
		(st_pfx_vector < dimension_value_t, dimensional_count >& to_normalize);

	static PFX_INLINE st_pfx_vector < dimension_value_t, dimensional_count >& normalize_replace 
		(st_pfx_vector < dimension_value_t, dimensional_count >& to_normalize);

	static PFX_INLINE st_pfx_vector < dimension_value_t, dimensional_count > cross
		(const st_pfx_vector < dimension_value_t, dimensional_count >& vec_a,
		const st_pfx_vector < dimension_value_t, dimensional_count >& vec_b);

	static PFX_INLINE st_pfx_vector < dimension_value_t, dimensional_count >& cross_replace
		(st_pfx_vector < dimension_value_t, dimensional_count >& vec_a,
		const st_pfx_vector < dimension_value_t, dimensional_count >& vec_b);

	static PFX_INLINE st_pfx_vector < dimension_value_t, dimensional_count > add
		(const st_pfx_vector < dimension_value_t, dimensional_count >& a, const st_pfx_vector < dimension_value_t, dimensional_count >& b);

	static PFX_INLINE st_pfx_vector < dimension_value_t, dimensional_count >& add_replace
		(st_pfx_vector < dimension_value_t, dimensional_count >& a, const st_pfx_vector < dimension_value_t, dimensional_count >& b);

	static PFX_INLINE st_pfx_vector < dimension_value_t, dimensional_count > sub
		(const st_pfx_vector < dimension_value_t, dimensional_count >&a, const st_pfx_vector < dimension_value_t, dimensional_count >& b);

	static PFX_INLINE st_pfx_vector < dimension_value_t, dimensional_count >& sub_replace 
		(st_pfx_vector < dimension_value_t, dimensional_count >& a, const st_pfx_vector < dimension_value_t, dimensional_count >& b);

	static PFX_INLINE st_pfx_vector < dimension_value_t, dimensional_count > mul
		(const st_pfx_vector < dimension_value_t, dimensional_count >& a, dimension_value_t b);

	static PFX_INLINE st_pfx_vector < dimension_value_t, dimensional_count >& mul_replace 
		(st_pfx_vector < dimension_value_t, dimensional_count >& a, dimension_value_t b);

	static PFX_INLINE st_pfx_vector < dimension_value_t, dimensional_count > div
		(const st_pfx_vector < dimension_value_t, dimensional_count >& a,dimension_value_t b);

	static PFX_INLINE st_pfx_vector < dimension_value_t, dimensional_count >& div_replace
		(st_pfx_vector < dimension_value_t, dimensional_count >& a,dimension_value_t b);
};



PECKER_END

#endif			//PFX_VECTOR_H_
