/*
* pfx_picture_box.h
*
*  Created on: 2015-2-17
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
*/

#ifndef		PFX_PICTURE_BOX_H_
#define		PFX_PICTURE_BOX_H_

#include "../../include/cshare_object.h"
#include "../render_system/pfx_render_state.h"


PFX_C_EXTERN_BEGIN


PFX_C_EXTERN_END

PECKER_BEGIN



PFX_Interface IPfx_picture_box : public creference_root
{
	virtual ~IPfx_picture_box(){ ; }

};


PECKER_END

#endif			//PFX_PICTURE_BOX_H_
