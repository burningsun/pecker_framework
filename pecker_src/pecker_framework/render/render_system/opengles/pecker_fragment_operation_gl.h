/*
 * pecker_fragment_operation_gl.h
 *
 *  Created on: 2013-4-4
 *      Author: ¿Ó’Ú≥«  £® cut / cutxyz£©
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_FRAME_BUFFER_GL_H_
#define  PECKER_FRAME_BUFFER_GL_H_

#include "pecker_opengles_object.h"
#include "../pecker_fragment_operation.h"

PECKER_BEGIN

class  pecker_fragment_operation_gles2 : public Ipecker_fragment_operation,public virtual pecker_opengles_v2_object
{
public:
	pecker_fragment_operation_gles2();
	virtual ~pecker_fragment_operation_gles2();
	virtual UInt get_object_location() const;
public:
	HResult bind_frame_buffer(Ipecker_frame_buffer* pframe_buffer = null);
	HResult set_clear_mask(BitField bitmask);
	HResult clear_color(Float red,Float green,Float blue,Float alpha_value);
	HResult clear_depth(Float depth_value);
	HResult clear_stencil(BitField stencil_mask);

	HResult set_color_mask(Bool red,Bool green,Bool blue,Bool alpha_mask);
	HResult set_depth_mask(Bool depth_mask);
	HResult set_stencil_mask(BitField stencil_mask);
	HResult set_stencil_mask(HEnum face, BitField stencil_mask);

	HResult set_scissor_test(SInt x, SInt y, nSize width,nSize heigh);
	HResult set_stencil_test_func(HEnum test_func,SInt ref,BitField mask);
	HResult set_stencil_test_func(HEnum face, HEnum test_func,SInt ref,BitField mask);

	HResult set_depth_test_func(HEnum test_func);

	HResult stencil_test(HEnum s_fial_operation,HEnum z_fial_operation,HEnum z_pass_operation);
	HResult stencil_test(HEnum face,HEnum s_fial_operation,HEnum z_fial_operation,HEnum z_pass_operation);

	HResult set_blend_func(HEnum src_factor,HEnum dst_factor);
	HResult set_blend_func(HEnum src_rgb_factor,HEnum dst_rgb_factor,HEnum src_alpha_factor,HEnum dst_alpha_factor);

	HResult set_blend_color(Float red,Float green,Float blue,Float alpha_value);

	HResult set_blend_equation(HEnum color_mode);
	HResult set_blend_equation(HEnum rgb_mode,HEnum alpha_mode);

	HResult set_sample_coverage(Float value_,Bool invert);

	HResult bind_frame_buffer_object(Ipecker_frame_buffer_object* pframe_buffer_object);


};

PECKER_END

#endif //PECKER_FRAME_BUFFER_GL_H_