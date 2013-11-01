/*
 * pfx_view_context.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_VIEW_CONTEXT_H_
#define		PFX_VIEW_CONTEXT_H_

#include "../../pfx_defines.h"
#include "../../data/pfx_string.h"
#include "pfx_rendertevent.h"
#include "pfx_rendertarget.h"


PFX_Interface Ipfx_message_event;
class pfx_windows_context_base
{
public:
	pfx_windows_context_base ();
	virtual ~pfx_windows_context_base ();
public:
	virtual pfx_result_t init_context ();
	virtual pfx_result_t resize_context (pfx_usize_t width, pfx_usize_t height);
	virtual pfx_result_t move_context (pfx_nsize_t x,pfx_nsize_t y);

	virtual pfx_result_t on_landscape_change (pfx_usize_t width, pfx_usize_t height,pfx_bool_t is_landscape);
	virtual pfx_result_t on_message_event (Ipfx_message_event* PARAM_INOUT pevent_,pfx_unknown_event_object_t* pobject);
	
	virtual pfx_result_t on_load_datas ();
	virtual pfx_result_t on_render_init ();
	virtual pfx_result_t on_render_frame ();
	virtual pfx_result_t on_swap_render_frame ();
	
	virtual pfx_result_t on_close ();
	virtual pfx_result_t on_parse ();
	virtual pfx_result_t on_exit ();
};


//PFX_C_EXTERN_BEGIN
//
//typedef struct pfx_windows_context pfx_windows_context_t;
//typedef struct Ipfx_windows_context_method Ipfx_windows_context_method_t;
//typedef struct pfx_windows_message_event pfx_windows_message_event_t;
//typedef pfx_handle_t pfx_unknown_event_object_t;
//
//struct Ipfx_windows_context_method
//{
//	pfx_result_t (*init_windows_context) (pfx_windows_context_t* PARAM_INOUT context);
//	
//	pfx_result_t (*on_resize_context) (pfx_windows_context_t* PARAM_INOUT context,pfx_usize_t width,pfx_usize_t height);
//	pfx_result_t (*on_move_context) (pfx_windows_context_t* PARAM_INOUT context,pfx_nsize_t new_X,pfx_nsize_t new_Y);
//	pfx_result_t (*on_landscape_change) (pfx_windows_context_t* PARAM_INOUT context,pfx_usize_t width,pfx_usize_t height,
//		pfx_bool_t is_landscape);
//
//	pfx_result_t (*on_message_event) (pfx_windows_context_t* PARAM_INOUT context,
//		pfx_windows_message_event_t* PARAM_INOUT message_event_,
//		pfx_unknown_event_object_t PARAM_INOUT event_object_);
//
//	pfx_result_t (*on_load_datas) (pfx_windows_context_t* context);
//	pfx_result_t (*on_render_init) (pfx_windows_context_t* context);
//	pfx_result_t (*on_render_frame) (pfx_windows_context_t* context);
//	pfx_result_t (*on_swap_render_frame) (pfx_windows_context_t* context);
//
//	pfx_result_t (*on_close) (pfx_windows_context_t* context);
//	pfx_result_t (*on_parse) (pfx_windows_context_t* context);
//	pfx_result_t (*on_exit) (pfx_windows_context_t* context);
//};
//
//struct pfx_windows_context
//{
//	pfx_string_t					m_windows_title;
//	pfx_enum_int_t				m_windows_stype;
//	pfx_enum_int_t				m_windows_extern_stype;
//	pfx_sint_t						m_topx;
//	pfx_sint_t						m_topy;
//	//pfx_usize_t						m_width;
//	//pfx_usize_t						m_height;
//	pfx_render_target_t		m_render_target;
//};
//
//struct pfx_windows_message_event
//{
//	pfx_enum_int_t m_umessage_code;
//	pfx_long_t m_wParam;
//	pfx_long_t m_lParam;
//};
//
//
//PFX_C_EXTERN_END

#endif			//PFX_VIEW_CONTEXT_H_
