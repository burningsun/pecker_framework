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
#include <GLES2/gl2.h>
PECKER_BEGIN

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
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_render_device_gles2::set_const_value(HEnum name,HEnum operation_type,nSize nvalue_count,const PVoid P_IN value_)
{
	return  pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_render_device_gles2::set_value(HEnum name,HEnum operation_type,nSize nvalue_count,PVoid P_IN value_)
{
	return  pecker_opengles_v2_object::get_last_error_code();
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