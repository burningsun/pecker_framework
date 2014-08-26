/*
 * pfx_resource_reader.h
 *
 *  Created on: 2014-8-10
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RESOURCE_READER_H_
#define		PFX_RESOURCE_READER_H_

#include "../pfx_defines.h"

// 用于打包的只读资源



#if (OS_CONFIG == OS_WINDOWS)
#include "pfx_resource_reader_windows.h"

PECKER_BEGIN
typedef cresource_reader_windows         cresource_reader_t;
typedef casset_reader_windows 	         casset_reader_t;
typedef cresource_share_reader_windows_t sresource_reader_t;
typedef casset_share_reader_windows_t    sasset_reader_t;
PECKER_END

#endif // #if (OS_CONFIG == OS_WINDOWS)

#if (OS_CONFIG == OS_ANDROID)
#include "pfx_resource_reader_android.h"

PECKER_BEGIN
typedef cresource_reader_android	cresource_reader_t;
typedef casset_reader_android	    casset_reader_t;
typedef sresource_reader_android_t  sresource_reader_t;
typedef sasset_reader_android_t     sasset_reader_t;

PECKER_END

#endif // #if (OS_CONFIG == OS_ANDROID)




#endif			//PFX_RESOURCE_READER_WINDOWS_H_
