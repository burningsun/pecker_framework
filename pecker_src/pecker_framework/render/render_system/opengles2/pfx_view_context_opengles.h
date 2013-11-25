/*
 * pfx_view_context_opengles.h
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_VIEW_CONTEXT_OPENGLES_H_
#define		PFX_VIEW_CONTEXT_OPENGLES_H_

#include "../pfx_view_context.h"
#include "../pfx_rendertevent.h"
PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

//class CPfx_view_context_opengles : public pfx_windows_context_base
//{
//
//};

class CPfx_window_display_opengles
{
protected:
	pfx_windows_context_base* m_context;
protected:
	static LRESULT WINAPI WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
protected:
	pfx_result_t windows_message_process (	pfx_enum_int_t m_umessage_code,
	pfx_long_t m_wParam,
	pfx_long_t m_lParam);
public:
	pfx_result_t add_event_process (Ipfx_message_event* PARAM_INOUT event_); 
public:
	pfx_result_t attach_context (pfx_windows_context_base* PARAM_INOUT context);

public:
	pfx_result_t show ();
	pfx_result_t close ();
};

PECKER_END

#endif			//PFX_VIEW_CONTEXT_OPENGLES_H_
