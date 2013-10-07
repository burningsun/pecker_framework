/*
 * pfx_fixed_point.h
 *
 *  Created on: 2013-10-5
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_FIXED_POINT_H_
#define		PFX_FIXED_POINT_H_

#include "../pfx_defines.h"

#define PFX_FLOAT_2_INTX(f)		( (int) ( (f)*(65536) ) )
#define PFX_INTX_2_FLOAT(x)		((float)(x)/65536.0f)
#define PFX_INTX_MUL(a,b)	( (int)( ((long long)(a)*(b)) / 65536 ) )
#define PFX_INTX_DIV(a,b)	( (int)( (((long long)(a))<<16)/(b) ) )
#define PFX_ABS(a)		((a) <= 0 ? -(a) : (a))



#endif			//PFX_FIXED_POINT_H_
