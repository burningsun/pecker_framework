/*
 * pfx_view_context_form.h
 *
 *  Created on: 2013-11-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_VIEW_CONTEXT_FORM_H_
#define		PFX_VIEW_CONTEXT_FORM_H_

#include "../pfx_defines.h"
#include "../../render/render_system/pfx_view_context.h"
#include "../../render/render_system/pfx_rendertevent.h"

PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

PFX_Interface IPfx_windows_display;

PFX_Interface IPfx_windows_form
{
public:
	virtual pfx_result_t add_event_process (Ipfx_message_event* PARAM_INOUT event_) = 0; 
public:
	virtual pfx_result_t attach_context (pfx_windows_context_base* PARAM_INOUT context) = 0;
	virtual pfx_result_t dettach_context () = 0;
public:
	virtual pfx_result_t show () = 0;
	virtual pfx_result_t close () = 0;
	virtual pfx_result_t dispose () = 0;
protected: 
	virtual pfx_result_t _render_thread () = 0;
	virtual IPfx_windows_display* get_display () = 0;
public:
	virtual ~IPfx_windows_form() {;};
}; 

PFX_Interface IPfx_windows_display
{
	virtual pfx_result_t init_display_device (IPfx_windows_form* PARAM_INOUT windows_form) = 0;
	virtual pfx_result_t on_swap_back_buffer () = 0;
	virtual pfx_result_t close_display_device () = 0;
	virtual ~IPfx_windows_display() {;};
};

PECKER_END

#endif			//PFX_VIEW_CONTEXT_FORM_H_
