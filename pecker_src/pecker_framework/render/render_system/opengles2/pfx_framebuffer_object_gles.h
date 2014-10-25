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

//////////////////////////////////////////////////////////////////////////
class PFX_RENDER_SYSTEM_API cnative_renderbuffer_gles2
{
private:
	GLuint     m_renderbufferID;
	enum_int_t m_usage_type;
	enum_int_t m_internalformat;
	usize__t   m_width;
	usize__t   m_height;
public:
	cnative_renderbuffer_gles2();
	virtual ~cnative_renderbuffer_gles2();
	result_t create_rendertarget(enum_int_t usage_type, //  PFX_RENDER_BUFFER_FMT_t
		enum_int_t format,
		usize__t width, usize__t height);
	result_t update_default();
	result_t bind();
	result_t dispose();
	result_t dispose_render_target();
	PFX_INLINE usize__t width() const
	{
		return m_width;
	}
	PFX_INLINE usize__t height() const
	{
		return m_height;
	}
	PFX_INLINE enum_int_t get_usage_type() const
	{
		return m_usage_type;
	}
	PFX_INLINE enum_int_t get_internal_format() const
	{
		return m_internalformat;
	}


	PFX_INLINE long_t   get_native_handle() const
	{
		return (long_t)(m_renderbufferID);
	}

	PFX_INLINE GLuint get_bufferID() const
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

//////////////////////////////////////////////////////////////////////////


class PFX_RENDER_SYSTEM_API crenderbuffer_gles2 : public IPfx_renderbuffer
{
	typedef cnative_renderbuffer_gles2 native_t;
	DECLARE_FRIEND_CLASS(RENDERBUFFER_ALLOC_GLES2);
private:
	native_t m_native;
public:
	DELARE_REF_METHOD(crenderbuffer_gles2, IPfx_renderbuffer, crenderbuffer_alloc_gles2_t);
protected:
	crenderbuffer_gles2()
	{
		RFBO_LOG_INFO("create...0x%08X", (lpointer_t)this);
	}
	virtual ~crenderbuffer_gles2()
	{ 
		RFBO_LOG_INFO("release...0x%08X", (lpointer_t)this);
	}
	virtual PFX_INLINE result_t real_dispose()
	{
		return __real_dispose();
	}
public:
	
	PFX_INLINE result_t create_rendertarget(enum_int_t usage_type, //  PFX_RENDER_BUFFER_FMT_t
		enum_int_t format,
		usize__t width, usize__t height)
	{
		return m_native.create_rendertarget(usage_type, format, width, height);
	}
	PFX_INLINE bool     check_status() const
	{
		return m_native.check_status();
	}
	PFX_INLINE result_t update_default()
	{
		return m_native.update_default();
	}

	PFX_INLINE result_t bind_renderbuffer()
	{
		return m_native.bind();
	}

	PFX_INLINE result_t bind()
	{
		if (m_native.check_status())
		{
			return m_native.bind();
		}
		else
		{
			return m_native.update_default();
		}
	}

	PFX_INLINE enum_int_t get_usage_type() const
	{
		return m_native.get_usage_type();
	}
	PFX_INLINE enum_int_t get_format() const
	{
		return m_native.get_internal_format();
	}

	PFX_INLINE result_t dispose_renderbuffer()
	{
		return m_native.dispose();
	}
	PFX_INLINE result_t dispose_render_target()
	{
		return m_native.dispose_render_target();
	}

	PFX_INLINE long_t   get_native_handle() const
	{
		return m_native.get_native_handle();
	}
	PFX_INLINE GLuint get_bufferID() const
	{
		return m_native.get_bufferID();
	}
	PFX_INLINE u64_t    get_version() const
	{
		return native_t::get_version();
	}
};


//////////////////////////////////////////////////////////////////////////
//
class PFX_RENDER_SYSTEM_API cnative_framebuffer_gles2
{

};

class PFX_RENDER_SYSTEM_API  cframebuffer_gles2 : public IPfx_framebuffer
{
public:
	virtual ~cframebuffer_gles2(){ ; }

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

	PFX_INLINE result_t create_rendertarget(
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
