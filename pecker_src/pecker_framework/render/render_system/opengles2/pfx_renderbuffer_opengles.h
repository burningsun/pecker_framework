/*
 * pfx_renderbuffer_opengles2.h
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDERBUFFER_OPENGLES2_H_
#define		PFX_RENDERBUFFER_OPENGLES2_H_

#include "../pfx_renderbuffer.h"

PECKER_BEGIN

class CPfx_color_buffer_opengles2 : public Ipfx_color_buffer
{
public:
	virtual pfx_result_t init_color_buffer (PFX_COLOR_BUFFER_TYPE_t type_,
		pfx_usize_t width,pfx_usize_t height);

	virtual pfx_result_t dispose_color_buffer ();

	virtual pfx_long_t get_color_buffer_target () ;

	virtual pfx_usize_t get_width () const;
	virtual pfx_usize_t get_height () const;
	virtual pfx_result_t get_format (PFX_COLOR_BUFFER_TYPE_t& PARAM_OUT format_);
	//////////////////////////////////
	virtual ~CPfx_color_buffer_opengles2();
};

class CPfx_depth_buffer_opengles2 : public Ipfx_depth_buffer
{
public:
	virtual pfx_result_t init_depth_buffer (PFX_DEPTH_BUFFER_TYPE_t type_,
		pfx_usize_t width,pfx_usize_t height);

	virtual pfx_result_t dispose_depth_buffer ();

	virtual pfx_long_t get_depth_buffer_target ();

	virtual pfx_usize_t get_width () const;
	virtual pfx_usize_t get_height () const;
	virtual pfx_result_t get_format (PFX_DEPTH_BUFFER_TYPE_t& PARAM_OUT format_);
	//////////////////////////////////
	virtual ~CPfx_depth_buffer_opengles2();
};

class CPfx_stencil_buffer_opengles2 : public Ipfx_stencil_buffer
{
public:
	virtual pfx_result_t init_stencil_buffer (PFX_STENCIL_BUFFER_TYPE_t type_,
		pfx_usize_t width,pfx_usize_t height);

	virtual pfx_result_t dispose_stencil_buffer ();

	virtual pfx_long_t get_stencil_buffer_target ();

	virtual pfx_usize_t get_width () const;
	virtual pfx_usize_t get_height () const;
	virtual pfx_result_t get_format (PFX_STENCIL_BUFFER_TYPE_t& PARAM_OUT format_);
	//////////////////////////////////
	virtual ~CPfx_stencil_buffer_opengles2();
};

PECKER_END

#endif			//PFX_RENDERBUFFER_OPENGLES2_H_
