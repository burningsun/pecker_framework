/*
 * pfx_framebuffer_object_gles.cpp
 *
 *  Created on: 2014-10-15
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_framebuffer_object_gles.h"
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

cnative_renderbuffer_gles::cnative_renderbuffer_gles() :m_renderbufferID(0),
                                                        m_usage_type(PFX_DEPTH_BUFFER_FMT),
														m_internalformat(PFX_DEPTH_COMPONENT16_FMT),
														m_width(0),
														m_height(0)
{

}
cnative_renderbuffer_gles::~cnative_renderbuffer_gles()
{
	dispose();
}



result_t cnative_renderbuffer_gles::store_renderbuffer(enum_int_t usage_type, //  PFX_RENDER_BUFFER_FMT_t
enum_int_t format,
usize__t width, usize__t height)
{
	RETURN_INVALID_RESULT((!width || !height || usage_type < PFX_UNKOWN_RENDER_BUFFER_FMT),
		PFX_STATUS_INVALID_PARAMS);

	GLint maxRenderbufferSize;
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderbufferSize);
	GLenum internalformat = PFX_FMT_TO_GLRB_FMT(usage_type, format);

	RETURN_INVALID_RESULT((width > maxRenderbufferSize 
		|| height > maxRenderbufferSize
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

result_t cnative_renderbuffer_gles::bind()
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
result_t cnative_renderbuffer_gles::dispose()
{
	m_usage_type = PFX_DEPTH_BUFFER_FMT;
	m_internalformat = PFX_DEPTH_COMPONENT16_FMT;
	m_width = 0;
	m_height = 0;
	return dispose_render_target();
}
result_t cnative_renderbuffer_gles::dispose_render_target()
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

PECKER_END

