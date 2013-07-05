/*
 * pecker_opengles_object.cpp
 *
 *  Created on: 2013-3-6
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_opengles_object.h"
#include <GLES2/gl2.h>
PECKER_BEGIN


const pecker_render_system_info & pecker_opengles_v2_object::get_render_system_info(pecker_render_system_info PARAM_IN &system_info) const
{
	system_info._M_system_type = OPENGLES_RENDER_SYSTEM;
	system_info._M_version_part1 = 2;
	system_info._M_version_part2 = 0;
	return system_info;
}

UInt pecker_opengles_v2_object::get_object_location() const
{
	return 0;
}

HResult pecker_opengles_v2_object::get_last_error_code()
{
	UInt uerror_code = ::glGetError();
	if (GL_NO_ERROR != uerror_code)
	{
		uerror_code = -(uerror_code - 0x500) - 1;
	}
	return uerror_code;
}

const pecker_render_system_info & pecker_opengles_v3_object::get_render_system_info(pecker_render_system_info PARAM_IN &system_info) const
{
	system_info._M_system_type = OPENGLES_RENDER_SYSTEM;
	system_info._M_version_part1 = 3;
	system_info._M_version_part2 = 0;
	return system_info;
}

UInt pecker_opengles_v3_object::get_object_location() const
{
	return 0;
}

HResult pecker_opengles_v3_object::get_last_error_code()
{
	UInt uerror_code = ::glGetError();
	if (GL_NO_ERROR != uerror_code)
	{
		uerror_code = -(uerror_code - 0x500) - 1;
	}
	return uerror_code;
}


PECKER_END