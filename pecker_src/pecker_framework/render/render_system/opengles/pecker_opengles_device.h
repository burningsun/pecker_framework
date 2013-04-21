/*
 * pecker_opengles_device.h
 *
 *  Created on: 2013-3-6
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_OPENGLES_DEVICE_H_
#define PECKER_OPENGLES_DEVICE_H_

#include "pecker_opengles_object.h"
#include "../pecker_render_device.h"

PECKER_BEGIN

class pecker_render_device_gles2 : public Ipecker_render_device, public virtual pecker_opengles_v2_object
{
public:
	pecker_render_device_gles2();
	virtual ~pecker_render_device_gles2();

public:
	Ipecker_gpu_program* create_gpu_program();
	HResult release_gpu_program(Ipecker_gpu_program* &pgpu_program);

	Ipecker_graphic_buffer* create_buffer(HEnum buffer_type);
	HResult release_buffer(Ipecker_graphic_buffer* &pbuffer);

	Ipecker_frame_buffer_object* create_frame_buffer_object(HEnum object_type,HEnum detail_type);
	HResult release_frame_buffer_object(Ipecker_frame_buffer_object* &pobject);

	Ipecker_frame_buffer* create_frame_buffer();
	HResult release_frame_buffer(Ipecker_frame_buffer* &pframe_buffer);

	HResult set_viewport(SInt x,SInt y,nSize width,nSize height);

	HResult set_const_value(HEnum name,HEnum operation_type,nSize nvalue_count,const PVoid P_IN value_);
	HResult set_value(HEnum name,HEnum operation_type,nSize nvalue_count,PVoid P_IN value_);

	HResult get_device_info(HEnum info_type,pecker_string& P_OUT strInfo) const;

};




PECKER_END

#endif //PECKER_OPENGLES_DEVICE_H_