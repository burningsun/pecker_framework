/*
 * pfx_framebuffer_object.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDERBUFFER_H_
#define		PFX_RENDERBUFFER_H_

#include "../../pfx_defines.h"
#include "../pfx_color.h"
#include "pfx_texture.h"

PECKER_BEGIN

typedef enum enumRENDER_BUFFER_FORMAT
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

template < const pfx_enum_int_t DEPTH_BUFFER_FORMAT >
struct depth_buffer_format
{
	static PFX_INLINE  pfx_usize_t  BITS_SIZE()
	{
		return 0;
	}
	static PFX_INLINE  pfx_usize_t  BYTES_SIZE()
	{
		return 0;
	}
};

#define DEPTH_BUFFER_FORMAT_TRAITS(DEPTH_BUFFER_FMT,BITS_OF_TYPE) \
template < > \
struct depth_buffer_format < DEPTH_BUFFER_FMT > \
{ \
	static PFX_INLINE  pfx_usize_t  BITS_SIZE()\
	{\
		return BITS_OF_TYPE;\
	}\
	static PFX_INLINE  pfx_usize_t  BYTES_SIZE()\
	{\
		pfx_usize_t retn_size = (pfx_usize_t)BITS_OF_TYPE >> 3;/* BITS_OF_TYPE*/\
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

template < const pfx_enum_int_t STENCIL_BUFFER_FORMAT >
struct stencil_buffer_format
{
	static PFX_INLINE  pfx_usize_t  BITS_SIZE()
	{
		return 0;
	}
};

#define STENCIL_BUFFER_FORMAT_TRAITS(STENCIL_BUFFER_FMT,BITS_OF_TYPE) \
	template < > \
struct stencil_buffer_format < STENCIL_BUFFER_FMT > \
{ \
	static PFX_INLINE  pfx_usize_t  BITS_SIZE()\
   {\
	return BITS_OF_TYPE;\
   }\
};

STENCIL_BUFFER_FORMAT_TRAITS(PFX_STENCIL_INDEX8_FMT, 8);

PFX_Interface IPfx_renderbuffer
{
	virtual pfx_usize_t get_width () const = 0;
	virtual pfx_usize_t get_height () const = 0;
	virtual PFX_RENDER_BUFFER_FMT_t get_renderbuffer_format() const = 0;
	virtual pfx_uindex_t get_attachment_unit () const = 0;

	virtual pfx_result_t bind_renderbuffer () = 0;
};

PFX_Interface IPfx_framebuffer
{
	virtual pfx_result_t attach_render_buffer (IPfx_renderbuffer* PARAM_IN attach_buffer_ptr,
		pfx_uindex_t attachment_unit = 0) = 0;

	virtual pfx_result_t attach_texture_layer (Ipfx_texture_layer* PARAM_IN attach_texture_ptr,
		PFX_RENDER_BUFFER_FMT_t attachment_for, pfx_uindex_t attachment_unit = 0) = 0;

	virtual pfx_result_t check_complete () const = 0;

	virtual pfx_result_t bind_framebuffer () = 0;
};

typedef enum enumFRAMEBUFFER_FORMAT
{
	PFX_FRAMEBUFFER_FMT = 0,
	PFX_UNKNOWN_FRAMEBUFFER_FMT,
	PFX_FRAMEBUFFER_FORMAT_COUNT
}PFX_FRAMEBUFFER_FMT_t;

template < typename frame_buffer_object_type >
struct PFX_FrameBufferObject
{
	typedef typename frame_buffer_object_type::render_device_t		render_device_t;

	PFX_INLINE static IPfx_renderbuffer* create_renderbuffer (render_device_t render_device, 
		PFX_RENDER_BUFFER_FMT_t format,
		pfx_enum_int_t internal_format, pfx_usize_t width, pfx_usize_t height)
	{
		return null;
	}
	PFX_INLINE static pfx_result_t release_renderbuffer (render_device_t render_device, 
		IPfx_renderbuffer* PARAM_IN renderbuffer_ptr)
	{
		return PFX_STATUS_DENIED;
	}

	PFX_INLINE static IPfx_framebuffer* create_framebuffer (render_device_t render_device,
		pfx_enum_int_t framebuffer_format = 0)
	{
		return null;
	}
	PFX_INLINE static pfx_result_t release_framebuffer (render_device_t render_device,
		pfx_enum_int_t framebuffer_format = 0) 
	{
		return PFX_STATUS_DENIED;
	}
};

PECKER_END

#endif			//PFX_RENDERBUFFER_H_
