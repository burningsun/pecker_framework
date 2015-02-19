/*
 * pfx_android_load_pfx.h
 *
 *  Created on: 2015-2-19
*      Author: 李镇城  （ cut / cutxyz） (e-mail: cut-12345@hotmail.com/501931049@qq.com)
 */
#ifndef PFX_ANDROID_LOAD_PFX_H_
#define PFX_ANDROID_LOAD_PFX_H_
#include <dlfcn.h>
#include <android/log.h>
#include <android/native_activity.h>
#include "include/cstring_pfx.h"
#include "native/android_native_form.h"

PECKER_BEGIN
class candroid_application
{
private:
	void* m_handle;
	cstring_ascii_t m_working_lib_name;
public:
	candroid_application();
	~candroid_application();
	result_t init (ANativeActivity* act_ptr);
	result_t load_working_lib (const char* dl_name, int flag);
	result_t close_working_lib ();
	android_native_form::PFX_main_callback enter_point();
	const char* get_working_lib_path () const;
};

PECKER_END

//class cdl_load
//{
//public:
//	static inline cdl_load& dl_load()
//	{
//		static cdl_load __load;
//		return __load;
//	}
//
//	inline int load_dl (JNIEnv* env, const char* dl_name)
//	{
//		__android_log_print(ANDROID_LOG_INFO,
//				__func__,
//				"env  %p",
//				env);
//
//		if (env)
//		{
//			jclass cls_system = env->FindClass("java/lang/System");
//			__android_log_print(ANDROID_LOG_INFO,
//					__func__,
//					"env ->FindClass(env, \"java/lang/System\") %p",
//					cls_system);
//
//			if (cls_system)
//			{
//
//			    //获取System.loadLibrary
//				jmethodID methodID = env->GetMethodID(cls_system, "loadLibrary",
//							"()Ljava/lang/Void;");
//
//				__android_log_print(ANDROID_LOG_INFO,
//									__func__,
//									"env ->GetMethodID(cls_system, \"loadLibrary\"\"()Ljava/lang/Void;\") %p",
//									methodID);
//
//				jstring str_dl_name = env->NewStringUTF(dl_name);
//
//				__android_log_print(ANDROID_LOG_INFO,
//									__func__,
//									"env->NewStringUTF(env, dl_name) %p",
//									str_dl_name);
//
//				env->CallVoidMethod(cls_system, methodID, str_dl_name);
//				__android_log_print(ANDROID_LOG_INFO,
//									__func__,
//									"env->CallVoidMethod(env, cls_system, methodID, str_dl_name)");
//				env->ReleaseStringUTFChars(str_dl_name, dl_name);
//				__android_log_print(ANDROID_LOG_INFO,
//									__func__,
//									"env->ReleaseStringUTFChars)(env, str_dl_name, dl_name)");
//				return 0;
//			}
//		}
//		return -1;
//	}
//public:
//	void* handle;
//public:
//	cdl_load():handle(0)
//	{
//		handle = dlopen("libPFX_CORE_GLES.so", RTLD_NOW);
//		__android_log_print(ANDROID_LOG_INFO,__func__,"dlopen - %sn", dlerror());
//	}
//	~cdl_load()
//	{
//	    if (handle)
//	    {
//	    	dlclose(handle);
//	    }
//	}
//	static inline const char* get_apk_lib_path (ANativeActivity* activity)
//	{
//
//	}
//	inline void* load(const char* dl_name, int flag)
//	{
//		if (handle)
//		{
//			dlclose(handle);
//			handle = 0;
//		}
//		handle = dlopen(dl_name, flag);
//		__android_log_print(ANDROID_LOG_INFO,__func__,"dlopen - %sn", dlerror());
//		return handle;
//	}
//};

#endif //PFX_ANDROID_LOAD_PFX_H_




