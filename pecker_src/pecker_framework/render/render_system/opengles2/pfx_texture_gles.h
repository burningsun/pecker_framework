/*
 * pfx_texture_gles.h
 *
 *  Created on: 2014-7-27
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_TEXTURE_GLES_H_
#define		PFX_TEXTURE_GLES_H_

#include <GLES2/gl2.h>
#include "../../pfx_image.h"
#include "../pfx_texture.h"
#include "../../../pfx_hal_info_gles2.h"
#include "pfx_render_allocator_gles.h"

#define  RTEX_DEBUG

PECKER_BEGIN

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif

#ifdef RTEX_DEBUG
#define RTEX_LOG_STR  PECKER_LOG_STR
#define RTEX_LOG_INFO PECKER_LOG_INFO
#define RTEX_LOG_ERR  PECKER_LOG_ERR
#else
#define RTEX_LOG_STR(...)
#define RTEX_LOG_INFO(...)
#define RTEX_LOG_ERR(...)
#endif


class PFX_RENDER_SYSTEM_API cnative_texture2D_gles
{
private:
	GLuint            m_textureID;
	ctexture_surface* m_surface_ptr;
	GLint             m_color_format;
	bool              m_bupdate;
	usize__t          m_render_width;
	usize__t          m_render_height;
	
public:
	cnative_texture2D_gles();
	virtual ~cnative_texture2D_gles();
public:
	result_t   create_rendertarget(usize__t width, usize__t height, enum_int_t internal_color_format);
	result_t   update_surface(ctexture_surface* PARAM_IN surface_ptr = null);

	result_t   update_rect(const texture_rect_t& __rect,
		const byte_t* buffer_ptr,
		usize__t bytes_count,
		uindex_t miplevel = 0);

	void bind();

	void dispose();

	void set_texture_filter(enum_int_t param_name, enum_int_t __param);

	void dispose_render_target();
	
	

	PFX_INLINE long_t   get_native_handle() const
	{
		return (long_t)(m_textureID);
	}

	PFX_INLINE GLuint get_textureID() const
	{
		return m_textureID;
	}

	PFX_INLINE ctexture_surface* get_surface()
	{
		if (m_surface_ptr)
		{
			return m_surface_ptr->new_ref();
		}
		else
		{
			return null;
		}
		
	}

	PFX_INLINE bool check_status() const
	{
		return ((0 != m_textureID) && ((m_surface_ptr)||(m_render_height && m_render_width)));
	}

	static PFX_INLINE u64_t get_version()
	{
		return (get_hal_instanse_ID_gles2().m_version);
	}
};

class PFX_RENDER_SYSTEM_API ctexture2D_gles : public IPfx_texture
{
	typedef   cnative_texture2D_gles native_t;
	DECLARE_FRIEND_CLASS(TEXTURE_2D_NODE_ALLOC_GLES2);
private:
	native_t m_native;
public:
	DELARE_REF_METHOD(ctexture2D_gles, IPfx_texture, ctexture2D_gles_allocator_t);
protected:
	ctexture2D_gles()
	{
		RTEX_LOG_INFO("create...0x%08X", (lpointer_t)this);
	}
	virtual ~ctexture2D_gles()
	{
		RTEX_LOG_INFO("release...0x%08X", (lpointer_t)this);
	}
	virtual PFX_INLINE result_t real_dispose()
	{
		return __real_dispose();
	}
public:
	PFX_INLINE result_t create_rendertarget(usize__t width, usize__t height, enum_int_t color_format)
	{
		return m_native.create_rendertarget(width, height, color_format);
	}

	PFX_INLINE result_t   update_surface(ctexture_surface* PARAM_IN surface_ptr = null,
		enum_int_t surface_type = PFX_TEXTURE_DEFUALT_SURFACE)
	{
		RETURN_INVALID_RESULT(PFX_TEXTURE_2D_SURFACE != surface_type &&
			PFX_TEXTURE_DEFUALT_SURFACE != surface_type, PFX_STATUS_INVALID_PARAMS);
		return m_native.update_surface(surface_ptr);
	}

	PFX_INLINE result_t   update_rect(const texture_rect_t& __rect,
		const byte_t* buffer_ptr,
		usize__t bytes_count,
		enum_int_t surface_type = PFX_TEXTURE_DEFUALT_SURFACE,//PFX_TEXTURE_SURFACE_TYPE_t
		uindex_t miplevel = 0)
	{
		RETURN_INVALID_RESULT(PFX_TEXTURE_2D_SURFACE != surface_type &&
			PFX_TEXTURE_DEFUALT_SURFACE != surface_type, PFX_STATUS_INVALID_PARAMS);
		return m_native.update_rect(__rect, buffer_ptr, bytes_count, miplevel);
	}

	PFX_INLINE bool     check_status() const
	{
		return m_native.check_status();
	}

	PFX_INLINE result_t dispose_texture()
	{
		return dispose_object();
	}

	PFX_INLINE result_t dispose_render_target()
	{
		m_native.dispose_render_target();
		return PFX_STATUS_OK;
	}

	PFX_INLINE ctexture_surface* get_surface(enum_int_t surface_type = PFX_TEXTURE_DEFUALT_SURFACE)
	{
		RETURN_INVALID_RESULT(PFX_TEXTURE_2D_SURFACE != surface_type &&
			PFX_TEXTURE_DEFUALT_SURFACE != surface_type, null);
		return m_native.get_surface();
	}

	PFX_INLINE result_t set_texture_filter(enum_int_t param_name, enum_int_t __param)
	{
		m_native.set_texture_filter(param_name, __param);
		return PFX_STATUS_OK;
	}

	PFX_INLINE result_t bind_texture()
	{
		m_native.bind();
		return PFX_STATUS_OK;
	}
	PFX_INLINE long_t   get_native_handle() const
	{
		return m_native.get_native_handle();
	}
	PFX_INLINE u64_t    get_version() const
	{
		return native_t::get_version();
	}

};

class PFX_RENDER_SYSTEM_API ctextureCube_gles : public IPfx_texture
{

};


#ifdef _MSC_VER
#pragma warning(pop)
#endif

PECKER_END

#endif			//PFX_TEXTURE_GLES_H_
