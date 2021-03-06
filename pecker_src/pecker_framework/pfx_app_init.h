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

#ifdef _WINDOWS	  // windows 窗口程序
#pragma comment(linker,"/SUBSYSTEM:WINDOWS")
int WINAPI WinMain
(
HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPSTR lpCmdLine,
int nCmdShow
)
#else  			  // windows 控制台程序
//_CONSOLE
#pragma comment(linker,"/SUBSYSTEM:CONSOLE")
int main()
#endif	//#ifdef _WINDOWS
{
	return pecker_sdk::window_native_form::app_main(PFX_main);
}


#else

#if (defined(__ANDROID__))

#if (!defined(PURE_NATIVE_CODE))
#include "native/android_native_form.h"

//#include "pfx_android_load_pfx.h"
extern int PFX_main(pecker_sdk::android_native_form* PARAM_INOUT main_form);
void ANativeActivity_onCreate(ANativeActivity* activity,
	void* savedState, size_t savedStateSize)
{
//	__android_log_print(ANDROID_LOG_INFO,
//						__func__,
//						"%p, %p, %d",
//						activity,
//						savedState,
//						savedStateSize);

	//cdl_load::dl_load().load_dl(activity->env, "PFX_CORE_GLES_S");
	pecker_sdk::android_native_form::app_main(PFX_main, activity, savedState, savedStateSize);
}
#else //if (!defined(PURE_NATIVE_CODE))
#include "native/android_native_form.h"

int PFX_main(pecker_sdk::android_native_form* PARAM_INOUT main_form);

#endif	//if (!defined(PURE_NATIVE_CODE))

#endif	// #ifdef __ANDROID__

#endif // #if (OS_CONFIG == OS_WINDOWS) && defined (__APP_MAIN_SHOW__)


#endif			//PFX_APP_INIT_H_
