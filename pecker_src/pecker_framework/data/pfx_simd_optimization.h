/*
 * pfx_simd_optimization.h
 *
 *  Created on: 2013-10-14
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_OPTIMIZATION_H_
#define		PFX_SIMD_OPTIMIZATION_H_

#include "../pfx_defines.h"


#ifdef USING_SSE_

#else
//////////////////////////////////////////////////////////////////////////////////////
	#define init_vector2_default_unsafe								init_vector2_default_unsafe_std
	#define init_vector2_by_float_unsafe							init_vector2_by_float_unsafe_std
	#define init_vector2_unsafe											init_vector2_unsafe_std
	#define init_vector2_by_vector2_unsafe						init_vector2_by_vector2_unsafe_std
	#define vector2_add_ref_unsafe										vector2_add_ref_unsafe_std
	#define vector2_sub_ref_unsafe										vector2_sub_ref_unsafe_std
	#define vector2_add_unsafe											vector2_add_unsafe_std
	#define vector2_sub_unsafe											vector2_sub_unsafe_std
	#define vector2_mul_float_ref_unsafe							vector2_mul_float_ref_unsafe_std
	#define vector2_div_float_ref_unsafe							vector2_div_float_ref_unsafe_std
	#define vector2_mul_float_unsafe									vector2_mul_float_unsafe_std
	#define vector2_div_float_unsafe									vector2_div_float_unsafe_std
	#define vector2_mul_vector2_ref_unsafe						vector2_mul_vector2_ref_unsafe_std
	#define vector2_div_vector2_ref_unsafe						vector2_div_vector2_ref_unsafe_std
	#define vector2_mul_vector2_unsafe							vector2_mul_vector2_unsafe_std
	#define vector2_div_vector2_unsafe								vector2_div_vector2_unsafe_std
	#define vector2_equals_unsafe										vector2_equals_unsafe_std
	#define vector2_square_unsafe										vector2_square_unsafe_std
	#define vector2_length													vector2_length_std
	#define vector2_normalize_ref_unsafe							vector2_normalize_ref_unsafe_std
	#define vector2_normalize_unsafe									vector2_normalize_unsafe_std
	#define vector2_rotated_90_unsafe								vector2_rotated_90_unsafe_std
	#define vector2_dot_unsafe											vector2_dot_unsafe_std

	//////////////////////////////////////////////
	#define init_vector3_default_unsafe								init_vector3_default_unsafe_std
	#define init_vector3_by_float_unsafe							init_vector3_by_float_unsafe_std
	#define init_vector3_unsafe											init_vector3_unsafe_std
	#define init_vector3_by_vector3_unsafe						init_vector3_by_vector3_unsafe_std
	#define vector3_add_ref_unsafe										vector3_add_ref_unsafe_std
	#define vector3_sub_ref_unsafe										vector3_sub_ref_unsafe_std
	#define vector3_add_unsafe											vector3_add_unsafe_std
	#define vector3_sub_unsafe											vector3_sub_unsafe_std
	#define vector3_mul_float_ref_unsafe							vector3_mul_float_ref_unsafe_std
	#define vector3_div_float_ref_unsafe							vector3_div_float_ref_unsafe_std
	#define vector3_mul_float_unsafe									vector3_mul_float_unsafe_std
	#define vector3_div_float_unsafe									vector3_div_float_unsafe_std
	#define vector3_mul_vector3_ref_unsafe						vector3_mul_vector3_ref_unsafe_std
	#define vector3_div_vector3_ref_unsafe						vector3_div_vector3_ref_unsafe_std
	#define vector3_mul_vector3_unsafe							vector3_mul_vector3_unsafe_std
	#define vector3_div_vector3_unsafe								vector3_div_vector3_unsafe_std
	#define vector3_equals_unsafe										vector3_equals_unsafe_std
	#define vector3_square_unsafe										vector3_square_unsafe_std
	#define vector3_length_unsafe										vector3_length_unsafe_std
	#define vector3_dot_unsafe											vector3_dot_unsafe_std
	#define vector3_cross_unsafe											vector3_cross_unsafe_std
	#define vector3_normalize_ref_unsafe							vector3_normalize_ref_unsafe_std
	#define vector3_normalize_unsafe									vector3_normalize_unsafe_std

	///////////////////////////////////////////
	#define init_vector4_default_unsafe								init_vector4_default_unsafe_std
	#define init_vector4_by_float_unsafe							init_vector4_by_float_unsafe_std
	#define init_vector4_unsafe											init_vector4_unsafe_std
	#define init_vector4_by_vector3_unsafe						init_vector4_by_vector3_unsafe_std
	#define init_vector4_by_vector4_unsafe						init_vector4_by_vector4_unsafe_std
	#define vector4_add_ref_unsafe										vector4_add_ref_unsafe_std
	#define vector4_sub_ref_unsafe										vector4_sub_ref_unsafe_std
	#define vector4_add_unsafe											vector4_add_unsafe_std
	#define vector4_sub_unsafe											vector4_sub_unsafe_std
	#define vector4_mul_float_ref_unsafe							vector4_mul_float_ref_unsafe_std
	#define vector4_div_float_ref_unsafe							vector4_div_float_ref_unsafe_std
	#define vector4_mul_float_unsafe									vector4_mul_float_unsafe_std
	#define vector4_div_float_unsafe									vector4_div_float_unsafe_std
	#define vector4_mul_vector4_ref_unsafe						vector4_mul_vector4_ref_unsafe_std
	#define vector4_div_vector4_ref_unsafe						vector4_div_vector4_ref_unsafe_std
	#define vector4_mul_vector4_unsafe							vector4_mul_vector4_unsafe_std
	#define vector4_div_vector4_unsafe								vector4_div_vector4_unsafe_std
	#define vector4_equals_unsafe										vector4_equals_unsafe_std
	#define vector4_square_unsafe										vector4_square_unsafe_std
	#define vector4_length_unsafe										vector4_length_unsafe_std
	#define vector4_dot_unsafe											vector4_dot_unsafe_std
	#define vector4_normalize_ref_unsafe							vector4_normalize_ref_unsafe_std
	#define vector4_normalize_unsafe									vector4_normalize_unsafe_std

#endif


#endif			//PFX_SIMD_OPTIMIZATION_H_
