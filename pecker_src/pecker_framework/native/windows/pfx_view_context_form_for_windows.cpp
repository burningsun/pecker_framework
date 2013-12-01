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

LRESULT WINAPI CPfx_window_form_for_win :: WndProc(HWND hwnd, UINT message_, WPARAM wParam, LPARAM lParam)
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

static HWND gMainWnd = null;

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
			status_ = m_context->init_context();
			if (NULL == m_hdc)
			{
				m_hdc = ::GetDC(m_hwnd);
			}
		}
		break;

	case WM_CLOSE:
		{
			status_ = m_context->on_close();
			CPfx_window_form_for_win* pchild_win = PFX_GET_LIST_NEXT (this);
			::PostMessage (pchild_win->m_hwnd,WM_CLOSE,wParam,lParam);
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
		}
		break;
	case WM_PAINT:
		{
			status_ = m_context->on_message_event(umessage_code,wParam,lParam);
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
	case WM_DESTROY:
		{
			status_ = m_context->on_exit();

			if (gMainWnd == m_hwnd)
			{
				m_hwnd = null;
				::PostQuitMessage(0);
			}

			CPfx_window_form_for_win* pchild_win = PFX_GET_LIST_NEXT (this);
			::PostMessage (pchild_win->m_hwnd,WM_DESTROY,wParam,lParam);
		}
		break;
	default:
		break;
	}
	if (null != m_pnext_node && null != m_pnext_node->m_context)
	{
		m_pnext_node->m_context->on_perent_event (umessage_code,wParam,lParam);
	}

	if (PFX_STATUS_CODE_COUNT != status_)
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

pfx_result_t CPfx_window_form_for_win::dettach_context()
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

pfx_result_t CPfx_window_form_for_win::show()
{
	if (!m_is_showed)
	{
		DWORD load_thread_id;
		DWORD render_thread_id;
		m_load_data_thread = ::CreateThread(NULL,0,CPfx_window_form_for_win::LoadDataThreadProc,this,0,&load_thread_id);
		if (NULL == m_load_data_thread)
		{
			PECKER_LOG_ERR ("CPfx_window_form_for_win::show()",
				"m_load_data_thread = ::CreateThread (...);.... GetLastError = %d",
				GetLastError());
			return PFX_STATUS_FAIL;
		}
		m_render_thread = ::CreateThread(NULL,0,CPfx_window_form_for_win::RenderThreadProc,this,0,&render_thread_id);
		if (NULL == m_render_thread)
		{
			PECKER_LOG_ERR ("CPfx_window_form_for_win::show()",
				"m_render_thread = ::CreateThread (...);.... GetLastError = %d",
				GetLastError());
			return PFX_STATUS_FAIL;
		}
	}
	m_is_showed = pfx_true;
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win::close()
{
	::SendMessage (m_hwnd,WM_CLOSE,2,0);
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win::dispose()
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

pfx_result_t CPfx_window_form_for_win::_render_thread()
{
	RETURN_INVALID_RESULT (null == m_display || null ==  m_context,PFX_STATUS_INVALID_PARAMS);
	pfx_boolean_t is_exit = pfx_false;
	pfx_result_t status_;
	pecker_tick tick_;
	pfx_64bit_t escape_tick;
	m_context->init_context ();
	
	
	while (pfx_true != is_exit)
	{
		pfx_double_t last_frame_tick_interval = 0.0;
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
		escape_tick.m_longlong_type = 0;
		

		while (pfx_false == is_exit)
		{
			tick_.start();
			status_ = m_display->update_frame(escape_tick,last_frame_tick_interval,is_exit);
			status_ = m_display->swap_back_buffer();
			last_frame_tick_interval = tick_.get_millisecond();
			tick_.stop();
			escape_tick.m_longlong_type += (pfx_long_t)(last_frame_tick_interval);	
		}

		status_ = m_display->close_display_device();

		if (PFX_STATUS_OK == status_)
		{
			PECKER_LOG_INFO ("CPfx_window_form_for_win::_render_thread()",
				"status_ = m_display->close_display_device (this);.... %s",
				"PFX_STATUS_OK == status_");
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
	m_context->on_release_datas();

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

IPfx_windows_display* CPfx_window_form_for_win::get_display()
{
	return m_display;
}

PECKER_END


