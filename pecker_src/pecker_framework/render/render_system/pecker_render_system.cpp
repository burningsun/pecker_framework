/*
 * pecker_render_system.cpp
 *
 *  Created on: 2013-4-30
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_render_system.h"
#include "opengles/pecker_render_system_gl.h"
PECKER_BEGIN
Ipecker_render_system* pecker_render_system_factory::create_render_system(const pecker_string &render_system_name)
{
	if (0 == render_system_name.compare("opengl es 2.0",strlen("opengl es 2.0")))
	{
		return new pecker_render_system_gles2();
	}
	return null;
}
void pecker_render_system_factory::release_render_system(Ipecker_render_system* &prender_system)
{
	if (prender_system)
	{
		delete prender_system;
		prender_system = null;
	}
}


PECKER_END

