/*
 * pecker_render_system_gl.cpp
 *
 *  Created on: 2013-4-30
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#include "pecker_render_system_gl.h"
#include <GLES2/gl2.h>
#include "../../../native/pecker_log.h"

PECKER_BEGIN



static HEnum gRSYS_color_buffer_type_table[RENDER_SYS_PARAM_COLOR_BUFFER_TYPE_COUNT] = {EGL_RGB_BUFFER,EGL_LUMINANCE_BUFFER};

pecker_render_system_gles2::pecker_render_system_gles2():_M_device_is_open(false)
{
	set_bytes_in_bitfield_mask(_M_config._M_color_buffer,0,0,0,RSYS_RGB_BUFFER);
	set_bytes_in_bitfield_mask(_M_config._M_color_bpp,8,8,8,8);
	set_bytes_in_bitfield_mask(_M_config._M_render_buffer,0,0,16,8);
	set_u16_in_bitfield_mask(_M_config._M_sample,4,1);
	set_bytes_in_bitfield_mask(_M_config._M_transparent,0,0,0,0);
	_M_config._M_config_mask = BIT_0_MASK_0_to_31;

	_M_config._M_pbuffer_width = 0;
	_M_config._M_pbuffer_height = 0;
	_M_config._M_back_buffer_size = 0;
	_M_config._M_pback_buffer = null;
}

pecker_render_system_gles2::~pecker_render_system_gles2()
{

}
HResult pecker_render_system_gles2::set_render_system_param(const pecker_render_system_param & sys_param)
{
	_M_config = sys_param;
	return P_OK;
}

Ipecker_render_device* pecker_render_system_gles2::open_render_device(Ipecker_window_display* pwindows_display)
{
	if (null == pwindows_display)
	{
		return null;
	}
	if (_M_device_is_open)
	{
		return &_M_graphic_device;
	}

	_M_config._M_pbuffer_width = pwindows_display->get_width();
	_M_config._M_pbuffer_height = pwindows_display->get_height();

	// 从窗口中获取底层display接口，windows对应的是HDC
	_M_EGLDisplay = eglGetDisplay((EGLNativeDisplayType)(pwindows_display->get_native_display()));
	
	if (EGL_NO_DISPLAY == _M_EGLDisplay)
	{
		_M_EGLDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
	}

	// 获取display失败
	if (EGL_NO_DISPLAY == _M_EGLDisplay)
	{
		return null;
	}

	if(!eglInitialize(_M_EGLDisplay, &_M_MajorVersion, &_M_MinorVersion))
	{
		PECKER_LOG_ERR("Unable to initialise EGL","EGL ERROR %d",eglGetError());
		return null;
	}

	PECKER_LOG_INFO("EGL initialized","EGL %d %d",_M_MajorVersion,_M_MinorVersion);
	
	// 绑定底层渲染API
	if (!eglBindAPI(EGL_OPENGL_ES_API)
	{
		PECKER_LOG_ERR("Unable to bind API EGL","EGL ERROR %d",eglGetError());
		return null;
	}

	pecker_render_system_param backup_config = _M_config;

	do 
	{

	} while (EGL_NO_CONTEXT == _M_EGLContext);
	

	return &_M_graphic_device;
}

HResult pecker_render_system_gles2::close_render_device()
{
	return P_OK;
}

HResult pecker_render_system_gles2::resize_render_display(nSize x,nSize y,nSize width,nSize height,Ipecker_window_display* pwindows_display)
{
	return P_OK;
}

HResult pecker_render_system_gles2::swap_frame_buffer()
{
	//eglWaitGL()
	//eglSwapBuffers()
	return pecker_opengles_v2_object::get_last_error_code();
}
HResult pecker_render_system_gles2::flush_frame_buffer()
{
	glFlush();
	return pecker_opengles_v2_object::get_last_error_code();
}

HResult pecker_render_system_gles2::parse_render_display(Ipecker_window_display* pwindows_display)
{
	return P_OK;
}
HResult pecker_render_system_gles2::resume_render_display(Ipecker_window_display* pwindows_display)
{
	return P_OK;
}
HResult pecker_render_system_gles2::close_render_display(Ipecker_window_display* pwindows_display)
{
	return P_OK;
}

HResult pecker_render_system_gles2::pecker_config_to_egl_config(const pecker_render_system_param& config,rsys_config_stack& P_OUT egl_config)
{
	HEnum config_cmd;
	HEnum config_data;
	egl_config.clear();
	if (config._M_config_ID > 0)
	{
		config_cmd = EGL_CONFIG_ID;
		config_data = config._M_config_ID;
		egl_config.push(config_cmd);
		egl_config.push(config_data);
		config_cmd = EGL_NONE;
		egl_config.push(config_cmd);
		return P_OK;
	}

	config_cmd = EGL_RED_SIZE;
	config_data = get_bitfield_mask(config._M_color_bpp,BIT_0_to_7_MASK_0_to_31);
	egl_config.push(config_cmd);
	egl_config.push(config_data);

	config_cmd = EGL_GREEN_SIZE;
	config_data = get_bitfield_mask(config._M_color_bpp,BIT_8_to_15_MASK_0_to_31);
	egl_config.push(config_cmd);
	egl_config.push(config_data);

	config_cmd = EGL_BLUE_SIZE;
	config_data = get_bitfield_mask(config._M_color_bpp,BIT_16_to_23_MASK_0_to_31);
	egl_config.push(config_cmd);
	egl_config.push(config_data);

	config_cmd = EGL_ALPHA_SIZE;
	config_data = get_bitfield_mask(config._M_color_bpp,BIT_24_to_31_MASK_0_to_31);
	egl_config.push(config_cmd);
	egl_config.push(config_data);

	config_cmd = EGL_DEPTH_SIZE;
	config_data = get_bitfield_mask(config._M_render_buffer,BIT_16_to_23_MASK_0_to_31);
	egl_config.push(config_cmd);
	egl_config.push(config_data);

	config_cmd = EGL_STENCIL_SIZE;
	config_data = get_bitfield_mask(config._M_render_buffer,BIT_24_to_31_MASK_0_to_31);
	egl_config.push(config_cmd);
	egl_config.push(config_data);

	config_cmd = EGL_ALPHA_MASK_SIZE;
	config_data = get_bitfield_mask(config._M_render_buffer,BIT_16_to_23_MASK_0_to_31);
	egl_config.push(config_cmd);
	egl_config.push(config_data);

	config_cmd = EGL_COLOR_BUFFER_TYPE;
	config_data = get_bitfield_mask(config._M_color_buffer,BIT_24_to_31_MASK_0_to_31);
	if (config_data < RENDER_SYS_PARAM_COLOR_BUFFER_TYPE_COUNT)
	{
		config_data = gRSYS_color_buffer_type_table[config_data];
		egl_config.push(config_cmd);
		egl_config.push(config_data);
	}

	if (EGL_LUMINANCE_BUFFER == config_data)
	{
		config_cmd = EGL_LUMINANCE_SIZE;
		config_data = get_bitfield_mask(config._M_color_buffer,BIT_0_to_7_MASK_0_to_31);
		egl_config.push(config_cmd);
		egl_config.push(config_data);
	}

	config_cmd = EGL_SURFACE_TYPE;
	egl_config.push(config_cmd);
	config_data = EGL_WINDOW_BIT;

	if (BIT_0_MASK_0_to_31 | config._M_config_mask)
	{
		config_data |= EGL_PBUFFER_BIT;
	}

	if (BIT_1_MASK_0_to_31 | config._M_config_mask)
	{
		config_data |= EGL_PIXMAP_BIT;
	}
	egl_config.push(config_data);


	config_cmd = EGL_RENDERABLE_TYPE;
	config_data = EGL_OPENGL_ES2_BIT;
	egl_config.push(config_cmd);
	egl_config.push(config_data);

	config_cmd = EGL_NONE;
	egl_config.push(config_cmd);




	return P_OK;
}

PECKER_END

