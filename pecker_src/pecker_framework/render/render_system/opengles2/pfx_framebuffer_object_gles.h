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

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#pragma warning(disable:4275)
#endif

PFX_RENDER_SYSTEM_API GLenum PFX_FMT_TO_GLRB_FMT(enum_int_t usage_type, enum_int_t PFX_FMT);
PFX_FORCE_INLINE GLenum PFX_RBF_TO_GL_RBF(enum_int_t fmt, uindex_t level = 0)
{
	GLenum val = -1;
	switch (fmt)
	{
	case PFX_COLOR_BUFFER_FMT:
		val = GL_COLOR_ATTACHMENT0 + level;
		break;
	case PFX_DEPTH_BUFFER_FMT:
		val = GL_DEPTH_ATTACHMENT + level;
		break;
	case PFX_STENCIL_BUFFER_FMT:
		val = GL_STENCIL_ATTACHMENT + level;
		break;
	default:
		break;
	}
	return val;
}
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
		return dispose_object();
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
	PFX_INLINE enum_int_t get_target_type() const
	{
		return PFX_RENDER_BUFFER_TAG;
	}

	PFX_INLINE usize__t width() const
	{
		return m_native.width();
	}
	PFX_INLINE usize__t height() const
	{
		return m_native.height();
	}

	PFX_INLINE rect_size_t* get_size(rect_size_t& PARAM_OUT __size,
		uindex_t level = 0) const
	{
		__size.m_height = m_native.height();
		__size.m_width = m_native.width();
		return &__size;
	}
};


//////////////////////////////////////////////////////////////////////////
//
class PFX_RENDER_SYSTEM_API cnative_framebuffer_gles2
{
protected:
	typedef struct st_FBO_rendertag
	{
		IPfx_rendertarget* m_color_buffer_ptr;
		IPfx_rendertarget* m_depth_buffer_ptr;
		IPfx_rendertarget* m_stencil_buffer_ptr;
	}__FBO_TAG_t;

	typedef struct st_FBO_buftag
	{
		IPfx_renderbuffer* m_color_buffer_ptr;
		IPfx_renderbuffer* m_depth_buffer_ptr;
		IPfx_renderbuffer* m_stencil_buffer_ptr;
	}__FBO_buf_TAG_t;

	typedef struct st_FBO_textag
	{
		IPfx_texture* m_color_buffer_ptr;
		IPfx_texture* m_depth_buffer_ptr;
		IPfx_renderbuffer* m_stencil_buffer_ptr;
	}__FBO_tex_TAG_t;

	typedef union un_FBO_rendertag
	{
		__FBO_TAG_t        m_tags;
		__FBO_buf_TAG_t    m_buf_tags;
		__FBO_tex_TAG_t    m_tex_tags;
		IPfx_rendertarget* m_render_target_ptr[3];
		IPfx_renderbuffer* m_render_buffer_ptr[3];
		IPfx_texture*      m_render_texture_ptr[3];
	}FBO_TAG_t;
	//typedef struct st_RBO_size_info
	//{
	//	rect_size_t m_size;
	//	uindex_t    m_level;

	//	st_RBO_size_info() :m_level(0){ ; }
	//}RBO_SZ_t;
private:
	GLuint      m_framebufferID;
	GLenum      m_fbo_complete_status;
	FBO_TAG_t   m_fbo_tag;
	//RBO_SZ_t    m_RBO_sz[3];
	enum_int_t  m_surface_type[3];
	uindex_t    m_mip_level[3];
	usize__t    m_width;
	usize__t    m_height;
public:
	cnative_framebuffer_gles2();
	virtual ~cnative_framebuffer_gles2();

	result_t attach_renderbuffer(
		IPfx_renderbuffer* PARAM_IN render_buffer,
		uindex_t attachment_index = 0
		);
	result_t attach_texture(
		enum_int_t usage_type, //  PFX_RENDER_BUFFER_FMT_t
		IPfx_texture* PARAM_IN texture2D_ptr,
		uindex_t attachment_index = 0,
		uindex_t mip_level = 0,
		enum_int_t surface_type = PFX_TEXTURE_DEFUALT_SURFACE);

	result_t complete_attachment();
	result_t create_rendertarget(
		usize__t width = 0, usize__t height = 0,
		enum_int_t color_format = PFX_RGBA8_FMT,
		enum_int_t depth_format = PFX_DEPTH_COMPONENT16_FMT,
		enum_int_t stencil_format = PFX_STENCIL_INDEX8_FMT
		);
	result_t dispose();
	result_t dispose_render_target();
	result_t bind();
	result_t bind_framebuffer();
	result_t update_default();

	PFX_INLINE bool     check_status() const
	{
		return 	(m_framebufferID && 
			GL_FRAMEBUFFER_COMPLETE == m_fbo_complete_status);
	}

	PFX_INLINE GLenum get_last_complete_status() const
	{
		return m_fbo_complete_status;
	}

	PFX_INLINE IPfx_texture* get_texture(enum_int_t usage_type, 
		uindex_t attachment_index)
	{
		if (attachment_index > 0 || usage_type >= PFX_STENCIL_BUFFER_FMT)
		{
			return null;
		}
		else
		{
			IPfx_rendertarget* tag_ptr = m_fbo_tag.m_render_target_ptr[usage_type];
			if (tag_ptr && PFX_TEXTURE_TAG == tag_ptr->get_target_type() && tag_ptr->share())
			{
				return m_fbo_tag.m_render_texture_ptr[usage_type];;
			}
			else
			{
				return null;
			}
		}
		
	}

	PFX_INLINE GLuint   get_framebufferID() const
	{
		return m_framebufferID;
	}
	PFX_INLINE long_t   get_native_handle() const
	{
		return (long_t)m_framebufferID;
	}

	PFX_INLINE usize__t get_width() const
	{
		return m_width;
	}

	PFX_INLINE usize__t get_height() const
	{
		return m_height;
	}

	PFX_INLINE IPfx_renderbuffer* get_renderbuffer(enum_int_t usage_type, uindex_t attachment_index)
	{
		if (usage_type < 3 && usage_type >= 0)
		{
			if (m_fbo_tag.m_render_target_ptr[usage_type]->share())
			{
				return m_fbo_tag.m_render_buffer_ptr[usage_type];
			}
			else
			{
				return null;
			}
		}
		else
		{
			return null;
		}
	}

	static PFX_INLINE u64_t    get_version() 
	{
		return (get_hal_instanse_ID_gles2().m_version);
	}
};

class PFX_RENDER_SYSTEM_API  cframebuffer_gles2 : public IPfx_framebuffer
{

	typedef cnative_framebuffer_gles2 native_t;
	DECLARE_FRIEND_CLASS(FRAMEBUFFER_ALLOC_GLES2);
private:
	native_t m_native;
public:
	DELARE_REF_METHOD(cframebuffer_gles2, IPfx_framebuffer, cframebuffer_alloc_gles2_t);
protected:
	cframebuffer_gles2()
	{
		RFBO_LOG_INFO("create...0x%08X", (lpointer_t)this);
	}
	virtual ~cframebuffer_gles2()
	{
		RFBO_LOG_INFO("release...0x%08X", (lpointer_t)this);
	}
	virtual PFX_INLINE result_t real_dispose()
	{
		return __real_dispose();
	}

public:

	PFX_INLINE result_t attach_renderbuffer(
		IPfx_renderbuffer* PARAM_IN render_buffer,
		uindex_t attachment_index = 0
		) 
	{
		return m_native.attach_renderbuffer(render_buffer,attachment_index);
	}
	PFX_INLINE result_t attach_texture(
		enum_int_t usage_type, //  PFX_RENDER_BUFFER_FMT_t
		IPfx_texture* PARAM_IN texture2D_ptr, 
		uindex_t attachment_index = 0,
		uindex_t mip_level = 0,
		enum_int_t surface_type = PFX_TEXTURE_DEFUALT_SURFACE)
	{
		return m_native.attach_texture(usage_type,texture2D_ptr,
			attachment_index,mip_level,surface_type);
	}
	PFX_INLINE result_t complete_attachment()
	{
		return m_native.complete_attachment();
	}
	PFX_INLINE bool     check_status() const
	{
		return m_native.check_status();
	}

	PFX_INLINE result_t create_rendertarget(
		usize__t width = 0, usize__t height = 0,
		enum_int_t color_format = PFX_RGBA8_FMT,
		enum_int_t depth_format = PFX_DEPTH_COMPONENT16_FMT,
		enum_int_t stencil_format = -1
		)
	{
		return m_native.create_rendertarget(width,height,
			color_format,depth_format,stencil_format);
	}

	PFX_INLINE result_t dispose_framebuffer()
	{
		return dispose_object();
	}
	PFX_INLINE result_t dispose_render_target()
	{
		return m_native.dispose_render_target();
	}

	PFX_INLINE IPfx_texture* get_texture(enum_int_t usage_type, uindex_t attachment_index)
	{
		return m_native.get_texture(usage_type, attachment_index);
	}

	PFX_INLINE result_t bind_framebuffer()
	{
		return m_native.bind_framebuffer();
	}

	PFX_INLINE long_t   get_native_handle() const
	{
		return m_native.get_native_handle();
	}
	PFX_INLINE u64_t    get_version() const
	{
		return native_t::get_version();
	}


	PFX_INLINE result_t update_default()
	{
		return m_native.update_default();
	}
	PFX_INLINE result_t bind()
	{
		return m_native.bind();
	}

	PFX_INLINE rect_size_t* get_size(rect_size_t& PARAM_OUT __size,
		uindex_t level = 0) const
	{
		__size.m_height = m_native.get_height();
		__size.m_width = m_native.get_width();
		if (__size.m_width && __size.m_height)
		{
			return &__size;
		}
		else
		{
			return null;
		}
		
	}

	PFX_INLINE enum_int_t get_target_type() const
	{
		return PFX_FRAME_BUFFER_TAG;
	}


};


#ifdef _MSC_VER
#pragma warning(pop)
#endif

PECKER_END

#endif			//PFX_FRAMEBUFFER_OBJECT_GLES_H_
