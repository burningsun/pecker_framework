/*
 * pfx_api_info_gles2.cpp
 *
 *  Created on: 2014-7-23
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_hal_info_gles2.h"

#if ((RENDER_SYSTEM_TYPE == OPENGLES_BASE_RENDER_SYSTEM) && RENDER_SYSTEM_VERSION == (2))
static instance_version_t gInstance_version = { OPENGLES_BASE_RENDER_SYSTEM, 2, 0, 0 };
#endif

const instance_version_t& get_hal_instanse_ID_gles2()
{
	return gInstance_version;
}
