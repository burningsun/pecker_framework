/*
 * pecker_render_application.h
 *
 *  Created on: 2013-3-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_RENDER_APPLICATION_H_
#define PECKER_RENDER_APPLICATION_H_

#include "../pecker_render_object.h"
#include "pecker_buffer.h"
#include "pecker_texture.h"

PECKER_BEGIN

//struct render_draw_params
//{
//
//};


PeckerInterface Ipecker_render_application
{
	virtual ~Ipecker_render_application(){;}

	virtual HResult render() = 0;
	//virtual HResult set_draw_params(render_draw_params) = 0;
	//virtual HResult attach_vertex_buffer() = 0;
	//virtual HResult attach_index_buffer() = 0;
	//virtual HResult attach_vertexindex_buffer_collection() = 0;
	//virtual HResult attach_texture();
};

class pecker_render_program_app
{
public:
	virtual ~pecker_render_program_app();
	static HResult render_process(Ipecker_render_application* prender_app/*,other params*/ );
};

PECKER_END

#endif //PECKER_RENDER_APPLICATION_H_