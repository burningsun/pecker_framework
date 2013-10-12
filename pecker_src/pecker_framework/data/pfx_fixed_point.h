/*
 * pfx_fixed_point.h
 *
 *  Created on: 2013-10-5
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_FIXED_POINT_H_
#define		PFX_FIXED_POINT_H_

#include "../pfx_defines.h"
#include "pfx_math_table.h"

#define VEC_FLOAT	pfx_float_t


#define PFX_FLOAT_2_INTX(f)		( (int) ( (f)*(65536) ) )
#define PFX_INTX_2_FLOAT(x)		((float)(x)/65536.0f)
#define PFX_INTX_MUL(a,b)	( (int)( ((long long)(a)*(b)) / 65536 ) )
#define PFX_INTX_DIV(a,b)	( (int)( (((long long)(a))<<16)/(b) ) )
#define PFX_ABS(a)		((a) <= 0 ? -(a) : (a))



#define COS_TABLE(x)	(pfx_cos_val[(PVRTXMUL(((PVRTXDIV((x)<0? -(x):(x), PVRT_TWO_PIx)) & 0x0000FFFF), (NUM_ENTRIES-1)))])
#define SIN_TABLE(x)	(pfx_sin_val[(PVRTXMUL(((PVRTXDIV((x)<0 ? PVRT_PIx-(x):(x), PVRT_TWO_PIx)) & 0x0000FFFF), (NUM_ENTRIES-1)))])
#define TAN_TABLE(x)	( (x)<0 ? -pfx_tan_val[(PVRTXMUL(((PVRTXDIV(-(x), PVRT_TWO_PIx)) & 0x0000FFFF), (NUM_ENTRIES-1)))] : pfx_tan_val[(PVRTXMUL(((PVRTXDIV(x, PVRT_TWO_PIx)) & 0x0000FFFF), (NUM_ENTRIES-1)))] )
#define ACOS_TABLE(x)	(pfx_acos_val[PVRTXMUL(((((x) + PVRTF2X(1.0f))>>1) & 0x0000FFFF), (NUM_ENTRIES-1))])

#ifdef USE_TRIGONOMETRIC_LOOKUP_TABLES
#define	pfx_cos(x)		PFX_INTX_2_FLOAT(COS_TABLE(PFX_FLOAT_2_INTX(x)))
#define	pfx_sin(x)		PFX_INTX_2_FLOAT(SIN_TABLE(PFX_FLOAT_2_INTX(x)))
#define	pfx_tan(x)		PFX_INTX_2_FLOAT(TAN_TABLE(PFX_FLOAT_2_INTX(x)))
#define	pfx_acos(x)		PFX_INTX_2_FLOAT(ACOS_TABLE(PFX_FLOAT_2_INTX(x)))
#else
#include <math.h>
#define	pfx_cos(x)		((pfx_float_t)cos(x))
#define	pfx_sin(x)		((pfx_float_t)sin(x))
#define	pfx_tan(x)		((pfx_float_t)tan(x))
#define	pfx_acos(x)		((pfx_float_t)acos(x))
#endif


#ifdef PFX_FIXED_POINT_ENABLE 
// 没有fpu下的兼容模式
#define VEC_FLOAT_MUL(a,b)		PFX_INTX_MUL(a,b)
#define VEC_FLOAT_DIV(a,b)		PFX_INTX_DIV(a,b)
#define VEC_FLOAT_ABS(a)			PFX_ABS(a)
#define VEC_FLOAT_EQUALS(a,b)		((a) == (b))
#define VEC_FLOAT_CMP(a,b)				((a) - (b))
#define VEC_FLOAT_EQUALS_ZERO(a)	(a)
#define pfx_f2vt(f) 					PFX_FLOAT_2_INTX(f)
#define pfx_vt2f(x) 					PFX_INTX_2_FLOAT(x)

#else
// 有fpu
#include <math.h>
#define VEC_FLOAT_MUL(a,b)		((VEC_FLOAT)((a)*(b)))
#define VEC_FLOAT_DIV(a,b)		((VEC_FLOAT)((a)/(b)))
#define VEC_FLOAT_ABS(a)			((VEC_FLOAT)(fabs(a)))

#define pfx_f2vt(x)						(x)
#define pfx_vt2f(x)						(x)

#define FLOAT_REF_VALUE				(0.0000999f)
#define FLOAT_ERROR_VALUE			(1e-7)
#define FLOAT_ERROR_MASK			(10)
#define FLOAT_REF_SIN_MASK_COUNT		(12)
// IEEE754浮点数比较
#define FLAOT_EXP_BIT_MASK		(0x7F800000)
#define FLOAT_SIGNIF_BIT_MASK	(0x007FFFFF)


PFX_INLINE pfx_bitfield_t pfx_float_to_int_bits (pfx_float_t X)
{
	PFX_32bit_DataType bitfiled;
	bitfiled.m_float_type = X;

	if (((bitfiled.m_uint_type & FLAOT_EXP_BIT_MASK) == FLAOT_EXP_BIT_MASK) &&
		(bitfiled.m_uint_type & FLOAT_SIGNIF_BIT_MASK) != 0)
	{
		bitfiled.m_uint_type = 0x7FC00000;
	}
	return bitfiled.m_uint_type;
}
PFX_INLINE pfx_sint_t float_equals (pfx_float_t X,pfx_float_t Y)
{
	if (X > FLOAT_REF_VALUE || X < (-FLOAT_REF_VALUE))
	{
		X = X - Y;
		if  (X > FLOAT_ERROR_VALUE && X < (-FLOAT_ERROR_VALUE))
		{
			return pfx_false;
		}
		else
		{
			return pfx_true;
		}
	}
	else
	{
		PFX_32bit_DataType		bitfiledx;
		pfx_bitfield_t					bit_count;
		int cmp_mask;

		bitfiledx.m_float_type = X;

		bit_count = bitfiledx.m_uint_type & FLOAT_SIGNIF_BIT_MASK;

		if (((bitfiledx.m_uint_type & FLAOT_EXP_BIT_MASK) == FLAOT_EXP_BIT_MASK) &&
			bit_count != 0)
		{
			bitfiledx.m_uint_type = 0x7FC00000;
		}
		//计算有效数位1的个数，1的个数越多证明有效数字越多
		//在设定有效数位阀值的时候，进行误差过滤
		bit_count = get_32bit_onemask_count(bit_count);

		cmp_mask = bitfiledx.m_int_type - (int)pfx_float_to_int_bits(Y);

		if (bit_count > FLOAT_REF_SIN_MASK_COUNT)
		{
			if ((cmp_mask < FLOAT_ERROR_MASK) && (cmp_mask > (-FLOAT_ERROR_MASK)))
			{
				return pfx_true;
			}
		}

		if (cmp_mask)
		{
			return pfx_false;
		}
		else
		{
			return pfx_true;
		}
	}
}
PFX_INLINE int float_cmp (pfx_float_t X,pfx_float_t Y)
{
	int cmp_mask;

	if (X > FLOAT_REF_VALUE || X < (-FLOAT_REF_VALUE))
	{
		X = X - Y;
		if  (X < FLOAT_ERROR_VALUE && X > (-FLOAT_ERROR_VALUE))
		{
			return 0;
		}
		else if (X > 0)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		PFX_32bit_DataType		bitfiledx;
		pfx_bitfield_t					bit_count;

		bitfiledx.m_float_type = X;

		
		bit_count = bitfiledx.m_uint_type & FLOAT_SIGNIF_BIT_MASK;

		if (((bitfiledx.m_uint_type & FLAOT_EXP_BIT_MASK) == FLAOT_EXP_BIT_MASK) &&
			bit_count != 0)
		{
			bitfiledx.m_uint_type = 0x7FC00000;
		}
		//计算有效数位1的个数，1的个数越多证明有效数字越多
		//在设定有效数位阀值的时候，进行误差过滤
		bit_count = get_32bit_onemask_count(bit_count);

		cmp_mask = bitfiledx.m_int_type - (int)pfx_float_to_int_bits(Y);

		if (bit_count > FLOAT_REF_SIN_MASK_COUNT)
		{
			if ((cmp_mask < FLOAT_ERROR_MASK) && (cmp_mask > (-FLOAT_ERROR_MASK)))
			{
				cmp_mask = 0;
			}
		}
		return cmp_mask;
	}
}
PFX_INLINE int float_cmp_zero (pfx_float_t X)
{	
	if (X > FLOAT_ERROR_VALUE)
	{
		return 1;
	}
	else if (X < -FLOAT_ERROR_VALUE)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}



#define VEC_FLOAT_EQUALS(a,b)			float_equals((a),(b))
#define VEC_FLOAT_CMP(a,b)					float_cmp((a),(b))
#define VEC_FLOAT_EQUALS_ZERO(a)	float_cmp_zero((a));


#endif

#endif			//PFX_FIXED_POINT_H_
