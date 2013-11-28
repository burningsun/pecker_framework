/*
 * pfx_view_context_form_for_windows.h
 *
 *  Created on: 2013-11-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_VIEW_CONTEXT_FORM_FOR_WINDOWS_H_
#define		PFX_VIEW_CONTEXT_FORM_FOR_WINDOWS_H_

#include "../pfx_view_context_form.h"

PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

class CPfx_window_form_for_win : public IPfx_windows_form
{
	//////////////////////////////////////////////////////////////////////////
private:
	HWND m_hwnd;
	HANDLE m_renderthread;
protected:
	static LRESULT WINAPI WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	//////////////////////////////////////////////////////////////////////////
protected:
	pfx_windows_context_base* m_context;
	CPfx_window_form_for_win* m_prev_node;
	CPfx_window_form_for_win* m_pnext_node;

protected:
	pfx_result_t windows_message_process (	pfx_enum_int_t umessage_code,
	pfx_long_t wParam,
	pfx_long_t lParam);
public:
	virtual pfx_result_t add_event_process (Ipfx_message_event* PARAM_INOUT event_); 
public:
	pfx_result_t attach_context (pfx_windows_context_base* PARAM_INOUT context);
	pfx_result_t dettach_context ();
public:
	pfx_result_t show ();
	pfx_result_t close ();
	pfx_result_t dispose ();

protected: 
	virtual pfx_result_t _render_thread ();
	virtual IPfx_windows_display* get_display ();
};

PECKER_END

#endif			//PFX_VIEW_CONTEXT_FORM_FOR_WINDOWS_H_
