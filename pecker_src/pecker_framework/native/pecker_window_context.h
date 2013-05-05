/*
 * pecker_window_context.h
 *
 *  Created on: 2013-5-5
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_WINDOW_CONTEXT_H_
#define PECKER_WINDOW_CONTEXT_H_

#include "pecker_window.h"

PECKER_BEGIN

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
	virtual HResult pixmap_copy();
	virtual HResult load_render_resource();
	virtual HResult release_render_resource();

	virtual HResult init_render_resource();
	virtual HResult deinit_render_resource();
	

	HResult attach_graphic_device(PeckerInterface Ipecker_render_device* pdevice);
public:
	nSize get_width() const;
	nSize get_height() const;
	virtual Handle get_native_window() const;
	virtual Handle get_native_display() const;
	virtual Handle get_native_pixelmap() const;
	virtual HResult set_buffers_geometry(nINDEX visual_id) ;
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
#endif // PECKER_WINDOW_CONTEXT_H_
