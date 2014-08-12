/*
 * color.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_COLOR_H_
#define		PFX_COLOR_H_

#include "pfx_render_traits.h"

PECKER_BEGIN

typedef enum enumINTERNAL_COLOR_FORMAT_TYPE
{
	PFX_RGBA_FMT,
	PFX_RGB_FMT,

	PFX_ALPHA_FMT,
	PFX_LUMINANCE_FMT,
	PFX_LUMINANCE_ALPHA_FMT,

	PFX_UNKNOWN_COLOR_INFMT,
	INTERNAL_COLOR_FORMAT_TYPE_t
}PFX_INTERNAL_COLOR_FORMAT_TYPE_t;

typedef enum enumCOLOR_FORMAT_TYPE
{
	PFX_RGBA_FLOAT_FMT = 0,
	PFX_RGBA8_FMT,
	PFX_RGBA_4444_FMT,
	PFX_RGBA_5551_FMT,

	PFX_RGBA16_FMT,
	PFX_RGB16_FMT,

	PFX_RGB_FLOAT_FMT,
	PFX_RGB8_FMT,
	PFX_RGB_565_FMT,

	PFX_ALPHA_8_FMT,
	PFX_LUMINANCE_8_FMT,
	PFX_LUMINANCE_ALPHA_88_FMT,

	PFX_COMPRESS_COLOR_FMT,
	PFX_UNKNOW_COLOR_FMT,
	PFX_COLOR_FORMAT_COUNT
}PFX_COLOR_FORMAT_TYPE_t;

template < const enum_int_t color_format >
struct PFX_RENDER_TEMPLATE_API color_internal_format
{
	static  PFX_INLINE enum_int_t get_internal_format ()
	{
		return PFX_UNKNOWN_COLOR_INFMT;
	}
};
#define COLOR_INTERNAL_FORMAT_TRAITS(FORMAT,INTERANL_FORMAT) \
template <  >\
struct  color_internal_format < FORMAT >\
{\
	static  PFX_INLINE enum_int_t get_internal_format ()\
	{\
		return INTERANL_FORMAT;\
	}\
};
COLOR_INTERNAL_FORMAT_TRAITS(PFX_RGBA_FLOAT_FMT, PFX_RGBA_FMT)
COLOR_INTERNAL_FORMAT_TRAITS(PFX_RGBA8_FMT, PFX_RGBA_FMT)
COLOR_INTERNAL_FORMAT_TRAITS(PFX_RGBA_4444_FMT, PFX_RGBA_FMT)
COLOR_INTERNAL_FORMAT_TRAITS(PFX_RGBA_5551_FMT, PFX_RGBA_FMT)

COLOR_INTERNAL_FORMAT_TRAITS(PFX_RGB_FLOAT_FMT,PFX_RGB_FMT)
COLOR_INTERNAL_FORMAT_TRAITS(PFX_RGB8_FMT,PFX_RGB_FMT)
COLOR_INTERNAL_FORMAT_TRAITS(PFX_RGB_565_FMT,PFX_RGB_FMT)

COLOR_INTERNAL_FORMAT_TRAITS(PFX_ALPHA_8_FMT, PFX_ALPHA_FMT)
COLOR_INTERNAL_FORMAT_TRAITS(PFX_LUMINANCE_8_FMT, PFX_LUMINANCE_FMT)
COLOR_INTERNAL_FORMAT_TRAITS(PFX_LUMINANCE_ALPHA_88_FMT, PFX_LUMINANCE_ALPHA_FMT)

//PFX_INLINE pfx_enum_int_t get_internal_format (pfx_enum_int_t color_format)
//{
//	pfx_enum_int_t retn_format;
//	switch (color_format)
//	{
//		case PFX_RGBA_FLOAT_FMT:
//		case PFX_RGBA8_FMT:
//		case PFX_RGBA_4444_FMT:
//		case PFX_RGBA_5551_FMT:
//			retn_format = PFX_RGBA_FMT;
//			break;
//		case PFX_RGB_FLOAT_FMT:
//		case PFX_RGB8_FMT:
//		case PFX_RGB_565_FMT:
//			retn_format = PFX_RGB_FMT;
//			break;
//		case PFX_ALPHA_8_FMT:
//			retn_format = PFX_ALPHA_FMT;
//			break;
//		case PFX_LUMINANCE_8_FMT:
//			retn_format = PFX_LUMINANCE_FMT;
//			break;
//		case PFX_LUMINANCE_ALPHA_88_FMT:
//			retn_format = PFX_LUMINANCE_ALPHA_FMT;
//			break;
//		default:
//			retn_format = PFX_UNKNOW_COLOR_INFMT;
//			break;
//	}
//	return retn_format;
//}

typedef bitfield_t		bits_color_t;
typedef u16_t			u16bits_color_t;
typedef u8_t			u8bits_color_t;

#pragma pack(push)
#pragma pack(1)
struct float_RGBA_color
{
	typedef float_t value_type;

	float_t m_red;
	float_t m_green;
	float_t m_blue;
	float_t m_alpha;
};

struct float_RGB_color
{
	typedef float_t value_type;

	float_t m_red;
	float_t m_green;
	float_t m_blue;
};

struct RGBA8_color
{
	typedef u8_t value_type;

	unsigned m_red		:8;
	unsigned m_green	:8;
	unsigned m_blue		:8;
	unsigned m_alpha	:8;
};

struct RGBA16_color
{
	typedef u16_t value_type;

	unsigned m_red : 16;
	unsigned m_green : 16;
	unsigned m_blue : 16;
	unsigned m_alpha : 16;
};

struct RBG8_color
{
	typedef u8_t value_type;

	unsigned m_red		:8;
	unsigned m_green	:8;
	unsigned m_blue		:8;
	//unsigned m_alpha	:8;
};

struct RGB16_color
{
	typedef u16_t value_type;

	unsigned m_red : 16;
	unsigned m_green : 16;
	unsigned m_blue : 16;
};

struct RGBA_4444_color
{
	typedef u8_t value_type;

	unsigned m_red		:4;
	unsigned m_green	:4;
	unsigned m_blue		:4;
	unsigned m_alpha	:4;
};

struct RGBA_5551_color
{
	typedef u8_t value_type;

	unsigned m_red		:5;
	unsigned m_green	:5;
	unsigned m_blue		:5;
	unsigned m_alpha	:1;
};

struct RGB_565_color
{
	typedef u8_t value_type;

	unsigned m_red		:5;
	unsigned m_green	:6;
	unsigned m_blue		:5;
};

struct ALPHA_8_color
{
	typedef u8_t value_type;

	u8_t m_alpha;
};

struct LUMINANCE_8_color
{
	typedef u8_t value_type;

	u8_t m_luminance;
};

struct LUMINANCE_ALPHA_88_color
{
	typedef u8_t value_type;

	u8_t m_luminance;
	u8_t m_alpha;
};
#pragma pack(pop)

PFX_INLINE usize__t max_color_size()
{
	static const usize__t max_size = (sizeof (float_RGBA_color)+ 2 * sizeof(float_t));
	return max_size;
}

// 通过 PFX_COLOR_FORMAT_TYPE_t 和
//容器color_format_reference获取想要的颜色结构
template < const enum_int_t color_format >
struct PFX_RENDER_TEMPLATE_API color_value_reference
{
	// 通用情况下是PFX_UNKNOW_COLOR_FMT
	typedef bits_color_t	color_value;
};

//容器特例化
template <  >
struct color_value_reference < PFX_RGBA_FLOAT_FMT >
{
	typedef float_RGBA_color	color_value;
};
template <  >
struct color_value_reference < PFX_RGB_FLOAT_FMT >
{
	typedef float_RGB_color color_value;
};
template <  >
struct color_value_reference < PFX_RGBA8_FMT >
{
	typedef RGBA8_color	color_value;
};
template <  >
struct color_value_reference < PFX_RGB8_FMT >
{
	typedef RGBA8_color color_value;
};
template <  >
struct color_value_reference < PFX_RGBA_4444_FMT >
{
	typedef RGBA_4444_color	color_value;
};
template <  >
struct color_value_reference < PFX_RGBA_5551_FMT >
{
	typedef RGBA_5551_color	color_value;
};
template <  >
struct color_value_reference < PFX_RGB_565_FMT >
{
	typedef RGB_565_color	color_value;
};
template <  >
struct color_value_reference < PFX_ALPHA_8_FMT >
{
	typedef ALPHA_8_color	color_value;
};
template <  >
struct color_value_reference < PFX_LUMINANCE_8_FMT >
{
	typedef LUMINANCE_8_color	color_value;
};
template <  >
struct color_value_reference < PFX_LUMINANCE_ALPHA_88_FMT >
{
	typedef LUMINANCE_ALPHA_88_color	color_value;
};

template <  >
struct color_value_reference < PFX_RGB16_FMT >
{
	typedef RGB16_color	color_value;
};

template <  >
struct color_value_reference < PFX_RGBA16_FMT >
{
	typedef RGBA16_color	color_value;
};

template <  >
struct color_value_reference < PFX_COMPRESS_COLOR_FMT >
{
	typedef byte_t	color_value;
};

template< const enum_int_t  color_format >
struct color_format_size
{
	static PFX_INLINE  nsize__t SIZE()
	{
		return sizeof (typename color_value_reference < color_format >::color_value);
	}
};

// 颜色类
template < class color_value >
struct PFX_RENDER_TEMPLATE_API color
{
	typedef color_value value_type;
	typedef typename color_reference_type < color_value >::value_type color_chanel_t; 

	color_value	m_value;

	color ();
	color (const color_chanel_t luminance,const color_chanel_t alpha);
	color (const color_chanel_t red, const color_chanel_t green, 
		const color_chanel_t blue, const color_chanel_t alpha);
	color (const color_chanel_t alpha);
	color (const color_value& color_val);
	color (bitfield_t RGBA);
	color (const color< color_value >& other);

	// 32bits
	PFX_INLINE bitfield_t to_RGBA_bits_format () const;
	// 24bits
	PFX_INLINE bitfield_t to_RGB_bits_format () const;

	PFX_INLINE  void set_color(const color_chanel_t red, const color_chanel_t green, 
		const color_chanel_t blue, const color_chanel_t alpha);

	PFX_INLINE  void set_color(const color_chanel_t luminance);

	PFX_INLINE void set_color (const color_value& color_val);
	PFX_INLINE void set_color_by_bits (bitfield_t RGBA);
	PFX_INLINE void set_color (const color< color_value >& other);

	PFX_INLINE color_chanel_t* get_buffer_reference ();
	PFX_INLINE const color_chanel_t* get_buffer ()		const;

	PFX_INLINE const color_chanel_t red ()					const;
	PFX_INLINE const color_chanel_t green ()				const;
	PFX_INLINE const color_chanel_t blue ()					const;
	PFX_INLINE const color_chanel_t alpha ()				const;
	PFX_INLINE const color_chanel_t luminance ()		const;

	PFX_INLINE void red (const color_chanel_t chanel_value);
	PFX_INLINE void green (const color_chanel_t chanel_value);
	PFX_INLINE void blue (const color_chanel_t chanel_value);
	PFX_INLINE void alpha (const color_chanel_t chanel_value);
	PFX_INLINE void luminance (const color_chanel_t chanel_value);
};

template < const enum_int_t color_format >
struct PFX_RENDER_TEMPLATE_API color_reference
{
	typedef color < typename  color_value_reference< color_format >::color_value	 >	color_t;
};


typedef color_reference< PFX_RGBA8_FMT >::color_t		colori_t;
typedef color_reference< PFX_RGBA_FLOAT_FMT >::color_t	colorf_t;











///codes
/////////////////////////////////////////////////////////////////////////
#define pfx_color_chanel_t typename color_reference_type < color_value >::value_type
#define PFX_COLOR_TEMPLATE_DEFINES template < class color_value >
#define PFX_COLOR_TEMPLATE_PARAMS < color_value >
#define pfx_color_chanel_sp_t(color_value) color_reference_type < color_value >::value_type

//////////////////////////////////////////////////////////////////////////
PFX_COLOR_TEMPLATE_DEFINES
color PFX_COLOR_TEMPLATE_PARAMS :: color ()
{ 
	set_color (0,0,0,0);
	set_color (0);
}
//template<>
//color < bits_color_t > :: color() : m_value(0)
//{;}
//template<>
//color < u16bits_color_t > :: color() : m_value(0)
//{;}
//template<>
//color < u8bits_color_t > :: color() : m_value(0)
//{;}

//////////////////////////////////////////////////////////////////////////
//color (const color_chanel_t luminance,const color_chanel_t alpha)
PFX_COLOR_TEMPLATE_DEFINES
color PFX_COLOR_TEMPLATE_PARAMS :: color(const color_chanel_t luminance,const color_chanel_t alpha)
{
	set_color (0,0,0,alpha);
	set_color (luminance);
}
//template<>
//color < bits_color_t > :: color(const color_chanel_t luminance,const color_chanel_t alpha) : 
//m_value((((bits_color_t)luminance << 8)& 0xFF00)|(((bits_color_t)alpha)&0xFF))
//{;}
//template<>
//color < u16bits_color_t > :: color(const color_chanel_t luminance,const color_chanel_t alpha) : 
//m_value((((bits_color_t)luminance << 8) & 0xFF00)|((bits_color_t)alpha&0xFF))
//{;}
//template<>
//color < u8bits_color_t > :: color(const color_chanel_t luminance,const color_chanel_t alpha) : m_value(0)
//{;}
//
//	color (const color_chanel_t red, const color_chanel_t green, 
//	const color_chanel_t blue, const color_chanel_t alpha)
PFX_COLOR_TEMPLATE_DEFINES
color PFX_COLOR_TEMPLATE_PARAMS :: color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	set_color (red,green,blue,alpha);
	set_color (0);
}
//template<>
//color < bits_color_t > :: color(const color_chanel_t red, const color_chanel_t green, const color_chanel_t blue, const color_chanel_t alpha): 
//m_value((((bits_color_t)red << 24) & 0xFF000000)|(((bits_color_t)green << 16) & 0xFF0000)|(((bits_color_t)blue << 8) & 0xFF00)|((bits_color_t)alpha &0xFF))
//{;}
//template<>
//	color < u16bits_color_t > :: color(const color_chanel_t red, const color_chanel_t green, 
//	const color_chanel_t blue, const color_chanel_t alpha) : 
//m_value((((bits_color_t)red << 12) & 0xF000)|(((bits_color_t)green << 8) & 0xF00)|(((bits_color_t)blue << 4) & 0xF0)|((bits_color_t)alpha &0xF))
//{;}
//template<>
//color < u8bits_color_t > :: color(const color_chanel_t red, const color_chanel_t green, 
//	const color_chanel_t blue, const color_chanel_t alpha) : m_value(0)
//{;}

//////////////////////////////////////////////////////////////////////////
//color (const  const color_chanel_t alpha);
PFX_COLOR_TEMPLATE_DEFINES
color PFX_COLOR_TEMPLATE_PARAMS :: color (const color_chanel_t alpha) 
{
	set_color (0,0,0,alpha);
	set_color (0);
}
//template<>
//color < bits_color_t > :: color(const color_chanel_t alpha) : 
//m_value(((bits_color_t)alpha)&0xFF)
//{;}
//template<>
//color < u16bits_color_t > :: color(const color_chanel_t alpha) : 
//m_value(((bits_color_t)alpha >> 4)&0xF)
//{;}
//template<>
//color < u8bits_color_t > :: color (const color_chanel_t alpha) : m_value (0)
//{;}

//////////////////////////////////////////////////////////////////////////
PFX_COLOR_TEMPLATE_DEFINES
color PFX_COLOR_TEMPLATE_PARAMS :: color (const color_value& color_val) : m_value (color_val)
{;}
//////////////////////////////////////////////////////////////////////////
PFX_COLOR_TEMPLATE_DEFINES
color PFX_COLOR_TEMPLATE_PARAMS :: color (bitfield_t RGBA) : 
color PFX_COLOR_TEMPLATE_PARAMS ( (const color_chanel_t )((RGBA >> 24)&0xFF),
	(const color_chanel_t) ((RGBA >> 16)&0xFF) ,
	(const color_chanel_t) ((RGBA >> 8)&0xFF),
	(const color_chanel_t) (RGBA&0xFF))
{
	;
}
//
//color (const color< color_value >& other);
PFX_COLOR_TEMPLATE_DEFINES
color PFX_COLOR_TEMPLATE_PARAMS :: color (const color< color_value >& other)
{
	if (this != &other)
	{
		m_value = other.m_value;
	}
}

//// 32bits
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE bitfield_t color PFX_COLOR_TEMPLATE_PARAMS ::to_RGBA_bits_format () const
{
	return m_value;
}

template<>
PFX_INLINE bitfield_t color < u16bits_color_t > ::to_RGBA_bits_format () const
{
	return (((bitfield_t)(m_value & 0xF000) * 17) << 12 )|
		(((bitfield_t)(m_value & 0xF00)*17) << 8 )|
		(((bitfield_t)(m_value & 0xF0)*17) << 4 )|
		(((bitfield_t)(m_value & 0xF)*17));
}

template<>
PFX_INLINE bitfield_t color < float_RGBA_color > ::to_RGBA_bits_format () const
{
	return ((bitfield_t)(m_value.m_red * 255.0f) << 24 )|
				((bitfield_t)(m_value.m_green * 255.0f) << 16 )|
				((bitfield_t)(m_value.m_blue * 255.0f) << 8 )|
				((bitfield_t)(m_value.m_alpha * 255.0f) );
}

template<>
PFX_INLINE bitfield_t color < float_RGB_color > ::to_RGBA_bits_format () const
{
	return ((bitfield_t)(m_value.m_red * 255.0f) << 24 )|
		((bitfield_t)(m_value.m_green * 255.0f) << 16 )|
		((bitfield_t)(m_value.m_blue * 255.0f) << 8 ) | 0xFF;
}

template<>
PFX_INLINE bitfield_t color < RGBA8_color > ::to_RGBA_bits_format () const
{
	return ((bitfield_t)(m_value.m_red) << 24 )|
		((bitfield_t)(m_value.m_green) << 16 )|
		((bitfield_t)(m_value.m_blue) << 8 )|
		((bitfield_t)(m_value.m_alpha) );
}

template<>
PFX_INLINE bitfield_t color < RBG8_color > ::to_RGBA_bits_format () const
{
	return ((bitfield_t)(m_value.m_red) << 24 )|
		((bitfield_t)(m_value.m_green) << 16 )|
		((bitfield_t)(m_value.m_blue) << 8 ) | 0xFF;
}

template<>
PFX_INLINE bitfield_t color < RGBA_4444_color > ::to_RGBA_bits_format () const
{
	return (((bitfield_t)(m_value.m_red) * 17) << 24 )|
		(((bitfield_t)(m_value.m_green)*17) << 16 )|
		(((bitfield_t)(m_value.m_blue)*17) << 8 )|
		(((bitfield_t)(m_value.m_alpha)*17));
}

template<>
PFX_INLINE bitfield_t color < RGBA_5551_color > ::to_RGBA_bits_format () const
{
	return (((bitfield_t)(m_value.m_red) * 255 / 31) << 24 )|
		(((bitfield_t)(m_value.m_green)*255/31) << 16 )|
		(((bitfield_t)(m_value.m_blue)*255/31) << 8 )|
		(((bitfield_t)(m_value.m_alpha)* 255));
}

template<>
PFX_INLINE bitfield_t color < RGB_565_color > ::to_RGBA_bits_format () const
{
	return (((bitfield_t)(m_value.m_red) * 255 / 31) << 24 )|
		(((bitfield_t)(m_value.m_green)*255/63) << 16 )|
		(((bitfield_t)(m_value.m_blue)*255/31) << 8 )| 0xFF;
}

template<>
PFX_INLINE bitfield_t color < ALPHA_8_color > ::to_RGBA_bits_format () const
{
	return (bitfield_t)(m_value.m_alpha)* 17;
}

template<>
PFX_INLINE bitfield_t color < LUMINANCE_8_color > ::to_RGBA_bits_format () const
{
	return 0;
}

template<>
PFX_INLINE bitfield_t color < LUMINANCE_ALPHA_88_color > ::to_RGBA_bits_format () const
{
	return (bitfield_t)(m_value.m_alpha)* 17;
}


//// 24bits
//PFX_INLINE pfx_bitfield_t to_RGB_bits_format () const;
PFX_COLOR_TEMPLATE_DEFINES
	PFX_INLINE bitfield_t color PFX_COLOR_TEMPLATE_PARAMS ::to_RGB_bits_format () const
{
	return m_value;
}

template<>
	PFX_INLINE bitfield_t color < u16bits_color_t > ::to_RGB_bits_format () const
{
	return (((bitfield_t)(m_value & 0xF000) * 17) << 8 )|
		(((bitfield_t)(m_value & 0xF00)*17) << 4 )|
		(((bitfield_t)(m_value & 0xF0)*17) );
}

template<>
PFX_INLINE bitfield_t color < float_RGBA_color > ::to_RGB_bits_format () const
{
	return ((bitfield_t)(m_value.m_red * 255.0f) << 16 )|
		((bitfield_t)(m_value.m_green * 255.0f) << 8 )|
		((bitfield_t)(m_value.m_blue * 255.0f));
}

template<>
	PFX_INLINE bitfield_t color < float_RGB_color > ::to_RGB_bits_format () const
{
	return ((bitfield_t)(m_value.m_red * 255.0f) << 16 )|
		((bitfield_t)(m_value.m_green * 255.0f) << 8 )|
		((bitfield_t)(m_value.m_blue * 255.0f));
}

template<>
	PFX_INLINE bitfield_t color < RGBA8_color > ::to_RGB_bits_format () const
{
	return ((bitfield_t)(m_value.m_red) << 16 )|
		((bitfield_t)(m_value.m_green) << 8 )|
		((bitfield_t)(m_value.m_blue));
}

template<>
	PFX_INLINE bitfield_t color < RBG8_color > ::to_RGB_bits_format () const
{
	return ((bitfield_t)(m_value.m_red) << 16 )|
		((bitfield_t)(m_value.m_green) << 8 )|
		((bitfield_t)(m_value.m_blue));
}

template<>
	PFX_INLINE bitfield_t color < RGBA_4444_color > ::to_RGB_bits_format () const
{
	return (((bitfield_t)(m_value.m_red) * 17) << 16 )|
		(((bitfield_t)(m_value.m_green)*17) << 8 )|
		(((bitfield_t)(m_value.m_blue)*17));
}

template<>
	PFX_INLINE bitfield_t color < RGBA_5551_color > ::to_RGB_bits_format () const
{
	return (((bitfield_t)(m_value.m_red) * 255 / 31) << 16 )|
		(((bitfield_t)(m_value.m_green)*255/31) << 8 )|
		(((bitfield_t)(m_value.m_blue)*255/31));
}

template<>
	PFX_INLINE bitfield_t color < RGB_565_color > ::to_RGB_bits_format () const
{
	return (((bitfield_t)(m_value.m_red) * 255 / 31) << 16 )|
		(((bitfield_t)(m_value.m_green)*255/63) << 8 )|
		(((bitfield_t)(m_value.m_blue)*255/31));
}

template<>
	PFX_INLINE bitfield_t color < ALPHA_8_color > ::to_RGB_bits_format () const
{
	return 0;
}

template<>
	PFX_INLINE bitfield_t color < LUMINANCE_8_color > ::to_RGB_bits_format () const
{
	return 0;
}

template<>
	PFX_INLINE bitfield_t color < LUMINANCE_ALPHA_88_color > ::to_RGB_bits_format () const
{
	return 0;
}

//
//PFX_INLINE  void set_color(const color_chanel_t red, const color_chanel_t green, 
//	const color_chanel_t blue, const color_chanel_t alpha);
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE  void color PFX_COLOR_TEMPLATE_PARAMS :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value  = 0;
}
template<>
PFX_INLINE  void color < bits_color_t > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value = ((((bits_color_t)red << 24) & 0xFF000000)|(((bits_color_t)green << 16) & 0xFF0000)|(((bits_color_t)blue << 8) & 0xFF00)|((bits_color_t)alpha &0xFF));
}

template<>
PFX_INLINE  void color < u16bits_color_t > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha) 
{
	m_value = ((((bits_color_t)red << 8) & 0xF000)|(((bits_color_t)green << 4) & 0xF00)|(((bits_color_t)blue) & 0xF0)|(((bits_color_t)alpha >> 4)  &0xF));
}

template<>
PFX_INLINE  void color < float_RGBA_color > :: set_color (const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_red		= red;
	m_value.m_green	= green;
	m_value.m_blue		= blue;
	m_value.m_alpha	= alpha;
}
template<>
PFX_INLINE  void color < float_RGB_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_red		= red;
	m_value.m_green	= green;
	m_value.m_blue		= blue;
}

template<>
PFX_INLINE  void color < RGBA8_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_red		= red;
	m_value.m_green	= green;
	m_value.m_blue		= blue;
	m_value.m_alpha	= alpha;
}
template<>
PFX_INLINE  void color < RBG8_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_red		= red;
	m_value.m_green	= green;
	m_value.m_blue		= blue;
}

template<>
PFX_INLINE  void color < RGBA_4444_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_red		= red >> 4;
	m_value.m_green	= green >> 4;
	m_value.m_blue		= blue >> 4;
	m_value.m_alpha	= alpha >> 4;
}
template<>
PFX_INLINE  void color < RGBA_5551_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha) 
{
	m_value.m_red		= red >> 3;
	m_value.m_green	= green >> 3;
	m_value.m_blue		= blue >> 3;
	m_value.m_alpha	= alpha > 0 ? 1:0;
}
template<>
PFX_INLINE  void color < RGB_565_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_red		= red >> 3;
	m_value.m_green	= green >> 2;
	m_value.m_blue		= blue >> 3;
}
template<>
PFX_INLINE  void color < ALPHA_8_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_alpha = alpha;
}
template<>
PFX_INLINE  void color < LUMINANCE_8_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha){;}
template<>
PFX_INLINE  void color < LUMINANCE_ALPHA_88_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_alpha = alpha;
}

//
//PFX_INLINE  void set_color(const color_chanel_t luminance);
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE  void color PFX_COLOR_TEMPLATE_PARAMS :: set_color(const color_chanel_t luminance)
{
	;
}
template<>
	PFX_INLINE  void color < LUMINANCE_8_color > :: set_color(const color_chanel_t luminance)
{
	m_value.m_luminance =0;
}
template<>
PFX_INLINE  void color < LUMINANCE_ALPHA_88_color > :: set_color(const color_chanel_t luminance)
{
	m_value.m_luminance =0;
}

//
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE  void color PFX_COLOR_TEMPLATE_PARAMS ::set_color (const color_value& color_val)
{
	m_value = color_val;
}

PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE void color PFX_COLOR_TEMPLATE_PARAMS ::set_color_by_bits (bitfield_t RGBA)
{
	set_color( (RGBA&0xFF000000)>>24,  (RGBA&0xFF0000)>>16,  (RGBA&0xFF00)>>8,  RGBA&0xFF );
}

PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE void color PFX_COLOR_TEMPLATE_PARAMS ::set_color (const color< color_value >& other)
{
	if (&other != this)
	{
		m_value = other.m_value;
	}
}
//
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE pfx_color_chanel_t* color PFX_COLOR_TEMPLATE_PARAMS ::get_buffer_reference ()
{
	return (pfx_color_chanel_t*)&m_value;
}
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE const pfx_color_chanel_t* color PFX_COLOR_TEMPLATE_PARAMS ::get_buffer ()		const
{
	return (const pfx_color_chanel_t*)&m_value;
}

PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE const pfx_color_chanel_t color PFX_COLOR_TEMPLATE_PARAMS ::red ()	const
{
	return m_value.m_red;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(bitfield_t) color < bitfield_t > ::red ()	const
{
	return (m_value & 0xFF000000) >> 24;
}

template<>
PFX_INLINE const pfx_color_chanel_sp_t(u16bits_color_t) color < u16bits_color_t > ::red ()	const
{
	return ((m_value & 0xF000) * 17 )<< 12;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(u8bits_color_t) color < u8bits_color_t > ::red ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(ALPHA_8_color) color < ALPHA_8_color > ::red ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(LUMINANCE_8_color) color < LUMINANCE_8_color > ::red ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(LUMINANCE_ALPHA_88_color) color < LUMINANCE_ALPHA_88_color > ::red ()	const
{
	return 0;
}


//////////////////////////////////////////////////////////////////////////
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE const pfx_color_chanel_t color PFX_COLOR_TEMPLATE_PARAMS ::green ()	 const
{
	return m_value.m_green;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(u16bits_color_t) color < u16bits_color_t > ::green ()	const
{
	return ((m_value & 0xF00) * 17 )<< 8;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(u8bits_color_t) color < u8bits_color_t > ::green ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(ALPHA_8_color) color < ALPHA_8_color > ::green ()	const
{
	return 0;
}
template<>
	PFX_INLINE const pfx_color_chanel_sp_t(LUMINANCE_8_color) color < LUMINANCE_8_color > ::green ()	const
{
	return 0;
}
template<>
	PFX_INLINE const pfx_color_chanel_sp_t(LUMINANCE_ALPHA_88_color) color < LUMINANCE_ALPHA_88_color > ::green ()	const
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE const pfx_color_chanel_t color PFX_COLOR_TEMPLATE_PARAMS ::blue () const
{
	return m_value.m_blue;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(u16bits_color_t) color < u16bits_color_t > ::blue ()	const
{
	return ((m_value & 0xF0) * 17 )<< 4;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(u8bits_color_t) color < u8bits_color_t > ::blue ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(ALPHA_8_color) color < ALPHA_8_color > ::blue ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(LUMINANCE_8_color) color < LUMINANCE_8_color > ::blue ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(LUMINANCE_ALPHA_88_color) color < LUMINANCE_ALPHA_88_color > ::blue ()	const
{
	return 0;
}


PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE const pfx_color_chanel_t color PFX_COLOR_TEMPLATE_PARAMS ::alpha ()	const
{
	return m_value.m_alpha;
}
template<>
	PFX_INLINE const pfx_color_chanel_sp_t(u16bits_color_t) color < u16bits_color_t > ::alpha ()	const
{
	return ((m_value & 0xF0) * 17 );
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(u8bits_color_t) color < u8bits_color_t > ::alpha ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(ALPHA_8_color) color < ALPHA_8_color > ::alpha ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(LUMINANCE_8_color) color < LUMINANCE_8_color > ::alpha ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(float_RGB_color) color < float_RGB_color > ::alpha ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(RBG8_color) color < RBG8_color > ::alpha ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(RGB_565_color) color < RGB_565_color > ::alpha ()	const
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE const pfx_color_chanel_t color PFX_COLOR_TEMPLATE_PARAMS ::luminance () const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(LUMINANCE_8_color) color < LUMINANCE_8_color > ::luminance () const
{
	return m_value.m_luminance;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(LUMINANCE_ALPHA_88_color) color < LUMINANCE_ALPHA_88_color > ::luminance () const
{
	return m_value.m_luminance;
}

//
//PFX_INLINE void red (const color_chanel_t chanel_value);
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE void color PFX_COLOR_TEMPLATE_PARAMS ::red (const pfx_color_chanel_t chanel_value)
{
	m_value.m_red = chanel_value;
}

template<>
PFX_INLINE void color < bitfield_t > ::red (const pfx_color_chanel_sp_t(bitfield_t) chanel_value)
{
	 m_value &= ~(0xFF000000);
	 m_value |= (((bitfield_t)chanel_value & 0xFF) << 24);
}

template<>
PFX_INLINE void color < u16bits_color_t > ::red (const pfx_color_chanel_sp_t(u16bits_color_t) chanel_value)
{
	m_value &= ~(0xF000);
	m_value |= (((u16bits_color_t)chanel_value  << 8) & 0xF000);
}
template<>
PFX_INLINE void color < u8bits_color_t > ::red (const pfx_color_chanel_sp_t(u8bits_color_t) chanel_value)
{
	;
}

template<>
PFX_INLINE void color < ALPHA_8_color > ::red (const pfx_color_chanel_sp_t(ALPHA_8_color) chanel_value)
{
	;
}
template<>
PFX_INLINE void color < LUMINANCE_8_color > ::red (const pfx_color_chanel_sp_t(LUMINANCE_8_color) chanel_value)
{
	;
}
template<>
PFX_INLINE void color < LUMINANCE_ALPHA_88_color > ::red (const pfx_color_chanel_sp_t(LUMINANCE_ALPHA_88_color) chanel_value)
{
	;
}

//////////////////////////////////////////////////////////////////////////
//PFX_INLINE void green (const color_chanel_t chanel_value);
PFX_COLOR_TEMPLATE_DEFINES
	PFX_INLINE void color PFX_COLOR_TEMPLATE_PARAMS ::green (const pfx_color_chanel_t chanel_value)
{
	m_value.m_green = chanel_value;
}

template<>
	PFX_INLINE void color < bitfield_t > ::green (const pfx_color_chanel_sp_t( bitfield_t ) chanel_value)
{
	m_value &= ~(0xFF0000);
	m_value |= (((bitfield_t)chanel_value & 0xFF) << 16);
}

template<>
	PFX_INLINE void color < u16bits_color_t > ::green (const pfx_color_chanel_sp_t(u16bits_color_t) chanel_value)
{
	m_value &= ~(0xF00);
	m_value |= (((u16bits_color_t)chanel_value << 4) & 0xF00);
}
template<>
	PFX_INLINE void color < u8bits_color_t > ::green (const pfx_color_chanel_sp_t(u8bits_color_t) chanel_value)
{
	;
}

template<>
	PFX_INLINE void color < ALPHA_8_color > ::green (const pfx_color_chanel_sp_t(ALPHA_8_color) chanel_value)
{
	;
}
template<>
	PFX_INLINE void color < LUMINANCE_8_color > ::green (const pfx_color_chanel_sp_t(LUMINANCE_8_color) chanel_value)
{
	;
}
template<>
	PFX_INLINE void color < LUMINANCE_ALPHA_88_color > ::green (const pfx_color_chanel_sp_t(LUMINANCE_ALPHA_88_color) chanel_value)
{
	;
}



//PFX_INLINE void blue (const color_chanel_t chanel_value);
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE void color PFX_COLOR_TEMPLATE_PARAMS ::blue (const pfx_color_chanel_t chanel_value)
{
	m_value.blue = chanel_value;
}

template<>
PFX_INLINE void color < bitfield_t > ::blue (const pfx_color_chanel_sp_t(bitfield_t) chanel_value)
{
	m_value &= ~(0xFF00);
	m_value |= (((bitfield_t)chanel_value & 0xFF) << 8);
}

template<>
	PFX_INLINE void color < u16bits_color_t > ::blue (const pfx_color_chanel_sp_t(u16bits_color_t) chanel_value)
{
	m_value &= ~(0xF0);
	m_value |= (((u16bits_color_t)chanel_value) & 0xF0);
}
template<>
	PFX_INLINE void color < u8bits_color_t > ::blue (const pfx_color_chanel_sp_t(u8bits_color_t) chanel_value)
{
	;
}

template<>
	PFX_INLINE void color < ALPHA_8_color > ::blue (const pfx_color_chanel_sp_t(ALPHA_8_color) chanel_value)
{
	;
}
template<>
	PFX_INLINE void color < LUMINANCE_8_color > ::blue (const pfx_color_chanel_sp_t(LUMINANCE_8_color) chanel_value)
{
	;
}
template<>
	PFX_INLINE void color < LUMINANCE_ALPHA_88_color > ::blue (const pfx_color_chanel_sp_t(LUMINANCE_ALPHA_88_color) chanel_value)
{
	;
}
//////////////////////////////////////////////////////////////////////////
//PFX_INLINE void alpha (const color_chanel_t chanel_value);
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE void color PFX_COLOR_TEMPLATE_PARAMS ::alpha (const pfx_color_chanel_t chanel_value)
{
	m_value.m_alpha = chanel_value;
}

template<>
	PFX_INLINE void color < bitfield_t > ::alpha (const pfx_color_chanel_sp_t(bitfield_t) chanel_value)
{
	m_value &= ~(0xFF);
	m_value |= ((bitfield_t)chanel_value & 0xFF);
}

template<>
	PFX_INLINE void color < u16bits_color_t > ::alpha (const pfx_color_chanel_sp_t(u16bits_color_t) chanel_value)
{
	m_value &= ~(0xF);
	m_value |= ((u16bits_color_t)(chanel_value >> 4) & 0xF);
}
template<>
	PFX_INLINE void color < u8bits_color_t > ::alpha (const pfx_color_chanel_sp_t(u8bits_color_t) chanel_value)
{
	;
}
template<>
PFX_INLINE void color < LUMINANCE_8_color > ::alpha (const pfx_color_chanel_sp_t(LUMINANCE_8_color) chanel_value)
{
	;
}

//////////////////////////////////////////////////////////////////////////
//PFX_INLINE void luminance (const color_chanel_t chanel_value);
PFX_COLOR_TEMPLATE_DEFINES
	PFX_INLINE void color PFX_COLOR_TEMPLATE_PARAMS ::luminance (const pfx_color_chanel_t chanel_value)
{
	;
}

template<>
PFX_INLINE void color < LUMINANCE_8_color > ::luminance (const pfx_color_chanel_sp_t(LUMINANCE_8_color) chanel_value)
{
	m_value.m_luminance = chanel_value;
}

template<>
PFX_INLINE void color < LUMINANCE_ALPHA_88_color > ::luminance (const pfx_color_chanel_sp_t(LUMINANCE_ALPHA_88_color) chanel_value)
{
	m_value.m_luminance = chanel_value;
}

PECKER_END

#endif			//PFX_COLOR_H_
