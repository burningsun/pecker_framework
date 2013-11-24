/*
 * pfx_renderbuffer_opengles2.cpp
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_renderbuffer_opengles.h"

PECKER_BEGIN


CPfx_color_buffer_opengles2::~CPfx_color_buffer_opengles2() 
{
	;
};
pfx_result_t CPfx_color_buffer_opengles2::init_color_buffer (PFX_COLOR_BUFFER_TYPE_t type_,
		pfx_usize_t width,pfx_usize_t height)
{
	return 0;
}

pfx_result_t CPfx_color_buffer_opengles2::dispose_color_buffer ()
{
	return 0;
}

pfx_long_t CPfx_color_buffer_opengles2::get_color_buffer_target ()
{
	return 0;
}

pfx_usize_t CPfx_color_buffer_opengles2::get_width () const
{
	return 0;
}
pfx_usize_t CPfx_color_buffer_opengles2::get_height () const
{
	return 0;
}
pfx_result_t CPfx_color_buffer_opengles2::get_format (PFX_COLOR_BUFFER_TYPE_t& PARAM_OUT format_)
{
	return 0;
}

CPfx_depth_buffer_opengles2::~CPfx_depth_buffer_opengles2() 
{
	;
}

pfx_result_t CPfx_depth_buffer_opengles2::init_depth_buffer (PFX_DEPTH_BUFFER_TYPE_t type_,
		pfx_usize_t width,pfx_usize_t height)
{
	return 0;
}

pfx_result_t CPfx_depth_buffer_opengles2::dispose_depth_buffer ()
{
	return 0;
}

pfx_long_t CPfx_depth_buffer_opengles2::get_depth_buffer_target ()
{
	return 0;
}

pfx_usize_t CPfx_depth_buffer_opengles2::get_width () const
{
	return 0;
}

pfx_usize_t CPfx_depth_buffer_opengles2::get_height () const
{
	return 0;
}
pfx_result_t CPfx_depth_buffer_opengles2::get_format (PFX_DEPTH_BUFFER_TYPE_t& PARAM_OUT format_)
{
	return 0;
};

CPfx_stencil_buffer_opengles2::~CPfx_stencil_buffer_opengles2() 
{
	;
}

pfx_result_t CPfx_stencil_buffer_opengles2::init_stencil_buffer (PFX_STENCIL_BUFFER_TYPE_t type_,
		pfx_usize_t width,pfx_usize_t height)
{
	return 0;
}

pfx_result_t CPfx_stencil_buffer_opengles2::dispose_stencil_buffer ()
{
	return 0;
}

pfx_long_t CPfx_stencil_buffer_opengles2::get_stencil_buffer_target ()
{
	return 0;
}

pfx_usize_t CPfx_stencil_buffer_opengles2::get_width () const
{
	return 0;
}
pfx_usize_t CPfx_stencil_buffer_opengles2::get_height () const
{
	return 0;
}
pfx_result_t CPfx_stencil_buffer_opengles2::get_format (PFX_STENCIL_BUFFER_TYPE_t& PARAM_OUT format_)
{
	return 0;
};

PECKER_END
