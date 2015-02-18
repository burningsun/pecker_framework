/*
* pfx_canvus.h
*
*  Created on: 2014-11-11
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#ifndef		PFX_CANVUS_H_
#define		PFX_CANVUS_H_

#include "../render_system/pfx_render_state.h"

#include "pfx_pen.h"
#include "pfx_text_pen.h"
#include "pfx_line_pen.h"

PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

PFX_Interface IPfx_canvus
{
	virtual ~IPfx_canvus(){ ; }
	virtual result_t use_render_state(IPfx_render_state* PARAM_IN render_state_ptr) = 0;
	virtual IPfx_render_state* get_render_state() const = 0;
};

PECKER_END

#endif			//PFX_CANVUS_H_
