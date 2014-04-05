/*
 * pfx_api_info.cpp
 *
 *  Created on: 2014-1-31
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#include "pfx_api_info.h"

static pfx_version_t gVersion = {1,0,0,0};
const pfx_version_t& get_pecker_api_version ()
{
	return gVersion;
}