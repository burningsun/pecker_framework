/*
 * pfx_simd_fdiv_std.h
 *
 *  Created on: 2014-9-13
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_SIMD_FDIV_H_
#define		PFX_SIMD_FDIV_H_

#include "../pfx_defines.h"

#include "pfx_simd_param.h"
#include <math.h>

PECKER_BEGIN

//除法
typedef struct st_array_fdiv_unsafe_std
{
	static PFX_FORCE_INLINE float_t* operate(float_t*  PARAM_INOUT dst_ptr,
	const float_t cst,
	usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr] /= cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PARAM_INOUT dst_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] /= cst;
			dst_ptr[itr].m_vec[1] /= cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PARAM_INOUT dst_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] /= cst;
			dst_ptr[itr].m_vec[1] /= cst;
			dst_ptr[itr].m_vec[2] /= cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PARAM_INOUT dst_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] /= cst;
			dst_ptr[itr].m_vec[1] /= cst;
			dst_ptr[itr].m_vec[2] /= cst;
			dst_ptr[itr].m_vec[3] /= cst;
		}
		return dst_ptr;
	}


	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr] = src_ptr[itr] / cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src_ptr[itr].m_vec[0] / cst;
			dst_ptr[itr].m_vec[1] = src_ptr[itr].m_vec[1] / cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src_ptr[itr].m_vec[0] / cst;
			dst_ptr[itr].m_vec[1] = src_ptr[itr].m_vec[1] / cst;
			dst_ptr[itr].m_vec[2] = src_ptr[itr].m_vec[2] / cst;
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT  PARAM_OUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
		const float_t cst,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src_ptr[itr].m_vec[0] / cst;
			dst_ptr[itr].m_vec[1] = src_ptr[itr].m_vec[1] / cst;
			dst_ptr[itr].m_vec[2] = src_ptr[itr].m_vec[2] / cst;
			dst_ptr[itr].m_vec[3] = src_ptr[itr].m_vec[3] / cst;
		}
		return dst_ptr;
	}




	static PFX_FORCE_INLINE float_t* operate(float_t* PFX_RESTRICT PARAM_OUT dst_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const float_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr] = src1_ptr[itr] / src2_ptr[itr];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src1_ptr[itr].m_vec[0] / src2_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] = src1_ptr[itr].m_vec[1] / src2_ptr[itr].m_vec[1];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src1_ptr[itr].m_vec[0] / src2_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] = src1_ptr[itr].m_vec[1] / src2_ptr[itr].m_vec[1];
			dst_ptr[itr].m_vec[2] = src1_ptr[itr].m_vec[2] / src2_ptr[itr].m_vec[2];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src1_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src2_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] = src1_ptr[itr].m_vec[0] / src2_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] = src1_ptr[itr].m_vec[1] / src2_ptr[itr].m_vec[1];
			dst_ptr[itr].m_vec[2] = src1_ptr[itr].m_vec[2] / src2_ptr[itr].m_vec[2];
			dst_ptr[itr].m_vec[3] = src1_ptr[itr].m_vec[3] / src2_ptr[itr].m_vec[3];
		}
		return dst_ptr;
	}



	static PFX_FORCE_INLINE float_t* operate(float_t*  PARAM_INOUT dst_ptr,
		const float_t*  PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr] /= src_ptr[itr];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR2F_t* operate(VECTOR2F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR2F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] /= src_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] /= src_ptr[itr].m_vec[1];
		}
		return dst_ptr;
	}
	static PFX_FORCE_INLINE VECTOR3F_t* operate(VECTOR3F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR3F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] /= src_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] /= src_ptr[itr].m_vec[1];
			dst_ptr[itr].m_vec[2] /= src_ptr[itr].m_vec[2];
		}
		return dst_ptr;
	}

	static PFX_FORCE_INLINE VECTOR4F_t* operate(VECTOR4F_t* PFX_RESTRICT PARAM_INOUT dst_ptr,
		const VECTOR4F_t* PFX_RESTRICT PARAM_IN src_ptr,
		usize__t count)
	{
		for (uindex_t itr = count; itr != 0;)
		{
			--itr;
			dst_ptr[itr].m_vec[0] /= src_ptr[itr].m_vec[0];
			dst_ptr[itr].m_vec[1] /= src_ptr[itr].m_vec[1];
			dst_ptr[itr].m_vec[2] /= src_ptr[itr].m_vec[2];
			dst_ptr[itr].m_vec[3] /= src_ptr[itr].m_vec[3];
		}
		return dst_ptr;
	}

}array_fdiv_unsafe_std_t;

PECKER_END

#endif			//PFX_SIMD_FDIV_H_
