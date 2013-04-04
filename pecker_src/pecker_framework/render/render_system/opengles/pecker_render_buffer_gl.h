/*
 * pecker_render_buffer_gl.h
 *
 *  Created on: 2013-4-2
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */
#ifndef PECKER_RENDER_BUFFER_GL_H_
#define PECKER_RENDER_BUFFER_GL_H_

#include "pecker_opengles_object.h"
#include "../pecker_render_buffer.h"

PECKER_BEGIN

class pecker_color_buffer_gles2 : public Ipecker_color_buffer,
	public virtual pecker_opengles_v2_object
{
private:
	UInt		_M_gpu_target;
	pecker_render_buffer_info _M_render_buffer_info;
public:
	pecker_color_buffer_gles2();
	virtual ~pecker_color_buffer_gles2();

public:
	HResult attach_by_frame_buffer(PeckerInterface Ipecker_frame_buffer* pframe_buffer,HEnum attach_index = 0); 
	HResult bind();

	HResult allocate_buffer_from_gpu_ram();
	HResult release_buffer_from_gpu_ram();
	//HResult set_default_render_buffer_info(const pecker_render_buffer_info& buf_info);
	HResult use_render_buffer_info();
	HResult use_render_buffer_info(const pecker_render_buffer_info& buf_info);
	const pecker_render_buffer_info& get_render_buffer_info() const;
public:
	virtual UInt get_object_location() const;
};

class pecker_depth_buffer_gles2 : public Ipecker_depth_buffer,
	public virtual pecker_opengles_v2_object
{
private:
	UInt		_M_gpu_target;
	pecker_render_buffer_info _M_render_buffer_info;
public:
	pecker_depth_buffer_gles2();
	virtual ~pecker_depth_buffer_gles2();

public:
	HResult attach_by_frame_buffer(PeckerInterface Ipecker_frame_buffer* pframe_buffer,HEnum attach_index = 0); 
	HResult bind();

	HResult allocate_buffer_from_gpu_ram();
	HResult release_buffer_from_gpu_ram();
	//HResult set_default_render_buffer_info(const pecker_render_buffer_info& buf_info);
	HResult use_render_buffer_info();
	HResult use_render_buffer_info(const pecker_render_buffer_info& buf_info);
	const pecker_render_buffer_info& get_render_buffer_info() const;
public:
	virtual UInt get_object_location() const;
};

class pecker_stencil_buffer_gles2 : public Ipecker_stencil_buffer,
	public virtual pecker_opengles_v2_object
{
private:
	UInt		_M_gpu_target;
	pecker_render_buffer_info _M_render_buffer_info;

public:
	pecker_stencil_buffer_gles2();
	virtual ~pecker_stencil_buffer_gles2();

public:
	HResult attach_by_frame_buffer(PeckerInterface Ipecker_frame_buffer* pframe_buffer,HEnum attach_index = 0); 
	HResult bind();

	HResult allocate_buffer_from_gpu_ram();
	HResult release_buffer_from_gpu_ram();
	//HResult set_default_render_buffer_info(const pecker_render_buffer_info& buf_info);
	HResult use_render_buffer_info();
	HResult use_render_buffer_info(const pecker_render_buffer_info& buf_info);
	const pecker_render_buffer_info& get_render_buffer_info() const;
public:
	virtual UInt get_object_location() const;
};

PECKER_END

#endif //PECKER_RENDER_BUFFER_GL_H_