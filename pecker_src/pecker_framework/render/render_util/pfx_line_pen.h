/*
* pfx_line_pen.h
*
*  Created on: 2015-2-17
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#ifndef		PFX_LINE_PEN_H_
#define		PFX_LINE_PEN_H_

#include "pfx_pen.h"

PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

PFX_Interface IPfx_line_pen : public IPfx_pen
{
	virtual ~IPfx_line_pen(){ ; }

	virtual result_t lineTo(const VECTOR4F_t& next_pos) = 0;
	virtual result_t lineTo(const VECTOR3F_t& next_pos) = 0;
	virtual result_t lineTo(const VECTOR2F_t& next_pos) = 0;

	virtual result_t save_line() = 0;
	virtual result_t clear_all_line() = 0;

	virtual bool has_lines() const = 0;

	virtual result_t clear_line() = 0;

	
};

PECKER_END

#endif			//PFX_LINE_PEN_H_
