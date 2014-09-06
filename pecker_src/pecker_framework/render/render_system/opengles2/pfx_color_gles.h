/*
 * pfx_color_gles.h
 *
 *  Created on: 2014-9-6
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_COLOR_GLES_H_
#define		PFX_COLOR_GLES_H_

#include <GLES2/gl2.h>
#include "../../pfx_color.h"
#include "../../../pfx_hal_info_gles2.h"
#include "pfx_render_allocator_gles.h"

PECKER_BEGIN


PFX_INLINE GLint PFX_CLR_T_2_GLES2_CLR(enum_int_t __PFX_format)
{
	static GLint res_table[PFX_UNKNOWN_COLOR_INFMT] =
	{
		GL_RGBA,
		GL_RGB,
		GL_ALPHA,
		GL_LUMINANCE,
		GL_LUMINANCE_ALPHA,
		-1,
		-1
	};

	if (__PFX_format < PFX_UNKNOWN_COLOR_INFMT && __PFX_format >= 0)
	{
		return res_table[__PFX_format];
	}
	else
	{
		return -1;
	}

}

PFX_INLINE GLint PFX_CLR_2_GLES2_CLR(enum_int_t __PFX_format)
{
	if (PFX_RGBA8_FMT <= __PFX_format && __PFX_format <= PFX_RGBA_5551_FMT)
	{
		return GL_RGBA;
	}
	else if (PFX_RGB8_FMT <= __PFX_format && __PFX_format <= PFX_RGB_565_FMT)
	{
		return GL_RGB;
	}
	else if (PFX_ALPHA_8_FMT == __PFX_format)
	{
		return GL_ALPHA;
	}
	else if (PFX_LUMINANCE_8_FMT == __PFX_format)
	{
		return GL_LUMINANCE;
	}
	else if (PFX_LUMINANCE_ALPHA_88_FMT == __PFX_format)
	{
		return GL_LUMINANCE_ALPHA;
	}
	else
	{
		return (-1);
	}
}

PFX_INLINE GLenum PFX_CLR_GET_GLES2_CLR_BITS_TYPE(enum_int_t __PFX_format)
{	
	if (PFX_RGBA8_FMT == __PFX_format ||
		PFX_RGB8_FMT == __PFX_format ||
		(PFX_ALPHA_8_FMT <= __PFX_format && PFX_LUMINANCE_ALPHA_88_FMT >= __PFX_format))
	{
		return GL_UNSIGNED_BYTE;
	}
	else if (PFX_RGB_565_FMT == __PFX_format)
	{
		return GL_UNSIGNED_SHORT_5_6_5;
	}
	else if (PFX_RGBA_5551_FMT == __PFX_format)
	{
		return GL_UNSIGNED_SHORT_5_5_5_1;
	}
	else if (PFX_RGBA_4444_FMT == __PFX_format)
	{
		return GL_UNSIGNED_SHORT_4_4_4_4;
	}
	else
	{
		return (-1);
	}
}


PECKER_END

#endif			//PFX_COLOR_GLES_H_
