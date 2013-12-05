/*
 * pfx_winows_form_test.cpp
 *
 *  Created on: 2013-12-3
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "../native/windows/pfx_view_context_form_for_windows.h"
#include "../render/render_system/opengles2/pfx_windows_display_opengles.h"
#include "../native/pfx_log.h"
USING_PECKER_SDK


class  CmyTestContext : public pfx_windows_context_base
{
private:
	PFX_WINDOWS_INFO_t m_windows_context_info;
	pfx_boolean_t m_exit_render;
protected:
	virtual PFX_WINDOWS_INFO_t& get_context_info_ref () const
	{
		const PFX_WINDOWS_INFO_t& info = m_windows_context_info;
		return (PFX_WINDOWS_INFO_t&)info;
	}

public:
	CmyTestContext():m_exit_render(pfx_false)
	{
		;
	}
	pfx_result_t init_context ()
	{
		pfx_result_t status_ = pfx_windows_context_base::init_context();
		// to do ......
		PFX_WINDOWS_INFO_t& info = get_context_info_ref ();
		info.m_windows_style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		info.m_windows_exstyle = WS_EX_APPWINDOW;
		m_exit_render = pfx_false;
		return status_;
	}

	pfx_result_t on_load_render_resource ()
	{
		PECKER_LOG_INFO ("on load","load render resource,%s","...");
		return PFX_STATUS_OK;
	}
	pfx_result_t on_render_frame (Ipfx_render_device*  PARAM_INOUT graphic_device_,
		const pfx_64bit_t& PARAM_IN escape_tick,
		pfx_double_t last_frame_tick_interval,
		pfx_boolean_t& PARAM_INOUT exit_render)
	{
		exit_render = m_exit_render;
		Ipfx_framebuffer_operation* operation_ = null;

		if (PFX_STATUS_OK == graphic_device_->begin_draw(operation_))
		{
			operation_->clear_color (PFX_RGBA_BITS (200,100,200,255));
			operation_->clear_buffer (0x00000100|0x00004000);
			graphic_device_->end_draw();
		}
		::Sleep(20);
		return PFX_STATUS_OK;
	}
	pfx_result_t on_release_render_resource ()
	{
		return PFX_STATUS_OK;
	}
	pfx_result_t on_close()
	{
		m_exit_render = pfx_true;
		return PFX_STATUS_OK;
	}
	pfx_result_t on_exit()
	{
		m_exit_render = pfx_true;
		return PFX_STATUS_OK;
	}
};


pfx_result_t test_form ()
{
	CmyTestContext context_;
	CPfx_window_form_for_win form_;
	CPfx_windows_display_opengles2 display_;
	//form_.test_ins = ::GetModuleHandle(NULL);
	return IPfx_windows_form::run_windows_program(&form_,&context_,&display_);
}

