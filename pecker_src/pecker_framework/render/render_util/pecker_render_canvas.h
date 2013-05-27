/*
 * pecker_render_canvas.h
 *
 *  Created on: 2013-5-27
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_RENDER_CANVAS_H_
#define  PECKER_RENDER_CANVAS_H_

#include "../pecker_render_object.h"
#include "../render_system/pecker_render_system_defines.h"
#include "../../data/pecker_shape.h"

PECKER_BEGIN

class pecker_render_canvas_base
{
private:
	Ipecker_render_device* _M_render_device;
	Ipecker_frame_buffer*	  _M_frame_buffer;
	Ipecker_fragment_operation* _M_fragment_operation;
	
public:
	pecker_render_canvas_base();
	virtual ~pecker_render_canvas_base();
public:
	HResult init_canvas();
	HResult deinit_canvas();
	HResult config_canvas();

	Ipecker_fragment_operation* get_fragment_operation() const;

	HResult fill_color(const pecker_color& color);
	HResult clear_mask(BitField bitmask);
	HResult clear_depth(Float depth_value);
	HResult clear_stencil(BitField stencil_mask);

	HResult begin_draw(HEnum  draw_type,Ipecker_gpu_program* pgpu_program = 0);
	HResult end_draw();

	HResult draw_rect2d();
	HResult draw_triangle2d();
	HResult draw_line2d();
	HResult draw_dot2d();
	HResult draw_cycle2d();
	HResult draw_curve2d();

	HResult draw_rect();
	HResult draw_triangle();
	HResult draw_line();
	HResult draw_dot();
	HResult draw_cycle();
	HResult draw_curve();

	HResult draw_cube();
	HResult draw_boll();
	
	HResult set_texture(HEnum sample,const Ipecker_texture* pTexture);
	HResult draw_texture(HEnum sample,const Ipecker_shape_logic* pdsc_shape,const Ipecker_shape_logic* psrc_shape);

	HResult select_pen();
	HResult set_mvp();




	HResult draw_array();
	HResult draw_element();

};

PECKER_END

#endif //PECKER_RENDER_CANVAS_H_
