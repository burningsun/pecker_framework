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
	result_t init (ANativeActivity* act_ptr,
			const char* str_check_flag_name = "working_lib_in_apk",
			const char* str_lib_name = "working_lib_name");
	result_t load_working_lib (const char* dl_name, int flag);
	result_t close_working_lib ();
	void* func_addr(const char* str_name);
	void* handle ();
	const char* get_working_lib_path () const;
};

PECKER_END

#endif //PFX_ANDROID_LOAD_PFX_H_




