/*
 * pfx_texture_opengles.cpp
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include "pfx_texture_opengles.h"
PECKER_BEGIN

CPfx_texture_opengles2::~CPfx_texture_opengles2()
{

}
pfx_result_t CPfx_texture_opengles2::init_texture(PFX_TEXTURE_TYPE_t type_)
{
	return 0;
}

pfx_result_t CPfx_texture_opengles2::dispose_texture()
{
	return 0;
}

pfx_long_t CPfx_texture_opengles2::get_texture() const
{
	return 0;
}

PFX_TEXTURE_TYPE_t CPfx_texture_opengles2::get_texture_type() const
{
	return PFX_TEXTURE_TYPE_COUNT;
}

pfx_result_t CPfx_texture_opengles2::load_texture_from_memery (PFX_TEXTURE_SURFACE_TYPE_t surface_type_, 
	pfx_usize_t miplevel, 
	PFX_IMAGE_STORAGE_FORMAT_t texture_strorage_format, 
	const PFX_CONST_IMAGE_t* PARAM_IN image_, 
	pfx_sint_t border_ /* = 0 */)
{
	return 0;
}

pfx_result_t CPfx_texture_opengles2::update_sub_texture_from_memery (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
	pfx_usize_t miplevel,
	pfx_index_t offset_x,
	pfx_index_t offset_y,
	const PFX_CONST_IMAGE_t* PARAM_IN image_)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
pfx_result_t CPfx_texture_opengles2::load_compressed_texture_from_memery (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
	pfx_usize_t miplevel,
	PFX_IMAGE_STORAGE_FORMAT_t	texture_strorage_format,
	const PFX_CONST_COMPRESSED_IMAGE_t* PARAM_IN image_,
	pfx_sint_t	border_ /*= 0*/)
{
	return 0;
}

pfx_result_t CPfx_texture_opengles2::update_sub_compressed_texture_from_memery (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
	pfx_usize_t miplevel,
	pfx_index_t offset_x,
	pfx_index_t offset_y,
	const PFX_CONST_COMPRESSED_IMAGE_t* PARAM_IN image_)
{
	return 0;
}
//////////////////////////////////////////////////////////////////////////

pfx_result_t CPfx_texture_opengles2::begin_setting_texture (pfx_index_t texture_unit /*= -1*/)
{
	return 0;
}
pfx_result_t CPfx_texture_opengles2::end_setting_texture (pfx_boolean_t texture_unit_recover /*= pfx_true*/)
{
	return 0;
}

pfx_result_t CPfx_texture_opengles2::set_texture_params (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
	PFX_TEXTURE_PARAMS_NAME_t	params_name,
	PFX_TEXTURE_PARAMS_t				param_)
{
	return 0;
}

pfx_result_t CPfx_texture_opengles2::get_texture_params (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
	PFX_TEXTURE_PARAMS_NAME_t				params_name,
	PFX_TEXTURE_PARAMS_t& PARAM_OUT param_)
{
	return 0;
}

pfx_result_t CPfx_texture_opengles2::get_texture_info (PFX_TEXTURE_SURFACE_TYPE_t surface_type_, 
	PFX_CONST_COMPRESSED_IMAGE_t& image_info_) const
{
	return 0;
}

pfx_result_t CPfx_texture_opengles2::generate_mipmap ()
{
	return 0;
}




PECKER_END


