/*
 * pfx_framebuffer_object_gles.cpp
 *
 *  Created on: 2014-10-15
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_framebuffer_object_gles.h"
#include "pfx_texture_gles.h"
#include <GLES2/gl2ext.h>

PECKER_BEGIN

GLenum PFX_FMT_TO_GLRB_FMT(enum_int_t usage_type, enum_int_t PFX_FMT)
{
	GLenum res = -1;
	switch (usage_type)
	{
	 case PFX_COLOR_BUFFER_FMT:
	 {
		res = GL_RGBA4;
		 switch (PFX_FMT)
		 {
		  case PFX_RGBA_FLOAT_FMT:
		  case PFX_RGBA8_FMT:
		  case PFX_RGBA16_FMT:
#ifdef GL_RGBA8_OES
			  res = GL_RGBA8_OES;
#endif
			  break;

		  case PFX_RGBA_4444_FMT:
			  res = GL_RGBA4;
			  break;
		
		  case PFX_RGBA_5551_FMT:
			  res = GL_RGB5_A1;
			  break;

		  case PFX_RGB16_FMT:
		  case PFX_RGB_FLOAT_FMT:
		  case PFX_RGB8_FMT:
#ifdef GL_RGB8_OES
			  res = GL_RGB8_OES;
			  break;
#endif
		  case	PFX_RGB_565_FMT:
			  res = GL_RGB565;
			  break;
		 default:
			  break;
		 }
	 }
	 break;
	case PFX_DEPTH_BUFFER_FMT:
		res = GL_DEPTH_COMPONENT16;
		switch (PFX_FMT)
		{
		case PFX_DEPTH_COMPONENT32_FMT:
#ifdef  GL_DEPTH_COMPONENT32_OES
			res = GL_DEPTH_COMPONENT32_OES;
			break;
#endif	// GL_DEPTH_COMPONENT32_OES
		case PFX_DEPTH_COMPONENT24_FMT:
#ifdef GL_DEPTH_COMPONENT24_OES
			res = GL_DEPTH_COMPONENT24_OES;
			break;
#endif // GL_DEPTH_COMPONENT24_OES
		case PFX_DEPTH_COMPONENT16_FMT:
			res = GL_DEPTH_COMPONENT16;
			break;
		default:
			break;
		}
		break;
	case PFX_STENCIL_BUFFER_FMT:
		res = GL_STENCIL_INDEX8;
		switch (PFX_FMT)
		{
		case PFX_STENCIL_INDEX1_FMT:
#ifdef  GL_STENCIL_INDEX1_OES
			res = GL_STENCIL_INDEX1_OES;
			break;
#endif	// GL_DEPTH_COMPONENT32_OES
		case PFX_STENCIL_INDEX4_FMT:
#ifdef GL_STENCIL_INDEX4_OES
			res = GL_STENCIL_INDEX4_OES;
			break;
#endif // GL_DEPTH_COMPONENT24_OES
		case PFX_STENCIL_INDEX8_FMT:
			res = GL_STENCIL_INDEX8;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return res;
}

cnative_renderbuffer_gles2::cnative_renderbuffer_gles2() :m_renderbufferID(0),
                                                        m_usage_type(PFX_DEPTH_BUFFER_FMT),
														m_internalformat(PFX_DEPTH_COMPONENT16_FMT),
														m_width(0),
														m_height(0)
{

}
cnative_renderbuffer_gles2::~cnative_renderbuffer_gles2()
{
	dispose();
}



result_t cnative_renderbuffer_gles2::create_rendertarget(enum_int_t usage_type, //  PFX_RENDER_BUFFER_FMT_t
enum_int_t format,
usize__t width, usize__t height)
{
	RETURN_INVALID_RESULT((!width || !height || usage_type >= PFX_UNKOWN_RENDER_BUFFER_FMT),
		PFX_STATUS_INVALID_PARAMS);

	GLint maxRenderbufferSize;
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderbufferSize);
	GLenum internalformat = PFX_FMT_TO_GLRB_FMT(usage_type, format);

	RETURN_INVALID_RESULT(((nsize__t)width > maxRenderbufferSize
		|| (nsize__t)height > maxRenderbufferSize
		|| -1 == internalformat),
		PFX_STATUS_INVALID_PARAMS);

	if (!m_renderbufferID)
	{
		::glGenRenderbuffers(1, &m_renderbufferID);
		m_width = 0;
		m_height = 0;
	}
	if (m_renderbufferID)
	{
		::glBindRenderbuffer(GL_RENDERBUFFER, m_renderbufferID);
		if (usage_type != m_usage_type || m_internalformat != format || m_width != width || height != m_height)
		{
			::glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);
			m_usage_type = usage_type;
			m_internalformat = format;
			m_width = width;
			m_height = height;
		}		
	}
	return PFX_STATUS_OK;
}

result_t cnative_renderbuffer_gles2::update_default()
{
	if (!m_width || !m_height || m_usage_type < PFX_UNKOWN_RENDER_BUFFER_FMT)
	{
		if (m_renderbufferID)
		{
			return create_rendertarget(m_usage_type, m_internalformat, m_width, m_height);
		}
		else
		{
			return PFX_STATUS_OK;
		}
	}
	else
	{
		return PFX_STATUS_UNINIT;
	}
}
result_t cnative_renderbuffer_gles2::bind()
{
	if (m_renderbufferID)
	{
		::glBindRenderbuffer(GL_RENDERBUFFER, m_renderbufferID);
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_UNINIT;
	}
}
result_t cnative_renderbuffer_gles2::dispose()
{
	m_usage_type = PFX_DEPTH_BUFFER_FMT;
	m_internalformat = PFX_DEPTH_COMPONENT16_FMT;
	m_width = 0;
	m_height = 0;
	return dispose_render_target();
}
result_t cnative_renderbuffer_gles2::dispose_render_target()
{
	if (m_renderbufferID)
	{
		::glDeleteRenderbuffers(1, &m_renderbufferID);
		m_renderbufferID = 0;
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_UNINIT;
	}
}


cnative_framebuffer_gles2::cnative_framebuffer_gles2() :
m_height(0),
m_width(0),
m_framebufferID(0),
m_fbo_complete_status(-1)
{	
	ZeroMemory(&m_fbo_tag, sizeof(m_fbo_tag));
	ZeroMemory(m_mip_level, sizeof(m_mip_level));
	ZeroMemory(m_surface_type, sizeof(m_surface_type));
}
cnative_framebuffer_gles2::~cnative_framebuffer_gles2()
{
	dispose();
}

result_t cnative_framebuffer_gles2::attach_renderbuffer(
	IPfx_renderbuffer* PARAM_IN render_buffer,
	uindex_t attachment_index// = 0
	)
{
	RETURN_INVALID_RESULT(!render_buffer, 
		PFX_STATUS_INVALID_PARAMS);

	RETURN_INVALID_RESULT(render_buffer->get_version()
		!= get_version(),
		PFX_STATUS_INVALID_VERSION);

	enum_int_t target_type = render_buffer->get_target_type();
	
	RETURN_INVALID_RESULT((target_type != PFX_RENDER_BUFFER_TAG), 
		PFX_STATUS_INVALID_PARAMS);

	


	// 标准OPENGL ES2 最大只有一个attachment		
	if (attachment_index > 0)
	{
		attachment_index = 0;
	}

	enum_int_t usage_type = render_buffer->get_usage_type();
	GLenum attachment = PFX_RBF_TO_GL_RBF(usage_type, attachment_index);
	
	RETURN_INVALID_RESULT(attachment<0,
		PFX_STATUS_INVALID_PARAMS);

	if (!m_framebufferID)
	{
		::glGenFramebuffers(1, &m_framebufferID);
	}

	RETURN_INVALID_RESULT(!m_framebufferID, PFX_STATUS_UNINIT);

	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);

	rect_size_t __RBO_sz;
	rect_size_t* __sz_ptr = 
		render_buffer->get_size(__RBO_sz, 0);
	RETURN_INVALID_RESULT((!__sz_ptr), 
		PFX_STATUS_INVALID_LEVEL);

	if (m_width && m_height)
	{
		RETURN_INVALID_RESULT((__sz_ptr->m_width != m_width ||
			__sz_ptr->m_height != m_height),
			PFX_STATUS_INVALID_SIZE);
	}
	else
	{
		m_width = __sz_ptr->m_width;
		m_height = __sz_ptr->m_height;
	}

	
	 
	result_t status = render_buffer->bind();
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),
		status);

	if (usage_type < PFX_UNKOWN_RENDER_BUFFER_FMT &&
		render_buffer->share())
	{
		if (m_fbo_tag.m_render_target_ptr[usage_type])
		{
			m_fbo_tag.m_render_target_ptr[usage_type]->dispose();
		}
		m_fbo_tag.m_render_buffer_ptr[usage_type]
			= render_buffer;
		m_mip_level[usage_type] = 0;

		//////////////////////////////////////////////////////////////////////////
		//
		::glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
			attachment, 
			GL_RENDERBUFFER,
			(GLuint)(render_buffer->get_native_handle()));
		status = PFX_STATUS_OK;
	}
	else
	{
		status = PFX_STATUS_ERROR_;
	}

	 



	return status;
}
result_t cnative_framebuffer_gles2::attach_texture(
	enum_int_t usage_type, //  PFX_RENDER_BUFFER_FMT_t
	IPfx_texture* PARAM_IN texture2D_ptr,
	uindex_t attachment_index,//= 0,
	uindex_t mip_level,// = 0,
	enum_int_t surface_type //= PFX_TEXTURE_DEFUALT_SURFACE
	)
{
	RETURN_INVALID_RESULT(!texture2D_ptr,
		PFX_STATUS_INVALID_PARAMS);

	RETURN_INVALID_RESULT(texture2D_ptr->get_version()
		!= get_version(),
		PFX_STATUS_INVALID_VERSION);

	enum_int_t target_type = texture2D_ptr->get_target_type();
	RETURN_INVALID_RESULT((target_type != PFX_TEXTURE_TAG),
		PFX_STATUS_INVALID_PARAMS);

	GLenum gl_surface_type =
		PFX_TEXSUR_2_GL_TEXSUR((PFX_TEXTURE_SURFACE_TYPE_t)surface_type);

	// 标准OPENGL ES2 最大只有一个attachment		
	if (attachment_index > 0)
	{
		attachment_index = 0;
	}

	GLenum attachment = PFX_RBF_TO_GL_RBF(usage_type, attachment_index);

	RETURN_INVALID_RESULT(attachment < 0,
		PFX_STATUS_INVALID_PARAMS);

	if (!m_framebufferID)
	{
		::glGenFramebuffers(1, &m_framebufferID);
	}

	RETURN_INVALID_RESULT(!m_framebufferID, PFX_STATUS_UNINIT);

	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);

	rect_size_t __RBO_sz;
	rect_size_t* __sz_ptr =
		texture2D_ptr->get_size(__RBO_sz, mip_level);
	RETURN_INVALID_RESULT((!__sz_ptr),
		PFX_STATUS_INVALID_LEVEL);

	if (m_width && m_height)
	{
		RETURN_INVALID_RESULT((__sz_ptr->m_width != m_width ||
			__sz_ptr->m_height != m_height),
			PFX_STATUS_INVALID_SIZE);
	}
	else
	{
		m_width = __sz_ptr->m_width;
		m_height = __sz_ptr->m_height;
	}

	result_t status = texture2D_ptr->bind();
	RETURN_INVALID_RESULT((PFX_STATUS_OK != status),
		status);

	if (usage_type < PFX_STENCIL_BUFFER_FMT &&
		texture2D_ptr->share())
	{
		if (m_fbo_tag.m_render_target_ptr[usage_type])
		{
			m_fbo_tag.m_render_target_ptr[usage_type]->dispose();
		}
		m_fbo_tag.m_render_texture_ptr[usage_type]
			= texture2D_ptr;
		m_mip_level[usage_type] = mip_level;
		m_surface_type[usage_type] = surface_type;

		//////////////////////////////////////////////////////////////////////////
		//
		::glFramebufferTexture2D(GL_FRAMEBUFFER,
			attachment,
			gl_surface_type,
			(GLuint)(texture2D_ptr->get_native_handle()),mip_level);
		status = PFX_STATUS_OK;
	}
	else
	{
		status = PFX_STATUS_ERROR_;
	}

	return status;
}

result_t cnative_framebuffer_gles2::complete_attachment()
{
	result_t status = PFX_STATUS_ERROR_;
	if (m_framebufferID)
	{
		::glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
		m_fbo_complete_status = ::glCheckFramebufferStatus(GL_FRAMEBUFFER);
		switch (m_fbo_complete_status)
		{
		case GL_FRAMEBUFFER_COMPLETE:
			status = PFX_STATUS_OK;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			status = PFX_STATUS_INCOMPLETE;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
			status = PFX_STATUS_INVALID_SIZE;
			break;
#ifdef 	GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
#endif
#ifdef GL_FRAMEBUFFER_MISSING_ATTACHMENT
		case GL_FRAMEBUFFER_MISSING_ATTACHMENT:
#endif
			status = PFX_STATUS_MISSING;
			break;
#ifdef GL_FRAMEBUFFER_INCOMPLETE_FORMATS
		case  GL_FRAMEBUFFER_INCOMPLETE_FORMATS:
			status = PFX_STATUS_INVALID_FORMAT;
			break;
#endif
		case GL_FRAMEBUFFER_UNSUPPORTED:
			status = PFX_STATUS_NOT_SUPPORTED;
			break;
		default:
			break;
		}
	}
	else
	{
		status = PFX_STATUS_UNINIT;
	}
	
	return status;
}
result_t cnative_framebuffer_gles2::create_rendertarget(
	usize__t width,//= 0, 
	usize__t height,// = 0,
	enum_int_t _color_format,// = PFX_RGBA8_FMT,
	enum_int_t _depth_format,// = PFX_DEPTH_COMPONENT16_FMT,
	enum_int_t _stencil_format// = PFX_STENCIL_INDEX8_FMT
	)
{
	sint_t color_format = _color_format;
	sint_t depth_format = _depth_format;
	sint_t stencil_format = _stencil_format;
	RETURN_INVALID_RESULT((!width) || (!height) ||
		(color_format < 0 || color_format >= PFX_UNKNOW_COLOR_FMT) ||
		(depth_format >= PFX_UNKOWN_DEPTH_BUFFER_FMT) ||
		(stencil_format >= PFX_UNKOWN_STENCIL_BUFFER_FMT)
		, PFX_STATUS_INVALID_PARAMS);

	if (m_framebufferID)
	{
		for (index_t i = 3; i != 0;)
		{
			--i;
			if (m_fbo_tag.m_render_target_ptr[i])
			{
				m_fbo_tag.m_render_target_ptr[i]->dispose();
				m_fbo_tag.m_render_target_ptr[i] = null;
			}
		}
	}

	ctexture2D_gles2* tex2d_ptr = null;
	result_t status = PFX_STATUS_FAIL;

	crenderbuffer_gles2* depth_ptr = null;
	crenderbuffer_gles2* stencil_ptr = null;
	FOR_ONE_LOOP_BEGIN
	
	tex2d_ptr = ctexture2D_gles2::create_new_object();
	BREAK_LOOP_CONDITION(null == tex2d_ptr);

	status = tex2d_ptr->create_rendertarget(width, height, color_format);
	BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);

	tex2d_ptr->set_texture_filter(PFX_TRN_MIN_FILTER, PFX_TP_NEAREST);
	tex2d_ptr->set_texture_filter(PFX_TRN_MAG_FILTER, PFX_TP_NEAREST);

	status = attach_texture(PFX_COLOR_BUFFER_FMT, tex2d_ptr);
	BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);

	if (depth_format >= 0)
	{
		depth_ptr = crenderbuffer_gles2::create_new_object();
		BREAK_LOOP_CONDITION(null == depth_ptr);

		status = depth_ptr->create_rendertarget(PFX_DEPTH_BUFFER_FMT, 
			depth_format, width, height);
		BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);
		
		status = attach_renderbuffer(depth_ptr);
		BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);
	}

	if (stencil_format >= 0)
	{
		stencil_ptr = crenderbuffer_gles2::create_new_object();
		BREAK_LOOP_CONDITION(null == stencil_ptr);

		status = stencil_ptr->create_rendertarget(PFX_STENCIL_BUFFER_FMT,
			stencil_format, width, height);
		BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);

		status = attach_renderbuffer(stencil_ptr);
		BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);
	}

	status = PFX_STATUS_OK;

	FOR_ONE_LOOP_END

	if (tex2d_ptr)
	{
		tex2d_ptr->dispose();
	}
	if (depth_ptr)
	{
		depth_ptr->dispose();
	}
	if (stencil_ptr)
	{
		stencil_ptr->dispose();
	}
	
	if (PFX_STATUS_OK == status)
	{
		status = complete_attachment();
	}
	return status;
}
result_t cnative_framebuffer_gles2::dispose()
{
	result_t status = PFX_STATUS_OK;
	for (index_t i = 3; i != 0;)
	{
		--i;
		result_t sub_status = PFX_STATUS_OK;
		if (m_fbo_tag.m_render_target_ptr[i])
		{
			sub_status = m_fbo_tag.m_render_target_ptr[i]->dispose();
			m_fbo_tag.m_render_target_ptr[i] = null;
		}
		if (PFX_STATUS_OK == status)
		{
			status = sub_status;
		}
	}
	m_width = 0;
	m_height = 0;
	return dispose_render_target();
}
result_t cnative_framebuffer_gles2::dispose_render_target()
{
	result_t status = PFX_STATUS_OK;
	for (index_t i = 3; i != 0;)
	{
		--i;
		result_t sub_status = PFX_STATUS_OK;
		if (m_fbo_tag.m_render_target_ptr[i])
		{
			sub_status = m_fbo_tag.m_render_target_ptr[i]->dispose_render_target();
		}
		if (PFX_STATUS_OK == status)
		{
			status = sub_status;
		}
	}
	if (m_framebufferID)
	{
		::glDeleteFramebuffers(1, &m_framebufferID);
		m_framebufferID = 0;
	}
	m_fbo_complete_status = -1;

	return status;
}
result_t cnative_framebuffer_gles2::bind()
{
	if (PFX_STATUS_OK == complete_attachment())
	{
		return PFX_STATUS_OK;
	}
	else
	{
		return update_default();
	}
}
result_t cnative_framebuffer_gles2::bind_framebuffer()
{
	if (m_framebufferID)
	{
		::glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);
		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_UNINIT;
	}
}
result_t cnative_framebuffer_gles2::update_default()
{
	if (m_framebufferID)
	{
		::glBindFramebuffer(GL_FRAMEBUFFER,m_framebufferID);
		return PFX_STATUS_OK;
	}

	result_t status = PFX_STATUS_OK;
	for (index_t i = 3; i != 0;)
	{
		--i;
		if (m_fbo_tag.m_render_target_ptr[i])
		{
			status = m_fbo_tag.m_render_target_ptr[i]->update_default();
		}
		if (PFX_STATUS_OK != status)
		{
			break;
		}
	}

	RETURN_INVALID_RESULT((PFX_STATUS_OK != status), status);

	//////////////////////////////////////////////////////////////////////////
	enum_int_t tag_type = PFX_UNKOWN_TAG;
	
	FOR_ONE_LOOP_BEGIN

	// color format
	if (m_fbo_tag.m_tags.m_color_buffer_ptr)
	{
		tag_type = m_fbo_tag.m_tags.m_color_buffer_ptr->get_target_type();
		if (PFX_TEXTURE_TAG == tag_type)
		{
			status = attach_texture(PFX_COLOR_BUFFER_FMT,
				m_fbo_tag.m_tex_tags.m_color_buffer_ptr,
				0, m_mip_level[PFX_COLOR_BUFFER_FMT],
				m_surface_type[PFX_COLOR_BUFFER_FMT]);
		}
		else if (PFX_RENDER_BUFFER_TAG == tag_type)
		{
			status = attach_renderbuffer(m_fbo_tag.m_buf_tags.m_color_buffer_ptr);
		}
		else
		{
			status = PFX_STATUS_INVALID_VALUE;
		}

		BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);
	}


	// depth format
	if (m_fbo_tag.m_tags.m_depth_buffer_ptr)
	{
		tag_type = m_fbo_tag.m_tags.m_depth_buffer_ptr->get_target_type();
		if (PFX_TEXTURE_TAG == tag_type)
		{
			status = attach_texture(PFX_DEPTH_BUFFER_FMT,
				m_fbo_tag.m_tex_tags.m_depth_buffer_ptr,
				0, m_mip_level[PFX_DEPTH_BUFFER_FMT],
				m_surface_type[PFX_DEPTH_BUFFER_FMT]);
		}
		else if (PFX_RENDER_BUFFER_TAG == tag_type)
		{
			status = attach_renderbuffer(m_fbo_tag.m_buf_tags.m_depth_buffer_ptr);
		}
		else
		{
			status = PFX_STATUS_INVALID_VALUE;
		}

		BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);
	}


	//
	if (m_fbo_tag.m_tags.m_stencil_buffer_ptr)
	{
		tag_type = m_fbo_tag.m_tags.m_stencil_buffer_ptr->get_target_type();
		if (PFX_RENDER_BUFFER_TAG == tag_type)
		{
			status = attach_renderbuffer(m_fbo_tag.m_buf_tags.m_stencil_buffer_ptr);
		}
		else
		{
			status = PFX_STATUS_INVALID_VALUE;
		}

		BREAK_LOOP_CONDITION(PFX_STATUS_OK != status);
	}


	status = complete_attachment();

	FOR_ONE_LOOP_END

	return status;
}

PECKER_END

