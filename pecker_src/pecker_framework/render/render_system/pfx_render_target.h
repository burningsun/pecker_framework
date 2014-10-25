/*
 * pfx_render_target.h
 *
 *  Created on: 2013-10-28
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RENDER_TARGET_H_
#define		PFX_RENDER_TARGET_H_

#include "../../include/config"
#include "../../include/util"
#include "../../include/cshare_object.h"

PECKER_BEGIN

typedef enum enumRENDER_TARGET_TYPE
{
	PFX_TEXTURE_TAG,
	PFX_RENDER_BUFFER_TAG,
}RENDER_TARGET_TYPE_t;


PFX_Interface  IPfx_rendertarget : public creference_root
{

	virtual result_t dispose_render_target() = 0;
	virtual result_t update_default() = 0;
	virtual result_t bind() = 0;
	virtual bool     check_status() const = 0;
	virtual long_t   get_native_handle() const = 0;
	virtual u64_t    get_version() const = 0;
};



PECKER_END

#endif			//PFX_FRAMEBUFFER_OBJECT_H_
