/*
 * pecker_render_system.h
 *
 *  Created on: 2013-4-7
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_RENDER_SYSTEM_H_
#define PECKER_RENDER_SYSTEM_H_

#include "../pecker_render_object.h"
#include "../pecker_render_device.h"
#include "../../native/pecker_window.h"

PECKER_BEGIN

struct pecker_render_system_param
{

};

struct pecker_render_system_info
{

};

PeckerInterface Ipecker_render_system
{
	virtual ~Ipecker_render_system(){;}
	virtual HResult set_render_system_param(const pecker_render_system_param & sys_param) = 0;
	virtual Ipecker_render_device* create_render_device(Ipecker_window_display* pwindows_display) = 0;
	
	virtual HResult resize_render_display(nSize x,nSize y,nSize width,nSize height,Ipecker_window_display* pwindows_display) = 0;

	virtual HResult swap_frame_buffer() = 0;
	virtual HResult flush_frame_buffer() = 0;

	virtual HResult parse_render_display(Ipecker_window_display* pwindows_display) = 0;
	virtual HResult resume_render_display(Ipecker_window_display* pwindows_display) = 0;
	virtual HResult close_render_display(Ipecker_window_display* pwindows_display) = 0;

	virtual HResult get_system_info(pecker_render_system_info& P_OUT system_info) = 0;
};


PECKER_END

#endif //PECKER_RENDER_SYSTEM_H_