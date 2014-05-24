/*
 * pfx_framebuffer_object.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDERBUFFER_H_
#define		PFX_RENDERBUFFER_H_

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

PFX_Interface IPfx_renderbuffer
{
	virtual usize__t			get_width () const = 0;
	virtual usize__t			get_height () const = 0;
	virtual enum_int_t	get_renderbuffer_format() const = 0; //PFX_RENDER_BUFFER_FMT_t
	virtual uindex_t		get_attachment_unit () const = 0;

	virtual result_t			bind_renderbuffer () = 0;
};

PFX_Interface IPfx_framebuffer
{
	virtual result_t attach_render_buffer (IPfx_renderbuffer* PARAM_IN attach_buffer_ptr,
																		uindex_t attachment_unit = 0) = 0;

	virtual result_t attach_texture_layer (Ipfx_texture_layer* PARAM_IN attach_texture_ptr,
																		enum_int_t attachment_for, //PFX_RENDER_BUFFER_FMT_t
																		uindex_t attachment_unit = 0) = 0;

	virtual result_t check_complete () const = 0;

	virtual result_t bind_framebuffer () = 0;
};

typedef enum enumFRAMEBUFFER_FORMAT
{
	PFX_FRAMEBUFFER_FMT = 0,
	PFX_UNKNOWN_FRAMEBUFFER_FMT,
	PFX_FRAMEBUFFER_FORMAT_COUNT
}PFX_FRAMEBUFFER_FMT_t;

template < typename frame_buffer_object_type >
struct PFX_FrameBufferObject_traits
{
	typedef typename frame_buffer_object_type	FBO_t;
	typedef typename FBO_t::render_device_t		render_device_t;
	typedef typename FBO_t::frame_buffer_t			frame_buffer_t;
	typedef typename FBO_t::render_buffer_t		render_buffer_t;

	static PFX_INLINE render_device_t& get_render_device (FBO_t& __fbo)
	{
		return FBO_t::get_render_device (__fbo);
	}
	static PFX_INLINE render_buffer_t* create_renderbuffer (render_device_t& render_device, 
		enum_int_t usage_format, //PFX_RENDER_BUFFER_FMT_t
		enum_int_t internal_format, 
		usize__t width, usize__t height)
	{
		return FBO_t::create_renderbuffer (render_device, usage_format, internal_format, width, height);
	}

	static PFX_INLINE result_t release_renderbuffer (render_device_t& render_device, 
		render_buffer_t* PARAM_IN renderbuffer_ptr)
	{
		return FBO_t::release_renderbuffer (render_device, renderbuffer_ptr);
	}

	static PFX_INLINE  frame_buffer_t* create_framebuffer (render_device_t& render_device,
		enum_int_t framebuffer_format = 0)
	{
		return FBO_t::create_framebuffer (render_device, framebuffer_format);
	}

	static PFX_INLINE  result_t release_framebuffer (render_device_t& render_device,
		frame_buffer_t* PARAM_IN framebuffer_ptr) 
	{
		return FBO_t::release_framebuffer(render_device, framebuffer_ptr);
	}

	static PFX_INLINE usize__t read_pixel (FBO_t& __fbo, const rectangle_region& __rect,
		enum_int_t pixelformat, void* read_pixel_buff_ptr, usize__t pixel_buffer_size)
	{
		return __fbo.read_pixel (__rect, pixelformat, read_pixel_buff_ptr, pixel_buffer_size);
	}

	static PFX_INLINE result_t pifxel_stroe_alignment (FBO_t& __fbo, enum_int_t PACK_ALIGNMENT)
	{
		return __fbo.pifxel_stroe_alignment (__fbo, PACK_ALIGNMENT);
	}

	//Whole Framebuffer Operations
	//	Fine Control of Buffer Updates [4.2.2]
	static PFX_INLINE void color_mask(FBO_t& __fbo,
		boolean_t r, boolean_t g, boolean_t b, boolean_t a)
	{
		__fbo.color_mask (r, g, b, a);
	}
	static PFX_INLINE void depth_mask(FBO_t& __fbo, boolean_t mask)
	{
		__fbo.depth_mask (mask);
	}

	static PFX_INLINE void stencil_mask(FBO_t& __fbo, bitfield_t mask)
	{
		__fbo.stencil_mask (mask);
	}
	static PFX_INLINE void stencil_mask_separete (FBO_t& __fbo, 
		enum_int_t __face, bitfield_t mask)
	{
		__fbo.stencil_mask_separete (__fbo, __face, mask);
	}

	static PFX_INLINE void clear (FBO_t& __fbo, bitfield_t buf)
	{
		__fbo.clear (buf);
	}
	static PFX_INLINE void clear (FBO_t& __fbo, bitfield_t buf)
	{
		__fbo.clear (buf);
	}
	static PFX_INLINE void clear_color (FBO_t& __fbo, 
		const float_RGBA_color& __color)
	{
		__fbo.clear_color (__color);
	}
	static PFX_INLINE void clear_color (FBO_t& __fbo, 
		const RGBA8_color& __color)
	{
		__fbo.clear_color (__color);
	}
	static PFX_INLINE void clear_depthf (FBO_t& __fbo, 
		const float_t& __depth)
	{
		__fbo.clear_depthf (__depth);
	}
	static PFX_INLINE void clear_stencil (FBO_t& __fbo, flag_t s)
	{
		__fbo.clear_stencil (s);
	}
};

//template < typename fragment_process  >
//struct PFX_PerFragment_traits
//{
//	typedef typename fragment_process											fragment_process_t;
//	typedef typename fragment_process_t::render_device_t		render_device_t;
//	static PFX_INLINE result_t enable_render_state ()
//	{
//
//	}
	//Scissor Test [4.1.2]
//	Enable/Disable(SCISSOR_TEST)
//		void Scissor(int left, int bottom, sizei width, sizei height );
//	Multisample Fragment Operations [4.1.3]
//	Enable/Disable(cap)
//cap: SAMPLE_ALPHA_TO_COVERAGE, SAMPLE_COVERAGE
//	 void SampleCoverage(clampf value, boolean invert);
//	Stencil Test [4.1.4]
//	Enable/Disable(STENCIL_TEST)
//		void StencilFunc(enum func, int ref, uint mask);
//	void StencilFuncSeparate(enum face, enum func, int ref,
//		uint mask);
//	void StencilOp(enum sfail, enum dpfail, enum dppass);
//	void StencilOpSeparate(enum face, enum sfail, enum dpfail,
//		enum dppass);
//face: FRONT, BACK, FRONT_AND_BACK
//		  sfail, dpfail, and dppass: KEEP, ZERO, REPLACE, INCR, DECR, INVERT,
//		  INCR_WRAP, DECR_WRAP
//func: NEVER, ALWAYS, LESS, LEQUAL, EQUAL, GREATER, GEQUAL,
//	  NOTEQUAL
//	  Depth Buffer Test [4.1.5]
//	  Enable/Disable(DEPTH_TEST)
//		  void DepthFunc(enum func);
//func: NEVER, ALWAYS, LESS, LEQUAL, EQUAL, GREATER, GEQUAL, NOTEQUAL
//		  Blending [4.1.6]
//	  Enable/Disable(BLEND) (applies to all draw buffers)
//		  void BlendEquation(enum mode);
//	  void BlendEquationSeparate(enum modeRGB,
//		  enum modeAlpha);
//	  mode, modeRGB, and modeAlpha: FUNC_ADD, FUNC_SUBTRACT,
//		  FUNC_REVERSE_SUBTRACT
//		  void BlendFuncSeparate(enum srcRGB, enum dstRGB,
//		  enum srcAlpha, enum dstAlpha);
//	  void BlendFunc(enum src, enum dst);
//	  dst, dstRGB, and dstAlpha: ZERO, ONE, [ONE_MINUS_]SRC_COLOR,
//		  [ONE_MINUS_]DST_COLOR, [ONE_MINUS_]SRC_ALPHA,
//		  [ONE_MINUS_]DST_ALPHA, [ONE_MINUS_]CONSTANT_COLOR,
//		  [ONE_MINUS_]CONSTANT_ALPHA
//		  src, srcRGB, srcAlpha: same for dst, plus SRC_ALPHA_SATURATE
//		  void BlendColor(clampf red, clampf green, clampf blue, clampf alpha);
//	  Dithering [4.1.7]
//	  Enable/Disable(DITHER)
//};

PECKER_END

#endif			//PFX_RENDERBUFFER_H_
