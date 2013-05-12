
/*
 * pecker_window.h
 *
 *  Created on: 2012-11-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_WINDOW_H_
#define PECKER_WINDOW_H_

#include "../CPeckerObject.h"
#include "../data/pecker_string.h"
#include "pecker_thread.h"
PECKER_BEGIN

typedef enum
{
	DEFAULT_WIN_BORDERSTYLE = 0,
	FIXED_WIN_BORDERSTYLE,
	RESIZEABLE_WIN_BORDERSTYLE,
	WIN_BORDERSTYLE_COUNT
}WIN_BORDER_STYLE;

typedef enum
{
	DEFAULT_CURSOR_BORDERSTYLE = 0,
	CURSOR_BORDERSTYLE_COUNT
}CURSOR_BORDER_STYLE;

typedef enum
{
	DEFAULT_WINDOW_STATE = 0,
	WINDOW_STATE_COUNT
}WINDOW_STATE;

typedef enum
{
	WIN_EX_APPWINDOW_STYLE = 0,
	WIN_EX_APPWINDOW_STYLE_COUNT
}WINDOW_EX_STYLE;

struct pecker_window_param
{
	UInt _M_window_style;
	UInt _M_window_external_style;
	UInt _M_cursor_style;
	nSize _M_width;
	nSize _M_height;
	nINDEX _M_x;
	nINDEX _M_y;
};
struct pecker_window_info
{
	UInt			_M_window_id;
	Handle	_M_window_handle;
	Handle	_M_pixmap_handle;
	Handle	_M_resouce_handle;
	Handle	_M_menu_handle;
	Boolean _M_is_full_screen;
	Boolean _M_visiable;
	Boolean _M_is_mul_frame_buffer;
	Boolean _M_using_render_thread;
	pecker_window_param _M_window_param;
	pecker_string _M_window_title;
	pecker_string _M_render_system_name;
};

PeckerInterface Ipecker_window_display
{
	virtual ~Ipecker_window_display(){;}
	virtual HResult on_init_view(nSize x,nSize y,nSize width,nSize height) = 0;
	virtual HResult on_resize_view(nSize x,nSize y,nSize width,nSize height) = 0;
	virtual HResult on_draw_frame() = 0;
	
	virtual HResult on_next_frame(Boolean  bswap_buffer) = 0;

	virtual HResult on_parse_frame() = 0;
	virtual HResult on_close_frame() = 0;
	virtual HResult on_resume_frame() = 0;
	
	virtual HResult load_render_resource() = 0;
	virtual HResult release_render_resource() = 0;

	virtual HResult init_render_resource() = 0;
	virtual HResult deinit_render_resource() = 0;
	
	virtual HResult attach_graphic_device(PeckerInterface Ipecker_render_device* pdevice) = 0;

	virtual nSize get_width() const = 0;
	virtual nSize get_height() const = 0;

	virtual Handle get_native_window() const = 0;
	virtual Handle get_native_display() const = 0;
	virtual Handle get_native_pixelmap() const = 0;
	virtual HResult set_buffers_geometry(nINDEX visual_id) = 0;

	virtual HResult pixmap_copy() = 0;
};


PECKER_END
#endif
