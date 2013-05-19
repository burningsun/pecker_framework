/*
 * pecker_fragment_operation_gl.cpp
 *
 *  Created on: 2013-4-4
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_fragment_operation_gl.h"
#include <GLES2/gl2.h>
PECKER_BEGIN

static HEnum gFragment_operation_table[ENABLE_FRAGMENT_OPERATION_STATE_COUNT] = {GL_CULL_FACE,
GL_POLYGON_OFFSET_FILL,
GL_SCISSOR_TEST,
GL_SAMPLE_COVERAGE,
GL_SAMPLE_ALPHA_TO_COVERAGE,
GL_STENCIL_TEST,
GL_DEPTH_TEST,
GL_BLEND,
GL_DITHER};

static HEnum gFragment_render_face_table[FRAGMEMT_RENDER_FACE_TYPE_COUNT] = {GL_FRONT, GL_BACK, GL_FRONT_AND_BACK};

static HEnum gStencil_func_table[STENCIL_FUNCTION_TYPE_COUNT] = {GL_EQUAL, GL_NOTEQUAL, GL_LESS,
																															GL_GREATER, GL_LEQUAL, GL_GEQUAL, GL_ALWAYS, GL_NEVER};

static HEnum gStencil_op_table[STENCIL_OPERATION_TYPE_COUNT] = {GL_ZERO,GL_REPLACE,GL_INCR, GL_DECR,
																															GL_INCR_WRAP, GL_DECR_WRAP,GL_KEEP,GL_INVERT};

static HEnum* gDepth_func_table = gStencil_func_table;

static HEnum gBlend_color_func_table[BLEND_COLOR_FUNCION_TYPE_COUNT] = {GL_ZERO,
	GL_ONE , GL_SRC_COLOR , GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, 
	GL_ONE_MINUS_SRC_ALPHA, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_DST_ALPHA, 
	GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR,
	GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA, GL_SRC_ALPHA_SATURATE};

static HEnum gBlend_color_mode_table[BLEND_COLOR_MODE_COUNT] = 
	{GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT,
	GL_BLEND_EQUATION, GL_BLEND_EQUATION_RGB, GL_BLEND_EQUATION_ALPHA};

pecker_fragment_operation_gles2::pecker_fragment_operation_gles2()
{

}

pecker_fragment_operation_gles2::~pecker_fragment_operation_gles2()
{

}

UInt pecker_fragment_operation_gles2::get_object_location() const
{
	return 0;
}

HResult pecker_fragment_operation_gles2::bind_frame_buffer(Ipecker_frame_buffer* pframe_buffer /* = null */)
{
	if (null == pframe_buffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		return pecker_fragment_operation_gles2::get_last_error_code();
	}
	else
	{
		pecker_opengles_v2_object* pgles_object = dynamic_cast< pecker_opengles_v2_object* >(pframe_buffer);
		if (null == pgles_object)
		{
			return P_INVALID_VALUE;
		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER,pgles_object->get_object_location());
		}
		return pecker_fragment_operation_gles2::get_last_error_code();
	}
}

HResult pecker_fragment_operation_gles2::set_clear_mask(BitField bitmask)
{
	//GL_COLOR_BUFFER_BIT
	glClear(bitmask);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::clear_color(Float red,Float green,Float blue,Float alpha_value)
{
	glClearColor(red,green,blue,alpha_value);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::clear_depth(Float depth_value)
{
	glClearDepthf(depth_value);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::clear_stencil(BitField stencil_mask)
{
	glClearStencil(stencil_mask);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_color_mask(Bool red,Bool green,Bool blue,Bool alpha_mask)
{
	glColorMask(red,green,blue,alpha_mask);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_depth_mask(Bool depth_mask)
{
	glDepthMask(depth_mask);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_stencil_mask(BitField stencil_mask)
{
	glStencilMask(stencil_mask);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_stencil_mask(HEnum face, BitField stencil_mask)
{
	if (face >= FRAGMEMT_RENDER_FACE_TYPE_COUNT)
	{
		return P_INVALID_ENUM;
	}
	glStencilMaskSeparate(gFragment_render_face_table[face],stencil_mask);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_scissor_test(SInt x, SInt y, nSize width,nSize heigh)
{
	glScissor(x,y,width,heigh);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_stencil_test_func(HEnum test_func,SInt ref,BitField mask)
{
	if (test_func >= STENCIL_FUNCTION_TYPE_COUNT)
	{
		return P_INVALID_ENUM;
	}
	glStencilFunc(gStencil_func_table[test_func],ref,mask);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_stencil_test_func(HEnum face, HEnum test_func,SInt ref,BitField mask)
{
	if (face >= FRAGMEMT_RENDER_FACE_TYPE_COUNT || test_func >= STENCIL_FUNCTION_TYPE_COUNT)
	{
		return P_INVALID_ENUM;
	}
	glStencilFuncSeparate(gFragment_render_face_table[face],gStencil_func_table[test_func],ref,mask);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_depth_test_func(HEnum test_func)
{
	if (test_func >= DEPTH_TEST_FUNCTION_TYPE_COUNT)
	{
		return P_INVALID_ENUM;
	}
	glDepthFunc(gDepth_func_table[test_func]);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::stencil_test(HEnum s_fial_operation,HEnum z_fial_operation,HEnum z_pass_operation)
{
	if (s_fial_operation >= STENCIL_OPERATION_TYPE_COUNT || 
		z_fial_operation >= STENCIL_OPERATION_TYPE_COUNT || 
		z_pass_operation >= STENCIL_OPERATION_TYPE_COUNT)
	{
		return P_INVALID_ENUM;
	}
	glStencilOp(gStencil_op_table[s_fial_operation],
		gStencil_op_table[z_fial_operation],gStencil_op_table[z_pass_operation]);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::stencil_test(HEnum face,HEnum s_fial_operation,HEnum z_fial_operation,HEnum z_pass_operation)
{
	if (face >= FRAGMEMT_RENDER_FACE_TYPE_COUNT ||
		s_fial_operation >= STENCIL_OPERATION_TYPE_COUNT || 
		z_fial_operation >= STENCIL_OPERATION_TYPE_COUNT || 
		z_pass_operation >= STENCIL_OPERATION_TYPE_COUNT)
	{
		return P_INVALID_ENUM;
	}
	glStencilOpSeparate(gFragment_render_face_table[face],
		gStencil_op_table[s_fial_operation],gStencil_op_table[z_fial_operation],
		gStencil_op_table[z_pass_operation]);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_blend_func(HEnum src_factor,HEnum dst_factor)
{
	if (src_factor >= BLEND_COLOR_FUNCION_TYPE_COUNT ||
		dst_factor >= BLEND_COLOR_FUNCION_TYPE_COUNT)
	{
		return P_INVALID_ENUM;
	}
	glBlendFunc(gBlend_color_func_table[src_factor],gBlend_color_func_table[dst_factor]);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_blend_func(HEnum src_rgb_factor,HEnum dst_rgb_factor,HEnum src_alpha_factor,HEnum dst_alpha_factor)
{
	if (src_rgb_factor >= BLEND_COLOR_FUNCION_TYPE_COUNT ||
		dst_rgb_factor >= BLEND_COLOR_FUNCION_TYPE_COUNT ||
		src_alpha_factor >= BLEND_COLOR_FUNCION_TYPE_COUNT ||
		dst_alpha_factor >= BLEND_COLOR_FUNCION_TYPE_COUNT)
	{
		return P_INVALID_ENUM;
	}
	glBlendFuncSeparate(gBlend_color_func_table[src_rgb_factor],
		gBlend_color_func_table[dst_rgb_factor],
		gBlend_color_func_table[src_alpha_factor],
		gBlend_color_func_table[dst_alpha_factor]);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_blend_color(Float red,Float green,Float blue,Float alpha_value)
{
	glBlendColor(red,green,blue,alpha_value);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_blend_equation(HEnum color_mode)
{
	if (color_mode >=BLEND_COLOR_MODE_COUNT)
	{
		return P_INVALID_ENUM;
	}
	glBlendEquation(gBlend_color_mode_table[color_mode]);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_blend_equation(HEnum rgb_mode,HEnum alpha_mode)
{
	if (rgb_mode >=BLEND_COLOR_MODE_COUNT ||
		alpha_mode >= BLEND_COLOR_MODE_COUNT)
	{
		return P_INVALID_ENUM;
	}
	glBlendEquationSeparate(gBlend_color_mode_table[rgb_mode],
		gBlend_color_mode_table[alpha_mode]);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::set_sample_coverage(Float value_,Bool invert)
{
	glSampleCoverage(value_,invert);
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_fragment_operation_gles2::bind_frame_buffer_object(Ipecker_frame_buffer_object* pframe_buffer_object)
{
	if (null != pframe_buffer_object)
	{
		return pframe_buffer_object->bind();
	}
	else
	{
		return P_INVALID_VALUE;
	}
}

Bool pecker_fragment_operation_gles2::enable_state(HEnum state)
{
	if (state >= ENABLE_FRAGMENT_OPERATION_STATE_COUNT)
	{
		return false;
	}
	state = gFragment_operation_table[state];
	glEnable(state);
	return glIsEnabled(state);
}
Bool pecker_fragment_operation_gles2::disable_state(HEnum state)
{
	if (state >= ENABLE_FRAGMENT_OPERATION_STATE_COUNT)
	{
		return false;
	}

	state = gFragment_operation_table[state];
	glDisable(state);
	return !(glIsEnabled(state));
}
Bool pecker_fragment_operation_gles2::is_enable(HEnum state) const
{
	if (state >= ENABLE_FRAGMENT_OPERATION_STATE_COUNT)
	{
		return false;
	}
	state = gFragment_operation_table[state];
	return glIsEnabled(state);
}
PECKER_END