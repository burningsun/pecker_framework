/*
 * pfx_view_context_opengles.h
 *
 *  Created on: 2013-11-24
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_VIEW_CONTEXT_OPENGLES_H_
#define		PFX_VIEW_CONTEXT_OPENGLES_H_

#include "../../../native/pfx_view_context_form.h"

PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

class PFX_RENDER_SYSTEM_API CPfx_windows_display_opengles2 :
	public IPfx_windows_display
{
protected:
	IPfx_windows_form* m_form;
public:
	pfx_result_t init_display_device (IPfx_windows_form* PARAM_INOUT windows_form);
	pfx_result_t on_swap_back_buffer ();
	pfx_result_t close_display_device ();

	CPfx_windows_display_opengles2 ();
	virtual ~CPfx_windows_display_opengles2 ();
};


PECKER_END

#endif			//PFX_VIEW_CONTEXT_OPENGLES_H_
