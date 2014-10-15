/*
 * pfx_framebuffer_object_gles.h
 *
 *  Created on: 2014-10-15
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_FRAMEBUFFER_OBJECT_GLES_H_
#define		PFX_FRAMEBUFFER_OBJECT_GLES_H_

#include <GLES2/gl2.h>

#include "../../../pfx_hal_info_gles2.h"
#include "../../../Include/native"
#include "pfx_render_allocator_gles.h"
#include "../pfx_framebuffer_object.h"
#include "../../pfx_color.h"

#define RFBO_DEBUG

#undef  RFBO_LOG_STR
#undef  RFBO_LOG_INFO
#ifdef  RFBO_DEBUG

#define RFBO_LOG_STR PECKER_LOG_STR
#define RFBO_LOG_INFO PECKER_LOG_INFO
#else
#define RFBO_LOG_STR(...)
#define RFBO_LOG_INFO(...)
#endif

PECKER_BEGIN

PFX_RENDER_SYSTEM_API GLenum PFX_FMT_TO_GLRB_FMT(enum_int_t usage_type, enum_int_t PFX_FMT);

class PFX_RENDER_SYSTEM_API cnative_renderbuffer_gles
{
private:
	GLuint     m_renderbufferID;
	enum_int_t m_usage_type;
	enum_int_t m_internalformat;
	usize__t   m_width;
	usize__t   m_height;
public:
	cnative_renderbuffer_gles();
	virtual ~cnative_renderbuffer_gles();
	result_t store_renderbuffer(enum_int_t usage_type, //  PFX_RENDER_BUFFER_FMT_t
		enum_int_t format,
		usize__t width, usize__t height);
	result_t bind();
	result_t dispose();
	result_t dispose_render_target();

	PFX_INLINE long_t   get_native_handle() const
	{
		return (long_t)(m_renderbufferID);
	}

	PFX_INLINE GLuint get_textureID() const
	{
		return m_renderbufferID;
	}
	PFX_INLINE bool check_status() const
	{
		return (0 != m_renderbufferID);
	}

	static PFX_INLINE u64_t get_version()
	{
		return (get_hal_instanse_ID_gles2().m_version);
	}
};


class PFX_RENDER_SYSTEM_API crenderbuffer_gles : public IPfx_renderbuffer
{
public:
	virtual ~crenderbuffer_gles(){ ; }
	PFX_INLINE result_t store_renderbuffer(enum_int_t usage_type, //  PFX_RENDER_BUFFER_FMT_t
		enum_int_t format,
		usize__t width, usize__t height)
	{
		return PFX_STATUS_OK;
	}
	PFX_INLINE bool     check_status() const
	{
		return false;
	}
	PFX_INLINE enum_int_t get_usage_type() const
	{
		return PFX_DEPTH_BUFFER_FMT;
	}
	PFX_INLINE enum_int_t get_format() const
	{
		return PFX_DEPTH_COMPONENT16_FMT;
	}

	PFX_INLINE result_t dispose_renderbuffer()
	{
		return PFX_STATUS_OK;
	}
	PFX_INLINE result_t dispose_render_target()
	{
		return PFX_STATUS_OK;
	}

	PFX_INLINE long_t   get_native_handle() const
	{
		return 0;
	}
	PFX_INLINE u64_t    get_version() const
	{
		return 0;
	}
};

class PFX_RENDER_SYSTEM_API  cframebuffer_gles : public IPfx_framebuffer
{
public:
	virtual ~cframebuffer_gles(){ ; }

	PFX_INLINE result_t attach_renderbuffer(
		IPfx_renderbuffer* PARAM_IN render_buffer,
		uindex_t attachment_index = 0
		) 
	{
		return PFX_STATUS_OK;
	}
	PFX_INLINE result_t attach_texture(
		enum_int_t usage_type, //  PFX_RENDER_BUFFER_FMT_t
		IPfx_texture* PARAM_IN texture2D_ptr, 
		uindex_t attachment_index = 0,
		uindex_t mip_level = 0,
		enum_int_t surface_type = PFX_TEXTURE_DEFUALT_SURFACE)
	{
		return PFX_STATUS_OK;
	}

	PFX_INLINE bool     check_status() const
	{
		return false;
	}

	PFX_INLINE result_t create_render_target(
		usize__t width = 0, usize__t height = 0,
		enum_int_t color_format = PFX_TEXTURE_2D,
		enum_int_t depth_format = PFX_DEPTH_COMPONENT16_FMT,
		enum_int_t stencil_format = PFX_STENCIL_INDEX8_FMT
		)
	{
		return PFX_STATUS_OK;
	}

	PFX_INLINE result_t dispose_framebuffer()
	{
		return PFX_STATUS_OK;
	}
	PFX_INLINE result_t dispose_render_target()
	{
		return PFX_STATUS_OK;
	}

	PFX_INLINE IPfx_texture* get_texture(uindex_t attachment_index)
	{
		return null;
	}

	PFX_INLINE result_t bind_framebuffer()
	{
		return PFX_STATUS_OK;
	}

	PFX_INLINE long_t   get_native_handle() const
	{
		return 0;
	}
	PFX_INLINE u64_t    get_version() const
	{
		return 0;
	}
};




PECKER_END

#endif			//PFX_FRAMEBUFFER_OBJECT_GLES_H_
