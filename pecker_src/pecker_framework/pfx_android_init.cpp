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

#define GET_META_DATA (0x00000080)

class cdl_load
{
private:
	char m_name[256];
public:
	static inline cdl_load& dl_load()
	{
		static cdl_load __load;
		return __load;
	}

	int load_dl (JNIEnv* env, const char* dl_name)
	{
		__android_log_print(ANDROID_LOG_INFO,
				__func__,
				"env  %p",
				env);

		if (env)
		{
			jclass cls_system = env->FindClass("java/lang/System");

			__android_log_print(ANDROID_LOG_INFO,
					__func__,
					"env ->FindClass(env, \"java/lang/System\") %p",
					cls_system);

			if (cls_system)
			{
			    //获取System.loadLibrary
				jmethodID methodID = env->GetMethodID(cls_system, "loadLibrary",
							"(Ljava/lang/String)Ljava/lang/Void;");

				__android_log_print(ANDROID_LOG_INFO,
									__func__,
									"env ->GetMethodID(cls_system, \"loadLibrary\"\"(Ljava/lang/String;)Ljava/lang/Void;\") %p",
									methodID);

				jstring str_dl_name = env->NewStringUTF(dl_name);

				__android_log_print(ANDROID_LOG_INFO,
									__func__,
									"env->NewStringUTF(env, dl_name) %p",
									str_dl_name);

				env->CallVoidMethod(cls_system, methodID, str_dl_name);
				__android_log_print(ANDROID_LOG_INFO,
									__func__,
									"env->CallVoidMethod(env, cls_system, methodID, str_dl_name)");
				env->DeleteLocalRef(str_dl_name);

				__android_log_print(ANDROID_LOG_INFO,
									__func__,
									"env->DeleteLocalRef(str_dl_name)");
				return 0;
			}
		}
		return -1;
	}

};

#endif //PFX_ANDROID_LOAD_PFX_H_




