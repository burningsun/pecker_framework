/*
 * pfx_simd_fmatcross_std.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FMATCROSS_H_
#define		PFX_SIMD_FMATCROSS_H_

#include "../pfx_defines.h"

#include "pfx_simd_param.h"
#include <math.h>
#include "pfx_simd_fadd_std.h"
#include "pfx_simd_fsub_std.h"
#include "pfx_simd_fmul_std.h"
#include "pfx_simd_fdiv_std.h"

PECKER_BEGIN

typedef struct st_vector_cross_unsafe_std
{
	//////////////////////////////////////////////////////////////////////////
	// 
	// 多个矩阵点乘队列
	// 2x2矩阵
	// M(行，列)
	//   M11, M12
	//   M21, M22

	// 3x3矩阵 
	// M(行，列)
	//   M11, M12, M13
	//   M21, M22, M23
	//   M31, M32, M33

	// 4x4矩阵
	//   M11, M12, M13, M14
	//   M21, M22, M23, M24
	//   M31, M32, M33, M34
	//   M41, M42, M43, M44

//////////////////////////////////////////////////////////////////////////
// 叉乘
#define VEC_D_X    dst.m_vec[DIMENSION_X]
#define VEC_D_Y    dst.m_vec[DIMENSION_Y]
#define VEC_D_Z    dst.m_vec[DIMENSION_Z]
#define VEC_S1_X   src1.m_vec[DIMENSION_X]
#define VEC_S1_Y   src1.m_vec[DIMENSION_Y]
#define VEC_S1_Z   src1.m_vec[DIMENSION_Z]
#define VEC_S2_X   src2.m_vec[DIMENSION_X]
#define VEC_S2_Y   src2.m_vec[DIMENSION_Y]
#define VEC_S2_Z   src2.m_vec[DIMENSION_Z]

	static PFX_FORCE_INLINE VECTOR3F_t* cross
		(VECTOR3F_t& PFX_RESTRICT PARAM_INOUT dst,
		const VECTOR3F_t& PFX_RESTRICT PARAM_INOUT src1,
		const VECTOR3F_t& PFX_RESTRICT PARAM_INOUT src2)
	{
		VEC_D_X = (VEC_S1_Y * VEC_S2_Z) - (VEC_S1_Z * VEC_S2_Y);
		VEC_D_Y = (VEC_S1_Z * VEC_S2_X) - (VEC_S1_X * VEC_S2_Z);
		VEC_D_Z = (VEC_S1_X * VEC_S2_Y) - (VEC_S1_Y * VEC_S2_X);
		return &dst;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* cross
		(VECTOR4F_t& PFX_RESTRICT PARAM_INOUT dst,
		const VECTOR4F_t& PFX_RESTRICT PARAM_INOUT src1,
		const VECTOR4F_t& PFX_RESTRICT PARAM_INOUT src2)
	{
		VEC_D_X = (VEC_S1_Y * VEC_S2_Z) - (VEC_S1_Z * VEC_S2_Y);
		VEC_D_Y = (VEC_S1_Z * VEC_S2_X) - (VEC_S1_X * VEC_S2_Z);
		VEC_D_Z = (VEC_S1_X * VEC_S2_Y) - (VEC_S1_Y * VEC_S2_X);
		dst.m_vec[DIMENSION_W] = 1.0;
		return &dst;
	}

#undef VEC_D_X 
#undef VEC_D_Y 
#undef VEC_D_Z 
#undef VEC_S1_X
#undef VEC_S1_Y
#undef VEC_S1_Z
#undef VEC_S2_X
#undef VEC_S2_Y
#undef VEC_S2_Z


}vector_cross_unsafe_std_t;


typedef VECTOR3F_t* (*fvec3_cross_func)
                                       (VECTOR3F_t& PFX_RESTRICT PARAM_INOUT dst,
                                       const VECTOR3F_t& PFX_RESTRICT PARAM_INOUT src1,
                                       const VECTOR3F_t& PFX_RESTRICT PARAM_INOUT src2);

typedef VECTOR4F_t* (*fvec3_extern_cross_func)
                                      (VECTOR4F_t& PFX_RESTRICT PARAM_INOUT dst,
                                      const VECTOR4F_t& PFX_RESTRICT PARAM_INOUT src1,
                                      const VECTOR4F_t& PFX_RESTRICT PARAM_INOUT src2);


typedef struct st_simd_fvec_cross_unsafe
{
	fvec3_cross_func         fvec3_cross;
	fvec3_extern_cross_func  fvec3_extern_cross;
}simd_fvec_cross_unsafe_t;


PFX_INLINE simd_fvec_cross_unsafe_t*	init_simd_fvec_cross_std(simd_fvec_cross_unsafe_t& __fcross)
{
	__fcross.fvec3_cross         = vector_cross_unsafe_std_t::cross;
	__fcross.fvec3_extern_cross  = vector_cross_unsafe_std_t::cross;
	return &__fcross;
}
PECKER_END

#endif			//PFX_SIMD_FMATCROSS_H_
