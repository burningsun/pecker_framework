/*
 * pecker_fragment_operation.h
 *
 *  Created on: 2013-3-17
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_FRAGMET_OPERATION_H_
#define  PECKER_FRAGMET_OPERATION_H_

#include "pecker_frame_buffer.h"

PECKER_BEGIN


PeckerInterface Ipecker_fragment_operation
{
	virtual ~Ipecker_fragment_operation(){;}
	//virtual HResult switch_to_defualf_framebuffer() = 0;
	virtual HResult bind_frame_buffer(Ipecker_frame_buffer* pframe_buffer = null) = 0;
	virtual HResult set_clear_mask(BitField bitmask) = 0;
	virtual HResult clear_color(Float red,Float green,Float blue,Float alpha_value) = 0;
	virtual HResult clear_depth(Float depth_value) = 0;
	virtual HResult clear_stencil(BitField stencil_mask) = 0;

	virtual HResult set_color_mask(Bool red,Bool green,Bool blue,Bool alpha_mask) = 0;
	virtual HResult set_depth_mask(Bool depth_mask) = 0;
	virtual HResult set_stencil_mask(BitField stencil_mask) = 0;
	virtual HResult set_stencil_mask(HEnum face, BitField stencil_mask) = 0;

	virtual HResult set_scissor_test(SInt x, SInt y, nSize width,nSize heigh) = 0;
	virtual HResult set_stencil_test_func(HEnum test_func,SInt ref,BitField mask) = 0;
	virtual HResult set_stencil_test_func(HEnum face, HEnum test_func,SInt ref,BitField mask) = 0;

	virtual HResult set_depth_test_func(HEnum test_func) = 0;

	virtual HResult stencil_test(HEnum s_fial_operation,HEnum z_fial_operation,HEnum z_pass_operation) = 0;
	virtual HResult stencil_test(HEnum face,HEnum s_fial_operation,HEnum z_fial_operation,HEnum z_pass_operation) = 0;

	virtual HResult set_blend_func(HEnum src_factor,HEnum dst_factor) = 0;
	virtual HResult set_blend_func(HEnum src_rgb_factor,HEnum dst_rgb_factor,HEnum src_alpha_factor,HEnum dst_alpha_factor) = 0;

	virtual HResult set_blend_color(Float red,Float green,Float blue,Float alpha_value) = 0;

	virtual HResult set_blend_equation(HEnum color_mode) = 0;
	virtual HResult set_blend_equation(HEnum rgb_mode,HEnum alpha_mode) = 0;

	virtual HResult set_sample_coverage(Float value_,Bool invert) = 0;

	virtual HResult bind_frame_buffer_object(Ipecker_frame_buffer_object* pframe_buffer_object) = 0;

	
};


PECKER_END

#endif //PECKER_FRAGMET_OPERATION_H_