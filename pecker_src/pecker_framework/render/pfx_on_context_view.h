/*
 * pfx_on_context_view.h
 *
 *  Created on: 2014-7-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_ON_CONTEXT_VIEW_H_
#define		PFX_ON_CONTEXT_VIEW_H_

#include "../pfx_defines.h"
#include "pfx_render_defs.h"
#include "pfx_color.h"
PECKER_BEGIN

typedef struct st_display_device_info
{
	void*	m_Display;
	void*	m_Window;
	void*	m_Context;
	void*	m_Config;
	sint_t	m_MajorVersion;
	sint_t	m_MinorVersion;
}display_device_t;

typedef struct  st_back_buffer_info
{
	usize__t	m_width;
	usize__t	m_height;
	void*		m_buffer_ptr;
	usize__t	m_buffer_bytes_count;
}back_buffer_t;

typedef enum enumRENDER_SYS_PARAM_COLOR_BUFFER_TYPE
{
	PFX_RSYS_RGB_BUFFER = 0,
	PFX_RSYS_LUMINANCE_BUFFER,

	PFX_RENDER_SYS_PARAM_COLOR_BUFFER_TYPE_COUNT
}PFX_RSYS_PARAM_COLOR_BUFFER_TYPE_t;

typedef enum enumCONTEXT_PREPRIORITY_TYPE
{
	PFX_CONTEXT_DEFAULT_PREPRIORITY = 0,
	PFX_CONTEXT_LOW_PREPRIORITY,
	PFX_CONTEXT_MEDIUM_PREPRIORITY,
	PFX_CONTEXT_HIGH_PREPRIORITY,
	PFX_CONTEXT_PREPRIORITY_TYPE_COUNT
}PFX_CONTEX_PREPRIORITY_t;

typedef struct st_window_contex_info
{
	viewport_rect_t m_viewport;
	long_t			m_hwnd;
	long_t			m_hdc;
	long_t			m_hpixelmap;
	back_buffer_t*	m_back_buffer_ptr;

	unsigned		m_red_size			: 8;
	unsigned		m_green_size		: 8;
	unsigned		m_blue_size			: 8;
	unsigned		m_alpha_size		: 8;
	unsigned		m_luminance_size	: 8;
	unsigned		m_depth_size		: 8;
	unsigned		m_stencil_size		: 8;
	unsigned		m_alpha_mask_size	: 8;
	unsigned		m_color_buffer_type : 8;
	unsigned		m_context_priority	: 3;
	unsigned		m_conformat_bit		: 2;
	unsigned		m_pbuffer_bit		: 1;
	unsigned		m_pixelmap_bit		: 1;
	unsigned		m_max_pbuffer_size	: 24;
	unsigned		m_fsaamode_bit		: 1;
	unsigned		m_sample_per_pixel	: 16;
	unsigned		m_multisample_count : 16;
	unsigned		m_transparent_info	: 32;

	st_window_contex_info() :
		m_hwnd(null),
		m_hdc(null),
		m_hpixelmap(null),
		m_back_buffer_ptr(null),
		m_red_size(8),
		m_green_size(8),
		m_blue_size(8),
		m_alpha_size(8),
		m_luminance_size(0),
		m_depth_size(16),
		m_stencil_size(8),
		m_alpha_mask_size(0),
		m_color_buffer_type(PFX_RSYS_RGB_BUFFER),
		m_context_priority(PFX_CONTEXT_DEFAULT_PREPRIORITY),
		m_conformat_bit(0),
		m_pbuffer_bit(1),
		m_pixelmap_bit(0),
		m_max_pbuffer_size(0),
		m_fsaamode_bit(0),
		m_sample_per_pixel(4),
		m_multisample_count(1),
		m_transparent_info(0)
	{
		;
	}
	~st_window_contex_info()
	{
		;
	}



}window_contex_t;

template <class render_state >
class PFX_RENDER_SYS_TEMPLATE_API cOn_render_view_base
{
private:
	volatile bool	m_bon_hideview;
	volatile bool	m_bon_resize;
	volatile bool	m_bon_exit;
	volatile bool	m_bhide_complate;
	volatile bool	m_bexit_complate;
protected:
	window_contex_t	m_target;
public:
	PFX_INLINE volatile bool is_on_hideview() const
	{
		return m_bon_hideview;
	}
	PFX_INLINE volatile bool is_on_resize() const
	{
		return m_bon_resize;
	}
	PFX_INLINE volatile bool is_on_exit() const
	{
		return m_bon_exit;
	}
	PFX_INLINE volatile bool is_hide_complate() const
	{
		return m_bhide_complate;
	}
	PFX_INLINE volatile bool is_exit_complate() const
	{
		return m_bexit_complate;
	}

	virtual void set_hideview(bool bEnable)
	{
		m_bon_hideview = bEnable;
	}
	virtual void set_resize(bool bEnable)
	{
		m_bon_resize = bEnable;
	}
	virtual void set_exit(bool bEnable)
	{
		m_bon_exit = bEnable;
	}
	virtual void set_window_context(const window_contex_t& PARAM_IN win_context)
	{
		m_target = win_context;
	}

public:
	virtual void on_hide_complate(bool enable)
	{
		m_bhide_complate = enable;
	}
	virtual void on_exit_complate(bool enable)
	{
		m_bexit_complate = enable;
	}
public:
	cOn_render_view_base(){ ; }
	virtual ~cOn_render_view_base(){ ; }

	virtual void on_view(
		const display_device_t& PARAM_IN device,
		render_state& PARAM_INOUT __state,
		u64_t	__escape_time,
		flag_t& PARAM_OUT msg_type,
		usize__t& PARAM_OUT param_size,
		void*& PARAM_OUT param_data_ptr)
	{
		;
	}

	virtual void on_load(
		const display_device_t& PARAM_IN device,
		render_state& PARAM_INOUT __state,
		u64_t	__escape_time,
		flag_t& PARAM_OUT msg_type,
		usize__t& PARAM_OUT param_size,
		void*& PARAM_OUT param_data_ptr)
	{
		;
	}

	virtual void on_render_complete(
		const display_device_t& PARAM_IN device,
		render_state& PARAM_INOUT __state,
		result_t status)
	{
		;
	}

	virtual void on_closing_render_device(
		u64_t	__escape_time,
		const display_device_t& PARAM_IN device,
		render_state& PARAM_INOUT __state)
	{
		;
	}


	virtual void on_init(window_contex_t& PARAM_OUT win_context)
	{
		win_context = m_target;
	}

	virtual void on_log(result_t status, const char_t* str_info_ptr,
		usize__t str_info_length)
	{
		;
	}

	virtual void on_message_box(result_t status, const char_t* str_info_ptr,
		usize__t str_info_length)
	{
		;
	}


};



PECKER_END

#endif			//PFX_ON_CONTEXT_VIEW_H_
