/*
 * pfx_	framebuffer_opengles.cpp
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */



#include "pfx_framebuffer_opengles.h"

PECKER_BEGIN


CPfx_framebuffer_opengles2::~CPfx_framebuffer_opengles2()
{
	;
} 

pfx_result_t CPfx_framebuffer_opengles2::init_framebuffer (PFX_FRAME_BUFFER_TYPE_t type_)
{
	return 0;
}
pfx_result_t CPfx_framebuffer_opengles2::dispose_framebuffer()
{
	return 0;
}
	//////////////////////////////////////////////////////////////////////////
pfx_result_t CPfx_framebuffer_opengles2::begin_setting_framebuffer(pfx_enum_t type_ /*= PFX_FRAME_BUFFER_TYPE*/)
{
	return 0;
}
pfx_result_t CPfx_framebuffer_opengles2::end_setting_framebuffer(pfx_boolean_t flag /*= pfx_false*/)
{
	return 0;
}
	//////////////////////////////////////////////////////////////////////////
pfx_result_t CPfx_framebuffer_opengles2::check_attach_complete()
{
	return 0;
}
	//////////////////////////////////////////////////////////////////////////
pfx_result_t CPfx_framebuffer_opengles2::attach_renderbuffer (Ipfx_color_buffer* PARAM_INOUT colorbuffer,
		pfx_index_t attach_unit/* = 0*/)
{
	return 0;
}
pfx_result_t CPfx_framebuffer_opengles2::attach_renderbuffer (Ipfx_depth_buffer* PARAM_INOUT colorbuffer,
		pfx_index_t attach_unit /*= 0*/)
{
	return 0;
}
pfx_result_t CPfx_framebuffer_opengles2::attach_renderbuffer (Ipfx_stencil_buffer* PARAM_INOUT colorbuffer,
		pfx_index_t attach_unit /*= 0*/)
{
	return 0;
}
	//////////////////////////////////////////////////////////////////////////
pfx_result_t CPfx_framebuffer_opengles2::attach_texture (Ipfx_texture* PARAM_INOUT texture,
		PFX_RENDER_BUFFER_TYPE_t attach_type_,
		PFX_TEXTURE_SURFACE_TYPE_t attach_texture_surface /*= PFX_TEXTURE_DEFUALT_SURFACE*/,
		pfx_index_t mip_lever /*= 0*/,
		pfx_index_t attach_unit /*= 0*/)
{
	return 0;
}





CPfx_framebuffer_operation_opengles2::~CPfx_framebuffer_operation_opengles2() 
{
	;
};
	//////////////////////////////////////////////////////////////////////////
pfx_result_t CPfx_framebuffer_operation_opengles2::set_viewport (pfx_index_t x,pfx_index_t y,
		pfx_usize_t width,pfx_usize_t height)
{
	return 0;
}
	
pfx_result_t CPfx_framebuffer_operation_opengles2::set_depthrange(pfx_float_t near_,
		pfx_float_t far_)
{
	return 0;
}
	////////////////////////////////////////////////

pfx_result_t CPfx_framebuffer_operation_opengles2::clear_buffer (pfx_bitfield_t mask)
{
	return 0;
}

pfx_result_t CPfx_framebuffer_operation_opengles2::clear_color (pfx_bitfield_t rgba_)
{
	return 0;
}
pfx_result_t CPfx_framebuffer_operation_opengles2::clear_color (const pfx_color_t& PARAM_IN rgba_)
{
	return 0;
}

pfx_result_t CPfx_framebuffer_operation_opengles2::clear_depth (pfx_float_t depth_)
{
	return 0;
}

pfx_result_t CPfx_framebuffer_operation_opengles2::clear_stencil (pfx_bitfield_t stencil)
{
	return 0;
}
	//////////////////////////////////////////////////////////////////////////
pfx_result_t CPfx_framebuffer_operation_opengles2::color_mask (pfx_boolean_t red_,
															pfx_boolean_t green_,
															pfx_boolean_t blue_,
															pfx_boolean_t alpha_)
{
	return 0;
}
pfx_result_t CPfx_framebuffer_operation_opengles2::depth_mask (pfx_boolean_t depth_ ) 
{
	return 0;
}
pfx_result_t CPfx_framebuffer_operation_opengles2::stencil_mask (pfx_bitfield_t mask_)
{
	return 0;
}
	//////////////////////////////////////////////////////////////////////////
pfx_result_t CPfx_framebuffer_operation_opengles2::enable_test (PFX_FRAGMENT_TEST_ENABLE_TOKENS_t type_)
{
	return 0;
}
pfx_result_t CPfx_framebuffer_operation_opengles2::disable_test (PFX_FRAGMENT_TEST_ENABLE_TOKENS_t type_)
{
	return 0;
}
	//////////////////////////////////////////////////////////////////////////
pfx_result_t CPfx_framebuffer_operation_opengles2::set_scissor_test (pfx_index_t x,pfx_index_t y,
		pfx_usize_t width,pfx_usize_t height)
{
	return 0;
}

pfx_result_t CPfx_framebuffer_operation_opengles2::set_stencil_function (PFX_FRAGMENT_TEST_FUNCION_t function_,
		pfx_bitfield_t comarison_value,
		pfx_bitfield_t mask_)
{
	return 0;
}
pfx_result_t CPfx_framebuffer_operation_opengles2::set_stencil_operation (PFX_FRAGMENT_TEST_OPERATES_t stencil_fail_,
																			PFX_FRAGMENT_TEST_OPERATES_t depth_fail_,
																			PFX_FRAGMENT_TEST_OPERATES_t pass_)
{
	return 0;
}

pfx_result_t CPfx_framebuffer_operation_opengles2::set_depth_function (PFX_FRAGMENT_TEST_OPERATES_t cmp_func) 
{
	return 0;
}

pfx_result_t CPfx_framebuffer_operation_opengles2::set_blend_function (PFX_BLEND_FUNCTIONS_t source_factor,
																		PFX_BLEND_FUNCTIONS_t destination_factor)
{
	return 0;
}

pfx_result_t CPfx_framebuffer_operation_opengles2::set_blend_function (PFX_BLEND_FUNCTIONS_t source_RGB_factor,
																		PFX_BLEND_FUNCTIONS_t destination_RGB_factor,
																		PFX_BLEND_FUNCTIONS_t source_Alpha_factor,
																		PFX_BLEND_FUNCTIONS_t destination_Alpha_factor)
{
	return 0;
}

pfx_result_t CPfx_framebuffer_operation_opengles2::set_blend_equation (PFX_BLEND_MODE_t mode_)
{
	return 0;
}
pfx_result_t CPfx_framebuffer_operation_opengles2::set_blend_equation (PFX_BLEND_MODE_t RGB_mode,
																		PFX_BLEND_MODE_t Alpha_mode)
{
	return 0;
}

pfx_result_t CPfx_framebuffer_operation_opengles2::set_color_function (const pfx_color_t& color_)
{
	return 0;
}
pfx_result_t CPfx_framebuffer_operation_opengles2::set_color_function (pfx_bitfield_t color_)
{
	return 0;
}

pfx_result_t CPfx_framebuffer_operation_opengles2::set_sample_coverage (pfx_float_t value_,pfx_boolean_t invert_mask)
{
	return 0;
}

	
	//////////////////////////////////////////////////////////////////////////
pfx_result_t CPfx_framebuffer_operation_opengles2::read_image (PFX_IMAGE_t& PARAM_INOUT pixel_)
{
	return 0;
}


PECKER_END

PFX_C_EXTERN_BEGIN

PFX_C_EXTERN_END


