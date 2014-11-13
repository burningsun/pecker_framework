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

	virtual result_t set_pen_info(const pen_info_t& __pen_info) = 0;
	virtual result_t set_fill_brush(IPfx_brush* _brush_ptr = null) = 0;

	virtual result_t use() = 0;

	virtual result_t lineTo(const VECTOR4F_t& next_pos) = 0;
	virtual result_t lineTo(const VECTOR3F_t& next_pos) = 0;
	virtual result_t lineTo(const VECTOR2F_t& next_pos) = 0;

	virtual result_t save_line() = 0;
	virtual result_t clear_all_line() = 0;

	virtual bool has_lines() const = 0;

	virtual result_t clear_line() = 0;

	virtual result_t draw() = 0;
	virtual result_t draw_all() = 0;

	virtual result_t dispose_pen() = 0;

	virtual result_t dispose_render_target() = 0;
};

PECKER_END

#endif			//PFX_PEN_H_
