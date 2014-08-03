/*
* pfx_native_component.h
*
*  Created on: 2014-7-30
*      Author: 李镇城  （ cut / cutxyz）
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/
#ifndef PFX_NATIVE_COMPONENT_H_
#define PFX_NATIVE_COMPONENT_H_
#include "../pfx_defines.h"
#include "../data/pfx_region.h"
#include "../include/cstring"
//#include "pfx_native_component.h"
#include "pfx_native_form.h"


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
	unsigned m_minable		: 1; // 最小化
	unsigned m_maxable		: 1; // 最大化
	unsigned m_pixlmap		: 1;
	unsigned m_reverd		: 28;

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


PFX_Interface PFX_NATIVE_API IActivity_component
{
	virtual ~IActivity_component(){ ; }
	virtual void on_create (activity_init_state_t& PARAM_OUT init_state) = 0;
	virtual void on_start(CNative_form_ptr PARAM_INOUT active_form_ptr) = 0;
	virtual void on_restart ()	= 0;
	virtual void on_resume()	= 0;
	virtual void on_parse()		= 0;
	virtual void on_stop ()		= 0;
	virtual void on_destroy()	= 0;

	virtual void on_modify_view() = 0;
	virtual void on_finish_modify_view() = 0;

	virtual	result_t on_event(flag_t message, long_t wParam, long_t lParam) = 0;
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

PECKER_END




#endif //PFX_NATIVE_COMPONENT_H_
