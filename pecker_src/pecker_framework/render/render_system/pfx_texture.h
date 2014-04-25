/*
 * pfx_texture.h
 *
 *  Created on: 2013-11-16
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_TEXTURE_H_
#define		PFX_TEXTURE_H_

#include "../../pfx_defines.h"
#include "../../data/pfx_region.h"
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
	//PFX_TRN_MAG_FILTER
	PFX_TP_NEAREST = 0,
	PFX_TP_LINEAR,

	//PFX_TRN_MIN_FILTER
	//PFX_TP_NEAREST,
	//PFX_TP_LINEAR,
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

typedef struct texture_bits
{
	//pfx_byte_t*										m_bits_ptr;
	//pfx_usize_t										m_bytes_count;
	//pfx_sint_t											m_border;		
	//PFX_COLOR_FORMAT_TYPE_t		m_color_format;
	image_bits_t										m_image_bits;
		
	PFX_COLOR_FORMAT_TYPE_t		m_texture_color_format;
	rectangle_region < pfx_usize_t >	m_texture_region;
	pfx_boolean_t									m_enable_active;
}texture_bits_t;

typedef struct texture_param
{
	pfx_enum_int_t	m_name;
	pfx_enum_int_t	m_param_value;
}texture_param_t;

PFX_Interface Ipfx_update_texture_layer_usermode
{
	virtual pfx_result_t update_texture_layer (texture_bits_t* PARAM_INOUT lock_bits_ptr) = 0;
};


PFX_Interface Ipfx_texture_layer
{
	virtual PFX_TEXTURE_TYPE_t	get_texture_layer_type () const = 0;
	virtual pfx_enum_int_t				get_render_system_type () const = 0;
	//
	virtual pfx_result_t lock_texture (texture_bits_t* & PARAM_INOUT lock_bits_ptr) = 0;
	virtual pfx_result_t unlock_texture () = 0;

	// 使用 lock_and_unlock_texture 等价于lock_texture和unlock_texture配合使用
	virtual pfx_result_t update_texture (Ipfx_update_texture_layer_usermode* PARAM_IN usermode_settings_ptr) = 0;

	virtual pfx_uindex_t	get_layer_level () const = 0;
	//
	virtual pfx_result_t bind_texture () = 0;
	virtual const PFX_Interface IPfx_texture* get_texture () const = 0;
};

PFX_Interface IPfx_texture
{
	virtual PFX_TEXTURE_TYPE_t	get_texture_type () const = 0;
	virtual pfx_enum_int_t				get_render_system_type () const = 0;

	virtual pfx_result_t attach_texture_layer (Ipfx_texture_layer* PARAM_IN texture_layer_ptr) = 0;
	virtual pfx_result_t bind_texture () = 0;
	virtual Ipfx_texture_layer* get_texture_layer (pfx_uindex_t mipLevel) = 0;
};

template < typename  texture_operate_type >
struct PFX_TextureOperation
{
	typedef typename texture_operate_type::render_device_t		render_device_t;
	typedef typename texture_operate_type::texture_param_t		texture_param_t;

	//static PFX_INLINE pfx_result_t bind_texture (Ipfx_texture_layer* PARAM_INOUT texture_layer_ptr)
	//{
	//	IPfx_texture* texture_ptr = null;
	//	if (texture_layer_ptr)
	//	{
	//		texture_ptr = (IPfx_texture*)(texture_layer_ptr->get_texture ());
	//	}
	//	if (texture_ptr)
	//	{
	//		return texture_ptr->bind_texture ();
	//	}
	//	return PFX_STATUS_INVALID_PARAMS;
	//}

	static PFX_INLINE pfx_result_t active_texture_params (render_device_t device, const texture_param_t* PARAM_INOUT texture_params,pfx_usize_t params_count)
	{
		return PFX_STATUS_DENIED;
	}
	static PFX_INLINE pfx_result_t active_texture_unit (render_device_t device, pfx_uindex_t unit_index)
	{
		return PFX_STATUS_DENIED;
	}
};


template < typename  texture_type >
struct PFX_TextureLayer
{
	typedef typename texture_type::render_device_t		render_device_t;
	typedef typename texture_type::texture_layer_t		texture_layer_t;
	typedef typename texture_type::extern_params_t		extern_params_t;

	static PFX_INLINE texture_type* create_texture (render_device_t render_device)
	{
		return null;
	}
	static PFX_INLINE pfx_result_t release_texture (texture_type* PARAM_INOUT texture_ptr)
	{
		return PFX_STATUS_DENIED;
	}

	static PFX_INLINE texture_layer_t* create_texture_layer (texture_type* PARAM_INOUT texture_ptr,
		pfx_usize_t nMipLevel,const texture_bits_t* PARAM_IN texture_bits_,const extern_params_t* PARAM_IN  extern_params_)
	{
		return null;
	}
	static PFX_INLINE pfx_result_t release_texture_layer (texture_layer_t* PARAM_INOUT texture_ptr)
	{
		return null;
	}
};

//template < typename  texture_type >
//struct PFX_TextureCUBE
//{
//	typedef typename texture_type::render_device_t		render_device_t;
//	typedef typename texture_type::extern_params_t		extern_params_t;
//	typedef typename texture_type::texture_layer_t		texture_layer_t;
//
//	//typedef typename texture_type::texture_positve_x_layer_t		texture_positve_x_layer_t;
//	//typedef typename texture_type::texture_positve_y_layer_t		texture_positve_y_layer_t;
//	//typedef typename texture_type::texture_positve_z_layer_t		texture_positve_z_layer_t;
//
//	//typedef typename texture_type::texture_negative_x_layer_t	texture_negative_x_layer_t;
//	//typedef typename texture_type::texture_negative_y_layer_t	texture_negative_y_layer_t;
//	//typedef typename texture_type::texture_negative_z_layer_t	texture_negative_z_layer_t;
//
//	static PFX_INLINE texture_type* create_texture (render_device_t render_device)
//	{
//		return null;
//	}
//	static PFX_INLINE pfx_result_t release_texture (texture_type* PARAM_INOUT texture_ptr)
//	{
//		return null;
//	}
//
//	static PFX_INLINE texture_layer_t* create_texture_positve_x_layer (texture_type* PARAM_INOUT texture_ptr,
//		pfx_usize_t nMipLevel,const texture_bits_t* PARAM_IN texture_bits_,const extern_params_t* PARAM_IN extern_params_)
//	{
//		return null;
//	}
//	static PFX_INLINE texture_layer_t* create_texture_positve_y_layer (texture_type* PARAM_INOUT texture_ptr,
//		pfx_usize_t nMipLevel,const texture_bits_t* PARAM_IN texture_bits_,const extern_params_t* PARAM_IN  extern_params_)
//	{
//		return null;
//	}
//	static PFX_INLINE texture_layer_t* create_texture_positve_z_layer (texture_type* PARAM_INOUT texture_ptr,
//		pfx_usize_t nMipLevel,const texture_bits_t* PARAM_IN texture_bits_,const extern_params_t* PARAM_IN  extern_params_)
//	{
//		return null;
//	}
//	static PFX_INLINE texture_layer_t* create_texture_negative_x_layer (texture_type* PARAM_INOUT texture_ptr,
//		pfx_usize_t nMipLevel,const texture_bits_t* PARAM_IN texture_bits_,const extern_params_t* PARAM_IN  extern_params_)
//	{
//		return null;
//	}
//	static PFX_INLINE texture_layer_t* create_texture_negative_y_layer (texture_type* PARAM_INOUT texture_ptr,
//		pfx_usize_t nMipLevel,const texture_bits_t* PARAM_IN texture_bits_,const extern_params_t* PARAM_IN  extern_params_)
//	{
//		return null;
//	}
//	static PFX_INLINE texture_layer_t* create_texture_negative_z_layer (texture_type* PARAM_INOUT texture_ptr,
//		pfx_usize_t nMipLevel,const texture_bits_t* PARAM_IN texture_bits_,const extern_params_t* PARAM_IN xtern_params_)
//	{
//		return null;
//	}
//
//	static PFX_INLINE pfx_result_t release_texture_layer (texture_layer_t* PARAM_INOUT texture_ptr)
//	{
//		return null;
//	}
//};

//template < const pfx_enum_int_t TEXTURE_TYPE >
//struct PFX_Texture
//{
//	typedef pfx_ulong_t Texture_t;
//};

PECKER_END

#endif			//PFX_TEXTURE_H_
