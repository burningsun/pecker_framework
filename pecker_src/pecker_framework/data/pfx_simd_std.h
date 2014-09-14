/*
 * pfx_simd_std.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_H_
#define		PFX_SIMD_H_

#include "../pfx_defines.h"

#include "../../depends_lib/Ne10/inc/NE10_math_pfx.h"

#include "pfx_vector4_param.h"

PECKER_BEGIN

typedef struct st_array_abs_std
{

}array_abs_std_t;

typedef struct st_array_add_std
{
	static PFX_INLINE result_t operate(float_t* dst_ptr, const float_t* src_ptr, const float_t cst, usize__t count)
	{
		return ne10_addc_float_c(dst_ptr, (float_t*)src_ptr, cst, count);
	}
	static PFX_INLINE result_t operate(VECTOR2F_t* dst, const VECTOR2F_t* src_ptr, const VECTOR2F_t& cst, usize__t count)
	{
		return ne10_addc_vec2f_c((ne10_vec2f_t*)dst, (ne10_vec2f_t*)src_ptr, (const ne10_vec2f_t*)&cst, count);
	}
	static PFX_INLINE result_t operate(VECTOR3F_t* dst, const VECTOR3F_t* src_ptr, const VECTOR3F_t& cst, usize__t count)
	{
		return ne10_addc_vec3f_c((ne10_vec3f_t*)dst, (ne10_vec3f_t*)src_ptr, (const ne10_vec3f_t*)&cst, count);
	}
	static PFX_INLINE result_t operate(VECTOR4F_t* dst, const VECTOR4F_t* src_ptr, const VECTOR4F_t& cst, usize__t count)
	{
		return ne10_addc_vec4f_c((ne10_vec4f_t*)dst, (ne10_vec4f_t*)src_ptr, (const ne10_vec4f_t*)&cst, count);
	}
}array_add_std_t;

PECKER_END

#endif			//PFX_SIMD_H_
