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
#include "../pfx_image.h"

PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

typedef struct st_font_style
{
	nsize__t m_border_size;
	nsize__t m_angle_degree;
}font_style_t;

typedef struct st_font_info
{
	usize__t		m_size;
	usize__t		m_render_dpi;
	font_style_t    m_style;
	cstring_ascii_t m_font_name;
}font_info_t;



PFX_Interface IPfx_renderchar
{
	virtual ~IPfx_renderchar(){ ; }
	virtual result_t draw_char(const image_bits* PARAM_IN gray_image_ptr,
		coord_t draw_X,
		coord_t draw_Y)= 0;
};

PFX_Interface IPfx_font : public creference_root
{
	virtual ~IPfx_font(){ ; }

	virtual result_t init(const font_info_t& PARAM_IN font_info) = 0;
	virtual result_t dispose() = 0;

	virtual result_t render_char(ulong_t char_code, 
		IPfx_renderchar* PARAM_IN render_char_ptr, 
		coord_t x = -1, coord_t y = -1) = 0;

	virtual const font_info_t& get_font_info() const = 0;

	virtual bool equal_to(const IPfx_font* PARAM_IN other_ptr) const = 0;
};


PECKER_END

#endif			//PFX_FONT_H_
