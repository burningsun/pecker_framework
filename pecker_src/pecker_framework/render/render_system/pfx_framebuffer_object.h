/*
 * pfx_framebuffer_object.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_FRAMEBUFFER_OBJECT_H_
#define		PFX_FRAMEBUFFER_OBJECT_H_

#include "../../include/config"
#include "../../include/util"
#include "../pfx_color.h"
#include "pfx_texture.h"

PECKER_BEGIN

typedef enum enumRENDER_BUFFER_USAGE
{
	PFX_COLOR_BUFFER_FMT,
	PFX_DEPTH_BUFFER_FMT,
	PFX_STENCIL_BUFFER_FMT,

	PFX_UNKOWN_RENDER_BUFFER_FMT,
	PFX_RENDER_BUFFER_FMT_COUNT
}PFX_RENDER_BUFFER_FMT_t;

typedef enum enumDEPTH_BUFFER_FMT
{
	PFX_DEPTH_COMPONENT16_FMT = 0,

	//OES_TYPE,
	PFX_DEPTH_COMPONENT24_FMT,
	PFX_DEPTH_COMPONENT32_FMT,

	PFX_UNKOWN_DEPTH_BUFFER_FMT,
	PFX_DEPTH_BUFFER_FMT_COUNT
}PFX_DEPTH_BUFFER_FMT_t;

template < const enum_int_t DEPTH_BUFFER_FORMAT >
struct depth_buffer_format
{
	static PFX_INLINE  usize__t  BITS_SIZE()
	{
		return 0;
	}
	static PFX_INLINE  usize__t  BYTES_SIZE()
	{
		return 0;
	}
};

#define DEPTH_BUFFER_FORMAT_TRAITS(DEPTH_BUFFER_FMT,BITS_OF_TYPE) \
template < > \
struct depth_buffer_format < DEPTH_BUFFER_FMT > \
{ \
	static PFX_INLINE  usize__t  BITS_SIZE()\
	{\
		return BITS_OF_TYPE;\
	}\
	static PFX_INLINE  usize__t  BYTES_SIZE()\
	{\
		usize__t retn_size = (usize__t)BITS_OF_TYPE >> 3;/* BITS_OF_TYPE*/\
		return ((retn_size) ? retn_size:1);\
	}\
};
DEPTH_BUFFER_FORMAT_TRAITS(PFX_DEPTH_COMPONENT16_FMT,16);

typedef enum enumSTENCIL_BUFFER_FORMAT
{
	PFX_STENCIL_INDEX8_FMT = 0,

	//OES_TYPE,

	PFX_STENCIL_INDEX1_FMT,
	PFX_STENCIL_INDEX4_FMT,

	PFX_UNKOWN_STENCIL_BUFFER_FMT,
	PFX_STENCIL_BUFFER_FMT_COUNT
}PFX_STENCIL_BUFFER_FMT_t;

template < const enum_int_t STENCIL_BUFFER_FORMAT >
struct stencil_buffer_format
{
	static PFX_INLINE  usize__t  BITS_SIZE()
	{
		return 0;
	}
};

#define STENCIL_BUFFER_FORMAT_TRAITS(STENCIL_BUFFER_FMT,BITS_OF_TYPE) \
	template < > \
struct stencil_buffer_format < STENCIL_BUFFER_FMT > \
{ \
	static PFX_INLINE  usize__t  BITS_SIZE()\
   {\
	return BITS_OF_TYPE;\
   }\
};

STENCIL_BUFFER_FORMAT_TRAITS(PFX_STENCIL_INDEX8_FMT, 8);



typedef enum enumFRAMEBUFFER_FORMAT
{
	PFX_FRAMEBUFFER_FMT = 0,
	PFX_UNKNOWN_FRAMEBUFFER_FMT,
	PFX_FRAMEBUFFER_FORMAT_COUNT
}PFX_FRAMEBUFFER_FMT_t;

PFX_Interface  IPfx_renderbuffer : public IPfx_rendertarget
{
	virtual ~IPfx_renderbuffer(){ ; }
	virtual result_t create_rendertarget(enum_int_t usage_type, //  PFX_RENDER_BUFFER_FMT_t
		enum_int_t format,
		usize__t width, usize__t height) = 0;
	virtual bool     check_status() const = 0;

	virtual enum_int_t get_usage_type() const = 0;
	virtual enum_int_t get_format() const = 0;

	virtual result_t bind_renderbuffer() = 0;

	virtual result_t dispose_renderbuffer() = 0;
	virtual result_t dispose_render_target() = 0;

	virtual long_t   get_native_handle() const = 0;
	virtual u64_t    get_version() const = 0;
};

PFX_Interface  IPfx_framebuffer : public IPfx_rendertarget
{
	virtual ~IPfx_framebuffer(){ ; }

	virtual result_t attach_renderbuffer(
		IPfx_renderbuffer* PARAM_IN render_buffer,
		uindex_t attachment_index = 0
		) = 0;
	virtual result_t attach_texture(
		enum_int_t usage_type, //  PFX_RENDER_BUFFER_FMT_t
		IPfx_texture* PARAM_IN texture2D_ptr, 
		uindex_t attachment_index = 0,
		uindex_t mip_level = 0,
		enum_int_t surface_type = PFX_TEXTURE_DEFUALT_SURFACE) = 0;

	virtual bool     check_status() const = 0;

	virtual result_t create_rendertarget(
		usize__t width = 0, usize__t height = 0,
		enum_int_t color_format = PFX_RGB_565_FMT,
		enum_int_t depth_format = PFX_DEPTH_COMPONENT16_FMT,
		enum_int_t stencil_format = PFX_STENCIL_INDEX8_FMT
		) = 0;

	virtual result_t dispose_framebuffer() = 0;
	virtual result_t dispose_render_target() = 0;

	virtual IPfx_texture* get_texture(enum_int_t usage_type, 
		uindex_t attachment_index) = 0;

	virtual result_t bind_framebuffer() = 0;

	virtual long_t   get_native_handle() const = 0;
	virtual u64_t    get_version() const = 0;
};




PECKER_END

#endif			//PFX_FRAMEBUFFER_OBJECT_H_
