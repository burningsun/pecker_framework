/*
 * pecker_render_system_gl.cpp
 *
 *  Created on: 2013-4-30
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_render_system_gl.h"
#include <GLES2/gl2.h>
#include <EGL/egl.h>
PECKER_BEGIN

pecker_render_system_gles2::pecker_render_system_gles2()
{

}
pecker_render_system_gles2::~pecker_render_system_gles2()
{

}
HResult pecker_render_system_gles2::set_render_system_param(const pecker_render_system_param & sys_param)
{
	return P_OK;
}

Ipecker_render_device* pecker_render_system_gles2::open_render_device(Ipecker_window_display* pwindows_display)
{
	return &_M_graphic_device;
}

HResult pecker_render_system_gles2::close_render_device()
{
	return P_OK;
}

HResult pecker_render_system_gles2::resize_render_display(nSize x,nSize y,nSize width,nSize height,Ipecker_window_display* pwindows_display)
{
	return P_OK;
}

HResult pecker_render_system_gles2::swap_frame_buffer()
{
	//eglWaitGL()
	//eglSwapBuffers()
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_render_system_gles2::flush_frame_buffer()
{
	glFlush();
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_render_system_gles2::parse_render_display(Ipecker_window_display* pwindows_display)
{
	return P_OK;
}
HResult pecker_render_system_gles2::resume_render_display(Ipecker_window_display* pwindows_display)
{
	return P_OK;
}
HResult pecker_render_system_gles2::close_render_display(Ipecker_window_display* pwindows_display)
{
	return P_OK;
}

PECKER_END

