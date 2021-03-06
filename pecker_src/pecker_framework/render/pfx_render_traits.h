﻿/*
 * pfx_render_traits.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDER_TRAITS_H_
#define		PFX_RENDER_TRAITS_H_

#include "../include/config"

PECKER_BEGIN

template < typename color_value_type >
struct color_reference_type
{
	typedef typename color_value_type::value_type value_type;
};
template <>
struct color_reference_type < bitfield_t >
{
	typedef u8_t value_type;
};
template <>
struct color_reference_type < u16_t >
{
	typedef u16_t value_type;
};
template <>
struct color_reference_type < u8_t >
{
	typedef u8_t value_type;
};

PECKER_END

#endif			//PFX_RENDER_TRAITS_H_
