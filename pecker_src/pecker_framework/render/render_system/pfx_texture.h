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
#include "../../include/cshare_object.h"
#include "../pfx_render_allocator.h"
#include "pfx_render_target.h"

PECKER_BEGIN

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#pragma warning(disable:4275)
#endif
	
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


typedef struct st_mip_image
{
	sImage_t*  m_image_ptr;
	enum_int_t m_rcolor_type;
	st_mip_image() :m_image_ptr(null),
		m_rcolor_type(PFX_RGBA8_FMT)
	{
		;
	}
	~st_mip_image()
	{
		if (m_image_ptr)
		{
			m_image_ptr->dispose_object();
			m_image_ptr = null;
		}
		m_rcolor_type = PFX_RGBA8_FMT;
	}

}mip_image_t;

//typedef struct texture_param
//{
//	enum_int_t	m_name;
//	enum_int_t	m_param_value;
//}texture_param_t;
			
class PFX_RENDER_API ctexture_surface : 
	public creference_root
{
	DECLARE_FRIEND_CLASS(TEXTURE_SURFACE_ALLOC);
protected:
	typedef  carray < mip_image_allocator_t > mip_images_t;
private:
	mip_images_t m_mip_images;	
protected:
	ctexture_surface();
	virtual ~ctexture_surface();
	virtual result_t real_dispose()
	{
		return __real_dispose();
	}
public:
	__DELARE_REF_METHOD(ctexture_surface, texture_surface_allocator_t);

	 result_t      update_image(sImage_t* image_ptr,
	                   enum_int_t render_color_type,
	                    uindex_t mip_level = 0);

	 result_t      update_image_with_copy(sImage_t* image_ptr,
	                   enum_int_t render_color_type,
	                    uindex_t mip_level = 0);


	 result_t      auto_mipmap(usize__t max_mip_level);

	 result_t      clean();

	 PFX_INLINE usize__t get_max_miplevel() const
	 {
		 return m_mip_images.size();
	 }
	 PFX_INLINE mip_image_t*  get_image(uindex_t mip_level)
	 {
		 return m_mip_images.get_element_ptr_at(mip_level);
	 }
};

PFX_Interface IPfx_texture : public IPfx_rendertarget
{
	virtual ~IPfx_texture(){ ; }
	
	virtual result_t   create_rendertarget(usize__t width, usize__t height, enum_int_t color_format) = 0;
	virtual result_t   update_surface(ctexture_surface* PARAM_IN surface_ptr = null, 
		                               enum_int_t surface_type = PFX_TEXTURE_DEFUALT_SURFACE,
									   bool bforce_update = false) = 0;


	virtual result_t   update_rect(const texture_rect_t& __rect,
		                           const byte_t* buffer_ptr,
		                           usize__t bytes_count,
								   enum_int_t surface_type = PFX_TEXTURE_DEFUALT_SURFACE,//PFX_TEXTURE_SURFACE_TYPE_t
		                           uindex_t miplevel = 0) = 0;

	virtual bool     check_status() const = 0;

	virtual result_t dispose_texture() = 0;

	virtual result_t dispose_render_target() = 0;
											  
	virtual ctexture_surface* get_surface(enum_int_t surface_type = PFX_TEXTURE_DEFUALT_SURFACE) = 0;

	virtual result_t set_texture_filter(enum_int_t param_name, enum_int_t __param) = 0;
	virtual result_t set_texture_filter(enum_int_t param_name, const enum_int_t* __param_ptr) = 0;

	virtual result_t bind_texture() = 0;
	virtual long_t   get_native_handle() const = 0;
	virtual u64_t    get_version() const = 0;

	virtual IPfx_texture* new_share() = 0;
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif
PECKER_END

#endif			//PFX_TEXTURE_H_
