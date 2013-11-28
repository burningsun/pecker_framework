/*
 * pfx_view_context_form.h
 *
 *  Created on: 2013-11-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_VIEW_CONTEXT_FORM_H_
#define		PFX_VIEW_CONTEXT_FORM_H_

#include "../pfx_defines.h"
#include "../render/render_system/pfx_view_context.h"
#include "../render/render_system/pfx_rendertevent.h"

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

	virtual pfx_windows_context_base* get_context () const = 0;
public:
	virtual pfx_result_t show () = 0;
	virtual pfx_result_t close () = 0;
	virtual pfx_result_t dispose () = 0;

public:
	virtual pfx_long_t get_form_handle () const = 0; // hwnd
	virtual pfx_long_t get_display_handle () const = 0; // hdc
protected: 
	virtual pfx_result_t _render_thread () = 0;

	virtual pfx_result_t attach_display (IPfx_windows_display* PARAM_INOUT display_) = 0;
	virtual pfx_result_t dettach_display () = 0;

	virtual IPfx_windows_display* get_display () = 0;
public:
	static PFX_INLINE pfx_result_t config_windows_form (IPfx_windows_form* PARAM_INOUT form_,
		IPfx_windows_display* PARAM_INOUT display_);
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


PFX_INLINE pfx_result_t  IPfx_windows_form::config_windows_form (IPfx_windows_form* PARAM_INOUT form_,
	IPfx_windows_display* PARAM_INOUT display_)
{
	pfx_result_t status_;
	RETURN_INVALID_RESULT (null == form_ || null == display_,PFX_STATUS_INVALID_PARAMS);
	status_ = form_->dettach_display ();
	if (PFX_STATUS_OK == status_)
	{
		status_ = form_->attach_display (display_);
	}
	return status_;
}


PECKER_END

#endif			//PFX_VIEW_CONTEXT_FORM_H_
