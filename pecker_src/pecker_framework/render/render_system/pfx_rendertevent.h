/*
 * pfx_renderevent.h
 *
 *  Created on: 2013-11-1
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDEREVENT_H_
#define		PFX_RENDEREVENT_H_

#include "../../pfx_defines.h"
#include "../pfx_render_type.h"

PECKER_BEGIN

typedef pfx_handle_t pfx_unknown_event_object_t;

typedef struct pfx_message_event_code pfx_message_event_code_t;
struct pfx_message_event_code
{
	pfx_enum_int_t m_umessage_code;
	pfx_long_t m_wParam;
	pfx_long_t m_lParam;
};

PFX_Interface Ipfx_message_event
{
	virtual ~Ipfx_message_event () {;}
	virtual const pfx_message_event_code_t& get_message_code() const = 0; 
	virtual pfx_result_t on_event(pfx_unknown_event_object_t pobject) = 0;
};

PFX_Interface Ipfx_shader_program;
PFX_Interface Ipfx_shader_render_params;

PFX_Interface Ipfx_render_event
{
	virtual ~Ipfx_render_event() {;}
	virtual pfx_result_t on_render (Ipfx_shader_program* PARAM_INOUT shader_,
		Ipfx_shader_render_params* PARAM_INOUT params_,pfx_unknown_event_object_t pobject) = 0;
};

PECKER_END

#endif			//PFX_RENDEREVENT_H_
