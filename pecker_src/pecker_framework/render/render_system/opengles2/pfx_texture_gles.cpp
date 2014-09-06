/*
 * pfx_texture_gles.cpp
 *
 *  Created on: 2014-7-27
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */


#include "pfx_texture_gles.h"
#include "pfx_color_gles.h"

PECKER_BEGIN

cnative_texture2D_gles::cnative_texture2D_gles() :m_textureID(0), m_surface_ptr(null), 
m_internal_format(GL_RGBA)
{

}
cnative_texture2D_gles::~cnative_texture2D_gles()
{
	dispose();

}



result_t   cnative_texture2D_gles::update_surface(ctexture_surface* PARAM_IN surface_ptr)
{
	RETURN_INVALID_RESULT(null == surface_ptr && null == m_surface_ptr, PFX_STATUS_UNINIT);

	if (null == surface_ptr && m_surface_ptr)
	{
		if (0 == m_textureID)
		{
			::glGenTextures(1, &m_textureID);
		}
		RETURN_INVALID_RESULT(0 == m_textureID, 
			PFX_STATUS_FAIL);

		bind();

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


			cImage& img_ref = simg_ptr->native();
			const image_data_t& img = img_ref.get_image_direct();
			GLint img_clr_format = PFX_CLR_2_GLES2_CLR(img.m_img.m_color_format);
			
			::glPixelStorei(GL_UNPACK_ALIGNMENT, img.m_pack_size);
			if (img_clr_format >= 0 && internal_format >= 0)
			{
				if (PFX_IMG_UNCOMPRESS_FMT == img.m_img.m_compression_format)
				{
					GLenum enum_bytes_type = PFX_CLR_GET_GLES2_CLR_BITS_TYPE(img.m_img.m_color_format);
					::glTexImage2D(GL_TEXTURE_2D, imip, internal_format, img.m_img.m_width,
						img.m_img.m_height, 0, img_clr_format,
						enum_bytes_type, img.m_img.m_bits_ptr);
				}
				else
				{
					::glCompressedTexImage2D(GL_TEXTURE_2D, imip, internal_format, img.m_img.m_width,
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
	}


	return update_surface(null);
}


result_t   cnative_texture2D_gles::update_rect(const texture_rect_t& __rect,
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
		if (PFX_IMG_UNCOMPRESS_FMT == img.m_img.m_compression_format)
		{
			if (__rect.m_width * __rect.m_height * img.m_img.m_stride > bytes_count)
			{
				simg_ptr->dispose_object();
				return PFX_STATUS_INVALID_PARAMS;
			}
			GLenum enum_bytes_type = PFX_CLR_GET_GLES2_CLR_BITS_TYPE(img.m_img.m_color_format);
			::glTexSubImage2D(GL_TEXTURE_2D, miplevel,
				__rect.m_x, __rect.m_y, __rect.m_width, __rect.m_height,
				img_clr_format, enum_bytes_type, buffer_ptr);
		}
		else
		{
			::glCompressedTexSubImage2D(GL_TEXTURE_2D, miplevel,
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


void cnative_texture2D_gles::bind()
{
	::glBindTexture(GL_TEXTURE_2D, m_textureID);
}



void cnative_texture2D_gles::dispose_render_target()
{
	if (m_textureID)
	{
		::glDeleteTextures(1, &m_textureID);
		m_textureID = 0;
	}
}
void cnative_texture2D_gles::dispose()
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
}

void cnative_texture2D_gles::set_texture_filter(enum_int_t param_name, enum_int_t __param)
{
	if (m_textureID)
	{
		::glBindTexture(GL_TEXTURE_2D, m_textureID);
		::glTexParameteri(GL_TEXTURE_2D, param_name, __param);
	}
	
}

PECKER_END

