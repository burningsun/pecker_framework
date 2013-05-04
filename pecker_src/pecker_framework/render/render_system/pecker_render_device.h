/*
 * pecker_render_device.h
 *
 *  Created on: 2013-4-7
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_RENDER_DEVICE_H_
#define PECKER_RENDER_DEVICE_H_

#include "../pecker_render_object.h"
#include "pecker_gpu_program.h"
#include "pecker_buffer.h"
#include "pecker_fragment_operation.h"

PECKER_BEGIN

enum DEVICE_INFO_TYPE
{
	VENDOR_INFO = 0,
	RENDERER_INFO,
	VERSION_INFO,
	EXTENSIONS_INFO,
	DEVICE_INFO_TYPE_COUNT
};

union pecker_state_value
{
	Bool _M_bvalue;
	Float _M_fvalue;
	SInt	_M_ivalue;
	Float _M_ftwo_value[2];
	SInt _M_itwo_value[2];
	Float _M_four_value[4];
	SInt _M_ifour_value[4];
};

enum PECKER_RENDER_STATE_VALUE
{
	GET_INTEGER_STATE_VALUE = 0,
	VIEWPORT_VALUE,
	CULL_FACE_MODE_VALUE,
	FRONT_FACE_VALUE,
	STENCIL_WRITEMASK_VALUE,
	STENCIL_BACK_WRITEMASK_VALUE,
	DEPTH_CLEAR_VALUE_VALUE,
	STENCIL_CLEAR_VALUE_VALUE,
	SUBPIXEL_BITS_VALUE,
	MAX_TEXTURE_SIZE_VALUE,
	MAX_CUBE_MAP_TEXTURE_SIZE_VALUE,
	MAX_VIEWPORT_DIMS_VALUE,
	NUM_COMPRESSED_TEXTURE_FORMATS_VALUE,
	COMPRESSED_TEXTURE_FORMATS_VALUE,
	RED_BITS_VALUE,
	GREEN_BITS_VALUE,
	BLUE_BITS_VALUE,
	ALPHA_BITS_VALUE,
	DEPTH_BITS_VALUE,
	STENCIL_BITS_VALUE,
	IMPLEMENTATION_COLOR_READ_TYPE_VALUE,
	IMPLEMENTATION_COLOR_READ_FORMAT_VALUE,
	ARRAY_BUFFER_BINDING_VALUE,
	ELEMENT_ARRAY_BUFFER_BINDING_VALUE,
	TEXTURE_BINDING_2D_VALUE,
	TEXTURE_BINDING_CUBE_MAP_VALUE,
	ACTIVE_TEXTURE_VALUE,
	SCISSOR_BOX_VALUE,
	STENCIL_FUNC_VALUE,
	STENCIL_VALUE_MASK_VALUE,
	STENCIL_REF_VALUE,
	STENCIL_FAIL_VALUE,
	STENCIL_PASS_DEPTH_FAIL_VALUE,
	STENCIL_PASS_DEPTH_PASS_VALUE,
	STENCIL_BACK_FUNC_VALUE,
	STENCIL_BACK_VALUE_MASK_VALUE,
	STENCIL_BACK_REF_VALUE,
	STENCIL_BACK_FAIL_VALUE,
	STENCIL_BACK_PASS_DEPTH_FAIL_VALUE,
	STENCIL_BACK_PASS_DEPTH_PASS_VALUE,
	DEPTH_FUNC_VALUE,
	BLEND_SRC_RGB_VALUE,
	BLEND_SRC_ALPHA_VALUE,
	BLEND_DST_RGB_VALUE,
	BLEND_DST_ALPHA_VALUE,
	BLEND_EQUATION_VALUE,
	BLEND_EQUATION_RGB_VALUE,
	BLEND_EQUATION_ALPHA_VALUE,
	UNPACK_ALIGNMENT_VALUE,
	PACK_ALIGNMENT_VALUE,
	CURRENT_PROGRAM_VALUE,
	RENDERBUFFER_BINDING_VALUE,
	FRAMEBUFFER_BINDING_VALUE,

	GET_FLOAT_STATE_VALUE,
	DEPTH_RANGE_VALUE,
	LINE_WIDTH_VALUE,
	POLYGON_OFFSET_FACTOR_VALUE,
	POLYGON_OFFSET_UNITS_VALUE,
	SAMPLE_COVERAGE_VALUE_VALUE,
	COLOR_CLEAR_VALUE_VALUE,
	ALIASED_POINT_SIZE_RANGE_VALUE,
	ALIASED_LINE_WIDTH_RANGE_VALUE,
	BLEND_COLOR_VALUE,


	GET_BOOLEAN_STATE_VALUE,
	SAMPLE_COVERAGE_INVERT_VALUE,
	COLOR_WRITEMASK_VALUE,
	DEPTH_WRITEMASK_VALUE,

	PECKER_RENDER_STATE_VALUE_COUNT
};

struct pecker_viewport
{
	nINDEX _M_x;
	nINDEX _M_y;
	nSize _M_width;
	nSize _M_height;
	pecker_viewport():_M_x(0),_M_y(0),_M_width(0),_M_height(0){;}
	pecker_viewport(nINDEX x,nINDEX y,nSize w,nSize h):_M_x(x),_M_y(y),_M_width(w),_M_height(h){;}
};

PeckerInterface Ipecker_render_device
{
	virtual ~Ipecker_render_device(){;}
	
	virtual Ipecker_gpu_program* create_gpu_program() = 0;
	virtual HResult release_gpu_program(Ipecker_gpu_program* &pgpu_program) = 0;

	virtual Ipecker_graphic_buffer* create_buffer(HEnum buffer_type) = 0;
	virtual HResult release_buffer(Ipecker_graphic_buffer* &pbuffer) = 0;

	virtual Ipecker_frame_buffer_object* create_frame_buffer_object(HEnum object_type,HEnum detail_type) = 0;
	virtual HResult release_frame_buffer_object(Ipecker_frame_buffer_object* &pobject) = 0;

	virtual Ipecker_frame_buffer* create_frame_buffer() = 0;
	virtual HResult release_frame_buffer(Ipecker_frame_buffer* &pframe_buffer) = 0;

	virtual HResult set_viewport(SInt x,SInt y,nSize width,nSize height) = 0;
	virtual HResult set_viewport(const pecker_viewport& viewport) = 0;
	virtual const pecker_viewport& get_viewport() const= 0;

	virtual Ipecker_fragment_operation* get_fragment_operation() const = 0;
	virtual HResult get_state_value(HEnum state,pecker_state_value& state_value) const = 0;
	//virtual HResult set_const_value(HEnum name,HEnum operation_type,nSize nvalue_count,const PVoid P_IN value_) = 0;
	//virtual HResult set_value(HEnum name,HEnum operation_type,nSize nvalue_count,PVoid P_IN value_) = 0;

	virtual HResult get_device_info(HEnum info_type,pecker_string& P_OUT strInfo) const= 0;
};


PECKER_END

#endif //PECKER_RENDER_DEVICE_H_