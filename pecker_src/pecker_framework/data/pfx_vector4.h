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

PFX_C_EXTERN_BEGIN

typedef struct st_pfx_vector_2f pfx_vector2f_t;
typedef struct st_pfx_vector_3f pfx_vector3f_t;
typedef struct st_pfx_vector_4f pfx_vector4f_t;

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

union un_pfx_vector_2
{
	VEC_FLOAT				m_vec_f[2];
	st_pfx_vector_2f	m_vec2f;
};

union un_pfx_vector_3
{
	VEC_FLOAT				m_vec_f[3];
	st_pfx_vector_3f	m_vec3f;
};

union un_pfx_vector_4
{
	VEC_FLOAT				m_vec_f[4];
	st_pfx_vector_4f	m_vec4f;
};

PFX_INLINE void init_vector2_default_unsafe (pfx_vector2_t* PARAM_INOUT vec2)
{
	memset (vec2,0,sizeof (pfx_vector2_t));
}

PFX_INLINE void init_vector2_unsafe (pfx_vector2_t* PARAM_INOUT vec2,
	VEC_FLOAT fx,VEC_FLOAT fy)
{
	vec2->m_vec2f.x = fx;
	vec2->m_vec2f.y = fy;
}

PFX_INLINE void init_vector2_by_vector2_unsafe (pfx_vector2_t* PARAM_INOUT vec2,
	const pfx_vector2_t* pvec)
{
	memcpy (vec2,pvec,sizeof(pfx_vector2_t));
}

PFX_INLINE pfx_vector2_t* vector2_add_unsafe (pfx_vector2_t* PARAM_INOUT vec2,
	const pfx_vector2_t* PARAM_IN vec2_)
{
	vec2->m_vec2f.x += vec2_->m_vec2f.x;
	vec2->m_vec2f.y += vec2_->m_vec2f.y;

	return vec2;
}

PFX_INLINE pfx_vector2_t* vector2_sub_unsafe (pfx_vector2_t* PARAM_INOUT vec2,
	const pfx_vector2_t* PARAM_IN vec2_)
{
	vec2->m_vec2f.x -= vec2_->m_vec2f.x;
	vec2->m_vec2f.y -= vec2_->m_vec2f.y;

	return vec2;
}

PFX_INLINE pfx_vector2_t* vector2_mul_float_unsafe (pfx_vector2_t* PARAM_INOUT vec2,
	VEC_FLOAT fval)
{
	vec2->m_vec2f.x = VEC_FLOAT_MUL (vec2->m_vec2f.x,fval);
	vec2->m_vec2f.y = VEC_FLOAT_MUL (vec2->m_vec2f.y,fval);

	return vec2;
}

PFX_INLINE pfx_vector2_t* vector2_div_float_unsafe (pfx_vector2_t* PARAM_INOUT vec2,
	VEC_FLOAT fval)
{
	vec2->m_vec2f.x = VEC_FLOAT_DIV (vec2->m_vec2f.x,fval);
	vec2->m_vec2f.y = VEC_FLOAT_DIV (vec2->m_vec2f.y,fval);

	return vec2;
}

PFX_INLINE pfx_vector2_t* vector2_mul_vector2_ref_unsafe (pfx_vector2_t* PARAM_INOUT vec2,
	const pfx_vector2_t* PARAM_IN vec2_val)
{
	vec2->m_vec2f.x = VEC_FLOAT_MUL (vec2->m_vec2f.x,vec2_val->m_vec2f.x);
	vec2->m_vec2f.y = VEC_FLOAT_MUL (vec2->m_vec2f.y,vec2_val->m_vec2f.y);

	return vec2;
}

PFX_INLINE pfx_vector2_t* vector2_div_vector2_ref_unsafe (pfx_vector2_t* PARAM_INOUT vec2,
	const pfx_vector2_t* PARAM_IN vec2_val)
{
	vec2->m_vec2f.x = VEC_FLOAT_DIV (vec2->m_vec2f.x,vec2_val->m_vec2f.x);
	vec2->m_vec2f.y = VEC_FLOAT_DIV (vec2->m_vec2f.y,vec2_val->m_vec2f.y);

	return vec2;
}

PFX_INLINE pfx_vector2_t vector2_mul_vector2_unsafe (pfx_vector2_t* PARAM_INOUT vec2,
	const pfx_vector2_t* PARAM_IN vec2_val)
{
	pfx_vector2_t vec_result;
	init_vector2_by_vector2_unsafe (&vec_result,vec2);
	vector2_mul_vector2_ref_unsafe (&vec_result,vec2_val);
	return vec_result;
}

PFX_INLINE pfx_vector2_t vector2_div_vector2_unsafe (pfx_vector2_t* PARAM_INOUT vec2,
	const pfx_vector2_t* PARAM_IN vec2_val)
{
	pfx_vector2_t vec_result;
	init_vector2_by_vector2_unsafe (&vec_result,vec2);
	vector2_div_vector2_ref_unsafe (&vec_result,vec2_val);
	return vec_result;
}

PFX_INLINE pfx_bool_t vector2_equals_unsafe (const pfx_vector2_t* PARAM_IN vec_a,
	const pfx_vector2_t* PARAM_IN vec_b)
{
	return (pfx_bool_t)((vec_a->m_vec2f.x == vec_b->m_vec2f.x) && 
		(vec_b->m_vec2f.y == vec_b->m_vec2f.y));
}

PFX_INLINE VEC_FLOAT vector2_square_unsafe (const pfx_vector2_t* PARAM_IN vec_x)
{
	return VEC_FLOAT_MUL (vec_x->m_vec2f.x,vec_x->m_vec2f.x) + 
		VEC_FLOAT_MUL (vec_x->m_vec2f.y,vec_x->m_vec2f.y);
}

PFX_INLINE VEC_FLOAT vector2_length (const pfx_vector2_t* PARAM_IN vec_)
{
	return (VEC_FLOAT) pfx_f2vt (sqrt
		(pfx_vt2f (vec_->m_vec2f.x) * pfx_vt2f (vec_->m_vec2f.x) + 
		pfx_vt2f (vec_->m_vec2f.y) * pfx_vt2f(vec_->m_vec2f.y)) );
}

PFX_INLINE pfx_vector2_t* vector2_normalize_ref_unsafe(pfx_vector2_t* PARAM_INOUT vec)
{
	return vector2_div_float_unsafe(vec,vector2_length(vec));
}

PFX_INLINE pfx_vector2_t vector2_normalize_unsafe(pfx_vector2_t* PARAM_INOUT vec)
{
	pfx_vector2_t vec_2;
	init_vector2_by_vector2_unsafe (&vec_2,vec);
	vector2_div_float_unsafe(&vec_2,vector2_length(&vec_2));
	return vec_2;
}

PFX_INLINE pfx_vector2_t* vector2_rotated_90_unsafe (const pfx_vector2_t* PARAM_IN vec_src,
	pfx_vector2_t* PARAM_INOUT result_vec)
{
	 init_vector2_unsafe(result_vec,-vec_src->m_vec2f.y,vec_src->m_vec2f.x);
	 return result_vec;
}

PFX_INLINE VEC_FLOAT vector2_dot_unsafe (const pfx_vector2_t* PARAM_IN vec_a,
	const pfx_vector2_t* vec_b)
{
	return VEC_FLOAT_MUL (vec_a->m_vec2f.x,vec_b->m_vec2f.x) +
		VEC_FLOAT_MUL (vec_a->m_vec2f.y,vec_b->m_vec2f.y);
}

PFX_C_EXTERN_END

#endif			//PFX_VECTOR4_H_
