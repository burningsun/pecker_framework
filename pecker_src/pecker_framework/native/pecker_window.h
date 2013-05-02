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
	UInt _M_width;
	UInt _M_height;
	UInt _M_x;
	UInt _M_y;
};
struct pecker_window_info
{
	UInt			_M_window_id;
	Handle	_M_window_handle;
	Handle	_M_resouce_handle;
	Handle	_M_menu_handle;
	Boolean _M_is_full_screen;
	Boolean _M_visiable;
	Boolean _M_is_mul_frame_buffer;
	Boolean _M_using_render_thread;
	pecker_window_param _M_window_param;
	pecker_string _M_window_title;
};

class pecker_window_context;

//PeckerInterface pecker_window_process
//{
//	virtual ~pecker_window_process(){;}
//	virtual HResult on_windowproc(pecker_window_context* pwindow_context, UInt umessage,Long wParam,Long lParam) = 0;
//};

PeckerInterface Ipecker_window_display //: public pecker_window_process
{
	virtual ~Ipecker_window_display(){;}
	virtual HResult on_init_view(nSize x,nSize y,nSize width,nSize height) = 0;
	virtual HResult on_resize_view(nSize x,nSize y,nSize width,nSize height) = 0;
	virtual HResult on_draw_frame() = 0;
	
	virtual HResult on_next_frame(Boolean  bswap_buffer) = 0;

	virtual HResult on_parse_frame() = 0;
	virtual HResult on_close_frame() = 0;
	virtual HResult on_resume_frame() = 0;

	virtual HResult attach_graphic_device(PeckerInterface Ipecker_render_device* pdevice) = 0;

	virtual nSize get_width() const = 0;
	virtual nSize get_height() const = 0;

	//virtual HResult on_render() = 0;
};

class pecker_window_context : protected Ipecker_window_display
{
public:
	pecker_window_context();
	virtual ~pecker_window_context();
protected:
	pecker_window_context* _M_perant_context;
	Boolean _M_closed;
	pecker_window_info _M_window_info;
	PeckerInterface Ipecker_render_device* _M_render_device;

	pecker_thread					_M_render_thread;
	pecker_critical_section  _M_render_lock;
protected:
	virtual HResult on_event(UInt umessage,Long wParam,Long lParam);
	virtual HResult on_create();
	virtual HResult on_close();
	virtual HResult on_render();
	virtual HResult on_parse();
	virtual HResult on_resume();
	HResult attach_graphic_device(PeckerInterface Ipecker_render_device* pdevice);
public:
	nSize get_width() const;
	nSize get_height() const;
public:
	static HResult pecker_windows_apps(pecker_window_context* pwindow_context, UInt umessage,Long wParam,Long lParam);
	static HResult pecker_render_thread(pecker_window_context* pwindow_context);
public:
	virtual Boolean is_visiable() const;
	virtual HResult set_visiable(Boolean bVisiable);
	const pecker_window_info& get_window_info() const;
	virtual HResult  init_window(const pecker_window_info& window_info);
	virtual Boolean is_full_screen() const;
	virtual HResult set_full_screen(Boolean bfull_screen_enable);
	virtual HResult show(Boolean bIs_dialog = BOOL_FALSE);
	virtual HResult close();
	
};

template< class graphic_driver >
class pecker_window_form : public pecker_window_context
{
protected:
	graphic_driver _M_graphic_driver;
protected:
	HResult on_init_view(nSize x,nSize y,nSize width,nSize height)
	{
		return 0;
	}
	HResult on_resize_view(nSize x,nSize y,nSize width,nSize height)
	{
		return 0;
	}
	HResult on_draw_frame()
	{
		return 0;
	}
	HResult on_next_frame(Boolean  bswap_buffer)
	{
		return 0;
	}
	HResult on_parse_frame()
	{
		return 0;
	}
	HResult on_close_frame()
	{
		return 0;
	}
	HResult on_resume_frame()
	{
		return 0;
	}
	//HResult on_windowproc(pecker_window_context* pwindow_context, UInt umessage,Long wParam,Long lParam)
	//{
	//	return P_OK;
	//}
public:
	graphic_driver* get_graphic_driver() const
	{
		return &_M_graphic_driver;
	}
};

class pecker_program_apps
{
public:
	static HResult init_apps();
	static HResult execute_program(pecker_window_context* pwindow_context,const pecker_string& str_cmd_params);
	static HResult execute_program(pecker_string str_file_path,const pecker_string& str_cmd_params);
	static const pecker_string& get_current_directory();
};
PECKER_END
#endif