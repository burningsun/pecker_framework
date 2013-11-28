/*
 * pfx_view_context_form_for_windows.cpp
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_view_context_form_for_windows.h"
#include "../../data/pfx_list.h"

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
		}
		break;

	case WM_CLOSE:
		{
			status_ = m_context->on_close();
			CPfx_window_form_for_win* pchild_win = PFX_GET_LIST_NEXT (this);
			::PostMessage (pchild_win->m_hwnd,WM_CLOSE,wParam,lParam);
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
	m_context = null;
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win :: add_event_process (Ipfx_message_event* PARAM_INOUT event_)
{
	return PFX_STATUS_DENIED;
}

pfx_result_t CPfx_window_form_for_win::show()
{
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win::close()
{
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win::dispose()
{
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win::_render_thread()
{
	return PFX_STATUS_OK;
}

IPfx_windows_display* CPfx_window_form_for_win::get_display()
{
	return null;
}

PECKER_END


