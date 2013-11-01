/*
 * pfx_vector4.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_VECTOR4_H_
#define		PFX_VECTOR4_H_

#include "../pfx_defines.h"
#include "pfx_fixed_point.h"
#include "pfx_simd_optimization.h"

PFX_C_EXTERN_BEGIN

typedef struct st_pfx_vector_2f pfx_vector2f_t;
typedef struct st_pfx_vector_3f pfx_vector3f_t;
typedef struct st_pfx_vector_4f pfx_vector4f_t;

typedef struct st_pfx_vector_2i pfx_vector2i_t;
typedef struct st_pfx_vector_3i pfx_vector3i_t;
typedef struct st_pfx_vector_4i pfx_vector4i_t;

typedef union un_pfx_vector_2 pfx_vector2_t;
typedef union un_pfx_vector_3 pfx_vector3_t;
typedef union un_pfx_vector_4 pfx_vector4_t;

struct st_pfx_vector_2f
{
	VEC_FLOAT	x;
	VEC_FLOAT	y;
};

struct st_pfx_vector_3f
{
	VEC_FLOAT	x;
	VEC_FLOAT	y;
	VEC_FLOAT	z;
};

struct st_pfx_vector_4f
{
	VEC_FLOAT	x;
	VEC_FLOAT	y;
	VEC_FLOAT	z;
	VEC_FLOAT	w;
};

struct st_pfx_vector_2i
{
	pfx_sint_t	x;
	pfx_sint_t	y;
};

struct st_pfx_vector_3i
{
	pfx_sint_t	x;
	pfx_sint_t	y;
	pfx_sint_t	z;
};

struct st_pfx_vector_4i
{
	pfx_sint_t	x;
	pfx_sint_t	y;
	pfx_sint_t	z;
	pfx_sint_t	w;
};

union un_pfx_vector_2
{
	VEC_FLOAT				m_vec_f[2];
	pfx_vector2f_t		m_vec;
	pfx_vector2i_t		m_vec_i;
};

union un_pfx_vector_3
{
	VEC_FLOAT				m_vec_f[3];
	pfx_vector3f_t		m_vec;
	pfx_vector3i_t		m_vec_i;
};

union un_pfx_vector_4
{
	VEC_FLOAT				m_vec_f[4];
	pfx_vector4f_t		m_vec;
	pfx_vector4i_t		m_vec_i;
};

typedef enum enumVECTOR_INDEX
{
	VEC_INDEX_X = 0,
	VEC_INDEX_Y,
	VEC_INDEX_Z,
	VEC_INDEX_W,

	VECTOR_INDEX_COUNT
}VECTOR_INDEX_t;

#define VECTOR_DATA(VEC,INDEX) ((VEC).m_vec_f[(INDEX)])
#define PVECTOR_DATA(VEC,INDEX) ((VEC)->m_vec_f[(INDEX)])
#define VECTOR4_DATA_SUM(VEC) (VECTOR_DATA(VEC,0)+VECTOR_DATA(VEC,1)+VECTOR_DATA(VEC,2)+VECTOR_DATA(VEC,3))
#define PVECTOR4_DATA_SUM(VEC) (PVECTOR_DATA(VEC,0)+PVECTOR_DATA(VEC,1)+PVECTOR_DATA(VEC,2)+PVECTOR_DATA(VEC,3))

PFX_INLINE void init_vector2_default_unsafe_std (pfx_vector2_t* PARAM_INOUT vec2)
{
	memset (vec2,0,sizeof (pfx_vector2_t));
}

PFX_INLINE void init_vector2_by_float_unsafe_std (pfx_vector2_t* PARAM_INOUT vec,
	VEC_FLOAT fval)
{
	vec->m_vec.x = fval;
	vec->m_vec.y = fval;
}

PFX_INLINE void init_vector2_unsafe_std (pfx_vector2_t* PARAM_INOUT vec2,
	VEC_FLOAT fx,VEC_FLOAT fy)
{
	vec2->m_vec.x = fx;
	vec2->m_vec.y = fy;
}

PFX_INLINE void init_vector2_by_vector2_unsafe_std (pfx_vector2_t* PARAM_INOUT vec2,
	const pfx_vector2_t* pvec)
{
	memcpy (vec2,pvec,sizeof(pfx_vector2_t));
}

PFX_INLINE pfx_vector2_t* vector2_add_ref_unsafe_std (pfx_vector2_t* PARAM_INOUT vec2,
	const pfx_vector2_t* PARAM_IN vec2_)
{
	vec2->m_vec.x += vec2_->m_vec.x;
	vec2->m_vec.y += vec2_->m_vec.y;

	return vec2;
}

PFX_INLINE pfx_vector2_t* vector2_sub_ref_unsafe_std (pfx_vector2_t* PARAM_INOUT vec2,
	const pfx_vector2_t* PARAM_IN vec2_)
{
	vec2->m_vec.x -= vec2_->m_vec.x;
	vec2->m_vec.y -= vec2_->m_vec.y;

	return vec2;
}

PFX_INLINE pfx_vector2_t vector2_add_unsafe_std (const pfx_vector2_t* PARAM_IN vec2,
	const pfx_vector2_t* PARAM_IN vec2_)
{
	pfx_vector2_t result_vec;

	result_vec.m_vec.x = vec2->m_vec.x + vec2_->m_vec.x;
	result_vec.m_vec.y = vec2->m_vec.y + vec2_->m_vec.y;

	return result_vec;
}

PFX_INLINE pfx_vector2_t vector2_sub_unsafe_std (const pfx_vector2_t* PARAM_IN vec2,
	const pfx_vector2_t* PARAM_IN vec2_)
{
	pfx_vector2_t result_vec;

	result_vec.m_vec.x = vec2->m_vec.x - vec2_->m_vec.x;
	result_vec.m_vec.y = vec2->m_vec.y - vec2_->m_vec.y;

	return result_vec;
}

PFX_INLINE pfx_vector2_t* vector2_mul_float_ref_unsafe_std (pfx_vector2_t* PARAM_INOUT vec2,
	VEC_FLOAT fval)
{
	vec2->m_vec.x = VEC_FLOAT_MUL (vec2->m_vec.x,fval);
	vec2->m_vec.y = VEC_FLOAT_MUL (vec2->m_vec.y,fval);

	return vec2;
}

PFX_INLINE pfx_vector2_t* vector2_div_float_ref_unsafe_std (pfx_vector2_t* PARAM_INOUT vec2,
	VEC_FLOAT fval)
{
	vec2->m_vec.x = VEC_FLOAT_DIV (vec2->m_vec.x,fval);
	vec2->m_vec.y = VEC_FLOAT_DIV (vec2->m_vec.y,fval);

	return vec2;
}

PFX_INLINE pfx_vector2_t vector2_mul_float_unsafe_std (const pfx_vector2_t* PARAM_IN vec2,
	VEC_FLOAT fval)
{
	pfx_vector2_t result_vec;

	result_vec.m_vec.x = VEC_FLOAT_MUL (vec2->m_vec.x,fval);
	result_vec.m_vec.y = VEC_FLOAT_MUL (vec2->m_vec.y,fval);

	return result_vec;
}

PFX_INLINE pfx_vector2_t vector2_div_float_unsafe_std (const pfx_vector2_t* PARAM_IN vec2,
	VEC_FLOAT fval)
{
	pfx_vector2_t result_vec;

	result_vec.m_vec.x = VEC_FLOAT_DIV (vec2->m_vec.x,fval);
	result_vec.m_vec.y = VEC_FLOAT_DIV (vec2->m_vec.y,fval);

	return result_vec;
}

PFX_INLINE pfx_vector2_t* vector2_mul_vector2_ref_unsafe_std (pfx_vector2_t* PARAM_INOUT vec2,
	const pfx_vector2_t* PARAM_IN vec2_val)
{
	vec2->m_vec.x = VEC_FLOAT_MUL (vec2->m_vec.x,vec2_val->m_vec.x);
	vec2->m_vec.y = VEC_FLOAT_MUL (vec2->m_vec.y,vec2_val->m_vec.y);

	return vec2;
}

PFX_INLINE pfx_vector2_t* vector2_div_vector2_ref_unsafe_std (pfx_vector2_t* PARAM_INOUT vec2,
	const pfx_vector2_t* PARAM_IN vec2_val)
{
	vec2->m_vec.x = VEC_FLOAT_DIV (vec2->m_vec.x,vec2_val->m_vec.x);
	vec2->m_vec.y = VEC_FLOAT_DIV (vec2->m_vec.y,vec2_val->m_vec.y);

	return vec2;
}

PFX_INLINE pfx_vector2_t vector2_mul_vector2_unsafe_std (const pfx_vector2_t* PARAM_IN vec2,
	const pfx_vector2_t* PARAM_IN vec2_val)
{
	pfx_vector2_t vec_result;
	vec_result.m_vec.x = VEC_FLOAT_MUL (vec2->m_vec.x,vec2_val->m_vec.x);
	vec_result.m_vec.y = VEC_FLOAT_MUL (vec2->m_vec.y,vec2_val->m_vec.y);
	return vec_result;
}

PFX_INLINE pfx_vector2_t vector2_div_vector2_unsafe_std (pfx_vector2_t* PARAM_INOUT vec2,
	const pfx_vector2_t* PARAM_IN vec2_val)
{
	pfx_vector2_t vec_result;
	vec_result.m_vec.x = VEC_FLOAT_DIV (vec2->m_vec.x,vec2_val->m_vec.x);
	vec_result.m_vec.y = VEC_FLOAT_DIV (vec2->m_vec.y,vec2_val->m_vec.y);
	return vec_result;
}

PFX_INLINE pfx_bool_t vector2_equals_unsafe_std (const pfx_vector2_t* PARAM_IN vec_a,
	const pfx_vector2_t* PARAM_IN vec_b)
{
	//return (pfx_bool_t)((vec_a->m_vec.x == vec_b->m_vec.x) && 
	//	(vec_b->m_vec.y == vec_b->m_vec.y));
	return (pfx_bool_t)(VEC_FLOAT_EQUALS (vec_a->m_vec.x,vec_b->m_vec.x) && 
		VEC_FLOAT_EQUALS (vec_a->m_vec.y,vec_b->m_vec.y));
}

PFX_INLINE VEC_FLOAT vector2_square_unsafe_std (const pfx_vector2_t* PARAM_IN vec_x)
{
	return VEC_FLOAT_MUL (vec_x->m_vec.x,vec_x->m_vec.x) + 
		VEC_FLOAT_MUL (vec_x->m_vec.y,vec_x->m_vec.y);
}

PFX_INLINE VEC_FLOAT vector2_length_std (const pfx_vector2_t* PARAM_IN vec_)
{
	return (VEC_FLOAT) pfx_f2vt (sqrt
		(pfx_vt2f (vec_->m_vec.x) * pfx_vt2f (vec_->m_vec.x) + 
		pfx_vt2f (vec_->m_vec.y) * pfx_vt2f(vec_->m_vec.y)) );
}

PFX_INLINE pfx_vector2_t* vector2_normalize_ref_unsafe_std (pfx_vector2_t* PARAM_INOUT vec)
{
	return vector2_div_float_ref_unsafe_std (vec,vector2_length_std (vec));
}

PFX_INLINE pfx_vector2_t vector2_normalize_unsafe_std (pfx_vector2_t* PARAM_INOUT vec)
{
	return vector2_div_float_unsafe_std (vec,vector2_length_std (vec));
}

PFX_INLINE pfx_vector2_t* vector2_rotated_90_unsafe_std (const pfx_vector2_t* PARAM_IN vec_src,
	pfx_vector2_t* PARAM_INOUT result_vec)
{
	 init_vector2_unsafe_std (result_vec,-vec_src->m_vec.y,vec_src->m_vec.x);
	 return result_vec;
}

PFX_INLINE VEC_FLOAT vector2_dot_unsafe_std (const pfx_vector2_t* PARAM_IN vec_a,
	const pfx_vector2_t* vec_b)
{
	return VEC_FLOAT_MUL (vec_a->m_vec.x,vec_b->m_vec.x) +
		VEC_FLOAT_MUL (vec_a->m_vec.y,vec_b->m_vec.y);
}

//////////////////////////////////////////////////////////////////////////
PFX_INLINE void init_vector3_default_unsafe_std (pfx_vector3_t* PARAM_INOUT vec)
{
	memset (vec,0,sizeof (pfx_vector3_t));
}
PFX_INLINE void init_vector3_by_float_unsafe_std (pfx_vector3_t* PARAM_INOUT vec,
	VEC_FLOAT fval)
{
	vec->m_vec.x = fval;
	vec->m_vec.y = fval;
	vec->m_vec.z = fval;
}

PFX_INLINE void init_vector3_unsafe_std (pfx_vector3_t* PARAM_INOUT vec,
	VEC_FLOAT fx,VEC_FLOAT fy,VEC_FLOAT fz)
{
	vec->m_vec.x = fx;
	vec->m_vec.y = fy;
	vec->m_vec.z = fz;
}

PFX_INLINE void init_vector3_by_vector3_unsafe_std (pfx_vector3_t* PARAM_INOUT vec,
	const pfx_vector3_t* pvec)
{
	memcpy (vec,pvec,sizeof(pfx_vector3_t));
}

PFX_INLINE pfx_vector3_t* vector3_add_ref_unsafe_std (pfx_vector3_t* PARAM_INOUT vec,
	const pfx_vector3_t* PARAM_IN vec_)
{
	vec->m_vec.x += vec_->m_vec.x;
	vec->m_vec.y += vec_->m_vec.y;
	vec->m_vec.z += vec_->m_vec.z;
	return vec;
}

PFX_INLINE pfx_vector3_t* vector3_sub_ref_unsafe_std (pfx_vector3_t* PARAM_INOUT vec,
	const pfx_vector3_t* PARAM_IN vec_)
{
	vec->m_vec.x -= vec_->m_vec.x;
	vec->m_vec.y -= vec_->m_vec.y;
	vec->m_vec.z -= vec_->m_vec.z;

	return vec;
}

PFX_INLINE pfx_vector3_t vector3_add_unsafe_std (const pfx_vector3_t* PARAM_IN vec,
	const pfx_vector3_t* PARAM_IN vec_)
{
	pfx_vector3_t result_vec;
	result_vec.m_vec.x = vec->m_vec.x + vec_->m_vec.x;
	result_vec.m_vec.y = vec->m_vec.y + vec_->m_vec.y;
	result_vec.m_vec.z = vec->m_vec.z +  vec_->m_vec.z;
	return result_vec;
}

PFX_INLINE pfx_vector3_t vector3_sub_unsafe_std (const pfx_vector3_t* PARAM_IN vec,
	const pfx_vector3_t* PARAM_IN vec_)
{
	pfx_vector3_t result_vec;

	result_vec.m_vec.x = vec->m_vec.x - vec_->m_vec.x;
	result_vec.m_vec.y = vec->m_vec.y - vec_->m_vec.y;
	result_vec.m_vec.z = vec->m_vec.z - vec_->m_vec.z;

	return result_vec;
}

PFX_INLINE pfx_vector3_t* vector3_mul_float_ref_unsafe_std (pfx_vector3_t* PARAM_INOUT vec,
	VEC_FLOAT fval)
{
	vec->m_vec.x = VEC_FLOAT_MUL (vec->m_vec.x,fval);
	vec->m_vec.y = VEC_FLOAT_MUL (vec->m_vec.y,fval);
	vec->m_vec.z = VEC_FLOAT_MUL (vec->m_vec.z,fval);

	return vec;
}

PFX_INLINE pfx_vector3_t* vector3_div_float_ref_unsafe_std (pfx_vector3_t* PARAM_INOUT vec,
	VEC_FLOAT fval)
{
	vec->m_vec.x = VEC_FLOAT_DIV (vec->m_vec.x,fval);
	vec->m_vec.y = VEC_FLOAT_DIV (vec->m_vec.y,fval);
	vec->m_vec.z = VEC_FLOAT_DIV (vec->m_vec.z,fval);
	return vec;
}

PFX_INLINE pfx_vector3_t vector3_mul_float_unsafe_std (const pfx_vector3_t* PARAM_IN vec,
	VEC_FLOAT fval)
{
	pfx_vector3_t result_vec;

	result_vec.m_vec.x = VEC_FLOAT_MUL (vec->m_vec.x,fval);
	result_vec.m_vec.y = VEC_FLOAT_MUL (vec->m_vec.y,fval);
	result_vec.m_vec.z = VEC_FLOAT_MUL (vec->m_vec.z,fval);

	return result_vec;
}

PFX_INLINE pfx_vector3_t vector3_div_float_unsafe_std (const pfx_vector3_t* PARAM_IN vec,
	VEC_FLOAT fval)
{
	pfx_vector3_t result_vec;
	result_vec.m_vec.x = VEC_FLOAT_DIV (vec->m_vec.x,fval);
	result_vec.m_vec.y = VEC_FLOAT_DIV (vec->m_vec.y,fval);
	result_vec.m_vec.z = VEC_FLOAT_DIV (vec->m_vec.z,fval);
	return result_vec;
}


PFX_INLINE pfx_vector3_t* vector3_mul_vector3_ref_unsafe_std (pfx_vector3_t* PARAM_INOUT vec,
	const pfx_vector3_t* PARAM_IN vec_val)
{
	vec->m_vec.x = VEC_FLOAT_MUL (vec->m_vec.x,vec_val->m_vec.x);
	vec->m_vec.y = VEC_FLOAT_MUL (vec->m_vec.y,vec_val->m_vec.y);
	vec->m_vec.z = VEC_FLOAT_MUL (vec->m_vec.z,vec_val->m_vec.z);
	return vec;
}

PFX_INLINE pfx_vector3_t* vector3_div_vector3_ref_unsafe_std (pfx_vector3_t* PARAM_INOUT vec,
	const pfx_vector3_t* PARAM_IN vec_val)
{
	vec->m_vec.x = VEC_FLOAT_DIV (vec->m_vec.x,vec_val->m_vec.x);
	vec->m_vec.y = VEC_FLOAT_DIV (vec->m_vec.y,vec_val->m_vec.y);
	vec->m_vec.z = VEC_FLOAT_DIV (vec->m_vec.z,vec_val->m_vec.z);
	return vec;
}

PFX_INLINE pfx_vector3_t vector3_mul_vector3_unsafe_std (pfx_vector3_t* PARAM_INOUT vec,
	const pfx_vector3_t* PARAM_IN vec_val)
{
	pfx_vector3_t vec_result;
	
	vec_result.m_vec.x = VEC_FLOAT_MUL (vec->m_vec.x,vec_val->m_vec.x);
	vec_result.m_vec.y = VEC_FLOAT_MUL (vec->m_vec.y,vec_val->m_vec.y);
	vec_result.m_vec.z = VEC_FLOAT_MUL (vec->m_vec.z,vec_val->m_vec.z);

	return vec_result;
}

PFX_INLINE pfx_vector3_t vector3_div_vector3_unsafe_std (pfx_vector3_t* PARAM_INOUT vec,
	const pfx_vector3_t* PARAM_IN vec_val)
{
	pfx_vector3_t vec_result;

	vec_result.m_vec.x = VEC_FLOAT_DIV (vec->m_vec.x,vec_val->m_vec.x);
	vec_result.m_vec.y = VEC_FLOAT_DIV (vec->m_vec.y,vec_val->m_vec.y);
	vec_result.m_vec.z = VEC_FLOAT_DIV (vec->m_vec.z,vec_val->m_vec.z);

	return vec_result;
}

PFX_INLINE pfx_bool_t vector3_equals_unsafe_std (const pfx_vector3_t* PARAM_IN vec_a,
	const pfx_vector3_t* PARAM_IN vec_b)
{
	return (pfx_bool_t)(VEC_FLOAT_EQUALS (vec_a->m_vec.x,vec_b->m_vec.x) && 
		VEC_FLOAT_EQUALS (vec_a->m_vec.y,vec_b->m_vec.y) && 
		VEC_FLOAT_EQUALS (vec_a->m_vec.z,vec_b->m_vec.z));
}

PFX_INLINE VEC_FLOAT vector3_square_unsafe_std (const pfx_vector3_t* PARAM_IN vec)
{
	return VEC_FLOAT_MUL (vec->m_vec.x,vec->m_vec.x) + 
		VEC_FLOAT_MUL (vec->m_vec.y,vec->m_vec.y) +
		VEC_FLOAT_MUL (vec->m_vec.z,vec->m_vec.z);
}

PFX_INLINE VEC_FLOAT vector3_length_unsafe_std (const pfx_vector3_t* PARAM_IN vec_)
{
	return (VEC_FLOAT) pfx_f2vt (sqrt(pfx_vt2f (vec_->m_vec.x) * pfx_vt2f (vec_->m_vec.x) + 
		pfx_vt2f (vec_->m_vec.y) * pfx_vt2f(vec_->m_vec.y) +
		pfx_vt2f (vec_->m_vec.z) * pfx_vt2f(vec_->m_vec.z)) );
}

PFX_INLINE VEC_FLOAT vector3_dot_unsafe_std (const pfx_vector3_t* PARAM_IN vec_a,
	const pfx_vector3_t* vec_b)
{
	return VEC_FLOAT_MUL (vec_a->m_vec.x,vec_b->m_vec.x) +
		VEC_FLOAT_MUL (vec_a->m_vec.y,vec_b->m_vec.y) + 
		VEC_FLOAT_MUL (vec_a->m_vec.z,vec_b->m_vec.z);
}

PFX_INLINE pfx_vector3_t vector3_cross_unsafe_std (const pfx_vector3_t* PARAM_IN vec_a,
	const pfx_vector3_t* PARAM_IN vec_b)
{
	pfx_vector3_t result_vec;
	result_vec.m_vec.x = VEC_FLOAT_MUL (vec_a->m_vec.y,vec_b->m_vec.z) - 
		VEC_FLOAT_MUL (vec_a->m_vec.z,vec_b->m_vec.y);

	result_vec.m_vec.y = VEC_FLOAT_MUL (vec_a->m_vec.z,vec_b->m_vec.x) - 
		VEC_FLOAT_MUL (vec_a->m_vec.x,vec_b->m_vec.z);

	result_vec.m_vec.z = VEC_FLOAT_MUL (vec_a->m_vec.x,vec_b->m_vec.y) -
		VEC_FLOAT_MUL (vec_a->m_vec.y,vec_b->m_vec.x);
	return result_vec;
}

PFX_INLINE pfx_vector3_t* vector3_normalize_ref_unsafe_std (pfx_vector3_t* PARAM_INOUT vec)
{
#if defined(PFX_FIXED_POINT_ENABLE)
	// Scale vector by uniform value
	int n = PFX_ABS (vec->m_vec.x) + PFX_ABS (vec->m_vec.y) + PFX_ABS (vec->m_vec.z);
	vec->m_vec.x = VEC_FLOAT_DIV (vec->m_vec.x, n);
	vec->m_vec.y = VEC_FLOAT_DIV (vec->m_vec.y, n);
	vec->m_vec.z = VEC_FLOAT_DIV (vec->m_vec.z, n);

	// Calculate x2+y2+z2/sqrt(x2+y2+z2)
	int f = vector3_dot_unsafe_std (vec,vec);
	f = VEC_FLOAT_DIV (pfx_f2vt(1.0f), pfx_f2vt(sqrt(pfx_vt2f(f))));

	// Multiply vector components by f
	vec->m_vec.x = VEC_FLOAT_MUL (vec->m_vec.x, f);
	vec->m_vec.y = VEC_FLOAT_MUL (vec->m_vec.y, f);
	vec->m_vec.z = VEC_FLOAT_MUL (vec->m_vec.z, f);
#else
	VEC_FLOAT len = vector3_length_unsafe_std (vec);
	vec->m_vec.x =VEC_FLOAT_DIV (vec->m_vec.x,len);
	vec->m_vec.y =VEC_FLOAT_DIV (vec->m_vec.y,len);
	vec->m_vec.z =VEC_FLOAT_DIV (vec->m_vec.z,len);
#endif
	return vec;
}

PFX_INLINE pfx_vector3_t vector3_normalize_unsafe_std (pfx_vector3_t* PARAM_INOUT vec)
{
	pfx_vector3_t return_vec;
#if defined(PFX_FIXED_POINT_ENABLE)
	// Scale vector by uniform value
	int n = PFX_ABS (vec->m_vec.x) + PFX_ABS (vec->m_vec.y) + PFX_ABS (vec->m_vec.z);
	return_vec.m_vec.x = VEC_FLOAT_DIV (vec->m_vec.x, n);
	return_vec.m_vec.y = VEC_FLOAT_DIV (vec->m_vec.y, n);
	return_vec.m_vec.z = VEC_FLOAT_DIV (vec->m_vec.z, n);

	// Calculate x2+y2+z2/sqrt(x2+y2+z2)
	int f = vector3_dot_unsafe_std (return_vec,return_vec);
	f = VEC_FLOAT_DIV (pfx_f2vt(1.0f), pfx_f2vt(sqrt(pfx_vt2f(f))));

	// Multiply vector components by f
	return_vec.m_vec.x = VEC_FLOAT_MUL (return_vec.m_vec.x, f);
	return_vec.m_vec.y = VEC_FLOAT_MUL (return_vec.m_vec.y, f);
	return_vec.m_vec.z = VEC_FLOAT_MUL (return_vec.m_vec.z, f);
#else
	VEC_FLOAT len = vector3_length_unsafe_std (vec);
	return_vec.m_vec.x =VEC_FLOAT_DIV (vec->m_vec.x,len);
	return_vec.m_vec.y =VEC_FLOAT_DIV (vec->m_vec.y,len);
	return_vec.m_vec.z =VEC_FLOAT_DIV (vec->m_vec.z,len);
#endif
	return return_vec;
}


//////////////////////////////////////////////////////////////////////////
PFX_INLINE void init_vector4_default_unsafe_std (pfx_vector4_t* PARAM_INOUT vec)
{
	memset (vec,0,sizeof (pfx_vector4_t));
}

PFX_INLINE void init_vector4_by_float_unsafe_std (pfx_vector4_t* PARAM_INOUT vec,
	VEC_FLOAT fval)
{
	vec->m_vec.x = fval;
	vec->m_vec.y = fval;
	vec->m_vec.z = fval;
	vec->m_vec.w = fval;
}


PFX_INLINE void init_vector4_unsafe_std (pfx_vector4_t* PARAM_INOUT vec,
	VEC_FLOAT fx,VEC_FLOAT fy,VEC_FLOAT fz,VEC_FLOAT fw)
{
	vec->m_vec.x = fx;
	vec->m_vec.y = fy;
	vec->m_vec.z = fz;
	vec->m_vec.w = fw;
}

PFX_INLINE void init_vector4_by_vector3_unsafe_std (pfx_vector4_t* PARAM_INOUT vec,
	const pfx_vector3_t* PARAM_IN pvec,VEC_FLOAT fw)
{
	memcpy (vec,pvec,sizeof(pfx_vector3_t));
	vec->m_vec.w = fw;
}

PFX_INLINE void init_vector4_by_vector4_unsafe_std (pfx_vector4_t* PARAM_INOUT vec,
	const pfx_vector4_t* PARAM_IN pvec)
{
	memcpy (vec,pvec,sizeof(pfx_vector4_t));
}

PFX_INLINE pfx_vector4_t* vector4_add_ref_unsafe_std (pfx_vector4_t* PARAM_INOUT vec,
	const pfx_vector4_t* PARAM_IN vec_)
{
	vec->m_vec.x += vec_->m_vec.x;
	vec->m_vec.y += vec_->m_vec.y;
	vec->m_vec.z += vec_->m_vec.z;
	vec->m_vec.w += vec_->m_vec.w;
	return vec;
}

PFX_INLINE pfx_vector4_t* vector4_sub_ref_unsafe_std (pfx_vector4_t* PARAM_INOUT vec,
	const pfx_vector4_t* PARAM_IN vec_)
{
	vec->m_vec.x -= vec_->m_vec.x;
	vec->m_vec.y -= vec_->m_vec.y;
	vec->m_vec.z -= vec_->m_vec.z;
	vec->m_vec.w -= vec_->m_vec.w;

	return vec;
}

PFX_INLINE pfx_vector4_t vector4_add_unsafe_std (const pfx_vector4_t* PARAM_IN vec,
	const pfx_vector4_t* PARAM_IN vec_)
{
	pfx_vector4_t result_vec;
	result_vec.m_vec.x = vec->m_vec.x + vec_->m_vec.x;
	result_vec.m_vec.y = vec->m_vec.y + vec_->m_vec.y;
	result_vec.m_vec.z = vec->m_vec.z +  vec_->m_vec.z;
	result_vec.m_vec.w = vec->m_vec.w + vec_->m_vec.w;
	return result_vec;
}

PFX_INLINE pfx_vector4_t vector4_sub_unsafe_std (const pfx_vector4_t* PARAM_IN vec,
	const pfx_vector4_t* PARAM_IN vec_)
{
	pfx_vector4_t result_vec;

	result_vec.m_vec.x = vec->m_vec.x - vec_->m_vec.x;
	result_vec.m_vec.y = vec->m_vec.y - vec_->m_vec.y;
	result_vec.m_vec.z = vec->m_vec.z - vec_->m_vec.z;
	result_vec.m_vec.w = vec->m_vec.w - vec_->m_vec.w;

	return result_vec;
}

PFX_INLINE pfx_vector4_t* vector4_mul_float_ref_unsafe_std (pfx_vector4_t* PARAM_INOUT vec,
	VEC_FLOAT fval)
{
	vec->m_vec.x = VEC_FLOAT_MUL (vec->m_vec.x,fval);
	vec->m_vec.y = VEC_FLOAT_MUL (vec->m_vec.y,fval);
	vec->m_vec.z = VEC_FLOAT_MUL (vec->m_vec.z,fval);
	vec->m_vec.w = VEC_FLOAT_MUL (vec->m_vec.w,fval);
	return vec;
}

PFX_INLINE pfx_vector4_t* vector4_div_float_ref_unsafe_std (pfx_vector4_t* PARAM_INOUT vec,
	VEC_FLOAT fval)
{
	vec->m_vec.x = VEC_FLOAT_DIV (vec->m_vec.x,fval);
	vec->m_vec.y = VEC_FLOAT_DIV (vec->m_vec.y,fval);
	vec->m_vec.z = VEC_FLOAT_DIV (vec->m_vec.z,fval);
	vec->m_vec.w = VEC_FLOAT_DIV (vec->m_vec.w,fval);
	return vec;
}

PFX_INLINE pfx_vector4_t vector4_mul_float_unsafe_std (const pfx_vector4_t* PARAM_IN vec,
	VEC_FLOAT fval)
{
	pfx_vector4_t result_vec;

	result_vec.m_vec.x = VEC_FLOAT_MUL (vec->m_vec.x,fval);
	result_vec.m_vec.y = VEC_FLOAT_MUL (vec->m_vec.y,fval);
	result_vec.m_vec.z = VEC_FLOAT_MUL (vec->m_vec.z,fval);
	result_vec.m_vec.w = VEC_FLOAT_MUL (vec->m_vec.w,fval);

	return result_vec;
}

PFX_INLINE pfx_vector4_t vector4_div_float_unsafe_std (const pfx_vector4_t* PARAM_IN vec,
	VEC_FLOAT fval)
{
	pfx_vector4_t result_vec;

	result_vec.m_vec.x = VEC_FLOAT_DIV (vec->m_vec.x,fval);
	result_vec.m_vec.y = VEC_FLOAT_DIV (vec->m_vec.y,fval);
	result_vec.m_vec.z = VEC_FLOAT_DIV (vec->m_vec.z,fval);
	result_vec.m_vec.w = VEC_FLOAT_DIV (vec->m_vec.w,fval);

	return result_vec;
}


PFX_INLINE pfx_vector4_t* vector4_mul_vector4_ref_unsafe_std (pfx_vector4_t* PARAM_INOUT vec,
	const pfx_vector4_t* PARAM_IN vec_val)
{
	vec->m_vec.x = VEC_FLOAT_MUL (vec->m_vec.x,vec_val->m_vec.x);
	vec->m_vec.y = VEC_FLOAT_MUL (vec->m_vec.y,vec_val->m_vec.y);
	vec->m_vec.z = VEC_FLOAT_MUL (vec->m_vec.z,vec_val->m_vec.z);
	vec->m_vec.w = VEC_FLOAT_MUL (vec->m_vec.w,vec_val->m_vec.w);
	return vec;
}

PFX_INLINE pfx_vector4_t* vector4_div_vector4_ref_unsafe_std (pfx_vector4_t* PARAM_INOUT vec,
	const pfx_vector4_t* PARAM_IN vec_val)
{
	vec->m_vec.x = VEC_FLOAT_DIV (vec->m_vec.x,vec_val->m_vec.x);
	vec->m_vec.y = VEC_FLOAT_DIV (vec->m_vec.y,vec_val->m_vec.y);
	vec->m_vec.z = VEC_FLOAT_DIV (vec->m_vec.z,vec_val->m_vec.z);
	vec->m_vec.w = VEC_FLOAT_DIV (vec->m_vec.w,vec_val->m_vec.w);
	return vec;
}

PFX_INLINE pfx_vector4_t vector4_mul_vector4_unsafe_std (const pfx_vector4_t* PARAM_IN vec,
	const pfx_vector4_t* PARAM_IN vec_val)
{
	pfx_vector4_t vec_result;

	vec_result.m_vec.x = VEC_FLOAT_MUL (vec->m_vec.x,vec_val->m_vec.x);
	vec_result.m_vec.y = VEC_FLOAT_MUL (vec->m_vec.y,vec_val->m_vec.y);
	vec_result.m_vec.z = VEC_FLOAT_MUL (vec->m_vec.z,vec_val->m_vec.z);
	vec_result.m_vec.w = VEC_FLOAT_MUL (vec->m_vec.w,vec_val->m_vec.w);
	return vec_result;
}

PFX_INLINE pfx_vector4_t vector4_div_vector4_unsafe_std (const pfx_vector4_t* PARAM_IN vec,
	const pfx_vector4_t* PARAM_IN vec_val)
{
	pfx_vector4_t vec_result;

	vec_result.m_vec.x = VEC_FLOAT_DIV (vec->m_vec.x,vec_val->m_vec.x);
	vec_result.m_vec.y = VEC_FLOAT_DIV (vec->m_vec.y,vec_val->m_vec.y);
	vec_result.m_vec.z = VEC_FLOAT_DIV (vec->m_vec.z,vec_val->m_vec.z);
	vec_result.m_vec.w = VEC_FLOAT_DIV (vec->m_vec.w,vec_val->m_vec.w);

	return vec_result;
}

PFX_INLINE pfx_bool_t vector4_equals_unsafe_std (const pfx_vector4_t* PARAM_IN vec_a,
	const pfx_vector4_t* PARAM_IN vec_b)
{
	return (pfx_bool_t)(VEC_FLOAT_EQUALS (vec_a->m_vec.x,vec_b->m_vec.x) && 
		VEC_FLOAT_EQUALS (vec_a->m_vec.y,vec_b->m_vec.y) && 
		VEC_FLOAT_EQUALS (vec_a->m_vec.z,vec_b->m_vec.z) &&
		VEC_FLOAT_EQUALS (vec_a->m_vec.w,vec_b->m_vec.w));
}

PFX_INLINE VEC_FLOAT vector4_square_unsafe_std (const pfx_vector4_t* PARAM_IN vec)
{
	return VEC_FLOAT_MUL (vec->m_vec.x,vec->m_vec.x) + 
		VEC_FLOAT_MUL (vec->m_vec.y,vec->m_vec.y) +
		VEC_FLOAT_MUL (vec->m_vec.z,vec->m_vec.z) +
		VEC_FLOAT_MUL (vec->m_vec.w,vec->m_vec.w);
}

PFX_INLINE VEC_FLOAT vector4_length_unsafe_std (const pfx_vector4_t* PARAM_IN vec_)
{
	return (VEC_FLOAT) pfx_f2vt (sqrt(pfx_vt2f (vec_->m_vec.x) * pfx_vt2f (vec_->m_vec.x) + 
		pfx_vt2f (vec_->m_vec.y) * pfx_vt2f(vec_->m_vec.y) +
		pfx_vt2f (vec_->m_vec.z) * pfx_vt2f(vec_->m_vec.z) +
		pfx_vt2f (vec_->m_vec.w)*pfx_vt2f(vec_->m_vec.w)) );
}

PFX_INLINE VEC_FLOAT vector4_dot_unsafe_std (const pfx_vector4_t* PARAM_IN vec_a,
	const pfx_vector4_t* vec_b)
{
	return VEC_FLOAT_MUL (vec_a->m_vec.x,vec_b->m_vec.x) +
		VEC_FLOAT_MUL (vec_a->m_vec.y,vec_b->m_vec.y) + 
		VEC_FLOAT_MUL (vec_a->m_vec.z,vec_b->m_vec.z) +
		VEC_FLOAT_MUL (vec_a->m_vec.w,vec_b->m_vec.w);
}


PFX_INLINE pfx_vector4_t* vector4_normalize_ref_unsafe_std (pfx_vector4_t* PARAM_INOUT vec)
{
	return vector4_div_float_ref_unsafe_std (vec,vector4_length_unsafe_std (vec));
}

PFX_INLINE pfx_vector4_t vector4_normalize_unsafe_std (pfx_vector4_t* PARAM_INOUT vec)
{
	return vector4_div_float_unsafe_std (vec,vector4_length_unsafe_std (vec));
}


PFX_C_EXTERN_END

#endif			//PFX_VECTOR4_H_
