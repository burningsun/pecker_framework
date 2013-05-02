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
#include "pecker_render_device.h"
#include "../../native/pecker_window.h"

PECKER_BEGIN

struct pecker_render_system_param
{
	BitField _M_color_buffer;//   bit order 0~31bit, 0~7 luminance size 8~15 alpha size 
												//		16~23 alpha mask size,24~31 color buffer type
	BitField _M_color_bpp; //  bit order 0~31bit , 0~7 red 8~15 green 16~23 blue 24~31 alpha
	BitField _M_render_buffer; //   bit order 0~31bit , 0~15 reserved 16~23 depth buffer size 24~31 stcencil buffer size
	BitField _M_config_mask; //  bit order 0~31bit,0 need Pbuffer bit , 1 need pixmap bit, 2 conformant bit,3 max pbuffer width
												   //  4 max pbuffer height, 5 max pbuffer pixels,6 bind to  texture rgb bit,7 bind to texture rgba bit,
												  // 8 mip texture bit , 9 10 11texture target
												  // 12~19 texture format
	BitField _M_sample; //    bit order 0~31bit , 0~15 sample per pixel  16~31 number of multisample buffers
	BitField _M_transparent; //   bit order 0~31bit , 0~7 transparent type 8~15 red 16~23 green 24~31 blue
	nINDEX _M_config_ID;
	nSize  _M_pbuffer_width;
	nSize  _M_pbuffer_height;

	nSize	_M_back_buffer_size;
	PVoid _M_pback_buffer;
};
//struct pecker_render_device_info
//{
//
//};
enum RENDER_SYS_PARAM_COLOR_BUFFER_TYPE
{
	RSYS_RGB_BUFFER = 0,
	RSYS_LUMINANCE_BUFFER,

	RENDER_SYS_PARAM_COLOR_BUFFER_TYPE_COUNT
};


PeckerInterface Ipecker_render_system
{
	virtual ~Ipecker_render_system(){;}
	virtual HResult set_render_system_param(const pecker_render_system_param & sys_param) = 0;
	virtual Ipecker_render_device* open_render_device(Ipecker_window_display* pwindows_display) = 0;
	virtual HResult close_render_device() = 0;
	
	virtual HResult resize_render_display(nSize x,nSize y,nSize width,nSize height,Ipecker_window_display* pwindows_display) = 0;

	virtual HResult swap_frame_buffer() = 0;
	virtual HResult flush_frame_buffer() = 0;

	virtual HResult parse_render_display(Ipecker_window_display* pwindows_display) = 0;
	virtual HResult resume_render_display(Ipecker_window_display* pwindows_display) = 0;
	virtual HResult close_render_display(Ipecker_window_display* pwindows_display) = 0;

	//virtual HResult get_system_info(pecker_render_system_info& P_OUT system_info) = 0;
};

class pecker_render_system_factory
{
public:
	static Ipecker_render_system* create_render_system(const pecker_string &render_system_name);
	static void release_render_system(Ipecker_render_system* &prender_system);
};

PECKER_END

#endif //PECKER_RENDER_SYSTEM_H_