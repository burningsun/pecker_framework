/*
 * pecker_texture.cpp
 *
 *  Created on: 2013-3-17
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_texture.h"

PECKER_BEGIN

HEnum Ipecker_texture::get_frame_buffer_object_type() const
{
	return TEXTURE_BUFFER_TYPE;
}

HEnum Ipecker_texture2d::get_texture_type() const
{
	return TEXTURE_2D_TYPE;
}

HEnum Ipecker_texture_cube::get_texture_type() const
{
	return TEXTURE_CUBE_TYPE;
}

PECKER_END
