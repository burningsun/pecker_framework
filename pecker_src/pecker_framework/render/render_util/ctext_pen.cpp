/*
* ctext_pen.cpp
*
*  Created on: 2015-2-17
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#include "ctext_pen.h"

PECKER_BEGIN

ctext_pen::ctext_pen() :m_render_state_ptr(null),
m_shader_program_ptr(null),
m_image_ptr(null),
m_frame_buffer_ptr(null),
m_fontcache_ptr(null),
m_temp_chars_tex_ptr(null),
m_surface_ptr(null)
{
	m_pen_info.m_color.set_color(0.0, 0.0, 0.0, 0.0);
	m_pen_info.m_size = 2;
}
ctext_pen::~ctext_pen()
{
	if (m_shader_program_ptr)
	{
		m_shader_program_ptr->dispose();
		m_shader_program_ptr = null;
	}
	m_render_state_ptr = null;
	if (m_image_ptr)
	{
		m_image_ptr->dispose();
		m_image_ptr = null;
	}

	if (m_frame_buffer_ptr)
	{
		m_frame_buffer_ptr->dispose();
		m_frame_buffer_ptr = null;
	}

	if (m_fontcache_ptr)
	{
		m_fontcache_ptr->dispose();
		m_fontcache_ptr = null;
	}

}

ctext_pen::ctext_pen(const ctext_pen& PARAM_IN __other)
{
	if (this != &__other)
	{
		this->m_pen_info = __other.m_pen_info;
		m_render_state_ptr = __other.m_render_state_ptr;

		this->m_viewport = __other.m_viewport;
		if (__other.m_shader_program_ptr)
		{
			m_shader_program_ptr = __other.m_shader_program_ptr->new_share();
		}
		else
		{
			m_shader_program_ptr = null;
		}

		if (__other.m_image_ptr)
		{
			m_image_ptr = sImage_t::create_new_object();
			m_image_ptr->native() = __other.m_image_ptr->native();
			m_surface_ptr = ctexture_surface::create_new_object();
			m_surface_ptr->update_image(m_image_ptr, 
				PFX_LUMINANCE_8_FMT);
			m_temp_chars_tex_ptr = m_render_state_ptr->create_texture2D();
			m_temp_chars_tex_ptr->update_surface(m_surface_ptr);
			m_temp_chars_tex_ptr->set_texture_filter(PFX_TRN_MIN_FILTER, PFX_TP_NEAREST);
			m_temp_chars_tex_ptr->set_texture_filter(PFX_TRN_MAG_FILTER, PFX_TP_NEAREST);
		}
		else
		{
			m_image_ptr = null;
			m_surface_ptr = null;
			m_temp_chars_tex_ptr = null;
		}

		if (__other.m_frame_buffer_ptr)
		{
			m_frame_buffer_ptr = __other.m_frame_buffer_ptr->new_share();
		}
		else
		{
			m_frame_buffer_ptr = null;
		}

		if (m_fontcache_ptr)
		{
			m_fontcache_ptr = __other.m_fontcache_ptr->new_share();
		}
		else
		{
			m_fontcache_ptr = null;
		}

	}
	
}


result_t ctext_pen::init(const pen_info_t& __pen_info)
{
	return PFX_STATUS_OK;
}
result_t ctext_pen::use()
{
	return PFX_STATUS_OK;
}
result_t ctext_pen::direct_draw()
{
	return PFX_STATUS_OK;
}
result_t ctext_pen::draw_all()
{
	return PFX_STATUS_OK;
}
result_t ctext_pen::dispose_pen()
{
	return PFX_STATUS_OK;
}
result_t ctext_pen::dispose_render_target()
{
	return PFX_STATUS_OK;
}

result_t ctext_pen::set_viewport(const viewport_rect_t& viewport)
{
	m_viewport = viewport;
	return PFX_STATUS_OK;
}
const viewport_rect_t& ctext_pen::get_viewport() const
{
	return m_viewport;
}


result_t ctext_pen::use_render_state(IPfx_render_state* PARAM_IN render_state_ptr)
{
	return PFX_STATUS_OK;
}
IPfx_render_state* ctext_pen::get_render_state() const
{
	return this->m_render_state_ptr;
}

Ipfx_shader_program* ctext_pen::select_program(Ipfx_shader_program* PARAM_IN program_ptr,
	result_t& PARAM_OUT status)
{
	Ipfx_shader_program* old_program_ptr = this->m_shader_program_ptr;
	if (program_ptr)
	{
		this->m_shader_program_ptr = program_ptr->new_share();
		status = PFX_STATUS_OK;
	}
	else
	{
		status = PFX_STATUS_INVALID_PARAMS;
	}
	
	return old_program_ptr;
}
IPfx_framebuffer* ctext_pen::select_frame_buffer(IPfx_framebuffer* PARAM_IN framebuffer_ptr,
	result_t& PARAM_OUT status)
{
	IPfx_framebuffer* old_program_ptr = this->m_frame_buffer_ptr;
	if (framebuffer_ptr)
	{
		this->m_frame_buffer_ptr = framebuffer_ptr->new_share();
		status = PFX_STATUS_OK;
	}
	else
	{
		status = PFX_STATUS_INVALID_PARAMS;
	}

	return old_program_ptr;
}


IPfx_fontcache* ctext_pen::select_fontcache(IPfx_fontcache* PARAM_INOUT fontcache_ptr)
{
	return null;
}

result_t ctext_pen::set_font(IPfx_font* PARAM_IN font_ptr)
{
	return PFX_STATUS_OK;
}

result_t ctext_pen::textout(
	const cstring_ascii_t& PARAM_IN strText,
	const pointf_t& PARAM_IN view_pos,
	const rect_size_t& PARAM_IN text_box_size)
{
	return PFX_STATUS_OK;
}

result_t ctext_pen::textout(
	const cstring_unicode_t& PARAM_IN strText,
	const pointf_t& PARAM_IN view_pos,
	const rect_size_t& PARAM_IN text_box_size)
{
	return PFX_STATUS_OK;
}

result_t ctext_pen::ascii_textout(
	const char* PARAM_IN strText,
	usize__t strTextLen,
	const pointf_t& PARAM_IN view_pos,
	const rect_size_t& PARAM_IN text_box_size)
{
	return PFX_STATUS_OK;
}

PECKER_END
