/*
 * pfx_region.h
 *
 *  Created on: 2013-8-25
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_REGION_H_
#define		PFX_REGION_H_

#include "../pfx_defines.h"

PECKER_BEGIN

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

typename < typename linear_pos_value >
struct linear_region
{
	linear_pos_value m_offset;

};

PECKER_END

#endif			//PFX_REGION_H_
