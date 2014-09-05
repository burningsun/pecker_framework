/*
 * pfx_texture.h
 *
 *  Created on: 2013-11-16
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_TEXTURE_H_
#define		PFX_TEXTURE_H_

#include "../../include/config"
#include "../../include/util"
#include "../pfx_render_defs.h"
#include "../pfx_color.h"
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

	PFX_TEXTURE_SURFACE_TYPE_COUNT
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
	
	PFX_TP_NEAREST = 0,
	PFX_TP_LINEAR,

	///////////////////////////
	//PFX_TRN_MAG_FILTER,
	//PFX_TRN_MIN_FILTER,

	//PFX_TP_NEAREST,
	//PFX_TP_LINEAR,
	PFX_TP_NEAREST_MIPMAP_NEAREST,
	PFX_TP_NEAREST_MIPMAP_LINEAR,
	PFX_TP_LINEAR_MIPMAP_NEAREST,
	PFX_TP_LINEAR_MIPMAP_LINEAR,

	//////////////////////////
	//PFX_TRN_WRAP_S,
	//PFX_TRN_WRAP_T,
	
	PFX_TP_REPEAT,
	PFX_TP_CLAMP_TO_EDGE,
	PFX_TP_MIRRORED_REPEAT,

	PFX_TEXTURE_PARAMS_COUNT
}PFX_TEXTURE_PARAMS_t;

typedef struct texture_bits
{
	//pfx_byte_t*										m_bits_ptr;
	//pfx_usize_t										m_bytes_count;
	//pfx_sint_t											m_border;		
	//PFX_COLOR_FORMAT_TYPE_t		m_color_format;
	image_bits_t										m_image_bits;
	enum_int_t										m_texture_color_format; //PFX_TEXTURE_PARAMS_t
	rectangle_region < usize__t >		m_texture_region;
	boolean_t											m_enable_active;
}texture_bits_t;

typedef struct texture_param
{
	enum_int_t	m_name;
	enum_int_t	m_param_value;
}texture_param_t;

PFX_Interface Ipfx_update_texture_layer_usermode
{
	virtual result_t update_texture_layer (texture_bits_t* PARAM_INOUT lock_bits_ptr) = 0;
};


PFX_Interface Ipfx_texture_layer
{
	//virtual result_t								lock_texture (texture_bits_t* & PARAM_INOUT lock_bits_ptr) = 0;
	//virtual result_t								unlock_texture () = 0;

	//// 使用 lock_and_unlock_texture 等价于lock_texture和unlock_texture配合使用
	//virtual result_t								update_texture (Ipfx_update_texture_layer_usermode* PARAM_IN usermode_settings_ptr) = 0;

	//virtual uindex_t							get_layer_level () const = 0;
	////
	//virtual result_t								bind_texture () = 0;
	//virtual const PFX_Interface		IPfx_texture* get_texture () const = 0;
};

PFX_Interface IPfx_texture
{
	virtual result_t   update_image(enum_int_t surface_type, // PFX_TEXTURE_SURFACE_TYPE_t
	                                sImage_t* image_ptr,
	                                enum_int_t render_color_type,
									uindex_t mip_level = 0) = 0;

	virtual sImage_t*  get_image(uindex_t mip_level) = 0;
	virtual enum_int_t get_texture_layer_type() const = 0; //PFX_TEXTURE_TYPE_t
	virtual enum_int_t get_render_system_type() const = 0;
	virtual result_t   update_rect(const texture_rect_t& __rect,
		const byte_t* buffer_ptr,
		usize__t bytes_count,
		uindex_t miplevel = 0,
		bool bmodify_ram_image = false) = 0;

	virtual result_t set_texture_filter(enum_int_t param_name, enum_int_t __param);
	virtual result_t clone_image() = 0;
	virtual result_t auto_mipmap() = 0;
	virtual result_t bind_texture() = 0;
	virtual usize__t get_max_miplevel() const = 0;
	virtual long_t   get_native_handle() const = 0;
	//virtual enum_int_t						get_texture_type () const = 0; //enum_int_t
	//virtual enum_int_t						get_render_system_type () const = 0;

	//virtual result_t								attach_texture_layer (Ipfx_texture_layer* PARAM_IN texture_layer_ptr) = 0;
	//virtual result_t								bind_texture () = 0;
	//virtual Ipfx_texture_layer*		get_texture_layer (uindex_t mipLevel) = 0;
};


PECKER_END

#endif			//PFX_TEXTURE_H_
