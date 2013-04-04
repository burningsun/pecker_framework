/*
 * pecker_render_application.cpp
 *
 *  Created on: 2013-3-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */


#include "pecker_render_application.h"

PECKER_BEGIN
pecker_render_program_app::~pecker_render_program_app()
{

}
HResult pecker_render_program_app::render_process(Ipecker_render_application* prender_app )
{
	if (prender_app)
	{
		return prender_app->render();
	}
	else
	{
		return P_ERR;
	}
	
}


PECKER_END

