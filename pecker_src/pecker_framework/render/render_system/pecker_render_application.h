/*
 * pecker_render_application.h
 *
 *  Created on: 2013-3-14
 *      Author: ¿Ó’Ú≥«  £® cut / cutxyz£©
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_RENDER_APPLICATION_H_
#define PECKER_RENDER_APPLICATION_H_

#include "../pecker_render_object.h"

PECKER_BEGIN

PeckerInterface Ipecker_render_application
{
	virtual ~Ipecker_render_application(){;}
	virtual HResult render() = 0;
};

class pecker_render_program_app
{
public:
	virtual ~pecker_render_program_app();
	static HResult render_process(Ipecker_render_application* prender_app/*,other params*/ );
};

PECKER_END

#endif //PECKER_RENDER_APPLICATION_H_