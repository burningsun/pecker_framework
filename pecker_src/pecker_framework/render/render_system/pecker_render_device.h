/*
 * pecker_render_device.h
 *
 *  Created on: 2013-4-7
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_RENDER_DEVICE_H_
#define PECKER_RENDER_DEVICE_H_

#include "../pecker_render_object.h"
#include "pecker_gpu_program.h"
#include "pecker_buffer.h"

PECKER_BEGIN

enum DEVICE_INFO_TYPE
{
	VENDOR_INFO = 0,
	RENDERER_INFO,
	VERSION_INFO,
	EXTENSIONS_INFO,
	DEVICE_INFO_TYPE_COUNT
};

PeckerInterface Ipecker_render_device
{
	virtual ~Ipecker_render_device(){;}
	
	virtual Ipecker_gpu_program* create_gpu_program() = 0;
	virtual HResult release_gpu_program(Ipecker_gpu_program* &pgpu_program) = 0;

	virtual Ipecker_graphic_buffer* create_buffer(HEnum buffer_type) = 0;
	virtual HResult release_buffer(Ipecker_graphic_buffer* &pbuffer) = 0;

	virtual Ipecker_frame_buffer_object* create_frame_buffer_object(HEnum object_type,HEnum detail_type) = 0;
	virtual HResult release_frame_buffer_object(Ipecker_frame_buffer_object* &pobject) = 0;

	virtual Ipecker_frame_buffer* create_frame_buffer() = 0;
	virtual HResult release_frame_buffer(Ipecker_frame_buffer* &pframe_buffer) = 0;

	virtual HResult set_viewport(SInt x,SInt y,nSize width,nSize height) = 0;

	virtual HResult set_const_value(HEnum name,HEnum operation_type,nSize nvalue_count,const PVoid P_IN value_) = 0;
	virtual HResult set_value(HEnum name,HEnum operation_type,nSize nvalue_count,PVoid P_IN value_) = 0;

	virtual HResult get_device_info(HEnum info_type,pecker_string& P_OUT strInfo) const= 0;
};


PECKER_END

#endif //PECKER_RENDER_DEVICE_H_