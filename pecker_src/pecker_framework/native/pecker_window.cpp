/*
 * pecker_window.cpp
 *
 *  Created on: 2012-11-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#include "pecker_window.h"
#include "pecker_stream.h"
#include "../render/render_system/pecker_render_device.h"

PECKER_BEGIN

#ifdef WINDOWS_PC

static HWND g_main_window_handle = NULL;
static LRESULT WINAPI WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//if (NULL == hwnd)
	//{
	//	return 0;
	//}
	if (WM_CREATE == message)
	{	// Store pointer to Win32Window in user data area
		::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG)(((LPCREATESTRUCT)lParam)->lpCreateParams));
		return 0;
	}

	// look up window instance
	// note: it is possible to get a WM_SIZE before WM_CREATE
	pecker_window_context* pWinForm = (pecker_window_context*)(::GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (null != pWinForm)
	{
		return pecker_window_context::pecker_windows_apps(pWinForm,message,wParam,lParam);
	}

	return ::DefWindowProc(hwnd, message, wParam, lParam);
}


DWORD  WINAPI pecker_render_thread_callback(__in  LPVOID lpParameter)
{
	return pecker_window_context::pecker_render_thread((pecker_window_context*)lpParameter);
}
#endif

static UInt globle_windows_id = 0;
pecker_window_context::pecker_window_context() : _M_perant_context(null),_M_closed(BOOL_FALSE),_M_render_device(null)
{
	_M_window_info._M_window_id = globle_windows_id;
	++globle_windows_id;
	
	_M_window_info._M_is_mul_frame_buffer = BOOL_TRUE;
	_M_window_info._M_resouce_handle = null;
	_M_window_info._M_window_handle = null;
	_M_window_info._M_menu_handle = null;
	_M_window_info._M_visiable = BOOL_TRUE;
	_M_window_info._M_using_render_thread = BOOL_FALSE;
	_M_window_info._M_window_title.init("pfx_win\0\0\0\0\0\0\0\0\0",16);
	
	pecker_write_stream_to_memery write_stream;
	write_stream.bind_write_buffer( (char*)(_M_window_info._M_window_title.get_data() + 7),8);
	write_stream.write_integer(_M_window_info._M_window_id);

	_M_window_info._M_window_param._M_window_style = DEFAULT_WIN_BORDERSTYLE;
	_M_window_info._M_window_param._M_cursor_style = DEFAULT_CURSOR_BORDERSTYLE;
	_M_window_info._M_window_param._M_window_external_style = WIN_EX_APPWINDOW_STYLE;

#ifdef WINDOWS_PC
	_M_window_info._M_is_full_screen = BOOL_FALSE;
	_M_window_info._M_window_param._M_x = ::GetSystemMetrics(SM_CXSCREEN) / 5;
	_M_window_info._M_window_param._M_y = ::GetSystemMetrics(SM_CYSCREEN) / 5;

	_M_render_thread.init_thread(pecker_render_thread_callback,this);
#else
	_M_window_info._M_is_full_screen = BOOL_TRUE;
	_M_window_info._M_window_param._M_x = 0;
	_M_window_info._M_window_param._M_y = 0;
#endif
	_M_window_info._M_window_param._M_width = 800;
	_M_window_info._M_window_param._M_height = 600;


}

pecker_window_context::~pecker_window_context()
{
	//on_parse();
	//on_close();
}

HResult pecker_window_context::on_event(UInt umessage,Long wParam,Long lParam)
{
	return P_OK;
}

HResult pecker_window_context::on_create()
{
	return P_OK;
}
HResult pecker_window_context::on_close()
{
	HResult result_value = this->on_close_frame();

	return result_value;
}

HResult pecker_window_context::on_render()
{
	return P_OK;
}

HResult pecker_window_context::on_parse()
{
	return P_OK;
}

HResult pecker_window_context::on_resume()
{
	return P_OK;
}

HResult pecker_window_context::pecker_windows_apps(pecker_window_context* pwindow_context, UInt umessage,Long wParam,Long lParam)
{
	HResult hresult = P_WAITRESULT;
	
#ifdef WINDOWS_PC

	switch(umessage)
	{
	case WM_CREATE:
		pwindow_context->_M_closed = BOOL_FALSE;
		hresult = pwindow_context->on_create();
		if (P_OK == hresult)
		{
			pecker_critical_lock thread_lock;
			thread_lock.lock(&pwindow_context->_M_render_lock);
			pwindow_context->on_init_view(pwindow_context->_M_window_info._M_window_param._M_x,
																		pwindow_context->_M_window_info._M_window_param._M_y,
																		pwindow_context->_M_window_info._M_window_param._M_width,
																		pwindow_context->_M_window_info._M_window_param._M_height);
			//if (BOOL_TRUE == pwindow_context->_M_window_info._M_using_render_thread)
			//{
			//	// start render thread

			//}
			thread_lock.unlock();
		}
		break;
	case WM_CLOSE:
		pwindow_context->_M_window_info._M_visiable = BOOL_FALSE;
		{
			pecker_critical_lock thread_lock;
			thread_lock.lock(&pwindow_context->_M_render_lock);
			pwindow_context->_M_closed = BOOL_TRUE;
			thread_lock.unlock();
			pwindow_context->_M_render_thread.join_thread(-1);
			hresult = pwindow_context->on_close_frame();
		}
		hresult =  pwindow_context->on_close();
		break;
	case WM_PAINT:
		if (BOOL_TRUE != pwindow_context->_M_window_info._M_using_render_thread)
		{
			hresult = pwindow_context->on_draw_frame();
			if (P_OK == hresult)
			{
				hresult = pwindow_context->on_next_frame(pwindow_context->_M_window_info._M_is_mul_frame_buffer);
			}
		}
		break;
	case WM_SIZE:
		RECT cleint_rect;
		if (::GetClientRect((HWND)(pwindow_context->_M_window_info._M_window_handle),&cleint_rect))
		{
			pecker_critical_lock thread_lock;
			thread_lock.lock(&pwindow_context->_M_render_lock);
			hresult = pwindow_context->on_resize_view(cleint_rect.left,cleint_rect.top,cleint_rect.right - cleint_rect.left,cleint_rect.bottom - cleint_rect.top);
			thread_lock.unlock();
		}
		break;
	case WM_DESTROY:
		{
			if (NULL != g_main_window_handle && 
				((HWND)(pwindow_context->_M_window_info._M_window_handle)) == g_main_window_handle)
			{
				::PostQuitMessage(0);
			}
		}
		break;
	default:
		hresult = pwindow_context->on_event(umessage,wParam,lParam);
		break;
	}
	if (P_OK != hresult || P_FIN != hresult)
	{
		return ::DefWindowProc((HWND)(pwindow_context->_M_window_info._M_window_handle), umessage, wParam, lParam);
	}
#endif

	return hresult;
	
}

HResult pecker_window_context::pecker_render_thread(pecker_window_context* pwindow_context)
{
	//while(1)
	while (BOOL_FALSE == pwindow_context->_M_closed)
	{
		//pecker_critical_lock thread_lock;
		//thread_lock.lock(&pwindow_context->_M_render_lock);
		//if (BOOL_FALSE != pwindow_context->_M_closed)
		//{
		//	break;
		//}
		//thread_lock.unlock();
		
		//pwindow_context->_M_render_lock.enter_critical_section();
		pwindow_context->on_draw_frame();
		pwindow_context->on_next_frame(pwindow_context->_M_window_info._M_is_mul_frame_buffer);
		//pwindow_context->_M_render_lock.leave_critical_section();
	}
	return P_OK;
}

HResult pecker_window_context::attach_graphic_device(PeckerInterface Ipecker_render_device* pdevice)
{
	if (null != pdevice)
	{
		if (null != _M_render_device)
		{
			pecker_render_object* pobject = dynamic_cast<pecker_render_object*>(_M_render_device);
			if (null != pobject)
			{
				pobject->release_this_reference();
			}
		}
		_M_render_device = pdevice;

		return P_OK;
	}
	return P_INVALID_VALUE;
}

nSize pecker_window_context::get_width() const
{
	return _M_window_info._M_window_param._M_width;
}

nSize pecker_window_context::get_height() const
{
	return _M_window_info._M_window_param._M_height;
}

Boolean pecker_window_context::is_visiable() const
{
	return _M_window_info._M_visiable;
}

HResult pecker_window_context::set_visiable(Boolean bVisiable)
{
	_M_window_info._M_visiable = bVisiable;
	return P_OK;
}
	
const pecker_window_info& pecker_window_context::get_window_info() const
{
	return _M_window_info;
}

HResult  pecker_window_context::init_window(const pecker_window_info& window_info)
{
	_M_window_info = window_info;

	return P_OK;
}

Boolean pecker_window_context::is_full_screen() const
{
	return _M_window_info._M_is_full_screen;
}

HResult pecker_window_context::set_full_screen(Boolean bfull_screen_enable)
{
	return P_OK;
}

HResult pecker_window_context::show(Boolean bIs_dialog /* = BOOL_FALSE */)
{

#ifdef WINDOWS_PC
	HWND hWnd = (HWND)_M_window_info._M_window_handle;
	if (null == _M_window_info._M_window_handle)
	{
		WNDCLASS window_class;
		memset(&window_class, 0, sizeof(WNDCLASS));

		DWORD window_style;
		DWORD window_ex_style;
		// 设置窗口类型
		switch (_M_window_info._M_window_param._M_window_style)
		{
		case FIXED_WIN_BORDERSTYLE:
			{
				window_style = WS_BORDER | WS_SYSMENU;
				window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
			}
			break;
		case RESIZEABLE_WIN_BORDERSTYLE:
			{
				window_style = WS_OVERLAPPEDWINDOW;
				window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
			}
			break;
		case DEFAULT_WIN_BORDERSTYLE:
		default :
			{
				window_style = WS_BORDER | WS_SYSMENU;
				window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
			}
			break;
		}

		// 使用默认的鼠标
		switch (_M_window_info._M_window_param._M_cursor_style)
		{
		case DEFAULT_CURSOR_BORDERSTYLE:
		default:
			{
				window_class.hCursor = ::LoadCursor(NULL, IDC_ARROW);
			}
			break;
		}

		// 给定一个注册窗口时使用的名字
		window_class.lpszClassName = _M_window_info._M_window_title.get_data();


		switch (_M_window_info._M_window_param._M_window_external_style)
		{
		case WIN_EX_APPWINDOW_STYLE:
			{
				window_ex_style = WS_EX_APPWINDOW;
			}
			break;
		default:
			{
				window_ex_style = WS_EX_APPWINDOW;
			}
			break;
		}

		// 设置信息处理函数为WndProc
		window_class.lpfnWndProc = WndProc;
		// 获得目前运行的程序
		window_class.hInstance = ::GetModuleHandle(NULL);
		// 向操作系统注册一个新的窗口
		if (0 == ::RegisterClass(&window_class))
		{
			return P_ERR;
		}

		// 计算窗口的边线会占掉的点数, 必要时要增加窗口大小
		RECT window_rect;
		::SetRect(&window_rect, 
			_M_window_info._M_window_param._M_x,
			_M_window_info._M_window_param._M_y,
			_M_window_info._M_window_param._M_x + _M_window_info._M_window_param._M_width,
			_M_window_info._M_window_param._M_y + _M_window_info._M_window_param._M_height);
			
		::AdjustWindowRect(&window_rect, window_style, FALSE);

		HWND hWndParent = NULL;
		if (_M_perant_context)
		{
			hWndParent = (HWND)(_M_perant_context->_M_window_info._M_window_handle);
		}
		// 准备工作完成, 打开一个窗口.
		hWnd = ::CreateWindowEx(
			window_ex_style,
			_M_window_info._M_window_title.get_data(),
			_M_window_info._M_window_title.get_data(),
			window_style,
			window_rect.left,	// x
			window_rect.top,	// y
			window_rect.right - window_rect.left,	// width
			window_rect.bottom - window_rect.top,	// height
			hWndParent,
			(HMENU)_M_window_info._M_menu_handle,
			window_class.hInstance,
			this
			);
		_M_window_info._M_window_handle = (Handle)hWnd;
	   }
		
		if (NULL != hWnd)
		{
			DWORD show_style = SW_NORMAL;
			if (_M_window_info._M_visiable != BOOL_TRUE)
			{
				show_style = SW_HIDE;
			}
			if (::ShowWindow(hWnd,show_style))
			{
				_M_render_thread.start_thread();
			}
			::SetActiveWindow(hWnd);
		}
		else
		{
			_M_window_info._M_visiable = BOOL_FALSE;
		}

		if (BOOL_TRUE == bIs_dialog)
		{
			MSG msg;
			DWORD msg_result = ::GetMessage( &msg, null, 0, 0 );

			while (BOOL_FALSE == _M_closed && 0 != msg_result)
			{
				if (-1 == msg_result)
				{
					// handle the error and possibly exit
					break;
				}
				else
				{
					::TranslateMessage(&msg); 
					::DispatchMessage(&msg); 
				}
				msg_result = ::GetMessage( &msg, null, 0, 0 );
			}
		}
#endif
		
	
	return P_OK;
}

HResult pecker_window_context::close()
{
	return P_OK;
}



static pecker_string g_str_current_directory;
HResult pecker_program_apps::init_apps()
{
#ifdef WINDOWS_PC
	char path_chars[2048] = {0};
	DWORD length = 2048;
	if (::GetCurrentDirectory(length,path_chars))
	{
		g_str_current_directory.init(path_chars,strlen(path_chars));
		return P_OK;
	}
	else
	{
		return P_FAIL;
	}
#endif
	return P_OK;
}

HResult pecker_program_apps::execute_program(pecker_window_context* pwindow_context,const pecker_string &str_cmd_params)
{
	if (null != g_main_window_handle)
	{
		return P_UNIQUE_ERR;
	}
	if (null != pwindow_context)
	{
		if (P_OK == pwindow_context->show())
		{
			g_main_window_handle = (HWND)(pwindow_context->get_window_info()._M_window_handle);
		}
#ifdef WINDOWS_PC
		MSG msg;
		SInt bRet;

		while( (bRet = ::GetMessage( &msg, null, 0, 0 )) != 0)
		{ 
			if (bRet == -1)
			{
				// handle the error and possibly exit
				break;
			}
			else
			{
				::TranslateMessage(&msg); 
				::DispatchMessage(&msg); 
			}
		} 
#endif
		return P_OK;
	}

	return P_ERR;
	
}

HResult pecker_program_apps::execute_program(pecker_string str_file_path,const pecker_string &str_cmd_params)
{
	return P_OK;
}

const pecker_string& pecker_program_apps::get_current_directory()
{
	return g_str_current_directory;
}

PECKER_END
