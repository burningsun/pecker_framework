/*
 * pecker_opengles_device.cpp
 *
 *  Created on: 2013-4-21
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_opengles_device.h"
#include "pecker_render_resource_container_gl.h"
#include "pecker_fragment_operation_gl.h"
#include <GLES2/gl2.h>
PECKER_BEGIN

	static HEnum gState_value_table[PECKER_RENDER_STATE_VALUE_COUNT] = {0,
	GL_VIEWPORT,
	GL_CULL_FACE_MODE,
	GL_FRONT_FACE,
	GL_STENCIL_WRITEMASK,
	GL_STENCIL_BACK_WRITEMASK,
	GL_DEPTH_CLEAR_VALUE,
	GL_STENCIL_CLEAR_VALUE,
	GL_SUBPIXEL_BITS,
	GL_MAX_TEXTURE_SIZE,
	GL_MAX_CUBE_MAP_TEXTURE_SIZE,
	GL_MAX_VIEWPORT_DIMS,
	GL_NUM_COMPRESSED_TEXTURE_FORMATS,
	GL_COMPRESSED_TEXTURE_FORMATS,
	GL_RED_BITS,
	GL_GREEN_BITS,
	GL_BLUE_BITS,
	GL_ALPHA_BITS,
	GL_DEPTH_BITS,
	GL_STENCIL_BITS,
	GL_IMPLEMENTATION_COLOR_READ_TYPE,
	GL_IMPLEMENTATION_COLOR_READ_FORMAT,
	GL_ARRAY_BUFFER_BINDING,
	GL_ELEMENT_ARRAY_BUFFER_BINDING,
	GL_TEXTURE_BINDING_2D,
	GL_TEXTURE_BINDING_CUBE_MAP,
	GL_ACTIVE_TEXTURE,
	GL_SCISSOR_BOX,
	GL_STENCIL_FUNC,
	GL_STENCIL_VALUE_MASK,
	GL_STENCIL_REF,
	GL_STENCIL_FAIL,
	GL_STENCIL_PASS_DEPTH_FAIL,
	GL_STENCIL_PASS_DEPTH_PASS,
	GL_STENCIL_BACK_FUNC,
	GL_STENCIL_BACK_VALUE_MASK,
	GL_STENCIL_BACK_REF,
	GL_STENCIL_BACK_FAIL,
	GL_STENCIL_BACK_PASS_DEPTH_FAIL,
	GL_STENCIL_BACK_PASS_DEPTH_PASS,
	GL_DEPTH_FUNC,
	GL_BLEND_SRC_RGB,
	GL_BLEND_SRC_ALPHA,
	GL_BLEND_DST_RGB,
	GL_BLEND_DST_ALPHA,
	GL_BLEND_EQUATION,
	GL_BLEND_EQUATION_RGB,
	GL_BLEND_EQUATION_ALPHA,
	GL_UNPACK_ALIGNMENT,
	GL_PACK_ALIGNMENT,
	GL_CURRENT_PROGRAM,
	GL_RENDERBUFFER_BINDING,
	GL_FRAMEBUFFER_BINDING,

	0,
	GL_DEPTH_RANGE,
	GL_LINE_WIDTH,
	GL_POLYGON_OFFSET_FACTOR,
	GL_POLYGON_OFFSET_UNITS,
	GL_SAMPLE_COVERAGE_VALUE,
	GL_COLOR_CLEAR_VALUE,
	GL_ALIASED_POINT_SIZE_RANGE,
	GL_ALIASED_LINE_WIDTH_RANGE,
	GL_BLEND_COLOR,

	0,
	GL_SAMPLE_COVERAGE_INVERT,
	GL_COLOR_WRITEMASK,
	GL_DEPTH_WRITEMASK
};

static pecker_fragment_operation_gles2 gFragment_operation;
pecker_render_device_gles2::pecker_render_device_gles2()
{
	;
}

pecker_render_device_gles2::~pecker_render_device_gles2()
{
	;
}

Ipecker_gpu_program* pecker_render_device_gles2::create_gpu_program()
{
	return gpu_program_allocator_gles2::allocate_object();
}

HResult pecker_render_device_gles2::release_gpu_program(Ipecker_gpu_program* &pgpu_program)
{
	 pecker_shader_program_glsles1* prelease_program = dynamic_cast<pecker_shader_program_glsles1*>(pgpu_program);
	 if (prelease_program)
	 {
		 gpu_program_allocator_gles2::deallocate_object(prelease_program);
		 pgpu_program = null;
		 return P_OK;
	 }
	 else
	 {
		 return P_FAIL;
	 }
	 
}

Ipecker_graphic_buffer* pecker_render_device_gles2::create_buffer(HEnum buffer_type)
{
	Ipecker_graphic_buffer* preturn_buffer = null;
	switch(buffer_type)
	{
	case VERTEX_BUFFER_TYPE:
		preturn_buffer = vertex_allocator_gles2::allocate_object();
		break;
	case INDEX_BUFFER_TYPE:
		preturn_buffer = index_allocator_gles2::allocate_object();
		break;
	default:
		preturn_buffer = null;
		break;
	}
	return preturn_buffer;
}
HResult pecker_render_device_gles2::release_buffer(Ipecker_graphic_buffer* &pbuffer)
{
	if (null == pbuffer)
	{
		return P_FAIL;
	}
	HResult return_value = P_FAIL;
	HEnum buffer_type = pbuffer->get_buffer_type(); 
	switch(buffer_type)
	{
	case VERTEX_BUFFER_TYPE:
		{
			pecker_vertex_buffer_gles2* pdel_obj = dynamic_cast<pecker_vertex_buffer_gles2*>(pbuffer);
			if (pdel_obj)
			{
				vertex_allocator_gles2::deallocate_object(pdel_obj);
				return_value = P_OK;
				pbuffer = null;
			}
		}
		
		break;
	case INDEX_BUFFER_TYPE:
		{
			pecker_index_buffer_gles2* pdel_obj = dynamic_cast<pecker_index_buffer_gles2*>(pbuffer);
			if (pdel_obj)
			{
				index_allocator_gles2::deallocate_object(pdel_obj);
				return_value = P_OK;
				pbuffer = null;
			}
		}
		break;
	default:
		 return_value = P_FAIL;
		break;
	}
	return return_value;
}

Ipecker_frame_buffer_object* pecker_render_device_gles2::create_frame_buffer_object(HEnum object_type,HEnum detail_type)
{
	Ipecker_frame_buffer_object* preturn_obj = null;
	switch(object_type)
	{
	case COLOR_BUFFER_TYPE:
		{
			preturn_obj = colorbuffer_allocator_gles2::allocate_object();
		}
		break;
	case DEPTH_BUFFER_TYPE:
		{
			preturn_obj = depthbuffer_allocator_gles2::allocate_object();
		}
		break;
	case STENCIL_BUFFER_TYPE:
		{
			preturn_obj = stencilbuffer_allocator_gles2::allocate_object();
		}
		break;
	case TEXTURE_BUFFER_TYPE:
		{
			switch(detail_type)
			{
			case TEXTURE_2D_TYPE:
				{
					preturn_obj = texture2d_allocator_gles2::allocate_object();
				}
				break;
			case  TEXTURE_CUBE_TYPE:
				{
					preturn_obj = texture_cube_allocator_gles2::allocate_object();
				}
				break;
			default:
				preturn_obj = null;
				break;
			}
		}
		break;
	default:
		preturn_obj = null;
		break;
	}
	return preturn_obj;
}
HResult pecker_render_device_gles2::release_frame_buffer_object(Ipecker_frame_buffer_object* &pobject)
{
	if (null == pobject)
	{
		return P_FAIL;
	}
	HResult return_value = P_FAIL;
	HEnum object_type = pobject->get_frame_buffer_object_type();
	switch(object_type)
	{
	case COLOR_BUFFER_TYPE:
		{
			pecker_color_buffer_gles2* pdel_obj = dynamic_cast<pecker_color_buffer_gles2*>(pobject);
			if (pdel_obj)
			{
				colorbuffer_allocator_gles2::deallocate_object(pdel_obj);
				pobject = null;
				return_value = P_OK;
			}
		}
		break;
	case DEPTH_BUFFER_TYPE:
		{
			pecker_depth_buffer_gles2* pdel_obj = dynamic_cast<pecker_depth_buffer_gles2*>(pobject);
			if (pdel_obj)
			{
				depthbuffer_allocator_gles2::deallocate_object(pdel_obj);
				pobject = null;
				return_value = P_OK;
			}
		}
		break;
	case STENCIL_BUFFER_TYPE:
		{
			pecker_stencil_buffer_gles2* pdel_obj = dynamic_cast<pecker_stencil_buffer_gles2*>(pobject);
			if (pdel_obj)
			{
				stencilbuffer_allocator_gles2::deallocate_object(pdel_obj);
				pobject = null;
				return_value = P_OK;
			}
		}
		break;
	case TEXTURE_BUFFER_TYPE:
		{
			Ipecker_texture* pdel_obj = dynamic_cast<Ipecker_texture*>(pobject);
			
			if (pdel_obj)
			{
				HEnum detail_type = pdel_obj->get_texture_type();

				switch(detail_type)
				{
				case TEXTURE_2D_TYPE:
					{
						pecker_texture_2d_gles2* pdel_tex = dynamic_cast<pecker_texture_2d_gles2*>(pdel_obj);
						if (pdel_tex)
						{
							texture2d_allocator_gles2::deallocate_object(pdel_tex);
							pobject = null;
							return_value = P_OK;
						}
					}
					break;
				case  TEXTURE_CUBE_TYPE:
					{
						pecker_texture_cube_gles2* pdel_tex = dynamic_cast<pecker_texture_cube_gles2*>(pdel_obj);
						if (pdel_tex)
						{
							texture_cube_allocator_gles2::deallocate_object(pdel_tex);
							pobject = null;
							return_value = P_OK;
						}
					}
					break;
				default:
					 return_value = P_FAIL;
					break;
				}
			}

		}
		break;
	default:
		 return_value = P_FAIL;
		break;
	}
	return  return_value;
}

Ipecker_frame_buffer* pecker_render_device_gles2::create_frame_buffer()
{
	return framebuffer_allocator_gles2::allocate_object();
}
HResult pecker_render_device_gles2::release_frame_buffer(Ipecker_frame_buffer* &pframe_buffer)
{
	pecker_frame_buffer_gles2* pdel_obj = dynamic_cast<pecker_frame_buffer_gles2*>(pframe_buffer);
	if (pframe_buffer)
	{
		framebuffer_allocator_gles2::deallocate_object(pdel_obj);
		pframe_buffer = null;
		return P_OK;
	}
	else
	{
		return P_FAIL;
	}
}

HResult pecker_render_device_gles2::set_viewport(SInt x,SInt y,nSize width,nSize height)
{
	glViewport(x,y,width,height);
	HResult return_value =  pecker_opengles_v2_object::get_last_error_code();
	if (P_OK == return_value)
	{
		_M_viewport._M_x = x;
		_M_viewport._M_y = y;
		_M_viewport._M_width = width;
		_M_viewport._M_height = height;
	}
	return return_value;
}

HResult pecker_render_device_gles2::set_viewport(const pecker_viewport& viewport)
{
	return set_viewport(viewport._M_x,viewport._M_y,viewport._M_width,viewport._M_height);
}

const pecker_viewport& pecker_render_device_gles2::get_viewport() const
{
	return _M_viewport;
}

//HResult pecker_render_device_gles2::set_const_value(HEnum name,HEnum operation_type,nSize nvalue_count,const PVoid P_IN value_)
//{
//	return  pecker_opengles_v2_object::get_last_error_code();
//}
//HResult pecker_render_device_gles2::set_value(HEnum name,HEnum operation_type,nSize nvalue_count,PVoid P_IN value_)
//{
//	return  pecker_opengles_v2_object::get_last_error_code();
//}
 Ipecker_fragment_operation* pecker_render_device_gles2::get_fragment_operation() const
 {
	 return &gFragment_operation;
 }

HResult pecker_render_device_gles2::get_state_value(HEnum state,pecker_state_value& state_value) const
{
	if (state >= PECKER_RENDER_STATE_VALUE_COUNT &&  
		state <= GET_INTEGER_STATE_VALUE &&
		GET_FLOAT_STATE_VALUE == state &&
		GET_BOOLEAN_STATE_VALUE == state)
	{
		return P_INVALID_ENUM;
	}
	HEnum glState_value = gState_value_table[state];
	if (state > GET_INTEGER_STATE_VALUE && state < GET_FLOAT_STATE_VALUE)
	{
		glGetIntegerv(glState_value,(GLint*)(&state_value));
	}
	else if (state < GET_BOOLEAN_STATE_VALUE)
	{
		glGetFloatv(glState_value,(GLfloat*)(&state_value));
	}
	else
	{
		glGetBooleanv(glState_value,(GLboolean*)(&state_value));
	}
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_render_device_gles2::get_device_info(HEnum info_type,pecker_string& P_OUT strInfo) const
{
	if (info_type >= DEVICE_INFO_TYPE_COUNT)
	{
		return P_INVALID_ENUM;
	}
	const GLubyte* pstr = glGetString(GL_VENDOR + info_type);
	nSize strlength = strlen((const char*)pstr);
	strInfo.init((const char*)pstr,strlength+1);
	return pecker_opengles_v2_object::get_last_error_code();
}


PECKER_END