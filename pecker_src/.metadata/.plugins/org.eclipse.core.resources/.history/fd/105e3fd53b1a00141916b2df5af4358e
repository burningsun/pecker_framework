/*
 * pfx_display_context_gles.h
 *
 *  Created on: 2014-7-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef PFX_DISPLAY_CONTEXT_GLES_H_
#define PFX_DISPLAY_CONTEXT_GLES_H_

#include <gl2.h>
#include <EGL/egl.h>
#include "pfx_hal_info_gles2.h"
#include "pfx_render_state_gles.h"
#include "../../../Include/native"
#include "../../pfx_on_context_view.h"
#include "../../../include/carray"
#include "../../pfx_render_allocator.h"

PECKER_BEGIN



typedef struct stEGL_device
{
	EGLDisplay	m_EGLDisplay;
	EGLSurface	m_EGLWindow;
	EGLContext	m_EGLContext;
	EGLConfig	m_EGLConfig;
	EGLint		m_MajorVersion;
	EGLint		m_MinorVersion;

	stEGL_device() :m_EGLDisplay(null),
		m_EGLWindow(null),
		m_EGLContext(null),
		m_EGLConfig(null),
		m_MajorVersion(0),
		m_MinorVersion(0)
	{
		;
	}
	stEGL_device(const display_device_t& __dev)
	{
		memcpy_s(((byte_t*)this), sizeof(stEGL_device), 
			(byte_t*)&__dev, sizeof(stEGL_device));
	}
}EGL_device_t;

class PFX_RENDER_SYSTEM_API cdisplay_context_gles
{
public:
	typedef cOn_render_view_base < cnative_render_state_gles2 >	cOn_render_view_t;
	typedef cnative_render_state_gles2							render_state_t;
	typedef	window_contex_t										win_contex_t;
protected:
	typedef long_t(cdisplay_context_gles::*on_callback_t)(proxy_status_t* PARAM_INOUT status_ptr);
	typedef thread_proxy< cdisplay_context_gles, on_callback_t > thread_proxy_t;
protected:
	thread_t				m_thread;
	thread_proxy_t			m_thread_proxy;
	cOn_render_view_t*		m_on_render_view_ptr;
	proxy_status_t			m_proxy_status;
	EGL_device_t			m_egl_device;
	EGLint					m_egl_context_ID;
	volatile result_t		m_last_status;
	volatile bool			m_bshow_window;
	volatile usize__t		m_limit_frame_time;
	volatile usize__t		m_last_fp1ks;
public:
	typedef carray< configbuffer_allocator_t > configs_stack_t;
	typedef pecker_simple_allocator< EGLConfig > egl_config_allocator_t;
	typedef carray< egl_config_allocator_t > EGLconfig_list_t;

	static result_t pfx_config_to_egl_config(EGLint egl_context_ID,
		const window_contex_t& PARAM_INOUT __context, 
		configs_stack_t& PARAM_OUT config_list);
	static result_t select_config(EGLint PARAM_INOUT &egl_context_ID,
		EGLDisplay hdc,
		const window_contex_t& PARAM_INOUT __contet,
		EGLConfig& PARAM_OUT selection_config,
		configs_stack_t& PARAM_OUT config_list,
		EGLconfig_list_t& PARAM_OUT __egl_configs);
protected:
	static result_t init_egl_context(window_contex_t& PARAM_INOUT __context,
		EGL_device_t& PARAM_INOUT __egl_device,
		EGLint& PARAM_INOUT contextID,
		configs_stack_t& PARAM_OUT config_list,
		cOn_render_view_t* on_view_ptr);

	static result_t create_egl_device(window_contex_t& PARAM_INOUT __context, 
		EGL_device_t& PARAM_OUT __egl_device,
		EGLint& PARAM_INOUT __contextID,
		cOn_render_view_t* on_view_ptr);

	static result_t destroy_egl_device(
		EGL_device_t& PARAM_OUT __egl_device,
		EGLint& PARAM_INOUT __contextID,
		cOn_render_view_t* on_view_ptr);
	 

	virtual void on_msg(
		const EGL_device_t& PARAM_IN device,
		cnative_render_state_gles2& PARAM_INOUT __state,
		u64_t	__escape_time,
		flag_t& PARAM_OUT msg_type,
		usize__t& PARAM_OUT param_size,
		void*& PARAM_OUT param_data_ptr);

	long_t render(proxy_status_t* PARAM_INOUT status_ptr);
public:
	result_t render_complete(
		const EGL_device_t& PARAM_IN device,
		bool bswap_buffer = true);
public:
	cdisplay_context_gles();
	~cdisplay_context_gles();

	PFX_INLINE volatile usize__t get_fp1ks() const
	{
		return	m_last_fp1ks;
	}
	PFX_INLINE result_t set_limit_fps(usize__t fps)
	{
		if (!fps)
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
		m_limit_frame_time = 1000 / fps;
		m_last_fp1ks = 1000000 / m_limit_frame_time;
		return PFX_STATUS_OK;
	}
	result_t show_view(cOn_render_view_t* PARAM_INOUT on_view_callback_ptr);
	result_t close_view();
};



PECKER_END

#endif //PFX_DISPLAY_CONTEXT_GLES_H_


