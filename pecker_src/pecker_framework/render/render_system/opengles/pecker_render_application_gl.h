/*
 * pecker_render_application_gl.h
 *
 *  Created on: 2013-4-4
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef  PECKER_RENDER_APPLICATION_GL_H_
#define PECKER_RENDER_APPLICATION_GL_H_

#include "pecker_opengles_object.h"
#include "../pecker_render_application.h"

PECKER_BEGIN

class  pecker_render_application_gles2 : public Ipecker_render_application,public virtual pecker_opengles_v2_object
{
private:

public:
	pecker_render_application_gles2();
	virtual ~pecker_render_application_gles2();
	//virtual UInt get_object_location() const;
public:
	HResult render();
	HResult set_draw_params();
	//HResult attach_vertex_buffer();
	//HResult attach_index_buffer();
	//HResult attach_vertexindex_buffer();
	//HResult attach_texture();
	//HResult attach_render_buffer();

};

PECKER_END

#endif //PECKER_RENDER_APPLICATION_GL_H_