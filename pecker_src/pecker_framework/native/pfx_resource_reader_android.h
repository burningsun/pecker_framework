﻿/*
 * pfx_resource_reader_windows.h
 *
 *  Created on: 2014-8-10
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_RESOURCE_READER_WINDOWS_H_
#define		PFX_RESOURCE_READER_WINDOWS_H_

#include "../pfx_defines.h"
#if (OS_CONFIG == OS_ANDROID))

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

PECKER_BEGIN

class cresource_reader_android
{
private:

public:
	cresource_reader_android();
	virtual ~cresource_reader_android();

};




PECKER_END
#endif	 // #if (OS_CONFIG == OS_WINDOWS)


#endif			//PFX_RESOURCE_READER_WINDOWS_H_
