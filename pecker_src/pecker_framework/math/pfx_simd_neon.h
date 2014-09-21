/*
* pfx_simd_neon.h
*
*  Created on: 2014-9-13
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/
#ifndef		PFX_SIMD_NEON_H_
#define		PFX_SIMD_NEON_H_

//#include "../pfx_defines.h"


//PECKER_BEGIN


int abs_float32_neon(float * dst_ptr, float * src_ptr,
                        unsigned int count);

//PECKER_END

#endif			//PFX_SIMD_NEON_H_
