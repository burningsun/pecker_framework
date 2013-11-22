/*
 * pfx_	framebuffer.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_FRAMEBUFFER_H_
#define		PFX_FRAMEBUFFER_H_

#include "../../pfx_defines.h"
#include "../pfx_render_type.h"
#include "pfx_renderbuffer.h"
#include "pfx_texture.h"


PECKER_BEGIN

typedef enum enumFRAME_BUFFER_TYPE
{
	PFX_FRAME_BUFFER_TYPE = 0,

	PFX_FRAME_BUFFER_TYPE_COUNT
}PFX_FRAME_BUFFER_TYPE_t;

PFX_Interface Ipfx_framebuffer_operation;

PFX_Interface Ipfx_framebuffer
{
public:
	virtual pfx_result_t init_framebuffer (PFX_FRAME_BUFFER_TYPE_t type_) = 0;
	virtual pfx_result_t dispose_framebuffer() = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t begin_setting_framebuffer(pfx_enum_t type_ = PFX_FRAME_BUFFER_TYPE) = 0;
	virtual pfx_result_t end_setting_framebuffer(pfx_boolean_t flag = pfx_false) = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t check_attach_complete() = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t attach_renderbuffer (Ipfx_color_buffer* PARAM_INOUT colorbuffer,
		pfx_index_t attach_unit = 0) = 0;
	virtual pfx_result_t attach_renderbuffer (Ipfx_depth_buffer* PARAM_INOUT colorbuffer,
		pfx_index_t attach_unit = 0) = 0;
	virtual pfx_result_t attach_renderbuffer (Ipfx_stencil_buffer* PARAM_INOUT colorbuffer,
		pfx_index_t attach_unit = 0) = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t attach_texture (Ipfx_texture* PARAM_INOUT texture,
		PFX_RENDER_BUFFER_TYPE_t attach_type_,
		pfx_index_t attach_unit = 0) = 0;
	//////////////////////////////////////////////////////////////////////////

	PFX_INLINE Ipfx_framebuffer_operation* get_opertation () const;
	//////////////////////////////////////////////////////////////////////////
	virtual ~Ipfx_framebuffer(){;}; 
protected:
	Ipfx_framebuffer_operation* m_framebuffer_operation;
};

PFX_INLINE Ipfx_framebuffer_operation* Ipfx_framebuffer::get_opertation () const
{
	return m_framebuffer_operation;
}


typedef enum enumFRAGMENT_TEST_ENABLE_TOKENS
{
	PFX_DEPTH_TEST = 0,								//Control depth testing of fragments

	PFX_STENCIL_TEST,									// Control stencil testing of fragments

	PFX_BLEND,												// Control blending of fragments with
																		// colors stored in the color buffer

	PFX_DITHER,												//	Control the dithering of fragment
																		//	colors before being written in the color
																		//	buffer

	PFX_SAMPLE_COVERAGE,						//Control the computation of sample
																		//coverage values

	PFX_SAMPLE_ALPHA_TO_COVERAGE,	//Control the use of a sample’s alpha in
																		//the computation

	FRAGMENT_TEST_ENABLE_TOKENS_COUNT
}PFX_FRAGMENT_TEST_ENABLE_TOKENS_t;

typedef enum enumFRAGMENT_TEST_FUNCION
{
	PFX_FTF_EQUAL = 0, 
	PFX_FTF_NOTEQUAL, 
	PFX_FTF_LESS, 
	PFX_FTF_GREATER,
	PFX_FTF_LEQUAL, 
	PFX_FTF_GEQUAL, 
	PFX_FTF_ALWAYS, 
	PFX_FTF_NEVER,
	FRAGMENT_TEST_FUNCION_COUNT
}PFX_FRAGMENT_TEST_FUNCION_t;

typedef enum enumFRAGMENT_TEST_OPERATES
{
	PFX_FTO_KEEP,
	PFX_FTO_ZERO, 
	PFX_FTO_REPLACE, 
	PFX_FTO_INCR, 
	PFX_FTO_DECR, 
	PFX_FTO_INCR_WRAP,
	PFX_FTO_DECR_WRAP,  
	PFX_FTO_INVERT,
	FRAGMENT_TEST_OPERATES_COUNT
}PFX_FRAGMENT_TEST_OPERATES_t;

typedef enum enumBLEND_FUNCTIONS
{
	PFX_BF_ZERO = 0,
	PFX_BF_ONE,
	PFX_BF_SRC_COLOR,
	PFX_BF_ONE_MINUS_SRC_COLOR,
	PFX_BF_SRC_ALPHA,
	PFX_BF_ONE_MINUS_SRC_ALPHA,
	PFX_BF_DST_COLOR,
	PFX_BF_ONE_MINUS_DST_COLOR,
	PFX_BF_DST_ALPHA,
	PFX_BF_ONE_MINUS_DST_ALPHA,
	PFX_BF_CONSTANT_COLOR,
	PFX_BF_ONE_MINUS_CONSTANT_COLOR,
	PFX_BF_CONSTANT_ALPHA,
	PFX_BF_ONE_MINUS_CONSTANT_ALPHA,
	PFX_BF_SRC_ALPHA_SATURATE,

	BLEND_FUNCTIONS_COUNT
}PFX_BLEND_FUNCTIONS_t;

typedef enum enumBLEND_MODE
{
	PFX_BM_FUNC_ADD = 0,
	PFX_BM_FUNC_SUBTRACT,
	PFX_BM_FUNC_REVERSE_SUBTRACT,

	BLEND_MODE_COUNT
}PFX_BLEND_MODE_t;

PFX_Interface Ipfx_framebuffer_operation
{
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t set_viewport (pfx_index_t x,pfx_index_t y,
		pfx_usize_t width,pfx_usize_t height) = 0;
	
	virtual pfx_result_t set_depthrange(pfx_float_t near_,
		pfx_float_t far_) = 0;
	////////////////////////////////////////////////

	virtual pfx_result_t clear_buffer (pfx_bitfield_t mask) = 0;

	virtual pfx_result_t clear_color (pfx_bitfield_t rgba_) = 0;
	virtual pfx_result_t clear_color (const pfx_color_t& PARAM_IN rgba_) = 0;

	virtual pfx_result_t clear_depth (pfx_float_t depth_) = 0;

	virtual pfx_result_t clear_stencil (pfx_bitfield_t stencil) = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t color_mask (pfx_boolean_t red_,
															pfx_boolean_t green_,
															pfx_boolean_t blue_,
															pfx_boolean_t alpha_) = 0;
	virtual pfx_result_t depth_mask (pfx_boolean_t depth_ ) = 0;
	virtual pfx_result_t stencil_mask (pfx_bitfield_t mask_) = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t enable_test (PFX_FRAGMENT_TEST_ENABLE_TOKENS_t type_) = 0;
	virtual pfx_result_t disable_test (PFX_FRAGMENT_TEST_ENABLE_TOKENS_t type_) = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t set_scissor_test (pfx_index_t x,pfx_index_t y,
		pfx_usize_t width,pfx_usize_t height) = 0;

	virtual pfx_result_t set_stencil_function (PFX_FRAGMENT_TEST_FUNCION_t function_,
		pfx_bitfield_t comarison_value,
		pfx_bitfield_t mask_) = 0;
	virtual pfx_result_t set_stencil_operation (PFX_FRAGMENT_TEST_OPERATES_t stencil_fail_,
																			PFX_FRAGMENT_TEST_OPERATES_t depth_fail_,
																			PFX_FRAGMENT_TEST_OPERATES_t pass_) = 0;

	virtual pfx_result_t set_depth_function (PFX_FRAGMENT_TEST_OPERATES_t cmp_func) = 0;

	virtual pfx_result_t set_blend_function (PFX_BLEND_FUNCTIONS_t source_factor,
																		PFX_BLEND_FUNCTIONS_t destination_factor) = 0;

	virtual pfx_result_t set_blend_function (PFX_BLEND_FUNCTIONS_t source_RGB_factor,
																		PFX_BLEND_FUNCTIONS_t destination_RGB_factor,
																		PFX_BLEND_FUNCTIONS_t source_Alpha_factor,
																		PFX_BLEND_FUNCTIONS_t destination_Alpha_factor) = 0;

	virtual pfx_result_t set_blend_equation (PFX_BLEND_MODE_t mode_) = 0;
	virtual pfx_result_t set_blend_equation (PFX_BLEND_MODE_t RGB_mode,
																		PFX_BLEND_MODE_t Alpha_mode) = 0;

	virtual pfx_result_t set_color_function (const pfx_color_t& color_) = 0;
	virtual pfx_result_t set_color_function (pfx_bitfield_t color_) = 0;

	virtual pfx_result_t set_sample_coverage (pfx_float_t value_,pfx_boolean_t invert_mask) = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t read_image (PFX_IMAGE_t& PARAM_INOUT pixel_) = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual ~Ipfx_framebuffer_operation() {;};
};

PECKER_END

PFX_C_EXTERN_BEGIN

PFX_C_EXTERN_END

#endif			//PFX_UTIL_H_
