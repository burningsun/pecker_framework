/*
 * pecker_render_system_gl.h
 *
 *  Created on: 2013-4-30
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_RENDER_SYSTEM_GL_H_
#define PECKER_RENDER_SYSTEM_GL_H_
#include "pecker_opengles_object.h"
#include "../pecker_render_system.h"
#include "pecker_opengles_device.h"
#include "pecker_render_resource_container_gl.h"
#include "../../../data/pecker_stack.h"
#include <EGL/egl.h>

PECKER_BEGIN

#define  EGL_CONFIG_CMD_BUFFER_SIZE 256

typedef pecker_stack_pool_array<HEnum,
																render_system_config_param_allocator_gles2,
																render_system_config_param_pointer_allocator_gles2,
																EGL_CONFIG_CMD_BUFFER_SIZE> rsys_config_stack;


class pecker_render_system_gles2 : public Ipecker_render_system,public virtual pecker_opengles_v2_object
{
private:
	pecker_render_device_gles2 _M_graphic_device;
	Bool	_M_device_is_open;

	EGLDisplay	_M_EGLDisplay;
	EGLSurface	_M_EGLWindow;
	EGLContext	_M_EGLContext;
	EGLConfig	_M_EGLConfig;

	EGLint		_M_MajorVersion;
	EGLint		_M_MinorVersion;
protected:
	pecker_render_system_const_param _M_const_config;
	pecker_render_system_variable_param _M_variable_config;

	Ipecker_window_display* _M_pwindow_display;
private:
	rsys_config_stack _M_optimation_tmp_config_stack1;
	rsys_config_stack _M_optimation_tmp_config_stack2;
public:
	pecker_render_system_gles2();
	virtual ~pecker_render_system_gles2();
	virtual HResult set_render_system_param(const pecker_render_system_const_param & sys_param);
	virtual Ipecker_render_device* open_render_device(Ipecker_window_display* pwindows_display);
	virtual HResult close_render_device();
	
	virtual HResult render_complete();
	virtual HResult flush_frame_buffer(Bool bfinish = false);

	virtual HResult set_param(HEnum update_type, const pecker_render_system_variable_param& sys_param);
	virtual const pecker_render_system_variable_param& get_param(HEnum param_type) const;

	//virtual HResult resize_render_display(nSize x,nSize y,nSize width,nSize height);
	//virtual HResult parse_render_display();
	//virtual HResult resume_render_display();
	//virtual HResult close_render_display();
public:
	static HResult pecker_config_to_egl_config(const pecker_render_system_const_param& config,rsys_config_stack& P_OUT egl_config);
	static Bool is_egl_externsion_supported(EGLDisplay egl_display,const char* pstr_extension);
protected:
	HResult select_config(const pecker_render_system_const_param& config,nINDEX &config_id,EGLConfig &selection_config);
};



PECKER_END

#endif //PECKER_RENDER_SYSTEM_H_