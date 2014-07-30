/*
* window_native_form.h
*
*  Created on: 2014-7-30
*      Author: ¿Ó’Ú≥«  £® cut / cutxyz£©
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/

#ifndef PFX_WINDOWS_NATIVE_FORM_H_
#define PFX_WINDOWS_NATIVE_FORM_H_
#include "../pfx_defines.h"

#include "pfx_native_component.h"

#if (OS_CONFIG == OS_WINDOWS)


PECKER_BEGIN

class PFX_NATIVE_API window_native_form
{
protected:
	static HWND	hwnd_main;
	static LRESULT WINAPI WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	volatile bool m_visiable;
protected:
	HWND		m_hwmd;
	HDC			m_hdc;
	HBITMAP		m_pixelmap;
protected:
	window_native_form* m_parent_form_ptr;
protected:
	activity_init_state_t	m_init_state;
	IActivity_component*	m_component_ptr;
	PFX_ACTIVE_STATUS_t		m_activity_status;
	volatile bool			m_started_window;	
protected:
	result_t	listen_message();
protected:
	LRESULT		on_message(UINT message, WPARAM wParam, LPARAM lParam);
public:
	window_native_form();
	virtual ~window_native_form();
public:
	result_t	init(IActivity_component* activity_ptr, 
		window_native_form* parent_form_ptr = null);
	result_t	dispose();

	result_t	create();
	void 		show(bool fullscreen = false);
	result_t	show_dialog(bool fullscreen = false);
	result_t	close();
	result_t	hide();

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



PECKER_END

#endif//	(OS_CONFIG == OS_WINDOWS)


#endif //PFX_WINDOWS_NATIVE_FORM_H_
