/*
 * pecker_frame_buffer_gl.cpp
 *
 *  Created on: 2013-3-17
 *      Author: ¿Ó’Ú≥«  £® cut / cutxyz£©
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_frame_buffer_gl.h"
#include <GLES2/gl2.h>
PECKER_BEGIN


#define  MAX_RENDER_BUFFER_TABLE_TYPE 1
static const HEnum RENDER_BUFFER_MAX_ATTCHMENT_INDEX_INFO[TEXTURE_BUFFER_TYPE]
= {MAX_COLOR_ATTACHMENT_GLES2,MAX_DEPTH_ATTACHMENT_GLES2,MAX_STENCIL_ATTACHMENT_GLES2};

static const HEnum RENDER_BUFFER_ATTCHMENT_INDEX_TABLE[TEXTURE_BUFFER_TYPE][MAX_RENDER_BUFFER_TABLE_TYPE] = 
{
	{GL_COLOR_ATTACHMENT0},
	{GL_DEPTH_ATTACHMENT},
	{GL_STENCIL_ATTACHMENT}
};

pecker_frame_buffer_gles2::pecker_frame_buffer_gles2():_M_gpu_target(0)
{

}

pecker_frame_buffer_gles2::~pecker_frame_buffer_gles2()
{
	release_buffer_from_gpu_ram();
	_M_gpu_target = 0;
}

HResult pecker_frame_buffer_gles2::allocate_buffer_from_gpu_ram()
{
	if (0 == _M_gpu_target)
	{
		glGenFramebuffers(1,&_M_gpu_target);
		return pecker_opengles_v2_object::get_last_error_code();
	}
	return P_UNIQUE_ERR;
}

HResult pecker_frame_buffer_gles2::release_buffer_from_gpu_ram()
{
	if (0 != _M_gpu_target)
	{
		glDeleteFramebuffers(1,&_M_gpu_target);
		return pecker_opengles_v2_object::get_last_error_code();
	}
	return P_UNIQUE_ERR;
}

UInt pecker_frame_buffer_gles2::get_object_location() const
{
	return _M_gpu_target;
}

HResult pecker_frame_buffer_gles2::attach_render_buffer(Ipecker_render_buffer* prender_buffer,HEnum attach_index /* = 0 */)
{
	if (null == prender_buffer)
	{
		return P_INVALID_VALUE;
	}
	
	HEnum render_buffer_type = prender_buffer->get_frame_buffer_object_type();
	if (render_buffer_type > 2 || (attach_index < 0 || attach_index >= RENDER_BUFFER_MAX_ATTCHMENT_INDEX_INFO[render_buffer_type]))
	{
		return P_INVALID_VALUE;
	}

	pecker_opengles_v2_object* pgles2_object = dynamic_cast< pecker_opengles_v2_object* > (prender_buffer);
	if (null == pgles2_object)
	{
		return P_INVALID_VALUE;
	}

	if (0 == _M_gpu_target)
	{
		return P_FAIL;
	}

	glBindFramebuffer(GL_FRAMEBUFFER,_M_gpu_target);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,
		RENDER_BUFFER_ATTCHMENT_INDEX_TABLE[render_buffer_type][attach_index],
		GL_RENDERBUFFER,pgles2_object->get_object_location());

	HResult result_ = pecker_opengles_v2_object::get_last_error_code();
	return result_;
}

HResult pecker_frame_buffer_gles2::attach_texture(Ipecker_texture* ptexture,HEnum attach_index /* = 0 */)//,HEnum face_type /* = 0 */,nSize zoffset /* = 0 */)
{
	if (null == ptexture)
	{
		return P_INVALID_VALUE;
	}

	HEnum render_type = ptexture->get_render_type();
	if (render_type >= 2 || (attach_index < 0 || attach_index >= RENDER_BUFFER_MAX_ATTCHMENT_INDEX_INFO[render_type]))
	{
		return P_INVALID_VALUE;
	}

	pecker_opengles_v2_object* pgles2_object = dynamic_cast< pecker_opengles_v2_object* > (ptexture);
	if (null == pgles2_object)
	{
		return P_INVALID_VALUE;
	}

	if (0 == _M_gpu_target)
	{
		return P_FAIL;
	}

	HEnum attachment = RENDER_BUFFER_ATTCHMENT_INDEX_TABLE[render_type][attach_index];
	HEnum texture_type = ptexture->get_texture_type();
	HResult result_ = P_FAIL;

	
	switch(texture_type)
	{
	case TEXTURE_2D_TYPE:
		{
			glBindFramebuffer(GL_FRAMEBUFFER,_M_gpu_target);
			glFramebufferTexture2D(GL_FRAMEBUFFER,attachment,GL_TEXTURE_2D,pgles2_object->get_object_location(),ptexture->get_active_miplevel());		
			result_ = pecker_opengles_v2_object::get_last_error_code();
		}
		break;
	case TEXTURE_CUBE_TYPE:
		{
			Ipecker_texture_cube* pcube_texture = dynamic_cast<Ipecker_texture_cube*>(ptexture);
			if (null != pcube_texture)
			{
				glBindFramebuffer(GL_FRAMEBUFFER,_M_gpu_target);
				glFramebufferTexture2D(GL_FRAMEBUFFER,attachment,
					(pcube_texture->get_active_face() + GL_TEXTURE_CUBE_MAP_POSITIVE_X),pgles2_object->get_object_location(),ptexture->get_active_miplevel());		
				result_ = pecker_opengles_v2_object::get_last_error_code();
			}
		}
		break;
	case TEXTURE_3D_TYPE:
		{
			result_ = P_INVALID_ENUM;
		}
		break;
	default:
		break;
	}

	return P_OK;
}

HResult pecker_frame_buffer_gles2::attach_frame_buffer_object(Ipecker_frame_buffer_object* pframe_buffer_object,HEnum attach_index /* = 0 */)
{
	if (null != pframe_buffer_object)
	{
		return P_INVALID_VALUE;
	}
	HEnum render_buffer_object_type = pframe_buffer_object->get_frame_buffer_object_type();
	HResult result_ = P_FAIL;
	switch(render_buffer_object_type)
	{
	case COLOR_BUFFER_TYPE:
	case DEPTH_BUFFER_TYPE:
	case STENCIL_BUFFER_TYPE:
		{
			Ipecker_render_buffer* prender_buffer = dynamic_cast<Ipecker_render_buffer*>(pframe_buffer_object);
			result_ = attach_render_buffer(prender_buffer,attach_index);
		}
		break;
	case TEXTURE_BUFFER_TYPE:
		{
			Ipecker_texture* ptexture = dynamic_cast<Ipecker_texture*>(pframe_buffer_object);
			result_ = attach_texture(ptexture,attach_index);
		}
	default:
		result_ = P_INVALID_VALUE;
		break;
	}
	return P_OK;
}

HEnum pecker_frame_buffer_gles2::check_status() const
{
	if (0 != _M_gpu_target)
	{
		glBindFramebuffer(GL_FRAMEBUFFER,_M_gpu_target);
		HEnum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		return (status - GL_FRAMEBUFFER_COMPLETE);
	}
	return FRAMEBUFFER_NOT_EXIST;
}


PECKER_END