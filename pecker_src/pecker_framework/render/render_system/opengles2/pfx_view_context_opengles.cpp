/*
 * pfx_view_context_opengles.cpp
 *
 *  Created on: 2013-10-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_view_context_opengles.h"

PECKER_BEGIN

pfx_result_t CPfx_window_form_for_win_opengles::_render_thread ()
{
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win_opengles::init_display_device (IPfx_windows_form* PARAM_INOUT windows_form)
{
	if (this != windows_form)
	{
		return PFX_STATUS_DENIED;
	}
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win_opengles::on_swap_back_buffer ()
{
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_window_form_for_win_opengles::close_display_device ()
{
	return PFX_STATUS_OK;
}

PECKER_END


