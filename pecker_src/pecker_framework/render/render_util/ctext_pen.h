/*
* ctext_pen.h
*
*  Created on: 2015-2-17
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#ifndef		CTEXT_PEN_H_
#define		CTEXT_PEN_H_

#include "pfx_text_pen.h"


PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN



class ctext_pen : public IPfx_text_pen
{
private:
	IPfx_render_state* m_render_state_ptr;
	Ipfx_shader_program* m_shader_program_ptr = null;
public:
	ctext_pen();
	virtual ~ctext_pen();
public:
	virtual result_t init(const pen_info_t& __pen_info);
	virtual result_t use();
	virtual result_t direct_draw();
	virtual result_t draw_all();
	virtual result_t dispose_pen();
	virtual result_t dispose_render_target();

	virtual result_t set_viewport(const viewport_rect_t& viewport);
	virtual const viewport_rect_t& get_viewport() const;

public:
	virtual result_t use_render_state(IPfx_render_state* PARAM_IN render_state_ptr);
	virtual IPfx_render_state* get_render_state() const;

	virtual Ipfx_shader_program* select_program(Ipfx_shader_program* PARAM_IN program_ptr,
		result_t& PARAM_OUT status);
	virtual IPfx_framebuffer* select_frame_buffer(IPfx_framebuffer* PARAM_IN framebuffer_ptr);

public:
	virtual IPfx_fontcache* select_fontcache(IPfx_fontcache* PARAM_INOUT fontcache_ptr);

	virtual result_t set_font(IPfx_font* PARAM_IN font_ptr);

	virtual result_t textout(
		const cstring_ascii_t& PARAM_IN strText,
		const pointf_t& PARAM_IN view_pos,
		const rect_size_t& PARAM_IN text_box_size);

	virtual result_t textout(
		const cstring_unicode_t& PARAM_IN strText,			
		const pointf_t& PARAM_IN view_pos,
		const rect_size_t& PARAM_IN text_box_size);

	virtual result_t ascii_textout(
		const char* PARAM_IN strText,
		usize__t strTextLen,
		const pointf_t& PARAM_IN view_pos,
		const rect_size_t& PARAM_IN text_box_size);
};


PECKER_END

#endif			//CTEXT_PEN_H_
