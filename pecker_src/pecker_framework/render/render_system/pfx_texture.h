/*
 * pfx_texture.h
 *
 *  Created on: 2013-11-16
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_TEXTURE_H_
#define		PFX_TEXTURE_H_

#include "../../pfx_defines.h"
#include "../pfx_image.h"
PECKER_BEGIN
	
typedef enum enumTEXTURE_TYPE
{
	PFX_TEXTURE_DEFUALT = 0,

	PFX_TEXTURE_2D,
	PFX_TEXTURE_CUBE_MAP,

	PFX_TEXTURE_TYPE_COUNT
}PFX_TEXTURE_TYPE_t;

typedef enum enumTEXTURE_SURFACE_TYPE
{
	PFX_TEXTURE_DEFUALT_SURFACE = 0,

	PFX_TEXTURE_2D_SURFACE,

	PFX_TEXTURE_CUBE_MAP_POSITIVE_X_SURFACE,
	PFX_TEXTURE_CUBE_MAP_POSITIVE_Y_SURFACE,
	PFX_TEXTURE_CUBE_MAP_POSITIVE_Z_SURFACE,

	PFX_TEXTURE_CUBE_MAP_NEGATIVE_X_SURFACE,
	PFX_TEXTURE_CUBE_MAP_NEGATIVE_Y_SURFACE,
	PFX_TEXTURE_CUBE_MAP_NEGATIVE_Z_SURFACE,

	PFX_TEXTURE_TYPE_COUNT
}PFX_TEXTURE_SURFACE_TYPE_t;

typedef enum enumTEXTURE_PARAMS_NAME
{
	PFX_TRN_MAG_FILTER = 0,
	PFX_TRN_MIN_FILTER,
	PFX_TRN_WRAP_S,
	PFX_TRN_WRAP_T,

	PFX_TEXTURE_PARAMS_NAME_COUNT
}PFX_TEXTURE_PARAMS_NAME_t;

typedef enum enumTEXTURE_PARAMS
{
	//PFX_TRN_MAG_FILTER
	PFX_TP_NEAREST = 0
	PFX_TP_LINEAR,

	//PFX_TRN_MIN_FILTER
	PFX_TP_NEAREST,
	PFX_TP_LINEAR,
	PFX_TP_NEAREST_MIPMAP_NEAREST,
	PFX_TP_NEAREST_MIPMAP_LINEAR,
	PFX_TP_LINEAR_MIPMAP_NEAREST,
	PFX_TP_LINEAR_MIPMAP_LINEAR,

	//PFX_TRN_WRAP_S
	//PFX_TRN_WRAP_T
	PFX_TP_REPEAT,
	PFX_TP_CLAMP_TO_EDGE,
	PFX_TP_MIRRORED_REPEAT,

	PFX_TEXTURE_PARAMS_COUNT
}PFX_TEXTURE_PARAMS_t;

PFX_Interface Ipfx_texture
{
	virtual pfx_result_t init_texture (PFX_TEXTURE_TYPE_t type_) = 0;
	virtual pfx_result_t dispose_texture () = 0;
	
	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t load_texture_from_memery (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
		pfx_usize_t miplevel,
		PFX_IMAGE_STORAGE_FORMAT_t	texture_strorage_format,
		const PFX_CONST_IMAGE_t* PARAM_IN image_,
		pfx_sint_t	border_ = 0) = 0;

	virtual pfx_result_t update_sub_texture_from_memery (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
		pfx_usize_t miplevel,
		pfx_index_t offset_x,
		pfx_index_t offset_y,
		const PFX_CONST_IMAGE_t* PARAM_IN image_) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual pfx_result_t load_compressed_texture_from_memery (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
		pfx_usize_t miplevel,
		PFX_IMAGE_STORAGE_FORMAT_t	texture_strorage_format,
		const PFX_CONST_COMPRESSED_IMAGE_t* PARAM_IN image_,
		pfx_sint_t	border_ = 0) = 0;

	virtual pfx_result_t update_sub_compressed_texture_from_memery (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
		pfx_usize_t miplevel,
		pfx_index_t offset_x,
		pfx_index_t offset_y,
		const PFX_CONST_COMPRESSED_IMAGE_t* PARAM_IN image_) = 0;
	//////////////////////////////////////////////////////////////////////////

	virtual pfx_result_t begin_setting_texture (PFX_TEXTURE_TYPE_t surface_type_ = PFX_TEXTURE_DEFUALT_SURFACE) = 0;
	virtual pfx_result_t end_setting_texture () = 0;

	virtual pfx_result_t set_texture_params (PFX_TEXTURE_SURFACE_TYPE_t surface_type_,
		PFX_TEXTURE_PARAMS_NAME_t	params_name,
		PFX_TEXTURE_PARAMS_t				param_) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual ~Ipfx_texture (){;}
};

PECKER_END

#endif			//PFX_TEXTURE_H_
