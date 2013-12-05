/*
 * pfx_windows_display_opengles.h
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_WINDOWS_DISPLAY_OPENGLES_H_
#define		PFX_WINDOWS_DISPLAY_OPENGLES_H_

#include "../../../native/pfx_view_context_form.h"
#include "pfx_renderdevice_opengles.h"

#ifndef EGLContext
typedef void *EGLContext;
#endif

#ifndef EGLDisplay
typedef void *EGLDisplay;
#endif

#ifndef EGLSurface
typedef void *EGLSurface;
#endif



PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

#define MAX_EGL_CONFIGS_BUFFER_SIZE (256)




class PFX_RENDER_SYSTEM_API CPfx_windows_display_opengles2 :
	public IPfx_windows_display
{
protected:
	IPfx_windows_form* m_form;
	CPfx_render_device_opengles2* m_graphic_device;
protected:
	EGLDisplay	m_EGL_display;
	EGLSurface	m_EGL_window;
	EGLContext m_EGL_context;
	//EGLConfig	m_EGL_config;

	pfx_sint_t		m_major_version;
	pfx_sint_t		m_minor_version;
protected:
	pfx_result_t create_graphic_device ();
	pfx_result_t release_grahic_device ();
protected:
	pfx_result_t egl_init ();
	pfx_result_t egl_close ();
	pfx_result_t egl_swapbuffer ();
public:
	static pfx_bool_t is_egl_externsion_supported (EGLDisplay egl_dispaly,const char* pstr_extension);
public:
	pfx_result_t init_display_device (IPfx_windows_form* PARAM_INOUT windows_form);
	pfx_result_t update_frame (const pfx_64bit_t& PARAM_IN escape_tick,
		pfx_double_t last_frame_tick_interval,
		pfx_boolean_t& PARAM_INOUT exit_render);
	pfx_result_t swap_back_buffer ();
	pfx_result_t close_display_device ();

	CPfx_windows_display_opengles2 ();
	virtual ~CPfx_windows_display_opengles2 ();
};


PECKER_END

#endif			//PFX_WINDOWS_DISPLAY_OPENGLES_H_
