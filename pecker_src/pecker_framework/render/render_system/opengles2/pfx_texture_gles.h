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
#pragma warning(disable:4275)
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

PFX_INLINE GLenum PFX_TEXSUR_2_GL_TEXSUR(PFX_TEXTURE_SURFACE_TYPE_t surtype)
{
	static GLenum texture_surface_type[PFX_TEXTURE_SURFACE_TYPE_COUNT + 1] =
	{
		GL_TEXTURE_2D,
		GL_TEXTURE_2D,
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
		GL_TEXTURE_2D
	};
	return texture_surface_type[surtype];
}
PFX_INLINE GLenum PFX_TEXFILTER_NAME_2_GLTEXFILTER_NAME(PFX_TEXTURE_PARAMS_NAME_t filtername)
{
	static GLenum filter[PFX_TEXTURE_PARAMS_NAME_COUNT + 1] =
	{
		GL_TEXTURE_MAG_FILTER,
		GL_TEXTURE_MIN_FILTER,
		GL_TEXTURE_WRAP_S,
		GL_TEXTURE_WRAP_T,
		GL_TEXTURE_MAG_FILTER
	};
	return filter[filtername];
}

PFX_INLINE GLenum PFX_TEXFILTER_PARAM_2_GLTEXFILTER_PARAM(PFX_TEXTURE_PARAMS_t filter_param)
{
	static GLenum filter[PFX_TEXTURE_PARAMS_COUNT + 1] =
	{
		GL_NEAREST,
		GL_LINEAR,
		GL_NEAREST_MIPMAP_NEAREST,
		GL_NEAREST_MIPMAP_LINEAR,
		GL_LINEAR_MIPMAP_NEAREST,
		GL_LINEAR_MIPMAP_LINEAR,
		GL_REPEAT,
		GL_CLAMP_TO_EDGE,
		GL_MIRRORED_REPEAT,
		GL_NEAREST
	};
	return filter[filter_param];
}

PFX_INLINE usize__t PFX_TEXFILTER_PARAM_COUNT(PFX_TEXTURE_PARAMS_NAME_t filtername)
{
	static usize__t param_count[PFX_TEXTURE_PARAMS_NAME_COUNT + 1] =
	{
		1,
		1,
		1,
		1,
		0
	};
	return param_count[filtername];
}

PFX_INLINE bool CHECK_PFX_TEX_PARAM_OK_GLES2(PFX_TEXTURE_PARAMS_NAME_t filtername,
	PFX_TEXTURE_PARAMS_t filter_param)
{
	return ((PFX_TRN_MAG_FILTER == filtername && filter_param <= PFX_TP_LINEAR) ||
		(PFX_TRN_MIN_FILTER == filtername &&
		(
		(filter_param >= PFX_TP_NEAREST_MIPMAP_NEAREST &&
		filter_param <= PFX_TP_LINEAR_MIPMAP_LINEAR) || (filter_param <= PFX_TP_LINEAR)
		)) ||
		((PFX_TRN_WRAP_S == filtername || PFX_TRN_WRAP_T == filtername)&&
		(PFX_TP_REPEAT <= filter_param && filter_param <= PFX_TP_MIRRORED_REPEAT))
		);
}


class PFX_RENDER_SYSTEM_API cnative_texture2D_gles2
{
public:
	static const usize__t MAX_TEXFILTER_PARAM_BUFFER_SIZE = 32;
private:
	GLuint                      m_textureID;
	GLenum                      m_gl_tex_surface_type;
	PFX_TEXTURE_SURFACE_TYPE_t  m_tex_surface_type;
	ctexture_surface*           m_surface_ptr;
	GLint                       m_color_format;
	bool                        m_bupdate;
	usize__t                    m_render_width;
	usize__t                    m_render_height;

	usize__t                    m_texfilter_param_bufsize;
	enum_int_t                  m_texfilter_param_buf[MAX_TEXFILTER_PARAM_BUFFER_SIZE];
	index_t                     m_texfilers[PFX_TEXTURE_PARAMS_NAME_COUNT];

	
public:
	cnative_texture2D_gles2();
	virtual ~cnative_texture2D_gles2();
public: 
	result_t   create_rendertarget();
	result_t   create_rendertarget(PFX_TEXTURE_SURFACE_TYPE_t sur_type, 
		usize__t width, usize__t height, enum_int_t internal_color_format);
	result_t   update_surface(ctexture_surface* PARAM_IN surface_ptr = null);

	result_t   update_rect(const texture_rect_t& __rect,
		const byte_t* buffer_ptr,
		usize__t bytes_count,
		uindex_t miplevel = 0);

	void bind();

	void dispose();

	result_t set_texture_filter(enum_int_t param_name, enum_int_t __param);
	result_t set_texture_filter(enum_int_t param_name, const enum_int_t* __param_ptr);

	result_t reset_texture_filter();

	void dispose_render_target();
	
	PFX_INLINE usize__t width() const
	{
		return m_render_width;
	}
	PFX_INLINE usize__t height() const
	{
		return m_render_width;
	}

	PFX_INLINE rect_size_t* get_size(rect_size_t& PARAM_OUT __size,
		uindex_t level = 0) const
	{
		if (m_surface_ptr)
		{
			mip_image_t* mip_ptr = m_surface_ptr->get_image(level);
			if (mip_ptr && mip_ptr->m_image_ptr)
			{
				__size.m_width = mip_ptr->m_image_ptr->native().get_image_direct().m_img.m_width;
				__size.m_height = mip_ptr->m_image_ptr->native().get_image_direct().m_img.m_height;
				return &__size;
			}
		}

		__size.m_width = m_render_width;
		__size.m_height = m_render_height;
		return &__size;
	}

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

	PFX_INLINE enum_int_t get_surface_type() const
	{
		return m_tex_surface_type;
	}
};

class PFX_RENDER_SYSTEM_API ctexture2D_gles2 : public IPfx_texture
{
	typedef   cnative_texture2D_gles2 native_t;
	DECLARE_FRIEND_CLASS(TEXTURE_2D_NODE_ALLOC_GLES2);
private:
	native_t m_native;
public:
	DELARE_REF_METHOD(ctexture2D_gles2, IPfx_texture, ctexture2D_gles_allocator_t);
protected:
	ctexture2D_gles2()
	{
		RTEX_LOG_INFO("create...0x%08X", (lpointer_t)this);
	}
	virtual ~ctexture2D_gles2()
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
		return m_native.create_rendertarget(PFX_TEXTURE_2D_SURFACE, width, height, color_format);
	}

	PFX_INLINE result_t   update_surface(ctexture_surface* PARAM_IN surface_ptr = null,
		enum_int_t surface_type = PFX_TEXTURE_DEFUALT_SURFACE)
	{
		RETURN_INVALID_RESULT(PFX_TEXTURE_2D_SURFACE != surface_type &&
			PFX_TEXTURE_DEFUALT_SURFACE != surface_type, PFX_STATUS_INVALID_PARAMS);
		return m_native.update_surface(surface_ptr);
	}

	PFX_INLINE result_t update_default()
	{
		return m_native.update_surface(null);
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
		return m_native.set_texture_filter(param_name, __param);
	}

	PFX_INLINE result_t set_texture_filter(enum_int_t param_name, const enum_int_t* __param_ptr)
	{
		return m_native.set_texture_filter(param_name, __param_ptr);
	}

	PFX_INLINE result_t bind_texture()
	{
		m_native.bind();
		return PFX_STATUS_OK;
	}
	PFX_INLINE result_t bind ()
	{
		result_t status = PFX_STATUS_FAIL;
		if (m_native.check_status())
		{
			m_native.bind();
			status = PFX_STATUS_OK;
		}
		else
		{
			status = update_default();
			if (PFX_STATUS_OK <= status)
			{
				status = PFX_STATUS_SUCCESS;
			}
		}
		return status;
	}

	PFX_INLINE long_t   get_native_handle() const
	{
		return m_native.get_native_handle();
	}
	PFX_INLINE u64_t    get_version() const
	{
		return native_t::get_version();
	}

	PFX_INLINE enum_int_t get_target_type() const
	{
		return PFX_TEXTURE_TAG;
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
		return m_native.get_size(__size, level);
	}


};

class PFX_RENDER_SYSTEM_API ctextureCube_gles2 : public IPfx_texture
{

};


#ifdef _MSC_VER
#pragma warning(pop)
#endif

PECKER_END

#endif			//PFX_TEXTURE_GLES_H_
