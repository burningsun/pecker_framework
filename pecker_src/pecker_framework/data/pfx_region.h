﻿/*
 * pfx_region.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_REGION_H_
#define		PFX_REGION_H_

#include "../pfx_defines.h"

PECKER_BEGIN

template <typename rect_size_value >
struct rectangle_size
{
	rect_size_value m_width;
	rect_size_value m_height;

	rectangle_size() : m_width(0), m_height(0){ ; }
	rectangle_size(rect_size_value w, rect_size_value h) :
		 m_width(w), m_height(h)
	{
		;
	}
};

template <typename pos_value >
struct point_locate
{
	pos_value m_xpos;
	pos_value m_ypos;

	point_locate() : m_xpos(0), m_ypos(0){ ; }
	point_locate(pos_value x, pos_value y) :
		m_xpos(x), m_ypos(y)
	{
		;
	}
};

typedef rectangle_size< usize__t > rect_size_t;
typedef rectangle_size< float_t > rect_sizef_t;
typedef point_locate< nsize__t > pointi_t;
typedef point_locate< float_t > pointf_t;

typedef struct st_screen_info
{
	rect_size_t m_screen_size;
	rect_size_t m_screen_dpi;
}screen_info_t;

template <typename rect_pos_value >
struct rectangle_region
{
	rect_pos_value m_x;
	rect_pos_value m_y;
	rect_pos_value m_width;
	rect_pos_value m_height;

	rectangle_region ():m_x (0),m_y(0),m_width(0),m_height(0){;}
	rectangle_region (rect_pos_value x, rect_pos_value y, rect_pos_value w, rect_pos_value h):
	m_x (x),m_y(y),m_width(w),m_height(h){;}
};

typedef rectangle_region< sint_t > viewport_rect_t;
typedef rectangle_region< sint_t > int_rect_t;

template < typename linear_pos_value >
struct linear_region
{
	linear_pos_value m_offset;

};

PECKER_END

#endif			//PFX_REGION_H_
