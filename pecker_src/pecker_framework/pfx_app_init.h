﻿/*
 * pfx_api_info.h
 *
 *  Created on: 2014-1-31
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */

#ifndef		PFX_APP_INIT_H_
#define		PFX_APP_INIT_H_

#include "pfx_defines.h"
#if (OS_CONFIG == OS_WINDOWS) && defined (__APP_MAIN_SHOW__)
#include "native/window_native_form.h"


extern int PFX_main(pecker_sdk::window_native_form* PARAM_INOUT main_form);

int main()
{
	return pecker_sdk::window_native_form::app_main(PFX_main);
}
#else

#ifdef __ANDROID__

#include "native/android_native_form.h"
extern int PFX_main(pecker_sdk::android_native_form* PARAM_INOUT main_form);
void ANativeActivity_onCreate(ANativeActivity* activity,
	void* savedState, size_t savedStateSize)
{
	pecker_sdk::android_native_form::app_main(PFX_main, activity, savedState, savedStateSize);
}
#endif

#endif // #if (OS_CONFIG == OS_WINDOWS) && defined (__APP_MAIN_SHOW__)


#endif			//PFX_APP_INIT_H_
