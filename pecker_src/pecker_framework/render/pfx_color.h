/*
 * pfx_color.h
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

	PFX_RGB_FLOAT_FMT,
	PFX_RGB8_FMT,
	PFX_RGB_565_FMT,

	PFX_ALPHA_8_FMT,
	PFX_LUMINANCE_8_FMT,
	PFX_LUMINANCE_ALPHA_88_FMT,

	PFX_UNKNOW_COLOR_FMT,
	PFX_COLOR_FORMAT_COUNT
}PFX_COLOR_FORMAT_TYPE_t;

template < const pfx_enum_int_t color_format >
struct PFX_DATA_TEMPALE_API color_internal_format
{
	static  PFX_INLINE pfx_enum_int_t get_internal_format ()
	{
		return PFX_UNKNOWN_COLOR_INFMT;
	}
};
#define COLOR_INTERNAL_FORMAT_TRAITS(FORMAT,INTERANL_FORMAT) \
template <  >\
struct PFX_DATA_TEMPALE_API color_internal_format < FORMAT >\
{\
	static  PFX_INLINE pfx_enum_int_t get_internal_format ()\
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

typedef pfx_bitfield_t		pfx_bits_color;
typedef pfx_u16_t			pfx_16bits_color;
typedef pfx_u8_t				pfx_8bits_color;

struct pfx_float_RGBA_color
{
	typedef pfx_float_t value_type;

	pfx_float_t m_red;
	pfx_float_t m_green;
	pfx_float_t m_blue;
	pfx_float_t m_alpha;
};

struct pfx_float_RGB_color
{
	typedef pfx_float_t value_type;

	pfx_float_t m_red;
	pfx_float_t m_green;
	pfx_float_t m_blue;
};

struct pfx_RGBA8_color
{
	typedef pfx_u8_t value_type;

	unsigned m_red		:8;
	unsigned m_green	:8;
	unsigned m_blue		:8;
	unsigned m_alpha	:8;
};

struct pfx_RBG8_color
{
	typedef pfx_u8_t value_type;

	unsigned m_red		:8;
	unsigned m_green	:8;
	unsigned m_blue		:8;
	unsigned m_alpha	:8;
};

struct pfx_RGBA_4444_color
{
	typedef pfx_u8_t value_type;

	unsigned m_red		:4;
	unsigned m_green	:4;
	unsigned m_blue		:4;
	unsigned m_alpha	:4;
};

struct pfx_RGBA_5551_color
{
	typedef pfx_u8_t value_type;

	unsigned m_red		:5;
	unsigned m_green	:5;
	unsigned m_blue		:5;
	unsigned m_alpha	:1;
};

struct pfx_RGB_565_color
{
	typedef pfx_u8_t value_type;

	unsigned m_red		:5;
	unsigned m_green	:6;
	unsigned m_blue		:5;
};

struct pfx_ALPHA_8_color
{
	typedef pfx_u8_t value_type;

	pfx_u8_t m_alpha;
};

struct pfx_LUMINANCE_8_color
{
	typedef pfx_u8_t value_type;

	pfx_u8_t m_luminance;
};

struct pfx_LUMINANCE_ALPHA_88_color
{
	typedef pfx_u8_t value_type;

	pfx_u8_t m_luminance;
	pfx_u8_t m_alpha;
};

// 通过 PFX_COLOR_FORMAT_TYPE_t 和
//容器color_format_reference获取想要的颜色结构
template < const pfx_enum_int_t color_format >
struct PFX_DATA_TEMPALE_API color_value_reference
{
	// 通用情况下是PFX_UNKNOW_COLOR_FMT
	typedef pfx_bits_color	color_value;
};

//容器特例化
template <  >
struct color_value_reference < PFX_RGBA_FLOAT_FMT >
{
	typedef pfx_float_RGBA_color	color_value;
};
template <  >
struct color_value_reference < PFX_RGB_FLOAT_FMT >
{
	typedef pfx_float_RGB_color color_value;
};
template <  >
struct color_value_reference < PFX_RGBA8_FMT >
{
	typedef pfx_RGBA8_color	color_value;
};
template <  >
struct color_value_reference < PFX_RGB8_FMT >
{
	typedef pfx_RGBA8_color color_value;
};
template <  >
struct color_value_reference < PFX_RGBA_4444_FMT >
{
	typedef pfx_RGBA_4444_color	color_value;
};
template <  >
struct color_value_reference < PFX_RGBA_5551_FMT >
{
	typedef pfx_RGBA_5551_color	color_value;
};
template <  >
struct color_value_reference < PFX_RGB_565_FMT >
{
	typedef pfx_RGB_565_color	color_value;
};
template <  >
struct color_value_reference < PFX_ALPHA_8_FMT >
{
	typedef pfx_ALPHA_8_color	color_value;
};
template <  >
struct color_value_reference < PFX_LUMINANCE_8_FMT >
{
	typedef pfx_LUMINANCE_8_color	color_value;
};
template <  >
struct color_value_reference < PFX_LUMINANCE_ALPHA_88_FMT >
{
	typedef pfx_LUMINANCE_ALPHA_88_color	color_value;
};

template< const pfx_enum_int_t  color_format >
struct color_format_size
{
	static PFX_INLINE  pfx_nsize_t SIZE()
	{
		return sizeof (typename color_value_reference < color_format >::color_value);
	}
};

// 颜色类
template < class color_value >
struct PFX_DATA_TEMPALE_API pfx_color
{
	typedef color_value value_type;
	typedef typename color_reference_type < color_value >::value_type color_chanel_t; 

	color_value	m_value;

	pfx_color ();
	pfx_color (const color_chanel_t luminance,const color_chanel_t alpha);
	pfx_color (const color_chanel_t red, const color_chanel_t green, 
		const color_chanel_t blue, const color_chanel_t alpha);
	pfx_color (const color_chanel_t alpha);
	pfx_color (const color_value& color_val);
	pfx_color (pfx_bitfield_t RGBA);
	pfx_color (const pfx_color< color_value >& other);

	// 32bits
	PFX_INLINE pfx_bitfield_t to_RGBA_bits_format () const;
	// 24bits
	PFX_INLINE pfx_bitfield_t to_RGB_bits_format () const;

	PFX_INLINE  void set_color(const color_chanel_t red, const color_chanel_t green, 
		const color_chanel_t blue, const color_chanel_t alpha);

	PFX_INLINE  void set_color(const color_chanel_t luminance);

	PFX_INLINE void set_color (const color_value& color_val);
	PFX_INLINE void set_color_by_bits (pfx_bitfield_t RGBA);
	PFX_INLINE void set_color (const pfx_color< color_value >& other);

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

template < const pfx_enum_int_t color_format >
struct PFX_DATA_TEMPALE_API color_reference
{
	typedef pfx_color < typename  color_value_reference< color_format >::color_value	 >	color_t;
};















///codes
/////////////////////////////////////////////////////////////////////////
#define pfx_color_chanel_t typename color_reference_type < color_value >::value_type
#define PFX_COLOR_TEMPLATE_DEFINES template < class color_value >
#define PFX_COLOR_TEMPLATE_PARAMS < color_value >
#define pfx_color_chanel_sp_t(color_value) color_reference_type < color_value >::value_type

//////////////////////////////////////////////////////////////////////////
PFX_COLOR_TEMPLATE_DEFINES
pfx_color PFX_COLOR_TEMPLATE_PARAMS :: pfx_color ()
{ 
	set_color (0,0,0,0);
	set_color (0);
}
template<>
pfx_color < pfx_bits_color > :: pfx_color() : m_value(0)
{;}
template<>
pfx_color < pfx_16bits_color > :: pfx_color() : m_value(0)
{;}
template<>
pfx_color < pfx_8bits_color > :: pfx_color() : m_value(0)
{;}

//////////////////////////////////////////////////////////////////////////
//pfx_color (const color_chanel_t luminance,const color_chanel_t alpha)
PFX_COLOR_TEMPLATE_DEFINES
pfx_color PFX_COLOR_TEMPLATE_PARAMS :: pfx_color(const color_chanel_t luminance,const color_chanel_t alpha)
{
	set_color (0,0,0,alpha);
	set_color (luminance);
}
template<>
pfx_color < pfx_bits_color > :: pfx_color(const color_chanel_t luminance,const color_chanel_t alpha) : 
m_value((((pfx_bits_color)luminance << 8)& 0xFF00)|(((pfx_bits_color)alpha)&0xFF))
{;}
template<>
pfx_color < pfx_16bits_color > :: pfx_color(const color_chanel_t luminance,const color_chanel_t alpha) : 
m_value((((pfx_bits_color)luminance << 8) & 0xFF00)|((pfx_bits_color)alpha&0xFF))
{;}
template<>
pfx_color < pfx_8bits_color > :: pfx_color(const color_chanel_t luminance,const color_chanel_t alpha) : m_value(0)
{;}
//
//	pfx_color (const color_chanel_t red, const color_chanel_t green, 
//	const color_chanel_t blue, const color_chanel_t alpha)
PFX_COLOR_TEMPLATE_DEFINES
pfx_color PFX_COLOR_TEMPLATE_PARAMS :: pfx_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	set_color (red,green,blue,alpha);
	set_color (0);
}
template<>
pfx_color < pfx_bits_color > :: pfx_color(const color_chanel_t red, const color_chanel_t green, const color_chanel_t blue, const color_chanel_t alpha): 
m_value((((pfx_bits_color)red << 24) & 0xFF000000)|(((pfx_bits_color)green << 16) & 0xFF0000)|(((pfx_bits_color)blue << 8) & 0xFF00)|((pfx_bits_color)alpha &0xFF))
{;}
template<>
	pfx_color < pfx_16bits_color > :: pfx_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha) : 
m_value((((pfx_bits_color)red << 12) & 0xF000)|(((pfx_bits_color)green << 8) & 0xF00)|(((pfx_bits_color)blue << 4) & 0xF0)|((pfx_bits_color)alpha &0xF))
{;}
template<>
pfx_color < pfx_8bits_color > :: pfx_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha) : m_value(0)
{;}

//////////////////////////////////////////////////////////////////////////
//pfx_color (const  const color_chanel_t alpha);
PFX_COLOR_TEMPLATE_DEFINES
pfx_color PFX_COLOR_TEMPLATE_PARAMS :: pfx_color (const color_chanel_t alpha) 
{
	set_color (0,0,0,alpha);
	set_color (0);
}
template<>
pfx_color < pfx_bits_color > :: pfx_color(const color_chanel_t alpha) : 
m_value(((pfx_bits_color)alpha)&0xFF)
{;}
template<>
pfx_color < pfx_16bits_color > :: pfx_color(const color_chanel_t alpha) : 
m_value(((pfx_bits_color)alpha >> 4)&0xF)
{;}
template<>
pfx_color < pfx_8bits_color > :: pfx_color (const color_chanel_t alpha) : m_value (0)
{;}

//////////////////////////////////////////////////////////////////////////
PFX_COLOR_TEMPLATE_DEFINES
pfx_color PFX_COLOR_TEMPLATE_PARAMS :: pfx_color (const color_value& color_val) : m_value (color_val)
{;}
//////////////////////////////////////////////////////////////////////////
PFX_COLOR_TEMPLATE_DEFINES
pfx_color PFX_COLOR_TEMPLATE_PARAMS :: pfx_color (pfx_bitfield_t RGBA) : 
pfx_color PFX_COLOR_TEMPLATE_PARAMS ( (const color_chanel_t )((RGBA >> 24)&0xFF),
	const color_chanel_t ((RGBA >> 16)&0xFF) ,
	const color_chanel_t ((RGBA >> 8)&0xFF),
	const color_chanel_t (RGBA&0xFF))
{
	;
}
//
//pfx_color (const pfx_color< color_value >& other);
PFX_COLOR_TEMPLATE_DEFINES
pfx_color PFX_COLOR_TEMPLATE_PARAMS :: pfx_color (const pfx_color< color_value >& other)
{
	if (this != &other)
	{
		m_value = other.m_value;
	}
}

//// 32bits
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE pfx_bitfield_t pfx_color PFX_COLOR_TEMPLATE_PARAMS ::to_RGBA_bits_format () const
{
	return m_value;
}

template<>
PFX_INLINE pfx_bitfield_t pfx_color < pfx_16bits_color > ::to_RGBA_bits_format () const
{
	return (((pfx_bitfield_t)(m_value & 0xF000) * 17) << 12 )|
		(((pfx_bitfield_t)(m_value & 0xF00)*17) << 8 )|
		(((pfx_bitfield_t)(m_value & 0xF0)*17) << 4 )|
		(((pfx_bitfield_t)(m_value & 0xF)*17));
}

template<>
PFX_INLINE pfx_bitfield_t pfx_color < pfx_float_RGBA_color > ::to_RGBA_bits_format () const
{
	return ((pfx_bitfield_t)(m_value.m_red * 255.0f) << 24 )|
				((pfx_bitfield_t)(m_value.m_green * 255.0f) << 16 )|
				((pfx_bitfield_t)(m_value.m_blue * 255.0f) << 8 )|
				((pfx_bitfield_t)(m_value.m_alpha * 255.0f) );
}

template<>
PFX_INLINE pfx_bitfield_t pfx_color < pfx_float_RGB_color > ::to_RGBA_bits_format () const
{
	return ((pfx_bitfield_t)(m_value.m_red * 255.0f) << 24 )|
		((pfx_bitfield_t)(m_value.m_green * 255.0f) << 16 )|
		((pfx_bitfield_t)(m_value.m_blue * 255.0f) << 8 ) | 0xFF;
}

template<>
PFX_INLINE pfx_bitfield_t pfx_color < pfx_RGBA8_color > ::to_RGBA_bits_format () const
{
	return ((pfx_bitfield_t)(m_value.m_red) << 24 )|
		((pfx_bitfield_t)(m_value.m_green) << 16 )|
		((pfx_bitfield_t)(m_value.m_blue) << 8 )|
		((pfx_bitfield_t)(m_value.m_alpha) );
}

template<>
PFX_INLINE pfx_bitfield_t pfx_color < pfx_RBG8_color > ::to_RGBA_bits_format () const
{
	return ((pfx_bitfield_t)(m_value.m_red) << 24 )|
		((pfx_bitfield_t)(m_value.m_green) << 16 )|
		((pfx_bitfield_t)(m_value.m_blue) << 8 ) | 0xFF;
}

template<>
PFX_INLINE pfx_bitfield_t pfx_color < pfx_RGBA_4444_color > ::to_RGBA_bits_format () const
{
	return (((pfx_bitfield_t)(m_value.m_red) * 17) << 24 )|
		(((pfx_bitfield_t)(m_value.m_green)*17) << 16 )|
		(((pfx_bitfield_t)(m_value.m_blue)*17) << 8 )|
		(((pfx_bitfield_t)(m_value.m_alpha)*17));
}

template<>
PFX_INLINE pfx_bitfield_t pfx_color < pfx_RGBA_5551_color > ::to_RGBA_bits_format () const
{
	return (((pfx_bitfield_t)(m_value.m_red) * 255 / 31) << 24 )|
		(((pfx_bitfield_t)(m_value.m_green)*255/31) << 16 )|
		(((pfx_bitfield_t)(m_value.m_blue)*255/31) << 8 )|
		(((pfx_bitfield_t)(m_value.m_alpha)* 255));
}

template<>
PFX_INLINE pfx_bitfield_t pfx_color < pfx_RGB_565_color > ::to_RGBA_bits_format () const
{
	return (((pfx_bitfield_t)(m_value.m_red) * 255 / 31) << 24 )|
		(((pfx_bitfield_t)(m_value.m_green)*255/63) << 16 )|
		(((pfx_bitfield_t)(m_value.m_blue)*255/31) << 8 )| 0xFF;
}

template<>
PFX_INLINE pfx_bitfield_t pfx_color < pfx_ALPHA_8_color > ::to_RGBA_bits_format () const
{
	return (pfx_bitfield_t)(m_value.m_alpha)* 17;
}

template<>
PFX_INLINE pfx_bitfield_t pfx_color < pfx_LUMINANCE_8_color > ::to_RGBA_bits_format () const
{
	return 0;
}

template<>
PFX_INLINE pfx_bitfield_t pfx_color < pfx_LUMINANCE_ALPHA_88_color > ::to_RGBA_bits_format () const
{
	return (pfx_bitfield_t)(m_value.m_alpha)* 17;
}


//// 24bits
//PFX_INLINE pfx_bitfield_t to_RGB_bits_format () const;
PFX_COLOR_TEMPLATE_DEFINES
	PFX_INLINE pfx_bitfield_t pfx_color PFX_COLOR_TEMPLATE_PARAMS ::to_RGB_bits_format () const
{
	return m_value;
}

template<>
	PFX_INLINE pfx_bitfield_t pfx_color < pfx_16bits_color > ::to_RGB_bits_format () const
{
	return (((pfx_bitfield_t)(m_value & 0xF000) * 17) << 8 )|
		(((pfx_bitfield_t)(m_value & 0xF00)*17) << 4 )|
		(((pfx_bitfield_t)(m_value & 0xF0)*17) );
}

template<>
PFX_INLINE pfx_bitfield_t pfx_color < pfx_float_RGBA_color > ::to_RGB_bits_format () const
{
	return ((pfx_bitfield_t)(m_value.m_red * 255.0f) << 16 )|
		((pfx_bitfield_t)(m_value.m_green * 255.0f) << 8 )|
		((pfx_bitfield_t)(m_value.m_blue * 255.0f));
}

template<>
	PFX_INLINE pfx_bitfield_t pfx_color < pfx_float_RGB_color > ::to_RGB_bits_format () const
{
	return ((pfx_bitfield_t)(m_value.m_red * 255.0f) << 16 )|
		((pfx_bitfield_t)(m_value.m_green * 255.0f) << 8 )|
		((pfx_bitfield_t)(m_value.m_blue * 255.0f));
}

template<>
	PFX_INLINE pfx_bitfield_t pfx_color < pfx_RGBA8_color > ::to_RGB_bits_format () const
{
	return ((pfx_bitfield_t)(m_value.m_red) << 16 )|
		((pfx_bitfield_t)(m_value.m_green) << 8 )|
		((pfx_bitfield_t)(m_value.m_blue));
}

template<>
	PFX_INLINE pfx_bitfield_t pfx_color < pfx_RBG8_color > ::to_RGB_bits_format () const
{
	return ((pfx_bitfield_t)(m_value.m_red) << 16 )|
		((pfx_bitfield_t)(m_value.m_green) << 8 )|
		((pfx_bitfield_t)(m_value.m_blue));
}

template<>
	PFX_INLINE pfx_bitfield_t pfx_color < pfx_RGBA_4444_color > ::to_RGB_bits_format () const
{
	return (((pfx_bitfield_t)(m_value.m_red) * 17) << 16 )|
		(((pfx_bitfield_t)(m_value.m_green)*17) << 8 )|
		(((pfx_bitfield_t)(m_value.m_blue)*17));
}

template<>
	PFX_INLINE pfx_bitfield_t pfx_color < pfx_RGBA_5551_color > ::to_RGB_bits_format () const
{
	return (((pfx_bitfield_t)(m_value.m_red) * 255 / 31) << 16 )|
		(((pfx_bitfield_t)(m_value.m_green)*255/31) << 8 )|
		(((pfx_bitfield_t)(m_value.m_blue)*255/31));
}

template<>
	PFX_INLINE pfx_bitfield_t pfx_color < pfx_RGB_565_color > ::to_RGB_bits_format () const
{
	return (((pfx_bitfield_t)(m_value.m_red) * 255 / 31) << 16 )|
		(((pfx_bitfield_t)(m_value.m_green)*255/63) << 8 )|
		(((pfx_bitfield_t)(m_value.m_blue)*255/31));
}

template<>
	PFX_INLINE pfx_bitfield_t pfx_color < pfx_ALPHA_8_color > ::to_RGB_bits_format () const
{
	return 0;
}

template<>
	PFX_INLINE pfx_bitfield_t pfx_color < pfx_LUMINANCE_8_color > ::to_RGB_bits_format () const
{
	return 0;
}

template<>
	PFX_INLINE pfx_bitfield_t pfx_color < pfx_LUMINANCE_ALPHA_88_color > ::to_RGB_bits_format () const
{
	return 0;
}

//
//PFX_INLINE  void set_color(const color_chanel_t red, const color_chanel_t green, 
//	const color_chanel_t blue, const color_chanel_t alpha);
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE  void pfx_color PFX_COLOR_TEMPLATE_PARAMS :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value  = 0;
}
template<>
PFX_INLINE  void pfx_color < pfx_bits_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value = ((((pfx_bits_color)red << 24) & 0xFF000000)|(((pfx_bits_color)green << 16) & 0xFF0000)|(((pfx_bits_color)blue << 8) & 0xFF00)|((pfx_bits_color)alpha &0xFF));
}

template<>
PFX_INLINE  void pfx_color < pfx_16bits_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha) 
{
	m_value = ((((pfx_bits_color)red << 8) & 0xF000)|(((pfx_bits_color)green << 4) & 0xF00)|(((pfx_bits_color)blue) & 0xF0)|(((pfx_bits_color)alpha >> 4)  &0xF));
}

template<>
PFX_INLINE  void pfx_color < pfx_float_RGBA_color > :: set_color (const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_red		= red;
	m_value.m_green	= green;
	m_value.m_blue		= blue;
	m_value.m_alpha	= alpha;
}
template<>
PFX_INLINE  void pfx_color < pfx_float_RGB_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_red		= red;
	m_value.m_green	= green;
	m_value.m_blue		= blue;
}

template<>
PFX_INLINE  void pfx_color < pfx_RGBA8_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_red		= red;
	m_value.m_green	= green;
	m_value.m_blue		= blue;
	m_value.m_alpha	= alpha;
}
template<>
PFX_INLINE  void pfx_color < pfx_RBG8_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_red		= red;
	m_value.m_green	= green;
	m_value.m_blue		= blue;
}

template<>
PFX_INLINE  void pfx_color < pfx_RGBA_4444_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_red		= red >> 4;
	m_value.m_green	= green >> 4;
	m_value.m_blue		= blue >> 4;
	m_value.m_alpha	= alpha >> 4;
}
template<>
PFX_INLINE  void pfx_color < pfx_RGBA_5551_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha) 
{
	m_value.m_red		= red >> 3;
	m_value.m_green	= green >> 3;
	m_value.m_blue		= blue >> 3;
	m_value.m_alpha	= alpha > 0 ? 1:0;
}
template<>
PFX_INLINE  void pfx_color < pfx_RGB_565_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_red		= red >> 3;
	m_value.m_green	= green >> 2;
	m_value.m_blue		= blue >> 3;
}
template<>
PFX_INLINE  void pfx_color < pfx_ALPHA_8_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_alpha = alpha;
}
template<>
PFX_INLINE  void pfx_color < pfx_LUMINANCE_8_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha){;}
template<>
PFX_INLINE  void pfx_color < pfx_LUMINANCE_ALPHA_88_color > :: set_color(const color_chanel_t red, const color_chanel_t green, 
	const color_chanel_t blue, const color_chanel_t alpha)
{
	m_value.m_alpha = alpha;
}

//
//PFX_INLINE  void set_color(const color_chanel_t luminance);
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE  void pfx_color PFX_COLOR_TEMPLATE_PARAMS :: set_color(const color_chanel_t luminance)
{
	;
}
template<>
	PFX_INLINE  void pfx_color < pfx_LUMINANCE_8_color > :: set_color(const color_chanel_t luminance)
{
	m_value.m_luminance =0;
}
template<>
PFX_INLINE  void pfx_color < pfx_LUMINANCE_ALPHA_88_color > :: set_color(const color_chanel_t luminance)
{
	m_value.m_luminance =0;
}

//
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE  void pfx_color PFX_COLOR_TEMPLATE_PARAMS ::set_color (const color_value& color_val)
{
	m_value = color_val;
}

PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE void pfx_color PFX_COLOR_TEMPLATE_PARAMS ::set_color_by_bits (pfx_bitfield_t RGBA)
{
	set_color( (RGBA&0xFF000000)>>24,  (RGBA&0xFF0000)>>16,  (RGBA&0xFF00)>>8,  RGBA&0xFF );
}

PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE void pfx_color PFX_COLOR_TEMPLATE_PARAMS ::set_color (const pfx_color< color_value >& other)
{
	if (&other != this)
	{
		m_value = other.m_value;
	}
}
//
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE pfx_color_chanel_t* pfx_color PFX_COLOR_TEMPLATE_PARAMS ::get_buffer_reference ()
{
	return (pfx_color_chanel_t*)&m_value;
}
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE const pfx_color_chanel_t* pfx_color PFX_COLOR_TEMPLATE_PARAMS ::get_buffer ()		const
{
	return (const pfx_color_chanel_t*)&m_value;
}

PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE const pfx_color_chanel_t pfx_color PFX_COLOR_TEMPLATE_PARAMS ::red ()	const
{
	return m_value.m_red;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_bitfield_t) pfx_color < pfx_bitfield_t > ::red ()	const
{
	return (m_value & 0xFF000000) >> 24;
}

template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_16bits_color) pfx_color < pfx_16bits_color > ::red ()	const
{
	return ((m_value & 0xF000) * 17 )<< 12;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_8bits_color) pfx_color < pfx_8bits_color > ::red ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_ALPHA_8_color) pfx_color < pfx_ALPHA_8_color > ::red ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_LUMINANCE_8_color) pfx_color < pfx_LUMINANCE_8_color > ::red ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_LUMINANCE_ALPHA_88_color) pfx_color < pfx_LUMINANCE_ALPHA_88_color > ::red ()	const
{
	return 0;
}


//////////////////////////////////////////////////////////////////////////
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE const pfx_color_chanel_t pfx_color PFX_COLOR_TEMPLATE_PARAMS ::green ()	 const
{
	return m_value.m_green;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_16bits_color) pfx_color < pfx_16bits_color > ::green ()	const
{
	return ((m_value & 0xF00) * 17 )<< 8;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_8bits_color) pfx_color < pfx_8bits_color > ::green ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_ALPHA_8_color) pfx_color < pfx_ALPHA_8_color > ::green ()	const
{
	return 0;
}
template<>
	PFX_INLINE const pfx_color_chanel_sp_t(pfx_LUMINANCE_8_color) pfx_color < pfx_LUMINANCE_8_color > ::green ()	const
{
	return 0;
}
template<>
	PFX_INLINE const pfx_color_chanel_sp_t(pfx_LUMINANCE_ALPHA_88_color) pfx_color < pfx_LUMINANCE_ALPHA_88_color > ::green ()	const
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE const pfx_color_chanel_t pfx_color PFX_COLOR_TEMPLATE_PARAMS ::blue () const
{
	return m_value.m_blue;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_16bits_color) pfx_color < pfx_16bits_color > ::blue ()	const
{
	return ((m_value & 0xF0) * 17 )<< 4;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_8bits_color) pfx_color < pfx_8bits_color > ::blue ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_ALPHA_8_color) pfx_color < pfx_ALPHA_8_color > ::blue ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_LUMINANCE_8_color) pfx_color < pfx_LUMINANCE_8_color > ::blue ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_LUMINANCE_ALPHA_88_color) pfx_color < pfx_LUMINANCE_ALPHA_88_color > ::blue ()	const
{
	return 0;
}


PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE const pfx_color_chanel_t pfx_color PFX_COLOR_TEMPLATE_PARAMS ::alpha ()	const
{
	return m_value.m_alpha;
}
template<>
	PFX_INLINE const pfx_color_chanel_sp_t(pfx_16bits_color) pfx_color < pfx_16bits_color > ::alpha ()	const
{
	return ((m_value & 0xF0) * 17 );
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_8bits_color) pfx_color < pfx_8bits_color > ::alpha ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_ALPHA_8_color) pfx_color < pfx_ALPHA_8_color > ::alpha ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_LUMINANCE_8_color) pfx_color < pfx_LUMINANCE_8_color > ::alpha ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_float_RGB_color) pfx_color < pfx_float_RGB_color > ::alpha ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_RBG8_color) pfx_color < pfx_RBG8_color > ::alpha ()	const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_RGB_565_color) pfx_color < pfx_RGB_565_color > ::alpha ()	const
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE const pfx_color_chanel_t pfx_color PFX_COLOR_TEMPLATE_PARAMS ::luminance () const
{
	return 0;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_LUMINANCE_8_color) pfx_color < pfx_LUMINANCE_8_color > ::luminance () const
{
	return m_value.m_luminance;
}
template<>
PFX_INLINE const pfx_color_chanel_sp_t(pfx_LUMINANCE_ALPHA_88_color) pfx_color < pfx_LUMINANCE_ALPHA_88_color > ::luminance () const
{
	return m_value.m_luminance;
}

//
//PFX_INLINE void red (const color_chanel_t chanel_value);
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE void pfx_color PFX_COLOR_TEMPLATE_PARAMS ::red (const pfx_color_chanel_t chanel_value)
{
	m_value.m_red = chanel_value;
}

template<>
PFX_INLINE void pfx_color < pfx_bitfield_t > ::red (const pfx_color_chanel_sp_t(pfx_bitfield_t) chanel_value)
{
	 m_value &= ~(0xFF000000);
	 m_value |= (((pfx_bitfield_t)chanel_value & 0xFF) << 24);
}

template<>
PFX_INLINE void pfx_color < pfx_16bits_color > ::red (const pfx_color_chanel_sp_t(pfx_16bits_color) chanel_value)
{
	m_value &= ~(0xF000);
	m_value |= (((pfx_16bits_color)chanel_value  << 8) & 0xF000);
}
template<>
PFX_INLINE void pfx_color < pfx_8bits_color > ::red (const pfx_color_chanel_sp_t(pfx_8bits_color) chanel_value)
{
	;
}

template<>
PFX_INLINE void pfx_color < pfx_ALPHA_8_color > ::red (const pfx_color_chanel_sp_t(pfx_ALPHA_8_color) chanel_value)
{
	;
}
template<>
PFX_INLINE void pfx_color < pfx_LUMINANCE_8_color > ::red (const pfx_color_chanel_sp_t(pfx_LUMINANCE_8_color) chanel_value)
{
	;
}
template<>
PFX_INLINE void pfx_color < pfx_LUMINANCE_ALPHA_88_color > ::red (const pfx_color_chanel_sp_t(pfx_LUMINANCE_ALPHA_88_color) chanel_value)
{
	;
}

//////////////////////////////////////////////////////////////////////////
//PFX_INLINE void green (const color_chanel_t chanel_value);
PFX_COLOR_TEMPLATE_DEFINES
	PFX_INLINE void pfx_color PFX_COLOR_TEMPLATE_PARAMS ::green (const pfx_color_chanel_t chanel_value)
{
	m_value.m_green = chanel_value;
}

template<>
	PFX_INLINE void pfx_color < pfx_bitfield_t > ::green (const pfx_color_chanel_sp_t( pfx_bitfield_t ) chanel_value)
{
	m_value &= ~(0xFF0000);
	m_value |= (((pfx_bitfield_t)chanel_value & 0xFF) << 16);
}

template<>
	PFX_INLINE void pfx_color < pfx_16bits_color > ::green (const pfx_color_chanel_sp_t(pfx_16bits_color) chanel_value)
{
	m_value &= ~(0xF00);
	m_value |= (((pfx_16bits_color)chanel_value << 4) & 0xF00);
}
template<>
	PFX_INLINE void pfx_color < pfx_8bits_color > ::green (const pfx_color_chanel_sp_t(pfx_8bits_color) chanel_value)
{
	;
}

template<>
	PFX_INLINE void pfx_color < pfx_ALPHA_8_color > ::green (const pfx_color_chanel_sp_t(pfx_ALPHA_8_color) chanel_value)
{
	;
}
template<>
	PFX_INLINE void pfx_color < pfx_LUMINANCE_8_color > ::green (const pfx_color_chanel_sp_t(pfx_LUMINANCE_8_color) chanel_value)
{
	;
}
template<>
	PFX_INLINE void pfx_color < pfx_LUMINANCE_ALPHA_88_color > ::green (const pfx_color_chanel_sp_t(pfx_LUMINANCE_ALPHA_88_color) chanel_value)
{
	;
}



//PFX_INLINE void blue (const color_chanel_t chanel_value);
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE void pfx_color PFX_COLOR_TEMPLATE_PARAMS ::blue (const pfx_color_chanel_t chanel_value)
{
	m_value.blue = chanel_value;
}

template<>
PFX_INLINE void pfx_color < pfx_bitfield_t > ::blue (const pfx_color_chanel_sp_t(pfx_bitfield_t) chanel_value)
{
	m_value &= ~(0xFF00);
	m_value |= (((pfx_bitfield_t)chanel_value & 0xFF) << 8);
}

template<>
	PFX_INLINE void pfx_color < pfx_16bits_color > ::blue (const pfx_color_chanel_sp_t(pfx_16bits_color) chanel_value)
{
	m_value &= ~(0xF0);
	m_value |= (((pfx_16bits_color)chanel_value) & 0xF0);
}
template<>
	PFX_INLINE void pfx_color < pfx_8bits_color > ::blue (const pfx_color_chanel_sp_t(pfx_8bits_color) chanel_value)
{
	;
}

template<>
	PFX_INLINE void pfx_color < pfx_ALPHA_8_color > ::blue (const pfx_color_chanel_sp_t(pfx_ALPHA_8_color) chanel_value)
{
	;
}
template<>
	PFX_INLINE void pfx_color < pfx_LUMINANCE_8_color > ::blue (const pfx_color_chanel_sp_t(pfx_LUMINANCE_8_color) chanel_value)
{
	;
}
template<>
	PFX_INLINE void pfx_color < pfx_LUMINANCE_ALPHA_88_color > ::blue (const pfx_color_chanel_sp_t(pfx_LUMINANCE_ALPHA_88_color) chanel_value)
{
	;
}
//////////////////////////////////////////////////////////////////////////
//PFX_INLINE void alpha (const color_chanel_t chanel_value);
PFX_COLOR_TEMPLATE_DEFINES
PFX_INLINE void pfx_color PFX_COLOR_TEMPLATE_PARAMS ::alpha (const pfx_color_chanel_t chanel_value)
{
	m_value.m_alpha = chanel_value;
}

template<>
	PFX_INLINE void pfx_color < pfx_bitfield_t > ::alpha (const pfx_color_chanel_sp_t(pfx_bitfield_t) chanel_value)
{
	m_value &= ~(0xFF);
	m_value |= ((pfx_bitfield_t)chanel_value & 0xFF);
}

template<>
	PFX_INLINE void pfx_color < pfx_16bits_color > ::alpha (const pfx_color_chanel_sp_t(pfx_16bits_color) chanel_value)
{
	m_value &= ~(0xF);
	m_value |= ((pfx_16bits_color)(chanel_value >> 4) & 0xF);
}
template<>
	PFX_INLINE void pfx_color < pfx_8bits_color > ::alpha (const pfx_color_chanel_sp_t(pfx_8bits_color) chanel_value)
{
	;
}
template<>
PFX_INLINE void pfx_color < pfx_LUMINANCE_8_color > ::alpha (const pfx_color_chanel_sp_t(pfx_LUMINANCE_8_color) chanel_value)
{
	;
}

//////////////////////////////////////////////////////////////////////////
//PFX_INLINE void luminance (const color_chanel_t chanel_value);
PFX_COLOR_TEMPLATE_DEFINES
	PFX_INLINE void pfx_color PFX_COLOR_TEMPLATE_PARAMS ::luminance (const pfx_color_chanel_t chanel_value)
{
	;
}

template<>
PFX_INLINE void pfx_color < pfx_LUMINANCE_8_color > ::luminance (const pfx_color_chanel_sp_t(pfx_LUMINANCE_8_color) chanel_value)
{
	m_value.m_luminance = chanel_value;
}

template<>
PFX_INLINE void pfx_color < pfx_LUMINANCE_ALPHA_88_color > ::luminance (const pfx_color_chanel_sp_t(pfx_LUMINANCE_ALPHA_88_color) chanel_value)
{
	m_value.m_luminance = chanel_value;
}

PECKER_END

#endif			//PFX_COLOR_H_
