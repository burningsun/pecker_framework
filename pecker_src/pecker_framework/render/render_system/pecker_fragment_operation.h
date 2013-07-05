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
#include "pecker_buffer.h"
PECKER_BEGIN
enum	ENABLE_FRAGMENT_OPERATION_STATE
{
	CULL_FACE_OPERATION = 0,
	POLYGON_OFFSET_FILL_OPERATION,
	SCISSOR_TEST_OPERATION,
	SAMPLE_COVERAGE_OPERATION,
	SAMPLE_ALPHA_TO_COVERAGE_OPERATION,
	STENCIL_TEST_OPERATION,
	DEPTH_TEST_OPERATION,
	BLEND_OPERATION,
	DITHER_OPERATION,

	ENABLE_FRAGMENT_OPERATION_STATE_COUNT
};

// clear buffer mask
#define PECKER_FP_DEPTH_BUFFER_BIT               0x00000100
#define PECKER_FP_STENCIL_BUFFER_BIT             0x00000400
#define PECKER_FP_COLOR_BUFFER_BIT               0x00004000

enum FRAGMEMT_RENDER_FACE_TYPE
{
	FRONT_FACE = 0,
	BACK_FACE,
	FRONT_AND_BACK,

	FRAGMEMT_RENDER_FACE_TYPE_COUNT
};

enum STENCIL_FUNCTION_TYPE
{
	STENCIL_FUNC_EQUAL = 0, 
	STENCIL_FUNC_NOTEQUAL, 
	STENCIL_FUNC_LESS, 
	STENCIL_FUNC_GREATER, 
	STENCIL_FUNC_LEQUAL, 
	STENCIL_FUNC_GEQUAL, 
	STENCIL_FUNC_ALWAYS, 
	STENCIL_FUNC_NEVER,
	STENCIL_FUNCTION_TYPE_COUNT
};


enum STENCIL_OPERATION_TYPE
{
	STENCIL_SET_ZERO = 0,
	STENCIL_SET_REPLACE, 
	STENCIL_SET_INCREMENT, 
	STENCIL_SET_DECREMENT,
	STENCIL_SET_INCREMENT_WRAP, 
	STENCIL_SET_DECREMENT_WRAP,
	STENCIL_SET_KEEP,
	STENCIL_SET_BITWISE_INVERT,

	STENCIL_OPERATION_TYPE_COUNT
};

enum DEPTH_TEST_FUNCTION_TYPE
{
	DEPTH_TEST_FUNC_EQUAL = 0, 
	DEPTH_TEST_FUNC_NOTEQUAL, 
	DEPTH_TEST_FUNC_LESS, 
	DEPTH_TEST_FUNC_GREATER, 
	DEPTH_TEST_FUNC_LEQUAL, 
	DEPTH_TEST_FUNC_GEQUAL, 
	DEPTH_TEST_FUNC_ALWAYS, 
	DEPTH_TEST_FUNC_NEVER,
	DEPTH_TEST_FUNCTION_TYPE_COUNT
};

enum BLEND_COLOR_FUNCION_TYPE
{
	//Blending Coefficient Enum ,                     (RGB Blending Factors)  Alpha Blending Factor
	BLEND_ZERO = 0,											// (0, 0, 0) 0
	BLEND_ONE,													// (1, 1, 1) 1 
	BLEND_SRC_COLOR,										// (Rs, Gs, Bs ) As 
	BLEND_ONE_MINUS_SRC_COLOR,				// (1 – Rs, 1 – Gs, 1 – Bs) 1 – As 
	BLEND_SRC_ALPHA,										// (As, As, As) As 
	BLEND_ONE_MINUS_SRC_ALPHA,				// (1 – As, 1 – As, 1 – As) 1 – As 
	BLEND_DST_COLOR ,										//(Rd, Gd, Bd) Ad 
	BLEND_ONE_MINUS_DST_COLOR,				//(1 – Rd, 1 – Gd, 1 – Bd) 1 – Ad 
	BLEND_DST_ALPHA,										// (Ad, Ad, Ad) Ad 
	BLEND_ONE_MINUS_DST_ALPHA,				// (1 – Ad, 1 – Ad, 1 – Ad) 1 – Ad 
	BLEND_CONSTANT_COLOR,							// (Rc, Gc, Bc) Ac 
	BLEND_ONE_MINUS_CONSTANT_COLOR,	// (1 – Rc, 1 – Gc, 1 – Bc) 1 – Ac 
	BLEND_CONSTANT_ALPHA,							// (Ac, Ac, Ac) Ac 
	BLEND_ONE_MINUS_CONSTANT_ALPHA, //(1 – Ac, 1 – Ac, 1 – Ac) 1 – Ac
	BLEND_SRC_ALPHA_SATURATE,					// min( As, 1 – Ad) 1

	BLEND_COLOR_FUNCION_TYPE_COUNT
};

enum BLEND_COLOR_MODE
{
	BLEND_COLOR_FUNC_ADD = 0, 
	BLEND_COLOR_FUNC_SUBTRACT, 
	BLEND_COLOR_FUNC_REVERSE_SUBTRACT,
	BLEND_COLOR_EQUATION, 
	BLEND_COLOR_EQUATION_RGB, 
	BLEND_COLOR_EQUATION_ALPHA,

	BLEND_COLOR_MODE_COUNT
};

enum DRAW_MODE
{
		DRAW_POINTS                      = 0,
		DRAW_LINES,                         
		DRAW_LINE_LOOP,                
		DRAW_LINE_STRIP,                
		DRAW_TRIANGLES,                
		DRAW_TRIANGLE_STRIP,      
		DRAW_TRIANGLE_FAN,

		DRAW_MODE_COUNT
};

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


	virtual HResult draw_array(DRAW_MODE draw_mode,nINDEX fist,nSize count) = 0;
	virtual HResult draw_element(DRAW_MODE draw_mode,nSize count,ATTRIBUTE_DATA_TYPE datatype,PVoid pindex_buffer = null ) = 0;

	virtual Bool enable_state(HEnum state) = 0;
	virtual Bool disable_state(HEnum state) = 0;
	virtual Bool is_enable(HEnum state) const = 0;

	
};


PECKER_END

#endif //PECKER_FRAGMET_OPERATION_H_