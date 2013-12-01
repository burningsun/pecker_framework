﻿/*
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
#include "pfx_renderdevice.h"

PECKER_BEGIN

PFX_Interface Ipfx_message_event;


typedef struct st_PRESENT_PARAMETERS 
{
		pfx_usize_t m_buffer_width;
		pfx_usize_t m_buffer_height;
		pfx_usize_t m_buffer_count;
		pfx_enum_t m_buffer_format;
		// 31 ~ 0
		// 0~7 sample type 8~15 sample quality
		pfx_bitfield_t m_multi_sample_mask; 

		pfx_bitfield_t m_swap_effect;
		
		// 0~2 conext priority level 7 EnableAutoDepthStencil   8~15 AutoDepthFormat 16~23 AutoStenciFormat 24~32 luminance color bit size
		pfx_bitfield_t m_renderbuffer_mask;

		// 0 Windowed 8~15 FullScreen_RefreshRateInHz 16~23 PresentationInterval
		pfx_bitfield_t m_screen_mask;
		//
		pfx_flag_t		m_flags;
} PFX_PRESENT_PARAMETERS;

#define  PFX_FULL_SCREEN_MASK (1)
#define PFX_CONTEXT_PRIORITY_LEVEL_VALUE(X) ((X)&0X7)

typedef enum enumCONTEXT_PRIORITY_LEVEL_IMG
{
	PFX_CONTEXT_LOW_PREPRIORITY = 0,
	PFX_CONTEXT_MEDIUM_PREPRIORITY,
	PFX_CONTEXT_HIGH_PREPRIORITY,
	PFX_CONTEXT_PRIORITY_LEVEL_IMG_TYPE_COUNT
}PFX_CONTEXT_PRIORITY_LEVEL_IMG_t;


typedef struct st_windows_info
{
	pfx_nsize_t m_x;
	pfx_nsize_t m_y;
	pfx_usize_t m_width;
	pfx_usize_t m_hight;

	pfx_bitfield_t	m_windows_style;
	pfx_bitfield_t	m_windows_exstyle;
	pfx_string_t	m_str_title_name;

	PFX_PRESENT_PARAMETERS	m_present_params;

	pfx_handle_t m_render_params_ex;
}PFX_WINDOWS_INFO_t;

class  pfx_windows_context_base
{
public:
	//pfx_windows_context_base ();
	virtual ~pfx_windows_context_base (){;};
public:
	virtual pfx_result_t init_context () = 0;
	virtual pfx_result_t resize_context (pfx_usize_t width, pfx_usize_t height) = 0;
	virtual pfx_result_t move_context (pfx_nsize_t x,pfx_nsize_t y) = 0;

	virtual pfx_result_t on_landscape_change (pfx_usize_t width, pfx_usize_t height,pfx_bool_t is_landscape) = 0;
	virtual pfx_result_t on_message_event (pfx_enum_int_t umessage_code, pfx_long_t wParam, pfx_long_t lParam) = 0;
	
	virtual pfx_result_t on_load_datas () = 0;
	virtual pfx_result_t on_release_datas () = 0;

	virtual pfx_result_t on_render_init (Ipfx_render_device*  PARAM_INOUT graphic_device_) = 0;
	
	virtual pfx_result_t on_load_render_resource () = 0;
	virtual pfx_result_t on_render_frame (Ipfx_render_device*  PARAM_INOUT graphic_device_,
																	const pfx_64bit_t& PARAM_IN escape_tick,
																	pfx_double_t last_frame_tick_interval,
																	pfx_boolean_t& PARAM_INOUT exit_render) = 0;
	virtual pfx_result_t on_release_render_resource () = 0;

	virtual pfx_result_t on_swap_render_frame (Ipfx_render_device*  PARAM_INOUT graphic_device_) = 0;
	
	virtual pfx_result_t on_close () = 0;
	virtual pfx_result_t on_parse () = 0;
	virtual pfx_result_t on_exit () = 0;

	virtual const PFX_WINDOWS_INFO_t& get_context_info () const = 0;
	virtual pfx_result_t on_perent_event (pfx_enum_int_t umessage_code, pfx_long_t wParam, pfx_long_t lParam) = 0;
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

PECKER_END

#endif			//PFX_VIEW_CONTEXT_H_
