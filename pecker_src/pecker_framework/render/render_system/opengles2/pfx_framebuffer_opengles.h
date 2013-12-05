/*
 * pfx_	framebuffer_opengles.h
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_FRAMEBUFFER_OPENGLES2_H_
#define		PFX_FRAMEBUFFER_OPENGLES2_H_

#include "../pfx_framebuffer.h"

PECKER_BEGIN

//class PFX_RENDER_SYSTEM_API CPfx_render_device_opengles2;
class PFX_RENDER_SYSTEM_API CPfx_framebuffer_operation_opengles2 : public Ipfx_framebuffer_operation
{
public:
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t set_viewport (pfx_index_t x,pfx_index_t y,
		pfx_usize_t width,pfx_usize_t height);

	virtual pfx_result_t set_depthrange(pfx_float_t near_,
		pfx_float_t far_);
	////////////////////////////////////////////////

	virtual pfx_result_t clear_buffer (pfx_bitfield_t mask);

	virtual pfx_result_t clear_color (pfx_bitfield_t rgba_);
	virtual pfx_result_t clear_color (const pfx_color_t& PARAM_IN rgba_);

	virtual pfx_result_t clear_depth (pfx_float_t depth_);

	virtual pfx_result_t clear_stencil (pfx_bitfield_t stencil);
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t color_mask (pfx_boolean_t red_,
		pfx_boolean_t green_,
		pfx_boolean_t blue_,
		pfx_boolean_t alpha_);
	virtual pfx_result_t depth_mask (pfx_boolean_t depth_ );
	virtual pfx_result_t stencil_mask (pfx_bitfield_t mask_);
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t enable_test (PFX_FRAGMENT_TEST_ENABLE_TOKENS_t type_);
	virtual pfx_result_t disable_test (PFX_FRAGMENT_TEST_ENABLE_TOKENS_t type_);
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t set_scissor_test (pfx_index_t x,pfx_index_t y,
		pfx_usize_t width,pfx_usize_t height);

	virtual pfx_result_t set_stencil_function (PFX_FRAGMENT_TEST_FUNCION_t function_,
		pfx_bitfield_t comarison_value,
		pfx_bitfield_t mask_);
	virtual pfx_result_t set_stencil_operation (PFX_FRAGMENT_TEST_OPERATES_t stencil_fail_,
		PFX_FRAGMENT_TEST_OPERATES_t depth_fail_,
		PFX_FRAGMENT_TEST_OPERATES_t pass_);

	virtual pfx_result_t set_depth_function (PFX_FRAGMENT_TEST_OPERATES_t cmp_func);

	virtual pfx_result_t set_blend_function (PFX_BLEND_FUNCTIONS_t source_factor,
		PFX_BLEND_FUNCTIONS_t destination_factor);

	virtual pfx_result_t set_blend_function (PFX_BLEND_FUNCTIONS_t source_RGB_factor,
		PFX_BLEND_FUNCTIONS_t destination_RGB_factor,
		PFX_BLEND_FUNCTIONS_t source_Alpha_factor,
		PFX_BLEND_FUNCTIONS_t destination_Alpha_factor);

	virtual pfx_result_t set_blend_equation (PFX_BLEND_MODE_t mode_);
	virtual pfx_result_t set_blend_equation (PFX_BLEND_MODE_t RGB_mode,
		PFX_BLEND_MODE_t Alpha_mode);

	virtual pfx_result_t set_color_function (const pfx_color_t& color_);
	virtual pfx_result_t set_color_function (pfx_bitfield_t color_);

	virtual pfx_result_t set_sample_coverage (pfx_float_t value_,pfx_boolean_t invert_mask);


	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t read_image (PFX_IMAGE_t& PARAM_INOUT pixel_);
	//virtual pfx_result_t set_pixel_store () = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual ~CPfx_framebuffer_operation_opengles2();
};

class PFX_RENDER_SYSTEM_API CPfx_framebuffer_opengles2 : public  Ipfx_framebuffer
{
public:
	virtual pfx_result_t init_framebuffer (PFX_FRAME_BUFFER_TYPE_t type_);
	virtual pfx_result_t dispose_framebuffer();
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t begin_setting_framebuffer(pfx_enum_t type_ = PFX_FRAME_BUFFER_TYPE);
	virtual pfx_result_t end_setting_framebuffer(pfx_boolean_t flag = pfx_false);
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t check_attach_complete();
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t attach_renderbuffer (Ipfx_color_buffer* PARAM_INOUT colorbuffer,
		pfx_index_t attach_unit = 0);
	virtual pfx_result_t attach_renderbuffer (Ipfx_depth_buffer* PARAM_INOUT colorbuffer,
		pfx_index_t attach_unit = 0);
	virtual pfx_result_t attach_renderbuffer (Ipfx_stencil_buffer* PARAM_INOUT colorbuffer,
		pfx_index_t attach_unit = 0);
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t attach_texture (Ipfx_texture* PARAM_INOUT texture,
		PFX_RENDER_BUFFER_TYPE_t attach_type_,
		PFX_TEXTURE_SURFACE_TYPE_t attach_texture_surface = PFX_TEXTURE_DEFUALT_SURFACE,
		pfx_index_t mip_lever = 0,
		pfx_index_t attach_unit = 0);
	//////////////////////////////////////////////////////////////////////////
	CPfx_framebuffer_opengles2 ();
	virtual ~CPfx_framebuffer_opengles2 (); 
private:
	CPfx_framebuffer_operation_opengles2 m_defualt_framebuffer_operation_gles2;
//protected:
//	Ipfx_framebuffer_operation* m_framebuffer_operation;
};





PECKER_END

PFX_C_EXTERN_BEGIN

PFX_C_EXTERN_END

#endif			//PFX_FRAMEBUFFER_OPENGLES2_H_
