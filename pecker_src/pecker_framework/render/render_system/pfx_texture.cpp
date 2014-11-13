/*
 * pfx_texture.cpp
 *
 *  Created on: 2014-9-6
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_texture.h"

PECKER_BEGIN

ctexture_surface::ctexture_surface()
{
	;
}

ctexture_surface::~ctexture_surface()
{
	;
}

result_t   ctexture_surface::update_image(sImage_t* image_ptr,
	enum_int_t render_color_type,
	uindex_t mip_level// = 0
	)
{
	RETURN_INVALID_RESULT(null == image_ptr || render_color_type > PFX_UNKNOW_COLOR_FMT, 
		PFX_STATUS_INVALID_PARAMS);
	RETURN_INVALID_RESULT(mip_level > get_max_miplevel(), PFX_STATUS_DENIED);

	mip_image_t* mip_image_ptr = get_image(mip_level);
	result_t status;
	if (null == mip_image_ptr)
	{
		status = m_mip_images.resize(mip_level + 1);
		RETURN_INVALID_RESULT(PFX_STATUS_OK > status, status);
		mip_image_ptr = get_image(mip_level);
	}
	sImage_t* new_ptr = image_ptr->new_ref();
	RETURN_INVALID_RESULT(null == new_ptr, PFX_STATUS_FAIL);

	if (mip_image_ptr->m_image_ptr)
	{
		mip_image_ptr->m_image_ptr->dispose_object();
	}
	mip_image_ptr->m_image_ptr = new_ptr;
	mip_image_ptr->m_rcolor_type = render_color_type;

	return PFX_STATUS_OK;
}

result_t   ctexture_surface::update_image_with_copy(sImage_t* image_ptr,
	enum_int_t render_color_type,
	uindex_t mip_level //= 0
	)
{
	RETURN_INVALID_RESULT(null == image_ptr || render_color_type > PFX_UNKNOW_COLOR_FMT,
		PFX_STATUS_INVALID_PARAMS);
	RETURN_INVALID_RESULT(mip_level > get_max_miplevel(), PFX_STATUS_DENIED);

	mip_image_t* mip_image_ptr = get_image(mip_level);
	result_t status;
	if (null == mip_image_ptr)
	{
		status = m_mip_images.resize(mip_level + 1);
		RETURN_INVALID_RESULT(PFX_STATUS_OK > status, status);
		mip_image_ptr = get_image(mip_level);
	}
	sImage_t* new_ptr = image_ptr->create_object();
	RETURN_INVALID_RESULT(null == new_ptr, PFX_STATUS_FAIL);
	
	status= image_ptr->native().copy_to(new_ptr->native());
	RETURN_INVALID_RESULT(PFX_STATUS_OK > status, status);

	if (mip_image_ptr->m_image_ptr)
	{
		mip_image_ptr->m_image_ptr->dispose_object();
	}
	mip_image_ptr->m_image_ptr = new_ptr;
	mip_image_ptr->m_rcolor_type = render_color_type;

	return PFX_STATUS_OK;
}

result_t   ctexture_surface::auto_mipmap(usize__t max_mip_level)
{
	return PFX_STATUS_DENIED;
}

result_t   ctexture_surface::clean()
{
	return m_mip_images.clean();
}




PECKER_END


