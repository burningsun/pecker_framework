/*
 * pfx_render_type.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDER_TYPE_H_
#define		PFX_RENDER_TYPE_H_

#include "../pfx_defines.h"

PFX_C_EXTERN_BEGIN

typedef struct st_pfx_color pfx_color_t;

struct st_pfx_color
{
	pfx_float_t m_red;
	pfx_float_t m_green;
	pfx_float_t m_blue;
};

PFX_C_EXTERN_END

#endif			//PFX_RENDER_TYPE_H_
