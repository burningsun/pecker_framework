/*
* pfx_pen.h
*
*  Created on: 2014-11-11
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#ifndef		PFX_PEN_H_
#define		PFX_PEN_H_

#include "../../include/config"
#include "../../include/util"
#include "../../include/cshare_object.h"
#include "../pfx_color.h"
#include "../render_system/pfx_shader_program.h"
#include "../render_system/pfx_framebuffer_object.h"
#include "../render_system/pfx_render_state.h"
#include "../../math/pfx_math.h"
#include "pfx_brush.h"

PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

typedef struct st_pen_info
{
	colorf_t m_color;
	nsize__t m_size;
}pen_info_t;

PFX_Interface IPfx_pen : public creference_root
{
	virtual ~IPfx_pen(){ ; }

	virtual result_t init(const pen_info_t& __pen_info) = 0;
	virtual result_t use() = 0;
	virtual result_t direct_draw() = 0;
	virtual result_t draw_all() = 0;
	virtual result_t dispose_pen() = 0;
	virtual result_t dispose_render_target() = 0;

	virtual result_t set_viewport(const viewport_rect_t& viewport) = 0;
	virtual const viewport_rect_t& get_viewport() const = 0;

	virtual result_t use_render_state(IPfx_render_state* PARAM_IN render_state_ptr) = 0;
	virtual IPfx_render_state* get_render_state() const = 0;

	virtual Ipfx_shader_program* select_program(Ipfx_shader_program* PARAM_IN program_ptr, 
		result_t& PARAM_OUT status) = 0;
	virtual IPfx_framebuffer* select_frame_buffer(IPfx_framebuffer* PARAM_IN framebuffer_ptr) = 0;
};

PECKER_END

#endif			//PFX_PEN_H_
