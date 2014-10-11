/*
 * pfx_vector4_param_sse.h
 *
 *  Created on: 2013-8-25
 *      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_VECTOR4_PARAM_SSE_H_
#define		PFX_VECTOR4_PARAM_SSE_H_

#include "pfx_simd_param.h"

#include <xmmintrin.h>
#include <intrin.h>

PECKER_BEGIN


//#pragma pack (push)
//#pragma pack (1)

typedef union PFX_SIMD_INTRIN  PFX_SIMD_ALIGN_TYPE(8, un_simd64_bit
{
	__m64     m_vec64bit;
	VECTOR2F_t m_vec2f;
	VECTOR2I_t m_vec2i;
}simd64bit_t); 

typedef union PFX_SIMD_INTRIN PFX_SIMD_ALIGN_TYPE(16, un_simd128_bit
{
	__m128      m_vec128bit;
	simd64bit_t m_64bit[2];
	VECTOR4F_t  m_vec4f;
	VECTOR4I_t  m_vec4i;
	VECTOR3F_t  m_vec3f;
	VECTOR3I_t  m_vec3i;
	VECTOR2F_t  m_vec2f[2];
	VECTOR2I_t  m_vec2i[2];
	MATRIX2F_t  m_mat2x2f;
	MATRIX2I_t  m_mat2x2i;
}simd128bit_t);

typedef union PFX_SIMD_INTRIN PFX_SIMD_ALIGN_TYPE(32, un_simd256_bit
{
	__m256       m_vec256bit;
	simd64bit_t  m_64bit[4];
	simd128bit_t m_128bit[2];
	VECTOR4F_t   m_vec4f[2];
	VECTOR4I_t   m_vec4i[2];
	VECTOR3F_t   m_vec3f[2];
	VECTOR3I_t   m_vec3i[2];
	VECTOR2F_t   m_vec2f[4];
	VECTOR2I_t   m_vec2i[4];
	MATRIX2F_t   m_mat2x2f[2];
	MATRIX2I_t   m_mat2x2i[2];
}simd256bit_t);

#define SIMD_64BIT(NAME)  DECLARE_SIMD_ALIGN_BUF(simd64bit_t, NAME, PFX_SIMD64BIT_ALIGH)
#define SIMD_128BIT(NAME) DECLARE_SIMD_ALIGN_BUF(simd128bit_t, NAME, PFX_SIMD128BIT_ALIGH)
#define SIMD_256BIT(NAME) DECLARE_SIMD_ALIGN_BUF(simd256bit_t, NAME, PFX_SIMD256BIT_ALIGH)

//#pragma pack (pop)

PECKER_END

#endif			//PFX_VECTOR4_PARAM_SSE_H_
