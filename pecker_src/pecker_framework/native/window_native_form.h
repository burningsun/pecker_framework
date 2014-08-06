/*
* window_native_form.h
*
*  Created on: 2014-7-30
*      Author: 李镇城  （ cut / cutxyz）
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/

#ifndef PFX_WINDOWS_NATIVE_FORM_H_
#define PFX_WINDOWS_NATIVE_FORM_H_
#include "../pfx_defines.h"

//#include "pfx_native_component.h"
#include "../data/pfx_region.h"
#include "../include/cstring"
#include "pfx_thread.h"

#if (OS_CONFIG == OS_WINDOWS)


PECKER_BEGIN

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif

typedef struct PFX_NATIVE_API st_activity_init_state
{
	unsigned m_native_style : 1; // 0 使用m_reverd前的字段初始化，
	// 1 使用m_style，m_extern_style字段初始化 
	unsigned m_fixed_window : 1; // 0 resize ; 1 fixed
	unsigned m_minable : 1; // 最小化
	unsigned m_maxable : 1; // 最大化
	unsigned m_pixlmap : 1;
	unsigned m_reverd : 28;

	bitfield_t		m_style;
	bitfield_t		m_extern_style;

	void*			m_instance_ptr;

	viewport_rect_t	m_windows_rect;
	cstring_ascii_t	m_strtitle;
	cstring_ascii_t m_str_cmdline;

	st_activity_init_state() :m_native_style(0),
		m_fixed_window(1),
		m_minable(0),
		m_maxable(0),
		m_pixlmap(0),
		m_reverd(0),
		m_style(0),
		m_extern_style(0),
		m_instance_ptr(null)
	{
		;
	}
	~st_activity_init_state()
	{
		;
	}
}activity_init_state_t;

typedef enum enumACTIVE_STATUS
{
	PFX_ACTIVE_NO_INIT = 0,
	PFX_ACTIVE_CREATE,
	PFX_ACTIVE_START,
	PFX_ACTIVE_RESTART,
	PFX_ACTIVE_RESUME,
	PFX_ACTIVE_PARSE,
	PFX_ACTIVE_STOP,
	PFX_ACTIVE_DESTROY,
	PFX_ACTIVE_STATUS_COUNT
}PFX_ACTIVE_STATUS_t;

class PFX_NATIVE_API window_native_form
{
public:
	PFX_Interface PFX_NATIVE_API IActivity_component
	{
		virtual ~IActivity_component(){ ; }
		virtual void on_create(activity_init_state_t& PARAM_OUT init_state) = 0;
		virtual void on_start() = 0;
		virtual result_t on_init(window_native_form* PARAM_INOUT active_form_ptr) = 0;
		virtual result_t on_restart() = 0;
		virtual void on_resume() = 0;
		virtual void on_parse() = 0;
		virtual void on_stop() = 0;
		virtual void on_destroy() = 0;

		virtual void on_modify_view() = 0;
		virtual void on_finish_modify_view() = 0;

		virtual	result_t on_event(flag_t message, long_t wParam, long_t lParam) = 0;
	};
protected:
	typedef long (window_native_form::*on_message_translate_callback_t) (proxy_status_t* __proxy_status_ptr);
	typedef thread_proxy < window_native_form, on_message_translate_callback_t >	thread_proxy_t;
protected:
	//static HWND	hwnd_main;
	static LRESULT WINAPI WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	volatile bool m_visiable;
	volatile bool m_benter_size_move;
	volatile bool m_bview_change;
protected:
	HWND		m_hwmd;
	HDC			m_hdc;
	HBITMAP		m_pixelmap;
protected:
	thread_proxy_t	m_msg_trans_proxy;
	thread_t		m_msg_trans_thread;
protected:
	window_native_form* m_parent_form_ptr;
protected:
	activity_init_state_t	m_init_state;
	IActivity_component*	m_component_ptr;
	PFX_ACTIVE_STATUS_t		m_activity_status;
	volatile bool			m_started_window;
	volatile result_t		m_dlg_result;
protected:
	result_t	listen_message();
	long		on_message_translate(proxy_status_t* __proxy_status_ptr);
protected:
	LRESULT		on_message(UINT message, WPARAM wParam, LPARAM lParam);
	result_t	create();
public:
	window_native_form();
	virtual ~window_native_form();
public:
	result_t	init(IActivity_component* activity_ptr, 
		window_native_form* parent_form_ptr = null);
	result_t	dispose();

	
	void 		show(bool fullscreen = false);
	result_t	show_dialog(bool fullscreen = false);
	result_t	close();
	result_t	set_visiable(bool bvisiable, bool bfullscreen = false);

	PFX_INLINE result_t get_dlg_result()  const
	{
		result_t status = m_dlg_result;
		return status;
	}

	PFX_INLINE volatile bool visiable() const
	{
		return m_visiable;
	}
	PFX_INLINE long_t get_native_window() const
	{
		return (long_t)m_hwmd;
	}
	PFX_INLINE long_t get_native_display() const
	{
		return (long_t)m_hdc;
	}
	PFX_INLINE long_t get_native_pixelmap() const
	{
		return (long_t)m_pixelmap;
	}
	PFX_INLINE const activity_init_state_t&	get_activity_state() const
	{
		return m_init_state;
	}

};

#ifdef _MSC_VER
#pragma warning(pop)
#endif


PECKER_END

#endif//	(OS_CONFIG == OS_WINDOWS)


#endif //PFX_WINDOWS_NATIVE_FORM_H_
