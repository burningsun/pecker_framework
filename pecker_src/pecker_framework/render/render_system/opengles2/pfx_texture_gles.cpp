/*
 * pfx_texture_gles.cpp
 *
 *  Created on: 2014-7-27
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */


#include "pfx_texture_gles.h"
#include "pfx_color_gles.h"

PECKER_BEGIN


cnative_texture2D_gles2::cnative_texture2D_gles2() :m_textureID(0), m_surface_ptr(null), 
m_color_format(GL_RGBA), m_render_height(0), m_render_width(0), m_bupdate(true), 
m_tex_surface_type(PFX_TEXTURE_2D_SURFACE),
m_gl_tex_surface_type(GL_TEXTURE_2D),
m_texfilter_param_bufsize(0)
{

	for (uindex_t i = PFX_TEXTURE_PARAMS_NAME_COUNT; i != 0;)
	{
		--i;
		m_texfilers[i] = -1;
	}
}
cnative_texture2D_gles2::~cnative_texture2D_gles2()
{
	dispose();

} 



result_t  cnative_texture2D_gles2::create_rendertarget(PFX_TEXTURE_SURFACE_TYPE_t sur_type, 
	usize__t width, usize__t height, enum_int_t color_format)
{

	GLint internal_format = PFX_CLR_2_GLES2_CLR(color_format);
	GLenum enum_bytes_type = PFX_CLR_GET_GLES2_CLR_BITS_TYPE(color_format);
	RETURN_INVALID_RESULT(color_format < 0 || enum_bytes_type < 0, PFX_STATUS_INVALID_PARAMS);

	if (0 == m_textureID)
	{
		::glGenTextures(1, &m_textureID);
		RETURN_INVALID_RESULT(0 == m_textureID,
			PFX_STATUS_FAIL);
		reset_texture_filter();
		m_bupdate = true;
	}

	m_color_format = color_format;
	m_tex_surface_type = sur_type;

	m_gl_tex_surface_type = PFX_TEXSUR_2_GL_TEXSUR(sur_type);
	if (width && height)
	{
		if (width != m_render_height && height != m_render_width)
		{
			m_bupdate = true;
		}
		
		if (m_bupdate)
		{
			bind();
			::glTexImage2D(m_gl_tex_surface_type, 0, internal_format, width,
				height, 0, internal_format,
				enum_bytes_type, null);
			m_bupdate = false;
			
		}


		m_render_width = width;
		m_render_height = height;
		
	}
	else
	{
		m_render_width = 0;
		m_render_height = 0;
	}

	return PFX_STATUS_OK;
}

result_t   cnative_texture2D_gles2::update_surface(ctexture_surface* PARAM_IN surface_ptr)
{
	if (null == m_surface_ptr && null == surface_ptr)
	{
		if (m_render_height && m_render_width)
		{
			return create_rendertarget(m_tex_surface_type,m_render_width, m_render_height, m_color_format);
		}
		return PFX_STATUS_UNINIT;
	}

	if (null == surface_ptr && m_surface_ptr)
	{
		if (0 == m_textureID)
		{
			::glGenTextures(1, &m_textureID);
			reset_texture_filter();
			m_bupdate = true;			
		}
		else
		{
			bind();
		}

		RETURN_INVALID_RESULT(0 == m_textureID, 
			PFX_STATUS_FAIL);

		RETURN_RESULT(!m_bupdate, PFX_STATUS_OK);

		m_bupdate = false;
		

		usize__t max_mip_level = m_surface_ptr->get_max_miplevel();
		uindex_t imip = 0;

		for (; imip < max_mip_level; ++imip)
		{
			mip_image_t* mip_img_ptr; 
			sImage_t* simg_ptr;
			mip_img_ptr = m_surface_ptr->get_image(imip);

			if (mip_img_ptr && mip_img_ptr->m_image_ptr)
			{
				simg_ptr = mip_img_ptr->m_image_ptr->new_ref();
			}
			else
			{
				RTEX_LOG_ERR("mip_img_ptr = 0x%08X", ((lpointer_t)mip_img_ptr));
				break;
			}

			GLint internal_format = PFX_CLR_T_2_GLES2_CLR(mip_img_ptr->m_rcolor_type);
			m_gl_tex_surface_type = PFX_TEXSUR_2_GL_TEXSUR(m_tex_surface_type);

			cImage& img_ref = simg_ptr->native();
			const image_data_t& img = img_ref.get_image_direct();
			GLint img_clr_format = PFX_CLR_2_GLES2_CLR(img.m_img.m_color_format);
			
			::glPixelStorei(GL_UNPACK_ALIGNMENT, img.m_pack_size);
			if (img_clr_format >= 0 && internal_format >= 0)
			{
				if (PFX_IMG_UNCOMPRESS_FMT == img.m_img.m_compression_format)
				{
					GLenum enum_bytes_type = PFX_CLR_GET_GLES2_CLR_BITS_TYPE(img.m_img.m_color_format);
						::glTexImage2D(m_gl_tex_surface_type, imip, internal_format, img.m_img.m_width,
							img.m_img.m_height, 0, img_clr_format,
							enum_bytes_type, img.m_img.m_bits_ptr);

				}
				else
				{
					::glCompressedTexImage2D(m_gl_tex_surface_type, imip, internal_format, img.m_img.m_width,
						img.m_img.m_height, 0, img.m_img.m_bytes_count, img.m_img.m_bits_ptr);
				}
			}
			else
			{
				simg_ptr->dispose_object();
				RTEX_LOG_ERR("unkown format for opengl es2, pfx format = %d", img.m_img.m_color_format);
				break;
			}

			simg_ptr->dispose_object();

		}
		if (imip > 0)
		{
			return PFX_STATUS_OK;
		}
		else
		{
			return PFX_STATUS_FAIL;
		}

	}

	if (surface_ptr != m_surface_ptr)
	{
		ctexture_surface* new_ptr = surface_ptr->new_ref();

		if (null == new_ptr)
		{
			return PFX_STATUS_FAIL;
		}

		if (m_surface_ptr)
		{
			m_surface_ptr->dispose_object();
		}
		m_surface_ptr = new_ptr;
		m_render_height = 0;
		m_render_width  = 0;
		m_bupdate = true;
	}


	return update_surface(null);
}


result_t   cnative_texture2D_gles2::update_rect(const texture_rect_t& __rect,
	const byte_t* buffer_ptr,
	usize__t bytes_count,
	uindex_t miplevel //= 0
	)
{
	RETURN_INVALID_RESULT(null == m_surface_ptr, PFX_STATUS_UNINIT);

	mip_image_t* mip_img_ptr;
	sImage_t* simg_ptr;
	mip_img_ptr = m_surface_ptr->get_image(miplevel);

	RETURN_INVALID_RESULT(null == mip_img_ptr || null == mip_img_ptr->m_image_ptr,
		PFX_STATUS_UNINIT);

	simg_ptr = mip_img_ptr->m_image_ptr->new_ref();

	RETURN_INVALID_RESULT(null == simg_ptr, PFX_STATUS_UNINIT);

	cImage& img_ref = simg_ptr->native();
	const image_data_t& img = img_ref.get_image_direct();

	result_t status;
	status = PFX_STATUS_OK;

	GLint img_clr_format = PFX_CLR_2_GLES2_CLR(img.m_img.m_color_format);

	if (img_clr_format >= 0)
	{
		m_gl_tex_surface_type = PFX_TEXSUR_2_GL_TEXSUR(m_tex_surface_type);
		if (PFX_IMG_UNCOMPRESS_FMT == img.m_img.m_compression_format)
		{
			if (__rect.m_width * __rect.m_height * img.m_img.m_stride > bytes_count)
			{
				simg_ptr->dispose_object();
				return PFX_STATUS_INVALID_PARAMS;
			}
			GLenum enum_bytes_type = PFX_CLR_GET_GLES2_CLR_BITS_TYPE(img.m_img.m_color_format);
			::glTexSubImage2D(m_gl_tex_surface_type, miplevel,
				__rect.m_x, __rect.m_y, __rect.m_width, __rect.m_height,
				img_clr_format, enum_bytes_type, buffer_ptr);
		}
		else
		{
			::glCompressedTexSubImage2D(m_gl_tex_surface_type, miplevel,
				__rect.m_x, __rect.m_y, __rect.m_width, __rect.m_height,
				img_clr_format, bytes_count, buffer_ptr);
		}

	}
	else
	{
		status = PFX_STATUS_FAIL;
	}

	simg_ptr->dispose_object();
	return status;
}


void cnative_texture2D_gles2::bind()
{
	::glBindTexture(m_gl_tex_surface_type, m_textureID);
}



void cnative_texture2D_gles2::dispose_render_target()
{
	if (m_textureID)
	{
		::glDeleteTextures(1, &m_textureID);
		m_textureID = 0;
	}
}
void cnative_texture2D_gles2::dispose()
{
	if (m_textureID)
	{
		::glDeleteTextures(1, &m_textureID);
		m_textureID = 0;
	}

	if (m_surface_ptr)
	{
		m_surface_ptr->dispose_object();
		m_surface_ptr = null;
	}

	m_texfilter_param_bufsize = 0;

	for (uindex_t i = PFX_TEXTURE_PARAMS_NAME_COUNT; i != 0;)
	{
		--i;
		m_texfilers[i] = -1;
	}

}

result_t cnative_texture2D_gles2::set_texture_filter(enum_int_t param_name, enum_int_t __param)
{
	if (m_textureID)
	{
		RETURN_INVALID_RESULT(param_name > PFX_TEXTURE_PARAMS_NAME_COUNT || 
			__param > PFX_TEXTURE_PARAMS_COUNT ||
			param_name < 0 ||
			__param < 0 ||
			!CHECK_PFX_TEX_PARAM_OK_GLES2((PFX_TEXTURE_PARAMS_NAME_t)param_name, 
			(PFX_TEXTURE_PARAMS_t)__param), PFX_STATUS_INVALID_PARAMS);

		::glBindTexture(m_gl_tex_surface_type, m_textureID);
		GLenum glparam_name = PFX_TEXFILTER_NAME_2_GLTEXFILTER_NAME((PFX_TEXTURE_PARAMS_NAME_t)param_name);
		GLint glparam = PFX_TEXFILTER_PARAM_2_GLTEXFILTER_PARAM((PFX_TEXTURE_PARAMS_t)__param);

		::glTexParameteri(m_gl_tex_surface_type, glparam_name, glparam);

		if (m_texfilers[param_name] < 0 && 
			m_texfilter_param_bufsize < MAX_TEXFILTER_PARAM_BUFFER_SIZE)
		{
			m_texfilter_param_buf[m_texfilter_param_bufsize] = glparam;
			m_texfilers[param_name] = m_texfilter_param_bufsize;
			m_texfilter_param_bufsize += PFX_TEXFILTER_PARAM_COUNT((PFX_TEXTURE_PARAMS_NAME_t)param_name);
		}
		else if (m_texfilers[param_name] < MAX_TEXFILTER_PARAM_BUFFER_SIZE)
		{
			m_texfilter_param_buf[m_texfilers[param_name]] = glparam;
		}


		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_UNINIT;
	}
	
}

result_t cnative_texture2D_gles2::set_texture_filter(enum_int_t param_name, const enum_int_t* __param_ptr)
{
	RETURN_INVALID_RESULT(null == __param_ptr, PFX_STATUS_INVALID_PARAMS);

	usize__t param_count = PFX_TEXFILTER_PARAM_COUNT((PFX_TEXTURE_PARAMS_NAME_t)param_name);
	if (1 == param_count)
	{
		return set_texture_filter(param_name, __param_ptr[0]);
	}

	if (m_textureID)
	{
#define MAX_GLES2_PARAMCOUNT (8)

		RETURN_INVALID_RESULT(
			param_name > PFX_TEXTURE_PARAMS_NAME_COUNT ||
			param_name < 0, PFX_STATUS_INVALID_PARAMS);

		GLenum glparam_name = PFX_TEXFILTER_NAME_2_GLTEXFILTER_NAME((PFX_TEXTURE_PARAMS_NAME_t)param_name);
		GLint glparam[MAX_GLES2_PARAMCOUNT];

		for (uindex_t i = param_count; i != 0;)
		{
			--i;

			RETURN_INVALID_RESULT(
				__param_ptr[i] > PFX_TEXTURE_PARAMS_COUNT ||
				__param_ptr[i] < 0, PFX_STATUS_INVALID_PARAMS);

			glparam[i] = PFX_TEXFILTER_PARAM_2_GLTEXFILTER_PARAM((PFX_TEXTURE_PARAMS_t)__param_ptr[i]);
		}

		

		::glBindTexture(m_gl_tex_surface_type, m_textureID);
		::glTexParameteriv(m_gl_tex_surface_type, glparam_name, glparam);

		if (m_texfilers[param_name] < 0 &&
			m_texfilter_param_bufsize < MAX_TEXFILTER_PARAM_BUFFER_SIZE)
		{
		    memcpy(m_texfilter_param_buf + m_texfilter_param_bufsize, glparam, param_count);
			m_texfilers[param_name] = m_texfilter_param_bufsize;
			m_texfilter_param_bufsize += param_count;
		}
		else if (m_texfilers[param_name] < MAX_TEXFILTER_PARAM_BUFFER_SIZE)
		{
			memcpy(m_texfilter_param_buf + m_texfilers[param_name], glparam, param_count);
		}


		return PFX_STATUS_OK;
	}
	else
	{
		return PFX_STATUS_UNINIT;
	}
}

result_t cnative_texture2D_gles2::reset_texture_filter()
{
	if (m_textureID)
	{
		::glBindTexture(m_gl_tex_surface_type, m_textureID);
	}
	else
	{
		return PFX_STATUS_UNINIT;
	}
	const usize__t max_filter_count = (sizeof(m_texfilers) / sizeof(enum_int_t));
	for (uindex_t i = 0; i < max_filter_count; ++i)
	{
		index_t offset = m_texfilers[i];
		if (offset < 0)
		{
			continue;
		}
	    GLenum glparam_name = PFX_TEXFILTER_NAME_2_GLTEXFILTER_NAME((PFX_TEXTURE_PARAMS_NAME_t)i);
		GLint* glparam_ptr = (GLint*)(&m_texfilter_param_buf[offset]);
		::glTexParameteriv(m_gl_tex_surface_type, glparam_name, glparam_ptr);
	}
	return PFX_STATUS_OK;
}
PECKER_END

