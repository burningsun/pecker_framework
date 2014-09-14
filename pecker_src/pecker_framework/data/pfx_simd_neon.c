/*
* pfx_simd_neon.cpp
*
*  Created on: 2014-9-13
*      Author: ¿Ó’Ú≥«  £® cut / cutxyz£© (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#include "pfx_simd_neon.h"
//#include <arm_neon.h>


//PECKER_BEGIN

inline void FLOAT32ARR_ABS_NEON_ARMV7(float * dst_ptr, float * src_ptr)
{
//	vld1_s16((const int32_t*)src_ptr);

//	__asm__("vld1.32  {q0}, [%1]!    \n\t"
//			"vabs.f32 q3, q0         \n\t"
//			"vst1.32  {d6,d7}, [%0]! \n\t"
//			:"=r"(dst_ptr)
//			:"r"(src_ptr)
//			:"memory", "q0", "q3", "d6", "d7");
}

int abs_float32_neon(float * dst_ptr, float * src_ptr,
                        unsigned int count)
{
	unsigned int loop_remain_count;
	unsigned int loop_count;
    loop_remain_count = count & 0x03;// count % 4;
    loop_count = count >> 2;

    while (loop_count)
    {
    	FLOAT32ARR_ABS_NEON_ARMV7(dst_ptr,src_ptr);
    	--loop_count;
    }

	return 0;
}

//PECKER_END

