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
	usize__t		m_sizex;
	usize__t        m_sizey;
	usize__t		m_ptx_count;
	usize__t		m_pty_count;
	usize__t		m_render_dpix;
	usize__t		m_render_dpiy;

	font_style_t    m_style;
	cstring_ascii_t m_font_name;
}font_info_t;

struct font_info_compare
{
	typedef font_info_t	element_t;

	PFX_INLINE int operator () (const element_t& info1, const element_t& info2) const
	{
		return compare(info1, info2);
	}

	static PFX_INLINE int compare(const element_t& info1, const element_t& info2)
	{
		int cmp_result = 0;
		FOR_ONE_LOOP_BEGIN
		int temp1;
		int temp2;

		temp1 = (int)((info1.m_sizex) ? (info1.m_sizex) : (info1.m_sizey));
		temp2 = (int)((info2.m_sizex) ? (info2.m_sizex) : (info2.m_sizey));

		cmp_result = temp1 - temp2;
		BREAK_LOOP_CONDITION(0 != cmp_result);

		temp1 = (int)((info1.m_sizey) ? (info1.m_sizey) : (info1.m_sizex));
		temp2 = (int)((info2.m_sizey) ? (info2.m_sizey) : (info2.m_sizex));

		cmp_result = temp1 - temp2;
		BREAK_LOOP_CONDITION(0 != cmp_result);
		
		temp1 = (int)((info1.m_ptx_count) ? (info1.m_ptx_count) : (info1.m_pty_count));
		temp2 = (int)((info2.m_ptx_count) ? (info2.m_ptx_count) : (info2.m_pty_count));

		cmp_result = temp1 - temp2;
		BREAK_LOOP_CONDITION(0 != cmp_result);

		temp1 = (int)((info1.m_pty_count) ? (info1.m_pty_count) : (info1.m_ptx_count));
		temp2 = (int)((info2.m_pty_count) ? (info2.m_pty_count) : (info2.m_ptx_count));

		cmp_result = temp1 - temp2;
		BREAK_LOOP_CONDITION(0 != cmp_result);


		temp1 = (int)((info1.m_render_dpix) ? (info1.m_render_dpix) : (info1.m_render_dpiy));
		temp2 = (int)((info2.m_render_dpix) ? (info2.m_render_dpix) : (info2.m_render_dpiy));

		cmp_result = temp1 - temp2;
		BREAK_LOOP_CONDITION(0 != cmp_result);

		temp1 = (int)((info1.m_render_dpiy) ? (info1.m_render_dpiy) : (info1.m_render_dpix));
		temp2 = (int)((info2.m_render_dpiy) ? (info2.m_render_dpiy) : (info2.m_render_dpix));

		cmp_result = temp1 - temp2;
		BREAK_LOOP_CONDITION(0 != cmp_result);

		cmp_result = (int)info1.m_style.m_border_size - (int)info2.m_style.m_border_size;
		BREAK_LOOP_CONDITION(0 != cmp_result);

		cmp_result = (int)info1.m_style.m_angle_degree - (int)info2.m_style.m_angle_degree;
		BREAK_LOOP_CONDITION(0 != cmp_result);

		cmp_result = cascii_string_compare_t::compare(info1.m_font_name, info2.m_font_name);
		FOR_ONE_LOOP_END

		return cmp_result;
	}

};



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

	virtual PFX_INLINE bool equal_to(const IPfx_font* PARAM_IN other_ptr) const
	{
		RETURN_INVALID_RESULT(null == other_ptr, false);
		return equal_to(other_ptr->get_font_info());
	}

	virtual PFX_INLINE bool equal_to(const font_info_t& PARAM_IN other_info) const
	{
		return 	(!(bool)font_info_compare::compare(get_font_info(), other_info));
	}
};


PECKER_END

#endif			//PFX_FONT_H_
