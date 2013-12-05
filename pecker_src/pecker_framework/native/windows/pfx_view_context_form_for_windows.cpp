/*
 * pfx_view_context_form_for_windows.cpp
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_view_context_form_for_windows.h"
#include "../../data/pfx_list.h"
#include "../pfx_timetick.h"
#include "../pfx_log.h"

PECKER_BEGIN

static HWND gMainWnd = null;

LRESULT WINAPI CPfx_window_form_for_win :: WndProc (HWND hwnd, UINT message_, WPARAM wParam, LPARAM lParam)
{
	if (NULL == hwnd)
	{
		return 0;
	}

	if (WM_CREATE == message_)
	{	
		::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG)(((LPCREATESTRUCT)lParam)->lpCreateParams));
	}

	CPfx_window_form_for_win* pWinForm = (CPfx_window_form_for_win*)(::GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (NULL != pWinForm)
	{
		LRESULT res = pWinForm->windows_message_process(message_,wParam,lParam);
		return res;
	}

	return ::DefWindowProc(hwnd, message_, wParam, lParam);
}
DWORD WINAPI CPfx_window_form_for_win::RenderThreadProc (__in LPVOID lpParameter)
{
	RETURN_INVALID_RESULT (NULL == lpParameter,PFX_STATUS_INVALID_PARAMS);
	CPfx_window_form_for_win* pform = (CPfx_window_form_for_win*)lpParameter;
	return pform->_render_thread();
}
DWORD WINAPI CPfx_window_form_for_win::LoadDataThreadProc (__in LPVOID lpParameter)
{
	RETURN_INVALID_RESULT (NULL == lpParameter,PFX_STATUS_INVALID_PARAMS);
	CPfx_window_form_for_win* pform = (CPfx_window_form_for_win*)lpParameter;
	pfx_windows_context_base* context_;
	context_ = pform->get_context();
	RETURN_INVALID_RESULT (null == context_,PFX_STATUS_INVALID_PARAMS);
	return context_->on_load_datas();
}

CPfx_window_form_for_win :: CPfx_window_form_for_win () : m_context (null),m_display(null),
	m_hdc(null),
	m_hwnd(null),
	m_pnext_node (null),
	m_prev_node (null),
	m_render_thread (NULL),
	m_load_data_thread (NULL),
	m_is_showed (pfx_false)
{
	;
}
CPfx_window_form_for_win::~CPfx_window_form_for_win()
{
	dispose();
}

pfx_result_t CPfx_window_form_for_win :: windows_message_process (pfx_enum_int_t umessage_code, pfx_long_t wParam, pfx_long_t lParam)
{
	if (null == m_context)
	{
		return ::DefWindowProc(m_hwnd, umessage_code, wParam, lParam);
	}

	pfx_result_t status_ = PFX_STATUS_CODE_COUNT;

	switch(umessage_code)
	{
	case WM_CREATE:
		{
			//status_ = m_context->init_context();
			//if (NULL == m_hdc)
			//{
			//	m_hdc = ::GetDC(m_hwnd);
			//}
		}
		break;

	case WM_CLOSE:
		{
			status_ = m_context->on_close();
			CPfx_window_form_for_win* pchild_win = PFX_GET_LIST_NEXT (this);
			if (null != pchild_win)
			{
				::PostMessage (pchild_win->m_hwnd,WM_CLOSE,wParam,lParam);
			}
			
			HANDLE thread_handle_array[2];
			thread_handle_array[0] = m_load_data_thread;
			thread_handle_array[1] = m_render_thread;
			WaitForMultipleObjects(2, thread_handle_array, TRUE, 10000);
			if (m_load_data_thread)
			{
				::CloseHandle (m_load_data_thread);
				m_load_data_thread = NULL;
			}
			if (m_render_thread)
			{
				::CloseHandle(m_render_thread);
				m_render_thread = NULL;
			}
			if (NULL != m_hdc)
			{
				::ReleaseDC(m_hwnd,m_hdc);
				m_hdc = NULL;
			}
			m_is_showed = pfx_false;
			::DestroyWindow(m_hwnd);
		}
		break;
	case WM_PAINT:
		{
			status_ = m_context->on_message_event(umessage_code,wParam,lParam);
			//::Sleep(10);
		}
		break;
	case WM_SIZE:
		{
			const PFX_WINDOWS_INFO_t& info = m_context->get_context_info();
			 pfx_usize_t width =  LOWORD(lParam);
			 pfx_usize_t height = HIWORD(lParam);
			if ((info.m_present_params.m_screen_mask & PFX_FULL_SCREEN_MASK) &&
				info.m_hight ==width&& 
				info.m_width ==  height)
			{
				pfx_bool_t is_landscape = pfx_false;
				if (info.m_width > info.m_hight)
				{
					is_landscape = pfx_true;
				}
				status_ = m_context->on_landscape_change(width,
					height,is_landscape);
			}
			else
			{
				status_ = m_context->resize_context (width,height);
			}
		}
		break;
	case  WM_MOVE:
		{
			pfx_nsize_t posx = LOWORD(lParam);
			pfx_nsize_t posy = HIWORD(lParam);
			status_ = m_context->move_context(posx,posy);
		}
		break;
	case WM_DESTROY:
		{
			status_ = m_context->on_exit();

			if (gMainWnd == m_hwnd)
			{
				m_hwnd = null;
				gMainWnd = null;
				::PostQuitMessage(0);
			}

			CPfx_window_form_for_win* pchild_win = PFX_GET_LIST_NEXT (this);
			if (null != pchild_win)
			{
				::PostMessage (pchild_win->m_hwnd,WM_DESTROY,wParam,lParam);
			}
			
		}
		break;
	default:
		break;
	}
	if (null != m_pnext_node && null != m_pnext_node->m_context)
	{
		m_pnext_node->m_context->on_perent_event (umessage_code,wParam,lParam);
	}

	if (PFX_STATUS_CODE_COUNT == status_)
	{
		return ::DefWindowProc(m_hwnd, umessage_code, wParam, lParam);
	}
	else
	{
		return status_;
	}
	
}

pfx_result_t CPfx_window_form_for_win::attach_context (pfx_windows_context_base* PARAM_INOUT context)
{
	if (null == context)
	{
		return PFX_STATUS_INVALID_PARAMS;
	}
	if (null != m_context)
	{
		return PFX_STATUS_DENIED;
	}
	m_context = context;
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win::dettach_context ()
{
	//stop render thread
	if (m_is_showed)
	{
		::SendMessage (m_hwnd,WM_CLOSE,1,0);
	}
	//if (m_load_data_thread)
	//{
	//	::CloseHandle (m_load_data_thread);
	//	m_load_data_thread = NULL;
	//}
	//if (m_render_thread)
	//{
	//	::CloseHandle(m_render_thread);
	//	m_render_thread = NULL;
	//}
	m_context = null;
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win :: add_event_process (Ipfx_message_event* PARAM_INOUT event_)
{
	return PFX_STATUS_DENIED;
}

pfx_result_t CPfx_window_form_for_win::show ()
{
	RETURN_INVALID_RESULT (null == m_context || null == m_display,PFX_STATUS_UNINIT);
	pfx_result_t status_ = PFX_STATUS_OPENED;

	if (!m_is_showed)
	{
		wchar_t* titlename = NULL;

		FOR_ONE_LOOP_BEGIN
		status_ = m_context->init_context ();
		if (PFX_STATUS_OK != status_)
		{
			PECKER_LOG_ERR ("CPfx_window_form_for_win::show",
				"status_ =  context_->init_context(); status_ = %d",
				status_);
			break;
		}

		if (0 >= get_string_chars_length(&(m_context->get_context_info().m_str_title_name)))
		{
			PECKER_LOG_ERR ("CPfx_window_form_for_win::show",
				"get_string_chars_length(&(m_context->get_context_info().m_str_title_name)) <= 0; %s",
				"null == titlename");
			BREAK_LOOP (status_,PFX_STATUS_INVALID_PARAMS);
		}

		int  unicode_len = ::MultiByteToWideChar( CP_ACP,
			0,
			get_string_chars_buffer(&(m_context->get_context_info().m_str_title_name)),
			get_string_chars_length(&(m_context->get_context_info().m_str_title_name)),
			NULL,
			0 );  
		titlename = new wchar_t[unicode_len+1];

		if (null == titlename)
		{
			PECKER_LOG_ERR ("CPfx_window_form_for_win::show",
				"titlename = new wchar_t[unicode_len+1]; %s",
				"null == titlename");

			BREAK_LOOP (status_,PFX_STATUS_MEM_LOW);
		}

		::MultiByteToWideChar( CP_ACP,
			0,
			get_string_chars_buffer(&(m_context->get_context_info().m_str_title_name)),
			get_string_chars_length(&(m_context->get_context_info().m_str_title_name)),
			(LPWSTR)titlename,
			unicode_len);  

		titlename[unicode_len] = 0;


		WNDCLASS window_class;
		memset(&window_class, 0, sizeof(WNDCLASS));
		window_class.lpszClassName = titlename;
		window_class.lpfnWndProc = WndProc;
		window_class.style = m_context->get_context_info().m_windows_style;//CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		window_class.hCursor = ::LoadCursor(NULL, IDC_ARROW);
		window_class.hIcon = ::LoadIcon (NULL,IDI_APPLICATION);
		//wchar_t modlename[256] = pfx_char_type("pecker_core.dll");
		window_class.hInstance =::GetModuleHandle(NULL);

		RECT window_rect;
		::SetRect(&window_rect, 
			m_context->get_context_info().m_x,
			m_context->get_context_info().m_y,
			m_context->get_context_info().m_x + m_context->get_context_info().m_width,
			m_context->get_context_info().m_y + m_context->get_context_info().m_hight);

		if (0 == ::RegisterClass(&window_class))
		{
			PECKER_LOG_ERR ("CPfx_window_form_for_win::show",
				"0 == ::RegisterClass(&window_class); error = %d",
				GetLastError());

			BREAK_LOOP (status_,PFX_STATUS_INVALID_PARAMS);
		}


		status_ = ::AdjustWindowRect(&window_rect, WS_BORDER | WS_SYSMENU, FALSE);

		if (!status_)
		{
			PECKER_LOG_ERR ("CPfx_window_form_for_win::show",
				"0 == ::AdjustWindowRect(...); error = %d",
				GetLastError());
			BREAK_LOOP (status_,PFX_STATUS_INVALID_PARAMS);
		}


		m_hwnd = ::CreateWindowEx(
			m_context->get_context_info().m_windows_exstyle,
			titlename,
			titlename,
			WS_BORDER | WS_SYSMENU,
			window_rect.left,	// x
			window_rect.top,	// y
			window_rect.right - window_rect.left,	// width
			window_rect.bottom - window_rect.top,	// height
			NULL,
			NULL,
			window_class.hInstance,
			this
			);


		if (NULL == m_hwnd)
		{
			PECKER_LOG_ERR ("CPfx_window_form_for_win::show",
				"0 == ::CreateWindowEx(...); error = %d",
				GetLastError());
			BREAK_LOOP (status_,PFX_STATUS_INVALID_PARAMS);
		}

		if (NULL == m_hdc)
		{
			m_hdc = ::GetDC(m_hwnd);
		}
		//status_ = GetLastError();

		//status_ = GetLastError();
		//DWORD load_thread_id;
		DWORD render_thread_id;

		m_render_thread = ::CreateThread(NULL,0,CPfx_window_form_for_win::RenderThreadProc,this,0,&render_thread_id);
		if (NULL == m_render_thread)
		{
			PECKER_LOG_ERR ("CPfx_window_form_for_win::show()",
				"m_render_thread = ::CreateThread (...);.... GetLastError = %d",
				GetLastError());
			BREAK_LOOP (status_,PFX_STATUS_FAIL);
		}
		status_ = PFX_STATUS_OK;
		FOR_ONE_LOOP_END

		if (titlename)
		{
			delete [] titlename;
			titlename = null;
		}

		::ShowWindow(m_hwnd,SW_SHOW);
		::UpdateWindow(m_hwnd);
		m_is_showed = pfx_true;

		return status_;
	}


	return status_;
}

pfx_result_t CPfx_window_form_for_win::close ()
{
	::SendMessage (m_hwnd,WM_CLOSE,2,0);
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win::dispose ()
{
	close();
	if (m_context)
	{
		m_context->on_exit();
	}

	m_context = null;
	m_display = null;
	m_hdc = null;
	m_hwnd = null;
	m_pnext_node = null;
	m_prev_node = null;
	m_render_thread = NULL;
	m_load_data_thread = NULL;
	m_is_showed = pfx_false;

	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win::blocking_and_loop ()
{
	MSG msg;
	BOOL bRet;

	while( (bRet = ::GetMessage( &msg, NULL, 0, 0 )) != 0)
	{ 
		if (bRet == -1)
		{
			break;
		}
		else
		{
			::TranslateMessage(&msg); 
			::DispatchMessage(&msg); 
		}
	} 
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win::run_app ()
{
	if (NULL == gMainWnd)
	{
		gMainWnd = m_hwnd;
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_DENIED;
	}
	
}

pfx_result_t CPfx_window_form_for_win::_render_thread ()
{
	RETURN_INVALID_RESULT (null == m_display || null ==  m_context,PFX_STATUS_INVALID_PARAMS);
	pfx_boolean_t is_exit = pfx_true_val2;
	pfx_result_t status_;
	pecker_tick tick_;
	pfx_64bit_t escape_tick;
	// 初始化窗体内容
	//m_context->init_context ();
	// 初始化绘图显示设备
	status_ = m_display->init_display_device (this);
	if (PFX_STATUS_OK == status_)
	{
		PECKER_LOG_INFO ("CPfx_window_form_for_win::_render_thread()",
			"status_ = m_display->init_display_device (this);.... %s",
			pfx_char_type("PFX_STATUS_OK == status_"));
	}
	else
	{
		PECKER_LOG_ERR ("CPfx_window_form_for_win::_render_thread()",
			"status_ = m_display->init_display_device (this);.... status_ = %d",
			status_);
		::PostMessage (m_hwnd,WM_CLOSE,0,status_);
		return status_;
	}

	// 渲染应用循环
	while (pfx_true != is_exit)
	{
		pfx_double_t last_frame_tick_interval = 0.0;

		// 当 pfx_true_val2 == is_exit 只需重新加载资源的时候
		// 用于场景图像给CPU RAM加载硬盘图像数据数据
		if (pfx_true_val2 == is_exit && NULL == m_load_data_thread)
		{
			DWORD load_thread_id;
			m_load_data_thread = ::CreateThread(NULL,0,
				CPfx_window_form_for_win::LoadDataThreadProc,this,0,&load_thread_id);
			if (NULL == m_load_data_thread)
			{
				PECKER_LOG_ERR ("CPfx_window_form_for_win::show()",
					"m_load_data_thread = ::CreateThread (...);.... GetLastError = %d",
					GetLastError());
				BREAK_LOOP (status_,PFX_STATUS_FAIL);
			}
		}
		// 当 pfx_true_val2 != is_exit 的时候重新初始化绘图显示设备
		if (pfx_true_val2 != is_exit)
		{
			status_ = m_display->init_display_device (this);
			if (PFX_STATUS_OK == status_)
			{
				PECKER_LOG_INFO ("CPfx_window_form_for_win::_render_thread()",
					"status_ = m_display->init_display_device (this);.... %s",
					"PFX_STATUS_OK == status_");
			}
			else
			{
				PECKER_LOG_ERR ("CPfx_window_form_for_win::_render_thread()",
					"status_ = m_display->init_display_device (this);.... status_ = %d",
					status_);
				::PostMessage (m_hwnd,WM_CLOSE,0,status_);
				break;
			}
		}


		escape_tick.m_longlong_type = 0;
		

		// 将CPU RAM的数据加载到GPU RAM上面
		status_ = m_context->on_load_render_resource ();
		if (PFX_STATUS_OK == status_)
		{
			PECKER_LOG_INFO ("CPfx_window_form_for_win::_render_thread()",
				"status_ = m_display->on_load_render_resource ();.... %s",
				pfx_char_type("PFX_STATUS_OK == status_"));
		}
		else
		{
			PECKER_LOG_ERR ("CPfx_window_form_for_win::_render_thread()",
				"status_ = m_display->on_load_render_resource ();.... status_ = %d",
				status_);
			::PostMessage (m_hwnd,WM_CLOSE,0,status_);
			break;
		}

		is_exit = pfx_false;
		//pfx_sint_t interval_ = PFX_GET_PRESENTATION_INTERVAL (m_context->get_context_info().m_present_params.m_screen_mask);
		//interval_ = interval_ / 3;
		// 渲染图像
		while (pfx_false == is_exit)
		{
			tick_.start();
			status_ = m_display->update_frame(escape_tick,last_frame_tick_interval,is_exit);
			status_ = m_display->swap_back_buffer();
			last_frame_tick_interval = tick_.get_millisecond();
			//if (last_frame_tick_interval < interval_)
			//{
			//	::Sleep(interval_);
			//}
			tick_.stop();
			escape_tick.m_longlong_type += (pfx_long_t)(last_frame_tick_interval);	
		}

		// 释放GPU RAM占用的资源数据
		status_ = m_context->on_release_render_resource ();
		if (PFX_STATUS_OK == status_)
		{
			PECKER_LOG_INFO ("CPfx_window_form_for_win::_render_thread()",
				"status_ = m_display->on_release_render_resource ();.... %s",
				pfx_char_type("PFX_STATUS_OK == status_"));
		}
		else
		{
			PECKER_LOG_ERR ("CPfx_window_form_for_win::_render_thread()",
				"status_ = m_display->on_release_render_resource ();.... status_ = %d",
				status_);
		}

		// 无限等待加载线程退出，并关闭其线程句柄
		if (NULL != m_load_data_thread)
		{
			::WaitForSingleObject(m_load_data_thread,INFINITE);
			::CloseHandle(m_load_data_thread);
			m_load_data_thread = null;
		}

		if (pfx_true_val2 == is_exit)
		{
			m_context->on_release_datas();
		}

		// 当 pfx_true_val2 != is_exit 的时候关闭当前绘图显示设备
		if (pfx_true_val2 != is_exit)
		{
			status_ = m_display->close_display_device();

			if (PFX_STATUS_OK == status_)
			{
				PECKER_LOG_INFO ("CPfx_window_form_for_win::_render_thread()",
					"status_ = m_display->close_display_device (this);.... %s",
					pfx_char_type("PFX_STATUS_OK == status_"));
			}
			else
			{
				PECKER_LOG_ERR ("CPfx_window_form_for_win::_render_thread()",
					"status_ = m_display->close_display_device (this);.... status_ = %d",
					status_);
				::PostMessage (m_hwnd,WM_CLOSE,0,status_);
				break;
			}
		}

	}

	// 无限等待加载线程退出，并关闭其线程句柄
	if (NULL != m_load_data_thread)
	{
		::WaitForSingleObject(m_load_data_thread,INFINITE);
		::CloseHandle(m_load_data_thread);
		m_load_data_thread = null;
	}

	m_context->on_release_datas();

	// 关闭绘图显示设备
	status_ = m_display->close_display_device();

	if (PFX_STATUS_OK == status_)
	{
		PECKER_LOG_INFO ("CPfx_window_form_for_win::_render_thread()",
			"status_ = m_display->close_display_device (this);.... %s",
			pfx_char_type("PFX_STATUS_OK == status_"));
	}
	else
	{
		PECKER_LOG_ERR ("CPfx_window_form_for_win::_render_thread()",
			"status_ = m_display->close_display_device (this);.... status_ = %d",
			status_);
		::PostMessage (m_hwnd,WM_CLOSE,0,status_);
	}

	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win::attach_display (IPfx_windows_display* PARAM_INOUT display_)
{
	RETURN_INVALID_RESULT (null == display_,PFX_STATUS_INVALID_PARAMS);
	RETURN_INVALID_RESULT (null != m_display,PFX_STATUS_DENIED);
	m_display = display_;
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win::dettach_display ()
{
	//stop render thread
	if (m_is_showed)
	{
		::SendMessage (m_hwnd,WM_CLOSE,1,0);
	}
	
	//if (m_load_data_thread)
	//{
	//	::CloseHandle (m_load_data_thread);
	//	m_load_data_thread = NULL;
	//}
	//if (m_render_thread)
	//{
	//	::CloseHandle(m_render_thread);
	//	m_render_thread = NULL;
	//}
	
	m_display = null;
	return PFX_STATUS_OK;
}

IPfx_windows_display* CPfx_window_form_for_win::get_display ()
{
	return m_display;
}

PECKER_END


