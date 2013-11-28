/*
 * pfx_view_context_opengles.cpp
 *
 *  Created on: 2013-10-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_view_context_opengles.h"

PECKER_BEGIN

CPfx_windows_display_opengles2::CPfx_windows_display_opengles2 () : m_form (null)
{
	;
}
CPfx_windows_display_opengles2::~CPfx_windows_display_opengles2 ()
{
	close_display_device();
}
pfx_result_t CPfx_windows_display_opengles2::init_display_device (IPfx_windows_form* PARAM_INOUT windows_form)
{
	RETURN_INVALID_RESULT (null == windows_form,PFX_STATUS_INVALID_PARAMS);
	RETURN_INVALID_RESULT (null != m_form,PFX_STATUS_DENIED);
	m_form = windows_form;
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_windows_display_opengles2::on_swap_back_buffer ()
{
	return PFX_STATUS_OK;
}

pfx_result_t CPfx_windows_display_opengles2::close_display_device ()
{
	m_form = null;
	return PFX_STATUS_OK;
}

PECKER_END


