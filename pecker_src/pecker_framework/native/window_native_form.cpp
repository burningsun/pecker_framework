/*
* window_native_form.cpp
*
*  Created on: 2014-7-30
*      Author: 李镇城  （ cut / cutxyz）
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/

#include "window_native_form.h"
#include "window_msgcode_def.h"
#if (OS_CONFIG == OS_WINDOWS)


PECKER_BEGIN

//HWND window_native_form::hwnd_main = null;

LRESULT WINAPI window_native_form::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (NULL == hwnd)
	{
		return 0;
	}

	if (WM_CREATE == message)
	{	// Store pointer to Win32Window in user data area
		::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG)(((LPCREATESTRUCT)lParam)->lpCreateParams));
		//return 0;
	}



	// look up window instance
	// note: it is possible to get a WM_SIZE before WM_CREATE
	window_native_form* winform_ptr = (window_native_form*)(::GetWindowLongPtr(hwnd, GWLP_USERDATA));
	//if (null == hwnd_main)
	//{
	//	hwnd_main = hwnd;
	//}
	if (winform_ptr)
	{
		return 	winform_ptr->on_message(message, wParam, lParam);
	}

	return ::DefWindowProc(hwnd, message, wParam, lParam);
}

window_native_form::window_native_form() :m_hwmd(null),
m_hdc(null),
m_pixelmap(null),
m_activity_status(PFX_ACTIVE_NO_INIT),
m_component_ptr(null),
m_visiable(false),
m_started_window(false),
m_parent_form_ptr(null),
m_dlg_result(0),
m_benter_size_move(false),
m_bview_change(false)
{
	m_msg_trans_proxy.m_object_ptr		= this;
	m_msg_trans_proxy.m_callback		= &window_native_form::on_message_translate;
	m_msg_trans_proxy.m_proxy_status	= null;
	;
}

window_native_form::~window_native_form()
{
	dispose();
}

result_t window_native_form::listen_message()
{
	result_t status;
	MSG msg;
	DWORD msg_result;
	HWND hwnd;
	
	hwnd		= null;	 // recv all hwnd in process;
	status		= PFX_STATUS_OK;
	msg_result	= ::GetMessage(&msg, hwnd, 0, 0);

	while (0 != msg_result)
	{
		if (-1 == msg_result)
		{
			// handle the error and possibly exit
			status = PFX_STATUS_ERROR_;
			break;
		}
		else
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		msg_result = ::GetMessage(&msg, hwnd, 0, 0);
	}
	m_started_window = false;
	return status;
}



LRESULT	window_native_form::on_message(UINT message, WPARAM wParam, LPARAM lParam)
{
	result_t status;
	RECT client_rect;
	status = PFX_STATUS_FIN;
	if (m_component_ptr)
	{
		switch (message)
		{
		case WM_CREATE:
			status = PFX_STATUS_OK;	
			m_benter_size_move = false;
			m_bview_change = false;
			m_visiable = true;
			break;
		case WM_ENTERSIZEMOVE:
			m_benter_size_move = true;
			break;
		case WM_EXITSIZEMOVE:
			m_benter_size_move = false;
			if (m_bview_change)
			{
				m_bview_change = false;
				::GetClientRect(m_hwmd, &client_rect);
				m_component_ptr->on_modify_view();

				if (m_hdc)
				{
					::ReleaseDC(m_hwmd, m_hdc);
					m_hdc = null;
				}
				if (m_pixelmap)
				{
					::DeleteObject(m_pixelmap);
					m_pixelmap = null;
				}
				m_hdc = ::GetDC(m_hwmd);
				if (m_init_state.m_pixlmap)
				{
					m_pixelmap = ::CreateCompatibleBitmap(m_hdc,
						m_init_state.m_windows_rect.m_width,
						m_init_state.m_windows_rect.m_height);
				}
				::GetClientRect(m_hwmd, &client_rect);
				m_init_state.m_windows_rect.m_x = client_rect.left;
				m_init_state.m_windows_rect.m_y = client_rect.top;
				m_init_state.m_windows_rect.m_width = client_rect.right - client_rect.left;
				m_init_state.m_windows_rect.m_height = client_rect.bottom - client_rect.top;


				m_component_ptr->on_finish_modify_view();
				m_activity_status = PFX_ACTIVE_RESUME;
			}


			
			break;
		case WM_SIZE:
			m_bview_change = true;
			// 第一次 设置窗口的大小
			if (PFX_ACTIVE_CREATE == m_activity_status ||
				PFX_ACTIVE_RESTART == m_activity_status)
			{
				m_bview_change = false;
				::GetClientRect(m_hwmd, &client_rect);

				if (m_hdc)
				{
					::ReleaseDC(m_hwmd, m_hdc);
					m_hdc = null;
				}
				if (m_pixelmap)
				{
					::DeleteObject(m_pixelmap);
					m_pixelmap = null;
				}
				m_hdc = ::GetDC(m_hwmd);
				if (m_init_state.m_pixlmap)
				{
					m_pixelmap = ::CreateCompatibleBitmap(m_hdc,
						m_init_state.m_windows_rect.m_width,
						m_init_state.m_windows_rect.m_height);
				}

				m_init_state.m_windows_rect.m_x = client_rect.left;
				m_init_state.m_windows_rect.m_y = client_rect.top;
				m_init_state.m_windows_rect.m_width = client_rect.right - client_rect.left;
				m_init_state.m_windows_rect.m_height = client_rect.bottom - client_rect.top;



				m_component_ptr->on_start(this);
				m_activity_status = PFX_ACTIVE_START;
			}
			// 非第一次改变窗口的大小
			else if (!m_benter_size_move)
			{
				::PostMessage(m_hwmd, WM_EXITSIZEMOVE, null, null);
			}
			status = PFX_STATUS_OK;
			break;

		case WM_CLOSE:
			m_component_ptr->on_stop();
			m_activity_status = PFX_ACTIVE_STOP;

			//status = PFX_STATUS_OK;
			break;
		case WM_DESTROY:
			m_component_ptr->on_destroy();
			m_activity_status = PFX_ACTIVE_DESTROY;
			status = PFX_STATUS_OK;
			::PostQuitMessage(0);
			m_hwmd = null;
			break;
		case WM_SHOW_PARSE:
			m_visiable = false;
			//m_component_ptr->on_parse();
			status = PFX_STATUS_OK;
			break;
		case WM_SHOW_RESUM:
			m_visiable = true;
			//m_component_ptr->on_resume();
			status = PFX_STATUS_OK;
			break;
		case WM_SHOW_RESTART:
			if (m_hdc)
			{
				::ReleaseDC(m_hwmd, m_hdc);
				m_hdc = null;
			}
			if (m_pixelmap)
			{
				::DeleteObject(m_pixelmap);
				m_pixelmap = null;
			}
			m_hdc = ::GetDC(m_hwmd);
			if (m_init_state.m_pixlmap)
			{
				m_pixelmap = ::CreateCompatibleBitmap(m_hdc,
					m_init_state.m_windows_rect.m_width,
					m_init_state.m_windows_rect.m_height);
			}
			m_visiable = true;
			::GetClientRect(m_hwmd, &client_rect);
			m_init_state.m_windows_rect.m_x = client_rect.left;
			m_init_state.m_windows_rect.m_y = client_rect.top;
			m_init_state.m_windows_rect.m_width = client_rect.right - client_rect.left;
			m_init_state.m_windows_rect.m_height = client_rect.bottom - client_rect.top;
			m_component_ptr->on_restart();
			m_activity_status = PFX_ACTIVE_RESTART;
			status = PFX_STATUS_OK;
			break;
		default:
			status = m_component_ptr->on_event(message, (long_t)wParam, (long_t)lParam);
			break;
		}
	}
	if (PFX_STATUS_FIN == status)
	{
		return ::DefWindowProc(m_hwmd, message, wParam, lParam);
	}
	else
	{
		return 0;
	}
	
}


result_t window_native_form::init(IActivity_component* activity_ptr,
	window_native_form* parent_form_ptr //= null
	)
{
	if (!activity_ptr)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	if (m_component_ptr && (PFX_ACTIVE_NO_INIT != m_activity_status ||
		PFX_ACTIVE_DESTROY != m_activity_status)
		)
	{
		return PFX_STATUS_DENIED;
	}
	m_component_ptr		= activity_ptr;
	m_activity_status	= PFX_ACTIVE_NO_INIT;
	m_init_state.m_windows_rect.m_x			= 100;
	m_init_state.m_windows_rect.m_y			= 100;
	m_init_state.m_windows_rect.m_width		= 800;
	m_init_state.m_windows_rect.m_height	= 600;

	m_component_ptr->on_create(m_init_state);

	if (m_init_state.m_windows_rect.m_width > 0 &&
		m_init_state.m_windows_rect.m_height > 0)
	{
		m_activity_status = PFX_ACTIVE_CREATE;
		m_parent_form_ptr = parent_form_ptr;
		return PFX_STATUS_OK;
	}
	else
	{
		m_component_ptr = null;
		return PFX_STATUS_FAIL;
	}
}
	
result_t window_native_form::dispose()
{
	m_started_window = false;
	return close();
}

	
result_t window_native_form::create()
{
	if (PFX_ACTIVE_CREATE != m_activity_status)
	{
		return PFX_STATUS_DENIED;
	}

	WNDCLASS window_class;
	memset(&window_class, 0, sizeof(WNDCLASS));

	DWORD window_style;
	DWORD window_ex_style;

	window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	// 设置窗口类型
	if (m_init_state.m_native_style)
	{
		window_style = m_init_state.m_style;
		window_ex_style = m_init_state.m_extern_style;
	}
	else
	{
		window_ex_style = WS_EX_APPWINDOW;
		if (m_init_state.m_fixed_window)
		{
			window_style = WS_BORDER | WS_SYSMENU;
		}
		else
		{
			window_style = WS_OVERLAPPEDWINDOW;
		}

	}

	window_class.hCursor = ::LoadCursor(NULL, IDC_ARROW);


	// 给定一个注册窗口时使用的名字
	cstring_ascii_t& strtitle = m_init_state.m_strtitle;
	uindex_t last_index = strtitle.get_length() - 1;
	const cstring_ascii_t::element_t* last_char_ptr = strtitle.get_charbuffer_at(last_index);

	const char_t* strtitle_ptr = null;
	
	if (strtitle.get_length())
	{
		strtitle_ptr = strtitle.get_string();
	}
	
	if (last_char_ptr && 0 != *last_char_ptr)
	{
		cstring_ascii_t::element_t last_char = 0;
		last_index = strtitle.get_length();
		strtitle.resize_string(last_index + 1);
		strtitle.set_charbuffer_at(last_index, &last_char, sizeof(cstring_ascii_t::element_t));
		strtitle_ptr = strtitle.get_string();
	}

	window_class.lpszClassName = strtitle_ptr;

	// 设置信息处理函数为WndProc
	window_class.lpfnWndProc = WndProc;
	// 获得目前运行的程序
	window_class.hInstance = ::GetModuleHandle(NULL);
	// 向操作系统注册一个新的窗口
	if (0 == ::RegisterClass(&window_class))
	{
		return PFX_STATUS_FAIL;
	}

	// 计算窗口的边线会占掉的点数, 必要时要增加窗口大小
	RECT window_rect;
	::SetRect(&window_rect,
		m_init_state.m_windows_rect.m_x,
		m_init_state.m_windows_rect.m_y,
		m_init_state.m_windows_rect.m_x + m_init_state.m_windows_rect.m_width,
		m_init_state.m_windows_rect.m_y + m_init_state.m_windows_rect.m_height);

	::AdjustWindowRect(&window_rect, window_style, FALSE);

	HWND parent_hwnd;
	if (m_parent_form_ptr)
	{
		parent_hwnd = m_parent_form_ptr->m_hwmd;
	}
	else
	{
		parent_hwnd = null;
	}
	// 准备工作完成, 打开一个窗口.
	m_hwmd = ::CreateWindowEx(
		window_ex_style,
		strtitle_ptr,
		strtitle_ptr,
		window_style,
		window_rect.left,	// x
		window_rect.top,	// y
		window_rect.right - window_rect.left,	// width
		window_rect.bottom - window_rect.top,	// height
		parent_hwnd,
		null,
		window_class.hInstance,
		this
		);

	if (m_hwmd)
	{
		m_started_window = true;
		return PFX_STATUS_OK;
	}
	else
	{
		m_started_window = false;
		return PFX_STATUS_FAIL;
	}
}

long window_native_form::on_message_translate(proxy_status_t* __proxy_status_ptr)
{
	
	return show_dialog();
}
	
void window_native_form::show(bool fullscreen //= false
	)
{
	if (m_hwmd)
	{
		return;
	}
	m_msg_trans_thread.start_thread(&m_msg_trans_proxy);

}
	
result_t window_native_form::show_dialog(bool fullscreen //= false
	)
{
	if (m_hwmd)
	{
		return PFX_STATUS_DENIED;
	}
	result_t status;
	status = create();
	if (m_hwmd)
	{		
		if (fullscreen)
		{
			::ShowWindow(m_hwmd, SW_MAXIMIZE);
		}
		else
		{
			::ShowWindow(m_hwmd, SW_NORMAL);
		}
		this->listen_message();
		
	}

	return PFX_STATUS_OK;
}

result_t window_native_form::close()
{
	if (m_started_window)
	{
		::PostMessage(m_hwmd, WM_CLOSE, null, null);
	}
	m_msg_trans_thread.wait_thread_exit(5000);
	return PFX_STATUS_OK;
}
	
result_t window_native_form::set_visiable(bool bvisiable, 
	bool bfullscreen //= false
	)
{	
	if (!m_hwmd)
	{
		return PFX_ACTIVE_NO_INIT;
	}
	
	if (!bvisiable)
	{
		::ShowWindow(m_hwmd, SW_HIDE);
		::PostMessage(m_hwmd, WM_SHOW_PARSE, null, null);
	}
	else
	{
		if (bfullscreen)
		{
			::ShowWindow(m_hwmd, SW_MAXIMIZE);
		}
		else
		{
			::ShowWindow(m_hwmd, SW_NORMAL);
		}
		::PostMessage(m_hwmd, WM_SHOW_RESUM, null, null);
	}

	return PFX_STATUS_OK;
}








PECKER_END




#endif //(OS_CONFIG == OS_WINDOWS)
