﻿/*
 * pfx_resource_reader.h
 *
 *  Created on: 2014-8-10
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RESOURCE_READER_H_
#define		PFX_RESOURCE_READER_H_

#include "../pfx_defines.h"

// 用于打包的只读资源

PECKER_BEGIN

#if (OS_CONFIG == OS_WINDOWS)
#include "pfx_resource_reader_windows.h"

typedef cresource_reader_windows 	 cresource_reader_t;

#endif // #if (OS_CONFIG == OS_WINDOWS)

#if (OS_CONFIG == OS_ANDROID)
#include "pfx_resource_reader_android.h"
typedef cresource_reader_android	cresource_reader_t;

#endif // #if (OS_CONFIG == OS_ANDROID)

PECKER_END


#endif			//PFX_RESOURCE_READER_WINDOWS_H_
