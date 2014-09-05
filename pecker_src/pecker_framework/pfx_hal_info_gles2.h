/*
 * pfx_hal_info_gles2.h
 *
 *  Created on: 2014-7-23
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_HAL_INFO_H_
#define		PFX_HAL_INFO_H_

#include "pfx_defines.h"


#ifndef OPENGLES_VERSION
#define OPENGLES_VERSION (2)
#endif

const instance_version_t& get_hal_instanse_ID_gles2();
#if ((RENDER_SYSTEM_TYPE == OPENGLES_BASE_RENDER_SYSTEM) && RENDER_SYSTEM_VERSION == (2))
extern "C"
{
	PFX_INLINE const instance_version_t& get_hal_instanse_ID()
	{
		return get_hal_instanse_ID_gles2();
	}
}
#endif



#endif			//PFX_HAL_INFO_H_
