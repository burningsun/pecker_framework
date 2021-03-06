﻿/*
 * pfx_window_form_test.cpp
 *
 *  Created on: 2014-7-31
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/native/pfx_native_form.h"
#include "../pecker_framework/native/pfx_log.h"


USING_PECKER_SDK

class helloactivity : public native_form_t::IActivity_component
{
private:
	int m_iresize_count;
public:
	helloactivity(){ ; }
	virtual ~helloactivity(){ ; }
	virtual void on_create(activity_init_state_t& PARAM_OUT init_state)
	{
		init_state.m_fixed_window = 0;
		init_state.m_strtitle.init_string("hello activity", strlen("hello activity") + 1);
	}
	virtual result_t on_init(window_native_form* PARAM_INOUT active_form_ptr)
	{
		return PFX_STATUS_OK;
	}
	virtual void on_start()
	{
		m_iresize_count = 0;
		;
	}
	virtual result_t on_restart()
	{
		return PFX_STATUS_OK;
	}
	virtual void on_resume()
	{
		;
	}
	virtual void on_pause()
	{
		;
	}
	virtual void on_stop()
	{
		;
	}
	virtual void on_destroy()
	{
		;
	}

	virtual void on_modify_view()
	{

		++m_iresize_count;
		;
	}
	virtual void on_finish_modify_view()
	{
		PECKER_LOG_("resize count = %d\n", m_iresize_count);
		;
	}

	virtual	result_t on_event(flag_t message, long_t wParam, long_t lParam)
	{
		return PFX_STATUS_FIN;
	}

	virtual void on_save_instance_state()
	{
		;
	}
	virtual void on_free_instance_state()
	{
		;
	}
	virtual void on_focus_changed(boolean_t bfocus)
	{
		;
	}
	virtual void on_config_changed()
	{
		;
	}
	virtual void on_low_memery()
	{
		;
	}
};

#include <iostream>
void form_test ()
{
	int iwait = 0;
	native_form_t form;
	helloactivity hellow;
	form.init(&hellow);
	//form.create();
	//form.show_dialog(false);
	form.show(false);
	std::cin >> iwait;
	form.set_visiable(false);
	std::cin >> iwait;
	form.set_visiable(true, true);
	std::cin >> iwait;
	form.set_visiable(false);
	std::cin >> iwait;
	form.set_visiable(true, false);
	std::cin >> iwait;
	form.close();
	std::cin >> iwait;
	form.dispose();
}