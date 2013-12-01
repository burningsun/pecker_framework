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
	virtual pfx_result_t blocking_and_loop () = 0;
protected:
	virtual pfx_result_t run_app () = 0;
public:
	virtual pfx_long_t get_native_window () const = 0; // hwnd
	virtual pfx_long_t get_native_display () const = 0; // hdc
	virtual pfx_long_t get_native_pixelmap() const = 0;
protected: 
	virtual pfx_result_t _render_thread () = 0;

	virtual pfx_result_t attach_display (IPfx_windows_display* PARAM_INOUT display_) = 0;
	virtual pfx_result_t dettach_display () = 0;

	virtual IPfx_windows_display* get_display () = 0;
public:
	static PFX_INLINE pfx_result_t config_windows_form (IPfx_windows_form* PARAM_INOUT form_,
		IPfx_windows_display* PARAM_INOUT display_);

	static PFX_INLINE pfx_result_t run_windows_program (IPfx_windows_form* PARAM_INOUT form_,
																pfx_windows_context_base* PARAM_INOUT context_,
																IPfx_windows_display* PARAM_INOUT display_);
public:
	virtual ~IPfx_windows_form() {;};
}; 

PFX_INLINE pfx_result_t run_windows_program (IPfx_windows_form* PARAM_INOUT form_,
																pfx_windows_context_base* PARAM_INOUT context_,
																IPfx_windows_display* PARAM_INOUT display_);

PFX_Interface IPfx_windows_display
{
	virtual pfx_result_t init_display_device (IPfx_windows_form* PARAM_INOUT windows_form) = 0;
	virtual pfx_result_t update_frame (const pfx_64bit_t& PARAM_IN escape_tick,
		pfx_double_t last_frame_tick_interval,
		pfx_boolean_t& PARAM_INOUT exist_render) = 0;
	virtual pfx_result_t swap_back_buffer () = 0;
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

PFX_INLINE pfx_result_t IPfx_windows_form::run_windows_program (IPfx_windows_form* PARAM_INOUT form_,
																pfx_windows_context_base* PARAM_INOUT context_,
																IPfx_windows_display* PARAM_INOUT display_)
{
		RETURN_INVALID_RESULT (null == form_||null==context_||null == display_,PFX_STATUS_INVALID_PARAMS);

		pfx_result_t status_;

		FOR_ONE_LOOP_BEGIN
		status_ = IPfx_windows_form::config_windows_form(form_,display_);
		BREAK_LOOP_CONDITION (status_ != PFX_STATUS_OK);
		status_ = form_->attach_context(context_);
		BREAK_LOOP_CONDITION (status_ != PFX_STATUS_OK);
		status_ = form_->show();
		BREAK_LOOP_CONDITION (status_ != PFX_STATUS_OK);
		status_ = form_->run_app();
		BREAK_LOOP_CONDITION (status_ != PFX_STATUS_OK);
		status_ = form_->blocking_and_loop();
		FOR_ONE_LOOP_END

		return status_;
}

PECKER_END

#endif			//PFX_VIEW_CONTEXT_FORM_H_
