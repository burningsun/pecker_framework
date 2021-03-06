/*
* pfx_native_activity.h
*
*  Created on: 2014-7-30
*      Author: �����  �� cut / cutxyz��
*		e-mail: cut-12345@hotmail.com
*              501931049@qq.com
*/
#ifndef PFX_NATIVE_ACTIVITY_H_
#define PFX_NATIVE_ACTIVITY_H_


#include "pfx_native_form.h"
#include "../render/pfx_on_context_view.h"
#include "pfx_log.h"
PECKER_BEGIN

template < class display_context >
class PFX_NATIVE_TEMPLATE_API cnative_activity : public native_form_t::IActivity_component
{
public:
	//typedef typename display_context::cOn_render_view_t IOnRenderView_t;
	typedef typename display_context::render_state_t	render_state_t;
	typedef cOn_render_view_base< render_state_t >		IOnRenderView_t;
protected:
	native_form_t*		m_active_form_ptr;
	IOnRenderView_t*	m_render_view_ptr;
	display_context		m_display_context;
	
protected:
	PFX_INLINE result_t set_render_view(IOnRenderView_t* render_view_ptr)
	{
		if (!render_view_ptr)
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
		m_display_context.close_view();
		m_render_view_ptr = render_view_ptr;
		if (m_active_form_ptr)
		{
			window_contex_t win_context;
			win_context.m_hwnd = m_active_form_ptr->get_native_window();
			win_context.m_hdc = m_active_form_ptr->get_native_display();
			win_context.m_hpixelmap = m_active_form_ptr->get_native_pixelmap();
			win_context.m_viewport = m_active_form_ptr->get_activity_state().m_windows_rect;

			m_render_view_ptr->set_window_context(win_context);
		}
		return PFX_STATUS_OK;
	}
public:
	cnative_activity() :m_active_form_ptr(null),
		m_render_view_ptr(null)
	{
		;
	}
	virtual ~cnative_activity()
	{ 
		if (m_render_view_ptr)
		{
			m_render_view_ptr->set_exit(true);
		}
		m_render_view_ptr = null;
		m_active_form_ptr = null;
	}

	virtual result_t init(IOnRenderView_t* render_view_ptr)
	{
		return set_render_view(render_view_ptr);
	}

	virtual void on_create(activity_init_state_t& PARAM_OUT init_state)
	{
		init_state.m_fixed_window = true;
		init_state.m_windows_rect = viewport_rect_t(100, 100, 800, 600);
	}
	virtual result_t on_init(native_form_t* PARAM_INOUT active_form_ptr)
	{
		result_t status;
		if (!active_form_ptr)
		{
			return PFX_STATUS_INVALID_PARAMS;
		}
		if (m_render_view_ptr)
		{
			m_render_view_ptr->set_hideview(true);
		}
		m_display_context.close_view();

		status = PFX_STATUS_UNINIT;
		if (m_render_view_ptr)
		{
			window_contex_t win_context;
			win_context.m_hwnd = active_form_ptr->get_native_window();
			win_context.m_hdc = active_form_ptr->get_native_display();
			win_context.m_hpixelmap = active_form_ptr->get_native_pixelmap();
			win_context.m_viewport = active_form_ptr->get_activity_state().m_windows_rect;
			m_active_form_ptr = active_form_ptr;
			m_render_view_ptr->set_window_context(win_context);
			m_render_view_ptr->set_hideview(false);
			m_render_view_ptr->set_exit(false);
			m_render_view_ptr->set_resize(false);

			PECKER_LOG_STR("m_display_context.show_view ing\n");

			status = m_display_context.show_view(m_render_view_ptr);
			if (status)
			{
				PECKER_LOG_ERR("m_display_context.show_view",
						"status = %d", (int)status);
				m_display_context.close_view();
			}
		}
		return status;
	}
	virtual void on_start()
	{
		return;
	}
	virtual result_t on_restart()
	{
		result_t status;
		if (m_render_view_ptr)
		{
			m_render_view_ptr->set_hideview(false);
			m_render_view_ptr->set_exit(false);
		}
		m_display_context.close_view();
		status = PFX_STATUS_UNINIT;
		if (m_render_view_ptr && m_active_form_ptr)
		{
			window_contex_t win_context;
			win_context.m_hwnd = m_active_form_ptr->get_native_window();
			win_context.m_hdc = m_active_form_ptr->get_native_display();
			win_context.m_hpixelmap = m_active_form_ptr->get_native_pixelmap();
			win_context.m_viewport = m_active_form_ptr->get_activity_state().m_windows_rect;

			m_render_view_ptr->set_window_context(win_context);
			m_render_view_ptr->set_hideview(false);
			m_render_view_ptr->set_exit(false);
			m_render_view_ptr->set_resize(false);
			status = m_display_context.show_view(m_render_view_ptr);
			if (status)
			{
				PECKER_LOG_ERR("m_display_context.show_view",
						"status = %d", (int)status);
				m_display_context.close_view();
			}
		}
		return status;
	}
	virtual void on_resume()
	{
		if (m_render_view_ptr)
		{
			//m_render_view_ptr->set_hideview(false);
		}
	}
	virtual void on_pause()
	{ 
		if (m_render_view_ptr)
		{
			//m_render_view_ptr->set_hideview(true);
		}
	}
	virtual void on_stop()
	{
		if (m_render_view_ptr)
		{
			//m_render_view_ptr->set_hideview(true);
		}
	}
	virtual void on_destroy()
	{
		result_t status;
		if (m_render_view_ptr)
		{
			m_render_view_ptr->set_exit(true);
		}
		status = m_display_context.close_view();

		PECKER_LOG_INFO("on_destory..close_view = %d",
				status);
	}

	virtual void on_modify_view()
	{
		if (m_render_view_ptr)
		{
			m_render_view_ptr->set_hideview(true);
			m_render_view_ptr->set_resize(true);
			uindex_t  time_out_count = 50;
			while (time_out_count)
			{	
				if (m_render_view_ptr->is_hide_complate())
				{
					break;
				}
				SleepMS(100);
				--time_out_count;
			}
			PECKER_LOG_INFO("time_out_count=%d, is_hide_complate=%d",
					time_out_count,
					m_render_view_ptr->is_hide_complate());
		}
	}
	virtual void on_finish_modify_view()
	{
		if (m_render_view_ptr)
		{
			window_contex_t win_context;
			win_context.m_hwnd = m_active_form_ptr->get_native_window();
			win_context.m_hdc = m_active_form_ptr->get_native_display();
			win_context.m_hpixelmap = m_active_form_ptr->get_native_pixelmap();
			win_context.m_viewport = m_active_form_ptr->get_activity_state().m_windows_rect;

			m_render_view_ptr->set_window_context(win_context);

			m_render_view_ptr->set_hideview(false);
			m_render_view_ptr->set_resize(false);
			PECKER_LOG_INFO("is_hide_complate=%d",
					m_render_view_ptr->is_hide_complate());
		}
	}

	virtual	result_t on_event(flag_t message, long_t wParam, long_t lParam)
	{
		return PFX_STATUS_FIN;
	}

	virtual void on_save_instance_state ()
	{
		;
	}
	virtual void on_free_instance_state ()
	{
		;
	}
	virtual void on_focus_changed (boolean_t bfocus)
	{
		PECKER_LOG_INFO("on focus %p %d",m_render_view_ptr,bfocus);
		if (m_render_view_ptr)
		{
			//m_render_view_ptr->set_pause_render(!bfocus);
		}
	}
	virtual void on_config_changed()
	{
		;
	}
	virtual void on_low_memery ()
	{
		;
	}
};



PECKER_END




#endif //PFX_NATIVE_COMPONENT_H_
