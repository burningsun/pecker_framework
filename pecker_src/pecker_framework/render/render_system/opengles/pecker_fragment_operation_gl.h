/*
 * pecker_fragment_operation_gl.h
 *
 *  Created on: 2013-4-4
 *      Author: ¿Ó’Ú≥«  £® cut / cutxyz£©
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_FRAME_BUFFER_GL_H_
#define  PECKER_FRAME_BUFFER_GL_H_

#include "pecker_opengles_object.h"
#include "../pecker_fragment_operation.h"

PECKER_BEGIN

//#define MAX_COLOR_ATTACHMENT_GLES2 1
//#define MAX_DEPTH_ATTACHMENT_GLES2 1
//#define MAX_STENCIL_ATTACHMENT_GLES2 1
//
//class pecker_frame_buffer_gles2 : public Ipecker_frame_buffer,public virtual pecker_opengles_v2_object
//{
//private:
//	UInt _M_gpu_target;
//public:
//	pecker_frame_buffer_gles2();
//	~pecker_frame_buffer_gles2();
//	HResult allocate_buffer_from_gpu_ram();
//	HResult release_buffer_from_gpu_ram();
//	HResult attach_render_buffer(Ipecker_render_buffer* prender_buffer,HEnum attach_index = 0);
//	HResult attach_texture(Ipecker_texture* ptexture,HEnum attach_index = 0);//,HEnum face_type = 0,nSize zoffset = 0);
//	HResult attach_frame_buffer_object(Ipecker_frame_buffer_object* pframe_buffer_object,HEnum attach_index = 0);
//	HEnum check_status() const;
//public:
//	virtual UInt get_object_location() const;
//};


PECKER_END

#endif //PECKER_FRAME_BUFFER_GL_H_