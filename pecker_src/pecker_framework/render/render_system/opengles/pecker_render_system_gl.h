/*
 * pecker_render_system_gl.h
 *
 *  Created on: 2013-4-30
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_RENDER_SYSTEM_GL_H_
#define PECKER_RENDER_SYSTEM_GL_H_
#include "pecker_opengles_object.h"
#include "../pecker_render_system.h"
#include "pecker_opengles_device.h"
PECKER_BEGIN



class pecker_render_system_gles2 : public Ipecker_render_system,public virtual pecker_opengles_v2_object
{
private:
	pecker_render_device_gles2 _M_graphic_device;
public:
	pecker_render_system_gles2();
	virtual ~pecker_render_system_gles2();
	HResult set_render_system_param(const pecker_render_system_param & sys_param);
	Ipecker_render_device* open_render_device(Ipecker_window_display* pwindows_display);
	HResult close_render_device();
	
	HResult resize_render_display(nSize x,nSize y,nSize width,nSize height,Ipecker_window_display* pwindows_display);

	HResult swap_frame_buffer();
	HResult flush_frame_buffer();

	HResult parse_render_display(Ipecker_window_display* pwindows_display);
	HResult resume_render_display(Ipecker_window_display* pwindows_display);
	HResult close_render_display(Ipecker_window_display* pwindows_display);
};



PECKER_END

#endif //PECKER_RENDER_SYSTEM_H_