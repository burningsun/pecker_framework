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
#include "pecker_gpu_program.h"

PECKER_BEGIN

//PeckerInterface Ipecker_graphic_device
//{
//	virtual ~Ipecker_graphic_device(){;}
//	virtual HResult bind_frame_buffer_object(Ipecker_frame_buffer_object* prender_object) = 0;
//	virtual HResult bind_vertex_buffer(Ipecker_vertex_buffer* pvertex_buffer) = 0;
//	virtual HResult bind_index_buffer(Ipecker_index_buffer* pindex_buffer) = 0;
//	virtual HResult use_gpu_program(Ipecker_gpu_program* pshader_program) = 0;
//	virtual HResult set_object(HEnum object_type,PVoid pobject) = 0;
//	virtual HResult begin() = 0;
//	virtual HResult end() = 0;
//	virtual HResult get_error_info(pecker_string &error_info) = 0;
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