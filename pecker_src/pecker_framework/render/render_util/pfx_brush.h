/*
* pfx_brush.h
*
*  Created on: 2014-11-11
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#ifndef		PFX_BRUSH_H_
#define		PFX_BRUSH_H_

#include "../../include/config"
#include "../../include/util"
#include "../../include/cshare_object.h"
#include "../pfx_color.h"
#include "../render_system/pfx_shader_program.h"
#include "../../math/pfx_math.h"

PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN

PFX_Interface IPfx_brush : public creference_root
{
	virtual ~IPfx_brush(){ ; }
};
PECKER_END

#endif			//PFX_BRUSH_H_
