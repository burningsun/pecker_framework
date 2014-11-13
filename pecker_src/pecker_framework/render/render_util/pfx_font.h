/*
 * pfx_font.h
 *
 *  Created on: 2014-11-11
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_FONT_H_
#define		PFX_FONT_H_

#include "../../include/config"
#include "../../include/util"
#include "../../include/cstring_pfx.h"
#include "../../include/cshare_object.h"
#include "../pfx_color.h"
#include "../render_system/pfx_shader_program.h"
#include "../../math/pfx_math.h"

PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN


typedef struct st_font_info
{
	colorf_t m_color;
	usize__t m_size;
	usize__t m_render_dpi;

	st_font_info() :m_size(16), m_render_dpi(64)
	{
		;
	}
	st_font_info(colorf_t __color, 
		usize__t __size, 
		usize__t __dpi) :m_color(__color), 
		m_size(__size), 
		m_render_dpi(__dpi)
	{
		;
	}
	st_font_info(bitfield_t __color,
		usize__t __size,
		usize__t __dpi) :m_color(__color),
		m_size(__size),
		m_render_dpi(__dpi)
	{
		;
	}
}font_info_t;

typedef struct st_render_text_info
{
	pointf_t m_tex_coord;
	colorf_t m_color;
}render_text_info_t;

PFX_Interface IPfx_font : public creference_root
{
	virtual ~IPfx_font(){ ; }

	virtual result_t init_font(const cstring_ascii_t& PARAM_IN str_font_name) = 0;
	virtual result_t set_info(const font_info_t& PARAM_IN _info) = 0;
	virtual result_t set_rbuffer_cache_size(const rect_size_t& __size) = 0;
	virtual result_t set_cache_size(usize__t __size) = 0;
	virtual result_t bind_string_texture(const cstring_ascii_t& PARAM_IN str_text,
		render_text_info_t& PARAM_OUT __info) = 0;
	virtual result_t clean_cache() = 0;
	virtual result_t dispose_render_target() = 0;
};

PECKER_END

#endif			//PFX_FONT_H_
