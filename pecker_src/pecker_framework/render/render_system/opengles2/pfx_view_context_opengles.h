/*
 * pfx_view_context_opengles.h
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_VIEW_CONTEXT_OPENGLES_H_
#define		PFX_VIEW_CONTEXT_OPENGLES_H_

#include "../../../native/windows/pfx_view_context_form_for_windows.h"

PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

class PFX_RENDER_SYSTEM_API CPfx_window_form_for_win_opengles : 
	public CPfx_window_form_for_win,
	public IPfx_windows_display
{
public:
	 pfx_result_t _render_thread ();
protected:
	PFX_INLINE IPfx_windows_display* get_display ();
	pfx_result_t init_display_device (IPfx_windows_form* PARAM_INOUT windows_form);
	pfx_result_t on_swap_back_buffer ();
	pfx_result_t close_display_device ();
};

PFX_INLINE IPfx_windows_display* CPfx_window_form_for_win_opengles::get_display()
{
	IPfx_windows_display* display = this;
	return display;
}

PECKER_END

#endif			//PFX_VIEW_CONTEXT_OPENGLES_H_
