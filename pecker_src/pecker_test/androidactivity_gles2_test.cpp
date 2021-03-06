﻿/*
 * pfx_gles2_displayview_test.cpp
 *
 *  Created on: 2014-3-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#include <stdio.h>
#include "../pecker_framework/native/pfx_native_form.h"
#include "../pecker_framework/native/pfx_log.h"
#include "../pecker_framework/native/pfx_native_activity.h"
#include "../pecker_framework/render/opengles2_render_system.h"

USING_PECKER_SDK

typedef  cnative_activity< cdisplay_context_gles >	opengles2_activity_t;

class  chello_gles_activity : public opengles2_activity_t
{
private:
	int m_iresize_count;
public:
	chello_gles_activity()
	{
		;
	}
	virtual ~chello_gles_activity()
	{
		;
	}
	virtual void on_create(activity_init_state_t& PARAM_OUT init_state)
	{
		opengles2_activity_t::on_create(init_state);
		init_state.m_fixed_window = 0;
		init_state.m_strtitle.init_string("hello activity", strlen("hello activity") + 1);
	}
	virtual void on_start()
	{
		opengles2_activity_t::on_start();
		m_iresize_count = 0;
	}
	virtual void on_finish_modify_view()
	{
		opengles2_activity_t::on_finish_modify_view();
		PECKER_LOG_("resize count = %d\n", m_iresize_count);
	}
};

class chello_opengles_render_view : public 	opengles2_activity_t::IOnRenderView_t
{
private:
	u64_t last_tick;
public:
	chello_opengles_render_view() : last_tick(0)
	{
		;
	}
	virtual ~chello_opengles_render_view(){ ; }

	virtual void on_view(
		const display_device_t& PARAM_IN device,
		opengles2_activity_t::render_state_t& PARAM_INOUT __state,
		u64_t	__escape_time,
		flag_t& PARAM_OUT msg_type,
		usize__t& PARAM_OUT param_size,
		void*& PARAM_OUT param_data_ptr)
	{
		static float_t red_color = 0.7f;
		__state.clear_color(red_color, 0.2f, 0.7f, 1.0f);
		__state.set_clear_mask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		red_color += 0.01;
		if (red_color >= 1.0)
		{
			red_color = 0.0;
		}

		//SleepMS(100);
		//PECKER_LOG_INFO("on_view escape time = %lld",__escape_time);
	    u64_t tick;
	    tick = __escape_time - last_tick;
	    if (tick > 2000)
	    {
	    	PECKER_LOG_INFO("on_view escape time = %lld",__escape_time);
	    	last_tick = __escape_time;
	    }
	}

	virtual void on_load(
		const display_device_t& PARAM_IN device,
		opengles2_activity_t::render_state_t& PARAM_INOUT __state,
		u64_t	__escape_time,
		flag_t& PARAM_OUT msg_type,
		usize__t& PARAM_OUT param_size,
		void*& PARAM_OUT param_data_ptr)
	{
		PECKER_LOG_INFO("on_load escape time = %lld",__escape_time);
	}

	virtual void on_render_complete(
		const display_device_t& PARAM_IN device,
		opengles2_activity_t::render_state_t& PARAM_INOUT __state,
		result_t status)
	{
		
		//PECKER_LOG_INFO("on_render_complete","status time = %d",status);
	}

	virtual void on_closing_render_device(
		u64_t	__escape_time,
		const display_device_t& PARAM_IN device,
		opengles2_activity_t::render_state_t& PARAM_INOUT __state)
	{
		PECKER_LOG_INFO("on_closing_render_device status time = %lld",__escape_time);
	}


	virtual void on_init(window_contex_t& PARAM_OUT win_context)
	{
		opengles2_activity_t::IOnRenderView_t::on_init(win_context);
	}

	virtual void on_log(result_t status, const char_t* str_info_ptr,
		usize__t str_info_length)
	{
		;
	}

	virtual void on_message_box(result_t status, const char_t* str_info_ptr,
		usize__t str_info_length)
	{
		PECKER_LOG_ERR("on_message_box error %s", "str_info_ptr");
	}

};
chello_gles_activity* activity_ptr = new chello_gles_activity();
chello_opengles_render_view* render_view_ptr = new chello_opengles_render_view();

int PFX_main (pecker_sdk::android_native_form* PARAM_INOUT main_form)
{
	activity_ptr->init(render_view_ptr);
	main_form->init(activity_ptr);
	main_form->show_form();
	return 0;
}
