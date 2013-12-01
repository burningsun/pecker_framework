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
	HDC		 m_hdc;
	HANDLE m_render_thread;
	HANDLE m_load_data_thread;
	pfx_boolean_t m_is_showed;
protected:
	static LRESULT WINAPI WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	static DWORD WINAPI RenderThreadProc (__in LPVOID lpParameter);
	static DWORD WINAPI LoadDataThreadProc (__in LPVOID lpParameter);
	//////////////////////////////////////////////////////////////////////////
protected:
	pfx_windows_context_base* m_context;
	IPfx_windows_display* m_display;

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

	PFX_INLINE pfx_windows_context_base* get_context () const;
public:
	pfx_result_t show ();
	pfx_result_t close ();
	pfx_result_t dispose ();
public:
	PFX_INLINE pfx_long_t get_native_window () const; 
	PFX_INLINE pfx_long_t get_native_display () const;
	PFX_INLINE pfx_long_t get_native_pixelmap () const;
protected: 
	 pfx_result_t _render_thread ();

	 pfx_result_t attach_display (IPfx_windows_display* PARAM_INOUT display_);
	 pfx_result_t dettach_display ();

	 IPfx_windows_display* get_display ();

public:
	CPfx_window_form_for_win();
	virtual ~CPfx_window_form_for_win();
};

PFX_INLINE pfx_windows_context_base* CPfx_window_form_for_win::get_context () const
{
	return m_context;
}
PFX_INLINE pfx_long_t CPfx_window_form_for_win::get_native_window () const
{
	return (pfx_long_t)m_hwnd;
}
PFX_INLINE pfx_long_t CPfx_window_form_for_win::get_native_display () const
{
	return (pfx_long_t)m_hdc;
}
PFX_INLINE pfx_long_t CPfx_window_form_for_win::get_native_pixelmap() const
{
	return null;
}

PECKER_END

#endif			//PFX_VIEW_CONTEXT_FORM_FOR_WINDOWS_H_
