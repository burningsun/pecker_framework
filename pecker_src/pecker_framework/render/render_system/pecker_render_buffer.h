/*
 * pecker_render_buffer.h
 *
 *  Created on: 2013-3-17
 *      Author: ¿Ó’Ú≥«  £® cut / cutxyz£©
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_RENDER_BUFFER_H_
#define  PECKER_RENDER_BUFFER_H_

#include "../pecker_render_object.h"

PECKER_BEGIN




struct pecker_render_buffer_info
{
	HEnum _M_internal_format;
	nSize		_M_width;
	nSize		_M_heigth;
};

PeckerInterface Ipecker_render_buffer :public Ipecker_frame_buffer_object//: public Ipecker_graphic_buffer
{
	virtual ~Ipecker_render_buffer(){;}
	virtual HResult allocate_buffer_from_gpu_ram() = 0;
	virtual HResult release_buffer_from_gpu_ram() = 0;
	//virtual HResult set_default_render_buffer_info(const pecker_render_buffer_info& buf_info) = 0;
	virtual HResult use_render_buffer_info() = 0;
	virtual HResult use_render_buffer_info(const pecker_render_buffer_info& buf_info) = 0;
	virtual const pecker_render_buffer_info& get_render_buffer_info() const = 0;
	//virtual HEnum get_frame_buffer_object_type() const = 0;
};

enum COLOR_BUFFER_FORMAT
{
	COLOR_RGB565 = 0,
	COLOR_RGBA4,
	COLOR_RGB5_A1,

	COLOR_RGB8_OES,
	COLOR_RGBA8_OES,

	COLOR_BUFFER_FORMAT_COUNT
};
PeckerInterface Ipecker_color_buffer : public Ipecker_render_buffer
{
	virtual ~Ipecker_color_buffer(){;}
	HEnum get_frame_buffer_object_type() const;
};

enum DEPTH_BUFFER_FORMAT
{
	DEPTH_COMPONENT16 = 0,

	DEPTH_COMPONENT24_OES,
	DEPTH_COMPONENT32_OES,
	DEPTH24_STENCIL8_OES,

	DEPTH_BUFFER_FORMAT_COUNT
};
PeckerInterface Ipecker_depth_buffer : public Ipecker_render_buffer
{
	virtual ~Ipecker_depth_buffer(){;}
	HEnum get_frame_buffer_object_type() const;
};

enum STENCIL_BUFFER_FORMAT
{

	STENCIL_INDEX8 = 0,

	STENCIL_INDEX1_OES,
	STENCIL_INDEX4_OES,

	STENCIL8_DEPTH24_OES,

	STENCIL_BUFFER_FORMAT_COUNT
};

PeckerInterface Ipecker_stencil_buffer : public Ipecker_render_buffer
{
	virtual ~Ipecker_stencil_buffer(){;}
	HEnum get_frame_buffer_object_type() const;
};

PECKER_END

#endif //PECKER_RENDER_BUFFER_H_