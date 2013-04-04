/*
 * pecker_render_buffer.h
 *
 *  Created on: 2013-3-17
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_render_buffer.h"


PECKER_BEGIN

//HEnum Ipecker_render_buffer::get_buffer_type()
//{
//	return RENDER_BUFFER_TYPE;
//}

HEnum Ipecker_color_buffer::get_frame_buffer_object_type() const
{
	return COLOR_BUFFER_TYPE;
}

HEnum Ipecker_depth_buffer::get_frame_buffer_object_type() const
{
	return DEPTH_BUFFER_TYPE;
}

HEnum Ipecker_stencil_buffer::get_frame_buffer_object_type() const
{
	return STENCIL_BUFFER_TYPE;
}

PECKER_END

