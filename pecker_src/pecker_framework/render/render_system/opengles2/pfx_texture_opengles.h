/*
 * pfx_texture_opengles.h
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_TEXTURE_OPENGLES2_H_
#define		PFX_TEXTURE_OPENGLES2_H_

#include "../pfx_texture.h"

PECKER_BEGIN

class PFX_RENDER_SYSTEM_API CPfx_texture_opengles2 : public Ipfx_texture
{
public:
	virtual pfx_result_t init_texture (PFX_TEXTURE_TYPE_t type_);
	virtual pfx_result_t dispose_texture ();

	virtual pfx_long_t get_texture () const;
	virtual PFX_TEXTURE_TYPE_t get_texture_type () const;
	
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t load_texture_from_memery (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
		pfx_usize_t miplevel,
		PFX_IMAGE_STORAGE_FORMAT_t	texture_strorage_format,
		const PFX_CONST_IMAGE_t* PARAM_IN image_,
		pfx_sint_t	border_ = 0);

	virtual pfx_result_t update_sub_texture_from_memery (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
		pfx_usize_t miplevel,
		pfx_index_t offset_x,
		pfx_index_t offset_y,
		const PFX_CONST_IMAGE_t* PARAM_IN image_);

	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t load_compressed_texture_from_memery (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
		pfx_usize_t miplevel,
		PFX_IMAGE_STORAGE_FORMAT_t	texture_strorage_format,
		const PFX_CONST_COMPRESSED_IMAGE_t* PARAM_IN image_,
		pfx_sint_t	border_ = 0);

	virtual pfx_result_t update_sub_compressed_texture_from_memery (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
		pfx_usize_t miplevel,
		pfx_index_t offset_x,
		pfx_index_t offset_y,
		const PFX_CONST_COMPRESSED_IMAGE_t* PARAM_IN image_);
	//////////////////////////////////////////////////////////////////////////

	virtual pfx_result_t begin_setting_texture (pfx_index_t texture_unit = -1);
	virtual pfx_result_t end_setting_texture (pfx_boolean_t texture_unit_recover = pfx_true);

	virtual pfx_result_t set_texture_params (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
		PFX_TEXTURE_PARAMS_NAME_t	params_name,
		PFX_TEXTURE_PARAMS_t				param_);

	virtual pfx_result_t get_texture_params (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
		PFX_TEXTURE_PARAMS_NAME_t				params_name,
		PFX_TEXTURE_PARAMS_t& PARAM_OUT param_);

	virtual pfx_result_t get_texture_info (PFX_TEXTURE_SURFACE_TYPE_t surface_type_, 
																	PFX_CONST_COMPRESSED_IMAGE_t& image_info_) const;  

	virtual pfx_result_t generate_mipmap ();
	//////////////////////////////////////////////////////////////////////////
	//virtual pfx_result_t set_texture_unit (pfx_index_t unit_number) = 0;
	//////////////////////////////////////////////////////////////////////////
	//CPfx_texture_opengles (Ipfx_render_device)
	virtual ~CPfx_texture_opengles2 ();
};

PECKER_END

#endif			//PFX_TEXTURE_OPENGLES2_H_
