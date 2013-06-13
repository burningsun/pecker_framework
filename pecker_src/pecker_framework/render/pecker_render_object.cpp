/*
 * pecker_render_object.cpp
 *
 *  Created on: 2013-3-6
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_render_object.h"
#include <typeinfo>
#include <stdlib.h>

PECKER_BEGIN

pecker_render_object::pecker_render_object() : _M_reference_count(0)
{

}

pecker_render_object::~pecker_render_object()
{
	_M_reference_count = 0;
}

const render_string & pecker_render_object::toString(render_string P_IN &string_input) const
{
	const char* pstring_chars = typeid(*this).name();
	nSize string_len = strlen(pstring_chars);
	string_input.init(pstring_chars,string_len);
	return string_input;
}

const pecker_render_system_info &pecker_render_object::get_render_system_info(pecker_render_system_info P_IN &system_info) const
{
	system_info._M_system_type = UNKNOWN_RENDER_SYSTEM;
	system_info._M_version_part1 = 0;
	system_info._M_version_part2 = 0;
	return system_info;
}

pecker_render_object* pecker_render_object::get_this_reference()
{
	++_M_reference_count;
	return this;
}

HResult pecker_render_object::release_this_reference()
{
	--_M_reference_count;
	if (_M_reference_count <= 0)
	{
		this->~pecker_render_object();
	}
	return P_OK;
}



PECKER_END