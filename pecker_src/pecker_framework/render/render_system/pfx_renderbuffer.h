/*
 * pfx_renderbuffer.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDERBUFFER_H_
#define		PFX_RENDERBUFFER_H_

#include "../../pfx_defines.h"
#include "../pfx_render_type.h"

PECKER_BEGIN

typedef enum enumRENDER_BUFFER_TYPE
{
	PFX_COLOR_BUFFER_TYPE,
	PFX_DEPTH_BUFFER_TYPE,
	PFX_STENCIL_BUFFER_TYPE,

	PFX_RENDER_BUFFER_TYPE_COUNT
}PFX_RENDER_BUFFER_TYPE_t;

typedef enum enumCOLOR_BUFFER_TYPE
{
	PFX_CBT_RGB565	= 0,
	PFX_CBT_RGBA4,
	PFX_CBT_RGB5_A1,
	
	PFX_CBT_OES_TYPE,
	PFX_CBT_RGB8,
	PFX_CBT_RGBA8,

	PFX_COLOR_BUFFER_TYPE_COUNT

}PFX_COLOR_BUFFER_TYPE_t;

PFX_INLINE PFX_PIXEL_COLOR_FORMAT_t* GET_COLOR_BUFFER_COLOR_SIZE 
	(PFX_COLOR_BUFFER_TYPE_t type_,PFX_PIXEL_COLOR_FORMAT_t* PARAM_INOUT format_)
{
	RETURN_INVALID_RESULT (null == format_,null);

	switch (type_)
	{
	case PFX_CBT_RGB565:
		format_->m_red_size		= 5;
		format_->m_green_size	= 6;
		format_->m_blue_size		= 5;
		format_->m_alpha_size		= 0;
		break;
	case PFX_CBT_RGBA4:
		format_->m_red_size		= 4;
		format_->m_green_size	= 4;
		format_->m_blue_size		= 4;
		format_->m_alpha_size		= 4;
		break;
	case PFX_CBT_RGB5_A1:
		format_->m_red_size		= 5;
		format_->m_green_size	= 5;
		format_->m_blue_size		= 5;
		format_->m_alpha_size		= 1;
		break;
	case PFX_CBT_RGB8:
		format_->m_red_size		= 8;
		format_->m_green_size	= 8;
		format_->m_blue_size		= 8;
		format_->m_alpha_size		= 0;
		break;
	case PFX_CBT_RGBA8:
		format_->m_red_size		= 8;
		format_->m_green_size	= 8;
		format_->m_blue_size		= 8;
		format_->m_alpha_size		= 8;
		break;
	default:
		format_ = null;
		break;
	}
	return format_;
}

typedef enum enumDEPTH_BUFFER_TYPE
{
	PFX_DEPTH_COMPONENT16 = 0,

	PFX_DEPTH_OES_TYPE,
	PFX_DEPTH_COMPONENT24,
	PFX_DEPTH_COMPONENT32,

	PFX_DEPTH_BUFFER_TYPE_COUNT
}PFX_DEPTH_BUFFER_TYPE_t;

PFX_INLINE pfx_usize_t GET_DEPTH_BUFFER_FORMAT_SIZE (PFX_DEPTH_BUFFER_TYPE_t type_)
{
	pfx_usize_t size_;
	switch (type_)
	{
	case PFX_DEPTH_COMPONENT16:
		size_ = 16;
		break;
	case PFX_DEPTH_COMPONENT24:
		size_ = 24;
		break;
	case PFX_DEPTH_COMPONENT32:
		size_ = 32;
		break;
	default:
		size_ = 0;
		break;
	}
	return size_;
}

typedef enum enumSTENCIL_BUFFER_TYPE
{
	PFX_STENCIL_INDEX8 = 0,

	PFX_STENCIL_OES_TYPE,
	PFX_STENCIL_INDEX1,
	PFX_STENCIL_INDEX4,

	PFX_STENCIL_BUFFER_TYPE_COUNT
}PFX_STENCIL_BUFFER_TYPE_t;

PFX_INLINE pfx_usize_t GET_STENCIL_BUFFER_FORMAT_SIZE ( PFX_STENCIL_BUFFER_TYPE_t type_)
{
	pfx_usize_t size_;

	switch (type_)
	{
		case PFX_STENCIL_INDEX8:
			size_ = 8;
			break;
		case PFX_STENCIL_INDEX1:
			size_ = 1;
			break;
		case PFX_STENCIL_INDEX4:
			size_ = 4;
			break;
		default:
			size_ = 0;
			break;
	}
	return size_;
}

PFX_Interface Ipfx_color_buffer
{
	virtual pfx_result_t init_color_buffer (PFX_COLOR_BUFFER_TYPE_t type_,
		pfx_usize_t width,pfx_usize_t height) = 0;

	virtual pfx_result_t dispose_color_buffer () = 0;
	//////////////////////////////////////////////////////////////////////////
	//virtual pfx_result_t begin_setting_color_buffer () = 0;
	//virtual pfx_result_t end_setting_color_buffer (pfx_boolean_t flag = pfx_false) = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_long_t get_color_buffer_target () = 0;

	virtual pfx_usize_t get_width () const = 0;
	virtual pfx_usize_t get_height () const = 0;
	virtual pfx_result_t get_format (PFX_COLOR_BUFFER_TYPE_t& PARAM_OUT format_) = 0;
	//////////////////////////////////
	virtual ~Ipfx_color_buffer() {;};
};

PFX_Interface Ipfx_depth_buffer
{
	virtual pfx_result_t init_depth_buffer (PFX_DEPTH_BUFFER_TYPE_t type_,
		pfx_usize_t width,pfx_usize_t height) = 0;

	virtual pfx_result_t dispose_depth_buffer () = 0;
	//////////////////////////////////////////////////////////////////////////
	//virtual pfx_result_t begin_setting_depth_buffer () = 0;
	//virtual pfx_result_t end_setting_depth_buffer (pfx_boolean_t flag = pfx_false) = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_long_t get_depth_buffer_target () = 0;

	virtual pfx_usize_t get_width () const = 0;
	virtual pfx_usize_t get_height () const = 0;
	virtual pfx_result_t get_format (PFX_DEPTH_BUFFER_TYPE_t& PARAM_OUT format_) = 0;
	//////////////////////////////////
	virtual ~Ipfx_depth_buffer() {;};
};

PFX_Interface Ipfx_stencil_buffer
{
	virtual pfx_result_t init_stencil_buffer (PFX_STENCIL_BUFFER_TYPE_t type_,
		pfx_usize_t width,pfx_usize_t height) = 0;

	virtual pfx_result_t dispose_stencil_buffer () = 0;
	//////////////////////////////////////////////////////////////////////////
	//virtual pfx_result_t begin_setting_stencil_buffer () = 0;
	//virtual pfx_result_t end_setting_stencil_buffer (pfx_boolean_t flag = pfx_false) = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_long_t get_stencil_buffer_target () = 0;

	virtual pfx_usize_t get_width () const = 0;
	virtual pfx_usize_t get_height () const = 0;
	virtual pfx_result_t get_format (PFX_STENCIL_BUFFER_TYPE_t& PARAM_OUT format_) = 0;
	//////////////////////////////////
	virtual ~Ipfx_stencil_buffer() {;};
};

PECKER_END

#endif			//PFX_RENDERBUFFER_H_
